#include "file_ah9837.h"

//24c32  一个区32个字节


#define I2c_delay 0x100


unsigned long I2CM_SendRecv(I2CWorkType *I2CWork)
{
// 数据地址长度或收发数据大小不能为0，否则不执行任何操作
   if ((I2CWork->gtDevice.uiLen <= 0) || (I2CWork->gtDevice.uiSize <= 0))
         {
          return(I2C_MASTER_ERR_NONE);
         }
   
    if (I2CWork->gtDevice.uiLen > 4)
		{
		 I2CWork->gtDevice.uiLen = 4; // 数据地址长度不能超过4B
    	} 
       
        I2CWork->guiAddrIndex = 0;
        I2CWork->guiDataIndex = 0;
   switch (I2CWork->gtDevice.uiLen) // 将数据地址分解成数组
        {
          case 1: // 1字节数据地址
               I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr);
               break;
          case 2: // 2字节数据地址
               I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr >> 8);
               I2CWork->gcAddr[1] = (char)(I2CWork->gtDevice.ulAddr);
               break;
          case 3: // 3字节数据地址
              I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr >> 16);
              I2CWork->gcAddr[1] = (char)(I2CWork->gtDevice.ulAddr >> 8);
              I2CWork->gcAddr[2] = (char)(I2CWork->gtDevice.ulAddr);
              break;
          case 4: // 4字节数据地址
              I2CWork->gcAddr[0] = (char)(I2CWork->gtDevice.ulAddr >> 24);
              I2CWork->gcAddr[1] = (char)(I2CWork->gtDevice.ulAddr >> 16);
              I2CWork->gcAddr[2] = (char)(I2CWork->gtDevice.ulAddr >> 8);
              I2CWork->gcAddr[3] = (char)(I2CWork->gtDevice.ulAddr);
              break;
          default:
              break;
        }
    // 如果是多主机通信，则需要首先等待总线空闲
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
    while(I2CMasterBusy(I2CWork.I2CM_BASE)==true) // 等待总线空闲
    	{
    	 i++;
		 if(i>I2c_delay)
		 	{
		 	 break;
		 	}
    	}
  	}
  */	
	  while (I2CMasterBusBusy(I2CWork->I2CM_BASE)); // 等待总线空闲

	 
	    I2CMasterSlaveAddrSet(I2CWork->I2CM_BASE, I2CWork->gtDevice.ucSLA, EI2C_send); // 设置从机地址，写操作

		
	
        I2CMasterDataPut(I2CWork->I2CM_BASE, I2CWork->gcAddr[I2CWork->guiAddrIndex++]); // 开始发送数据地址
        I2CWork->gucStatus = STAT_ADDR; // 设置状态：发送数据地址
  
        while (I2CMasterBusBusy(I2CWork->I2CM_BASE)); // 等待总线空闲
// 命令：主机突发发送起始
       I2CMasterControl(I2CWork->I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_START);
         
     //  while (I2CWork->gucStatus != STAT_IDLE); // 等待总线操作完毕
         
       return(I2CMasterErr(I2CWork->I2CM_BASE)); // 返回可能的错误状态
}












#if 0
// I2C中断服务函数
void I2C_ISR(void)
{
    unsigned long ulStatus;
    ulStatus = I2CMasterIntStatus(I2CM_BASE, true); // 读取中断状态
    I2CMasterIntClear(I2CM_BASE); // 清除中断状态
    if (I2CMasterErr(I2CM_BASE) != I2C_MASTER_ERR_NONE) // 若遇到错误
       {
         gucStatus = STAT_IDLE;
         return;
       }
    if (!ulStatus) return;
    switch (gucStatus)
       {
         case STAT_ADDR: // 发送数据地址状态
             if (guiAddrIndex < gtDevice.uiLen) // 若数据地址未发送完毕
                {
                 // 继续发送数据地址
                 I2CMasterDataPut(I2CM_BASE, gcAddr[guiAddrIndex++]);

                 // 命令：主机突发发送继续
                 I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
                 break;
                }
             else
                {
                   gucStatus = STAT_DATA; // 设置状态：收发数据
                   if (gbSendRecv) // 若是接收操作
                       {
                         // 设置从机地址，读操作
                         I2CMasterSlaveAddrSet(I2CM_BASE, gtDevice.ucSLA, true);
                         if (gtDevice.uiSize == 1) // 若只准备接收1个字节
                             {
                               gucStatus = STAT_FINISH; // 设置状态：接收结束
                               // 命令：主机单次接收
                               I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
                             }
                         else
                             {
                               // 命令：主机突发接收起始
                               I2CMasterControl(I2CM_BASE,
                               I2C_MASTER_CMD_BURST_RECEIVE_START);
                             }
                           break;
                       }
                   }

           case STAT_DATA: // 收发数据状态
                if (gbSendRecv) // 若是接收操作
                    {
                      // 读取接收到的数据
                      gtDevice.pcData[guiDataIndex++] = I2CMasterDataGet(I2CM_BASE);
                      if (guiDataIndex + 1 < gtDevice.uiSize) // 若数据未接收完毕
                          {
                              // 命令：主机突发接收继续 
                               I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                          }
                      else
                          {
                             gucStatus = STAT_FINISH; // 设置状态：接收完成
                             // 命令：主机突发接收完成
                             I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
                          }
                    }
                else
                    {
                      // 发送数据
                      I2CMasterDataPut(I2CM_BASE, gtDevice.pcData[guiDataIndex++]);
                      if (guiDataIndex < gtDevice.uiSize) // 若数据未发送完毕
                        {
                          // 命令：主机突发发送继续
                           I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
                        }
                      else
                        {
                          gucStatus = STAT_FINISH; // 设置状态：发送完成
                           // 命令：主机突发发送完成
                          I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
                        }
                   }
                   break;
          case STAT_FINISH: // 收发完成状态
                   if (gbSendRecv) // 若是接收操作
                         {
                          // 读取接最后收到的数据
                          gtDevice.pcData[guiDataIndex] = I2CMasterDataGet(I2CM_BASE);
                         }
                     gucStatus = STAT_IDLE; // 设置状态：空闲
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
     
    while(I2CMasterBusy(I2CWork.I2CM_BASE)==true); // 等待总线空闲
  
   
	pp=I2CMasterErr(I2CWork.I2CM_BASE) 	;
    if (pp != I2C_MASTER_ERR_NONE) // 若遇到错误
       {
   
         I2CWork.gucStatus = STAT_IDLE;
         return;
       }
  
     switch (I2CWork.gucStatus)
       {
         case STAT_ADDR: // 发送数据地址状态
             if (I2CWork.guiAddrIndex < I2CWork.gtDevice.uiLen) // 若数据地址未发送完毕
                {
                 // 继续发送数据地址
                 I2CMasterDataPut(I2CWork.I2CM_BASE, I2CWork.gcAddr[I2CWork.guiAddrIndex++]);

                 // 命令：主机突发发送继续
                 I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
				
                 break;
                }
             else
                {
                   I2CWork.gucStatus = STAT_DATA; // 设置状态：收发数据
                   if (I2CWork.gbSendRecv==EI2C_Recv) // 若是接收操作
                       {
                         // 设置从机地址，读操作
                         I2CMasterSlaveAddrSet(I2CWork.I2CM_BASE, I2CWork.gtDevice.ucSLA, EI2C_Recv);
                         if (I2CWork.gtDevice.uiSize == 1) // 若只准备接收1个字节
                             {
                               I2CWork.gucStatus = STAT_FINISH; // 设置状态：接收结束
                               // 命令：主机单次接收
                               I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
                             }
                         else
                             {
                               // 命令：主机突发接收起始
                               I2CMasterControl(I2CWork.I2CM_BASE,I2C_MASTER_CMD_BURST_RECEIVE_START);
                             }
						 
                           break;
                       }
                   }

           case STAT_DATA: // 收发数据状态
                if (I2CWork.gbSendRecv==EI2C_Recv) // 若是接收操作
                    {
                      // 读取接收到的数据
                      I2CWork.gtDevice.pcData[I2CWork.guiDataIndex++] = I2CMasterDataGet(I2CWork.I2CM_BASE);
                      if (I2CWork.guiDataIndex + 1 < I2CWork.gtDevice.uiSize) // 若数据未接收完毕
                          {
                              // 命令：主机突发接收继续 
                               I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
                          }
                      else
                          {
                             I2CWork.gucStatus = STAT_FINISH; // 设置状态：接收完成
                             // 命令：主机突发接收完成
                             I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
                          }
					   
                    }
                else
                    {
                      // 发送数据
                      I2CMasterDataPut(I2CWork.I2CM_BASE, I2CWork.gtDevice.pcData[I2CWork.guiDataIndex++]);
                      if (I2CWork.guiDataIndex < I2CWork.gtDevice.uiSize) // 若数据未发送完毕
                        {
                          // 命令：主机突发发送继续
                           I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
                        }
                      else
                        {
                          I2CWork.gucStatus = STAT_FINISH; // 设置状态：发送完成
                           // 命令：主机突发发送完成
                          I2CMasterControl(I2CWork.I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
                        }
					  
                   }
                   break;
          case STAT_FINISH: // 收发完成状态
                   if (I2CWork.gbSendRecv==EI2C_Recv) // 若是接收操作
                         {
                          // 读取接最后收到的数据
                          I2CWork.gtDevice.pcData[I2CWork.guiDataIndex] = I2CMasterDataGet(I2CWork.I2CM_BASE);
					//	  UARTCharPut(UART0_BASE, 0x66);
                         }
				     
                     I2CWork.gucStatus = STAT_IDLE; // 设置状态：空闲
                   //  UARTCharPut(UART0_BASE, 0x77);
                     return;
                    
          default:
                 break;
    }

}
 
  
}






