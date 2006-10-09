/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    DBEvent

\brief    


\date     $Date: 2006/04/07 13:28:56,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBEvent"

#include  <popa7.h>
#ifndef   DLL_DBReaction_HPP
#define   DLL_DBReaction_HPP
#include  <sDBReaction.hpp>
#include  <sDLL.h>
#endif
#include  <sCAU_Event.hpp>
#include  <sCAU_simpleAction.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sDBResource.hpp>
#include  <sSimpleAction.hpp>
#include  <sUCA_Action.hpp>
#include  <sDBEvent.hpp>


/******************************************************************************/
/**
\brief  CheckEvent - 


\return term - Termination code

\param  ctxptr - 
\param  clear_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEvent"

logical DBEvent :: CheckEvent (CTX_DBBase *ctxptr, logical clear_event )
{
  logical                 term = NO;
  if ( clear_event )
    pre_cond_true = NO;

  if ( pre_cond_true )
  {
    term = YES;
    if ( post_condition )
      term = post_condition->Execute(ctxptr);
  }
  
  if ( term )
    term = ctxptr->get_resource()->GenerateEvent(this,ctxptr);
    
  pre_cond_true = YES;
  if ( pre_condition )
    pre_cond_true = pre_condition->Execute(ctxptr);
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCondition - 


\return actptr - Action pointer

\param  simplact - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCondition"

UCA_Action *DBEvent :: CreateCondition (CAU_simpleAction *simplact, CTX_DBBase *ctxptr )
{

  return( simplact->get_action_type() 
          ? ctxptr->CreateAction((SimpleAction *)simplact)
          : NULL                           );

}

/******************************************************************************/
/**
\brief  DBEvent - 


-------------------------------------------------------------------------------
\brief  i0


\param  cauevt_ptr - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBEvent"

                        DBEvent :: DBEvent (CAU_Event *cauevt_ptr, CTX_DBBase *ctxptr )
                     :   pre_condition(NULL),
  pre_cond_true(NO),
  post_condition(NULL),
  int_event(cauevt_ptr->get_int_event()),
  reactions(new DLL(DBReaction))
{
  DBReaction       *reaction;
  char             *reactid_key;
  int32              reactid;

BEGINSEQ
  memcpy(name,cauevt_ptr->get_sys_ident(),sizeof(name));

  pre_condition  = CreateCondition(&cauevt_ptr->get_pre_condition(),ctxptr);
  post_condition = CreateCondition(&cauevt_ptr->get_post_condition(),ctxptr);
  
  cauevt_ptr->get_reactions_evt().Cancel();
  while ( reactid_key = cauevt_ptr->get_reactions_evt().NextKey() )
  {
    memcpy(&reactid,reactid_key,sizeof(int32));
    if ( reactid ) 
    {
      if ( !(reaction = new DBReaction(reactid)) )     SDBERR(95)
      reactions->AddTail(reaction);
    }
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02


\param  ph - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBEvent"

                        DBEvent :: DBEvent (PropertyHandle &ph, CTX_DBBase *ctxptr )
                     :   pre_condition(NULL),
  pre_cond_true(NO),
  post_condition(NULL),
  int_event((DB_Event)ph.GetInt("int_event")),
  reactions(new DLL(DBReaction))
{
  DBReaction       *reaction;
  char             *reactid_key;
  int32              reactid;
BEGINSEQ
  memcpy(name,ph.GetArea("sys_ident"),sizeof(name));

  pre_condition  = CreateCondition((CAU_simpleAction *)ph.GetArea("pre_condition"),ctxptr);
  post_condition = CreateCondition((CAU_simpleAction *)ph.GetArea("post_condition"),ctxptr);
  
  PH(&ph,reactions_evt)
  reactions_evt.Cancel();
  while ( reactid_key = reactions_evt.NextKey() )
  {
    memcpy(&reactid,reactid_key,sizeof(int32));
    if ( reactid ) 
    {
      if ( !(reaction = new DBReaction(reactid)) )     SDBERR(95)
      reactions->AddTail(reaction);
    }
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBEvent"

                        DBEvent :: DBEvent ( )
                     :   pre_condition(NULL),
  pre_cond_true(NO),
  post_condition(NULL),
  int_event(DB_undefined),
  reactions(NULL)
{



}

/******************************************************************************/
/**
\brief  ~DBEvent - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBEvent"

                        DBEvent :: ~DBEvent ( )
{
  DBReaction        *reaction;
  while ( reaction = reactions->RemoveTail() )
    delete reaction;

  delete reactions;

}


