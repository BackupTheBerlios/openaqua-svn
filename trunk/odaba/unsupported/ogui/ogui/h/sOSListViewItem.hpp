/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSListViewItem

\brief    OSListViewItem
          When QListViewItem knows to less
          and 
          OListViewItem does to much
          you may consider using this class

\date     $Date: 2006/03/13 21:34:33,75 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSListViewItem_HPP
#define   OSListViewItem_HPP

class     OSListViewItem;

#include  <sItemData.hpp>
class  OSListViewItem :public QTreeWidgetItem,
public ItemData
{

public     :
public     : virtual                             QTreeWidgetItem *GetQListViewItem ( );
public     :                                                             OSListViewItem (QTreeWidget *pQTreeWidget );
public     :                                                             OSListViewItem (QTreeWidgetItem *pQTreeWidgetItem );
public     :                                                             ~OSListViewItem ( );
};

#endif
