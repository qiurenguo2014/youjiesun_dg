#include "file_ah9837.h"

void modifybigtosmall(void)
{
 
   uint8 temp8;
   uint32 page;
 
  
   for(page=ECN3_modify;page<=EUk_modify;page++)
  	 {
  	  
  	  
  	 	  temp8= modify_k.f_k[page].word_U8[0];
          modify_k.f_k[page].word_U8[0]=modify_k.f_k[page].word_U8[3];
          modify_k.f_k[page].word_U8[3]=temp8;
		  temp8= modify_k.f_k[page].word_U8[1];
          modify_k.f_k[page].word_U8[1]=modify_k.f_k[page].word_U8[2];
          modify_k.f_k[page].word_U8[2]=temp8;
    
	  }
}







void modifyfloat(void)
 {
  
   uint32 option;
   for(option=ECN3_modify;option<=EUk_modify;option++)
  	 	{
  	 	  modify_k.f_k[option].word_F=float_js( modify_k.f_k[option].word_U32)/100000.0;
      	}
  	 
 }
	
void modifyCx_Tg(void)
 {
    modify_k.f_k[ECN3_modify].word_F= modify_k.f_k[ ECN3_modify].word_F*3.16227;
    modify_k.f_k[ECN10_modify].word_F= modify_k.f_k[ECN10_modify].word_F*10.0;
	modify_k.f_k[ECX3_modify].word_F= modify_k.f_k[ ECX3_modify].word_F*3.16227;
    modify_k.f_k[ECX10_modify].word_F= modify_k.f_k[ECX10_modify].word_F*10.0;
	
 }

void modifyR(void)
{
    modify_k.f_k[ERk500_modify].word_F= modify_k.f_k[ ERk500_modify].word_F*500.0;
    modify_k.f_k[ERk1M_modify].word_F= modify_k.f_k[ERk1M_modify].word_F*1000000.0;
	modify_k.f_k[ERzio_modify].word_F= modify_k.f_k[ ERzio_modify].word_F*1.0;
    modify_k.f_k[EUk_modify].word_F= modify_k.f_k[EUk_modify].word_F*1100;
 
}






#define  _modifysto_page     (1024*2)
#define  _AD7705ziosto_page  (1024*3)
#define   _modifysto_nub  20

void modify_save(void)
{
  
   SysCtlDelay(SysCtlClockGet()/10);
   modify_k=rx_data.mune.modify_k;
   modify_k.H_k[_modifysto_nub-1]=0x44424821;
   FlashErase(_modifysto_page);
   FlashProgram(modify_k.H_k, _modifysto_page, _modifysto_nub*4);  

}




void modifyK_js(void)
{

  uint32 i;

  for(i=0; i<4*5; i++)
    {
      modify_k.H_k[i] = HWREG(_modifysto_page + i*4) ;// 读取Flash 的数据
    }
 
  if( modify_k.H_k[_modifysto_nub-1]!=0x44424821)
  	{
  	  for(i=0; i<4*_modifysto_nub; i++)
      {
        modify_k.H_k[i] = 0x00000001 ;// 读取Flash 的数据
      }
	}
 

   modifybigtosmall();

   modifyfloat();
 
   modifyCx_Tg();
   modifyR();
   /*
   for(i=0; i<3; i++)
    {
      modify_k.H_k[E7705I500zio_modify+i] = HWREG(_AD7705ziosto_page+ i*4) ;// 读取Flash 的数据
    }

   for(i=0;i<16;i++)
   	{
   	 modify_k.f_k[i].word_F=modifydata_lib[i];
   	}
   */
   /*
   for(i=0;i<16;i++)
   	{
   	  DPRINTF(("i=%f \n",i,modify_k.f_k[i].word_F));
   	}
   */

}



void modify_ToView(void)
{
  uint8 sum;
  uint32 i;
  SysCtlDelay(SysCtlClockGet()/10);
  for(i=0; i<4*5; i++)
    {
      modify_k.H_k[i] = HWREG(_modifysto_page + i*4) ;// 读取Flash 的数据
    }

 //  modify_k.H_k[4*15-1]=0x00;
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3Sview_pcb;
   tx_data.mune.slavepcb=ELM3Stgr_pcb;
   
   tx_data.mune.nub=3+ modify_nub;
  sum=tx_data.mune.maincommand= EModify_TXmain;
   tx_data.mune.subcommand=	0x0;
   tx_data.mune.nop=0x00;
 
 
   
   for(i=0x00 ;i<8;i++ )
	
		{
		 UARTCharPut(UART1_BASE, tx_data.byte[i]);
		}	

   
   for(i=0x00 ;i<_modifysto_nub*4 ;i++ )
	
		{
			 UARTCharPut(UART1_BASE ,  modify_k.b_k[i]);
			 sum+= modify_k.b_k[i];
		}	

   UARTCharPut(UART1_BASE , sum);
   
  
}




