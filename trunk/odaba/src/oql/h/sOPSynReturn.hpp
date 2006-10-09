/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynReturn

\brief    


\date     $Date: 2006/03/12 19:20:12,89 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSynReturn_HPP
#define   OPSynReturn_HPP

class     OPSynReturn;

class     BNFData;
#include  <sOPOperation.hpp>
class  OPSynReturn :public OPOperation
{

public     :
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSynReturn (OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPSynReturn ( );
};

#endif
