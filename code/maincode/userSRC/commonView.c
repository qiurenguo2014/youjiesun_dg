 #include "file_ah9837.h"

void Sendstc_Relay_tap(RElaygainflagtype  *RElaygainflag)
{
   uint32 i;
   uint8 sum;
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3Sview_pcb;
   tx_data.mune.slavepcb=ELM3Stgr_pcb;
   tx_data.mune.nub=5;
   sum= tx_data.mune.maincommand=ERelay_tap;
   
  for(i=0x00;i<4;i++)
	{
	  tx_data.mune.bill[i]=RElaygainflag->byte[i];
	  sum+=tx_data.mune.bill[i];
	}
   tx_data.mune.bill[4]=sum;
  for(i=0x00 ;i< tx_data.mune.nub+5+1;i++ )
	
		{
			  UARTCharPut(UART1_BASE , tx_data.byte[i]);
		}
   
}


void Sendstc_station(uint8 station)
{
   uint32 i;
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3Sview_pcb;
   tx_data.mune.slavepcb=ELM3Stgr_pcb;
   tx_data.mune.nub=3;
   tx_data.mune.maincommand=EStation_TXmain;
   tx_data.mune.subcommand=station;
   tx_data.mune.nop=0x00;
   
   tx_data.mune.bill[0]=EStation_TXmain+station;
    for(i=0x00 ;i<= tx_data.mune.nub+5;i++ )
	
		{
			 UARTCharPut(UART1_BASE , tx_data.byte[i]);
			// UARTCharPut(UART0_BASE , tx_data.byte[i]); 
		}
   
}
 void Sendstc_ask()
             {
                 uint32 i;
				 tx_data.mune.order0=com_command0;
                 tx_data.mune.order1=com_command1;
                 tx_data.mune.mainpcb=ELM3Sview_pcb;
                 tx_data.mune.slavepcb=ELM3Stgr_pcb;
                 tx_data.mune.nub=2;
                 tx_data.mune.maincommand=Ecommand_TXmain;
                 tx_data.mune.subcommand=rx_data.mune.workcommand;
                 tx_data.mune.nop= tx_data.mune.maincommand+tx_data.mune.subcommand;
                 for(i=0x00 ;i< tx_data.mune.nub+5+1;i++ )
	     		     {
		      	         UARTCharPut(UART1_BASE , tx_data.byte[i]);
					 }
            }
         


void Sendstc_result(uint8 command)
 {
   uint8 sum;
   uint32 i;
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3Sview_pcb;
   tx_data.mune.slavepcb=ELM3Stgr_pcb;
   tx_data.mune.maincommand=EResult_TXmain;
   tx_data.mune.subcommand=	command;
   tx_data.mune.nop=0x00;
   tx_data.mune.nub=3;
   sum=EResult_TXmain+command;
   
   switch(command)
   	{
      case EResult_Ann:
                 for(i=0x00;i<4;i++)
						{
						  tx_data.mune.bill[i]=Resulttest.result[EAnn_result].word_U8[i];
						  tx_data.mune.bill[i+4]=Resulttest.result[EKnn_result].word_U8[i];
						  sum+=tx_data.mune.bill[i];
						  sum+=tx_data.mune.bill[i+4];
						}
				   tx_data.mune.nub+=8;
				   tx_data.mune.bill[8]=sum;
				   break;
	  case EResult_R:
                 for(i=0x00;i<4;i++)
						{
						  tx_data.mune.bill[i]=Resulttest.result[ERx_result].word_U8[i];
						//  tx_data.mune.bill[i+4]=Resulttest.result[EE_result].word_U8[i];
						  sum+=tx_data.mune.bill[i];
						//  sum+=tx_data.mune.bill[i+4];
						}
				   tx_data.mune.nub+=4;
				   tx_data.mune.bill[4]=sum;
				   break;
	  	
	  case EResult_vL:
                {
		          for(i=0x00;i<4;i++)
						{
						  tx_data.mune.bill[i]=Resulttest.result[EU_result].word_U8[i];
						  sum+=tx_data.mune.bill[i];
						}
				   tx_data.mune.nub+=4;
				   tx_data.mune.bill[4]=sum;
				   break;
	  	        }  

	  case EResult_tg:
                
		           for(i=0x00;i<4;i++)
						{
						  tx_data.mune.bill[i]=Resulttest.result[ETg_result].word_U8[i];
						  tx_data.mune.bill[i+4]=Resulttest.result[ECx_result].word_U8[i];
						  sum+=tx_data.mune.bill[i];
						  sum+=tx_data.mune.bill[i+4];
						}
					 tx_data.mune.nub+=8;
					 tx_data.mune.bill[8]=sum;
	             //    i=15;   
	  	             break;
	  	        	 
   	
   	}
     for(i=0x00 ;i<=tx_data.mune.nub+5;i++ )
	
		{
			  UARTCharPut(UART1_BASE , tx_data.byte[i]);
			//  UARTCharPut(UART0_BASE , tx_data.byte[i]); 
		}
}






