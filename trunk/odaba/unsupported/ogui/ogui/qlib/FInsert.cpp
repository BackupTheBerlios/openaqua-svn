/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    FInsert

\brief    Insert
          Constructs a dialog that inserts a string to a selectable region

\date     $Date: 2006/03/13 21:35:04,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FInsert"

#include  <pogui7.h>
#include  <cqt.h>
#include  <decl_mt.h>
#include  <mFInsert.h>
class     ItemData;
#include  <sODS.hpp>
#include  <sODSRegion.hpp>
#include  <sODataWidget.hpp>
#include  <sOListCtl.hpp>
#include  <sPropertyHandle.hpp>
#include  <sFInsert.hpp>


/******************************************************************************/
/**
\brief  FInsert - Constructor



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FInsert"

                        FInsert :: FInsert (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : ODialog(pODataWidget,oODataWidget,YES,"Insert/Append Item",YES),
  meta_model(NULL),
  meta_tree(NULL),
  line_edit(NULL),
  grid(NULL),
  ph_selected(NULL),
  label(NULL)
{

  InitializeButtons();
  
  meta_model = new QStandardItemModel(this);
  meta_tree  = new QTreeView(this);
  label      = new QLabel(this); 
  line_edit  = new QLineEdit(this);
  grid       = new QGridLayout(this);
  
  
  setWindowTitle(SZ2QS("Insert/Append Item"));
  label->setText(SZ2QS("Enter a key to insert/append"));
  meta_tree->setRootIsDecorated(true);
  meta_tree->setItemsExpandable(true);


}

/******************************************************************************/
/**
\brief  ResultPH - 


\return prophdl -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResultPH"

PropertyHandle *FInsert :: ResultPH ( )
{

  return ( ph_selected );

}

/******************************************************************************/
/**
\brief  ResultString - 


\return pQString -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResultString"

QString FInsert :: ResultString ( )
{

  return ( input_string );

}

/******************************************************************************/
/**
\brief  accept - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accept"

void FInsert :: accept ( )
{
  QModelIndex  model_index;
  QVariant     qvar;
  input_string = line_edit->text();
  ph_selected  = NULL;
  
  model_index = meta_tree->currentIndex();
  if ( model_index.isValid() )
  {
    qvar = meta_model->data(meta_model->index(model_index.row(),1,model_index.parent()),
                            Qt::DisplayRole);
    ph_selected = qvar.value<ODSRegion *>()->Handle();       
  }
  
  ODialog::accept();

}

/******************************************************************************/
/**
\brief  exec - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exec"

logical FInsert :: exec ( )
{
  OListCtl        *list_control = owning_odw->GetListControl();
  QModelIndex      model_index;
  logical          show_tree    = NO;
  logical          cond         = YES;

  grid->addWidget(label,0,0,1,3,Qt::AlignTop);

  if ( list_control ) {
    // get a empty tree but still a usable layout    
    model_index = list_control->get_listCache().
                  FillMetaModel(meta_model,list_control->get_cur_item());
  
    show_tree = meta_model->rowCount() > 1 || 
                meta_model->hasChildren(model_index);
  }        
  grid->addWidget(line_edit,1,0,1,3,Qt::AlignTop);
  
  if ( show_tree )
    grid->addWidget(meta_tree,2,0,1,3,Qt::AlignTop);
  else
    meta_tree->hide();
    
    
  grid->addWidget(qbOK     ,show_tree ? 3 : 2,1,Qt::AlignTop);
  grid->addWidget(qbCancel ,show_tree ? 3 : 2,2,Qt::AlignTop);
  
  setGeometry(200,200,400,show_tree ? 260 : 50);
  
  if ( show_tree )
  {
    meta_tree->setModel(meta_model);
    meta_tree->setColumnHidden(1,true);
    meta_tree->setExpanded(model_index,true);
    meta_tree->setCurrentIndex(model_index);
  }
  
  line_edit->setFocus();
    
  cond = ODialog::exec();
  return(cond);
}

/******************************************************************************/
/**
\brief  ~FInsert


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~FInsert"

                        FInsert :: ~FInsert ( )
{

  ph_selected = NULL;



}


