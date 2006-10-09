/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPEnumeration

\brief    


\date     $Date: 2006/03/12 19:20:04,71 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPEnumeration_HPP
#define   OPEnumeration_HPP

class     OPEnumeration;

#define  SYS_NSID                                  0
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
class  OPEnumeration :public OPVariable
{

public     :
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPEnumeration (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPEnumeration ( );
};

#endif
