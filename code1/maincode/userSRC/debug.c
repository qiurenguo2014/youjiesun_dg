/*
#include "macro.h"
#include "mcudef.h"
#include "useruart.h"
#include "debug.h"
#include "ioport.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
*/
#include "file_ah9837.h"
#ifdef _GLOBAL_DEBUG_ENABLE

#define DbgSendByte(m) Uart0Send(m)

#define FUNCLEN 32

//char temp_buffer[128];
int debug_printf(const char *format,...)
{
	int length = 0,i = 0;
	
char temp_buffer[128];
	va_list arg_ptr;

	va_start (arg_ptr, format);           /* format string */
	vsprintf (temp_buffer, format, arg_ptr);
	length = strlen(temp_buffer);

	for(i=0;i<length;i++)
		{
		 DbgSendByte(temp_buffer[i]);
		}

	va_end (arg_ptr);

	return length;
}

void assert_Function(char *file_name, unsigned int line_no, char *expression)
{
	debug_printf("\nFile: %s,line:%d Error.\n",file_name,line_no);
	debug_printf(expression);
	debug_printf("\n");
	while(1);
}

static void sSysLog_PrintWhiteSpace( unsigned char Size )
{
	if( FUNCLEN < Size )
		return;

	while( Size-- )
		DbgSendByte(' ');
}

void SysLog_PrintTimeStamp(const char *pStr)
{
	debug_printf("-%s()",pStr);
	sSysLog_PrintWhiteSpace(FUNCLEN-strlen(pStr));
	debug_printf(": ");
}

#endif

