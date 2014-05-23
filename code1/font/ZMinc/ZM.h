extern  const unsigned char  Font1616[];
extern  const unsigned char  Font0808[];
extern  const unsigned char  Font1608[];
extern  const unsigned char  Font1208[];
extern  const unsigned char  Font1612[];

  /*       0 ,      1 ,         2      3,      4,      5 ,       6,       7,        8,         9*/   
enum{   jie,      sun,         kai,   te,     dian,    qi,     you,     rong,     ya,        gao,   //00�����ص�������ѹ��
        duan,     lu,          guo,   biao,   zhun,    wu   ,  xin,     hao,      ce,        liang, //01��·����׼���źŲ���
        zheng,    zai,         wen,   zi,     dong,    shou,   tong,    fang,     shi,       ti,    //02�������Զ���ͨ��ʽ��
        ji ,      zu,          lv,    zhi,    hao1,    fan,    chong,   ding,     jia,       re,    //03�������ʺķų䶨����
        qi1,       xi,         tong1,  gu,     zhang,   heng,   zhong,   kai1,    guan,      tiao,  //04��ϵͳ���Ϻ��п��ص�
        zheng1,   shi1,        zhong1, wan,    cheng,   she,    zhi1,    cha,     jie1,       xian, //05��ʱ��������ò����
        qing,     gai,         shang, zi1,    hou,     ji1,    xu,      bu,       ti1,       shi2,  //06������Ӻ��������ʾ
        yun,      xing,        kong,  bei,    yi,      da,     yu,      fu,       wei,       chong1,//07���пձ��˴��ڸ�λ��
        xin1,      tai,         an,    jian,   zai1,    xuan,   ze,      pu,      hua,       ke,    //08��̫������ѡ���ջ���
        ji2,      jian1,       kg  ,  li,     shi3 ,   shu,    ju,      w90,      yu1,       yan,   //09����  ��ʷ����w90����
        wen1,     yang,        bian,  jiao,    zhi2,   liu,    pin,     shi4,     En,        li1,   //10�����ֱཻ��Ƶ��enli
        gh,       yi1,         qi2 ,  U   ,    pan,    xun,    da1,      yin,     zhuan,     cun,   //11gh����U ��Ѷ��ӡת��
        shi5,     bai,         di,    fan1,    hui,//ʧ�ܵط���  
  	};


extern const uint8 text_dayin[ ];//={2,shou,dong};//��ӡ
extern const uint8 text_Upan[ ];//={2,tong,xin};//U��
extern const uint8 text_tongxun[ ];//={2,kong,bei};//ͨѶ
extern const  uint8 * fileset_p[];//={ text_dayin,text_Upan,text_tongxun};


extern const uint8 text_zhuancun[ ];//={2,zhuan,cun};//ת��
extern const uint8 text_wancheng[ ];//={2,wan,cheng};//���
extern const uint8 text_shibai[ ];//={2,shi5,bai};//ʧ��
extern const  uint8 *Udisk_p[];//={text_zhuancun,text_wancheng,text_shibai};




extern const uint8 text_phkj[ ];//={4,pu,hua,ke,ji};//�ջ��Ƽ�
extern const uint8 text_ktdq[ ];//={4,ke,te,dian,qi};//���ص���
extern const  uint8 *  company_p[];//={ text_phkj, text_ktdq};

extern const uint8 text_dyxz[ ];//={4,dian,ya,xuan,ze};//��ѹѡ��
extern const uint8 text_clfs[ ];//={4,ce,liang,fang,shi};//������ʽ
extern const uint8 text_lssj[ ];//={4,li,shi3,shu,ju};//��ʷ����
extern const uint8 *  mainset_p[];//={text_dyxz,text_clfs,text_yysz,text_lssj};
extern const  unsigned char char_clock[ ];//={16,'-',' ',' ','-',' ',' ',' ',' ',' ',' ',':',' ',' ',':',' ',' ',':'};  

extern const uint8 text_yjzsh[ ];//={5,you,jie,zhi,sun,hao};//�ͽ������
extern const uint8 text_tjdzl[ ];//={5,ti,ji,dian,zu,lv};//���������
extern const uint8 text_jrqd[ ];//={4,jia,re,qi,dong};//��������
extern const uint8 text_ywsd[ ];//={4,you,wen,she,ding};//�����趨
extern const uint8 text_jldy[ ];//={4,jiao,liu, dian,ya};//������ѹ
extern const uint8 text_jlpl[ ];//={4,jiao,liu, pin,lv};//����Ƶ��
extern const uint8 text_zldy[ ];//={4,zhi2,liu,dian,ya};//ֱ������ѹ
extern const uint8 text_kbdr[ ];//={4,kong,bei,dian,rong};//�ձ�����
extern const uint8 text_tzsz[ ];//={4,tiao,zheng,shi,zhong };//����ʱ��
extern const uint8 text_yuyan[ ];//={2,yu1,yan};//����
extern const uint8 text_fanhui[ ];//={2,fan1,hui};//����
extern const uint8 text_zhongwen[ ];//={2,zhong,wen1};//����
extern const uint8 text_enligh[ ];//={2,En,li1,gh};//����
extern const  uint8 *Lanset_p[];//={text_zhongwen,text_enligh};
extern const uint8 text_guan[ ];//={3,kg,guan,kg};//��
extern const uint8 *  oilset_p[];//={text_yjzsh,text_tjdzl,text_jrqd,text_ywsd,text_kbdr,text_tzsz, text_yuyan};

extern const uint8 text_aqdjwcsz[ ];//={8,an,qi,dong,jian,wan,cheng,she,zhi};//���������������


extern const uint8 text_zidong[ ];//={2,zi,dong};//�Զ�
extern const uint8 text_shoudong[ ];//={2,shou,dong};//�ֶ�
extern const uint8 text_tongxun[ ];//={2,tong,xin};//ͨ��
extern const  uint8 * workset_p[];//={text_zidong,text_shoudong,text_tongxun};


extern const uint8 char_50hz[ ];//={4,'5','0','H','Z'};//50hz
extern const uint8 char_60hz[ ];//={4,'6','0','H','Z'};//60hz
extern const uint8 * Fre_p[];//={char_50hz,char_60hz};



extern const uint8 text_zdcl[ ];//={4,zi,dong,ce,liang};//�Զ�����
extern const uint8 text_sdcl[ ];//={4,shou,kg,kg,dong};//��  ��
extern const uint8 text_zztx[ ];//={4,zheng,zai,tong,xin,};//����ͨѶ
extern const  uint8 * workdisplay_p[];//={text_zdcl,text_sdcl,text_zztx};


extern const uint8 text_jiesun[ ];//={2,jie,sun};//����
extern const uint8 text_dianrong[ ];//={2,dian,rong};//����
extern const uint8 text_jiedian[ ];//={2,jie,dian,};//���
extern const uint8 text_dzl[ ];//={3,dian,zu,lv};//������




extern const uint8 text_youwen[ ];//={2,you,wen};//����
extern const uint8 text_guoya[ ];//={4,guo,kg,kg,ya};//��ѹ
extern const uint8 text_gydl[ ];//={4,gao,ya,duan,lu};//��ѹ��·
extern const uint8 text_jrxtgz[ ];//={6,jia,re,xi,tong,gu,zhang};// ����ϵͳ����
extern const uint8 text_xhxtgz[ ];//={6,xin,hao,xi,tong,gu,zhang};//�ź�ϵͳ����
extern const uint8 text_jyxtgz[ ];//={6,jia,ya,xi,tong1,gu,zhang}; //��ѹϵͳ����

extern  const uint8 text_jsdxjxyx[ ];//={8,jie,shang,di,xian,ji,xu,yun,xing};//���ϵ��߼�������
extern const uint8 text_gsgzjxyx[ ];//={8,gai,shang,gai,zi,ji,xu,yun,xing};//���ϸ��Ӽ�������
extern const uint8 text_aqdjbzts[ ];//={8,an,qi,dong,jian,bu,zai,ti,shi};//��������������ʾ


extern const uint8 text_zhwz[ ];//={4,zai,heng,wen,zhong};//�ں�����
extern const uint8 text_zzjr[ ];//={4,zheng,zai,jia,re};//���ڼ���
extern const uint8 text_cjx[ ];//={4,cha,jie,xian,kg};//�����

extern const uint8 text_qcybjx[ ];//={6,qing,cha,you,bei,jie,xian};//����ͱ�����
extern const uint8 text_aqdjjxyx[ ];//={8,an,qi,dong,jian,ji,xu,yun,xing};//����������������


extern const uint8 text_kbjr[ ];//={4,kong,bei,jia,re};//�ձ�����
extern const uint8 text_ywbdy90[ ];//={7,you,wen,bu,yi,da,yu,90,};//�¶Ȳ��˴���90
extern const uint8 text_afwjcxsz[ ];//={8,an,fu,wei,jian,chong,xin,she,zhi};//����λ����������



extern const uint8 text_zzcd[ ];//={4,zheng,zai,fang,dian,};//���ڷŵ�
extern const uint8 text_zzfd[ ];//={4,zheng,zai,chong,dian};//���ڳ��
extern const uint8 text_bzwxh[ ];//={5,biao,zhun,wu,xin,hao};//��׼���ź�
extern const uint8 text_clwxh[ ];//={5,ce,liang,wu,xin,hao};//�������ź�
extern const uint8 text_zzcl[ ];//={zheng,zai,ce,liang};//���ڲ���
extern const uint8 text_bzwxh[ ];//={5,biao,zhun,xin,hao,da};//��׼�źŴ�
extern const uint8 text_clwxh[ ];//={5,ce,liang,xin,hao,da};//�����źŴ�

extern const  uint8 *TgcStation_p[];//={text_zzcl,text_bzwxh,text_clwxh,text_bzwxh,text_clwxh};



extern const uint8 char_T[ ] ;//={3,'T',' ','='};//60hz
extern const uint8 char_TgA[ ] ;//={4,'T','g ',0x86,'='};
extern const uint8 char_Cx[ ] ;//={4,' ','C','x','='};
extern const uint8 char_E[ ] ;//={4,' ',' ',0x84,'='};
extern const uint8 char_Rx[ ] ;//={4,' ','R','x','='};
extern const uint8 char_P[ ] ;//={4,' ',' ',0x85,'='};


extern const uint8 char1208_clock[ ];//={11,11,15,11,11,15,11,11,11,11,11,11,16,11,11}; 
extern const uint8 char1208_TgA[ ];//={4,25,26,22,19};
extern const uint8 char1208_Cx[ ];//={4,11,27,24,19};
extern const uint8 char1208_E[ ];//={4,11,11,21,19};
extern const uint8 char1208_Rx[ ];//={4,11,23,24,19};
extern const uint8 char1208_P[ ];//={4,11,11,22,19};

extern const uint8 text12_up[ ];//={2,0,1};//u��
extern const uint8 text12_tx[ ];//={2,2,3};//ͨѶ
extern const unsigned char text12_fh[];//	=	{2,10,11};	//����
extern const uint8  text12_zc[ ];//={2,6,7};//ת��
extern const uint8  text12_wc[ ];//={2,8,9};//���
extern const uint8  text12_sb[ ];//={2,4,5};//ʧ��
		

