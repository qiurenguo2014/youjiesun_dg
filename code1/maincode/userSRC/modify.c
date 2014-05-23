#include "file_ah9837.h"













wordtype modifybigtosmall(wordtype datIn)
{
   wordtype datOut;
   datOut.word_U8[0]=datIn.word_U8[3];
   datOut.word_U8[1]=datIn.word_U8[2];
   datOut.word_U8[2]=datIn.word_U8[1];
   datOut.word_U8[3]=datIn.word_U8[0];
  return(datOut);
}







void modifyfloat(void)
 {
   
  
//   modify_k.f_k[option].word_F=float_js( modify_k.f_k[page][option].word_U32);
  
 }
	


/*
#define  _modifysto_page  (1024*2)
#define   _modifysto_nub  (4*15)

void modify_save(void)
{
  
   SysCtlDelay(SysCtlClockGet()/10);
   modify_k=rx_data.mune.modify_k;
   modify_k.H_k[5*4-1]=0x44424821;

   FlashErase(_modifysto_page);
   FlashProgram(modify_k.H_k, _modifysto_page, _modifysto_nub*4);  

}
*/

void modifyK_js(void)
{
  float To,Tk;
   wordtype T100_lm331,T120_lm331;
   
   uint8 option;
   for(option=EVdcK_modify;option<=EVacK_modify;option++)
      {
       modify_k.f_k[option]=modifybigtosmall(modify_k.f_k[option]);
       modify_k.f_k[option].word_F=float_js( modify_k.f_k[option].word_U32)/100.00;   //5000.00v
   	  }

   for(option=EPIDarea_modify;option<=EPIDY1_modify;option++)
   	{
   	  modify_k.f_k[option]=modifybigtosmall(modify_k.f_k[option]);
	  modify_k.H_k[option]=(uint32)float_js(modify_k.f_k[option].word_U32);
	//  DPRINTF(("k=%d  \n",modify_k.H_k[option]));
   	}
    //DPRINTF(("k=%d  \n",modify_k.H_k[EPIDY1_modify]));
    modify_k.H_k[EPIDY1_modify]*=(uint32)1000000;
	//DPRINTF(("k2=%d  \n",modify_k.H_k[EPIDY1_modify]));

  for(option=ET100_modify;option<=ET120_modify;option++)
   	{
   	  modify_k.f_k[option]=modifybigtosmall(modify_k.f_k[option]);
	  modify_k.f_k[option].word_F=float_js(modify_k.f_k[option].word_U32);
	  //  DPRINTF(("k=%d  \n",modify_k.H_k[option]));
   	}
   readbyte_much(Temp_Zio_addr, 4, T100_lm331.word_U8);
   readbyte_much(Temp_K_addr,   4, T120_lm331.word_U8);   
   /*120欧的频率-100欧*/
   Tk=((float)T120_lm331.word_U32-(float)T100_lm331.word_U32)/( modify_k.f_k[ET120_modify].word_F- modify_k.f_k[ET100_modify].word_F);
   To=	(float)T120_lm331.word_U32-Tk*modify_k.f_k[ET120_modify].word_F;
	T331.T0_331=(uint32)To;
	T331.Tk_331=Tk;
    // DPRINTF(("T0=%u, Tk=%f  \n",T331.T0_331,T331.Tk_331));
    readbyte_much(Cn_addr, 4, Resulttest.result[ECn_result].word_U8);
}

/*

void modify_TOstc(void)
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
   tx_data.mune.mainpcb=ESTC_pcb;
   tx_data.mune.slavepcb=ELM3S_pcb;
   
   tx_data.mune.nub=_modifysto_nub*4+1;
   
   sum=tx_data.mune.maincommand=EResule_modify;
   
   for(i=0x00 ;i<6;i++ )
	
		{
			 UARTCharPut(UART0_BASE, tx_data.byte[i]);
			
		}	

   
   for(i=0x00 ;i<_modifysto_nub*4 ;i++ )
	
		{
			 UARTCharPut(UART0_BASE ,  modify_k.b_k[i]);
			 sum+= modify_k.b_k[i];
		}	

   UARTCharPut(UART0_BASE , sum);
   
  
}
*/





