/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OLabel

\brief    


\date     $Date: 2006/03/13 21:35:55,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OLabel"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOLabelDesignMode.hpp>
#include  <sOLabel.hpp>


/******************************************************************************/
/**
\brief  EnableDesignMode - sets widget into designmode



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableDesignMode"

void OLabel :: EnableDesignMode ( )
{

/*
  if ( !dmode_factory )
    design_mode = (OWidgetDesignModeBase*) new OLabelDesignMode(this);
  else
    design_mode = dmode_factory->CreateDM(this);
*/

}

/******************************************************************************/
/**
\brief  FrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OLabel :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetText - 


\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

char *OLabel :: GetText ( )
{
  static QByteArray  static_qba;
  return(QS2SZ_P(QLabel::text(),static_qba));

}

/******************************************************************************/
/**
\brief  OLabel - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OLabel"

                        OLabel :: OLabel (ODataWidget *pODataWidget, ODataWidget *oODataWidget )
                     : QLabel( pODataWidget ? pODataWidget->WidgetQ() : NULL), 
ODataWidget (pODataWidget,oODataWidget,NO),
  drawFocusRect(YES)
{



}

/******************************************************************************/
/**
\brief  SetDrawFocusRect - 



\param  f -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDrawFocusRect"

void OLabel :: SetDrawFocusRect (logical f )
{

  drawFocusRect = f;
  update();


}

/******************************************************************************/
/**
\brief  SetText - 



\param  rcQString -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void OLabel :: SetText (const QString &rcQString )
{

  QLabel::setText(rcQString);

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return pQWidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OLabel :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  drawContents - 



\param  pQPainter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "drawContents"

void OLabel :: drawContents (QPainter *pQPainter )
{

/* No drawContents
  QLabel::drawContents(pQPainter);
    
  if ( drawFocusRect && buddy() && buddy()->hasFocus() )
  {
    QRect   r(contentsRect());
    style().drawPrimitive(QStyle::PE_FocusRect,pQPainter,r,colorGroup());
  }
*/

}

/******************************************************************************/
/**
\brief  eventFilter - 


\return cond -

\param  watched -
\param  e -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eventFilter"

bool OLabel :: eventFilter (QObject *watched, QEvent *e )
{

  if ( drawFocusRect && watched == buddy()   && 
       ( e->type() == QEvent::FocusIn || 
         e->type() == QEvent::FocusOut     )    )
    update();

  return QLabel::eventFilter(watched,e);
}

/******************************************************************************/
/**
\brief  setBuddy - 



\param  pQWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setBuddy"

void OLabel :: setBuddy (QWidget *pQWidget )
{

BEGINSEQ
  if ( !pQWidget )                                   LEAVESEQ
  
  QLabel::setBuddy(pQWidget);
  pQWidget->installEventFilter(this);

ENDSEQ

}


