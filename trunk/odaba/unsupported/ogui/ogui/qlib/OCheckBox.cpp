/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OCheckBox



\date     $Date: 2006/05/22 17:07:46,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OCheckBox"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOCheckBox.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOCheckBox.hpp>


/******************************************************************************/
/**
\brief  Activate

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OCheckBox :: Activate ( )
{
  logical          ini  = stscini();
  OEHControlValue::Activate();
  
  if ( !ini )
    connect(this, SIGNAL(toggled(bool)),
            this, SLOT(storeToValue()));
  

  return(NO);
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

logical OCheckBox :: Deactivate (logical data_only )
{
  logical          ini  = stscini();

  if ( ini && !data_only )
    disconnect(this, SIGNAL(toggled(bool)),
               this, SLOT(storeToValue()));
  
  OEHControlValue::Deactivate(data_only);
  


  return(NO);
}

/******************************************************************************/
/**
\brief  FillData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OCheckBox :: FillData ( )
{

  setChecked(ods()->ValueIsTrue());
  


}

/******************************************************************************/
/**
\brief  OCheckBox

-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckBox"

     OCheckBox :: OCheckBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : QCheckBox( pODataWidget ? pODataWidget->WidgetQ() : NULL), 
OEHControlValue(pODataWidget,oODataWidget,pODS_w)
{

  has_edit = YES;
  setFocusPolicy(Qt::StrongFocus);

}

/******************************************************************************/
/**
\brief  i01


\param  pQWidget
\param  oODataWidget - Owning data widget
\param  pODS_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckBox"

     OCheckBox :: OCheckBox (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : QCheckBox( pQWidget), 
OEHControlValue(oODataWidget,oODataWidget,pODS_w)
{
}

/******************************************************************************/
/**
\brief  SetReadOnly


\param  fReadOnly
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OCheckBox :: SetReadOnly (logical fReadOnly )
{

  setEnabled(!fReadOnly);


}

/******************************************************************************/
/**
\brief  WidgetQ

\return qwidget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OCheckBox :: WidgetQ ( )
{

  return(this);
}

/******************************************************************************/
/**
\brief  storeToValue


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void OCheckBox :: storeToValue ( )
{

  StoreToValue((logical)isChecked());


}

/******************************************************************************/
/**
\brief  ~OCheckBox


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OCheckBox"

     OCheckBox :: ~OCheckBox ( )
{
}


