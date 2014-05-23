
#include "file_ah9837.h"

uint32 SysLinearTimer = 0;


Resulttesttype Resulttest;
RElaygainflagtype  four;
sint16  sinA[_FourierTime_sampleNub];
sint16 cosA[_FourierTime_sampleNub];
rx_datatype  rx_data ;
tx_datatype   tx_data ;
modifytype  modify_k; 
uint16  rx_flag    ;//_at_ 0x0b;
uint8 tx_nub     ;
uint32 FRE_flag  ;


uint32 Tlong;
settype set;



const float Rsample_CX[]={2000.0,2000.0};

const    uint32  Rcpm_data[8]={0x01bc,0x037c,0x06f8,0x0df0,0x1be0,0x37c0,0x6f80,0xff00};   //7705
float const modifydata_lib[]={3.22,10.0,0.0,0.0,
	                    3.22,10.0,0.0,0.0,
	                    500.0,1000000.0,0.0,1000.0 ,
	                    0.0,0.0,0.0,0.0};




//const float Rgain3 []={3.16227,10.0};

