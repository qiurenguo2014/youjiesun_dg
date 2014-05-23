#ifndef _Viewdata
#define _Viewdata
enum{ EASII_no, EASII_yes };
void  ResultMune_display(void);
void Resulttest_display(void );
uint8 floatE_xs(float xs_data,char *byte,uint8 flag);
void e_display(uint16 lin, uint8 column, float xsdata,uint8 flag);
uint8 float_xs(float xs_data,char  *byte,uint8 flag);
void TG_display(uint16 lin,uint8 column, float xsdata);
void Cx_display(uint16 lin,uint8 column, float xsdata);
void E_display(uint16 lin,uint8 column, float xsdata);
void Rx_display(uint16 lin,uint8 column, float xsdata,uint8 flag);
void P_display(uint16 lin,uint8 column, float xsdata,uint8 flag);
void STOdataxs(uint16 page);
uint8 Viewdata_Hander(void);
void Resulttest_sto(void);
void ResultCOMtest_sto( uint8 page,uint8 option);
void V_display(uint16 lin,uint8 column, float xsdata);
uint8  fileHander(void);
void xs_Ann(uint8 option,float dat);
void  Resultcom_display(void);
#endif

