/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cColorRole

\brief    


\date     $Date: 2006/04/24 12:55:12,13 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cColorRole"

#include  <pdesign.h>
#include  <scColorRole.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cColorRole :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cColorRole();
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

int8 cColorRole :: DoAfterSelect ( )
{


  return ( LocateBrush(YES) );


}

/******************************************************************************/
/**
\brief  DoBeforeFillData

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cColorRole :: DoBeforeFillData ( )
{

  return ( LocateBrush(NO) );

}

/******************************************************************************/
/**
\brief  LocateBrush

\return term - 

\param  store_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateBrush"

logical cColorRole :: LocateBrush (logical store_opt )
{
  PropertyHandle  *cur_ph     = GetPropertyHandle();
  CTX_Control     *colors_ctx = GetFieldContext(".colors");   
  logical          term       = NO;

BEGINSEQ
  if ( !colors_ctx )                                 ERROR
    
  if ( store_opt )  
    ExecuteAction("StoreEntry", ACT_Function);
    
  colors_ctx->GetPropertyHandle()->Provide(*cur_ph);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


