/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPGlobalVariable

\brief    


\date     $Date: 2006/03/12 19:20:07,20 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPGlobalVariable_HPP
#define   OPGlobalVariable_HPP

class     OPGlobalVariable;

class     BNFData;
class     Dictionary;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
#include  <sPropertyHandle.hpp>
class  OPGlobalVariable :public OPVariable
{

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPGlobalVariable (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPGlobalVariable ( );
};

#endif
