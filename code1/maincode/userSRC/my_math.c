#include "file_ah9837.h"
void hex16_bcd4(uint16 xs_data,uint8 *byte,uint8 nub )
{
  uint8 i;	
  for(i=nub-1;i<nub;i--)
   	{
   	 byte[i]=xs_data%10;
	 xs_data/=10;
   	}
}


uint32  bcd_hex(uint32 ptbb)
{
  unsigned long int bb_first=00;
  unsigned long int bb_big;
  unsigned char i,k;
  bb_big=ptbb&0xffffff00  ;//&0xffffffff;
  for(i=00;i<8;i++)
          { 
    	      k=(bb_big>>28)&0x0f;
			  bb_first=((unsigned long int)k+bb_first)*10;   
			  bb_big= bb_big<<4;
           }

   return(bb_first);
	/*{
      float f_data;
	   switch (j)
    	{
    	 case 0:f_data=100000000.0;break;
    	 case 1:f_data=10000000.0;break;
		 case 2:f_data=1000000.0;break;
		 case 3:f_data=100000.0;break;
		 case 4:f_data=10000.0;break;
		 case 5:f_data=1000.0;break;
		 case 6:f_data=100.0;break;
		 default:f_data=10.0;break;
    	}
	
	 return((float)bb_first/f_data);
   	}*/
 }


//=============
/*
unsigned char bcd_hex(unsigned char i)
     {
       i=(i>>4)*10+(i&0x0f);
       return (i);
     }
 */
//=====================================


/*
unsigned long int bcd32_hex(unsigned char *modify_data,unsigned char k)
 {

  return(((unsigned long int)*(modify_data+k*3+0)<<24)+((unsigned long int)*(modify_data+k*3+1)<<16)+((unsigned long int)*(modify_data+k*3+2)<<8) ) ; 
 

}
*/
//==========
uint8 keyoption_js(uint8 option,uint8 key_temp,uint8 nub_key,uint8 mune_flag)
 {
     if(key_temp==key_down)
     	{
     	 mune_flag=(mune_flag!=Emune_key)?key_up:key_down;
     	}
	 else
	 {
       mune_flag=(mune_flag!=Emune_key)?key_up:key_down;
      } 
	 if(key_temp==mune_flag)
   	   {
   	     option++;
   	   }
        else
   	   {
   	    option--;
   	   }
		
    if(option>nub_key)
      {
   	   option=nub_key-1;
   	  }
    if(option==nub_key)
   	  {
   	   option=0x00;
   	  }
     return(option);	
  
 }


unsigned int bcd_hex2(unsigned int bcd_data)
 {
    bcd_data=((bcd_data>>12)&0x0f)*1000+
                    ((bcd_data>>8)&0x0f)*100+
                       ((bcd_data>>4)&0x0f)*10+
                                  (bcd_data&0x0f);
   return (bcd_data);
 }
//===============


/*
void hex2_bcd(uint8 *byte,uint16 uint_temp)
{
    unsigned char j;
	for(j=5;j>0;j--)
		{
		 byte[j]=uint_temp%10;
		 uint_temp=uint_temp/10;
		} 
	byte[0]=(unsigned char)uint_temp;
					 
}

void bcd4_xs(uint16 *parameter,uint8 *byte)
{
       
	  *(byte+0)=(*parameter>>12)&0x0f;
      *(byte+1)=(*parameter>>8)&0x0f;
	  *(byte+2)=(*parameter>>4)&0x0f;
	  *(byte+3)=(*parameter)&0x0f;
	
}
uint16 max_find(uint16 *group,uint8 nub)
  {
    uint16 max_data=0x00;
	uint8 i;
	for(i=0x00;i<nub;i++)
		{
		 if(group[i]>max_data)
		 	{
		 	 max_data=group[i];
		 	}
		}
	return(max_data)	;
   
  }

uint16 min_find(uint16 *group,uint8 nub)
  {
    uint16 min_data=0xffff;
	uint8 i;
	for(i=0x00;i<nub;i++)
		{
		 if(group[i]<min_data)
		 	{
		 	 min_data=group[i];
		 	}
		}
	return(min_data)	;
   
  }
*/

  
float float_js(unsigned long int ptbb)
{
 unsigned long int bb_first=00;
  unsigned char j=6;
  {
  	unsigned long int bb_big;
    unsigned char i,k;
    bb_big=ptbb&0xffffff00;
    for(i=00;i<6;i++)
          { 
    	      k=(bb_big>>28)&0x0f;
			  if(k==0x0a) 
			      j=i;
			  else 
			  	  {	
			        bb_first=((unsigned long int)k+bb_first)*10;   
			  	  }
			  bb_big= bb_big<<4;
        	}
   	}
	{
      float f_data;
	   switch (j)
    	{
    	 case 0:f_data=1000000.0;break;
    	 case 1:f_data=100000.0;break;
		 case 2:f_data=10000.0;break;
		 case 3:f_data=1000.0;break;
		 case 4:f_data=100.0;break;
		 default:f_data=10.0;
    	}
	
	 return((float)bb_first/f_data);
   	}
 }
  

