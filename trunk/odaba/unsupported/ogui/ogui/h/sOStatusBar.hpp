/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OStatusBar

\brief    


\date     $Date: 2006/03/13 21:34:42,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OStatusBar_HPP
#define   OStatusBar_HPP

class     OStatusBar;

class     OWidget;
#include  <sODataWidget.hpp>
class  OStatusBar :public QStatusBar,
public ODataWidget
{

public     :
public     :         OGUI7ImpExp                 void AddElement (OWidget *o_element );
public     :         OGUI7ImpExp                                         OStatusBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical show_grip=YES );
public     :                                     QWidget *WidgetQ ( );
};

#endif
