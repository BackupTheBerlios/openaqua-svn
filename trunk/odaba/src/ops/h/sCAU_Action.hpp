/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_Action

\brief    Conditional action
          A  conditional  action  allows  handling  events  for initializing new
          instances,  consistency checks for modifications and other purposes. A
          conditional  action  is  defined  in  a structure or property context.
          Conditional  actions may combine related object  instances or a set of
          instances  in the database. A conditional  action is identified by its
          name, which must be unique in the context of the causality.
          A  conditional action defines the direct  reaction on an event, i.e. a
          reaction  of the same object instance that has generated the event. It
          is,  however,  also  possible  to  define reactions of other (related)
          instances  via reactions. A conditional action is imbedded in pre- and
          post-processing.  The pre-processing  action can  suppress running the
          action  if  necessary.  The  post-processing  allows  final  handling 
          specific for a given context.

\date     $Date: 2006/03/13 21:30:04,68 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_Action_HPP
#define   CAU_Action_HPP

class     CAU_Action;

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
#ifndef   P_CAU_simpleAction_HPP
#define   P_CAU_simpleAction_HPP
#include  <sPI.hpp>
class       CAU_simpleAction;
PI_dcl     (CAU_simpleAction)
#endif
#ifndef   P_simpleAction_HPP
#define   P_simpleAction_HPP
#include  <sPI.hpp>
class       simpleAction;
PI_dcl     (simpleAction)
#endif
#include  <cActionType.h>
#include  <sCAU_simpleAction.hpp>
#pragma pack(8)

class  CAU_Action :public CAU_simpleAction
{
protected  :         char                                         structure[40] ATTR_ALIGN(4);                               // Structure for the event generating instance
protected  :         char                                         property[40];                                              // Event generating property
protected  :         PI(CAU_simpleAction)                         pre_handler;                                               // Pre-handler
protected  :         PI(CAU_simpleAction)                         post_handler;                                              // Post-handler
protected  :         PI(CAU_Causality)                            causality;                                                 // Related causality
protected  :         PI(CAU_Reaction)                             reactions_act;                                             // Reactions on events

public     :
                     char                                        *get_structure() { return(structure); }
                     char                                        *get_property() { return(property); }
                     PI(CAU_simpleAction)                        &get_pre_handler() { return(pre_handler); }
                     PI(CAU_simpleAction)                        &get_post_handler() { return(post_handler); }
                     PI(CAU_Causality)                           &get_causality() { return(causality); }
                     PI(CAU_Reaction)                            &get_reactions_act() { return(reactions_act); }
public     :         OPS7ImpExp                                          CAU_Action (char *action_name, ActionType actiontyp );
public     :         OPS7ImpExp                                          CAU_Action ( );
};

#pragma pack()
#endif
