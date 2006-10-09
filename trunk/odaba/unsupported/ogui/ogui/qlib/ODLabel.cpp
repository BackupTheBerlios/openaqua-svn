/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    ODLabel



\date     $Date: 2006/04/28 17:05:15,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODLabel"

#include  <pogui7.h>
#include  <sODControl.hpp>
#include  <sODataWidget.hpp>
#include  <sODLabel.hpp>


/******************************************************************************/
/**
\brief  GetText - 


\return label_text - Label text

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

char *ODLabel :: GetText ( )
{
  static QByteArray  static_qba;
  return (   controlWidget 
           ? QS2SZ_P(((OLabel *)controlWidget)->text(),static_qba)
           : NULL );

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 

\param  position
\param  dsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ODLabel :: Initialize (DPoint &position, DSize &dsize )
{
  logical                 term = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  ODLabel - 


\return term - 

\param  pODControl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODLabel"

     ODLabel :: ODLabel (ODControl *pODControl )
                     : ODControl (pODControl,NULL),
  target(0),
  drawFocusRect(0)
{
  QWidget    *parent_widget = parent->ControlWidget() ? parent->ControlWidget()->WidgetQ() : NULL;
  OLabel     *ol;
  ol = new OLabel(ClientWidgetParent(),WidgetOwner());
  controlWidget = ol;
  
  if ( parent_widget )
  {
    ol->setBuddy(parent_widget);  
    ol->setFocusProxy(parent_widget);  
  }
  
  ol->SetDrawFocusRect(drawFocusRect);
  
  BindClientWidget(ol,0);

//  loadText(); kommt aus OADI (SetLabelText)


}

/******************************************************************************/
/**
\brief  SetDrawFocusRect


\param  fEnable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDrawFocusRect"

void ODLabel :: SetDrawFocusRect (logical fEnable )
{
  OLabel     *ol = (OLabel *)controlWidget;
  drawFocusRect = fEnable;

  ol->SetDrawFocusRect(drawFocusRect);

}

/******************************************************************************/
/**
\brief  SetText - 


\return term - 

\param  label_text - Label text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

logical ODLabel :: SetText (char *label_text )
{
  OLabel     *ol = (OLabel *)controlWidget;
  logical     term = NO;
  ol->setText(SZ2QS(label_text));
  return(term);
}


