extern  const unsigned char  Font1616[];
extern  const unsigned char  Font0808[];
extern  const unsigned char  Font1608[];
extern  const unsigned char  Font1208[];
extern  const unsigned char  Font1612[];

  /*       0 ,      1 ,         2      3,      4,      5 ,       6,       7,        8,         9*/   
enum{   jie,      sun,         kai,   te,     dian,    qi,     you,     rong,     ya,        gao,   //00介损凯特电气油容压高
        duan,     lu,          guo,   biao,   zhun,    wu   ,  xin,     hao,      ce,        liang, //01短路过标准无信号测量
        zheng,    zai,         wen,   zi,     dong,    shou,   tong,    fang,     shi,       ti,    //02正在温自动手通方式体
        ji ,      zu,          lv,    zhi,    hao1,    fan,    chong,   ding,     jia,       re,    //03积阻率质耗放充定加热
        qi1,       xi,         tong1,  gu,     zhang,   heng,   zhong,   kai1,    guan,      tiao,  //04启系统故障恒中开关调
        zheng1,   shi1,        zhong1, wan,    cheng,   she,    zhi1,    cha,     jie1,       xian, //05整时钟完成设置查接线
        qing,     gai,         shang, zi1,    hou,     ji1,    xu,      bu,       ti1,       shi2,  //06请盖上子后继续不提示
        yun,      xing,        kong,  bei,    yi,      da,     yu,      fu,       wei,       chong1,//07运行空杯宜大于复位重
        xin1,      tai,         an,    jian,   zai1,    xuan,   ze,      pu,      hua,       ke,    //08新太按键再选择普华科
        ji2,      jian1,       kg  ,  li,     shi3 ,   shu,    ju,      w90,      yu1,       yan,   //09技箭  历史数据w90语言
        wen1,     yang,        bian,  jiao,    zhi2,   liu,    pin,     shi4,     En,        li1,   //10文样编交直流频试enli
        gh,       yi1,         qi2 ,  U   ,    pan,    xun,    da1,      yin,     zhuan,     cun,   //11gh仪器U 盘讯打印转存
        shi5,     bai,         di,    fan1,    hui,//失败地返回  
  	};


extern const uint8 text_dayin[ ];//={2,shou,dong};//打印
extern const uint8 text_Upan[ ];//={2,tong,xin};//U盘
extern const uint8 text_tongxun[ ];//={2,kong,bei};//通讯
extern const  uint8 * fileset_p[];//={ text_dayin,text_Upan,text_tongxun};


extern const uint8 text_zhuancun[ ];//={2,zhuan,cun};//转存
extern const uint8 text_wancheng[ ];//={2,wan,cheng};//完成
extern const uint8 text_shibai[ ];//={2,shi5,bai};//失败
extern const  uint8 *Udisk_p[];//={text_zhuancun,text_wancheng,text_shibai};




extern const uint8 text_phkj[ ];//={4,pu,hua,ke,ji};//普华科技
extern const uint8 text_ktdq[ ];//={4,ke,te,dian,qi};//凯特电气
extern const  uint8 *  company_p[];//={ text_phkj, text_ktdq};

extern const uint8 text_dyxz[ ];//={4,dian,ya,xuan,ze};//电压选择
extern const uint8 text_clfs[ ];//={4,ce,liang,fang,shi};//测量方式
extern const uint8 text_lssj[ ];//={4,li,shi3,shu,ju};//历史数据
extern const uint8 *  mainset_p[];//={text_dyxz,text_clfs,text_yysz,text_lssj};
extern const  unsigned char char_clock[ ];//={16,'-',' ',' ','-',' ',' ',' ',' ',' ',' ',':',' ',' ',':',' ',' ',':'};  

extern const uint8 text_yjzsh[ ];//={5,you,jie,zhi,sun,hao};//油介质损耗
extern const uint8 text_tjdzl[ ];//={5,ti,ji,dian,zu,lv};//体积电阻率
extern const uint8 text_jrqd[ ];//={4,jia,re,qi,dong};//加热启动
extern const uint8 text_ywsd[ ];//={4,you,wen,she,ding};//油温设定
extern const uint8 text_jldy[ ];//={4,jiao,liu, dian,ya};//交流电压
extern const uint8 text_jlpl[ ];//={4,jiao,liu, pin,lv};//交流频率
extern const uint8 text_zldy[ ];//={4,zhi2,liu,dian,ya};//直流流电压
extern const uint8 text_kbdr[ ];//={4,kong,bei,dian,rong};//空杯电容
extern const uint8 text_tzsz[ ];//={4,tiao,zheng,shi,zhong };//调整时钟
extern const uint8 text_yuyan[ ];//={2,yu1,yan};//语言
extern const uint8 text_fanhui[ ];//={2,fan1,hui};//返回
extern const uint8 text_zhongwen[ ];//={2,zhong,wen1};//中文
extern const uint8 text_enligh[ ];//={2,En,li1,gh};//中文
extern const  uint8 *Lanset_p[];//={text_zhongwen,text_enligh};
extern const uint8 text_guan[ ];//={3,kg,guan,kg};//关
extern const uint8 *  oilset_p[];//={text_yjzsh,text_tjdzl,text_jrqd,text_ywsd,text_kbdr,text_tzsz, text_yuyan};

extern const uint8 text_aqdjwcsz[ ];//={8,an,qi,dong,jian,wan,cheng,she,zhi};//按启动键完成设置


extern const uint8 text_zidong[ ];//={2,zi,dong};//自动
extern const uint8 text_shoudong[ ];//={2,shou,dong};//手动
extern const uint8 text_tongxun[ ];//={2,tong,xin};//通信
extern const  uint8 * workset_p[];//={text_zidong,text_shoudong,text_tongxun};


extern const uint8 char_50hz[ ];//={4,'5','0','H','Z'};//50hz
extern const uint8 char_60hz[ ];//={4,'6','0','H','Z'};//60hz
extern const uint8 * Fre_p[];//={char_50hz,char_60hz};



extern const uint8 text_zdcl[ ];//={4,zi,dong,ce,liang};//自动测量
extern const uint8 text_sdcl[ ];//={4,shou,kg,kg,dong};//手  动
extern const uint8 text_zztx[ ];//={4,zheng,zai,tong,xin,};//正在通讯
extern const  uint8 * workdisplay_p[];//={text_zdcl,text_sdcl,text_zztx};


extern const uint8 text_jiesun[ ];//={2,jie,sun};//介损
extern const uint8 text_dianrong[ ];//={2,dian,rong};//电容
extern const uint8 text_jiedian[ ];//={2,jie,dian,};//介电
extern const uint8 text_dzl[ ];//={3,dian,zu,lv};//电阻率




extern const uint8 text_youwen[ ];//={2,you,wen};//油温
extern const uint8 text_guoya[ ];//={4,guo,kg,kg,ya};//过压
extern const uint8 text_gydl[ ];//={4,gao,ya,duan,lu};//高压短路
extern const uint8 text_jrxtgz[ ];//={6,jia,re,xi,tong,gu,zhang};// 加热系统故障
extern const uint8 text_xhxtgz[ ];//={6,xin,hao,xi,tong,gu,zhang};//信号系统故障
extern const uint8 text_jyxtgz[ ];//={6,jia,ya,xi,tong1,gu,zhang}; //加压系统故障

extern  const uint8 text_jsdxjxyx[ ];//={8,jie,shang,di,xian,ji,xu,yun,xing};//接上地线继续运行
extern const uint8 text_gsgzjxyx[ ];//={8,gai,shang,gai,zi,ji,xu,yun,xing};//盖上盖子继续运行
extern const uint8 text_aqdjbzts[ ];//={8,an,qi,dong,jian,bu,zai,ti,shi};//按启动键不再提示


extern const uint8 text_zhwz[ ];//={4,zai,heng,wen,zhong};//在恒温中
extern const uint8 text_zzjr[ ];//={4,zheng,zai,jia,re};//正在加热
extern const uint8 text_cjx[ ];//={4,cha,jie,xian,kg};//查接线

extern const uint8 text_qcybjx[ ];//={6,qing,cha,you,bei,jie,xian};//请查油杯接线
extern const uint8 text_aqdjjxyx[ ];//={8,an,qi,dong,jian,ji,xu,yun,xing};//按启动键继续运行


extern const uint8 text_kbjr[ ];//={4,kong,bei,jia,re};//空杯加热
extern const uint8 text_ywbdy90[ ];//={7,you,wen,bu,yi,da,yu,90,};//温度不宜大于90
extern const uint8 text_afwjcxsz[ ];//={8,an,fu,wei,jian,chong,xin,she,zhi};//按复位键重新设置



extern const uint8 text_zzcd[ ];//={4,zheng,zai,fang,dian,};//正在放电
extern const uint8 text_zzfd[ ];//={4,zheng,zai,chong,dian};//正在充电
extern const uint8 text_bzwxh[ ];//={5,biao,zhun,wu,xin,hao};//标准无信号
extern const uint8 text_clwxh[ ];//={5,ce,liang,wu,xin,hao};//测量无信号
extern const uint8 text_zzcl[ ];//={zheng,zai,ce,liang};//正在测量
extern const uint8 text_bzwxh[ ];//={5,biao,zhun,xin,hao,da};//标准信号大
extern const uint8 text_clwxh[ ];//={5,ce,liang,xin,hao,da};//测量信号大

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

extern const uint8 text12_up[ ];//={2,0,1};//u盘
extern const uint8 text12_tx[ ];//={2,2,3};//通讯
extern const unsigned char text12_fh[];//	=	{2,10,11};	//返回
extern const uint8  text12_zc[ ];//={2,6,7};//转存
extern const uint8  text12_wc[ ];//={2,8,9};//完成
extern const uint8  text12_sb[ ];//={2,4,5};//失败
		

