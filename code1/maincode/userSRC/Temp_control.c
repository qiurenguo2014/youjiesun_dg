#include "file_ah9837.h"

enum{EHOTH_pwm,EHOTL_pwm,};
enum{ETemp_upflag,ETemp_downflag};
enum{Temp_constantN0flag,Temp_constantYESflag};
#define time_TempUpDownNUB 4
#define Pwm_HotSucceess  40     //全80秒加热

void TEMP_disp(void)
 	{
	 char   sprintfbyte[8];
     float_xs((Resulttest.result[ET_result].word_F/10.0),&sprintfbyte[1],0);
	 sprintfbyte[0]=5;
     charLine1208(Tempoilwarn_lin, Tempoilwarn_column+9,  sprintfbyte);
    }	




void Temp_control()
	{
	   	switch(set.mune.work)
	 	 {
	 	   case ECair_work://空杯
                Cair_test();
				break;				
		   case EHand_work://手动
			    Temp_Handcontrol();
				break;				
		   case EAuto_work://自动
			    Temp_Autocontrol();
				break;					
	    	case ECom_work://通信
			    Temp_Comcontrol();
				break;	
			case ER_work://电阻
			    R_test();
				break;		
		}        		
		while(Keyset.keyEfficiency!=key_ok);
   }


uint32 Temp_Handcontrol()
 {
    uint32 pwm_flag;
    uint32 PID_Tlong=1;
   // sint16 Tempoilcurrently;
	float Tempoilconstant_limit;
   
    uint32 SysLinearHZ;
    uint32 Pwm_HotTime;
	float  Temp_start;
	uint8  constantTemp_flag=Temp_constantN0flag;     // ;达到恒温标志  -0.5<tg-tk<0.5
	uint8  StartTemp_flag   = Temp_constantN0flag;     // ;达到恒温标志  -0.5<tg-tk<0.5
	
    SysLinearHZ=2*SysCtlClockGet();
	Tempoilconstant_limit=(float)set.mune.Temp*5.0;
		
	Oiltempset.oilTAlarm=EOiltemp_AlarmNO;
	InitLCD();
	testHOT_mune();
	
    if(TRUE_z!=Cuplin_check())
  {
     
     SysLinearTimer =0;
     while(SysLinearTimer <TIMER_FREQ/2);
     testHOT_mune();
     Temp_account();//系数计算	
	 Temp_start=20.0+Resulttest.result[ET_result].word_F;
      if(Temp_start> Tempoilconstant_limit)  
      	{
      	 Temp_start=Tempoilconstant_limit;
      	}
	 
	Pwm_HotTime=0;	
    T2Init_HOT(SysLinearHZ);
	if(E00T!=set.mune.Temp);
	   	{
	     Tempoilconstant_limit=(float)set.mune.Temp*50.0-1.0;
	     PIN_Tpower_relay(ERelay_on);
		 HOT_init(set.mune.Temp*50);
         PID_init();
		
	    }
 
    while( 1)
		{
		 {
		   uint32 T_pwm=pid_control();
		   Pwm_HotTime+=T_pwm;
		   PID_Tlong=(uint32) ((uint64)T_pwm*(uint64)SysLinearHZ/PID_PERIODIC);
       	   PID_Tlong=SysLinearHZ- PID_Tlong;
    	 }
		 TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
		 
		 if(PID_Tlong>100)
		 {
		  PIN_Tpwm_Write(EHOTH_pwm);
		  pwm_flag=EHOTH_pwm;
		 }
		 else
		 {
		   PIN_Tpwm_Write(EHOTL_pwm);
		   pwm_flag=EHOTL_pwm;
		 }
         while((TimerIntStatus(TIMER2_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS)	
           {
     		 
         	  if( pwm_flag==EHOTH_pwm)
				{
				  // DPRINTF(("pwmH=%x",pwm_flag )); 
				   if( TimerValueGet(TIMER2_BASE,TIMER_A)<=PID_Tlong)
                 	{					   
                 	  PIN_Tpwm_Write(EHOTL_pwm);
					  pwm_flag=EHOTL_pwm;
					//  DPRINTF(("pwml=%x",pwm_flag )); 
				  	}
               	}
			  
              if(Oiltempset.oilTAlarm!=EOiltemp_AlarmYes)
                   {
               	      if(SysLinearTimer>TIMER_FREQ) 
	                   {
	                     if(Ganset.GanAlarm==EGan_AlarmYes)
           	                 {
           	                  Gandispose();
           	                 }						   
	                      Temp_account();//系数计算	
	                     {
	                      char   sprintfbyte[8];
                          float_xs((Resulttest.result[ET_result].word_F/10.0),&sprintfbyte[1],0);
	                      sprintfbyte[0]=5;
                          charLine1208(Tempoilwarn_lin, Tempoilwarn_column+9,  sprintfbyte);
						  ShowPicture(Tempoilwarn_lin, Tempoilwarn_column+9+5,Font1208,32 );  
                         }
                         if(StartTemp_flag==Temp_constantN0flag)
                         	{
                              if(Resulttest.result[ET_result].word_F<Temp_start)
                                {
                         	   	 if(Pwm_HotTime>(PID_PERIODIC*Pwm_HotSucceess))
                         	    	{ 
                         	    	 StopHot_Hander();
                         	 	     ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_jrxtgz);
									 while(1);
                         	 	    }
                              	}
							  else
							  	{
							  	 StartTemp_flag=Temp_constantYESflag;
							  	}
                            }
						  

	                     Clockread_xs( )	;
	                     if(constantTemp_flag==Temp_constantN0flag)
                             {
                                if(Resulttest.result[ET_result].word_F>=Tempoilconstant_limit)
             	                    {
							         constantTemp_flag=Temp_constantYESflag;
		                             ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_zhwz);
    	                            }
               				  
	           	            }
					        SysLinearTimer=0;
               	     } 
			     
          	      }
             else
           	        {
           	          //  ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_wzsk);
           	              PIN_Tpower_relay(ERelay_off);
		   	         }

			   
		   
             if(Keyset.keyEfficiency==key_ok)
           	      {
           	        StopHot_Hander();
					InitLCD();
                    ResultMune_display();
                    cs_start();
					fileHander();
			     	return(0);
           	      }
			else  if(Keyset.keyEfficiency==key_back)
					{
					   StopHot_Hander();
					   return(0);
					   
					}
         }
	   }
   	}
	return(0);	
 }












uint8 Temp_Autocontrol()
 {
    uint32 pwm_flag;
    uint32 PID_Tlong=1;
    float Tempoilconstant_limit;
	uint32 SysLinearHZ;
  
	float Tempoillast;
	sint16 time_TempUpDown;
    uint8  Temp_updownFlag;   //是否过最高温度且降温
	uint8  constantTemp_flag;     // ;达到恒温标志  -0.5<tg-tk<0.5
    
	SysLinearHZ=2*SysCtlClockGet();
	 
	Oiltempset.oilTAlarm=EOiltemp_AlarmNO;
	InitLCD();
	testHOT_mune();
  if(TRUE_z!=Cuplin_check())
  {
   
    SysLinearTimer =0;
    while(SysLinearTimer <TIMER_FREQ/2);
    testHOT_mune();
	 
    T2Init_HOT(SysLinearHZ);
	
	Tempoilconstant_limit=set.mune.Temp*50-1;   
	PIN_Tpower_relay(ERelay_on);
	HOT_init(set.mune.Temp*50);
    PID_init();
		
	 

	Temp_updownFlag=ETemp_upflag;
	Tempoillast=0.0;
	constantTemp_flag=Temp_constantN0flag; 
	time_TempUpDown=0x00;
	
	while(1)
		{
         PID_Tlong=(uint32) ((uint64)pid_control()*(uint64)SysLinearHZ/PID_PERIODIC);
       	 PID_Tlong=SysLinearHZ- PID_Tlong;
		 
		 TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
		 
		 if(PID_Tlong>100)
		 {
		  PIN_Tpwm_Write(EHOTH_pwm);
		  pwm_flag=EHOTH_pwm;
		 }
		 else
		 {
		   PIN_Tpwm_Write(EHOTL_pwm);
		   pwm_flag=EHOTL_pwm;
		 }
         while((TimerIntStatus(TIMER2_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS)	
           {
     		 
         	  if( pwm_flag==EHOTH_pwm)
				{
				  
				   if( TimerValueGet(TIMER2_BASE,TIMER_A)<=PID_Tlong)
                 	{ 
					   
                 	  PIN_Tpwm_Write(EHOTL_pwm);
					  pwm_flag=EHOTL_pwm;
					
				  	}
               	}

              if(Oiltempset.oilTAlarm!=EOiltemp_AlarmYes)
                   {
               	      if(SysLinearTimer>TIMER_FREQ) 
	                   {
	                     if(Ganset.GanAlarm==EGan_AlarmYes)
           	                 {
           	                  Gandispose();
           	                 }
						   
	                     Temp_account();//系数计算	
	                     {
	                      char   sprintfbyte[8];
                          float_xs((Resulttest.result[ET_result].word_F/10.0),&sprintfbyte[1],0);
	                      sprintfbyte[0]=5;
                          charLine1208(Tempoilwarn_lin, Tempoilwarn_column+9,  sprintfbyte);
						    ShowPicture(Tempoilwarn_lin, Tempoilwarn_column+9+5,Font1208,32 );  
                         }	

	                     Clockread_xs( )	;
	                     if(constantTemp_flag==Temp_constantN0flag)
                             {
                                if(Resulttest.result[ET_result].word_F>=Tempoilconstant_limit)
             	                    {
							         constantTemp_flag=Temp_constantYESflag;
		                             ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_zhwz);
									 PIN_Tpower_relay(ERelay_off);
    	                            }
               				  
	           	            }
                        
			            else 
			   	           {
			   	              if(Temp_updownFlag==ETemp_upflag)
			   	     	         {
                                    if(Resulttest.result[ET_result].word_F>=Tempoillast)   
                           	            {
                           	              time_TempUpDown=0;
                           	            }
						            else
						   	            {
						   	              time_TempUpDown++;
								          if(time_TempUpDown>time_TempUpDownNUB)
									       {
									          Temp_updownFlag=ETemp_downflag;
									       }
						   	           }
						             Tempoillast=Resulttest.result[ET_result].word_F;
						 
			   	     	        }
					          else
					 	        {
					 	             if(fabs(Resulttest.result[ET_result].word_F-Tempoilconstant_limit)<=2.0) // 0.2度
						              	{
							              StopHot_Hander();
										  InitLCD();
                                          ResultMune_display();
						   	              cs_start();
							              fileHander();
						   	              return(0);
					 	   	            }
					 	        }
			   	          }

						 
					        SysLinearTimer=0;
               	     } 
			     
          	      }
             else
           	        {
           	             StopHot_Hander();
						 ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_jrxtgz);
						 while(1);
		   	         }

			   
		   
          
			 if(Keyset.keyEfficiency==key_back)
					{
					   StopHot_Hander();
					   return(0);
					   
					}
        
          	}
		}				
	}
	return(0);
 }




sint16 TempSendcom_Calculate(sint16 Tempoilcurrently,sint16  Tempoilset_5)
  {
     sint16 Temp_Sendcom=0;
     if(Tempoilcurrently>=Tempoilset_5)
     	{
     	   while( Temp_Sendcom<Tempoilcurrently)
     	      {
     	       Temp_Sendcom=Temp_Sendcom+10 ;  //1度
     	   	  } 
     	}
	 else
	 	{
	 	 //Tempoilset_5=300;     //300度
	 	 //  Temp_Sendcom=250;
	 	   while( Temp_Sendcom<Tempoilcurrently)
     	      {
     	       Temp_Sendcom= Temp_Sendcom+50 ;  //5度
     	   	  } 
	  	}
	 return(Temp_Sendcom)  ;
  }



uint8  Temp_Comcontrol()
 {
     
    uint32 pwm_flag;
    uint32 PID_Tlong=1;
	uint32 SysLinearHZ;
    float Tempoilconstant_limit;
	float Tempoillast;
	sint16 time_TempUpDown;
   	sint16   Tempoilset,TempConSet;
	uint8  Temp_updownFlag;   //是否过最低温度且升温
	uint8  constantTemp_flag;     // ;达到恒温标志  -0.5<tg-tk<0.5
	uint8  stopage;
	uint8  stooption=0;
	

   
   readbyte_much(VIEWnewpagesto_addr,1, &stopage);
   stopage++;
   if(stopage>=viewpage_nub)
    	{
  	      stopage=0;
  	     }
   
  SysLinearHZ=2*SysCtlClockGet();
  Oiltempset.oilTAlarm=EOiltemp_AlarmNO;

  InitLCD();
  testHOT_mune();
 if(TRUE_z!=Cuplin_check())
  {
  
    SysLinearTimer =0;
    while(SysLinearTimer <TIMER_FREQ/2);
    testHOT_mune();
	 
    T2Init_HOT(SysLinearHZ);


	Temp_updownFlag=ETemp_upflag;
	Tempoillast=0.0;
	constantTemp_flag=Temp_constantN0flag; 
	time_TempUpDown=0x00;
	Tempoilconstant_limit=(float)set.mune.Temp*50.0-1.0;  
	Tempoilset=set.mune.Temp*50-50;
    Temp_account();//系数计算	
  
	if(Resulttest.result[ET_result].word_F<Tempoilconstant_limit)
		{
		    Temp_updownFlag=ETemp_downflag;
	        Tempoillast=0.0;
	        constantTemp_flag=Temp_constantN0flag; 
	        time_TempUpDown=0x00;	
			TempConSet=TempSendcom_Calculate( (sint16)(Resulttest.result[ET_result].word_F), Tempoilset );
			DPRINTF(("pwm0=%u",TempConSet )); 
		    DPRINTF(("set2=%u",Tempoilset )); 
   	       	PIN_Tpower_relay(ERelay_on);
	        HOT_init(TempConSet);
            PID_init();
		}
	else
		{
		    Temp_updownFlag=ETemp_downflag;
	        Tempoillast=1500.0;
	        constantTemp_flag=Temp_constantYESflag; 
	        time_TempUpDown=0x00;	
   	        PIN_Tpower_relay(ERelay_off);
		}

	
	while(1)
		{

         PID_Tlong=(uint32) ((uint64)pid_control()*(uint64)SysLinearHZ/PID_PERIODIC);
       	 PID_Tlong=SysLinearHZ- PID_Tlong;
		 
		 TimerIntClear(TIMER2_BASE, TIMER_RIS_TATORIS);
		 
		 if(PID_Tlong>100)
		 {
		  PIN_Tpwm_Write(EHOTH_pwm);
		  pwm_flag=EHOTH_pwm;
		 }
		 else
		 {
		   PIN_Tpwm_Write(EHOTL_pwm);
		   pwm_flag=EHOTL_pwm;
		 }
         while((TimerIntStatus(TIMER2_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS)	
           {
     		 
         	  if( pwm_flag==EHOTH_pwm)
				{
				 
				   if( TimerValueGet(TIMER2_BASE,TIMER_A)<=PID_Tlong)
                 	{ 
					   
                 	  PIN_Tpwm_Write(EHOTL_pwm);
					  pwm_flag=EHOTL_pwm;
				
				  	}
               	}

              if(Oiltempset.oilTAlarm!=EOiltemp_AlarmYes)
                   {
               	      if(SysLinearTimer>TIMER_FREQ) 
	                   {
	                     if(Ganset.GanAlarm==EGan_AlarmYes)
           	                 {
           	                  Gandispose();
           	                 }
						   
	                      Temp_account();//系数计算	
	                     {
	                      char   sprintfbyte[8];
                          float_xs((Resulttest.result[ET_result].word_F/10.0),&sprintfbyte[1],0);
	                      sprintfbyte[0]=5;
                          charLine1208(Tempoilwarn_lin, Tempoilwarn_column+9,  sprintfbyte);
						    ShowPicture(Tempoilwarn_lin, Tempoilwarn_column+9+5,Font1208,32 );  
                         }	

	                     Clockread_xs( )	;
                        if(constantTemp_flag==Temp_constantYESflag)
							{
							   if(fabs(Resulttest.result[ET_result].word_F-Tempoilconstant_limit)<=2.0) // 0.2度
						              	{
							              StopHot_Hander();
						   	              cs_start();
							              fileHander();
						   	              return(0);
					 	   	            }
							}
 
						 
	                   else    // if(constantTemp_flag==Temp_constantN0flag)
                           {
                             if((Temp_updownFlag==ETemp_downflag))
                   	           {
                                  if( Resulttest.result[ET_result].word_F<=Tempoillast)   
                           	              {
                           	                time_TempUpDown=0;
                           	              }
						          else
						   	             {
						   	                time_TempUpDown++;
							                if(time_TempUpDown>time_TempUpDownNUB+5)
									         {
								         	  Temp_updownFlag=ETemp_upflag;
											  TempConSet=TempSendcom_Calculate( (sint16)(Resulttest.result[ET_result].word_F), Tempoilset );
											  HOT_init(TempConSet);
                                              PID_init();
											  DPRINTF(("pwm1=%u,set1=%u",TempConSet ,Tempoilset )); 
									         }
						   	             }
						              Tempoillast=Resulttest.result[ET_result].word_F;
				  	           }
						
			                 else          
			   	     	        {
								 
                                  if(Resulttest.result[ET_result].word_F>=Tempoilconstant_limit)
             	                    {
							         constantTemp_flag=Temp_constantYESflag;
		                             ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_zhwz);
									 PIN_Tpower_relay(ERelay_off);
    	                            }

							
                                  else if( TempConSet<=(sint16)Resulttest.result[ET_result].word_F) // 0.2度
						    	      {
						    	       
   	                                    PIN_Tpower_relay(ERelay_off);
	                              
								        {
								          TgTesttype TgTest; 
                                          TgTest=TestTg_start();
								          Resulttest.result[ETg_result].word_F=TgTest.tg;
                                          Resulttest.result[ECx_result].word_F=TgTest.cx;
						    	          ResultCOMtest_sto(stopage,stooption);
                                          stooption++;
										  Resultcom_display();
                                        }
								        TempConSet=TempSendcom_Calculate( (sint16)(Resulttest.result[ET_result].word_F)+8, Tempoilset ); 
										DPRINTF(("pwm0=%u,set0=%u", TempConSet, Tempoilset )); 
						    	        PIN_Tpower_relay(ERelay_on);
								        testHOT_mune();
										
									//	DPRINTF(("t=%u,ts=%u\n",(sint16)Resulttest.result[ET_result].word_F,TempConSet )); 
										HOT_init(TempConSet);
                                        PID_init();
						     	   
					 	   	          }
					 	        }
						    SysLinearTimer=0;
			   	          }
               	     }
              	}
			     
          	     
             else 
           	         {
           	            ShowtextLine( HOTwarn_lin,  HOTwarn_column, text_jrxtgz);
           	            StopHot_Hander();
						while(1);  
		   	         }

			   
		   
          
			 if(Keyset.keyEfficiency==key_back)
					{
					   StopHot_Hander();
					   return(0);
			 	    }
        
          	   }
           	}
		 }
  	 return(0);
}




void StopSave_hander(void)
{
	PWM_sign_stop();
}


void StopHot_Hander(void)
{
   PIN_Tpwm_Write(EHOTL_pwm);
   TimerDisable(TIMER2_BASE, TIMER_A);
   PIN_Tpower_relay(ERelay_off);
}




















