#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef _GLOBAL_DEBUG_ENABLE
#include <stdio.h>
extern int debug_printf(const char *format,...);
extern void assert_Function(char *file_name, unsigned int line_no, char *expression);
extern void SysLog_PrintTimeStamp(const char *pStr);
#ifdef SYSLOG
#define assert( expr ) \
	( (void)( !(expr) ? assert_Function(__FILE__, __LINE__, #expr),(void)1 : (void)0 ) )
#define DPRINTF(a) 		{debug_printf a;}
#define LOG_FUNC_NAME( expr )          static const char* FUNC_NAME = expr;
#define LOG_FUNC( expr )               { DPRINTF(("%s\n",FUNC_NAME));}
//#define LOG_TEXT( expr )               { SysLog_PrintTimeStamp(FUNC_NAME); DPRINTF(expr); DPRINTF(("\n")); }
	#if ( 1 <= SYSLOG )
		#define LOG_TXT1( expr )       { SysLog_PrintTimeStamp(FUNC_NAME); DPRINTF(expr); DPRINTF(("\n")); }
	#else
		#define LOG_TXT1( expr )       ( (void)0 )
	#endif

	#if ( 2 <= SYSLOG )
		#define LOG_TXT2( expr )       { SysLog_PrintTimeStamp(FUNC_NAME); DPRINTF(expr); DPRINTF(("\n")); }
	#else
		#define LOG_TXT2( expr )       ( (void)0 )
	#endif

	#if ( 3 <= SYSLOG )
		#define LOG_TXT3( expr )       { SysLog_PrintTimeStamp(FUNC_NAME); DPRINTF(expr); DPRINTF(("\n")); }
	#else
		#define LOG_TXT3( expr )       ( (void)0 )
	#endif

#else
#define DPRINTF(a)
#define assert(expr)                   ( (void)0 )
#define LOG_FUNC_NAME( _expr )
#define LOG_FUNC( expr )                   ( (void)0 )
#define LOG_TXT1( expr )       ( (void)0 )
#define LOG_TXT2( expr )       ( (void)0 )
#define LOG_TXT3( expr )       ( (void)0 )
#endif

#else
#define DPRINTF(a)                   ( (void)0 )
#define assert(expr)                    ( (void)0 )
#define LOG_FUNC_NAME( _expr )
#define LOG_FUNC( expr )                   ( (void)0 )
#define LOG_TXT1( expr )       ( (void)0 )
#define LOG_TXT2( expr )       ( (void)0 )
#define LOG_TXT3( expr )       ( (void)0 )

//#define _DETECT_UPDATE_PIN

#endif

#endif

