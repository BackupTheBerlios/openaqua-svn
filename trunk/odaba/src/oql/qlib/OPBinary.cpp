/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPBinary

\brief    


\date     $Date: 2006/06/12 13:34:15,68 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPBinary"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPBinary.hpp>


/******************************************************************************/
/**
\brief  GetOpType - 


\return st_opcode - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOpType"

ST_OpCodes OPBinary :: GetOpType (BNFData *bdata )
{
  ST_OpCodes         st_opcode = ST_undefined;
  return (   bdata->IsValue("-")          ? ST_minus
           : bdata->GetSymbol("_and")     ? ST_and
           : bdata->GetSymbol("_or")      ? ST_or
           : bdata->GetSymbol("_xor")     ? ST_xor
           : bdata->IsValue("^")          ? ST_power
           : bdata->IsValue("%")          ? ST_remainder
           : bdata->IsValue("+")          ? ST_plus
           : bdata->IsValue("*")          ? ST_multi
           : bdata->IsValue("/")          ? ST_divi
           : bdata->IsValue(">=")         ? ST_greaterEqual
           : bdata->IsValue(">")          ? ST_greater
           : bdata->IsValue("<=")         ? ST_lowerEqual
           : bdata->IsValue("<")          ? ST_lower
           : bdata->IsValue("<>")         ? ST_unequal
           : bdata->IsValue("!=")         ? ST_unequal
           : bdata->IsValue("==")         ? ST_equal
           : bdata->IsValue(":")          ? ST_assign
           : bdata->IsValue(":=")         ? ST_assign
           : bdata->IsValue("=")          ? ST_assign
           : bdata->IsValue("&=")         ? ST_assign_ref
           : bdata->IsValue("+=")         ? ST_plus_assign
           : bdata->IsValue("-=")         ? ST_minus_assign
           : bdata->IsValue("*=")         ? ST_mult_assign
           : bdata->IsValue("/=")         ? ST_divi_assign
           : bdata->IsValue(">>")         ? ST_shift_right
           : bdata->IsValue("<<")         ? ST_shift_left
                                          : ST_undefined      );

  return(st_opcode);
}

/******************************************************************************/
/**
\brief  GetPriority - 


\return priority - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPriority"

int16 OPBinary :: GetPriority ( )
{

  return(max_priority ? 999 : priority);

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPBinary :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
// operation   := un_operation bin_operand
// bin_operand := bin_op operand
  
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : ProvideOperands();
              if ( SetupSource() )                   ERROR
              if ( SetupParameters() )               ERROR
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
\brief  OPBinary - 


\return term - 

\param  oper_bnf - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPBinary"

     OPBinary :: OPBinary (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL),
  data_type(0),
  op_code(ST_undefined),
  priority(0),
  max_priority(NO)
{

  op_type = NT_OPBinary;

  Initialize(0);


}

/******************************************************************************/
/**
\brief  OrderOperands - 


\return op_node - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OrderOperands"

OPBase *OPBinary :: OrderOperands ( )
{
  OPBase                     *op_node  = this;
  OPBase                     *right    = NULL;
  OPBase                     *newright = NULL;

  right = Parmlist()->GetAt(0);
  if ( priority > right->GetPriority() )
  {
    Parmlist()->ElementAt(0) = right->Source();
    right->SetSource(this);
    op_node = right;
  }

  return(op_node);
}

/******************************************************************************/
/**
\brief  ProvideOperands - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideOperands"

logical OPBinary :: ProvideOperands ( )
{
  BNFData                *binop;
  logical                 term = NO;
// operand     := un_operation bin_operand   
// bin_operand := bin_op operand  

  binop       = operand_bnf->GetElement(1)->GetElement(0); // bin_op
  SetPriority(op_code = GetOpType(binop));                    
  SetOPName(binop->StringValue());
    
  parm_bnf    = operand_bnf->GetElement(1)->GetElement(1); // operand
  operand_bnf = operand_bnf->GetElement(0);                // un_operation
    

  return(term);
}

/******************************************************************************/
/**
\brief  SetMaxPriority - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMaxPriority"

void OPBinary :: SetMaxPriority ( )
{

  max_priority = YES;

}

/******************************************************************************/
/**
\brief  SetPriority - 



\param  lst_opcode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPriority"

void OPBinary :: SetPriority (ST_OpCodes lst_opcode )
{

  switch (lst_opcode)
  {
    case ST_assign_ref   :
    case ST_assign       : priority = 2;
                           break;
    
    case ST_xor          :
    case ST_or           : priority = 4;
                           break;
    
    case ST_and          : priority = 6;
                           break;
    
    case ST_greaterEqual :
    case ST_greater      :
    case ST_lowerEqual   :
    case ST_lower        : 
    case ST_equal        :
    case ST_unequal      : priority = 8;
                           break;
    
    case ST_plus         :
    case ST_minus        : priority = 10;
                           break;
    
    case ST_multi        :
    case ST_divi         :
    case ST_remainder    : priority = 12;
                           break;
    
    case ST_shift_right  :
    case ST_shift_left   : priority = 13;  // prüfen, ob die Priorität wie in C ist
                           break;
    
    case ST_power        : priority = 14;
                           break;
    
    default              : priority = 0;
  }


}

/******************************************************************************/
/**
\brief  ~OPBinary - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPBinary"

     OPBinary :: ~OPBinary ( )
{



}


