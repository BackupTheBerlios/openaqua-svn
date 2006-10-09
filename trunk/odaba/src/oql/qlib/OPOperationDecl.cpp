/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPOperationDecl

\brief    


\date     $Date: 2006/08/25 14:50:15,43 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPOperationDecl"

#include  <poql.h>
#include  <sNodeStack.hpp>
#include  <sOPOperation.hpp>
#include  <sOPParmList.hpp>
#include  <sOperEnvironment.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSchemaResources.hpp>
#include  <snode.hpp>
#include  <sOPOperationDecl.hpp>


/******************************************************************************/
/**
\brief  Call - 



\return term - 

\param  co - 
\param  call_parms - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPOperationDecl :: Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
  PushCO(co);

  if ( call_parms->GetSize() > 0 )
    nodeptr = call_parms->GetAt(0)->Value();
  term = ExecuteOperation(nodeptr);

  PopCO();
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteOperation - 



\return term - 

\param  operand_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteOperation"

logical OPOperationDecl :: ExecuteOperation (node *operand_node )
{
  node                   *srce_node = CO()->get_nodeptr();
  PropertyHandle          source_ph(CO());
  PropertyHandle          operand_ph(operand_node);
  logical                 term = NO;
BEGINSEQ
  if ( !srce_node || !srce_node->GetNode() || 
       !srce_node->GetNode()->GetArea() )
  {
    switch ( Environment()->GetNullValueERC() )
    {
      case ERC_terminate : ERROR
      case ERC_null      : value.RegisterNode((node *)NULL);
                           LEAVESEQ
      default            : source_ph.Open("");
    }
  }  

// unary operations
  switch (op_code)
  {
     case ST_decrement      : value.RegisterNode( ( source_ph--).get_nodeptr() );
                              LEAVESEQ
     case ST_increment      : value.RegisterNode( ( source_ph++).get_nodeptr() );
                              LEAVESEQ
     case ST_not            : value.SetValue( !source_ph.IsTrue() );
                              LEAVESEQ
     case ST_typecast       : SetValue(source->Value());
                              LEAVESEQ
     default                : ;
  }

  if ( !operand_node || !operand_node->GetNode() || 
       !operand_node->GetNode()->GetArea() )
  {
    switch ( Environment()->GetNullValueERC() )
    {
      case ERC_terminate : ERROR
      case ERC_null      : value.RegisterNode((node *)NULL);
                           LEAVESEQ
      default            : operand_ph.Open("");
                           operand_node = operand_ph.get_nodeptr();
    }
  }  

  switch (op_code)
  {
     case ST_minus          : if ( operand_node )
                                value.RegisterNode( ( source_ph - operand_ph).get_nodeptr() );
                              else
                                value.RegisterNode( ( -source_ph).get_nodeptr() );
                              LEAVESEQ
     case ST_plus           : value.RegisterNode( ( source_ph + operand_ph).get_nodeptr() );
                              LEAVESEQ
     case ST_power          : value.RegisterNode( ( source_ph.Power(operand_ph)).get_nodeptr() );
                              LEAVESEQ
     case ST_multi          : value.RegisterNode( ( source_ph * operand_ph).get_nodeptr() );
                              LEAVESEQ
     case ST_divi           : value.RegisterNode( ( source_ph / operand_ph).get_nodeptr() );
                              LEAVESEQ
     case ST_remainder      : value.RegisterNode( ( source_ph % operand_ph).get_nodeptr() );  
                              LEAVESEQ
     
     case ST_plus_assign    : value.RegisterNode( ( source_ph += operand_ph).get_nodeptr() );  
                              LEAVESEQ
     case ST_minus_assign   : value.RegisterNode( ( source_ph -= operand_ph).get_nodeptr() );  
                              LEAVESEQ
     case ST_mult_assign    : value.RegisterNode( ( source_ph *= operand_ph).get_nodeptr() );  
                              LEAVESEQ
     case ST_divi_assign    : value.RegisterNode( ( source_ph /= operand_ph).get_nodeptr() );  
                              LEAVESEQ
     
     case ST_greaterEqual   : value.SetValue( source_ph >= operand_ph );
                              LEAVESEQ
     case ST_greater        : value.SetValue( source_ph >  operand_ph );
                              LEAVESEQ
     case ST_lower          : value.SetValue( source_ph <  operand_ph );
                              LEAVESEQ
     case ST_lowerEqual     : value.SetValue( source_ph <= operand_ph );
                              LEAVESEQ
     case ST_equal          : value.SetValue( source_ph == operand_ph );
                              LEAVESEQ
     case ST_unequal        : value.SetValue( source_ph != operand_ph );
                              LEAVESEQ
     
     case ST_and            : value.SetValue( source_ph && operand_ph );
                              LEAVESEQ
     case ST_xor            : value.SetValue( source_ph ^  operand_ph );
                              LEAVESEQ
     case ST_or             : value.SetValue( source_ph || operand_ph );
                              LEAVESEQ
     
     case ST_shift_left     : value.SetValue( source_ph << operand_ph );
                              LEAVESEQ
     case ST_shift_right    : value.SetValue( source_ph >> operand_ph );
                              LEAVESEQ

     case ST_assign_ref     : source->SetReference(operand_node);
                              value.RegisterNode(source_ph);
                              LEAVESEQ
     case ST_assign         : if ( source->CheckValue(operand_node) )
                                                    ERROR
                              source->SetValue(operand_node);
                              value.RegisterNode(source_ph);
                              LEAVESEQ
     
     default                : OQLSERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitResult - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical OPOperationDecl :: InitResult ( )
{

  return(SetupResult());

}

/******************************************************************************/
/**
\brief  OPOperationDecl - 



\return term - 

\param  opcode - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPOperationDecl"

     OPOperationDecl :: OPOperationDecl (ST_OpCodes opcode, OPBase *parent_node )
                     : OPDecl (parent_node),
  op_code(opcode)
{

  op_type = NT_OPOperationDecl;

  source = parent_node->Source();
  SetupResult();


}

/******************************************************************************/
/**
\brief  SetupResult - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupResult"

logical OPOperationDecl :: SetupResult ( )
{
  DBFieldDef             *fielddef;
  logical                 term = NO;
  switch ( op_code )
  {
    case ST_power        : 
    case ST_multi        :
    case ST_divi         : AllocDescription("REAL",T_REAL,17);   
                           break;
    case ST_greaterEqual :
    case ST_greater      :
    case ST_lowerEqual   :
    case ST_lower        : 
    case ST_equal        :
    case ST_unequal      : 
    case ST_and          :
    case ST_xor          :
    case ST_or           : 
    case ST_not          : AllocDescription("LOGICAL",T_LO,1);
                           break;
    case ST_typecast     : fielddef = ProvideDescription();
                           Schema()->GetTypeSpec(fielddef,((OPOperation *)parent)->get_parm_bnf(),YES);
                           break;
    default              : SetDescription(source->GetDescription());
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ~OPOperationDecl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPOperationDecl"

     OPOperationDecl :: ~OPOperationDecl ( )
{



}


