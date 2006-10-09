/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPOperationDecl

\brief    


\date     $Date: 2006/03/12 19:20:08,76 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPOperationDecl_HPP
#define   OPOperationDecl_HPP

class     OPOperationDecl;

class     OPParmList;
class     OperEnvironment;
class     node;
#include  <sOPDecl.hpp>
#include  <sPropertyHandle.hpp>
class  OPOperationDecl :public OPDecl
{
protected  :         ST_OpCodes                                   op_code;                                                   //

public     :
public     :                                     logical Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     :                                     logical ExecuteOperation (node *operand_node );
public     : virtual                             logical InitResult ( );
public     :                                                             OPOperationDecl (ST_OpCodes opcode, OPBase *parent_node );
public     :                                     logical SetupResult ( );
public     :                                                             ~OPOperationDecl ( );
};

#endif
