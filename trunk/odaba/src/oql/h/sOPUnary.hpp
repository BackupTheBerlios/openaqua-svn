/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPUnary

\brief    


\date     $Date: 2006/03/12 19:20:14,09 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPUnary_HPP
#define   OPUnary_HPP

class     OPUnary;

class     BNFData;
class     OPBase;
#include  <cST_OpCodes.h>
#include  <sOPOperation.hpp>
class  OPUnary :public OPOperation
{
protected  :         int8                                         data_type;                                                 //
protected  :         ST_OpCodes                                   op_code;                                                   //

public     :
                     int8                                         get_data_type() { return(data_type); }
public     :                                     ST_OpCodes GetOpType (BNFData *bdata );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPUnary (BNFData *oper_bnf, OPBase *parent_node );
public     :                                     logical ProvideOperands ( );
public     :                                                             ~OPUnary ( );
};

#endif
