/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    CellData

\brief    


\date     $Date: 2006/07/31 16:51:23,51 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CellData"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sItemTreeModel.hpp>
#include  <sODS.hpp>
#include  <sODSList.hpp>
#include  <sODSRegion.hpp>
#include  <sODataLayout.hpp>
#include  <sOEHControlData.hpp>
#include  <sOEHControlValue.hpp>
#include  <sPropertyHandle.hpp>
#include  <sCellData.hpp>


/******************************************************************************/
/**
\brief  CellData - Konstruktor




\param  pItemData - ItemData
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CellData"

     CellData :: CellData (ItemData *pItemData, int column )
                     : ODSItemState (),
ODataLayoutRef (NO),
  item_data(pItemData),
  col(column),
  value()
{



}

/******************************************************************************/
/**
\brief  ClearData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void CellData :: ClearData ( )
{

  if ( !item_data->get_heading() )
    value = "";

}

/******************************************************************************/
/**
\brief  FillData - 



\return term - 

\param  init_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

logical CellData :: FillData (logical init_opt )
{
  ODSList  *ods  = ListODS();
  logical   term = NO;
BEGINSEQ
  if ( !ods )                                   ERROR
    
  switch ( item_data->get_heading() )
  {
    case 0  : if ( ods->IsKey() && this == item_data && item_data->get_key_val() )
                value = item_data->get_key_val();
              else
              {
                if ( init_opt )
                  ods->ValueInit();
                if ( ods->IsBool() )
                  value = ods->ValueIsTrue() ? Qt::Checked : Qt::Unchecked;
                else
                  value = ods->ValueGetString();
              }
                
              break;
    
    case 1  : if ( !col )
                value = item_data->Region()->GetStaticText();
              break;
             
    case 2  : value = ods->GetStaticText();
              break;
             
    default : OGUIERR(99);
  }    


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetBackgroundColor - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBackgroundColor"

QVariant CellData :: GetBackgroundColor ( )
{
  QColor   *color = NULL;
  if ( item_data->get_heading() )
    color = item_data->Region()->GetBackgroundColor();
  else  
    if ( !(color = ODataLayoutRef::GetBackgroundColor()) )
      color = item_data->Region()->Column(col)->GetBackgroundColor();

  return ( color ? QVariant(QVariant::Color,color) : QVariant() );

}

/******************************************************************************/
/**
\brief  GetCheckState - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCheckState"

QVariant CellData :: GetCheckState ( )
{

  return ( ListODS()->IsBool() ? value : QVariant() );

}

/******************************************************************************/
/**
\brief  GetData - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

QVariant CellData :: GetData ( )
{

  return ( this && !ListODS()->IsBool() ? value : QVariant() );



}

/******************************************************************************/
/**
\brief  GetDataWidget - 



\return pOEHControlData - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataWidget"

OEHControlData *CellData :: GetDataWidget ( )
{
  ODSList    *ods = ListODS();
  return (   this && ods 
           ? ods->get_data_widget()
           : NULL                   );

}

/******************************************************************************/
/**
\brief  GetFont - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

QVariant CellData :: GetFont ( )
{
  QFont    *font = NULL;
  if ( item_data->get_heading() )
    font = item_data->Region()->GetFont();
  else
    if ( !(font = ODataLayoutRef::GetFont()) )
      font = item_data->Region()->Column(col)->GetFont();
  return ( font ? QVariant(QVariant::Font,font) : QVariant() );

}

/******************************************************************************/
/**
\brief  GetHelp - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHelp"

QVariant CellData :: GetHelp ( )
{
  char *string = NULL;
  if ( item_data->get_heading() == 1 )
    string = item_data->Region()->GetHelp();
  else
    item_data->Region()->Column(col)->GetHelp();  
  
  return ( string ? QVariant(string) : QVariant() );

}

/******************************************************************************/
/**
\brief  GetIcon - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIcon"

QVariant CellData :: GetIcon ( )
{
  QIcon    *icon = NULL;
  if ( item_data->get_heading() && !col )   // war nur fuer == 1
    icon = item_data->Region()->GetIcon();  
  
  if ( !item_data->get_heading() )
    if ( !(icon = ODataLayoutRef::GetIcon()) )
      icon = item_data->Region()->Column(col)->GetIcon();
          
  return ( icon ? QVariant(QVariant::Icon,icon) : QVariant() );

}

/******************************************************************************/
/**
\brief  GetModelIndex - 



\return mindex - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModelIndex"

QModelIndex CellData :: GetModelIndex ( )
{
  ItemTreeModel      *model  = NULL;
  QAbstractItemModel *amodel   = NULL;
  CellData           *parent = Parent();
  if ( !this || !(model = item_data->Model()) )
    return QModelIndex();
  else{
    //toohot 060730 if( !(amodel = model->get_proxyModel()) )
      amodel = model;
    return     model->get_transposed()
             ? amodel->index(col,item_data->get_row(),parent->GetModelIndex())
             : amodel->index(item_data->get_row(),col,parent->GetModelIndex()) ;
  }

}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CellData :: GetPropertyHandle ( )
{
  ODSList   *ods = ListODS();
  return ( ods ? ods->Handle() : NULL );

}

/******************************************************************************/
/**
\brief  GetTextAlignment - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextAlignment"

QVariant CellData :: GetTextAlignment ( )
{
  ItemTreeModel   *model = this ? item_data->Model() : NULL;
  int              align = Qt::AlignLeft;

BEGINSEQ
  if ( !model )                                      ERROR
    
  if ( !model->get_transposed() && ListODS()->IsNumber() )
    align = Qt::AlignRight;
  
  align|=Qt::AlignVCenter;
RECOVER

ENDSEQ
  return(align);
}

/******************************************************************************/
/**
\brief  GetTextColor - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextColor"

QVariant CellData :: GetTextColor ( )
{
  QColor   *color = NULL;
  if ( item_data->get_heading() )
    color = item_data->Region()->GetTextColor();
  else  
    if ( !(color = ODataLayoutRef::GetTextColor()) )
      color = item_data->Region()->Column(col)->GetTextColor();

  return ( color ? QVariant(QVariant::Color,color) : QVariant() );

}

/******************************************************************************/
/**
\brief  GetToolTip - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetToolTip"

QVariant CellData :: GetToolTip ( )
{
  char  *string = NULL;
  if ( item_data->get_heading() == 1 )
    string = item_data->Region()->GetToolTip();  
  else
    string = item_data->Region()->Column(col)->GetToolTip();  
  
  return ( string ? QVariant(string) : QVariant() );

}

/******************************************************************************/
/**
\brief  IsReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical CellData :: IsReadOnly ( )
{

  return ( ListODS()->InstIsReadOnly() );

}

/******************************************************************************/
/**
\brief  Item - 



\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Item"

ItemData *CellData :: Item ( )
{

  return ( this ? item_data : NULL );

}

/******************************************************************************/
/**
\brief  ListODS - 



\return pODSList - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListODS"

ODSList *CellData :: ListODS ( )
{

  return (   this
           ? item_data->Region()->Column(col)
           : NULL   );

}

/******************************************************************************/
/**
\brief  Parent - 



\return pCellData - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

CellData *CellData :: Parent ( )
{
  ItemData     *parent_item = NULL;
  return(   this && (parent_item = item_data->Parent())
          ? parent_item->Cell(col)
          : NULL                    );

}

/******************************************************************************/
/**
\brief  SetData - 



\return term - 

\param  qvariant - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical CellData :: SetData (const QVariant &qvariant )
{
  ODSList  *ods  = ListODS();
  logical   term = NO;
BEGINSEQ
  if ( item_data->get_heading() )                    LEAVESEQ

  if ( !ods )                                        ERROR
  if ( item_data->Position() )                       ERROR
  
  if ( ods->IsBool() )
    ods->ValueSet(qvariant.toInt() == Qt::Checked ? YES : NO);
  else  
    ods->ValueSet(qvariant.toString());

  UpdateData();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDataWidget - 




\param  pOEHControlData - 
\param  pODSList - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataWidget"

void CellData :: SetDataWidget (OEHControlData *pOEHControlData, ODSList *pODSList )
{
  ODSList    *ods = ListODS();
  if ( this && ods )
    ods->SetControlData(pOEHControlData);


}

/******************************************************************************/
/**
\brief  ToggleChecked - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToggleChecked"

logical CellData :: ToggleChecked ( )
{
  ODSList                *ods  = ListODS();
  logical                 check_state;
  logical                 cond = NO;
BEGINSEQ
  if ( !ods->IsBool() )                               ERROR

  check_state = ods->ValueIsTrue() ? false : true;
  ods->ValueSet(check_state);
  ods->ValueStore();
    
  UpdateData();
  cond = YES;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  UpdateData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

void CellData :: UpdateData ( )
{

  if ( this )
  {
    FillData(NO);
    item_data->Model()->UpdateData(this);
  }

}

/******************************************************************************/
/**
\brief  ~CellData - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CellData"

     CellData :: ~CellData ( )
{



}


