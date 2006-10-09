/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_Causality

\brief    Causality
          A  causality defines one or more  events and actions that describe the
          reactions  on  the  events.  Related  events and actions are linked by
          means  of a reaction.  In the case  that the event-generating instance
          is  the  acting  instance  as  well,  the  reaction  is  described  as
          self-reacting.  More sophisticated reactions can be described by means
          of  reaction paths,  which refer  to a  number of related instances as
          reacting  instances.  When  the  reacting  instance  is  an  unrelated
          (observing)  instance, it must be  registered explicitly for observing
          the event.

\date     $Date: 2006/03/13 21:30:17,73 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_Causality"

#include  <pops7.h>
#ifndef   P_CAU_Action_HPP
#define   P_CAU_Action_HPP
#include  <sPI.hpp>
class       CAU_Action;
PI_dcl     (CAU_Action)
#endif
#include  <sCAU_Causality.hpp>


/******************************************************************************/
/**
\brief  CAU_Causality - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CAU_Causality"

                        CAU_Causality :: CAU_Causality ( )
                     :   actions(),
  event()

{



}

/******************************************************************************/
/**
\brief  LocateAction - 


\return act_pi

\param  action_names -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateAction"

PI(CAU_Action) *CAU_Causality :: LocateAction (char *action_names )
{
  PI(CAU_Action)         *act_pi = &actions;
  char                    act_name[ID_SIZE];
BEGINSEQ
  gvtxstb(act_name,action_names,ID_SIZE);
  if ( !actions(act_name) )                          ERROR
RECOVER
  act_pi = NULL;
ENDSEQ
  return(act_pi);
}

/******************************************************************************/
/**
\brief  ~CAU_Causality - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CAU_Causality"

                        CAU_Causality :: ~CAU_Causality ( )
{



}


