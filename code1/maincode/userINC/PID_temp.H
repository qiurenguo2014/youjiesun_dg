#ifndef _PID_temp
#define _PID_temp
#define PID_PERIODIC  2000
void HOT_init(sint16 Temp);
void PID_init(void);
uint16 pid_control(void);
uint16  PID_account(void);
 void Temp_account(void);

#endif

