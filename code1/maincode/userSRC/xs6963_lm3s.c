#include "file_ah9837.h"

/*
���ݿ�data------PIN_PB
#define  PIN_CE6963   PIN_PH0
#define  PIN_CD6963   PIN_PH1
#define  PIN_RD6963   PIN_PH2
#define  PIN_WR6963   PIN_PH3
*/




//======================
void WR_6963(unsigned char xs_data)
 {
  GPIOPinTypeGPIOOutput(PORT_DATA6963,  WHOLE_PORT );   //DATA ����
  GPIOPinWrite(PORT_DATA6963 , xs_data,xs_data);
  GPIOPinWrite(PORT_DATA6963 , ~xs_data,0);
  GPIOPinWrite(PORT_SET6963 ,PIN_CE6963,0);
  GPIOPinWrite(PORT_SET6963,PIN_WR6963,0);
  GPIOPinWrite(PORT_SET6963,PIN_CE6963|PIN_WR6963,PIN_CE6963|PIN_WR6963);
 }

//========================
uint8  RD_6963()
{
  uint8 read_data;
  GPIOPinTypeGPIOInput(PORT_DATA6963,  WHOLE_PORT );   //DATA ����
  GPIOPinWrite(PORT_SET6963 ,PIN_CE6963,0);
  GPIOPinWrite(PORT_SET6963,PIN_RD6963,0);
  read_data=(uint8)GPIOPinRead(PORT_DATA6963,  WHOLE_PORT );
  GPIOPinWrite(PORT_SET6963,PIN_CE6963|PIN_RD6963,PIN_CE6963|PIN_RD6963);
  return(read_data);
}

//=====================
void RWCheck()
{
  
  GPIOPinWrite(PORT_SET6963,PIN_CD6963,PIN_CD6963);
  while ((RD_6963()&0x03)^0x03)
  {
   
  }
  
}
//================================

// �����ݿڷ�Data
void OutPortData(uint8 dat ) 
                { 
                   RWCheck();
                   GPIOPinWrite(PORT_SET6963,PIN_CD6963,0);
                   WR_6963(dat);
				}

//д�� 1 ����������
void OutPortCom1(uint8 command)
          {
             RWCheck();
			 GPIOPinWrite(PORT_SET6963,PIN_CD6963,PIN_CD6963);
			 WR_6963(command);
		  }

//д�� 2 ����������
void OutPortCom2(uint8 dat,uint8 command) 
            {
              OutPortData(dat); 
			  OutPortCom1(command);
			}

//д�� 3 ����������
void OutPortCom3(uint8 data1,uint8 data2,uint8 command)
                  {
                   OutPortData(data1);
				   OutPortData(data2); 
				   OutPortCom1(command);
				  }


uint8 InPortData()
	              { 
	                 RWCheck();
					 GPIOPinWrite(PORT_SET6963,PIN_CD6963,0);
					 return(RD_6963()); 
				   }


void xs6963_init(void)
{
  GPIOPinWrite(PORT_SET6963,PIN_CE6963|PIN_RD6963|PIN_WR6963|PIN_CD6963,PIN_CE6963|PIN_RD6963|PIN_WR6963|PIN_CD6963);
}


