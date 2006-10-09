/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/03/13 21:35:38,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODockArea"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODockWidget.hpp>
#include  <sOPopupMenu.hpp>
#include  <sODockArea.hpp>


/******************************************************************************/
/**
\brief  AddDockWidget - adds a docked control
        add   a   odockwidget   control   (a   toolbar   or   anything)  to a <a
        href="p:/qt/doc/html/qt.html#Dock-enum">edge</a>

-------------------------------------------------------------------------------
\brief  i01


\param  pODockWidget -
\param  dockEdge -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddDockWidget"

void ODockArea :: AddDockWidget (ODockWidget *pODockWidget, Qt::DockWidgetArea dockEdge )
{


  addDockWidget(dockEdge,pODockWidget);

}

/******************************************************************************/
/**
\brief  i02


\param  pODockWidget -
\param  dalign -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddDockWidget"

void ODockArea :: AddDockWidget (ODockWidget *pODockWidget, DAlign &dalign )
{

  AddDockWidget(pODockWidget,GetDockPosition(dalign));
  
  


}

/******************************************************************************/
/**
\brief  GetDockPosition - 


\return dockEdge -

\param  dalign -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDockPosition"

Qt::DockWidgetArea ODockArea :: GetDockPosition (DAlign &dalign )
{
  Qt::DockWidgetArea  dockEdge = Qt::AllDockWidgetAreas;
  switch ( dalign.Hori(HPS_undefined) )
  {
    case HPS_InnerLeft  :
    case HPS_OuterLeft  : dockEdge = Qt::LeftDockWidgetArea;
                          break;
    
    case HPS_InnerRight :
    case HPS_OuterRight : dockEdge = Qt::RightDockWidgetArea;
                          break;
    
    default             : 
       switch ( dalign.Vert(VPS_undefined) )
       {
         case VPS_InnerBottom :
         case VPS_OuterBottom : dockEdge = Qt::BottomDockWidgetArea;
                                break;
         case VPS_InnerTop    :
         case VPS_OuterTop    : dockEdge = Qt::TopDockWidgetArea;
                                break;
       }
  }


  return(dockEdge);
}

/******************************************************************************/
/**
\brief  ODockArea - Constructor
        Wraps Dockareas arround any OWidget


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS -
\param  centralWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODockArea"

                        ODockArea :: ODockArea (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, QWidget *centralWidget )
                     : QMainWindow(pODataWidget->WidgetQ()),
ODataWidget(pODataWidget,oODataWidget,pODS)
{

  if ( centralWidget )
    setCentralWidget(centralWidget);
  setWindowFlags(windowFlags() ^ Qt::Window );


}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODockArea :: WidgetQ ( )
{


  return(this);
}


