#include "file_ah9837.h"




////////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------------------------------------*/
//��ʾһ���ַ���(����,��ĸ����,һ��16�ֽ�)
//lin:��
//lineheadaddr: ���к��ִ������׵�ַ
 /*void ShowLine(unsigned int lin,unsigned char column,unsigned char linehead[])
 {
 unsigned char i,j;
 unsigned char byte;
 unsigned int hzcode;

 for( i= column,j=0; i< column+14 ; )
 { byte=linehead[j];
 if(byte < 0x80) //��ĸ
 {
 ShowChar(lin, i , byte);
 i=i+1;j=j+1;
 }
 else // byte >= 0x80(����)
 {
byte=byte & 0x7f; //���λ��0,��:��ȥ0x8000
hzcode=byte*256 + linehead[j+1]; //�ӵ�8λ,��ϳ���������ַ
ShowHZ( lin,i,hzcode);
i=i+2;j=j+2;
}
}
}
//��ʾһ��(����,
//lin:��
//lineheadaddr: ���к��ִ������׵�ַ
//nubber   ��ʾ����    */

void ShowtextLine(unsigned int lin,unsigned char column, const unsigned char linehead[])
 {
    unsigned char i,j,nubber;
    unsigned int hzcode;
    nubber=linehead[0]+1  ;
    for( i= 1; i< nubber ;i++ )
     {
	   j=(column+i*2)-2;
       hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
       ShowPicture( lin,j, Font1616,hzcode);
     }
 }


void ShowtextLine1216(unsigned  int lin,unsigned char column, const unsigned char linehead[])
 {
    unsigned char i,j,nubber;
    unsigned int hzcode;
    nubber=linehead[0]+1  ;
    for( i= 1; i< nubber ;i++ )
     {
	   j=(column+i*2)-2;
       hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
       ShowPicture( lin,j, Font1612,hzcode);
     }
 }

/*---------------
//��ʾһ��(�ַ�
//lin:��
//lineheadaddr: ���к��ִ������׵�ַ
//nubber   ��ʾ����  */

 void charLine(unsigned  int lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
    for( i= 0; i< nubber ;i++ )
       {
         j=column+i;
         hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
          ShowPicture( lin,j, Font1608,hzcode);
       }
 }


 void charLineASCII(unsigned  int lin ,unsigned char column , const unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
	uint8 nubber;
	nubber=linehead[0]+1;
    for( i= 1; i< nubber ;i++ )
       {
         j=column+i-1;
         hzcode= linehead[i]-0x20; //�ӵ�8λ,��ϳ���������ַ
         ShowPicture( lin,j, Font1608,hzcode);
       }
 }

//========================
 void charLine8(unsigned  int lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
    for( i= 0; i< nubber ;i++ )
       {
         j=column+i;
         hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
         ShowPicture( lin,j, Font0808,hzcode);
       }
 }
//=========================
void  ShowPixel( unsigned  int StartlinPixel,unsigned char StartcolumnPixel,const unsigned char *adddd,uint8 nub)
 {
   uint8 xsdata;
   uint8 i,j;	
   uint8 Mode;
   unsigned char LineWidth=*adddd++;
   unsigned char ColumnWidth=*adddd++;
  
   adddd+=LineWidth*((ColumnWidth+4)/8 )*nub;
  
   for(i=0;i<LineWidth;i++)
     {
       xsdata=*adddd++; //set address
      
       for(j=0;j<ColumnWidth;j++)
         {
           Mode=(xsdata&0x80);
           Pixel(StartlinPixel, StartcolumnPixel+j,  Mode)	;
		   xsdata<<=1;
         }
	    StartlinPixel++;
     
     }
 }


/*

 void charLine0806(unsigned int linPixel ,unsigned char columnPixel ,unsigned char nubber,unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
    for( i= 0; i< nubber ;i++ )
       {
         j=columnPixel+i*6;
         hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
         ShowPixel( linPixel,j, Font0806,hzcode);
       }
 }



//================================

 void charLine1621(unsigned int lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
    for( i= 0; i< nubber ;i++ )
       {
         j=column+i*2;
         hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
         ShowPicture( lin,j,ASCII1621,hzcode);
       }
 }
*/

 void charLine1208_const(unsigned  int lin ,unsigned char column , const unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
	uint8 nubber;
	nubber=linehead[0]+1;
    for( i= 1; i< nubber ;i++ )
       {
         j=column+i-1;
         hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
         ShowPicture( lin,j,Font1208,hzcode);
       }
 }


//====
 void charLine1208(unsigned  int lin ,unsigned char column , char linehead[])
 {
    unsigned char i,j;
    char hzcode;
	uint8 nubber;
	nubber=linehead[0]+1;
    for( i= 1; i< nubber ;i++ )
       {
         j=column+i-1;
         hzcode= linehead[i]; //�ӵ�8λ,��ϳ���������ַ
         ShowPicture( lin,j,Font1208,hzcode);
       }
 }


//----------------------------------------------------------------------------------------
/*
 void charLine35(unsigned uint16 lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[])
 {
    unsigned char i,j;
    unsigned char hzcode;
    for( i= 0; i< nubber ;i++ )
	  {
	     j=column+3*i;
		 hzcode= linehead[i];        //�ӵ�8λ,��ϳ���������ַ
         ShowChar35(lin,j,hzcode);
	   }
 }
*/
//-----------------------------------------------------------------------------------
//��ʾһ������
//pageheadaddr:�������ִ����ַ���׵�ַ
/*void ShowPage(unsigned char lin,unsigned char column1,unsigned char pagehead[][14])
{
unsigned char i;
for(i=0;i< 4 ;i++)
 {}//ShowLine((lin+i*20),column1,pagehead[i]); //1��8������,16�ֽ�
}
*/

//����һ���ַ�
//lin:��(0-7), column: ��(0-15)

void Reversepic(unsigned  int lin,unsigned char column,unsigned char high,unsigned char width)
{
       unsigned char dat,i,j;
       unsigned int StartAddr;
       StartAddr=lin*LineChar +column+0X800; //��λ��ʼ��
       for(i=0;i<high;i++)
         {
            OutPortCom3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24);
            for(j=0;j<width;j++)
             {
               OutPortCom1( 0xc5 ); //����һ�ζ�����ַ����
               dat=InPortData(); //��������
               dat=~dat; //ȡ��
               OutPortCom2( dat,0xc0); //�ͻ�
             }
           StartAddr=StartAddr+ LineChar;
         }
}



//����һ������
/*
lin:��(0-7), column: ��(0-15)
void ReverseShowHZ(unsigned uint16 lin,unsigned char column)
{
ReverseShowChar(lin,column);
ReverseShowChar(lin,column+1);
}
//lin:��(0-7)
void ReverseShowLine(unsigned uint16 lin)
{
unsigned char column;
for(column=0; column< ColumnChar; column++) ReverseShowChar(lin,column);
} 
*/
void ShowPicture(unsigned  int Startline,unsigned char Startcolumn, const unsigned char *adddd,uint8 nub)
{
   unsigned char i,j;
   unsigned int StartAddr;
   unsigned char LineWidth=*adddd++;
   unsigned char ColumnWidth=(4+(*adddd++))/8;
   adddd+=LineWidth*ColumnWidth*nub;
   StartAddr=Startline*LineChar + Startcolumn+0X0800; //��λ��ʼλ��
   for(i=0;i<LineWidth;i++)
     {
	   OutPortCom3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24); //set address
       for(j=0;j<ColumnWidth;j++)
         {
           OutPortCom2 (*adddd,0xc0);           //FJPH[i*LineWidth+j]
           adddd++;
         }
       StartAddr=StartAddr + LineChar;
     }
}

//////////////////////////////////////////////////////////////////////////////////////
/*
void ShowPicture(unsigned  int Startline,unsigned char Startcolumn,unsigned char LineWidth,unsigned char ColumnWidth,unsigned char *adddd)
{
   unsigned char i,j;
   unsigned int StartAddr;
   unsigned char i,j;
   StartAddr=Startline*LineChar + Startcolumn+0X0800; //��λ��ʼλ��
   
   for(i=0;i<ColumnWidth;i++)
     {
	   OutPortCom3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24); //set address
       for(j=0;j<LineWidth;j++)
         {
           OutPortCom2 (*adddd,0xc0);           //FJPH[i*LineWidth+j]
           adddd++;
         }
       StartAddr=StartAddr + LineChar;
     }
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//ͼ�κ���,������㻭ͼ
//---------------------------------------------------------------------------
//��ָ��λ����ʾһ����
//�����ʾ��������256*256,���޸�������� PointX,PointY������
//Mode 1:��ʾ 0:����õ�
void Pixel(unsigned  int PointY,unsigned char PointX,uint8 Mode)
{
unsigned int StartAddr=0;
unsigned char dat;


StartAddr=PointY*LineChar + PointX/8+0x0800;
dat=0xf0+7-PointX%8;
if(Mode) dat=dat|0x08;

OutPortCom3( (unsigned char)(StartAddr),(unsigned char)(StartAddr>>8),0x24 ); //���øõ����ڵ�Ԫ��ַ
OutPortCom1(dat);
}
//=============
void y_line(unsigned  int y1, unsigned char x1, unsigned  int y2, uint8 Mode)
  { 

    if(abs(y2-y1)>1)
    {if(y1<y2)
        {
         for(y1++;y1<y2;y1++)
            Pixel(y1, x1,  Mode)	 ;
         }
     else 
	 	{
	 	 for(y2++;y2<y1;y2++)
		 	 Pixel(y2, x1, Mode)  ;
		}
    } 
  } 
//=========
void x_line(unsigned  int y1, unsigned char x1, unsigned char x2, uint8 Mode)
 { 
    if(abs(x2-x1)>1)
   {
    if(x1<x2)
        {
         for(x1++;x1<x2;x1++)
            Pixel(y1, x1, Mode)	   ;
         }
     else 
	 	{
	 	 for(x2++;x2<x1;x2++)
		 	 Pixel(y1, x2, Mode)	;
		}
   }	 
  } 
//-------------------------------------------------------------------------------

//���ߺ���(�з���)
void Line( unsigned  int y1, unsigned char x1, unsigned  int y2, unsigned char x2,  uint8 Mode)
{
  unsigned char x,y,z;
  float k,b;
 if(x1==x2)
 	 y_line(y1,x1, y2,  Mode);
   else if(y1==y2)
 	   x_line(y1,x1, x2,  Mode);
    else
       {   
          z=0;
         	{
			 signed int y_f,x_f;
			 y_f=(signed int)y2-(signed int)y1;	
			 x_f=(signed int)x2-(signed int)x1;
			 if( abs(y_f)< abs(x_f) ) // |k|<=1
             z=1;
		    }	
        if( z==1 ) // |k|<=1
          { 
            {
			 signed int y_f,x_f;
			 y_f=(signed int)y2-(signed int)y1;	
			 x_f=(signed int)x2-(signed int)x1;	 
             k=(float)(y_f) / (float)(x_f) ;
             b=(float)y1-k*(float)x1;
        	}
           if( x1 < x2 )
            { 
                z=y1;
                for(x=x1+1;x<x2;x++)
               {
                 y=(unsigned char)(k*(float)x+b);
                 Pixel(y, x, Mode);
		         y_line(y,  x, z, Mode);
		         z=y;
               }
            }

         else 	
            {
              z=y2;
              for(x=x2+1;x<x1;x++)
             {
             y=(unsigned char)(k*(float)x+b);
              Pixel(y, x, Mode);
		      y_line(y,  x, z, Mode);
		      z=y;
             }
           }
		   
         }
    else // abs(y1-y2) < abs(x1-x2) |K|>1
       { 
        {
         signed int y_f,x_f;
		 y_f=(signed int)y2-(signed int)y1;	
		 x_f=(signed int)x2-(signed int)x1;	 
         k=(float)x_f / (float)y_f ;
         b=(float)x1-k*(float)y1;
         }
         if( y1 <= y2 )
           {
            z=x1;
            for(y=y1+1;y<y2;y++)
             {
                x=(unsigned char)(k*(float)y+b);
                Pixel( y , x,Mode );
		        x_line(y,  x, z, Mode);
		  	    z=x;
		     }
           }
         else
            {
               z=x2;
               for(y=y2+1;y<y1;y++)
              {
              x=(unsigned char)(k*(float)y+b);
              Pixel( y, x,Mode );
	          x_line(y,  x, z,Mode);
		      z=x;
              }
            }
       
      }
   }
}

void ClearScreen_sector(unsigned  int Startlin,unsigned char Startcolumn,unsigned  int LineWidth,unsigned char ColumnWidth)
{
  unsigned char i,j;	  ///////// ����ʾ RAM �� 0000h--2000h (8k)
  unsigned int StartAddr;
  StartAddr=Startlin*LineChar +0x0800+Startcolumn;
  OutPortCom3((unsigned char)(StartAddr), (unsigned char)(StartAddr>>8),0x24); //����ָ���ַ0000H
  for(i=0;i<LineWidth;i++)
     {
	   OutPortCom3( (unsigned char)(StartAddr), (unsigned char)(StartAddr>>8), 0x24); //set address
       for(j=0;j<ColumnWidth;j++)
         {
           OutPortCom2 (0x00,0xc0);           //FJPH[i*LineWidth+j]
         }
       StartAddr=StartAddr + LineChar;
     }
}

/*---------------------------------------------------------------------------------------------------*/
void ClearScreen()
{
  unsigned int i;	  ///////// ����ʾ RAM �� 0000h--2000h (8k)
  OutPortCom3(0x00,0x00,0x24); //����ָ���ַ0000H
  OutPortCom1(0xb0); //�����Զ�д״̬
  for(i=0x00;i<0x4800;i++) OutPortData(0x00); // data=0;
      OutPortCom1(0xb2); // �Զ�д����
}

//��ʼ��LCD
//��Ҫ�ֶ�����
void InitLCD()
{
   OutPortCom3( 0x00,0x00,0x40 ); //����ͼ����ʾ�����׵�ַGraphAddr 
   OutPortCom3(LineChar,0x00,0x41 ); //����ͼ����ʾ������ : LineChar
   OutPortCom3( 0x00,0x08,0x42 ); //����ͼ����ʾ�����׵�ַGraphAddr
   OutPortCom3( LineChar,0x00,0x43); //����ͼ����ʾ������:10H
   OutPortCom1(0xa5); //���ù����״ cursor size 8x8
   OutPortCom1(0x80); //������ʾ��ʽ: CGROM��ʽ �ı�\ͼ�� "��"
   OutPortCom1(0x9c); //������ʾ����: 1001 1100 ͼ��
   ClearScreen();
}
//============================
void pane( unsigned  int Start_py,uint8 Start_px,unsigned  int Stop_py,uint8 Stop_px)
 {
  Line(Start_py,Start_px,Start_py, Stop_px,1); //left
  Line(Stop_py,Start_px,Stop_py, Stop_px,1); //right
  Line(Start_py,Start_px,Stop_py, Start_px,1); //high
  Line(Start_py,Stop_px,Stop_py, Stop_px,1); //low
 }

void panemore(unsigned  int Start_py,uint8 Start_px,unsigned  int Stop_py,uint8 Stop_px,uint8 width)
 {
  uint8 i;
  for(i=0x00;i<width;i++)
  	{
     pane(Start_py+i,Start_px+i,Stop_py-i, Stop_px-i);
  	}
 }


void Showpoint(unsigned  int PointY,unsigned char PointX,uint8 Mode)
 {
   uint8 y,x;
   PointY-=1;
   PointX-=1;
   for(y=0;y<3;y++)
   	{
   	 for(x=0;x<3;x++)
      {
       Pixel(PointY+y, PointX+x,  Mode)	 ;
   	  }
   	} 
   Pixel(PointY+1, PointX+1,  !Mode)	 ;
 }

/*
//��˫�ֽ���ʾ
void float_xs(unsigned char lin ,unsigned char column,float xs_data,bit xs_8,bit xs_4)
{ 
   unsigned char byte[6]={0,0,0,0,0,0};
   unsigned char pixel_0;
  
   sprintf (byte, "%4.4f\n", xs_data);
   {
   	unsigned char j;
	 pixel_0=0x00;
	for(j=0;j<6;j++)
		{
		 byte[j]=byte[j]-0x30;
         switch(byte[j])
		   {
		    case (0x2e-0x30):	
                { 
					unsigned char k;
                 	if(j!=5)
					{
					pixel_0=j;
					for(k=j;k<5;k++)
						{
						 byte[k]=byte[k+1];
						}

					}
				   byte[j]=byte[j]-0x30;
		    	}	
				break;
		    case (0x20-0x30) :
		         byte[j]=13;
		         break;
	        default: break;
		 }
       }
	
	byte[5]=xs_4? 5:4;
   	
	 if(xs_8)
    	{
	      charLine(lin,column,byte[5],byte) ;
		  if(pixel_0!=0x00)
		  	{
		  	 Pixel(0x00, (column+pixel_0)*8, lin+15, 1);
		  	}
		  
    	}
	else 	  
        {
	      charLine8(lin,column,byte[5],byte) ;
	    if(pixel_0!=0x00)
		 {
		  Pixel(0x00, (column+pixel_0)*8, lin+7, 1);
		 }
    	}
   }
 
}	

 

void uint16_bcd4xs(unsigned char lin ,unsigned char column,unsigned int  uint_temp,bit xs_8)
{ 
   unsigned char byte[4]={0,0,0,0};
   unsigned char j;
	for(j=3;j>0;j--)
		{
		 byte[j]=uint_temp%10;
		 uint_temp=uint_temp/10;
		} 
	byte[0]=(unsigned char)uint_temp;
	if(byte[0]==0x00)
		{
		 byte[0]=13;
		 if(byte[1]==0x00)
		 	{
		     byte[1]=13;
		 	} 
		}
  
    if(xs_8)
    	{
	      charLine(lin,column,4,byte) ;
    	}
	else 	  
        {
	      charLine8(lin,column,4,byte) ;
    	}
}	

	  */




	  /*
	  unsigned char j;
	  unsigned char byte[6]={0,0,0,0,0,0};
	  unsigned long int int_data;
	  xs_data*=100;
	     if(xs_data<0.000000001)
		 	 ShowChar(lin,column-1,12);
		  else 
		  	 ShowChar(lin,column-1,13);
	  int_data=(unsigned long int)(fabs(xs_data)) ;
	  for(j=5;j>0;j--)
	    {
	     byte[j]=int_data%10;
	     int_data=int_data/10;
      	}
	  byte[0]=int_data%10;
	  for(j=0;j<3;j++)
	    {
	    if(byte[j]==0)
   	       byte[j]=13 ;
		 else j=06;
		} 				   
               charLine(lin,column,4,byte) ;
	           ShowChar(lin,column+4,10);
	           ShowChar(lin,column+5,byte[4]);
	           ShowChar(lin,column+6,byte[5]);	
	}
	   */        
 /*   
bcd_hex(unsigned char i)
	  	{
	  	}
   */
