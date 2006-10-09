/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACPath_old



\date     $Date: 2006/03/12 19:12:07,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACPath_old_HPP
#define   ACPath_old_HPP

class     ACPath_old;

#pragma pack(8)

class  ACPath_old :public LNode
{
protected  :         Dictionary                                  *dictionary ATTR_ALIGN(4);                                  
protected  :         DLL(ACPathElement)                           elements;                                                  
protected  :         int32                                        current_element;                                           
protected  :         char                                        *expression;                                                //
protected  :         BNFData                                     *expression_bnf;                                            //
protected  :         int32                                        parent_objid;                                              //
protected  :         ParmList                                    *parameters;                                                //
protected  :         ParmList                                    *variables;                                                 //

public     :
                     Dictionary                                  *get_dictionary() { return(dictionary); }
                     DLL(ACPathElement)                          &get_elements() { return(elements); }
                     int32                                        get_current_element() { return(current_element); }
                     char                                        *get_expression() { return(expression); }
                     BNFData                                     *get_expression_bnf() { return(expression_bnf); }
                     int32                                        get_parent_objid() { return(parent_objid); }
                     ParmList                                    *get_parameters() { return(parameters); }
                     ParmList                                    *get_variables() { return(variables); }
public     :                                     void ACPath (Dictionary *dict_ptr, ACObject *obhandle, node *nodeptr, BNFData *bnf_data, ParmList *parm_list, ParmList *var_list, PIACC accmode=PI_undefined );
public     :                                     void ACPath (LACObject *lobhandle, DBExtend *dbextdef, PIACC accmode=PI_undefined );
public     :                                     void ACPath (ACPath &acpathref );
public     :                                     void ACPath (node *co_node, DBFieldDef *fielddef, PIACC accmode=PI_undefined );
public     : virtual opa7ImpExp                  void *Add (int32 lindx0, logical global_add=NO );
public     : virtual opa7ImpExp                  void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual opa7ImpExp                  logical CanUpdateCollection (logical chknode=YES );
public     : virtual                             logical Cancel (logical chknode=YES );
public     : virtual opa7ImpExp                  PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                             logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual opa7ImpExp                  int8 CompareKey (char *skey1, char *skey2, logical chknode=YES );
public     : virtual opa7ImpExp                  int8 CompareSortKey (char *skey1, char *skey2, logical chknode=YES );
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
public     : virtual                             ACPathElement *GetAccessNode ( );
public     : virtual                             int32 GetCount ( );
public     :                                     ACPathElement *GetElementNode (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *co, BNFData *bnf_data, char *key_name_w=NULL );
public     :                                     ACPathElement *GetElementNode (char *symbol, ACPathElement *parent_element, BNFData *bnf_data, logical optional=YES );
public     :                                     ACPathElement *GetElementNode (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *co, BNFData *path_operand, BNFData *parm_data, char *key_name_w=NULL );
public     :                                     FunctionTypes GetElementType (PropertyHandle *co, BNFData *bnf_data );
public     :                                     EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                     EB_Number GetID (char *skey, logical chknode=YES, logical pif_opt=NO );
public     : virtual                             void *GetInitInstance (logical set_init=YES );
public     : virtual                             int16 GetInstModCount ( );
public     :                                     int16 GetKeyLength ( );
public     : virtual                             smcb *GetKeySMCB (char *key_name_w=NULL );
public     : virtual                             PropertyHandle *GetPathElement (char *path_element );
public     : virtual                             int16 GetRefModCount ( );
public     :                                     int16 GetSortKeyLength (logical chknode=YES );
public     :                                     smcb *GetSortKeySMCB ( );
public     :                                     logical InitAccessPath (BNFData *bnf_data );
public     :                                     logical InitElements (BNFData *bnf_data );
public     :                                     logical InitElements (DBStructDef *dbview_str, DLL(FieldSource) *source_list );
public     :                                     logical InitFromElement (DBStructDef *dbview_str, DLL(FieldSource) *source_list );
public     :                                     logical InitOQLSelect (BNFData *bnf_data );
public     :                                     ACPathElement *InitTopElementNode (ACPath *accpath, ACPathElement *parent_element, PropertyHandle *co );
public     :                                     logical InitViewElements (DBStructDef *dbview_str );
public     :                                     void Initialize (BNFData *bnf_data );
public     :                                     void Initialize (ACObject *obhandle );
public     :                                     void Initialize (DBFieldDef *fielddef );
public     :                                     FunctionTypes IsCollectionOperand (BNFData *bnf_data );
public     :                                     logical IsGlobalVariable (char *opname );
public     :                                     FunctionTypes IsInlineExpression (BNFData *bnf_data );
public     :                                     logical IsLocalVariable (char *opname );
public     :                                     logical IsParameter (char *opname );
public     : virtual                             logical IsPositioned ( );
public     : virtual                             logical IsSelected ( );
public     :                                     FunctionTypes IsSysVariable (BNFData *bnf_data );
public     :                                     FunctionTypes IsViewPath (BNFData *bnf_data );
public     :                                     logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                     logical Lock ( );
public     :                                     logical LockSet (logical chknode=YES );
public     :                                     char *NextKey (char *skey, int16 switch_level=0 );
public     :                                     logical Open ( );
public     : virtual opa7ImpExp                  int32 Position (int32 count, logical chknode=YES );
public     : virtual                             logical Reset ( );
public     : virtual                             logical ResetNode (logical reset_all );
public     :                                     logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual opa7ImpExp                  logical SetContextVariables (char *context_string );
public     :                                     logical SetKey (kcb *kcbptr, char *keyptr, void *instptr );
public     :                                     logical SetKey (char *keyptr, void *instptr );
public     : virtual                             logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                     logical SetSortKey (char *keyptr, void *instptr );
public     :                                     void SetupInstance ( );
public     : virtual                             logical Switch (int32 indx0 );
public     :                                     logical Unlock ( );
public     :                                     logical UnlockSet (logical extlock, logical chknode=YES );
public     : virtual                             node *ValidateNode (logical crt_opt );
public     :                                     void set_expression (char *path_def );
public     : virtual                             void ~ACPath ( );
};

#pragma pack()
#endif
