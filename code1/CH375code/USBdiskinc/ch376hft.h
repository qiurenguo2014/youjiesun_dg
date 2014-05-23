#ifndef  _ch376hft
#define _ch376hft
uint8 udisk_ch376(void );
void exram_init(void);
void file_name(uint8 *buf);
//uint8 udisk_sto();
uint16 CreateDate( time_type *time);
uint16 CreateTime( time_type *time);
uint8	SetFileCreateTime( uint16 iCreateDate, uint16 iCreateTime);//,uint8 *buf );
void  udisk_content(void);
unsigned char bcd_hex1(unsigned char i);
 #endif

