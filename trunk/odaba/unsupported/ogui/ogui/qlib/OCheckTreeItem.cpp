/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OCheckTreeItem

\brief    


\date     $Date: 2006/03/13 21:35:11,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OCheckTreeItem"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sOCheckTreeItem.hpp>
#include  <sOTreeView.hpp>
#include  <sOCheckTreeItem.hpp>


/******************************************************************************/
/**
\brief  OCheckTreeItem - Konstruktor


-------------------------------------------------------------------------------
\brief  i0


\param  pOTreeView -
\param  pItemDataAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckTreeItem"

                        OCheckTreeItem :: OCheckTreeItem (OTreeView *pOTreeView, ItemData *pItemDataAfter )
                     : OTreeWidgetItem(
  pOTreeView
 ,pItemDataAfter
)
{

  InitializeNewTreeItem();

}

/******************************************************************************/
/**
\brief  i01


\param  pItemDataParent -
\param  pItemDataAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckTreeItem"

                        OCheckTreeItem :: OCheckTreeItem (ItemData *pItemDataParent, ItemData *pItemDataAfter )
                     : OTreeWidgetItem(pItemDataParent,pItemDataAfter)
{

  InitializeNewTreeItem();

}

/******************************************************************************/
/**
\brief  ProvideNew - 


\return next_lvi -

\param  is_first_item -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideNew"

ItemData *OCheckTreeItem :: ProvideNew (logical is_first_item )
{
  OTreeView       *parentTree = treeView();
  ItemData        *parentItem = Parent();
  ItemData        *prevItem   = this;
  ItemData        *first_item = NULL;
  OCheckTreeItem  *newItem    = NULL;
  if ( is_first_item )   // insert as first (of region)
  {
    first_item = parentItem ? parentItem->FirstChild()
                            : parentTree->FirstChild();
      
    if ( !first_item || ods_region != first_item->ods_region )    // find last item of previous region 
      prevItem = PreviousSibling();
    else
      prevItem = NULL;
  }

  if ( parentItem )
    newItem = new OCheckTreeItem(parentItem,prevItem);
  else
    newItem = new OCheckTreeItem(parentTree,prevItem);
    
  if ( prevItem ) 
    newItem->MoveItem(prevItem);

  return(newItem);
}

/******************************************************************************/
/**
\brief  ~OCheckTreeItem - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OCheckTreeItem"

                        OCheckTreeItem :: ~OCheckTreeItem ( )
{



}


