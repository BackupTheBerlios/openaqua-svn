/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OTimeEdit

\brief    


\date     $Date: 2006/06/26 16:41:39,42 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTimeEdit"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOTimeEdit.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOTimeEdit.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OTimeEdit :: Activate ( )
{
  logical             ini  = stscini();
  logical             term = NO;
  OEHControlValue::Activate();
  
  if ( !ini && event_handling )
  {
      connect(this  ,SIGNAL(timeChanged(const QTime &)),
              this  ,SLOT  (storeToValue()));         
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ClearData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OTimeEdit :: ClearData ( )
{

  setTime(QTime());


}

/******************************************************************************/
/**
\brief  Deactivate - 


\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OTimeEdit :: Deactivate (logical data_only )
{
  logical             ini  = stscini();
  logical             term = NO;
  if ( ini && event_handling && !data_only )
  {
    disconnect(this ,SIGNAL(timeChanged(const QTime &)),
               this ,SLOT  (storeToValue()));         
  }

  OEHControlValue::Deactivate(data_only);
  return(term);
}

/******************************************************************************/
/**
\brief  FillData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OTimeEdit :: FillData ( )
{
  dbtm        tm;
  tm = ods()->ValueGetTime();
  setTime(QTime(tm.GetHour(),tm.GetMinute(),tm.GetSecond(),tm.GetHSecond()*10));


}

/******************************************************************************/
/**
\brief  OTimeEdit - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTimeEdit"

     OTimeEdit :: OTimeEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QTimeEdit (pODataWidget->WidgetQ()),
OEHControlValue(pODataWidget,oODataWidget,create_ods)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  i01 - 


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTimeEdit"

     OTimeEdit :: OTimeEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QTimeEdit (pODataWidget->WidgetQ()),
OEHControlValue(pODataWidget,oODataWidget,pODS)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  SetReadOnly - 



\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OTimeEdit :: SetReadOnly (logical fReadOnly )
{

  setEnabled(!fReadOnly);

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return this - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OTimeEdit :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  paintEvent - 



\param  pQPaintEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "paintEvent"

void OTimeEdit :: paintEvent (QPaintEvent *pQPaintEvent )
{
QPalette pInvalid,pValid;

  pInvalid.setColor(QPalette::Background,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::Foreground,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::Text,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::Button,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::ButtonText,pValid.color(QPalette::Base));

  if(ods()->Value() == ""){
    setPalette(pInvalid);
  }else{
    setPalette(pValid);
  }
  
  QTimeEdit::paintEvent(pQPaintEvent);


}

/******************************************************************************/
/**
\brief  storeToValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void OTimeEdit :: storeToValue ( )
{

  StoreToValue( dbtm(time().hour(),time().minute(),
                time().second(),time().msec()/10) ); 


}


