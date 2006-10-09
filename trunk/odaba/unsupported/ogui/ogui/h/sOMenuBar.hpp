/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OMenuBar

\brief    Menu bar


\date     $Date: 2006/03/13 21:34:27,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OMenuBar_HPP
#define   OMenuBar_HPP

class     OMenuBar;

class     ODataWidget;
#include  <sOMenu.hpp>
class  OMenuBar :public QMenuBar,
public OMenu
{

public     :
public     :         OGUI7ImpExp                                         OMenuBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget );
public     :                                     QWidget *WidgetQ ( );
public     :                                                             ~OMenuBar ( );
};

#endif
