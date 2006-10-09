/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OTreeWidgetItem

\brief    TreeWidgetItem
          Items for trees and widgets

\date     $Date: 2006/07/28 18:19:08,25 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTreeWidgetItem"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sOTreeView.hpp>
#include  <sOTreeWidgetItem.hpp>


/******************************************************************************/
/**
\brief  Child - Return the Child
        Returns the Child Item index

\return pItemData - ItemData

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Child"

ItemData *OTreeWidgetItem :: Child (int index )
{
  ItemData            *pItemData = NULL;
   pItemData = ItemData::GetItemData(child(index));
  return(pItemData);
}

/******************************************************************************/
/**
\brief  Count - Count
        Returns the Count of the current item and all item with its parents

\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

int32 OTreeWidgetItem :: Count ( )
{
  int                 count = 0;
  if( parent() )
    count = parent()->childCount();
  else
    count = treeWidget()->topLevelItemCount();
  return(count);
}

/******************************************************************************/
/**
\brief  GetLevel - 


\return level - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLevel"

int32 OTreeWidgetItem :: GetLevel ( )
{
  int                    level  = 0;
  ItemData              *parent = this;
  while((parent = parent->Parent()))
    level++;
  return(level);
}

/******************************************************************************/
/**
\brief  GetOpen - 


\return open - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOpen"

logical OTreeWidgetItem :: GetOpen ( )
{
  logical             open = NO;
  open = treeWidget()->isItemExpanded(this);
  return(open);
}

/******************************************************************************/
/**
\brief  GetQTreeWidgetItem - 


\return pQTreeWidgetItem - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetQTreeWidgetItem"

QTreeWidgetItem *OTreeWidgetItem :: GetQTreeWidgetItem ( )
{
  QTreeWidgetItem        *pQTreeWidgetItem;
  pQTreeWidgetItem = this;
  return(pQTreeWidgetItem);
}

/******************************************************************************/
/**
\brief  Index - Returns the Index of this Item


\return index - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Index"

int32 OTreeWidgetItem :: Index ( )
{
  int                index = NO;
  if (parent())
    index = parent()->indexOfChild(this);
  else
    index = treeWidget()->indexOfTopLevelItem(this);
  return(index);
}

/******************************************************************************/
/**
\brief  Item - Returns this item


\return pItemData - ItemData

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Item"

ItemData *OTreeWidgetItem :: Item (int index )
{
  ItemData           *pItemData = NULL;
  if ( Parent() ) 
    pItemData = Parent()->Child(index);
  else
    pItemData = ItemData::GetItemData(treeWidget()->topLevelItem(index));
  return(pItemData);
}

/******************************************************************************/
/**
\brief  OTreeWidgetItem - 


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeWidgetItem"

     OTreeWidgetItem :: OTreeWidgetItem ( )
                     : QTreeWidgetItem ()
,ItemData (pos)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  pOTreeView - 
\param  pItemDataAfter - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeWidgetItem"

     OTreeWidgetItem :: OTreeWidgetItem (OTreeView *pOTreeView, ItemData *pItemDataAfter )
                     : QTreeWidgetItem(
  pOTreeView
   ?(QTreeWidget*)pOTreeView->WidgetQ()
   :NULL
 ,pItemDataAfter
   ?pItemDataAfter->GetQTreeWidgetItem()
   :NULL
)
,ItemData(
  pItemDataAfter
   ?pItemDataAfter->pos+1
   :pos
 )
{



}

/******************************************************************************/
/**
\brief  i02 - 


\param  pItemDataParent - 
\param  pItemDataAfter - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeWidgetItem"

     OTreeWidgetItem :: OTreeWidgetItem (ItemData *pItemDataParent, ItemData *pItemDataAfter )
                     : QTreeWidgetItem(
  pItemDataParent
   ?pItemDataParent->GetQTreeWidgetItem()
   :NULL
 ,pItemDataAfter
   ?pItemDataAfter->GetQTreeWidgetItem()
   :NULL
)
,ItemData(
  pItemDataAfter
   ?pItemDataAfter->pos+1
   :pos
 )
{



}

/******************************************************************************/
/**
\brief  i03 - 


\param  pQTreeWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeWidgetItem"

     OTreeWidgetItem :: OTreeWidgetItem (QTreeWidget *pQTreeWidget )
                     : QTreeWidgetItem(pQTreeWidget),
ItemData(0)
{



}

/******************************************************************************/
/**
\brief  i04 - 


\param  pQTreeWidget - 
\param  pItemDataAfter - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeWidgetItem"

     OTreeWidgetItem :: OTreeWidgetItem (QTreeWidget *pQTreeWidget, ItemData *pItemDataAfter )
                     : QTreeWidgetItem(pQTreeWidget
  ,pItemDataAfter
   ?pItemDataAfter->GetQTreeWidgetItem()
   :NULL
)
,ItemData(
  pItemDataAfter
   ?pItemDataAfter->pos+1
   :pos
 )
{



}

/******************************************************************************/
/**
\brief  Parent - Returns the Parent of this item


\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

ItemData *OTreeWidgetItem :: Parent ( )
{
  ItemData            *pItemData = NULL;
  pItemData = ItemData::GetItemData(parent());
  return(pItemData);
}

/******************************************************************************/
/**
\brief  SetExpanded - 


\return term - 

\param  toggle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpanded"

logical OTreeWidgetItem :: SetExpanded (bool toggle )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetOpen - 


\return term - 

\param  toggle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOpen"

logical OTreeWidgetItem :: SetOpen (bool toggle )
{
  logical                 term = NO;
  if(toggle)
    treeWidget()->expandItem(this);
  else
    treeWidget()->collapseItem(this);
  return(term);
}

/******************************************************************************/
/**
\brief  ~OTreeWidgetItem - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OTreeWidgetItem"

     OTreeWidgetItem :: ~OTreeWidgetItem ( )
{



}


