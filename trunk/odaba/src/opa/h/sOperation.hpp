/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    Operation



\date     $Date: 2006/05/20 20:18:40,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Operation_HPP
#define   Operation_HPP

class     Operation;

class     ACObject;
class     BNFData;
class     BNFExpData;
class     DBFieldDef;
class     DBHandle;
class     DBStructDef;
class     Dictionary;
class     OPDecl;
class     OperEnvironment;
class     ParmList;
class     node;
#include  <cFunctionTypes.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  Operation :public PropertyHandle
{
protected  :         OPDecl                                      *operation_decl;                                            
protected  :         PropertyHandle                              *calling_object;                                            
protected  :         char                                        *expression;                                                
protected  :         OperationHandle                             *op_handle;                                                 
protected  :         logical                                      is_owner;                                                  
protected  :         OperEnvironment                             *oper_env;                                                  

public     :
                     OPDecl                                      *get_operation_decl() { return(operation_decl); }
                     PropertyHandle                              *get_calling_object() { return(calling_object); }
                     char                                        *get_expression() { return(expression); }
                     OperationHandle                             *get_op_handle() { return(op_handle); }
                     logical                                      get_is_owner() { return(is_owner); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
public     :                  OPAImpExp             logical CheckExpression (Dictionary *dictptr, ACObject *obhandle, char *clsnames, char *exprnames, char *impnames );
public     :                  OPAImpExp             logical CheckExpression (Dictionary *dictptr, char *expression, ACObject *obhandle, char *clsnames );
public     :                                        void Close ( );
public     : virtual          OPAImpExp             logical Execute (ParmList *parmlist );
public     : virtual          OPAImpExp             logical Execute (PropertyHandle *co, ParmList *parmlist );
public     : virtual          OPAImpExp             logical Execute (ACObject *obhandle, ParmList *parmlist );
public     : virtual          OPAImpExp             int32 GetDimension ( );
public     :                  OPAImpExp             DBFieldDef *GetRetvalDefinition ( );
public     : virtual          OPAImpExp             int32 GetSize ( );
public     :                                        logical InitResult (PropertyHandle &prophdl_ref );
public     :                  OPAImpExp             logical IsDefined ( );
public     : virtual          OPAImpExp             logical Open (PropertyHandle &prophdl_ref, OperEnvironment *operenv_w=NULL );
public     :                  OPAImpExp                  Operation (PropertyHandle &prophdl_ref, OperEnvironment *operenv_w=NULL );
public     :                  OPAImpExp                  Operation (OperEnvironment *operenv_w=NULL );
public     : virtual          OPAImpExp             logical ProvAccessPath (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, BNFData *oper_bnf, char *prop_path, char *clsnames );
public     : virtual          OPAImpExp             logical ProvAccessPath (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, char *expr_string );
public     : virtual          OPAImpExp             logical ProvAccessPath (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, BNFData *bnf_data );
public     : virtual          OPAImpExp             logical ProvExpression (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, char *clsnames, char *exprnames, ParmList *parmlist, logical refresh_opt=NO );
public     : virtual          OPAImpExp             logical ProvExpression (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, char *expr_string );
public     : virtual          OPAImpExp             logical ProvExpression (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, BNFData *bnf_data );
public     : virtual          OPAImpExp             logical ProvFunction (Dictionary *dictptr, ACObject *obhandle, char *clsnames, char *fnames, ParmList *parmlist );
public     : virtual          OPAImpExp             logical ProvFunction (Dictionary *dictptr, char *clsnames, char *fnames, ParmList *parmlist );
public     :                  OPAImpExp             logical Remove ( );
public     :                                        void SetCallingObject (PropertyHandle *prop_handle );
public     :                                        void SetEnvironment (OperEnvironment *operenv );
public     :                                        void SetHandle (OperationHandle *operation_handle );
public     :                                        void set_expression (char *expr_string );
public     : virtual          OPAImpExp                  ~Operation ( );
};

#pragma pack()
#endif
