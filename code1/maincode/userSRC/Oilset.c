 #include "file_ah9837.h"

uint32 oidset()
 	{
 	   uint32 option=EStart_oil;
	   uint8 key=Keyset.keyEfficiency;
       oidset_mune();
       Reversepic(oilset_lin+option*oilset_high, oilset_column, mainset_high, 8);// ShowPicture(oilset_lin+option*oilset_high, oilset_column+10, Font1616,jian1);
	   while(1)
       	{
       	  while(key==Keyset.keyEfficiency);
		  key=Keyset.keyEfficiency;
		  switch(key)
       	  	{
     	      case key_no:			 
			  	       continue;
			  case key_back:
			  	       writebyte_much(0x1000,settype_nub,set.byte );//保存历史设置数据
			  	       return(0);
			  case key_oil:
			  	        Oilclear();//排油
						break;			 		   
			  case key_up:
              case key_down:
			  	        Reversepic(oilset_lin+option*oilset_high, oilset_column, mainset_high, 8);
			            option=keyoption_js(option, key, EStart_oil+1, Emune_key);
						Reversepic(oilset_lin+option*oilset_high, oilset_column, mainset_high, 8);
                        break;
			  case  key_ok:
			 	        if(option==EStart_oil)//开始测试
			 	        	{
			 	        	  uint16  Keytime;
			 	        	  writebyte_much(setsto_addr,settype_nub,set.byte );//保存历史设置数据
                              SysLinearTimer=0;
							  Coverset.Coverwork=ECover_Workon;//盖子判断
	                          while(SysLinearTimer<3*TIMER_FREQ)
                                  {
                                    key=Keyset.keyEfficiency;
                                    if(key==key_ok)
    	                               {
		                                 while(Keyset.keyEfficiency==key_ok); 
    	                                 Keytime++;
		                                 if(option>=5)
	       	                                {
	       	                                   Coverdispose();
			                                   Temp_control();//开始测试
											   break;
	   	                                     }
       	                               }                            
                                  }
							    Coverset.Coverwork=ECover_Workoff;
							  oidset_mune();//这里已经返回了
                              Reversepic(oilset_lin+option*oilset_high, oilset_column, mainset_high, 8);
			 	        	}
                        else
                        	{
						     oiltest_set(option);
                        	}
				      break;
	                     
       	  	}							   
       	}
 	}




uint8 oiltest_set(uint8 option)
{
  uint8 pam;
  uint8 key=Keyset.keyEfficiency;
  uint8 nubkey[5]={E2000Vac-E00Vac+1,EFre60_5-EFre50_0+1,E600Vdc-E00Vdc+1,E130T-E00T+1,ER_work-EAuto_work+1};
  uint8 key_zio[5]={E00Vac,EFre50_0,E00Vdc,E00T,EAuto_work};
  ShowPicture(oilset_lin+option*oilset_high, oilset_column+8, Font1616,jian1);
  pam=set.byte[option]-key_zio[option];
  
  while(1)
  {

	    while(key==Keyset.keyEfficiency);
		  key=Keyset.keyEfficiency;
      	  switch(key)
       	  	{
     	      case key_no:
			   	       continue;
			 
			  case key_oil:
			  	        Oilclear();
						break;

              case key_up:
              case key_down:
			  	         pam=keyoption_js(pam, key,nubkey[option], Emune_key);
                         set.byte[option]=pam+key_zio[option];
						 switch(option)
						 	{
						 	  case ETg_oil:
							         Vacdisplay();
									 break;
							  case ER_oil:
							  	    Vdcdisplay();
									break;
                              case EFre_oil:
							  	    Fredisplay();
									break;
							  case EWork_oil:
							  	    workdisplay();
									break;
							  case EHot_oil:
							  	    oiltempdisplay();
									break;
									 
						 	}
						 break;
			 case  key_ok:
			 	     
			 case key_back:
			  	       ShowPicture(oilset_lin+option*oilset_high, oilset_column+8, Font1616,kg);
			  	       return(0);
		   }				              

	}

 
}

 



uint8 clockset_mune()
 {
  uint8 key=Keyset.keyEfficiency;
  uint8 option;
  uint8 cloumn;
  uint8 lin;
  uint8  byte[12];
  read_time();
  
  Clock_viewxs( byte);

  option=0 ;
  cloumn=clockset_column;
  lin=clockset_line;
  OutPortCom1(0x09f);
  OutPortCom3( cloumn,lin/8+1,0x21);
  

  while(1)
   {
  
     while(key==Keyset.keyEfficiency);
	 key=Keyset.keyEfficiency;
     switch(key)
     {
       case 0x000: 
	   case key_oil:
	   	       continue;
       case key_up:
	   case key_down:
              byte[option]=keyoption_js(byte[option],key, 10,Edata_key);
			  ShowPicture(lin, cloumn,Font1608 ,0x10+byte[option]);
			  break;
       case key_back:
                     cloumn=10;
                     for(option=0x00;option<7;option++)
        	            {
        	               if(option!=0x03)
        	                	{
        	                	 time.byte[option]=(byte[cloumn]<<4)+(byte[cloumn+1]);
        	  	                 cloumn-=2;
        	  	                }
                    	}
				     time.time.second=0;
					 write_time()     ;
					 OutPortCom1(0x09d);
					 return(00);
       	    		
	   case key_ok:
              option++;
			  if(option>11)
			  	{
			  	 option=0;
			  	}
			 cloumn=(option/2*3+option%2+option/6+clockset_column);
			 OutPortCom3(cloumn,lin/8+1,0x21);
    	      break;
      
      }
 
    }


	
     
}

