/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pRegions_StyleAction



\date     $Date: 2006/05/23 13:51:36,34 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pRegions_StyleAction"

#include  <padkctxi.h>
#include  <spc_ADK_Field.hpp>
#include  <spRegions_StyleAction.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  propctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pRegions_StyleAction :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pRegions_StyleAction();
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

logical pRegions_StyleAction :: DBInserted ( )
{
  PropertyHandle   *prophdl = GetPropertyHandle();
BEGINSEQ
  if ( !prophdl->IsServer() )                       LEAVESEQ
  pc_ADK_Field(prophdl).SetupRegion();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  pRegions_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pRegions_StyleAction"

     pRegions_StyleAction :: pRegions_StyleAction ( )
                     : CTX_Property ()
{
}

/******************************************************************************/
/**
\brief  ~pRegions_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pRegions_StyleAction"

     pRegions_StyleAction :: ~pRegions_StyleAction ( )
{
}


