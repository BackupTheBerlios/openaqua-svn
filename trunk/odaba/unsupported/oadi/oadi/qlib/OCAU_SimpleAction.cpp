/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OCAU_SimpleAction



\date     $Date: 2006/04/30 16:24:13,46 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OCAU_SimpleAction"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sCTX_GUIBase.hpp>
#include  <sOAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sResourceCache.hpp>
#include  <sTComponent.hpp>
#include  <sTProjectManager.hpp>
#include  <sOCAU_SimpleAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OCAU_SimpleAction :: CastPointer (char *typenames )
{

  return (   !typenames                             ? NULL
           : !strcmp(typenames,"OCAU_SimpleAction") ? this
                                                    : OResource::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OCAU_SimpleAction :: CreateInstance (void **instptrp )
{
  *instptrp = new OCAU_SimpleAction();
  return(0);
}

/******************************************************************************/
/**
\brief  Execute - Execute action
        The  function executes the  action as defined  in the object and returns
        the  result. When  the defined  action could  not be found, the function
        returns AUTO, otherwise the returncode from the executed action. .

\return executed - How was function exetuted

\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char OCAU_SimpleAction :: Execute (CTX_GUIBase *ctxptr )
{
  char    executed = AUTO;
BEGINSEQ
  if ( !action ) // diese Optimierung geht wegen ctxptr so nicht!
  {
    if ( !(action = TProjectManager::TPM->Cache()->ReadAction( 
                      sys_ident,actionType)) )
      if ( !(action = TProjectManager::TPM->Cache()->ProvideDefaultAction( 
                        sys_ident,actionType,ctxptr)) )
                                                     LEAVESEQ
  }
  
  executed = action->Execute(ctxptr);

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  IsEmpty

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical OCAU_SimpleAction :: IsEmpty ( ) const
{

  return ( *sys_ident >= ' ' ? YES : NO );

}

/******************************************************************************/
/**
\brief  OCAU_SimpleAction

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCAU_SimpleAction"

     OCAU_SimpleAction :: OCAU_SimpleAction ( )
                     : OResource (),
  actionType((ActionType)0),
  action(NULL),
  current_component(NULL)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  actionType
\param  pOAction
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCAU_SimpleAction"

     OCAU_SimpleAction :: OCAU_SimpleAction (OResource bcOResource, int32 actionType, OAction *pOAction )
                     : OResource (bcOResource),
  actionType((ActionType)actionType),
  action(pOAction),
  current_component(NULL)
{


/*
  "OCAU_SimpleAction("
  +        ADK_Resource::Generate()
  + ", " + action_type
  + ", " + ADK_Action::Generate(sys_ident,action_type)
!! pOAction is possibly more complicated
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OCAU_SimpleAction :: Read (PropertyHandle *ph )
{
  int32                   number;
  logical                 term = NO;
  OPersistent::Read(ph);
  
  if ( number = ph->GetInt("action_type") )
  {
    (int&)actionType = number;
    strcpy(sys_ident,ph->GetString("sys_ident"));
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OCAU_SimpleAction :: Reset ( )
{
  if ( action )
    action->Release();
  action = NULL;

  actionType = (ActionType)0;
  
  OResource::Reset();
}

/******************************************************************************/
/**
\brief  SetAction

\return term

\param  act_names
\param  vActionType
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

logical OCAU_SimpleAction :: SetAction (char *act_names, ActionType vActionType )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  gvtxbts(sys_ident,act_names,sizeof(sys_ident)-1);
  actionType = vActionType;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCurrentComponent


\param  pTComponent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentComponent"

void OCAU_SimpleAction :: SetCurrentComponent (TComponent *pTComponent )
{

  if ( this )
    current_component = pTComponent;

}

/******************************************************************************/
/**
\brief  set_actionType


\param  act_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_actionType"

void OCAU_SimpleAction :: set_actionType (ActionType act_type )
{

  actionType = act_type;

}

/******************************************************************************/
/**
\brief  ~OCAU_SimpleAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OCAU_SimpleAction"

     OCAU_SimpleAction :: ~OCAU_SimpleAction ( )
{
  if ( !Deleting() )
    Reset();
}


