/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/03/13 21:34:49,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTreeViewX_HPP
#define   OTreeViewX_HPP

class     OTreeViewX;

class     ODS;
class     ODSRegion;
class     ODSTree;
class     OTreeLayout;
class     OTreeView;
class     OTreeViewItem;
class     PropertyHandle;
#include  <cODSPropertyType.h>
#include  <sODataWidget.hpp>
#include  <sOEHControlList.hpp>
#include  <sOListCtl.hpp>
class  OTreeViewX :public QTreeWidget,
public OListCtl
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         logical                                      ignore;                                                    //
protected  :         ItemData                                    *cur_display_item;                                          //
protected  :         ItemData                                    *cur_item_candidate;                                        //
protected  :         logical                                      isRefreshing;                                              
protected  :         logical                                      checkMode;                                                 
protected  :         ItemData                                    *dnd_preview_item;                                          
protected  :         ItemData                                    *inputitem;                                                 

public     :
public     : virtual                             void FillList ( );
public     :                                     ItemData *FirstChild ( );
public     :                                     PropertyHandle *GetSelectedPropertyHandle ( );
public     :         OGUI7ImpExp                 void Initialize ( );
public     :         OGUI7ImpExp                 void OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical chk_items_w=NO, logical multi_sel_w=NO, logical sort_opt_w=NO );
public     :         OGUI7ImpExp                 void OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical chk_items_w=NO, logical multi_sel_w=NO, logical sort_opt_w=NO );
protected  : virtual                             void SetCurrentItem (int index );
protected  : virtual                             void SetCurrentItem (ItemData *pItemData );
public     :                                     logical ShowRegionData (OTreeViewItem *pOTreeViewItem, OTreeLayout *pOTreeLayout );
public     :                                     logical ShowRegionData (OTreeView *pOTreeView, OTreeLayout *pOTreeLayout );
public     : virtual                             void UpdateList ( );
public     :                                     QWidget *WidgetQ ( );
public     :                                     logical cleanRegion ( );
public     :                                     logical cleanRegion (ODSRegion *pODSRegion );
public     : virtual                             ItemData *createItem ( );
public     : virtual                             ItemData *createItem (ItemData *pItemData );
public     :                                     ItemData *createRegion (ItemData *pItemData, ODSRegion *pODSRegion, ItemData *last_lvi );
public     :                                     logical createStaticItem (ItemData *pItemData, ODSRegion *pODSRegion );
public     :                                     ItemData *createSubItem (ItemData *pItemData );
public     :                                     logical doExpanded (QTreeWidgetItem *pQTreeWidgetItem );
protected  : virtual                             QTreeWidgetItem *item (int iIndex );
protected  : virtual                             ItemData *removeItems (ItemData *pItemData );
public     : virtual                             logical selectionRestore ( );
public     : virtual                             logical selectionStore ( );
public     :                                     public slots: void slotItemCollapsed (QTreeWidgetItem *pQTreeWidgetItem );
public     :                                     public slots: void slotItemCollapsed (ItemData *pItemData );
public     :                                     public slots: void slotItemExpanded (QTreeWidgetItem *pQTreeWidgetItem );
public     :                                     public slots: void slotItemExpanded (ItemData *pItemData );
public     :                                     public slots: void slotItemSelected (QTreeWidgetItem *pQTreeWidgetItem );
public     : virtual                             logical updateData ( );
public     :                                     void updatePositions ( );
public     :                                     void updatePositions (ItemData *pItemData );
public     :                                     logical updateRegion ( );
public     :                                     logical updateRegion (ItemData *pItemData );
public     : virtual                             void updateSelection ( );
public     :                                     logical xHierSync (OTreeViewItem *pOTreeViewItem );
};

#endif
