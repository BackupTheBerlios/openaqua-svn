/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODS

\brief    


\date     $Date: 2006/07/13 15:39:24,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODS_HPP
#define   ODS_HPP

class     ODS;

#ifndef   DLL_ODS_HPP
#define   DLL_ODS_HPP
#include  <sODS.hpp>
#include  <sDLL.h>
#endif
class     DatabaseHandle;
class     ODSItem;
class     ODSList;
class     ODSRegion;
class     PropertyHandle;
#include  <cADK_DBEVENT.h>
#include  <cItemStates.h>
#include  <cODSPropertyType.h>
#include  <sDBObjectHandle.hpp>
#include  <sODS.hpp>
#include  <sODSItemState.hpp>
#include  <sODSPropPath.hpp>
#include  <sdbdt.hpp>
#include  <sdbtm.hpp>
#pragma pack(4)

class  ODS :public QObject,
public ODSItemState
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         ODSPropPath                                  path;                                                      // 
protected  :         ODSItem                                     *prop;                                                      // 
protected  :         ODS                                         *parentODS;                                                 // 
protected  :         DBObjectHandle                               parentDB;                                                  // 
protected  :         ODSItem                                     *parentODSItem;                                             // 
protected  :         logical                                      active;                                                    // 
protected  :         PIACC                                        accessMode;                                                // 
protected  :         DLL(ODS)                                     childODS;                                                  // 
protected  :         friend class                                 ODSItem;                                                   // 

public     :
                     ODSPropPath                                 &get_path() { return(path); }
                     ODSItem                                     *get_prop() { return(prop); }
                     ODS                                         *get_parentODS() { return(parentODS); }
                     PIACC                                       &get_accessMode() { return(accessMode); }
                     DLL(ODS)                                    &get_childODS() { return(childODS); }
public     :                                        void ActivateDesignMode (logical fDmode );
public     :                                        logical BlockEvents (logical block_opt );
public     :                                        void BlockItemEvents (logical block_opt );
public     :                                        void BlockSignals (logical block_opt );
public     :                                        logical ChangedCollection ( );
public     :                  OGUIImpExp            logical CheckItem ( );
public     :                  OGUIImpExp            logical ColFind (const QString &rcqsKey, logical fConvert_YES=YES );
public     :                  OGUIImpExp            logical ColFind (const char *cszKey, logical fConvert_YES=YES );
public     :                  OGUIImpExp            int32 ColGetCount ( );
public     :                  OGUIImpExp            int32 ColGetIndex ( );
public     :                  OGUIImpExp            logical ColIsValid (logical set_state, logical check_opt );
public     :                  OGUIImpExp            logical ColNext (logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColPosition (int32 indx0, logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColPrev (logical fire_signals=YES );
public     :                  OGUIImpExp            void ColReset (logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColScroll (int32 lIndex, logical fire_signals=YES );
public     :                  OGUIImpExp            logical ColSync (int32 lID, int32 lIndexHint );
public     :                  OGUIImpExp            logical DefinesCollection ( );
public     :                                        logical GenerateEvent (ADK_DBEVENT ogui_db_event );
public     :                                        char *GetStructure ( );
public     :                                        char *GetType ( );
public     :                  OGUIImpExp            PropertyHandle *Handle ( );
public     :                  OGUIImpExp            logical HasBaseCollection ( );
public     :                                        logical HasColChanged ( );
public     :                                        logical HasInstChanged ( );
public     :                                        logical HasSelection ( );
public     :                  OGUIImpExp            char *InstGetKeyString ( );
public     :                  OGUIImpExp            int32 InstGetObjID ( );
public     :                                        void InstInit ( );
public     :                  OGUIImpExp            logical InstIsModified ( );
public     :                  OGUIImpExp            logical InstIsReadOnly ( );
public     :                  OGUIImpExp            logical InstSave (logical recursive );
public     :                                        logical IsAttribute ( );
public     :                                        logical IsAutoLocate ( );
public     :                  OGUIImpExp            logical IsBaseCollection ( );
public     :                                        logical IsBool ( );
public     :                  OGUIImpExp            logical IsCollection ( );
public     :                                        logical IsKey ( );
public     :                                        logical IsNumber ( );
public     :                                        logical IsReference ( );
public     :                                        logical IsSingleReference ( );
public     :                                        ItemStates ItemState ( );
public     : virtual                                ODSList *ListODS ( );
public     :                  OGUIImpExp                 ODS (DBObjectHandle &vDBObjectHandle, ODSPropPath &rODSPropPath, logical active_f );
public     :                  OGUIImpExp                 ODS ( );
public     :                  OGUIImpExp                 ODS (const ODS &rcODS );
public     :                  OGUIImpExp                 ODS (ODS *pODS, ODSPropPath &rODSPropPath, logical active_f );
protected  : signals:                               void OnActivated (logical fActivated );
public     : signals:                               void OnAfterDataSet ( );
public     : signals:                               void OnBeforeDataSet (logical *pterm );
protected  : signals:                               void OnBlockInstChanged (int32 lID );
protected  : signals:                               void OnBlockSignals (logical block_opt );
public     : signals:                               void OnCollectionChanged ( );
public     : signals:                               void OnCollectionReset ( );
public     : signals:                               void OnCollectionUpdated ( );
public     : signals:                               void OnDesignModeActivated (logical fDmode );
public     : signals:                               void OnHandleClosed ( );
public     : signals:                               void OnHandleOpened ( );
public     : signals:                               void OnInstanceInserted ( );
public     : signals:                               void OnInstanceRemoved ( );
public     : signals:                               void OnInstanceReset ( );
public     : signals:                               void OnInstanceSelected ( );
public     : signals:                               void OnInstanceUpdated ( );
public     :                  OGUIImpExp            DBObjectHandle &ParentDB ( );
public     :                  OGUIImpExp            ODS *ParentODS ( );
public     :                  OGUIImpExp            ODSItem *ParentODSItem ( );
public     :                                        ItemStates ProvideItem ( );
public     : virtual                                ODSRegion *RegionODS ( );
public     :                  OGUIImpExp            logical ResetPropertyHandle ( );
public     :                  OGUIImpExp            void SetActive (logical fActive );
public     :                                        logical SetFilter (char *expression, logical enable_opt );
public     :                  OGUIImpExp            void SetItemState ( );
public     :                  OGUIImpExp            void SetParentDB (DBObjectHandle &vDBObjectHandle );
public     :                  OGUIImpExp            void SetParentODS (ODS *pODS );
public     :                  OGUIImpExp            void SetParentODSItem (ODSItem *pODSItem );
public     :                  OGUIImpExp            void SetPath (char *prop_path, ODSPropertyType prop_type=PT_undefined );
public     :                  OGUIImpExp            void SetPath (ODSPropPath &rODSPropPath );
public     :                  OGUIImpExp            void SetPath (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type=PT_undefined, PIACC accmode_w=PI_Update );
public     :                                        void SetPropHdl (ODSItem *pODSItem );
public     :                  OGUIImpExp            logical SetPropertyHandle (PropertyHandle *prophdl );
public     :                                        logical Signal (char *names );
public     :                                        logical SyncColState ( );
public     :                                        logical SyncInstState ( );
public     :                                        logical SyncState ( );
public     :                                        QString Value ( );
public     :                                        dbdt ValueGetDate ( );
public     :                                        int32 ValueGetInt ( );
public     :                                        char *ValueGetString ( );
public     :                                        dbtm ValueGetTime ( );
public     :                                        void ValueInit ( );
public     :                                        logical ValueIsTrue ( );
public     :                  OGUIImpExp            logical ValueIsUpdated ( );
public     :                                        logical ValueIsValid ( );
public     :                                        void ValueReset ( );
public     :                                        logical ValueSet (const QString &rcqsText );
public     :                                        logical ValueSet (char *string );
public     :                                        logical ValueSet (int32 number );
public     :                                        logical ValueSet (logical cond );
public     :                                        logical ValueSet (dbdt date );
public     :                                        logical ValueSet (dbtm time );
public     :                                        void ValueStore ( );
public     : virtual                                void activate (logical fActivate );
public     :                                        void activate_intern ( );
public     : virtual          OGUIImpExp                 ~ODS ( );
public     :                                        logical Active ( ){

  return active;

}

public     :                  OGUIImpExp            logical IsActivated ( ){

  return !!prop;

}

public     :                  OGUIImpExp            ODSItem *Item ( ){

  return ( this ? prop : NULL );

}

public     :                                        const ODSPropPath &Path ( ) const{

  return path;

}

};

#pragma pack()
#endif
