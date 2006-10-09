/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODockArea

\brief    ODockArea
          Changes  any Control  into a  dockarea, what  means, that you can dock
          windows on all edges.
          just wrap any Control by
          OControl myControl(parent....)
          odarea = new ODockArea(parent,myControl);
          and move add it to your layout.
          ..359 degrees) or the dialog layout needs a square widget.

          Both  API- and UI-wise, the dial is  very similar to a slider. Indeed,
          when  wrapping() is  FALSE (the  default) there  is no real difference
          between  a slider  and a  dial. They  have the same signals, slots and
          member  functions, all of which do the  same things. Which one you use
          depends only on your taste and on the application.

\date     $Date: 2006/03/13 21:34:06,03 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODockArea_HPP
#define   ODockArea_HPP

class     ODockArea;

#define  DOCKSIZE                                  5
class     ODS;
class     ODockWidget;
class     OPopupMenu;
#include  <sDAlign.hpp>
#include  <sODataWidget.hpp>
class  ODockArea :public QMainWindow,
public ODataWidget
{

public     :
public     :         OGUI7ImpExp                 void AddDockWidget (ODockWidget *pODockWidget, Qt::DockWidgetArea dockEdge );
public     :         OGUI7ImpExp                 void AddDockWidget (ODockWidget *pODockWidget, DAlign &dalign );
public     :                                     Qt::DockWidgetArea GetDockPosition (DAlign &dalign );
public     :         OGUI7ImpExp                                         ODockArea (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, QWidget *centralWidget );
public     : virtual                             QWidget *WidgetQ ( );
};

#endif
