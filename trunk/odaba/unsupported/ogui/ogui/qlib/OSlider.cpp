/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSlider

\brief    


\date     $Date: 2006/03/13 21:36:15,75 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSlider"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOSlider.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOSlider.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OSlider :: Activate ( )
{
  logical             ini  = stscini();
  logical             term = NO;
  OEHControlValue::Activate();

  if ( !ini && event_handling ) 
  {
      connect(this  ,SIGNAL(valueChanged(int)),
              this  ,SLOT  (storeToValue()));         
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ClearData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OSlider :: ClearData ( )
{

  setValue(0);

}

/******************************************************************************/
/**
\brief  Deactivate

\return term -

\param  data_only -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OSlider :: Deactivate (logical data_only )
{
  logical             ini  = stscini();
  logical             term = NO;
  if ( ini && event_handling && !data_only ) 
  {
    disconnect(this  ,SIGNAL(valueChanged(int)),
               this  ,SLOT  (storeToValue()));         
  }

  OEHControlValue::Deactivate(data_only);

  return(term);
}

/******************************************************************************/
/**
\brief  FillData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OSlider :: FillData ( )
{

  setValue(ods()->ValueGetInt());

}

/******************************************************************************/
/**
\brief  OSlider - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSlider"

                        OSlider :: OSlider (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QSlider (pODataWidget->WidgetQ()),
OEHControlValue (pODataWidget,oODataWidget,create_ods)
{



}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSlider"

                        OSlider :: OSlider (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QSlider (pODataWidget->WidgetQ()),
OEHControlValue (pODataWidget,oODataWidget,pODS)
{



}

/******************************************************************************/
/**
\brief  SetReadOnly


\param  fReadOnly -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OSlider :: SetReadOnly (logical fReadOnly )
{

  setEnabled(fReadOnly);

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return this -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OSlider :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  storeToValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void OSlider :: storeToValue ( )
{

  StoreToValue(value());

}


