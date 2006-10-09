/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    LACObject

\brief    Database Object handle
          Database  Object  handle  (Object  handle) are necessary for accessing
          data  in an Database Object. It  allows accessing extents that contain
          the  main instances  in a  Database Object.  The object handle for the
          root  Database Object it the database  handle ({\b {.r DBHandle}}) and
          need not to be opened explicitly. 
          An  object handle is necessary for opening collection handles (PI) for
          accessing object instances stored in extents.  
          Moreover;  the object handle  administrates transactions. Transactions
          can be started and stopped for each object handle. 
          The  object handle  allows also  defining Database Object versions for
          creating and accessing version slices for a Database Object.

\date     $Date: 2006/08/26 11:55:52,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LACObject_HPP
#define   LACObject_HPP

class     LACObject;

#define  WRITE_EXTEND_LIST                         2
#include  <sDLL.h>
class     ACExtend;
#include  <sDLL.h>
class     DiffListBuffer;
#include  <sDPA.h>
class     DiffListBuffer;
#include  <sGSRT.h>
class     ExtentListEntry;
#include  <sDPA.h>
class     StructAccess;
#include  <sGSRT.h>
class     VersionEntry;
#ifndef   BTI_ACExtend_HPP
#define   BTI_ACExtend_HPP
#include  <sACExtend.hpp>
#include  <sBTI.h>
#endif
#ifndef   DLL_DBFieldDef_HPP
#define   DLL_DBFieldDef_HPP
#include  <sDBFieldDef.hpp>
#include  <sDLL.h>
#endif
#ifndef   INTERVAL_dttm_HPP
#define   INTERVAL_dttm_HPP
#include  <sdttm.hpp>
#include  <sINTERVAL.h>
#endif
class     ACExtend;
class     ACNode;
class     ACRelationship;
class     BNFData;
class     BNFExpData;
class     DBExtend;
class     DBFieldDef;
class     DBHandle;
class     DBIndex;
class     DBStructDef;
class     DiffListBuffer;
class     DifferenceList;
class     GlobalObject;
class     InternalTA;
class     LDBHandle;
class     OperEnvironment;
class     SDB_ObjectExt;
class     StructAccess;
class     TABuffer;
class     acb;
class     bnode;
class     mvli;
class     node;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <sACObject.hpp>
#include  <sBinTree.hpp>
#include  <sEB_Number.hpp>
#include  <sEntryEventList.hpp>
#include  <sLACObject.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
#include  <sdttm.hpp>
#include  <sexd.hpp>
#pragma pack(8)

class  LACObject :public virtual ACObject
{
protected  :         exd                                         *object_instance;                                           // 
protected  :         mvli                                        *extend_list;                                               // 
protected  :         BinTree                                     *acextent_tree;                                             // 
protected  :         BTI(ACExtend)                                acextent_list;                                             // 
protected  :         mvli                                        *temp_extend_list;                                          // 
protected  :         GSRT(VersionEntry)                          *version_list;                                              // 
protected  :         TABuffer                                    *ta_buffer;                                                 // 
protected  :         int32                                        ta_count;                                                  // 
protected  :         InternalTA                                  *internal_ta;                                               // 
protected  :         DPA(StructAccess)                           *struct_acc_list;                                           // 
protected  :         LDBHandle                                   *local_dbhandle;                                            // 
protected  :         logical                                      server_object;                                             // 
protected  :         logical                                      pif;                                                       // 
protected  :         logical                                      handle_cache;                                              // 
protected  :         GlobalObject                                *global_object;                                             // 
protected  :         DPA(StructAccess)                           *shadow_sal;                                                // 
protected  :         DPA(StructAccess)                           *original_sal;                                              // 
protected  :         DPA(DiffListBuffer)                         *dl_buffers;                                                // 
protected  :         PropertyHandle                               guid_pi;                                                   // 
protected  :         DLL(DBFieldDef)                              reserved_fields;                                           // 
protected  :         EntryEventList                               local_events;                                              // 
protected  :         EntryEventList                               server_events;                                             // 
protected  :         DLL(node)                                    cs_nodes;                                                  // 

public     :
                     exd                                         *get_object_instance() { return(object_instance); }
                     mvli                                        *get_extend_list() { return(extend_list); }
                     BinTree                                     *get_acextent_tree() { return(acextent_tree); }
                     BTI(ACExtend)                               &get_acextent_list() { return(acextent_list); }
                     mvli                                        *get_temp_extend_list() { return(temp_extend_list); }
                     GSRT(VersionEntry)                          *get_version_list() { return(version_list); }
                     TABuffer                                    *get_ta_buffer() { return(ta_buffer); }
                     int32                                        get_ta_count() { return(ta_count); }
                     InternalTA                                  *get_internal_ta() { return(internal_ta); }
                     DPA(StructAccess)                           *get_struct_acc_list() { return(struct_acc_list); }
                     LDBHandle                                   *get_local_dbhandle() { return(local_dbhandle); }
                     logical                                      get_server_object() { return(server_object); }
                     logical                                      get_pif() { return(pif); }
                     logical                                      get_handle_cache() { return(handle_cache); }
                     GlobalObject                                *get_global_object() { return(global_object); }
                     DPA(StructAccess)                           *get_shadow_sal() { return(shadow_sal); }
                     DPA(StructAccess)                           *get_original_sal() { return(original_sal); }
                     DPA(DiffListBuffer)                         *get_dl_buffers() { return(dl_buffers); }
                     PropertyHandle                              &get_guid_pi() { return(guid_pi); }
                     EntryEventList                              &get_local_events() { return(local_events); }
                     EntryEventList                              &get_server_events() { return(server_events); }
                     DLL(node)                                   &get_cs_nodes() { return(cs_nodes); }
public     :                                        logical ActivateShadowDB ( );
public     :                                        logical AddACExtent (ACExtend *acextent );
public     :                                        logical AddCSNode (node *nodeptr );
public     :                                        logical AddDelInstEntry (char *extnames, EB_Number pifent );
public     :                                        logical AddEvent (acb *acbptr, CSA_Events event_id );
public     : virtual                                EB_Number *AddExtendRef (DBExtend *dbextdef );
public     : virtual                                logical ChangeTimeStamp (uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
public     :                                        int16 CheckDBEntry (EB_Number entnr );
public     :                                        logical CheckEBI (exd *exdptr );
public     :                                        logical CheckEBI (EB_Number entnr );
public     :                                        logical CheckWProtect (exd *exdptr );
public     :                                        void ClearDiffListBuffer ( );
public     : virtual                                logical CloseObject ( );
public     : virtual                                ACObject *CreateACObject (int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     : virtual                                ACObject *CreateACObject (char *obname, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                        EB_Number CreateEntry (int16 mbnumber, uint16 sbnumber, EB_Number clnumb, uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             node *CreateNode (DBExtend *dbextdef, PIACC accopt );
public     : virtual          OPAImpExp             node *CreateNode (char *extnames, PIACC accopt );
public     :                                        EB_Number CreateObjInst ( );
public     : virtual                                node *CreatePathNode (char *prop_path, OperEnvironment *operenv, PIACC accopt );
public     : virtual                                node *CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv, PIACC accopt );
public     :                                        logical CreateTempExtentList ( );
public     : virtual                                node *CreateTempNode (DBFieldDef *dbfield_def );
public     : virtual                                node *CreateTempNode (node *basenode );
public     : virtual                                node *CreateTempNode (node *basenode, char *grouping_rule );
public     :                                        logical CreateVersEntry (uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
public     :                                        logical CreateVersList ( );
public     :                                        logical DeactivateShadowDB ( );
public     :                                        logical Delete (exd *exdptr );
public     : virtual                                logical DeleteExtendRef (char *extnames );
public     : virtual                                logical DeleteExtent (char *extnames );
public     : virtual                                logical ExtentExist (char *extnames );
public     :                                        logical FieldReserved (DBFieldDef *fielddef );
public     :                                        logical FlushCluster (acb *acbptr );
public     :                                        logical GenerateLocalEvents ( );
public     :                                        logical GenerateServerEvents ( );
public     :                                        ACExtend *GetACExtend (TypeKey &tkey );
public     :                                        ACExtend *GetACExtend (char *extnames );
public     :                                        uint16 GetDBVersion ( );
public     :                                        exd *GetDiffListEXD (EB_Number entnr, uint8 wslevel );
public     :                                        logical GetEBI (exd *exdptr );
public     :                                        exd *GetEXD (exd *exdarea );
public     :                                        EB_Number *GetExtendRef (TypeKey &tkey );
public     : virtual                                char *GetExtent (int32 indx0 );
public     : virtual                                GSRT(ExtentListEntry) *GetExtentList ( );
public     :                                        int32 GetLength (acb *acbptr );
public     : virtual                                LACObject *GetLocalACObject ( );
public     : virtual          OPAImpExp             int16 GetModCount (EB_Number entnr );
public     : virtual                                StructAccess *GetStructAccess (int16 sid );
public     : virtual                                StructAccess *GetStructAccess (DBStructDef *strdefptr );
public     :                                        DifferenceList *GetTADiffList (EB_Number entnr, logical recursiv=NO );
public     : virtual                                int16 GetTALevel ( );
public     : virtual                                dttm GetTimeStamp (uint16 version_nr=CUR_VERSION );
public     :                                        int32 GetUsedLength (acb *acbptr );
public     : virtual                                uint16 GetVersion (dttm timestamp=dttm() );
public     :                                        logical GetWorkspaceLevel ( );
public     :                                        logical HasWorkspace ( );
public     :                                        logical Initialize (DBHandle *dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION, logical is_server=NO );
public     :                                        logical Initialize ( );
public     :                                        logical IsExternalTA ( );
public     :                                        logical IsInternalTA ( );
public     : virtual                                int8 IsModified (exd *exdptr );
public     :                                        logical IsOpened ( );
public     :                                        logical IsPIF ( );
public     :                  OPAImpExp                  LACObject (DBHandle *dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION, logical is_server=NO );
public     :                  OPAImpExp                  LACObject (LACObject &lobhandle_ref, logical gl_object );
public     :                  OPAImpExp                  LACObject (ACObject *obhandle, int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp                  LACObject (ACObject *obhandle, char *obname, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp                  LACObject (char *data_source_name, PIACC accmode=PI_undefined );
public     :                  OPAImpExp                  LACObject ( );
public     :                                        logical LocateTAEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr=CUR_VERSION );
public     :                                        logical Lock (acb *acbptr );
public     :                                        logical LockInternal (exd *exdptr, logical wait );
public     :                                        logical LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual                                logical NewVersion (dttm timestamp=dttm(), uint16 version_nr=CUR_VERSION );
public     :                                        logical Open (EB_Number ebsnum, ACObject *obhandle );
public     :                                        ACExtend *ProvideACExtend (TypeKey &tkey, PIACC accopt, logical extadd=YES );
public     :                                        ACExtend *ProvideACExtend (char *extnames, PIACC accopt, logical extadd=YES );
public     :                                        ACExtend *ProvideACExtend (DBExtend *dbextdef, ACExtend *ac_baseext, PIACC accopt );
public     :                                        ACExtend *ProvideACExtend (char *extnames, PIACC accopt, ACRelationship *acrelptr, logical extadd=YES );
public     :                                        EB_Number *ProvideCSRef (TypeKey &tkey );
public     :                                        DiffListBuffer *ProvideDLBuffer (uint8 wslevel );
public     :                                        exd *ProvideDiffListEXD (EB_Number entnr, uint8 wslevel );
public     :                                        DifferenceList *ProvideTADiffList (DifferenceList *dlist_ptr );
public     :                                        DifferenceList *ProvideTADiffList (DBIndex *db_index, EB_Number entnr, logical shared_opt );
public     :                                        logical Read (exd *exdptr, int32 w_instlen=AUTO, logical skip_ta=NO );
public     :                                        logical ReadObjectInst ( );
public     :                                        logical ReadVersionInst (exd &version_inst, EB_Number entnr );
public     :                                        logical ReleaseField (DBFieldDef *fielddef );
public     :                                        void ReleaseFields ( );
public     :                                        logical ReleaseGlobalObject ( );
public     :                                        void ReleaseInstance (acb *acbptr );
public     :                                        logical RemoveACExtent (ACExtend *acextent );
public     :                                        logical RemoveCSNode (node *nodeptr );
public     :                                        logical RemoveVersionEntries (uint16 version_nr=CUR_VERSION );
public     :                                        logical Reserve (acb *acbptr, logical wait );
public     :                                        logical Reserve (exd *exdptr, logical wait );
public     :                                        logical ReserveField (DBFieldDef *fielddef );
public     :                                        LACObject *ReserveGlobalObject ( );
public     :                                        logical ReserveInstance (acb *acbptr );
public     : virtual                                logical ResetLastVersion ( );
public     :                                        logical ResetStructAcc (StructAccess *structacc, int16 sid );
public     : virtual                                logical SaveExtentList ( );
public     :                                        void SetServer ( );
public     :                                        logical SetStructAccess (StructAccess *structacc, int16 sid );
public     :                                        void SetTA (TABuffer *tabuffer );
public     : virtual                                void SetTransactionError ( );
public     : virtual                                logical SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                                logical SetVersion (dbdt date );
public     : virtual                                logical SetVersion (dttm timestamp=dttm() );
public     : virtual                                int16 StartTAIntern (logical ext_TA, logical intern_TA=NO, int16 w_maxnum=AUTO );
public     : virtual                                logical StopTA (int16 talevel=AUTO, logical error_case_w=NO );
public     :                                        logical Unlock (acb *acbptr );
public     :                                        logical UnlockInternal (exd *exdptr );
public     :                                        logical UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual                                int32 VersionCount ( );
public     : virtual                                INTERVAL(dttm) VersionIntervall (uint16 version_nr=CUR_VERSION );
public     :                                        logical Write (exd *exdptr );
public     :                                        logical WriteObjectInst ( );
public     :                                        logical WriteVersionInst (exd &version_inst, EB_Number entnr );
public     :                                        SDB_ObjectExt *get_ExtObject ( );
public     : virtual                                     ~LACObject ( );
};

#pragma pack()
#endif
