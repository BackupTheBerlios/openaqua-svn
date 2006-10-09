/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pColumns_StyleAction



\date     $Date: 2006/05/23 13:20:47,57 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pColumns_StyleAction"

#include  <padkctxi.h>
#include  <spc_ADK_Field.hpp>
#include  <spColumns_StyleAction.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  propctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pColumns_StyleAction :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pColumns_StyleAction();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBInserted

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInserted"

logical pColumns_StyleAction :: DBInserted ( )
{
  PropertyHandle   *prophdl = GetPropertyHandle();
BEGINSEQ
  if ( !prophdl->IsServer() )                       LEAVESEQ
  pc_ADK_Field(prophdl).SetupColumn();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  pColumns_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pColumns_StyleAction"

     pColumns_StyleAction :: pColumns_StyleAction ( )
                     : CTX_Property ()
{
}

/******************************************************************************/
/**
\brief  ~pColumns_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pColumns_StyleAction"

     pColumns_StyleAction :: ~pColumns_StyleAction ( )
{
}


