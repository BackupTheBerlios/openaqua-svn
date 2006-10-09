/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACPathNode

\brief    


\date     $Date: 2006/08/04 12:04:29,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACPathNode_HPP
#define   ACPathNode_HPP

class     ACPathNode;

#ifndef   DLL_node_HPP
#define   DLL_node_HPP
#include  <snode.hpp>
#include  <sDLL.h>
#endif
class     ACExtend;
class     ACObject;
class     BNFData;
class     CSA_Handle;
class     CTX_Base;
class     CTX_DBBase;
class     CTX_Property;
class     DBFieldDef;
class     DBStructDef;
class     EventProxy;
class     OperEnvironment;
class     kcb;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sACPathNode.hpp>
#include  <sEB_Number.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#include  <snode.hpp>
class  ACPathNode :public bnode
{
protected  :         DLL(node)                                    node_path;                                                 // 
protected  :         ACPathNode                                  *copy_node;                                                 // 
protected  :         BNFData                                     *bnf_spec;                                                  // 
protected  :         EventProxy                                  *event_proxy;                                               // 
protected  :         BNFData                                     *bnf;                                                       // 
protected  :         OperEnvironment                             *oper_env;                                                  // 
protected  :         logical                                      owner;                                                     // 

public     :
                     DLL(node)                                   &get_node_path() { return(node_path); }
                     ACPathNode                                  *get_copy_node() { return(copy_node); }
                     BNFData                                     *get_bnf_spec() { return(bnf_spec); }
                     BNFData                                     *get_bnf() { return(bnf); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
                     logical                                      get_owner() { return(owner); }
public     :                                             ACPathNode (node *nodeptr, BNFData *parm_data, OperEnvironment *operenv );
public     :                                             ACPathNode (ACObject *obhandle, BNFData *parm_data, OperEnvironment *operenv, PIACC accopt );
public     :                                             ACPathNode (ACPathNode &acpath_node );
public     :                                             ACPathNode (ACObject *obhandle, char *proppath, OperEnvironment *operenv, PIACC accopt );
public     :                                             ACPathNode (node *nodeptr, char *proppath, OperEnvironment *operenv );
public     :                                        void *Add (int32 lindx0, logical global_add=NO );
public     :                                        void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     :                                        logical AddReference (node *srcenode, int32 lindx0 );
public     : virtual          OPAImpExp             logical Cancel (logical chknode=YES );
public     :                                        PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     :                                        logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                        logical CheckWProtect ( );
public     :                                        logical Close ( );
public     :                                        logical CloseHierarchy ( );
public     :                                        logical Contains (char *reg_string, logical case_opt=YES );
public     : virtual          OPAImpExp             node *CreateAccessPath (BNFData *parm_bnf, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreateAccessPath (char *prop_path, OperEnvironment *operenv );
public     : virtual                                node *CreateCopyNode ( );
public     :                                        node *CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv );
public     :                                        node *CreatePathNode (char *prop_path, OperEnvironment *operenv );
public     :                                        node *CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     :                                        logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     :                                        logical Delete (char *skey, logical chknode=YES );
public     :                                        logical DeleteIndex (logical gen_events );
public     :                                        logical DeleteSet (logical chknode=YES, logical del_dep=YES );
public     :                                        void *Duplicate (char *keyptr, PIREPL db_replace=REPL_none, logical chknode=YES );
public     : virtual          OPAImpExp             logical Execute (ParmList *parmlist );
public     :                                        char *ExtractKey (char *keyptr, void *instptr, logical chknode=YES );
public     :                                        char *ExtractSortKey (char *keyptr, void *instptr, logical chknode=YES );
public     :                                        logical First ( );
public     :                                        char *FirstKey (logical chknode=YES );
public     :                                        void *Get (int32 indx0, logical chknode=YES );
public     :                                        void *Get (char *skey, logical chknode=YES );
public     : virtual                                CTX_Property *GetContext ( );
public     :                                        int32 GetCount (logical chknode=YES );
public     : virtual          OPAImpExp             DBStructDef *GetCurrentTypeDef ( );
public     : virtual                                int32 GetDimension (logical chknode=YES );
public     :                                        EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                        EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     :                                        int16 GetInstModCount ( );
public     :                                        char *GetKey (int32 lindx0, logical chknode=YES );
public     :                                        node **GetNodePtr (char *prop_path, logical *is_transient=NULL, logical supress_struct_error=NO );
public     :                                        logical GetPosition (int16 direction );
public     :                                        int16 GetRefModCount ( );
public     :                                        logical GoUp (int16 direction );
public     :                                        logical HasFilter ( );
public     :                                        node *Head ( );
public     :                                        logical IsPositioned ( );
public     :                                        logical IsReadOnly ( );
public     :                                        logical IsSelected ( );
public     :                                        char *KeyToString (char *key_string, char *key_val, char *key_name_w=NULL );
public     :                                        logical Last ( );
public     :                                        logical Locate (EB_Number entnr, logical read_opt=YES );
public     :                                        logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                        node *LocateNode (char *proppath );
public     :                                        logical Lock ( );
public     :                                        logical LockSet (logical chknode=YES );
public     : virtual          OPAImpExp             void *Modify (logical chknode=YES );
public     :                                        void *Move (node *srcenode, PIREPL db_replace=REPL_none, char *w_newkey=NULL, logical chknode=YES );
public     :                                        logical MoveDown ( );
public     :                                        logical MoveUp ( );
public     :                                        logical NextCollection ( );
public     :                                        char *NextKey (char *skey, int16 switch_level=0 );
public     :                                        logical Open (BNFData *parm_data );
public     :                                        logical Open (char *proppath );
public     :                                        node *OpenPathElement (node *nodeptr, BNFData *acp, int32 &indx_ref, logical crt_copy );
public     :                                        logical Open_intern (BNFData *parm_data );
public     :                                        logical Open_intern (char *proppath );
public     :                                        int32 Position (int32 count, logical chknode=YES );
public     :                                        logical PositionNode (node *nodeptr, int16 direction, logical accept_position );
public     :                                        void *Provide (char *skey, logical global_add=NO );
public     :                                        void *Provide (int32 lindx0, logical global_add=NO );
public     :                                        void *Provide (void *datarea, logical global_add=NO );
public     :                                        logical RegisterHandle (CSA_Handle *cs_handle );
public     :                                        logical Rename (char *identkey, logical chknode=YES );
public     :                                        logical ReopenPath ( );
public     :                                        logical Reset ( );
public     :                                        logical ResetExpression ( );
public     : virtual          OPAImpExp             void ResetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void ResetInstanceProcessHandler (EventLink *event_link );
public     :                                        logical ResetNode (logical reset_all );
public     : virtual          OPAImpExp             void ResetPosition ( );
public     : virtual          OPAImpExp             void ResetPropertyEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void ResetPropertyProcessHandler (EventLink *event_link );
public     :                                        logical ResetWProtect ( );
public     :                                        logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                        logical Select (node *nodeptr, char *expression, int32 min_inst=AUTO );
public     :                                        logical SetExpression (char *expression );
public     :                                        logical SetExpression (BNFData *bnf_data );
public     :                                        logical SetGenAttribute (char *fldnames, int attrtype, char *attrstr );
public     :                                        logical SetGenAttribute (int attrtype, char *attrstr );
public     :                                        logical SetGenAttribute ( );
public     : virtual          OPAImpExp             void SetInstanceEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetInstanceProcessHandler (EventLink *event_link );
public     :                                        logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     : virtual          OPAImpExp             void SetPropertyEventHandler (EventLink *event_link );
public     : virtual          OPAImpExp             void SetPropertyProcessHandler (EventLink *event_link );
public     : virtual                                logical SetType (char *strnames, logical chknode=YES );
public     :                                        logical SetWProtect ( );
public     : virtual          OPAImpExp             logical Store ( );
public     : virtual                                char *StringToKey (char *key_string, char *key_name_w=NULL );
public     :                                        node *Tail ( );
public     :                                        logical ToTop ( );
public     :                                        logical Unlock ( );
public     :                                        logical UnlockSet (logical extlock, logical chknode=YES );
public     :                                        logical UnregisterHandle ( );
public     :                                        void *UpdatePosition ( );
public     : virtual          OPAImpExp             node *ValidateNode (logical crt_opt );
public     :                                             ~ACPathNode ( );
};

#endif
