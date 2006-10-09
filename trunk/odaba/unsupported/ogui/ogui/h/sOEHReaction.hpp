/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OEHReaction

\brief    O-Control Reaction
          An  O-control  reaction  defines  a stack for possible reactions. Only
          the  reaction  on  top  of  the  stack  is  executed when activating a
          reaction.

\date     $Date: 2006/05/04 12:32:24,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHReaction_HPP
#define   OEHReaction_HPP

class     OEHReaction;

#ifndef   DLO_OEHAction_HPP
#define   DLO_OEHAction_HPP
#include  <sOEHAction.hpp>
#include  <sDLO.h>
#endif
class     ODataWidget;
class     OEHAction;
class     OEHEvent;
class  OEHReaction
{
protected  :         OEHEvent                                    *event;                                                     // 
protected  :         DLO(OEHAction)                               action_list;                                               

public     :
                     OEHEvent                                    *get_event() { return(event); }
public     :                                        void AddAction (ODataWidget *ogui_causer, OEHAction *action, logical new_event_opt );
public     :                                        OEHAction *FindAction (char *act_names, char *loid, logical on_top_w=YES );
public     :                                        OEHAction *GetAction ( );
public     :                                        logical IsEmpty ( );
public     :                                             OEHReaction (OEHEvent *pOEHEvent );
public     :                                        logical RemoveAction (OEHAction *action, ODataWidget *ogui_causer );
public     :                                        logical RemoveAction (OEHAction *action );
public     :                                        void RemoveActions (ODataWidget *ogui_causer );
public     :                                             ~OEHReaction ( );
};

#endif
