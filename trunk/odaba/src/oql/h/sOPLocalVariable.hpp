/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPLocalVariable

\brief    


\date     $Date: 2006/03/12 19:20:07,42 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPLocalVariable_HPP
#define   OPLocalVariable_HPP

class     OPLocalVariable;

class     BNFData;
class     ParmList;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
class  OPLocalVariable :public OPVariable
{

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPLocalVariable (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPLocalVariable ( );
};

#endif
