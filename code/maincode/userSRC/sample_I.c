			 #include "file_ah9837.h"

/*

#define _FRE_40  40    // 1s/20=50ms
#define _sample_nub  1024  
#define _ADChigh  (0x1fff*998/1000)
#define _ADCmiddle (0x1fff*290/1000)
#define _ADClow   (0x1fff*88/1000)

*/
void delay(uint32 i)
{
 for( ;i>0;i--)
 	{
 	}
}



void AD7367_init(void)
{
  Ad7367CnvstWrite(1);
  Ad7367SclkWrite(1);
  Ad7367CsWrite(1);
  Ad7367AddrWrite(0);
}

uint32  AD7367_read(void)
{
   uint32 i;
   uint32 dat=0;
   
   HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CS<< 2))) = 0;// Ad7367CsWrite(0);
   for(i=0;i<28;i++)
   	{
   	   dat=dat<<1;
       HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_SCLK << 2))) = 0;//GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_SCLK,0);
	
	   if( PIN_AD7367_DOUTB ==HWREG(GPIO_PORTB_BASE  + (GPIO_O_DATA + (PIN_AD7367_DOUTB << 2))))
	   	{
	   	  dat|=0x1 ;
	   	}
	   HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_SCLK << 2))) = PIN_AD7367_SCLK;// GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_SCLK,PIN_AD7367_SCLK);	
	}
 //  HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_SCLK << 2))) = PIN_AD7367_SCLK;//GPIOPinWrite(GPIO_PORTB_BASE, PIN_AD7367_SCLK,PIN_AD7367_SCLK);	
   HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CS<< 2))) = PIN_AD7367_CS;// Ad7367CsWrite(1);
   return(dat);	
}

#define _FRE_20  20    // 1s/20=50ms

RElaygainflagtype gainchange(void)
 {
    uint32 read_nub;
    uint32 CX_max;
    uint32 CN_max;
	uint32 CX_read;
	uint32 CN_read;
	uint32 N_flag;
	uint32 X_flag;
	uint32 rdatn[_sample_nub*4];
	uint32 rdatx[_sample_nub*4];

    RElaygainflagtype RElaygainflag_B;
	
    RElaygainflag_B.RElaygainBIT.CNgain=RElaygainflag_B.RElaygainBIT.CXgain=0;
    RElaygainflag_B.RElaygainBIT.CN_3=RElaygainflag_B.RElaygainBIT.CX_3=Egain_3_no;
	
	
    PIN_JUX_relay(ERelay_off);
	PIN_JUN_relay(ERelay_off);
	
    N_flag=X_flag=false;
	
	T0Init_sample((SysCtlClockGet()/(_FRE_20*_sample_nub))%0x10000);
    while((X_flag!=true)||(N_flag!=true))
    	{
    	
          CX_max=0;
          CN_max=0;
    	  read_nub=0;
		  while(read_nub<(_sample_nub*4*6))   //delay 200ms
             {
               while((TimerIntStatus(TIMER0_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS  );
    	       read_nub++;
		       TimerIntClear(TIMER0_BASE, TIMER_RIS_TATORIS );
    	  	 }
		 
    	  read_nub=0;
		 
          while(read_nub<_sample_nub*4)     //读50ms，取最大值
          {
            // while((TimerIntStatus(TIMER0_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS  );
			  HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CNVST<< 2))) = 0;//  Ad7367CnvstWrite(0);//
    	    //  Ad7367CnvstWrite(0);
    	  //    TimerIntClear(TIMER0_BASE, TIMER_RIS_TATORIS );
		      HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CNVST<< 2))) = PIN_AD7367_CNVST;//Ad7367CnvstWrite(1);
			  while (HWREG(GPIO_PORTB_BASE  + (GPIO_O_DATA + (PIN_AD7367_BUSY << 2)))==PIN_AD7367_BUSY ) ;  
			  CX_read=AD7367_read();
			  rdatn[read_nub]=CN_read=CX_read&0x3fff;
			  rdatx[read_nub]=CX_read=(CX_read>>14)&0x3fff;
	         
			    if( CN_read>0x2000)
	             	{
	             	 CN_read=0x3fff-CN_read;
	             	}
				 if(CN_read>CN_max)
				 	{
				 	 CN_max=CN_read;
				 	}
				 if( (CX_read)>0x2000)
	             	{
	             	 CX_read=0x3fff-CX_read;
	             	}
				 if(CX_read>CX_max)
				 	{
				 	 CX_max=CX_read;
				 	}
	
			   read_nub++;
			  
         }  

   if(N_flag==false)
	 {
       if(CN_max<_ADCmiddle)
	   	{
	   	 RElaygainflag_B.RElaygainBIT.CN_3=Egain_3_yes;     //  3倍 
	   	 PIN_JUN_relay(ERelay_on);
	   	}
	   
	   	   N_flag=true;                                  //结束
	  
	 }

   
	if(X_flag==false) 
	 {
	   if(CX_max<_ADCmiddle)
	   	{
	  
	   	 RElaygainflag_B.RElaygainBIT.CX_3=Egain_3_yes;
	   	 PIN_JUX_relay(ERelay_on);
	   	}
	    X_flag=true;
	 }
    if(set.Debug==EDebug_sub)	
     {
       DPRINTF(("Xmax=%x  ,Nmax=%x\n",CX_max,CN_max));
     }
 	

	
   }
	/*
 if(set.Debug==EDebug_sub)	
  {
   for(read_nub=0;read_nub<_sample_nub*4;read_nub++)
   {
     DPRINTF(("%d  ,n=%x ,x=%x \n",read_nub,rdatn[read_nub],rdatx[read_nub]));
   }
  }	
  */
  return(RElaygainflag_B);
 }

