/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPSystemVariable

\brief    


\date     $Date: 2006/04/03 12:31:43,87 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPSystemVariable_HPP
#define   OPSystemVariable_HPP

class     OPSystemVariable;

class     BNFData;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>
#include  <sPropertyHandle.hpp>
class  OPSystemVariable :public OPBase
{

public     :
public     :                                     ExecReturnCodes Execute ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPSystemVariable (BNFData *oper_bnf, OPBase *parent_node );
public     :                                     logical SetValue (node *source_node );
public     :                                     logical Store ( );
public     :                                                             ~OPSystemVariable ( );
};

#endif
