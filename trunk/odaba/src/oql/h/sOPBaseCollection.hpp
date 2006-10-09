/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPBaseCollection

\brief    


\date     $Date: 2006/03/12 19:20:02,48 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPBaseCollection_HPP
#define   OPBaseCollection_HPP

class     OPBaseCollection;

class     ACObject;
class     BNFData;
class     ParmList;
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
class  OPBaseCollection :public OPVariable
{

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPBaseCollection (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPBaseCollection ( );
};

#endif
