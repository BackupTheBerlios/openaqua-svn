/*******************************************************************/
/*                           O Q L                                 */
/*         Project Includes - General Defines and Error Class      */
/*   Version 0.1                                          10.03.93 */
/*******************************************************************/ 

#ifndef   POQL_H
#define   POQL_H

#define  _OQL7_

#include  <csos4mac.h>
#define   MEMO    mem

#include  <codaba2.h>
#include  <podaba2.h>
#include  <OGUIDdef.h>


extern   int32     opnode_count;

/*******************************************************************/ 

/*******************************************************************/ 

#define   OQLERR(x)    { OQLError().SetError( x,OBJ_ID,MOD_ID); \
		                 goto on_error;  }

#define   OQLSERR(x)   { ShowError( x,OBJ_ID,MOD_ID,(BNFData *)NULL); \
		                 goto on_error;  }

#define   OQLBERR(x)   { parent_node->ShowError( x,OBJ_ID,MOD_ID,(BNFData *)NULL); \
		                 goto on_error;  }

#define   OQLIERR(x)   { OQLError().SetError( x,NULL,NULL);	\
	            		 goto on_error;  }

#define   OQLPERR      { OQLError().SetError(0,"",MOD_ID); \
                         goto on_error;  }

#define   OQLCERR      { if ( OQLError().CheckError() )	\
                           goto on_error;  }

#define   OQLSET(x)    { OQLError().SetError( x,OBJ_ID,MOD_ID);  }

#define   OQLISET(x)   { OQLError().SetError( x,NULL,NULL);       }

#define   OQLRESET     { OQLError().ResetError();      }

#define   OQL_DSPL_ON  { OQLError().tdspl = YES; } 
#define   OQL_DSPL_OFF { OQLError().tdspl = NO; } 
#define   OQL_LIST_ON  { OQLError().tlist = YES; }
#define   OQL_LIST_OFF { OQLError().tlist = NO; }
#define   OQL_HIER_ON  { OQLError().thier = YES; } 
#define   OQL_HIER_OFF { OQLError().thier = NO; } 

#ifdef    _TST_
#undef    BEGINSEQ
#undef    RECOVER 
#undef    ENDSEQ  

#define   BEGINSEQ       static void *tptr=NULL; { OQLError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'B');
#define   RECOVER        } goto on_end; on_error: { OQLError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'R');
#define   ENDSEQ         } on_end: OQLError().TraceFunction(&tptr,MOD_ID,OBJ_ID,'E');   
#endif // _TST_

 /*******************************************************************/ 

#define   OQLEV1(str,len)  { OQLError().SetErrorVariable(1, str, len); }
#define   OQLEV2(str,len)  { OQLError().SetErrorVariable(2, str, len); }
#define   OQLEV3(str,len)  { OQLError().SetErrorVariable(3, str, len); }
#define   OQLEV4(str,len)  { OQLError().SetErrorVariable(4, str, len); }

 /*******************************************************************/ 


#include  <coqlerr.h>

#include  <igvtx.h>
#include  <igvts.h>
#include  <igvtu.h>
#include  <imsm.h>
#include  <ifil.h>

#endif    // POQL_H

