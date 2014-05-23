// sbit pri_busy =P3^0;


#include "file_ah9837.h"


//打印区
const  unsigned char  pri_command[ ]={0x01c,0x02e,0x01b,0x40,0x01b,0x57,0x01,0x01b,0x63,0x00,0x01c,0x026,0x01c,0x057,0x01,0x0ff};
// unsigned char code pri_screen_command[ ]={0x01c,0x02e,0x01b,0x63,0x00,0x01b,0x6d,0x06,0x0ff};
const unsigned char  pri_screen_command[ ]={0x01c,0x02e,0x01B,0x040,0x01b,0x031,0x000,0x01b,0x055,0x03,0x01b,0x056,0x02,0x01b,0x63,0x00,0x01b,0x6d,0x06,0x0ff};

const unsigned char pri_compant[ ]="   福建省普华电子科技有限公司" ;//"       福州凯特电气有限公司 " ;//
const unsigned char  pri_yiqi[ ]  ="  AH9858选频电压表" ;//便携式
 
 

const unsigned char pri_tg[ ]="tg=";
const unsigned char  pri_Cx[ ]= "Cx=";
const unsigned char pri_E[ ]=" ε=";
const unsigned char pri_Rx[ ]=" Rx=";
const unsigned char pri_P[ ]="ρ="; 
 
 
const unsigned char pri_Vdc[ ]="Vdc=";
const unsigned char  pri_Vac[ ]="Vac=";

const unsigned char  pri_Temp[ ]="  T=";
 
const unsigned char  pri_kV[ ]="kV";
const unsigned char pri_V[ ]="V";
 
 
const unsigned char pri_A[ ]="A";
const unsigned char pri_mA[ ]="mA";
const unsigned char  pri_uA[ ]="uA";
 
 
const unsigned char  pri_nF[ ]="nF";
const unsigned char  pri_pF[ ]="pF";
 
 
const unsigned char  pri_du[ ]="℃";
 


const unsigned char  pri_csry[ ]="试验人员:  "  ;
const unsigned char  pri_cssb[ ]="试品编号:  "  ;

const unsigned char  pri_kkkk[]="       ";


/*--------------------------*/
void print_one(unsigned char i)
 {    ;
 // while (pri_busy&0x01);
   //communication_one_tx(i);
    UARTCharPut(UART1_BASE , i);
 }
/*-------------------------------------*/

void printchar_link(const unsigned char *address)
 {
  while(*address!=0x0ff)
  print_one(*address++);
  }
 
/*------------------------------------*/
 
void printhz_link( const  unsigned char *address)
 {
  while(*address!='\0')
  print_one(*address++);
 }

//===========
 void print_BCD(uint8 bcd)																		
 	{
 	  print_one(0x30+(bcd>>4));
      print_one(0x30+(bcd&0x0f));
	  
 	}



void printchar_str( char *address,uint8 nub)
{
 uint8 i;
 for(i=0;i<nub;i++)
 	{
 	 print_one(address[i]+0x20);
 	}
}







 




 

/*----------------------------------------*/
void print()
  {
  
    char   sprintfbyte[8];
    delay(0x100000);
  
   printchar_link(pri_command) ;
   
   printhz_link(pri_compant);	
   
   print_one(0x0d);
  
 
  
//  printchar_link(pri_screen_command) ;
//  print_screen(0x00,0x00,127,30)    ;
//  print_screen(0x80,0x00,127,30)    ;

  if( set.mune.Vac !=E00Vac)
   	{
   	    printhz_link(pri_tg);
		float_xs(Resulttest.result[ETg_result].word_F,sprintfbyte,1);
		printchar_str(sprintfbyte,5);
		print_one('%');
        print_one(0x0d);
		
	    printhz_link(pri_Cx);
		float_xs(Resulttest.result[ECx_result].word_F,sprintfbyte,1);
		printchar_str(sprintfbyte,5);
		 printhz_link(pri_pF);
        print_one(0x0d);
	  
	    printhz_link(pri_E);
		float_xs(Resulttest.result[ECx_result].word_F/Resulttest.result[ECn_result].word_F,sprintfbyte,1);
		printchar_str(sprintfbyte,5);
        print_one(0x0d);
      
	   if(set.mune.Vdc!=E00Vdc)
	   	{
	    printhz_link(pri_P);
		float_xs(Resulttest.result[ERx_result].word_F*6.78,sprintfbyte,1);
		printchar_str(sprintfbyte,5);
		 print_one(0x0d);
	   	}  
   	}
   else if( (set.mune.Vac ==E00Vac)&&(set.mune.Vdc !=E00Vdc))
   	{
  	    printhz_link(pri_P);
		float_xs(Resulttest.result[ERx_result].word_F*6.78,sprintfbyte,1);
		printchar_str(sprintfbyte,5);
        print_one(0x0d);
		printhz_link(pri_Rx);
		float_xs(Resulttest.result[ERx_result].word_F,sprintfbyte,1);
		printchar_str(sprintfbyte,5);
		print_one(0x0d);
   	}
  
  printhz_link(pri_csry);	
  print_one(0x0d);

  printhz_link(pri_cssb);	
  print_one(0x0d);
 

   print_BCD(time.time.year);
   print_one('-');
 
   print_BCD( time.time.month);
   print_one('-');
  
   print_BCD(time.time.day);
   print_one(' ');
   print_one(' ');
  
   print_BCD(time.time.hour);
   print_one(':');
  
   print_BCD(time.time.minute); 
  
	
   print_one(0x0d);
   print_one(0x20);
   print_one(0x0d);
   print_one(0x20);
   print_one(0x0d);
   print_one(0x20);
   print_one(0x0d);
   
 
}
/*----------------------------------------*/



