//#include "define.h"
#include "Macro.h" 









//测试结果
enum{ETg_result,ECx_result,ERx_result,EE_result,EU_result,EAnn_result,EKnn_result};
enum{EVn_read,EVx_read};

#define pi 3.14159265358979



   //通讯协议
#define com_command0 0xaa
#define com_command1 0x55
#define rx_succeed  0xfaa
#define rx_wrong    0xfbb

//#define bsp_uart   115200  // 
enum{ELM3Sview_pcb,ELM3Stgr_pcb,EPC_pcb};	 

enum{Ecommand_TXmain,EStation_TXmain,EResult_TXmain,ECal_main,EModify_TXmain}; //发送主命令
enum{ETest_on,ETest_off,EStandard_no,EMeasure_no,EStandard_sup,EMeasure_sup};//状态 --故障提示状态display
enum{EResult_Fre,EResult_I,EResult_tg,EResult_vL,ERelay_tap,EResult_R,EResult_Ann};//结果 --
enum{EDC_cal,EAC_cal};//自校

enum{EstartTg_main,EstartR_main,EstartV_main,EstartX_main,Estop_main,Emodifyout_main,Emodifyin_main,ECAL_main,ERelay_main}  ; //接收work低四位
enum{EDebug_sub,ECal_sub,EGeneral_sub}; //接收debug高四位 
enum{EFre_000,EFre_450,EFre_475,EFre_500,EFre_525,EFre_550,EFre_575,EFre_600,EFre_625,EFre_650}; //接收FRE
enum{E00Vac=5,E600Vac,E700Vac,E800Vac,E900Vac,E1000Vac,E1100Vac,E1200Vac,E1300Vac,E1400Vac,E1500Vac,E1600Vac,E1700Vac,E1800Vac,E1900Vac,E2000Vac,E2100Vac,E2200Vac,E2300Vac,E2400Vac,E2500Vac,E2600Vac};
enum{E00Vdc=2,E300Vdc,E400Vdc,E500Vdc,E600Vdc};
/*

      0xaa,0x55,0x00,0x01,0x04, Ecommand,Ework,EFre,Evoltage,sum
常规介损  aa 55 00 01 04 00 20 02 01 23       
调试介损  aa 55 00 01 04 00 00 02 01 03 
校正介损  aa 55 00 01 04 00 10 02 01 13 

常规电阻  aa 55 00 01 04 00 21 02 01 23       
调试电阻  aa 55 00 01 04 00 01 02 01 03 
校正电阻  aa 55 00 01 04 00 11 02 01 13 

常规电压  aa 55 00 01 04 00 02 00 01 23   直流
常规电压  aa 55 00 01 04 00 02 00 01 23   交流  //频率0---直流

停止测试  aa 55 00 01 04 00 03 00 00 03    

修正数据  aa 55 00 01 04 04 00 00 00 modify   03  


LM3s---to---STC8958
Ecommand :       nub=2, data=enum{ETest_on,ETest_finsh,EStandard_no,EMeasure_no,EStandard_sup,EMeasure_sup,EResult};
EResult_Fre:     nub=5, data=float[Efre]
EResult_I:       nub=9, data=float[EIn]+float[EIx]
EResult_tg:      nub=9, data=float[Etg]+float[ECx]

*/
#define _FRE_40  40    // 1s/20=50ms
#define _sample_nub  1024  
#define _ADChigh  (0x1fff*998/1000)
#define _ADCmiddle (0x1fff*290/1000)
#define _ADClow   (0x1fff*88/1000)

//===傅立叶采样
#define _Low_current  0.0000001   //700uA
#define _High_current 1.5   //700uA
extern const float Rsample_CX[];//={2.0,20.0,200.0,2000.0,20000.0};
//extern const float Rgain3 [];//={3.16227,10.0};
#define _ADC7367LSBSize   (10.0/16384.0)
#define _ADC7705LSBSize   (2.50/65536.0)
#define  _Fourier_avrnub 3
#define  _FourierNUB  7
//#define  _FourierTime  30
#define  _FourierTime_sampleNub  1024  //一周期 1024点
#define  _complex64   0x7c00000000000000

#define _sin_flag1    16384

extern const float Rsample[];//={2.0,20.0,200.0,2000.0,20000.0};

enum {ERelay_off,ERelay_on}	;
//enum{Egain_2,Egain_20,Egain_200,Egain_2k,Egain_20k}; //relay
enum{Egain_3_no,Egain_3_yes};                       //relay 3.33  -- 10    

//modify_k
//修正
enum{
     ECN3_modify,ECN10_modify,ETgN3_modify,ETgN10_modify,
     ECX3_modify,ECX10_modify,ETgX3_modify,ETgX10_modify,
     ERk500_modify,ERk1M_modify,ERzio_modify,EUk_modify,
     E7705I500zio_modify, E7705I1Mzio_modify,E7705Uzio_modify
   
    };

#define Pre450_500  (9*4)     //0.8s  
#define Pre475_500  (19*2)    //0.8s
#define Pre500_500  40        //0.8s
#define Pre525_500  (21*2)    //0.8s
#define Pre550_500  (22*2)    //0.8s  


#define Pre550_600  (11*4)    //0.8s  
#define Pre575_600  (23*2)    //0.8s
#define Pre600_600   48       //0.8s
#define Pre625_600  (25*2)    //0.8s
#define Pre650_600  (13*4)    //0.8s  

//enum{EK_BatFull,EK_BatHigh,EK_BatMiddle,EK_BatLow};
//enum{EBAT_HM,EBAT_LE,ETempK,Esave}; 

//===选频==
//#define  _Fre_samplenub  (1360*10)

extern rx_datatype  rx_data ;
extern tx_datatype  tx_data ;
extern modifytype   modify_k; 
extern uint16 rx_flag    ;//_at_ 0x0b;
extern uint8 tx_nub     ;
extern uint32 FRE_flag  ;
extern  uint32 Tlong;
extern sint16 sinA[_FourierTime_sampleNub];
extern sint16 cosA[_FourierTime_sampleNub];
extern settype set;

extern RElaygainflagtype  four;
extern uint32 SysLinearTimer;
extern Resulttesttype Resulttest;
extern const    uint32  Rcpm_data[8];//={0x01bc,0x037c,0x06f8,0x0df0,0x1be0,0x37c0,0x6f80,0xff00};
extern const float Rsample_CX[];//={1000.0,10000.0};
extern float const modifydata_lib[];



