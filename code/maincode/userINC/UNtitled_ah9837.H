#ifndef _untitled_ah9837
#define _untitled_ah9837
void  PIN_JUN_relay(uint16 flag);
void  PIN_JUX_relay(uint16 flag);
void  PIN_JUNX_relay(uint16 flag);
void  PIN_JRTG_relay(uint16 flag);
void  PIN_JR_relay(uint16 flag);
void Ad7367CnvstWrite(uint16 flag);
void Ad7367CsWrite(uint16 flag);
void Ad7367SclkWrite(uint16 flag);
void Ad7367AddrWrite(uint16 flag);
void Ad7705RESWrite(uint16 flag);
void Ad7705CSWrite(uint16 flag);

void Ad7705DINWrite(uint16 flag);
void Ad7705SCLKWrite(uint16 flag);


void spi_ad7705Init(void);
void T2Init_BAT(void);
void T0Init_sample(uint32 Periodic);
void T1Init_FRE(void);
void IoPortInit(void);
void Uart1Init(uint32 bsp);
void Uart0Init(uint32 bsp);
int Uart0Send(u8 send_data);
void TimerInit(void);
#endif



