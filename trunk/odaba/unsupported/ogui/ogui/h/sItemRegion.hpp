/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ItemRegion

\brief    Item Region
          An  item region is a  item list, which handles  the items for a region
          (ODSRegion), which represents a collection in the database.

\date     $Date: 2006/08/24 16:47:52,85 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ItemRegion_HPP
#define   ItemRegion_HPP

class     ItemRegion;

class     ItemData;
class     ItemRegionList;
class     ItemTreeModel;
class     ODSRegion;
class     PropertyHandle;
#include  <sItemList.hpp>
#include  <sODSItemColState.hpp>
class  ItemRegion :public ODSItemColState,
public ItemList
{
protected  :         ODSRegion                                   *region;                                                    // 
protected  :         ItemRegionList                              *region_list;                                               // 
protected  :         ItemData                                    *static_item;                                               // 
protected  :         ItemData                                    *header_item;                                               // 
protected  :         int                                          first_row;                                                 // 
protected  :         int                                          count;                                                     // 

public     :
                     ODSRegion                                   *get_region() { return(region); }
                     ItemRegionList                              *get_region_list() { return(region_list); }
                     ItemData                                    *get_static_item() { return(static_item); }
                     ItemData                                    *get_header_item() { return(header_item); }
                     int                                         &get_first_row() { return(first_row); }
                     int                                         &get_count() { return(count); }
public     :                                        void Clear ( );
public     :                                        int Count (ItemData *parent_item_data, logical update_opt );
public     :                                        ItemData *CreateItem (int index0, logical insert_opt );
public     :                                        logical FillData ( );
public     :                                        ItemData *FillItems (int index0, ItemData *parent_item_data );
public     :                                        int GetRowForDBIndex (int32 indx0 );
public     :                                        logical HasColChanged ( );
public     :                                        logical HasHeader ( );
public     :                                        logical HasInstChanged ( );
public     :                                        ItemData *InsertItem (int row );
public     :                                        ItemData *Item (int index0, ItemData *parent_item_data );
public     :                                        ItemData *ItemByDBIndex (int32 indx0, logical provide=NO );
public     :                                        ItemData *ItemByKey (char *skey, logical provide=NO );
public     :                                        ItemData *ItemByLOID (int32 objid, logical provide=NO );
public     :                                        ItemData *ItemByValue (QString &pQString, int col );
public     :                                             ItemRegion (ItemRegionList *pItemRegionList, ODSRegion *pODSRegion );
public     :                                        ItemTreeModel *Model ( );
public     :                                        ItemData *NewItem (int32 objid, char *skey, int32 indx0, int index0 );
public     :                                        ItemData *Parent (ItemData *parent_item_data );
public     :                                        ODSRegion *Region ( );
public     :                                        logical RemoveItem (int row );
public     :                                        void SetFirstRow (int row );
public     :                                        void SetupItemRows (int start_row );
public     :                                        void SetupStaticRow (int row, ItemData *parent_item_data );
public     :                                        logical StaticItemToUse (ItemData *parent_item_data );
public     :                                        logical SyncColState ( );
public     :                                        logical SyncInstState ( );
public     :                                        logical UpdateData ( );
public     :                                        ItemData *xx_Item (int index0, ItemData *parent_item_data );
public     :                                             ~ItemRegion ( );
};

#endif
