/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPConstant

\brief    


\date     $Date: 2006/03/12 19:20:03,21 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPConstant_HPP
#define   OPConstant_HPP

class     OPConstant;

class     BNFData;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>
#include  <sPropertyHandle.hpp>
class  OPConstant :public OPBase
{

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPConstant (BNFData *oper_bnf, OPBase *parent_node );
public     :                                     void OpenValue (BNFData *oper_bnf );
public     :                                     void ResetValue ( );
public     :                                                             ~OPConstant ( );
};

#endif
