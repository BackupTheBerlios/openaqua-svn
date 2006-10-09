/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynException

\brief    


\date     $Date: 2006/03/12 19:20:11,50 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynException_HPP
#define   OPSynException_HPP

class     OPSynException;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <sOPOperation.hpp>
#include  <sOPSynError.hpp>
class  OPSynException :public OPOperation
{

public     :
public     :                                     ExecReturnCodes Execute ( );
public     :                                     void InitLastExceptionCode (int32 err_code );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynException (OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPSynException ( );
};

#endif
