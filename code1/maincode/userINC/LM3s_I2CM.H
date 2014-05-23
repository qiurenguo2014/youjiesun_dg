//�ļ���LM3S_I2CM.h
#ifndef __LM3S_I2CM_H__
#define __LM3S_I2CM_H__

#include <hw_types.h>
#include <hw_memmap.h>
#include <i2c.h>

// ����I2C�����ṹ��
typedef struct
{
   unsigned long int ulAddr; // ���ݵ�ַ
   unsigned int uiLen;   // ���ݵ�ַ���ȣ�ȡֵ1��2��4��
   unsigned int uiSize;  // �շ����ݳ���
   unsigned char ucSLA;  // �ӻ���ַ������7λ����ַ��������д����λ��
   unsigned char  *pcData;         // ָ���շ����ݻ�������ָ��
}tI2CM_DEVICE;



extern void I2CM_DeviceInitSet(tI2CM_DEVICE *pDevice, unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen, unsigned char  *pcData,unsigned int uiSize);// ��tI2CM_DEVICE�ṹ�������ʼ�������������ݳ�Ա

extern void I2CM_DeviceDataSet(tI2CM_DEVICE *pDevice, unsigned long ulAddr, unsigned char  *pcData,unsigned int uiSize);// ��tI2CM_DEVICE�ṹ����������������շ���صĳ�Ա�����ݵ�ַ�����ݻ����������ݴ�С��

extern void I2CM_Init(void); // I2C������ʼ��

extern unsigned long I2CM_SendRecv(tI2CM_DEVICE *pDevice, tBoolean bFlag);// I2C�������ͻ��������
void I2C_ISR(void);

#define I2CM_DataSend(pDevice) I2CM_SendRecv(pDevice, false)  // ����꺯������������

#define I2CM_DataRecv(pDevice) I2CM_SendRecv(pDevice, true)  // ����꺯������������

#endif // __LM3S_I2CM_H__
