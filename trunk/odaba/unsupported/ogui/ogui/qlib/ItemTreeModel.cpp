/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ItemTreeModel

\brief    


\date     $Date: 2006/08/26 17:49:39,68 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ItemTreeModel"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sCellData.hpp>
#include  <sItemData.hpp>
#include  <sItemRegion.hpp>
#include  <sODSList.hpp>
#include  <sODSRegion.hpp>
#include  <sODataWidget.hpp>
#include  <sODragObject.hpp>
#include  <sOEHControlData.hpp>
#include  <sOListCtl.hpp>
#include  <sOTreeLayout.hpp>
#include  <sItemTreeModel.hpp>


/******************************************************************************/
/**
\brief  Cell - 



\return pCellData - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cell"

CellData *__cdecl ItemTreeModel :: Cell (const QModelIndex &model_index )
{

  return (   model_index.isValid() 
           ? (CellData *)model_index.internalPointer()
           : NULL );

}

/******************************************************************************/
/**
\brief  ChildList - 



\return pItemRegionList - 

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChildList"

ItemRegionList *ItemTreeModel :: ChildList (ItemData *pItemData ) const
{

  return ( pItemData ? pItemData->Children()
                     : (ItemRegionList *)this );


}

/******************************************************************************/
/**
\brief  ClearData - 




\param  del_regions - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void ItemTreeModel :: ClearData (logical del_regions )
{

  ItemRegionList::Clear(del_regions);
  
  SetCurItem(NULL);   // j 051212 crash while setting type of member attribute; nd:sollte wegen item_data destructor schon NULL sein
  initialized = NO;
  
  reset();
  ResetState();

}

/******************************************************************************/
/**
\brief  FillItems - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillItems"

logical ItemTreeModel :: FillItems ( )
{
statistics3.Start();
  QModelIndex             model_index;
  int32                   count   = 0;
  int32                   indx0   = 0;
  logical                 blocked = NO;
  logical                 term    = NO;
BEGINSEQ
  if ( !(count = transposed ? columnCount() : rowCount()) )
                                                     LEAVESEQ
  blocked = BlockEvents(YES);
  
  initialized = YES;  // -=6 lines wegen rekursion (item->hiersync->isexpanded->index->fillitems)
  
  while ( indx0 < count )
    ItemRegionList::Item(indx0++,NULL);

  if ( blocked )
    if ( !BlockEvents(NO) )
    {
      OGUISET(18)
      OGUIRESET
    }


ENDSEQ
statistics3.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  FillMetaModel - 



\return pQModelIndex - 

\param  pQStandardItemModel - 
\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillMetaModel"

QModelIndex ItemTreeModel :: FillMetaModel (QStandardItemModel *pQStandardItemModel, ItemData *pItemData )
{
  QModelIndex    model_index;
BEGINSEQ
  if ( !this )                                       ERROR
    
  model_index = RegionList(pItemData)->
                FillMetaModel(pQStandardItemModel,pItemData);
  
  pQStandardItemModel->setHeaderData(0,Qt::Horizontal,"Type",Qt::DisplayRole);
  pQStandardItemModel->setHeaderData(2,Qt::Horizontal,"Path",Qt::DisplayRole);
  pQStandardItemModel->setHeaderData(3,Qt::Horizontal,"Current Key",Qt::DisplayRole);

RECOVER

ENDSEQ
  return(model_index);
}

/******************************************************************************/
/**
\brief  FilterChanged - 



\return term - 

\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FilterChanged"

logical ItemTreeModel :: FilterChanged (ODSRegion *pODSRegion )
{

  return ( FindRegion(pODSRegion)->UpdateData() );


}

/******************************************************************************/
/**
\brief  FindRegion - 



\return pItemRegion - 

\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindRegion"

ItemRegion *ItemTreeModel :: FindRegion (ODSRegion *pODSRegion )
{
  ODSRegion      *parent_ods  = NULL;
  ItemData       *parent_item = NULL;
  int32           parent_loid = 0;
  ItemRegion     *item_region = NULL;

  if ( !pODSRegion )
    item_region = ItemRegionList::GetHead();
  else if ( !(parent_ods = pODSRegion->ParentRegion()) )
    item_region = ItemRegionList::FindRegion(pODSRegion);
  else
  {
    parent_loid = parent_ods->Handle()->GetID(AUTO);
    parent_item = ItemByLOID(parent_ods,parent_loid,NO);
    if(parent_item)
      item_region = parent_item->Children()->FindRegion(pODSRegion);
    else  // there is no parent (tree root)
      item_region = ItemRegionList::FindRegion(pODSRegion);
  }
  return(item_region);
}

/******************************************************************************/
/**
\brief  GetSortProxy - 



\return pQAbstractItemModel - 

\param  pQAbstractItemView - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortProxy"

QAbstractItemModel *ItemTreeModel :: GetSortProxy (QAbstractItemView *pQAbstractItemView )
{

BEGINSEQ
OGUIERR(99)
proxyModel = new QSortFilterProxyModel(pQAbstractItemView);
proxyModel->setSourceModel(this);
return proxyModel;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  InitRegions - 



\return term - 

\param  pODSTree - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRegions"

logical ItemTreeModel :: InitRegions (ODSTree *pODSTree )
{
  logical                 no_regions = !HasSubRegions();
  logical                 term = NO;
  if ( DefinesCollection() || no_regions )
    term = ProvideRegion(this);
  else
    term = ItemRegionList::InitRegions(this);
  return(term);
}

/******************************************************************************/
/**
\brief  InsertItem - 



\return new_item - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertItem"

ItemData *ItemTreeModel :: InsertItem (ODSRegion *pODSRegion )
{
  PropertyHandle *ph          = pODSRegion->Handle();
  int32           indx0       = AUTO;
  logical         blocked     = NO;
  ItemData       *new_item    = NULL;


BEGINSEQ
  if ( !ph )                                         ERROR
  
  indx0 = ph->GetCurrentIndex();
  
  if ( !(new_item = InsertItem(pODSRegion,indx0)) )  ERROR

  if ( ph->GetCurrentIndex() != indx0 )  // OComboBox mit list_sa_ods stellt auf zuvor eingestellten zurueck
  {
    blocked = BlockEvents(YES);

    ph->Get(indx0);

    if ( blocked )
      if ( !BlockEvents(NO) )
      {
        OGUISET(18)
        OGUIRESET
      }
  }

RECOVER

ENDSEQ
  return(new_item);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODSRegion - 
\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertItem"

ItemData *ItemTreeModel :: InsertItem (ODSRegion *pODSRegion, int32 indx0 )
{
  OListCtl       *list_ctl    = GetListControl();
  ItemRegion     *item_region = FindRegion(pODSRegion);
  ItemRegionList *region_list = NULL;
  ItemData       *parent      = NULL;
  int             index0      = -1;
  ItemData       *new_item    = NULL;
BEGINSEQ
  if ( !item_region || indx0 == AUTO )               ERROR
  parent = item_region->Parent(NULL);

  if ( parent && !parent->get_expanded() && !item_region->GetSize() )
  {
    item_region->Count(parent,YES);
    list_ctl->ExpandIndex(parent->GetModelIndex());
    if ( !(new_item = item_region->ItemByDBIndex(indx0,NO)) )
                                                    OGUIERR(99)
  }
  else
  {
    if ( parent ) 
      parent->set_is_updating(YES);

    index0      = item_region->GetRowForDBIndex(indx0);
    region_list = item_region->get_region_list();
  
    if ( transposed )
      beginInsertColumns(parent->GetModelIndex(),index0,index0);
    else
      beginInsertRows(parent->GetModelIndex(),index0,index0);
  
    new_item = region_list->InsertItem(index0,item_region);
  
    endInsertRows();

    if ( parent ) 
      parent->set_is_updating(YES);
  }
RECOVER
  new_item = NULL;
ENDSEQ
  FlushEvents();
  return(new_item);
}

/******************************************************************************/
/**
\brief  IsRelated - 



\return cond - 

\param  model_index - 
\param  model_index_compare - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRelated"

logical ItemTreeModel :: IsRelated (const QModelIndex &model_index, const QModelIndex &model_index_compare )
{
  logical                 term = NO;
  ItemData               *pItemData = NULL
                        ,*pItemDataCompare = NULL;
BEGINSEQ
  pItemData = Item(model_index);
  pItemDataCompare = Item(model_index_compare);

  if(!pItemData || !pItemDataCompare)                ERROR
  term = pItemData->get_region() == pItemDataCompare->get_region()
      && pItemData->Parent()     == pItemDataCompare->Parent();
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsVisible - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsVisible"

logical ItemTreeModel :: IsVisible ( ) const
{
  OListCtl        *list_ctl = GetListControl();
  return ( list_ctl->IsVisible() && !list_ctl->InDesignMode() );

}

/******************************************************************************/
/**
\brief  Item - 



\return pItemData - ItemData

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Item"

ItemData *ItemTreeModel :: Item (const QModelIndex &model_index ) const
{

  return (   model_index.isValid() 
           ? ((CellData *)model_index.internalPointer())->Item() 
           : NULL );

}

/******************************************************************************/
/**
\brief  ItemByDBIndex - 



\return pItemData - ItemData
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pCollectionItem - 
\param  indx0 - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByDBIndex"

ItemData *ItemTreeModel :: ItemByDBIndex (ItemData *pCollectionItem, int32 indx0, logical provide )
{
  ItemRegion        *curlist   = NULL;
  ItemData          *pItemData = NULL;
BEGINSEQ
  if ( pCollectionItem )
  {
    if ( pItemData = pCollectionItem->IsItemDBIndex(indx0) )
                                                     LEAVESEQ
    curlist = pCollectionItem->get_region();  
  }
  
  if ( !curlist )
    pItemData = ItemByDBIndex(indx0,provide);
  else
    pItemData = curlist->ItemByDBIndex(indx0,provide);

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODSRegion - 
\param  indx0 - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByDBIndex"

ItemData *ItemTreeModel :: ItemByDBIndex (ODSRegion *pODSRegion, int32 indx0, logical provide )
{
  ItemRegion     *item_region = NULL;
  ItemData       *pItemData   = NULL;

BEGINSEQ
  if ( !(item_region = FindRegion(pODSRegion)) )     ERROR
  
  pItemData = item_region->ItemByDBIndex(indx0,provide);
RECOVER

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  indx0 - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByDBIndex"

ItemData *ItemTreeModel :: ItemByDBIndex (int32 indx0, logical provide )
{

  return ( ItemByDBIndex((ODSRegion *)NULL,indx0,provide) );

}

/******************************************************************************/
/**
\brief  ItemByKey - 



\return pItemData - ItemData

\param  pCollectionItem - 
\param  skey - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByKey"

ItemData *ItemTreeModel :: ItemByKey (ItemData *pCollectionItem, char *skey, logical provide )
{
  ItemRegionList    *curlist   = NULL;
  ItemData          *pItemData = NULL;
BEGINSEQ
  if ( pCollectionItem )
  {
    if ( pItemData = pCollectionItem->IsItemKey(skey) )
                                                     LEAVESEQ
    curlist = pCollectionItem->RegionList();  // oder nur in der ODSREgion des items suchen ??
  }
  
  if ( !curlist )
    curlist = this;
  
  pItemData = curlist->ItemByKey(skey,provide);

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByLOID - 



\return pItemData - ItemData
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pCollectionItem - 
\param  objid - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByLOID"

ItemData *ItemTreeModel :: ItemByLOID (ItemData *pCollectionItem, int32 objid, logical provide )
{
  ItemData          *pItemData = NULL;
BEGINSEQ
  if ( pCollectionItem )
  {
    if ( pItemData = pCollectionItem->IsItemLOID(objid) )
                                                     LEAVESEQ
    pItemData = pCollectionItem->get_region()->ItemByLOID(objid,provide);
  }
  else
    pItemData = ItemRegionList::ItemByLOID(objid,provide);

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODSRegion - 
\param  objid - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByLOID"

ItemData *ItemTreeModel :: ItemByLOID (ODSRegion *pODSRegion, int32 objid, logical provide )
{
  ItemRegion     *item_region = NULL;
  ItemData       *pItemData   = NULL;

BEGINSEQ
  if ( !(item_region = FindRegion(pODSRegion)) )     ERROR
  
  pItemData = item_region->ItemByLOID(objid,provide);
RECOVER

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByRow - 



\return pItemData - ItemData

\param  row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByRow"

ItemData *ItemTreeModel :: ItemByRow (int row )
{
  QModelIndex     parent;
  return(Item(index(row,0,parent)));

}

/******************************************************************************/
/**
\brief  ItemByValue - 



\return pItemData - ItemData

\param  pCollectionItem - 
\param  pQString - 
\param  col - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByValue"

ItemData *ItemTreeModel :: ItemByValue (ItemData *pCollectionItem, QString &pQString, int col )
{
  ItemRegionList    *curlist   = NULL;
  ItemData          *pItemData = NULL;
BEGINSEQ
  if ( pCollectionItem )
  {
    if ( pItemData = pCollectionItem->IsItemValue(pQString,col) )
                                                     LEAVESEQ
    curlist = pCollectionItem->RegionList();  // oder nur in der ODSREgion des items suchen ??
  }
  
  if ( !curlist )
    curlist = this;
  
  pItemData = curlist->ItemByValue(pQString,col);

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemCount - 



\return count - 

\param  mi_parent_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemCount"

int32 ItemTreeModel :: ItemCount (const QModelIndex &mi_parent_w ) const
{
  ItemData       *item_data = Item(mi_parent_w);
  ItemRegionList *item_list = ChildList(item_data);
  ODSRegion      *region    = item_data ? item_data->Region() : (ODSTree *)this;
  OWidget        *codw      = NULL;
  logical         blocked   = NO;
  int32           count     = 0;
BEGINSEQ
  if ( !region )                                     ERROR 
  if ( !IsVisible() )                                LEAVESEQ
//  if ( item_list )                                   ERROR    //j 060103: expand 1st tree item
  
  blocked = region->BlockEvents(YES);
  
  if ( item_list->IsDirty(NO) )
    item_list->UpdateData(NO);
    
  count = item_list->Count();

  if ( blocked )
    if ( !region->BlockEvents(NO) )
    {
      OGUISET(18)
      OGUIRESET
    }


RECOVER

ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  ItemTreeModel - 




\param  pOEHControlData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemTreeModel"

     ItemTreeModel :: ItemTreeModel (OEHControlData *pOEHControlData )
                     : QAbstractItemModel (pOEHControlData->WidgetQ()),
ItemRegionList (NULL),
ODSTree(pOEHControlData),
  transposed(NO),
  check_box(NO),
  initialized(NO),
  proxyModel(NULL)
{



}

/******************************************************************************/
/**
\brief  RegionList - 



\return pItemRegionList - 

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegionList"

ItemRegionList *ItemTreeModel :: RegionList (ItemData *pItemData ) const
{

  return ( pItemData ? pItemData->RegionList()
                     : (ItemRegionList *)this );


}

/******************************************************************************/
/**
\brief  RemoveItem - 



\return next_item - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  pODSRegion - 
\param  objid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItem"

ItemData *ItemTreeModel :: RemoveItem (ODSRegion *pODSRegion, int32 objid )
{

  return (   objid > 0 
           ? RemoveItem(ItemByLOID(pODSRegion,objid,NO))
           : NULL );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItem"

ItemData *ItemTreeModel :: RemoveItem (ItemData *pItemData )
{
  ItemRegionList *region_list      = NULL;
  ODSRegion      *ods_region       = NULL;
  ItemData       *parent           = NULL;
  ItemData       *parent_for_model = NULL;
  int             index0           = -1;
  logical         started          = NO;
  ItemData       *next_item        = NULL;

BEGINSEQ
  if ( !pItemData )                                  ERROR 

  index0           = pItemData->get_row();
  parent           = pItemData->Parent();
  ods_region       = pItemData->Region();
  region_list      = pItemData->RegionList();
  
  started = GetListControl()->BeginOnce();
  if ( parent ) 
    parent->set_is_updating(YES);
  
  if ( transposed )
    beginRemoveColumns(parent->GetModelIndex(),index0,index0);  
  else
    beginRemoveRows(parent->GetModelIndex(),index0,index0);  
  
  region_list->RemoveItem(pItemData);
  
  endRemoveRows();
  
  if ( parent ) 
    parent->set_is_updating(NO);
  GetListControl()->EndOnce(started);

  FlushEvents();
  // magic remember of the selection
  // next -> next
  // !next -> previous : parent

  if ( !(next_item = region_list->Item(index0,parent)) )
    if ( !(next_item = region_list->Item(index0-1>0?index0-1:0,parent)) )
      next_item = parent;

RECOVER

ENDSEQ
  return(next_item);
}

/******************************************************************************/
/**
\brief  RemoveRegion - 




\param  parent_id - 
\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveRegion"

void ItemTreeModel :: RemoveRegion (int32 parent_id, int32 region_id, logical reset_columns )
{

// parent id wird vorerst ignoriert ...
  if ( !region_id )
    ClearData(YES);
  else
  {
    ItemRegionList::RemoveRegion(region_id);
    reset();
  }
  ODSTree::RemoveRegion(parent_id,region_id,reset_columns);

}

/******************************************************************************/
/**
\brief  RemoveRows - 




\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveRows"

void ItemTreeModel :: RemoveRows (ItemData *pItemData )
{
  QModelIndex   model_index = pItemData->GetModelIndex();
BEGINSEQ
  if ( !this || !pItemData )                         LEAVESEQ

  beginRemoveRows(model_index,0,rowCount(model_index));  
  ChildList(Item(model_index))->Clear(NO);
  endRemoveRows();
ENDSEQ

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

logical ItemTreeModel :: SetFilter (char *expression, logical enable_opt )
{
  ItemRegion     *item_region = NULL;
  logical         term        = NO;
BEGINSEQ
  if ( !(item_region = ItemRegionList::GetHead()) )  LEAVESEQ
  
  item_region->Region()->SetFilter(expression,enable_opt);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetLayout - 



\return term - 

\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLayout"

logical ItemTreeModel :: SetLayout (OTreeLayout *pOTreeLayout )
{
  logical                 term = NO;
BEGINSEQ
  if ( layout == (OListLayout *)pOTreeLayout && !pOTreeLayout->get_dirty() )
                                                    LEAVESEQ
  ODSTree::Clear(NO);            // reset layout definitions
  ODSTree::SetLayout(pOTreeLayout);
  InitRegions(this);
  
  pOTreeLayout->reset_dirty();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTransposed - 




\param  toggle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransposed"

void ItemTreeModel :: SetTransposed (bool toggle )
{

  transposed = toggle;

}

/******************************************************************************/
/**
\brief  Tree - 



\return pODSTree - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Tree"

ODSTree *ItemTreeModel :: Tree ( ) const
{

  return ( this ? tree : NULL );

}

/******************************************************************************/
/**
\brief  UpdateData - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

void ItemTreeModel :: UpdateData ( )
{

  if ( HaveColChanged() )
    ClearData(NO);
  else
  {
    if ( !HasItems() )
      FillItems();
    emit layoutChanged();  // oder reset(); ???
  }

  FlushEvents();

}

/******************************************************************************/
/**
\brief  i01 - 



\param  first_item - 
\param  last_item - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

void ItemTreeModel :: UpdateData (ItemData *first_item, ItemData *last_item )
{
  QModelIndex   top_left;
  QModelIndex   bottom_right;
  int           count = 0;
BEGINSEQ
  if ( !first_item )                                 ERROR
    
  top_left = first_item->GetModelIndex();
  
  if ( transposed )
  {
    count = rowCount();
    bottom_right = index(MAX(0,count-1),
                         last_item ? last_item->get_row() : first_item->get_row(),
                         first_item->Parent()->GetModelIndex());    
  }
  else
  {
    count = columnCount();
    bottom_right = index(last_item ? last_item->get_row() : first_item->get_row(),
                         MAX(0,count-1),
                         first_item->Parent()->GetModelIndex());    
  }
    
  emit dataChanged(top_left,bottom_right);
  FlushEvents();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



\param  pCellData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

void ItemTreeModel :: UpdateData (CellData *pCellData )
{
  QModelIndex   cell_index;
BEGINSEQ
  if ( !this || !pCellData )                         ERROR
    
  cell_index = pCellData->GetModelIndex();
  
  emit dataChanged(cell_index,cell_index);
  FlushEvents();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  UpdateTreeLayout - 



\return term - 

\param  tree_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTreeLayout"

logical ItemTreeModel :: UpdateTreeLayout (OTreeLayout *tree_layout )
{
  logical          term = NO;
  ODSTree::UpdateTreeLayout(tree_layout);
  
  ClearData(NO);
  FillItems();

  emit layoutChanged();  // oder reset(); ???

  return(term);
}

/******************************************************************************/
/**
\brief  columnCount - 



\return count - 

\param  mi_parent_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "columnCount"

int ItemTreeModel :: columnCount (const QModelIndex &mi_parent_w ) const
{

  return (   transposed
           ? ItemCount(mi_parent_w)
           : Tree()->ColumnCount()    );

}

/******************************************************************************/
/**
\brief  data - 



\return qvariant - 

\param  model_index - 
\param  dat_role - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "data"

QVariant ItemTreeModel :: data (const QModelIndex &model_index, int dat_role ) const
{
  CellData    *cell_data = Cell(model_index);
  QVariant     variant;
BEGINSEQ
  if ( !cell_data )                                      ERROR
  switch ( dat_role )
  {
    case Qt::EditRole            : 
    case Qt::DisplayRole         : variant = cell_data->GetData();
         break;
    case Qt::DecorationRole      : variant = cell_data->GetIcon();
         break;
    case Qt::ToolTipRole         : 
    case Qt::StatusTipRole       : variant = cell_data->GetToolTip();
         break;
    case Qt::WhatsThisRole       : variant = cell_data->GetHelp();
         break;
    case Qt::FontRole            : variant = cell_data->GetFont();
         break;
    case Qt::TextAlignmentRole   : variant = cell_data->GetTextAlignment();
         break;
    case Qt::BackgroundColorRole : variant = cell_data->GetBackgroundColor();
         break;
    case Qt::TextColorRole       : variant = cell_data->GetTextColor();
         break;
    case Qt::CheckStateRole      : variant = check_box && model_index.column() == 0 
                                             ? Item(model_index)->GetCheckState() 
                                             : cell_data->GetCheckState();
         break;
    default : ;
  }

RECOVER

ENDSEQ
  return(variant);
}

/******************************************************************************/
/**
\brief  dropMimeData - handles the drop of mime data

        currentlty accepts property handles and text/plain

        Handles  the data supplied by a drag  and drop operation that ended with
        the  given  action  over  the  row  in  the  model specified by the row,
        column, and the parent index.

        See also supportedDropActions().

\return term - 

\param  cpQMimeData - 
\param  mime_drop_action - 
\param  row - 
\param  column - 
\param  mi_parent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dropMimeData"

bool ItemTreeModel :: dropMimeData (const QMimeData *cpQMimeData, Qt::DropAction mime_drop_action, int row, int column, const QModelIndex &mi_parent )
{
  ItemData         *item_data = NULL;
  PropertyHandle   *sph       = NULL;
  PropertyHandle   *tph       = NULL;
  DatabaseHandle   *db        = NULL;
  DictionaryHandle *dict      = NULL;
  ODSRegion        *region    = NULL;
  logical           insert    = NO;
  logical           cond      = true;

BEGINSEQ
  if ( !cpQMimeData )                                ERROR
  if ( (drop_action = mime_drop_action) == Qt::IgnoreAction )
                                                     LEAVESEQ
  if ( column > 0 )                                  ERROR
  
  // drop ended before or after some item
  // ItemData* item = ODragAndDrop::get_drop_item(mi_parent,row,column);
  // change insert 8<
  
  if ( !mi_parent.isValid() || row == -1 || column == -1)  // drop on item 
    item_data = Item(mi_parent);  
  else                                                     //it now depends on the row and if the rowcount > row
  {
    if ( !(item_data = Item(index(row,column,mi_parent))) )
      item_data = Item(index(row-1, column, mi_parent));      
    
    if ( item_data )
      drop_index = row - item_data->get_region()->get_first_row();  
    
    if ( rowCount(mi_parent) > row )
      insert = YES;
  }
  
  // \get_drop_item >8
  
  if ( cpQMimeData->hasFormat("application/vnd.odaba.propertyhandle") )
  {
    /// ODragAndDrop::dnd_decode()
    /// decoded_propertyhandle,decoded_text etc
    // 8<
    
    ODragObject::decode(cpQMimeData,&decoded_propertyhandle,&db,&dict);
    if ( item_data )
    {
      item_data->HierSync(YES);
      tph = item_data->Region()->Handle();
    }
    else
    {
      if ( !(region = GetHead()->Region()) )         ERROR
      tph = region->Handle();
    }
    //// \dnd_decode >8
    
    dnd_drop_propertyhandle(tph);
    
    UpdateData(item_data->Parent(),item_data->Parent());
    LEAVESEQ
  }
  
  if ( cpQMimeData->hasFormat("text/xml") )          LEAVESEQ
    
  if ( cpQMimeData->hasFormat("text/plain") )
  {
    /// ODragAndDrop::dnd_decode();
    // 8<
    
    ODragObject::decode(cpQMimeData,decoded_text);
    QStringList newItems = decoded_text.split("\n");
    QStringList::iterator slit;
    if ( !item_data )                                ERROR
    item_data->HierSync(YES);
    
    // >8
    /// ODragAndDrop::dnd_drop_text(decoded_text);
    // 8<
    
    for ( slit = newItems.begin(); slit != newItems.end(); slit++)
      GetListControl()->DA_Add(!insert,QS2SZ(*slit));        // thats something that has to be done different in the model
    
    // >8
    
    LEAVESEQ
  }
  ERROR
  

RECOVER
  cond = false;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  flags - 



\return itemflags - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "flags"

Qt::ItemFlags ItemTreeModel :: flags (const QModelIndex &model_index ) const
{
  ItemData     *item_data = Item(model_index);
  Qt::ItemFlags flags     = QAbstractItemModel::flags(model_index);
  flags |= Qt::ItemIsDropEnabled;            // It can be used as a drop target.
  
  if ( item_data )
  {  
    flags |= Qt::ItemIsSelectable;           // It can be selected.
    flags |= Qt::ItemIsEnabled;              // The user can interact with the item.
  
    if ( !item_data->get_heading() )
    {
      if ( !Cell(model_index)->IsReadOnly() )
      {
        flags |= Qt::ItemIsEditable;         // It can be edited.
        flags |= Qt::ItemIsUserCheckable;    // It can be checked or unchecked by the user.
      }    
      flags |= Qt::ItemIsDragEnabled;        // It can be dragged.
//    flags |= Qt::ItemIsTristate;           // The item is checkable with three separate states.
    }
  }
  return(flags);
}

/******************************************************************************/
/**
\brief  hasChildren - 



\return cond - 

\param  mi_parent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "hasChildren"

bool ItemTreeModel :: hasChildren (const QModelIndex &mi_parent ) const
{
   ItemData       *item_data = NULL;
   ItemRegionList *item_list = NULL;
   ItemRegion     *region    = NULL;

 // optimize the answer to  the question 
 // there are children when at least 1
 // region got static items
 if(   !transposed                        // rowCount
    && (item_data = Item(mi_parent))      // ItemCount
    && (item_list = ChildList(item_data)) // ItemCount
   ){
     item_list->GoTop();
     while ( region = item_list->GetNext() )
       if(region->StaticItemToUse(item_data))
         return true;
 }


  return ( rowCount(mi_parent) > 0 ? true : false );
}

/******************************************************************************/
/**
\brief  headerData - 



\return qvariant - 

\param  section - 
\param  horientation - 
\param  dat_role - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "headerData"

QVariant ItemTreeModel :: headerData (int section, Qt::Orientation horientation, int dat_role ) const
{
  ODSList     *col = NULL;
  QVariant     qvariant;
BEGINSEQ
  if ( (horientation == Qt::Vertical   && !transposed) ||
       (horientation == Qt::Horizontal && transposed)     ) // zweiter header, der in OTableView versteckt wird
  {
    switch ( dat_role )
    {
      case Qt::DisplayRole        : return section;         // satznummer waere ok: ist das aber nicht (immer)
           break;
      default:
          // all the other roles are like the first column
          col = ((ODSTree *)this)->Column(0);               // warum gerade 0 ?
          break;
    }
  }
  else
    col = ((ODSTree *)this)->Column(section);
  
  if ( !col )                                        ERROR

  switch ( dat_role )
  {
    case Qt::DisplayRole         : 
         return( col->GetStaticText() );
         break;
    case Qt::DecorationRole      : return( col->GetIcon() );
         break;
    case Qt::ToolTipRole         : 
    case Qt::StatusTipRole       : return( col->GetToolTip() );
         break;
    case Qt::WhatsThisRole       : return( col->GetHelp() );
         break;
    case Qt::FontRole            : return( col->GetFont() );
         break;
    case Qt::TextAlignmentRole   : ; // return( col->GetTextAlignment() );
         return Qt::AlignLeft;
         break;
    case Qt::BackgroundColorRole : return( col->GetBackgroundColor() );
         break;
    case Qt::TextColorRole       : return( col->GetTextColor() );
         break;
    case Qt::CheckStateRole      : //return( col->GetCheckState() );
         break;
    default : ;
  }

RECOVER

ENDSEQ
  return(qvariant);
}

/******************************************************************************/
/**
\brief  index - 



\return model_index - 

\param  row - 
\param  column - 
\param  mi_parent_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "index"

QModelIndex ItemTreeModel :: index (int row, int column, const QModelIndex &mi_parent_w ) const
{
  ItemData         *item_data = Item(mi_parent_w);
  ItemRegionList   *reg_list  = (ItemRegionList *)this;
  QModelIndex       model_index;
  logical           bStoreTAItem = NO;
BEGINSEQ
  if ( row < 0 || column < 0 )                       ERROR
  if ( !IsVisible() )                                ERROR
  if ( column >= columnCount(mi_parent_w) )          ERROR
  if ( !initialized )
    ((ItemTreeModel *)this)->FillItems();
    
  if ( item_data )
    if ( !(reg_list = item_data->Children()) )       ERROR
  if ( !(item_data = reg_list->Item(transposed ? column : row,
                                    item_data)))     ERROR
  model_index =  createIndex(row,column,
                             item_data->Cell(transposed ? row : column));

RECOVER

ENDSEQ
  return(model_index);

}

/******************************************************************************/
/**
\brief  mimeData - 

        Returns  an  object  that  contains  a  serialized  description  of  the
        specified  indexes. The format used  to describe the items corresponding
        to the indexes is obtained from the mimeTypes() function.

        If  the list of indexes is empty, 0 is returned rather than a serialized
        empty list.

\return pQMimeData - 

\param  model_indicies - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mimeData"

QMimeData *ItemTreeModel :: mimeData (const QModelIndexList &model_indicies ) const
{
  ItemData       *item_data              = NULL;
  CellData       *cell_data              = NULL;
  ODS            *pODS                   = NULL;
  PropertyHandle *pEncodedPropertyHandle = NULL;
  PropertyHandle *ph                     = NULL;
  DatabaseHandle *dbh                    = NULL;
  QMimeData      *data                   = NULL;
  QString         dbpath;
  QString         dictpath;
  QString         s;
  QString         xmlinstance;
  QString         qsText;
  QByteArray      enc_xmlpropertyhandle;
  QByteArray      enc_propertyhandle;
  QByteArray      enc_text;
  int             inst_id                = 0;

  item_data = Item(model_indicies[0]);
  item_data->HierSync(NO);
  
  pODS                   = item_data->Region();
  pEncodedPropertyHandle = pODS->Handle();
  
  // create mimedata for each supported type
  inst_id                = pODS->InstGetObjID();
  if ( ph = pODS->Handle() )
  {
    ph->ExtractKey();
    dbh      = &ph->GetDBHandle();
    dbpath   = SZ2QS(dbh->GetPath());
    dictpath = SZ2QS(dbh->GetDictionary().GetPath());
    pEncodedPropertyHandle = new PropertyHandle();
    pEncodedPropertyHandle->OpenHierarchy(ph); 
    pEncodedPropertyHandle->ExtractKey();
    ph->ExtractKey();
  }
  else
  {
    dbpath = SZ2QS("undefined");
    dbpath = SZ2QS("undefined");
    dbh    = NULL;
  }
  cell_data = Cell(model_indicies[0]);
  qsText = cell_data->GetData().toString();
  xmlinstance   = SZ2QS("<instance id=\"%i\" propertyhandle=\"%p\" applicationhandle=\"%p\" databasehandle=\"%p\" odragobject=\"%p\" databasepath=\"%s\" dictionarypath=\"%s\">\n%s\n</instance>");
  s.sprintf(QS2SZ(xmlinstance),inst_id,pEncodedPropertyHandle,QCoreApplication::instance(),dbh,this,QS2SZ(dbpath),QS2SZ(dictpath),QS2SZ(qsText));
  enc_xmlpropertyhandle.resize(s.length());
  memcpy(enc_xmlpropertyhandle.data(),s.toLatin1(),s.length());

  xmlinstance   = SZ2QS("%i\n%p\n%p\n%p\n%p\n%s\n%s");
  s.sprintf(QS2SZ(xmlinstance),inst_id,pEncodedPropertyHandle,QCoreApplication::instance(),dbh,this,QS2SZ(dbpath),QS2SZ(dictpath));
  enc_propertyhandle.resize(s.length());
  memcpy(enc_propertyhandle.data(),s.toLatin1(),s.length());
  
  enc_text.resize( qsText.length() );
  memcpy( enc_text.data(), qsText.toLatin1(), qsText.length() );

  
  data = new QMimeData();
  data->setData("text/xml",enc_xmlpropertyhandle);
  data->setData("application/vnd.odaba.propertyhandle",enc_propertyhandle);
  data->setData("text/plain",enc_text);
  return(data);
}

/******************************************************************************/
/**
\brief  mimeTypes - 

        Returns  a list  of MIME  types that  can be  used to describe a list of
        model indexes.

        See also mimeData().

\return types - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mimeTypes"

QStringList ItemTreeModel :: mimeTypes ( ) const
{
  QStringList types;
  types = QAbstractItemModel::mimeTypes();
  types << "application/vnd.odaba.propertyhandle";
  types << "text/plain";
  types << "text/xml";

  return types;
}

/******************************************************************************/
/**
\brief  parent - 



\return model_index - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "parent"

QModelIndex ItemTreeModel :: parent (const QModelIndex &model_index ) const
{
  ItemData      *item_data = Item(model_index);
  if ( item_data )
    item_data = item_data->Parent();
    
  return ( item_data->GetModelIndex() );
  
//  return (   item_data  
//           ? createIndex(item_data->get_row(),0,item_data)
//           : QModelIndex()  );  



}

/******************************************************************************/
/**
\brief  removeRows - 



\return cond - 

\param  row - 
\param  count - 
\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "removeRows"

bool ItemTreeModel :: removeRows (int row, int count, const QModelIndex &model_index )
{
  bool          cond = true;
// sollte optimiert werden

  RemoveRows(Item(model_index));
  return(cond);
}

/******************************************************************************/
/**
\brief  rowCount - 



\return count - 

\param  mi_parent_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rowCount"

int ItemTreeModel :: rowCount (const QModelIndex &mi_parent_w ) const
{

  return (   transposed 
           ? Tree()->ColumnCount() 
           : ItemCount(mi_parent_w) );

}

/******************************************************************************/
/**
\brief  setData - 



\return cond - 

\param  model_index - 
\param  qvariant - 
\param  edit_role - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setData"

bool ItemTreeModel :: setData (const QModelIndex &model_index, const QVariant &qvariant, int edit_role )
{
  CellData    *cell_data = Cell(model_index);
  bool         cond      = true;
BEGINSEQ
  if ( !cell_data )                                  ERROR
  
  if ( edit_role != Qt::EditRole )                   LEAVESEQ
  if ( (flags(model_index) & Qt::ItemIsEditable) == 0 ) 
                                                     ERROR
  cell_data->SetData(qvariant);


RECOVER
  cond = false;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  set_check_box - 




\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_check_box"

void ItemTreeModel :: set_check_box (logical check_items )
{

  check_box = check_items;

}

/******************************************************************************/
/**
\brief  supportedDropActions - Returns the drop actions supported by this model.

        The  default implementation returns Qt::CopyAction. It is only necessary
        to  reimplement this function in subclasses  if you wish to support more
        types of drag and drop operation.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "supportedDropActions"

Qt::DropActions ItemTreeModel :: supportedDropActions ( ) const
{
  Qt::DropActions actions;
  actions |= Qt::CopyAction;
  actions |= Qt::MoveAction;
  actions |= Qt::LinkAction;

//  actions |= Qt::IgnoreAction;
  return(actions);
}

/******************************************************************************/
/**
\brief  ~ItemTreeModel - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ItemTreeModel"

     ItemTreeModel :: ~ItemTreeModel ( )
{

if ( proxyModel )
  delete proxyModel;
proxyModel = NULL;

}


