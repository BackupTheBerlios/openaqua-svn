/*******************************************************************/
/*		            	     C T X                         */
/*                      Error Macro Definitions                    */
/*   Version 0.1                                          02.09.94 */
/*******************************************************************/

#ifndef   CTXERR_H
#define   CTXERR_H

#include  <sError.hpp>
#include  <iopai.h>

 /*******************************************************************/


#define   CTXERR(x)       { CTXError().SetError( x,OBJ_ID,MOD_ID); \
		                    goto on_error;  }

#define   CTXIERR(x)      { CTXError().SetError( x,NULL,NULL);	\
			                goto on_error;  }

#define   CTXSET(x)       { CTXError().SetError( x,OBJ_ID,MOD_ID);  }

#define   CTXISET(x)      { CTXError().SetError( x,NULL,NULL);       }

#define   CTXCERR         { if ( CTXError().CheckError() )	\
                           goto on_error;  }

#define   CTXSDBERR(x)    { if ( !SDBError().CheckError() )	\
                              CTXError().SetError( x,OBJ_ID,MOD_ID); \
                            goto on_error;  }

#define   CTXP_ERR        { if ( P_Error().CheckError() )	\
                              CTXError().SetError(P_Error().CheckError(),OBJ_ID,MOD_ID); \
                            goto on_error;  }

#define   CTXERROR          CTXError().CheckError() 

#define   CTXRESET        { CTXError().ResetError();      }

#define   CTXCHECK(x)     { if ( CTXError().SystemCheck( x,OBJ_ID,MOD_ID) ) \
                            goto on_error;            }

#define   CTXCHECKERR(x)  { if ( CTXError().SystemCheck( x,OBJ_ID,MOD_ID) ) \
                            goto on_error;            }

#define   CTXDISPLAY_ERROR { CTXError().DisplayMessage();          }

#define   CTXDISPLAY(x)   { CTXError().SetError( x,NULL,NULL);     \
                            CTXError().DisplayMessage();          }

 /*********************/

#define   CTXSETEV1(str,len)  { CTXError().SetErrorVariable(1, str, len); }
#define   CTXSETEV2(str,len)  { CTXError().SetErrorVariable(2, str, len); }
#define   CTXSETEV3(str,len)  { CTXError().SetErrorVariable(3, str, len); }
#define   CTXSETEV4(str,len)  { CTXError().SetErrorVariable(4, str, len); }
#define   CTXSETEV5(str,len)  { CTXError().SetErrorVariable(5, str, len); }
#define   CTXSETEV6(str,len)  { CTXError().SetErrorVariable(6, str, len); }

 /*******************************************************************/

#endif



