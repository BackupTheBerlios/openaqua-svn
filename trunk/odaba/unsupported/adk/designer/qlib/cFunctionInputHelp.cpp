/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cFunctionInputHelp

\brief    


\date     $Date: 2006/06/21 16:43:29,51 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cFunctionInputHelp"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <scFunctionInputHelp.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cFunctionInputHelp :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cFunctionInputHelp();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterShow - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterShow"

int8 cFunctionInputHelp :: DoAfterShow ( )
{
  pODE            *ode_ctx     = ODEContext(this);
  char            *datarea     = NULL;
  TypeKey          type_key;
  int32            offset      = UNDEF;
  char             executed    = NO;
BEGINSEQ
  if ( !ode_ctx )                                    ERROR
    
  if ( GetMyClass(type_key) )                        ERROR
  if ( !(datarea = GetContextInfo(offset)) )         ERROR
    
  if ( SetDatasource(ode_ctx->GetFunctionInputHelpPH(type_key,datarea,offset,NO)) )
                                                     ERROR    

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cFunctionInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cFunctionInputHelp"

     cFunctionInputHelp :: cFunctionInputHelp ( )
                     : cInputHelpBase ()
{



}

/******************************************************************************/
/**
\brief  ~cFunctionInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cFunctionInputHelp"

     cFunctionInputHelp :: ~cFunctionInputHelp ( )
{



}


