 #include "file_ah9837.h"


enum{Efre_time,Eportpin,};
enum{EfristEdgn,EsecondEdgn};

#define _FRE_readnub 122

#define _FRE_avrnub  5

uint32  FourierTime;  
const uint32 Pre_Fre[]={1,Pre450_500,Pre475_500,Pre500_500,Pre550_500,Pre575_600,Pre600_600,Pre625_600,Pre650_600};
enum{Echannl_N,Echannl_X};
//========================================================
void sinacose(void)   //
{
 uint32 i;
 for(i=0x00;i<_FourierTime_sampleNub;i++)
 	{
 	 float angle;
	 angle=i*2*pi/_FourierTime_sampleNub;
 	 sinA[i]=(sint16)(sin(angle)*_sin_flag1);
	 cosA[i]=(sint16)(cos(angle)*_sin_flag1);	
 	}
 
}
//=======================
void start_adj(void)
{
  uint32 flag=0;
  uint32 N_temp;

  while(1)
	 {

		     while((TimerIntStatus(TIMER0_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS  );
             HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CNVST<< 2))) = 0;//Ad7367CnvstWrite(0);
    	     TimerIntClear(TIMER0_BASE, TIMER_RIS_TATORIS );
		     HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CNVST<< 2))) = PIN_AD7367_CNVST;//Ad7367CnvstWrite(1);
             while (HWREG(GPIO_PORTB_BASE  + (GPIO_O_DATA + (PIN_AD7367_BUSY << 2)))==PIN_AD7367_BUSY ) ; // while (GPIOPinRead(GPIO_PORTB_BASE,PIN_AD7367_BUSY)==PIN_AD7367_BUSY ) ;         
		      {
		  	                
    		   N_temp=AD7367_read()&0x3fff;
               if(flag==0)
               	{
               	  if(N_temp>=0x2000)
			 	   {
			 	     flag=1;
			 	   }
			   	}
			   else
			   	{
			   	  if(N_temp<0x2000)
			   	  	{
			   	  	 break;
			   	  	}
			   	}
			}	

      }
}




//========================================================
void Fourier_ADCread(FourierComplextype *complex,uint32 nub,uint32 sample_T)	   //定点计算
 {
      uint32 read_nub;
	  uint32 Fourier_readNUB;
	  uint32 Fourier_time;
	  sint64 Nreal_allsum;
	  sint64 Nimage_allsum;
	  sint64 Nreal;
	  sint64 Nimage;
	  sint64 Xreal_allsum;
	  sint64 Ximage_allsum;
	  sint64 Xreal;
	  sint64 Ximage;
      //uint32 re[_FourierTime_sampleNub] ;
      for(Fourier_readNUB=0x00;Fourier_readNUB<nub;Fourier_readNUB++)
     	{
     	    Nreal_allsum=0x00;
	        Nimage_allsum=0x00;
	        Nreal=0x00;
	        Nimage=0x00;
	        Xreal_allsum=0x00;
	        Ximage_allsum=0x00;
	        Xreal=0x00;
	        Ximage=0x00;
            T0Init_sample(sample_T);
       //   while(FREN_pin==GPIOPinRead(GPIO_PORTA_BASE,FREN_pin));
	   //   while(0==GPIOPinRead(GPIO_PORTA_BASE,FREN_pin));
            start_adj();
	     for(Fourier_time=0;Fourier_time<FourierTime;Fourier_time++)
	     {
		 
	     for(read_nub=0x00;read_nub<_FourierTime_sampleNub;read_nub++)
	  	   {
	  	     while((TimerIntStatus(TIMER0_BASE,false)&TIMER_RIS_TATORIS) !=TIMER_RIS_TATORIS  );
             HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CNVST<< 2))) = 0;// Ad7367CnvstWrite(0);
    	     HWREG(TIMER0_BASE + TIMER_O_ICR) =  TIMER_RIS_TATORIS;// TimerIntClear(TIMER0_BASE, TIMER_RIS_TATORIS );
		     HWREG(GPIO_PORTB_BASE + (GPIO_O_DATA + ( PIN_AD7367_CNVST<< 2))) = PIN_AD7367_CNVST;// Ad7367CnvstWrite(1);
		     
             if((Nreal>_complex64)||(Nreal<(-1*_complex64)))
			   	{
			   	  Nreal_allsum+=Nreal/_sin_flag1;
				  Nreal=Nreal%_sin_flag1;
			   	}
			 if((Nimage>_complex64)||(Nimage<(-1*_complex64)))
			   	{
			   	  Nimage_allsum+=Nimage/_sin_flag1;
				  Nimage=Nimage%_sin_flag1;
			   	}
			   
             if((Xreal>_complex64)||(Xreal<(-1*_complex64)))
			   	{
			   	  Xreal_allsum+=Xreal/_sin_flag1;
				  Xreal=Xreal%_sin_flag1;
				 
			   	}
			  if((Ximage>_complex64)||(Ximage<(-1*_complex64)))
			   	{
			   	  Ximage_allsum+=Ximage/_sin_flag1;
				  Ximage=Ximage%_sin_flag1;
			  	} 
			   
			 
             while (HWREG(GPIO_PORTB_BASE  + (GPIO_O_DATA + (PIN_AD7367_BUSY << 2)))==PIN_AD7367_BUSY ) ; //while (GPIOPinRead(GPIO_PORTB_BASE,PIN_AD7367_BUSY)==PIN_AD7367_BUSY ) ;         
		      {
		  	    unsigned long N_temp;
				unsigned long X_temp;
				sint32  real32;
				sint32  image32 ;
				//uint32  sin_nub;
	               
			    N_temp=AD7367_read();
			    X_temp=0x3fff&(N_temp>>14);
				//re[read_nub]=
					N_temp=N_temp&0x3fff;
				
			    if(N_temp>=0x2000)
			 	  {
			 	   N_temp+=0xffffc000;
			 	  }
               //(_FourierTime*read_nub)%(_FourierTime*_FourierTime_sampleNub);
	           real32=(sint32)((uint32)N_temp)*(sint32)cosA[read_nub];
               image32=(sint32)((uint32)N_temp)*(sint32)sinA[read_nub]; 
			   Nreal+=(sint64)real32;
			   Nimage+=(sint64)image32;
			
			 
			   if(X_temp>=0x2000)
			 	 {
			 	   X_temp+=0xFFFFc000;
			 	 }
	           real32=(sint32)((uint32)X_temp)*(sint32)cosA[read_nub];
               image32=(sint32)((uint32)X_temp)*(sint32)sinA[read_nub]; 
			   Xreal+=(sint64)real32;
			   Ximage+=(sint64)image32;
			  
			 }
     	  }
		 
            Nreal_allsum+=Nreal/_sin_flag1;
		    Nimage_allsum+=Nimage/_sin_flag1;
		    Xreal_allsum+=Xreal/_sin_flag1;
		    Ximage_allsum+=Ximage/_sin_flag1;
		    complex->complex[Fourier_readNUB][Echannl_N].real=(float)Nreal_allsum;
		    complex->complex[Fourier_readNUB][Echannl_N].image=(float)Nimage_allsum;
		    complex->complex[Fourier_readNUB][Echannl_X].real=(float)Xreal_allsum;
		    complex->complex[Fourier_readNUB][Echannl_X].image=(float)Ximage_allsum;
      }
   }
/*
   if(set.Debug==EDebug_sub)	
    {  
      for(read_nub=0;read_nub<_FourierTime_sampleNub;read_nub++)
       {
         DPRINTF(("%d  ,re=%x\n",read_nub,re[read_nub]));
       }
    }
  */  
 }


//========================================================
float Farrange_FromSMALLtoBIG(float *complex_f, uint32 account_nub)
 {
   uint32   nub;
   uint32 flag;
   
 

   
 	  {
		uint32 j;
		float temp;
     	for(nub=0;nub<account_nub;nub++)
			 {   
			   flag=0;
				 {
					for	(j=0;j<account_nub-1-nub;j++)
					  { 
						 if(*(complex_f+j)>*(complex_f+j+1))
							{
							   flag=1;
							   temp=*(complex_f+j);
							   *(complex_f+j)=*(complex_f+j+1);
							  *(complex_f+j+1)=temp;
                           	 }
							
					 }
			   if(!flag)  
			   	{
			     break	;
			   	}
			   }
		   }
	   }
  		   
    
   	{
	
	  uint32 stopnub;
      float avrflag=0.0;
	  nub=account_nub/2-1;
	  stopnub= nub+_Fourier_avrnub;
	  if((stopnub>nub)&&(stopnub<account_nub))
	    {
	     for(;nub<stopnub;nub++)
	    	{
	    	 avrflag+=*(complex_f+nub);
	    	}
	  	}
	  else
	  	{
	  	 avrflag=(*(complex_f+account_nub/2))*_Fourier_avrnub;
	  	}
	 return(avrflag/_Fourier_avrnub)	  ;  
    }
  
 }
//========================================================
void  Fourier_Iaccount(FourierComplextype *complex, float *complex_f,uint32 Echannl)
 {
   uint32 i;
   for(i=0x00; i<_FourierNUB;i++)
   	{
   	 complex_f[i]=(complex->complex[i][Echannl].real*complex->complex[i][Echannl].real+complex->complex[i][Echannl].image*complex->complex[i][Echannl].image);
   	}
 }
//========================================================
void Fourier_Terroraccount(FourierComplextype *complex,float *complex_f)
 	{
	   uint32 i;
	   float tgN;
	   float tgX;
       for(i=0x00; i<_FourierNUB;i++)
     	{
         tgN=complex->complex[i][Echannl_N].image/complex->complex[i][Echannl_N].real;
		 tgX=complex->complex[i][Echannl_X].image/complex->complex[i][Echannl_X].real;
		 complex_f[i]=(tgX-tgN)/(1+tgX*tgN);                         //(X-N)
     	}	
    }

//========================================================
void  Fourier_Itestaccount(  Sampleresulttype *Sampleresult,RElaygainflagtype RElaygainflag,uint32 flag)    //有效值计算
 {
    float k_F=1.0;
	if(flag==Echannl_X)
      {
        k_F=modify_k.f_k[RElaygainflag.RElaygainBIT.CN_3+ECN3_modify].word_F*Rsample_CX[RElaygainflag.RElaygainBIT.CNgain]*16.0;  //_sin_flag1
	  }
    Sampleresult->In.word_F= sqrt(Sampleresult->In.word_F)*(2.0*_ADC7367LSBSize/1.4142135/(FourierTime*_FourierTime_sampleNub))/k_F;
	if(flag==Echannl_X)
		{
          k_F=modify_k.f_k[RElaygainflag.RElaygainBIT.CX_3+ECX3_modify].word_F*Rsample_CX[RElaygainflag.RElaygainBIT.CXgain]*16.0;
		}  
	Sampleresult->Ix.word_F = sqrt(Sampleresult->Ix.word_F)*(2.0*_ADC7367LSBSize/1.4142135/(FourierTime*_FourierTime_sampleNub))/k_F;
 }


//========================================================

void  Fourier_Iread(Sampleresulttype *Sampleresult)
{
     FourierComplextype complex;
	 	
	 Fourier_ADCread(&complex,_FourierNUB,Sampleresult->Fre_T.word_U32);
   	
   	{
     float complex_f[_FourierNUB];
	 Fourier_Iaccount(&complex,complex_f,Echannl_N);
     if(set.Debug==EDebug_sub)
	      {
	       uint16 i;
		   DPRINTF(("\n VPP_n \n"));
	       for(i=0;i<_FourierNUB;i++)
	   	     {
	   	      DPRINTF((" %f  \n", complex_f[i] ));
	       	 } 
		 
      	  }	 
	 Sampleresult->In.word_F=Farrange_FromSMALLtoBIG(complex_f,_FourierNUB);
	 
	 
     Fourier_Iaccount(&complex,complex_f,Echannl_X);

     if(set.Debug==EDebug_sub)
	      {
	       uint16 i;
		   DPRINTF(("\n VPP_x \n"));
	       for(i=0;i<_FourierNUB;i++)
	   	     {
	   	      DPRINTF((" %f  \n", complex_f[i] ));
	       	 } 
		 
      	  }	 
	 Sampleresult->Ix.word_F=Farrange_FromSMALLtoBIG(complex_f,_FourierNUB);

	 
	 Fourier_Terroraccount(&complex,complex_f);
     if(set.Debug==EDebug_sub)
	      {
	       uint16 i;
		   DPRINTF(("\n tg_nx  \n"));
	       for(i=0;i<_FourierNUB;i++)
	   	     {
	   	      DPRINTF((" %f  \n", complex_f[i] ));
	       	 } 
		 
      	  }	 

	 Sampleresult->Terror.word_F=Farrange_FromSMALLtoBIG(complex_f,_FourierNUB);
 
 }
}







//========================================================


//========================================================
uint32  warn_I( Sampleresulttype *Sampleresult)
{
 
  if(Sampleresult->In.word_F<_Low_current)
  	{
//  	 ShowtextLine(SIGNwarn_lin, SIGNwarn_column, text_bzwxh);
     return(false);
    }
  else  if(Sampleresult->In.word_F>_High_current)
  	{
  //	  ShowtextLine(SIGNwarn_lin, SIGNwarn_column, text_bzwxh);
     return(false);
    }
  if(Sampleresult->Ix.word_F<_Low_current)
  	{
 // 	 ShowtextLine(SIGNwarn_lin, SIGNwarn_column, text_clwxh);
     return(false);
    }
  else  if(Sampleresult->Ix.word_F>_High_current)
  	{
 // 	  ShowtextLine(SIGNwarn_lin, SIGNwarn_column, text_clwxh);
     return(false);
    }
  return(true); 
}

//====
//enum{E45_0HZ,E47_5HZ,E50_0HZ,E52_5HZ,E55HZ,E57_5HZ,E60_0HZ,E62_5HZ,E65_5HZ};

  



//========================================================
uint32 Fourier_Samplestart()
{
  // Resulttesttype Resulttest;
   RElaygainflagtype RElaygainflag;
   Sampleresulttype Sampleresult_NX;
   Sampleresulttype Sampleresult_NN;
 
   RElaygainflag=gainchange();	//档位选择
   sinacose();                             //sin cos 表(4周)   
  /* 获得频率 */
   Sampleresult_NX.Fre_T.word_U32=Sampleresult_NN.Fre_T.word_U32=(10*SysCtlClockGet())/(((set.Fre-EFre_450)*25+450)*_FourierTime_sampleNub);
  FourierTime=Pre_Fre[set.Fre-EFre_450];
  
	 
   Fourier_Iread(&Sampleresult_NX); //fourier 采样    IN  IX 峰值，角差 (tg)
     
   Fourier_Itestaccount(&Sampleresult_NX, RElaygainflag,Echannl_X) ;   //有效值计算
 /* 
   if(false==warn_I(&Sampleresult_NX))
   	{
   	 return(false)	 ;
   	}
*/
   
  PIN_JUNX_relay(ERelay_on);
  if( RElaygainflag.RElaygainBIT.CN_3==Egain_3_yes)
   	{
   	  PIN_JUX_relay(ERelay_on);
   	}
   else
   	{
   	 PIN_JUX_relay(ERelay_off);
   	}
   //delay();
   delay(0x1000000);

  
   
   Fourier_Iread(&Sampleresult_NN);
   Fourier_Itestaccount(&Sampleresult_NN, RElaygainflag,Echannl_N) ;
	     if(set.Debug==EDebug_sub)
	     	{
		     DPRINTF(("IXn= %f mA\n",Sampleresult_NX.In.word_F*1000));
             DPRINTF(("IXx= %f mA\n",Sampleresult_NX.Ix.word_F*1000));
	   	     DPRINTF(("INn= %f V\n",Sampleresult_NN.In.word_F));
             DPRINTF(("INx= %f V\n",Sampleresult_NN.Ix.word_F));
	     	}
   
 
   	{
		    
	         float tgA; 

			 Resulttest.result[EAnn_result].word_F=Sampleresult_NN.Terror.word_F ;
			 Resulttest.result[EKnn_result].word_F=(Sampleresult_NN.In.word_F/Sampleresult_NN.Ix.word_F) ; 
			 
			 tgA= (Sampleresult_NX.Terror.word_F-modify_k.f_k[RElaygainflag.RElaygainBIT.CX_3+ETgX3_modify].word_F)/(1+Sampleresult_NX.Terror.word_F*modify_k.f_k[RElaygainflag.RElaygainBIT.CX_3+ETgX3_modify].word_F);		 
             Sampleresult_NX.Terror.word_F=tgA;
			 
			 
			 tgA= (Sampleresult_NN.Terror.word_F-modify_k.f_k[RElaygainflag.RElaygainBIT.CN_3+ETgN3_modify].word_F)/(1+Sampleresult_NN.Terror.word_F*modify_k.f_k[RElaygainflag.RElaygainBIT.CN_3+ETgN3_modify].word_F);		 
             Sampleresult_NN.Terror.word_F=tgA;

			 
			 tgA=(Sampleresult_NX.Terror.word_F-Sampleresult_NN.Terror.word_F)/(1+Sampleresult_NN.Terror.word_F*Sampleresult_NX.Terror.word_F)	;
			
            
   
       if(set.Debug==EDebug_sub)
	             
       	{
	   
			 DPRINTF(("In=%d   ,Ix=%d  ,In3=%d  ,Ix3=%d  \n",RElaygainflag.RElaygainBIT.CNgain,RElaygainflag.RElaygainBIT.CXgain,RElaygainflag.RElaygainBIT.CN_3,RElaygainflag.RElaygainBIT.CX_3));
           //  DPRINTF(("T= %d\n", Sampleresult_NX.Fre_T.word_U32));
	       //  DPRINTF(("f= %f\n",50000000.0/(float) Sampleresult_NX.Fre_T.word_U32));

			 DPRINTF(("TgNX= %f \n",Sampleresult_NX.Terror.word_F));
	   	     DPRINTF(("TgNN= %f \n",Sampleresult_NN.Terror.word_F));
			
             DPRINTF(("TerrorA=  %f \n",tgA));
       	}	
			
	      
          Resulttest.result[ETg_result].word_F= tgA*100;
          Resulttest.result[ECx_result].word_F=(Sampleresult_NX.Ix.word_F/Sampleresult_NX.In.word_F)*(Sampleresult_NN.In.word_F/Sampleresult_NN.Ix.word_F);
          //Resulttest.result[EE_result].word_F= Resulttest.result[ECx_result].word_F;
          DPRINTF(("cx=  %f \n",Resulttest.result[ECx_result].word_F));

   }

    Sendstc_result(EResult_Ann);
    Sendstc_result(EResult_Ann);
	
	Sendstc_result(EResult_tg);
	Sendstc_result(EResult_tg);
	
	Sendstc_station(ETest_off);
	Sendstc_station(ETest_off);
    return(true);  
 
 }

  
 




