/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    OperEnvironment

\brief    


\date     $Date: 2006/07/16 17:52:38,04 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OperEnvironment_HPP
#define   OperEnvironment_HPP

class     OperEnvironment;

class     ACObject;
class     BNFData;
class     Dictionary;
class     ExtentList;
class     NodeStack;
class     OPBase;
class     OPDecl;
class     OPParmList;
class     OperEnvironment;
class     OperResources;
class     ParmList;
class     SchemaResources;
class     node;
#include  <cExecReturnCodes.h>
#include  <cVHN_Types.h>
#include  <sPIStack.hpp>
#include  <sPropertyHandle.hpp>
class  OperEnvironment
{
protected  :         SchemaResources                             *resources;                                                 // 
protected  :         NodeStack                                   *stack;                                                     // 
protected  :         char                                        *expression;                                                // 
protected  :         BNFData                                     *expr_bnf;                                                  // 
protected  :         DBStructDef                                 *scope;                                                     // 
protected  :         PIStack                                      calling_object;                                            // 
protected  :         OPParmList                                  *variables;                                                 // 
protected  :         OPParmList                                  *parameters;                                                // 
protected  :         int16                                        calling_parms;                                             // 
protected  :         logical                                      intern_env;                                                // 
protected  :         PropertyHandle                               last_executed;                                             // 
protected  :         int32                                        last_ityp;                                                 // 
protected  :         int64                                        last_inst;                                                 // 
protected  :         OPDecl                                      *declaration;                                               // 
protected  :         OperEnvironment                             *prev_env;                                                  // 
protected  :         VHN_Types                                    nvh_type;                                                  // 
protected  :         VHN_Types                                    exh_type;                                                  // 
protected  :         ExtentList                                  *extent_list;                                               // 

public     :
                     SchemaResources                             *get_resources() { return(resources); }
                     NodeStack                                   *get_stack() { return(stack); }
                     char                                        *get_expression() { return(expression); }
                     BNFData                                     *get_expr_bnf() { return(expr_bnf); }
                     DBStructDef                                 *get_scope() { return(scope); }
                     PIStack                                     &get_calling_object() { return(calling_object); }
                     OPParmList                                  *get_variables() { return(variables); }
                     OPParmList                                  *get_parameters() { return(parameters); }
                     int16                                        get_calling_parms() { return(calling_parms); }
                     logical                                      get_intern_env() { return(intern_env); }
                     PropertyHandle                              &get_last_executed() { return(last_executed); }
                     int32                                        get_last_ityp() { return(last_ityp); }
                     int64                                        get_last_inst() { return(last_inst); }
                     OPDecl                                      *get_declaration() { return(declaration); }
                     OperEnvironment                             *get_prev_env() { return(prev_env); }
                     VHN_Types                                    get_nvh_type() { return(nvh_type); }
                     VHN_Types                                    get_exh_type() { return(exh_type); }
                     ExtentList                                  *get_extent_list() { return(extent_list); }
public     :                                        PropertyHandle *CO ( );
public     :                                        int16 CallingParmCount ( );
public     :                                        logical Copy (OperEnvironment *operenv, logical intern_opt=NO );
public     :                                        BNFData *CreateExpression (PropertyHandle *impl_ph );
public     :                                        logical CreateGlobals (PropertyHandle *var_ph );
public     :                                        Dictionary *DictHandle ( );
public     :                                        ExecReturnCodes GetExceptionERC ( );
public     :                                        char *GetExpression ( );
public     :                                        OPDecl *GetExpressionDecl ( );
public     :                                        ExtentList *GetExtentList ( );
public     :                                        ExecReturnCodes GetNullValueERC ( );
public     :                                        DBFieldDef *GetParameterDef (char *varnames );
public     :                                        node *GetParameterNode (char *varnames );
public     :                                        OPDecl *GetPreviousOPDecl ( );
public     :                                        int16 GetReopen (PropertyHandle *co );
public     :                                        DBFieldDef *GetVariableDef (char *varnames );
public     :                                        node *GetVariableNode (char *varnames );
public     :                                        ACObject *ObjectHandle ( );
public     :                                             OperEnvironment (Dictionary *dictptr, ACObject *resobj, DBStructDef *scope_str, BNFData *bdata, ACObject *obhandle, PropertyHandle *co, OPDecl *op_decl, char *expr_dup_w=NULL );
public     :                                             OperEnvironment ( );
public     :                                        OPParmList *Parameters ( );
public     :                                        void PopCO ( );
public     :                                        void PushCO (PropertyHandle *co );
public     :                                        ACObject *ResOBHandle ( );
public     :                                        logical Reset (logical intern_opt=NO );
public     :                                        int32 SetCO (PropertyHandle *co );
public     :                                        void SetExceptionHandling (VHN_Types ex_handling );
public     :                                        BNFData *SetExpression (char *expr_string, char *bsymbol );
public     :                                        void SetNVHType (VHN_Types nv_handling );
public     :                                        void SetParmCount (int32 parm_count );
public     :                                        void SetPreviousEnvironment (OperEnvironment *operenv );
public     :                                        void SetScope (DBStructDef *strdef );
public     :                                        logical SetUpperCO ( );
public     :                                        logical SetupEnvironment ( );
public     :                                        NodeStack *Stack ( );
public     :                                        OPParmList *Variables ( );
public     :                                        void set_last_executed (node *nodeptr );
public     :                                             ~OperEnvironment ( );
};

#endif
