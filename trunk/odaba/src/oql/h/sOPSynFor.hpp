/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynFor

\brief    


\date     $Date: 2006/03/12 19:20:11,84 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynFor_HPP
#define   OPSynFor_HPP

class     OPSynFor;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <sOPOperation.hpp>
class  OPSynFor :public OPOperation
{

public     :
public     :                                     logical CreateStatements ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynFor (BNFData *oper_bnf, OPBase *parent_node );
public     :                                                             ~OPSynFor ( );
};

#endif
