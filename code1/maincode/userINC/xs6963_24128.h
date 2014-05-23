#ifndef _xs6963_24128
#define _xs6963_24128

#define LineChar 0x20 //Ò»ÐÐ16¸ö×Ö·û(8*8)
 void charLine1208_const(unsigned int lin ,unsigned char column , const unsigned char linehead[]);
 void charLine1208(unsigned int lin ,unsigned char column ,char linehead[]);
void ShowtextLine(unsigned int lin,unsigned char column,const unsigned char linehead[]);
void charLine(unsigned int lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[]);
void charLine8(unsigned int lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[]);
void Reversepic(unsigned int lin,unsigned char column,unsigned char high,unsigned char width);
void ShowPicture(unsigned int Startline,unsigned char Startcolumn,const unsigned char *adddd,uint8 nub);
void Pixel(unsigned int PointY,unsigned char PointX,unsigned char Mode);
void y_line(unsigned int y1, unsigned char x1, unsigned int y2, unsigned char Mode)	;
void x_line(unsigned int y1, unsigned char x1, unsigned char x2,  unsigned char Mode);
void Line( unsigned int y1, unsigned char x1, unsigned int y2, unsigned char x2, unsigned char Mode);
void ClearScreen_sector(unsigned int Startlin,unsigned char Startcolumn,unsigned int LineWidth,unsigned char ColumnWidth);
void ClearScreen(void );
void InitLCD(void );
void charLine1621(unsigned int lin ,unsigned char column ,unsigned char nubber,unsigned char linehead[]);
void charLineASCII(unsigned int lin ,unsigned char column ,const unsigned char linehead[]);
void pane(unsigned int Start_py,unsigned char Start_px,unsigned int Stop_py,unsigned char Stop_px);
void panemore(unsigned int Start_py,unsigned char Start_px,unsigned int Stop_py,unsigned char Stop_px,unsigned char width);
void  ShowPixel( unsigned int StartlinPixel,unsigned char StartcolumnPixel, const unsigned char *adddd,uint8 nub);
void charLine0806(unsigned int linPixel ,unsigned char columnPixel ,unsigned char nubber,unsigned char linehead[]);
void Showpoint(unsigned int PointY,unsigned char PointX,unsigned char Mode);
void ShowtextLine1216(unsigned int lin,unsigned char column, const unsigned char linehead[]);
#endif

