#ifndef _24cXX
#define _24cXX
typedef struct
{
 
  unsigned long ulAddr; // ���ݵ�ַ
  unsigned int uiLen;  // ���ݵ�ַ���ȣ�ȡֵ1��2��4��
  unsigned int uiSize; // �շ�����
  unsigned char ucSLA;  // �ӻ���ַ������7λ����ַ��������д����λ��
  char *pcData;        // ָ���շ����ݻ�������ָ��
}tI2CM_DEVICE;


typedef struct
{
 
 char gcAddr[4];        // ���ݵ�ַ����
 unsigned int guiAddrIndex; // ���ݵ�ַ������������
 unsigned int guiDataIndex; // ���ݻ�������������
 unsigned long I2CM_BASE ;//= I2C0_MASTER_BASE;   // ����I2C������ַ������ʼ��
 tI2CM_DEVICE gtDevice; // �������ݽӿ�
 unsigned char gucStatus ;// ����״̬
 tBoolean gbSendRecv;   // �շ�������־��false���ͣ�true����
 
}I2CWorkType;





#define STAT_IDLE 0 // ����״̬
#define STAT_ADDR 1 // �������ݵ�ַ״̬
#define STAT_DATA 2 // ���ջ�������״̬
#define STAT_FINISH 3 // �շ����״̬


#define UcSLA_24cXX   (0xa0>>1)
#define uiLen_24cXX   2




unsigned long I2CM_SendRecv(I2CWorkType *I2CWork);
void   I2Cwrite_much( uint32 I2C_BASE, unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen,char *pcData,unsigned int uiSize,tBoolean SendRecv);
//���β�����Ҫ�м������������
#endif

