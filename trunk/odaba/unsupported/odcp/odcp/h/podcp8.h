/*******************************************************************/
/*			     O D C P 8                             */
/*         Project Includes - General Defines and Error Class      */
/*   Version 0.1                                          02.07.03 */
/*******************************************************************/

#ifndef   PODCP8_H
#define   PODCP8_H

#ifndef    IF_Class
#define    _ODCP8_
#define    _OADI_
#include  <codcpdll.h>
#include  <coadidll.h>
#include  <coguidll.h>
#include  <copadll.h>
#include  <csosdll.h>
#endif

#include  <padcstd.h>
#include  <cuctx.h>

#define  flnkx                          LinkHdl

class QObject;
class QEvent;
//#include   <sv.hpp>
//#include   <afxcolli.h>

 /*******************************************************************/

#define   OADIERR(x)         { OADIError().SetError( x,OBJ_ID,MOD_ID);          \
             			       goto on_error;  }

#define   P_OADICERR         { if ( OADIError().CheckError() )	                     \
                               { P_Error().SetError(OADI_ERROR,OBJ_ID,MOD_ID); \
                                 goto on_error; } }

#define   OADIERV1(str,len)  { OADIError().SetErrorVariable(1, str, len); }
#define   OADIERV2(str,len)  { OADIError().SetErrorVariable(2, str, len); }
#define   OADIERV3(str,len)  { OADIError().SetErrorVariable(3, str, len); }
#define   OADIERV4(str,len)  { OADIError().SetErrorVariable(4, str, len); }
#define   OADIERV5(str,len)  { OADIError().SetErrorVariable(5, str, len); }

 /*******************************************************************/

#include  <csos4mac.h>
#include  <igvtx.h>
#include  <imsm.h>

#include  <csmcbmac.h> 
#include  <codaba2.h>
#include  <cutimac.h>


#include  <coadimac2.h>
#include  <cperrmac.h>
//#include  <csqlmac.h>
//#include  <cdcmac.h> 

#include <soe_helper.hpp>
#endif    // PODCP8_H

