/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OEHReactions

\brief    List of reactions
          The  class  lists  the  reactions  for  a  certain GUI resource. Since
          reactions  for  a  control  can  be  caused by different reaources (as
          buttons  associated  with  a  control), actions are collected for each
          resource associated with the event handling control.

\date     $Date: 2006/05/03 21:37:42,89 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHReactions_HPP
#define   OEHReactions_HPP

class     OEHReactions;

#ifndef   DLL_OEHReaction_HPP
#define   DLL_OEHReaction_HPP
#include  <sOEHReaction.hpp>
#include  <sDLL.h>
#endif
class     ODataWidget;
class     OEHAction;
class     OEHEvent;
class  OEHReactions
{
protected  :         ODataWidget                                 *ogui_causer;                                               // 
protected  :         QObject                                     *qt_causer;                                                 
protected  :         DLL(OEHReaction)                             reactions;                                                 

public     :
                     ODataWidget                                 *get_ogui_causer() { return(ogui_causer); }
                     QObject                                     *get_qt_causer() { return(qt_causer); }
                     DLL(OEHReaction)                            &get_reactions() { return(reactions); }
public     :                                        OEHAction *FindReaction (OEHEvent *pOEHEvent );
public     :                                        logical IsEmpty ( );
public     :                                             OEHReactions (ODataWidget *oODataWidget );
public     :                                        void RemoveAction (OEHAction *action );
public     :                                        void RemoveReaction (OEHEvent *pOEHEvent, logical on_top_w=YES );
public     :                                        logical SetReaction (OEHEvent *pOEHEvent, OEHAction *action, logical new_event_opt );
public     :                                             ~OEHReactions ( );
};

#endif
