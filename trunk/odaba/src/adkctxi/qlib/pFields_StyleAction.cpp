/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pFields_StyleAction



\date     $Date: 2006/05/23 13:40:46,70 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pFields_StyleAction"

#include  <padkctxi.h>
#include  <spc_ADK_Field.hpp>
#include  <spFields_StyleAction.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  propctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pFields_StyleAction :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pFields_StyleAction();
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

logical pFields_StyleAction :: DBInserted ( )
{
  PropertyHandle   *prophdl = GetPropertyHandle();
BEGINSEQ
  if ( !prophdl->IsServer() )                       LEAVESEQ
  pc_ADK_Field(prophdl).SetupField();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  pFields_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pFields_StyleAction"

     pFields_StyleAction :: pFields_StyleAction ( )
                     : CTX_Property ()
{
}

/******************************************************************************/
/**
\brief  ~pFields_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pFields_StyleAction"

     pFields_StyleAction :: ~pFields_StyleAction ( )
{
}


