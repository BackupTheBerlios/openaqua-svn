/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORadioButton

\brief    Radio button
          Radio  buttons are  value lists  with one  possible selection. A radio
          button works similar to drop down combo boxes.
          q4 the buttongroup manages the storage of the buttons with no visual

\date     $Date: 2006/03/13 21:36:10,17 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ORadioButton"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mORadioButton.h>
#include  <sDBorder.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlList.hpp>
#include  <sOEHEvent.hpp>
#include  <sOListCtl.hpp>
#include  <sORadioButtonGroup.hpp>
#include  <sORadioButton.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ORadioButton :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( OEHControlListValue::Activate() )
    term = YES;
  
//  buttonGroup->ods()->SetParentODS(List()); 
  
//  if ( buttonGroup->Activate() )
//    term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  ClearData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void ORadioButton :: ClearData ( )
{

  buttonGroup->ClearData();  // keiner eingeschaltet 


}

/******************************************************************************/
/**
\brief  CurrentText - 


\return qtext -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CurrentText"

QString ORadioButton :: CurrentText ( )
{

  return (   buttonGroup->GetCheckedButton() 
           ? buttonGroup->GetCheckedButton()->GetText(0) 
           : QString()                       );

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

logical ORadioButton :: Deactivate (logical data_only )
{
  logical                 term = NO;
//  if ( buttonGroup->Deactivate(data_only) )
//    term = YES;
  
  if ( OEHControlListValue::Deactivate(data_only) )
    term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  FillData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void ORadioButton :: FillData ( )
{

  if ( !ValueLocate() )
    buttonGroup->SetActive(List()->ColGetIndex());
  else
    buttonGroup->ClearData();  // keiner eingeschaltet 


}

/******************************************************************************/
/**
\brief  FillList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillList"

void ORadioButton :: FillList ( )
{

BEGINSEQ
  if ( !buttonGroup )                            ERROR
    
//  buttonGroup->ods()->Item()->SetItemState(NO);
//  buttonGroup->ListChanged(NO);
  ValueSelected();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  FrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *ORadioButton :: FrameQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  label_text - Label text
\param  auto_size - Determin size dynamically
\param  no_strips - Number of strips
\param  hori_strip - Horizontal orientation
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ORadioButton :: Initialize (char *label_text, logical auto_size, int32 no_strips, logical hori_strip )
{

buttonGroup = new ORadioButtonGroup(this,this,YES,auto_size,no_strips,hori_strip);

/*
  addChild(buttonGroup);
  buttonGroup->installEventFilter(this);
  
  buttonGroup->SetPath(NULL,NULL,YES,NULL,PT_Self);
  buttonGroup->disableEventHandling();
    
//  connect(buttonGroup ,SIGNAL(clicked(int id)),
//          this        ,SLOT(doClicked(int id)));
// q3 no title          
//  if ( label_text )
//    buttonGroup->setTitle(SZ2QS(label_text));
*/
  setFrameStyle(QFrame::NoFrame);



}

/******************************************************************************/
/**
\brief  ListControl - 


\return pOListCtl -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListControl"

OListCtl *ORadioButton :: ListControl ( )
{

  return(buttonGroup);

}

/******************************************************************************/
/**
\brief  ORadioButton - 


\return term -

\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  label_text - Label text
\param  auto_size - Determin size dynamically
\param  pODS_w -
\param  no_strips - Number of strips
\param  hori_strip - Horizontal orientation
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ORadioButton"

                        ORadioButton :: ORadioButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, char *label_text, logical auto_size, ODS *pODS_w, int32 no_strips, logical hori_strip )
                     : QScrollArea(pODataWidget ? pODataWidget->WidgetQ() : NULL),
OEHControlListValue (pODataWidget,oODataWidget,pODS_w),
  buttonGroup(NULL)

{

BEGINSEQ
//q3:ini:
//QScrollView(pODataWidget ? pODataWidget->WidgetQ() : NULL,NULL,QWidget::WPaintClever | QWidget::WStyle_NoBorder ),

  OGUICERR  
    
//  viewport()->setBackgroundMode(QWidget::PaletteBackground);
  
  Initialize(label_text,auto_size,no_strips,hori_strip); 

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OnSetupListCaption - 



\param  rODSList -
\param  rODSCaption -
\param  fSetup -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnSetupListCaption"

void ORadioButton :: OnSetupListCaption (ODS &rODSList, ODS &rODSCaption, logical fSetup )
{

  rODSCaption.SetParentODS(&rODSList);
  rODSCaption.SetPath((ODSPropPath&)ODSPropPath(NULL,PT_NewCursor));
  rODSCaption.SetActive(fSetup);

}

/******************************************************************************/
/**
\brief  SetFrameStyle - 



\param  pDBorder -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFrameStyle"

void ORadioButton :: SetFrameStyle (DBorder *pDBorder )
{
  logical       has_scrol = YES;

  has_scrol = horizontalScrollBarPolicy() != Qt::ScrollBarAlwaysOff ||
              verticalScrollBarPolicy()   != Qt::ScrollBarAlwaysOff;
  
  buttonGroup->SetFrameStyle(has_scrol ? NULL : pDBorder);
  OEHControlListValue::SetFrameStyle(has_scrol ? pDBorder : NULL);

}

/******************************************************************************/
/**
\brief  SetReadOnly - 



\param  fReadOnly -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void ORadioButton :: SetReadOnly (logical fReadOnly )
{

  setDisabled(fReadOnly);


}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ORadioButton :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  getEnabled - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical ORadioButton :: getEnabled ( )
{

  return( ods()->ProvideItem() >= IST_selected && 
          List()->ColIsValid()                    );

}

/******************************************************************************/
/**
\brief  resizeEvent - 



\param  pQResizeEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "resizeEvent"

void ORadioButton :: resizeEvent (QResizeEvent *pQResizeEvent )
{
  QRect       r = geometry();
  /*
  if ( !buttonGroup->get_auto_resize() ) 
  {
    viewport()->resize(size());
    buttonGroup->Resize();
  }
  */

}

/******************************************************************************/
/**
\brief  storeToValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void ORadioButton :: storeToValue ( )
{

  StoreToValue(CurrentText());
    
  if ( !list_as_ods )
    ValueLocate();


}

/******************************************************************************/
/**
\brief  ~ORadioButton - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ORadioButton"

                        ORadioButton :: ~ORadioButton ( )
{

  delete buttonGroup;
  buttonGroup = NULL;

}


