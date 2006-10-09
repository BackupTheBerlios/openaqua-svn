/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OTreeWidgetItem

\brief    TreeWidgetItem
          Items for trees and widgets

\date     $Date: 2006/03/13 21:34:50,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTreeWidgetItem_HPP
#define   OTreeWidgetItem_HPP

class     OTreeWidgetItem;

class     OTreeView;
#include  <sItemData.hpp>
class  OTreeWidgetItem :public QTreeWidgetItem,
public ItemData
{

public     :
public     : virtual                             ItemData *Child (int index );
public     : virtual                             int32 Count ( );
public     :                                     int32 GetLevel ( );
public     :                                     logical GetOpen ( );
public     :                                     QTreeWidgetItem *GetQTreeWidgetItem ( );
public     : virtual                             int32 Index ( );
public     : virtual                             ItemData *Item (int index );
public     :                                                             OTreeWidgetItem ( );
public     :                                                             OTreeWidgetItem (OTreeView *pOTreeView, ItemData *pItemDataAfter );
public     :                                                             OTreeWidgetItem (ItemData *pItemDataParent, ItemData *pItemDataAfter );
public     :                                                             OTreeWidgetItem (QTreeWidget *pQTreeWidget );
public     :                                                             OTreeWidgetItem (QTreeWidget *pQTreeWidget, ItemData *pItemDataAfter );
public     : virtual                             ItemData *Parent ( );
public     :                                     logical SetExpanded (bool toggle=FALSE );
public     :                                     logical SetOpen (bool toggle=FALSE );
public     :                                                             ~OTreeWidgetItem ( );
};

#endif
