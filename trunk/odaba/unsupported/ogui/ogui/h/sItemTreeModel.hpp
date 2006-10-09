/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ItemTreeModel

\brief    


\date     $Date: 2006/08/26 17:43:13,84 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ItemTreeModel_HPP
#define   ItemTreeModel_HPP

class     ItemTreeModel;

#ifndef   VECTOR_ItemData_HPP
#define   VECTOR_ItemData_HPP
#include  <sItemData.hpp>
#include  <sVECTOR.h>
#endif
class     CellData;
class     ItemData;
class     ItemRegion;
class     ODSList;
class     ODSRegion;
class     ODataWidget;
class     OEHControlData;
class     OTreeLayout;
#include  <cADK_DataReferenceType.h>
#include  <sItemRegionList.hpp>
#include  <sODSTree.hpp>
#include  <sODragAndDrop.hpp>
#include  <sQAbstractItemModel.hpp>
#include  <sQModelIndex.hpp>
class  ItemTreeModel :public QAbstractItemModel,
public ItemRegionList,
public ODSTree,
public ODragAndDrop
{
protected  :         logical                                      transposed;                                                // 
protected  :         logical                                      check_box;                                                 // 
protected  :         logical                                      top_filter;                                                // 
protected  :         logical                                      initialized;                                               // 
protected  :         QAbstractProxyModel                         *proxyModel;                                                // 

public     :
                     logical                                      get_transposed() { return(transposed); }
                     logical                                      get_check_box() { return(check_box); }
                     logical                                      get_top_filter() { return(top_filter); }
                     QAbstractProxyModel                         *get_proxyModel() { return(proxyModel); }
public     : static                                 CellData *__cdecl Cell (const QModelIndex &model_index );
public     :                                        ItemRegionList *ChildList (ItemData *pItemData ) const;
public     :                                        void ClearData (logical del_regions );
public     :                                        logical FillItems ( );
public     :                                        QModelIndex FillMetaModel (QStandardItemModel *pQStandardItemModel, ItemData *pItemData );
public     :                                        logical FilterChanged (ODSRegion *pODSRegion );
public     :                                        ItemRegion *FindRegion (ODSRegion *pODSRegion );
public     :                                        QAbstractItemModel *GetSortProxy (QAbstractItemView *pQAbstractItemView );
public     :                                        logical InitRegions (ODSTree *pODSTree );
public     :                                        ItemData *InsertItem (ODSRegion *pODSRegion );
public     :                                        ItemData *InsertItem (ODSRegion *pODSRegion, int32 indx0 );
public     :                                        logical IsRelated (const QModelIndex &model_index, const QModelIndex &model_index_compare );
public     :                                        logical IsVisible ( ) const;
public     :                                        ItemData *Item (const QModelIndex &model_index ) const;
public     :                                        ItemData *ItemByDBIndex (ItemData *pCollectionItem, int32 indx0, logical provide=NO );
public     :                                        ItemData *ItemByDBIndex (ODSRegion *pODSRegion, int32 indx0, logical provide=NO );
public     :                                        ItemData *ItemByDBIndex (int32 indx0, logical provide=NO );
public     :                                        ItemData *ItemByKey (ItemData *pCollectionItem, char *skey, logical provide=NO );
public     :                                        ItemData *ItemByLOID (ItemData *pCollectionItem, int32 objid, logical provide=NO );
public     :                                        ItemData *ItemByLOID (ODSRegion *pODSRegion, int32 objid, logical provide=NO );
public     :                                        ItemData *ItemByRow (int row );
public     :                                        ItemData *ItemByValue (ItemData *pCollectionItem, QString &pQString, int col );
public     :                                        int32 ItemCount (const QModelIndex &mi_parent_w=QModelIndex() ) const;
public     :                                             ItemTreeModel (OEHControlData *pOEHControlData );
public     :                                        ItemRegionList *RegionList (ItemData *pItemData ) const;
public     :                                        ItemData *RemoveItem (ODSRegion *pODSRegion, int32 objid );
public     :                                        ItemData *RemoveItem (ItemData *pItemData );
public     :                                        void RemoveRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     :                                        void RemoveRows (ItemData *pItemData );
public     :                                        logical SetFilter (char *expression, logical enable_opt );
public     :                                        logical SetLayout (OTreeLayout *pOTreeLayout );
public     :                                        void SetTransposed (bool toggle=FALSE );
public     :                                        ODSTree *Tree ( ) const;
public     :                                        void UpdateData ( );
public     :                                        void UpdateData (ItemData *first_item, ItemData *last_item );
public     :                                        void UpdateData (CellData *pCellData );
public     :                                        logical UpdateTreeLayout (OTreeLayout *tree_layout );
public     :                                        int columnCount (const QModelIndex &mi_parent_w=QModelIndex() ) const;
public     : virtual                                QVariant data (const QModelIndex &model_index, int dat_role ) const;
public     : virtual                                bool dropMimeData (const QMimeData *cpQMimeData, Qt::DropAction mime_drop_action, int row, int column, const QModelIndex &mi_parent );
public     :                                        Qt::ItemFlags flags (const QModelIndex &model_index ) const;
public     : virtual                                bool hasChildren (const QModelIndex &mi_parent ) const;
public     : virtual                                QVariant headerData (int section, Qt::Orientation horientation, int dat_role ) const;
public     : virtual                                QModelIndex index (int row, int column, const QModelIndex &mi_parent_w=QModelIndex() ) const;
public     : virtual                                QMimeData *mimeData (const QModelIndexList &model_indicies ) const;
public     : virtual                                QStringList mimeTypes ( ) const;
public     : virtual                                QModelIndex parent (const QModelIndex &model_index ) const;
public     : virtual                                bool removeRows (int row, int count, const QModelIndex &model_index );
public     : virtual                                int rowCount (const QModelIndex &mi_parent_w=QModelIndex() ) const;
public     : virtual                                bool setData (const QModelIndex &model_index, const QVariant &qvariant, int edit_role );
public     :                                        void set_check_box (logical check_items=NO );
public     : virtual                                Qt::DropActions supportedDropActions ( ) const;
public     :                                             ~ItemTreeModel ( );
};

#endif
