#include "file_ah9837.h"


//view_mune 
//   unsigned char code char_clock[ ]={14,'-',' ',' ','-',' ',' ',' ',' ',' ',' ',':',' ',' ',':',' ',' ',':'};  
 

  //=============================================
/*#define startmune_screen screen_0
#define clock_line       (14*16)
#define clock_column     (40-18)
#define clock_screen screen_0
#define clockset_nubkey  12*/

void Clock_viewxs(uint8 *byte)
   { 
        	 
	 uint8 option,address;
     address=11;
     for(option=0x00;option<7;option++)
       	{
        	 
			  if(option!=0x03)
        	  	{
        	  	 byte[address]=time.byte[option]&0x0f;
				 address--;
				 byte[address]=time.byte[option]>>4;
				 address--;
        	  	}
        }
     for(option=0x00;option<12;option++)
      	{
      	  address=(option/2*3+option%2+option/6+clockset_column);
          ShowPicture(clockset_line,address, Font1608,byte[option]+0x10);
    	}
   }

//==============================================

void Clockread_xs( )
   { 

     
	   uint8 byte[8];
	   read_time();

	 
   	   byte[0]=0x10+(time.time.month>>4);
	   byte[1]=0x10+(time.time.month&0x0f);
       byte[2]=':'-0x20;
	   byte[3]=0x10+(time.time.day>>4);
	   byte[4]=0x10+(time.time.day&0x0f);
	    charLine(Clockwarn_lin,Clockwarn_column,5,byte); 
	
      // uint8 byte[8];
	   byte[0]=0x10+(time.time.hour>>4);
	   byte[1]=0x10+(time.time.hour&0x0f);
       byte[2]=':'-0x20;
	   byte[3]=0x10+(time.time.minute>>4);
	   byte[4]=0x10+(time.time.minute&0x0f);
	   byte[5]=':'-0x20;
	   byte[6]=0x10+(time.time.second>>4);
	   byte[7]=0x10+(time.time.second&0x0f);
	   charLine(Clockwarn_lin,Clockwarn_column+8,8,byte); 
	
   }




void start_mune()
 {
   InitLCD();

  ShowtextLine(0x18,0x4,text_phkj);	
  
  
 }

void Vacdisplay()
 {
   if(set.mune.Vac==E00Vac)
   	{
   	  ShowtextLine(oilset_lin+ETg_oil*oilset_high, oilset_column+10,text_guan)	;
   	}
   

   else if(set.mune.Vac<E1000Vac)
   	{
   	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+10,  Font1608, set.mune.Vac+0x10);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+11,  Font1608, 0+0x10);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+12,  Font1608, 0+0x10);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+13,  Font1608, ' '-0x20);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+14,  Font1608, 'V'-0x20);
   	}
   else
   	{
   	 uint8 Vac= set.mune.Vac-E1000Vac;
   	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+10,  Font1608, Vac/10+0x11);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+11,  Font1608, '.'-0x20);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+12,  Font1608, Vac%10+0x10);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+13,  Font1608, 'k'-0x20);
	 ShowPicture(oilset_lin+ETg_oil*oilset_high, oilset_column+14,  Font1608, 'V'-0x20);
   	}
    
 }

void Vdcdisplay()
 {
    if(set.mune.Vdc!=E00Vdc)
   	 {
   	  ShowPicture(oilset_lin+ER_oil*oilset_high, oilset_column+10,  Font1608, set.mune.Vdc+0x10);
	  ShowPicture(oilset_lin+ER_oil*oilset_high, oilset_column+11,  Font1608, 0+0x10);
	  ShowPicture(oilset_lin+ER_oil*oilset_high, oilset_column+12,  Font1608, 0+0x10);
	  ShowPicture(oilset_lin+ER_oil*oilset_high, oilset_column+13,  Font1608, ' '-0x20);
      ShowPicture(oilset_lin+ER_oil*oilset_high, oilset_column+14,  Font1608, 'V'-0x20);
     }
	else
		{
		 ShowtextLine(oilset_lin+ER_oil*oilset_high, oilset_column+10,text_guan)	;
		}
	
 }
 void oiltempdisplay()
 {
     uint32 oiltemp=set.mune.Temp*5;
	 if(oiltemp!=E00T*5)
      {
       uint32 xsdata;
	   xsdata= oiltemp/100;
	   oiltemp%=100;
	   ShowPicture(oilset_lin+EHot_oil*oilset_high, oilset_column+10,  Font1608, xsdata+0x10);
       xsdata= oiltemp/10;
	   oiltemp%=10;

	   ShowPicture(oilset_lin+EHot_oil*oilset_high, oilset_column+11,  Font1608, xsdata+0x10);
	   ShowPicture(oilset_lin+EHot_oil*oilset_high, oilset_column+12,  Font1608, oiltemp+0x10);
	   ShowPicture(oilset_lin+EHot_oil*oilset_high, oilset_column+13,  Font1608, ' '-0x20);
       ShowPicture(oilset_lin+EHot_oil*oilset_high, oilset_column+14,  Font1608, 0x80-0x20);
	 }
	else
	 {
	   ShowtextLine(oilset_lin+EHot_oil*oilset_high, oilset_column+10,text_guan)	;
	 }
   
 }

void  Fredisplay()
 {
   charLineASCII(oilset_lin+EFre_oil*oilset_high, oilset_column+10,Fre_p[set.mune.Fre])	  ;
 }

 




void  workdisplay()
 {
   ShowtextLine(oilset_lin+EWork_oil*oilset_high, oilset_column+10,workset_p[set.mune.work])	;
 }


//=============
void mainset_mune()
{
  uint32 i;
    InitLCD();
  for(i=EOilset_main;i<=ELan_main;i++)
  	{
  	   ShowtextLine(mainset_lin+i*mainset_high,mainset_column,mainset_p[i]);	
  	}

  //workdisplay();
 ShowtextLine(mainset_lin+ELan_main*mainset_high, mainset_column+0x10,Lanset_p[set.mune.Langue]);	
 charLineASCII(clockset_line, clockset_column+2,char_clock)	  ; 
  
}


//================
/*设置时候显示的*/
void oidset_mune()
 {
  uint32 i;
  InitLCD();
  for(i=ETg_oil;i<=ECair_oil;i++)
  	{
  	  ShowtextLine(oilset_lin+i*oilset_high,oilset_column,(const uint8 *)oilset_p[i]);	
  	}
 
  Vacdisplay();
  Vdcdisplay();
  oiltempdisplay();
  Fredisplay();
  workdisplay();

  Cx_display(oilset_lin+ECair_oil*oilset_high,oilset_column+10,Resulttest.result[ECn_result].word_F);
}	






void testHOT_mune()
 {
  
 
  
  ShowtextLine(Workwarn_lin,Workwarn_column,workdisplay_p[set.mune.work]);	
  ShowtextLine(HOTwarn_lin,HOTwarn_column,text_zzjr);	
  ShowtextLine(Tempoilwarn_lin ,Tempoilwarn_column,text_youwen);	
  charLineASCII(Tempoilwarn_lin ,Tempoilwarn_column+6,char_T)	  ;

}	










