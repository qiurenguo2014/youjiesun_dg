#ifndef _xs6963_lm3s
#define _xs6963_lm3s

void WR_6963(unsigned char xs_data);
uint8  RD_6963(void );
void xs6963_init(void);
void RWCheck(void );
void OutPortData(unsigned char dat );
void OutPortCom1(unsigned char command);
void OutPortCom2(unsigned char dat,unsigned char command);
void OutPortCom3(unsigned char data1, unsigned char data2,unsigned char command) ;
unsigned char InPortData(void );
#endif
