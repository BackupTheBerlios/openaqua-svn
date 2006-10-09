/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OMainWindow

\brief    


\date     $Date: 2006/03/13 21:34:27,53 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OMainWindow_HPP
#define   OMainWindow_HPP

class     OMainWindow;

#include  <sODataWidget.hpp>
class  OMainWindow :public QMainWindow,
public ODataWidget
{

public     :
public     :         OGUI7ImpExp                                         OMainWindow ( );
public     :                                     QWidget *WidgetQ ( );
public     :                                                             ~OMainWindow ( );
};

#endif
