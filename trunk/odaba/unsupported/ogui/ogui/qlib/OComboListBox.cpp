/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OComboListBox

\brief    Combo-Listbox
          A  combo listbox is used to display  collections. A combo list box has
          a  line edit and a  list containing one or  more columns. The list may
          display a key or instance attributes in the columns. 
          The  list is  usually ordered  according to  the selected order of the
          database  collection. The user may change the order by clicking on one
          of  the  columns  headings.  When  the  column  is  associated  with a
          database  order  the  list  will  be ordered according to the database
          order  (fast reorder). When  no sort order  is associated, the list is
          ordered  according  to  the  column content. This requires reading all
          instances  for  the  list,  which  may  take  some  while  for  large 
          collections. 
          The  edit  field  always  displays  the  key  value  according  to the
          selected  database  order.  This  key  is also used for table look-up.
          When  no database order is selected  the edit field displays the value
          for  the selected column, which can  be used for locating instances in
          the  table but not for creating new table instances in case of ordered
          collections. 
          The  combo list box  can be used  for collection properties or extents
          and  for attribute arrays. Combo list  boxes cannot be used for single
          attributes or single references.
          The  insert  action  will  add  an instance according to the key value
          entered  in  the  edit  field.  The  user  cannot  add  instances when
          applying the list box on an array.

\date     $Date: 2006/05/07 19:17:09,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OComboListBox"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOComboListBox.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODeferrer.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHControlList.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOListCtl.hpp>
#include  <sOListView.hpp>
#include  <sOSingleLineEdit.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOComboListBox.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OComboListBox :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
BEGINSEQ
  if ( !edit->ods() || !listbox->ods() )             ERROR
 
  if ( OEHControlListValue::Activate() )
    term = YES;
  
  edit->ods()->SetParentODS(ods());       
  listbox->ods()->SetParentODS(List());   
    
  if ( listbox->Activate() )
    term = YES;
  else if ( !ini )
    listbox->WidgetQ()->installEventFilter(event_filter);

  if ( edit->Activate() )
    term = YES;
  else if ( !ini )
    edit->WidgetQ()->installEventFilter(event_filter);

  if ( !ini )
  {
    connect(listbox,SIGNAL(OnCurrentRowChanged(ItemData *)),
            this   ,SLOT  (updateValue(ItemData *)));
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BlockSignals


\param  block_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void OComboListBox :: BlockSignals (logical block_opt )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( signalsBlocked() == block_opt )               LEAVESEQ

  OEHDataWidget::BlockSignals(block_opt);

  edit->BlockSignals(block_opt);
  listbox->BlockSignals(block_opt);
ENDSEQ

}

/******************************************************************************/
/**
\brief  ClearData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OComboListBox :: ClearData ( )
{

  edit->clear();
  listbox->clearSelection();

}

/******************************************************************************/
/**
\brief  Count - 


\return count

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

int OComboListBox :: Count ( )
{

  return ( listbox->model()->rowCount() );

}

/******************************************************************************/
/**
\brief  DA_FindEntry

\return term - 
-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OComboListBox :: DA_FindEntry ( )
{
  logical          term = NO;

  term = listbox->DA_FindEntry();

  updateValue(term ? NULL : cur_item);
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  skey
\param  cur_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OComboListBox :: DA_FindEntry (char *skey, logical cur_opt )
{
  logical          term = NO;
  term = listbox->DA_FindEntry(skey,cur_opt);

  updateValue(term ? NULL : cur_item);
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

logical OComboListBox :: DA_Refresh ( )
{

  return(listbox->DA_Refresh());


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

logical OComboListBox :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( ini && !data_only )
  {
    disconnect(listbox,SIGNAL(OnCurrentRowChanged(ItemData *)),
               this   ,SLOT  (updateValue(ItemData *)));
  }    
  
  if ( edit->Deactivate(data_only) )
    term = YES;
  
  if ( listbox->Deactivate(data_only) )
    term = YES;
    
  if ( OEHControlListValue::Deactivate(data_only) )
    term = YES;



  return(term);
}

/******************************************************************************/
/**
\brief  FillList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillList"

void OComboListBox :: FillList ( )
{

  listbox->ListChanged(NO);
  
  updateValue(listbox->GetCurrentItem());


}

/******************************************************************************/
/**
\brief  GetListControl

\return pOListCtl

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListControl"

OListCtl *OComboListBox :: GetListControl ( )
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

OTreeLayout *OComboListBox :: GetListLayout ( )
{

  return ( listbox->GetLayout() );

}

/******************************************************************************/
/**
\brief  ListControl

\return pOListCtl

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListControl"

OListCtl *OComboListBox :: ListControl ( )
{

  return(listbox);
}

/******************************************************************************/
/**
\brief  OComboListBox - 
        The  function creates a list box control. When not passing a data source
        (pODS_w)  or  passing  NULL  as  ODS  the  function  creates an own data
        source.

\return term - 

\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w
\param  multi_sel_w
\param  sort_order
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OComboListBox"

     OComboListBox :: OComboListBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w, logical multi_sel_w, int8 sort_order )
                     : QWidget(pODataWidget ? pODataWidget->WidgetQ() : NULL),
OEHControlListValue (pODataWidget,oODataWidget,pODS_w),
  edit(NULL),
  listbox(NULL),
  autofinding(NO)

{

BEGINSEQ
  OGUICERR    
  has_edit = YES;
  
  edit = new OSingleLineEdit((ODataWidget *)this,this,YES,NO);
  setFocusProxy(edit);

  listbox = new OListView(this,this,YES,multi_sel_w,sort_order);
  listbox->viewport()->setFocusProxy(edit);
  listbox->setFocusProxy(edit);
  
  edit->installEventFilter(this);
  listbox->installEventFilter(this);

  connect(edit,SIGNAL(textChanged(const QString &)),
          this,SLOT  (editTextChanged(const QString &)));
  setFocusProxy(edit);

  QVBoxLayout  *l= new QVBoxLayout(this);
  l->setMargin(0);
  l->setSpacing(0);
  l->addWidget(edit);
  l->addWidget(listbox);

  edit->SetPath(NULL,PT_Key);
  listbox->SetPath(NULL,NULL,YES,NULL,PT_Self);

  edit->disableEventHandling();
  listbox->disableEventHandling();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetDefaultReactions

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OComboListBox :: SetDefaultReactions ( )
{
  OEHAction                 *oeh_action = NULL;
  QAction                   *qaction    = NULL;
  QList<QAction*>            l;
  QList<QAction*>::iterator  it;
  logical                    term       = NO;
BEGINSEQ
  OEHControlListValue::SetDefaultReactions();
  
  if ( !edit )                                       LEAVESEQ
  
  l = oeh()->ActionList();
  for ( it=l.begin(); it!=l.end(); it++ )
  {
    oeh_action = OActionList::GetAction(*it);  
    if ( qaction = oeh_action->get_qaction() )
      if ( !qaction->shortcut().isEmpty() &&
           qaction->shortcutContext() == Qt::WidgetShortcut)
        edit->addAction(qaction);
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetFilter

\return term - 

\param  expression
\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical OComboListBox :: SetFilter (char *expression, logical enable_opt )
{

  listbox->SetFilter(expression,enable_opt);
  return(NO);
}

/******************************************************************************/
/**
\brief  SetPath - 


\return pOTreeLayout - Tree layout definition

\param  prop_path - Property path
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

OTreeLayout *OComboListBox :: SetPath (char *prop_path, ODSPropertyType prop_type )
{
  OTreeLayout     *pOTreeLayout = NULL;
BEGINSEQ
  if ( !OEHControlListValue::SetPath(prop_path,prop_type) ) 
                                                     ERROR
  if ( !edit->ods() )                                ERROR
  if ( !listbox->ods() )                             ERROR
 
  edit->ods()->SetParentODS(ods());
  listbox->ods()->SetParentODS(ods());

  pOTreeLayout = olayout;
RECOVER
  pOTreeLayout = NULL;
ENDSEQ
  return(pOTreeLayout);
}

/******************************************************************************/
/**
\brief  SetReadOnly


\param  fReadOnly
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OComboListBox :: SetReadOnly (logical fReadOnly )
{

  edit->UpdateReadOnly(fReadOnly);
  listbox->setEnabled(!fReadOnly);




}

/******************************************************************************/
/**
\brief  Value - Value ODS
        The  function  returns  the  ODS  that  helds  the  value (text) for the
        control.  In  case  of  combo-listboxes  this  is  the value in the edit
        control.

\return pODS

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Value"

ODS *OComboListBox :: Value ( )
{

  return ( edit->ods() );

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OComboListBox :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  editTextChanged - 



\param  rcqsText
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "editTextChanged"

void OComboListBox :: editTextChanged (const QString &rcqsText )
{
  BEGIN_ONCE(ignore)
  ItemData      *item_data = NULL;
  if ( item_data = listbox->LocateItem(rcqsText,YES) )
    listbox->scrollTo(item_data->GetModelIndex(),
                      QAbstractItemView::PositionAtTop);
  END_ONCE
}

/******************************************************************************/
/**
\brief  eventFilter

\return term - 

\param  watched
\param  pQEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eventFilter"

bool OComboListBox :: eventFilter (QObject *watched, QEvent *pQEvent )
{
  ItemData   *found_item_data = NULL;
  logical     winstyle        = UNDEF;
  bool        cond            = YES;
BEGINSEQ
  if ( !watched || !pQEvent )                        ERROR
  
//  winstyle = style()->styleHint(QStyle::SH_GUIStyle) == Qt::WindowsStyle;
  winstyle = true;
  
  if ( pQEvent->type() == QEvent::KeyPress )
  {
    if ( watched == edit )
    {
      QKeyEvent  *k = (QKeyEvent *)pQEvent;
      if ( k->key() == Qt::Key_Up       ||
           k->key() == Qt::Key_Down     ||
           k->key() == Qt::Key_PageUp   ||
           k->key() == Qt::Key_PageDown ||
           ((k->key() == Qt::Key_A || // default lineedit bindings
             k->key() == Qt::Key_B ||
             k->key() == Qt::Key_C ||
             k->key() == Qt::Key_F ||
             k->key() == Qt::Key_H ||
             k->key() == Qt::Key_K
            )
            && k->modifiers() == Qt::ControlModifier) 
           )
      {
        if ( //autofinding && j060420 not used anymore
             (found_item_data = listbox->LocateItem(edit->text(),YES)) &&
             found_item_data != listbox->GetCurrentItem() )
        {
          //autofinding = NO; j060420 not used anymore
          listbox->SetCurrentItem(found_item_data);
          if ( k->key() != Qt::Key_Up && k->key() != Qt::Key_Down )
            (void)QApplication::sendEvent(listbox,k);          
          if ( winstyle ) 
            edit->selectAll();
        }
        else
          QCoreApplication::instance()->sendEvent(listbox,k);
        LEAVESEQ
      }
    }
  }
  else if ( pQEvent->type() == QEvent::FocusIn && winstyle )
  {
    if ( watched == edit )
      edit->selectAll();
  }
  else if ( pQEvent->type() == QEvent::MouseButtonPress )
  {
    if ( watched == listbox )
      edit->setFocus();
  }

  if ( watched == edit )
    switch( pQEvent->type() )
    {
      case QEvent::FocusIn  :
      case QEvent::FocusOut : // route events to me (qt-misbehaviour)
                              QApplication::sendEvent(this,pQEvent);
    }
    
  cond = QWidget::eventFilter(watched,pQEvent);

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  getEnabled - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OComboListBox :: getEnabled ( )
{

  return YES;

}

/******************************************************************************/
/**
\brief  updateValue


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateValue"

void OComboListBox :: updateValue (ItemData *pItemData )
{
BEGINSEQ
//  listbox->ValueUpdated();
  
  if ( pItemData ) 
    edit->setText(pItemData->GetKey());
  else 
    edit->setText(QString());

// defer since other reactions could setText and thus deselect
//  USE_DEFERRER1(edit,param1->selectAll(),QLineEdit*,edit);
//060420 not used (only set NULL)
//  autofinding = NO;
  List()->ValueInit();
  ods()->ValueSet(List()->Value());
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  ~OComboListBox - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OComboListBox"

     OComboListBox :: ~OComboListBox ( )
{

  Deactivate(NO);

}


