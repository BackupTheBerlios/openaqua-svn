 /*******************************************************************/
 /*                                                                 */
 /*                                                         (ACTP)  */
 /*  Version 0.1                                          30.01.95  */
 /*******************************************************************/

#ifndef   TFCTP_H
#define   TFCTP_H

#include  <svcls.hpp>

typedef logical (vcls::*TFCTP)( void );

#define TLINK( instptr, clsname, funcptr ) ThreadLink ( (vcls *)(void *)instptr,(ACTP)(logical (clsname::*)(void)) &clsname::funcptr)

#endif
