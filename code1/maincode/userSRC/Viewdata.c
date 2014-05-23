#include "file_ah9837.h"

void  ResultMune_display(void)
{
   if( set.mune.Vac !=E00Vac)
   	{
       charLine1208_const(Resulttest_lin ,Resulttest_column,char1208_TgA)	  ;
	   charLine1208_const(Resulttest_lin+Resulttest_high*1 ,Resulttest_column,char1208_Cx)	  ;
       charLine1208_const(Resulttest_lin+Resulttest_high*2 ,Resulttest_column,char1208_E)	  ;
	
	   if(set.mune.Vdc!=E00Vdc)
	   	{
	      charLine1208_const(Resulttest_lin+Resulttest_high*3 ,Resulttest_column,char1208_P)	  ;
	    }  
   	}
   else if( (set.mune.Vac ==E00Vac)&&(set.mune.Vdc !=E00Vdc))
   	{
   	   charLine1208_const(Resulttest_lin+Resulttest_high*1 ,Resulttest_column,char1208_Rx)	  ;
	   charLine1208_const(Resulttest_lin+Resulttest_high*2 ,Resulttest_column,char1208_P)	  ;
  	}
 
}

void  Resultcom_display(void)
{
  
       charLine1208_const(Resulttest_lin_com ,Resulttest_column,char1208_TgA)	  ;
	   charLine1208_const(Resulttest_lin_com+Resulttest_high*1 ,Resulttest_column,char1208_Cx)	  ;
	   TG_display(Resulttest_lin_com ,Resulttest_column+5,Resulttest.result[ETg_result].word_F);
	   Cx_display(Resulttest_lin_com+Resulttest_high*1 ,Resulttest_column+5,Resulttest.result[ECx_result].word_F);
 
}





void Resulttest_display( )
 {
   if( set.mune.Vac !=E00Vac)
   	{
   	   TG_display(Resulttest_lin ,Resulttest_column+5,Resulttest.result[ETg_result].word_F);
	   Cx_display(Resulttest_lin+Resulttest_high*1 ,Resulttest_column+5,Resulttest.result[ECx_result].word_F);
	  
	   E_display(Resulttest_lin+Resulttest_high*2 ,Resulttest_column+5,Resulttest.result[ECx_result].word_F/Resulttest.result[ECn_result].word_F);
      
	   if(set.mune.Vdc!=E00Vdc)
	   	{
	      P_display(Resulttest_lin+Resulttest_high*3 ,Resulttest_column+5,Resulttest.result[ERx_result].word_F*6.78,EASII_no);
	   	}  
   	}
   else if( (set.mune.Vac ==E00Vac)&&(set.mune.Vdc !=E00Vdc))
   	{
  	   Rx_display(Resulttest_lin+Resulttest_high*1 ,Resulttest_column+5,Resulttest.result[ERx_result].word_F,EASII_no);
	   P_display(Resulttest_lin+Resulttest_high*2 ,Resulttest_column+5,Resulttest.result[ERx_result].word_F*6.78,EASII_no);
   	}
  
 
 }



void xs_Ann(uint8 option,float dat)
 {
  uint32 i;
  char byte[10];
  sprintf(byte, "%8.7f\n", dat);
  for(i=0;i<10;i++)
  	{
  	 byte[i]-=0x20;
  	}
  charLine(Annwarn_lin+0x10*option, Annwarn_column,8, byte);
 }






uint8 float_xs(float xs_data,char *byte,uint8 flag)
{
   uint32 j;
   uint32 uion_address;
  if(xs_data>99999.0)
  	{
  	 xs_data=99999.0;
  	}
   else if(xs_data<-99999.0)
  	{
  	 xs_data=-99999.0 ;
  	}
   uion_address=6;
   sprintf(byte, "%6.3f\n", xs_data);
   if(byte[5]=='.')
         {
         	 byte[5]=' ';
         }
  	  for(j=0;j<6;j++)
		{
         
		
		 if(byte[j]==0x0a)
		 	{
		 	 uion_address=j;
		 	 for(;j<6;j++)
		 	 	{
		 	 	 if(flag==EASII_yes)
		 	 	    {
		 	 	     byte[j]=' ';
		 	 	    }
				 else
				 	{
				 	 byte[j]=11;
				 	}
		 	 	}
             break; 
		 	}
        //else 
		 if(flag!=EASII_yes)
		   {
		    switch(byte[j])
		     {
		      case ('.'):	
 		          byte[j]=10;
			      break;
		       case ('-'):

				  byte[j]=12;
			      break;
		       case (' '):		
		          byte[j]=11;
		           break;
		       default:
				 byte[j]=byte[j]-0x30;
				 break;

				 
		    }
		  }
		 else
		  {
		   byte[j]-=0x20;
		  }
		 
		 		 
       }
   return(uion_address);   
}


uint8 floatE_xs(float xs_data,char *byte,uint8 flag)
{
   uint32 j;
   uint32 uion_address;
 
   uion_address=12;
   sprintf(byte, "%e\n", xs_data);
   for(j=0;j<12;j++)
		{
         
		
		 if(byte[j]==0x0a)
		 	{
		 	 uion_address=j;
		 	 for(;j<12;j++)
		 	 	{
		 	 	 if(flag==EASII_yes)
		 	 	    {
		 	 	     byte[j]=' ';
		 	 	    }
				 else
				 	{
				 	 byte[j]=11;
				 	}
		 	 	}
             break; 
		 	}
        //else 
		 if(flag!=EASII_yes)
		   {
		    switch(byte[j])
		     {
		      case ('.'):	
 		          byte[j]=10;
			      break;
		       case ('-'):

				  byte[j]=12;
			      break;
		       case (' '):		
		          byte[j]=11;
		           break;
               case ('E'):
              case ('e'):		
		          byte[j]=29;
		           break;  
				 case ('+'):

				  byte[j]=31;
			      break;   
				   
		       default:
				 byte[j]=byte[j]-0x30;
				 break;
		    }
		  }
		 else
		  {
		   byte[j]-=0x20;
		  }
		 
		 		 
       }
   return(uion_address);   
}



void e_display(uint16 lin, uint8 column, float xsdata,uint8 flag)
{
  char byte[16];
 // uint8 uion_address;
  uint32 j,k;
 // uion_address=
  floatE_xs( xsdata,byte,EASII_no);
 
  for(j=0;j<4;j++)
  	{
  	  if(flag==EASII_yes)
  	  	{
  	  	 ShowPicture(lin, column+j, Font1608, byte[j]);
  	  	}
	  else
	  	{
	  	  ShowPicture(lin, column+j,Font1208 , byte[j]);
	  	}
   	}
  for(;j<16;j++)
  	{
      if(flag==EASII_yes)
      	{
      	 if((byte[j]=='E') ||(byte[j]=='e'))
      	 	{
      	 	 break;
      	 	}
      	}
	  else
	  	{
	  	  if((byte[j]==29) )
      	 	{
      	 	 break;
      	 	}
	  	}
	
  	}
  k=j+4;
  for(  ;j<k;j++)
  	{
  	  if(flag==EASII_yes)
  	  	{
  	  	 ShowPicture(lin, column+j-4, Font1608, byte[j]);
  	  	}
	  else
	  	{
	  	  ShowPicture(lin, column+j-4,Font1208 , byte[j]);
	  	}
  	}
     


 
}






void V_display(uint16 lin,uint8 column, float xsdata)
{ 
      char   sprintfbyte[8];
      uint8 uion_address;
	  
	  uion_address=float_xs( xsdata,&sprintfbyte[1],EASII_no);
	  sprintfbyte[0]=6;
      charLine1208(lin, column,  sprintfbyte);
	  ShowPicture(lin, column+uion_address*1,Font1608,'V'-0x20 );  
 
}



void TG_display(uint16 lin,uint8 column, float xsdata)
{ 
      char   sprintfbyte[8];
      uint8 uion_address;
	  
	  uion_address=float_xs( xsdata,&sprintfbyte[1],EASII_no);
	  sprintfbyte[0]=6;
      charLine1208(lin, column,  sprintfbyte);
	  ShowPicture(lin, column+uion_address*1,Font1608,'%'-0x20 );  
 
}

void Cx_display(uint16 lin,uint8 column, float xsdata)
  { 
      char     sprintfbyte[8];
      uint8 uion_address;
	  
	  uion_address=float_xs( xsdata,&sprintfbyte[1],EASII_no);
      sprintfbyte[0]=6;
      charLine1208(lin, column,  sprintfbyte);
	  ShowPicture(lin, column+uion_address,Font1608,'p'-0x20 );  
      ShowPicture(lin, column+uion_address+1,Font1608,'F'-0x20 );  
}


void E_display(uint16 lin,uint8 column, float xsdata)
	{ 
      char    sprintfbyte[8];
      //uint8 uion_address;	 uion_address=
	  
	  float_xs(xsdata,&sprintfbyte[1],EASII_no);
	  sprintfbyte[0]=6;
      charLine1208(lin, column,  sprintfbyte);
	
    }

void Rx_display(uint16 lin,uint8 column, float xsdata ,uint8 flag)
   {
      e_display( lin,  column,  xsdata, flag);
	  ShowPicture(lin, column+8,Font1208,20 );  
   
   }

void P_display(uint16 lin,uint8 column, float xsdata,uint8 flag)
   {
       e_display( lin,  column,  xsdata, flag);
	   ShowPicture(lin, column+8,Font1208,20 );  
	   ShowPicture(lin, column+9,Font1208,10 );  
	   ShowPicture(lin, column+10,Font1208,30 );  
   
   }


void Resulttest_sto()
 {
   uint8 page;
    uint16 addr;
   readbyte_much(VIEWnewpagesto_addr,1, &page);
   if(page>=viewpage_nub)
    	{
  	      page=0;
  	     }
   page++;
   addr=page*pageLong+VIEWsto_addr;
   writebyte_much( addr+SetRAMoffsets, settype_nub, set.byte);
   writebyte_much( addr+ResultRAMoffsets, 0x10,Resulttest.b_k);
   	{
     
	  read_time();
	  writebyte_much( addr+ClockRAMoffsets, 0x8,time.byte);
   	}	
   writebyte_much(VIEWnewpagesto_addr,1, &page);
 
 }


void ResultCOMtest_sto(  uint8 page,uint8 option)
 {
 
   uint16 addr;
  
   addr=page*pageLong+VIEWsto_addr;
   writebyte_much( addr+DataCompointRAMoffsets+option*DatapointLong, 0x10,Resulttest.b_k);
   option++ ;
   writebyte_much( addr+ComPointRAMoffsets, 1,&option);
   if(option==1)
	{
     
	  read_time();
	  writebyte_much( addr+ClockRAMoffsets, 0x8,time.byte);
	  writebyte_much( addr+SetRAMoffsets, settype_nub, set.byte);
	  writebyte_much(VIEWnewpagesto_addr,1, &page);
   	}	
 
 }






void STOdataxs(uint16 page)
  {
     uint16 addr=page*pageLong+VIEWsto_addr;
	 uint8 nub;
	 readbyte_much(addr+SetRAMoffsets, settype_nub, set.byte);
	 charLine1208_const(clockset_line,clockset_line+2,char1208_clock);		
	 readbyte_much(addr+ComPointRAMoffsets, 1, &nub);
	 nub--;
	     {
				 uint8   byte[12]; 
				 readbyte_much(addr+  ClockRAMoffsets, 7, time.byte);
				 Clock_viewxs(byte);
          }	

     readbyte_much( (addr+ResultRAMoffsets ),DatapointLong , Resulttest.b_k);
	 ResultMune_display();
	 Resulttest_display();
	
    }





 //view½çÃæ


uint8  Viewdata_Hander()
{
  uint8 page=0;
 
 fileset_go: 
   InitLCD();
  readbyte_much(VIEWnewpagesto_addr,1, &page);
  if(page>=viewpage_nub)
  	{
  	 page=0;
  	}

 
  STOdataxs(page);
  
  while (1)
    {
	  uint8	key_temp=Keyset.keyEfficiency;
	   	 
	   switch(key_temp)
           {
             case  key_oil:
              case 0x00:
			 	   continue;
		   
             case  key_up:
			 case  key_down:
                  		 page =keyoption_js(page,key_temp,viewpage_nub,Emune_key);
                         goto fileset_go;
									
			    
                    
		     case key_back:
			 	    return(0);
					 

		
				 
					
		    case  key_ok:
                     fileHander();
                     break;   
				 
              }
	  
	     
	     
    }

}



uint8 fileHander(void)

             	{
				  uint8 option=EUdisk_file;	
				  uint8	key_temp1;
				  ClearScreen_sector(ResultKEY_lin,ResultKEY_column,16,0x10) ;
                  ShowtextLine(ResultKEY_lin,ResultKEY_column+EUdisk_file*ResultKEY_width, text_Upan);
				  ShowtextLine(ResultKEY_lin,ResultKEY_column+EPrint_file*ResultKEY_width, text_dayin);
				  ShowtextLine(ResultKEY_lin,ResultKEY_column+EPcCom_file*ResultKEY_width, text_tongxun);
                  Reversepic(ResultKEY_lin,ResultKEY_column+option*ResultKEY_width, ResultKEY_high, 4);
				  while(1) 
				  	{
                      while(key_temp1==Keyset.keyEfficiency);
                      key_temp1=Keyset.keyEfficiency;
	   	              switch(key_temp1)
	   	              	{
	   	              	     case key_oil:
                             case 0x00:
							 	    continue;

                              case  key_up:
			                  case  key_down:
							  	          Reversepic(ResultKEY_lin,ResultKEY_column+option*ResultKEY_width, ResultKEY_high, 4);
                                          option=keyoption_js(option,key_temp1,3,Emune_key);
						                  Reversepic(ResultKEY_lin,ResultKEY_column+option*ResultKEY_width, ResultKEY_high, 4);
                                          break;
					
			
			                case key_ok:
			 	              switch(option)
			 		            {
                                  case EPrint_file:
								  	    print();
										break;
															  
			                      case EPcCom_file:
								
			                	  case EUdisk_file:

                                               USbdisk_hander(option);
                                                break;
									
				                 	    
				                        
			                        
		 	                      }
                                  break;
						  case key_back:
						  	       ClearScreen_sector(ResultKEY_lin,ResultKEY_column,16,0x10) ;
								   return(0);
								  

							  
	   	              	}
				  	   }
		 	                      
             		}
			     //break;

