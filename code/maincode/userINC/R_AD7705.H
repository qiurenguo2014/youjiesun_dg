//文件：LM3S_I2CM.h
#ifndef _R_ad7705
#define _R_ad7705

//===========Communication Register
//   0/DRDY (0) RS2 (0) RS1 (0) RS0 (0) R/W (0) STBY (0) CH1 (0) CH0 (0)

//Register  RS2 RS1 RS0
#define CommunicationR_7705   (0<<4) // register 8 bits
#define  SetupR_7705   (1<<4) // register 8 bits
#define  ClockR_7705   (2<<4) // register 8 bits
#define DataR_7705   (3<<4) // register 16 bits
#define TestR_7705   (4<<4) // register 8 bits
#define NooperationR_7705   (5<<4) //
#define OffsetR_7705   (6<<4) // register 24 bits
#define GainR_7705   (7<<4) // register 24 bits
//   0/DRDY (0)  R/W (0)  STBY (0)
#define Wrbit    (0<<3)
#define Rdbit    (1<<3)
#define DRTYOnBIt  (1<<7)
#define DRTYOffBIt  (1<<7)
#define STBYOnBit     (1<<2)
#define STBYOffBit     (0<<2)
//CH1  CH0
#define AIN_ch11  00
#define AIN_ch22  01
#define AIN_ch00  02
#define AIN_ch12  03


//======== Setup Register 
//  MD1 (0) MD0 (0) G2 (0) G1 (0) G0 (0) B/U (0) BUF (0) FSYNC (1)

//MD1 MD0
#define Normal_Mode                       (00<<6)
#define SelfCalibration_Mode              (0x01<<6)
#define ZeroScaleSystemCalibration_Mode   (0x02<<6)
#define FullScaleSystemCalibration_Mode   (0x03<<6)

// G2 (0) G1 (0) G0 (0)     gain=(1~~128)
enum{Egain1,Egain2,Egain4,Egain8,Egain16,Egain32,Egain64,Egain128};
//  B/U (0) BUF (0) FSYNC (1)

#define  BipolarBit     (0<<2)
#define  UnipolarBit    (1<<2)

#define  BUFOnBit     (1<<1)
#define  BUFOffBit    (0<<1)

#define  FSYNCOnBit     (0<<0)
#define  FSYNCOffBit    (1<<0)


//============Clock  Register    
//    ZERO (0) ZERO (0) ZERO (0) CLKDIS (0) CLKDIV (0) CLK (1) FS1 (0) FS0 (1)

#define  CLKDISOnBit     (0<<4)
#define  CLKDISOffBit    (1<<4)

#define  CLKDIV1Bit     (0<<3)
#define  CLKDIV2Bit     (1<<3)


#define  CLK245Bit     (1<<2)
#define  CLK100Bit     (0<<2)

//   FS1 (0) FS0 
#define  FS_20hz_50hz       (0x0<<0)
#define  FS_25hz_60hz       (0x1<<0)
#define  FS_100hz_250hz     (0x2<<0)
#define  FS_200hz_500hz     (0x3<<0)


enum{ERsample_50,ERsample_1M}  ;

#define AD7705zio_readnub 0x10





// 定义I2C主机结构体
typedef struct
{
   unsigned char  ulAddr; // 数据地址
   unsigned char  *pcData;// 指向收发数据缓冲区的指针
   unsigned char   size;
   
}AD7705_ResHandtype;

void AD7705_init(void);
uint32 R_test(void);
Rgainflagtype Rgainchange(void);
uint32 gain_adjust(uint32 read_data,uint32 gain);
uint32 Read_ad7705_U(uint32 gain,uint32 readnub);
uint32 Read_ad7705_I(uint32 gain,uint32 readnub);
void ad7705_cal(void);
void write_ad7705Res(uint32 Register,uint32 *munedata,uint32 size);
void Read_ad7705Res(uint32 Register,uint32 *munedata,uint32 size);
void ad7705_zio( uint32 *I_zio,   uint32 *U_zio);

void spiDataGet(uint32  *dat);
void spiDataPut(uint8 dat);
#endif // __LM3S_I2CM_H__

