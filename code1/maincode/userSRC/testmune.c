#include "file_ah9837.h"


void Cair_test(void)
{  
  settype settemp;
  TgTesttype TgTest;
  debug_flag=EGeneral_sub;  
  settemp=set;
  set.mune.Vdc=E00Vdc;
  InitLCD();
  ResultMune_display();
  SysLinearTimer=0	;
  while(SysLinearTimer<TIMER_FREQ)
     {
      if( Keyset.keyEfficiency==key_ok|key_oil)
    	 {
    	   debug_flag=EDebug_sub;
	     }
	 }
  //Uart0Send(0x55);
  TgTest=TestTg_start();//介质损耗测量
  Resulttest.result[ETg_result].word_F=TgTest.tg;
  Resulttest.result[ECn_result].word_F=Resulttest.result[ECx_result].word_F=TgTest.cx;
  Resulttest_display();
  set=settemp;
  writebyte_much(Cn_addr,4,Resulttest.result[ECn_result].word_U8);
  if( debug_flag==EDebug_sub)
  	{
  	 while(1)
  	 	{
  	 	  if(key_back==Keyset.keyEfficiency)
  	 	  	{
  	 	  	 break;
  	 	  	}
		  else if(key_ok==Keyset.keyEfficiency)
		  	{			  
			  	  uint16 lin;
			  lin=Annwarn_lin*LineChar+0x800;
			  OutPortCom3( lin&0xff,lin/0x100,0x42 );
		  	}
  	 	}
  	}



  
}


void R_test(void)
{
  
  settype settemp;
  settemp=set;
  set.mune.Vac=E00Vac;
  
  InitLCD();
  ResultMune_display();
  SysLinearTimer=0	;
  debug_flag=EGeneral_sub;
  while(SysLinearTimer<TIMER_FREQ)
     {
      if( Keyset.keyEfficiency==key_ok|key_oil)
    	 {
    	   debug_flag=EDebug_sub;
	     }
	 }
  //Uart0Send(0x55);
  Resulttest.result[ERx_result].word_F=TestR_start();
  Resulttest_display();
  set=settemp;
}



void  cs_start()
 	{
  if(set.mune.Vac!=E00Vdc)
	     {
	       TgTesttype TgTest;
           TgTest=TestTg_start();
		   Resulttest.result[ETg_result].word_F=TgTest.tg;
           Resulttest.result[ECx_result].word_F=TgTest.cx;
		   InitLCD();

		   
         //  Resulttest_display( );
		    Resultcom_display();
		  
		  
	  	 }

	  if(set.mune.Vdc!=E00Vdc)
	  	{
	  	  if(set.mune.Vac!=E00Vac)
            {
              discharge_1min();
			  ClearScreen_sector(Chargewarn_lin-16 , Chargewarn_column, 17,16);
		   	} 
	  	 charge_1min();
	  	 Resulttest.result[ERx_result].word_F=  TestR_start();
	  	}
      InitLCD();
      ResultMune_display();
	  Resulttest_sto();
	  Resulttest_display();
       
	  
	  
 	}




float  TestR_start(void)
 {
   float R_P;
   uint16 command;
   float V_set;
   float PP_temp;
   
   Sendtgc(ERelay_main, debug_flag, EFre_000);
   
   V_set=100.0* (float)set.mune.Vdc;
   PP_temp=(V_set/modify_k.f_k[EVdcK_modify].word_F)*Vpp_Pwmstandard;       ; // 	=V_adj(fre_F);
   
   PIN_DCAC_pwm(EDC_power);
   PIN_TDA7367stand_Write(ETDA7367work_no);

   PWM_sign_acc(0.0,PP_temp);
   SysLinearTimer =0;
   while(SysLinearTimer <TIMER_FREQ);
 
   Vsign_xs(V_set/2.0,EFre_000);
   
   Sendtgc(EstartR_main, debug_flag, EFre_000);
   SysLinearTimer =0;
   rx_flag=0x0;
   while(SysLinearTimer <(TIMER_FREQ *20))
   	{
   	 if(key_back==Keyset.keyEfficiency)
  	 	  	{
  	 	  	 StopHot_Hander();
  	 	  	 PWM_sign_stop();
  	 	  	 return(0);
  	 	  	}
   	 
   	 if(rx_flag==rx_succeed)
   	 	{
   	 	    command=rxlm3stg_Hander();
		    switch(command)
			   {
			     case (EResult_TXmain<<8)|EResult_tg:
                	   break;
					  
				 case (EResult_TXmain<<8)|EResult_R:
                	   R_P=resultRX.mune.R_p;  //显示角差
				       break;	 

				 default:
				 	   break;
				 	
               }
	      if(command==((EStation_TXmain<<8)|ETest_off) )
				   {
				     //  while(width!=0);
				     PWM_sign_stop();
				     break;
				   }	
		 
	  	}
	   
   }
   
  
  return(R_P);
   
 
 }
TgTesttype  TestTg_start(void)
 {
   float Ann;
   float Knn;
   float fre_F,fre_B;
   float PP_temp;//幅值
   float tg_F,tg_B;
   float cx_F,cx_B;
   uint8 Efre_F,Efre_B;
   TgTesttype TgTest;
   uint16 command;
   float V_set;
   switch(set.mune.Fre)
   	{
   	 case EFre50_0:
	 	  fre_F=fre_B=50.0;
		  Efre_F=Efre_B=EFre_500;
		  break;
     case EFre50_2:
	 	  fre_F=47.5; 
		  fre_B=52.5;
		  Efre_F=EFre_475;
		  Efre_B=EFre_525;
		  break;
     case EFre50_5:
	 	  fre_F=45.0;
		  fre_B=55.0;
		  Efre_F=EFre_450;
		  Efre_B=EFre_550;
		  break;
	 case EFre60_0:
	 	  fre_F=fre_B=60.0;
		  Efre_F= Efre_B=EFre_600;
		  break;
	 case EFre60_2:
	 	  fre_F=57.5;
		  fre_B=62.5;
		  Efre_F=EFre_575;
		  Efre_B=EFre_625;
		  break;	  
	  case EFre60_5:
	 	  fre_F=55.0;
		  fre_B=65.0;
		  Efre_F=EFre_550;
		  Efre_B=EFre_650;
		  break;	  	  
   	}  
   V_set=100.0* (float)set.mune.Vac;
   PP_temp=(V_set/modify_k.f_k[EVacK_modify].word_F)*Vpp_Pwmstandard;       ; // 	=V_adj(fre_F);
   /* 切换AC模式*/
   PIN_DCAC_pwm(EAC_power);
   /* TDA7396工作*/
   PIN_TDA7367stand_Write(ETDA7367work_yes);
  /*设置交流输出  频率和幅值*/
   PWM_sign_acc(fre_F,PP_temp);
   SysLinearTimer =0;
   while(SysLinearTimer <TIMER_FREQ);//等待稳定?  
   Vsign_xs(V_set/2.0,Efre_F);//这里应该是检测电压是否生成成功
   Sendtgc(EstartTg_main,debug_flag, Efre_F);
   SysLinearTimer =0;
   rx_flag=0x0;
   while(SysLinearTimer <(TIMER_FREQ *20))
   	{
   	  if(key_back==Keyset.keyEfficiency)
  	 	  	{
  	 	  	   StopHot_Hander();
  	 	  	  PWM_sign_stop();
  	 	  	  return(TgTest);
  	 	  	}
   	 if(rx_flag==rx_succeed)
   	 	{
   	 	    command=rxlm3stg_Hander();
		    switch(command)
			   {
			     case (EResult_TXmain<<8)|EResult_tg:
                	 tg_F=resultRX.mune.tgA;
				     cx_F=resultRX.mune.cx;
                     break;
				 case (EResult_TXmain<<8)|EResult_Ann:
                	
                	 Ann=resultRX.mune.Ann;  //显示角差
				     Knn=resultRX.mune.Knn;
				     break;	 
				 default:
				 	 break;				 	
               }
	      if(command==((EStation_TXmain<<8)|ETest_off) )
				   {
				     //  while(width!=0);
				   //   StopHot_Hander();
				     PWM_sign_stop();
				     break;
				   }	
		 
	  	}
	   
   	 }

	xs_Ann(0,Ann);
	xs_Ann(1,Knn);
	delay(0x3000000);
   
	PWM_sign_acc(fre_B,PP_temp);
	SysLinearTimer =0;
	while(SysLinearTimer <TIMER_FREQ);
	Vsign_xs(V_set/2.0,Efre_B);
	Sendtgc(EstartTg_main,debug_flag, Efre_B);
	SysLinearTimer =0;
	rx_flag=0x00;
   while(SysLinearTimer <(TIMER_FREQ *20))
   	{
   	 if(key_back==Keyset.keyEfficiency)
  	 	  	{
  	 	  	  PWM_sign_stop();
			  StopHot_Hander();
  	 	  	  return(TgTest);
  	 	  	}
   	 if(rx_flag==rx_succeed)
   	 	{
   	 	    command=rxlm3stg_Hander();
		    switch(command)
			   {
			     case (EResult_TXmain<<8)|EResult_tg:
                	 tg_B=resultRX.mune.tgA;
				     cx_B=resultRX.mune.cx;
					 break;
				 case (EResult_TXmain<<8)|EResult_Ann:
                	 Ann=resultRX.mune.Ann;  //显示角差
				     Knn=resultRX.mune.Knn;
                     break;
				 default:
				 	 break;
				 	
               }
		    if(command==((EStation_TXmain<<8)|ETest_off) )
				   {
				     PWM_sign_stop();
				     break;
				   }	 
	  	}
   	 }
  TgTest.tg=(tg_B+tg_F)/2.0;
  TgTest.cx=(cx_B+cx_F)/2.0*50;
  PWM_sign_stop();
  xs_Ann(2,Ann);
  xs_Ann(3,Knn);
  return(TgTest); 
 }

void Vsign_xs(float V_set,uint8 fre)
{
   float V_new;
   float V_last=0;
   uint16 command;
   uint32 Timer_B;
   wordtype U_k;
   uint32 Vwrong_nub=0;
   uint32 rx_nub=0;
   float fre_k;
   fre_k=((fre-EFre_450)*2.5+45.0)/50.0;
   Sendtgc(EstartV_main,debug_flag,fre);//让下位机进行电压测量//频率为0时测量直流
   if(fre!=EFre_000)//直流
      {
       readbyte_much(Vac_K_addr,4,U_k.word_U8); 
   	  }
   else
   	  {
   	    readbyte_much(Vdc_K_addr,4,U_k.word_U8); 
		fre_k=1;
   	  }
   SysLinearTimer =0;
   rx_flag=0x00;
   while(SysLinearTimer <(TIMER_FREQ*5)/2)
   	{
   	  Timer_B= SysLinearTimer+20;  
      while(rx_flag!=rx_succeed)   //死循环
         	{
			  if(SysLinearTimer>Timer_B)
			  	{
			  	 break;
			  	}
      	    }
	  rx_nub++;
      command=rxlm3stg_Hander();
	  if(command==((EResult_TXmain<<8)|EResult_vL))
	      {
	        V_new=U_k.word_F*resultRX.mune.vL/fre_k;
	        V_display(Voltage_lin, Voltage_column+0x10,V_new);   //显示电压
	        if( (V_new<V_last)&&(V_new< V_set)&&(rx_nub>3))
	        	{
	        	 Vwrong_nub++;
				 if(Vwrong_nub>0x6)
				 	{
				 	   PWM_sign_stop();
					   ShowtextLine(Workwarn_lin , Workwarn_column,text_jyxtgz)	;  //高压系统故障
					   ShowtextLine(Workwarn_lin+Workwarn_high, Workwarn_column,text_cjx);//查接线
					   Sendtgc(Estop_main,debug_flag,0x0);
           			   while(1)  ;                
				 	}
	        	}
			else
				{
				 V_last=V_new;
				}
			
	  	  } 
       
	
   	}

 if(V_new< V_set)
	{
	  PWM_sign_stop();
	  ShowtextLine(Workwarn_lin , Workwarn_column,text_jyxtgz)	;//高压系统故障
	  ShowtextLine(Workwarn_lin+Workwarn_high, Workwarn_column,text_cjx);//查接线
	  Sendtgc(Estop_main,debug_flag,0x0);
      while(1)  ;                
	}   
 Sendtgc(Estop_main,debug_flag,0x0);
}

void  discharge_1min(void )
{
  uint8 i;
  ShowtextLine( SIGNwarn_lin, SIGNwarn_column, text_zzfd);
  SysLinearTimer=0;
  i=0x0;
 // charge_mune(i);
  
  while(1)
	{
	 
     while(SysLinearTimer< (TIMER_FREQ*60/16)  );
	 SysLinearTimer=0; 
	 discharge_mune(i);
	 i++;
	 if(i>=16)
	 	{
	 	 break;
	 	}
    
	 
  	}
}

 
void charge_1min(void)
{
 uint8 i;
 ShowtextLine( SIGNwarn_lin, SIGNwarn_column, text_zzcd);
 SysLinearTimer=0;
 i=0;
// discharge_mune(i);
 while(1)
	{
     while(SysLinearTimer< (TIMER_FREQ*60/16)  );
	 SysLinearTimer=0; 
	 charge_mune(i);
	 i++;
	 if(i>=16)
	 	{
	 	 break;
	 	}
	
  	}
}

void charge_mune(uint8 option)
  {
    uint8 i;
    uint16   StartAddr;
    StartAddr=Chargewarn_lin*LineChar + Chargewarn_column+0X0800+option; //定位起始位置
    option++;
    for(i=0;i<option;i++)
     {
	   OutPortCom3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24); //set address
       
       OutPortCom2 (0Xf0,0xc0);           //FJPH[i*LineWidth+j]
          
       
       StartAddr=StartAddr - LineChar; 


      }
}

  
void discharge_mune(uint8 option)
{
    uint8 i;
    uint16   StartAddr;
    StartAddr=Chargewarn_lin*LineChar + Chargewarn_column+0X0800+option; //定位起始位置
    option=16-option;
    for(i=0;i<option;i++)
     {
	   OutPortCom3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24); //set address
       OutPortCom2 (0Xf0,0xc0);           //FJPH[i*LineWidth+j]
       StartAddr=StartAddr - LineChar; 
      }
}






uint8 Vxsign_xs()    //转成标准侧电压
{
   float V_new;
   float V_last=0;
   float V_set;
   uint8 fre=EFre_500;
   uint32 rx_nub=0;
   uint16 command;
   uint32 Timer_B;
   wordtype U_k;
   uint32 Vwrong_nub=0;
   float PP_temp;

   V_set=100.0* (float)E600Vac;
   PP_temp=(V_set/modify_k.f_k[EVacK_modify].word_F)*Vpp_Pwmstandard;       ;

   PIN_DCAC_pwm(EAC_power);
   PIN_TDA7367stand_Write(ETDA7367work_yes);
   PWM_sign_acc(50.0,PP_temp);
   Sendtgc(EstartX_main,debug_flag,fre);
   SysLinearTimer =0;
   while(SysLinearTimer <TIMER_FREQ);

   
   readbyte_much(Vac_K_addr,4,U_k.word_U8); 
   V_set= V_set/(2.0*U_k.word_F);
   V_display(Voltage_lin+0x10, Voltage_column+0x10,V_set); 
   SysLinearTimer =0;
   rx_flag=0x00;
   while(SysLinearTimer <TIMER_FREQ*3/2)
   	{
   	  Timer_B= SysLinearTimer+20;  
      while(rx_flag!=rx_succeed)   //死循环
         	{
			  if(SysLinearTimer>Timer_B)
			  	{
			  	 break;
			  	}
      	    }	
      command=rxlm3stg_Hander();
	  rx_nub++;
	  if(command==((EResult_TXmain<<8)|EResult_vL))
	      {
	        V_new=resultRX.mune.vL*(50.0/Resulttest.result[ECn_result].word_F);
	        V_display(Voltage_lin, Voltage_column+0x10,V_new );   //显示电压
	        if( (V_new<V_last)&&(V_new< V_set)&&(rx_nub>3))
	        	{
	        	  Vwrong_nub++;
				  if(Vwrong_nub>0x8)
				 	{
				 	   PWM_sign_stop();
					   ShowtextLine(Workwarn_lin , Workwarn_column,text_jyxtgz)	;                  //
					   Sendtgc(Estop_main,debug_flag,0x0);
                       while(1)
		  	            { 
		  	              if(Keyset.keyEfficiency==key_back)
		  	    	          {
		  	    	           return(TRUE_z);
		  	    	           } 
				
		  	            }               
				 	}
	        	}
			else
				{
				 V_last=V_new;
				}
			
	  	  } 
	 




	
   	}

 	
 Sendtgc(Estop_main,debug_flag,0x0);
 PWM_sign_stop();
 
       V_last*=U_k.word_F;
	//   V_display(Voltage_lin+0x10, Voltage_column+0x10,V_last);   //显示电压
	//   V_display(Voltage_lin+0x20, Voltage_column+0x10,U_k.word_F);   //显示电压
       if(V_last<(70.0* (float)E600Vac))     //小于420v      > 600
        	{
        	// InitLCD();
			 ShowtextLine(0x18,0x0,text_cjx);	
			
			 while(1)
		  	   { 
		  	    if(Keyset.keyEfficiency==key_back)
		  	    	{
		  	    	 return(TRUE_z);
		  	    	} 
				else if(Keyset.keyEfficiency==key_ok)
		  	    	{
		  	    	 InitLCD();
		  	    	 return(FALSE_z);
		  	    	} 
				
		  	    }
			 
        	}
        else if(V_last<140.0* (float)E600Vac)      //小于840v     >  600
        	{
              //InitLCD();
			  ShowtextLine(0x0,0x0,text_kbjr);	
			  ShowtextLine(0x10,0x0,text_ywbdy90);	
			  ShowtextLine(0x20,0x0,text_afwjcxsz);	
			  ShowtextLine(0x30,0x0,text_aqdjjxyx);	
              while(1)
		  	   { 
		  	    if(Keyset.keyEfficiency==key_back)
		  	    	{
		  	    	 return(TRUE_z);
		  	    	} 
				 else if(Keyset.keyEfficiency==key_ok)
		  	    	{
		  	    	 InitLCD();
		  	    	 return(FALSE_z);
		  	    	} 
				
		  	    }
		   	}
			
		else
			{
			 return(FALSE_z);
			} 


 
}


