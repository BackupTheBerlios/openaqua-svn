/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynSwitch

\brief    


\date     $Date: 2006/03/12 19:20:13,12 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynSwitch_HPP
#define   OPSynSwitch_HPP

class     OPSynSwitch;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <sOPOperation.hpp>
class  OPSynSwitch :public OPOperation
{

public     :
public     :                                     logical CreateStatements ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynSwitch (BNFData *oper_bnf, OPBase *parent_node );
public     :                                                             ~OPSynSwitch ( );
};

#endif
