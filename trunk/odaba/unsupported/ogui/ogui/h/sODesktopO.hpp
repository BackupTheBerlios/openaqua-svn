/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODesktopO



\date     $Date: 2006/03/13 21:34:05,50 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODesktopO_HPP
#define   ODesktopO_HPP

class     ODesktopO;

#include  <sODataWidget.hpp>
class  ODesktopO :public QDesktopWidget,
public ODataWidget
{

public     :
public     :         OGUI7ImpExp                                         ODesktopO (ODataWidget *pODataWidget, logical create_ods );
public     :         OGUI7ImpExp                 QWidget *WidgetQ ( );
public     :         OGUI7ImpExp                                         ~ODesktopO ( );
};

#endif
