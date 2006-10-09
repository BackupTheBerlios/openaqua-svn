/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    ODataWidgetEventFilter

\brief    


\date     $Date: 2006/03/21 11:59:10,39 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODataWidgetEventFilter"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sODataWidgetEventFilter.hpp>


/******************************************************************************/
/**
\brief  ODataWidgetEventFilter - Konstruktor



\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataWidgetEventFilter"

                        ODataWidgetEventFilter :: ODataWidgetEventFilter (ODataWidget *pODataWidget )
                     : QObject (pODataWidget->WidgetQ()),
  odw(pODataWidget)
{

BEGINSEQ
  if ( !pODataWidget )                               ERROR
  pODataWidget->WidgetQ()->installEventFilter(this);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  eventFilter - 


\return term -

\param  pQObject -
\param  pQEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eventFilter"

bool ODataWidgetEventFilter :: eventFilter (QObject *pQObject, QEvent *pQEvent )
{
  QWidget     *qwidget;
  bool         term = false;
BEGINSEQ
/*
  switch ( pQEvent->type() ) 
  {
    case QEvent::DragEnter :
    case QEvent::DragMove  :
    case QEvent::DragLeave :
    case QEvent::Drop      : 
      if ( odw->get_parent_odw() && 
           (qwidget = odw->get_parent_odw()->WidgetQ()) )
      {
        term = QApplication::sendEvent(qwidget,pQEvent);
        LEAVESEQ
      }
    
    default : term = false;
  }
*/
ENDSEQ
  return(term);
}


