/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynError

\brief    


\date     $Date: 2006/03/12 19:20:11,20 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynError_HPP
#define   OPSynError_HPP

class     OPSynError;

class     BNFData;
class     OPBase;
#include  <cExecReturnCodes.h>
#include  <sOPOperation.hpp>
class  OPSynError :public OPOperation
{

public     :
public     :                                     ExecReturnCodes Execute ( );
public     :                                     void InitLastErrorCode (int32 err_code );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynError (OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPSynError ( );
};

#endif
