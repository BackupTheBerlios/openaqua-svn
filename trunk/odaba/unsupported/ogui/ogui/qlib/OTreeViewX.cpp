/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OTreeViewX

\brief    Tree view
          The  tree  view  allows  displaying  a  number  of  collections.  Each
          collection  is  displayed  in  a  tree  view  region. A region behaves
          mainly  like a List  view (see OListView),  i.e. you may select one or
          more  attributes from the collection  instances for being displayed as
          columns in the list. 
          Each  region may have a different list of columns, but the same number
          of  columns for each  reagion are required.  Moreover, each region may
          have a separate headline displayed on top of the reagion. 
          A  region (e.g. Person  collection) may have  several sub regions. Sub
          regions  are displayed  for each  instance in  the collection with (or
          without)  head  line.  Sub  regions  refer  to  collections, which are
          properties  of the  upper instances  (e.g. children  or accounts for a
          person).  You  may  also  define  recursive sub regions for displaying
          children of children of children ... .
          Only  the first column  in a tree  view displays the hierarchy defined
          by  regions.  The  other  columns  (when  being  defined)  display the
          attributed  according to the column definition for the region. When no
          column  list is defined for a  region, the region inherits the columns
          from  the upper  region. When  no columns  are defined at all, the key
          value  according  to  the  sort  order  defined  for  the  region  is 
          displayed.  Actions  as  change  order,  or  position oprations (next,
          previous,  move up etc) are applied on the current ly selected region,
          always.  The tree view supports insert and delete actions according to
          the position in the tree.

\date     $Date: 2006/03/13 21:36:21,40 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTreeViewX"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOTreeViewX.h>
#include  <cItemCandidateTypes.h>
#include  <sOCheckTreeItem.hpp>
#include  <sODS.hpp>
#include  <sODSRegion.hpp>
#include  <sODSTree.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlList.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOTreeView.hpp>
#include  <sOTreeViewItem.hpp>
#include  <sPropertyHandle.hpp>
#include  <ssts.hpp>
#include  <sOTreeViewX.hpp>


/******************************************************************************/
/**
\brief  FillList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillList"

void OTreeViewX :: FillList ( )
{

BEGINSEQ
///q3:  if ( stsclck() )                                 LEAVESEQ
  updatePositions();
  OEHControlList::FillList();

ENDSEQ


}

/******************************************************************************/
/**
\brief  FirstChild - 


\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstChild"

ItemData *OTreeViewX :: FirstChild ( )
{
  ItemData          *pItemData = NULL;
  pItemData = ItemData::GetItemData(topLevelItem(0));
  return(pItemData);
}

/******************************************************************************/
/**
\brief  GetSelectedPropertyHandle - 


\return prop_handle - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedPropertyHandle"

PropertyHandle *OTreeViewX :: GetSelectedPropertyHandle ( )
{
  ItemData                *cur_item_data;
  PropertyHandle          *prop_handle = NULL;
BEGINSEQ
  BlockSignals(YES);
  
  if(!cur_item)                                      ERROR
  cur_item_data = cur_item;
  cur_item_data->HierSync(NO);
  prop_handle = cur_item_data->ods_region->Handle();
RECOVER
  prop_handle = NULL;
ENDSEQ
  BlockSignals(NO);
  return(prop_handle);
}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OTreeViewX :: Initialize ( )
{

  
  connect( this, SIGNAL(itemExpanded(QTreeWidgetItem *)),
           this, SLOT(slotItemExpanded(QTreeWidgetItem *)));
           
  connect( this, SIGNAL(itemCollapsed(QTreeWidgetItem *)),
           this, SLOT(slotItemCollapsed(QTreeWidgetItem *)));

  setRootIsDecorated (true);


}

/******************************************************************************/
/**
\brief  OTreeView - 


-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
\param  chk_items_w -
\param  multi_sel_w -
\param  sort_opt_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeView"

void OTreeViewX :: OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical chk_items_w, logical multi_sel_w, logical sort_opt_w )
                     : QTreeWidget(
  pODataWidget?pODataWidget->WidgetQ():NULL)
/*OListView(pODataWidget,oODataWidget,create_ods,
          chk_items_w,multi_sel_w,sort_opt_w)
*/
,OListCtl(pODataWidget,oODataWidget,create_ods)
,ignore(NO)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS -
\param  chk_items_w -
\param  multi_sel_w -
\param  sort_opt_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeView"

void OTreeViewX :: OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical chk_items_w, logical multi_sel_w, logical sort_opt_w )
                     : QTreeWidget(
  pODataWidget?pODataWidget->WidgetQ():NULL)

/*
OListView(pODataWidget,oODataWidget,pODS,
          chk_items_w,multi_sel_w,sort_opt_w)
*/
,OListCtl(pODataWidget,oODataWidget,pODS)
,ignore(NO)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  SetCurrentItem - 


-------------------------------------------------------------------------------
\brief  i0


\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentItem"

void OTreeViewX :: SetCurrentItem (int index )
{
  ItemData           *current = NULL;
  ItemData           *first   = NULL;
BEGINSEQ
  if ( index == AUTO && cur_item_candidate )
  {
    setCurrentItem(cur_item_candidate->GetQTreeWidgetItem());
    cur_item_candidate=NULL;    
    LEAVESEQ
  }
  if ( !(current = ItemData::GetItemData(currentItem())) )
    ERROR
  first = current;
  if ( current->Parent() )
    current = current->Parent()->FirstChild();
  else
    current = FirstChild();
  while (index-- && (current = current->NextSibling()) && current && first)
    if ( current->ods_region != first->ods_region)
      break;
  if(current)
    setCurrentItem(current->GetQTreeWidgetItem());

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentItem"

void OTreeViewX :: SetCurrentItem (ItemData *pItemData )
{

BEGINSEQ
  if (!pItemData)                                    ERROR
  setCurrentItem(pItemData->GetQTreeWidgetItem());

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ShowRegionData - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  pOTreeViewItem -
\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowRegionData"

logical OTreeViewX :: ShowRegionData (OTreeViewItem *pOTreeViewItem, OTreeLayout *pOTreeLayout )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  pOTreeView -
\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowRegionData"

logical OTreeViewX :: ShowRegionData (OTreeView *pOTreeView, OTreeLayout *pOTreeLayout )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  UpdateList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateList"

void OTreeViewX :: UpdateList ( )
{

BEGINSEQ
  if ( stsclck() )                                 LEAVESEQ
  
  /* update region if rootlevel is unchanged */
  if ( topLevelItem(0) && !isRefreshing )
    updateRegion();
  else
    FillList();

ENDSEQ


}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return pQWidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OTreeViewX :: WidgetQ ( )
{

  return this;

}

/******************************************************************************/
/**
\brief  cleanRegion - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cleanRegion"

logical OTreeViewX :: cleanRegion ( )
{
  logical      term = NO;
  cleanRegion(&listCache);
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  pODSRegion -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cleanRegion"

logical OTreeViewX :: cleanRegion (ODSRegion *pODSRegion )
{
  int32        ireg   = -1;
  logical      term   = YES;

BEGINSEQ
  if ( !pODSRegion )                                 ERROR
    
  while ( pODSRegion->Region(++ireg) )
    cleanRegion(pODSRegion->Region(ireg));
  
  pODSRegion->set_dirty(NO);

RECOVER
  term = NO;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  createItem - 


\return pItemData - ItemData
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createItem"

ItemData *OTreeViewX :: createItem ( )
{

  if ( checkMode ) 
    return new OCheckTreeItem(this,FirstChild());
  else
    return new OTreeViewItem(this,FirstChild());
  return NULL;
}

/******************************************************************************/
/**
\brief  i01


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createItem"

ItemData *OTreeViewX :: createItem (ItemData *pItemData )
{

  if ( checkMode ) 
    return new OCheckTreeItem(pItemData,pItemData->FirstChild());
  else
    return new OTreeViewItem(pItemData,pItemData->FirstChild());

}

/******************************************************************************/
/**
\brief  createRegion - 


\return term -

\param  pItemData - ItemData
\param  pODSRegion -
\param  last_lvi -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createRegion"

ItemData *OTreeViewX :: createRegion (ItemData *pItemData, ODSRegion *pODSRegion, ItemData *last_lvi )
{

BEGINSEQ
  pODSRegion->SetActive(YES);
  SetWidgetBusy(YES);
  if ( pODSRegion->get_layout()->GetStaticText() && !pItemData->get_heading() )
  {
    createStaticItem(pItemData,pODSRegion);
    LEAVESEQ
  }
  
  if ( pODSRegion->ColGetCount() )
  {
    if ( !last_lvi )
      last_lvi = createSubItem(pItemData);
    BlockSignals(NO);
    last_lvi = pODSRegion->SetRegionItemData(last_lvi,NULL,NO);
    BlockSignals(YES);
  }
ENDSEQ
  SetWidgetBusy(NO);
  return last_lvi;
}

/******************************************************************************/
/**
\brief  createStaticItem - 


\return term -

\param  pItemData - ItemData
\param  pODSRegion -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createStaticItem"

logical OTreeViewX :: createStaticItem (ItemData *pItemData, ODSRegion *pODSRegion )
{
  ItemData          *static_item;
  QTreeWidgetItem   *static_qitem;
  char              *text = NULL;
  logical            term = NO;
BEGINSEQ
  if ( pODSRegion )
  {
    text = pODSRegion->GetLayout()->GetStaticText();
    pODSRegion->set_dirty(NO);
  }    
  
  if ( !(static_item = createSubItem(pItemData)) )   ERROR
    
  static_qitem = static_item->GetQTreeWidgetItem();
  
  static_item->setHeading(true);
  static_item->ods_region = pODSRegion;
  static_qitem->setText(0,SZ2QS(text && *text ? text : "no heading"));
  static_qitem->setFlags(static_qitem->flags() ^ Qt::ItemIsEditable);
//q3 no expandable 
// if ( !pODSRegion || !pODSRegion->ColGetCount() )
//    static_qitem->setExpandable(false);
  BlockSignals(NO);
  if(static_item && static_item->ods_region)
    static_item->ods_region->restore_expanded(static_item);
  BlockSignals(YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  createSubItem - 


\return pItemData - ItemData

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createSubItem"

ItemData *OTreeViewX :: createSubItem (ItemData *pItemData )
{
  ItemData                  *pLastChild = NULL;
  /* make sure static texts are inserted in order */
  if(pItemData)
    pLastChild = pItemData->FirstChild();
  if(pLastChild)
    while(pLastChild->NextSibling())
      pLastChild = pLastChild->NextSibling();
  if ( checkMode ) 
    return new OCheckTreeItem(pItemData, pLastChild);
  else
    return new OTreeViewItem(pItemData, pLastChild);

}

/******************************************************************************/
/**
\brief  doExpanded - 


\return term -

\param  pQTreeWidgetItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doExpanded"

logical OTreeViewX :: doExpanded (QTreeWidgetItem *pQTreeWidgetItem )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  item - 


\return pQTreeWidgetItem -

\param  iIndex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "item"

QTreeWidgetItem *OTreeViewX :: item (int iIndex )
{
  ODSRegion          *ireg         = NULL;
  ItemData           *item_data
                    ,*current
                    ,*currentparent;
  int32               icount       = 0;

BEGINSEQ
  if ( !(current = ItemData::GetItemData(currentItem())) )
    ERROR
  currentparent = current->Parent();
    
  current->HierSync(YES);
  ireg   = current->ods_region;
  if (currentparent){
    icount   = currentparent->Count();
    current  = currentparent->FirstChild();
  }else{
    icount   = topLevelItemCount();
    current  = FirstChild();
  }
  
  /* add static regions to index */
  
  if ( iIndex < 0 )                                  ERROR
  if ( iIndex >= icount )                            ERROR
  
  while ( iIndex > 0 && current)
  {
    if ( current->ods_region == ireg )
      iIndex--;
    current = current->NextSibling();
  }
RECOVER
  current = NULL;
ENDSEQ
  return current?current->GetQTreeWidgetItem():NULL;
}

/******************************************************************************/
/**
\brief  removeItems - removes remaining items
        removes items with region of pItemData. 
        reeLayout)  for the  region with  the index  number passed (firts region
        has number 0).

\return term -

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "removeItems"

ItemData *OTreeViewX :: removeItems (ItemData *pItemData )
{
  ItemData         *current =  NULL;
  ItemData         *next = NULL;
  ODSRegion        *ireg       = NULL;
  logical           rcheck     = YES;
BEGINSEQ
  if ( !pItemData  )  
  {
    if ( current = FirstChild() )  
      pItemData = current;
    rcheck = NO;
  }
  if ( !pItemData  )                                 LEAVESEQ
  
  next = pItemData; 
  if(pItemData->get_heading())                       LEAVESEQ
  ireg = pItemData->ods_region;
    
  while ( next && (!rcheck || ireg == next->ods_region) )
  {
    current = next;
    next = next->NextSibling();
    
    
    if ( isItemSelected(currentItem()) )
//      setCurrentItemCandidate(ICT_Deleted,current->PreviousItem());
      SetCurrentItem(current->PreviousItem());
    if( current == cur_item_candidate )
      cur_item_candidate = NULL; 
    delete current;
    current = NULL;
  }
ENDSEQ
 return next;
}

/******************************************************************************/
/**
\brief  selectionRestore - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "selectionRestore"

logical OTreeViewX :: selectionRestore ( )
{
  logical                 term              = NO;
  QString                 current_key_value;
  QString                 current_value;
  ItemData               *item              = NULL;
  ItemData               *restore_item      = NULL;
  /* restore selection * * * /
  item = FirstChild();
  while(!storedSelection.empty()){
    current_key_value = storedSelection.last();
    while(item){
      if(item->get_heading())
        current_value = SZ2QS(item->ods_region->Layout()->GetStaticText());
      else
        current_value = SZ2QS(item->get_key_val());
      if(   !current_value.isEmpty() && !current_key_value.isEmpty()
         && current_value == current_key_value )
        break;
      item = item->NextSibling();
    }
    if(    item 
        && (   item->FirstChild() 
            || (   !current_value.isEmpty()
                && !current_key_value.isEmpty()
                && current_value == current_key_value
               )
           ) 
      ){
      restore_item = item;
      item = item->FirstChild();
    }
    storedSelection.pop_back();
  }
  if(restore_item){
    if(   cur_item_candidate
       && (   cur_item_candidate->Ancestor(restore_item)
           || cur_item_candidate->ods_region == restore_item->ods_region
          )
       && !isRefreshing
      )
      SetCurrentItem(cur_item_candidate);
    else
      SetCurrentItem(restore_item);
  }else{
    if(cur_item_candidate)
      SetCurrentItem(cur_item_candidate);
    else
      SetCurrentItem(FirstChild());
  }
  setItemSelected(currentItem(),true); // always highlight the current after restoring
  resetCurrentItemCandidate();
 * * */
  return(term);
}

/******************************************************************************/
/**
\brief  selectionStore - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "selectionStore"

logical OTreeViewX :: selectionStore ( )
{
  logical                 term  = NO;
  ItemData               *item  = NULL;
  QString                 value;
  /* store selected item (by key) * * * /
  item = ItemData::GetItemData(currentItem());
  storedSelection.clear();
  while ( item )
  {
    if ( item->get_heading() )
      value = SZ2QS(item->ods_region->Layout()->GetStaticText());
    else
      value = SZ2QS(item->get_key_val());
    QS2SZ(value);
    storedSelection.append(value);
    
    item = item->Parent();
  }
  * * */
  return(term);
}

/******************************************************************************/
/**
\brief  slotItemCollapsed - Slot Handling collapsing of Items
        Removes Child Items from pQListViewItem

-------------------------------------------------------------------------------
\brief  i0


\param  pQTreeWidgetItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemCollapsed"

void OTreeViewX :: slotItemCollapsed (QTreeWidgetItem *pQTreeWidgetItem )
{
  BEGIN_ONCE(ignore)
  ItemData       *item_data  = ItemData::GetItemData(pQTreeWidgetItem);
  ItemData       *child_item = NULL;
  logical         blocked    = NO;

BEGINSEQ
  if ( !item_data )                                  ERROR
  
  BlockSignals(YES);
  blocked = listCache.BlockEvents(YES);
  
  if ( item_data->ods_region)
  {
    item_data->HierSync(YES);
    item_data->ods_region->set_expanded(NO);
  }
  
  if ( dnd_preview_item && dnd_preview_item->Ancestor(item_data) ) // pitfall 1: dnd autocollapse 
    dnd_preview_item = NULL;
  
  if ( cur_item_candidate && cur_item_candidate->Ancestor(item_data) ) // pitfall 2: missplaced candidate
    cur_item_candidate = item_data;
  
  if ( item_data)
    while ( child_item = item_data->FirstChild() )
      delete child_item;
  inputitem = NULL;

  if ( blocked )
    listCache.BlockEvents(NO);
  BlockSignals(NO);


RECOVER

ENDSEQ
  END_ONCE
}

/******************************************************************************/
/**
\brief  i01


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemCollapsed"

void OTreeViewX :: slotItemCollapsed (ItemData *pItemData )
{

BEGINSEQ
if(!pItemData)                                       ERROR
slotItemCollapsed(pItemData->GetQTreeWidgetItem());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotItemExpanded - Slot handling Expanding of Items
        Invokes creation of data or region header.
        Removes Child Items from pQListViewItem

-------------------------------------------------------------------------------
\brief  i0


\param  pQTreeWidgetItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemExpanded"

void OTreeViewX :: slotItemExpanded (QTreeWidgetItem *pQTreeWidgetItem )
{
  ODSRegion      *sub_region = NULL;
  ItemData       *last_item  = NULL;
  ItemData  *child_item = NULL;
  ItemData       *last_lvi   = NULL;
  ItemData       *item_data  = ItemData::GetItemData(pQTreeWidgetItem);
  int             iregion    = 0;
  logical         blocked    = NO;

  BEGIN_ONCE(ignore)
  last_item = cur_display_item;
  
  BlockSignals(YES);
  blocked = listCache.BlockEvents(YES);
  
  item_data->HierSync(YES);
  
  if ( item_data->get_heading() )                     // create the regions below the expanded item 
    last_lvi = createRegion(item_data,(ODSTree*)item_data->ods_region,last_lvi);
  else
    if ( item_data->ods_region )
      while ( sub_region = item_data->ods_region->Region(iregion++) )
        last_lvi = createRegion(item_data,sub_region,last_lvi);
  
  listCache.ColScroll(AUTO);                          // ToTop für Tree um Reset-Events abzuarbeiten
  
  if ( last_lvi )
  {
    if ( last_item == last_lvi )
      last_item = NULL;
    removeItems(last_lvi);
  }
  
  if ( item_data->ods_region ) 
  {
    item_data->HierSync(YES);
    item_data->ods_region->set_expanded(YES);
  } 
  
  if ( blocked )
    listCache.BlockEvents(NO);
  BlockSignals(NO);
  
  if ( last_item )
  {
    last_item->HierSync(YES);
    SetCurrentItem(last_item);
  }
  END_ONCE

  if ( !ignore && item_data)                  // all items that are autoexpanded will have open nodes and no data in them
    for ( child_item = item_data->FirstChild(); child_item ; child_item = child_item->NextSibling() )
      if ( child_item->GetOpen() && !child_item->Count() )
        slotItemExpanded(child_item->GetQTreeWidgetItem());

}

/******************************************************************************/
/**
\brief  i01


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemExpanded"

void OTreeViewX :: slotItemExpanded (ItemData *pItemData )
{

BEGINSEQ
if(!pItemData)                                       ERROR
slotItemExpanded(pItemData->GetQTreeWidgetItem());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotItemSelected - 



\param  pQTreeWidgetItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotItemSelected"

void OTreeViewX :: slotItemSelected (QTreeWidgetItem *pQTreeWidgetItem )
{




}

/******************************************************************************/
/**
\brief  updateData - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateData"

logical OTreeViewX :: updateData ( )
{
  logical                 term = NO;
BEGINSEQ
  clear();
  OGUIERR(99)
  //term = OListView::updateData();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  updatePositions - 


-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updatePositions"

void OTreeViewX :: updatePositions ( )
{

BEGINSEQ
  /* save positions in tree */
  if(!FirstChild())                                  ERROR
  if(!FirstChild()->ods_region)                      ERROR
  listCache.expandType = EXT_Key;  
  
  updatePositions(FirstChild());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updatePositions"

void OTreeViewX :: updatePositions (ItemData *pItemData )
{
  ItemData           *item = NULL;
  ItemData           *pidata = NULL;
BEGINSEQ
  if(!pItemData )                                    ERROR
  
  if(pItemData->Parent() && pItemData->Parent()->GetOpen()){
    /* this item is open */
    pidata = pItemData->Parent();
    pItemData->HierSync(YES);
    pidata->ods_region->set_expanded(YES);
  }
  for(item = pItemData;item;item = item->NextSibling()){
    updatePositions(item->FirstChild());
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  updateRegion - updates regions, that got a event and are visible


\return term -
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateRegion"

logical OTreeViewX :: updateRegion ( )
{
  logical                 term = NO;
  updateRegion(FirstChild());
  cleanRegion();
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateRegion"

logical OTreeViewX :: updateRegion (ItemData *pItemData )
{
  ItemData             *last_item_data = NULL
                      ,*item_data = NULL;
  ItemData             *first_child;
  ODSRegion            *ireg           = NULL;
  bool                  term           = YES;
  int                   colcount       = 0;
BEGINSEQ
//debug
int itemno = 0;

  while ( pItemData )
  {
    if ( first_child = pItemData->FirstChild() )
    {
      if ( !updateRegion(first_child) && !pItemData->ChildDataCount() )
      {
        pItemData->SetOpen(false);
        pItemData->RemoveChildItems();
        slotItemCollapsed(pItemData);
      }
    }
    /* update recent changed regions */
    if ( ireg != pItemData->ods_region && pItemData->ods_region && pItemData->ods_region->get_dirty() )
    {
      pItemData->HierSync(YES);
      ireg = pItemData->ods_region;
      if(pItemData->get_heading()){
        /* close/open static elements if nessesary */
        colcount = ireg->ColGetCount();
        if(colcount && !pItemData->FirstChild()){
          createItem(pItemData);
          pItemData->SetOpen(false);
        }
        if(!colcount && pItemData->FirstChild())
          pItemData->RemoveChildItems();
        LEAVESEQ
      }
      /* has _this_ region changed ? */
      if ( pItemData->ChangedRegion() )
      {
        ireg->BlockSignals(YES);
        ireg->ColScroll(0);
        if ( pItemData->inst_id != ireg->InstGetObjID() )
        {
          /* region changed - first_item */
          int current_index = ireg->ColGetIndex();
          pItemData = pItemData->ProvideChanged(pItemData);
          /* no sense ? j 11.10.04 
          if(!pItemData->ChildDataCount())
            if(pItemData->Parent())
              pItemData->Parent()->RemoveChildItems();
          */
          ireg->ColScroll(current_index);
        }
        ireg->BlockSignals(NO);
        last_item_data = ireg->SetRegionItemData(item_data,NULL, 0 );
        ireg->set_dirty(YES);
        if ( last_item_data && (last_item_data->ods_region == ireg || !last_item_data->ods_region) )
          pItemData =   (last_item_data = removeItems(last_item_data))
                           ? last_item_data : NULL;
      }
      else
      {
        /* remove remaining region items */
        /* warum ? ohne funktioniert alles so wie ich will
           also wenn an, dann auf die items aufpassen, die mit anderem parent sich nach einem
           update schliessen.
           dass passiert, weil bei !updateRegion die node geschlossen wird.
          pItemData =   (last_item_data = removeItems(item_data))
                            ? last_item_data : NULL;
         
          */
          term = NO;
      }
    }
    else
      pItemData = pItemData->NextSibling();
itemno++;
  }

ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  updateSelection - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateSelection"

void OTreeViewX :: updateSelection ( )
{
  QList<QTreeWidgetItem*> selected;
  selected = selectedItems();
  
  cur_display_item = ItemData::GetItemData(selected[0]);
  /* happens if multiselection is enabled */
  if ( !cur_display_item ) cur_display_item = ItemData::GetItemData(currentItem());
    
  if(cur_display_item)
    cur_display_item->HierSync(YES);
  SetCurrentItem(cur_display_item);



}

/******************************************************************************/
/**
\brief  xHierSync - 


\return term -

\param  pOTreeViewItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xHierSync"

logical OTreeViewX :: xHierSync (OTreeViewItem *pOTreeViewItem )
{
  logical                 term = NO;

  return(term);
}


