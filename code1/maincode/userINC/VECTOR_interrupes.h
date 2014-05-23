#ifndef _VECTOR_interrupes
#define _VECTOR_interrupes
void DelayMs(u16 ms_value);
uint32 GetSysLinearTimer(void);
void SysTickHandler(void);
void UART0IntHandler(void);
void UART2IntHandler(void);
#endif

