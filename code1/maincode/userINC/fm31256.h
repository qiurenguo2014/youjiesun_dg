#ifndef _fm31256
#define _fm31256


/* void start(void);
 void stop(void);
 void ack(void);
 void Recack(void);
 unsigned char  inbyte(void);
 void outbyte(unsigned char outdata);
 void write_reg(unsigned char add,unsigned char wbyte);
 void rst_wdg( );
  void clockset_mune();
 */ 

 void read_time(void);
 void write_time(void);

 void writebyte_much(unsigned int add,unsigned int i,unsigned char *dress);
 void readbyte_much (unsigned int add,unsigned int  i,unsigned char *dress);

  
#endif


