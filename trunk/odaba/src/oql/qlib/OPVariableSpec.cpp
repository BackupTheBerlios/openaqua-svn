/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPVariableSpec

\brief    Variable definitions
          Specific re-open codes are
          10: init value at beginning of procedure
          11: de-init value at ent of procedure

\date     $Date: 2006/08/25 14:58:03,53 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPVariableSpec"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sExpressionReference.hpp>
#include  <sOPBase.hpp>
#include  <sParmList.hpp>
#include  <snode.hpp>
#include  <sOPVariableSpec.hpp>


/******************************************************************************/
/**
\brief  CreateInitValue - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInitValue"

logical OPVariableSpec :: CreateInitValue ( )
{
  DBFieldDef             *fielddef = GetDescription();
  logical                 term = NO;
  if ( fielddef->fmcbinit )
    if ( parm_bnf = fielddef->get_initval_expr()->GetBNFData(DictHandle()) )
    {
      source = CreateOperandNode(this,parm_bnf);
      init_value.CopyHandle(source->GetValue());
    }

  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 



\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPVariableSpec :: Execute ( )
{
  ExecReturnCodes         exec_rc = ERC_success;
BEGINSEQ
  if ( source )
  {
    if ( source->Execute() == ERC_success )
    {
      if ( CheckSourceValue(source->Value()) )        ERROR
      SetValueOrReference(source->Value());
      LEAVESEQ
    }
  }
  else
  {
    InitValue();
    if ( GetValue()->Initialize() )                     ERROR
  }

RECOVER
  exec_rc = ERC_success;
ENDSEQ
  return(exec_rc);
}

/******************************************************************************/
/**
\brief  GetValue - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

PropertyHandle *OPVariableSpec :: GetValue ( )
{

  return(&init_value);

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

logical OPVariableSpec :: Initialize (int32 ini_opt )
{
  PropertyHandle         *ph = NULL;
  logical                 term = NO;
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case 10 : PushValue();
              re_open = 0;
              break;
    case 11 : PopValue();
              re_open = 0;
              break;
    case -1 : CreateInitValue();
    default : re_open = 0;
  }  


  return(term);
}

/******************************************************************************/
/**
\brief  OPVariableSpec - 



\return term - 

\param  fielddef - Internal field defintion
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPVariableSpec"

     OPVariableSpec :: OPVariableSpec (DBFieldDef *fielddef, OPBase *parent_node )
                     : OPVariable (NULL,NULL,parent_node,NULL),
  init_value(NULL)
{
  DictionaryHandle        dictionary(DictHandle());

  op_type = NT_OPVariableSpec;
  
  if ( fielddef )
  {
    SetDescription(fielddef);
    if ( fielddef->get_initval_expr() )
      operand_bnf = fielddef->get_initval_expr()->get_bnf();
  }
  proto_type = YES;
  
//  class_ref = dictionary.GetStructDef(fielddef->fmcbtype);
  
  Initialize(0);

}

/******************************************************************************/
/**
\brief  PopValue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopValue"

void OPVariableSpec :: PopValue ( )
{

  init_value.Pop();

}

/******************************************************************************/
/**
\brief  PushValue - 



\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushValue"

ExecReturnCodes OPVariableSpec :: PushValue ( )
{
  ExecReturnCodes         exec_rc = ERC_success;
  init_value.Push();
  
  exec_rc = Execute();

  return(exec_rc);
}

/******************************************************************************/
/**
\brief  Value - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Value"

node *OPVariableSpec :: Value ( )
{

  return(init_value.get_nodeptr());

}

/******************************************************************************/
/**
\brief  ~OPVariableSpec - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPVariableSpec"

     OPVariableSpec :: ~OPVariableSpec ( )
{



}


