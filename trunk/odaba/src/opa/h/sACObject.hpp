/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACObject

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

\date     $Date: 2006/08/26 12:06:40,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACObject_HPP
#define   ACObject_HPP

class     ACObject;

#define  CUR_SYSVERSION                            18
#define  OBJECT_ID                                 1145651791
#define  RET_STR_LEN                               512
#define  TEMP_EXT                                  "_tempExt"
#ifndef   P_ODC_NamedObject_HPP
#define   P_ODC_NamedObject_HPP
#include  <sPI.hpp>
class       ODC_NamedObject;
PI_dcl     (ODC_NamedObject)
#endif
#ifndef   P_SDB_ObjectID_HPP
#define   P_SDB_ObjectID_HPP
#include  <sPI.hpp>
class       SDB_ObjectID;
PI_dcl     (SDB_ObjectID)
#endif
#include  <sDLL.h>
class     ACObject;
#include  <sGSRT.h>
class     ExtentListEntry;
#ifndef   DLL_bnode_HPP
#define   DLL_bnode_HPP
#include  <sbnode.hpp>
#include  <sDLL.h>
#endif
#ifndef   INTERVAL_dttm_HPP
#define   INTERVAL_dttm_HPP
#include  <sdttm.hpp>
#include  <sINTERVAL.h>
#endif
class     ACNode;
class     BNFData;
class     BNFExpData;
class     CACObject;
class     CClient;
class     CTX_Object;
class     DBExtend;
class     DBFieldDef;
class     DBHandle;
class     DBObjectHandle;
class     DBResource;
class     DBStructDef;
class     DataSourceHandle;
class     Dictionary;
class     Error;
class     LACObject;
class     OperEnvironment;
class     RessourceLock;
class     StructAccess;
class     bnode;
class     exd;
class     node;
class     smcb;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cResourceTypes.h>
#include  <sACObject.hpp>
#include  <sEB_Number.hpp>
#include  <sNString.hpp>
#include  <sODABAClient.hpp>
#include  <sObjectReference.hpp>
#include  <sPropertyHandle.hpp>
#include  <sReferenceObject.hpp>
#include  <sTypeKey.hpp>
#include  <sdttm.hpp>
#pragma pack(8)

class  ACObject :public ObjectReference
{
protected  :         int32                                        ident;                                                     // 
protected  :         ACObject                                    *obj_handle;                                                // 
protected  :         DBHandle                                    *db_handle;                                                 // 
protected  :         DLL(ACObject)                               *object_list;                                               // 
protected  :         PI(SDB_ObjectID)                            *objid_pi;                                                  // 
protected  :         PI(ODC_NamedObject)                         *objname_pi;                                                // 
protected  :         PIACC                                        access_mode;                                               // 
protected  :         logical                                      obj_overload;                                              // 
protected  :         uint16                                       version;                                                   // 
protected  :         logical                                      is_global_object;                                          // 
protected  :         logical                                      update_timestamp;                                          // 
protected  :         PropertyHandle                               void_pi;                                                   // 
protected  :         DBResource                                  *resource;                                                  // 
protected  :         NString                                      nstring;                                                   // 
protected  :         ACObject                                    *db_hdl;                                                    // 
protected  :         CTX_Object                                  *ocontext;                                                  // 
protected  :         logical                                      userdef_id;                                                // 
protected  :         logical                                      event_handling;                                            // 
protected  :         char                                        *context_path;                                              // 
protected  :         DataSourceHandle                            *ds_handle;                                                 // 
protected  :         DLL(bnode)                                   event_queue;                                               // 
protected  :         int32                                        rta_count;                                                 // 
protected  :         Error                                       *sdb_error;                                                 // 
protected  :         int16                                        data_version;                                              // 
protected  :         NString                                     *nresult;                                                   // 
protected  :         uint16                                       sys_version;                                               // 
protected  :         DLL(bnode)                                   path_nodes;                                                // 

public     :
                     ACObject                                    *get_obj_handle() { return(obj_handle); }
                     DBHandle                                    *get_db_handle() { return(db_handle); }
                     DLL(ACObject)                               *get_object_list() { return(object_list); }
                     PI(SDB_ObjectID)                            *get_objid_pi() { return(objid_pi); }
                     PI(ODC_NamedObject)                         *get_objname_pi() { return(objname_pi); }
                     PIACC                                        get_access_mode() { return(access_mode); }
                     logical                                      get_obj_overload() { return(obj_overload); }
                     uint16                                       get_version() { return(version); }
                     logical                                      get_is_global_object() { return(is_global_object); }
                     logical                                      get_update_timestamp() { return(update_timestamp); }
                     PropertyHandle                              &get_void_pi() { return(void_pi); }
                     DBResource                                  *get_resource() { return(resource); }
                     NString                                     &get_nstring() { return(nstring); }
                     ACObject                                    *get_db_hdl() { return(db_hdl); }
                     CTX_Object                                  *get_ocontext() { return(ocontext); }
                     logical                                      get_userdef_id() { return(userdef_id); }
                     logical                                      get_event_handling() { return(event_handling); }
                     char                                        *get_context_path() { return(context_path); }
                     DataSourceHandle                            *get_ds_handle() { return(ds_handle); }
                     DLL(bnode)                                  &get_event_queue() { return(event_queue); }
                     int32                                        get_rta_count() { return(rta_count); }
                     int16                                        get_data_version() { return(data_version); }
                     NString                                     *get_nresult() { return(nresult); }
                     uint16                                       get_sys_version() { return(sys_version); }
                     DLL(bnode)                                  &get_path_nodes() { return(path_nodes); }
public     :                  OPAImpExp                  ACObject (DBHandle *dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp                  ACObject (ACObject &obhandle_ref, logical gl_object );
public     :                  OPAImpExp                  ACObject (ACObject *obhandle, int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp                  ACObject (ACObject *obhandle, char *obname, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp                  ACObject ( );
public     :                                        logical AddEventNode (bnode *bnodeptr, int8 seq_opt );
public     :                                        logical AddPathNode (bnode *bnodeptr );
public     : virtual          OPAImpExp             logical ChangeTimeStamp (uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
public     :                  OPAImpExp             logical CheckAccess (PIACC accmode=PI_undefined );
public     :                                        bnode *CheckEventNode (bnode *bnodeptr );
public     : virtual          OPAImpExp             logical CloseObject ( );
public     : virtual          OPAImpExp             ACObject *CreateACObject (int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             ACObject *CreateACObject (char *obname, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                        logical CreateContext ( );
public     : virtual          OPAImpExp             node *CreateNode (DBExtend *dbextdef, PIACC accopt );
public     : virtual          OPAImpExp             node *CreateNode (char *extnames, PIACC accopt );
public     : virtual          OPAImpExp             node *CreatePathNode (char *prop_path, OperEnvironment *operenv, PIACC accopt );
public     : virtual          OPAImpExp             node *CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv, PIACC accopt );
public     : virtual          OPAImpExp             node *CreateTempNode (DBFieldDef *dbfield_def );
public     : virtual          OPAImpExp             node *CreateTempNode (node *basenode );
public     : virtual          OPAImpExp             node *CreateTempNode (node *basenode, char *grouping_rule );
public     : virtual          OPAImpExp             logical DeleteExtendRef (char *extnames );
public     : virtual          OPAImpExp             logical DeleteExtent (char *extnames );
public     :                                        logical DiffersFrom (ACObject *obhandle );
public     :                                        void DisableEventHandling ( );
public     :                                        void EnableEventHandling ( );
public     :                                        logical EventHandling ( );
public     : virtual          OPAImpExp             logical ExecObjCtxFunc (char *fnames, char *w_parms=NULL );
public     :                                        PropertyHandle ExecuteExpression (ACObject *resobj, char *expression );
public     : virtual          OPAImpExp             logical ExtentExist (char *extnames );
public     :                  OPAImpExp             PIACC GetAccess ( );
public     :                                        char *GetCTXIPath ( );
public     :                                        CClient *GetClient ( );
public     : virtual          OPAImpExp             CACObject *GetClientACObject ( );
public     : virtual          OPAImpExp             ODABAClient &GetConnectionClient ( );
public     :                                        uint16 GetCurrentSystemVersion ( );
public     :                  OPAImpExp             DBHandle *GetDBHandle ( );
public     :                                        DBObjectHandle *GetDBObjectHandle ( );
public     :                                        DataSourceHandle *GetDataSource ( );
public     :                  OPAImpExp             Dictionary *GetDictionary ( );
public     :                                        int32 GetErrorCode ( );
public     : virtual          OPAImpExp             char *GetExtent (int32 indx0 );
public     : virtual          OPAImpExp             GSRT(ExtentListEntry) *GetExtentList ( );
public     :                  OPAImpExp             ACObject *GetHighObject ( );
public     :                                        ACObject **GetHighObjectPtr ( );
public     :                                        int16 GetID_SIZE ( );
public     : virtual          OPAImpExp             LACObject *GetLocalACObject ( );
public     : virtual          OPAImpExp             int16 GetModCount (EB_Number entnr );
public     :                                        node *GetNodePtr (char *prop_path, OperEnvironment *operenv, FunctionTypes &path_type, PIACC accopt );
public     :                  OPAImpExp             char *GetObject (int32 indx0 );
public     :                                        char *GetOutputResult ( );
public     :                                        ResourceTypes GetResourceType (ResourceTypes local_ressources=RES_automatic, char *cpath_w=NULL );
public     :                  OPAImpExp             smcb *GetSMCB (TypeKey &tkey );
public     :                  OPAImpExp             smcb *GetSMCB (char *strnames, int32 nsid );
public     :                  OPAImpExp             smcb *GetSMCB (char *scoped_name );
public     :                                        uint16 GetSchemaVersion ( );
public     :                                        node *GetStartNode (OperEnvironment *operenv, char *propnames, FunctionTypes &path_type, PIACC accopt );
public     : virtual          OPAImpExp             StructAccess *GetStructAccess (int16 sid );
public     : virtual          OPAImpExp             StructAccess *GetStructAccess (DBStructDef *strdefptr );
public     :                  OPAImpExp             uint16 GetSystemVersion ( );
public     : virtual          OPAImpExp             int16 GetTALevel ( );
public     : virtual          OPAImpExp             DBHandle *GetThisDBHandle ( );
public     : virtual          OPAImpExp             Dictionary *GetThisDictionary ( );
public     :                                        ACObject *GetThisObject ( );
public     : virtual          OPAImpExp             dttm GetTimeStamp (uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp             logical GetTypes (char *scoped_name, int16 *itypptr=NULL, int16 *stypptr=NULL, int16 *atypptr=NULL );
public     : virtual          OPAImpExp             uint16 GetVersion (dttm timestamp=dttm() );
public     :                                        PropertyHandle *GetVoidPI ( );
public     :                                        logical Initialize ( );
public     :                                        logical Initialize (DBHandle *dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                        logical IsClientObject ( );
public     :                                        logical IsDBHandleDict ( );
public     : virtual          OPAImpExp             int8 IsModified (exd *exdptr );
public     :                                        logical IsServerObject ( );
public     :                                        logical IsSystemObject ( );
public     :                  OPAImpExp             logical IsUserDefinedIdentity ( );
public     :                  OPAImpExp             logical IsValid ( );
public     : virtual                                logical IsXMLBase ( );
public     : virtual          OPAImpExp             logical NewVersion (dttm timestamp=dttm(), uint16 version_nr=CUR_VERSION );
public     :                                        logical Open (EB_Number ebsnum, ACObject *obhandle );
public     :                                        logical OpenPIs ( );
public     :                                        void OutputResult (char *string );
public     :                                        logical PopConnectionResult ( );
public     :                                        logical PushConnectionResult ( );
public     :                                        logical ReleaseEvents (logical emit_opt );
public     :                                        logical RemoveEventNode (bnode *bnodeptr );
public     :                                        logical RemovePathNode (bnode *bnodeptr );
public     :                                        void ResetError ( );
public     :                                        void ResetErrorObject ( );
public     :                                        void ResetOutputResult ( );
public     : virtual          OPAImpExp             logical SaveExtentList ( );
public     :                                        logical SetActVersion (ACObject *obhandle );
public     :                                        void SetDataSource (DataSourceHandle *ds_handle );
public     :                                        void SetErrorVariables (char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     : virtual          OPAImpExp             logical SetOverload (logical overload_opt );
public     : virtual          OPAImpExp             void SetTransactionError ( );
public     : virtual          OPAImpExp             logical SetUserDefinedIdentity (logical identity_opt );
public     : virtual          OPAImpExp             logical SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             logical SetVersion (dbdt date );
public     : virtual          OPAImpExp             logical SetVersion (dttm timestamp=dttm() );
public     :                                        void StartReadTA ( );
public     : virtual          OPAImpExp             int16 StartTA (logical ext_TA, int16 w_maxnum=AUTO );
public     : virtual          OPAImpExp             int16 StartTAIntern (logical ext_TA, logical intern_TA=NO, int16 w_maxnum=AUTO );
public     :                                        void StopReadTA (logical error_case );
public     : virtual          OPAImpExp             logical StopTA (int16 talevel=AUTO, logical error_case_w=NO );
public     : virtual          OPAImpExp             logical UpdateTimestamp (logical timestamp_enabled );
public     : virtual          OPAImpExp             int32 VersionCount ( );
public     : virtual          OPAImpExp             INTERVAL(dttm) VersionIntervall (uint16 version_nr=CUR_VERSION );
public     :                                        char *set_result_string (char *char_buffer, int32 longlen );
public     : virtual          OPAImpExp                  ~ACObject ( );
};

#pragma pack()
#endif
