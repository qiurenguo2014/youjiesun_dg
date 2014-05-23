
//================主设置界面
 #define mainset_lin     0x00
 #define mainset_high    0x10
 #define mainset_column  0 
 #define mainset_width   0x08

//油样设置界面
 #define oilset_lin     0x00
 #define oilset_high    0x10
 #define oilset_column  0 
 #define oilset_width   0x08
//=========
#define clockset_line    (oilset_lin +(EClock_main+2)*oilset_high)
#define clockset_column  (oilset_column+4)  
#define clockset_high    0x10
#define clock_nubkey     12

 

#define clock_testlin  0x30
#define clock_testcolumn 0x00

#define clock_lin     0x70
#define clock_column  0x00



//====查阅截面







//加热过程提示
#define Workwarn_lin     0x00
#define Workwarn_column  0x00
#define Workwarn_high    0x10 



#define HOTwarn_lin     0x10
#define HOTwarn_column  0x00

#define Tempoilwarn_lin     0x20 
#define Tempoilwarn_column  00

#define Clockwarn_lin     clockset_line// 0x30 
#define Clockwarn_column  clockset_column//0x0


#define Voltage_lin     0x00
#define Voltage_column  0x00

//测试过程
#define SIGNwarn_lin   0x10
#define SIGNwarn_column   0x4

#define Chargewarn_lin   0x3f
#define Chargewarn_column   0x0



//结果显示

#define Resulttest_lin     0x0
#define Resulttest_column  0x0
#define Resulttest_high    12

#define Resulttest_lin_com  (Resulttest_lin  +Resulttest_high*7)

#define Resultclock_lin    (12*4)
#define Resultclock_column     0x00

#define ResultKEY_lin    (12*4)
#define ResultKEY_column     0x00
#define ResultKEY_width     0x06
#define ResultKEY_high        16


#define Annwarn_lin     0x80
#define Annwarn_column  0x00

