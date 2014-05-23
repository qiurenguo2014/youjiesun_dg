
/* CH376оƬ Ӳ����׼�첽�������ӵ�Ӳ������� V1.0 */
/* �ṩI/O�ӿ��ӳ��� */



//#include "Ch376inc.h"
//#include "hal.h"
/* �����е�Ӳ�����ӷ�ʽ����(ʵ��Ӧ�õ�·���Բ����޸��������弰�ӳ���) */
/* ��Ƭ��������    CH376оƬ������
      TXD                  RXD
      RXD                  TXD       */
 #include "file_ah9837.h"
 #include	"HAL.H"	


//#define CH376_INT_WIRE			0x00  //INT0	/* �ٶ�CH376��INT#����,���δ������ôҲ����ͨ����ѯ�����ж�״̬��ʵ�� */

#define	UART_INIT_BAUDRATE  9600	/* Ĭ��ͨѶ������9600bps,����ͨ��Ӳ�������趨ֱ��ѡ����ߵ�CH376��Ĭ��ͨѶ������ */
#define	UART_WORK_BAUDRATE	76800 //9600//19200   /* ��ʽͨѶ������57600bps */

//enum {EUdisk_initNO ,EUdisk_initYES};



void	CH376_PORT_INIT(uint8 k   )  /* ����ʹ���첽���ڶ�дʱ��,���Խ��г�ʼ�� */
{
//  uint8 SFRPAGE_save=SFRPAGE;
//  SFRPAGE=CONFIG_PAGE;
 
 
  mDelaymS( 200 );
  if((k&0x01)!=0x00)
    {
      Uart1Init(UART_INIT_BAUDRATE);
	}
  else
  	{
  	  Uart1Init(UART_WORK_BAUDRATE);
  	}
  UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT);
  IntDisable(INT_UART1);
  mDelaymS( 200 );
//  SFRPAGE=SFRPAGE_save;
}

#ifdef	UART_WORK_BAUDRATE
void	SET_WORK_BAUDRATE( void )  /* ����Ƭ���л�����ʽͨѶ������ */
{

  Uart1Init(UART_WORK_BAUDRATE);
   UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT);
  IntDisable(INT_UART1);
  mDelaymS( 200 );
}

#endif

//#define	xEndCH376Cmd( )  /* ����CH376����,������SPI�ӿڷ�ʽ */

void	xWriteCH376Cmd( UINT8 mCmd )  /* ��CH376д���� */
{

     UARTCharPut(UART1_BASE , SER_SYNC_CODE1); /* ���������ĵ�1������ͬ���� */
	 UARTCharPut(UART1_BASE , SER_SYNC_CODE2); /* ���������ĵ�2������ͬ���� */
	 UARTCharPut(UART1_BASE ,  mCmd);/* ������� */



}

void	xWriteCH376Data( UINT8 mData )  /* ��CH376д���� */
{
 
  UARTCharPut(UART1_BASE ,  mData);/* ������� */

}

UINT8	xReadCH376Data( void )  /* ��CH376������ */
{
	UINT32	i;
    uint8 sbuf_temp=0;
for ( i = 0; i < 0x50000; i ++ )
	{  /* ������ֹ��ʱ */
	  if( 0== (HWREG(UART1_BASE + UART_O_FR) & UART_FR_RXFE))
         {
           sbuf_temp=(uint8)(UART1_BASE + UART_O_DR);
		   break;
        }

  	}
	
	return( sbuf_temp);  /* ��Ӧ�÷�������� */
}

/* ��ѯCH376�ж�(INT#�͵�ƽ) */
UINT8	Query376Interrupt( void )
{
#ifdef	CH376_INT_WIRE
	return( CH376_INT_WIRE ? FALSE : TRUE );  /* ���������CH376���ж�������ֱ�Ӳ�ѯ�ж����� */
#else
  {
   	 if( 0== (HWREG(UART1_BASE + UART_O_FR) & UART_FR_RXFE))
	 	{  /* ���δ����CH376���ж��������ѯ�����ж�״̬�� */
		// HWREG(UART1_BASE + UART_O_DR);
		 return( TRUE );
	    }
	 
	 else
	 	{
	  	return( FALSE );
	 	} 
   }	
#endif
}



UINT8	mInitCH376Host(  )  /* ��ʼ��CH376 */
{
	UINT8	res;

	   uint8 k;
    for(k=0x00;k<6;k++)
    	{
	     CH376_PORT_INIT(k);  /* �ӿ�Ӳ����ʼ�� */
	     xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* ���Ե�Ƭ����CH376֮���ͨѶ�ӿ� */
         xWriteCH376Data( 0x65 );
         res = xReadCH376Data( );
//	xEndCH376Cmd( );  // �첽���ڷ�ʽ����Ҫ
	     if ( res == 0x9A ) 
	     	{
		 	 break;
		 	}
    	 }
    if(k>=6)
    	{
    	 return( ERR_USB_UNKNOWN );
    	} /* ͨѶ�ӿڲ�����,����ԭ����:�ӿ������쳣,�����豸Ӱ��(Ƭѡ��Ψһ),���ڲ�����,һֱ�ڸ�λ,���񲻹��� */
#ifdef	UART_WORK_BAUDRATE
	xWriteCH376Cmd( CMD21_SET_BAUDRATE );  /* ���ô���ͨѶ������ */
#if		UART_WORK_BAUDRATE >= 6000000/256
	xWriteCH376Data( 0x03 );
	xWriteCH376Data( 256 - 6000000/UART_WORK_BAUDRATE );
#else
	xWriteCH376Data( 0x02 );
	xWriteCH376Data( 256 - 750000/UART_WORK_BAUDRATE );
#endif
	SET_WORK_BAUDRATE( );  /* ����Ƭ���л�����ʽͨѶ������ */
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // �첽���ڷ�ʽ����Ҫ
	if ( res != CMD_RET_SUCCESS ) return( ERR_USB_UNKNOWN );  /* ͨѶ�������л�ʧ��,����ͨ��Ӳ����λCH376������ */
#endif
	xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* �豸USB����ģʽ */
	xWriteCH376Data( 0x06 );
//	mDelayuS( 20 );  // �첽���ڷ�ʽ����Ҫ
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // �첽���ڷ�ʽ����Ҫ
	if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
	else return( ERR_USB_UNKNOWN );  /* ����ģʽ���� */
}