/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSelectionTree



\date     $Date: 2006/04/24 13:45:51,18 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSelectionTree"

#include  <pdesign.h>
#include  <scSelectionTree.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cSelectionTree :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cSelectionTree();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterHandleActivated

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleActivated"

int8 cSelectionTree :: DoAfterHandleActivated ( )
{
  CTX_Control    *pctx     = (CTX_Control *)GetHighContext();
  PropertyHandle  typenames(pctx->GetResourceName());
  PropertyHandle *ph       = GetPropertyHandle();
  int8            executed = NO;
  ph->GetParentProperty()->Get(typenames);
  return(executed);
}

/******************************************************************************/
/**
\brief  DoAfterSelect

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cSelectionTree :: DoAfterSelect ( )
{
  CTX_Control    *pctx     = (CTX_Control *)GetHighContext();
  CTX_Control    *stack    = pctx->GetControlContext("dyn_selection_tab");
  PropertyHandle *ph       = GetCurrentPropertyHandle();
  char            executed = NO;
BEGINSEQ
  if ( !stack )                                     ERROR
  if ( !ph->IsSelected() )                          ERROR

  stack->SetDisplayLevel(ph->GetString("type"));


RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cSelectionTree


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSelectionTree"

                        cSelectionTree :: cSelectionTree ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cSelectionTree


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSelectionTree"

                        cSelectionTree :: ~cSelectionTree ( )
{



}


