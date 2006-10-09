/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPExtent

\brief    


\date     $Date: 2006/03/12 19:20:06,15 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPExtent_HPP
#define   OPExtent_HPP

class     OPExtent;

class     BNFData;
class     OPBase;
#include  <sOPVariable.hpp>
class  OPExtent :public OPVariable
{

public     :
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPExtent (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                                             ~OPExtent ( );
};

#endif
