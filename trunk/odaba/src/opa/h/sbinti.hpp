/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    binti

\brief    


\date     $Date: 2006/07/16 14:23:28,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   binti_HPP
#define   binti_HPP

class     binti;

#define  Bintiptr                                  ((binti *)intiptr)
#include  <sDLL.h>
class     EventLink;
class     ACGenericAttr;
class     CTX_Base;
class     CTX_Property;
class     CTX_Structure;
class     DBStructDef;
class     EventLink;
class     EventLinkList;
class     ProcessEventHandler;
class     PropertyHandle;
class     StructAccess;
class     binti;
class     bnode;
class     exd;
class     kcb;
class     node;
#include  <cDB_Event.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sEB_Number.hpp>
#include  <sinti.hpp>
#include  <snodelist.hpp>
#pragma pack(8)

class  binti :public inti
{
protected  :         nodelist                                     node_base;                                                 // 
protected  :         nodelist                                     node_refr;                                                 // 
protected  :         nodelist                                     node_rshp;                                                 // 
protected  :         nodelist                                     node_genattr;                                              // 
protected  :         nodelist                                     node_tref;                                                 // Sub-nodes
protected  :         char                                        *isel_init;                                                 // 
protected  :         logical                                      cluster_crtopt;                                            // 
protected  :         CTX_Structure                               *context;                                                   // 
protected  :         int32                                        identity_pos;                                              // 
protected  :         PropertyHandle                              *inst_field;                                                // 
protected  :         int64                                        objid;                                                     // 
protected  :         EventLinkList                               *event_handler;                                             // 
protected  :         ProcessEventHandler                         *proc_event_handler;                                        // 
protected  :         int32                                        weak_typed_offset;                                         // 

public     :
                     nodelist                                    &get_node_base() { return(node_base); }
                     nodelist                                    &get_node_refr() { return(node_refr); }
                     nodelist                                    &get_node_rshp() { return(node_rshp); }
                     nodelist                                    &get_node_genattr() { return(node_genattr); }
                     nodelist                                    &get_node_tref() { return(node_tref); }
                     char                                        *get_isel_init() { return(isel_init); }
                     logical                                      get_cluster_crtopt() { return(cluster_crtopt); }
                     CTX_Structure                               *get_context() { return(context); }
                     int32                                        get_identity_pos() { return(identity_pos); }
                     PropertyHandle                              *get_inst_field() { return(inst_field); }
                     int64                                        get_objid() { return(objid); }
                     EventLinkList                               *get_event_handler() { return(event_handler); }
                     ProcessEventHandler                         *get_proc_event_handler() { return(proc_event_handler); }
                     int32                                        get_weak_typed_offset() { return(weak_typed_offset); }
public     : virtual          OPAImpExp             logical AddGenericRef (char *fldname );
public     : virtual          OPAImpExp             logical Cancel ( );
public     : virtual          OPAImpExp             logical ChangeMode (PIACC accopt );
public     :                                        logical CheckAddReference ( );
public     :                                        logical CheckDelEmpty ( );
public     : virtual          OPAImpExp             logical Close ( );
public     : virtual          OPAImpExp             int16 Copy (inti *srceinti, node *nodeptr, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     :                                        logical CopyBReferences (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     : virtual          OPAImpExp             logical CopyBufferInstance (inti *intiptr );
public     :                                        logical CopyEventHandler (binti *bintiptr );
public     :                                        logical CopyGenAttr (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     :                                        logical CopyGlobalInst (binti *bintiptr );
public     :                                        logical CopyOReferences (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     :                                        logical CopySubnodes (binti *bintiptr );
public     : virtual          OPAImpExp             logical DelGenericRef (char *fldname );
public     :                                        logical DeleteInverseRef ( );
public     : virtual          OPAImpExp             logical DeleteReferences (char *extnames, logical is_root, int16 delopt=AUTO, logical del_dep=YES );
public     :                                        logical DeleteRelationships (char *extnames, logical is_root, int16 delopt=AUTO, logical del_dep=YES );
public     : virtual          OPAImpExp             void DeleteSubNodes ( );
public     :                                        void DisableContext ( );
public     :                                        void EnableContext ( );
public     :                                        logical ExecuteFunction (char *fnames, logical check_opt=NO );
public     :                                        void GenerateCSEvent (CSA_Events event_id, int64 identity, node *nodeptr );
public     :                                        logical GenerateEvent (DB_Event intevent );
public     :                                        void GenerateProcessEvent (DB_Event intevent );
public     :                                        binti *GetBaseBinti (char *strname, logical shared_only );
public     : virtual          OPAImpExp             EB_Number GetClusterNumber ( );
public     : virtual          OPAImpExp             CTX_Structure *GetContext ( );
public     :                                        exd *GetEXD ( );
public     : virtual          OPAImpExp             char *GetExtInst ( );
public     :                  OPAImpExp             ACGenericAttr *GetGenAttrNode (char *fldnames, CTX_Property *propctx );
public     :                  OPAImpExp             char *GetGlobalInstanceIdentity (char *id_string );
public     : virtual          OPAImpExp             EB_Number *GetIdentity ( );
public     : virtual          OPAImpExp             int16 GetMBNumber ( );
public     : virtual          OPAImpExp             char *GetOldInst (void *oldinst );
public     :                                        bnode *GetParentNode ( );
public     : virtual          OPAImpExp             node **GetPropNodePtr (char *prop_names, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             node **GetPropNodePtr (char *prop_names, char *proppath );
public     : virtual          OPAImpExp             StructAccess *GetStructAccess ( );
public     :                  OPAImpExp             node **GetSubNodePtr (char *prop_names, CTX_Property *highprop_ctx );
public     :                                        logical HasBaseAutoIdKey ( );
public     :                                        logical HasGenAttribute ( );
public     :                  OPAImpExp             logical Init (node *nodeptr, void *mspool, DBStructDef *strdefptr, void *instptr );
public     :                                        logical InitGenAttr (void *initinst=NULL, logical set_init=YES );
public     :                  OPAImpExp             void InitInit ( );
public     : virtual          OPAImpExp             logical Initialize (void *initinst=NULL, logical set_init=YES );
public     : virtual          OPAImpExp             logical IsPositioned ( );
public     : virtual          OPAImpExp             logical Modify ( );
public     : virtual          OPAImpExp             logical MoveInstance (inti *intiptr );
public     :                                        logical OpenEvent ( );
public     :                                        logical PrepareGenAttribute ( );
public     :                  OPAImpExp             logical ProcessEvent (DB_Event intevent );
public     : virtual          OPAImpExp             logical ProvGenAttribute ( );
public     :                                        PropertyHandle *ProvideInstField ( );
public     :                                        logical ReadEvent ( );
public     :                                        logical RecursiveEvents (DB_Event intevent );
public     : virtual          OPAImpExp             void Release ( );
public     :                                        logical ReleaseProcessEvents (logical emit_opt );
public     :                                        logical RemoveReferences (inti *srce_inti );
public     : virtual          OPAImpExp             void Reset ( );
public     :                                        void ResetEventHandler (EventLink *event_link );
public     :                                        void ResetGUID ( );
public     :                                        logical ResetGenAttribute ( );
public     :                                        logical ResetIdentity ( );
public     :                                        logical ResetInitializeEvent ( );
public     : virtual          OPAImpExp             void ResetInitialized ( );
public     :                                        void ResetInstanceProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical ResetNodes ( );
public     :                                        void ResetOldBaseInst ( );
public     :                  OPAImpExp             logical ResetReferences ( );
public     :                                        logical ResetSubNodes ( );
public     :                  OPAImpExp             logical ResetSubNodesRecursive ( );
public     : virtual          OPAImpExp             logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     :                                        logical SaveGenAttr (logical switchopt, logical overwrite=NO );
public     :                                        char SetAutoIdent (kcb *kcbptr, int attrtype );
public     : virtual          OPAImpExp             void SetClusterNumber (EB_Number clnumb );
public     :                                        void SetEventHandler (EventLinkList *event_links );
public     :                                        logical SetGenAttrMod (void *initinst=NULL );
public     :                                        void SetIdentity ( );
public     :                                        logical SetInitialize ( );
public     :                                        logical SetInitializeEvent ( );
public     : virtual          OPAImpExp             void SetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetInstanceProcessHandler (bnode *bnodeptr, EventLink *event_link );
public     : virtual          OPAImpExp             void SetMBNumber (int16 mbnumber );
public     : virtual          OPAImpExp             void SetObjectID (int64 obj_id );
public     :                                        void SetOldBaseInst ( );
public     :                                        void SetProcEventHandler (ProcessEventHandler *peh_ptr );
public     :                                        logical SetReadOnly (logical readonly );
public     : virtual          OPAImpExp             logical SetRefContext (inti *intiptr );
public     : virtual          OPAImpExp             void SetStructAccess (StructAccess *struct_access );
public     :                                        void SetupInst (logical update );
public     :                                        logical SetupNewInst (logical global_add=NO );
public     :                                        logical SetupReadOnly ( );
public     :                                        logical SetupSubNodes (logical create_ref, logical for_event_handling );
public     : virtual          OPAImpExp             logical StructAttrEvents (DB_Event intevent );
public     : virtual          OPAImpExp             logical StructureEvents (DB_Event intevent );
public     :                  OPAImpExp             void after_add ( );
public     :                  OPAImpExp             logical before_add ( );
public     :                  OPAImpExp                  binti (node *nodeptr, void *mspool, DBStructDef *strdefptr, void *instptr, logical crt_opt );
public     :                  OPAImpExp                  binti ( );
public     :                                        void set_objid (int64 obj_id );
public     : virtual          OPAImpExp                  ~binti ( );
public     :                                        void set_cluster_crt ( ){

  cluster_crtopt = YES;

}

};

#pragma pack()
#endif
