/*
 UART0    lm3s--stc 通讯协议
 T0---    采样周期cnvst   16;  (周期 1024点) 
 T1---    频率(相差)采样
 50ms周期  继电器切换(有无信号)



(1) 档位切换
(2) 频率 相差采样
(3) 幅值采样
*/



#include "file_ah9837.h"
void teststart(void);







  main()
  {
     uint8 option=0;
     uint8 key;
  
    SysCtlClockSet(SYSCTL_SYSDIV_4| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);
    Uart0Init(19200);
	Uart1Init(9600);
	Uart2Init(19200);
    IntMasterEnable();
    SysLinearTimer =0;
    IoPortInit();	  //IO口初始化
    I2C1Init() ;//Fm31256
   	TimerInit();
	xs6963_init();
	PIN_TDA7367stand_Write(ETDA7367work_no);
	FlashUsecSet(49);
	//T1Init_LM331();
    DPRINTF(("Bat=%d  ,cha=%d ,Temp=%d \n",1,2,3));
    Usb_Host_Init();  
    mainHandleinit();
	
    signPWM_init(50.0);
    PWM_sign_stop();
	/*LCD初始化*/
	start_mune();
	/* fm31256 eeprom 8 */
    readbyte_much(setsto_addr,settype_nub,set.byte );
 	/*修正系数*/
    modify_read();
	/**/
	Oiltempset.oilTwork=EOiltemp_Workon; 
	/*lm331初始化 温度测量使用*/
	T1Init_LM331();
	/*系统节拍*/
    SysLinearTimer=0;	
	while(SysLinearTimer<3*TIMER_FREQ)//后台参数设置
     {
       key=Keyset.keyEfficiency;
       if(key==key_modify)
    	 {
		   while(Keyset.keyEfficiency==key_modify); 
    	   option++;
		   if(option>=4)
	       	{
			   modify_read();//读取修正参数
			   TgC_read();
    	       modify();//修正
	   	    }
       	 }
    }	
   	modifyK_js();
    SysLinearTimer=0;
    rx_flag=0;
 	option=0;
mainset_go:
	  key=Keyset.keyEfficiency;
      mainset_mune();
      Reversepic(mainset_lin+option*mainset_high, mainset_column, mainset_high, 2*4);
	  while(1)
	  	{
	      while(key==Keyset.keyEfficiency)
		    {
		     if(SysLinearTimer>(3*TIMER_FREQ/4))  	   
              {
			    // Temp_account();
			  if(TRUE_z==Gandispose())//地线检测
			  	{
			  	  mainset_mune();
				  Reversepic(mainset_lin+option*mainset_high, mainset_column, mainset_high, 2*4);
			  	}
           	 
			   read_time();
			    {
				 uint8 byte[12];	
			   	 Clock_viewxs(byte)	;
			   	}
				 SysLinearTimer=0;
			 }
	  	   }
		   key=Keyset.keyEfficiency;
		  /*按键处理*/
           switch(key)
		   	{
               case key_no:
			   case key_back:
			   	        continue;
		       case key_down:
			   case key_up:
			   	      Reversepic(mainset_lin+option*mainset_high, mainset_column, mainset_high, 2*4);
			   	      option=keyoption_js(option, key,4,Emune_key);//
					  Reversepic(mainset_lin+option*mainset_high, mainset_column, mainset_high, 2*4);
                    /*  if(key==key_up)
                      	{
                         PWM_sign_acc(0.0, 0.0);
						 delay(0x80000);
                         PIN_DCAC_pwm(EDC_power);
                      	 PWM_sign_acc(0.0, 0.7);
                      	}
					  else
					  	{
					  	 PWM_sign_acc(0.0, 0.0);
						 delay(0x80000);
					   	 PIN_DCAC_pwm(EAC_power);
					  	 PWM_sign_acc(50.0, 0.8);
					  	}
					 */ 	
					  break;				
			   case key_ok:	
			   	      switch(option)
			   	      	{
			   	      	 
                          case ELan_main://语言
							    set.mune.Langue++;
							    set.mune.Langue&=0x01;
                                //ShowtextLine(mainset_lin+option*mainset_high, mainset_column+0x10,Lanset_p[set.mune.Langue]);	
								break;
					      case EOilset_main://油样设置
						  	    oidset();
							    break;
						  case EView_main://历史数据
						  	    Viewdata_Hander();
						  	   break;
						  case EClock_main://时钟设置
							   clockset_mune();
                               break;			   
			   	      	}					  
					    goto mainset_go ;
               case key_oil:                     			
			          Oilclear();//排油
					 break;
			   	     					  
		   	}
	  	}
}	

 



