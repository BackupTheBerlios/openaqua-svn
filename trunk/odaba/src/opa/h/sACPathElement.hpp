/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACPathElement

\brief    Path element
          Path  elements are  used to  control access  for complex access paths.
          Path  elements allow navigating and iterating through a path. The path
          elements  optimize iteration through a  path. This optimisation can be
          disturbed, when mixing iteration and navigation (access by key).

\date     $Date: 2006/03/12 19:12:01,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACPathElement_HPP
#define   ACPathElement_HPP

class     ACPathElement;

class     ACObject;
class     ACOperation;
class     ACPath;
class     BNFData;
class     BNFExpData;
class     DBFieldDef;
class     DBStructDef;
class     DBViewStructDef;
class     Dictionary;
class     Operation;
class     ParmList;
class     kcb;
class     smcb;
#include  <cFunctionTypes.h>
#include  <cPIACC.h>
#include  <sACPathElement.hpp>
#include  <sEB_Number.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#include  <snode.hpp>
#pragma pack(8)

class  ACPathElement :public bnode
{
protected  :         ACPath                                      *acc_path ATTR_ALIGN(4);                                    //
protected  :         ParmList                                    *parameters;                                                //
protected  :         int16                                        parm_count;                                                //
protected  :         DBStructDef                                 *class_ref;                                                 //
protected  :         PropertyHandle                              *co;                                                        //
protected  :         FunctionTypes                                op_type;                                                   //
protected  :         ST_OpCodes                                   op_code;                                                   //
protected  :         char                                         op_name[41];                                               //
protected  :         char                                        *bnf_top_string;                                            //
protected  :         BNFData                                     *bnf_top;                                                   //
protected  :         BNFData                                     *bnf_operand;                                               //
protected  :         BNFData                                     *bnf_parm;                                                  //
protected  :         Operation                                   *operation;                                                 //
protected  :         PropertyHandle                               selection;                                                 //
protected  :         PropertyHandle                               operand;                                                   //
protected  :         char                                        *order;                                                     //
protected  :         logical                                      set_operation;                                             //
protected  :         logical                                      meta_operation;                                            //
protected  :         logical                                      var_selection;                                             // Current path index
protected  :         int32                                        path_index;                                                // Start index
protected  :         int32                                        start_index;                                               // Path object identity
protected  :         int32                                        path_objid;                                                // Stop index
protected  :         int32                                        stop_index;                                                // Last node in path
protected  :         logical                                      last_node;                                                 //

public     :
                     ACPath                                      *get_acc_path() { return(acc_path); }
                     ParmList                                    *get_parameters() { return(parameters); }
                     int16                                        get_parm_count() { return(parm_count); }
                     DBStructDef                                 *get_class_ref() { return(class_ref); }
                     PropertyHandle                              *get_co() { return(co); }
                     ST_OpCodes                                  &get_op_code() { return(op_code); }
                     char                                        *get_op_name() { return(op_name); }
                     char                                        *get_bnf_top_string() { return(bnf_top_string); }
                     BNFData                                     *get_bnf_top() { return(bnf_top); }
                     BNFData                                     *get_bnf_operand() { return(bnf_operand); }
                     BNFData                                     *get_bnf_parm() { return(bnf_parm); }
                     PropertyHandle                              &get_selection() { return(selection); }
                     PropertyHandle                              &get_operand() { return(operand); }
                     char                                        *get_order() { return(order); }
                     logical                                      get_set_operation() { return(set_operation); }
                     logical                                      get_meta_operation() { return(meta_operation); }
                     logical                                      get_var_selection() { return(var_selection); }
                     int32                                        get_path_index() { return(path_index); }
                     int32                                        get_start_index() { return(start_index); }
                     int32                                        get_path_objid() { return(path_objid); }
                     int32                                        get_stop_index() { return(stop_index); }
                     logical                                      get_last_node() { return(last_node); }
public     :                                                             ACPathElement (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *prophdl, FunctionTypes fttype, char *opname, BNFData *path_operand, BNFData *parm_data, char *key_names );
public     :                                                             ACPathElement (ACPathElement &acpelmref );
public     :                                                             ACPathElement (ACPath *accpath, node *co_node, node *nodeptr, char *key_names );
public     :                                                             ACPathElement ( );
public     :                                                             ACPathElement (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *prophdl, DBStructDef *dbview_str );
public     :                                     ACPathElement *AccessNode ( );
public     :                                     ACPathElement *AccessParent ( );
public     : virtual opa7ImpExp                  void *Add (int32 lindx0, logical global_add=NO );
public     : virtual opa7ImpExp                  void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual opa7ImpExp                  logical CanUpdateCollection (logical chknode=YES );
public     : virtual                             logical Cancel (logical chknode=YES );
public     : virtual                             PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                             logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                             logical Close ( );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual opa7ImpExp                  logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES );
public     : virtual opa7ImpExp                  logical Delete (char *skey, logical chknode=YES );
public     : virtual opa7ImpExp                  logical ExecPropCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual opa7ImpExp                  logical ExecStrCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual opa7ImpExp                  char *ExtractKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual opa7ImpExp                  char *ExtractKey (char *keyptr, kcb *kcbptr, void *instptr );
public     : virtual opa7ImpExp                  char *ExtractSortKey (char *keyptr, void *instptr, logical chknode=YES );
public     :                                     void *Get (int32 indx0, logical chknode=YES );
public     :                                     void *Get (char *skey, logical chknode=YES );
public     :                                     void *Get ( );
public     : virtual                             int32 GetCount (logical chknode=YES );
public     :                                     FunctionTypes GetElementType (Dictionary *dictionary, smcb *smcbptr );
public     :                                     EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                     EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     :                                     void *GetInitInstance (logical set_init=YES );
public     :                                     int16 GetKeyLength ( );
public     : virtual                             smcb *GetKeySMCB (char *key_name_w=NULL );
public     :                                     node *GetNodePtr ( );
public     :                                     int16 GetSortKeyLength (logical chknode=YES );
public     :                                     smcb *GetSortKeySMCB ( );
public     :                                     logical InitCollection (Dictionary *dict_ptr );
public     :                                     logical InitElement (Dictionary *dictionary );
public     :                                     logical InitGlobalVariable (Dictionary *dict_ptr );
public     :                                     logical InitGroupOperation (Dictionary *dict_ptr );
public     :                                     logical InitInlineExpression (Dictionary *dict_ptr );
public     :                                     logical InitIntersectOperation (Dictionary *dict_ptr );
public     :                                     logical InitJoinOperation (Dictionary *dict_ptr );
public     :                                     logical InitLocation (Dictionary *dict_ptr );
public     :                                     logical InitMetaOperation (Dictionary *dict_ptr );
public     :                                     logical InitMinusOperation (Dictionary *dict_ptr );
public     :                                     logical InitOperation (Dictionary *dict_ptr );
public     :                                     logical InitParmList (Dictionary *dict_ptr );
public     :                                     logical InitPath ( );
public     :                                     logical InitProperty (Dictionary *dict_ptr, PIACC accopt );
public     :                                     logical InitProperty (Dictionary *dict_ptr );
public     :                                     logical InitSelection (Dictionary *dict_ptr );
public     :                                     logical InitSysVariable (Dictionary *dict_ptr );
public     :                                     logical InitUnionOperation (Dictionary *dict_ptr );
public     :                                     logical InitView (Dictionary *dict_ptr );
public     :                                     logical InitializeOperand ( );
public     :                                     logical InitializeOperands ( );
public     :                                     FunctionTypes IsAction (smcb *smcbptr );
public     :                                     FunctionTypes IsEnumeration (Dictionary *dictionary );
public     :                                     FunctionTypes IsExpression (Dictionary *dictionary, smcb *smcbptr );
public     :                                     FunctionTypes IsExtent (Dictionary *dictionary );
public     :                                     FunctionTypes IsFunction (Dictionary *dictionary, smcb *smcbptr );
public     :                                     FunctionTypes IsGlobalVariable ( );
public     :                                     FunctionTypes IsLocalVariable ( );
public     :                                     FunctionTypes IsOperation ( );
public     :                                     FunctionTypes IsParameter ( );
public     :                                     FunctionTypes IsProperty (smcb *smcbptr );
public     :                                     logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                     logical Lock ( );
public     :                                     logical LockSet (logical chknode=YES );
public     :                                     logical Next (int32 count );
public     :                                     logical NextParent ( );
public     :                                     logical Open (DBFieldDef *field_def );
public     :                                     logical OpenParmHandle (PropertyHandle *prophdl, BNFData *parm_data );
public     :                                     logical Prev (int32 count );
public     :                                     logical PrevParent ( );
public     :                                     logical Reset ( );
public     : virtual                             logical ResetNode (logical reset_all );
public     :                                     logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual opa7ImpExp                  logical SetContextVariables (char *context_string );
public     :                                     logical SetKey (kcb *kcbptr, char *keyptr, void *instptr );
public     :                                     logical SetKey (char *keyptr, void *instptr );
public     :                                     void SetLast ( );
public     : virtual                             logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                     logical SetSortKey (char *keyptr, void *instptr );
public     :                                     logical Setup ( );
public     :                                     void SetupInstance ( );
public     :                                     logical SetupPathIndex (int32 indx0 );
public     :                                     logical Switch (int32 indx0 );
public     :                                     logical Unlock ( );
public     :                                     logical UnlockSet (logical extlock, logical chknode=YES );
public     :                                     logical UpdateSelectionValue ( );
public     : virtual                             node *ValidateNode (logical crt_opt );
public     :                                     void set_bnftop (BNFData *bnf_data, char *string );
public     :                                     void set_order (char *string );
public     :                                     void set_path_index (int32 indx0 );
public     :                                     void set_set_operation (logical set_op_opt );
public     :                                                             ~ACPathElement ( );
};

#pragma pack()
#endif
