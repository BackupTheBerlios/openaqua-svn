/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OCAU_Action



\date     $Date: 2006/04/28 16:57:42,98 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OCAU_Action"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOCAU_SimpleAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOCAU_Action.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OCAU_Action :: CastPointer (char *typenames )
{

  return (   !typenames                       ? NULL
           : !strcmp(typenames,"OCAU_Action") ? this
                                              : OCAU_SimpleAction::CastPointer(typenames) );

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

int32 OCAU_Action :: CreateInstance (void **instptrp )
{
  *instptrp = new OCAU_Action();
  return(0);
}

/******************************************************************************/
/**
\brief  OCAU_Action

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCAU_Action"

     OCAU_Action :: OCAU_Action ( )
                     : OCAU_SimpleAction (),
  pre_handler(NULL),
  post_handler(NULL)
{

// fixme nd
// in dieser klasse fehlt die behandlung (einlesen...)
// von pre und post handler

}

/******************************************************************************/
/**
\brief  i01


\param  bcOCAU_SimpleAction
\param  pre_handler
\param  post_handler
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCAU_Action"

     OCAU_Action :: OCAU_Action (OCAU_SimpleAction bcOCAU_SimpleAction, OCAU_SimpleAction *pre_handler, OCAU_SimpleAction *post_handler )
                     : OCAU_SimpleAction (bcOCAU_SimpleAction),
  pre_handler(pre_handler),
  post_handler(post_handler)
{
/*
  "OCAU_Action("
  +        ADK_CAU_SimpleAction::Generate()
  + ", " + pre_handler.Generate()
  + ", " + post_handler.Generate()
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

logical OCAU_Action :: Read (PropertyHandle *ph )
{
  OCAU_SimpleAction      *sact;
  logical                 term = NO;
  OCAU_SimpleAction::Read(ph);

  if ( sact = CACHE_READ(ph,"pre_handler",OCAU_SimpleAction) )
  {
    if ( pre_handler )
      pre_handler->Release();
    pre_handler = sact;
  }
  if ( sact = CACHE_READ(ph,"post_handler",OCAU_SimpleAction) )
  {
    if ( post_handler )
      post_handler->Release();
    post_handler = sact;
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

void OCAU_Action :: Reset ( )
{
  if ( pre_handler )
    pre_handler->Release();
  pre_handler = NULL;
  
  if ( post_handler )
    post_handler->Release();
  post_handler = NULL;

  OCAU_SimpleAction::Reset();
}

/******************************************************************************/
/**
\brief  operator==

\return cond

\param  rOCAU_Action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

bool OCAU_Action :: operator== (OCAU_Action &rOCAU_Action )
{
  bool                    cond = TRUE;
BEGINSEQ
// sys_ident ist immer schon gleich
// aber pre und post handler muessen noch geprueft werden  *fixme* nd

  if ( actionType != rOCAU_Action.actionType )       ERROR
RECOVER
  cond = TRUE;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ~OCAU_Action


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OCAU_Action"

     OCAU_Action :: ~OCAU_Action ( )
{
  if ( !Deleting() )
    Reset();
}


