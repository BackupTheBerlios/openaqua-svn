/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OPopupMenu

\brief    Popup menu


\date     $Date: 2006/03/13 21:34:29,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPopupMenu_HPP
#define   OPopupMenu_HPP

class     OPopupMenu;

class     ODataWidget;
#include  <sOMenu.hpp>
class  OPopupMenu :public QMenu,
public OMenu
{

public     :
public     :         OGUI7ImpExp                                         OPopupMenu (ODataWidget *pODataWidget, ODataWidget *oODataWidget );
public     :         OGUI7ImpExp                                         OPopupMenu (ODataWidget *pODataWidget );
public     :                                     QWidget *WidgetQ ( );
public     :                                                             ~OPopupMenu ( );
};

#endif
