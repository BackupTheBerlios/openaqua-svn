/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynIf

\brief    


\date     $Date: 2006/03/12 19:20:12,14 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynIf_HPP
#define   OPSynIf_HPP

class     OPSynIf;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <cOQL_CodeBlock.h>
#include  <sOPOperation.hpp>
class  OPSynIf :public OPOperation
{

public     :
public     :                                     logical CreateStatements ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynIf (BNFData *oper_bnf, OPBase *parent_node );
public     :                                                             ~OPSynIf ( );
};

#endif
