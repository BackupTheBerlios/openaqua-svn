/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OTreeViewItem

\brief    


\date     $Date: 2006/03/13 21:34:49,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTreeViewItem_HPP
#define   OTreeViewItem_HPP

class     OTreeViewItem;

class     ItemData;
class     OTreeLayout;
class     OTreeView;
class     OTreeViewItem;
#include  <sODataWidget.hpp>
#include  <sOTreeWidgetItem.hpp>
class  OTreeViewItem :public OTreeWidgetItem
{

public     :
public     :         OGUI7ImpExp                                         OTreeViewItem (OTreeView *pOTreeView, OTreeViewItem *pOTreeViewItemAfter );
public     :         OGUI7ImpExp                                         OTreeViewItem (OTreeViewItem *pOTreeViewItem, OTreeViewItem *pOTreeViewItemAfter );
public     :         OGUI7ImpExp                                         OTreeViewItem (OTreeView *pOTreeView, ItemData *pItemDataAfter );
public     :         OGUI7ImpExp                                         OTreeViewItem (ItemData *pItemData, ItemData *pItemDataAfter );
protected  : virtual                             ItemData *ProvideNew (logical is_first_item=NO );
public     : virtual                             void setOpen (bool bOpen );
public     : virtual                                                     ~OTreeViewItem ( );
};

#endif
