/*******************************************************************/
/*		            	   P_ERR                           */
/*                      Error Macro Definitions                    */
/*   Version 0.1                                          20.07.04 */
/*******************************************************************/

#ifndef   P_ERRMAC_H
#define   P_ERRMAC_H

#include  <sError.hpp>
#include  <iOGUI_Interface.h>

 /*******************************************************************/

#define   P__CANCEL 1000


 /*******************************************************************/

#define   P_ERR(x)       { P_Error().SetError( x,OBJ_ID,MOD_ID); \
		           goto on_error;  }

#define   P_IERR(x)      { P_Error().SetError( x,NULL,NULL);	\
			   goto on_error;  }

#define   P_SET(x)       { P_Error().SetError( x,OBJ_ID,MOD_ID);  }

#define   P_ISET(x)      { P_Error().SetError( x,NULL,NULL);       }

#define   P_CERR         { if ( P_Error().CheckError() )	\
                           goto on_error;  }

#define   P_ERROR          P_Error().CheckError() 

#define   P_RESET        { P_Error().ResetError();      }

#define   P_CHECK(x)     { if ( x > 0 )                              \
                             P_Error().SetError( x,OBJ_ID,MOD_ID);   \
                           if ( x )                                  \
                             goto on_error;            }

#define   P_CHECKERR(x)  { if ( P_Error().SystemCheck( x,OBJ_ID,MOD_ID) ) \
                           goto on_error;            }

#define   P_DISPLAY_ERROR { P_Error().DisplayMessage();          }

#define   P_DISPLAY(x)   { P_Error().SetError( x,NULL,NULL);     \
                           P_Error().DisplayMessage();          }


 /*********************/

#define   P_SDBCERR   { if ( SDBError().CheckError() )	\
                          { P_Error().SetError(ODABA_ERROR,OBJ_ID,MOD_ID); \
                            goto on_error; } }
#define   P_SDBERR    { P_Error().SetError(ODABA_ERROR,OBJ_ID,MOD_ID); goto on_error; }

#define   P_OQLCERR   { if ( OQLError().CheckError() )	\
                          { P_Error().SetError(OQL_ERROR,OBJ_ID,MOD_ID); \
                            goto on_error; } }
#define   P_OQLERR    { P_Error().SetError(OQL_ERROR,OBJ_ID,MOD_ID); goto on_error; }

 /*********************/

#define   P_SETEV1(str,len)  { P_Error().SetErrorVariable(1, str, len); }
#define   P_SETEV2(str,len)  { P_Error().SetErrorVariable(2, str, len); }
#define   P_SETEV3(str,len)  { P_Error().SetErrorVariable(3, str, len); }
#define   P_SETEV4(str,len)  { P_Error().SetErrorVariable(4, str, len); }
#define   P_SETEV5(str,len)  { P_Error().SetErrorVariable(5, str, len); }

 /*******************************************************************/

#endif



