#include "file_ah9837.h"


/*
static volatile u16 DelayTimer = 0;
static u8 TickPhase = 0;
static uint32 SysLinearTimer = 0;


uint32 GetSysLinearTimer(void)
{
 
	return SysLinearTimer;
}

void SetSysLinearTimer(uint32 timer )
{
 	SysLinearTimer=timer;
}









void SysTickHandler(void)	//every 1ms
{
	TickPhase ++;
    SysLinearTimer++;
	switch(TickPhase)
		{
		case 8:
#ifdef USB_STORE_EN				
			Usb_Host_SysTick();
#endif
			break;
    
		case 10:
			TickPhase = 0;
			break;
		}

	

	if(DelayTimer)
		{
		DelayTimer --;
		}
	
}
*/

void USbdisk_hander(uint16 flag)

{
    //uint16 conuter=0; 
    uint16 USbflag;
	unsigned char  buffer[5000]={0};
	unsigned short cnt,j;
	RTC_T Time;
//	unsigned char count;
     cnt =usb_stodata(buffer, &Time)	;
    if(flag==EPcCom_file)
    	{
           for(j=0; j<cnt;j++)
           	{
           	 UARTCharPut(UART0_BASE, buffer[j]);
           	}
		 
    	}
	else
		{
   // Usb_Host_Init();      
     Udisk_work=EUdiskYes;
    ShowtextLine(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width, text_zhuancun);//	U盘失败
	Reversepic(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width,16,4);
   
   
	
    SysLinearTimer = 0;
	//conuter = GetSysLinearTimer()+1000;
	while(1)
		{

		 Usb_Host_Thread();
	 	 if(SysLinearTimer>2*TIMER_FREQ)
			{
			
			 USbflag=TestDataUsbDisk( cnt, buffer, &Time );
			  break;
			}
		}
     if(USbflag==false)
    	{
    	    
          ShowtextLine(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width, text_shibai);//	U盘失败
    	}
   else
    	{
   	     ShowtextLine(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width, text_wancheng);//	U盘失败
     	}
	Reversepic(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width,16,4);
    SysLinearTimer = 0;
   
	while( SysLinearTimer<3*TIMER_FREQ);
		
     ShowtextLine(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width, text_Upan);//	U盘失败
	Reversepic(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width,16,4);
   Udisk_work=EUdisk_No;
  
  }	

}


					                         











unsigned short usb_stodata(unsigned char  *buffer,RTC_T *Time)
{

  
	unsigned short cnt;
	
   	Time->Year  =time.time.year;  // Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.year));
	Time->Month = time.time.month;  // Int16_bcd(modbusInt16( timeMT4200_Analyse.mune.month));
	Time->Date  = time.time.day ;  // Int16_bcd(modbusInt16( timeMT4200_Analyse.mune.day));
	
	Time->Hours = time.time.hour;  // time.time.year;  //  Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.hour));
	Time->Minutes =time.time.minute;  //  Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.minute));
	Time->Seconds =time.time.second;  // Int16_bcd(modbusInt16(timeMT4200_Analyse.mune.second)); 
	

	cnt = 0;
   /*   if(modifyk.Sensor[ESensor_Compant]==Ecompant_PuHua)   
       {
         cnt+=WritToTxt(buffer+cnt,"福建普华电子科技有限公司\n");
      	}
	  else*/
	  	{
	  	 cnt+=WritToTxt(buffer+cnt,"福建瑞能博尔电力设备有限公司\n");
	  	}
	cnt+=WritToTxt(buffer+cnt,"AH9688 SF6气体密度继电器检验仪\n");	
	


	

			 
	
			    
			    
                 cnt+=WritToTxt(buffer+cnt,"Tg&:  %5.4f \n",Resulttest.result[ETg_result].word_F);
 			     cnt+=WritToTxt(buffer+cnt,"Cx:  %5.4f \n",Resulttest.result[ECx_result].word_F);
				 cnt+=WritToTxt(buffer+cnt,"E:  %5.4f \n",Resulttest.result[ECx_result].word_F/60.0);  
                 cnt+=WritToTxt(buffer+cnt,"Rx:  %5.4f \n",Resulttest.result[ERx_result].word_F); 
                 cnt+=WritToTxt(buffer+cnt,"p:  %5.4f \n",Resulttest.result[ERx_result].word_F*6.78);
				 

	
	cnt+=WritToTxt(buffer+cnt,"  测试时间: %2x-%2x-%2x  %2x:%2x \n",(time.time.year),(time.time.month),(time.time.day),(time.time.hour),(time.time.minute))	;
	return(cnt)	 ;

}







