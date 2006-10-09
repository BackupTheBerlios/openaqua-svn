/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ItemData

\brief    


\date     $Date: 2006/08/22 19:02:19,09 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ItemData"

#include  <pogui7.h>
#include  <cqt.h>
#ifndef   DPA_CellData_HPP
#define   DPA_CellData_HPP
#include  <sCellData.hpp>
#include  <sDPA.h>
#endif
#include  <sCellData.hpp>
#include  <sDFont.hpp>
#include  <sDPixmap.hpp>
#include  <sItemData.hpp>
#include  <sItemRegion.hpp>
#include  <sItemRegionList.hpp>
#include  <sItemTreeModel.hpp>
#include  <sODSItem.hpp>
#include  <sODSList.hpp>
#include  <sODSRegion.hpp>
#include  <sODataLayoutRef.hpp>
#include  <sOEHControlData.hpp>
#include  <sOFont.hpp>
#include  <sPropertyHandle.hpp>
#include  <sQAbstractItemModel.hpp>
#include  <sItemData.hpp>


/******************************************************************************/
/**
\brief  Cell - 



\return cell - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cell"

CellData *ItemData :: Cell (int column )
{
  CellData     *cell = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  if ( column == 0 )
    cell = !cells ? this : cells->GetAt(0);
  else
  {
    if ( !cells )                                  
    {
      if ( !heading )                                OGUIERR(99)
      LEAVESEQ
    }
    if ( !(cell = cells->GetAt(column)) )
    {
      if ( column >= cells->GetSize() )              ERROR
      cells->SetAt(column,new CellData(this,column));
      cell = cells->GetAt(column);
    }
  }
RECOVER

ENDSEQ
  return(cell);
}

/******************************************************************************/
/**
\brief  Children - 



\return pItemRegionList - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Children"

ItemRegionList *ItemData :: Children ( )
{
  ODSRegion     *ods_region = Region();
BEGINSEQ
  if ( children )                                    LEAVESEQ
  
  ods_region->SetupLayout();
  if ( !ods_region->HasSubRegions() )                ERROR
  
  children = new ItemRegionList(this);

  
  

RECOVER

ENDSEQ
  return(children);
}

/******************************************************************************/
/**
\brief  GetCheckState - 



\return qvariant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCheckState"

QVariant ItemData :: GetCheckState ( )
{

  return ( this ? QVariant(IsChecked() ? true : false) 
                : QVariant() );

}

/******************************************************************************/
/**
\brief  GetHierarchyPath - 




\param  string_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHierarchyPath"

void ItemData :: GetHierarchyPath (VECTOR(std_string) &string_list )
{
  char                      *sztext = NULL;
BEGINSEQ
  if ( !this )                                      LEAVESEQ
  if ( !key_val ){
    sztext = Region()->GetStaticText();
  }else{
    sztext = key_val;
  }
  if(sztext)
    string_list.push_back(std::string(sztext));
  
  Parent()->GetHierarchyPath(string_list);

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetKey - 



\return key_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *ItemData :: GetKey ( )
{

  return ( this ? key_val : NULL );

}

/******************************************************************************/
/**
\brief  GetLayout - 



\return dfont - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLayout"

DFont ItemData :: GetLayout (int column )
{

  return ( GetLayoutRef(column)->GetLayout() );


}

/******************************************************************************/
/**
\brief  GetLayoutRef - 



\return pODataLayoutRef - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLayoutRef"

ODataLayoutRef *ItemData :: GetLayoutRef (int column )
{
  CellData        *cell       = NULL;
  ODataLayoutRef  *layout_ref = NULL;

BEGINSEQ
  if ( !this )                                      OGUIERR(99)
    
  if ( column < 0 )
    layout_ref = this;
  else  
    if ( cell = Cell(column) )
      layout_ref = cell;

RECOVER

ENDSEQ
  return(layout_ref);
}

/******************************************************************************/
/**
\brief  GetModelIndex - 



\return mindex - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModelIndex"

QModelIndex ItemData :: GetModelIndex ( )
{
  ItemTreeModel      *model       = NULL;
  ItemData           *parent      = NULL;
  ItemRegionList     *parent_list = NULL;
  QAbstractItemModel *amodel   = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  model  = Model();
  parent = Parent();
  if ( !model )                                      ERROR
  if ( row == AUTO )
  {
    parent_list = parent ? parent->Children() : model;
    parent_list->Count();
  }
  //toohot 060730if( !(amodel = model->get_proxyModel()) )
    amodel = model;
  return ( model->get_transposed()
           ? amodel->index(0,row,parent->GetModelIndex())
           : amodel->index(row,0,parent->GetModelIndex()) );
RECOVER

ENDSEQ
  return QModelIndex() ;
}

/******************************************************************************/
/**
\brief  Handle - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Handle"

PropertyHandle *ItemData :: Handle ( )
{

  return( Region()->Handle() );

}

/******************************************************************************/
/**
\brief  HasLayout - 



\return cond - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasLayout"

logical ItemData :: HasLayout (int column )
{

  return ( GetLayoutRef(column)->HasLayout() );  


}

/******************************************************************************/
/**
\brief  HierSync - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierSync"

logical ItemData :: HierSync (logical block_opt )
{
  ODSRegion    *ods_region = Region();
  logical       blocked    = NO;
  logical       term       = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( !ods_region )                                 ERROR
  
  Parent()->HierSync(block_opt);
  
  if ( !heading )
  {
    blocked = ods_region->signalsBlocked();
    if ( block_opt && !blocked )
      ods_region->BlockSignals(YES);
                                    
    if ( ods_region->ColSync(lastObjID,lastIndex) ) // modified
      if ( blocked || block_opt )
        ods_region->ResetChildStates();
        
    SyncValue(ods_region);
                          
    if ( block_opt && !blocked )
      ods_region->BlockSignals(NO);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierSync"

logical ItemData :: HierSync ( )
{
  logical     term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  if ( !expanded && Model()->IsItemExpanded(this) )
    expanded = AUTO;
    
  term = HierSync(expanded == AUTO ? YES : NO);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsChecked - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsChecked"

logical ItemData :: IsChecked ( )
{

  return( this ? checked : NO );

}

/******************************************************************************/
/**
\brief  IsExpanding - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpanding"

logical ItemData :: IsExpanding ( )
{

  return ( this && expanded == AUTO ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsHeaderItem - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsHeaderItem"

logical ItemData :: IsHeaderItem ( )
{

  return ( this && heading == 2 ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsItemDBIndex - 



\return this - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemDBIndex"

ItemData *ItemData :: IsItemDBIndex (int32 indx0 )
{

  return (   this && lastIndex != AUTO && lastIndex == indx0 
           ? this 
           : NULL );

}

/******************************************************************************/
/**
\brief  IsItemKey - 



\return this - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemKey"

ItemData *ItemData :: IsItemKey (char *skey )
{

  return (   this && key_val && !strcmp(key_val,skey) 
           ? this 
           : NULL );

}

/******************************************************************************/
/**
\brief  IsItemLOID - 



\return this - 

\param  objid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemLOID"

ItemData *ItemData :: IsItemLOID (int32 objid )
{

  return (   this && lastObjID == objid 
           ? this 
           : NULL );

}

/******************************************************************************/
/**
\brief  IsItemRow - 



\return this - 

\param  index0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemRow"

ItemData *ItemData :: IsItemRow (int index0 )
{

  return (   this && row == index0 
           ? this 
           : NULL );

}

/******************************************************************************/
/**
\brief  IsItemValue - 



\return this - 

\param  pQString - 
\param  col - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemValue"

ItemData *ItemData :: IsItemValue (QString &pQString, int col )
{

  return (  col != AUTO || Cell(0) 
            ? Cell(col==AUTO ? 0 : col)->GetData() == pQString ? this : NULL
            : IsItemKey(QS2SZ(pQString)) ); 


}

/******************************************************************************/
/**
\brief  IsStaticItem - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsStaticItem"

logical ItemData :: IsStaticItem ( )
{

  return ( this && heading == 1 ? YES : NO );

}

/******************************************************************************/
/**
\brief  ItemData - 



\return term - 

\param  pItemRegion - 
\param  row_no - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemData"

     ItemData :: ItemData (ItemRegion *pItemRegion, int row_no )
                     : CellData (this,0),
  region(pItemRegion),
  children(NULL),
  row(row_no),
  cells(NULL),
  key_val(NULL),
  heading(NO),
  expanded(NO),
  checked(NO),
  is_updating(NO)

{
  int   col_count = pItemRegion->get_region()->ColumnCount();
  if ( col_count > 1 )
  {
    cells = new DPA(CellData)(col_count);
    cells->SetAt(0,this);
  }

}

/******************************************************************************/
/**
\brief  Model - 



\return pItemTreeModel - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Model"

ItemTreeModel *ItemData :: Model ( )
{

  return( this ? region->Model() : NULL );

}

/******************************************************************************/
/**
\brief  Parent - 



\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

ItemData *ItemData :: Parent ( )
{

  return( this ? region->Parent(this) : NULL );

}

/******************************************************************************/
/**
\brief  Position - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical ItemData :: Position ( )
{
  PropertyHandle         *ph = Region()->Handle();
  logical                 blocked = NO;
  logical                 term = NO;
BEGINSEQ
  if ( !ph->IsPositioned() )                         ERROR

  blocked = Region()->BlockEvents(YES);
  HierSync(NO);

  if ( !ph->IsPositioned() )                         ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( blocked )
    if ( !Region()->BlockEvents(NO) )
    {
      OGUISET(18)
      OGUIRESET
    }
  return(term);
}

/******************************************************************************/
/**
\brief  Region - 



\return pODSRegion - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Region"

ODSRegion *ItemData :: Region ( )
{

  return( this ? region->Region() : NULL );

}

/******************************************************************************/
/**
\brief  RegionList - 



\return pItemRegionList - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegionList"

ItemRegionList *ItemData :: RegionList ( )
{

  return (   this && region 
           ? region->get_region_list() 
           : NULL   );

}

/******************************************************************************/
/**
\brief  ResetChildData - 




\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetChildData"

void ItemData :: ResetChildData (logical chk_opt )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( is_updating )                                 LEAVESEQ
   
  if ( !chk_opt || heading || 
       (lastObjID > 0 && lastObjID == Region()->Handle()->GetID()) )
    children->ResetHandles();
  else
    children->SetDirty();
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetExpanded - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpanded"

void ItemData :: SetExpanded (logical option )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( expanded == option )                          LEAVESEQ
    
  if ( !(expanded = option) ) // collapsing
    UpdateChildData(YES);
  


ENDSEQ

}

/******************************************************************************/
/**
\brief  SetHeading - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHeading"

void ItemData :: SetHeading ( )
{

  heading = 2;

  Setup();

}

/******************************************************************************/
/**
\brief  SetIcon - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pQIcon - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

logical ItemData :: SetIcon (QIcon *pQIcon, int column )
{
  ODataLayoutRef  *layout_ref = GetLayoutRef(column);
  logical          term       = NO;
BEGINSEQ
  if ( !layout_ref )                                 ERROR

  layout_ref->ProvideDataLayout(YES);  
  layout_ref->SetIcon(pQIcon);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

logical ItemData :: SetIcon (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, int column )
{
  ODataLayoutRef  *layout_ref = GetLayoutRef(column);
  logical          term       = NO;
BEGINSEQ
  if ( !layout_ref )                                 ERROR

  layout_ref->ProvideDataLayout(YES);  
  layout_ref->SetIcon(pDPixmap_normal,pDPixmap_active,pDPixmap_disabled);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetKey - 




\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

void ItemData :: SetKey (char *skey )
{

BEGINSEQ
  if ( key_val )
  {
    if ( skey && !strcmp(key_val,skey) )             LEAVESEQ
      
    free(key_val);
    key_val = NULL;
  }

  if ( skey )
    key_val = strdup(skey);
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetLayout - 



\return term - 

\param  pDFont - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLayout"

logical ItemData :: SetLayout (DFont *pDFont, int column )
{
  ODataLayoutRef  *layout_ref = GetLayoutRef(column);
  logical          term       = NO;
BEGINSEQ
  if ( !layout_ref )                                 ERROR

  layout_ref->ProvideDataLayout(YES);  
  layout_ref->SetLayout(pDFont);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetStatic - 




\param  pItemRegionList - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatic"

void ItemData :: SetStatic (ItemRegionList *pItemRegionList )
{

  heading  = 1;
  children = new ItemRegionList(this);  

  Setup();

}

/******************************************************************************/
/**
\brief  Setup - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical ItemData :: Setup ( )
{
  PropertyHandle   *ph    = NULL;
  CellData         *cell  = NULL;
  char             *key   = NULL;
  char              string[1024];
  int               indx0 = 0;
  logical           term  = NO;
BEGINSEQ
  if ( !heading )
  {
    ph = Region()->Handle();
    
    if ( !ph->Exist() || (lastObjID > 0 && lastObjID != ph->GetID()) ) 
       OGUIERR(99) 

    SetValue(ph);
  
    if ( key = ph->GetKey(AUTO) )
      SetKey(ph->KeyToString(string,key));
    else
      SetKey(NULL);
  }
    
  if ( !cells )
    FillData(YES);
  else
    while ( cell = Cell(indx0++) )
      cell->FillData(YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ToggleChecked - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToggleChecked"

void ItemData :: ToggleChecked ( )
{

  if ( this )
  {
    checked = !checked;
    Model()->UpdateData(this);
  }


}

/******************************************************************************/
/**
\brief  UpdateChildData - 




\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateChildData"

void ItemData :: UpdateChildData (logical chk_opt )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( is_updating )                                 LEAVESEQ
   
  ResetChildData(YES);

  if ( chk_opt )
    children->HaveColChanged();
  else
    children->SetDirty();
ENDSEQ

}

/******************************************************************************/
/**
\brief  set_is_updating - 




\param  update_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_is_updating"

void ItemData :: set_is_updating (logical update_opt )
{

  is_updating = update_opt;

}

/******************************************************************************/
/**
\brief  set_row - 




\param  index0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_row"

void ItemData :: set_row (int index0 )
{

BEGINSEQ
  if ( !this )                                       ERROR
  
  row = index0;
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  setup_lastIndex - 




\param  diff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setup_lastIndex"

void ItemData :: setup_lastIndex (int32 diff )
{

  lastIndex += diff;

}

/******************************************************************************/
/**
\brief  ~ItemData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ItemData"

     ItemData :: ~ItemData ( )
{
  CellData  *cell   = NULL;
  int        count  = cells->GetSize();
  int        column = 1;
  Model()->ResetCurItem(this,NO);
  
  delete children;
  children = NULL;
  
  if ( key_val )
    free(key_val);
  key_val = NULL;

  while ( column < count )
  {
    if ( cell = cells->GetAt(column) )
      delete cell;
    column++;
  }
  
  delete cells;
  cells = NULL;



}


