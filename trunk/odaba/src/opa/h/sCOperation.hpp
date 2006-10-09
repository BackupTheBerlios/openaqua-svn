/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    COperation

\brief    Opreartion Handle
          Operation  handles can be used for executing operations as expressions
          or  function  calls.  Usually,  an  operation  is  associated  with  a
          property  handle defining the instance that is passed to the operation
          as calling object.

\date     $Date: 2006/04/05 23:14:28,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   COperation_HPP
#define   COperation_HPP

class     COperation;

class     ACObject;
class     BNFData;
class     Dictionary;
class     ParmList;
#include  <sCSHandle.hpp>
#include  <sInstance.hpp>
#include  <sOperation.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  COperation :public CSHandle,
public Operation
{

public     :
public     :         OPAImpExp                                           COperation (PropertyHandle &prophdl_ref );
public     :                                     logical CheckResultDef ( );
public     : virtual                             logical Execute (ParmList *parameters );
public     :         OPAImpExp                   logical Open (PropertyHandle &prophdl_ref );
public     :         OPAImpExp                   logical ProvExpression (Dictionary *dictionary, ACObject *resobj, ACObject *obhandle, char *expr_string );
public     :         OPAImpExp                   logical ProvExpression (Dictionary *dictionary, ACObject *resobj, ACObject *obhandle, char *clsnames, char *exprnames, ParmList *parmlist, logical refresh_opt=NO );
public     :                                     Instance SetupInstance (logical error_case );
public     :                                     logical SetupResult_intern (logical error_case );
public     : virtual                                                     ~COperation ( );
};

#pragma pack()
#endif
