/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ItemRegionList

\brief    Item Region list
          An item Region List handle the items from one or more regions.

\date     $Date: 2006/08/24 16:55:49,04 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ItemRegionList"

#include  <pogui7.h>
#include  <decl_mt.h>
#include  <sItemData.hpp>
#include  <sItemRegion.hpp>
#include  <sItemTreeModel.hpp>
#include  <sODSItem.hpp>
#include  <sODSRegion.hpp>
#include  <sOTreeLayout.hpp>
#include  <sItemRegionList.hpp>


/******************************************************************************/
/**
\brief  Clear - 




\param  del_regions - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ItemRegionList :: Clear (logical del_regions )
{
  ItemRegion     *region = NULL;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  GoTop();
  while ( region = GetNext() )
  {
    if ( !del_regions )
      region->Clear();
    else
    {
      delete region;
      RemoveAt();
      GoTop();
    }
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  Count - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

int ItemRegionList :: Count ( )
{
  ItemRegion   *region      = NULL;
  int           count       = 0;
BEGINSEQ
  if ( !this )                                       ERROR
    
  GoTop();
  while ( region = GetNext() )
  {
    region->SetupStaticRow(count,parent);
    count += region->Count(parent->IsStaticItem() ? parent : NULL,NO);
  }
RECOVER

ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  FillMetaModel - 



\return model_index - 

\param  pQStandardItemModel - 
\param  pItemData - ItemData
\param  mi_parent_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillMetaModel"

QModelIndex ItemRegionList :: FillMetaModel (QStandardItemModel *pQStandardItemModel, ItemData *pItemData, const QModelIndex &mi_parent_w )
{
  ItemRegion  *region     = NULL;
  ODSRegion   *ods_region = NULL;
  int          row        = 0;
  QVariant     qvar(QVariant::UserType+1);
  QModelIndex  model_index;
BEGINSEQ
  if ( !this )                                       ERROR
    
  pQStandardItemModel->insertRows(0,GetCount(),mi_parent_w);
  pQStandardItemModel->insertColumns(0,4,mi_parent_w);
  
  GoTop();
  while ( region = GetNext() )
  {
    if ( ods_region = region->Region() )
    {
      qvar.setValue<ODSRegion *>(ods_region);
      pQStandardItemModel->setData(pQStandardItemModel->index(row,0,mi_parent_w),
                                   ods_region->Handle()->GetCurrentType(),Qt::DisplayRole);
      pQStandardItemModel->setData(pQStandardItemModel->index(row,1,mi_parent_w),
                                   qvar,Qt::DisplayRole);
      pQStandardItemModel->setData(pQStandardItemModel->index(row,2,mi_parent_w),
                                   ods_region->Item()->get_path().get_path(),Qt::DisplayRole);
      pQStandardItemModel->setData(pQStandardItemModel->index(row,3,mi_parent_w),
                                   ods_region->Item()->getKey(YES),Qt::DisplayRole);
      
      if ( pItemData && ods_region == pItemData->Region() )
      {
        model_index = pQStandardItemModel->index(row,0,mi_parent_w);
        pItemData->Children()->FillMetaModel(pQStandardItemModel,NULL,model_index);
      }
    }
    row++;
  }
RECOVER

ENDSEQ
  return (   model_index.isValid() 
           ? model_index 
           : pQStandardItemModel->index(0,0));
}

/******************************************************************************/
/**
\brief  FindRegion - 



\return pItemRegion - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindRegion"

ItemRegion *ItemRegionList :: FindRegion (ODSRegion *pODSRegion )
{
  ItemRegion     *region = NULL;
BEGINSEQ
  GoTop();
  while ( region = GetNext() )
    if ( region->get_region() == pODSRegion )        LEAVESEQ
ENDSEQ
  return(region);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindRegion"

ItemRegion *ItemRegionList :: FindRegion (OTreeLayout *pOTreeLayout )
{
  ItemRegion     *region = NULL;
BEGINSEQ
  GoTop();
  while ( region = GetNext() )
    if ( region->get_region()->get_layout() == pOTreeLayout )  LEAVESEQ
ENDSEQ
  return(region);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindRegion"

ItemRegion *ItemRegionList :: FindRegion (int32 region_id )
{
  ItemRegion     *region = NULL;
BEGINSEQ
  GoTop();
  while ( region = GetNext() )
    if ( region->get_region()->get_layout()->get_intern_id() == region_id )  
                                                    LEAVESEQ

ENDSEQ
  return(region);
}

/******************************************************************************/
/**
\brief  HasItems - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasItems"

logical ItemRegionList :: HasItems ( )
{
  ItemRegion     *region = NULL;
  logical         cond   = YES;
BEGINSEQ
  if ( !this )                                       ERROR 
    
  GoTop();
  while ( region = GetNext() )
    if ( region->GetSize() > 0 )                     LEAVESEQ

  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  HaveColChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HaveColChanged"

logical ItemRegionList :: HaveColChanged ( )
{
  ItemRegion     *region = NULL;
  logical         cond   = YES;
BEGINSEQ
  if ( !this )                                       ERROR
    
  GoTop();
  while ( region = GetNext() )
    if ( region->HasColChanged() )
    {
      SetDirty();
      LEAVESEQ
    }
    
  cond = NO;
RECOVER
  cond = NO;
ENDSEQ

  return(cond);
}

/******************************************************************************/
/**
\brief  InitRegions - 



\return term - 

\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRegions"

logical ItemRegionList :: InitRegions (ODSRegion *pODSRegion )
{
  ODSRegion     *sub_reg    = NULL;
  int            indx0      = 0;
  logical        term       = NO;
  if ( pODSRegion )
    while ( sub_reg = pODSRegion->Region(indx0++) ) 
      ProvideRegion(sub_reg);

  return(term);
}

/******************************************************************************/
/**
\brief  InsertItem - 



\return new_item - 

\param  row - 
\param  pItemRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertItem"

ItemData *ItemRegionList :: InsertItem (int row, ItemRegion *pItemRegion )
{
  ItemRegion     *region    = NULL;
  int             start_row = 0;
  ItemData       *new_item  = NULL;
BEGINSEQ
  GoTop();
  while ( region = GetNext() )
  {
    if ( new_item )
      region->SetupItemRows(start_row);
    else
    {
      if ( region == pItemRegion )
        if ( !(new_item = region->InsertItem(row)) ) ERROR
    }
    
    start_row = region->GetSize();
  }

RECOVER

ENDSEQ
  return(new_item);
}

/******************************************************************************/
/**
\brief  IsDirty - 



\return term - 

\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDirty"

logical ItemRegionList :: IsDirty (logical chk_opt )
{
  logical  term = NO;

BEGINSEQ
  if ( !this )                                       ERROR
  
  if ( chk_opt )
    HaveColChanged();
    
  // j060103:
  // keine ahnung ob das eine gute idee ist
  // wenn man hier ehrlich antwortet kommt es zu sehr
  // komischen resultaten.
  // immer NO war am befriedigsten
  term = NO;
  //term = is_dirty;

RECOVER

ENDSEQ
  return (term);
}

/******************************************************************************/
/**
\brief  Item - 



\return pItemData - ItemData

\param  row - 
\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Item"

ItemData *ItemRegionList :: Item (int row, ItemData *parent_item_data )
{
  ItemRegion *region    = NULL;
  int         count     = 0;
  int         rcount    = 0;
  int         index0    = 0;
  ItemData   *item_data = NULL;
BEGINSEQ
  if ( parent_item_data && 
       (parent_item_data->IsHeaderItem() ||
        parent_item_data->IsStaticItem()   ) )
    region = parent_item_data->get_region();
  else
  {
    GoTop();
    while ( region = GetNext() )
    {
      rcount = region->Count(parent_item_data,NO);
      if ( count + rcount > row )
        break;
      count += rcount;
    }
  }
  if ( !region )                                     ERROR

  region->SetFirstRow(count);
  item_data = region->Item(row - count,parent_item_data);
RECOVER
  item_data = NULL;
ENDSEQ
  return(item_data);
}

/******************************************************************************/
/**
\brief  ItemByKey - 



\return pItemData - ItemData

\param  skey - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByKey"

ItemData *ItemRegionList :: ItemByKey (char *skey, logical provide )
{
  ItemRegion       *region    = NULL;
  ItemData         *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  GoTop();
  while ( region = GetNext() )
    if ( pItemData = region->ItemByKey(skey,provide) )
      LEAVESEQ
RECOVER

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByLOID - 



\return pItemData - ItemData

\param  objid - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByLOID"

ItemData *ItemRegionList :: ItemByLOID (int32 objid, logical provide )
{
  ItemRegion       *region    = NULL;
  ItemData         *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  GoTop();
  while ( region = GetNext() )
    if ( pItemData = region->ItemByLOID(objid,provide) )
      LEAVESEQ
RECOVER

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByValue - 



\return pItemData - ItemData

\param  pQString - 
\param  col - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByValue"

ItemData *ItemRegionList :: ItemByValue (QString &pQString, int col )
{
  ItemRegion       *region    = NULL;
  ItemData         *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  GoTop();
  while ( region = GetNext() )
    if ( pItemData = region->ItemByValue(pQString,col) )
      LEAVESEQ
RECOVER

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemRegionList - 




\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemRegionList"

     ItemRegionList :: ItemRegionList (ItemData *pItemData )
                     : DLL(ItemRegion) (),
  parent(pItemData),
  is_dirty(NO)
{

  if ( pItemData )
  {
    if ( pItemData->IsStaticItem() )
      AddTail(pItemData->get_region());
    else
      InitRegions(pItemData->Region());
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

ItemTreeModel *ItemRegionList :: Model ( )
{

  return( !this  ? NULL :
          parent ? parent->Model()
                 : (ItemTreeModel *)this );

}

/******************************************************************************/
/**
\brief  Parent - 



\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

ItemData *ItemRegionList :: Parent ( )
{

  return( this ? parent : NULL );

}

/******************************************************************************/
/**
\brief  ProvideRegion - 



\return term - 

\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideRegion"

logical ItemRegionList :: ProvideRegion (ODSRegion *pODSRegion )
{
  logical                 term = NO;
  if ( !FindRegion(pODSRegion) )
    AddTail(new ItemRegion(this,pODSRegion));
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveItem - 



\return term - 

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItem"

logical ItemRegionList :: RemoveItem (ItemData *pItemData )
{
  ItemRegion     *region    = NULL;
  int             start_row = 0;
  logical         removed   = NO;
  GoTop();
  while ( region = GetNext() )
  {
    if ( removed )
      region->SetupItemRows(start_row);
    else
    {
      if ( region == pItemData->get_region() )
        removed = !region->RemoveItem(pItemData->get_row());
    }
    
    start_row = region->GetSize();
  }

  return(!removed);
}

/******************************************************************************/
/**
\brief  RemoveRegion - 




\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveRegion"

void ItemRegionList :: RemoveRegion (int32 region_id )
{
  ItemRegion     *region = NULL;
  GoTop();
  while ( region = GetNext() )
  {
    if ( region->get_region()->GetLayout()->get_intern_id() == region_id )
    {
      region->Clear();
      delete region;
      RemoveAt();
      GoTop();
    }
    else
      region->RemoveRegion(region_id);
  }

}

/******************************************************************************/
/**
\brief  ResetHandles - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetHandles"

logical ItemRegionList :: ResetHandles ( )
{
  ItemRegion    *sub_reg    = NULL;
  int            indx0      = 0;
  logical        term       = NO;
  GoTop();
  while ( sub_reg = GetNext() ) 
    sub_reg->get_region()->Handle()->ToTop();

  return(term);
}

/******************************************************************************/
/**
\brief  SetDirty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDirty"

void ItemRegionList :: SetDirty ( )
{

  is_dirty = YES;

}

/******************************************************************************/
/**
\brief  UpdateData - 




\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

void ItemRegionList :: UpdateData (logical chk_opt )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( chk_opt )
    if ( !IsDirty(YES) )                             LEAVESEQ
  
  //j060103: wenn dirty YES bleibt kommt
  // es hier zu einer haesslichen rekursion
  
  is_dirty = NO;
  Model()->RemoveRows(parent);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ItemRegionList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ItemRegionList"

     ItemRegionList :: ~ItemRegionList ( )
{
  ItemRegion  *item_region  = NULL;
  logical      owns_regions = !parent->IsStaticItem();
  while ( item_region = RemoveTail() )
    if ( owns_regions )
      delete item_region;

}


