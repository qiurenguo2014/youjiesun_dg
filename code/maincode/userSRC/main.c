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




  main()
  {  
    SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_6MHZ);
	IntMasterEnable();
    Uart0Init(19200);
	Uart1Init(19200);
    DPRINTF(("Bat=%d  ,cha=%x ,Temp=%f \n",1,20,3.0));
//    ADCBAT_init();
//    Ssi0Init();   //AD7367
    //spi_ad7705Init();   //AD7705
    IoPortInit();	  //IO口初始化
//  I2CM_Init(); //Fm31256
  //TimerInit();
    PIN_JR_relay(ERelay_off);
    PIN_JRTG_relay(ERelay_off);
    PIN_JUNX_relay(ERelay_off);
    PIN_JUN_relay(ERelay_off);
    PIN_JUX_relay(ERelay_off); 	
	FlashUsecSet(49);
	AD7367_init();
	AD7705_init();     
  //   PIN_JR_relay(ERsample_1M);	
	/*	
   	{
	
      uint32 i;
	  set.Debug=EDebug_sub;
	  set.Fre=EFre_500;
	  
	  gainchange();
      Vac_read();
	  for(i=0;i<500;i++)
           {
           
            Fourier_Samplestart(); ;
			delay(0xf000*200);
           }
	}

  */	
/*
	{
		 uint32 i;
	     set.Debug=EDebug_sub;
	     set.Fre=EFre_000;
		 V_read();
		 for(i=0;i<50;i++)
		 	{
		 	  
			  DPRINTF(("I=%x   \n",Read_ad7705_I(0x07,1)));
		 	}
	
		 for(i=0;i<50;i++)
		 	{
			 
			  DPRINTF(("U=%x \n",Read_ad7705_U(0x07,1)));
		 	}
         for(i=0;i<500;i++)
           {
            R_test();
			delay(0xf000*200);
           }
    }
*/	
 	modifyK_js();
	rx_flag=0;
    while(1)
    {
     // uint8 option=0;
      
	    if((rx_flag==rx_succeed))
     	{
     	
          Sendstc_ask();
		  set.Work=0x0f&rx_data.mune.workcommand;
		  set.Debug=0x0f&(rx_data.mune.workcommand>>4);
		  set.Fre=rx_data.mune.Fre;
		  set.Voltage=rx_data.mune.Voltage;
          rx_flag=0x00;  
		  	   
          switch(set.Work)
          	{
              case EstartV_main:
			  	       V_read();
					   break;
		      case  EstartTg_main://AC
			  	      Fourier_Samplestart(); 
					  PIN_JRTG_relay(ERelay_off);
        	          PIN_JUNX_relay(ERelay_off);
                      PIN_JUN_relay(ERelay_off);
	                  PIN_JUX_relay(ERelay_off);
					  break;
			  case  EstartR_main://DC
			  	       R_test();
					   PIN_JRTG_relay(ERelay_off);
			    	   break;			                 
			  case 	Emodifyin_main:
			  	        modify_save();
				        modifyK_js();
						//DPRINTF(("In \n"));
				          break;
			  case  Emodifyout_main	:
			  	        delay(0x80000);
			 	        modify_ToView();
						modifyK_js();	
						//DPRINTF(("out \n"));
			 	        break;
			  case  EstartX_main  :
			            Vacx_read();
			            break;

              case ERelay_main:
			  	     PIN_JRTG_relay(ERelay_on);
					 PIN_JR_relay(ERsample_50);
					 break;					  
			  default :			  	    
			  	     SysCtlReset();					   
			  	     break;
		  	 
		  	}
		  if((rx_flag==rx_succeed))
				 	{
					   if(set.Work==0x0f&rx_data.mune.workcommand)
					  	  	{
					  	  	 rx_flag=0;
					  	  	}
					}
  		
     	}
     }	 


}	

 



