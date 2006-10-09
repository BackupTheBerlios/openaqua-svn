/*******************************************************************/
/*                      C O M P I L                                */
/*         Project Include - General Compiler Dependent Defines    */
/*   Version 0.1                                          06.10.92 */
/*******************************************************************/

#ifndef   PCOMPIL_H
#define   PCOMPIL_H

#define  ID_SIZE            40
#define  ID_S               ID_SIZE
#define  DATETIME           dttm

#ifdef  __unix__
typedef unsigned           char BYTE;
typedef unsigned short     int  WORD;
typedef unsigned           int  DWORD;

#define LARGE_INTEGER int64
#define __far
#define __cdecl
#define  _IF_ImpExp

#define SEGBASE
#define HELP_INDEX 0
#define BOOL logical
#define TRUE  true
#define FALSE false

//timeb
#define _timeb timeb
#define _ftime ftime
#define CTime  dbdt     // nur mal so bis geklaert ist, was CTime entspricht

//io
#define _open           open
#define _write          write
#define _close          close
#define _fileno         fileno
#define _lseeki64       lseek
#define _filelengthi64  fillength

//.dll
#define HINSTANCE       void *
#define LPSTR           char *

#define GetProcAddress  dlsym
// STRINGS
#define stricmp(a, b)   strcasecmp(a,b)
#define strnicmp(a, b, c)  strncasecmp(a,b,c)


//threads

#endif /* __unix__*/
#include <cthread.h>

#ifdef WIN32
#define SEGBASE
#define __far
#endif

#ifndef  __unix__
#define  getch        _getch
#define  _IF_ImpExp   __declspec(dllexport)
//#define  _open         open
//#define  _write        write
//#define  _read         read
//#define  _close        close
// #define  int86        _int86
// #define  intdosx      _intdosx
// #define  REGS         _REGS
// #define  SREGS        _SREGS
#endif

// alignment
#ifdef __unix__
#define ATTR_ALIGN(byte) __attribute__ ((__aligned__ (byte)))
#else
#define ATTR_ALIGN(byte)
#endif /* __unix__*/


#ifdef _MSC7_
#undef   DOS_DATE
#define  DOS_DATE      struct _dosdate_t
#undef   DOS_TIME
#define  DOS_TIME      struct _dostime_t
#endif

//#ifdef  _MSC7_
#define  SVLINK(a,b,c) LINK( a, b, c)
//#endif

#endif
