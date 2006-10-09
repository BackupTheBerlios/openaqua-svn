/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDB_Codeset_Edit



\date     $Date: 2006/04/24 13:45:05,48 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSDB_Codeset_Edit"

#include  <pdesign.h>
#include  <scSDB_Codeset_Edit.hpp>


/******************************************************************************/
/**
\brief  Create

\return 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cSDB_Codeset_Edit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cSDB_Codeset_Edit();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoBeforeFillData

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cSDB_Codeset_Edit :: DoBeforeFillData ( )
{
  PropertyHandle        *ph       = GetPropertyHandle();
  CTX_Control           *enum_ctx = NULL;
  char                   executed = NO;
BEGINSEQ
  if ( !ph->IsSelected() )                          ERROR

  cs_ph.Open(ph->GetDBHandle(),ph->GetString("sys_ident"),PI_Update);
                                                    P_SDBCERR
  if ( !(enum_ctx = GetControlContext("properties_member.enumerators")) )
                                                    ERROR
  enum_ctx->SetPropertyHandle(&cs_ph);

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cSDB_Codeset_Edit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSDB_Codeset_Edit"

                        cSDB_Codeset_Edit :: cSDB_Codeset_Edit ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cSDB_Codeset_Edit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSDB_Codeset_Edit"

                        cSDB_Codeset_Edit :: ~cSDB_Codeset_Edit ( )
{



}


