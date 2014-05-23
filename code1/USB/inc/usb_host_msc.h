#ifndef __USB_HOST_MSC_H
#define	__USB_HOST_MSC_H

#include "rtc.h"

#define USB_STORE_EN

enum{
OPEN=0X55,		   /*功能标志位使能*/
CLOSE=0XAA		   /*功能标志位关闭*/
};
enum{
MSC_OFF,
MSC_ON
};

extern unsigned char MSC_Flag;
extern unsigned char EeToUsbState;


extern void Usb_Host_SysTick(void);
extern void Usb_Host_Thread(void);
extern void Usb_Host_Init(void);
//void TestDataUsbDisk(RTC_T Time);
uint16 TestDataUsbDisk(unsigned short  cnt ,unsigned char  *buffer,RTC_T *Time);

extern char CompareEepromAndUDisk(RTC_T time);

extern void DelayMs(u16 ms_value);
int WritToTxt(unsigned char *p,const char *format,...);
#endif

