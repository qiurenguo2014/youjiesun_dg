
 #include "file_ah9837.h"

#define Uchan  AIN_ch22
#define Ichan  AIN_ch11



void AD7705_init(void)
{
  Ad7705SCLKWrite(1); 
  Ad7705SCLKWrite(1); 

  Ad7705CSWrite(0); 
  Ad7705CSWrite(0); 
  Ad7705CSWrite(0); 

  
  Ad7705RESWrite(0);
  delay(0x1000);
  Ad7705RESWrite(1);
 
}





uint32 R_test(void)
{
 
   Rgainflagtype  Rgainflag;
   float Uread;
   float Iread;
   float gain;
   PIN_JRTG_relay(ERelay_on);
   delay(0xf0000);
   Rgainflag= Rgainchange( );
   Uread=(float)Read_ad7705_U(Rgainflag.RgainBIT.U7705_gain, 0x10);
   Iread=(float)Read_ad7705_I(Rgainflag.RgainBIT.I7705_gain, 0x10);
  
    if(set.Debug==EDebug_sub)
	{
	DPRINTF(("Uread=%f, U_g=%d  , Iread=%f  ,I_g=%d,I_r=%d\n",Uread,Rgainflag.RgainBIT.U7705_gain,Iread,Rgainflag.RgainBIT.I7705_gain,Rgainflag.RgainBIT.I_gain));
	DPRINTF(("U_u=%f,   I_i=%f \n",Uread*_ADC7705LSBSize/(float)(0x01<<Rgainflag.RgainBIT.U7705_gain),Iread*_ADC7705LSBSize/(float)(0x01<<Rgainflag.RgainBIT.I7705_gain)));
	}


   

   gain=(float)(0x01<<Rgainflag.RgainBIT.U7705_gain);
   Uread=(Uread/gain-modify_k.f_k[E7705Uzio_modify].word_F)*modify_k.f_k[EUk_modify].word_F/2.0;
   
   gain=(float)(0x01<<Rgainflag.RgainBIT.I7705_gain);
   Iread=(Iread/gain-modify_k.f_k[E7705I500zio_modify+Rgainflag.RgainBIT.I_gain].word_F)/modify_k.f_k[ERk500_modify+Rgainflag.RgainBIT.I_gain].word_F;
   
   Resulttest.result[ERx_result].word_F=Uread/Iread-modify_k.f_k[ERzio_modify].word_F;
   if(set.Debug==EDebug_sub)
      	   {
      	      DPRINTF(("U=%f,  I=%f  ,r=%f\n",Uread,Iread,Resulttest.result[ERx_result].word_F));
   	       }
   Sendstc_result(EResult_R);
   Sendstc_result(EResult_R);
   delay(0x80000)	  ;
   Sendstc_station(ETest_off);
   Sendstc_station(ETest_off);
   return(true);
}

//===============================
Rgainflagtype Rgainchange( )
 {
    Rgainflagtype Rgainflag ;
    Rgainflagtype RgainflagB;
 //   uint32 Success_fLag=0;
	uint32 readdata;
	Rgainflag.RgainBIT.I7705_gain=Rgainflag.RgainBIT.U7705_gain=0;
	Rgainflag.RgainBIT.I_gain=Rgainflag.RgainBIT.U_gain=ERsample_50;
	PIN_JR_relay(ERsample_50);
	RgainflagB.RgainWORD=Rgainflag.RgainWORD;
   
	while(1)  //Success_fLag==0
	 {
	    readdata=Read_ad7705_I(Rgainflag.RgainBIT.I7705_gain, 3);
		
		if(( Rgainflag.RgainBIT.I_gain==ERsample_50)&&(Rgainflag.RgainBIT.I7705_gain==7)&&(readdata<0x0e00))   //500,128,1mv
              {
                Rgainflag.RgainBIT.I_gain=ERsample_1M;    //1m
                PIN_JR_relay(ERsample_1M);
			    Rgainflag.RgainBIT.I7705_gain=0;
              }
		else if(( Rgainflag.RgainBIT.I_gain==ERsample_1M)&&(Rgainflag.RgainBIT.I7705_gain==0x00)&&(readdata>0xff00))  //1m,00,2400mv
		   	   {
		   	       Rgainflag.RgainBIT.I_gain=ERsample_50;
				   PIN_JR_relay(ERsample_50);
			       Rgainflag.RgainBIT.I7705_gain=7;
		   	    }
		else 
		   	    {
		          Rgainflag.RgainBIT.I7705_gain=gain_adjust(readdata,Rgainflag.RgainBIT.I7705_gain);
		   	    }
		 readdata=Read_ad7705_U(Rgainflag.RgainBIT.U7705_gain, 3);      
         Rgainflag.RgainBIT.U7705_gain=gain_adjust(readdata,Rgainflag.RgainBIT.U7705_gain);
		 
       if(RgainflagB.RgainWORD==Rgainflag.RgainWORD)
       	  {
       	   return(Rgainflag);  //  Success_fLag=1;
		   // break;
          }
	   else
	   	{
	   	 RgainflagB.RgainWORD=Rgainflag.RgainWORD;
	   	}
	}
		
	
 }
uint32 gain_adjust(uint32 read_data,uint32 gain)
  {
     uint16 i;
	 uint32 gain_temp;
     if(read_data>Rcpm_data[7])
	   	{
		   gain=0x00;
	 	}
		 
		
	 else 
	  {
         for(i=0;i<7;i++) 
	       {
	        if(read_data<Rcpm_data[i])
	     	  {
	            gain_temp=i;
			    break;    
	     	  }
	       }
          gain_temp=7-i;  
	      if(gain_temp!=0)
	 	  {
	        gain_temp=gain+gain_temp;
	        if(gain_temp>7)
		      {
		         gain_temp=0x07;
		      }
		  gain=gain_temp;
	     }
	  }
	
	return(gain) 	;
  }

	
//======================
uint32 Read_ad7705_U(uint32 gain,uint32 readnub)
  {
    uint32 i;
    uint32 munedata[2];
	uint32 Uread;
   /*
   u_sum=0x0;
   i_sum=0x0;
   
   IOCLR1  = ad7705_cs;
   MSPI_Init();
   wait(100);
   IOCLR0=ad7705_res;
   wait(100);
   IOSET0=ad7705_res;
  */
  
   munedata[0]=CLKDISOnBit|CLKDIV1Bit|CLK245Bit |FS_20hz_50hz;   ;// 	// 时钟  通道1----时钟commdan   1M(2M分频），输出率50HZ，滤波截止率5.24HZ 
   write_ad7705Res(ClockR_7705|Uchan|Wrbit,munedata,1);
 

   munedata[0]=SelfCalibration_Mode|(gain<<3)|UnipolarBit|BUFOffBit| FSYNCOnBit ;//  设置 通道1，增益1，双极性，缓冲器短路，滤波器开 
   write_ad7705Res(SetupR_7705|Uchan|Wrbit,munedata,1);
   Uread=0x00;
  
   for(i=0;i<readnub;i++)
  	{

	    while (GPIOPinRead(PORT_AD7705,PIN_AD7705_DRDY)==PIN_AD7705_DRDY) ;    
  	    Read_ad7705Res(DataR_7705|Uchan|Rdbit,munedata,2);
  	 	Uread+=((munedata[0]&0xff)<<8)+(munedata[1]&0xff);
  	}
   return(Uread/readnub);
   
  }


uint32 Read_ad7705_I(uint32 gain,uint32 readnub)
  {
    uint32 i;
    uint32 munedata[2];
	uint32 Iread;
   /*
   u_sum=0x0;
   i_sum=0x0;
   
   IOCLR1  = ad7705_cs;
   MSPI_Init();
   wait(100);
   IOCLR0=ad7705_res;
   wait(100);
   IOSET0=ad7705_res;
  */
  
   munedata[0]=CLKDISOnBit|CLKDIV1Bit|CLK245Bit |FS_20hz_50hz;   ;// 	// 时钟  通道1----时钟commdan   1M(2M分频），输出率50HZ，滤波截止率5.24HZ 
   write_ad7705Res(ClockR_7705|Ichan|Wrbit,munedata,1); 
   munedata[0]=SelfCalibration_Mode|(gain<<3)|UnipolarBit|BUFOffBit| FSYNCOnBit ;//  设置 通道1，增益1，双极性，缓冲器短路，滤波器开 
   write_ad7705Res(SetupR_7705|Ichan|Wrbit,munedata,1);   
   Iread=0x00;
   for(i=0;i<readnub;i++)
  	{

	    while (GPIOPinRead(PORT_AD7705,PIN_AD7705_DRDY)==PIN_AD7705_DRDY) ;    
  	    Read_ad7705Res(DataR_7705|Ichan|Rdbit,munedata,2);
  	 	Iread+=((munedata[0]&0xff)<<8)+(munedata[1]&0xff);
	   // while (GPIOPinRead(PORT_AD7705,PIN_AD7705_DRDY)==0) ;   
  	}
   return(Iread/readnub);
   
  }




//====================================

void ad7705_cal()
 {
  /*
	IOCLR0=jr_gain;
    wait(0x20000);
  */	
  uint32 U_zio;
  uint32 I_zio;
  PIN_JR_relay(ERsample_50);
  delay(0x10000000);
  ad7705_zio(&U_zio,&I_zio);
  
	  	{
		 sint16 temp;
		 temp=(sint16)I_zio-0x8000;
		 modify_k.f_k[E7705I500zio_modify].word_F=(float)temp/64.0 ;
		}
	
	    {
		 sint16 temp;
		 temp=(sint16)I_zio-0x8000;
		 modify_k.f_k[E7705Uzio_modify].word_F=(float)temp/64.0 ;
		}


	PIN_JR_relay(ERsample_1M);
	delay(0x10000000);

	 ad7705_zio(&U_zio,&I_zio);
	  	{
		 sint16 temp;
		 temp=(sint16)I_zio-0x8000;
		 modify_k.f_k[E7705I1Mzio_modify].word_F=(float)temp/64.0 ;
		}
	/*
	    {
		 sint16 temp;
		 temp=(sint16)I_zio-0x8000;
		 modify_k.f_k[Ezio_ad7705][EUzio_2]=(float)temp/64.0 ;
		}	
    */  
	
}

void write_ad7705Res(uint32 Register,uint32 *munedata,uint32 size)
{
   uint32 i;
   
   spiDataPut(Register);
   for(i=0;i<size;i++)
      {
        spiDataPut(munedata[i]);
   	  }	
   
}
void Read_ad7705Res(uint32 Register,uint32 *munedata,uint32 size)
{
   uint32 i;
   spiDataPut(Register);
   for(i=0;i<size;i++)
      {
      //  SSIDataPut(SSI0_BASE,0x00);
        spiDataGet(&munedata[i]);
	  }	

}

void spiDataPut(uint8 dat)
 	{
         uint32 i;
         for(i=0;i<8;i++)
         	{
         	
         	  if((dat&0x80)==0x80)
         	  	{
         	  	 Ad7705DINWrite(1);
         	  	}
			  else
			  	{
			  	  Ad7705DINWrite(0);
			  	}
			  Ad7705SCLKWrite(0);
			  delay(5);
			  Ad7705SCLKWrite(1);
			  delay(5);
			  dat<<=1;
         	}

		
    }	
void spiDataGet(uint32  *dat)
 	{
		 uint8 data1=0;
         uint32 i;
         for(i=0;i<8;i++)
         	{
         	  Ad7705SCLKWrite(1);
			  delay(5);
			  Ad7705SCLKWrite(0);
			  delay(5);
         	  data1=data1<<1;
              if( PIN_AD7705_DOUT==GPIOPinRead(GPIO_PORTA_BASE,PIN_AD7705_DOUT))
	   	        {
	   	          data1|=0x1 ;
	   	         }
			 
			 
         	}
		 Ad7705SCLKWrite(1);
        *dat=data1;
		
    }	



 
#if 0
void write_ad7705Res(uint32 Register,uint32 *munedata,uint32 size)
{
   uint32 i;
   
   SSIDataPut(SSI0_BASE,Register);
   for(i=0;i<size;i++)
      {
        SSIDataPut(SSI0_BASE,munedata[i]);
   	  }	
   
}
void Read_ad7705Res(uint32 Register,uint32 *munedata,uint32 size)
{
   uint32 i;
   SSIDataPut(SSI0_BASE,Register);
   for(i=0;i<size;i++)
      {
        SSIDataPut(SSI0_BASE,0x00);
        SSIDataGet(SSI0_BASE,&munedata[i]);
	  }	

}
#endif

//===========================================================

void ad7705_zio( uint32 *I_zio,   uint32 *U_zio)
{
   uint32 i;
   uint32 munedata[2];
   /*
   u_sum=0x0;
   i_sum=0x0;
   
   IOCLR1  = ad7705_cs;
   MSPI_Init();
   wait(100);
   IOCLR0=ad7705_res;
   wait(100);
   IOSET0=ad7705_res;
  */
  
   munedata[0]=CLKDISOnBit|CLKDIV2Bit|CLK100Bit |FS_20hz_50hz;   ;// 	// 时钟  通道1----时钟commdan   1M(2M分频），输出率50HZ，滤波截止率5.24HZ 
   write_ad7705Res(ClockR_7705|Uchan|Wrbit,munedata,1);
  

   munedata[0]=SelfCalibration_Mode|(Egain128<<3)|BipolarBit|BUFOffBit| FSYNCOnBit ;//  设置 通道1，增益1，双极性，缓冲器短路，滤波器开 
   write_ad7705Res(SetupR_7705|Uchan|Wrbit,munedata,1);
   *U_zio=0;
   for(i=0;i<AD7705zio_readnub;i++)
  	{
	    while(GPIOPinRead(PORT_AD7705,PIN_AD7705_DRDY)==PIN_AD7705_DRDY) ;    
  	    Read_ad7705Res(SetupR_7705|Uchan|Rdbit,munedata,2);
  	 	*U_zio+=((munedata[0]&0xff)<<8)+(munedata[1]&0xff);
  	}
	
  /*
   IOCLR1  = ad7705_cs;
   MSPI_Init();
   wait(100);
   IOCLR0=ad7705_res;
   wait(100);
   IOSET0=ad7705_res;
*/

   munedata[0]=CLKDISOnBit|CLKDIV2Bit|CLK100Bit |FS_20hz_50hz;   ;// 	// 时钟  通道2----时钟commdan   1M(2M分频），输出率50HZ，滤波截止率5.24HZ
   write_ad7705Res(ClockR_7705|Ichan|Wrbit,munedata,1);
  

   munedata[0]=SelfCalibration_Mode|(Egain128<<3)|BipolarBit|BUFOffBit| FSYNCOnBit ;//   设置 通道2，增益1，双极性，缓冲器短路，滤波器开 
   write_ad7705Res(SetupR_7705|Ichan|Wrbit,munedata,1);
   *I_zio=0;
   for(i=0;i<AD7705zio_readnub;i++)
  	{

	    while (GPIOPinRead(PORT_AD7705,PIN_AD7705_DRDY)==PIN_AD7705_DRDY) ;    
  	    Read_ad7705Res(SetupR_7705|Ichan|Rdbit,munedata,2);
  	 	*I_zio+=((munedata[0]&0xff)<<8)+(munedata[1]&0xff);
  	}

}























