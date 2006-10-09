/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPAccessPathDecl

\brief    


\date     $Date: 2006/03/12 19:19:55,32 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPAccessPathDecl_HPP
#define   OPAccessPathDecl_HPP

class     OPAccessPathDecl;

class     ACObject;
class     BNFData;
class     Dictionary;
class     OPAccessPath;
class     OPParmList;
class     OperEnvironment;
class     ParmList;
class     PropertyHandle;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPDecl.hpp>
class  OPAccessPathDecl :public OPDecl
{

public     :
public     :                                     logical Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     :                                     logical Call (PropertyHandle *co, ParmList *parm_list, int8 set_operation=NO );
public     :                                     logical Create ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                                             OPAccessPathDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, char *expr_string, OperEnvironment *operenv_w=NULL );
public     :                                                             OPAccessPathDecl (OperEnvironment *operenv, PropertyHandle *co, BNFData *oper_bnf );
public     :                                                             OPAccessPathDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, BNFData *oper_bnf, OperEnvironment *operenv_w=NULL, char *expr_dup_w=NULL );
public     : virtual                             logical Position (int32 count );
public     :                                                             ~OPAccessPathDecl ( );
};

#endif
