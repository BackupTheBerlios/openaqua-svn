/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OComboBox

\brief    Drop down Combo Box
          A  combo  list  is  a  drop  list,  which  displays  the  value for an
          attribute  or the key  for a single  reference. The drop list contains
          the set of permisable values for the attribute or reference. 
          The  edit field  can be  enabled or  disabled for editing. It displays
          the  key  value  or  a  selected  attribute  from  the  the  instance 
          (referenced  instance) or  the attribute  value. For single references
          the  drop list usually contains the instances, which can be associated
          with  the property (base collection). For attributes enumerated values
          can  be displayed as well as a  list of possible string values from an
          instance collection (base collection). 
          When  using a combobox  for enumerated attributes  the edit field will
          not  accept  other  values  than  defined in the drop list. For single
          references  the value in the  edit field might not  be a member of the
          list  when  being  displayed,  but  only  members  of  the list can be
          entered  in  the  list.  When  the value is not member of the droplist
          when  leaving the field the original value is restored. Otherwise, the
          instance  represented by the value is linked to the reference. You may
          add a non existing value in the list using the insert action.
          When  using the combo  box for text  attributes the list may contain a
          number  of  proposed  values  for  the attribute. In this case you may
          enter  also  a  field  not  contained  in  the  list without causing a
          conflict.  You  may  also  add  the value to the list using the insert
          action. 
          The  droplist contains a single  column, which displays instances from
          the  base collection. It  displays either an  assigned key value or an
          attribute  for the instances. For  enumerations, the enumerator string
          is displayed.

\date     $Date: 2006/07/06 19:16:24,53 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OComboBox"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOComboBox.h>
#include  <sItemData.hpp>
#include  <sOComboBoxEventFilter.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlList.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOListCtl.hpp>
#include  <sOListView.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOTreeView.hpp>
#include  <sOComboBox.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OComboBox :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( OEHControlListValue::ActivateListValue(YES) )
    term = YES;
    
  if ( !ini && event_filter && lineEdit() )
    lineEdit()->installEventFilter(event_filter);
  
  if ( !ini )
  {
    connect(this  ,SIGNAL(activated(int)),
            this  ,SLOT  (SelectionChanged()));      
  }
      
  listbox->ods()->SetParentODS(List()); 
  
  if ( listbox->Activate() )
    term = YES;

  if ( !ini )
    connect(listbox,SIGNAL(OnCurrentRowChanged(ItemData *)),
            this    ,SLOT  (ListCurrentChanged()));
  

  return(term);
}

/******************************************************************************/
/**
\brief  BlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void OComboBox :: BlockSignals (logical block_opt )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( signalsBlocked() == block_opt )               LEAVESEQ

  OEHDataWidget::BlockSignals(block_opt);

  listbox->BlockSignals(block_opt);
ENDSEQ

}

/******************************************************************************/
/**
\brief  ClearData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OComboBox :: ClearData ( )
{

  in_clear = YES;
  
  listbox->clearSelection();
  setCurrentIndex(AUTO);
  clearEditText();

  in_clear = NO;

}

/******************************************************************************/
/**
\brief  DA_FindEntry - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OComboBox :: DA_FindEntry ( )
{
  ItemData       *item_data;
  logical         term = NO;
  term = listbox->DA_FindEntry();

  if ( item_data = listbox->GetCurrentItem() )
  setCurrentIndex(item_data->get_row());
  SelectionChanged();

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  skey - 
\param  cur_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OComboBox :: DA_FindEntry (char *skey, logical cur_opt )
{
  logical         term = NO;
  term = listbox->DA_FindEntry(skey,cur_opt);
  
  setCurrentIndex(listbox->currentIndex().row());
  SelectionChanged();
  return(NO);
}

/******************************************************************************/
/**
\brief  DA_Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Refresh"

logical OComboBox :: DA_Refresh ( )
{

  listbox->DA_Refresh();
  FillData();

  return(NO);
}

/******************************************************************************/
/**
\brief  DA_StoreEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_StoreEntry"

logical OComboBox :: DA_StoreEntry ( )
{
  QString         cur_text;
  PropertyHandle *ph;
  logical      term = NO;
  storeToValue();
  cur_text = currentText();
  if ( !cur_text.isEmpty() &&
       !listbox->LocateValue(cur_text,0) )
  {
    if ( DA_Add(NO,QS2SZ(cur_text)) )
    {
      ClearData();
      StoreToValue("");
    }
  }
  OEHControlListValue::DA_StoreEntry();
  if ( !cur_text.isEmpty() )
    GenerateEvent(GEV_Selected); 


  return(term);
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

logical OComboBox :: Deactivate (logical data_only )
{
  logical          ini  = stscini();

  if ( listbox )
    listbox->Deactivate(data_only);

  if ( ini && !data_only )
    disconnect(listbox,SIGNAL(OnCurrentRowChanged(ItemData *)),
               this   ,SLOT  (ListCurrentChanged()));

  OEHControlListValue::Deactivate(data_only);

  if ( ini && !data_only )
    disconnect(this  ,SIGNAL(activated(int)),
               this  ,SLOT  (TextChanged()));      
  

  return(NO);
}

/******************************************************************************/
/**
\brief  FillData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OComboBox :: FillData ( )
{
  ItemData    *item_data = NULL;
  QString      value = ods()->Value();
BEGINSEQ
  if( !List() )                                      ERROR
  if( !ods() )                                       ERROR
  
  if ( !value.isEmpty() && !(item_data = listbox->LocateKey(QS2SZ(value))) )
  {
    listbox->ods()->get_prop()->SetCurrentCol();     // update collection state (signal not yet fired)
    listbox->ListChanged(YES);                       // Refresh-Event kommt zu spät (für singuläre Referenzen)
    item_data = listbox->LocateKey(QS2SZ(value));
  }

  if ( item_data )
    setCurrentIndex(item_data->get_row());
  else
    listbox->clearSelection();
    
  if ( ods()->ValueIsValid() )
    setEditText(ods()->Value());
  else
    ClearData();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  FillList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillList"

void OComboBox :: FillList ( )
{

//  listbox->ods()->Item()->SetItemState(NO);
  listbox->ods()->ColIsValid(YES,NO);
  listbox->ListChanged(NO);
  
  if ( ods()->Item() && ods()->Item()->get_is_reference() )
    FillData();

}

/******************************************************************************/
/**
\brief  GetListControl - 



\return pOListCtl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListControl"

OListCtl *OComboBox :: GetListControl ( )
{

  return ( listbox->GetListControl() );

}

/******************************************************************************/
/**
\brief  GetListLayout - 



\return pOTreeLayout - Tree layout definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListLayout"

OTreeLayout *OComboBox :: GetListLayout ( )
{

  return ( listbox->GetLayout() );

}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OComboBox :: Initialize ( )
{
  logical                 term = NO;
  setAutoCompletion(has_edit);
//  setSizeAdjustPolicy(Qt::AdjustToMinimumContentsLength);
  
  listbox->SetPath(NULL,NULL,YES,NULL,PT_Self);
  // 
  ///listbox = (OListView*)(OEHControlListValue*) this;
  
  listbox->disableEventHandling();
  setMinimumContentsLength(10);
  setModel(listbox->model());  // setView setzt model der ComboBox in die View
  setView(listbox);
  setEditable(has_edit);
  
  ef = new OComboBoxEventFilter(this);
  installEventFilter(ef);
  
  listbox->installEventFilter(ef);
  
  if ( lineEdit() )
    lineEdit()->installEventFilter(ef);

  return(term);
}

/******************************************************************************/
/**
\brief  ListControl - 



\return pOListCtl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListControl"

OListCtl *OComboBox :: ListControl ( )
{

  return(listbox);

}

/******************************************************************************/
/**
\brief  ListCurrentChanged - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListCurrentChanged"

void OComboBox :: ListCurrentChanged ( )
{

BEGINSEQ
  if ( !list_as_ods )                                LEAVESEQ

  storeToValue();
ENDSEQ

}

/******************************************************************************/
/**
\brief  OComboBox - Create combobox

        The  function creates a combobox control. When not passing a data source
        (pODS_w)  or  passing  NULL  as  ODS  the  function  creates an own data
        source.

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
\param  editable_w - Is edit possible?
\param  sort_order - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OComboBox"

     OComboBox :: OComboBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w, logical editable_w, int8 sort_order )
                     : QComboBox (
 pODataWidget ? pODataWidget->WidgetQ() : NULL ), 
OEHControlListValue (pODataWidget,oODataWidget,pODS_w),
  ef(NULL),
  listbox( new OListView(NULL,this,(ODS *)NULL,NO,sort_order) ),
  in_clear(NO)

{

BEGINSEQ
  OGUICERR  
  has_edit = editable_w;
  Initialize();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  pQWidget - 
\param  oODataWidget - Owning data widget
\param  pODS_w - 
\param  editable_w - Is edit possible?
\param  sort_order - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OComboBox"

     OComboBox :: OComboBox (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS_w, logical editable_w, int8 sort_order )
                     : QComboBox(pQWidget),
OEHControlListValue(oODataWidget,oODataWidget,pODS_w),
  ef(NULL),
  listbox( new OListView(NULL,this,(ODS *)NULL,NO,sort_order)),
  in_clear(NO)

{

BEGINSEQ
  OGUICERR  
  has_edit = editable_w;
  Initialize();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ProvideContextMenu - 



\return term - 

\param  watched - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideContextMenu"

logical OComboBox :: ProvideContextMenu (QObject *watched )
{
  logical   term = NO;
  DA_StoreEntry();
  OEHControlListValue::ProvideContextMenu(watched);
  return(term);
}

/******************************************************************************/
/**
\brief  SelectionChanged - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectionChanged"

void OComboBox :: SelectionChanged ( )
{

  if ( !in_clear )
    DA_StoreEntry();

}

/******************************************************************************/
/**
\brief  SetBasePath - 



\return term - 

\param  base_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBasePath"

logical OComboBox :: SetBasePath (char *base_path )
{
  logical                 term = NO;
BEGINSEQ
  if ( OEHControlListValue::SetBasePath(base_path) ) ERROR
    
  if ( !listbox->SetPath(NULL,NULL,YES,NULL,PT_Self) )
                                                     ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultReactions - Set default actions for control

        The  function implements  the default  actions for the control. Usually,
        this  function is overloaded  in the specific  control classes. The base
        calss implements the following default actions:
        F1 - Help

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OComboBox :: SetDefaultReactions ( )
{

  OEHControlListValue::SetDefaultReactions();
  if ( event_handling > 1 ) {
    SetAction("DoBeforeDataSet",  NULL, OEHInternalEvent(DEV_BeforeDataSet), listbox, YES);
    SetAction("DoAfterDataSet",   NULL, OEHInternalEvent(DEV_AfterDataSet),  listbox, YES);
    SetAction("DoBeforeFillData", NULL, OEHInternalEvent(DEV_Fill),          listbox, YES);
    SetAction("DoAfterFillData",  NULL, OEHInternalEvent(DEV_Filled),        listbox, YES);
//    SetAction("DoAfterFillData",  NULL, OEHInternalEvent(DEV_Filled),        listbox, YES);
	SetAction("DoAfterClearData", NULL, OEHInternalEvent(DEV_Clear),         listbox, YES);
  }
// welche DesfaultReactions der OListBox ev. noch?
  return(NO);
}

/******************************************************************************/
/**
\brief  SetFilter - 



\return term - 

\param  expression - 
\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical OComboBox :: SetFilter (char *expression, logical enable_opt )
{

  listbox->SetFilter(expression,enable_opt);
  return(NO);
}

/******************************************************************************/
/**
\brief  SetFlat - 



\return term - 

\param  toggle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFlat"

logical OComboBox :: SetFlat (bool toggle )
{
  logical                 term = NO;
  setFrame(!toggle);
  return(term);
}

/******************************************************************************/
/**
\brief  SetReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OComboBox :: SetReadOnly (logical fReadOnly )
{

  if ( lineEdit() ) 
    lineEdit()->setReadOnly(fReadOnly);


}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OComboBox :: WidgetQ ( )
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

void OComboBox :: storeToValue ( )
{
  int          cur_index0 = currentIndex();
  QString      cur_text;
  QString      line_text;
  char         *skey      = NULL;
  if ( cur_index0 >= 0 )
    cur_text = currentText();
  
  if ( lineEdit() )
  {
    line_text = lineEdit()->text();
    if ( cur_index0 < 0 )
      cur_text = line_text;
    else if ( cur_text != line_text )
      setEditText(cur_text);
  }  
  
  if ( cur_index0 < 0 )
    if ( listbox->LocateValue(cur_text,AUTO) )
      setCurrentIndex(cur_index0 = listbox->get_cur_item()->get_row());
      
  if ( cur_index0 >= 0 )
  {
    if ( !listbox->get_cur_item() )
      listbox->LocateRow(cur_index0);
    if ( skey = listbox->get_cur_item()->GetKey() )
      StoreToValue(skey);
  }
  else // sollte eigentlich nicht passieren
    StoreToValue(cur_text);
  
  if ( list_as_ods )
    FillData(); // stellt einstellung her, die ggf. durch das Event geaendert wurde (z.B. wegen ablehnung)
  
// in der combo-box ist der gesetzte value gleichzeitig der selektierte
// da im GetData() des context dieser wert abgefragt werden kann/soll
// kann das event erst nach StoreToValue erzeugt werden



}

/******************************************************************************/
/**
\brief  ~OComboBox - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OComboBox"

     OComboBox :: ~OComboBox ( )
{

  delete ef;
  ef = NULL;

  Deactivate(NO);

}


