/*******************************************************************/
/*                 O A D I                                         */
/*         Project Includes - General Defines and Error Class      */
/*   Version 0.1                                          02.07.03 */
/*******************************************************************/ 

#ifndef   POADI_H
#define   POADI_H

#define    _OADI_
#define    _ODCP8_
#include  <coadidll.h>
#include  <coguidll.h>
#include  <codcpdll.h>
#include  <copadll.h>
#include  <csosdll.h>

#include  <padcstd.h>
#include  <oi.h>
#include  <cqt.h>
#include  <memdebug.h>
#ifndef   CONCAT
#define   CONCAT(a,b) a##b
#endif

#include <csos4mac.h>
#include <codaba2.h>
#include <coadimac.h>
#include <iopai.h>
#include <igvtx.h>
#include <sDLL_Handle.hpp>
#include <cutimac.h>
#include <cstats.h>

#include <sCS_Message.hpp>

#ifdef __unix__
#define   TRACEIT(s)
#else
#define   TRACEIT(s)     { OutputDebugStringA(s); OutputDebugStringA("\n"); }
#endif //__unix
#define   TRACEIT1(s,p1) { char __buf[2560]; sprintf( __buf, s, p1 ); TRACEIT(__buf); }
#define   TRACEIT2(s,p1,p2) { char __buf[2560]; sprintf( __buf, s, p1, p2 ); TRACEIT(__buf); }
#define   TRACEIT3(s,p1,p2,p3) { char __buf[2560]; sprintf( __buf, s, p1, p2, p3 ); TRACEIT(__buf); }
#define   TRACEIT4(s,p1,p2,p3,p4) { char __buf[2560]; sprintf( __buf, s, p1, p2, p3, p4 ); TRACEIT(__buf); }

#define   NOTTESTED  { TRACEIT2( "Warning: NOT TESTED %s::%s", OBJ_ID, MOD_ID ); }
#define   NIY(R)     { TRACEIT2( "Warning: NOT IMPLEMENTED YET %s::%s", OBJ_ID, MOD_ID ); return R; }
#define   NIY1(P,R)  { TRACEIT3( "Warning: NOT IMPLEMENTED YET %s::%s - %s", OBJ_ID, MOD_ID, P ); return R; }
#define   OBSOLETE(X)    { TRACEIT3( "Warning: OBSOLETE %s::%s, %s", OBJ_ID, MOD_ID, X ); }

#endif
