/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODial

\brief    Dial
          The  ODial class provides a rounded  range control (like a speedometer
          or potentiometer).

          ODial  is  used  when  the  user  needs  to  control  a value within a
          program-definable   range,   and   the   range   either   wraps around
          (typically,  0..359  degrees)  or  the  dialog  layout  needs a square
          widget.

          Both  API- and UI-wise, the dial is  very similar to a slider. Indeed,
          when  wrapping() is  FALSE (the  default) there  is no real difference
          between  a slider  and a  dial. They  have the same signals, slots and
          member  functions, all of which do the  same things. Which one you use
          depends only on your taste and on the application.

\date     $Date: 2006/03/13 21:35:38,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODial"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mODial.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODial.hpp>


/******************************************************************************/
/**
\brief  Activate - Activate
        Initializes the Connection to ODS
        Connects slots to loadValue and storeValue

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ODial :: Activate ( )
{
  logical             ini  = stscini();
  logical             term = NO;
  if ( OEHControlValue::Activate() )
    term = YES;

  if ( !ini && event_handling ) 
  {
    connect(this  ,SIGNAL(valueChanged(int)),
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

void ODial :: ClearData ( )
{

  setValue(0);


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

logical ODial :: Deactivate (logical data_only )
{
  logical                 ini  = stscini();
  logical                 term = NO;
  if ( !ini && event_handling && !data_only ) 
  {
    disconnect(this  ,SIGNAL(valueChanged(int)),
               this  ,SLOT  (storeToValue()));         
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

void ODial :: FillData ( )
{

  setValue(ods()->ValueGetInt());


}

/******************************************************************************/
/**
\brief  Initialize - Initialize
        Sets the basic Propertys for the Dial

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ODial :: Initialize ( )
{
  logical                 term = NO;
  QDial::setWrapping(YES);
  QDial::setSingleStep(1);
  QDial::setPageStep(10);
  QDial::setTracking(YES);
  QDial::setRange(0,100);
  QDial::setNotchesVisible(YES);
  return(term);
}

/******************************************************************************/
/**
\brief  ODial - ODial
        Constructor
        calls Initialize

\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODial"

                        ODial :: ODial (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QDial (pODataWidget->WidgetQ()),
OEHControlValue (pODataWidget,oODataWidget,create_ods),
  ignore(NO)
{

  Initialize();

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
#define    MOD_ID  "ODial"

                        ODial :: ODial (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QDial (pODataWidget->WidgetQ()),
OEHControlValue(pODataWidget,oODataWidget,pODS),
  ignore(NO)
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

void ODial :: SetReadOnly (logical fReadOnly )
{

  setEnabled(fReadOnly);

}

/******************************************************************************/
/**
\brief  WidgetQ - WidgetQ
        returns QWidget

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODial :: WidgetQ ( )
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

void ODial :: storeToValue ( )
{

  StoreToValue(value());

}


