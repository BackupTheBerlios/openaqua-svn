/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_CAction

\brief    


\date     $Date: 2006/03/12 19:22:02,59 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCA_CAction"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sUCA_Action.hpp>
#include  <sUCA_CAction.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return term - Success
-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical UCA_CAction :: Execute ( )
{
  int32                   rc = 0;
  logical                 term = NO;
BEGINSEQ
  if ( rc = (!action->CheckPermission() || 
             (pre_handler && pre_handler->Execute())) )   
  {
    action->get_context()->SetActionResult(AUTO);   LEAVESEQ
  }
  
  action->get_context()->SetActionResult(action->Execute());
      
  if ( post_handler )
    term = post_handler->Execute();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i1


\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical UCA_CAction :: Execute (CTX_Base *ctxptr )
{

  if ( pre_handler )
    pre_handler->set_context(ctxptr);

  if ( post_handler )
    post_handler->set_context(ctxptr);

  if ( action )
    action->set_context(ctxptr);

  return( Execute() );

}

/******************************************************************************/
/**
\brief  UCA_CAction

-------------------------------------------------------------------------------
\brief i0


\param  pre_action -
\param  cur_action -
\param  post_action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCA_CAction"

                        UCA_CAction :: UCA_CAction (UCA_Action *pre_action, UCA_Action *cur_action, UCA_Action *post_action )
                     : pre_handler(pre_action),
  action(cur_action),
  post_handler(post_action)
{



}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCA_CAction"

                        UCA_CAction :: UCA_CAction ( )
                     : pre_handler(NULL),
  action(NULL),
  post_handler(NULL)
{



}

/******************************************************************************/
/**
\brief  ~UCA_CAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~UCA_CAction"

                        UCA_CAction :: ~UCA_CAction ( )
{

  delete pre_handler;
  pre_handler = NULL;
  
  delete action;
  action = NULL;
  
  delete post_handler;
  post_handler = NULL;


}


