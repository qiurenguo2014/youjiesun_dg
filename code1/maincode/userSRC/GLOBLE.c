
#include "file_ah9837.h"

uint32 SysLinearTimer = 0;

//RElaygainflagtype  four;
sint16  sinA[_FourierTime*_FourierTime_sampleNub];
sint16 cosA[_FourierTime*_FourierTime_sampleNub];
time_type time;
rx_datatype  rx_data ;
tx_datatype   tx_data ;
modifytype  modify_k; 
uint8 tx_nub     ;
uint8 debug_flag;
uint32 Udisk_work;
uint16  rx_flag    ;//_at_ 0x0b;
uint32 FRE_flag  ;
//uint32 T0_nub     ;
uint32 Tlong;
settype set;
Bellsettype Bellset;
Keysettype  Keyset;
Gansettype  Ganset;
Coversettype Coverset;
Oiltempsettype  Oiltempset;
resultRXtype resultRX;
Resulttesttype Resulttest;
T331type gT331;

//const float Rgain3 []={3.16227,10.0};

