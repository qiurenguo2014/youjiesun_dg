#ifndef _USB_lm3s
#define _USB_lm3s

//uint32 GetSysLinearTimer(void);
//void SetSysLinearTimer(uint32 timer );

//void DelayMs(u16 ms_value);
//void SysTickHandler(void);
unsigned short usb_stodata(unsigned char  *buffer,RTC_T *Time);
void USbdisk_hander(uint16 flag);

#endif

