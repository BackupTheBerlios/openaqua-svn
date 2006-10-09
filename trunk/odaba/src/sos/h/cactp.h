 /*******************************************************************/
 /*                                                                 */
 /*                                                         (ACTP)  */
 /*  Version 0.1                                          30.01.95  */
 /*******************************************************************/ 
 
#ifndef   ACTP_H
#define   ACTP_H

#include  <svcls.hpp>

typedef logical (vcls::*ACTP)( void );

#define ALINK( instptr, clsname, funcptr ) flnk ( (vcls *)(void *)instptr,(ACTP)(logical (clsname::*)(void)) &clsname::funcptr)

#endif
