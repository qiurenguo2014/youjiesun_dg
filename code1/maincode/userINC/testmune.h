#ifndef _Testmune
#define _Testmune

uint8 Vxsign_xs(void);
void  cs_start(void);
void  charge_1min(void );
void  discharge_1min(void );
void charge_mune(uint8 option);
void discharge_mune(uint8 option);
TgTesttype   TestTg_start(void); 

void  Cair_test(void);
void  Vsign_xs(float V_set,uint8 fre);
float  TestR_start(void);
void R_test(void);
#endif

