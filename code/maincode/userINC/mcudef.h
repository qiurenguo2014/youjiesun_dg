#ifndef _MCUDEF_H
#define _MCUDEF_H

#include <LM3Sxxxx.H>
#include "LM3S5B91_GPIO.h"

#define WHOLE_PORT (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)


//´®¿Úuart0 --PIN_PA0,PIN_PA1


//AD7367  PA PC  PG 
#define PIN_Uart0RX  	PIN_PA0
#define PIN_Uart0TX		PIN_PA1
#define PIN_AD7705_SCLK	PIN_PA2
#define PIN_AD7705_CS	PIN_PA3
#define PIN_AD7705_DOUT	PIN_PA4
#define PIN_AD7705_DIN	PIN_PA5
#define PIN_AD7705_DRDY	PIN_PA6
#define PIN_AD7705_RST	PIN_PA7
#define  PORT_AD7705    GPIO_PORTA_BASE



#define PIN_AD7367_ADDR	    PIN_PB0
#define PIN_AD7367_BUSY  	PIN_PB1
#define PIN_AD7367_SCLK	    PIN_PB2
#define PIN_AD7367_DOUTB	PIN_PB3
#define PIN_AD7367_CNVST	PIN_PB4
#define PIN_AD7367_CS	    PIN_PB5







#define  PIN_JRTG       PIN_PE4
#define  PIN_JUX        PIN_PE5
#define  PIN_JUNX       PIN_PE6
#define  PIN_JUN        PIN_PE7
#define  PIN_JR         PIN_PJ0

//






#define SSI0_WRITE(m) HWREG(SSI0_BASE + SSI_O_DR) = (m);
#define SSI1_WRITE(m) HWREG(SSI1_BASE + SSI_O_DR) = (m);

#define SSI0_READ(m)     {while(!(HWREG(SSI0_BASE + SSI_O_SR) & SSI_SR_RNE));	\
						*m = HWREG(SSI0_BASE + SSI_O_DR);}
#define SSI1_READ(m)     {while(!(HWREG(SSI1_BASE + SSI_O_SR) & SSI_SR_RNE));	\
						m = HWREG(SSI1_BASE + SSI_O_DR);}

#endif

