/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPParameter

\brief    


\date     $Date: 2006/03/12 19:20:09,15 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPParameter_HPP
#define   OPParameter_HPP

class     OPParameter;

class     BNFData;
class     OPBase;
class     ParmList;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
class  OPParameter :public OPVariable
{

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPParameter (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPParameter ( );
};

#endif
