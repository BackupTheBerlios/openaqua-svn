/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    LNode

\brief    


\date     $Date: 2006/06/22 13:54:14,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LNode_HPP
#define   LNode_HPP

class     LNode;

class     ACExtend;
class     ACGenericAttr;
class     ACObject;
class     BNFData;
class     BNFExpData;
class     CSA_Handle;
class     CTX_Base;
class     DBExtend;
class     DBFieldDef;
class     DBIndex;
class     OPDecl;
class     OPExpressionDecl;
class     OperEnvironment;
class     ParmList;
class     SimpleAction;
class     binti;
class     inti;
class     isel;
class     kcb;
class     ref;
class     refTable;
class     smcb;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sCSHandle.hpp>
#include  <sCSHandleList.hpp>
#include  <sCheckOptions.hpp>
#include  <sEB_Number.hpp>
#include  <sLNode.hpp>
#include  <sNString.hpp>
#include  <sPCSHandle.hpp>
#include  <sbnode.hpp>
#include  <sdbf.hpp>
#include  <snode.hpp>
#pragma pack(8)

class  LNode :public bnode
{
protected  :         refTable                                    *noderefl;                                                  // 
protected  :         ref                                         *noderefp;                                                  // 
protected  :         ref                                         *noderefmain;                                               // 
protected  :         OPDecl                                      *nodesel;                                                   // 
protected  :         PCSHandle                                    act_handle;                                                // 

public     :
                     refTable                                    *get_noderefl() { return(noderefl); }
                     ref                                         *get_noderefp() { return(noderefp); }
                     ref                                         *get_noderefmain() { return(noderefmain); }
                     OPDecl                                      *get_nodesel() { return(nodesel); }
                     PCSHandle                                   &get_act_handle() { return(act_handle); }
public     : virtual          OPAImpExp             void *Add (int32 lindx0, logical global_add=NO );
public     : virtual          OPAImpExp             void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual          OPAImpExp             logical AddGenericRef (char *fldname );
public     :                                        logical AddID (int32 indx0 );
public     :                                        logical AddID (char *keyptr, EB_Number ebsnum, int32 lindx0 );
public     :                                        logical AddID (binti *bintiptr, EB_Number ebsnum );
public     :                                        logical AddID (binti *bintiptr, EB_Number ebsnum, int32 lindx0 );
public     : virtual          OPAImpExp             void *AddInstance (binti *bintiptr, int32 indx0 );
public     : virtual          OPAImpExp             logical AddReference (node *srcenode, int32 lindx0 );
public     : virtual          OPAImpExp             logical CanUpdateCollection (logical chknode=YES );
public     : virtual          OPAImpExp             logical Cancel (logical chknode=YES );
public     : virtual          OPAImpExp             logical CancelNode ( );
public     : virtual          OPAImpExp             logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                        logical CheckDB (CheckOptions check_opts );
public     :                                        logical CheckDBCollection (NString &nresult, CheckOptions check_opts );
public     :                                        logical CheckDBInstance (CheckOptions check_opts );
public     :                                        logical CheckDelInstance (int32 inst_id, EB_Number ref_id, logical del_inst=NO );
public     :                  OPAImpExp             logical CheckExpression ( );
public     : virtual          OPAImpExp             logical CheckWProtect ( );
public     : virtual          OPAImpExp             logical Close ( );
public     : virtual          OPAImpExp             logical Contains (char *reg_string, logical case_opt=YES );
public     : virtual                                node *CreateCopyNode ( );
public     :                                        logical CreateGUID (logical transaction=NO );
public     : virtual          OPAImpExp             node *CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreatePathNode (char *prop_path, OperEnvironment *operenv );
public     : virtual          OPAImpExp             node *CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     : virtual          OPAImpExp             logical DelGenericRef (char *fldname );
public     : virtual          OPAImpExp             logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual          OPAImpExp             logical Delete (char *skey, logical chknode=YES );
public     :                                        logical DeleteID (binti *bintiptr, void *oldinst, EB_Number entnr );
public     :                                        logical DeleteID (binti *bintiptr );
public     :                                        logical DeleteID ( );
public     : virtual          OPAImpExp             logical DeleteIndex (logical gen_events );
public     : virtual          OPAImpExp             logical DeleteIndexEntry ( );
public     :                                        logical DeleteInstance (inti *intiptr, char *extnames, logical is_root, logical del_dep=YES, logical switch_opt=NO, logical del_inst=NO );
public     : virtual          OPAImpExp             logical DeleteSet (logical chknode=YES, logical del_dep=YES );
public     :                  OPAImpExp             logical DeleteSetIndexes ( );
public     : virtual          OPAImpExp             void *Duplicate (char *keyptr, PIREPL db_replace=REPL_none, logical chknode=YES );
public     :                                        logical FieldReserved ( );
public     : virtual          OPAImpExp             char *FirstKey (logical chknode=YES );
public     : virtual          OPAImpExp             void *Get (int32 indx0, logical chknode=YES );
public     : virtual          OPAImpExp             void *Get (char *skey, logical chknode=YES );
public     : virtual          OPAImpExp             void *Get ( );
public     : virtual          OPAImpExp             int32 GetAt (int32 lindx0, int16 direction, logical chknode=YES );
public     :                                        char GetAutoIdent (inti *intiptr, kcb *kcbptr, int attrtype );
public     : virtual          OPAImpExp             int32 GetCollectionID ( );
public     : virtual          OPAImpExp             int32 GetCount (logical chknode=YES );
public     : virtual          OPAImpExp             DBIndex *GetDBIndex (char *key_name_w=NULL );
public     : virtual          OPAImpExp             void *GetExtInst (char *extinst );
public     :                                        ACGenericAttr *GetGenAttrNode (char *w_fldnames=NULL );
public     : virtual          OPAImpExp             int GetGenAttrType (char *fldnames );
public     : virtual          OPAImpExp             int GetGenOrderType ( );
public     : virtual          OPAImpExp             EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual          OPAImpExp             EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     :                                        ref *GetIKRef ( );
public     :                                        ref *GetIndex (char *keynames=NULL );
public     : virtual          OPAImpExp             int16 GetInstModCount ( );
public     :                                        void *GetInstance (EB_Number entnr );
public     : virtual          OPAImpExp             char *GetKey (int32 lindx0, logical chknode=YES );
public     :                                        char *GetKeyAt (int32 indx0, int16 direction, char *keyptr );
public     : virtual          OPAImpExp             int16 GetMainBase ( );
public     :                                        ref *GetMainRef ( );
public     :                                        ref *GetRef ( );
public     : virtual          OPAImpExp             int16 GetRefModCount ( );
public     : virtual          OPAImpExp             char *GetSelectedKey (logical chknode=YES );
public     : virtual          OPAImpExp             ACExtend *GetSystemNode ( );
public     : virtual          OPAImpExp             logical Group (node *nodeptr, logical distinct=NO );
public     : virtual          OPAImpExp             logical HasFilter ( );
public     :                                        logical InitExtendRef (DBExtend *dbext_ptr, EB_Number *extref, logical extadd=YES );
public     : virtual          OPAImpExp             logical InitReference ( );
public     : virtual          OPAImpExp             logical IsLocalNode ( );
public     : virtual          OPAImpExp             logical IsReadOnly ( );
public     :                                        char *KeyCheck (int32 indx0, char *keyptr );
public     :                                             LNode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     :                                             LNode ( );
public     :                                             LNode (LNode &lnoderef );
public     : virtual          OPAImpExp             logical Locate (EB_Number entnr, logical read_opt=YES );
public     :                                        logical LocateID (binti *bintiptr );
public     : virtual          OPAImpExp             logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                        logical LocatePosition (EB_Number pifent );
public     : virtual          OPAImpExp             logical Lock ( );
public     : virtual          OPAImpExp             logical LockSet (logical chknode=YES );
public     : virtual          OPAImpExp             void *Move (node *srcenode, PIREPL db_replace=REPL_none, char *w_newkey=NULL, logical setwpt=NO );
public     : virtual          OPAImpExp             logical MoveDown ( );
public     : virtual          OPAImpExp             logical MoveUp ( );
public     : virtual          OPAImpExp             char *NextKey (char *skey, int16 switch_level=0 );
public     :                                        logical PathAdd (logical global_add=NO );
public     : virtual          OPAImpExp             node *PathCreateCopy (node *top_node, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     : virtual          OPAImpExp             int32 Position (int32 count, logical chknode=YES );
public     : virtual          OPAImpExp             void *Provide (char *skey, logical global_add=NO );
public     : virtual          OPAImpExp             void *Provide (int32 lindx0, logical global_add=NO );
public     : virtual          OPAImpExp             void *Provide (void *datarea, logical global_add=NO );
public     : virtual          OPAImpExp             logical RegisterHandle (CSA_Handle *cs_handle );
public     :                                        logical ReleaseField ( );
public     : virtual          OPAImpExp             logical RemoveFromCollection ( );
public     :                                        logical RemoveGUID (logical transaction=NO );
public     :                                        logical RemoveReference ( );
public     : virtual          OPAImpExp             logical Rename (char *identkey, logical chknode=YES );
public     : virtual          OPAImpExp             logical RepairIndex (char *key_name, char *attrstr );
public     :                                        logical ReserveField ( );
public     : virtual          OPAImpExp             char *ReserveInstance ( );
public     : virtual          OPAImpExp             logical Reset ( );
public     : virtual          OPAImpExp             logical ResetExpression ( );
public     : virtual          OPAImpExp             void ResetInstance ( );
public     : virtual          OPAImpExp             logical ResetNode (logical reset_all );
public     : virtual          OPAImpExp             logical ResetReference ( );
public     : virtual          OPAImpExp             logical ResetWProtect ( );
public     : virtual          OPAImpExp             logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual          OPAImpExp             logical SaveInitInst ( );
public     : virtual          OPAImpExp             logical SaveNode (logical switchopt, logical overwrite=NO );
public     :                                        logical SaveReference ( );
public     : virtual          OPAImpExp             logical Select (node *nodeptr, char *expression, int32 min_inst=AUTO );
public     :                  OPAImpExp             logical SetAction (SimpleAction *simple_action );
public     : virtual          OPAImpExp             logical SetAutoIdent (uint32 *autoidnt );
public     : virtual                                void SetCurrentInti (inti *intiptr );
public     : virtual          OPAImpExp             logical SetExpression (char *expression );
public     : virtual          OPAImpExp             logical SetExpression (BNFData *bnf_data );
public     : virtual          OPAImpExp             logical SetGenAttribute (char *fldnames, int attrtype, char *attrstr );
public     : virtual          OPAImpExp             logical SetInstAction (SimpleAction *simple_action );
public     :                                        logical SetMainRef ( );
public     : virtual          OPAImpExp             logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                        void SetOrderRef (ref *refptr );
public     :                                        void SetSave ( );
public     : virtual          OPAImpExp             logical SetWProtect ( );
public     : virtual          OPAImpExp             logical SetupIndex (logical tempindx=NO );
public     :                                        int16 StartTA ( );
public     :                                        logical StopTA (logical error_case );
public     :                                        logical TARequired ( );
public     : virtual          OPAImpExp             logical Unlock ( );
public     : virtual          OPAImpExp             logical UnlockSet (logical extlock, logical chknode=YES );
public     : virtual          OPAImpExp             logical UnregisterHandle ( );
public     :                                        logical UpdateID (binti *bintiptr, void *oldinst, EB_Number entnr, logical temp_only=NO );
public     :                                        logical UpdateID (logical temp_only=NO );
public     :                                        logical nodedel (int32 lindx0, logical chknode=YES );
public     :                                        logical nodedel (EB_Number entnr );
public     :                                        void nodetwm (char *errtext );
public     : virtual          OPAImpExp                  ~LNode ( );
};

#pragma pack()
#endif
