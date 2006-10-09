/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSEDSelectionTab



\date     $Date: 2006/04/24 13:45:34,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSEDSelectionTab"

#include  <pdesign.h>
#include  <scSEDSelectionTab.hpp>


/******************************************************************************/
/**
\brief  Create

\return 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cSEDSelectionTab :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cSEDSelectionTab();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterSelect

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cSEDSelectionTab :: DoAfterSelect ( )
{
  PropertyHandle  *cur_pi     = GetCurrentPropertyHandle();
  CTX_Control     *strukt_ctx = GetHighContext("strukteditor")->GetControlContext();
  CTX_Control     *prop_ctx;
  char             executed   = NO;
  if ( prop_ctx = strukt_ctx->GetControlContext("struct_ws.property_stack") )
    prop_ctx->SetVirtualType(cur_pi);

  return(executed);
}

/******************************************************************************/
/**
\brief  cSEDSelectionTab


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSEDSelectionTab"

                        cSEDSelectionTab :: cSEDSelectionTab ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cSEDSelectionTab


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSEDSelectionTab"

                        cSEDSelectionTab :: ~cSEDSelectionTab ( )
{



}


