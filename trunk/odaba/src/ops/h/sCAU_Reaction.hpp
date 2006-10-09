/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_Reaction

\brief    Reaction
          The  reaction defines  a link  between an  event and an action that is
          called  when  the  event  is  signaled.  The  reaction  defines a path
          between  the  generating  object  instance  and  the  reacting  object
          instances.  When the path is referring  to a collection each object in
          the collection will react on the event.
          Events  and related  action are  defined in causality. Causalities are
          either  part of  a dictionary  resource (structure,  member) or can be
          defined as global causalities.

\date     $Date: 2006/03/13 21:30:06,28 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_Reaction_HPP
#define   CAU_Reaction_HPP

class     CAU_Reaction;

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
#include  <cCAU_Delay_Types.h>
#include  <cCAU_RCT_Types.h>
#include  <cDB_Event.h>
#include  <sCAU_Action.hpp>
#include  <sCAU_RCT_Path.hpp>
#pragma pack(8)

class  CAU_Reaction
{
protected  :         uint32                                       __AUTOIDENT;                                               // Global identifying number
protected  :         CAU_RCT_Path                                 rct_path;                                                  // Property path to reacting object(s)
protected  :         CAU_RCT_Types                                rct_type;                                                  // Reaction types
protected  :         CAU_Delay_Types                              delay;                                                     // Reacting at end of transaction
protected  :         PI(CAU_Event)                                db_event;                                                  // Initiating event
protected  :         PI(CAU_Causality)                            action_causality;                                          // Related causality
protected  :         PI(CAU_Action)                               db_action;                                                 // Action

public     :
                     uint32                                       get___AUTOIDENT() { return(__AUTOIDENT); }
                     CAU_RCT_Path                                &get_rct_path() { return(rct_path); }
                     CAU_RCT_Types                                get_rct_type() { return(rct_type); }
                     CAU_Delay_Types                              get_delay() { return(delay); }
                     PI(CAU_Event)                               &get_db_event() { return(db_event); }
                     PI(CAU_Causality)                           &get_action_causality() { return(action_causality); }
                     PI(CAU_Action)                              &get_db_action() { return(db_action); }
public     :         OPS7ImpExp                  void set__AUTOIDENT (int32 autoident );
};

#pragma pack()
#endif
