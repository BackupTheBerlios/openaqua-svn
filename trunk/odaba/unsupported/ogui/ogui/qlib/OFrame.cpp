/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OFrame

\brief    Splitter Window
          The  class provides a number of  areas separated by a splitter handle.
          The  controlls  are  added  to  this area according to the sequence of
          definition. Each control will get its own area.

\date     $Date: 2006/05/07 18:22:51,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFrame"

#include  <pogui7.h>
#include  <mOFrame.h>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODataWidget.hpp>
#include  <sODialog.hpp>
#include  <sOFrame.hpp>


/******************************************************************************/
/**
\brief  Activate

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OFrame :: Activate ( )
{

  return ( OEHControlValue::ActivateValue(YES,NO) );



}

/******************************************************************************/
/**
\brief  DA_CancelClose

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_CancelClose"

logical OFrame :: DA_CancelClose ( )
{
  QWidget   *qparent = WidgetQ() ? WidgetQ()->parentWidget() : NULL;
  logical     term    = NO;
BEGINSEQ
  OEHDataWidget::DA_Cancel();
  
  if ( !qparent )                                    ERROR
  
  if ( qparent->inherits("QDialog") )
    ((ODialog *)(QDialog *)qparent)->reject();
  else
    qparent->close();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Refresh

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Refresh"

logical OFrame :: DA_Refresh ( )
{
  logical     term = NO;
BEGINSEQ
  term = OEHControlValue::DA_Refresh();
  
  if ( od_control->RefreshElements() )              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_SaveClose

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SaveClose"

logical OFrame :: DA_SaveClose ( )
{
  QWidget   *qwidget = WidgetQ();
  QWidget   *qparent = qwidget ? qwidget->parentWidget() : NULL;
  logical     term    = NO;
BEGINSEQ
  OEHDataWidget::DA_Save();
/// q3 there is no mainWidget
// if ( qwidget == qApp->mainWidget() )
//    term = Quit();
//  else
  {
    if ( !qparent )                                    ERROR

    if ( qparent->inherits("QDialog") )
      ((ODialog *)(QDialog *)qparent)->accept();
    else
      qparent->close();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate

\return term - 

\param  data_only
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OFrame :: Deactivate (logical data_only )
{

  return ( OEHControlValue::DeactivateValue(YES,NO,data_only) );



}

/******************************************************************************/
/**
\brief  FillData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OFrame :: FillData ( )
{

  ods()->InstInit();

}

/******************************************************************************/
/**
\brief  FrameQ

\return pQFrame

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OFrame :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  OFrame

-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFrame"

     OFrame :: OFrame (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QFrame (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OEHControlValue (pODataWidget,oODataWidget,create_ods)
{
}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFrame"

     OFrame :: OFrame (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QFrame (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OEHControlValue (pODataWidget,oODataWidget,pODS)
{
  SetWindowFlags(YES,NO,YES,NO,NO,NO,NO,NO,NO);
}

/******************************************************************************/
/**
\brief  ValueReset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueReset"

void OFrame :: ValueReset ( )
{
  if ( !ods()->IsSingleReference() || ods()->Item()->AutoPosition() )
    OEHControlValue::ValueReset();
  else
    OEHControlValue::ValueSelected();

}

/******************************************************************************/
/**
\brief  WidgetQ

\return qwidget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OFrame :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  getEnabled

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OFrame :: getEnabled ( )
{

  return YES;

}

/******************************************************************************/
/**
\brief  resizeEvent


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "resizeEvent"

void OFrame :: resizeEvent ( )
{
}

/******************************************************************************/
/**
\brief  ~OFrame


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OFrame"

     OFrame :: ~OFrame ( )
{
  Deactivate(NO);
}


