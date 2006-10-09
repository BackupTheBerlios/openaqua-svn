/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODelegate

\brief    Delegate for view and edit modelitems
          this  class is used  to manipulate the  default behaviour of the items
          in a list or a table

\date     $Date: 2006/03/13 21:35:37,75 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODelegate"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sCellData.hpp>
#include  <sItemData.hpp>
#include  <sOCheckBox.hpp>
#include  <sOComboBox.hpp>
#include  <sODS.hpp>
#include  <sODSList.hpp>
#include  <sODSTree.hpp>
#include  <sODataWidget.hpp>
#include  <sODateEdit.hpp>
#include  <sOSingleLineEdit.hpp>
#include  <sOTableView.hpp>
#include  <sOTreeView.hpp>
#include  <sPropertyHandle.hpp>
#include  <sODelegate.hpp>


/******************************************************************************/
/**
\brief  CheckBox - Manipulates the checkbox display
        checkbox  has to be moved left to  show it where the checkbox is painted
        in display mode

\return term -

\param  pQWidget -
\param  model_index -
\param  crQStyleOptionViewItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckBox"

logical ODelegate :: CheckBox (QWidget *pQWidget, const QModelIndex &model_index, const QStyleOptionViewItem &crQStyleOptionViewItem ) const
{
  logical                    term     = NO;
  ODSList                   *pODSList = NULL;
  QRect                      r,cr;
BEGINSEQ
  pODSList = GetODS(model_index);
  if(!pODSList)                                      ERROR
  if(!pODSList->IsBool())                            LEAVESEQ
  
  // move the editcontrol to the left
  r = pQWidget->geometry();
  cr= check(crQStyleOptionViewItem,r,Qt::Checked);
  r.setX(r.x()-cr.width());
  r.setWidth(r.width() + cr.width());
  pQWidget->setGeometry(r);
 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ComboBox - Draws a Combox
        this  function is for demonstration what  is possible with delegates and
        not used yet

\return term -

\param  pQPainter -
\param  crQStyleOptionViewItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ComboBox"

logical ODelegate :: ComboBox (QPainter *pQPainter, const QStyleOptionViewItem &crQStyleOptionViewItem )
{
  logical                 term = NO;
  OComboBox              *pOComboBox = NULL;
BEGINSEQ
    if(!pOComboBox)                                  ERROR
    
    QStyleOptionComboBox opt;
    opt.initFrom(pOComboBox->WidgetQ());
    opt.rect = rData;
    opt.currentText = pOComboBox->currentText() ;
    
    // manage display of item (selected)
    opt.state = crQStyleOptionViewItem.state ;
    if(opt.state & QStyle::State_Selected )
        opt.state|=QStyle::State_HasFocus;
    
    // paint the item using qt functions
    // set the coordinate system
    pQPainter->translate(QPoint(rData.x(),rData.y()));
    opt.frame = false;
    QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &opt, pQPainter);
    opt.frame = true;
    QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, &opt, pQPainter);
    // restore the coordinate system
    pQPainter->translate(QPoint(rData.x()*-1,rData.y()*-1));


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetODS - Gets the ODS from a model_index
        extracts  the  ODSList  from  the  model_index  and  takes care for NULL
        pointer

\return pODSList -

\param  model_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetODS"

ODSList *ODelegate :: GetODS (const QModelIndex &model_index ) const
{
  ItemData               *pItemData = NULL;
  ODSList                *ods       = NULL;
  ItemTreeModel          *itm       = NULL;

BEGINSEQ
   if (!model_index.isValid())                       ERROR
   const QAbstractItemModel *model = model_index.model();
   if (!model)                                       ERROR
   itm = (ItemTreeModel*) model;
   if (!model_index.internalPointer())               ERROR
   pItemData = ((CellData *)model_index.internalPointer())->Item();
   if (!pItemData)                                   ERROR
   if (!pItemData->Region())                         ERROR
   // what about transposed models?
   ods  = pItemData->Region()->Column(itm->get_transposed()?model_index.row():model_index.column());

RECOVER
  ods = NULL;
ENDSEQ
  return(ods);
}

/******************************************************************************/
/**
\brief  GetType - Returns a string for the type of the odsList
        this  is used to have a castless  information what kind of widget should
        be created

\return string - Character string

\param  pODSList -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetType"

std_string ODelegate :: GetType (ODSList *pODSList ) const
{
  std_string              r = "unknown";
  std_string              phType = "";

  ODSList                *ods       = NULL;
BEGINSEQ
  if( !pODSList )                                     ERROR
  if( pODSList->GetType() )
    phType = std_string(pODSList->GetType());
  
  if (pODSList->IsBool())
    r = "CheckBox";
//  if (pODSList->isDate())
//    r = "DateEdit";
  if (!pODSList->IsCollection() && pODSList->HasBaseCollection()){
    r = "ComboBox";
  }
   
   // well there are 3 more possibles that cannot be covered this easy:
   // INT
   // r = "Slider"
   // r = "ProgressBar"
   // r = "Spinbox"

RECOVER
  r = "unknown";
ENDSEQ
  return r;
}

/******************************************************************************/
/**
\brief  GetWidget - 


\return pODataWidget - Parent data widget
-------------------------------------------------------------------------------
\brief  i0


\param  pODSList -
\param  pQWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWidget"

ODataWidget *ODelegate :: GetWidget (ODSList *pODSList, QWidget *pQWidget ) const
{
  ODataWidget             *widget = NULL;
  ODataWidget             *oODW   = NULL;
  ODS                     *pODS   = (ODS*)pODSList;
  std_string               sType  = "";
BEGINSEQ
   if(!pODSList)                                     ERROR
   if(!pODSList->get_data_widget()){
     sType = GetType(pODSList);
     /// nadja sagt das geht... das glaube ich aber garnicht
     /// weil das delegate geht auch fuer eine table
     ///   if(pODS)
     ///     oODW = (ODataWidget*)((ODSTree*)pODS)->GetListControl();
     /// ich mach das erstmal mit dem tree
     ///oODW = (ODataWidget*)(OTreeView*)(QTreeView*)pQWidget->parent();
     // oder doch besser mit der table?
     oODW = (ODataWidget*)(OTableView*)(QTableView*)pQWidget->parent();
     ODSPropPath path = pODS->get_path();
     if(      sType=="ComboBox"){
       widget = new OComboBox(pQWidget, oODW, (ODS*)NULL);
       ((OComboBox*)widget)->SetFlat(true);
       path.SetCollection(YES);
     }else if(sType=="DateEdit"){
       widget = new ODateEdit(pQWidget, oODW, (ODS*)NULL);
     }else if(sType=="CheckBox"){
       widget = new OCheckBox(pQWidget, oODW, (ODS*)NULL);
     }else {
       widget = new OSingleLineEdit(pQWidget, oODW, pODS, NO);
       ((OSingleLineEdit*)widget)->SetFlat(true);
     }
     widget->SetPath(path);
     pODSList->SetDataWidget((OEHControlData*)widget);
   }else
     widget = pODSList->get_data_widget();
   

RECOVER
  widget = NULL;
ENDSEQ
  return(widget);
}

/******************************************************************************/
/**
\brief  i01


\param  model_index -
\param  pQWidget -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWidget"

ODataWidget *ODelegate :: GetWidget (const QModelIndex &model_index, QWidget *pQWidget ) const
{
  ODataWidget              *widget = NULL;
  ODSList                  *pODSList = NULL;
BEGINSEQ
  if (! (pODSList = GetODS(model_index)) )           ERROR
  widget = GetWidget(pODSList,pQWidget);
RECOVER
  widget = NULL;
ENDSEQ
  return(widget);
}

/******************************************************************************/
/**
\brief  ODelegate - 


\return term -

\param  pQObject -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODelegate"

                        ODelegate :: ODelegate (QObject *pQObject )
                     : QItemDelegate (pQObject),
  rData(),
  rIcon(),
  rDecoration()
{



}

/******************************************************************************/
/**
\brief  createEditor - creates the Editor
        finds  (or  if  nessesary)  creates  the  edit widget and returns it. if
        nothing   appropiate   is   found   the   default   editor is displayed.
        (QLineEdit)

\return pQWidget -

\param  pQWidget -
\param  crQStyleOptionViewItem -
\param  model_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createEditor"

QWidget *ODelegate :: createEditor (QWidget *pQWidget, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const
{
  ODataWidget            *odw = NULL;
  QWidget                *editor = NULL;
  std_string              type;
BEGINSEQ
  odw = GetWidget(model_index,pQWidget);
  if( !odw )                                         ERROR
  editor = odw->WidgetQ();
  

RECOVER
  editor = QItemDelegate::createEditor(
             pQWidget
            ,crQStyleOptionViewItem
            ,model_index);
ENDSEQ
  return(editor);
}

/******************************************************************************/
/**
\brief  setEditorData - 



\param  pQWidget -
\param  model_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setEditorData"

void ODelegate :: setEditorData (QWidget *pQWidget, const QModelIndex &model_index ) const
{
  ODataWidget            *odw = NULL;
  QLineEdit              *defEdit = NULL;
  ODSList                *pODSList = NULL;
BEGINSEQ
  // if the odws need more settings this is the place where 
  // that could happen
  if(! (odw = GetWidget(model_index,pQWidget)) )     ERROR
  odw->Activate();

RECOVER

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

void ODelegate :: setModelData (QWidget *pQWidget, QAbstractItemModel *pQAbstractItemModel, const QModelIndex &model_index ) const
{
  ODataWidget            *odw = NULL;
  ODSList                *pODSList = NULL;
  QLineEdit              *defEdit = NULL;
BEGINSEQ
  if(! (odw = GetWidget(model_index,pQWidget)) )     ERROR
  // forget the widget in the model
  // because odw will get deleted by this delegate
  
  if(! (pODSList = GetODS(model_index)) )            ERROR
  pODSList->SetDataWidget(NULL);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  updateEditorGeometry - 



\param  pQWidget -
\param  crQStyleOptionViewItem -
\param  model_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateEditorGeometry"

void ODelegate :: updateEditorGeometry (QWidget *pQWidget, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const
{

BEGINSEQ
  if(!pQWidget)                                      ERROR
  QItemDelegate::updateEditorGeometry(pQWidget, crQStyleOptionViewItem, model_index);
  // move the pQWidget if it is a checkbox
  CheckBox(pQWidget,model_index,crQStyleOptionViewItem);

RECOVER

ENDSEQ

}


