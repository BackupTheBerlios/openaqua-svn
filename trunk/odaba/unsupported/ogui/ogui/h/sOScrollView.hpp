/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OScrollView

\brief    xxx


\date     $Date: 2006/03/13 21:34:35,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OScrollView_HPP
#define   OScrollView_HPP

class     OScrollView;

class     OWidgetDesignModeBase;
class     OWidgetDesignModeFactory;
#include  <sODataWidget.hpp>
class  OScrollView :public QScrollArea,
public ODataWidget
{

public     :
public     : virtual                             void DisableDesignMode ( );
public     : virtual                             OWidgetDesignModeBase *EnableDesignMode (OWidgetDesignModeFactory *dmode_factory=NULL );
public     : virtual                             QFrame *FrameQ ( );
public     :         OGUI7ImpExp                                         OScrollView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                     logical SetMargin (int32 imargin );
public     :                                     QWidget *WidgetQ ( );
public     : virtual OGUI7ImpExp                                         ~OScrollView ( );
};

#endif
