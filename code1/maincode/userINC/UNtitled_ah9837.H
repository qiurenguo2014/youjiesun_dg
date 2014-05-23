#ifndef _untitled_ah9837
#define _untitled_ah9837
void BellWrite(int high);
void  PIN_Tpwm_Write(uint16 flag);

void Uart1Init(uint32 bsp);
void I2C1Init(void)  ;


void IoPortInit(void);
void Uart0Init(uint32 bsp);
void Uart1Init(uint32 bsp);
void Uart2Init(uint32 bsp);
void TimerInit(void);
//void SystemInit(uint32 SYSCTL_SYSDIV );
void AdcCnvstWrite(int flag);
void T0Init_sample(uint32 Periodic);
void T1Init_FRE(void);
void T2Init_HOT(uint32 longtime);

int Uart0Send(u8 send_data);
void T1Init_LM331(void);



void  PIN_TDA7367stand_Write(uint16 flag);
void  PIN_OILclear_relay(uint16 flag);
void  PIN_DCAC_pwm(uint16 flag);
void  PIN_Tpower_relay(uint16 flag);

void TimerInit(void);


enum{EI2C_100k,EI2C_400k};
enum{EI2C_send,EI2C_Recv};

#endif



