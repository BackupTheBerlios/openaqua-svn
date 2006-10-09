/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OEHAction

\brief    Action
          An  action  is  defined  in  the  context  of  an event for a GUI data
          widget.

\date     $Date: 2006/07/09 11:32:53,10 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHAction_HPP
#define   OEHAction_HPP

class     OEHAction;

#ifndef   DLL_ODataWidget_HPP
#define   DLL_ODataWidget_HPP
#include  <sODataWidget.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLO_OWidget_HPP
#define   DLO_OWidget_HPP
#include  <sOWidget.hpp>
#include  <sDLO.h>
#endif
class     DAction;
class     DPixmap;
class     ODataWidget;
class     OEH;
class     OEHAction;
class     OEHActionList;
class     OEHShortcut;
class     OFont;
class     OIconSet;
class     OWidget;
#include  <cActionBubbleType.h>
class  OEHAction :public QObject
{
protected  :                                                      Q_OBJECT;                                                  // Action name
protected  :         QAction                                     *qaction;                                                   // List of causers for the action
protected  :         OEH                                         *oeh;                                                       // Default action
protected  :         char                                        *action;                                                    // Disabled action
protected  :         OEHActionList                               *childs;                                                    // Action is toggled
protected  :         QActionGroup                                *group;                                                     // 
protected  :         ODataWidget                                 *widget;                                                    // 
protected  :         DLO(OWidget)                                 causer;                                                    // 
protected  :         logical                                      is_default;                                                // 
protected  :         logical                                      is_active;                                                 // 
protected  :         logical                                      separate;                                                  // 
protected  :         ActionBubbleType                             pass;                                                      // 
protected  :         char                                        *pass_info;                                                 // 

public     :
                     QAction                                     *get_qaction() { return(qaction); }
                     OEH                                         *get_oeh() { return(oeh); }
                     char                                        *get_action() { return(action); }
                     OEHActionList                               *get_childs() { return(childs); }
                     QActionGroup                                *get_group() { return(group); }
                     ODataWidget                                 *get_widget() { return(widget); }
                     DLO(OWidget)                                &get_causer() { return(causer); }
                     logical                                      get_is_active() { return(is_active); }
                     logical                                      get_separate() { return(separate); }
                     ActionBubbleType                            &get_pass() { return(pass); }
                     char                                        *get_pass_info() { return(pass_info); }
public     :                                        logical AddAction (OEHAction *pOEHAction );
public     :                                        void AddCauser (OWidget *pOWidget );
public     :                                        char *GetAction ( );
public     :                                        char *GetName ( );
public     :                                        logical Is (char *act_names, char *loid );
public     :                                        logical IsDefault ( );
public     :                                        logical IsDisabled ( );
public     :                                        logical IsGrouped ( );
public     :                                        logical IsSeparated ( );
public     :                                        logical IsToggled ( );
public     :                                        logical IsVisible ( );
public     :                                             OEHAction (char *act_names, char *loid, QAction *pQAction, OEH *pOEH );
public     :                                        void RemoveCauser (OWidget *pOWidget );
public     :                                        void SetActive (logical fEnabled );
public     :                  OGUIImpExp            void SetDefault (logical def_action );
public     :                  OGUIImpExp            void SetDisabled (logical disabled_opt );
public     :                  OGUIImpExp            void SetFont (OFont *pOFont );
public     :                  OGUIImpExp            void SetFont (char *text, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled );
public     :                  OGUIImpExp            void SetFont ( );
public     :                  OGUIImpExp            void SetGrouped (logical group_opt );
public     :                  OGUIImpExp            void SetIcon (char *text, OIconSet *pOIcon );
public     :                  OGUIImpExp            void SetIcon (char *text, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled );
public     :                  OGUIImpExp            void SetIcon ( );
public     :                  OGUIImpExp            void SetPass (ActionBubbleType pass_opt, char *pass_to=NULL );
public     :                  OGUIImpExp            void SetSeparated (logical sep_opt );
public     :                  OGUIImpExp            void SetShortcut (OEHShortcut *pOEHShortcut );
public     :                  OGUIImpExp            void SetText (char *text, char *tip, char *status_tip, char *what );
public     :                  OGUIImpExp            void SetToggled (logical toggle_opt );
public     :                  OGUIImpExp            void SetVisible (logical fEnabled );
public     :                  OGUIImpExp            void SetWidget (ODataWidget *pODataWidget );
public     :                                        logical Setup (DAction *pDAction );
public     : public slots:                          logical doTriggered (bool bChecked );
public     :                                             ~OEHAction ( );
};

#endif
