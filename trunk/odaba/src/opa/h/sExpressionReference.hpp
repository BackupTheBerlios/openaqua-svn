/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ExpressionReference

\brief    


\date     $Date: 2006/03/12 19:13:22,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExpressionReference_HPP
#define   ExpressionReference_HPP

class     ExpressionReference;

class     BNFData;
class     DBFieldDef;
class     DBStructDef;
class     Dictionary;
class     OPDecl;
class     OPExpressionDecl;
class     ParmList;
#include  <cADT_Types.h>
#include  <sExpressionReference.hpp>
#include  <sPropertyHandle.hpp>
class  ExpressionReference
{
protected  :         char                                        *string;                                                    //
protected  :         BNFData                                     *bnf;                                                       //
protected  :         OPDecl                                      *expr_decl;                                                 //
protected  :         ADT_Types                                    type;                                                      //
protected  :         DBStructDef                                 *structure;                                                 //
protected  :         OperEnvironment                             *oper_env;                                                  //

public     :
                     char                                        *get_string() { return(string); }
                     BNFData                                     *get_bnf() { return(bnf); }
                     OPDecl                                      *get_expr_decl() { return(expr_decl); }
                     ADT_Types                                    get_type() { return(type); }
                     DBStructDef                                 *get_structure() { return(structure); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
public     :                                     logical Execute (PropertyHandle &retval_ref, PropertyHandle *co, ParmList *variables, ParmList *parameters );
public     :                                                             ExpressionReference (DBStructDef *struct_def, char *expression );
public     :                                                             ExpressionReference (ExpressionReference &exprref );
public     :                                                             ExpressionReference (DBStructDef *struct_def, BNFData *expr_bnf );
public     :                                     BNFData *GetBNFData (Dictionary *dictptr );
public     :                                     OPDecl *GetExpressionDecl (Dictionary *dictptr );
public     :                                     DBFieldDef *GetResultDescription (Dictionary *dictptr );
public     :                                     char *GetString ( );
public     :                                     void ReleaseExpression ( );
public     :                                     void SetExpression (char *expression );
public     :                                     void SetOperEnvironment (OperEnvironment *operenv );
public     :                                     void SetStructDef (DBStructDef *struct_def );
public     :                                                             ~ExpressionReference ( );
};

#endif
