/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPBinary

\brief    


\date     $Date: 2006/03/12 19:20:02,71 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPBinary_HPP
#define   OPBinary_HPP

class     OPBinary;

class     BNFData;
class     OPBase;
#include  <cST_OpCodes.h>
#include  <sOPOperation.hpp>
class  OPBinary :public OPOperation
{
protected  :         int8                                         data_type;                                                 //
protected  :         ST_OpCodes                                   op_code;                                                   //
protected  :         int16                                        priority;                                                  //
protected  :         logical                                      max_priority;                                              //

public     :
                     int8                                         get_data_type() { return(data_type); }
                     int16                                        get_priority() { return(priority); }
                     logical                                      get_max_priority() { return(max_priority); }
public     :                                     ST_OpCodes GetOpType (BNFData *bdata );
public     : virtual                             int16 GetPriority ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPBinary (BNFData *oper_bnf, OPBase *parent_node );
public     :                                     OPBase *OrderOperands ( );
public     :                                     logical ProvideOperands ( );
public     : virtual                             void SetMaxPriority ( );
public     : virtual                             void SetPriority (ST_OpCodes lst_opcode );
public     :                                                             ~OPBinary ( );
};

#endif
