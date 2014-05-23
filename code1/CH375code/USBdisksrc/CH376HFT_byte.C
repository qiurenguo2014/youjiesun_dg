/* 2008.10.18
****************************************
**  Copyright  (C)  W.ch  1999-2009   **
**  Web:  http://www.winchiphead.com  **
****************************************
**  USB Host File Interface for CH376 **
**  TC2.0@PC, KC7.0@MCS51             **
****************************************
*/
/* CH376 主机文件系统接口 */

/*
将数据处理成文本形式，100组；
结构: 组:  电流        电阻 
      00: I=200.0A     R=2000.0uo  
      01: I=100.0A     R=1000.0uo  
      .......
      99: I=99.0A      R=1000.0uo  
*/

/* C51   CH376HFT.C */
/* LX51  CH376HFT.OBJ */
/* OHX51 CH376HFT */

//#include <reg52.h>
//#include <stdio.h>
//#include <string.h>
#define		EN_DIR_CREATE	1	/* 支持新建多级子目录 */ 
#define		EN_LONG_NAME	1
#define	    EN_SECTOR_ACCESS 1
#define	    EN_DISK_QUERY 1
 #include "file_ah9837.h" 
//#include  " HAL.H"   //  硬件异步串口连接方式 */
#include  "FILE_SYS_c51.h" 



 /*
#define group_offset 0x00   
#define I_offset     0x04
#define R_offset     0x0e
#define group_nub    27
#define Udiskstartaddress 40


 void  udisk_content()
 {
   uint8 xdata udisk[2044];  
   uint8 k;
   uint16 address;
   xs_need xs_needon;
    {
	 
	  for(address=0x00;address<2048;address++)
	  	{
	  	 udisk[address]=' ';
	  	}
   	}
   strcpy( udisk,"   福建普华HL-IIIA回路电阻测试仪");
   udisk[Udiskstartaddress-2]=0x0d;
   udisk[Udiskstartaddress-1]=0x0a ;
   
   for(k=0x00;k<sto_group;k++)
   	{
      read_data(k,&xs_needon);
      address=k*group_nub+Udiskstartaddress;
	  
	  udisk[ address+group_offset]=0x30+k/10;
	  udisk[address+group_offset+1]=0x30+k%10;
	  udisk[address+group_offset+2]=':';

	  udisk[address+I_offset]='I';
	  udisk[address+I_offset+1]='=';
        {
		   uint8 j;	
		   sprintf (&udisk[address+I_offset+2], "%3.1f\n", xs_needon.f.i);	
            
		   for(j=0;j<5;j++)
		     {
		      if(udisk[address+I_offset+2+j]==0x0a)
		 	    {
		 	     udisk[address+I_offset+2+j]=' ';
			     for(j++;j<5;j++)
		 	 	  {
		 	 	   udisk[address+I_offset+2+j]=' ';
		 	 	  }
                 break; 
		 	   }
		   	 }
	  	}	
	  udisk[address+I_offset+7]='A';
   

      udisk[address+R_offset]='R';
	  udisk[address+R_offset+1]='=';
        {
		   uint8 j;	
		   sprintf (&udisk[address+R_offset+2], "%4.1f\n", xs_needon.f.r);	
		   for(j=0;j<6;j++)
		     {
		      if(udisk[address+R_offset+2+j]==0x0a)
		 	    {
		 	     udisk[address+R_offset+2+j]=' ';
			     for(j++;j<5;j++)
		 	 	  {
		 	 	   udisk[address+R_offset+2+j]=' ';
		 	 	  }
                 break; 
		 	   }
		   	 }
	  	}	
	  udisk[address+R_offset+8]='u';
	  udisk[address+R_offset+9]=0xa6 ;
	  udisk[address+R_offset+0xa]=0xb8 ;//'Ω';
	  
	  udisk[address+ group_nub-2]=0x0d ;//'Ω';
	  udisk[address+ group_nub-1]=0x0a ;

	  
	
   	}
   
 
 
 }
 
*/

/*
 void exram_init()
{
// uint8 k;
 uint16 i;
 uint8 xdata *p;
// uint8 SFRPAGE_save=SFRPAGE;
// EMI_in_Init();
 ERAMcs_set;
 p=(uint8 xdata *)0x00;
 for(i=0x00;i<0x200;i++)
 	{
 	 *p++=0x38;
 	}
 //EMI_out_Init();
 // SFRPAGE=CONFIG_PAGE;
  p=(uint8 xdata *)0x00;
  ERAMcs_UA;
     for(i=0x00;i<0x800;i++)
 	 {
 	   *p++=0x30+1;
 	 }
	 ERAMcs_UB;
	  p=(uint8 xdata *)0x00;
     for(i=0x00;i<0x800;i++)
 	 {
 	   *p++=0x30+2;
 	 }
	  ERAMcs_UC;
	   p=(uint8 xdata *)0x00;
     for(i=0x00;i<0x800;i++)
 	 {
 	   *p++=0x30+3;
 	 }
	  
 
// SFRPAGE=SFRPAGE_save;
}
*/                  
                                              
const uint8  Udiskname[4]={'O','i','l','_'} ;


void file_name(uint8 *buf )
  {
    uint8 k;
	union
		{
		 uint8 byte[2];	
         uint16 group;
		}name;
	
	
  
	{
		uint8 i;
		for (i=0x00;i<4;i++)
			{
			 buf[i]=Udiskname[i];
			}
 	}
   name.group=(unsigned int)udiskname_address ;
   readbyte_much( name.group,2, name.byte);


     for(k=4-1;k<4;k--)
   	      {
          	 buf[k+4]=(name.group%10)+0x30;
	         name.group/=10;
        	}
     	
   
   	buf[8]='.';
	buf[9]='T';
	buf[10]='X';
	buf[11]='T';
	buf[12]='\0';

  }


/* 为指定文件设置创建日期和时间 */
/* 输入参数:   原始文件名在iFileName中, 新的创建日期和时间: iCreateDate, iCreateTime */
/* 返回状态码: USB_INT_SUCCESS = 设置成功,
               其它状态码参考CH376INC.H */
		
 unsigned char bcd_hex1(unsigned char i)
     {
       i=(i>>4)*10+(i&0x0f);
       return (i);
     }
			 

uint16 CreateDate( time_type *time)
{
  uint8 year ;
  uint8 month;
  uint8 day;

  year=(uint8)(2000-1980+bcd_hex1(time->time.year));
  month=bcd_hex1(time->time.month);
  day=bcd_hex1(time->time.day);
  return( (year<<9) + (month<<5) + day );
}

uint16 CreateTime( time_type *time)
{
  uint8 hour ;
  uint8 minute;
  uint8 second;

  hour= bcd_hex1(time->time.hour);
  minute=bcd_hex1(time->time.minute);
  second=bcd_hex1(time->time.second);
  return ( (hour<<11) + (minute<<5) + (second>>1));
}




UINT8	SetFileCreateTime( UINT16 iCreateDate, UINT16 iCreateTime)//,uint8 *buf )
{
	UINT8	s; 
	uint8 bufz[2];
	//P_FAT_DIR_INFO	pDir;
	
	//s = CH376FileOpen( iFileName );  /* 打开文件 */
	//if ( s == USB_INT_SUCCESS ) {
		/* 文件读写操作等... */
		s = CH376DirInfoRead( );  /* 读取当前文件的目录信息FAT_DIR_INFO,将相关数据调到内存中 */
		if ( s == USB_INT_SUCCESS )
		 {

		 //  	CH376ReadBlock( buf );  /* 从内存缓冲区读取FAT_DIR_INFO数据块,返回长度总是sizeof(FAT_DIR_INFO) */
		//	pDir = (P_FAT_DIR_INFO)buf;  /* 当前文件目录信息 */
			
			bufz[0] = (UINT8)iCreateTime;  /* 文件创建的时间,低8位在前 */
			bufz[1] = (UINT8)(iCreateTime>>8);  /* 文件创建的时间,高8位在后 */
			CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_CrtTime ), 2 );  /* 向内部缓冲区偏移地址DIR_CrtTime写入2个字节 */
            CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_WrtTime ), 2 ); 
			
			bufz[0] = (UINT8)iCreateDate;  /* 文件创建的日期,低8位在前 */
			bufz[1] = (UINT8)(iCreateDate>>8);  /* 文件创建的日期,高8位在后 */
			CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_CrtDate ), 2 );  /* 向内部缓冲区偏移地址DIR_CrtDate写入2个字节 */
			CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_WrtDate ), 2 ); 
			s = CH376DirInfoSave( );  /* 保存文件的目录信息 */
			if ( s == USB_INT_SUCCESS ) {  /* 成功修改并保存 */
				/* 文件读写操作等... */
			}
	//	CH376FileClose( FALSE );  /* 关闭文件 */
	}
	return( s );
}

/*
//==U盘标准时钟


DWORD get_fattime (void)
{
	unsigned char Dec[6];
    RTC_T time;

	ReadRtc(&time);
	Dec[0] =  time.Year    - (time.Year>>4) * 6;
	Dec[1] =  time.Month   - (time.Month>>4) * 6;
	Dec[2] =  time.Date    - (time.Date>>4) * 6;
	Dec[3] =  time.Hours   - (time.Hours>>4) * 6;
	Dec[4] =  time.Minutes - (time.Minutes>>4) * 6;
	Dec[5] =  time.Seconds - (time.Seconds>>4) * 6;
	return    ((Dec[0]+20)  << 25)           // Year = 2007
            | ( Dec[1]      << 21)           // Month = June
            | ( Dec[2]      << 16)           // Day = 5
            | ( Dec[3]      << 11)           // Hour = 11
            | ( Dec[4]      << 5)            // Min = 38
            | ( Dec[5]      >> 1)            // Sec = 0
            ;
#if 0
    return    ((2007UL-1980) << 25) // Year = 2007
            | (6UL << 21)           // Month = June
            | (5UL << 16)           // Day = 5
            | (11U << 11)           // Hour = 11
            | (38U << 5)            // Min = 38
            | (0U >> 1)             // Sec = 0
            ;
#endif
} 

*/






uint8  udisk_ch376()
   {
   // uint8  SFRPAGE_save=SFRPAGE;
	UINT8	s;
    uint8			buf[40];
//	uint8 name ;
	mDelaymS( 100 );  /* 延时100毫秒 */
	//if(Udisk_uartflag==EUdisk_initNO)
    {
      s = mInitCH376Host();  /* 初始化CH376 */
   
	if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	{
    	 return(s);
    	}
	} 
     rx_flag=1;
	// China_swing(easydisk_warnlin,easydisk_warncolumn,&text_zzcz,easydisk_warnscreen|0x80);	//	U盘失败		 
	/* 其它电路初始化 */
	//printf( "Wait Udisk/SD\n" );等待U盘		 
//	while ( 1 )
	  {
		
	for(s=0;s<20;s++)
	     {
	       if( CH376DiskConnect( ) != USB_INT_SUCCESS ) 
		   { 
			  mDelaymS( 100 );   /* 检查U盘是否连接,等待U盘插入,对于SD卡,可以由单片机直接查询SD卡座的插拔状态引脚 */
            		  
		   }
		   else
		   	{
		   	 break;
		   	}
		}
		
		mDelaymS( 200 );        /* 延时,可选操作,有的USB存储器需要几十毫秒的延时 */

          if(s>=20) 
		    {
		     return(ERR_USB_UNKNOWN);
          	}
         //printf( "Ready ?\n" ); 正在转存   
		for ( s = 0; s < 10; s ++ )
		   {                       /*   对于检测到USB设备的,最多等待10*50mS  最长等待时间,10*50mS */
			mDelaymS( 50 );
			if ( CH376DiskMount( ) == USB_INT_SUCCESS ) 
				 break;  /* 初始化磁盘并测试磁盘是否就绪 */
		   }
        if(s>=10)
        	{
        	  return(s);
        	}
         
		
#if 0		
		s = CH376ReadBlock( buf );  /* 如果需要,可以读取数据块CH376_CMD_DATA.DiskMountInq,返回长度 */
		if ( s == sizeof( INQUIRY_DATA ) )
		{  /* U盘的厂商和产品信息 */
			buf[ s ] = 0;
			printf( "UdiskInfo: %s\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
		}
#endif
		s = CH376DirCreate( "/福建普华" );  /* 新建或者打开目录,该目录建在根目录下 */
		//if ( s == ERR_FOUND_NAME ) printf( "Found a file with same name\n" );
		//mStopIfError( s );
	
		CH376FileClose( FALSE );  /* 关闭目录 */
	   if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	{
    	 return(s);
    	}

/* 下面新建二级子目录 */
		
		strcpy( buf, "/福建普华/KD9001A" );  /* 目录名,该目录建在YEAR2008子目录下,YEAR2008目录必须事先存在,CH376DirCreatePath的文件名缓冲区必须在RAM中 */
      	s = CH376DirCreatePath( buf );  /* 新建或者打开目录,该目录建在多级目录下,输入路径必须在RAM中 */
	    if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	{
    	 return(s);
    	}
//		CH376FileClose( FALSE );  /* 暂时不关闭目录,因为下面要在这个新建或者打开的目录中新建文件 */

/* 目录新建或者打开成功,下面在这个子目录中新建一个演示文件,
   两种方法:一是CH376FileCreatePath新建多级目录下的文件,二是CH376FileCreate在当前目录下新建文件(如果前面打开了上级目录并且没有关闭) */
	

//		strcpy( buf, "/YEAR2008/MONTH05/DEMO2008.TXT" );  /* 文件名,该目录建在YEAR2008/MONTH05多级目录下,目录必须事先存在,CH376FileCreatePath的文件名缓冲区必须在RAM中 */
//		s = CH376FileCreatePath( buf );  /* 新建多级目录下的文件,如果文件已经存在则先删除后再新建,输入路径必须在RAM中 */


  
  
     {
        file_name(buf);
    //	s = CH376FileOpen( buf );  /* 打开文件,该文件在根目录下 */
	//	if ( s == USB_INT_SUCCESS )
	//		{  /* 文件存在并且已经被打开,移动文件指针到尾部以便添加数据 */
	//	 	 s = CH376ByteLocate( 0xFFFFFFFF );  /* 移到文件的尾部 */  /* 关闭目录 */
	//	    }
   //		else if ( s == ERR_MISS_FILE ) 
			{  /* 没有找到文件,必须新建文件 */
		   	  s = CH376FileCreate(buf);// NULL );  /* 新建文件并打开,如果文件已经存在则先删除后再新建,不必再提供文件名,刚才已经提供给CH376FileOpen */
			 
		    }
	
        
     }
}


	//	s = CH376FileCreate( buf );//("DEMO2009.TXT" );  /* 在当前目录下新建文件,如果文件已经存在则先删除后再新建 */
		if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	 {
    	   return(s);
    	 }
                //创建时间
     
     if(rx_flag==1)//  字节转存
       {
          uint8 i; 
          uint8  byte[pageLong ];
		  for(i=0;i<viewpage_nub;i++)
		  	{
		      uint16  address=VIEWsto_addr+i*pageLong;
		      readbyte_much( address,pageLong ,byte);
	       	  s = CH376ByteWrite(byte,pageLong , NULL ); 
	 	      if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	       {
             	 return(s);
    	       }
		  	}  
    	
       }

		
      
     
		else   // 扇区转存
		    {
		     //  SFRPAGE=CONFIG_PAGE;
	           s = CH376SecLocate( 0xFFFFFFFF );
			   if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	        {
    	         return(s);
    	        }
               s = CH376SecWrite( (uint8  *)0x00, (UINT8)(0x4200/DEF_SECTOR_SIZE), NULL );  
			  if(s==ERR_USB_UNKNOWN) 		//提示ch376 ok?
    	      {
    	       return(s);
    	       }
        	}
       	
		//printf( "Close\n" );转存结束
		{
		 time_type   time;
         read_time(&time);
	     SetFileCreateTime( CreateDate(&time), CreateTime(&time));//,buf );
		}
		s = CH376FileClose( TRUE );  /* 关闭文件,自动更新文件长度 */
		

		mDelaymS( 200 );
        return(succ_USB_KNOWN) ;
    
	}
// SFRPAGE=SFRPAGE_save;			 





