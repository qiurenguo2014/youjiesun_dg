#include "file_ah9837.h"

//24c32  һ����32���ֽ�


#define I2c_delay 0x100


unsigned long I2CM_SendRecv(I2CWorkType *I2CWork)
{
// ���ݵ�ַ���Ȼ��շ����ݴ�С����Ϊ0������ִ���κβ���
   if ((I2CWork->gtDevice.uiLen <= 0) || (I2CWork->gtDevice.uiSize <= 0))
         {
          return(I2C_MASTER_ERR_NONE);
         }
   
    if (I2CWork->gtDevice.uiLen > 4)
		{
		 I2CWork->gtDevice.uiLen = 4; // ���ݵ�ַ���Ȳ��ܳ���4B
    	} 
       
        I2CWork->guiAddrIndex = 0;
        I2CWork->guiDataIndex = 0;
   switch (I2CWork->gtDevice.uiLen) // �����ݵ�ַ�ֽ������
        {
          case 1: // 1�ֽ����ݵ�ַ
               I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr);
               break;
          case 2: // 2�ֽ����ݵ�ַ
               I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr >> 8);
               I2CWork->gcAddr[1] = (char)(I2CWork->gtDevice.ulAddr);
               break;
          case 3: // 3�ֽ����ݵ�ַ
              I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr >> 16);
              I2CWork->gcAddr[1] = (char)(I2CWork->gtDevice.ulAddr >> 8);
              I2CWork->gcAddr[2] = (char)(I2CWork->gtDevice.ulAddr);
              break;
          case 4: // 4�ֽ����ݵ�ַ
              I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr >> 24);
              I2CWork->gcAddr[1] = (char)(I2CWork->gtDevice.ulAddr >> 16);
              I2CWork->gcAddr[2] = (char)(I2CWork->gtDevice.ulAddr >> 8);
              I2CWork->gcAddr[3] = (char)(I2CWork->gtDevice.ulAddr);
              break;
          default:
              break;
        }
    // ����Ƕ�����ͨ�ţ�����Ҫ���ȵȴ����߿���
   	/*{
    	  uint64 i=0;
		  while(i<I2c_delay)
		  	{
		  	 if(I2CMasterBusBusy(I2CWork->I2CM_BASE)==false)
		  	 	{
		  	 	 break;
		  	 	}
			 if(i==(I2c_delay-2))
			 	{
			 	 return(I2C_MASTER_ERR_NONE);
			 	}
			 i++;
		  	}
	
    	}*/

  /*
   {
    uint16 i=0;
    while(I2CMasterBusy(I2CWork.I2CM_BASE)==true) // �ȴ����߿���
    	{
    	 i++;
		 if(i>I2c_delay)
		 	{
		 	 break;
		 	}
    	}
  	}
  */	
	  while (I2CMasterBusBusy(I2CWork->I2CM_BASE)); // �ȴ����߿���

	 
	    I2CMasterSlaveAddrSet(I2CWork->I2CM_BASE, I2CWork->gtDevice.ucSLA, EI2C_send); // ���ôӻ���ַ��д����

		
	
        I2CMasterDataPut(I2CWork->I2CM_BASE, I2CWork->gcAddr[I2CWork->guiAddrIndex++]); // ��ʼ�������ݵ�ַ
        I2CWork->gucStatus = STAT_ADDR; // ����״̬���������ݵ�ַ
  
        while (I2CMasterBusBusy(I2CWork->I2CM_BASE)); // �ȴ����߿���
// �������ͻ��������ʼ
       I2CMasterControl(I2CWork->I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_START);
         
     //  while (I2CWork->gucStatus != STAT_IDLE); // �ȴ����߲������
         
       return(I2CMasterErr(I2CWork->I2CM_BASE)); // ���ؿ��ܵĴ���״̬
}












#if 0
// I2C�жϷ�����
void I2C_ISR(void)
{
    unsigned long ulStatus;
    ulStatus = I2CMasterIntStatus(I2CM_BASE, true); // ��ȡ�ж�״̬
    I2CMasterIntClear(I2CM_BASE); // ����ж�״̬
    if (I2CMasterErr(I2CM_BASE) != I2C_MASTER_ERR_NONE) // ����������
       {
         gucStatus = STAT_IDLE;
         return;
       }
    if (!ulStatus) return;
    switch (gucStatus)
       {
         case STAT_ADDR: // �������ݵ�ַ״̬
             if (guiAddrIndex < gtDevice.uiLen) // �����ݵ�ַδ�������
                {
                 // �����������ݵ�ַ
                 I2CMasterDataPut(I2CM_BASE, gcAddr[guiAddrIndex++]);

                 // �������ͻ�����ͼ���
                 I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
                 break;
                }
             else
                {
                   gucStatus = STAT_DATA; // ����״̬���շ�����
                   if (gbSendRecv) // ���ǽ��ղ���
                       {
                         // ���ôӻ���ַ��������
                         I2CMasterSlaveAddrSet(I2CM_BASE, gtDevice.ucSLA, true);
                         if (gtDevice.uiSize == 1) // ��ֻ׼������1���ֽ�
                             {
                               gucStatus = STAT_FINISH; // ����״̬�����ս���
                               // ����������ν���
                               I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
                             }
                         else
                             {
                               // �������ͻ��������ʼ
                               I2CMasterControl(I2CM_BASE,
                               I2C_MASTER_CMD_BURST_RECEIVE_START);
                             }
                           break;
                       }
                   }

           case STAT_DATA: // �շ�����״̬
                if (gbSendRecv) // ���ǽ��ղ���
                    {
                      // ��ȡ���յ�������
                      gtDevice.pcData[guiDataIndex++] = I2CMasterDataGet(I2CM_BASE);
                      if (guiDataIndex + 1 < gtDevice.uiSize) // ������δ�������
                          {
                              // �������ͻ�����ռ��� 
                               I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                          }
                      else
                          {
                             gucStatus = STAT_FINISH; // ����״̬���������
                             // �������ͻ���������
                             I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
                          }
                    }
                else
                    {
                      // ��������
                      I2CMasterDataPut(I2CM_BASE, gtDevice.pcData[guiDataIndex++]);
                      if (guiDataIndex < gtDevice.uiSize) // ������δ�������
                        {
                          // �������ͻ�����ͼ���
                           I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
                        }
                      else
                        {
                          gucStatus = STAT_FINISH; // ����״̬���������
                           // �������ͻ���������
                          I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
                        }
                   }
                   break;
          case STAT_FINISH: // �շ����״̬
                   if (gbSendRecv) // ���ǽ��ղ���
                         {
                          // ��ȡ������յ�������
                          gtDevice.pcData[guiDataIndex] = I2CMasterDataGet(I2CM_BASE);
                         }
                     gucStatus = STAT_IDLE; // ����״̬������
                    break;
          default:
                 break;
    }

}

#endif


void   I2Cwrite_much(uint32 I2C_BASE   ,unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen,char *pcData,unsigned int uiSize,tBoolean SendRecv)
{
   uint32 pp;	
   I2CWorkType I2CWork;
   I2CWork.gtDevice.ucSLA=ucSLA;
   I2CWork.gtDevice.pcData=pcData;
   I2CWork.gtDevice.uiLen=uiLen;
   I2CWork.gtDevice.ulAddr=ulAddr;
   I2CWork.gtDevice.uiSize=uiSize;
   I2CWork.gbSendRecv=SendRecv;
   I2CWork.I2CM_BASE=I2C_BASE;
   I2CWork.guiAddrIndex=0;
   I2CWork.guiDataIndex=0;
   I2CM_SendRecv(&I2CWork);
   
  
 while(1)
  {
     
    while(I2CMasterBusy(I2CWork.I2CM_BASE)==true); // �ȴ����߿���
  
   
	pp=I2CMasterErr(I2CWork.I2CM_BASE) 	;
    if (pp != I2C_MASTER_ERR_NONE) // ����������
       {
   
         I2CWork.gucStatus = STAT_IDLE;
         return;
       }
  
     switch (I2CWork.gucStatus)
       {
         case STAT_ADDR: // �������ݵ�ַ״̬
             if (I2CWork.guiAddrIndex < I2CWork.gtDevice.uiLen) // �����ݵ�ַδ�������
                {
                 // �����������ݵ�ַ
                 I2CMasterDataPut(I2CWork.I2CM_BASE, I2CWork.gcAddr[I2CWork.guiAddrIndex++]);

                 // �������ͻ�����ͼ���
                 I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
				
                 break;
                }
             else
                {
                   I2CWork.gucStatus = STAT_DATA; // ����״̬���շ�����
                   if (I2CWork.gbSendRecv==EI2C_Recv) // ���ǽ��ղ���
                       {
                         // ���ôӻ���ַ��������
                         I2CMasterSlaveAddrSet(I2CWork.I2CM_BASE, I2CWork.gtDevice.ucSLA, EI2C_Recv);
                         if (I2CWork.gtDevice.uiSize == 1) // ��ֻ׼������1���ֽ�
                             {
                               I2CWork.gucStatus = STAT_FINISH; // ����״̬�����ս���
                               // ����������ν���
                               I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
                             }
                         else
                             {
                               // �������ͻ��������ʼ
                               I2CMasterControl(I2CWork.I2CM_BASE,I2C_MASTER_CMD_BURST_RECEIVE_START);
                             }
						 
                           break;
                       }
                   }

           case STAT_DATA: // �շ�����״̬
                if (I2CWork.gbSendRecv==EI2C_Recv) // ���ǽ��ղ���
                    {
                      // ��ȡ���յ�������
                      I2CWork.gtDevice.pcData[I2CWork.guiDataIndex++] = I2CMasterDataGet(I2CWork.I2CM_BASE);
                      if (I2CWork.guiDataIndex + 1 < I2CWork.gtDevice.uiSize) // ������δ�������
                          {
                              // �������ͻ�����ռ��� 
                               I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                          }
                      else
                          {
                             I2CWork.gucStatus = STAT_FINISH; // ����״̬���������
                             // �������ͻ���������
                             I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
                          }
					   
                    }
                else
                    {
                      // ��������
                      I2CMasterDataPut(I2CWork.I2CM_BASE, I2CWork.gtDevice.pcData[I2CWork.guiDataIndex++]);
                      if (I2CWork.guiDataIndex < I2CWork.gtDevice.uiSize) // ������δ�������
                        {
                          // �������ͻ�����ͼ���
                           I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
                        }
                      else
                        {
                          I2CWork.gucStatus = STAT_FINISH; // ����״̬���������
                           // �������ͻ���������
                          I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
                        }
					  
                   }
                   break;
          case STAT_FINISH: // �շ����״̬
                   if (I2CWork.gbSendRecv==EI2C_Recv) // ���ǽ��ղ���
                         {
                          // ��ȡ������յ�������
                          I2CWork.gtDevice.pcData[I2CWork.guiDataIndex] = I2CMasterDataGet(I2CWork.I2CM_BASE);
					//	  UARTCharPut(UART0_BASE, 0x66);
                         }
				     
                     I2CWork.gucStatus = STAT_IDLE; // ����״̬������
                   //  UARTCharPut(UART0_BASE, 0x77);
                     return;
                    
          default:
                 break;
    }

}
 
  
}






