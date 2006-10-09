/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OTreeViewItem

\brief    


\date     $Date: 2006/03/13 21:36:21,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTreeViewItem"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sODataWidget.hpp>
#include  <sOPixmap.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOTreeView.hpp>
#include  <sOTreeViewItem.hpp>
#include  <sOTreeViewItem.hpp>


/******************************************************************************/
/**
\brief  OTreeViewItem - 


-------------------------------------------------------------------------------
\brief  i01


\param  pOTreeView -
\param  pOTreeViewItemAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeViewItem"

                        OTreeViewItem :: OTreeViewItem (OTreeView *pOTreeView, OTreeViewItem *pOTreeViewItemAfter )
                     : OTreeWidgetItem()
{

  pOTreeView->insertTopLevelItem(pOTreeViewItemAfter->pos,this);
  InitializeNewTreeItem();


}

/******************************************************************************/
/**
\brief  i02


\param  pOTreeViewItem -
\param  pOTreeViewItemAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeViewItem"

                        OTreeViewItem :: OTreeViewItem (OTreeViewItem *pOTreeViewItem, OTreeViewItem *pOTreeViewItemAfter )
                     : OTreeWidgetItem()
{

  pOTreeViewItem->insertChild(pOTreeViewItemAfter->pos,this);
  InitializeNewTreeItem();

}

/******************************************************************************/
/**
\brief  i03


\param  pOTreeView -
\param  pItemDataAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeViewItem"

                        OTreeViewItem :: OTreeViewItem (OTreeView *pOTreeView, ItemData *pItemDataAfter )
                     : OTreeWidgetItem ()
{

  pOTreeView->insertTopLevelItem(pItemDataAfter->pos,this);
  InitializeNewTreeItem();

}

/******************************************************************************/
/**
\brief  i04


\param  pItemData - ItemData
\param  pItemDataAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTreeViewItem"

                        OTreeViewItem :: OTreeViewItem (ItemData *pItemData, ItemData *pItemDataAfter )
                     : OTreeWidgetItem ()
{

  pItemData->GetQTreeWidgetItem()->insertChild(pItemDataAfter->pos,this);
  InitializeNewTreeItem();

}

/******************************************************************************/
/**
\brief  ProvideNew - provide a new item


\return next_lvi -

\param  is_first_item -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideNew"

ItemData *OTreeViewItem :: ProvideNew (logical is_first_item )
{
  OTreeView      *parentList = (OTreeView *)treeView();
  ItemData       *parentItem = Parent() ? (OTreeViewItem *)Parent() : NULL;
  ItemData       *prevItem   = this;
  ItemData       *first_item;
  OTreeViewItem  *newItem    = NULL;
  if ( is_first_item )   // insert as first (of region)
  {
    first_item = parentItem ? parentItem->FirstChild()
                            : parentList->FirstChild();
      
    if ( !first_item|| ods_region != first_item->ods_region )    // find last item of previous region 
      prevItem = PreviousSibling();
    else
      prevItem = NULL;
  }

  if ( parentItem )
    newItem = new OTreeViewItem(parentItem,prevItem);
  else
    newItem = new OTreeViewItem(parentList,prevItem);
  
  if(prevItem)
    ItemData::GetItemData(newItem)->ods_region = prevItem->ods_region;
  return(newItem);
}

/******************************************************************************/
/**
\brief  setOpen - 



\param  bOpen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setOpen"

void OTreeViewItem :: setOpen (bool bOpen )
{
  OTreeLayout           *pOTLayout = NULL;
  int                    icol = 0;
BEGINSEQ
  if ( heading )                                     LEAVESEQ
  if ( !ods_region)                                  LEAVESEQ
  if ( !(pOTLayout = ods_region->GetLayout()))       LEAVESEQ
  
  if ( !bOpen ){
    if ( pOTLayout->get_normal_pixmap() )
      setIcon(0,*pOTLayout->get_normal_pixmap());
  }else{
    if ( pOTLayout->get_active_pixmap() )
      setIcon(0,*pOTLayout->get_active_pixmap());
  }
ENDSEQ
  treeWidget()->setItemExpanded(this,bOpen);
}

/******************************************************************************/
/**
\brief  ~OTreeViewItem - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OTreeViewItem"

                        OTreeViewItem :: ~OTreeViewItem ( )
{



}


