#include "file_ah9837.h"
//文件：LM3S_I2CM.c
/*
#define PART_LM3S1138
#include "LM3S_I2CM.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "sysctl.h"
#include "gpio.h"
#include "pin_map.h"
  */
 


// 定义工作状态
#define STAT_IDLE 0 // 空闲状态
#define STAT_ADDR 1 // 发送数据地址状态
#define STAT_DATA 2 // 接收或发送数据状态
#define STAT_FINISH 3 // 收发完成状态


// 定义全局变量
static unsigned long I2CM_BASE = I2C0_MASTER_BASE; // 定义I2C主机基址，并初始化
static tI2CM_DEVICE gtDevice; // 器件数据接口
static unsigned char gucStatus = STAT_IDLE; // 工作状态
static tBoolean gbSendRecv; // 收发操作标志，false发送，true接收
static char gcAddr[4]; // 数据地址数组
static unsigned int guiAddrIndex; // 数据地址数组索引变量
static unsigned int guiDataIndex; // 数据缓冲区索引变量


// 对tI2CM_DEVICE结构体变量初始化设置所有数据成员
void I2CM_DeviceInitSet(tI2CM_DEVICE *pDevice, unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen,unsigned char *pcData,unsigned int uiSize)
    {
      pDevice->ucSLA = ucSLA;
      pDevice->ulAddr = ulAddr;
      pDevice->uiLen = uiLen;
      pDevice->pcData = pcData;
      pDevice->uiSize = uiSize;
    }



// 对tI2CM_DEVICE结构体变量设置与数据收发相关的成员（数据地址、数据缓冲区、数据大小）
void I2CM_DeviceDataSet(tI2CM_DEVICE *pDevice, unsigned long ulAddr,unsigned char *pcData,unsigned int uiSize)
     {
       pDevice->ulAddr = ulAddr;
       pDevice->pcData = pcData;
       pDevice->uiSize = uiSize;
     }


// I2C主机初始化
void I2CM_Init(void)
{
    I2CM_DeviceInitSet(&gtDevice, 0, 0, 0, (void *)0, 0);
    if ((I2CM_BASE != I2C0_MASTER_BASE) && (I2CM_BASE != I2C1_MASTER_BASE))
       {
         I2CM_BASE = I2C0_MASTER_BASE;
       }
    switch (I2CM_BASE)
       {
           case I2C0_MASTER_BASE:
             	     SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0); // 使能I2C0模块
           	         SysCtlPeripheralEnable(I2C0SCL_PERIPH); // 使能SCL所在的GPIO模块
        		     GPIOPinTypeI2C(I2C0SCL_PORT, I2C0SCL_PIN); // 配置相关管脚为SCL功能
       		         SysCtlPeripheralEnable(I2C0SDA_PERIPH); // 使能SDA所在的GPIO模块
        	         GPIOPinTypeI2C(I2C0SDA_PORT, I2C0SDA_PIN); // 配置相关管脚为SDA功能
       	             IntEnable(INT_I2C0); // 使能I2C0中断
                  break;
			case I2C1_MASTER_BASE:
					 SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1); // 使能I2C1模块
					 SysCtlPeripheralEnable(I2C1SCL_PERIPH); // 使能SCL所在的GPIO模块
					 GPIOPinTypeI2C(I2C1SCL_PORT, I2C1SCL_PIN); // 配置相关管脚为SCL功能
					 SysCtlPeripheralEnable(I2C1SDA_PERIPH); // 使能SDA所在的GPIO模块
					 GPIOPinTypeI2C(I2C1SDA_PORT, I2C1SDA_PIN); // 配置相关管脚为SDA功能
					 IntEnable(INT_I2C1); // 使能I2C1中断
					 break;
            default:
                break;
       }
     I2CMasterInit(I2CM_BASE, false); // I2C主机模块初始化，100kbps
     I2CMasterIntEnable(I2CM_BASE); // 使能I2C主模块中断
     IntMasterEnable( ); // 使能处理器中断
     I2CMasterEnable(I2CM_BASE); // 使能I2C主机
}

// 功能：I2C主机发送或接收数据
// 参数：pDevice是指向tI2CM_DEVICE型结构体变量的指针 20
// bFlag取值false表示发送操作，取值true表示接收操作
// 返回：I2C_MASTER_ERR_NONE 没有错误
// I2C_MASTER_ERR_ADDR_ACK 地址应答错误
// I2C_MASTER_ERR_DATA_ACK 数据应答错误
// I2C_MASTER_ERR_ARB_LOST 多主机通信仲裁失败
// 发送格式：S | SLA+W | addr[1～4] | data[1～n] | P
// 接收格式：S | SLA+W | addr[1～4] | Sr | SLA+R | data[1～n] | P

unsigned long I2CM_SendRecv(tI2CM_DEVICE *pDevice, tBoolean bFlag)
    {
      
      if ((pDevice->uiLen <= 0) || (pDevice->uiSize <= 0))    // 数据地址长度或收发数据大小不能为0，否则不执行任何操作
          {
           return(I2C_MASTER_ERR_NONE);
          }
      gtDevice = *pDevice;
      if (gtDevice.uiLen > 4)
	  	  {
	  	    gtDevice.uiLen = 4; // 数据地址长度不能超过4B
      	  }  
       gbSendRecv = bFlag; // 相关全局变量初始化
       guiAddrIndex = 0;
       guiDataIndex = 0;
       switch (gtDevice.uiLen) // 将数据地址分解成数组
			{
				case 1: // 1字节数据地址
					gcAddr[0] = (char)(gtDevice.ulAddr);
					break;
				case 2: // 2字节数据地址
					gcAddr[0] = (char)(gtDevice.ulAddr >> 8);
					gcAddr[1] = (char)(gtDevice.ulAddr);
					break;
				case 3: // 3字节数据地址
					gcAddr[0] = (char)(gtDevice.ulAddr >> 16);
					gcAddr[1] = (char)(gtDevice.ulAddr >> 8);
					gcAddr[2] = (char)(gtDevice.ulAddr);
					break;
				case 4: // 4字节数据地址
					gcAddr[0] = (char)(gtDevice.ulAddr >> 24);
					gcAddr[1] = (char)(gtDevice.ulAddr >> 16);
					gcAddr[2] = (char)(gtDevice.ulAddr >> 8);
					gcAddr[3] = (char)(gtDevice.ulAddr);
                    break;
                default:
                    break;
             }
  // 如果是多主机通信，则需要首先等待总线空闲
  // while (I2CMasterBusBusy(I2CM_BASE)); // 等待总线空闲
  
	  I2CMasterSlaveAddrSet(I2CM_BASE, gtDevice.ucSLA, false); // 设置从机地址，写操作
      I2CMasterDataPut(I2CM_BASE, gcAddr[guiAddrIndex++]); // 开始发送数据地址
      gucStatus = STAT_ADDR; // 设置状态：发送数据地址
 
      I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_START); // 命令：主机突发发送起始
      while (gucStatus != STAT_IDLE) // 等待总线操作完毕
      	{
      	 I2C_ISR();
      	}
      return(I2CMasterErr(I2CM_BASE)); // 返回可能的错误状态
}




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
	if (!ulStatus)
		{
		  return;
		}   
	switch (gucStatus)
		{
			case STAT_ADDR: // 发送数据地址状态
				if (guiAddrIndex < gtDevice.uiLen) // 若数据地址未发送完毕
					{
					    I2CMasterDataPut(I2CM_BASE, gcAddr[guiAddrIndex++]); // 继续发送数据地址
						I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // 命令：主机突发发送继续
						break;
					}
				else
					{
						gucStatus = STAT_DATA; // 设置状态：收发数据
						if (gbSendRecv) // 若是接收操作
							{
								I2CMasterSlaveAddrSet(I2CM_BASE, gtDevice.ucSLA, true);// 设置从机地址，读操作
								if (gtDevice.uiSize == 1) // 若只准备接收1个字节
									{
										gucStatus = STAT_FINISH; // 设置状态：接收结束
										I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);// 命令：主机单次接收
									}
								else
									{
										I2CMasterControl(I2CM_BASE,// 命令：主机突发接收起始
										I2C_MASTER_CMD_BURST_RECEIVE_START);
									}
								break;
							}
					}
										// 直接进入下一条case语句
			case STAT_DATA: // 收发数据状态
					if (gbSendRecv) // 若是接收操作
					{
						gtDevice.pcData[guiDataIndex++] = I2CMasterDataGet(I2CM_BASE);// 读取接收到的数据
						if (guiDataIndex + 1 < gtDevice.uiSize) // 若数据未接收完毕
							{
								I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);// 命令：主机突发接收继续
							}
						else
							{
								gucStatus = STAT_FINISH; // 设置状态：接收完成
                                I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);   // 命令：主机突发接收完成
                            }
                     }
                    else
					{
                        I2CMasterDataPut(I2CM_BASE, gtDevice.pcData[guiDataIndex++]);  // 发送数据
                        if (guiDataIndex < gtDevice.uiSize) // 若数据未发送完毕
                         {
                           I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // 命令：主机突发发送继续
                         }
                       else
                         {
                            gucStatus = STAT_FINISH; // 设置状态：发送完成
                            I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);    // 命令：主机突发发送完成
                          }
                    }
                    break;
                case STAT_FINISH: // 收发完成状态
                         if (gbSendRecv) // 若是接收操作
                               {
                                 gtDevice.pcData[guiDataIndex] = I2CMasterDataGet(I2CM_BASE); // 读取接最后收到的数据
                               }
                            gucStatus = STAT_IDLE; // 设置状态：空闲
                            break;
                default:
                        break;
        }

}




















