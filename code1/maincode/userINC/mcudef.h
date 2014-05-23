#ifndef _MCUDEF_H
#define _MCUDEF_H

#include <LM3Sxxxx.H>
#include "LM3S5b91_GPIO.h"

#define WHOLE_PORT (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)



//=======PORT_A
#define   PIN_uart0Rx PIN_PA0    // ����uart0  IAP
#define   PIN_uart0Tx PIN_PA1    
//PA2---����
#define  PIN_Upwm   PIN_PA3         //���Ҳ�pwm
#define  PIN_Tpwm   PIN_PA4         //PID����pwm
#define  PIN_bell   PIN_PA5         //������
#define  PIN_fm3125SCL  PIN_PA6     //SCL 
#define  PIN_fm3125SDA  PIN_PA7     //SDA

//======PORT_B
//����  PIN_PB0----PIN_PB3
#define PIN_Krest  PIN_PB4
#define PIN_Kok    PIN_PB5
#define PIN_Kup    PIN_PB6
#define PIN_Kback  PIN_PB7


//=====PORT_C
//����JTAG   PIN_PC0----PIN_PC3
#define PIN_Twarn  PIN_PC5
#define PIN_Toil   PIN_PC4   //LM331--t0
#define PIN_uart1Rx  PIN_PC6   // ����uart1---��ӡ
#define PIN_uart1Tx  PIN_PC7


//====PORT_D
#define PIN_uart2Rx  PIN_PD0   // ����uart2---���԰�
#define PIN_uart2Tx  PIN_PD1
#define PIN_VoutChoose PIN_PD2  //pwm ��ֱ���л�
#define PIN_BOOT     PIN_PD3   //IAP
//����   PIN_PD4----PIN_PD7

//====PORT_E
//����   PIN_PE0----PIN_PE1
#define PIN_cover1   PIN_PE2//pwm ��ֱ���л�
#define PIN_cover2   PIN_PE3   //IAP
//����   PIN_PE4----PIN_PE7


//====PORT_F
#define  PIN_WR6963   PIN_PF0
//����   PIN_PF1----PIN_PF4
#define  PIN_RD6963   PIN_PF5
#define  PIN_CE6963   PIN_PF6
#define  PIN_CD6963   PIN_PF7



//======PIN_PG
#define  PORT_DATA6963  GPIO_PORTG_BASE   //��ʾ��6963
#define  PORT_SET6963   GPIO_PORTF_BASE



//=======PIN_PH
#define PIN_Kright  PIN_PH0
#define PIN_Kstart  PIN_PH1
#define PIN_Kleft   PIN_PH2
#define PIN_Kdown   PIN_PH3
//����   PIN_PH4----PIN_PH7



//=======PIN_PJ
#define PIN_Tpower     PIN_PJ0
#define PIN_ACstand    PIN_PJ1
#define PIN_Vchoose    PIN_PJ2
#define PIN_OilClear   PIN_PJ3
#define PIN_ACwrong    PIN_PJ4
#define PIN_GND        PIN_PJ5
#define PIN_Iover      PIN_PJ6
#define PIN_HZ220      PIN_PJ7

//����   PIN_PH4----PIN_PH7








//=====����
#define  PORTB_key       GPIO_PORTB_BASE
#define  PORTH_key       GPIO_PORTH_BASE
#define  PIN_cover        PIN_cover1
#define  PIN_gan          PIN_GND



//���� lm331   ����T1---ccp2


//����
#define  PORT_HOT      GPIO_PORTJ_BASE
#define  PIN_HOT       PIN_Tpower






#define SSI0_WRITE(m) HWREG(SSI0_BASE + SSI_O_DR) = (m);
#define SSI1_WRITE(m) HWREG(SSI1_BASE + SSI_O_DR) = (m);

#define SSI0_READ(m)     {while(!(HWREG(SSI0_BASE + SSI_O_SR) & SSI_SR_RNE));	\
						*m = HWREG(SSI0_BASE + SSI_O_DR);}
#define SSI1_READ(m)     {while(!(HWREG(SSI1_BASE + SSI_O_SR) & SSI_SR_RNE));	\
						m = HWREG(SSI1_BASE + SSI_O_DR);}

#endif

