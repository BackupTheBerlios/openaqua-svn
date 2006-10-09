/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OListCtl

\brief    


\date     $Date: 2006/08/26 17:20:06,20 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OListCtl_HPP
#define   OListCtl_HPP

class     OListCtl;

#ifndef   VECTOR_StringVector_HPP
#define   VECTOR_StringVector_HPP
#include  <sStringVector.hpp>
#include  <sVECTOR.h>
#endif
class     DPixmap;
class     ItemData;
class     ODSPropPath;
class     ODataWidget;
class     OEHEvent;
class     OHeaderView;
class     OListCtl;
class     OListLayout;
class     OTreeLayout;
class     PropertyHandle;
class     QAbstractItemView;
#include  <cADK_DataReferenceType.h>
#include  <sDFont.hpp>
#include  <sItemTreeModel.hpp>
#include  <sODS.hpp>
#include  <sODSTreeHandler.hpp>
#include  <sOEHControlList.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOSettings.hpp>
#include  <sQModelIndex.hpp>
#include  <sStringVector.hpp>
class  OListCtl :public ODSTreeHandler,
public OEHControlList
{
protected  :         ItemTreeModel                                listCache;                                                 // 
protected  :         VECTOR(StringVector)                         bookmarks;                                                 // 
protected  :         VECTOR(StringVector)                         history;                                                   // 
protected  :         int32                                        history_index;                                             // 
protected  :         OSettings                                    settings;                                                  // 
protected  :         QStyleOptionViewItem                         itemViewOptions;                                           // 

public     :
                     ItemTreeModel                               &get_listCache() { return(listCache); }
                     VECTOR(StringVector)                        &get_bookmarks() { return(bookmarks); }
                     VECTOR(StringVector)                        &get_history() { return(history); }
                     OSettings                                   &get_settings() { return(settings); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     : virtual          OGUIImpExp            int32 AddRegion (int32 parent_id, char *prop_path, logical is_collection, char *text, ODSPropertyType prop_type=PT_undefined );
public     :                                        logical BookmarkRestore (int32 indx0 );
public     : public slots:                          void DA_BookmarkNext ( );
public     :                                        logical DA_BookmarkPrevious ( );
public     :                                        logical DA_BookmarkRemove ( );
public     :                                        logical DA_BookmarkStore ( );
public     :                                        logical DA_CSVExport ( );
public     : virtual                                logical DA_FindEntry ( );
public     : virtual                                logical DA_FindEntry (char *skey, logical cur_opt=YES );
public     :                                        void DA_HistoryNext ( );
public     :                                        void DA_HistoryPrevious ( );
public     : virtual                                logical DA_NewFindEntry ( );
public     :                                        logical DA_Refresh ( );
public     : virtual                                logical DA_Reset ( );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     : virtual                                int8 ExecuteAction (char *act_names );
public     : virtual                                logical ExpandIndex (const QModelIndex &model_index );
public     : virtual                                void FillData ( );
public     : virtual                                void FillList ( );
public     : virtual                                int8 FocusInEvent ( );
public     : virtual                                ItemData *GetCurrentItem ( );
public     : virtual                                PropertyHandle *GetCurrentPropertyHandle ( );
public     : virtual          OGUIImpExp            int32 GetCurrentRegionID ( );
public     : virtual          OGUIImpExp            int32 GetCurrentRegionID (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type );
public     : virtual          OGUIImpExp            DFont GetLineFont (int column );
public     : virtual                                OListCtl *GetListControl ( );
public     : virtual          OGUIImpExp            OTreeLayout *GetListLayout ( );
public     : virtual          OGUIImpExp            PropertyHandle *GetPropertyHandle (ODSPropPath *pODSPropPath );
public     : virtual                                ODS *GetSelectedODS ( );
public     : virtual                                PropertyHandle *GetSelectedPropertyHandle ( );
public     : virtual          OGUIImpExp            int GetSubRegionCount (int32 region_id );
public     : virtual          OGUIImpExp            int GetSubRegionCount (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type );
public     : virtual                                OHeaderView *Header ( );
public     :                                        void HistoryRestore (int32 indx0 );
public     :                                        void HistoryStore ( );
public     :                                        void Initialize ( );
public     :                                        void Initialize (logical multi_sel, int8 sort_order=0, logical check_items=NO );
public     : virtual          OGUIImpExp            logical IsItemExpanded (ItemData *pItemData );
public     :                                        logical IsTransposed ( );
public     : virtual                                QAbstractItemView *ItemViewQ ( );
public     : virtual                                ItemData *LocateItem (const QModelIndex &model_index, const QString &rcqsText, logical recursive );
public     : virtual                                ItemData *LocateItem (const QString &rcqsText, logical recursive );
public     :                                        ItemData *LocateKey (char *skey );
public     :                                        ItemData *LocateRow (int row );
public     :                                        ItemData *LocateValue (QString &pQString, int col );
public     : virtual                                ItemData *NextItem (ItemData *pItemData );
public     :                                             OListCtl (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                             OListCtl (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                        void PersistentItem (ItemData *pItemData, StringVector &rStringVector );
public     :                                        ItemData *PersistentItemRestore (const StringVector &crStringVector );
public     : virtual                                ItemData *PreviousItem (ItemData *pItemData );
public     :                                        logical ProvideContextMenu (QObject *watched );
public     : virtual          OGUIImpExp            PropertyHandle *ReceiveSelectedItem ( );
public     :                  OGUIImpExp            void RefreshCurrentRegion ( );
public     : virtual          OGUIImpExp            void RefreshRegion (int32 region_id );
public     : virtual          OGUIImpExp            int32 ReplaceSubRegions (int32 parent_id, int32 region_id );
public     : virtual          OGUIImpExp            logical ResetRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     : virtual                                void SetCurrentItem (ItemData *pItemData );
public     : virtual                                void SetCurrentItem (const QModelIndex &qt_current );
public     : virtual                                logical SetDefaultReactions ( );
public     : virtual                                logical SetFilter (char *expression, logical enable_opt );
public     : virtual          OGUIImpExp            logical SetLineFont (char *font_names, int column );
public     : virtual          OGUIImpExp            logical SetLineFont (DFont *pDFont, int column );
public     : virtual          OGUIImpExp            logical SetLinePixmap (char *pixmap_names, int column );
public     : virtual          OGUIImpExp            logical SetLinePixmap (DPixmap *pDPixmap, int column );
public     :                                        void SetSorting (int8 sort_order=0 );
public     :                                        logical SyncColState ( );
public     :                                        logical SyncInstState ( );
public     : virtual                                void UnsyncState ( );
public     :                                        int UpdateColumnProperties (OListLayout *pOListLayout, int col );
public     :                                        void UpdateLayout ( );
public     :                                        void UpdateLayout (OListLayout *list_layout );
public     : virtual          OGUIImpExp            logical UpdateTreeLayout (int32 region_id );
public     : virtual                                void ValueUpdated ( );
protected  :                                        logical doCurrentChanged (ItemData *pItemData );
protected  :                                        logical doCurrentChanged (const QModelIndex &qt_current );
public     : virtual                                logical getEnabled ( );
protected  : virtual                                logical selectionRestore ( );
protected  : virtual                                logical selectionStore ( );
public     :                                        void updateListData ( );
public     :                                        void updateSelection ( );
public     : virtual                                     ~OListCtl ( );
public     : virtual                                ODS *List ( ){

  return(odw_ods);


}

};

#endif
