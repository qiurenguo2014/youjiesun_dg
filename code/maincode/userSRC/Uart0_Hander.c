#include "file_ah9837.h"

  #if 0
void Sendstc_HOT(uint8 work ,sint16 Tempsendcom)
{
   uint32 i;
   uint8 sum;
 
   
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3S_pcb;
   tx_data.mune.slavepcb=ESTChot_pcb;
   tx_data.mune.nub=3;
   sum= tx_data.mune.maincommand=work;
   tx_data.mune.bill[0]=Tempsendcom/0x100;
   tx_data.mune.bill[1]=Tempsendcom%0x100;
  
 
   tx_data.mune.bill[3]=sum+tx_data.mune.bill[0]+tx_data.mune.bill[1];
  
   
   
  for(i=0x00 ;i< tx_data.mune.nub+5+1;i++ )
	
		{
			  UARTCharPut(UART0_BASE , tx_data.byte[i]);
		}


}


void Sendsin_VOL(uint8 work,uint8 Fre,uint8 vlotage)
{
   uint32 i;
   uint8 sum;
 
   
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3S_pcb;
   tx_data.mune.slavepcb=ESTCsin_pcb;
   tx_data.mune.nub=3;

   sum= tx_data.mune.maincommand=work;
   tx_data.mune.bill[0]= Fre;
   tx_data.mune.bill[1]= vlotage;
  
 
   tx_data.mune.bill[3]=sum+tx_data.mune.bill[0]+tx_data.mune.bill[1];
  
   
   
   for(i=0x00 ;i< tx_data.mune.nub+5+1;i++ )
	 	{
			  UARTCharPut(UART0_BASE , tx_data.byte[i]);
		}


}

 #endif

