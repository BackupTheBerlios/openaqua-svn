/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ItemRegion

\brief    Item Region
          An  item region is a  item list, which handles  the items for a region
          (ODSRegion), which represents a collection in the database.

\date     $Date: 2006/08/23 15:29:36,85 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ItemRegion"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sItemRegionList.hpp>
#include  <sItemTreeModel.hpp>
#include  <sODSItem.hpp>
#include  <sODSRegion.hpp>
#include  <sOListCtl.hpp>
#include  <sOListLayout.hpp>
#include  <sPropertyHandle.hpp>
#include  <sItemRegion.hpp>


/******************************************************************************/
/**
\brief  Clear - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ItemRegion :: Clear ( )
{

  ItemList::Clear();
  
  first_row = 0;
  count     = AUTO;
  ResetState();

}

/******************************************************************************/
/**
\brief  Count - Get item region count

        The  function  returns  the  number  of  items  to  be displayed for the
        region.

\return count - 

\param  parent_item_data - 
\param  update_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

int ItemRegion :: Count (ItemData *parent_item_data, logical update_opt )
{
  int       rcount = 1;
BEGINSEQ
  if ( StaticItemToUse(parent_item_data) )           LEAVESEQ
  
  if ( count < 0 || update_opt )              // muss mal aktualisiert werden!
  {
    Parent(parent_item_data)->HierSync(YES);

    if ( !region->DefinesCollection() )
      count = region->Handle()->GetCount() > 0 ? 1 : 0;   
    else
    {
      if ( region->SyncColState() )
        FillData();
      
      if ( region->HasSelection() )
        count = GetSize();    
      else
      { 
        if ( region->IsBaseCollection() )
          region->Handle()->PositionTop();
        if ( (count = region->Handle()->GetCount()) > 0 )
          count += HasHeader();
      }
    }
  }

  rcount = count;
ENDSEQ
  return(MAX(0,rcount));
}

/******************************************************************************/
/**
\brief  CreateItem - 



\return pItemData - ItemData

\param  index0 - 
\param  insert_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateItem"

ItemData *ItemRegion :: CreateItem (int index0, logical insert_opt )
{
  ItemData       *pItemData = NULL;
BEGINSEQ
  if ( !(pItemData = ItemList::CreateItem(this,index0,
                                          first_row,insert_opt)) )
                                                     ERROR
  Model()->SetCurItem(pItemData);
  
  if ( Model()->BeforeDataSet() )
    if ( region->HasSelection() )                   ERROR
  
  pItemData->Setup();
  
  Model()->AfterDataSet();
RECOVER
  if ( pItemData )
    ItemList::RemoveItem(index0,insert_opt);
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  FillData - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

logical ItemRegion :: FillData ( )
{
  int                index0 = 0;
BEGINSEQ
  if ( !region->HasSelection() )                    LEAVESEQ
  
  Parent(NULL)->HierSync(YES);                       // damit Item es nicht mit NO ruft
  while ( Item(index0++,NULL) ) ;

  if ( GetSize() == 1 && HasHeader() )
    ItemList::RemoveItem(0,YES);
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  FillItems - 



\return pItemData - ItemData

\param  index0 - 
\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillItems"

ItemData *ItemRegion :: FillItems (int index0, ItemData *parent_item_data )
{
  logical       started   = NO;
  logical       blocked   = NO;
  int           row       = 0;
  ItemData     *cur_item  = NULL;
  ItemData     *pItemData = NULL;
BEGINSEQ
  cur_item = Model()->GetListControl()->get_cur_item();
  
  started = region->Handle()->StartRTA() ? YES : NO;
  if ( Parent(NULL)->HierSync() )                    ERROR
    
  if ( !parent_item_data || parent_item_data->IsExpanding() )  // 
    if ( blocked = !region->signalsBlocked() )
      region->BlockSignals(YES);
  
  if ( !index0  && HasHeader() )
  {
    if ( region->HasSelection() || region->Handle()->GetCount() > 0 )
      SetItem(header_item,0,YES);
  }
    
  NewItem(0,NULL,AUTO,AUTO);            // liest alle
  SyncColState();
  
  if ( cur_item )
    cur_item->HierSync();
  Model()->GetListControl()->set_cur_item(cur_item);
RECOVER
  pItemData  = NULL;
ENDSEQ
  region->Handle()->StopRTA(started);
  if ( blocked )
    region->BlockSignals(NO);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  GetRowForDBIndex - 



\return row - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRowForDBIndex"

int ItemRegion :: GetRowForDBIndex (int32 indx0 )
{


  return ( GetIndexForDBIndex(indx0) + first_row );

}

/******************************************************************************/
/**
\brief  HasColChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasColChanged"

logical ItemRegion :: HasColChanged ( )
{
  logical       cond = NO;
  if ( !region->DefinesCollection() )
    cond = HasInstChanged();

  if ( !cond )
  {
    region->ColIsValid(NO,NO);
    cond = HasChanged(region->Item(),region->Handle());
  }
  return(cond);
}

/******************************************************************************/
/**
\brief  HasHeader - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasHeader"

logical ItemRegion :: HasHeader ( )
{

  return ( header_item ? YES : NO );

}

/******************************************************************************/
/**
\brief  HasInstChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasInstChanged"

logical ItemRegion :: HasInstChanged ( )
{
  ItemData        *item_data  = Parent(static_item);
  ODSItemColState *inst_state = NULL;
  logical           cond      = NO;
  if ( item_data )
    inst_state = item_data;
  else
    inst_state = Model();   
     
  if ( inst_state )
    cond = inst_state->HasChanged(region->Item(),region->Handle());

  return(cond);
}

/******************************************************************************/
/**
\brief  InsertItem - 



\return new_item - 

\param  row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertItem"

ItemData *ItemRegion :: InsertItem (int row )
{
  PropertyHandle  *ph       = NULL;
  int              index0   = 0;
  ItemData        *new_item = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  index0   = row - first_row;
  
  if ( !(new_item = CreateItem(index0,YES)) )        ERROR
  SyncColState();
    
  ItemList::SetupItemRows(index0+1,first_row);
  SetupDBIndex(index0+1,1);
  
  if ( count >= 0 )
    count++;

RECOVER

ENDSEQ
  return(new_item);
}

/******************************************************************************/
/**
\brief  Item - 



\return pItemData - ItemData

\param  index0 - 
\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Item"

ItemData *ItemRegion :: Item (int index0, ItemData *parent_item_data )
{
  logical       started   = NO;
  logical       blocked   = NO;
  int           row       = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( StaticItemToUse(parent_item_data) )
  {
    if ( index0 )                                    OGUIERR(99)
    pItemData = static_item;                         LEAVESEQ
  }
  
  if ( pItemData = GetAt(index0) )                   LEAVESEQ
  
  FillItems(index0,parent_item_data);  // neu Füllen der Liste, früher xx_Item()
  pItemData = GetAt(index0);
RECOVER
  pItemData  = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByDBIndex - 



\return pItemData - ItemData

\param  indx0 - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByDBIndex"

ItemData *ItemRegion :: ItemByDBIndex (int32 indx0, logical provide )
{
  ItemData        *pItemData = NULL;
  int              index0    = 0;
BEGINSEQ
  if ( pItemData =   !region->HasSelection()
                   ? ItemList::GetAt(indx0 + HasHeader() )
                   : ItemList::ItemByDBIndex(indx0)) LEAVESEQ
  
  if ( !provide )                                    ERROR
  if ( Parent(NULL)->HierSync(NO) )                  ERROR
  
  if ( region->HasSelection() )
    pItemData = NewItem(0,NULL,indx0,AUTO);
  else
  {
    if ( region->ColScroll(indx0+HasHeader(),NO) )   ERROR // ph->Get(indx0)
    pItemData = CreateItem(indx0+HasHeader(),NO);
  }     
    

RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
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

ItemData *ItemRegion :: ItemByKey (char *skey, logical provide )
{
  ItemData        *pItemData = NULL;

BEGINSEQ
  if ( pItemData = ItemList::ItemByKey(skey) )       LEAVESEQ
  if ( !provide )                                    ERROR
  if ( Parent(NULL)->HierSync(NO) )                  ERROR
  
  if ( region->HasSelection() )
    pItemData = NewItem(0,skey,AUTO,AUTO);
  else
  {
    if ( !region->ColFind(skey,YES) )                ERROR
    pItemData = CreateItem(region->ColGetIndex()+HasHeader(),NO);   // ph->GetCurrentIndex()
  }     
  

RECOVER
  pItemData = NULL;
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

ItemData *ItemRegion :: ItemByLOID (int32 objid, logical provide )
{
  ItemData        *pItemData = NULL;
BEGINSEQ
  if ( pItemData = ItemList::ItemByLOID(objid) )     LEAVESEQ
  if ( !provide )                                    ERROR
  if ( Parent(NULL)->HierSync(NO) )                  ERROR
  
  pItemData = NewItem(objid,NULL,AUTO,AUTO);
RECOVER
  pItemData = NULL;
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

ItemData *ItemRegion :: ItemByValue (QString &pQString, int col )
{
  ItemData        *pItemData = NULL;
  pItemData = ItemList::ItemByValue(pQString,col);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemRegion - Cnstructor




\param  pItemRegionList - 
\param  pODSRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemRegion"

     ItemRegion :: ItemRegion (ItemRegionList *pItemRegionList, ODSRegion *pODSRegion )
                     : ODSItemColState(),
ItemList (),
  region(pODSRegion),
  region_list(pItemRegionList),
  static_item(NULL),
  header_item(NULL),
  first_row(0),
  count(ERIC)

{

  SyncState(pODSRegion);

  if ( pODSRegion->get_layout()->GetStaticText() )
  {
    static_item = new ItemData(this,AUTO);
    static_item->SetStatic(pItemRegionList);
  }
/*
  if ( pODSRegion != (ODSRegion *)Model() &&
       pODSRegion->get_layout()->DisplayHeader() )
  {
    header_item = new ItemData(this,0);
    header_item->SetHeading();
  }
*/

}

/******************************************************************************/
/**
\brief  Model - 



\return pItemTreeModel - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Model"

ItemTreeModel *ItemRegion :: Model ( )
{

  return( this ? region_list->Model() : NULL );

}

/******************************************************************************/
/**
\brief  NewItem - 



\return pItemData - ItemData

\param  objid - 
\param  skey - 
\param  indx0 - 
\param  index0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewItem"

ItemData *ItemRegion :: NewItem (int32 objid, char *skey, int32 indx0, int index0 )
{
  ItemData        *pItemData = NULL;
  int              row       = GetSize();
BEGINSEQ
  if ( region->DefinesCollection() )
  {  
    if ( pItemData = GetLast() )
      region->ColScroll(pItemData->get_lastIndex(),NO);      // ph->Get(pItemData->get_lastIndex());
    else
      region->ColReset();                                    // ph->ToTop();
  }
  else 
  {
    if ( row >= (HasHeader()+1) )                    ERROR
    if ( !region->Handle()->IsPositioned() )
      region->ProvideItem();
    if ( !(region->Handle()->IsPositioned()) )       ERROR
  }

  if ( !row && HasHeader() )
  {
    if ( !region->HasSelection() && region->Handle()->GetCount() <= 0 )
                                                     ERROR
    SetItem(header_item,0,YES);
    row++;
  }
  
  while ( region->ColNext() )                              // !ph->Position(1)
  {
    if ( pItemData = CreateItem(row,NO) )
    {
      if ( objid && pItemData->IsItemLOID(objid) )   LEAVESEQ
      if ( skey  && pItemData->IsItemKey(skey) )     LEAVESEQ
      if ( indx0 > AUTO  && pItemData->IsItemDBIndex(indx0) )
                                                     LEAVESEQ
      if ( index0 > AUTO && pItemData->IsItemRow(index0) )
                                                     LEAVESEQ
      row++;
    }
    if ( !region->DefinesCollection() )
      break;
  }  
  ERROR

RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  Parent - Get region parent item



\return pItemData - ItemData

\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

ItemData *ItemRegion :: Parent (ItemData *parent_item_data )
{

  return (   !this                             ? NULL
           : StaticItemToUse(parent_item_data) ? static_item
           :                                     region_list->Parent() );

}

/******************************************************************************/
/**
\brief  Region - 



\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Region"

ODSRegion *ItemRegion :: Region ( )
{

  return( this ? region : NULL );

}

/******************************************************************************/
/**
\brief  RemoveItem - 



\return term - 

\param  row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItem"

logical ItemRegion :: RemoveItem (int row )
{
  ItemData  *pItemData = NULL;
  int        index0    = row;
  logical    term      = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  
  index0 -= first_row;
  
  if ( !(pItemData = ItemList::RemoveItem(index0,YES)) )
                                                     ERROR
  SyncColState();
    
  Model()->ResetCurItem(pItemData,NO);
  
  ItemList::SetupItemRows(index0,first_row);
  SetupDBIndex(index0,-1);

  if ( count >= 0 )
    count--;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetFirstRow - 




\param  row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFirstRow"

void ItemRegion :: SetFirstRow (int row )
{

  if ( !static_item )
    first_row = row;

// ev. update der row fuer schon vorhandene items

}

/******************************************************************************/
/**
\brief  SetupItemRows - 




\param  start_row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupItemRows"

void ItemRegion :: SetupItemRows (int start_row )
{

  if ( static_item )
    static_item->set_row(start_row);
  else
  {
    SetFirstRow(start_row);
    ItemList::SetupItemRows(0,first_row);
  }

}

/******************************************************************************/
/**
\brief  SetupStaticRow - 




\param  row - 
\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupStaticRow"

void ItemRegion :: SetupStaticRow (int row, ItemData *parent_item_data )
{

  if ( StaticItemToUse(parent_item_data) )
    static_item->set_row(row);

}

/******************************************************************************/
/**
\brief  StaticItemToUse - 



\return cond - 

\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StaticItemToUse"

logical ItemRegion :: StaticItemToUse (ItemData *parent_item_data )
{

  return (   static_item && static_item != parent_item_data
           ? YES : NO );


}

/******************************************************************************/
/**
\brief  SyncColState - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncColState"

logical ItemRegion :: SyncColState ( )
{
  logical         modified = HasColChanged();
  if ( !region->DefinesCollection() )
    SyncInstState();

  SyncState(region->Item());
  SetupModCount(region->Handle());

  return(modified);
}

/******************************************************************************/
/**
\brief  SyncInstState - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncInstState"

logical ItemRegion :: SyncInstState ( )
{
  ItemData        *item_data  = Parent(static_item);
  ODSItemColState *inst_state = NULL;
  logical          modified   = HasInstChanged();
  if ( item_data )
    inst_state = item_data;
  else
    inst_state = Model();   
  
  if ( inst_state )
  {
    inst_state->SyncState(region->Item());
    inst_state->SetupModCount(region->Handle());
  }

  return(modified);
}

/******************************************************************************/
/**
\brief  UpdateData - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

logical ItemRegion :: UpdateData ( )
{
  ItemData    *first_item = GetAt(0);
  ItemData    *last_item  = GetLast();
BEGINSEQ
  if ( !this || !first_item )                          LEAVESEQ
    
  Model()->UpdateData(first_item,last_item);
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  xx_Item - 



\return pItemData - ItemData

\param  index0 - 
\param  parent_item_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xx_Item"

ItemData *ItemRegion :: xx_Item (int index0, ItemData *parent_item_data )
{
  logical       started   = NO;
  logical       blocked   = NO;
  int           row       = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( StaticItemToUse(parent_item_data) )
  {
    if ( index0 )                                    OGUIERR(99)
    pItemData = static_item;                         LEAVESEQ
  }
  
  if ( pItemData = GetAt(index0) )                   LEAVESEQ
  if ( Parent(NULL)->HierSync() )                    ERROR
    
  if ( !index0  && HasHeader() )
  {
    if ( region->HasSelection() || region->Handle()->GetCount() > 0 )
    {
      SetItem(header_item,0,YES);
      LEAVESEQ
    }
    ERROR
  }
    
  if ( parent_item_data->IsExpanding() )
    if ( blocked = !region->signalsBlocked() )
      region->BlockSignals(YES);
  
  started = region->Handle()->StartRTA() ? YES : NO;
  
  if ( region->HasSelection() )
    pItemData = NewItem(0,NULL,AUTO,index0);  
  else
  {
    if ( region->ColScroll(index0-HasHeader(),NO) )  ERROR // ph->Get(index0)
    pItemData = CreateItem(index0,NO);
  }
RECOVER
  pItemData  = NULL;
ENDSEQ
  region->Handle()->StopRTA(started);
  if ( blocked )
    region->BlockSignals(NO);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ~ItemRegion - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ItemRegion"

     ItemRegion :: ~ItemRegion ( )
{

  delete static_item;
  static_item = NULL;

  delete header_item;
  header_item = NULL;

}


