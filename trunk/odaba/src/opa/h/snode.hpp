/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    node

\brief    Access node


\date     $Date: 2006/08/29 20:17:52,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   node_HPP
#define   node_HPP

class     node;

#define  NODE_ID                                   1162104654
#define  NODE_IDD                                  1162104608
#define  RET_STR_LEN                               512
#include  <sDLL.h>
class     PropertyHandle;
#include  <sDLO.h>
class     PropertyHandle;
#include  <sDLL.h>
class     node;
class     ACExtend;
class     ACObject;
class     BNFData;
class     BNFExpData;
class     CSA_Handle;
class     CTX_Base;
class     CTX_Property;
class     CTX_Structure;
class     DBFieldDef;
class     DBIndex;
class     DBStructDef;
class     Dictionary;
class     EventLink;
class     OPBase;
class     OperEnvironment;
class     Operation;
class     ParmList;
class     PropertyHandle;
class     SDB_Member;
class     SimpleAction;
class     bnode;
class     fmcb;
class     guid;
class     inti;
class     kcb;
class     nodelist;
class     ref;
class     smcb;
#include  <cDB_Event.h>
#include  <cFunctionTypes.h>
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cPIADEF.h>
#include  <cPIREPL.h>
#include  <cSDB_RLEV.h>
#include  <sEB_Number.hpp>
#include  <sNString.hpp>
#include  <sODABAClient.hpp>
#include  <sTypeKey.hpp>
#include  <sdbf.hpp>
#include  <sdttm.hpp>
#include  <snode.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  node :public sts,
public dbf
{
protected  :         int32                                        nodeidnt;                                                  // 
protected  :         node                                        *nodenode;                                                  // 
protected  :         inti                                        *nodeinst;                                                  // 
protected  :         NodeTypes                                    nodetype;                                                  // 
protected  :         char                                        *prop_path;                                                 // 
protected  :         node                                        *origin;                                                    // 
protected  :         DLL(node)                                   *copies;                                                    // 
protected  :         NString                                      nstring;                                                   // 
protected  :         int8                                         global_instance;                                           // 
protected  :         char                                        *key_area;                                                  // 
protected  :         node                                        *parent;                                                    // 
protected  :         node                                        *ph;                                                        // 
protected  :         Operation                                   *auto_selection;                                            // 
protected  :         char                                        *auto_key;                                                  // 
protected  :         int32                                        auto_position;                                             // 
protected  :         logical                                      auto_provide;                                              // 
protected  :         nodelist                                    *node_meta;                                                 // 

public     :
                     int32                                        get_nodeidnt() { return(nodeidnt); }
                     node                                        *get_nodenode() { return(nodenode); }
                     inti                                        *get_nodeinst() { return(nodeinst); }
                     NodeTypes                                    get_nodetype() { return(nodetype); }
                     char                                        *get_prop_path() { return(prop_path); }
                     node                                        *get_origin() { return(origin); }
                     DLL(node)                                   *get_copies() { return(copies); }
                     NString                                     &get_nstring() { return(nstring); }
                     int8                                         get_global_instance() { return(global_instance); }
                     node                                        *get_parent() { return(parent); }
                     node                                        *get_ph() { return(ph); }
                     Operation                                   *get_auto_selection() { return(auto_selection); }
                     char                                        *get_auto_key() { return(auto_key); }
                     int32                                        get_auto_position() { return(auto_position); }
                     logical                                      get_auto_provide() { return(auto_provide); }
                     nodelist                                    *get_node_meta() { return(node_meta); }
public     : virtual          OPAImpExp             void *Add (int32 lindx0, logical global_add=NO );
public     : virtual          OPAImpExp             void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     :                                        logical AddCopy (node *nodeptr );
public     :                                        logical AddMetaNode (node *nodeptr );
public     : virtual          OPAImpExp             logical AddReference (node *srcenode, int32 lindx0 );
public     :                                        logical AllocKeyArea ( );
public     :                                        logical AllocateArea ( );
public     :                  OPAImpExp             logical AppendString (char *string );
public     :                                        logical AutoLocate (logical chknode=YES );
public     :                  OPAImpExp             logical AutoPosition ( );
public     :                                        guid *BuildGUID (guid *_guid );
public     : virtual          OPAImpExp             logical CacheSize (int16 bufnum=AUTO );
public     : virtual          OPAImpExp             logical CanUpdateCollection (logical chknode=YES );
public     : virtual          OPAImpExp             logical Cancel (logical chknode=YES );
public     : virtual          OPAImpExp             logical CancelBuffer ( );
public     : virtual          OPAImpExp             logical CancelNode ( );
public     : virtual          OPAImpExp             int16 ChangeBuffer (int16 bufnum=AUTO );
public     : virtual          OPAImpExp             PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual          OPAImpExp             logical Check (logical autoini=NO, logical acccheck=YES );
public     :                  OPAImpExp             logical CheckDescription ( );
public     : virtual          OPAImpExp             logical CheckGenAttribute ( );
public     :                                        FunctionTypes CheckInlineExpression (smcb *smcbptr, char *path );
public     : virtual          OPAImpExp             logical CheckModify ( );
public     :                                        logical CheckUpdate ( );
public     : virtual          OPAImpExp             logical CheckUpdateSet (logical no_error );
public     : virtual          OPAImpExp             logical CheckWProtect ( );
public     : virtual          OPAImpExp             logical Close ( );
public     :                  OPAImpExp             char Compare (node *srce_node );
public     : virtual          OPAImpExp             int8 CompareKey (char *skey1, char *skey2, logical chknode=YES );
public     : virtual          OPAImpExp             int8 CompareSortKey (char *skey1, char *skey2, logical chknode=YES );
public     : virtual          OPAImpExp             logical Contains (char *reg_string, logical case_opt=YES );
public     :                                        int16 ConversionError (void *srceinst, smcb *srcesmcb );
public     : virtual                                logical CopyBReferences (inti *srce_inti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     : virtual          OPAImpExp             void *CopyInst (node *srcenode, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical chknode=YES );
public     : virtual          OPAImpExp             void *CopyInst (void *srceinst, smcb *srcesmcb, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical setwpt=NO );
public     : virtual          OPAImpExp             char *CopyInstance (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical setwpt=NO );
public     : virtual          OPAImpExp             char *CopyInstance (node *srce_node, PIREPL db_replace=REPL_none, logical setwpt=NO );
public     : virtual          OPAImpExp             logical CopyReference (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     : virtual          OPAImpExp             int32 CopySet (node *srcenode, logical check_inverse, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, logical chknode=YES );
public     : virtual          OPAImpExp             node *CreateAccessPath (BNFData *parm_bnf, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreateAccessPath (char *prop_path, OperEnvironment *operenv );
public     :                                        node *CreateCopy ( );
public     : virtual          OPAImpExp             node *CreateCopyNode ( );
public     : virtual          OPAImpExp             inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     : static                                 node *__cdecl CreateOperationNode (ACObject *obhandle, node *nodeptr, ST_OpCodes op_type, char *rule, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     : static                                 node *__cdecl CreateOperationNode (ACObject *obhandle, node *nodeptr, ST_OpCodes op_type, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     : virtual          OPAImpExp             node *CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreatePathNode (char *prop_path, OperEnvironment *operenv );
public     : virtual                                node *CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     : virtual          OPAImpExp             node *CreateViewNode (char *expression, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreateViewNode (BNFData *bnf_data, OperEnvironment *operenv );
public     : virtual          OPAImpExp             logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual          OPAImpExp             logical Delete (char *skey, logical chknode=YES );
public     : virtual          OPAImpExp             logical DeleteIndex (logical gen_events );
public     : virtual          OPAImpExp             logical DeleteIndexEntry ( );
public     : virtual          OPAImpExp             logical DeleteSet (logical chknode=YES, logical del_dep=YES );
public     : virtual          OPAImpExp             logical DeleteSetIndexes ( );
public     : virtual          OPAImpExp             logical DisableKeyCheck (char chkopt=AUTO );
public     :                                        logical Distinct (node *nodeptr );
public     : virtual          OPAImpExp             void *Duplicate (char *keyptr, PIREPL db_replace=REPL_none, logical chknode=YES );
public     : virtual          OPAImpExp             logical EnableKeyCheck (char chkopt=AUTO );
public     : virtual          OPAImpExp             logical ExecPropCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual          OPAImpExp             logical ExecStrCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual          OPAImpExp             logical Execute (ParmList *parmlist );
public     : virtual          OPAImpExp             logical Exist ( );
public     : virtual          OPAImpExp             char *ExtractKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual          OPAImpExp             char *ExtractKey (char *keyptr, kcb *kcbptr, void *instptr );
public     : virtual          OPAImpExp             char *ExtractSortKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual          OPAImpExp             logical FillAll (void *instptr );
public     : virtual          OPAImpExp             logical FillData (void *instptr );
public     :                                        fmcb *FindSource (inti *srce_inti, int32 *offset_ptr, node **pp_srce_node=NULL );
public     : virtual          OPAImpExp             char *FirstKey (logical chknode=YES );
public     :                  OPAImpExp             char *Format (char *fstring, char **plist, int32 count );
public     :                                        char *GUIDToString (char *guid_string, guid *_guid );
public     : virtual          OPAImpExp             logical GenerateEvent (DB_Event intevent );
public     : virtual          OPAImpExp             void *Get (int32 indx0, logical chknode=YES );
public     : virtual          OPAImpExp             void *Get (char *skey, logical chknode=YES );
public     : virtual          OPAImpExp             void *Get ( );
public     :                  OPAImpExp             void *GetArea (logical chknode=YES );
public     :                  OPAImpExp             void *GetArea (char *prop_path, logical chknode=YES );
public     : virtual          OPAImpExp             int32 GetAt (int32 lindx0, int16 direction, logical chknode=YES );
public     :                  OPAImpExp             char *GetAttribute (int32 indx0, logical full_path, logical generic=YES );
public     : virtual          OPAImpExp             node **GetBaseNode ( );
public     : virtual          OPAImpExp             void *GetBufferInstance (int32 indx0 );
public     : virtual          OPAImpExp             int32 GetCollectionID ( );
public     :                                        ODABAClient &GetConnectionClient ( );
public     : virtual          OPAImpExp             CTX_Property *GetContext ( );
public     : virtual          OPAImpExp             int32 GetCount (logical chknode=YES );
public     :                  OPAImpExp             int32 GetCurrentIndex ( );
public     :                  OPAImpExp             char *GetCurrentType ( );
public     : virtual          OPAImpExp             DBStructDef *GetCurrentTypeDef ( );
public     : virtual          OPAImpExp             DBIndex *GetDBIndex (char *key_name_w=NULL );
public     :                  OPAImpExp             dbdt GetDate (char *prop_path, logical chknode=YES );
public     :                  OPAImpExp             dbdt GetDate (fmcb *fmcbptr, void *datarea );
public     :                  OPAImpExp             dttm GetDateTime (char *prop_path, logical chknode=YES );
public     :                  OPAImpExp             dttm GetDateTime (fmcb *fmcbptr, void *datarea );
public     : virtual          OPAImpExp             Dictionary *GetDictionary ( );
public     : virtual          OPAImpExp             int32 GetDimension (logical chknode=YES );
public     :                  OPAImpExp             double GetDouble (char *prop_path, logical chknode=YES );
public     :                  OPAImpExp             double GetDouble (fmcb *fmcbptr, void *datarea );
public     : virtual                                void *GetExtInst (char *extinst );
public     : virtual          OPAImpExp             char *GetExtentName ( );
public     : virtual          OPAImpExp             fmcb *GetFMCB (char *prop_path, int32 *offset_ptr );
public     : virtual          OPAImpExp             DBFieldDef *GetFieldDef (logical chknode=YES );
public     : virtual          OPAImpExp             char *GetFuncResult ( );
public     :                  OPAImpExp             char *GetGUID (logical any_id=YES );
public     : virtual          OPAImpExp             int GetGenAttrType (char *fldnames );
public     : virtual          OPAImpExp             int GetGenOrderType ( );
public     : virtual          OPAImpExp             EB_Number GetGlobalID ( );
public     : virtual          OPAImpExp             node **GetHighPIPointer ( );
public     : virtual          OPAImpExp             EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual          OPAImpExp             EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual          OPAImpExp             char *GetIdentity (char *id_string, logical first );
public     :                                        void *GetInitInstance (logical set_init=YES );
public     : virtual          OPAImpExp             CTX_Structure *GetInstContext ( );
public     :                                        DBFieldDef *GetInstFieldDef ( );
public     : virtual          OPAImpExp             int16 GetInstModCount ( );
public     :                  OPAImpExp             int32 GetInt (char *prop_path, logical chknode=YES );
public     :                  OPAImpExp             int32 GetInt (fmcb *fmcbptr, void *datarea );
public     : virtual          OPAImpExp             kcb *GetKCB ( );
public     : virtual          OPAImpExp             char *GetKey (int32 lindx0, logical chknode=YES );
public     :                                        char *GetKeyArea ( );
public     : virtual          OPAImpExp             int16 GetKeyLength ( );
public     : virtual          OPAImpExp             smcb *GetKeySMCB (char *key_name_w=NULL );
public     :                                        node *GetMetaNode (char *prop_name );
public     :                  OPAImpExp             node **GetMetaNodePtr (char *prop_name );
public     : virtual                                PIACC GetMode (logical chknode=YES );
public     : virtual          OPAImpExp             node *GetNode (logical autoini=NO );
public     : virtual          OPAImpExp             node **GetNodePtr (char *prop_path, logical *is_transient=NULL, logical supress_struct_error=NO );
public     : virtual          OPAImpExp             node **GetNodePtr (char *prop_path, OperEnvironment *operenv, FunctionTypes &path_type, PIACC accopt );
public     : virtual          OPAImpExp             OPBase *GetOPNode ( );
public     : virtual          OPAImpExp             ACObject *GetObjectHandle ( );
public     : virtual          OPAImpExp             ACObject **GetObjectHandlePtr ( );
public     :                                        void *GetOrigin ( );
public     :                                        PropertyHandle *GetPH ( );
public     :                                        BNFData *GetPathBNF (char *prop_path, char **expr_dup );
public     : virtual          OPAImpExp             PropertyHandle *GetPathElement (char *path_element );
public     :                                        char *GetPathString ( );
public     :                                        char *GetPathString (NString &rstring );
public     : virtual          OPAImpExp             PIADEF GetPrivilege ( );
public     :                                        node *GetPropNode (char *prop_names, CTX_Property *highprop_ctx );
public     :                                        node *GetPropNode (char *prop_names, char *proppath );
public     : virtual          OPAImpExp             node **GetPropNodePtr (char *prop_names, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             node **GetPropNodePtr (char *prop_names, char *proppath );
public     : virtual          OPAImpExp             int16 GetRefModCount ( );
public     :                  OPAImpExp             char *GetReference (int32 indx0, logical full_path, logical generic=YES );
public     : virtual          OPAImpExp             void *GetRelative (int32 indx0, logical chknode=YES );
public     : virtual          OPAImpExp             int32 GetRelativeCount ( );
public     : virtual          OPAImpExp             int32 GetRelativeIndex (logical last_opt, logical chknode=YES );
public     :                  OPAImpExp             smcb *GetSMCB (logical chknode=YES );
public     : virtual          OPAImpExp             char *GetSelectedKey ( );
public     :                  OPAImpExp             uint32 GetSizeOf ( );
public     :                  OPAImpExp             char *GetSortKey ( );
public     : virtual          OPAImpExp             int16 GetSortKeyLength (logical chknode=YES );
public     : virtual          OPAImpExp             smcb *GetSortKeySMCB ( );
public     : virtual          OPAImpExp             char *GetString (char *prop_path, logical chknode=YES );
public     : virtual          OPAImpExp             char *GetString (fmcb *fmcbptr, void *datarea );
public     : virtual          OPAImpExp             char *GetString ( );
public     :                                        DBStructDef *GetStructDef ( );
public     :                  OPAImpExp             node *GetSubNode (char *prop_names, CTX_Property *highprop_ctx );
public     :                  OPAImpExp             node **GetSubNodePtr (char *prop_names, CTX_Property *highprop_ctx );
public     :                  OPAImpExp             dbtm GetTime (char *prop_path, logical chknode=YES );
public     :                  OPAImpExp             dbtm GetTime (fmcb *fmcbptr, void *datarea );
public     :                  OPAImpExp             char *GetType ( );
public     :                  OPAImpExp             TypeKey &GetTypeKey ( );
public     :                                        void *GetValue (int32 lindx0 );
public     :                  OPAImpExp             uint16 GetVersion ( );
public     :                                        NodeTypes Get_data_nodetype ( );
public     : virtual          OPAImpExp             logical Group (node *nodeptr, logical distinct=NO );
public     : virtual          OPAImpExp             logical HasFilter ( );
public     : virtual          OPAImpExp             logical HasGenAttribute ( );
public     : virtual          OPAImpExp             logical HasIndex ( );
public     :                                        logical HasWorkspace ( );
public     :                                        logical Inherits (char *strnames );
public     : virtual          OPAImpExp             logical Init (void *instptr );
public     :                  OPAImpExp             logical InitInstance (void *instptr );
public     :                  OPAImpExp             logical InitInti (DBStructDef *strdefptr, void *instptr, logical init_nodes=YES );
public     : virtual          OPAImpExp             logical InitReference ( );
public     : virtual          OPAImpExp             logical Initialize (void *instptr, logical set_init=YES );
public     :                  OPAImpExp             logical Initialize_intern (void *instptr, logical set_init=YES );
public     :                  OPAImpExp             logical InsertString (char *string, int32 position );
public     : virtual          OPAImpExp             logical InstanceInserted ( );
public     :                  OPAImpExp             char *InstanceToString (char *string_sep, char *field_sep, char *block_sep, char *empty_string, logical skip_trans=NO );
public     : virtual          OPAImpExp             logical Intersect (node *nodeptr, char sk_opt=YES );
public     : virtual          OPAImpExp             logical Intersect (PropertyHandle **pi_liste, int32 count, char sk_opt=YES );
public     :                                        logical IsACShareBase ( );
public     : virtual          OPAImpExp             logical IsAttribute ( );
public     : virtual          OPAImpExp             logical IsAutoPosition ( );
public     :                  OPAImpExp             logical IsBasedOn (char *strnames );
public     : virtual          OPAImpExp             logical IsBasetypeProperty ( );
public     : virtual          OPAImpExp             logical IsClientNode ( );
public     : virtual          OPAImpExp             logical IsCollection ( );
public     : virtual          OPAImpExp             logical IsCopyNode ( );
public     : virtual                                logical IsDirectField ( );
public     : virtual          OPAImpExp             logical IsEnumeration ( );
public     : virtual          OPAImpExp             logical IsGenericAttribute ( );
public     :                                        logical IsGlobalInstance ( );
public     :                  OPAImpExp             logical IsInitInstance ( );
public     : virtual          OPAImpExp             logical IsLocalNode ( );
public     : virtual          OPAImpExp             logical IsMemo ( );
public     :                                        logical IsMetaAttribute ( );
public     :                                        logical IsModified ( );
public     : virtual          OPAImpExp             logical IsNewInstance ( );
public     : virtual          OPAImpExp             logical IsNewReference (logical create_ref );
public     :                  OPAImpExp             logical IsPathExpression ( );
public     : virtual          OPAImpExp             logical IsPositioned ( );
public     : virtual          OPAImpExp             logical IsReadOnly ( );
public     : virtual          OPAImpExp             logical IsSelected ( );
public     : virtual          OPAImpExp             logical IsSensitive ( );
public     : virtual          OPAImpExp             logical IsServerNode ( );
public     :                  OPAImpExp             logical IsText ( );
public     :                                        logical IsTransient ( );
public     : virtual                                logical IsTypeVariable ( );
public     :                                        logical IsUndefined ( );
public     :                                        logical IsUserHandle ( );
public     :                  OPAImpExp             logical IsValid ( );
public     :                  OPAImpExp             logical IsVariableType (logical chknode=YES );
public     : virtual          OPAImpExp             logical IsWrite ( );
public     : virtual          OPAImpExp             char *KeyToString (char *key_string, char *key_val, char *key_name_w=NULL );
public     : virtual          OPAImpExp             logical Locate (EB_Number entnr, logical read_opt=YES );
public     :                  OPAImpExp             logical LocateIndex (int32 lindx0, logical chknode=YES );
public     : virtual          OPAImpExp             logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                  OPAImpExp             logical LocatePIRef (PropertyHandle *pibptr );
public     :                  OPAImpExp             logical LocatePath ( );
public     : virtual          OPAImpExp             logical Lock ( );
public     : virtual          OPAImpExp             logical LockSet (logical chknode=YES );
public     : virtual          OPAImpExp             logical Minus (node *node1, node *node2, char sk_opt=YES );
public     : virtual          OPAImpExp             logical Minus (node *nodeptr, char sk_opt=YES );
public     : virtual          OPAImpExp             void *Modify (logical chknode=YES );
public     : virtual          OPAImpExp             void *Move (node *srcenode, PIREPL db_replace=REPL_none, char *w_newkey=NULL, logical chknode=YES );
public     : virtual          OPAImpExp             logical MoveDown ( );
public     : virtual          OPAImpExp             logical MoveUp ( );
public     : virtual          OPAImpExp             char *NextKey (char *skey, int16 switch_level=0 );
public     :                                        void OBHOutputResult (char *string );
public     :                                        logical Open (node *nodeptr, DBFieldDef *dbfield_ptr );
public     :                                        logical Open ( );
public     :                                        void OutputResult (char *string );
public     : virtual          OPAImpExp             node *PathCreateCopy (node *top_node, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     : virtual          OPAImpExp             int32 Position (int32 count, logical chknode=YES );
public     :                                        void *PositionExpression (char *expr_string );
public     :                                        void *PositionExpression (char *expr_string, char expr_char );
public     : virtual                                logical PositionTop ( );
public     : virtual          OPAImpExp             node *PositionTop_intern ( );
public     : virtual          OPAImpExp             logical PrepareGenAttribute ( );
public     : virtual          OPAImpExp             logical ProvGenAttribute ( );
public     : virtual          OPAImpExp             void *Provide (char *skey, logical global_add=NO );
public     : virtual          OPAImpExp             void *Provide (int32 lindx0, logical global_add=NO );
public     : virtual          OPAImpExp             void *Provide (void *datarea, logical global_add=NO );
public     :                                        void *ProvideArea ( );
public     :                  OPAImpExp             char *ProvideGUID (logical chknode=YES );
public     : virtual          OPAImpExp             int32 ReadBuffer (int32 lindx0, int16 direction );
public     : virtual          OPAImpExp             logical Refresh ( );
public     : virtual          OPAImpExp             logical RegisterHandle (CSA_Handle *cs_handle );
public     : virtual          OPAImpExp             logical ReleaseBuffer ( );
public     :                                        void ReleaseInti ( );
public     :                                        logical RemoveCopy (node *nodeptr );
public     : virtual                                logical RemoveFromCollection ( );
public     :                                        logical RemoveMetaNode (node *nodeptr );
public     :                  OPAImpExp             logical RemoveString (char *string, int32 position, uint16 len );
public     : virtual          OPAImpExp             logical Rename (char *identkey, logical chknode=YES );
public     :                                        logical RenameHandle (char *var_name );
public     : virtual                                logical RepairIndex (char *key_name, char *attrstr );
public     :                  OPAImpExp             logical Replace (char *old_str, char *new_str );
public     :                  OPAImpExp             logical ReplaceSysVar ( );
public     : virtual          OPAImpExp             logical Reset ( );
public     :                                        void ResetCopyNodes (node *node_ptr, int64 obj_id );
public     : virtual          OPAImpExp             logical ResetExpression ( );
public     : virtual          OPAImpExp             logical ResetGenAttribute ( );
public     :                  OPAImpExp             void ResetInitInstance ( );
public     : virtual                                void ResetInstance ( );
public     : virtual          OPAImpExp             void ResetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void ResetInstanceProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical ResetNode (logical reset_all );
public     :                  OPAImpExp             void ResetOnError ( );
public     :                                        logical ResetPIRef (PropertyHandle *pibptr );
public     : virtual          OPAImpExp             void ResetPropertyEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void ResetPropertyProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical ResetReference ( );
public     : virtual          OPAImpExp             logical ResetWProtect ( );
public     : virtual          OPAImpExp             logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual          OPAImpExp             logical SaveKey (char *savekey, char *skey );
public     : virtual          OPAImpExp             logical SaveNode (logical switchopt, logical overwrite=NO );
public     : virtual          OPAImpExp             logical Select (node *nodeptr, char *expression, int32 min_inst=AUTO );
public     : virtual          OPAImpExp             logical Set (node *nodeptr );
public     : virtual          OPAImpExp             logical SetAction (SimpleAction *simple_action );
public     : virtual          OPAImpExp             void *SetArea (void *datarea );
public     :                                        void SetAutoLocate (int32 auto_pos, char *keyptr, logical provide );
public     :                                        logical SetAutoLocateExpression (char *expression, OperEnvironment *operenv, logical provide );
public     : virtual          OPAImpExp             logical SetContextVariables (char *context_string );
public     : virtual          OPAImpExp             void SetCurrentInti (inti *intiptr );
public     : virtual          OPAImpExp             void SetDescription (DBFieldDef *field_def );
public     : virtual          OPAImpExp             logical SetDynLength ( );
public     : virtual          OPAImpExp             logical SetExpression (char *expression );
public     : virtual          OPAImpExp             logical SetExpression (BNFData *bnf_data );
public     :                                        void SetGUID ( );
public     : virtual          OPAImpExp             logical SetGenAttribute (char *fldnames, int attrtype, char *attrstr );
public     : virtual          OPAImpExp             logical SetGenAttribute (int attrtype, char *attrstr );
public     : virtual          OPAImpExp             logical SetGenAttribute ( );
public     : virtual          OPAImpExp             logical SetInstAction (SimpleAction *simple_action );
public     : virtual          OPAImpExp             void *SetInstance (void *instptr );
public     : virtual          OPAImpExp             void SetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetInstanceProcessHandler (EventLink *event_link );
public     :                                        void SetIntiArea (void *instptr );
public     :                  OPAImpExp             logical SetKey (kcb *kcbptr, char *keyptr, void *instptr );
public     :                  OPAImpExp             logical SetKey (char *keyptr, void *instptr );
public     :                                        char *SetKeyArea (char *skey, int16 klen );
public     :                  OPAImpExp             void SetMod ( );
public     : virtual          OPAImpExp             logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                  OPAImpExp             void SetPIRef (PropertyHandle *pibptr );
public     :                                        logical SetPathExpression (char *expr_string );
public     :                                        logical SetPathExpression (char *expr_string, char expr_char );
public     : virtual          OPAImpExp             void SetPropertyEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetPropertyProcessHandler (EventLink *event_link );
public     : virtual          OPAImpExp             logical SetSortKey (char *keyptr, void *instptr );
public     : virtual          OPAImpExp             logical SetTransientProperty (node *nodeptr );
public     : virtual          OPAImpExp             logical SetType (char *strnames, logical chknode=YES );
public     :                                        logical SetValue (node *nodeptr, logical chknode=YES );
public     : virtual          OPAImpExp             logical SetVersion (uint16 version_nr=CUR_VERSION );
public     :                                        void SetWPT ( );
public     : virtual          OPAImpExp             logical SetWProtect ( );
public     : virtual          OPAImpExp             logical SetupNode (logical create_ref, logical retain_mod );
public     :                                        logical SetupSubNode (logical create_ref );
public     : virtual          OPAImpExp             ACObject *StartReadTA ( );
public     : virtual          OPAImpExp             void StopReadTA (logical error_case );
public     : virtual          OPAImpExp             logical Store ( );
public     : virtual          OPAImpExp             logical StoreData (void *instptr );
public     :                                        guid *StringToGUID (guid *_guid, char *guid_string );
public     : virtual          OPAImpExp             char *StringToKey (char *key_string, char *key_name_w=NULL );
public     :                                        logical StructFieldError ( );
public     : virtual          OPAImpExp             logical Switch (int32 indx0 );
public     :                                        logical SynchInstance (int32 synch_cur=ERIC, int32 synch_loid=UNDEF );
public     :                                        logical ToTop ( );
public     : virtual          OPAImpExp             logical Union (node *nodeptr, char sk_opt=YES, logical distinct=NO );
public     : virtual          OPAImpExp             logical Union (PropertyHandle **pi_liste, int32 count, char sk_opt=YES, logical distinct=NO );
public     : virtual          OPAImpExp             logical Unlock ( );
public     : virtual          OPAImpExp             logical UnlockSet (logical extlock, logical chknode=YES );
public     : virtual          OPAImpExp             logical UnregisterHandle ( );
public     : virtual                                node *ValidateNode (logical crt_opt );
public     :                                        void __Decrease ( );
public     :                                        void __Increase ( );
public     : static                                 int32 __cdecl __TraceList (int32 max_count );
public     :                                        bnode *get_bnode ( );
public     :                                        node **get_nodenode_ptr ( );
public     :                  OPAImpExp                  node (int64 int64_val );
public     :                  OPAImpExp                  node (node *nodeptr, DBFieldDef *dbfield_ptr, void *instptr );
public     :                  OPAImpExp                  node (DBStructDef *struct_def, char *prop_names, void *instptr );
public     :                  OPAImpExp                  node (dbtm time_val );
public     :                  OPAImpExp                  node (Dictionary *dictptr, DBFieldDef *field_def, char *init_string, logical init_opt, logical const_opt );
public     :                  OPAImpExp                  node (logical logval );
public     :                  OPAImpExp                  node (Dictionary *dictptr, char *prop_names, char *typenames, int32 nsid, SDB_RLEV ref_level, uint32 size, int32 precision, uint32 dimension, char *init_string );
public     :                  OPAImpExp                  node (DBFieldDef *field_def, void *initinst=NULL );
public     :                  OPAImpExp                  node (char *string, int32 string_len );
public     :                  OPAImpExp                  node ( );
public     :                  OPAImpExp                  node (dttm datetime_val );
public     :                  OPAImpExp                  node (Dictionary *dictptr, char *typenames );
public     :                  OPAImpExp                  node (DBStructDef *strdef, void *instptr );
public     :                  OPAImpExp                  node (char *string );
public     :                  OPAImpExp                  node (double dbl_value );
public     :                  OPAImpExp                  node (int32 int_val );
public     :                  OPAImpExp                  node (dbdt date_val );
public     :                  OPAImpExp                  node (node &noderef );
public     :                                        logical set_auto_key (char *keyptr );
public     :                                        void set_auto_position (int32 lindx0 );
public     :                                        void set_auto_provide (logical logval );
public     :                                        void set_nodeinst (inti *intiptr );
public     :                                        void set_nodenode (node *nodeptr );
public     :                                        void set_parent (node *nodeptr );
public     :                                        void set_prop_path (char *path );
public     :                                        char *set_result_string (char *char_buffer, int32 longlen );
public     : virtual          OPAImpExp                  ~node ( );
public     :                                        logical IsGUID ( ){

  return( stscdel() );

}

public     :                                        node **get_pnodeptr ( ){

  return(&ph);

}

};

#pragma pack()
#endif
