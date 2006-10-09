 /*******************************************************************/
 /*                                                                 */
 /*                                                         (FCTP)  */
 /*  Version 0.1                                          06.09.94  */
 /*******************************************************************/

#ifndef   EVTP_H
#define   EVTP_H
#include  <svcls.hpp>
#include  <cCSA_Events.h>
#include  <cDB_Event.h>

class     PropertyHandle;
class     EventLink;

typedef logical (vcls::*EVTP)( CSA_Events, int32, PropertyHandle &);

#define ELINK( instptr, clsname, funcptr ) EventLink ( (vcls *)(void *)instptr,(EVTP)(logical (clsname::*)(CSA_Events, int32, PropertyHandle &)) &clsname::funcptr)

typedef logical (vcls::*EVTPL)( DB_Event);

#define ELINKL( instptr, clsname, funcptr ) EventLink ( (vcls *)(void *)instptr,(EVTPL)(logical (clsname::*)(DB_Event)) &clsname::funcptr)

#endif
