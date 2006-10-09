/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_Event

\brief    Event
          An  event  is  defined  through  the  state  transition of one or more
          object  instances.  The  event  defines potential state transitions by
          means  of pre  and post  condition, i.e.  pre- and post-states. Events
          can  be defined on the  structure or property level  as well as on the
          extent level.
          An  event is fired when the instance state before modification returns
          a  true  pre-condition  and  when  the state of the instance after the
          modification  returns a true  post-condition. Pre- and post-conditions
          can  be defined as functions, expressions or any other type of action.
          When  not  defining  pre-  and  post condition any modification on the
          instance is considered as event. 
          Special  events are  system events  that are  signaled by the database
          system  and usually indicate a change in  the process or life state of
          the  instance,  which  cannot  be  expressed  in  terms  of  pre-  and
          post-conditions. 
          Event  definitions  are  stored  globally  with  a unique name that is
          constructed  from the structure name, the  extent or property name and
          the  event name. This  allows referring to  an event from a far linked
          instance or registering instances for event observation. 
          When  an event is fired it can  be handled by an event handler defined
          in  the  causality  rule,  which  is  a  function, expression or other
          action again.

\date     $Date: 2006/03/13 21:30:06,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_Event_HPP
#define   CAU_Event_HPP

class     CAU_Event;

#ifndef   P_CAU_Causality_HPP
#define   P_CAU_Causality_HPP
#include  <sPI.hpp>
class       CAU_Causality;
PI_dcl     (CAU_Causality)
#endif
#ifndef   P_CAU_Reaction_HPP
#define   P_CAU_Reaction_HPP
#include  <sPI.hpp>
class       CAU_Reaction;
PI_dcl     (CAU_Reaction)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#include  <cDB_Event.h>
#include  <sCAU_simpleAction.hpp>
#pragma pack(8)

class  CAU_Event
{
protected  :         char                                         sys_ident[40];                                             // Event name
protected  :         CAU_simpleAction                             pre_condition;                                             // Pre-condition
protected  :         CAU_simpleAction                             post_condition;                                            // Post-condition
protected  :         DB_Event                                     int_event;                                                 // Global event
protected  :         logical                                      generate;                                                  // Global event
protected  :         PI(CAU_Causality)                            causality;                                                 // Related causality
protected  :         PI(CAU_Reaction)                             reactions_evt;                                             // Reaction to the event

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     CAU_simpleAction                            &get_pre_condition() { return(pre_condition); }
                     CAU_simpleAction                            &get_post_condition() { return(post_condition); }
                     DB_Event                                     get_int_event() { return(int_event); }
                     logical                                      get_generate() { return(generate); }
                     PI(CAU_Causality)                           &get_causality() { return(causality); }
                     PI(CAU_Reaction)                            &get_reactions_evt() { return(reactions_evt); }
};

#pragma pack()
#endif
