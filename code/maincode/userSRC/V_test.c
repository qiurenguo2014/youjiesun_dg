 #include "file_ah9837.h"



void  V_read(void)
 	{
         PIN_JUNX_relay(ERelay_off);
         PIN_JUN_relay(ERelay_off);
	     PIN_JUX_relay(ERelay_off);
	     PIN_JR_relay(ERsample_50);

	 if(set.Fre==EFre_000) 
       {
        PIN_JRTG_relay(ERelay_on);
	   }
	 else
	 	{
	 	 PIN_JRTG_relay(ERelay_off);
	 	}
	
      while(1)  
		{
		  if(set.Fre==EFre_000)
         	{
         	 Resulttest.result[EU_result].word_F=Vdc_read(); //DC
         	}
		  else
		 	{
		 	 Resulttest.result[EU_result].word_F =Vac_read(EVn_read);
		 	}
		
		  if(set.Debug==EDebug_sub)
      	   {
      	    DPRINTF(("Un=%f \n",  Resulttest.result[EU_result].word_F));//¥Ú”°≤‚ ‘Ω·π˚
			 
      	   }
           
          if((rx_flag==rx_succeed))//  &&((rx_data.mune.workcommand&0x0f)==Estop_main))
         	{   
               //delay(0x800000);
			   Sendstc_ask();
			   rx_flag=0;
			   if((rx_data.mune.workcommand&0x0f)==Estop_main)
         	    {
         	     // DPRINTF(("stop\n"));
         	      break;
			   	} 
			  
           	}
		  
	      Sendstc_result(EResult_vL);  
		  } 
      
	  
 	}




float Vdc_read(void)
  {
     float Udc;
	 uint32 x;
	 x=Read_ad7705_U(Egain2,1);
	 Udc=(float)x/2.0*_ADC7705LSBSize;    
   //  Udc=(Udc-modify_k.f_k[E7705Uzio_modify].word_F)*modify_k.f_k[EUk_modify].word_F;
	 return(Udc);
   
  }

#define Rac_CN 2000.0
#define Cac_CN 0.000000000050  //50.0pF

float Vac_read(uint8 flag)
  {
     uint32  sample_T;
	 uint32  i;
	 uint64  sumn=0;
	 uint64  sumx=0;
	 uint32  Unread;
	 uint32  Uxread;
      float  Uacn,Uacx;
	 uint32 fre;
	 fre=((set.Fre-1)*25+450);
	 sample_T=(10*SysCtlClockGet())/(fre*_FourierTime_sampleNub);
     T0Init_sample(sample_T);
	 for(i=0;i<_FourierTime_sampleNub;i++)
	 	{
              while((TimerIntStatus(TIMER0_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS  );
			  Ad7367CnvstWrite(0);
    	      TimerIntClear(TIMER0_BASE, TIMER_RIS_TATORIS );
		      Ad7367CnvstWrite(1);
			  while (GPIOPinRead(GPIO_PORTB_BASE,PIN_AD7367_BUSY)==PIN_AD7367_BUSY ) ;  
			  Unread=AD7367_read();
			  Uxread=(Unread>>14)&0x3fff;
			  Unread=Unread&0x3fff;			  
			  if(Unread>=0x2000)
			 	 {
			 	  Unread+=0xFFFFc000;
			 	 }
			  if(Uxread>=0x2000)
			 	 {
			 	  Uxread+=0xFFFFc000;
			 	 }
			  
			  sumn+=(uint64)((sint32)Unread*(sint32)Unread);
			  sumx+=(uint64)((sint32)Uxread*(sint32)Uxread);
	 	}
     Uacn=_ADC7367LSBSize*(float)sqrt(sumn/_FourierTime_sampleNub);
	 Uacx=_ADC7367LSBSize*(float)sqrt(sumx/_FourierTime_sampleNub);
	 //Uac=(2*pi*Cac_CN*(float)fre)*((Uac/modify_k.f_k[ECN3_modify].word_F)/Rac_CN)	;  
     if(flag==EVn_read)
	     {
	      return(Uacn);   
     	 }
	 else
	 	{
	 	 return(Uacx);   
	 	}
  
  }

void  Vacx_read(void)
{
 PIN_JRTG_relay(ERelay_off);
 PIN_JUNX_relay(ERelay_off);
 PIN_JUN_relay(ERelay_off);
 PIN_JUX_relay(ERelay_off); 
 PIN_JR_relay(ERelay_on);
  while(1)
  {
   Resulttest.result[EU_result].word_F =Vac_read(EVx_read);
   if((rx_flag==rx_succeed))//  &&((rx_data.mune.workcommand&0x0f)==Estop_main))
         	{   
               //delay(0x800000);
			   Sendstc_ask();
			   rx_flag=0;
			   if((rx_data.mune.workcommand&0x0f)==Estop_main)
         	    {
         	     // DPRINTF(("stop\n"));
         	      break;
			   	} 
			  
           	}
   if(set.Debug==EDebug_sub)
      	   {
      	    
      	   DPRINTF(("Ux=%f \n",  Resulttest.result[EU_result].word_F));
			 
      	   }	  
   Sendstc_result(EResult_vL);  
  }
}





































 
