/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pButtons_StyleAction

\brief    


\date     $Date: 2006/05/23 13:39:05,00 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pButtons_StyleAction"

#include  <padkctxi.h>
#include  <spc_ADK_Button.hpp>
#include  <spButtons_StyleAction.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  propctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pButtons_StyleAction :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pButtons_StyleAction();
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

logical pButtons_StyleAction :: DBInserted ( )
{
  PropertyHandle  *prophdl = GetPropertyHandle();
BEGINSEQ
  if ( !prophdl->IsServer() )                       LEAVESEQ
  pc_ADK_Button(prophdl).SetupButton();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  pButtons_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pButtons_StyleAction"

     pButtons_StyleAction :: pButtons_StyleAction ( )
                     : CTX_Property ()
{



}

/******************************************************************************/
/**
\brief  ~pButtons_StyleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pButtons_StyleAction"

     pButtons_StyleAction :: ~pButtons_StyleAction ( )
{



}


