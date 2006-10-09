/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynCase

\brief    


\date     $Date: 2006/03/12 19:20:10,60 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynCase_HPP
#define   OPSynCase_HPP

class     OPSynCase;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <cOQL_CodeBlock.h>
#include  <sOPOperation.hpp>
class  OPSynCase :public OPOperation
{
protected  :         OQL_CodeBlock                                block_type;                                                //

public     :
public     :                                     logical CreateStatements ( );
public     :                                     ExecReturnCodes Execute ( );
public     : virtual                             OQL_CodeBlock GetBlockType ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynCase (BNFData *oper_bnf, OPBase *parent_node );
public     :                                                             ~OPSynCase ( );
};

#endif
