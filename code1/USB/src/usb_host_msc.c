#define SYSLOG 0

#include "file_ah9837.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/usb.h"
#include "driverlib/interrupt.h"
#include "usblib/usblib.h"
#include "usblib/usbmsc.h"
#include "usblib/host/usbhost.h"
#include "usblib/host/usbhmsc.h"
#include "ff.h"

#include "macro.h"
#include "debug.h"
#include "user_usb.h"
#include "usb_host_msc.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define TICKS_PER_SECOND 100
#define MS_PER_SYSTICK (1000 / TICKS_PER_SECOND)
/*Date copy to msc enable flag*/
unsigned char EeToUsbState=0; 
/* */
unsigned char MSC_Flag;

void EepromToUsb(void);
//*****************************************************************************
//
// Our running system tick counter and a global used to determine the time
// elapsed since last call to GetTickms().
//
//*****************************************************************************
unsigned long g_ulSysTickCount;
unsigned long g_ulLastTick;

//*****************************************************************************
//
// Defines the size of the buffers that hold the path, or temporary data from
// the memory card.  There are two buffers allocated of this size.  The buffer
// size must be large enough to hold the longest expected full path name,
// including the file name, and a trailing null character.
//
//*****************************************************************************
#define PATH_BUF_SIZE   80


//*****************************************************************************
//
// This buffer holds the full path to the current working directory.  Initially
// it is root ("/").
//
//*****************************************************************************
static char g_cCwdBuf[PATH_BUF_SIZE] = "/";

//*****************************************************************************
//
// A temporary data buffer used when manipulating file paths, or reading data
// from the memory card.
//
//*****************************************************************************
static char g_cTmpBuf[PATH_BUF_SIZE];

//*****************************************************************************
//
// Current FAT fs state.
//
//*****************************************************************************
static FATFS g_sFatFs;
static DIR g_sDirObject;
static FILINFO g_sFileInfo;
static FIL g_sFileObject;

//*****************************************************************************
//
// A structure that holds a mapping between an FRESULT numerical code,
// and a string representation.  FRESULT codes are returned from the FatFs
// FAT file system driver.
//
//*****************************************************************************
typedef struct
{
    FRESULT fresult;
    char *pcResultStr;
}
tFresultString;

//*****************************************************************************
//
// A macro to make it easy to add result codes to the table.
//
//*****************************************************************************
#define FRESULT_ENTRY(f)        { (f), (#f) }

//*****************************************************************************
//
// A table that holds a mapping between the numerical FRESULT code and
// it's name as a string.  This is used for looking up error codes for
// printing to the console.
//
//*****************************************************************************
tFresultString g_sFresultStrings[] =
{
    FRESULT_ENTRY(FR_OK),
    FRESULT_ENTRY(FR_NOT_READY),
    FRESULT_ENTRY(FR_NO_FILE),
    FRESULT_ENTRY(FR_NO_PATH),
    FRESULT_ENTRY(FR_INVALID_NAME),
    FRESULT_ENTRY(FR_INVALID_DRIVE),
    FRESULT_ENTRY(FR_DENIED),
    FRESULT_ENTRY(FR_EXIST),
    FRESULT_ENTRY(FR_RW_ERROR),
    FRESULT_ENTRY(FR_WRITE_PROTECTED),
    FRESULT_ENTRY(FR_NOT_ENABLED),
    FRESULT_ENTRY(FR_NO_FILESYSTEM),
    FRESULT_ENTRY(FR_INVALID_OBJECT),
    FRESULT_ENTRY(FR_MKFS_ABORTED)
};

//*****************************************************************************
//
// A macro that holds the number of result codes.
//
//*****************************************************************************
#define NUM_FRESULT_CODES (sizeof(g_sFresultStrings) / sizeof(tFresultString))

//*****************************************************************************
//
// The size of the host controller's memory pool in bytes.
//
//*****************************************************************************
#define HCD_MEMORY_SIZE         128

//*****************************************************************************
//
// The memory pool to provide to the Host controller driver.
//
//*****************************************************************************
unsigned char g_pHCDPool[HCD_MEMORY_SIZE];

//*****************************************************************************
//
// The instance data for the MSC driver.
//
//*****************************************************************************
unsigned long g_ulMSCInstance = 0;

//*****************************************************************************
//
// Declare the USB Events driver interface.
//
//*****************************************************************************
DECLARE_EVENT_DRIVER(g_sUSBEventDriver, 0, 0, USBHCDEvents);

//*****************************************************************************
//
// The global that holds all of the host drivers in use in the application.
// In this case, only the MSC class is loaded.
//
//*****************************************************************************
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_USBHostMSCClassDriver,
    &g_sUSBEventDriver
};

//*****************************************************************************
//
// This global holds the number of class drivers in the g_ppHostClassDrivers
// list.
//
//*****************************************************************************
#define NUM_CLASS_DRIVERS       (sizeof(g_ppHostClassDrivers) /               \
                                 sizeof(g_ppHostClassDrivers[0]))

//*****************************************************************************
//
// Hold the current state for the application.
//
//*****************************************************************************
typedef enum
{
    //
    // No device is present.
    //
    STATE_NO_DEVICE,

    //
    // Mass storage device is being enumerated.
    //
    STATE_DEVICE_ENUM,

    //
    // Mass storage device is ready.
    //
    STATE_DEVICE_READY,

    //
    // An unsupported device has been attached.
    //
    STATE_UNKNOWN_DEVICE,

    //
    // A power fault has occurred.
    //
    STATE_POWER_FAULT
}
tState;
volatile tState g_eState;
volatile tState g_eUIState;

//*****************************************************************************
//
// The control table used by the uDMA controller.  This table must be aligned
// to a 1024 byte boundary.  In this application uDMA is only used for USB,
// so only the first 6 channels are needed.
//
//*****************************************************************************
#if defined(ewarm)
#pragma data_alignment=1024
tDMAControlTable g_sDMAControlTable[6];
#elif defined(ccs)
#pragma DATA_ALIGN(g_sDMAControlTable, 1024)
tDMAControlTable g_sDMAControlTable[6];
#else
tDMAControlTable g_sDMAControlTable[6] __attribute__ ((aligned(1024)));
#endif

//*****************************************************************************
//
// The current USB operating mode - Host, Device or unknown.
//
//*****************************************************************************
tUSBMode g_eCurrentUSBMode;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

//*****************************************************************************
//
// This is the handler for this SysTick interrupt.
//
//*****************************************************************************
void Usb_Host_SysTick(void)
{
    //
    // Update our tick counter.
    //
    g_ulSysTickCount++;
}

//*****************************************************************************
//
// This function returns the number of ticks since the last time this function
// was called.
//
//*****************************************************************************
unsigned long
GetTickms(void)
{
    unsigned long ulRetVal;
    unsigned long ulSaved;

    ulRetVal = g_ulSysTickCount;
    ulSaved = ulRetVal;

    if(ulSaved > g_ulLastTick)
    {
        ulRetVal = ulSaved - g_ulLastTick;
    }
    else
    {
        ulRetVal = g_ulLastTick - ulSaved;
    }

    //
    // This could miss a few milliseconds but the timings here are on a
    // much larger scale.
    //
    g_ulLastTick = ulSaved;

    //
    // Return the number of milliseconds since the last time this was called.
    //
    return(ulRetVal * MS_PER_SYSTICK);
}

//*****************************************************************************
//
// USB Mode callback
//
// \param ulIndex is the zero-based index of the USB controller making the
//        callback.
// \param eMode indicates the new operating mode.
//
// This function is called by the USB library whenever an OTG mode change
// occurs and, if a connection has been made, informs us of whether we are to
// operate as a host or device.
//
// \return None.
//
//*****************************************************************************
void
ModeCallback(unsigned long ulIndex, tUSBMode eMode)
{
    //
    // Save the new mode.
    //

    g_eCurrentUSBMode = eMode;
}


void
MSCCallback(unsigned long ulInstance, unsigned long ulEvent, void *pvData)
{
    //
    // Determine the event.
    //
    switch(ulEvent)
    {
        //
        // Called when the device driver has successfully enumerated an MSC
        // device.
        //
        case MSC_EVENT_OPEN:
        {
            //
            // Proceed to the enumeration state.
            //
            g_eState = STATE_DEVICE_ENUM;
            break;
        }

        //
        // Called when the device driver has been unloaded due to error or
        // the device is no longer present.
        //
        case MSC_EVENT_CLOSE:
        {
            //
            // Go back to the "no device" state and wait for a new connection.
            //
            g_eState = STATE_NO_DEVICE;

            break;
        }

        default:
        {
            break;
        }
    }
}

//*****************************************************************************
//
// This is the generic callback from host stack.
//
// \param pvData is actually a pointer to a tEventInfo structure.
//
// This function will be called to inform the application when a USB event has
// occurred that is outside those related to the mass storage device.  At this
// point this is used to detect unsupported devices being inserted and removed.
// It is also used to inform the application when a power fault has occurred.
// This function is required when the g_USBGenericEventDriver is included in
// the host controller driver array that is passed in to the
// USBHCDRegisterDrivers() function.
//
// \return None.
//
//*****************************************************************************
void
USBHCDEvents(void *pvData)
{
    tEventInfo *pEventInfo;

    //
    // Cast this pointer to its actual type.
    //
    pEventInfo = (tEventInfo *)pvData;

    switch(pEventInfo->ulEvent)
    {
        //
        // New keyboard detected.
        //
        case USB_EVENT_CONNECTED:
        {
            //
            // An unknown device was detected.
            //
            g_eState = STATE_UNKNOWN_DEVICE;

            break;
        }

        //
        // Keyboard has been unplugged.
        //
        case USB_EVENT_DISCONNECTED:
        {
            //
            // Unknown device has been removed.
            //
            g_eState = STATE_NO_DEVICE;

            break;
        }

        case USB_EVENT_POWER_FAULT:
        {
            //
            // No power means no device is present.
            //
            g_eState = STATE_POWER_FAULT;

            break;
        }

        default:
        {
            break;
        }
    }
}

void Usb_Host_Init(void)
{
    //
    // Initially wait for device connection.
    //
	g_eState   = STATE_NO_DEVICE;
    g_eUIState = STATE_NO_DEVICE;
	MSC_Flag   = MSC_OFF;
	//
    // Enable Clocking to the USB controller.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);
	
    //
    // Set the USB pins to be controlled by the USB controller.
    //
    /*
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA6_USB0EPEN);
    GPIOPinConfigure(GPIO_PA7_USB0PFLT); 
	GPIOPinTypeUSBDigital(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7); 
	//GPIOPinTypeUSBDigital(GPIO_PORTH_BASE, GPIO_PIN_3 | GPIO_PIN_4);
	*/
    //
    // Enable the uDMA controller and set up the control table base.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	//uDMAEnable();
	//uDMAControlBaseSet(g_sDMAControlTable);
    uDMAEnable();							
    uDMAControlBaseSet(g_sDMAControlTable);

    //
    // Initialize the USB stack mode and pass in a mode callback.
    //
    USBStackModeSet(0, USB_MODE_OTG, ModeCallback);

    //
    // Register the host class drivers.
    //
    USBHCDRegisterDrivers(0, g_ppHostClassDrivers, NUM_CLASS_DRIVERS);

    //
    // Open an instance of the mass storage class driver.
    //
    g_ulMSCInstance = USBHMSCDriveOpen(0, MSCCallback);	

    //
    // Initialize the power configuration.  This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);
    //
    // Initialize the USB controller for OTG operation with a 2ms polling
    // rate.
    //
    USBOTGModeInit(0, 2000, g_pHCDPool, HCD_MEMORY_SIZE);
	
	//
    // Initialize the file system.
    //
    f_mount(0, &g_sFatFs);
//	USBHostPwrFaultDisable(USB0_BASE);
    //RestUsbInit();
		
}



unsigned long TempTimerUsb=0;

//*****************************************************************************
//
// This function reads a line of text from the UART console.  The USB host main
// function is called throughout this process to keep USB alive and well.
//
//*****************************************************************************
void
Usb_Host_Thread(void)
{
    tState eStateCopy;
    	 
    if(g_eState == STATE_DEVICE_ENUM)
    {
        if(USBHMSCDriveReady(g_ulMSCInstance) != 0)
        {
            //
            // Wait about 100ms before attempting to check if the
            // device is ready again.
            //
            SysCtlDelay(SysCtlClockGet()/30);
        }

        //
        // Reset the working directory to the root.
        //
        g_cCwdBuf[0] = '/';
        g_cCwdBuf[1] = '\0';

        //
        // Attempt to open the directory.  Some drives take longer to
        // start up than others, and this may fail (even though the USB
        // device has enumerated) if it is still initializing.
        //
        f_mount(0, &g_sFatFs);
        if(f_opendir(&g_sDirObject, g_cCwdBuf) == FR_OK)
        {
            //
            // The drive is fully ready, so move to that state.
            //
			
            g_eState = STATE_DEVICE_READY;
        }
    }

    eStateCopy = g_eUIState;
    if(g_eState != eStateCopy)
    {
	   g_eUIState = g_eState; // Save the current state.
        switch(g_eState)
        {
            case STATE_NO_DEVICE:
				// if(MSC_Flag == MSC_ON)SetBeep(BEEP_MODE_PULSE,30,0);
				 MSC_Flag   = MSC_OFF;
                 break;

            case STATE_DEVICE_ENUM:			    
                break;

            case STATE_DEVICE_READY:
				 MSC_Flag = MSC_ON;	
				 EepromToUsb();				 	 
                break;

            case STATE_UNKNOWN_DEVICE:
			    MSC_Flag  = MSC_OFF;
                break;

            case STATE_POWER_FAULT:
			    MSC_Flag   = MSC_OFF;
                break;
        }	  
    }
	USBOTGMain(GetTickms());  

	if(GetSysLinearTimer() > TempTimerUsb)
		{
		 TempTimerUsb = GetSysLinearTimer() + 5000;
		 g_eState   = STATE_NO_DEVICE;
		 g_eUIState = STATE_NO_DEVICE;
	     MSC_Flag   = MSC_OFF;
		 RestUsbInit();/* usb 重新初始化*/
		} 	 		 	        
}

int WritToTxt(UCHAR *p,const char *format,...)
{
	WORD length = 0,i,cnt=0;
	char temp_buffer[128];
	va_list arg_ptr;

	va_start (arg_ptr, format);             /* format string */
	vsprintf (temp_buffer, format, arg_ptr);
	length = strlen(temp_buffer);
	va_end (arg_ptr);
	for(i=0;i<length;i++)
	  {
	   if(temp_buffer[i] == '\n')
	     {
		    *p=0X0D;  p++;
			*p=0X0A;  p++;
			cnt++;
		 }
	   else
	     {
	      *p=temp_buffer[i];
	       p++;
		 }
	  }
	return length+cnt;
}

WORD WritEnter(UCHAR *p)
{
    *p =0X0D;	p++;
	*p =0X0A;	p++;
	return 2;
}

#if 0
WORD WritString(UCHAR *p,const StrType Str)
{
	if(SysParam.Lang)
	    return WritToTxt(p,"%s",Str.StrEn);
	else	    
        return WritToTxt(p,"%s",Str.StrCh);
}
#endif
/*
int WritStrStrVoltage(UCHAR *p,float float_val)
{
	if(float_val < 0.01)
		{
		return WritToTxt(p,"%.3fmV",float_val * 1000);
		}
	else if(float_val < 0.1)
		{
		return WritToTxt(p,"%.2fmV",float_val * 1000);
		}
	else if(float_val < 1)
		{
		return WritToTxt(p,"%.1fmV",float_val * 1000);
		}
	else if(float_val < 10)
		{
		return WritToTxt(p,"%.3fV",float_val);
		}
	else if(float_val < 100)
		{
		return WritToTxt(p,"%.2fV",float_val);
		}
	else if(float_val < 1000)
		{
		return WritToTxt(p,"%.1fV",float_val);
		}
	else
		{
		return WritToTxt(p,"%.3fkV",float_val / 1000);
		}
}


int WritStrResistor(UCHAR *p,float float_val)
{
	if(float_val < 0.01)
		{
		return WritToTxt(p,"%0.3fmΩ",float_val * 1000);
		}
	else if(float_val < 0.1)
		{
		return WritToTxt(p,"%.2fmΩ",float_val * 1000);
		}
	else if(float_val < 1)
		{
		return WritToTxt(p,"%.1fmΩ",float_val * 1000);
		}
	else if(float_val < 10)
		{
		return WritToTxt(p,"%.3fΩ",float_val);
		}
	else if(float_val < 100)
		{
		return WritToTxt(p,"%.2fΩ",float_val);
		}
	else if(float_val < 1000)
		{
		return WritToTxt(p,"%.1fΩ",float_val);
		}
	else
		{
		return WritToTxt(p,"%.2fkΩ",float_val/1000);
		}
}
*/

/* 产品型号 为第一级文件夹 日期为第二级夹 时间为第三级文件 */
/* PH2801 / 年月日  / 时分秒 */

UCHAR StrFile_1_D[]  = "AH9688";
UCHAR StrFile_2_D[]  = "AH9688/20xxxxxx";
UCHAR SaveDataPath[] = "AH9688/20xxxxxx/xx-xx-xx.txt";


static void SaveTxtPathorName(UCHAR *p,RTC_T time)
{
	//if(time.Seconds <= 0x60)  /*  时钟芯片正常运行 */
		//{
		 p += 9;
		*p  =  (time.Year    >>4  )  +0X30;  
		StrFile_2_D[9]=*p;                  p++;
		*p  =  (time.Year    &0x0f)  +0X30;  
		StrFile_2_D[10]=*p;                  p++;
		*p  =  (time.Month   >>4  )  +0X30;  
		StrFile_2_D[11]=*p;                  p++;
		*p  =  (time.Month   &0x0f)  +0X30;  
		StrFile_2_D[12]=*p;                  p++;
		*p  =  (time.Date    >>4  )  +0X30;  
		StrFile_2_D[13]=*p;                  p++; 
		*p  =  (time.Date    &0x0f)  +0X30;  
		StrFile_2_D[14]=*p;                  p++;
		*p  =  '/';                          p++;
	/*  文件名 */	
		*p  =  (time.Hours   >>4  )  +0X30;  p++;
		*p  =  (time.Hours   &0x0f)  +0X30;  p++;
		*p  =  '-';                          p++;
		*p  =  (time.Minutes >>4  )  +0X30;  p++;
		*p  =  (time.Minutes &0x0f)  +0X30;  p++;
		*p  =  '-';                          p++;
		*p  =  (time.Seconds >>4  )  +0X30;  p++;
		*p  =  (time.Seconds &0x0f)  +0X30;  p++;      
	/*  属性 .txt*/
		//}
	//else                   /*  时钟芯片不正常运行 */
		//{
		
		//}
}



UCHAR WriteDateFat32(const char *path,const void *buff,WORD length)
{
#if 1
	f_open  (&g_sFileObject,path,FA_CREATE_NEW);
    if(f_open  (&g_sFileObject,path,FA_WRITE) != FR_OK)
	   return FALSE;
	if(f_lseek (&g_sFileObject,g_sFileObject.fsize) != FR_OK)
	   return FALSE;
	if(f_write (&g_sFileObject,buff,length,0) != FR_OK)
	   return FALSE;
	if(f_close (&g_sFileObject) != FR_OK)
	   return FALSE;
	return TRUE;   	
#else
	DPRINTF(("CREATE=%d\n",f_open(&g_sFileObject,path,FA_CREATE_NEW)));
	DPRINTF(("OPEN=%d\n",f_open(&g_sFileObject,path,FA_WRITE)));
	DPRINTF(("LSEEK=%d\n",f_lseek (&g_sFileObject,g_sFileObject.fsize)));
	DPRINTF(("WRIT=%d\n",f_write (&g_sFileObject,buff,length,0)));
	DPRINTF(("Close=%d\n",f_close (&g_sFileObject)));
#endif
}




#if 1
#define UsbMultBuff 5000		/*当开辟空间太大 程序执行不过去*/
#define UsbHaltMultBuff 512     /*根据上面问题 数据分块写，当计数值大于这个值时写数据*/

uint16 TestDataUsbDisk( WORD cnt ,UCHAR *buffer,RTC_T *Time)
{
	//UCHAR buffer[UsbMultBuff]={0},i,j;
	//WORD cnt;
	unsigned char count;
 
	
	//RTC_T Time;


	
	if(MSC_Flag == MSC_OFF)
	    return ;	
	
	if(EeToUsbState == CLOSE)
		{
		g_eState   = STATE_NO_DEVICE;
		g_eUIState = STATE_NO_DEVICE;
		MSC_Flag   = MSC_OFF;
		RestUsbInit();	
		count = 200;	
		while(count-- && (g_eState != STATE_DEVICE_READY))
			{
			  Usb_Host_Thread();
			  DelayMs(10); 
			}
		if(g_eState != STATE_DEVICE_READY)
			return ;
		}
   /*
	Time.Year  = Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.year));
	Time.Month = Int16_bcd(modbusInt16( timeMT4200_Analyse.mune.month));
	Time.Date  = Int16_bcd(modbusInt16( timeMT4200_Analyse.mune.day));
	
	Time.Hours =  Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.hour));
	Time.Minutes = Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.minute));
	Time.Seconds = Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.second)); 
*/	
	/*命名文件名 START*/
	SaveTxtPathorName(SaveDataPath,*Time);
	f_mkdir(StrFile_1_D);
//	DPRINTF(("%s\n",StrFile_1_D));
	f_mkdir(StrFile_2_D);
//	DPRINTF(("%s\n",StrFile_2_D));
//	DPRINTF(("%s\n",SaveDataPath));

	
	
	
	
	return(WriteDateFat32(SaveDataPath,buffer,cnt));
}
#endif



UCHAR path[]="AH9688/20xxxxxx/xx-xx-xx.txt";

char CompareEepromAndUDisk(RTC_T time)
{
	u8 result=0;
	SaveTxtPathorName(path,time);
	f_mkdir(StrFile_1_D);
	DPRINTF(("%s\n",StrFile_1_D));
	f_mkdir(StrFile_2_D);
	DPRINTF(("%s\n",StrFile_2_D));
	return f_open(&g_sFileObject,path,FA_OPEN_EXISTING);
}
void EepromToUsb(void)
{
	EeToUsbState=OPEN;
	//EepromToUDisk(); //将EEPROM记录数据拷贝到U盘
	EeToUsbState=CLOSE;			  
}
