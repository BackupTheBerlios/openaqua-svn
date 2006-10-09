 /*******************************************************************/
 /*                                                                 */
 /*                Document Composer Includes                       */
 /*  Version 0.1                                          11.06.93  */
 /*******************************************************************/

#ifndef   OADIERR_H
#define   OADIERR_H

#include  <sError.hpp>
//extern  OADIImpExp  Error   OADIerr;

/*******************************************************************/

#define   OADIERR(x)    { OADIError().SetError( x,OBJ_ID,MOD_ID); goto on_error;  }

#define   OADIIERR(x)   { OADIError().SetError( x,NULL,NULL);     goto on_error;  }

#define   OADIPERR      { OADIError().SetError(0,"",MOD_ID);       goto on_error;  }

#define   OADICERR      { if ( OADIError().CheckError() )          goto on_error;  }

#define   OADICSERR(x)  { if ( !OADIError().CheckError() )           \
	                    OADIError().SetError( x,OBJ_ID,MOD_ID); \
	                  goto on_error;  }

#define   OADISET(x)    { OADIError().SetError( x,OBJ_ID,MOD_ID);  }

#define   OADIISET(x)   { OADIError().SetError( x,NULL,NULL);       }

#define   OADIRESET     { OADIError().ResetError();      }

#define   OADIEV1(str,len)  { OADIError().SetErrorVariable(1, str, len); }
#define   OADIEV2(str,len)  { OADIError().SetErrorVariable(2, str, len); }
#define   OADIEV3(str,len)  { OADIError().SetErrorVariable(3, str, len); }
#define   OADIEV4(str,len)  { OADIError().SetErrorVariable(4, str, len); }
#define   OADIEV5(str,len)  { OADIError().SetErrorVariable(5, str, len); }
 
#define   OADISDBCERR       { if ( SDBError().CheckError() )                     \
                             { OADIError().SetError(ODABA_ERROR,OBJ_ID,MOD_ID);  \
                               goto on_error; } }

#define   OADISDBCSERR(x)   { if ( SDBError().CheckError() )                     \
                                OADIError().SetError(ODABA_ERROR,OBJ_ID,MOD_ID); \
                              else                                               \
       	                        OADIError().SetError( x,OBJ_ID,MOD_ID);         \
                              goto on_error;  }

#define   OADIGUICERR       { if ( OGUIError().CheckError() )                    \
                             { OADIError().SetError(OGUI_ERROR,OBJ_ID,MOD_ID);   \
                               goto on_error; } }

#define   OADIGUICSERR(x)   { if ( OGUIError().CheckError() )                    \
                                OADIError().SetError(OGUI_ERROR,OBJ_ID,MOD_ID);  \
                              else                                               \
       	                        OADIError().SetError( x,OBJ_ID,MOD_ID);         \
                              goto on_error;  }

#define   P_OADICERR         { if ( OADIError().CheckError() )                   \
                               { P_Error().SetError(OADI_ERROR,OBJ_ID,MOD_ID);   \
                                 goto on_error; } }

#define   OADIDCCERR        { if ( DCError().CheckError() )                      \
                             { OADIError().SetError(DC_ERROR,OBJ_ID,MOD_ID);     \
                               goto on_error; } }

#define   OADIDISPLAY_ERROR { OADIError().DisplayMessage(); }

#define   OADIDISPLAY(x)    { OADIError().SetError( x,NULL,NULL);               \
                             OADIError().DisplayMessage();  }

#define   OADI_CANCEL 1000

#define   OADIERROR     OADIError().CheckError()

/*******************************************************************/ 

#endif
