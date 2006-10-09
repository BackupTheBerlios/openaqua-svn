/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cLanguage



\date     $Date: 2006/05/19 13:12:54,90 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cLanguage"

#include  <pdesign.h>
#include  <scLanguage.hpp>


/******************************************************************************/
/**
\brief  Create

\return 

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cLanguage :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cLanguage();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterSelect

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cLanguage :: DoAfterSelect ( )
{
  CTX_GUIBase     *adk_ctx  = GetHighContext();
  PropertyHandle  *adk_pi   = adk_ctx ? adk_ctx->GetPropertyHandle() : NULL;
  char            *language = NULL;
  logical          reset    = NO;
  char             executed = NO;
BEGINSEQ
  if ( UserState1() )                                LEAVESEQ
  SetUserState1(YES);
  reset = YES;
  
  if ( !adk_pi->IsGenericAttribute() )
    if ( !(adk_pi  = adk_pi->GPH("text_definitions")) &&   // ADK_Text
         !(adk_pi  = adk_pi->GPH("definition"))          ) // DSC_TopicDef
                                                     ERROR
  adk_ctx->ExecuteAction("Save",ACT_Function);
  
  if ( !(language = GetKey()) )                      ERROR
    
  if ( strcmp(language,"undefined") )
    adk_pi->SetGenAttribute(language);
  else
  {
    if ( !adk_pi->GetGenAttrType() )                 LEAVESEQ
    adk_ctx->DoBeforeFillData();
  }

RECOVER
  executed = YES;
ENDSEQ
  if ( reset )
    SetUserState1(NO);
  return(executed);
}

/******************************************************************************/
/**
\brief  cLanguage


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cLanguage"

     cLanguage :: cLanguage ( )
                     : CTX_Control ()
{
}

/******************************************************************************/
/**
\brief  ~cLanguage


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cLanguage"

     cLanguage :: ~cLanguage ( )
{
}


