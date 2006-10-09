/*******************************************************************/
/*                           S O S 4                               */
/*         Project Includes - General Defines and Error Class      */
/*   Version 2.1                                          07.10.97 */
/*******************************************************************/

#ifndef   PSOS4_H
#define   PSOS4_H

#define   _SOS7_
#include  <csosdll.h>

#include  <padcstd.h>
#include  <csos4mac.h>

#define   SOSERR(x)    { SOSError().SetError( x,OBJ_ID,MOD_ID); goto on_error;  }

#define   SOSIERR(x)   { SOSError().SetError( x,NULL,NULL);     goto on_error;  }

#define   SOSPERR      { SOSError().SetError(0,"",MOD_ID);       goto on_error;  }

#define   SOSCERR      { if ( SOSError().CheckError() )          goto on_error;  }

#define   SOSSET(x)    { SOSError().SetError( x,OBJ_ID,MOD_ID);  }

#define   SOSISET(x)   { SOSError().SetError( x,NULL,NULL);       }

#define   SOSRESET     { SOSError().ResetError();      }

#define   SOSEV1(str,len)  { SOSError().SetErrorVariable(1, str, len); }
#define   SOSEV2(str,len)  { SOSError().SetErrorVariable(2, str, len); }
#define   SOSEV3(str,len)  { SOSError().SetErrorVariable(3, str, len); }
#define   SOSEV4(str,len)  { SOSError().SetErrorVariable(4, str, len); }
#define   SOSEV5(str,len)  { SOSError().SetErrorVariable(5, str, len); }

#include  <isosi.h>
#include  <igvtx.h>
#include  <igvts.h>
#include  <igvtu.h>
#include  <igvtc.h>
#include  <imsm.h>
#include  <ifil.h>

#include  <ctxdef.h>

#endif    // PSOS4_H
