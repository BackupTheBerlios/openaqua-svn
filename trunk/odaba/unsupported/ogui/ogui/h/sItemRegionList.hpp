/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ItemRegionList

\brief    Item Region list
          An item Region List handle the items from one or more regions.

\date     $Date: 2006/08/24 16:54:29,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ItemRegionList_HPP
#define   ItemRegionList_HPP

class     ItemRegionList;

#ifndef   DLL_ItemRegion_HPP
#define   DLL_ItemRegion_HPP
#include  <sItemRegion.hpp>
#include  <sDLL.h>
#endif
class     ItemData;
class     ItemRegion;
class     ItemTreeModel;
class     ODSRegion;
class     OTreeLayout;
#include  <sQModelIndex.hpp>
class  ItemRegionList :public DLL(ItemRegion)
{
protected  :         ItemData                                    *parent;                                                    // 
protected  :         logical                                      is_dirty;                                                  // 

public     :
                     ItemData                                    *get_parent() { return(parent); }
                     logical                                      get_is_dirty() { return(is_dirty); }
public     :                                        void Clear (logical del_regions );
public     :                                        int Count ( );
public     :                                        QModelIndex FillMetaModel (QStandardItemModel *pQStandardItemModel, ItemData *pItemData, const QModelIndex &mi_parent_w=QModelIndex() );
public     :                                        ItemRegion *FindRegion (ODSRegion *pODSRegion );
public     :                                        ItemRegion *FindRegion (OTreeLayout *pOTreeLayout );
public     :                                        ItemRegion *FindRegion (int32 region_id );
public     :                                        logical HasItems ( );
public     :                                        logical HaveColChanged ( );
public     :                                        logical InitRegions (ODSRegion *pODSRegion );
public     :                                        ItemData *InsertItem (int row, ItemRegion *pItemRegion );
public     :                                        logical IsDirty (logical chk_opt );
public     :                                        ItemData *Item (int row, ItemData *parent_item_data );
public     :                                        ItemData *ItemByKey (char *skey, logical provide=NO );
public     :                                        ItemData *ItemByLOID (int32 objid, logical provide=NO );
public     :                                        ItemData *ItemByValue (QString &pQString, int col );
public     :                                             ItemRegionList (ItemData *pItemData );
public     :                                        ItemTreeModel *Model ( );
public     :                                        ItemData *Parent ( );
public     :                                        logical ProvideRegion (ODSRegion *pODSRegion );
public     :                                        logical RemoveItem (ItemData *pItemData );
public     :                                        void RemoveRegion (int32 region_id );
public     :                                        logical ResetHandles ( );
public     :                                        void SetDirty ( );
public     :                                        void UpdateData (logical chk_opt );
public     :                                             ~ItemRegionList ( );
};

#endif
