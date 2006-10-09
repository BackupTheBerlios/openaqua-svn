 /*******************************************************************/
 /*                                                                 */
 /*                                                         (FCTP)  */
 /*  Version 0.1                                          06.09.94  */
 /*******************************************************************/ 
 
#ifndef   FCTP_H
#define   FCTP_H

#include  <svcls.hpp>
class      flnk;

typedef int32 (vcls::*FCTP)( void* parm );

#define FLINK( instptr, clsname, funcptr ) flnk ( (vcls *)(void *)instptr,(FCTP)(int32 (clsname::*)(void *)) &clsname::funcptr)

#define SLINK( clsname, funcptr ) flnk ( (vcls *)NULL,(FCTP)(int32 (clsname::*)(void *)) &clsname::funcptr)

#define LINKINST( instptr )  SetInstance ( (vcls *)(void *)instptr);

#endif

