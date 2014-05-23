#include "file_ah9837.h"
//�ļ���LM3S_I2CM.c
/*
#define PART_LM3S1138
#include "LM3S_I2CM.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "sysctl.h"
#include "gpio.h"
#include "pin_map.h"
  */
 


// ���幤��״̬
#define STAT_IDLE 0 // ����״̬
#define STAT_ADDR 1 // �������ݵ�ַ״̬
#define STAT_DATA 2 // ���ջ�������״̬
#define STAT_FINISH 3 // �շ����״̬


// ����ȫ�ֱ���
static unsigned long I2CM_BASE = I2C0_MASTER_BASE; // ����I2C������ַ������ʼ��
static tI2CM_DEVICE gtDevice; // �������ݽӿ�
static unsigned char gucStatus = STAT_IDLE; // ����״̬
static tBoolean gbSendRecv; // �շ�������־��false���ͣ�true����
static char gcAddr[4]; // ���ݵ�ַ����
static unsigned int guiAddrIndex; // ���ݵ�ַ������������
static unsigned int guiDataIndex; // ���ݻ�������������


// ��tI2CM_DEVICE�ṹ�������ʼ�������������ݳ�Ա
void I2CM_DeviceInitSet(tI2CM_DEVICE *pDevice, unsigned char ucSLA,unsigned long ulAddr,unsigned int uiLen,unsigned char *pcData,unsigned int uiSize)
    {
      pDevice->ucSLA = ucSLA;
      pDevice->ulAddr = ulAddr;
      pDevice->uiLen = uiLen;
      pDevice->pcData = pcData;
      pDevice->uiSize = uiSize;
    }



// ��tI2CM_DEVICE�ṹ����������������շ���صĳ�Ա�����ݵ�ַ�����ݻ����������ݴ�С��
void I2CM_DeviceDataSet(tI2CM_DEVICE *pDevice, unsigned long ulAddr,unsigned char *pcData,unsigned int uiSize)
     {
       pDevice->ulAddr = ulAddr;
       pDevice->pcData = pcData;
       pDevice->uiSize = uiSize;
     }


// I2C������ʼ��
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
             	     SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0); // ʹ��I2C0ģ��
           	         SysCtlPeripheralEnable(I2C0SCL_PERIPH); // ʹ��SCL���ڵ�GPIOģ��
        		     GPIOPinTypeI2C(I2C0SCL_PORT, I2C0SCL_PIN); // ������عܽ�ΪSCL����
       		         SysCtlPeripheralEnable(I2C0SDA_PERIPH); // ʹ��SDA���ڵ�GPIOģ��
        	         GPIOPinTypeI2C(I2C0SDA_PORT, I2C0SDA_PIN); // ������عܽ�ΪSDA����
       	             IntEnable(INT_I2C0); // ʹ��I2C0�ж�
                  break;
			case I2C1_MASTER_BASE:
					 SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1); // ʹ��I2C1ģ��
					 SysCtlPeripheralEnable(I2C1SCL_PERIPH); // ʹ��SCL���ڵ�GPIOģ��
					 GPIOPinTypeI2C(I2C1SCL_PORT, I2C1SCL_PIN); // ������عܽ�ΪSCL����
					 SysCtlPeripheralEnable(I2C1SDA_PERIPH); // ʹ��SDA���ڵ�GPIOģ��
					 GPIOPinTypeI2C(I2C1SDA_PORT, I2C1SDA_PIN); // ������عܽ�ΪSDA����
					 IntEnable(INT_I2C1); // ʹ��I2C1�ж�
					 break;
            default:
                break;
       }
     I2CMasterInit(I2CM_BASE, false); // I2C����ģ���ʼ����100kbps
     I2CMasterIntEnable(I2CM_BASE); // ʹ��I2C��ģ���ж�
     IntMasterEnable( ); // ʹ�ܴ������ж�
     I2CMasterEnable(I2CM_BASE); // ʹ��I2C����
}

// ���ܣ�I2C�������ͻ��������
// ������pDevice��ָ��tI2CM_DEVICE�ͽṹ�������ָ�� 20
// bFlagȡֵfalse��ʾ���Ͳ�����ȡֵtrue��ʾ���ղ���
// ���أ�I2C_MASTER_ERR_NONE û�д���
// I2C_MASTER_ERR_ADDR_ACK ��ַӦ�����
// I2C_MASTER_ERR_DATA_ACK ����Ӧ�����
// I2C_MASTER_ERR_ARB_LOST ������ͨ���ٲ�ʧ��
// ���͸�ʽ��S | SLA+W | addr[1��4] | data[1��n] | P
// ���ո�ʽ��S | SLA+W | addr[1��4] | Sr | SLA+R | data[1��n] | P

unsigned long I2CM_SendRecv(tI2CM_DEVICE *pDevice, tBoolean bFlag)
    {
      
      if ((pDevice->uiLen <= 0) || (pDevice->uiSize <= 0))    // ���ݵ�ַ���Ȼ��շ����ݴ�С����Ϊ0������ִ���κβ���
          {
           return(I2C_MASTER_ERR_NONE);
          }
      gtDevice = *pDevice;
      if (gtDevice.uiLen > 4)
	  	  {
	  	    gtDevice.uiLen = 4; // ���ݵ�ַ���Ȳ��ܳ���4B
      	  }  
       gbSendRecv = bFlag; // ���ȫ�ֱ�����ʼ��
       guiAddrIndex = 0;
       guiDataIndex = 0;
       switch (gtDevice.uiLen) // �����ݵ�ַ�ֽ������
			{
				case 1: // 1�ֽ����ݵ�ַ
					gcAddr[0] = (char)(gtDevice.ulAddr);
					break;
				case 2: // 2�ֽ����ݵ�ַ
					gcAddr[0] = (char)(gtDevice.ulAddr >> 8);
					gcAddr[1] = (char)(gtDevice.ulAddr);
					break;
				case 3: // 3�ֽ����ݵ�ַ
					gcAddr[0] = (char)(gtDevice.ulAddr >> 16);
					gcAddr[1] = (char)(gtDevice.ulAddr >> 8);
					gcAddr[2] = (char)(gtDevice.ulAddr);
					break;
				case 4: // 4�ֽ����ݵ�ַ
					gcAddr[0] = (char)(gtDevice.ulAddr >> 24);
					gcAddr[1] = (char)(gtDevice.ulAddr >> 16);
					gcAddr[2] = (char)(gtDevice.ulAddr >> 8);
					gcAddr[3] = (char)(gtDevice.ulAddr);
                    break;
                default:
                    break;
             }
  // ����Ƕ�����ͨ�ţ�����Ҫ���ȵȴ����߿���
  // while (I2CMasterBusBusy(I2CM_BASE)); // �ȴ����߿���
  
	  I2CMasterSlaveAddrSet(I2CM_BASE, gtDevice.ucSLA, false); // ���ôӻ���ַ��д����
      I2CMasterDataPut(I2CM_BASE, gcAddr[guiAddrIndex++]); // ��ʼ�������ݵ�ַ
      gucStatus = STAT_ADDR; // ����״̬���������ݵ�ַ
 
      I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_START); // �������ͻ��������ʼ
      while (gucStatus != STAT_IDLE) // �ȴ����߲������
      	{
      	 I2C_ISR();
      	}
      return(I2CMasterErr(I2CM_BASE)); // ���ؿ��ܵĴ���״̬
}




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
	if (!ulStatus)
		{
		  return;
		}   
	switch (gucStatus)
		{
			case STAT_ADDR: // �������ݵ�ַ״̬
				if (guiAddrIndex < gtDevice.uiLen) // �����ݵ�ַδ�������
					{
					    I2CMasterDataPut(I2CM_BASE, gcAddr[guiAddrIndex++]); // �����������ݵ�ַ
						I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // �������ͻ�����ͼ���
						break;
					}
				else
					{
						gucStatus = STAT_DATA; // ����״̬���շ�����
						if (gbSendRecv) // ���ǽ��ղ���
							{
								I2CMasterSlaveAddrSet(I2CM_BASE, gtDevice.ucSLA, true);// ���ôӻ���ַ��������
								if (gtDevice.uiSize == 1) // ��ֻ׼������1���ֽ�
									{
										gucStatus = STAT_FINISH; // ����״̬�����ս���
										I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);// ����������ν���
									}
								else
									{
										I2CMasterControl(I2CM_BASE,// �������ͻ��������ʼ
										I2C_MASTER_CMD_BURST_RECEIVE_START);
									}
								break;
							}
					}
										// ֱ�ӽ�����һ��case���
			case STAT_DATA: // �շ�����״̬
					if (gbSendRecv) // ���ǽ��ղ���
					{
						gtDevice.pcData[guiDataIndex++] = I2CMasterDataGet(I2CM_BASE);// ��ȡ���յ�������
						if (guiDataIndex + 1 < gtDevice.uiSize) // ������δ�������
							{
								I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);// �������ͻ�����ռ���
							}
						else
							{
								gucStatus = STAT_FINISH; // ����״̬���������
                                I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);   // �������ͻ���������
                            }
                     }
                    else
					{
                        I2CMasterDataPut(I2CM_BASE, gtDevice.pcData[guiDataIndex++]);  // ��������
                        if (guiDataIndex < gtDevice.uiSize) // ������δ�������
                         {
                           I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // �������ͻ�����ͼ���
                         }
                       else
                         {
                            gucStatus = STAT_FINISH; // ����״̬���������
                            I2CMasterControl(I2CM_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);    // �������ͻ���������
                          }
                    }
                    break;
                case STAT_FINISH: // �շ����״̬
                         if (gbSendRecv) // ���ǽ��ղ���
                               {
                                 gtDevice.pcData[guiDataIndex] = I2CMasterDataGet(I2CM_BASE); // ��ȡ������յ�������
                               }
                            gucStatus = STAT_IDLE; // ����״̬������
                            break;
                default:
                        break;
        }

}




















