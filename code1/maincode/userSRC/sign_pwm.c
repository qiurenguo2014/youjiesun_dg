
#include "file_ah9837.h"


#define PwmNub  256
sint32  PwmLib[256];
//#define pi 3.14159265358979
 static  uint32 width=0;


static sint32 DC_Standard; 
static sint32 UP_Period=0;
static uint32  Stoppwmflag;
static uint32  PwmStation;
enum{EUpVpwm,EDownVpwm};
enum{EStoppwm_Ready,EStoppwm_start};

void PWM_sign_acc(float Sin_Hz,float Sin_Peak)
{
  uint32 Pwm_HZ;
  uint32 i;
  float  AC_PeakValue ; 
if(Sin_Hz>0.1)
 {
  Pwm_HZ=(uint32)( (float)SysCtlClockGet()/Sin_Hz/(float)PwmNub);
  AC_PeakValue=(float)(Pwm_HZ/2)*Sin_Peak;
  DC_Standard=(Pwm_HZ+1)/2;
  for(i=0;i<PwmNub;i++)
  	 {
  	  PwmLib[i]=(sint16)(AC_PeakValue*sin(2*pi*(float)i/(float)PwmNub));
	 }

   
 
  }
else
  {
     Pwm_HZ=(uint32)( (float)SysCtlClockGet()/100.0/(float)PwmNub);
     DC_Standard=(uint32)((float)Pwm_HZ*Sin_Peak);
	 for(i=0;i<PwmNub;i++)
	 	{
	 	  PwmLib[i]=0;
	 	}
  }
   UP_Period=0;
   width=0 ; 
   PwmStation=EUpVpwm;
   PWMGenPeriodSet(PWM_BASE, PWM_GEN_2,Pwm_HZ);
   PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, (uint16)(PwmLib[width])); 
   PWMGenEnable(PWM_BASE, PWM_GEN_2);
}


void PWM_sign_stop(void)
{
 
 PwmStation=EDownVpwm;
 Stoppwmflag=EStoppwm_Ready	;
// PWMGenDisable(PWM_BASE, PWM_GEN_2); 
// PIN_TDA7367stand_Write(ETDA7367work_no);
 
}


 





 

void  PWM2IntHandler(void)
{
    //
    // Clear the PWM0 LOAD interrupt flag.  This flag gets set when the PWM
    // counter gets reloaded.
    //
    
    PWMGenIntClear(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_ZERO);
	width++;
	
    if(width>=PwmNub)
    	{
    	  width=0;
	  	}

	if(PwmStation==EUpVpwm)	
    {
     if(UP_Period<100)
    	{ 
    	  uint16 U_Pwm;
          if(width==0)
				{
				 UP_Period++;
				}
		  U_Pwm=(sint16) ((DC_Standard+PwmLib[width])*UP_Period/100);
          PWMPulseWidthSet(PWM_BASE, PWM_OUT_5,(uint16)U_Pwm); 
	   }
		 
    else  
 	   {
	    PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, (uint16)(DC_Standard+PwmLib[width])); 
 	   }
	}
	else if(PwmStation==EDownVpwm)	
	 {
	  /* if(Stoppwmflag==EStoppwm_Ready)
    	{ 
    	  PWMPulseWidthSet(PWM_BASE, PWM_OUT_5,(uint16)(DC_Standard+PwmLib[width])); 
          if(width==0)
          	{
		      Stoppwmflag=EStoppwm_start;
		   	}
		  
	    }
	  else  
 	   {
 	     PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, (uint16)(DC_Standard*(PwmNub-width)/PwmNub)); 
		 if(width==(PwmNub-1))
		 	{
		 	   PWMGenDisable(PWM_BASE, PWM_GEN_2); 
		 	}
		 
 	   }
	 */
	   if(Stoppwmflag==EStoppwm_Ready)
    	{ 
    	  PWMPulseWidthSet(PWM_BASE, PWM_OUT_5,(uint16)(DC_Standard+PwmLib[width])); 
          if(width==0)
          	{
		      Stoppwmflag=EStoppwm_start;
		   	}
		  
	    }
	  else  
 	    {
		   uint16 U_Pwm;
           if(width==0)
				{
				 UP_Period-=4;
           	    }
		   if(UP_Period>=0)
			    {
				  U_Pwm=(sint16) ((DC_Standard+PwmLib[width])*UP_Period/100);
				  PWMPulseWidthSet(PWM_BASE, PWM_OUT_5,(uint16)U_Pwm);  
			    }
			else
				{
				 PWMPulseWidthSet(PWM_BASE, PWM_OUT_5,(uint16)0);   //PWMGenDisable(PWM_BASE, PWM_GEN_2); 
				}
				                     
		
		 
	   }
	}
}


void signPWM_init(float Sin_Hz)
{
     uint32 Pwm_HZ;
     for( Pwm_HZ=0; Pwm_HZ<PwmNub; Pwm_HZ++)
	 	{
	 	  PwmLib[ Pwm_HZ]=0;
	 	}
	 Pwm_HZ= (uint32)( (float)SysCtlClockGet()/Sin_Hz/(float)PwmNub);
 
     UP_Period=100;
     DC_Standard=0;  //( Pwm_HZ+1)/2;
     width=0 ; 



  
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Set GPIO H7  as PWM pins.  They are used to output the PWM5 
    //
    GPIOPinConfigure(GPIO_PA3_PWM5);
   
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_3);

    //
    // Compute the PWM period based on the system clock.
    //
  //  ulPeriod = SysCtlClockGet() /Pwm_HZ;

    //
    // Set the PWM period to 50 (A) Hz.
    //
    PWMGenConfigure(PWM_BASE, PWM_GEN_2,
                        PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_BASE, PWM_GEN_2, Pwm_HZ);

    //
    // Set PWM0 to a duty cycle of 25% and PWM1 to a duty cycle of 75%.
    //
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_5, 0);
  
    IntMasterEnable();

    //
    // Allow PWM0 generated interrupts.  This configuration is done to
    // differentiate fault interrupts from other PWM0 related interrupts.
    //
    PWMIntEnable(PWM_BASE, PWM_INT_GEN_2);

    //
    // Enable the PWM0 LOAD interrupt on PWM0.
    //
    PWMGenIntTrigEnable(PWM_BASE, PWM_GEN_2, PWM_INT_CNT_ZERO);

    //
    // Enable the PWM0 interrupts on the processor (NVIC).
    //
    IntEnable(INT_PWM2);


    //
    // Enable the PWM0 and PWM1 output signals.
    //
    PWMOutputState(PWM_BASE, PWM_OUT_5_BIT, true);

    //
    // Enable the PWM generator.
    //
    PWMGenDisable(PWM_BASE, PWM_GEN_2);

}







#if 0
void PWM_sign_acc(float Sin_Hz,float Sin_Peak)
{
  uint16 i;
  //float hz=sinHZ_lib[Sin_HZ];
  uint32 Pwm_HZ;
  
  uint32 AC_PeakValue  ,DC_Standard; 
  
  while(width!=0) ;
  PWMGenDisable(PWM_BASE, PWM_GEN_2);
  PWMIntDisable(PWM_BASE, PWM_INT_GEN_2);
  if(Sin_Hz!=0.0)
   {
     float Pwm_Peak;
 //    PIN_TDA7367stand_Write(ETDA7367work_yes);
     Pwm_HZ=(uint32)( (float)SysCtlClockGet()/Sin_Hz/(float)PwmNub);
 
     AC_PeakValue=Pwm_HZ/2;
     DC_Standard=(Pwm_HZ+1)/2;
     Pwm_Peak=(float)AC_PeakValue*Sin_Peak;
  //DPRINTF(("HZ= %d   peak=%d   \n",Pwm_HZ,Pwm_Peak));
  	
    for(i=0;i<PwmNub;i++)
  	 {
  	  float sinX;
      sint16 pwmwidth;
	  sinX=sin(2*pi*(float)i/(float)PwmNub);
	  pwmwidth=DC_Standard+(sint16)(Pwm_Peak*sinX);
      PwmLib[i]=(uint16)pwmwidth;
	//  DPRINTF((" %d= %d  \n",i,PwmLib[i]));
  	 }
  }
 else 
  {
     uint32 Pwm_Peak;
 //    PIN_TDA7367stand_Write(ETDA7367work_no);
     Pwm_HZ=(uint32)( (float)SysCtlClockGet()/100.0/(float)PwmNub);
	 DC_Standard=Pwm_HZ;
     Pwm_Peak=(uint32)((float)DC_Standard*Sin_Peak);
	 for(i=0;i<PwmNub;i++)
	 	{
	 	  PwmLib[i]=(uint16)Pwm_Peak;
	 	}
  
  }
  
  PWMGenPeriodSet(PWM_BASE, PWM_GEN_2,Pwm_HZ);
  width=0 ; 
  PWMIntEnable(PWM_BASE, PWM_INT_GEN_2);
  PWMGenEnable(PWM_BASE, PWM_GEN_2);
 
}
#endif


/*
 先 20% 递增
 到80%后   5%递增
 95%后     2%   到超
*/
#if 0
enum{EV80_course,EV95_course,EV100_course};
float V_adj(float fre)
 {
    float PP_temp;
	float PP_step;
	float pp_current=0.0;
	
	float V_current=0.0;
	float V_set;
    float V_lim;

	wordtype U_k;
		
	uint32 Vadj_course;
    uint32 rx_nub; 
	uint16 command;

	
	if(fre>1.0)
	  {
	   PIN_DCAC_pwm(EAC_power);
	   V_set=100.0* (float)set.mune.Vac;
	   PP_temp=(V_set/modify_k.f_k[EVacK_modify].word_F)*0.5;      
	   readbyte_much(Vac_K_addr,4,U_k.word_U8); 
	  
	  }
	else
	  {
	    PIN_DCAC_pwm(EDC_power);
	    V_set=100.0* (float)set.mune.Vdc;
	    PP_temp=(V_set/modify_k.f_k[EVdcK_modify].word_F)*0.5;     
		readbyte_much(Vdc_K_addr,4,U_k.word_U8);
		
		
	  }
	

   Vadj_course=EV80_course;
	
   DPRINTF(("Uk=%f \n",U_k.word_F));
   while(V_current<V_set)
 	  {
         switch(Vadj_course)
        	{
              case EV80_course:
			  	  PP_step=(PP_temp/5.0);
			  	  pp_current+=PP_step;
                  V_lim=V_set*0.75;
				  break;
			 	  
              case EV95_course:
			  	  PP_step=(PP_temp/20.0);
			  	  pp_current+=PP_step;
				  V_lim=V_set*0.91;
				  break;

			  case EV100_course:
			  	  PP_step=(PP_temp/50.0);
			  	  pp_current+=PP_step;
				  V_lim=V_set;
				  break;
        	}
		    DPRINTF(("Vlim=%f \n",V_lim));
	        PWM_sign_acc(fre,pp_current);
			//delay(0x80000);
           while(1)
          	 {
               for(rx_nub=0;rx_nub<100;rx_nub++) 	   
                 { 
                    while(rx_flag!=rx_succeed) ;   //死循环
                    command=rxlm3stg_Hander();
			   	 }
			 
			   if(command==((EResult_TXmain<<8)|EResult_vL))
			      {
			        V_current=U_k.word_F*resultRX.mune.vL;
			        V_display(Voltage_lin, Voltage_column+0x10,V_current );   //显示电压
			   	  } 
			    else
			      {
			          DPRINTF(("V \n"));
                      PWM_sign_acc(0.0,0.0);
					  while(1);
				  }
				
			    if(V_current>V_lim)
			    	{
			  	      Vadj_course++;
				  	  break;
			  	    }
				else
					{
					
					  pp_current+=PP_step;
					  if(pp_current>1.08)
					  	{
					  	  DPRINTF(("z \n"));
					  	  PWM_sign_acc(0.0,0.0);
					      while(1);
					  	}
					  PWM_sign_acc(fre,pp_current);
					 // delay(0x80000);
					  DPRINTF(("pp=%f \n",pp_current));
					}
		   	}

   	  }
   /*
    if(fre>1.0)
	  {
	   writebyte_much(Vac_PP_addr+4* (set.mune.Vac-E00Vac),4,PP_temp.word_U8); 
	  }
	else
	  {
	   writebyte_much(Vdc_PP_addr+4* (set.mune.Vdc-E00Vdc),4,PP_temp.word_U8); 
	  }
   */
	Sendtgc(Estop_main,EGeneral_sub,0);
    DPRINTF(("over \n")); 
    return(pp_current);
 }


#endif
   
 
