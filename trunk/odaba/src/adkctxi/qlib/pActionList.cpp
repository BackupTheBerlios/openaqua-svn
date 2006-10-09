/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pActionList



\date     $Date: 2006/05/23 13:21:53,89 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pActionList"

#include  <padkctxi.h>
#include  <spc_ADK_EventAction.hpp>
#include  <spActionList.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  propctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pActionList :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pActionList();
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

logical pActionList :: DBInserted ( )
{
  PropertyHandle  *prophdl = GetPropertyHandle();
BEGINSEQ
  if ( !prophdl->IsServer() )                       LEAVESEQ
  pc_ADK_EventAction(prophdl).Setup();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  pActionList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pActionList"

     pActionList :: pActionList ( )
                     : CTX_Property ()
{
}

/******************************************************************************/
/**
\brief  ~pActionList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pActionList"

     pActionList :: ~pActionList ( )
{
}


