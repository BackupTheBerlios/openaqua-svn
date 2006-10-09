/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OCheckTreeItem

\brief    


\date     $Date: 2006/03/13 21:33:45,60 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OCheckTreeItem_HPP
#define   OCheckTreeItem_HPP

class     OCheckTreeItem;

class     ItemData;
class     OCheckTreeItem;
class     OTreeView;
#include  <sOTreeWidgetItem.hpp>
class  OCheckTreeItem :public OTreeWidgetItem
{

public     :
public     :                                                             OCheckTreeItem (OTreeView *pOTreeView, ItemData *pItemDataAfter );
public     :                                                             OCheckTreeItem (ItemData *pItemDataParent, ItemData *pItemDataAfter );
public     : virtual                             ItemData *ProvideNew (logical is_first_item=NO );
public     : virtual                                                     ~OCheckTreeItem ( );
};

#endif
