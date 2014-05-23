#ifndef _modifyset
#define _modifyset

uint8  modify_read(void);
void xz_mune(void);
void bcd8_display(  unsigned char *byte,uint16 lin,uint8 column, uint32 xsdata);
void xzset_mune(void);
uint8  modify_set8(unsigned char *byte,unsigned char nub,unsigned int lin ,unsigned char column);
uint8  modify(void);
void  modifyset_k(unsigned char option);
void Vmodify_set(uint8 option);
void Vmodifyset_sto(uint8 option);
uint8   TgC_read(void)	;
void Tmodify_set(uint8 option);
#endif




















