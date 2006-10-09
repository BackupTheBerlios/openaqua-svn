/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    CNode

\brief    Property Handle
          1.  "Alle"  Funktionen  sind  zu  ¸berarbeiten  f¸r not connection, da
          prophdl  aufgrung der  Dereferenzierung nicht  den Funktionsumfang von
          DBField  abdeckt, d.h. ggf. muﬂ die Funktionalit‰t mit local_ref (wenn
          nicht leer) oder prophdl aufgerufen werden.
          2.  Bei  Einf¸hrung  von  untergeordneten not connection PHs (z.B. f¸r
          Attribute)  f¸r  connection  PHs  muﬂ  in  "allen"  Funktionen gepr¸ft
          werden,  ob  und  wie  diese  mit  leerem  local_ref  und prophdl ohne
          highnod zurechtkommen.
          ******************
          Property  handle  are  used  to  manage  property  instances within an
          object  instance. They can be used also for managing extents, internal
          variables  or any other type of property. Property handle refer to the
          instance data as well as to the metadata (property definition).
          ********************
          Beschreibt  das DBField eine Collection in einer Datenbankinstanz oder
          einen  Extent, stehen neben den DBField-Funktionen alle Funktionen des
          PI-Handle zur Verf¸gung (siehe {.r PI}). 
          DBFields   kˆnnen   PI-basiert   konstruiert   werden,   wenn   die  
          Structure-Instanz,  in  der  sich  die  Property  befindet,  in  einem
          PI-Handle  verwaltet  wird.  In  diesem  Fall  wird mit dem Einstellen
          einer   neuen   Instanz   auch   die   Property-Instanz   im   DBField
          aktualisiert.  ƒnderungen im  DBField werden  in diesem Fall direkt an
          die  Structure-Instanz  des  PI-Handle  weitergeleitet. Damit entf‰llt
          die Modify-Anzeige durch den Entwickler. 
          Extent  oder PI-basierte DBFields sind mit einem Kontext ausgestattet.
          Damit  lˆsen diese DBFields  automatisch system- oder nutzerdefinierte
          Ereignisse  aus,  wenn  sie  ge‰ndert  oder  bereitgestellt  werden. 
          Auﬂerdem  ist  es  f¸r  kontextbezogene  DBFields  mˆglich,  Actions 
          auszulˆsen, die in diesem Kontext definiert sind (->ExecuteAction()).
          DBFields  sind nach auﬂen typneutral Felder,  d.h. der Typ wird intern
          verwaltet. 
          ********************
          Property  handles  support  standard  operations as +, - for different
          property  types, metadata operations and  a number of other functions.
          Property  handle  are  based  on  collection  handles  and provide all
          functionality  for  collection  handles,  especially when referring to
          reference properties.

\date     $Date: 2006/08/30 19:41:11,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CNode_HPP
#define   CNode_HPP

class     CNode;

#define  Cnodeinst                                 ((cinti *)nodeinst)
#define  Cnodenode                                 ((CNode *)nodenode)
#define  Cnodeptr                                  ((CNode *)nodeptr)
#define  Csrcenode                                 ((CNode *)srcenode)
#define  SYS_NSID                                  0
class     ACExtend;
class     ACObject;
class     BNFData;
class     BNFExpData;
class     CSA_Handle;
class     CS_Handle;
class     CTX_Base;
class     DBExtend;
class     DBFieldDef;
class     DBStructDef;
class     Dictionary;
class     OperEnvironment;
class     ParmList;
class     SimpleAction;
class     inti;
class     node;
class     smcb;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <cSDB_RLEV.h>
#include  <sCNode.hpp>
#include  <sEB_Number.hpp>
#include  <sInstance.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#pragma pack(8)

class  CNode :public bnode
{
protected  :         logical                                      conversion;                                                // Parent property handle
protected  :         NodeTypes                                    data_nodetype;                                             // Database Object Handle

public     :
                     logical                                      get_conversion() { return(conversion); }
                     NodeTypes                                    get_data_nodetype() { return(data_nodetype); }
public     : virtual                                void *Add (int32 indx0, char *sort_key, char *ident_key, void *initinst=NULL, logical global_add=NO );
public     : virtual                                logical AddReference (node *srcenode, int32 lindx0 );
public     :                                             CNode (node *nodeptr, NodeTypes nodtype, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 intoff, PIACC accopt );
public     :                                             CNode (ACObject *obhandle, DBStructDef *dbstructdef, char *key_name_w=NULL );
public     :                                             CNode (ACObject *obhandle, DBExtend *dbextdef, PIACC accopt );
public     :                                             CNode (CNode &cnode_ref, CNode &cnode_top, logical path_opt, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     :                                             CNode (CNode *cnodeptr );
public     :                                             CNode (node *nodeptr, CS_Handle *handle, char *ctx_strnames, char *proppath, char *strnames, char *sknames, logical temp_opt, logical weak_opt, logical own_opt );
public     :                                             CNode (node *nodeptr, CS_Handle *handle, char *proppath, char *fldtypes, int32 nsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim );
public     :                                             CNode (CNode &cnode_ref, char *expression );
public     :                                             CNode (ACObject *obhandle, ST_OpCodes op_type, char *rule );
public     :                                             CNode (ACObject *obhandle, ST_OpCodes op_type, BNFData *bnf_data );
public     :                                             CNode (CNode &cnode_ref, ST_OpCodes op_type, char *rule );
public     :                                             CNode (CNode &cnode_ref, ST_OpCodes op_type, BNFData *bnf_data );
public     :                                             CNode (ACObject *obhandle, BNFData *bnf_data, PIACC accopt );
public     :                                             CNode (ACObject *obhandle, char *expression, PIACC accopt );
public     :                                             CNode ( );
public     :                                             CNode (CNode &cnode_ref );
public     : virtual                                void CSAClosed (char *parmstring );
public     : virtual                                void CSADirty (char *parmstring );
public     : virtual                                logical CanUpdateCollection (logical chknode=YES );
public     : virtual                                logical Cancel (logical chknode=YES );
public     : virtual                                int16 ChangeBuffer (int16 buffnum=AUTO );
public     : virtual                                PIACC ChangeMode (PIACC newmode, char chkopt=AUTO );
public     :                                        void ChangeMode_intern (logical error_case, PIACC newmode );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                                logical CheckModify ( );
public     :                                        logical CheckReadOnly ( );
public     :                                        smcb *CheckSKey_intern (logical seterr_opt=YES );
public     : virtual                                logical CheckWProtect ( );
public     : virtual                                logical Close ( );
public     :                                        void Close_intern ( );
public     : virtual                                logical Contains (char *reg_string, logical case_opt=YES );
public     : virtual                                void *CopyInst (node *srcenode, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, char *w_newkey=NULL, int32 set_pos0_w=AUTO, logical chknode=YES );
public     : virtual                                int32 CopySet (node *srcenode, logical check_inverse, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, logical chknode=YES );
public     : virtual                                node *CreateAccessPath (char *prop_path, OperEnvironment *operenv );
public     : virtual                                node *CreateAccessPath (BNFData *bnf_data, OperEnvironment *operenv );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     : virtual                                node *CreatePathNode (char *path_prop, OperEnvironment *operenv );
public     : virtual                                node *CreatePathNode (BNFData *bnf_data, OperEnvironment *operenv );
public     : virtual                                node *CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     : virtual                                logical Delete (char *sort_key, logical chknode=YES );
public     : virtual                                logical Delete (int32 set_pos0_w=AUTO, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual                                logical DeleteSet (logical chknode=YES, logical del_dep=YES );
public     : virtual                                logical DisableKeyCheck (logical chknode=YES );
public     : virtual                                void *Duplicate (char *keyptr, PIREPL db_replace=REPL_none, logical chknode=YES );
public     : virtual                                logical EnableKeyCheck (logical chknode=YES );
public     : virtual                                logical ExecPropCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                                logical ExecStrCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                                char *FirstKey (logical chknode=YES );
public     : virtual                                void *Get (int32 lindx0, logical chknode=YES );
public     : virtual                                void *Get (char *skey, logical chknode=YES );
public     : virtual                                node **GetBaseNode ( );
public     : virtual                                int32 GetCollectionID ( );
public     : virtual                                int32 GetCount (logical chknode=YES );
public     : virtual                                node *GetExtentNode ( );
public     : virtual                                int GetGenAttrType (char *w_propnames=NULL );
public     : virtual                                int GetGenOrderType ( );
public     : virtual                                EB_Number GetGlobalID ( );
public     : virtual                                EB_Number GetID (int32 lindx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                EB_Number GetID_ByID (char *keyptr );
public     : virtual                                int16 GetInstModCount ( );
public     : virtual                                char *GetKey (int32 lindx0, logical chknode=YES );
public     : virtual                                PIACC GetMode (logical chknode=YES );
public     : virtual                                int16 GetRefModCount ( );
public     : virtual                                void *GetRelative (int32 lindx0, logical chknode=YES );
public     : virtual                                int32 GetRelativeCount ( );
public     : virtual                                int32 GetRelativeIndex (logical last_opt, logical chknode=YES );
public     : virtual                                char *GetSelectedKey (logical chknode=YES );
public     : virtual                                void *Get_ByID (char *skey );
public     : virtual                                void *Get_optimized (int32 lindx0, logical chknode=YES );
public     : virtual                                logical Group (node *nodeptr, logical distinct=NO );
public     :                                        logical InSave ( );
public     :                                        void InitHandle ( );
public     :                                        logical InitPathNode (CNode &cnode_ref );
public     :                                        logical InitPathNode (CNode &cnode_ref, char *expression );
public     :                                        logical InstBuffer_setup (int32 count );
public     :                                        char *InstKey_setup (logical error_case, char *keyptr );
public     :                                        logical InstOrder_setup (logical error_case );
protected  :                                        void *Inst_setup (logical error_case, logical add=NO, logical active=AUTO );
protected  :                                        void *Inst_setup (logical error_case, char *inst_data );
public     : virtual                                logical Intersect (PropertyHandle **pi_liste, int32 count, char sk_opt=YES );
public     : virtual                                logical Intersect (node *nodeptr, char sk_opt=YES );
public     : virtual                                logical IsAttribute ( );
public     : virtual                                logical IsGenericAttribute ( );
public     : virtual                                logical IsLocalNode ( );
public     : virtual                                logical IsNewInstance ( );
public     : virtual                                logical IsPositioned ( );
public     : virtual          OPAImpExp             logical IsReadOnly ( );
public     : virtual                                logical IsSelected ( );
public     : virtual                                logical Locate (EB_Number entnr, logical read_opt=YES );
public     : virtual                                logical LocateKey (char *sort_key, logical exact=YES, logical chknode=YES );
public     : virtual                                logical Lock ( );
public     : virtual                                logical LockSet (logical chknode=YES );
public     : virtual                                logical Minus (node *node1, node *node2, char sk_opt=YES );
public     : virtual                                logical Minus (node *nodeptr, char sk_opt=YES );
public     : virtual                                void *Modify (logical chknode=YES );
public     : virtual                                void *Move (node *srcenode, PIREPL db_replace=REPL_none, char *w_newkey=NULL, logical setwpt=NO );
public     :                                        logical MoveDown ( );
public     :                                        logical MoveUp ( );
public     : virtual                                char *NextKey (char *sort_key_w=NULL, int16 switch_level=0 );
public     :                                        Instance OInst_setup ( );
public     :                                        void Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt );
public     :                                        logical OpenAccessPath (ACObject *obhandle, logical temp_opt_w=NO );
public     :                                        logical OpenAccessPath (CNode &cnode_ref );
public     :                                        logical OpenBaseNode ( );
public     :                                        logical OpenCopyNode (CNode &cnode_ref );
public     :                                        logical OpenOperationNode (CNode &cnode_ref, ST_OpCodes op_type, char *rule );
public     :                                        logical OpenOperationNode (ACObject *obhandle, ST_OpCodes op_type, char *rule );
public     :                                        logical OpenPathCopy (CNode &cnode_ref, CNode &last_node, logical path_opt, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     :                                        logical OpenSubNode ( );
public     :                                        logical Open_setup ( );
public     : virtual                                node *PathCreateCopy (node *nodeptr, logical path_opt, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     : virtual                                int32 Position (int32 count, logical chknode=YES );
public     : virtual                                logical ProvGenAttribute ( );
public     : virtual                                void *Provide (int32 lindx0, logical global_add=NO );
public     : virtual                                void *Provide (char *skey, logical global_add=NO );
public     : virtual                                void *Provide (void *datarea, logical global_add=NO );
public     : virtual                                char *ProvideGUID ( );
public     : virtual                                int32 ReadBuffer (int32 set_pos0, int16 direction );
public     :                                        logical RecoverSelection (int64 obj_id );
public     : virtual                                logical Refresh ( );
public     : virtual                                logical RegisterHandle (CSA_Handle *cs_handle );
public     : virtual          OPAImpExp             logical RemoveFromCollection ( );
public     : virtual                                logical Rename (char *new_key, logical chknode=YES );
public     :                                        logical Reopen_intern ( );
public     : virtual                                logical RepairIndex (char *key_name, char *attrstr );
public     : virtual                                logical Reset ( );
public     : virtual                                logical ResetExpression ( );
public     : virtual                                void ResetInstance ( );
public     : virtual                                logical ResetWProtect ( );
public     : virtual                                logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                        logical Save_intern (logical switchopt );
public     : virtual                                logical Select (node *nodeptr, char *expression, int32 min_inst=AUTO );
public     : virtual                                logical SetAction (SimpleAction *simple_action );
public     :                                        logical SetBaseNode (CNode *cnode_ptr );
public     : virtual                                logical SetContextVariables (char *context_string );
public     : virtual                                logical SetExpression (char *expression );
public     : virtual                                logical SetGenAttribute (char *fldnames, int attrtype, char *attrstr );
public     : virtual                                logical SetGenAttribute (int attrtype, char *attrstr );
public     : virtual                                logical SetGenAttribute ( );
public     :                                        void SetGenKey (int attrtype );
public     : virtual                                logical SetInstAction (SimpleAction *simple_action );
public     :                                        void SetModified ( );
public     : virtual                                logical SetOrder (char *key_name, int attrtype, char *attrstr );
public     : virtual                                logical SetType (char *strnames, logical chknode=YES );
public     : virtual                                logical SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                                logical SetWProtect ( );
public     :                                        logical SetupCNode (int32 lindx0, logical retain_mod, logical active=AUTO );
public     : virtual                                logical Switch (int32 indx0 );
public     :                                        logical UninitHandle ( );
public     : virtual                                logical Union (PropertyHandle **pi_liste, int32 count, char sk_opt=YES, logical distinct=NO );
public     : virtual                                logical Union (node *nodeptr, char sk_opt=YES, logical distinct=NO );
public     : virtual                                logical Unlock ( );
public     : virtual                                logical UnlockSet (logical extlock, logical chknode=YES );
public     : virtual                                logical UnregisterHandle ( );
public     :                                        logical Update_intern (logical switchopt );
public     : virtual                                     ~CNode ( );
};

#pragma pack()
#endif
