#include "file_ah9837.h"


void BellWrite(int high)
{
	if(high)
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_bell, PIN_bell);
	else
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_bell, 0);
}



void  PIN_Tpower_relay(uint16 flag)
 {
    if(flag)
		GPIOPinWrite(PORT_HOT, PIN_HOT, PIN_HOT);
	else
		GPIOPinWrite(PORT_HOT, PIN_HOT, 0);
 
 }

void  PIN_Tpwm_Write(uint16 flag)
 {
 /*
    if(flag)
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_PA4,PIN_PA4);//PIN_Tpwm, PIN_Tpwm);
	else
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_PA4, 0);
  */
   if(flag)
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_cover2,PIN_cover2);//PIN_Tpwm, PIN_Tpwm);
	else
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_cover2, 0);
 
 }

void  PIN_TDA7367stand_Write(uint16 flag)
 {
    if(flag==ETDA7367work_yes)
		GPIOPinWrite(GPIO_PORTJ_BASE,  PIN_PJ1, 0 );
	else
		GPIOPinWrite(GPIO_PORTJ_BASE,  PIN_PJ1, PIN_PJ1);
 
 }


void  PIN_DCAC_pwm(uint16 flag)
 {
    if(flag==EDC_power)
		{
		// PIN_TDA7367stand_Write(ETDA7367work_no);
		 GPIOPinWrite(GPIO_PORTD_BASE, PIN_VoutChoose, 0);
		 GPIOPinWrite(GPIO_PORTJ_BASE, PIN_Vchoose, 0);
    	} 
	else
	   {
		 GPIOPinWrite(GPIO_PORTD_BASE, PIN_VoutChoose, PIN_VoutChoose);
		 GPIOPinWrite(GPIO_PORTJ_BASE, PIN_Vchoose,PIN_Vchoose);
		// PIN_TDA7367stand_Write(ETDA7367work_yes);
	   }
 }




void  PIN_OILclear_relay(uint16 flag)
 {
    if(flag)
		{
		 GPIOPinWrite(GPIO_PORTJ_BASE, PIN_OilClear, PIN_OilClear);
		
    	} 
	else
		{
		 GPIOPinWrite(GPIO_PORTJ_BASE, PIN_OilClear, 0);
		}

 }




void I2C1Init(void)   //24c32
/*Act as Master*/
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    I2CMasterInitExpClk(I2C1_MASTER_BASE,SysCtlClockGet(),EI2C_100k);

	
}




void T2Init_HOT(uint32 longtime)
 {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_32_BIT_PER|TIMER_CFG_A_PERIODIC);
	//TimerPrescaleMatchSet(TIMER2_BASE, TIMER_A, SysCtlClockGet()/0x10000);
    TimerLoadSet(TIMER2_BASE, TIMER_A,longtime); //
   // TimerControlTrigger(TIMER2_BASE, TIMER_A,true);
    TimerEnable(TIMER2_BASE, TIMER_A);


 }

void T0Init_sample(uint32 Periodic)
 {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_16_BIT_PAIR|TIMER_CFG_A_PERIODIC);
	TimerPrescaleMatchSet(TIMER0_BASE, TIMER_A,0x00 );//SysCtlClockGet()/(Periodic*sample_nub))/0x10000);
    TimerLoadSet(TIMER0_BASE, TIMER_A, Periodic); //
    
    TimerEnable(TIMER0_BASE, TIMER_A);

 }


/*
void T1Init_FRE(void)
 {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_32_BIT_PER);
	TimerLoadSet(TIMER1_BASE, TIMER_A, 0xffffffff);
   

 }
*/
void T1Init_LM331(void)
 {
   SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
   GPIOPinConfigure(GPIO_PC4_CCP2 ); 
   GPIOPinTypeTimer(GPIO_PORTC_BASE, PIN_Toil);
   TimerConfigure(TIMER1_BASE, TIMER_CFG_16_BIT_PAIR|TIMER_CFG_A_CAP_COUNT);
  // TimerControlEvent(TIMER1_BASE,TIMER_B,TIMER_EVENT_POS_EDGE);
   TimerControlEvent(TIMER1_BASE, TIMER_A,TIMER_EVENT_BOTH_EDGES);
   TimerLoadSet(TIMER1_BASE, TIMER_A, 0xffff );
   TimerPrescaleMatchSet(TIMER1_BASE, TIMER_A,0x00 );
   TimerMatchSet(TIMER1_BASE, TIMER_A,0x00 );
   TimerEnable(TIMER1_BASE, TIMER_A);
}









void IoPortInit(void)
{
	//
	// Enable the GPIO block.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
      // 要解锁只需要在配置GPIO前加入下面代码就可以了：

   // Unlock GPIO Commit GPIOAFSEL

   HWREG(GPIO_PORTB_BASE + GPIO_O_LOCK) = 0x4C4F434B;
  

   // Manually Write CR Register for PB7

   HWREG(GPIO_PORTB_BASE + GPIO_O_CR) |= (1 << 7);

 //  HWREG(GPIO_PORTB_BASE + GPIO_O_LOCK) = 0x1;

	


	
	//
	// Set GPIO D7 as an output.  This drives an LED on the board that will
	// toggle when a watchdog interrupt is processed.
	//
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, PIN_bell|PIN_Tpwm);
	//GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, PIN_ADC_CNVST );
	//GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, PIN_Twarn);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, PIN_VoutChoose);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, PIN_cover2 );
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, PIN_WR6963| PIN_RD6963|  PIN_CD6963|PIN_CE6963);
	GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, PIN_PG0|PIN_PG1|PIN_PG2|PIN_PG3|PIN_PG4|PIN_PG5|PIN_PG6|PIN_PG7);
    //GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, PIN_CE6963|PIN_CD6963|PIN_RD6963|PIN_WR6963);
    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, PIN_HOT|PIN_Vchoose|PIN_OilClear|PIN_ACstand);


//	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, FREN_pin |FREX_pin );
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,PIN_Krest|PIN_Kok|PIN_Kup|PIN_Kback);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,PIN_Twarn);
//	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, PIN_KEY1 | PIN_KEY2 | PIN_KEY3 | PIN_KEY4);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, PIN_cover1);
//	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, PIN_ISP2);
//	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, PIN_ADC_DOUTA );
	GPIOPinTypeGPIOInput(GPIO_PORTH_BASE,PIN_Kright|PIN_Kstart|PIN_Kleft|PIN_Kdown);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,PIN_ACwrong|PIN_GND|PIN_HZ220);


}

void Uart1Init(uint32 bsp)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC6_U1RX);
    GPIOPinConfigure(GPIO_PC7_U1TX);
	GPIOPinTypeUART(GPIO_PORTC_BASE, PIN_uart1Rx| PIN_uart1Tx);
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), bsp,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

	//UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
	//IntEnable(INT_UART1);
}

void Uart2Init(uint32 bsp)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinConfigure(GPIO_PD0_U2RX);
    GPIOPinConfigure(GPIO_PD1_U2TX);
	GPIOPinTypeUART(GPIO_PORTD_BASE, PIN_uart2Rx| PIN_uart2Tx);
	UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), bsp,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

	UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
	IntEnable(INT_UART2);
}


void Uart0Init(uint32 bsp)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), bsp,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
	IntEnable(INT_UART0);
}


int Uart0Send(u8 send_data)
{
 #ifdef _GLOBAL_DEBUG_ENABLE
	if(send_data == '\n')
		{
		UARTCharPut(UART0_BASE, '\r');
		}
 #endif
	UARTCharPut(UART0_BASE, send_data);
	return send_data;
}



//#define TIMER_FREQ  200   // 200Hz

void TimerInit(void)
{
	//
	// Set up and enable the SysTick timer.  It will be used as a reference
	// for the delay loop.  
	//
	SysTickPeriodSet(SysCtlClockGet()/TIMER_FREQ );
	SysTickIntEnable();
	SysTickEnable();
}


/*
// #define  _DETECT_UPDATE_PIN
 void SystemInit(uint32 SYSCTL_SYSDIV )
{
	SysCtlClockSet(SYSCTL_SYSDIV| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);	// 50MHz=200M/SYSCTL_SYSDIV_4

	IoPortInit();	  //IO口初始化
	Uart0Init();
	ADCBAT_init();
    T2Init_BAT();

}*/




