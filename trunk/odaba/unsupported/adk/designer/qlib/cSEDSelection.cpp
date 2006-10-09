/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSEDSelection

\brief    


\date     $Date: 2006/04/24 13:45:20,13 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSEDSelection"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <scSEDSelection.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cSEDSelection :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cSEDSelection();
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

int8 cSEDSelection :: DoAfterSelect ( )
{
  pODE            *ode_ctx    = ODEContext(this);
  PropertyHandle  *prophdl    = GetCurrentPropertyHandle();
  CTX_Control     *sed_ctx    = NULL;
  CTX_Control     *ws_tab_ctx = NULL;
  char             executed   = NO;
BEGINSEQ
  if ( !ode_ctx )                                    ERROR
  if ( !(sed_ctx = (CTX_Control *)GetHighContext("strukteditor")) ) 
                                                     ERROR
  if ( !(ws_tab_ctx = sed_ctx->GetControlContext("struct_ws.property_stack")) )
                                                     ERROR
  ws_tab_ctx->SetVirtualType(prophdl);

  cSDBResource_Base::DoAfterSelect();
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cSEDSelection - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSEDSelection"

                        cSEDSelection :: cSEDSelection ( )
                     : cSDBResource_Base()
{



}

/******************************************************************************/
/**
\brief  ~cSEDSelection - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSEDSelection"

                        cSEDSelection :: ~cSEDSelection ( )
{



}


