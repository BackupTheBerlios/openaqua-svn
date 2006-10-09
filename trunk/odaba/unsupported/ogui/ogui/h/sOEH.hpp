/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OEH

\brief    Event Handler for O-Controls
          OEH  is an  event handler  class for  O-controls. On one hand OEH maps
          all  relevant  events  to  actions, which are activated for execution.
          Events,  which  are  not  mapped  to  an action, are associated with a
          defined  defaulT action, which  will be activated.  The set of default
          actions supported depends on the control type.

\date     $Date: 2006/05/04 10:50:32,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEH_HPP
#define   OEH_HPP

class     OEH;

#ifndef   DLL_OEHReactions_HPP
#define   DLL_OEHReactions_HPP
#include  <sOEHReactions.hpp>
#include  <sDLL.h>
#endif
class     ODataWidget;
class     OEHAction;
class     OEHActionHandler;
class     OEHEvent;
class     OEHReactions;
class     OIconSet;
#include  <cADK_DATAEVENT.h>
#include  <cADK_DBEVENT.h>
#include  <cADK_GUIEVENT.h>
#include  <cActionBubbleType.h>
#include  <sOActionList.hpp>
#include  <sOEHInternalEvent.hpp>
#include  <standard.hpp>
class  OEH :public QObject
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         ODataWidget                                 *oeh_widget;                                                // 
protected  :         DLL(OEHReactions)                            reactions;                                                 // 
protected  :         OEHAction                                   *cur_action;                                                // 
protected  :         QObject                                     *cur_sender;                                                // 
protected  :         ODataWidget                                 *cur_sender_odw;                                            // 
protected  :         int                                          cur_retval;                                                // 
protected  :         OEHActionHandler                            *default_hdl;                                               
protected  :         OEHActionHandler                            *user_hdl;                                                  
protected  :         std::list<int>                              *event_cache;                                               

public     :
                     ODataWidget                                 *get_oeh_widget() { return(oeh_widget); }
                     DLL(OEHReactions)                           &get_reactions() { return(reactions); }
                     OEHAction                                   *get_cur_action() { return(cur_action); }
                     QObject                                     *get_cur_sender() { return(cur_sender); }
                     int                                         &get_cur_retval() { return(cur_retval); }
                     OEHActionHandler                            *get_default_hdl() { return(default_hdl); }
                     OEHActionHandler                            *get_user_hdl() { return(user_hdl); }
                     std::list<int>                              *get_event_cache() { return(event_cache); }
public     :                                        OActionList ActionList ( );
public     :                                        void CacheEvent (ADK_DATAEVENT ogui_data_event );
public     :                                        void CacheEvent (ADK_DBEVENT ogui_db_event );
public     :                                        void CacheEvent (ADK_GUIEVENT ogui_event );
public     :                                        void CacheEvent (int etype );
public     :                                        void Close ( );
public     :                                        int8 ExecuteAction (char *act_names, logical default_action, logical no_user_handling );
public     :                                        int8 ExecuteDefaultAction (char *act_names );
public     :                                        int8 ExecuteReaction (OEHEvent *pOEHEvent, ODataWidget *causer );
public     :                                        int8 ExecuteReaction (OEHAction *pOEHAction, logical no_user_handling );
public     :                                        int8 ExecuteReaction (QAction *pQAction );
public     :                                        int8 ExecuteUserAction (char *act_names );
public     :                                        OEHAction *FindAction (char *act_names, char *loid, logical on_top_w=YES );
public     :                                        OEHAction *FindReaction (OEHEvent *pOEHEvent, ODataWidget *causer );
public     :                                        OEHReactions *FindReactions (ODataWidget *oODataWidget );
public     :                                        void FlushEventCache ( );
public     :                                        int8 GenerateEvent (ADK_DATAEVENT ogui_data_event, ODataWidget *causer );
public     :                                        int8 GenerateEvent (ADK_DBEVENT ogui_db_event, ODataWidget *causer );
public     :                                        int8 GenerateEvent (ADK_GUIEVENT ogui_event, ODataWidget *causer );
public     :                                        char *GetActiveAction ( );
public     :                                        char *GetActiveActionItem ( );
public     :                                        logical IsActionDisabled (char *act_names, char *loid );
public     :                                        logical IsActionGrouped (char *act_names, char *loid );
public     :                                        logical IsActionSeparated (char *act_names, char *loid );
public     :                                        logical IsActionToggled (char *act_names, char *loid );
public     :                                        logical IsActionVisible (char *act_names, char *loid );
public     :                                        logical IsEmpty ( );
public     :                                        OEHAction *NewAction (char *act_names, char *loid, logical sys_opt );
public     :                                             OEH (ODataWidget *pODataWidget );
public     :                                        logical RemoveAction (OEHAction *action );
public     :                                        logical RemoveReaction (OEHEvent *pOEHEvent, ODataWidget *oODataWidget, logical on_top_w=YES );
public     :                                        void ResetCauser ( );
public     :                                        logical SetActionDisabled (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionGrouped (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionIcon (char *act_names, char *loid, char *text, OIconSet *pOIcon );
public     :                                        logical SetActionSeparated (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionShortcut (char *act_names, char *loid, char *string );
public     :                                        logical SetActionText (char *act_names, char *loid, char *text, char *tip, char *status_tip, char *what );
public     :                                        logical SetActionToggled (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionVisible (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionWidget (char *act_names, char *loid, ODataWidget *pODataWidget );
public     :                                        QObject *SetCauser ( );
public     :                                        OEHAction *SetReaction (char *act_names, char *loid, char *parent_loid, OEHEvent *pOEHEvent, ODataWidget *oODataWidget, logical default_w=NO, ActionBubbleType pass_opt_w=ABT_never, char *pass_to=NULL );
public     :                                        void SetUserActionHdl (OEHActionHandler *pOEHActionHandler );
public     : public slots:                          logical xx_doClicked ( );
public     : public slots:                          logical xx_doClicked (QObject *pQObject, int id );
public     :                                             ~OEH ( );
};

#endif
