/*******************************************************************/
/*			     S D B			           */
/*                      SDB Error Macro Definitions                */
/*   Version 0.1                                          02.07.95 */
/*******************************************************************/

#ifndef   SDBERR_H
#define   SDBERR_H

 /*******************************************************************/

#include  <sError.hpp>
//#include  <coqlerr.h>
#include  <cctxerr.h>
#include  <iopai.h>

 /*******************************************************************/

#define   META_ERROR_BASE  1089
#define   ODABA_ERROR      1090
#define   SQL_ERROR        1091
#define   DC_ERROR         1092
#define   OGUI_ERROR       1093    
#define   ADCO_ERROR       1093
#define   OQL_ERROR        1094
#define   COMEIN_ERROR     1095
#define   CONTEXT_ERROR    1096
#define   SERVER_ERROR     1097
#define   SOS_ERROR        1098
#define   APPL_ERROR       1099

#define   SDBCERR      { if ( SDBError().CheckError() )	\
                           goto on_error;  }

#define   SDBERROR     SDBError().CheckError()

#define   SDBRESET     { SDBError().ResetError();      }

#define   SDBCTXCERR   { if ( CTXError().CheckError() )                      \
                         { SDBError().SetError(CONTEXT_ERROR,OBJ_ID,MOD_ID); \
                           goto on_error;  }                 }

#define   SDBDISPLAY_ERROR { SDBError().DisplayMessage();          }

 /*******************************************************************/ 
 
#endif

