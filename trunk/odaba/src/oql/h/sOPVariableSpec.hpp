/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPVariableSpec

\brief    Variable definitions
          Specific re-open codes are
          10: init value at beginning of procedure
          11: de-init value at ent of procedure

\date     $Date: 2006/03/12 19:20:15,42 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPVariableSpec_HPP
#define   OPVariableSpec_HPP

class     OPVariableSpec;

class     BNFData;
class     ParmList;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>
#include  <sOPVariable.hpp>
#include  <sPIStack.hpp>
class  OPVariableSpec :public OPVariable
{
protected  :         PIStack                                      init_value;                                                //

public     :
public     :                                     logical CreateInitValue ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     PropertyHandle *GetValue ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPVariableSpec (DBFieldDef *fielddef, OPBase *parent_node );
public     :                                     void PopValue ( );
public     :                                     ExecReturnCodes PushValue ( );
public     :                                     node *Value ( );
public     :                                                             ~OPVariableSpec ( );
};

#endif
