 #include "file_ah9837.h"

#define Bellontime 5
#define Bellofftime 10

  void delay(uint32 i)
{
 for( ;i>0;i--)
 	{
 	}
}


 
void BellsetHandle(uint32 flag)
 	{
      switch(flag)  
      	{
          
    	   case EOne_bellstate:
		  	  Bellset.stateflag=EOne_bellstate;
			  Bellset.timecurrently=Bellontime;
		  	  BellWrite(EBellon);
              break;

           case EOnPeriod_bellstate:
		   case EOffPeriod_bellstate:
                Bellset.stateflag=EOnPeriod_bellstate;
			    Bellset.timecurrently=Bellset.timeon=Bellontime;
			    Bellset.timeoff=Bellofftime;
		  	    BellWrite(EBellon);
                break;
		   default:
		  	  Bellset.stateflag=EStop_bellstate;
		  	  BellWrite(EBelloff);
              break;	
			  
		
      	}
	
 	}





 void BellHandle()
 	{

	  
      if(Bellset.stateflag!=EStop_bellstate)
      	{
	  
      	  Bellset.timecurrently--;
		  if(Bellset.timecurrently==0)
		  	{
		  	 if(Bellset.stateflag==EOne_bellstate)
		  	 	{
		  	 	   BellWrite(EBelloff);
				   Bellset.stateflag=EStop_bellstate;
		  	 	  	
		  	 	}
               else
			   {
			   	if(Bellset.stateflag==EOnPeriod_bellstate)
               	  {
                    Bellset.timecurrently=Bellset.timeoff;
				    BellWrite(EBelloff);
				    Bellset.stateflag=EOffPeriod_bellstate;
			   	   }
			      else
			   	  {
			   	    Bellset.timecurrently=Bellset.timeon;
				    BellWrite(EBellon);
				    Bellset.stateflag=EOnPeriod_bellstate;
			   	  }

               }
		  	}
      	}
 	}



#define KeyEfficiencytime          3         //第一次有效计时
#define KeyNullitytime_first     (3+10)     //长按第一次无效计时
#define KeyNullitytime_more     (3+10+7)   //长按第一次后无效计时



void KeyHandle()
 {
   uint8 keycurrently;
   Keyset.keyEfficiency=key_no;
   keycurrently=(uint8)GPIOPinRead(PORTH_key,PIN_Kright|PIN_Kstart|PIN_Kleft|PIN_Kdown)&0x0f;
   keycurrently|=(uint8)GPIOPinRead(PORTB_key,PIN_Krest|PIN_Kok|PIN_Kup|PIN_Kback)&0xf0;
 
   keycurrently=(keycurrently&key_all)^key_all;

   if(keycurrently!=key_no)
   	{
      if(keycurrently!=Keyset.keyOld)
      	{
      	  Keyset.keyOld=keycurrently;   //按键变化 (可能误读)
      	  Keyset.keyTime=0;
      	}
	  else
	  	{
	  	  Keyset.keyTime++;
		  if((Keyset.keyTime==KeyEfficiencytime)||(Keyset.keyTime==KeyNullitytime_first)||(Keyset.keyTime==KeyNullitytime_more) )
		  	{
		  	 Keyset.keyEfficiency=keycurrently;
			 BellsetHandle(EOne_bellstate);
		      if (Keyset.keyTime==KeyNullitytime_more)
		       {
		  	     Keyset.keyTime=KeyNullitytime_first;
			   }  
	 	  	}
        }
   }
    
 }  



#define CoverEfficiencytime   3 

void  Coverhandle() //盖子判断
{
 
  if(Coverset.Coverwork==ECover_Workon)
  	{
  	  uint8 Covercurrently;
      Covercurrently=(uint8)GPIOPinRead(GPIO_PORTE_BASE,PIN_cover);
      if(Covercurrently==Coverset.Coverold)
      	{
      	 Coverset.Covertime++;
		 if(Coverset.Covertime==CoverEfficiencytime)
		 	{
              Coverset.CoverAlarm=(Covercurrently==PIN_cover)? ECover_AlarmYes:ECover_AlarmNO;
			  Coverset.Covertime=CoverEfficiencytime;
		 	}
	   	}
	  else
	  	{
	  	 Coverset.Covertime=0x00;
		 Coverset.CoverAlarm=ECover_AlarmIgnore;
		 Coverset.Coverold=Covercurrently;
	  	}
  	}
}


#define GanEfficiencytime   3 		
void GndHandle()	 //接地判断
{
   if( Ganset.Ganwork==EGan_Workon)
  	{
  	  uint8  Gancurrently;
      Gancurrently=(uint8)GPIOPinRead(GPIO_PORTJ_BASE,PIN_gan);
      if( Gancurrently== Ganset.Ganold)
      	{
      	 Ganset.Gantime++;
		 if(Ganset.Gantime==GanEfficiencytime)
		 	{
              Ganset.GanAlarm=(Gancurrently==PIN_gan)? EGan_AlarmYes:EGan_AlarmNO;
			  Ganset.Gantime=GanEfficiencytime;
		 	}
		
      	} 	
			
	  else
	  	{
	  	
	  	 Ganset.Gantime=0x00;
		 Ganset.GanAlarm=EGan_AlarmIgnore;
		 Ganset.Ganold=Gancurrently;
	  	}
  	}

}

void  oiltempHandle()	 //油温
{

//  Oiltempset.oilTAlarm=(PIN_Twarn==(uint8)GPIOPinRead(GPIO_PORTC_BASE,PIN_Twarn))?EOiltemp_AlarmYes:EOiltemp_AlarmNO;
/*
  if(Oiltempset.oilAlarm==EOiltemp_AlarmYes)
  	{
  	   //显示发送
  	   Oiltempset.oilAlarm=EOiltemp_AlarmNO;
  	}
*/
}



void mainHandleinit()
{
  BellsetHandle(EStop_bellstate);
   Udisk_work=EUdisk_No;
  

  Keyset.keyEfficiency=key_no;
  Keyset.keyOld=key_no;
  Keyset.keyTime=0;

  Coverset.Coverold=ECover_NO;
  Coverset.Covertime=0;
  Coverset.CoverAlarm=ECover_AlarmIgnore;
  Coverset.Coverwork=ECover_Workon;
  
  Ganset.Ganold=EGan_Yes;
  Ganset.Gantime=0;
  Ganset.GanAlarm=EGan_AlarmIgnore;
  Ganset.Ganwork=EGan_Workon;  

  Oiltempset.oilTAlarm=EOiltemp_AlarmNO;
  Oiltempset.oilTwork=EOiltemp_Workoff;
}



void  Oilclear(void)
{
  PIN_OILclear_relay(ERelay_on);
}


uint8  Coverdispose(void)
{
  if(Coverset.Coverwork==ECover_Workon)
  	{
  	 if(Coverset.CoverAlarm==ECover_AlarmYes)
  	 	{
          InitLCD();
		  ShowtextLine(0x18,0x0,text_gsgzjxyx);	//盖上盖子继续
		  ShowtextLine(0x28,0x0,text_aqdjbzts);	//按启动建不再提示
          SysLinearTimer=0;
		  while(SysLinearTimer<1*TIMER_FREQ);
		  while(1)
		  	{ 
		  	    if(Keyset.keyEfficiency==key_ok)
		  	    	{
		  	    	  Coverset.Coverwork=ECover_Workoff;
					  Coverset.CoverAlarm=ECover_AlarmNO;
					  return(0);
		  	    	}
				if(Coverset.CoverAlarm==ECover_AlarmNO)
					{
					 return(0);
					}
		  	}
		  	
		  
  	 	}
  	}


  return(0);

}



uint8  Gandispose()   //地线提示
  {
    if(Ganset.Ganwork==EGan_Workon)
  	{
  	 if(Ganset.GanAlarm==EGan_AlarmYes)
  	 	{
          InitLCD();
		  ShowtextLine(0x18,0x0,text_jsdxjxyx);	
		  ShowtextLine(0x28,0x0,text_aqdjbzts);	
       	  while(1)
		  	{ 
		  	    if(Keyset.keyEfficiency==key_ok)
		  	    	{
		  	    	  Ganset.Ganwork=EGan_Workoff;
					  Ganset.GanAlarm=EGan_AlarmNO;
					  return(TRUE_z);
		  	    	}
				if(Ganset.GanAlarm==EGan_AlarmNO)
					{
					 return(TRUE_z);
					}
		  	}
		  	
		  
  	 	}
   }
    return(FALSE_z);
 }


uint8  Cuplin_check()
  {
        
	return(Vxsign_xs());
      
  }











 
