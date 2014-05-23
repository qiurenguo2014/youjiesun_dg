#ifndef _sign_pwm
#define _sign_pwm

void signPWM_init(float Sin_Hz);
void  PWM2IntHandler(void);
void PWM_sign_acc(float Sin_Hz,float Sin_Peak);
float V_adj(float fre_F);
void PWM_sign_stop(void);
#endif

