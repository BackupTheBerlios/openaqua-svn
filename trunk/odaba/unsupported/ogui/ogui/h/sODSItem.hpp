/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODSItem

\brief    
          valueSet  - ist bleibt auch gesetzt, wenn der value-string (durch eine
          Context-Anforderung) bereits in die property übertragen wurde.

\date     $Date: 2006/07/21 14:52:51,96 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSItem_HPP
#define   ODSItem_HPP

class     ODSItem;

#define  offValue                                  tr("N")
#define  onValue                                   tr("Y")
#ifndef   DLL_ODS_HPP
#define   DLL_ODS_HPP
#include  <sODS.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_ODSItem_HPP
#define   DLL_ODSItem_HPP
#include  <sODSItem.hpp>
#include  <sDLL.h>
#endif
class     DBStructDef;
class     DatabaseHandle;
class     EventHandler;
class     ODSItem;
class     OEHDBEventHandler;
class     smcb;
#include  <cItemStates.h>
#include  <sDBObjectHandle.hpp>
#include  <sInstance.hpp>
#include  <sODS.hpp>
#include  <sODSItemState.hpp>
#include  <sODSPropPath.hpp>
#include  <sPropertyHandle.hpp>
#include  <sdbdt.hpp>
#include  <sdbtm.hpp>
#pragma pack(4)

class  ODSItem :public QObject,
public ODSItemState
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         ItemStates                                   istate;                                                    // 
protected  :         int8                                         auto_position;                                             // 
protected  :         logical                                      is_reference;                                              // 
protected  :         logical                                      is_memo;                                                   // 
protected  :         logical                                      is_multiple;                                               // 
protected  :         logical                                      is_generic;                                                // 
protected  :         logical                                      is_path;                                                   // 
protected  :         logical                                      is_bool;                                                   // 
protected  :         logical                                      is_number;                                                 // 
protected  :         char                                        *sort_key;                                                  // 
protected  :         PropertyHandle                              *property;                                                  // 
protected  :         int32                                        refCount;                                                  // 
protected  :         ODSPropPath                                  path;                                                      // 
protected  :         logical                                      ownsProperty;                                              // 
protected  :         QString                                      value;                                                     // 
protected  :         logical                                      valueSet;                                                  // 
protected  :         DLL(ODS)                                     odslist;                                                   // 
protected  :         DBObjectHandle                               obhandle;                                                  // 
protected  :         ODSItem                                     *parent;                                                    // 
protected  :         DLL(ODSItem)                                 subs;                                                      // 
protected  :         PIACC                                        accessMode;                                                // 
protected  :         OEHDBEventHandler                           *eventHandler;                                              // 
protected  :         PropertyHandle                               coll_prop;                                                 // 
protected  :         int32                                        block_count;                                               // 

public     :
                     ItemStates                                  &get_istate() { return(istate); }
                     int8                                         get_auto_position() { return(auto_position); }
                     logical                                      get_is_reference() { return(is_reference); }
                     logical                                      get_is_memo() { return(is_memo); }
                     logical                                      get_is_multiple() { return(is_multiple); }
                     logical                                      get_is_generic() { return(is_generic); }
                     logical                                      get_is_path() { return(is_path); }
                     logical                                      get_is_bool() { return(is_bool); }
                     logical                                      get_is_number() { return(is_number); }
                     char                                        *get_sort_key() { return(sort_key); }
                     PropertyHandle                              *get_property() { return(property); }
                     ODSPropPath                                 &get_path() { return(path); }
                     QString                                     &get_value() { return(value); }
                     logical                                      get_valueSet() { return(valueSet); }
                     DBObjectHandle                              &get_obhandle() { return(obhandle); }
                     ODSItem                                     *get_parent() { return(parent); }
                     DLL(ODSItem)                                &get_subs() { return(subs); }
                     PIACC                                       &get_accessMode() { return(accessMode); }
                     PropertyHandle                              &get_coll_prop() { return(coll_prop); }
                     int32                                        get_block_count() { return(block_count); }
public     :                                        void ActivateDBEvents ( );
public     :                  OGUIImpExp            void AddODS (ODS *pODS );
public     :                                        logical AutoPosition ( );
public     :                                        logical BlockEvents (logical block_opt );
public     :                                        void BlockSignals (logical block_opt );
public     :                                        logical CheckCollPosition ( );
public     :                  OGUIImpExp            logical CheckItem ( );
public     :                  OGUIImpExp            logical ColFind (const QString &rcqsKey, logical fConvert_YES=YES );
public     :                  OGUIImpExp            logical ColFind (const char *cszKey, logical fConvert_YES=YES );
public     :                  OGUIImpExp            int ColGetCount ( );
public     :                  OGUIImpExp            int ColGetIndex ( );
public     :                  OGUIImpExp            void ColInit ( );
public     :                                        logical ColIsModified ( );
public     :                  OGUIImpExp            logical ColIsValid (logical set_state, logical check_opt );
public     :                  OGUIImpExp            logical ColNext (logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColPosition (int8 direction, logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColPrev (logical fire_signals=YES );
public     :                  OGUIImpExp            void ColReset (logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColScroll (int32 lIndex, logical fire_signals=YES );
public     :                                        void ColSetOrder ( );
public     :                  OGUIImpExp            logical ColSync (int32 lID, int32 lIndexHint );
public     :                                        void CollectionChanged (logical clear_opt );
public     :                                        void CollectionReset ( );
public     :                                        void CollectionUpdated ( );
public     :                                        logical DBEventsActive ( );
public     :                                        logical DeactivateDBEvents ( );
public     :                  OGUIImpExp            void Deref ( );
public     :                                        logical EmitRefreshEvents ( );
public     :                                        void FireCollectionSignals (logical reset_opt_w=NO );
public     :                                        void FireInstanceSignals (logical reset_opt_w=NO );
public     :                                        int32 GetColID ( );
public     :                                        int32 GetInstID ( );
public     :                                        int32 GetLastIndex ( );
public     :                                        int32 GetLastObjID ( );
public     :                                        ODS *GetODS (int32 indx0 );
public     :                                        DBObjectHandle &GetObjectHandle ( );
public     :                  OGUIImpExp            char *GetType ( );
public     :                                        void HandleClosed ( );
public     :                                        void HandleOpened ( );
public     :                                        logical HasBaseCollection ( );
public     : static                                 logical __cdecl InitStatic ( );
public     :                                        void Initialize ( );
public     :                  OGUIImpExp            char *InstGetKeyString ( );
public     :                  OGUIImpExp            int32 InstGetObjID ( );
public     :                  OGUIImpExp            QString InstGetString ( );
public     :                  OGUIImpExp            std_string InstGetType ( );
public     :                                        logical InstInit ( );
public     :                                        logical InstIsModified ( );
public     :                  OGUIImpExp            logical InstIsReadOnly ( );
public     :                  OGUIImpExp            logical InstSave (logical recursive );
public     :                  OGUIImpExp            void InstStore ( );
public     :                                        void InstanceInitialized ( );
public     :                                        void InstanceInserted ( );
public     :                                        void InstanceRemoved ( );
public     :                                        void InstanceReset ( );
public     :                                        void InstanceSelected ( );
public     :                                        void InstanceUpdated ( );
public     :                                        logical IsAttribute ( );
public     :                                        logical IsAutoLocate ( );
public     :                  OGUIImpExp            logical IsCollection ( ) const;
public     :                                        logical IsReference ( );
public     :                  OGUIImpExp            logical IsSingleReference ( ) const;
public     :                                        logical IsUserDefined ( );
public     :                                        ItemStates ItemState ( );
public     :                  OGUIImpExp                 ODSItem ( );
public     :                  OGUIImpExp                 ODSItem (ODSItem *pODSItemParent, PropertyHandle *prophdl, logical fOwnsProperty, DBObjectHandle &ob_handle );
public     :                  OGUIImpExp                 ODSItem (ODSItem *pODSItemMaster, PIACC accmode );
public     :                  OGUIImpExp                 ODSItem (ODSItem *pODSItemParent, ODSPropPath &rODSPropPath, DBObjectHandle &ob_handle );
public     :                  OGUIImpExp                 ODSItem (ODSItem *pODSItemParent, DBObjectHandle &ob_handle );
public     :                  OGUIImpExp                 ODSItem (ODSItem *pODSItemParent, ODSItem *pODSItemTemplate );
public     :                                        void OnBlockSignals (logical block_opt );
public     :                                        logical OpenSystemVariable ( );
public     :                                        logical OpenUserField (char *strnames );
public     : static           OGUIImpExp            ODSItem *__cdecl Provide (ODSItem *pODSItemParent, ODSPropPath &rODSPropPath, DBObjectHandle &ob_handle );
public     : static           OGUIImpExp            ODSItem *__cdecl Provide (DBObjectHandle &ob_handle, ODSPropPath &rODSPropPath );
public     : static           OGUIImpExp            ODSItem *__cdecl Provide (PropertyHandle *prophdl, logical fOwnsProperty, DBObjectHandle &ob_handle, ODSPropPath &rODSPropPath );
public     : static           OGUIImpExp            ODSItem *__cdecl Provide (ODSItem *pODSItemParent, PropertyHandle *ph );
public     : static                                 ODSItem *__cdecl ProvideDBItem (DBObjectHandle &ob_handle );
public     :                                        ItemStates ProvideItem ( );
public     :                                        void Refresh ( );
public     :                                        void RefreshSubItems (logical own_opt );
public     :                  OGUIImpExp            void RemODS (ODS *pODS );
public     :                                        void ResetCurrentCol ( );
public     :                                        void ResetCurrentInst ( );
public     :                                        void ResetPH ( );
public     :                                        logical ResetPropertyHandle ( );
public     :                                        logical ResetSubItems ( );
public     :                                        void SetCurrentCol ( );
public     :                                        void SetCurrentInst ( );
public     :                                        logical SetFilter (char *expression, logical enable_opt );
public     :                                        void SetItemState (logical check_opt );
public     :                                        void SetItemState (ItemStates item_state );
public     :                  OGUIImpExp            logical SetPropertyHandle (PropertyHandle *prophdl );
public     :                  OGUIImpExp            void SetSortKey (char *names );
public     :                                        void Signal (char *fnames );
public     :                                        void UpdateItemState ( );
public     :                                        QString Value ( );
public     :                                        dbdt ValueGetDate ( );
public     :                                        int32 ValueGetInt ( );
public     :                                        char *ValueGetString ( );
public     :                                        dbtm ValueGetTime ( );
public     :                  OGUIImpExp            void ValueInit ( );
public     :                                        logical ValueIsTrue ( );
public     :                                        logical ValueIsUpdated ( );
public     :                                        logical ValueIsValid ( );
public     :                                        void ValueReset ( );
public     :                  OGUIImpExp            logical ValueSet (const QString &rcqsText );
public     :                  OGUIImpExp            logical ValueSet (char *string );
public     :                  OGUIImpExp            logical ValueSet (int32 number );
public     :                  OGUIImpExp            logical ValueSet (logical cond );
public     :                  OGUIImpExp            logical ValueSet (dbdt date );
public     :                  OGUIImpExp            logical ValueSet (dbtm time );
public     :                  OGUIImpExp            logical ValueStore ( );
protected  :                                        void closePH ( );
protected  :                                        PIACC collectAccessMode ( );
protected  :                                        void deactivate ( );
public     :                  OGUIImpExp            QString getKey (logical fConvert );
protected  :                                        smcb *getKeySMCB ( );
public     :                                        logical initColAction (logical chk_key, logical chk_col, logical chk_inst );
public     :                                        logical isDerived ( );
public     :                                        logical isKey ( );
public     :                                        logical isTop ( );
protected  :                                        void openPH ( );
public     :                                        void registerChild (ODSItem *pODSItem );
public     : static                                 void __cdecl registerItem (ODSItem *pODSItem );
public     : static                                 void __cdecl unregisterItem (ODSItem *pODSItem );
protected  :                                        logical updateAccessMode (logical incr_opt );
public     : static           OGUIImpExp            void __cdecl xxClearExtentCache ( );
public     : static           OGUIImpExp            PropertyHandle *__cdecl xxOpenExtent (DBObjectHandle &vDBObjectHandle, const std_string &rcsName, logical fClone );
public     : static                                 void __cdecl xxcheckItems ( );
public     : virtual          OGUIImpExp                 ~ODSItem ( );
public     :                  OGUIImpExp            PropertyHandle *Handle ( ){

  return property;

}

public     :                  OGUIImpExp            void Ref ( ){

  refCount++;

}

};

#pragma pack()
#endif
