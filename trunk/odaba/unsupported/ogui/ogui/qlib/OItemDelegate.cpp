/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OItemDelegate

\brief    


\date     $Date: 2006/08/23 21:29:16,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OItemDelegate"

#include  <pogui7.h>
#include  <sOCheckBox.hpp>
#include  <sOComboBox.hpp>
#include  <sODateEdit.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOListCtl.hpp>
#include  <sOObject.hpp>
#include  <sOSingleLineEdit.hpp>
#include  <sQPushButton.hpp>
#include  <sOItemDelegate.hpp>


/******************************************************************************/
/**
\brief  IsCheckColumn - 



\return cond - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCheckColumn"

logical OItemDelegate :: IsCheckColumn (const QModelIndex &model_index ) const
{
  CellData       *cell     = ItemTreeModel::Cell(model_index);
  ItemData       *item     = cell ? cell->item_data : NULL;
  ItemTreeModel  *model    = item ? item->Model() : NULL;  
  logical         cond     = NO;

BEGINSEQ
  if ( !cell )                                       ERROR
    
  if ( model->get_check_box() && !model_index.column() )
  {
    item->ToggleChecked();
    cond = YES;
  }
  else
   cond = cell->ToggleChecked();

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  OItemDelegate - 




\param  pOListCtl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OItemDelegate"

     OItemDelegate :: OItemDelegate (OListCtl *pOListCtl )
                     : QItemDelegate (pOListCtl ? pOListCtl->WidgetQ() : NULL),
  list_control(pOListCtl)
{



}

/******************************************************************************/
/**
\brief  createEditor - 



\return pQWidget - 

\param  pqwParent - Parent control
\param  crQStyleOptionViewItem - 
\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createEditor"

QWidget *OItemDelegate :: createEditor (QWidget *pqwParent, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const
{
  CellData         *cell   = ItemTreeModel::Cell(model_index);
  ODSList          *ods    = cell->ListODS();
  ODS            *ods_null = NULL;
  OEHDataWidget    *odw    = NULL;
  QWidget          *editor = NULL;
BEGINSEQ
  if ( IsCheckColumn(model_index) )                  LEAVESEQ
  if ( !cell || !ods || ods->get_path().get_acc_mode() == PI_Read )  
                                                     ERROR
  if ( !(odw = cell->GetDataWidget()) )
  {  
    if ( ods->IsBool() )  // wird nicht mehr aufgerufen!
      odw = new OCheckBox(pqwParent,list_control,ods_null);
//    else if ( !ods->IsDate() )
//      odw = new ODateEdit(pqwParent,list_control,ods_null);
    else if ( ods->HasBaseCollection() )   // bis 18.11.2005 && !ods->DefinesCollection() 
    {
      odw = new OComboBox(pqwParent,list_control,ods_null);
       ((OComboBox*)odw)->SetFlat(true);
    }
    else
    {
      odw = new OSingleLineEdit(pqwParent,list_control,ods_null);
      ((OSingleLineEdit*)odw)->SetFlat(true);
    }
  }
     
  if ( !odw )
    editor = QItemDelegate::createEditor(pqwParent,crQStyleOptionViewItem,model_index);
  else
  {  
    odw->ods()->SetParentODS(ods);
    odw->SetPath(NULL,NULL,NO,NULL,PT_Self);
    odw->Activate(); 
  
    editor = odw->WidgetQ();
    editor->installEventFilter((QObject *)this);
  }
RECOVER

ENDSEQ
  return(editor);
}

/******************************************************************************/
/**
\brief  paint - 




\param  pQPainter - 
\param  crQStyleOptionViewItem - 
\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "paint"

void OItemDelegate :: paint (QPainter *pQPainter, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const
{

BEGINSEQ
// error == base implementation
ERROR
// this code is the example implementation of a button in a listview
// item. it misses the implementation that handles over and click
// and only works for static items and more than two columns
if(model_index.column()==1){
  // is it a static item?
  ItemTreeModel *model = (ItemTreeModel*) model_index.model();
  if(!model)                                        ERROR
  ItemData *item = model->Item(model_index);
  if(item && !item->IsStaticItem())                 ERROR
  // make the style
  QStyleOptionButton opts;
  QPushButton *b = new QPushButton();
  opts.initFrom(b);
  opts.rect = crQStyleOptionViewItem.rect; 
  // div buttoncount (this are 3)
  opts.rect.setWidth(opts.rect.width()/3);
  // add some spacing
  opts.rect.setWidth(opts.rect.width()-4);
  opts.rect.setHeight(opts.rect.height()-4);
  opts.rect.moveTop(opts.rect.y()+2);
  // label the first
  opts.text = "x";
  for(int i = 0; i<3 ; i++){
    QApplication::style()->drawControl(QStyle::CE_PushButton, &opts, pQPainter);
    QApplication::style()->drawControl(QStyle::CE_PushButtonBevel, &opts, pQPainter);
    QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, &opts, pQPainter);
	//label the other
    opts.text = (char*)i==0?"+":"*";
    //adjust the position
    opts.rect.moveLeft(opts.rect.x() + opts.rect.width()+2);
  }
}else ERROR

RECOVER
  QItemDelegate::paint(pQPainter,crQStyleOptionViewItem, model_index);
ENDSEQ

}

/******************************************************************************/
/**
\brief  setModelData - 




\param  pQWidget - 
\param  pQAbstractItemModel - 
\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setModelData"

void OItemDelegate :: setModelData (QWidget *pQWidget, QAbstractItemModel *pQAbstractItemModel, const QModelIndex &model_index ) const
{
  ODataWidget   *odw    = OObject::GetODW(pQWidget);
  OEHDataWidget *oeh_dw = odw ? odw->DataWidgetOEH() : NULL;
  if ( oeh_dw )
    oeh_dw->DA_StoreEntry();
  
  ItemTreeModel::Cell(model_index)->UpdateData();

}

/******************************************************************************/
/**
\brief  updateEditorGeometry - 




\param  pQWidget - 
\param  crQStyleOptionViewItem - 
\param  crQModelIndex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateEditorGeometry"

void OItemDelegate :: updateEditorGeometry (QWidget *pQWidget, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &crQModelIndex )
{

BEGINSEQ
  if(!pQWidget)                                      ERROR
  QItemDelegate::updateEditorGeometry(pQWidget, crQStyleOptionViewItem, crQModelIndex);
//  pQWidget->setGeometry(0,0,300,300);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OItemDelegate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OItemDelegate"

     OItemDelegate :: ~OItemDelegate ( )
{



}


