/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSpinBox

\brief    


\date     $Date: 2006/03/13 21:36:16,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSpinBox"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOSpinBox.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOSpinBox.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OSpinBox :: Activate ( )
{
  logical             ini  = stscini();
  logical             term = NO;
  OEHControlValue::Activate();
  
  if ( !ini && event_handling ) 
  {
      connect(this  ,SIGNAL(valueChanged(int)),
              this  ,SLOT  (storeValue()));         
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

void OSpinBox :: ClearData ( )
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

logical OSpinBox :: Deactivate (logical data_only )
{
  logical             ini  = stscini();
  logical             term = NO;
  if ( ini && event_handling && !data_only ) 
  {
    disconnect(this  ,SIGNAL(valueChanged(int)),
               this  ,SLOT  (storeValue()));         
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

void OSpinBox :: FillData ( )
{

  setValue(ods()->ValueGetInt());

}

/******************************************************************************/
/**
\brief  OSpinBox - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSpinBox"

                        OSpinBox :: OSpinBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QSpinBox (pODataWidget->WidgetQ()),
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
#define    MOD_ID  "OSpinBox"

                        OSpinBox :: OSpinBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QSpinBox (pODataWidget->WidgetQ()),
OEHControlValue (pODataWidget,oODataWidget,pODS)
{



}

/******************************************************************************/
/**
\brief  SetReadOnly - 



\param  fReadOnly -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OSpinBox :: SetReadOnly (logical fReadOnly )
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

QWidget *OSpinBox :: WidgetQ ( )
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

void OSpinBox :: storeToValue ( )
{

  StoreToValue(value());

}


