/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPUnary

\brief    


\date     $Date: 2006/03/12 19:21:05,68 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPUnary"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPUnary.hpp>


/******************************************************************************/
/**
\brief  GetOpType - 


\return st_opcode

\param  bdata -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOpType"

ST_OpCodes OPUnary :: GetOpType (BNFData *bdata )
{
  ST_OpCodes         st_opcode = ST_undefined;
  return (   bdata->IsValue("-")        ? ST_minus
           : bdata->IsSymbol("_not")    ? ST_not
           : bdata->IsValue("--")       ? ST_decrement
           : bdata->IsValue("++")       ? ST_increment
                                        : ST_undefined   );

  return(st_opcode);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPUnary :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
// operation   := simple_op bin_operand
// bin_operand := bin_op operand
  
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : ProvideOperands();
              if ( SetupSource() )                   ERROR
              if ( CreateOperation(op_code) )        ERROR
              SetupResult();   
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPUnary - 


\return term

\param  oper_bnf -
\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPUnary"

                        OPUnary :: OPUnary (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL)
{

  op_type = NT_OPUnary;

  Initialize(0);


}

/******************************************************************************/
/**
\brief  ProvideOperands - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideOperands"

logical OPUnary :: ProvideOperands ( )
{
  BNFData                *oper;
  logical                 term = NO;
// un_operation  := un_oper simple_op	
// un_oper       := un_op | cast_op
// cast_op       := '(' simple_type_spec ')'

  oper = operand_bnf->GetElement(0);
  if ( oper->IsSymbol("cast_op") )
  {
    op_code = ST_typecast;
    parm_bnf = oper->GetElement("simple_type_spec");       // type spec
  }
  else
    op_code =  GetOpType(oper->GetElement("un_op"));       // un_op
  operand_bnf = operand_bnf->GetElement(1);                // operand
    
  SetOPName(operand_bnf->GetElement(0)->StringValue());
  return(term);
}

/******************************************************************************/
/**
\brief  ~OPUnary - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPUnary"

                        OPUnary :: ~OPUnary ( )
{



}


