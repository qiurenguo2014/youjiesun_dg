//#include "define.h"
#include "Macro.h" 
//===fm3125
#define udiskname_address 0x08
#define Cairsto_addr 0x10   //float2   2*4
#define setsto_addr  0x18
#define Vdc_K_addr  0x20   //float16  16*4
#define Vac_K_addr  0x28   //float4   4*4

#define Temp_Zio_addr  0x30   //float16  16*4
#define Temp_K_addr    0x38   //float4   4*4
#define  Cn_addr       0x40

#define modify_sto 0x100



#define viewpage_nub      20
#define VIEWnewpagesto_addr   0x0300	
#define VIEWsto_addr      0x0400	  //50
#define pageLong         (0x10*33)     //time+float[4]
#define ClockRAMoffsets    0x00
#define ComPointRAMoffsets 0x08
#define SetRAMoffsets      0x10
#define ResultRAMoffsets      0x20
#define DataCompointRAMoffsets     0x30
#define DatapointLong      0x10


#define TIMER_FREQ  200   // 节拍周期200Hz



//
enum{EDC_power,EAC_power};


//主界面
enum{EOilset_main,EView_main, EClock_main,ELan_main};



//油样设定
enum{ETg_oil,EFre_oil,ER_oil,EHot_oil,EWork_oil,EStart_oil,ECair_oil,};
enum{E00T=9,E50T,E55T,E60T,E65T,E70T,E75T,E80T,E85T,E90T,E95T,E100T,E105T,E110T,E115T,E120T,E125T,E130T};
enum{E00Vac=5,E600Vac,E700Vac,E800Vac,E900Vac,E1000Vac,E1100Vac,E1200Vac,E1300Vac,E1400Vac,E1500Vac,E1600Vac,E1700Vac,E1800Vac,E1900Vac,E2000Vac,E2100Vac,E2200Vac,E2300Vac,E2400Vac,E2500Vac,E2600Vac};
enum{E00Vdc=2,E300Vdc,E400Vdc,E500Vdc,E600Vdc};
enum{EFre50_0,EFre50_2,EFre50_5,EFre60_0,EFre60_2,EFre60_5};
enum{EAuto_work,EHand_work,ECom_work,ECair_work,ER_work};
enum{ETDA7367work_yes,ETDA7367work_no};



//文件管理
enum{EUdisk_file,EPrint_file,EPcCom_file};




//按键
#define  key_back    0x02//PIN_PE5
//#define  key_measure 0x40//PIN_PE5
#define  key_ok      0x40//PIN_PE5
#define  key_up      0x10//PIN_PE4
#define  key_down    0x20//PIN_PE3
//#define  key_right   0x04//PIN_PE2
//#define  key_left    0x02//PIN_PE1
#define  key_oil     0x01//PIN_PE0

#define  key_all       0x73
#define  key_modify    0x03
#define  key_no        0x00
enum{Edata_key,Emune_key};

//蜂鸣器
enum{EOnPeriod_bellstate,EOffPeriod_bellstate,EOne_bellstate ,EStop_bellstate};
enum{EBelloff,EBellon};

//盖子
enum{ECover_Yes,ECover_NO};
enum{ECover_Workon,ECover_Workoff};
enum{ECover_AlarmYes,ECover_AlarmNO,ECover_AlarmIgnore};



//接地
enum{EGan_Yes,EGan_NO};
enum{EGan_Workon,EGan_Workoff};
enum{EGan_AlarmYes,EGan_AlarmNO,EGan_AlarmIgnore};

//油温

enum{EOiltemp_Workon,EOiltemp_Workoff};
enum{EOiltemp_AlarmYes,EOiltemp_AlarmNO,EOiltemp_AlarmIgnore};




#define Vpp_Pwmstandard  0.5


#define pi 3.14159265358979

//测试结果
enum{ETg_result,ECx_result,ERx_result,ET_result,EUdc_result,EUac_result,ECn_result};


 
   //通讯协议
#define com_command0 0xaa
#define com_command1 0x55
#define rx_succeed  0xfaa
#define rx_wrong    0xfbb

//#define bsp_uart   115200  // 
enum{ELM3Sview_pcb,ELM3Stgr_pcb,EPC_pcb};
enum{Ecommand_TXmain,EStation_TXmain,EResult_TXmain,ECal,EModify_TXmain}; //接收主命令
enum{ETest_on,ETest_off,EStandard_no,EMeasure_no,EStandard_sup,EMeasure_sup};//采样板状态 --故障提示状态display
enum{EResult_Fre,EResult_I,EResult_tg,EResult_vL,ERelay_tap,EResult_R,EResult_Ann};//结果 --//结果 --
enum{EDC_cal,EAC_cal};//自校
enum{EstartTg_main,EstartR_main,EstartV_main,EstartX_main,Estop_main,Emodifyin_main,Emodifyout_main,ECAL_main,ERelay_main}  ; //发送work低四位
enum{EDebug_sub,ECal_sub,EGeneral_sub}; //发送debug高四位 
enum{EFre_000,EFre_450,EFre_475,EFre_500,EFre_525,EFre_550,EFre_575,EFre_600,EFre_625,EFre_650}; //发送FRE
//enum{E00Vac=5,E600Vac,E700Vac,E800Vac,E900Vac,E1000Vac,E1100Vac,E1200Vac,E1300Vac,E1400Vac,E1500Vac,E1600Vac,E1700Vac,E1800Vac,E1900Vac,E2000Vac,E2100Vac,E2200Vac,E2300Vac,E2400Vac,E2500Vac,E2600Vac};
//enum{E00Vdc=2,E300Vdc,E400Vdc,E500Vdc,E600Vdc};

/*

      0xaa,0x55,0x00,0x01,0x04,  Ecommand,Ework,EFre,Evoltage,sum
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
#define _ADCLSBSize   (20.0/16384.0)

#define  _Fourier_avrnub 3
#define  _FourierNUB  51
#define  _FourierTime 4     //一次四周期
#define  _FourierTime_sampleNub  1024  //一周期 1024点
#define  _complex64   0x7c00000000000000

#define _sin_flag1    16384


extern const float Rsample[];//={2.0,20.0,200.0,2000.0,20000.0};



enum {ERelay_off,ERelay_on}	;
//enum{Egain_2,Egain_20,Egain_200,Egain_2k,Egain_20k}; //relay
enum{Egain_3_no,Egain_3_yes};                       //relay 3.33  -- 10    


//modify_k
//修正
enum{//jacn3x(4.99/2.32 +1) jacn10x(556R)      
     ECN3_modify,      ECN10_modify,ETgN3_modify,ETgN10_modify,
	 	
     ECX3_modify,ECX10_modify,ETgX3_modify,ETgX10_modify,
     
     ERk500_modify,ERk1M_modify,ERzio_modify,EUk_modify,
     
     EPIDarea_modify,EPIDtransition_modify,EPIDkp1_modify,EPIDkp2_modify,EPIDTkp_modify,EPIDY1_modify,
     
     ETempZio_modify,ETempK_modify,EVdcK_modify,EVacK_modify,ET100_modify,ET120_modify,ESave_modify,
    };  
	 //pendicular ,EPTui

enum{EIzio_50,EIzio_1M,EIzio_10,EUzio};  //zio_ad7705
enum{ERI_50,ERI_1M,ERI_10M,ERU};  //gain_R
enum{ETemp_zio,ETempK,Epasscommande,Esave}; 

//enum{EK_BatFull,EK_BatHigh,EK_BatMiddle,EK_BatLow};
//enum{EBAT_HM,EBAT_LE,ETempK,Esave}; 

//==电池
enum{Epower_bat,Echange_bat};
enum{EUdisk_No ,EUdiskYes};

//===选频==
#define  _Fre_samplenub  (1360*10)
//enum{EFre_450,EFre_475,EFre_500,EFre_525,EFre_550,EFre_575,EFre_600,EFre_625,EFre_650}; 
enum{EVtest_sign,EFretest_sign,EVdisturb_sign,EFredisturb_sign}; // ResultdisplayFretype
#define FREsame  25   //12---0----12


extern time_type time;
extern rx_datatype  rx_data ;
extern tx_datatype  tx_data ;
extern modifytype   modify_k; 
extern uint16 rx_flag    ;//_at_ 0x0b;
extern uint8 tx_nub     ;
extern uint32 FRE_flag  ;
extern  uint32 Tlong;
extern sint16 sinA[_FourierTime*_FourierTime_sampleNub];
extern sint16 cosA[_FourierTime*_FourierTime_sampleNub];
extern settype set;
extern Bellsettype Bellset;
extern Keysettype  Keyset;
extern RElaygainflagtype  four;
extern uint32 SysLinearTimer;
extern Gansettype  Ganset;
extern Coversettype Coverset;
extern Oiltempsettype  Oiltempset; 
extern resultRXtype resultRX;
extern uint8 debug_flag;
extern Resulttesttype Resulttest;
extern T331type T331;
extern uint32 Udisk_work;




