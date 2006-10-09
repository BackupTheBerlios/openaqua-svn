/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynWhile

\brief    


\date     $Date: 2006/03/12 19:20:13,42 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynWhile_HPP
#define   OPSynWhile_HPP

class     OPSynWhile;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <sOPOperation.hpp>
class  OPSynWhile :public OPOperation
{

public     :
public     :                                     logical CreateStatements ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynWhile (BNFData *oper_bnf, OPBase *parent_node );
public     :                                                             ~OPSynWhile ( );
};

#endif
