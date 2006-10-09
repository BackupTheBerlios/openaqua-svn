/*******************************************************************/
/*                      A D C S T D                                */
/*         Project Include - General ADC Defines                   */
/*   Version 0.1                                          23.09.93 */
/*******************************************************************/

#ifndef   P_ADC_H
#define   P_ADC_H

#ifdef __unix__
#include <ctype.h>
#include <stdint.h>
#include <sys/ioctl.h>
#endif
#include <stdlib.h>

// std-types

#define std_string std::string 

// integer values with fixed size(in bit) 
#define atoi32(s) strtoi(s, NULL, 10)
#define atoui32(s) strtoui(s, NULL, 10)
#define strtoi32(s, t, b) strtoi(s, t, b)
#define strtoui32(s, t, b) strtoui(s, t, b)
#ifdef __unix__
#define atoi64(s) strtoll(s, NULL, 10)
#define atoui64(s) strtoull(s, NULL, 10)
#define strtoi64(s, t, b) strtoll(s, t, b)
#define strtoui64(s, t, b) strtoull(s, t, b)
#else
#define atoi64(s) _strtoi64(s, NULL, 10)
#define atoui64(s) _strtoui64(s, NULL, 10)
#define strtoi64(s, t, b) _strtoui64(s, t, b)
#define strtoui64(s, t, b) _strtoui64(s, t, b)
#endif

#ifdef __unix__
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;

#else
typedef char    int8;
typedef short   int16;
typedef int     int32;
typedef __int64 int64;

typedef unsigned char    uint8;
typedef unsigned short   uint16;
typedef unsigned int     uint32;
typedef unsigned __int64 uint64;
#endif

typedef uint16              bit;
typedef uint8               logical;
typedef unsigned char       uchar;
typedef unsigned int        uint;
typedef unsigned short int  ushort;
typedef unsigned long int   ulong;

#include <pcompil.h>
#include <stdio.h>
#include <string.h>

#define   NOTYPE

#define   DEFLOCALERR       int32  local_err = 0;
#define   LOCALERR(x)       {      local_err =  x; goto on_error; }
#define   LOCALERROR               local_err
#define   LOCAL_SDBCERR     { if ( SDBError().CheckError() )	\
                              { LOCALERROR = ODABA_ERROR;       \
                                goto on_error; } }
#ifndef   BEGINSEQ

#define   BEGINSEQ	 { 
#define   RECOVER        } goto on_end; on_error: {
#define   ENDSEQ	 } on_end: ;

#undef    ERROR
#define   ERROR          goto on_error;
#define   LEAVESEQ       goto on_end;

#endif

#define   CHECKTHIS      { if ( !this ) goto on_error; }

#define   StrToBuf(targ,srce)  gvtxstb(targ,srce,sizeof(targ))
#define   BufToStr(targ,srce)  gvtxbts(targ,srce,sizeof(targ)-1)
#define   CopyStr(targ,srce)   strncpy(targ,srce,sizeof(targ)-1)
#define   CopyBuf(targ,srce)   memcpy(targ,srce,sizeof(targ))
#define   CompBuf(targ,srce)   memcmp(targ,srce,sizeof(targ))

#define   LoadShort(shorti,buffer)   {((char *)&(shorti))[0] = ((char *)buffer)[0]; ((char *)&(shorti))[1] = ((char *)buffer)[1];}
#define   LoadLong(longi,buffer)     {((char *)&(longi))[0] = ((char *)buffer)[0];  ((char *)&(longi))[1] = ((char *)buffer)[1]; ((char *)&(longi))[2] = ((char *)buffer)[2]; ((char *)&(longi))[3] = ((char *)buffer)[3];}
#define   LoadFloat(longi,buffer)     {((char *)&(longi))[0] = ((char *)buffer)[0];  ((char *)&(longi))[1] = ((char *)buffer)[1]; ((char *)&(longi))[2] = ((char *)buffer)[2]; ((char *)&(longi))[3] = ((char *)buffer)[3];}
#define   LoadDouble(doubli,buffer)  {((char *)&(doubli))[0] = ((char *)buffer)[0]; ((char *)&(doubli))[1] = ((char *)buffer)[1]; ((char *)&(doubli))[2] = ((char *)buffer)[2]; ((char *)&(doubli))[3] = ((char *)buffer)[3]; ((char *)&(doubli))[4] = ((char *)buffer)[4];  ((char *)&(doubli))[5] = ((char *)buffer)[5]; ((char *)&(doubli))[6] = ((char *)buffer)[6]; ((char *)&(doubli))[7] = ((char *)buffer)[7];}
#define   LoadBigInt(doubli,buffer)  {((char *)&(doubli))[0] = ((char *)buffer)[0]; ((char *)&(doubli))[1] = ((char *)buffer)[1]; ((char *)&(doubli))[2] = ((char *)buffer)[2]; ((char *)&(doubli))[3] = ((char *)buffer)[3]; ((char *)&(doubli))[4] = ((char *)buffer)[4];  ((char *)&(doubli))[5] = ((char *)buffer)[5]; ((char *)&(doubli))[6] = ((char *)buffer)[6]; ((char *)&(doubli))[7] = ((char *)buffer)[7];}
#define   StoreShort(buffer,shorti)  {((char *)buffer)[0] = ((char *)&(shorti))[0]; ((char *)buffer)[1] = ((char *)&(shorti))[1];}
#define   StoreLong(buffer,longi)    {((char *)buffer)[0] = ((char *)&(longi))[0];  ((char *)buffer)[1] = ((char *)&(longi))[1]; ((char *)buffer)[2] = ((char *)&(longi))[2];  ((char *)buffer)[3] = ((char *)&(longi))[3];}
#define   StoreFloat(buffer,longi)    {((char *)buffer)[0] = ((char *)&(longi))[0];  ((char *)buffer)[1] = ((char *)&(longi))[1]; ((char *)buffer)[2] = ((char *)&(longi))[2];  ((char *)buffer)[3] = ((char *)&(longi))[3];}
#define   StoreDouble(buffer,doubli)  {((char *)buffer)[0] = ((char *)&(doubli))[0]; ((char *)buffer)[1] = ((char *)&(doubli))[1]; ((char *)buffer)[2] = ((char *)&(doubli))[2]; ((char *)buffer)[3] = ((char *)&(doubli))[3]; ((char *)buffer)[4] = ((char *)&(doubli))[4]; ((char *)buffer)[5] = ((char *)&(doubli))[5]; ((char *)buffer)[6] = ((char *)&(doubli))[6]; ((char *)buffer)[7] = ((char *)&(doubli))[7];}
#define   StoreBigInt(buffer,doubli)  {((char *)buffer)[0] = ((char *)&(doubli))[0]; ((char *)buffer)[1] = ((char *)&(doubli))[1]; ((char *)buffer)[2] = ((char *)&(doubli))[2]; ((char *)buffer)[3] = ((char *)&(doubli))[3]; ((char *)buffer)[4] = ((char *)&(doubli))[4]; ((char *)buffer)[5] = ((char *)&(doubli))[5]; ((char *)buffer)[6] = ((char *)&(doubli))[6]; ((char *)buffer)[7] = ((char *)&(doubli))[7];}

#ifndef NULL
#if defined (__cplusplus)
 || (__unix__)
#define NULL	0
#else
#define NULL	((__far void *)0)
#endif
#endif

#define   UCHARMAX    255
#define   USHORTMAX   65535
#define   LONGMAX     2147483647  // ((LONG)0x7FFFFFFF))
#define   ULONGMAX    4294967295  // ((ulong)0xFFFFFFFF))
#define   ERIC	     -99
#define   USERBREAK  -64
#define   AUTO       -1
#define   UNDEF       0
#define   UNDF        0
#define   NO          (logical)0
#define   YES         (logical)1
#define   CS_U        2147483647

#define   WT          1
#define   RD          2
#define   UP          3

#define   K_ESC  27
#define   K_RET  13  

#ifndef   dcl
#define   dcl(lt,et)      lt ## dcl(et)
#endif
#ifndef   MAX
#define   MAX(a,b)        (((a) > (b)) ? (a) : (b))
#endif
#ifndef   MIN
#define   MIN(a,b)        (((a) < (b)) ? (a) : (b))
#define   abs64(a)        (((a) < 0) ? (-a) : (a))
#endif

#ifndef WIN32
#ifndef   offsetof
#define   offsetof(t,i)	  ((size_t)((char *)&((t *)1)->i - (char *)1))
#endif
#endif

#endif    // P_ADC_H
