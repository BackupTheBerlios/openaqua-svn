/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACOperation

\brief    Operation nodes
          Operation  nodes are nodes that derive instances from a calling object
          node  (nodenode). An  operation node  may have multiple sources, which
          are  not  necessarily  identical  with  the  calling object. When a an
          operation  node may create more than  one instance per instance in the
          calling object, it is a "multiple children node".
          Multiple  children  sources  are  defined  static  field  definitions 
          (fmcbstat  = YES). Multiple children sources form a sub-node hierarchy
          when being defined as transient (fmcbtrans = YES).
          The  field  definition  contains  the source definition in the sources
          field.  The  field  name  may  differ  from the source name when being
          defined as:
          from(p=Person,c=Company).select(p.name, c.name)
          where  p and c are the fieldnames for further references. When no name
          has  been defined the  source expression is  used as name, i.e. a name
          should  always be defined,  when the source  is not simply a name. For
          field   deriviations,   operand   nodes   are   created performing the
          operation.

\date     $Date: 2006/08/30 18:21:02,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOperation_HPP
#define   ACOperation_HPP

class     ACOperation;

class     ACObject;
class     ACOperand;
class     BNFData;
class     DBFieldDef;
class     DBFieldList;
class     DBStructDef;
class     OPBase;
class     OperEnvironment;
class     inti;
class     kcb;
class     node;
class     smcb;
#include  <cPIACC.h>
#include  <sACNode.hpp>
#include  <sACOperation.hpp>
#include  <sEB_Number.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  ACOperation :public ACNode
{
protected  :         logical                                      has_references;                                            // 
protected  :         logical                                      multiple_children;                                         // 
protected  :         logical                                      temp_struct;                                               // 
protected  :         logical                                      bnf_owner;                                                 // 
protected  :         DBStructDef                                 *struct_def;                                                // 
protected  :         OperEnvironment                             *oper_env;                                                  // 
protected  :         BNFData                                     *oper_bnf;                                                  // 
protected  :         logical                                      created;                                                   // 
protected  :         logical                                      auto_create;                                               // 

public     :
                     logical                                      get_has_references() { return(has_references); }
                     logical                                      get_multiple_children() { return(multiple_children); }
                     logical                                      get_temp_struct() { return(temp_struct); }
                     logical                                      get_bnf_owner() { return(bnf_owner); }
                     DBStructDef                                 *get_struct_def() { return(struct_def); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
                     BNFData                                     *get_oper_bnf() { return(oper_bnf); }
                     logical                                      get_created() { return(created); }
                     logical                                      get_auto_create() { return(auto_create); }
public     :                                             ACOperation (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv );
public     :                                             ACOperation (ACOperation &opernode_ref );
public     : virtual                                void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual          OPAImpExp             logical CanUpdateCollection (logical chknode=YES );
public     : virtual                                logical Cancel (logical chknode=YES );
public     : virtual                                int16 ChangeBuffer (int16 bufnum=AUTO );
public     : virtual                                PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     :                                        logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                                logical Close ( );
public     : virtual                                DBFieldList *CreateFields ( );
public     : virtual                                inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     :                                        node *CreateNode (OPBase *op_base );
public     :                                        node *CreateNode (DBFieldDef *fielddef );
public     :                                        DBStructDef *CreateStruct (char *fldnames, char *strnames_w=NULL );
public     : virtual          OPAImpExp             logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual          OPAImpExp             logical Delete (logical del_dep=YES );
public     : virtual          OPAImpExp             logical Delete (char *skey, logical chknode=YES );
public     : virtual                                logical ExecPropCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                                logical ExecStrCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                                char *ExtractKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual                                char *ExtractKey (char *keyptr, kcb *kcbptr, void *instptr );
public     : virtual                                char *ExtractSortKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual                                char *FirstKey (logical chknode=YES );
public     : virtual                                void *Get (int32 indx0, logical chknode=YES );
public     : virtual                                void *Get (char *skey, logical chknode=YES );
public     : virtual                                int32 GetCount (logical chknode=YES );
public     : virtual                                EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     :                                        void *GetInitInstance (logical set_init=YES );
public     :                                        void *GetInstance ( );
public     :                                        int16 GetKeyLength ( );
public     : virtual                                smcb *GetKeySMCB (char *key_name_w=NULL );
public     :                                        PIACC GetMode (logical chknode=YES );
public     :                                        int16 GetSortKeyLength (logical chknode=YES );
public     :                                        smcb *GetSortKeySMCB ( );
public     :                                        logical Init (void *instptr );
public     :                                        logical InitFieldDef (char *fldnames );
public     :                                        logical InitOperandBNF (char *exprstr );
public     :                                        logical IsPositioned ( );
public     : virtual          OPAImpExp             logical IsSelected ( );
public     : virtual                                logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                        logical Lock ( );
public     :                                        logical LockSet (logical chknode=YES );
public     :                                        void *Modify (logical chknode=YES );
public     : virtual                                char *NextKey (char *skey, int16 switch_level=0 );
public     :                                        void Open (ACObject *obhandle, node *nodeptr, DBStructDef *structdef );
public     : virtual                                logical Reset ( );
public     : virtual                                logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                        void SetCO (node *nodeptr );
public     : virtual          OPAImpExp             logical SetContextVariables (char *context_string );
public     :                                        logical SetKey (kcb *kcbptr, char *keyptr, void *instptr );
public     :                                        logical SetKey (char *keyptr, void *instptr );
public     : virtual                                logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                        logical SetSortKey (char *keyptr, void *instptr );
public     : virtual                                void *SetupInstance ( );
public     :                                        logical Unlock ( );
public     :                                        logical UnlockSet (logical extlock, logical chknode=YES );
public     : virtual                                     ~ACOperation ( );
};

#pragma pack()
#endif
