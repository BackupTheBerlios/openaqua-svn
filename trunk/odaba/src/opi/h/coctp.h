 /*******************************************************************/ 
 /*                                                                 */
 /*                                                         (OCTP)  */
 /*  Version 0.1                                          10.05.2004  */
 /*******************************************************************/

#ifndef   OCTP_H
#define   OCTP_H

#include  <cExecutionTypes.h>

class     vcls; 
class     PropertyHandle;
class     ParmList;
typedef logical (vcls::*OCTP)( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *, ExecutionTypes);

#include  <svcls.hpp>

#define OLINK( clsname, funcptr ) FunctLink ( (OCTP)(logical (clsname::*)(PropertyHandle *, PropertyHandle *,ParmList *,char *,ExecutionTypes)) &clsname::funcptr)

#define SET_CO( instptr ) SetInstance ( (vcls *)(void *)instptr )

#endif

#include  <ccctp.h>
