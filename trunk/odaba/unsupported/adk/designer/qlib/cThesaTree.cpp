/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cThesaTree

\brief    


\date     $Date: 2006/07/23 13:03:55,31 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cThesaTree"

#include  <pdesign.h>
#include  <scThesaTree.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cThesaTree :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cThesaTree();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterSelect - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cThesaTree :: DoAfterSelect ( )
{
  CTX_Control     *thes_ctx = (CTX_Control *)GetHighContext("thesaurus");
  PropertyHandle  *cur_pi   = GetCurrentPropertyHandle();
  CTX_Control     *ws_ctx   = (CTX_Control *)thes_ctx->GetControlContext("these_ws");
  CTX_Control     *text_ctx = (CTX_Control *)ws_ctx->GetControlContext("these_edit_stack");
  CTX_Control     *prop_ctx = (CTX_Control *)thes_ctx->GetControlContext("these_property_stack");
  char             executed = NO;
  text_ctx->SetPropertyHandle(cur_pi);
  prop_ctx->SetPropertyHandle(cur_pi);

  return(executed);
}

/******************************************************************************/
/**
\brief  cThesaTree - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cThesaTree"

     cThesaTree :: cThesaTree ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cThesaTree - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cThesaTree"

     cThesaTree :: ~cThesaTree ( )
{



}


