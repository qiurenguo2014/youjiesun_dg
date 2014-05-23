#ifndef _24cXX
#define _24cXX
typedef struct
{
 
  unsigned long ulAddr; // 数据地址
  unsigned int uiLen;  // 数据地址长度（取值1、2或4）
  unsigned int uiSize; // 收发数据
  unsigned char ucSLA;  // 从机地址（这是7位纯地址，不含读写控制位）
  char *pcData;        // 指向收发数据缓冲区的指针
}tI2CM_DEVICE;


typedef struct
{
 
 char gcAddr[4];        // 数据地址数组
 unsigned int guiAddrIndex; // 数据地址数组索引变量
 unsigned int guiDataIndex; // 数据缓冲区索引变量
 unsigned long I2CM_BASE ;//= I2C0_MASTER_BASE;   // 定义I2C主机基址，并初始化
 tI2CM_DEVICE gtDevice; // 器件数据接口
 unsigned char gucStatus ;// 工作状态
 tBoolean gbSendRecv;   // 收发操作标志，false发送，true接收
 
}I2CWorkType;





#define STAT_IDLE 0 // 空闲状态
#define STAT_ADDR 1 // 发送数据地址状态
#define STAT_DATA 2 // 接收或发送数据状态
#define STAT_FINISH 3 // 收发完成状态


#define UcSLA_24cXX   (0xa0>>1)
#define uiLen_24cXX   2




unsigned long I2CM_SendRecv(I2CWorkType *I2CWork);
void   I2Cwrite_much( uint32 I2C_BASE, unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen,char *pcData,unsigned int uiSize,tBoolean SendRecv);
//两次操作间要有间隔，否则死机
#endif

