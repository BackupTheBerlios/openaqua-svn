 /*******************************************************************/
 /*                                                                 */
 /*                Document Composer Includes                       */
 /*  Version 0.1                                          11.06.93  */
 /*******************************************************************/

#ifndef   SOSERR_H
#define   SOSERR_H

#include  <sError.hpp>
#include  <isosi.h>
//extern  SOS4ImpExp  Error   soserr;

/*******************************************************************/

#define   SOSERR(x)    { SOSError().SetError( x,OBJ_ID,MOD_ID); goto on_error;  }

#define   SOSCERR      { if ( SOSError().CheckError() ) goto on_error;  }

#define   SOSRESET     { SOSError().ResetError(); }

#define   SOSERROR     SOSError().CheckError()

/*******************************************************************/ 

#endif
