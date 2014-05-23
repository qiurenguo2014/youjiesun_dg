#ifndef _Temp_control
#define _Temp_control

void Temp_control(void);
uint32 Temp_Handcontrol(void);
uint8  Temp_Autocontrol(void);
uint8  Temp_Comcontrol(void);
sint16 TempSendcom_Calculate(sint16 Tempoilcurrently,sint16  Tempoilset_5);
void StopSave_hander(void);
void TEMP_disp(void);
void StopHot_Hander(void);
void StopHot_Hander(void);
#endif
