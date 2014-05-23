//THIS CODE WAS DESIGNED TO DEMONSTRATE HOW THE FM24C04/FM24C04A SERIAL FRAM COULD
//BE INTERFACED TO THE 8051 MICROCONTROLLER. THE INTERFACE USES 2 LINES
//FROM PORT 2 (P2.7 AND P2.6) TO COMMUNICATE.
//THE CODE SHOWN DEMONSTRATES A 'RANDOM READ' AND 'BYTE WRITE'. THE OTHER *
//MODES OF OPERATION CAN BE CREATED BY EXPANDING UPON THESE ROUTINES.

//the first date writed:2003-06-28
//=============================
//sbit SDA=P3^4;//P1^1;//P1^2;//P1^1;//P1^2;//P2^7;	//THE SDA BIT IS PORT 2 BIT 7
//sbit SCL=P2^7;//P1^0;//P3^5;//P1^3;//P2^6;	//THE SCL BIT IS PORT 2 BIT 6
#include "file_ah9837.h"

#define IIC_READ 	0XA1     //
#define IIC_WRITE 	(0XA0>>1)   //
#define REG_READ 	0XD1
#define REG_WRITE 	(0XD0>>1)


#define IIC_uiLen   0x02
#define REG_uiLen   0x01

#define RUN 		1
#define STOP 		0
#define NOP 		_nop_()
//===============================

#define SERIALNUM 	0X11

#define COUNTER2M 	0X10
#define COUNTER2L 	0X0F
#define COUNTER1M 	0X0E
#define COUNTER1L 	0X0D
#define COUNTCON 	0X0C	//ALARM MINUTES

#define COMPANION 	0X0B   //ALARM SECONDS
#define WDCON 		0X0A
#define WDFLAG 		0X09	  //WATCHDOG

#define YEAR 		0X08	//YEARS
#define MONTH 		0X07	//MONTH
#define DATE 		0X06	//DATE
#define DAY 		0X05		//DAY
#define HOURS 		0X04	//HOURS
#define MINUTES 	0X03		//MINUTES
#define SECONDS 	0X02	//SECONDS

#define CONTROL 	0x01		//USER-NV
#define FLAGS 		0x00		//FLAGS/CONTROL

#define BL_write    0x00
#define BL_read     0x01
//enum{EI2C_send,EI2C_Recv};

#if 0

void write_time(time_type *time)

{
  tI2CM_DEVICE fm31256;
   unsigned char  byte=2;
 /*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=1;
  fm31256.ulAddr=FLAGS;
  fm31256.pcData=&byte;
 */ 
  I2CM_DeviceInitSet(&fm31256,REG_WRITE,FLAGS,1,&byte,1);
  I2CM_SendRecv(&fm31256,BL_write);

/*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=7;
  fm31256.ulAddr=SECONDS;
  fm31256.pcData=&time;
*/
 I2CM_DeviceDataSet(&fm31256, SECONDS,time->byte,7);
 I2CM_SendRecv(&fm31256,BL_write);

 /*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=1;
  fm31256.ulAddr=FLAGS;
  fm31256.pcData=&byte;
*/

  byte=0;
  I2CM_DeviceDataSet(&fm31256, FLAGS,&byte,1);
  I2CM_SendRecv(&fm31256,BL_write);

  
  /*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=1;
  fm31256.ulAddr=CONTROL;
  fm31256.pcData=&byte;
  */
  byte=0;
  I2CM_DeviceDataSet(&fm31256, CONTROL,&byte,1);
  I2CM_SendRecv(&fm31256,BL_write);

}


void read_time(time_type *time)
{  

  tI2CM_DEVICE fm31256;
  unsigned char  byte=1;
  /*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=1;
  fm31256.ulAddr=FLAGS;
  fm31256.pcData=&byte;
  */
   I2CM_DeviceInitSet(&fm31256,REG_WRITE,FLAGS,1,&byte,1);
  I2CM_SendRecv(&fm31256,BL_write);

/*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=7;
  fm31256.ulAddr=SECONDS;
  fm31256.pcData=&time;
  */
  I2CM_DeviceDataSet(&fm31256, SECONDS,time->byte,7);
  I2CM_SendRecv(&fm31256,BL_read);

   /*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=1;
  fm31256.ulAddr=FLAGS;
  fm31256.pcData=&byte;
*/

  byte=0;
  I2CM_DeviceDataSet(&fm31256, FLAGS,&byte,1);
  I2CM_SendRecv(&fm31256,BL_write);

  
 /*
  fm31256.ucSLA=REG_WRITE;
  fm31256.uiLen=1;
  fm31256.uiSize=1;
  fm31256.ulAddr=CONTROL;
  fm31256.pcData=&byte;
  */
  byte=0;
  I2CM_DeviceDataSet(&fm31256, CONTROL,&byte,1);
  I2CM_SendRecv(&fm31256,BL_write);
  




}


void readbyte_much (unsigned int add,unsigned int  i,unsigned char *dress)
{

  tI2CM_DEVICE fm31256;
  I2CM_DeviceInitSet(&fm31256,IIC_WRITE,add,2,dress,i);
  I2CM_SendRecv(&fm31256,BL_read);

}
//======================================================
void writebyte_much(unsigned int add,unsigned int i,unsigned char *dress)
{
  tI2CM_DEVICE fm31256;
  I2CM_DeviceInitSet(&fm31256,IIC_WRITE,add,2,dress,i);
  I2CM_SendRecv(&fm31256,BL_write);
}

#endif

void readbyte_much (unsigned int add,unsigned int  i,unsigned char *dress)
{

 I2Cwrite_much(I2C1_MASTER_BASE,IIC_WRITE,add ,IIC_uiLen,dress,i,EI2C_Recv);

}
//======================================================
void writebyte_much(unsigned int add,unsigned int i,unsigned char *dress)
{
  I2Cwrite_much(I2C1_MASTER_BASE,IIC_WRITE,add ,IIC_uiLen,dress,i,EI2C_send);
}


void read_time()
{
 uint8 byte=1	  ;
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,FLAGS ,REG_uiLen,&byte,1,EI2C_send);
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,SECONDS ,REG_uiLen,time.byte,7,EI2C_Recv);
 byte=0;
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,FLAGS ,REG_uiLen,&byte,1,EI2C_send);
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,CONTROL,REG_uiLen,&byte,1,EI2C_send);
}



void write_time()
{
 uint8 byte=2	  ;
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,FLAGS ,REG_uiLen,&byte,1,EI2C_send);
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,SECONDS ,REG_uiLen,time.byte,7,EI2C_send);
 byte=0;
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,FLAGS ,REG_uiLen,&byte,1,EI2C_send);
 I2Cwrite_much(I2C1_MASTER_BASE,REG_WRITE,CONTROL,REG_uiLen,&byte,1,EI2C_send);
}



