     
#include "file_ah9837.h"
	
const unsigned char char_C3_2[ ]="C3_N";      //1.00000*3.167
const unsigned char  char_C10_2[ ]="C10_N";   //1.00000*10.0
const  unsigned char  char_Tg3_2[ ]="%3_N";   
const  unsigned char  char_Tg10_2[ ]="%10_N";

const unsigned char  char_C3_20[ ]="C3_X";   //1.00000*3.167
const unsigned char  char_C10_20[ ]="C10_X";  //1.00000*10.0
 const unsigned char  char_Tg3_20[ ]="%3_X";
 const unsigned char  char_Tg10_20[ ]="%10_X";
 

 const unsigned  char char_Rk_500[ ]="Rk_500";  //5.00000*100
 const unsigned  char char_Rk_10M[ ]="Rk_10M";  //1.00000*1000000
  const unsigned char char_R_0[ ]="R_0";        //0.00*1000000
 const unsigned  char char_U_K[ ]="U_K";        //1.00000*1000


 
 const unsigned  char char_PID_area[ ]="PID_A";  //area 
 const unsigned char  char_PID_transition[ ]="PID_T";
 const unsigned  char char_PID_KP1[ ]="PID_K1";
 const unsigned  char char_PID_KP2[ ]="PID_K2"; 
 
 const unsigned  char char_PID_Tkp[ ]="PID_Tkp";
 const unsigned  char char_PID_Y0[ ]="PID_Y0";
 const unsigned char  char_T_zio[ ]="T_zio";
 const unsigned char  char_T_K[ ]="T_K";

 const unsigned char  char_Vac_K[ ]="Vac_K";  //0.50000*100
 const unsigned char  char_Vdc_K[ ]="Vdc_K";  //0.70000*100

 const unsigned char  char_T100[ ]="R_T00";  //0.50000*100
 const unsigned char  char_T120[ ]="R_T60";  //0.70000*100
 
 const unsigned  char char_Save[ ]="Save";

//modify_k
//修正
/*
enum{Egain_C2,Egain_C20,Egain_R,Etemp,Ezio_ad7705};  //pendicular ,EPTui
enum{EC_3,EC_10,ETg_3,ETg_10};  //horizontal
enum{EIzio_50,EIzio_1M,EIzio_10,EUzio};  //zio_ad7705
enum{ERI_50,ERI_1M,ERI_10M,ERU};  //gain_R
enum{ETemp_zio,ETempK,ETemp_gain,Esave}; 
*/


const uint32 modifydata_init[]={ 
                                   0x10000000,0x10000000,0x00000000,0x00000000,
                                   0x10000000,0x10000000,0x00000000,0x00000000,
                                   0x10000000,0x10000000,0x10000000,0x10000000,
                                   0x00024000,0x00003000,0x00500000,0x00500000,
                                   0x00010000,0x10036000,0x10000000,0x00000000,
                                   0x20000000,0x50000000,0x00000000,0x00060000,

                                   };

const  uint8 *modify_p[ ]={ 
	                           char_C3_2, char_C10_2,char_Tg3_2,char_Tg10_2,
	                           char_C3_20,char_C10_20,char_Tg3_20,char_Tg10_20,
	                           char_Rk_500,char_Rk_10M,char_R_0,char_U_K,
	                           char_PID_area,char_PID_transition,char_PID_KP1,char_PID_KP2,
							   char_PID_Tkp,char_PID_Y0,char_T_zio,char_T_K,
							   char_Vdc_K,char_Vac_K,char_T100,char_T120,
							   char_Save,
							};

  
//======================修正设定======================
/*
#define modifymune_line     00
#define modifymune_column   01
#define modifymune_high    0x10
#define modifymune_nubkey  0x7
*/


 // =修正







 
#define modify_line   0x0
#define modify_column 0x0
#define modify_high   0x10
#define modify_width  15
#define modify_nubkey 25


#define modifydata_nubkey          6
#define modifydata_column      (modify_column+8)

void xz_mune()
  	{
  	   
		uint32 option;
		InitLCD();
     
	    for(option=0;option<modify_nubkey;option++)
	          {
	          	const  uint8 *p;
				uint8 i;
				uint16 lin=option*modify_high+modify_line;
              	p=modify_p[option];
                i=0;
				while(*p!='\0')
                   {
                     ShowPicture(lin, modify_column+i, Font1608,*p-0x20);
					 p++;
					 i++;
                   }
			  }
	
    }	

void bcd8_display(  unsigned char *byte,uint16 lin,uint8 column, uint32 xsdata)
   {
 	  uint8 i;
      union 
 	      { 
 	        uint8 byte[4];
            uint32 t32;
 	      }k;
	  k.t32= xsdata;
	  for (i=0;i<4;i++ )
             {
      	      byte[0+i*2]=0x10+(k.byte[i]>>4);
			  byte[1+i*2]=0x10+(k.byte[i]&0x0f);	
	         } 
	  charLine(lin ,column,modifydata_nubkey,byte)	;
        
  }	



void xzset_mune()
  	{
  	   
		uint8 option;
		uint8 byte[8]; 
	    for(option=0;option<modify_nubkey;option++)
           	{
             bcd8_display(byte, option*modify_high+modify_line,modifydata_column,modify_k.H_k[option]);
           	}
          
    }	





  
//==================
uint8  modify_set8(unsigned char *byte,unsigned char nub,unsigned int lin ,unsigned char column)
  {    
   unsigned char option=00;  
   uint8 key;
   key=Keyset.keyEfficiency;
   Reversepic(lin, column+option, modify_high, 1);
  
  while (1)
   {
    
    while(key==Keyset.keyEfficiency);
	key=Keyset.keyEfficiency;
    switch(key)
    {
      case 0x000:
	  case key_oil:
	  	      continue;
	  case  key_up:
      case key_down:
   	          byte[option]=keyoption_js(byte[option],key, 10,Edata_key);
              ShowPicture(lin,column+option,Font1608,byte[option]+0x10);
			  Reversepic(lin, column+option, modify_high, 1);
			  break;
          
      case key_back:  
	  	       Reversepic(lin, column+option, modify_high, 1);  
	  		   while(key==Keyset.keyEfficiency);
	           return(0x00);
			 
      case key_ok: 
	  	     Reversepic(lin, column+option, modify_high, 1);
			 option++;
             if(option>=modifydata_nubkey)
             	{
             	 option=0;
             	}
			 Reversepic(lin, column+option, modify_high, 1);
			 break;
            
     }
   }
  
  }






//==================================================================
uint8  modify()
  { 
     unsigned char option=0x0;
	 uint8 key;
     key=Keyset.keyEfficiency;	
	 xz_mune();
	 xzset_mune();
	 modify_read();
     ShowPicture(option*modify_high+modify_line, modify_column+6, Font1616,jian1);
   
	 rx_flag=0;
     while(1)
        {  
            while(key==Keyset.keyEfficiency);
        	key=Keyset.keyEfficiency;
            switch(key)
            {
               case 0x00:
			   case key_oil:
			   	           continue;

			   case key_up:		 
			   case key_down:
			   	          ShowPicture(option*modify_high+modify_line, modify_column+6, Font1616,kg);
			              option=keyoption_js(option,key,modify_nubkey,Emune_key) ;
						  ShowPicture(option*modify_high+modify_line, modify_column+6, Font1616,jian1);
                           {
							 uint16 lin;
							 lin=(option*modify_high+modify_line)*LineChar+0x800;
						     OutPortCom3( lin&0xff,lin/0x100,0x42 );
						   }
						  
			             break;

               case  key_ok:
                      switch(option)
                      	{
                      	 case ESave_modify:
						 	   writebyte_much(modify_sto, modifytype_nub, modify_k.b_k);  
                               Sendtgc(Emodifyout_main,0x00,0x00);							   
                               return(0); 
						 case EVdcK_modify:
                         case EVacK_modify:
						 	     Vmodify_set(option);
                                 modifyset_k(option);
								 Vmodifyset_sto(option);
                                 break;
                         case  ET100_modify:
						 case  ET120_modify:
                                  SysLinearTimer=0;
								  while(SysLinearTimer<TIMER_FREQ*2)
								  {
								   if( (key_ok|key_oil)==Keyset.keyEfficiency)
							      	{
							 	      Tmodify_set(option);
									  modifyset_k(option);
									  break;
						 	        }
								  }	
									 break;
                                 
								 
					     default:
						 	   modifyset_k(option)	;
							   break;
						 	  
						 	 
                      	}
					   break;
               case key_back:
			   	      
			   	       return(0) ;
					   
		  
            }
		  
        }
   
  }  

void Tmodify_set(uint8 option)
{
    uint32 i=0,j;
	uint8 byte[8];
	
	wordtype TR_sto;
    SysLinearTimer=0;
	
    while(1)
	 {
	  if(SysLinearTimer>TIMER_FREQ)
    	{

		  SysLinearTimer=0;
    	  TR_sto.word_U32=Oiltempset.oilTemp;
		   DPRINTF(("t=%u \n",TR_sto.word_U32));	
		  hex16_bcd4(TR_sto.word_U32,byte, 6);
           for(j=0;j<6;j++)
           	{
           	  ShowPicture(option*modify_high+modify_line,modifydata_column+0x10+j, Font1608,byte[j]+0x10);
           	}
		  i++;
		  if(i>5)
		  	{
		  	 break;
		  	}
    	}
    }
	if(option==ET100_modify)
      {
       writebyte_much(Temp_Zio_addr,4,TR_sto.word_U8);
		}
	else
		{
		  writebyte_much(Temp_K_addr,4,TR_sto.word_U8);
		}
} 












void Vmodifyset_sto(uint8 option)
{
   wordtype dat;
   dat=modifybigtosmall(modify_k.f_k[option]);
   dat.word_F=float_js(dat.word_U32)/100.00;
   dat.word_F=dat.word_F/resultRX.mune.vL;
   if(option==EVdcK_modify)
       {
        writebyte_much(Vdc_K_addr,4,dat.word_U8); 
   	   }
   else
   	   {
   	    writebyte_much(Vac_K_addr,4,dat.word_U8); 
   	   }
   // DPRINTF(("uK=%f \n",dat.word_F));	
}


void Vmodify_set(uint8 option)
{
  uint16 command;
  delay(0x80000);
  if(option==EVdcK_modify)
     {
      PIN_DCAC_pwm(EDC_power);
	   PIN_TDA7367stand_Write(ETDA7367work_no);
      PWM_sign_acc(0.0, Vpp_Pwmstandard);
      Sendtgc(EstartV_main,debug_flag,EFre_000);
  	}
  else
   	{
    	delay(0x80000);
	    PIN_DCAC_pwm(EAC_power);
		PIN_TDA7367stand_Write(ETDA7367work_yes);
    	PWM_sign_acc(50.0, Vpp_Pwmstandard);
        Sendtgc(EstartV_main,debug_flag,EFre_500);
 	}

  rx_flag=0;
  SysLinearTimer=0;
  while(SysLinearTimer<TIMER_FREQ*8)
  	{
        if(rx_flag==rx_succeed)
   	 	{
   	 	    command=rxlm3stg_Hander();
           
			if(command==((EResult_TXmain<<8)|EResult_vL))
				{
				  V_display(modify_line+option*modify_high, modify_column+0x10, resultRX.mune.vL);
				 //  DPRINTF(("u=%f \n",resultRX.mune.vL));
				}

       	}
  	}
  
   Sendtgc(Estop_main,debug_flag,EFre_500);
   PWM_sign_stop();
   PIN_TDA7367stand_Write(ETDA7367work_no);
 
}







void  modifyset_k( unsigned char option)
{
     unsigned char i;	
   uint8  byte[8];
   union 
 	    { 
 	        uint8 byte[4];
            uint32 t32;
 	    }k;
   k.t32=modify_k.H_k[option];
   bcd8_display(byte,option*modify_high+modify_line,0x08+modify_column,k.t32);
   for (i=0;i<6;i++ )
            {
      	      byte[i]=byte[i]-0x10;
	        } 
   modify_set8(byte, modifydata_nubkey,option*modify_high+modify_line,0x08+modify_column);

	  for (i=0;i<4;i++ )
            {
      	      k.byte[i]=(byte[0+i*2]<<4)+(byte[1+i*2]&0x0f);
	        } 
 
 
  modify_k.H_k[option]= k.t32	  ;
 

}

uint8   modify_read(void)
  {
    readbyte_much(modify_sto, modifytype_nub, modify_k.b_k);
	
    if((modify_k.H_k[EPIDarea_modify]==0x00))
    	{
    	   uint8 option;
           for(option=0;option<=modify_nubkey;option++) 
	         {
                modify_k.f_k[option].word_U32= modifydata_init[option];
				modify_k.f_k[option]=modifybigtosmall(modify_k.f_k[option])	 ;
		   	 }
		 
    	}
  
    return(0);
   	 
    
 }
	   
uint8   TgC_read(void)	
  {
   while(1)
   	   	{
   	   	  uint32 timelim;
          Sendtgc(Emodifyin_main,debug_flag, 00);
		  timelim=SysLinearTimer+TIMER_FREQ/2;
          while(SysLinearTimer<timelim) 
		  { 
		    if(rx_flag==rx_succeed)
   	 	     {
   	 	       if((EModify_TXmain<<8)==rxlm3stg_Hander())
   	 	    	{

   	 	    	 return(0);
   	 	    	}
		    }
          } 
   	    }
    }

