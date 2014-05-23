#include "file_ah9837.h"


 tBoolean    BIT_SEPER ;//������
 tBoolean    BIT_TEMPstation; //��������¶ȱ�־λ
 tBoolean    BIT_kp;    //�ı�kpֵ��־
 tBoolean    BIT_100S ; //��������ǰ200S��ʱ���ж�MIN����MAX
 tBoolean    BIT_WHset; //wh(wl)Ϊseth(setl)��־
 tBoolean    BIT_80kp ;   //seth(setl)����80��
 tBoolean    BIT_Tset ; //�����趨ֵ��־λ
 tBoolean    BIT_IHset ; //��������IH�趨ֵ��־λ
 
sint64    YN;
sint64    YN_init; 
sint16    EH ;//����ƫ��ֵEH;;3.0
sint16    UNH ;//--UNH����,��ǰ�¶�
sint16    WH ;//�ֶ��趨ֵ
sint16    KPH ;//����ϵ��
sint16    IH ;//����ϵ��
sint16    DH ;//  ;΢��ϵ��
sint16    ENH ;//EQU 39H;39H--ENH ;e(n)
sint16    EN_1H ;//EQU 3BH;3BH--EN_1H  ;e(n-1)
sint16    EN_2H ;//EQU 3DH;3DH--EN_2H  ;e(n-2)
sint16    YNH ;//EQU 3FH;3FH--YNH ;��ǰPID
sint16    IH2 ;//  ;���û��ַ������Ҫʹ�õĻ���ϵ��
sint16    OUTH ;//���ڼ���������
sint16    TFULLH ;//������������

sint16    SETH ;//�趨�¶�T��16�룩     90
sint16    NUB_MAX ;//�ۼƱ����ֵС�Ĵ�����30�Σ�1����
sint16    MAXH ;//����¶�(bcd��)
  

sint16    NUB_UP;//����20S���£�2S*10��
sint16    NUM_100S ;//��������ǰ200S��ʱ�����������




// ;pid----�ֶ�ϵ�� (2051---rom)

sint16    area_hotH ;//      ;ÿ��������һ��pid��ʼ��
sint16    transition_H   ;// equ 32h     ;�����²�
sint16    kp1_80H    ; //  ;80��ǰkp
sint16    kp2_81H  ;   //   ;80�Ⱥ�kp
sint16    T_kpH   ;//�ı�kp�ķֽ�seth-kp_du
sint16    area_morestrH ;//   ÿ������+ �����²�+1
  
#define T80  800    //80.0��
#define T01  10     //1.0��

enum{ETempup_flag,ETempdown_flag};
enum{E100S_no,E100S_yes};
enum{EmaxT_no,EmaxT_yes,};
enum{EIwork_no,EIwork_yes};
enum{EKPwork_no,EKPwork_yes};
enum{ESETwork_no,ESETwork_yes};
enum{ETseper_no,ETseper_yes};
enum{EIHwork_no,EIHwork_yes};


void Temp_account(void)
 {
   Resulttest.result[ET_result].word_F=(float)((sint32)Oiltempset.oilTemp-(sint32)T331.T0_331)/T331.Tk_331;
   UNH=(sint16)Resulttest.result[ET_result].word_F;
 //  DPRINTF(("Tu=%u, Tf=%f  \n",UNH,Resulttest.result[ET_result].word_F));
 }

void HOT_init(sint16 Temp)
{
  area_hotH=(sint16)(modify_k.H_k[EPIDarea_modify]);
  transition_H=(sint16)(modify_k.H_k[EPIDtransition_modify]);
  kp1_80H=(sint16)(modify_k.H_k[EPIDkp1_modify]);
  kp2_81H=(sint16)(modify_k.H_k[EPIDkp2_modify]);
  T_kpH=(sint16)(modify_k.H_k[EPIDTkp_modify]);
  YN_init=(sint64)(modify_k.H_k[EPIDY1_modify]);
  area_morestrH =area_hotH+transition_H+10;
 /* 
  DPRINTF(("T1=%u,  \n",area_hotH));
  DPRINTF(("T2=%u,  \n",transition_H));
  DPRINTF(("T3=%u,  \n", kp1_80H));
  DPRINTF(("T4=%u,  \n", kp2_81H));
  DPRINTF(("T5=%u,  \n",(uint32) YN_init));
  DPRINTF(("T6=%u,  \n", modify_k.H_k[EPIDY1_modify]));
  */
  
  BIT_IHset=EIHwork_no;
  NUM_100S=100;
  BIT_100S=E100S_no;
  BIT_TEMPstation=EmaxT_no;
  BIT_WHset=EIwork_no;
  BIT_80kp=EKPwork_no;
  BIT_Tset=ESETwork_no;
  BIT_SEPER=ETseper_no;
  SETH=Temp;
  if(SETH!=00)
   	{ 	 
   	
     if(SETH>T80)
     	{
     	 T_kpH=SETH-T_kpH;
		 BIT_80kp=EKPwork_yes;
		 BIT_kp=EKPwork_no;
     	}
	 else
	 	{
	 	 T_kpH=SETH;
		 BIT_80kp=EKPwork_no;
		 BIT_kp=EKPwork_yes;
	 	}

    }
  else
  	{
  	 BIT_kp=EKPwork_yes;
  	 T_kpH=SETH=0;
  	}
 // DPRINTF(("T6=%u,  \n", SETH));
}

void PID_init(void)
 {
    Temp_account();
    MAXH=UNH; 
	WH=UNH+area_hotH;
    if(WH>=SETH)
    	{
          BIT_WHset=ESETwork_yes;
		  WH=SETH;
  	    }
	else
		{
		 BIT_WHset=ESETwork_no; 
		}
	EH=30;    
	KPH=kp1_80H;   //5.000
	DH=0x64;       //0.1
	IH=0x08;       //0,008 
	YN=YN_init;
	EN_1H=0;
	EN_2H=0;
	
	
 }


uint16 pid_control(void)
 {

   // UNH=Oiltempset.oilTemp;
    if(BIT_80kp==EKPwork_yes)
    	{
          if(BIT_kp==EKPwork_no)
          	{
          	   if(UNH>T_kpH)
          	   	{
          	   	    WH=SETH;
          	   	    KPH=kp2_81H;
					IH=0x10  ;// 0.016
					YN=YN_init;
					EN_1H=0;
	                EN_2H=0;
					BIT_kp=EKPwork_yes;
					BIT_WHset=ESETwork_yes;
				//	 DPRINTF(("j1\n"));
					
          	   	}
			   else
			   	{
			   	 goto area_account;
			   	}
          	}
		  else 
		  	{
		  	  if(BIT_Tset==ESETwork_no)
                {
                  if(UNH>SETH)
               	    {
               	      KPH=kp1_80H;
					  IH=0x08; //0.008
					  YN=YN_init;
					  EN_1H=0;
					  EN_2H=0;
					  BIT_Tset=ESETwork_yes;
				//	   DPRINTF(("j2\n"));
               	    }
		  	  	}
		  	}
	   	}
    else
    	{
          area_account:
              if(WH>(UNH+area_morestrH))
              	{
              	 WH=UNH+area_hotH;
				 BIT_WHset=ESETwork_no;
              	}

			  else
			  	{
                  if(BIT_WHset==ESETwork_no)
                  	{
                  	  if((WH+transition_H)<UNH)
                  	  	{
                  	  	  WH=WH+area_hotH;
						  if(WH>SETH)
						  	{
						  	 WH=SETH;
						  	 BIT_WHset=ESETwork_yes;
						  	}
						   KPH=kp1_80H;
					       IH=0x08;
					       YN=YN_init;
					       EN_1H=0;
					       EN_2H=0;
				//		    DPRINTF(("j3\n"));
					   }
					}
                 }
		 }

	
	 if(BIT_100S==E100S_no)  
	 	{
	 	  if(UNH>MAXH)
	 	  	{
	 	  	  NUB_UP++;
			  if(NUB_UP>10)
			  	{
			  	  BIT_TEMPstation=ETempup_flag;
			  	}
			
	 	   	   MAXH=UNH;
			   NUB_MAX=0;
	 	   	}
		  else
		  	{
                if(BIT_TEMPstation==ETempdown_flag)
                	{
                	  MAXH=UNH;
                	}
				else
					{
					  NUB_MAX++;
					}
		  	}
	 	  
	 	}
   return(PID_account());
	
 }

uint16  PID_account(void)
{
    sint32 data_PI;
	sint32 data_PD;
    sint32 data_PP;
	//DPRINTF(("en0=%x,en1=%x, en2=%x\n",ENH,EN_1H,EN_2H));
    ENH=WH-UNH;
	if(ENH<0)
		{
		 BIT_SEPER=ETseper_yes;
		}
	if(abs(ENH)>EH)
		{
		  if(BIT_IHset==EIHwork_no)
		  	{
		  	 if(NUB_MAX==30)
		  	 	{
		  	 	 WH=SETH;
				 IH2=IH;
				 BIT_IHset=EIHwork_yes;
		  	 	}
			  else
			  	{
			  	  IH2=0;
			  	}
		  	}
		 
		 }
	 else 
		{
		 if(BIT_WHset==ESETwork_no)
		 	{
		 	  if(NUB_MAX==30)
		  	 	{
		  	 	 WH=SETH;
				 IH2=IH;
				 BIT_IHset=EIHwork_yes;
		  	 	}
			  else
			  	{
			  	  IH2=0;
			  	}
		 	}
		 	
         else
         	{
		     IH2=IH;
			 BIT_IHset=EIHwork_yes;
         	} 
		}  

	// DPRINTF(("En=%x,WH=%u  \n",ENH,WH)); 
	data_PI= ENH*IH2 ;
	data_PP=(ENH-EN_1H)*1000 ;  //1000=1.0
	data_PD=(ENH+EN_2H-2*EN_1H)*DH;
	
	EN_2H=EN_1H;
	
	EN_1H=ENH;
	
	YN+=(sint64)KPH*((sint64)data_PI+(sint64)data_PD+(sint64)data_PP);
	
	
	
    YNH=YN/(uint32)1000000;
	if(YNH<0)
		{
		 YNH=0;
		}
	else if(YNH>PID_PERIODIC)
		{
		 YNH=PID_PERIODIC;
		}

   // DPRINTF(("PI=%x,PP=%x, PD=%x\n",data_PI,data_PP,data_PD));
	//DPRINTF(("Y=%u,YN=%u\n",YNH,YN%(uint32)1000000));
    return(YNH);	
	

}





















