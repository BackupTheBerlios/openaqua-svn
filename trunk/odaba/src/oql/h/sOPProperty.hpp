/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OPProperty

\brief    


\date     $Date: 2006/04/19 14:31:32,85 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPProperty_HPP
#define   OPProperty_HPP

class     OPProperty;

class     BNFData;
class     OPBase;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
#include  <sPropertyHandle.hpp>
class  OPProperty :public OPVariable
{
protected  :         logical                                      is_static;                                                 

public     :
                     logical                                      get_is_static() { return(is_static); }
public     :                                     logical InitDescription ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPProperty (DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                     logical OpenValue ( );
public     :                                     logical SetupSetOperation ( );
public     :                                                             ~OPProperty ( );
};

#endif
