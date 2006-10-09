/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OMenu

\brief    


\date     $Date: 2006/03/13 21:34:27,60 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OMenu_HPP
#define   OMenu_HPP

class     OMenu;

class     OEHAction;
#include  <sODataWidget.hpp>
#include  <sbsts.hpp>
class  OMenu :public bsts,
public ODataWidget
{
protected  :         QWidget                                     *qwidget;                                                   //
protected  :         OEHAction                                   *menu_action;                                               //

public     :
                     QWidget                                     *get_qwidget() { return(qwidget); }
                     OEHAction                                   *get_menu_action() { return(menu_action); }
public     :                                     void AddAction (QAction *pQAction, QAction *before_action=NULL );
public     :                                     void AddAction (OEHAction *action );
public     :                                     void AddActions (QList<QAction *> *pQActionList, QAction *before_action=NULL );
public     :                                     void AddMenu (QAction *pQAction, QMenu *pQMenu, QAction *before_action=NULL );
public     :                                     void AddMenu (OEHAction *action, QAction *before_action=NULL );
public     :                                     void AddSeparator (QAction *before_action=NULL );
public     :                                                             OMenu (ODataWidget *pODataWidget, ODataWidget *oODataWidget );
public     :                                     logical SetupActions (OEHAction *action );
public     :                                                             ~OMenu ( );
};

#endif
