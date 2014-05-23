//文件：LM3S_I2CM.h
#ifndef __LM3S_I2CM_H__
#define __LM3S_I2CM_H__

#include <hw_types.h>
#include <hw_memmap.h>
#include <i2c.h>

// 定义I2C主机结构体
typedef struct
{
   unsigned long int ulAddr; // 数据地址
   unsigned int uiLen;   // 数据地址长度（取值1、2或4）
   unsigned int uiSize;  // 收发数据长度
   unsigned char ucSLA;  // 从机地址（这是7位纯地址，不含读写控制位）
   unsigned char  *pcData;         // 指向收发数据缓冲区的指针
}tI2CM_DEVICE;



extern void I2CM_DeviceInitSet(tI2CM_DEVICE *pDevice, unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen, unsigned char  *pcData,unsigned int uiSize);// 对tI2CM_DEVICE结构体变量初始化设置所有数据成员

extern void I2CM_DeviceDataSet(tI2CM_DEVICE *pDevice, unsigned long ulAddr, unsigned char  *pcData,unsigned int uiSize);// 对tI2CM_DEVICE结构体变量设置与数据收发相关的成员（数据地址、数据缓冲区、数据大小）

extern void I2CM_Init(void); // I2C主机初始化

extern unsigned long I2CM_SendRecv(tI2CM_DEVICE *pDevice, tBoolean bFlag);// I2C主机发送或接收数据
void I2C_ISR(void);

#define I2CM_DataSend(pDevice) I2CM_SendRecv(pDevice, false)  // 定义宏函数：发送数据

#define I2CM_DataRecv(pDevice) I2CM_SendRecv(pDevice, true)  // 定义宏函数：接收数据

#endif // __LM3S_I2CM_H__

