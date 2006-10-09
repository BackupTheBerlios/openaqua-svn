/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OWorkspace

\brief    


\date     $Date: 2006/03/13 21:34:53,25 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWorkspace_HPP
#define   OWorkspace_HPP

class     OWorkspace;

class     ODataWidget;
class     OWidgetDesignModeBase;
class     OWidgetDesignModeFactory;
#include  <sOEHDataWidget.hpp>
class  OWorkspace :public QWorkspace,
public OEHDataWidget
{

public     :
public     : virtual                             void DisableDesignMode ( );
public     : virtual                             OWidgetDesignModeBase *EnableDesignMode (OWidgetDesignModeFactory *dmode_factory=NULL );
public     :         OGUI7ImpExp                                         OWorkspace (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                     QWidget *WidgetQ ( );
public     :         OGUI7ImpExp                                         ~OWorkspace ( );
};

#endif
