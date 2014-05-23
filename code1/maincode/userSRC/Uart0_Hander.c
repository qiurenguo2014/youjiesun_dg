#include "file_ah9837.h"


uint32 Sendtgc(uint8 work,uint8 debug,uint8 fre)
{
   uint32 i;
   uint8 sum;
   uint8 j;
   
   tx_data.mune.order0=com_command0;
   tx_data.mune.order1=com_command1;
   tx_data.mune.mainpcb=ELM3Sview_pcb;
   tx_data.mune.slavepcb=ELM3Stgr_pcb;
   tx_data.mune.nub=3;
   
   tx_data.mune.workcommand=work|(debug<<4);
   tx_data.mune.Fre=fre;
   tx_data.mune.Voltage=(fre==EFre_000)? set.mune.Vdc: set.mune.Vac; 
   sum=tx_data.mune.workcommand+ tx_data.mune.Fre+ tx_data.mune.Voltage;
   if(work==Emodifyout_main)
   	{

     tx_data.mune.modify_k=modify_k; 
   	 for(i=0;i<4*4*3;i++)
   	 	{
   	 	
		 sum+=modify_k.b_k[i];
   	 	}
	 tx_data.mune.nub+=4*4*3;
   	}


  for(j=0;j<10;j++)
    {
      for(i=0x00 ;i< tx_data.mune.nub+5;i++ )
	    {
		  UARTCharPut(UART2_BASE , tx_data.byte[i]);
		  
		}
	  UARTCharPut(UART2_BASE , sum);
	  
	  rx_flag=0x00;
      if(Asktgc_Wait(tx_data.mune.workcommand)==TRUE_z)
      	{
       	  return(TRUE_z);
       	}
	  
    }  
    ShowtextLine(Workwarn_lin , Workwarn_column,text_xhxtgz)	;
	StopSave_hander();  
//	while(1); 
  return(FALSE_z);
}




uint32  Asktgc_Wait(uint8 workcommand)
 {
  
    uint32 timelim;
	timelim=SysLinearTimer+TIMER_FREQ/2;
    while(SysLinearTimer<timelim)
	  	{
	  	   if(rx_flag==rx_succeed)
	  	    	{ 
	  	    	  rx_flag=0x00;
               	  if(workcommand==rx_data.mune.subcommand)
	  	    	  	{
				     return(TRUE_z);
	  	    	  	}
	  	       	}
		} 
     return(FALSE_z);
 }




uint16  rxlm3stg_Hander(void)
 {
   uint16 command;
   uint16 i;
   command=rx_data.mune.subcommand +(rx_data.mune.maincommand<<8)  ;
   rx_flag=0;
   if((command>>8)==EStation_TXmain) 
   	{
      if((command>>8)>ETest_off)
       	{
       	  ShowtextLine(SIGNwarn_lin, SIGNwarn_column,TgcStation_p[(command>>8)-1])	; 
       	  PWM_sign_acc(0.00,0.0);
		 // DPRINTF(("wr \n"));
		  while(1);
       	}
	   
	  
    }
   else if(rx_data.mune.maincommand==EResult_TXmain)
   	{
   	  
       union   
	     {
	      uint8 byte[8];
		  struct
	        {
	         float dat1;
	         float dat2;
		  	}mune; 
       	 }float2;
        for(i=0;i<8;i++)
        	{
        	 float2.byte[i]= rx_data.mune.bill[i];
        	}
	   rx_flag=0;
       switch(rx_data.mune.subcommand) 
       	{
       	 case EResult_Ann:
		 	resultRX.mune.Ann=float2.mune.dat1;
			resultRX.mune.Knn=float2.mune.dat2;
			break;
		 case EResult_tg:
		 	resultRX.mune.tgA=float2.mune.dat1;
			resultRX.mune.cx=float2.mune.dat2;
			break;	
		
		case EResult_vL:
		 	resultRX.mune.vL=float2.mune.dat1;
			break;			
         case EResult_R:
		 	resultRX.mune.R_p=float2.mune.dat1;
			break;
			
       	}
	
   	}
   else if(rx_data.mune.maincommand==EModify_TXmain)
   	{ 
      
	    for(i=0;i<4*12;i++)
        	{
        	 modify_k.b_k[i]= rx_data.mune.bill[i];
        	}
   	}
  
 return(command) ;
}





/*

void Sendsin_VOL(uint8 Fre,uint8 vlotage)
{
   uint32 i;
   uint8 sum;
  uint8 work=0;
   
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
*/



void pc_com(void)
{

   uint8 i;
	uint16 j;
	uint16 address;
	uint8 sum=0;
    UARTCharPut(UART0_BASE ,com_command0);
    UARTCharPut(UART0_BASE ,com_command1);

    UARTCharPut(UART0_BASE ,ELM3Sview_pcb);

    UARTCharPut(UART0_BASE ,EPC_pcb);

	UARTCharPut(UART0_BASE ,(pageLong*viewpage_nub)>>8);
	UARTCharPut(UART0_BASE ,(pageLong*viewpage_nub)&0xff);
	


	
   	{
         uint8  byte[pageLong ];
         for(i=0x00;i<viewpage_nub;i++)
         {
           address=VIEWsto_addr+pageLong*i ;
		   readbyte_much( address,pageLong ,byte);
		   for(j=0x00;j<pageLong ;j++)
		   	{
		     UARTCharPut(UART0_BASE ,byte[j]);
			 sum+=byte[j];
		   	}
         }
    	}
	
  UARTCharPut(UART0_BASE ,sum);

}


