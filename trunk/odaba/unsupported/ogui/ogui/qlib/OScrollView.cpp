/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OScrollView

\brief    xxx


\date     $Date: 2006/03/13 21:36:13,92 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OScrollView"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sODataWidgetEventFilter.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sOWidgetDesignModeFactory.hpp>
#include  <sOScrollView.hpp>


/******************************************************************************/
/**
\brief  DisableDesignMode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableDesignMode"

void OScrollView :: DisableDesignMode ( )
{

  ODataWidget::DisableDesignMode();

  setAcceptDrops(FALSE);

}

/******************************************************************************/
/**
\brief  EnableDesignMode - 


\return designer_mode -

\param  dmode_factory -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableDesignMode"

OWidgetDesignModeBase *OScrollView :: EnableDesignMode (OWidgetDesignModeFactory *dmode_factory )
{

  ODataWidget::EnableDesignMode(dmode_factory);

  setAcceptDrops(TRUE);

  return(design_mode);
}

/******************************************************************************/
/**
\brief  FrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OScrollView :: FrameQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  OScrollView - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OScrollView"

                        OScrollView :: OScrollView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QScrollArea(pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget (pODataWidget,oODataWidget,create_ods)

{

  new ODataWidgetEventFilter(this);

}

/******************************************************************************/
/**
\brief  SetMargin - sets the margin of the scrollarea
        Sets  the  margins  around  the  scrolling  area to left, top, right and
        bottom  all  the  same.  This  is  useful  for  applications  such  as 
        spreadsheets  with "locked" rows  and columns. The  marginal space is is
        left blank; put widgets in the unused area.

        By default all margins are zero.

\return term -

\param  imargin -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMargin"

logical OScrollView :: SetMargin (int32 imargin )
{
  QWidget                *qw = WidgetQ();
  logical                 term = NO;
  if ( qw && qw->layout() )
    qw->layout()->setMargin(imargin);
  else
    setContentsMargins(imargin, imargin, imargin, imargin);
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OScrollView :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  ~OScrollView - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OScrollView"

                        OScrollView :: ~OScrollView ( )
{



}


