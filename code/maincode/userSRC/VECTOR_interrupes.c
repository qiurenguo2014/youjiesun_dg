
#include "file_ah9837.h"








#define Oilread_time  200

void SysTickHandler(void)	//every 1ms
{
    static uint32	TickPhase=0;
	static uint32	OiltempPhase=0;
	TickPhase++;
	OiltempPhase++;
	switch(TickPhase)	             //10MS为一个周期
		{
	
		}

    SysLinearTimer ++;


}

void UART1IntHandler(void)
{
 
    static  uint16  rx_sum;
    static  uint16  nub;
	unsigned long ulStatus;
    boolean flag=true;
	//
	// Get the interrrupt status.
	//

	ulStatus = UARTIntStatus(UART1_BASE, true);  //UARTMIS

	//
	// Clear the asserted interrupts.
	//
	UARTIntClear(UART1_BASE, ulStatus);

	//
	// Loop while there are characters in the receive FIFO.
	//
	while(flag)
	  {
	    flag=UARTCharsAvail(UART1_BASE);
	    if(flag==true)
		{
		//
		// Read the next character from the UART and write it back to the UART.
		//
		  uint8 rx_temp; 
          rx_temp=(uint8) UARTCharGet(UART1_BASE)	 ;
		
		   if(rx_flag!=rx_succeed )
      	   {
		     if(rx_flag==0x00)
	           {
		          if( rx_temp!=com_command0)
		            {
		               nub=00;
		 	           rx_flag=0x0ffff;
                    }
		       } 
            else if(rx_flag==0x01)
	          {
		        if(rx_temp!=com_command1)
		 	     {
                    nub=00;
			        rx_flag=0x0ffff;
                 }
		      } 

            else if(rx_flag==0x02)
	           {
		        if(rx_temp!=ELM3Sview_pcb)
		 	      {
                    nub=00;
			        rx_flag=0x0ffff;
                  }
		      } 
            else if(rx_flag==0x03)
	              {
		           if(rx_temp!=ELM3Stgr_pcb)
		 	          {
                       nub=00;
			           rx_flag=0x0ffff;
                      }
		           } 

		 
		     else if(rx_flag==0x04)
		 	      {
                    nub=(uint16)rx_temp+5;
					rx_sum=0x00;
		  	      }
           else if((rx_flag>=nub)&&(nub!=0x00))
         	 {
               				   
			   if((uint8)rx_sum==rx_temp)
         	    {
         	     
         	      rx_flag=rx_succeed-1;
               			
			    }
			  else
			  	{
			  	 rx_flag=0xffff;
			 	}
			   nub=0;
			   rx_sum=0;
         	 }
				
		     else
		   	    {
		 	     rx_data.byte[rx_flag-4]=rx_temp;
		 	     rx_sum+=rx_temp;
                }
	 	     rx_flag++;
          
	      }
	   }
    }



}



#if 0
void UART0IntHandler(void)
{
    static  uint16  rx_sum;
    static  uint16  nub;
	unsigned long ulStatus;
    boolean flag=true;
	//
	// Get the interrrupt status.
	//

	ulStatus = UARTIntStatus(UART0_BASE, true);  //UARTMIS

	//
	// Clear the asserted interrupts.
	//
	UARTIntClear(UART0_BASE, ulStatus);

	//
	// Loop while there are characters in the receive FIFO.
	//
	while(flag)
	  {
	    flag=UARTCharsAvail(UART0_BASE);
	    if(flag==true)
		{
		//
		// Read the next character from the UART and write it back to the UART.
		//
		  uint8 rx_temp; 
          rx_temp=(uint8) UARTCharGet(UART0_BASE)	 ;
		
		   if(rx_flag!=rx_succeed )
      	   {
		     if(rx_flag==0x00)
	           {
		          if( rx_temp!=com_command0)
		            {
		               nub=00;
		 	           rx_flag=0x0ff;
                    }
		       } 
            else if(rx_flag==0x01)
	          {
		        if(rx_temp!=com_command1)
		 	     {
                    nub=00;
			        rx_flag=0x0ff;
                 }
		      } 

            else if(rx_flag==0x02)
	           {
		        if(rx_temp!=EPC_pcb)
		 	      {
                    nub=00;
			        rx_flag=0x0ff;
                  }
		      } 
            else if(rx_flag==0x03)
	              {
		           if(rx_temp!=ELM3Sview_pcb)
		 	          {
                       nub=00;
			           rx_flag=0x0ff;
                      }
		           } 

		 
		     else if(rx_flag==0x04)
		 	      {
                    nub=(uint16)rx_temp+5;
					rx_sum=0x00;
		  	      }
           else if((rx_flag==nub)&&(nub!=0x00))
         	 {

			   if((uint8)rx_sum==rx_temp)
         	    {
         	      uint32 i;
         	      rx_flag=rx_succeed-1;
                  tx_data.mune.order0=com_command0;
                  tx_data.mune.order1=com_command1;
                  tx_data.mune.mainpcb=EPC_pcb;
                  tx_data.mune.slavepcb=ELM3Sview_pcb;
                  tx_data.mune.nub=2;
                  tx_data.mune.maincommand=Ecommand;
                  tx_data.mune.bill[0]=ETest_on;
                  tx_data.mune.bill[1]=Ecommand+ETest_on;
                  for(i=0x00 ;i< tx_data.mune.nub+5+1;i++ )
	
        		      {
		      	         UARTCharPutNonBlocking(UART0_BASE , tx_data.byte[i]);
	        	     }
			   }
			  else
			  	{
			  	 rx_flag=0xff;
				 nub=0;
				 rx_sum=0;
			  	}
         	 }
				
		     else
		   	    {
		 	     rx_data.byte[rx_flag-5]=rx_temp;
		 	     rx_sum+=rx_temp;
                }
	 	     rx_flag++;
          
	      }
	   }
    }

    /*
flag=true;
 while(flag)
 	{
	   	//
		//  write  the next character  to the UART.
		//

 	  flag= UARTSpaceAvail(UART0_BASE);
      if(flag==true)
        {
 	      if(tx_nub<(tx_data.mune.nub+5))  //if(TXwork_flag==ETXYESwork)
           {
             UARTCharPut(UART0_BASE, tx_data.byte[tx_nub]);
	         tx_nub++;
           } 
        }
 	}  
*/
}


#endif 
   
 
