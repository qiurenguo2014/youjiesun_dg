#include "file_ah9837.h"




void  PIN_JUN_relay(uint16 flag)
 {
    if(flag)
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JUN, PIN_JUN);
	else
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JUN, 0);
 
 }
void  PIN_JUX_relay(uint16 flag)
 {
    if(flag)
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JUX, PIN_JUX);
	else
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JUX, 0);
 
 }

void  PIN_JUNX_relay(uint16 flag)
 {
    if(flag)
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JUNX, PIN_JUNX);
	else
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JUNX, 0);
 
 }

void  PIN_JRTG_relay(uint16 flag)
 {
    if(flag)
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JRTG, PIN_JRTG);
	else
		GPIOPinWrite(GPIO_PORTE_BASE, PIN_JRTG, 0);
 
 }
void  PIN_JR_relay(uint16 flag)
 {
    if(flag==ERsample_50)
		GPIOPinWrite(GPIO_PORTJ_BASE, PIN_JR, PIN_JR);
	else
		GPIOPinWrite(GPIO_PORTJ_BASE, PIN_JR, 0);
 
 }



void Ad7367CnvstWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_CNVST,PIN_AD7367_CNVST);
	else
		GPIOPinWrite(GPIO_PORTB_BASE,PIN_AD7367_CNVST, 0);
 
 }


void Ad7367SclkWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_SCLK,PIN_AD7367_SCLK);
	else
		GPIOPinWrite(GPIO_PORTB_BASE,PIN_AD7367_SCLK, 0);
 
 }


void Ad7367CsWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_CS,PIN_AD7367_CS);
	else
		GPIOPinWrite(GPIO_PORTB_BASE,PIN_AD7367_CS, 0);
 
 }


void Ad7367AddrWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_ADDR,PIN_AD7367_ADDR);
	else
		GPIOPinWrite(GPIO_PORTB_BASE,PIN_AD7367_ADDR, 0);
 
 }


void Ad7705RESWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_AD7705_RST,PIN_AD7705_RST);
	else
		GPIOPinWrite(GPIO_PORTA_BASE,PIN_AD7705_RST, 0);
 
 }
void Ad7705CSWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_AD7705_CS,PIN_AD7705_CS);
	else
		GPIOPinWrite(GPIO_PORTA_BASE,PIN_AD7705_CS, 0);
 
 }


void Ad7705SCLKWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_AD7705_SCLK,PIN_AD7705_SCLK);
	else
		GPIOPinWrite(GPIO_PORTA_BASE,PIN_AD7705_SCLK, 0);
 
 }


void Ad7705DINWrite(uint16 flag)
{
    if(flag)
		GPIOPinWrite(GPIO_PORTA_BASE, PIN_AD7705_DIN,PIN_AD7705_DIN);
	else
		GPIOPinWrite(GPIO_PORTA_BASE,PIN_AD7705_DIN, 0);
 
 }



void spi_ad7705Init(void)

{
    uint32 ulDataRx;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for SSI0 functions on port A2, A3, A4, and A5.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
  //  GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);

    //
    // Configure the GPIO settings for the SSI pins.  This function also gives
    // control of these pins to the SSI hardware.  Consult the data sheet to
    // see which functions are allocated per pin.
    // The pins are assigned as follows:
    //      PA5 - SSI0Tx
    //      PA4 - SSI0Rx
    //      PA3 - SSI0Fss
    //      PA2 - SSI0CLK
    // TODO: change this to select the port/pin you are using.
    //

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4  | //| GPIO_PIN_3
                   GPIO_PIN_2);

    //
    // Configure and enable the SSI port for SPI master mode.  Use SSI0,
    // system clock supply, idle clock level low and active low clock in
    // freescale SPI mode, master mode, 1MHz SSI frequency, and 8-bit data.
    // For SPI mode, you can set the polarity of the SSI clock when the SSI
    // unit is idle.  You can also configure what clock edge you want to
    // capture data on.  Please reference the datasheet for more information on
    // the different SPI modes.
    //
         
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,
                       SSI_MODE_MASTER, 1000000, 8);
	 

    //
    // Enable the SSI0 module.
    //
    SSIEnable(SSI0_BASE);

    //
    // Read any residual data from the SSI port.  This makes sure the receive
    // FIFOs are empty, so we don't read any unwanted junk.  This is done here
    // because the SPI SSI mode is full-duplex, which allows you to send and
    // receive at the same time.  The SSIDataGetNonBlocking function returns
    // "true" when data was returned, and "false" when no data was returned.
    // The "non-blocking" function checks if there is any data in the receive
    // FIFO and does not "hang" if there isn't.
    //
  
    while(SSIDataGetNonBlocking(SSI0_BASE, &ulDataRx)) ;
  
}





//static void GpioIntInit()
//{
//	GPIOIntTypeSet(GPIO_PORTA_BASE,PIN_ADC_BUSY,GPIO_FALLING_EDGE);	/*Set falling edge*/
//	AdcBusyIntEnable();
//	GPIOPinIntEnable(GPIO_PORTA_BASE,PIN_ADC_BUSY);

//	GPIOIntTypeSet(GPIO_PORTH_BASE,PIN_HV_SHORT_DETECT,GPIO_FALLING_EDGE);	/*Set falling edge*/
//	IntEnable(INT_GPIOH);
//	GPIOPinIntEnable(GPIO_PORTH_BASE,PIN_HV_SHORT_DETECT);
//}

/*
void AdcBusyIntEnable()
{
	IntEnable(INT_GPIOA);
}

void AdcBusyIntDisable()
{
	IntDisable(INT_GPIOA);
}
*/
#if 0
void Ssi1_ad7567Init(void)
/*Act as Master*/
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinConfigure(GPIO_PE0_SSI1CLK);
    GPIOPinConfigure(GPIO_PE1_SSI1FSS);
    GPIOPinConfigure(GPIO_PE2_SSI1RX);
    GPIOPinConfigure(GPIO_PE3_SSI1TX);
    GPIOPinTypeSSI(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3 );
   	SSIConfigSetExpClk(SSI1_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_2,SSI_MODE_MASTER,20000000,14);
	SSIEnable(SSI1_BASE);

	
}




void Ssi0Init(void)
/*Act as Master*/
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
   // GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4);
   	SSIConfigSetExpClk(SSI0_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_2,SSI_MODE_MASTER,20000000,14);
	SSIEnable(SSI0_BASE);

	
}

#endif
void T2Init_BAT(void)
 {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_32_BIT_PER|TIMER_CFG_A_PERIODIC);
	//TimerPrescaleMatchSet(TIMER2_BASE, TIMER_A, SysCtlClockGet()/0x10000);
    TimerLoadSet(TIMER2_BASE, TIMER_A,3*SysCtlClockGet()); //
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



void T1Init_FRE(void)
 {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_32_BIT_PER);
	TimerLoadSet(TIMER1_BASE, TIMER_A, 0xffffffff);
   

 }



void IoPortInit(void)
{
	//
	// Enable the GPIO block.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
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
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, PIN_AD7705_RST|PIN_AD7705_CS|PIN_AD7705_DIN|PIN_AD7705_SCLK);//
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, PIN_AD7367_ADDR|PIN_AD7367_CNVST|PIN_AD7367_CS|PIN_AD7367_SCLK);
	//GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, PIN_200X|PIN_2KX | PIN_20KX |PIN_3X);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, PIN_JUN|PIN_JUX|PIN_JRTG|PIN_JUNX);
	//GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, PIN_20N  | PIN_200N |  PIN_2KN );
	//GPIOPinTypeGPIOOutput(GPIO_PORTG_BASE, PIN_20KN |PIN_NX  | PIN_filterPASS|PIN_3N |PIN_ADC_ADDR|PIN_ADC_RANGE0);
    //GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, PIN_CE6963|PIN_CD6963|PIN_RD6963|PIN_WR6963);
    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, PIN_JR);

	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, PIN_AD7705_DRDY|PIN_AD7705_DOUT);//
	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, PIN_AD7367_DOUTB|PIN_AD7367_BUSY);
//    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,PIN_ADC_BUSY);
//	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, PIN_KEY1 | PIN_KEY2 | PIN_KEY3 | PIN_KEY4);
//    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, PIN_keyback| PIN_keydown|PIN_keyprint|PIN_keyset|PIN_keystart|PIN_keyup);
//	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, PIN_ISP2);
//	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, PIN_ADC_DOUTA );
//	GPIOPinTypeGPIOInput(GPIO_PORTH_BASE, );

//	GpioIntInit();

//	Led1Write(0);
//	Led2Write(0);
	
}

void Uart1Init(uint32 bsp)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinConfigure(GPIO_PD0_U1RX);
    GPIOPinConfigure(GPIO_PD1_U1TX);
	GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), bsp,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

	UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
	IntEnable(INT_UART1);
}




void Uart0Init(uint32 bsp)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), bsp,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));

//	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
//	IntEnable(INT_UART0);
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

#define TIMER_FREQ 200   // 200Hz

void TimerInit(void)
{
	//
	// Set up and enable the SysTick timer.  It will be used as a reference
	// for the delay loop.  
	//
	SysTickPeriodSet(SysCtlClockGet()/TIMER_FREQ);
	SysTickEnable();
	SysTickIntEnable();
}





