/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    FAssociate

\brief    Constructs a Dialog to Associate Items
          displays  a list  of items  of the  basecollection. you can check them
          and say ok to associate the items.
          already associated items will not apear in the list

\date     $Date: 2006/07/31 17:01:37,29 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FAssociate"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mFAssociate.h>
class     ItemData;
#include  <sItemTreeModel.hpp>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOTreeView.hpp>
#include  <sQGridLayout.hpp>
#include  <sQPushButton.hpp>
#include  <iigui.h>
#include  <iopai.h>
#include  <sFAssociate.hpp>


/******************************************************************************/
/**
\brief  FAssociate - Constructor

        Initializes


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FAssociate"

     FAssociate :: FAssociate (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : ODialog(pODataWidget,oODataWidget,YES,"",YES),
  od_control(NULL),
  base_list(NULL)
{

  InitializeButtons();
  


}

/******************************************************************************/
/**
\brief  InitODControl - 



\return term - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitODControl"

logical FAssociate :: InitODControl (char *control_name )
{
  char            *associate = control_name ? control_name : "associate";
  ODControl       *pod = owning_odw->get_od_control();
  ODataWidget     *odw;
  logical          term = NO;
BEGINSEQ
  if ( !pod )                                        ERROR
  
  if ( owning_odw->LoadDynamicControl(source->GetType(),associate,NO) )
                                                     ERROR
  if ( !(od_control = pod->RemoveControl(associate)) )
                                                     ERROR
  odw = od_control->get_controlWidget();
  if ( !odw->WidgetQ()->inherits("OTreeView") )      ERROR

  base_list = (OTreeView *)odw;
  base_list->WidgetQ()->setParent(this);
  base_list->SetParent(this,this);
  od_control->ResetControlWidget();
  
//  delete od_control; wird durch ForceClose beim Löschen des Trees gemacht
  od_control = NULL;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

\param  source_ph - 
\param  control_name - 
\param  title - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical FAssociate :: Initialize (PropertyHandle *source_ph, char *control_name, char *title )
{
  logical                 term = NO;
  setWindowTitle(SZ2QS(title));

  source = source_ph;
  if ( owning_odw ) 
  {
    if ( !source ) 
      source = owning_odw->GetBasePropertyHandle();
    parent.Open(owning_odw->GetCurrentPropertyHandle());  // war bis 24.7. copy handle
  }
    
  if ( InitODControl(control_name) )
    base_list = new OTreeView(this,this,(ODS*)NULL,NO,YES,NO,YES);
  
  connect((ODSTree *)&base_list->get_listCache(),SIGNAL(OnBeforeDataSet(logical*)),
          this     ,SLOT(slotHideAssociated(logical*)));
  connect(base_list,SIGNAL(activated(const QModelIndex &)),
          this     ,SLOT(ToggleItem(const QModelIndex &)));
  

  return(term);
}

/******************************************************************************/
/**
\brief  ToggleItem - 




\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToggleItem"

void FAssociate :: ToggleItem (const QModelIndex &model_index )
{
  ItemTreeModel  *model  = &base_list->get_listCache();
  ItemData       *item   = model->Item(model_index);
  item->ToggleChecked();
  model->UpdateData(item);


}

/******************************************************************************/
/**
\brief  accept - accepts the dialog selection

        traverses through selected items

        syncs to the current item (for all items)
        takes its propertyhandle and adds a reference


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accept"

void FAssociate :: accept ( )
{
  OEHDataWidget  *oeh_dw = owning_odw->DataWidgetOEH();
  ItemTreeModel  *model  = &base_list->get_listCache();
  QModelIndex     index;
  ItemData       *item   = NULL;

BEGINSEQ
  if ( !oeh_dw )                                     ERROR
  
  SetBusy(YES);
  parent.StartRTA();
  
  while ( (index = base_list->indexBelow(index)).isValid() ) 
  {
    if ( !(item = model->Item(index)) )
      break;
      
    if ( item->IsChecked() )
      oeh_dw->DA_Add(YES,item->get_key_val());
  }
  
  ODialog::accept();
  
  parent.StopRTA(YES);
  SetBusy(NO);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  exec - exec

        gets the property handles of the owning list
        creates the a stringlist from the current accociations
        construct the view (listview,buttons,grid,size)
        and executes the dialog


        "

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exec"

logical FAssociate :: exec ( )
{
  PropertyHandle    base_copy(*source);                 
  OTreeLayout      *pOTLayout;
  logical           term  = NO;
BEGINSEQ
  if ( !base_copy.IsValid() )                        ERROR
  if ( !owning_odw )                                 ERROR
  
  pOTLayout  = base_list->GetLayout();
  pOTLayout->SetPath(NULL,NULL,YES,NULL,PT_none);
  pOTLayout->SetFilter(NULL,YES);
  
  SetBusy(YES);
  base_list->SetPropertyHandle(&base_copy,YES);
  base_list->Activate();
  SetBusy(NO);
  
  qGrid = new QGridLayout(this);
  qGrid->addWidget(base_list,0,0,1,3);
  qGrid->addWidget(qbOK,1,1);
  qGrid->addWidget(qbCancel,1,2);
  setGeometry(200,200,400,200);
  if ( !ODialog::exec() )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  slotHideAssociated - hides associated items

        looks up the item that will display in the associated stringlist
        "returns" true if this item is asscociated
        the  local listcache  must be  connected to  a signal that can interpret
        the return value

        "


\param  pterm - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotHideAssociated"

void FAssociate :: slotHideAssociated (logical *pterm )
{
  PropertyHandle   *ph = NULL;
  char              keyval[513];
BEGINSEQ
  if ( !base_list )                                  ERROR
  if ( !base_list->List() )                          ERROR
  
  ph = base_list->List()->Handle();
  
  if ( ph->ExtractSortKey(keyval) )
    if ( !parent.LocateKey(keyval) )         // already exists
      *pterm = YES;
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~FAssociate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~FAssociate"

     FAssociate :: ~FAssociate ( )
{

  delete base_list;
  base_list = NULL;


}


