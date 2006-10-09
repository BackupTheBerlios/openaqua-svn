/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/03/13 21:30:05,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_Causality_HPP
#define   CAU_Causality_HPP

class     CAU_Causality;

#ifndef   P_CAU_Action_HPP
#define   P_CAU_Action_HPP
#include  <sPI.hpp>
class       CAU_Action;
PI_dcl     (CAU_Action)
#endif
#ifndef   P_CAU_Event_HPP
#define   P_CAU_Event_HPP
#include  <sPI.hpp>
class       CAU_Event;
PI_dcl     (CAU_Event)
#endif
#ifndef   P_CAU_Reaction_HPP
#define   P_CAU_Reaction_HPP
#include  <sPI.hpp>
class       CAU_Reaction;
PI_dcl     (CAU_Reaction)
#endif
#pragma pack(8)

class  CAU_Causality
{
protected  :         PI(CAU_Action)                               actions;                                                   // Action
protected  :         PI(CAU_Event)                                event;                                                     // Event
protected  :         PI(CAU_Reaction)                             reactions;                                                 // Reactions

public     :
                     PI(CAU_Action)                              &get_actions() { return(actions); }
                     PI(CAU_Event)                               &get_event() { return(event); }
                     PI(CAU_Reaction)                            &get_reactions() { return(reactions); }
public     :         OPS7ImpExp                                          CAU_Causality ( );
public     :         OPS7ImpExp                  PI(CAU_Action) *LocateAction (char *action_names );
public     :         OPS7ImpExp                                          ~CAU_Causality ( );
};

#pragma pack()
#endif
