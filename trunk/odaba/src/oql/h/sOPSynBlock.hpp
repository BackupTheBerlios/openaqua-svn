/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynBlock

\brief    


\date     $Date: 2006/03/12 19:20:10,04 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynBlock_HPP
#define   OPSynBlock_HPP

class     OPSynBlock;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <cOQL_CodeBlock.h>
#include  <sOPOperation.hpp>
class  OPSynBlock :public OPOperation
{
protected  :         OQL_CodeBlock                                block_type;                                                //

public     :
public     :                                     logical CreateStatements ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     OQL_CodeBlock GetBlockType ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynBlock (BNFData *oper_bnf, OPBase *parent_node, OQL_CodeBlock blktype=CB_undefined );
public     :                                                             ~OPSynBlock ( );
};

#endif
