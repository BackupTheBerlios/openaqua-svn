/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CAU_State

\brief    


\date     $Date: 2006/03/12 19:16:24,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_State"

#include  <popa7.h>
#include  <sCAU_StateAction.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sfnc.hpp>
#include  <sCAU_State.hpp>


/******************************************************************************/
/**
\brief  ExecuteCAction - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCAction"

logical CAU_State :: ExecuteCAction ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !actions.Exist() || !state_context )         ERROR

  term = state_context->ExecuteAction(actions->get_sys_ident(),
                                      actions->get_action_type());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetContext - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

logical CAU_State :: SetContext (CTX_DBBase *ctxptr )
{

  state_context = (fnc *)ctxptr;
  return(NO);
}

/******************************************************************************/
/**
\brief i1


\param  fncptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

logical CAU_State :: SetContext (fnc *fncptr )
{
  // für Version 2.x
  state_context = fncptr;
  return(NO);
}


