#ifndef _MACRO_H
#define _MACRO_H


#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif



typedef unsigned char boolean;
typedef  unsigned char       uint8    		;
typedef unsigned char u8;
typedef unsigned char uchar;

typedef  unsigned short int  uint16  		 ;
typedef unsigned short u16;


typedef  unsigned long int   uint32   		  ;
typedef  unsigned long long  uint64   		   ;
typedef  signed char          sint8    			;
typedef  signed short int    sint16   			 ;
typedef  signed long int     sint32   			  ;
typedef  signed long long    sint64    			   ;


/*

typedef union
 	{
 	 uint8 channlBYTE;
	 uint8 setmune;
	 struct
       {
        uint8 cx:2;
        uint8 tgradio:2;
        uint8 tg:4 ;
	   }channlBIT;	
    }channlinit;



typedef union
 {
   uint8 byte[2];
   struct
   	{
   	 uint8 command;
     channlinit channl;
   	}mune;
  }tx_datainit;
#define tx_datanub 2


typedef  struct
   	{
     uint8  option;
	 uint8  pcb;
	 channlinit channl;
	 
	}setinit; 
	 
*/ 









typedef union
 {
   uint8  word_U8[4];
   uint16 word_U16[2];
   uint32 word_U32;
   sint8  word_S8[4];
   sint16 word_S16[2];
   sint32 word_S32;
   float  word_F;
 }wordtype;


typedef struct
  {
    uint32  readmin;
	uint32  readmax;
  }readtype;



typedef union                //介损电容档位标志
  {
    uint8 byte[4];
	uint32 RElaygainWORD;
    struct
       {
        uint8 CNgain;
        uint8 CXgain;
        uint8 CN_3 ;
		uint8 CX_3 ;
	   }RElaygainBIT;	
  }RElaygainflagtype;


typedef  union
    {
     uint8     b_k[4*4];
     wordtype  Fre[4];
    }ResultdisplayFretype;
#define ResultdisplayFre_nub  16


typedef  union
    {
     uint8     b_k[4*7];
     wordtype  result[7];   //enum{ETg_result,ECx_result,ERx_result,EE_result,EU_result}
    }Resulttesttype;
#define Resulttest_nub  32



typedef union          //体积电阻率档位标志
  {
    uint8 byte[4];
	uint32 RgainWORD;
    struct
       {
        uint8 U_gain;
        uint8 I_gain;
        uint8 U7705_gain ;
		uint8 I7705_gain ;
	   }RgainBIT;	
  }Rgainflagtype;










typedef union
         {
          uint8     b_k[80];
          wordtype  f_k[20];
		  uint32    H_k[20];
         }modifytype; 
#define  modify_nub 80



typedef union
 {
   uint8 byte[48];
   struct
   	{
     uint8 order0;
     uint8 order1;
	 uint8 mainpcb;
	 uint8 slavepcb;
	 uint8 nub;
   	 uint8 maincommand;
     uint8 subcommand;
	 uint8 nop;
     uint8  bill[40];
   	}mune;
  }tx_datatype;
#define tx_datanub 48


typedef  union
  {
   uint8 byte[0xff];
   struct
   	{
   	 uint8 nub	 ;
   	 uint8 workcommand;
	 uint8 Fre;
	 uint8 Voltage;
	 modifytype modify_k;
  	}mune; 
  }rx_datatype;



typedef struct
 {
   uint8 Work;
   uint8 Fre;
   uint8 Voltage;
   uint8 Debug;
 }settype;



typedef struct
 	{
      wordtype  Fre_T;
	  wordtype  Terror;
	  wordtype  In;
      wordtype  Ix;
  	}Sampleresulttype;

typedef struct
   {
     float real;
     float image;
   }COMPLEXtype;

#define  _FourierNUB  7

typedef  struct
   {
     
	 float  f[_FourierNUB *2];
	 COMPLEXtype  complex[_FourierNUB ][2];     
    }FourierComplextype ;


#ifndef NULL
#define NULL 0
#endif

#define ARRAY_SIZE(m)  (sizeof(m)/sizeof((m)[0]))

#define MSB(x)	(((x)&0xff00)>>8)
#define LSB(x)	((x)&0xff)


//#define _SEND_MESSAGE_PC
#define SYSLOG 1
//#define _DETECT_UPDATE_PIN
#define  _GLOBAL_DEBUG_ENABLE
//#define  _FRE_DEBUG_ENABLE

#define  _PP_DEBUG_ENABLE
//#define  _gain_DEBUG_ENABLE
#define  _Terror_DEBUG_ENABLE


#endif

