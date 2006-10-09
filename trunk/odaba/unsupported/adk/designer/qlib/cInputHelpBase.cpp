/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cInputHelpBase

\brief    


\date     $Date: 2006/04/24 13:38:30,57 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cInputHelpBase"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <scInputHelpBase.hpp>


/******************************************************************************/
/**
\brief  DoAfterDataSet

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDataSet"

int8 cInputHelpBase :: DoAfterDataSet ( )
{
  PropertyHandle   *prophdl = GetPropertyHandle();
  if ( prophdl->GPH("source")->IsEmpty() )
  {
    DFont    font = GetLineFont(AUTO);
    font.SetWeight(FW_Bold);
    SetLineFont(font,AUTO);
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterHide - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHide"

int8 cInputHelpBase :: DoAfterHide ( )
{

  PropertyHandle     empty_handle;  
  SetPropertyHandle(&empty_handle);
  return(NO);
}

/******************************************************************************/
/**
\brief  GetContextInfo - 


\return datarea - 

\param  offset_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextInfo"

char *cInputHelpBase :: GetContextInfo (int32 &offset_ref )
{
  CTX_Control  *ctl_ctx = (CTX_Control *)GetHighContext(CTXT_Control);
  char         *result  = NULL;
  char         *datarea = NULL;
BEGINSEQ
  offset_ref = UNDEF;
  
  if ( !(datarea = ctl_ctx->GetData()->GetArea()) )  ERROR

  if ( ctl_ctx->ExecuteFunction("GetCurrentOffset")) ERROR
  if ( !(result = ctl_ctx->GetResult()) )            ERROR
  offset_ref = PropertyHandle(result).GetInt();


RECOVER
  datarea = NULL;
ENDSEQ
  return(datarea);
}

/******************************************************************************/
/**
\brief  GetMyClass - 


\return term - 

\param  type_key
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMyClass"

logical cInputHelpBase :: GetMyClass (TypeKey &type_key )
{
  CTX_Control  *ctl_ctx = (CTX_Control *)GetHighContext(CTXT_Control);
  logical       term    = NO;
  char         *result  = NULL;
BEGINSEQ
  if ( ctl_ctx->ExecuteFunction("GetClassName"))     ERROR
  if ( !(result = ctl_ctx->GetResult()) )            ERROR
  type_key.Initialize(result,0);

RECOVER
  type_key.Initialize("",0);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetMyFunctImpPH

\return prophdl - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMyFunctImpPH"

PropertyHandle *cInputHelpBase :: GetMyFunctImpPH ( )
{
  CTX_Control  *ctl_ctx = (CTX_Control *)GetHighContext(CTXT_Control);
  return ( ctl_ctx->GetPropertyHandle()->GetParentProperty() );


}

/******************************************************************************/
/**
\brief  SetDatasource - 


\return term - 

\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDatasource"

logical cInputHelpBase :: SetDatasource (PropertyHandle *source_ph )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  logical            term    = NO;
BEGINSEQ
  if ( source_ph->GetCount() <= 0 )                ERROR
  if ( prophdl->Is(*source_ph) )                   LEAVESEQ
    
  SetPropertyHandle(source_ph); 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cInputHelpBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cInputHelpBase"

                        cInputHelpBase :: cInputHelpBase ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cInputHelpBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cInputHelpBase"

                        cInputHelpBase :: ~cInputHelpBase ( )
{



}


