/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    TAction

\brief    


\date     $Date: 2006/03/13 21:33:21,53 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TAction"

#include  <poadi.h>
#include  <sCTX_GUIBase.hpp>
#include  <sOCAU_Action.hpp>
#include  <sTAction.hpp>


/******************************************************************************/
/**
\brief  Execute - Execute action
        The  function executes  the action  as defined  in the actin definitiont
        and  returns the result. When no action is defined or the defined action
        could  not be found,  the function returns  AUTO. Otherwise the function
        returns the return code from the executed action.

\return executed - How was function exetuted

\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char TAction :: Execute (CTX_GUIBase *ctxptr )
{

  return ( action ? action->Execute(ctxptr) : AUTO );

}

/******************************************************************************/
/**
\brief  GetActionType - 


\return vActionType -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActionType"

ActionType TAction :: GetActionType ( )
{

  return ( action ? action->get_actionType() : ACT_undefined );

}

/******************************************************************************/
/**
\brief  TAction - 



\param  act_names -
\param  pOCAU_Action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TAction"

                        TAction :: TAction (char *act_names, OCAU_Action *pOCAU_Action )
                     :   action(pOCAU_Action)
{

  gvtxstb(sys_ident,act_names,sizeof(sys_ident));

}


