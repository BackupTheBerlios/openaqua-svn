/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    bnode

\brief    


\date     $Date: 2006/08/04 12:02:27,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   bnode_HPP
#define   bnode_HPP

class     bnode;

#define  Bnodeinst                                 get_bnodeinst()
#define  Bnodenode                                 ((bnode *)nodenode)
#define  Bnodeptr                                  ((bnode *)nodeptr)
#define  getBnodeptr                               ((bnode *)get_nodeptr())
#include  <sDLL.h>
class     bnode;
#include  <sDPA.h>
class     inti;
class     ACExtend;
class     ACObject;
class     CSA_Handle;
class     CTX_Base;
class     CTX_Property;
class     CTX_Structure;
class     DBFieldDef;
class     DBIndex;
class     DBStructDef;
class     Dictionary;
class     EventLink;
class     EventLinkList;
class     InstBuffer;
class     InstanceCache;
class     ProcessEventHandler;
class     binti;
class     dbf;
class     isel;
class     kcb;
class     ref;
class     smcb;
#include  <cDB_Event.h>
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <cSDB_RLEV.h>
#include  <sCSHandle.hpp>
#include  <sEB_Number.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#include  <sflnk.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#pragma pack(8)

class  bnode :public CSHandle,
public node
{
protected  :         logical                                      nodewrit;                                                  // 
protected  :         logical                                      is_dirty;                                                  // 
protected  :         PIACC                                        nodeacc;                                                   // 
protected  :         DBFieldDef                                  *nodefield;                                                 // 
protected  :         CTX_Property                                *context;                                                   // 
protected  :         ACObject                                    *object_ref;                                                // 
protected  :         DPA(inti)                                   *type_inti;                                                 // 
protected  :         InstBuffer                                  *inti_buffer;                                               // 
protected  :         node                                        *base_node;                                                 // 
protected  :         kcb                                         *id_key;                                                    // 
protected  :         DBIndex                                     *sk_index;                                                  // 
protected  :         logical                                      is_collection;                                             // 
protected  :         logical                                      is_opened;                                                 // 
protected  :         logical                                      is_memo;                                                   // 
protected  :         logical                                      is_codeset;                                                // 
protected  :         logical                                      variable_type;                                             // 
protected  :         logical                                      moveable_instance;                                         // 
protected  :         logical                                      is_updated;                                                // 
protected  :         logical                                      is_valid;                                                  // 
protected  :         logical                                      has_event_handler;                                         // 
protected  :         logical                                      key_check;                                                 // 
protected  :         logical                                      reserve_lo;                                                // 
protected  :         logical                                      registered;                                                // 
protected  :         int64                                        objid;                                                     // 
protected  :         int8                                         new_instance;                                              // 
protected  :         logical                                      instance_inserted;                                         // 
protected  :         inti                                        *high_inti;                                                 // 
protected  :         node                                        *base_reference;                                            // 
protected  :         void                                        *spec_info;                                                 // 
protected  :         EventLinkList                               *event_handler;                                             // 
protected  :         ProcessEventHandler                         *proc_event_handler;                                        // 
protected  :         InstanceCache                               *cache_list;                                                // 
protected  :         int32                                        absolute_index;                                            // 
protected  :         int32                                        relative_index;                                            // 
protected  :         DLL(bnode)                                  *path_nodes;                                                // 

public     :
                     logical                                      get_nodewrit() { return(nodewrit); }
                     logical                                      get_is_dirty() { return(is_dirty); }
                     PIACC                                        get_nodeacc() { return(nodeacc); }
                     DBFieldDef                                  *get_nodefield() { return(nodefield); }
                     CTX_Property                                *get_context() { return(context); }
                     ACObject                                    *get_object_ref() { return(object_ref); }
                     DPA(inti)                                   *get_type_inti() { return(type_inti); }
                     node                                        *get_base_node() { return(base_node); }
                     kcb                                         *get_id_key() { return(id_key); }
                     DBIndex                                     *get_sk_index() { return(sk_index); }
                     logical                                      get_is_collection() { return(is_collection); }
                     logical                                      get_is_opened() { return(is_opened); }
                     logical                                      get_is_memo() { return(is_memo); }
                     logical                                      get_is_codeset() { return(is_codeset); }
                     logical                                      get_variable_type() { return(variable_type); }
                     logical                                      get_moveable_instance() { return(moveable_instance); }
                     logical                                      get_is_updated() { return(is_updated); }
                     logical                                      get_is_valid() { return(is_valid); }
                     logical                                      get_has_event_handler() { return(has_event_handler); }
                     logical                                      get_key_check() { return(key_check); }
                     logical                                      get_reserve_lo() { return(reserve_lo); }
                     logical                                      get_registered() { return(registered); }
                     int64                                        get_objid() { return(objid); }
                     int8                                         get_new_instance() { return(new_instance); }
                     logical                                      get_instance_inserted() { return(instance_inserted); }
                     inti                                        *get_high_inti() { return(high_inti); }
                     node                                        *get_base_reference() { return(base_reference); }
                     void                                        *get_spec_info() { return(spec_info); }
                     EventLinkList                               *get_event_handler() { return(event_handler); }
                     ProcessEventHandler                         *get_proc_event_handler() { return(proc_event_handler); }
                     InstanceCache                               *get_cache_list() { return(cache_list); }
                     int32                                        get_absolute_index() { return(absolute_index); }
                     int32                                        get_relative_index() { return(relative_index); }
                     DLL(bnode)                                  *get_path_nodes() { return(path_nodes); }
public     :                                        logical AddPathNode (bnode *bnodeptr );
public     : virtual          OPAImpExp             logical CacheSize (int16 bufnum=AUTO );
public     : virtual          OPAImpExp             logical CanUpdateCollection (logical chknode=YES );
public     : virtual          OPAImpExp             logical CancelBuffer ( );
public     : virtual          OPAImpExp             int16 ChangeBuffer (int16 bufnum=AUTO );
public     : virtual          OPAImpExp             PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                        logical CheckAccess ( );
public     :                                        logical CheckAccess (PIACC accopt );
public     :                                        char CheckAddSet ( );
public     :                                        logical CheckDelEmpty ( );
public     : virtual          OPAImpExp             logical CheckGenAttribute ( );
public     : virtual          OPAImpExp             logical CheckModify ( );
public     : virtual          OPAImpExp             logical CheckPropCtxFunc (char *fnames );
public     : virtual          OPAImpExp             logical CheckStrCtxFunc (char *fnames );
public     : virtual          OPAImpExp             logical CheckUpdateSet (logical no_error );
public     :                                        logical Check_intern ( );
public     : virtual                                logical Close ( );
public     : virtual          OPAImpExp             int8 CompareKey (char *skey1, char *skey2, logical chknode=YES );
public     : virtual          OPAImpExp             int8 CompareSortKey (char *skey1, char *skey2, logical chknode=YES );
public     : virtual          OPAImpExp             logical CopyBReferences (inti *srce_inti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     :                                        logical CopyEventHandler (bnode *bnodeptr );
public     : virtual          OPAImpExp             void *CopyInst (node *srcenode, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical chknode=YES );
public     : virtual          OPAImpExp             void *CopyInst (void *srceinst, smcb *srcesmcb, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical setwpt=NO );
public     : virtual          OPAImpExp             char *CopyInstance (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical setwpt=NO );
public     : virtual          OPAImpExp             char *CopyInstance (node *srce_node, PIREPL db_replace=REPL_none, logical setwpt=NO );
public     :                                        char *CopyInstanceData (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, logical setwpt=NO );
public     : virtual          OPAImpExp             logical CopyReference (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     : virtual          OPAImpExp             int32 CopySet (node *srcenode, logical check_inverse, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, logical chknode=YES );
public     : virtual          OPAImpExp             node *CreateAccessPath (BNFData *parm_bnf, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreateAccessPath (char *prop_path, OperEnvironment *operenv );
public     :                                        logical CreateContext (CTX_Base *highctx );
public     : virtual          OPAImpExp             inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     : virtual          OPAImpExp             node *CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     :                                        void DisableContext ( );
public     :                                        void DisableEventHandling ( );
public     : virtual          OPAImpExp             logical DisableKeyCheck (char chkopt=AUTO );
public     :                                        void EnableContext ( );
public     :                                        void EnableEventHandling ( );
public     : virtual          OPAImpExp             logical EnableKeyCheck (char chkopt=AUTO );
public     :                                        logical Event (DB_Event intevent );
public     : virtual          OPAImpExp             logical ExecPropCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual          OPAImpExp             logical ExecStrCtxFunc (char *fnames, char *w_parms=NULL );
public     :                  OPAImpExp             logical ExecuteEvent (uint32 int_event_id, char *parmstring );
public     : virtual          OPAImpExp             char *ExtractKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual          OPAImpExp             char *ExtractKey (char *keyptr, kcb *kcbptr, void *instptr );
public     : virtual          OPAImpExp             char *ExtractSortKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual          OPAImpExp             logical GenerateEvent (DB_Event intevent );
public     : virtual          OPAImpExp             node **GetBaseNode ( );
public     :                  OPAImpExp             void *GetBuffer (int32 lindx0, int16 direction );
public     :                  OPAImpExp             void *GetBuffer (char *skey, int16 direction );
public     : virtual          OPAImpExp             void *GetBufferInstance (int32 indx0 );
public     : virtual          OPAImpExp             ODABAClient &GetConnectionClient ( );
public     : virtual          OPAImpExp             CTX_Property *GetContext ( );
public     :                                        int32 GetCurrentIndex ( );
public     : virtual          OPAImpExp             Dictionary *GetDictionary ( );
public     : virtual          OPAImpExp             int32 GetDimension (logical chknode=YES );
public     :                                        int32 GetErrorCode ( );
public     : virtual          OPAImpExp             char *GetExtentName ( );
public     : virtual          OPAImpExp             node *GetExtentNode ( );
public     : virtual          OPAImpExp             DBFieldDef *GetFieldDef (logical chknode=YES );
public     : virtual          OPAImpExp             char *GetIdentity (char *id_string, logical first );
public     : virtual          OPAImpExp             CTX_Structure *GetInstContext ( );
public     : virtual          OPAImpExp             kcb *GetKCB ( );
public     :                                        char *GetKeyInstance (inti *intiptr, void *instptr );
public     : virtual          OPAImpExp             int16 GetKeyLength ( );
public     : virtual          OPAImpExp             PIACC GetMode (logical chknode=YES );
public     : virtual          OPAImpExp             ACObject *GetObjectHandle ( );
public     : virtual          OPAImpExp             ACObject **GetObjectHandlePtr ( );
public     :                                        logical GetPIF ( );
public     :                                        char *GetPropPath (char *proppath );
public     : virtual          OPAImpExp             void *GetRelative (int32 indx0, logical chknode=YES );
public     : virtual          OPAImpExp             int32 GetRelativeCount ( );
public     : virtual          OPAImpExp             int32 GetRelativeIndex (logical last_opt, logical chknode=YES );
public     : virtual          OPAImpExp             int16 GetSortKeyLength (logical chknode=YES );
public     : virtual          OPAImpExp             smcb *GetSortKeySMCB ( );
public     :                                        CTX_Structure *GetStructContext ( );
public     :                                        void *Get_attribute (int32 lindx0, logical chknode=YES );
public     :                                        void *Get_optimized (char *skey );
public     : virtual          OPAImpExp             logical HasGenAttribute ( );
public     : virtual          OPAImpExp             logical HasIndex ( );
public     : virtual          OPAImpExp             logical Init (void *instptr );
public     :                  OPAImpExp             logical InitInti (DBStructDef *strdefptr, void *instptr, logical init_nodes=YES );
public     :                                        logical InitTempExtent (DBStructDef *dbstrdef, char *key_name_w=NULL );
public     : virtual          OPAImpExp             logical InstanceInserted ( );
public     :                                        logical IsActive ( );
public     : virtual          OPAImpExp             logical IsClientNode ( );
public     : virtual          OPAImpExp             logical IsCollection ( );
public     :                  OPAImpExp             logical IsContextEnabled ( );
public     : virtual          OPAImpExp             logical IsDirectField ( );
public     :                  OPAImpExp             logical IsDirty ( );
public     : virtual          OPAImpExp             logical IsEnumeration ( );
public     :                                        logical IsInstReadOnly ( );
public     : virtual          OPAImpExp             logical IsMemo ( );
public     :                                        logical IsMoveableInstance ( );
public     : virtual          OPAImpExp             logical IsNewInstance ( );
public     :                                        logical IsPIF ( );
public     : virtual          OPAImpExp             logical IsPositioned ( );
public     : virtual          OPAImpExp             logical IsReadOnly ( );
public     :                                        int8 IsReserved ( );
public     : virtual          OPAImpExp             logical IsSelected ( );
public     : virtual          OPAImpExp             logical IsServerNode ( );
public     : virtual          OPAImpExp             logical IsTypeVariable ( );
public     :                                        logical IsValidForParent ( );
public     : virtual          OPAImpExp             logical IsWrite ( );
public     :                                        logical MarkReadOnly (logical readonly );
public     : virtual          OPAImpExp             void *Modify (logical chknode=YES );
public     :                  OPAImpExp             void *ModifyAttribute (logical chknode=YES );
public     :                                        logical Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     : virtual          OPAImpExp             logical PositionTop ( );
public     : virtual          OPAImpExp             node *PositionTop_intern ( );
public     : virtual          OPAImpExp             logical PrepareGenAttribute ( );
public     : virtual          OPAImpExp             logical ProvGenAttribute ( );
public     : virtual                                void *Provide (char *skey, logical global_add=NO );
public     : virtual                                void *Provide (int32 lindx0, logical global_add=NO );
public     : virtual                                void *Provide (void *datarea, logical global_add=NO );
public     :                                        node *ProvideExtentNode (char *extent_path );
public     : virtual          OPAImpExp             logical ProvideInti (EB_Number entnr );
public     : virtual          OPAImpExp             logical ProvideInti (int16 sid );
public     : virtual          OPAImpExp             int32 ReadBuffer (int32 lindx0, int16 direction );
public     :                                        logical RecoverSelection (int64 obj_id );
public     :                                        void RegisterPathNode ( );
public     :                                        void ReleaseBaseNode ( );
public     : virtual          OPAImpExp             logical ReleaseBuffer ( );
public     :                  OPAImpExp             logical ReleaseProcessEvents (logical emit_opt );
public     :                                        void RemoveField ( );
public     :                                        logical RemovePathNode (bnode *bnodeptr );
public     : virtual                                char *ReserveInstance ( );
public     : virtual          OPAImpExp             logical ResetGenAttribute ( );
public     : virtual                                void ResetInstance ( );
public     : virtual          OPAImpExp             void ResetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void ResetInstanceProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical ResetNode (logical reset_all );
public     : virtual          OPAImpExp             void ResetPropertyEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void ResetPropertyProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical SaveNode (logical switchopt, logical overwrite=NO );
public     : virtual          OPAImpExp             void *SetArea (void *datarea );
public     :                                        logical SetBaseNode (bnode *bnodeptr );
public     :                                        logical SetBaseNode (PropertyHandle &prophdl_ref );
public     : virtual                                void SetCurrentInti (inti *intiptr );
public     : virtual          OPAImpExp             void SetDescription (DBFieldDef *field_def );
public     :                  OPAImpExp             void SetDirty (logical dirty_opt );
public     : virtual          OPAImpExp             logical SetDynLength ( );
public     : virtual          OPAImpExp             void *SetInstance ( );
public     : virtual          OPAImpExp             void SetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetInstanceProcessHandler (EventLink *event_link );
public     :                  OPAImpExp             logical SetInti (inti *intiptr );
public     : virtual          OPAImpExp             logical SetMode (PIACC accopt );
public     : virtual          OPAImpExp             void SetPropertyEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetPropertyProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical SetSortKey (char *keyptr, void *instptr );
public     : virtual          OPAImpExp             logical SetType (char *strnames, logical chknode=YES );
public     :                                        logical SetType_intern (char *strnames );
public     :                                        logical SetupViewOrder ( );
public     : virtual          OPAImpExp             ACObject *StartReadTA ( );
public     : virtual          OPAImpExp             void StopReadTA (logical error_case );
public     : virtual          OPAImpExp             logical Store ( );
public     : virtual          OPAImpExp             logical Switch (int32 indx0 );
public     :                                        void UnregisterPathNode ( );
public     :                                        logical UserEventHandler ( );
public     :                                        node *ValidateExtentNode (node *top_node, node **pcancel_node );
public     : virtual          OPAImpExp             node *ValidateNode (logical crt_opt );
public     :                  OPAImpExp             node *ValidatePosition (logical crt_opt );
public     :                                             bnode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     :                                             bnode ( );
public     :                                             bnode (bnode &bnode_ref );
public     :                                             bnode (ACObject *obhandle, node *nodeptr, char *prop_names, char *typenames, int32 nsid, SDB_RLEV ref_level, uint32 size, int32 precision, uint32 dimension );
public     :                                        bnode *get_bnodenode ( );
public     :                                        smcb *get_idkey_smcb ( );
public     :                                        smcb *get_sortkey_smcb ( );
public     :                                        logical iChanged ( );
public     :                                        logical iCheck ( );
public     :                                        bnode *iRefresh (logical crt_opt, node *parent );
public     :                                        bnode *iReopen (node *parent );
public     :                                        void set_absolute_index (int32 lindx0 );
public     :                                        void set_base_node (node *nodeptr );
public     :                                        void set_base_reference (node *nodeptr );
public     :                                        void set_has_event_handler (logical has_evthdl );
public     :                                        void set_nodeacc (PIACC accopt );
public     :                                        void set_nodewrit (logical writeopt );
public     :                                        void set_objid (int64 obj_id );
public     :                                        void set_relative_index (int32 lindx0 );
public     : virtual                                     ~bnode ( );
public     :                                        binti *get_bnodeinst ( ){

  return ( nodeinst && nodeinst->stscnof() 
           ? ((binti *)nodeinst) : NULL );

}

public     :                                        void set_registered (logical reg_opt ){

  registered = reg_opt;

}

};

#pragma pack()
#endif
