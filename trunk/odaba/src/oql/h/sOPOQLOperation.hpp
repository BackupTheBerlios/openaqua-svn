/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPOQLOperation

\brief    


\date     $Date: 2006/04/01 20:19:34,60 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPOQLOperation_HPP
#define   OPOQLOperation_HPP

class     OPOQLOperation;

class     BNFData;
class     OPBase;
#include  <sOPVariable.hpp>
class  OPOQLOperation :public OPVariable
{
protected  :         ST_OpCodes                                   op_code;                                                   // 

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPOQLOperation (ST_OpCodes op_code, DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPOQLOperation ( );
};

#endif
