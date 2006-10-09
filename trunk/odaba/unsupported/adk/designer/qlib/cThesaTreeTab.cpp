/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cThesaTreeTab

\brief    


\date     $Date: 2006/07/22 18:06:31,78 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cThesaTreeTab"

#include  <pdesign.h>
#include  <scThesaTreeTab.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cThesaTreeTab :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cThesaTreeTab();
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

int8 cThesaTreeTab :: DoAfterSelect ( )
{
  CTX_Control     *thes_ctx;
  CTX_Control     *ws_ctx;
  CTX_Control     *text_ctx;
  CTX_Control     *prop_ctx;
  int16            level = GetDisplayLevel();
  char             executed = NO;
  thes_ctx = (CTX_Control *)GetHighContext("thesaurus");  
  ws_ctx = (CTX_Control *)thes_ctx->GetControlContext("these_ws");
  text_ctx = (CTX_Control *)ws_ctx->GetControlContext("edit_stack");
  prop_ctx = (CTX_Control *)thes_ctx->GetControlContext("these_property_stack");
  
  if ( level > 0 )
  {
    text_ctx->SetDisplayLevel(level);
    prop_ctx->SetDisplayLevel(level);
  }

  return(executed);
}

/******************************************************************************/
/**
\brief  cThesaTreeTab - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cThesaTreeTab"

     cThesaTreeTab :: cThesaTreeTab ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cThesaTreeTab - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cThesaTreeTab"

     cThesaTreeTab :: ~cThesaTreeTab ( )
{



}


