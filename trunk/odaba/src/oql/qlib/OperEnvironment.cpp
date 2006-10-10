/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OperEnvironment

\brief    


\date     $Date: 2006/07/17 19:09:27,04 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OperEnvironment"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sOqlExtentList.hpp>
#include  <sNodeStack.hpp>
#include  <sOPBase.hpp>
#include  <sOPDecl.hpp>
#include  <sOPParmList.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperResources.hpp>
#include  <sParmList.hpp>
#include  <sSchemaResources.hpp>
#include  <snode.hpp>
#include  <sOperEnvironment.hpp>


/******************************************************************************/
/**
\brief  CO - 


\return ph_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CO"

PropertyHandle *OperEnvironment :: CO ( )
{

  return(calling_object.get_nodeptr() ? &calling_object : NULL);

}

/******************************************************************************/
/**
\brief  CallingParmCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CallingParmCount"

int16 OperEnvironment :: CallingParmCount ( )
{

  return( prev_env ? prev_env->get_calling_parms() : UNDEF );

}

/******************************************************************************/
/**
\brief  Copy - 


\return term - 

\param  operenv - 
\param  intern_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical OperEnvironment :: Copy (OperEnvironment *operenv, logical intern_opt )
{
  logical                 term = NO;
  if ( intern_opt )
    intern_env = YES;
    
  if ( !prev_env )
    delete resources;
    
  prev_env  = operenv;
  resources = prev_env->get_resources();
  
  SetupEnvironment();
  
  if ( scope )
    last_ityp = scope->smcbityp;
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExpression - 


\return oper_bnf - 

\param  impl_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExpression"

BNFData *OperEnvironment :: CreateExpression (PropertyHandle *impl_ph )
{
  PropertyHandle       *code;
  char                  area[60000];
  logical               term = NO;
BEGINSEQ
  CreateGlobals(impl_ph->GPH("globals"));
  
  if ( !impl_ph->IsSelected() )                      OQLERR(99)
    
  impl_ph->ExecuteInstanceAction("FillHeadLine",NULL);
  strcpy(area,impl_ph->GetString("head_line"));
  strcat(area,"\n{");
  if ( !(code = impl_ph->GPH("start_code"))->IsEmpty() )
    strcat(strcat(area,"\nVARIABLES \n"),code->GetString());
  if ( !(code = impl_ph->GPH("init_code"))->IsEmpty() )
    strcat(strcat(area,"\nINIT \n"),code->GetString());
  if ( !(code = impl_ph->GPH("code"))->IsEmpty() )
    strcat(strcat(area,"\nPROCESS \n"),code->GetString());
  if ( !(code = impl_ph->GPH("error_code"))->IsEmpty() )
    strcat(strcat(area,"\nON_ERROR \n"),code->GetString());
  if ( !(code = impl_ph->GPH("term_code"))->IsEmpty() )
    strcat(strcat(area,"\nFINAL \n"),code->GetString());
  strcat(area,"\n}");
  
  if ( !SetExpression(area,"OQLExpression") )        ERROR
  


RECOVER
  delete expr_bnf;
  expr_bnf = NULL;
ENDSEQ
  return(expr_bnf);
}

/******************************************************************************/
/**
\brief  CreateGlobals - 


\return term - 

\param  var_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGlobals"

logical OperEnvironment :: CreateGlobals (PropertyHandle *var_ph )
{
  DictionaryHandle  dict(DictHandle());
  int32             indx0 = 0;
  DBFieldDef       *fielddef;
  DBFieldDef       *oflddef;
  PropertyHandle   *ph = NULL;
  PropertyHandle   *oph = NULL;
  logical           term = NO;
BEGINSEQ
  while ( var_ph->Get(indx0++) )
  {
    ph = new PropertyHandle();
    ph->AllocDescription();
    if ( !(fielddef = ph->GetDescription()) )        ERROR
    if ( fielddef->FillMember(*var_ph,dict.get_dictionary(),UNDEF,YES) )
                                                     ERROR
    fielddef->AllocateArea();
      
    if ( oph = dict.GetGlobalVariable(fielddef->fmcbname) )
    {
      oflddef = ph->GetDescription();
      if ( memcmp(oflddef->fmcbtype,fielddef->fmcbtype,ID_SIZE)  ||
           oflddef->fmcbsize != fielddef->fmcbsize               ||
           oflddef->fmcbdim  != fielddef->fmcbdim                ||
           oflddef->fmcbrlev != fielddef->fmcbrlev                 )
                                                     OQLERR(146)
    }
    else
    {
      if ( !ph->GetArea() )
        ph->AllocateArea();
      if ( fielddef->fmcbrlev != R_REFR )
        fielddef->fmcbrlev = R_INTERN;
      fielddef->fmcbinit = var_ph->GetDBField("initialize").IsTrue();
      fielddef->fmcbcnst = var_ph->GetDBField("const_val").IsTrue();
    }
    dict.CreateGlobalVariable(*ph,NULL);
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DictHandle - 


\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictHandle"

Dictionary *OperEnvironment :: DictHandle ( )
{

  return ( resources ? resources->get_dictionary() : NULL );

}

/******************************************************************************/
/**
\brief  GetExceptionERC - 


\return rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExceptionERC"

ExecReturnCodes OperEnvironment :: GetExceptionERC ( )
{

  switch ( exh_type )
  {
    case NVH_accept    : return(ERC_success);
    case NVH_ignore    : return(ERC_null); 
    case NVH_exception : 
    default            : return(ERC_terminate); 
  }


}

/******************************************************************************/
/**
\brief  GetExpression - 


\return string - String area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpression"

char *OperEnvironment :: GetExpression ( )
{
  char               *string = NULL;
BEGINSEQ
  if ( expression )
    string = expression;
  else if ( expr_bnf )
    string = expr_bnf->StringValue();
  else                                               ERROR

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetExpressionDecl - 


\return expr_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpressionDecl"

OPDecl *OperEnvironment :: GetExpressionDecl ( )
{

  return ( this ? declaration : NULL );

}

/******************************************************************************/
/**
\brief  GetExtentList - 


\return ext_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentList"

OqlExtentList *OperEnvironment :: GetExtentList ( )
{
  OqlExtentList            *ext_list = NULL;
  if ( declaration && declaration->get_oper_env() != this )
    ext_list = declaration->get_oper_env()->GetExtentList();
  else
  {
    if ( !extent_list )
      extent_list = new OqlExtentList();
    ext_list = extent_list;
  }
  return(ext_list);
}

/******************************************************************************/
/**
\brief  GetNullValueERC - 


\return rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNullValueERC"

ExecReturnCodes OperEnvironment :: GetNullValueERC ( )
{

  switch ( nvh_type )
  {
    case NVH_accept    : return(ERC_success);
    case NVH_exception : return(ERC_terminate); 
    case NVH_ignore    : 
    default            : return(ERC_null); 
  }


}

/******************************************************************************/
/**
\brief  GetParameterDef - 


\return fielddef - Internal field defintion

\param  varnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParameterDef"

DBFieldDef *OperEnvironment :: GetParameterDef (char *varnames )
{
  OPBase          *opnode;
  DBFieldDef      *fielddef = NULL;
BEGINSEQ
  if ( !parameters )                                 ERROR

  if ( !(opnode = parameters->Get(varnames)) )       ERROR
  
  fielddef = opnode->GetDescription();
RECOVER
  fielddef = NULL;
ENDSEQ
  return(fielddef);
}

/******************************************************************************/
/**
\brief  GetParameterNode - 


\return nodeptr - 

\param  varnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParameterNode"

node *OperEnvironment :: GetParameterNode (char *varnames )
{
  OPBase          *opnode;
  node            *nodeptr = NULL;
BEGINSEQ
  if ( !variables )                                 ERROR

  if ( !(opnode = parameters->Get(varnames)) )      ERROR
  
  nodeptr = opnode->GetValue()->get_nodeptr();
RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}


/******************************************************************************/
/**
\brief  GetPreviousOPDecl - 


\return expr_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPreviousOPDecl"

OPDecl *OperEnvironment :: GetPreviousOPDecl ( )
{

  return ( prev_env ? prev_env->GetExpressionDecl() : NULL );

}

/******************************************************************************/
/**
\brief  GetReopen - 


\return init_opt - 

\param  co - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReopen"

int16 OperEnvironment :: GetReopen (PropertyHandle *co )
{
  node     *new_node = calling_object.GetTNode();
  node     *nodeptr  = co ? co->GetTNode() 
                          : calling_object.GetTNode();
  DBStructDef *strdef = NULL;
  int16     ityp = UNDEF;
  int32     init_opt = 0;
  if ( new_node )
  {
    if ( strdef = new_node->GetCurrentTypeDef() )
      ityp = strdef->smcbityp;
    else
      ityp = new_node->GetDescription()->fmcbityp;
      
    if (  ityp != last_ityp )
    {
      last_ityp = ityp;
      init_opt = 4;
    }
  }
  if ( !init_opt )
  {
    if ( nodeptr != new_node )
      init_opt = 3;   // co changed
    else if ( last_inst != calling_object.GetLOID() )
      init_opt = 2;
  }

 return(init_opt);
}

/******************************************************************************/
/**
\brief  GetVariableDef - 


\return fielddef - Internal field defintion

\param  varnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVariableDef"

DBFieldDef *OperEnvironment :: GetVariableDef (char *varnames )
{
  OPBase          *opnode;
  DBFieldDef      *fielddef = NULL;
BEGINSEQ
  if ( !variables )                                 ERROR

  if ( !(opnode = variables->Get(varnames)) )       ERROR
  
  fielddef = opnode->GetDescription();
RECOVER
  fielddef = NULL;
ENDSEQ
  return(fielddef);
}

/******************************************************************************/
/**
\brief  GetVariableNode - 


\return nodeptr - 

\param  varnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVariableNode"

node *OperEnvironment :: GetVariableNode (char *varnames )
{
  OPBase          *opnode;
  node            *nodeptr = NULL;
BEGINSEQ
  if ( !variables )                                 ERROR

  if ( !(opnode = variables->Get(varnames)) )       ERROR
  
  nodeptr = opnode->GetValue()->get_nodeptr();
RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  ObjectHandle - 


\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectHandle"

ACObject *OperEnvironment :: ObjectHandle ( )
{
  ACObject *obhandle = NULL;
  if ( resources )
    obhandle = resources->get_database();
  if ( !obhandle && prev_env ) 
    obhandle = prev_env->ObjectHandle();
  return(obhandle);
}

/******************************************************************************/
/**
\brief  OperEnvironment - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  dictptr - 
\param  resobj - 
\param  scope_str - 
\param  bdata - 
\param  obhandle - 
\param  co - 
\param  op_decl - 
\param  expr_dup_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OperEnvironment"

     OperEnvironment :: OperEnvironment (Dictionary *dictptr, ACObject *resobj, DBStructDef *scope_str, BNFData *bdata, ACObject *obhandle, PropertyHandle *co, OPDecl *op_decl, char *expr_dup_w )
                     :   resources(NULL),
  stack(NULL),
  expression(expr_dup_w),
  expr_bnf(bdata),
  scope(scope_str),
  calling_object(co),
  variables(NULL),
  parameters(NULL),
  calling_parms(0),
  intern_env(NO),
  last_executed((node*)NULL),
  last_ityp(0),
  last_inst(0),
  declaration(op_decl),
  prev_env(NULL),
  nvh_type(NVH_undefined),
  exh_type(NVH_undefined),
  extent_list(NULL)
{

  if ( scope )
    last_ityp = scope->smcbityp;

  resources = new SchemaResources(dictptr,resobj,obhandle);

}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OperEnvironment"

     OperEnvironment :: OperEnvironment ( )
                     :   resources(NULL),
  stack(NULL),
  expression(NULL),
  expr_bnf(NULL),
  scope(NULL),
  calling_object(NULL),
  variables(NULL),
  parameters(NULL),
  calling_parms(0),
  intern_env(NO),
  last_executed((node*)NULL),
  last_ityp(0),
  last_inst(0),
  declaration(NULL),
  prev_env(NULL),
  nvh_type(NVH_undefined),
  exh_type(NVH_undefined),
  extent_list(NULL)
{



}

/******************************************************************************/
/**
\brief  Parameters - 


\return parameters - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parameters"

OPParmList *OperEnvironment :: Parameters ( )
{

  if ( !parameters )
    parameters = new OPParmList(YES);
  return(parameters);
}

/******************************************************************************/
/**
\brief  PopCO - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopCO"

void OperEnvironment :: PopCO ( )
{

  calling_object.Pop();



}

/******************************************************************************/
/**
\brief  PushCO - 



\param  co - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushCO"

void OperEnvironment :: PushCO (PropertyHandle *co )
{

  calling_object.Push(co);


}

/******************************************************************************/
/**
\brief  ResOBHandle - 


\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResOBHandle"

ACObject *OperEnvironment :: ResOBHandle ( )
{

  return ( resources ? resources->get_resources() : NULL );

}

/******************************************************************************/
/**
\brief  Reset - 


\return term - 

\param  intern_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical OperEnvironment :: Reset (logical intern_opt )
{
  logical                 term = NO;
// Pendant to Copy

  if ( intern_env )
  {
    variables  = NULL;
    parameters = NULL;
  }
  PopCO();
  return(term);
}

/******************************************************************************/
/**
\brief  SetCO - 


\return init_opt - 

\param  co - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCO"

int32 OperEnvironment :: SetCO (PropertyHandle *co )
{
  int32     init_opt = GetReopen(co);
  if ( init_opt )
    calling_object.Open(co);

 return(init_opt);
}

/******************************************************************************/
/**
\brief  SetExceptionHandling - 



\param  ex_handling - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExceptionHandling"

void OperEnvironment :: SetExceptionHandling (VHN_Types ex_handling )
{

  exh_type = ex_handling;

  if ( exh_type == NVH_undefined )
    exh_type = prev_env ? prev_env->get_exh_type() : NVH_exception;

}

/******************************************************************************/
/**
\brief  SetExpression - 


\return oper_bnf - 

\param  expr_string - 
\param  bsymbol - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

BNFData *OperEnvironment :: SetExpression (char *expr_string, char *bsymbol )
{
  DictionaryHandle        dict(DictHandle());
  char                   *string;
BEGINSEQ
  if ( !expr_string )                                OQLERR(99)
  string = expr_string;
  
  while ( *string == ' ')
    string++;
  expression = strdup(string);
  
  if ( !bsymbol ){
    if (*expression == '{') {
       bsymbol = "OQLExpression";
    } else {
       bsymbol = "operand";
    }
  }
  
  if ( !(expr_bnf = dict.ParseExpression(expression,bsymbol)) )
                                                     OQLERR(145)

RECOVER
  delete expr_bnf;
  expr_bnf = NULL;
ENDSEQ
  return(expr_bnf);
}

/******************************************************************************/
/**
\brief  SetNVHType - 



\param  nv_handling - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNVHType"

void OperEnvironment :: SetNVHType (VHN_Types nv_handling )
{

  nvh_type = nv_handling;

  if ( nvh_type == NVH_undefined && prev_env )
    nvh_type = prev_env->get_nvh_type();

}

/******************************************************************************/
/**
\brief  SetParmCount - 



\param  parm_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParmCount"

void OperEnvironment :: SetParmCount (int32 parm_count )
{

  calling_parms = parm_count;

}

/******************************************************************************/
/**
\brief  SetPreviousEnvironment - 



\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPreviousEnvironment"

void OperEnvironment :: SetPreviousEnvironment (OperEnvironment *operenv )
{

  if ( prev_env != operenv )
  {
    prev_env = operenv;
    SetupEnvironment();
  }



}

/******************************************************************************/
/**
\brief  SetScope - 



\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetScope"

void OperEnvironment :: SetScope (DBStructDef *strdef )
{

  scope = strdef;

}

/******************************************************************************/
/**
\brief  SetUpperCO - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUpperCO"

logical OperEnvironment :: SetUpperCO ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( calling_object.IsValid() )                    LEAVESEQ

  if ( !prev_env )                                   ERROR
  prev_env->SetUpperCO();

  calling_object.Open(prev_env->CO());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupEnvironment - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupEnvironment"

logical OperEnvironment :: SetupEnvironment ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !prev_env )                                   ERROR
    
  if ( intern_env )
  {
    variables  = prev_env->Variables();
    parameters = prev_env->Parameters();
  }
  stack = prev_env->Stack();
  resources = prev_env->resources;

  if ( !scope )
    scope = prev_env->get_scope();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Stack - 


\return stack - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stack"

NodeStack *OperEnvironment :: Stack ( )
{

  if ( !stack )
    stack = new NodeStack();
  return(stack);
}

/******************************************************************************/
/**
\brief  Variables - 


\return variables - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Variables"

OPParmList *OperEnvironment :: Variables ( )
{

  if ( !variables )
    variables = new OPParmList(YES);
  return(variables);
}

/******************************************************************************/
/**
\brief  set_last_executed - 



\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_last_executed"

void OperEnvironment :: set_last_executed (node *nodeptr )
{

  last_executed.RegisterNode(nodeptr);

}

/******************************************************************************/
/**
\brief  ~OperEnvironment - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OperEnvironment"

     OperEnvironment :: ~OperEnvironment ( )
{

  if ( expression )
  {
    delete expr_bnf;
    expr_bnf = NULL;
    free(expression);
  }
  
  if ( !intern_env )
  {
    delete parameters;
    delete variables;
  }
  
  if ( !prev_env )
  {
    delete resources;
    resources = NULL;
    delete stack;
  }
  stack = NULL;
  prev_env = NULL;

  parameters = NULL;
  variables = NULL;
  
  delete extent_list;
  extent_list = NULL;


}


