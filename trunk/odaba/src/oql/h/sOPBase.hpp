/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    OPBase

\brief    Base for operation nodes
          When  creating  an  operation  node  the  expression  is  sntactically
          analyzed.  As long as a calling  object whith a valid field definition
          is  passed, the system  resolves further references.  When this is not
          possible, references are resolved later.

\date     $Date: 2006/08/27 20:12:41,01 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPBase_HPP
#define   OPBase_HPP

class     OPBase;

class     ACObject;
class     BNFData;
class     DBreakPoint;
class     DLInterpreter;
class     Dictionary;
class     ExtentList;
class     NodeStack;
class     OPBase;
class     OPDecl;
class     OPOperation;
class     OPParmList;
class     OPVariable;
class     OperEnvironment;
class     ParmList;
class     SchemaResources;
class     node;
#include  <cADT_Types.h>
#include  <cExecReturnCodes.h>
#include  <cFunctionTypes.h>
#include  <cOPNodeTypes.h>
#include  <cOQL_CodeBlock.h>
#include  <cST_OpCodes.h>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  OPBase :public fld
{
protected  : static  DLInterpreter                               *debugger;                                                  // Operstion node type
protected  : static  int8                                         debug;                                                     // Operation environment
protected  :         DBStructDef                                 *class_ref;                                                 // 
protected  :         OPNodeTypes                                  op_type;                                                   // 
protected  :         OperEnvironment                             *oper_env;                                                  // 
protected  :         BNFData                                     *operand_bnf;                                               // 
protected  :         char                                        *opname;                                                    // 
protected  :         int32                                        row;                                                       // 
protected  :         int32                                        column;                                                    // Reopen option
protected  :         OPBase                                      *parent;                                                    // 
protected  :         uint16                                       result_position;                                           // 
protected  :         OPBase                                      *source;                                                    // 
protected  :         PropertyHandle                               value;                                                     // 
protected  :         PropertyHandle                               last_co;                                                   // 
protected  :         OPParmList                                  *parmlist;                                                  // 
protected  :         int8                                         re_open;                                                   // 
protected  :         logical                                      env_owner;                                                 // 
protected  :         logical                                      proto_type;                                                // 
protected  :         int8                                         conversion;                                                // 
protected  :         int8                                         inherits;                                                  // 
protected  :         DBreakPoint                                 *debug_break;                                               // 

public     :
                     DLInterpreter                               *get_debugger() { return(debugger); }
                     int8                                         get_debug() { return(debug); }
                     DBStructDef                                 *get_class_ref() { return(class_ref); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
                     BNFData                                     *get_operand_bnf() { return(operand_bnf); }
                     char                                        *get_opname() { return(opname); }
                     int32                                        get_row() { return(row); }
                     int32                                        get_column() { return(column); }
                     OPBase                                      *get_parent() { return(parent); }
                     uint16                                       get_result_position() { return(result_position); }
                     OPBase                                      *get_source() { return(source); }
                     PropertyHandle                              &get_value() { return(value); }
                     OPParmList                                  *get_parmlist() { return(parmlist); }
                     int8                                         get_re_open() { return(re_open); }
                     logical                                      get_env_owner() { return(env_owner); }
                     logical                                      get_proto_type() { return(proto_type); }
                     int8                                         get_conversion() { return(conversion); }
                     int8                                         get_inherits() { return(inherits); }
                     DBreakPoint                                 *get_debug_break() { return(debug_break); }
public     :                                        logical AddParameter (OPBase *parent_node, DBFieldDef *fielddef );
public     :                                        void AllocDescription ( );
public     :                                        void AllocDescription (char *fldtypes, int16 fldityp, uint32 fldsize );
public     :                                        PropertyHandle *CO ( );
public     : virtual                                logical Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     : virtual                                logical Call (PropertyHandle *co, ParmList *parm_list, int8 set_operation=NO );
public     :                                        logical CheckCO ( );
public     :                                        logical CheckSourceValue (node *source_node );
public     :                                        logical CheckType (DBFieldDef *fielddef );
public     :                                        logical CheckValue (node *source_node );
public     :                                        void CopyEnvironment (OperEnvironment *operenv, logical intern_opt=NO );
public     :                                        OPBase *CreateBStatement (BNFData *bdata );
public     :                                        OPBase *CreateBinOp (BNFData *oper_bnf );
public     :                                        OPBase *CreateBlock (BNFData *bdata, OQL_CodeBlock blktype=CB_undefined );
public     :                                        OPBase *CreateCase (BNFData *bdata );
public     :                                        OPBase *CreateDOperand (BNFData *bdata );
public     :                                        logical CreateEnvironment (Dictionary *dictionary, ACObject *resobj, DBStructDef *scope_str, BNFData *bdata, ACObject *obhandle, PropertyHandle *co, OPDecl *op_decl, char *expr_dup_w=NULL );
public     :                                        logical CreateGlobalVariable ( );
public     : static                                 OPBase *__cdecl CreateNode (ADT_Types source_type, FunctionTypes optype, OPBase *parent_node, char *clsname, BNFData *oper_bnf, BNFData *parm_bnf );
public     :                                        OPBase *CreateOperand (BNFData *bdata );
public     : static                                 OPBase *__cdecl CreateOperandNode (OPBase *parent_node, BNFData *srce_def );
public     : static                                 OPBase *__cdecl CreateOperandNode (ADT_Types source_type, OPBase *parent_node, char *clsname, BNFData *oper_bnf, BNFData *parm_bnf );
public     : static                                 OPBase *__cdecl CreateOperationNode (FunctionTypes op_type, OPBase *parent_node, char *clsname, BNFData *oper_bnf, BNFData *parm_bnf );
public     : static                                 OPBase *__cdecl CreateOperationNode (FunctionTypes op_type, OPBase *parent_node, DBStructDef *class_ref, BNFData *oper_bnf, BNFData *parm_bnf );
public     : static                                 OPBase *__cdecl CreatePathElementNode (OPBase *parent_node, BNFData *srce_def, char *clsname );
public     :                                        OPBase *CreateSimpleOp (BNFData *bdata );
public     :                                        OPBase *CreateStatement (BNFData *bdata );
public     :                                        OPBase *CreateStatementOpList (BNFData *bdata );
public     :                                        OPBase *CreateUniOp (BNFData *oper_bnf );
public     :                                        OPDecl *Declaration ( );
public     :                                        Dictionary *DictHandle ( );
public     :                                        OperEnvironment *Environment ( );
public     : virtual                                ExecReturnCodes Execute ( );
public     :                                        ExecReturnCodes ExecuteTrace (OPBase *op_node );
public     : virtual                                logical Get ( );
public     :                                        char *GetAutoRun ( );
public     : virtual                                OQL_CodeBlock GetBlockType ( );
public     :                                        char *GetCurrentLine ( );
public     :                                        DBFieldDef *GetDescription ( );
public     :                                        char *GetExpression ( );
public     :                                        OPDecl *GetExpressionDecl ( );
public     :                                        ExtentList *GetExtentList ( );
public     :                                        DBFieldDef *GetFieldDef ( );
public     : virtual                                OPBase *GetOPNode ( );
public     : static                                 FunctionTypes __cdecl GetOperationType (OperEnvironment *operenv, DBStructDef *classref, char *opname );
public     : static                                 FunctionTypes __cdecl GetOperationType (OperEnvironment *operenv, char *opname, DBStructDef *classref );
public     : static                                 DBStructDef *__cdecl GetParentType (OPBase *parent_node, char *clsname );
public     :                                        DBFieldDef *GetParmDescription (int32 indx0 );
public     :                                        PropertyHandle *GetParmValue (int32 indx0 );
public     :                                        ParmList *GetParmlist ( );
public     :                                        OPDecl *GetPreviousOPDecl ( );
public     : virtual                                int16 GetPriority ( );
public     :                                        PropertyHandle GetPropertyHandle (char *prop_path );
public     :                                        int16 GetReopen ( );
public     :                                        DBStructDef *GetScope ( );
public     : virtual                                PropertyHandle *GetValue ( );
public     : virtual                                OPVariable *GetVariable ( );
public     : static                                 void __cdecl InitDebug (char *proc_path );
public     :                                        void InitDescription (DBFieldDef *fielddef );
public     : virtual                                logical InitResult (PropertyHandle *co );
public     : virtual                                logical InitResult ( );
public     :                                        OPBase *InitSource (BNFData *oper_bnf );
public     :                                        logical InitValue ( );
public     : virtual                                logical Initialize (int32 ini_opt );
public     : static                                 FunctionTypes __cdecl IsAction (char *opname, smcb *smcbptr );
public     :                                        logical IsDebug ( );
public     : static                                 FunctionTypes __cdecl IsEnumeration (Dictionary *dictionary, char *opname );
public     : static                                 FunctionTypes __cdecl IsExpression (OperEnvironment *operenv, char *opname, smcb *smcbptr );
public     : static                                 FunctionTypes __cdecl IsExtent (Dictionary *dictionary, char *opname );
public     : static                                 FunctionTypes __cdecl IsFunction (Dictionary *dictionary, ACObject *resobj, char *opname, smcb *smcbptr );
public     : static                                 FunctionTypes __cdecl IsGlobalExpression (Dictionary *dictionary, char *opname );
public     : static                                 FunctionTypes __cdecl IsGlobalVariable (Dictionary *dictionary, char *opname );
public     :                                        logical IsInline ( );
public     :                                        logical IsIntern ( );
public     : virtual                                logical IsOrdered ( );
public     : static                                 FunctionTypes __cdecl IsPHFunction (Dictionary *dictionary, DBStructDef *classref, PropertyHandle *co, char *opname );
public     : static                                 FunctionTypes __cdecl IsProperty (smcb *smcbptr, char *opname );
public     : virtual                                logical IsSetOperand ( );
public     :                                        FunctionTypes IsStandardOperation (PropertyHandle *co, ST_OpCodes op_code );
public     : static                                 FunctionTypes __cdecl IsSysFunction (char *opname );
public     :                                        node *LastValue ( );
public     : virtual                                logical ListCallStack (int32 count );
public     : virtual                                DBStructDef *LocalScope ( );
public     : virtual                                void MarkResetScope (logical rscope );
public     : virtual                                logical Next ( );
public     :                                             OPBase (BNFData *oper_bnf, OPBase *parent_node );
public     :                                        char *OPName ( );
public     :                                        ACObject *ObjectHandle ( );
public     :                                        logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                                        logical Output (char *fstring, int32 intval, char *parm1=NULL, char *parm2=NULL );
public     :                                        OPParmList *Parameters ( );
public     : virtual                                logical ParentHasChanged ( );
public     : virtual                                OPParmList *Parmlist ( );
public     :                                        void PopCO ( );
public     :                                        logical Position (int32 &count_ref );
public     : virtual                                logical Previous ( );
public     :                                        logical ProvideBStatement (BNFData *bdata );
public     :                                        logical ProvideBlock (BNFData *bdata, OQL_CodeBlock blktype=CB_undefined );
public     : static                                 PropertyHandle *__cdecl ProvideCO (PropertyHandle &prophdl, Dictionary *dictionary, DBStructDef *classref );
public     :                                        DBFieldDef *ProvideDescription ( );
public     :                                        logical ProvideSimpleOp (BNFData *bdata );
public     :                                        logical ProvideStatement (BNFData *bdata );
public     :                                        logical ProvideStatementOpList (BNFData *bdata );
public     :                                        logical ProvideStatementOperands (BNFData *bdata );
public     :                                        logical ProvideStatements (BNFData *bdata, int32 indx0 );
public     :                                        void PushCO (PropertyHandle *co );
public     :                                        void RegisterLastValue ( );
public     :                                        ACObject *ResOBHandle ( );
public     : virtual                                logical ResetScope ( );
public     : virtual                                void ResetValue ( );
public     :                                        SchemaResources *Schema ( );
public     :                                        DBStructDef *Scope ( );
public     :                                        logical SetBreakPoint (logical bp_opt );
public     :                                        logical SetBreakPoint (BNFData *bdata );
public     :                                        logical SetBreakPoint (char *name );
public     :                                        logical SetCO (PropertyHandle *co );
public     :                                        logical SetDescription (DBFieldDef *fielddef );
public     :                                        logical SetDescription ( );
public     :                                        void SetLastValue (node *nodeptr );
public     : virtual                                void SetMaxPriority ( );
public     :                                        void SetOPName (char *op_name );
public     :                                        void SetParent (OPBase *parent_node );
public     :                                        void SetParmCount (int32 parm_count );
public     :                                        logical SetReference (node *source_node );
public     :                                        void SetReopen (int32 ini_opt );
public     :                                        void SetScope (DBStructDef *strdef );
public     :                                        void SetSource (OPBase *op_node );
public     :                                        logical SetUpperCO ( );
public     : virtual                                logical SetValue (node *source_node );
public     :                                        logical SetValueOrReference (node *source_node );
public     :                                        void Set_OPName (char *op_name );
public     :                                        void SetupEnvironment ( );
public     :                                        void ShowError (BNFData *oper_bnf, char *name1=NULL, char *name2=NULL, char *name3=NULL, char *name4=NULL );
public     :                                        void ShowError (int32 err_code, char *obj_id, char *mod_id, BNFData *oper_bnf );
public     :                                        OPBase *Source ( );
public     :                                        node *SourceNode ( );
public     :                                        NodeStack *Stack ( );
public     : virtual                                logical StoreValue ( );
public     : virtual                                logical ToTop (logical recursive );
public     :                                        void TraceCalls (ExecReturnCodes exec_rc );
public     : virtual                                node *Value ( );
public     :                                        OPParmList *Variables ( );
public     : virtual                                     ~OPBase ( );
};

#pragma pack()
#endif
