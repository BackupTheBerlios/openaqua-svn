/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    Operation

\brief    


\date     $Date: 2006/06/16 12:33:08,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Operation"

#include  <popa7.h>
#include  <podaba2.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOPAccessPathDecl.hpp>
#include  <sOPDecl.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOPFunctionDecl.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <snode.hpp>
#include  <sOperation.hpp>


/******************************************************************************/
/**
\brief  CheckExpression - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  dictptr - Dictionary handle
\param  obhandle - Database Object handle
\param  clsnames - 
\param  exprnames - 
\param  impnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical Operation :: CheckExpression (Dictionary *dictptr, ACObject *obhandle, char *clsnames, char *exprnames, char *impnames )
{
  logical          term = NO;
BEGINSEQ
  dictptr->CheckExpression(obhandle,clsnames,exprnames,impnames);
                                                     SDBCERR
  if ( OQLERROR )                                    SDBERR(OQL_ERROR)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  dictptr - Dictionary handle
\param  expression - Expression
\param  obhandle - Database Object handle
\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical Operation :: CheckExpression (Dictionary *dictptr, char *expression, ACObject *obhandle, char *clsnames )
{
  logical          term = NO;
BEGINSEQ
  dictptr->CheckExpression(expression,obhandle,clsnames);
                                                     SDBCERR
  if ( OQLERROR )                                    SDBERR(OQL_ERROR)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void Operation :: Close ( )
{

//  if ( calling_object && calling_object->get_nodeptr() )
//    calling_object->get_nodeptr()->RemoveOperation(this);
  calling_object = NULL;

}

/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical Operation :: Execute (ParmList *parmlist )
{
  logical           term = NO;
BEGINSEQ
  if ( !operation_decl )                             ERROR
    
  if ( oper_env && oper_env->CO() )
    SetCallingObject(oper_env->CO());
    
  term = operation_decl->Call(calling_object,parmlist);
  RegisterNode(operation_decl->Value());
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  co - 
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical Operation :: Execute (PropertyHandle *co, ParmList *parmlist )
{

  calling_object = co;

  return ( Execute(parmlist) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  obhandle - Database Object handle
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical Operation :: Execute (ACObject *obhandle, ParmList *parmlist )
{
  logical     term = NO;
BEGINSEQ
  if ( !operation_decl )                             ERROR
  
// das will rk erst sehn  
//  operation_decl->SetOBHandle(obhandle);
  
  if ( obhandle && obhandle != operation_decl->ObjectHandle() )
    SDBERR(999)
  
  return ( Execute(parmlist) );
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDimension - 


\return dimension - Dimension of property

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 Operation :: GetDimension ( )
{
  uint16                  dimension = 0;
  if ( !(dimension = operation_decl->GetValue()->GetDimension()) )
    dimension = AUTO;
  return(dimension);
}

/******************************************************************************/
/**
\brief  GetRetvalDefinition - 


\return field_def - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRetvalDefinition"

DBFieldDef *Operation :: GetRetvalDefinition ( )
{
  node                   *nodeptr = operation_decl->Value();
  DBFieldDef             *field_def;
BEGINSEQ
  if ( !nodeptr )                                    ERROR
    
  if ( !(field_def = nodeptr->GetInstFieldDef()) )
    field_def = calling_object->GetDescription();

RECOVER
  field_def = NULL;
ENDSEQ
  return(field_def);
}

/******************************************************************************/
/**
\brief  GetSize - 


\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

int32 Operation :: GetSize ( )
{
  int32                  size = 0;
  if ( !(size = operation_decl 
                ? operation_decl->GetValue()->GetSize()
                : PropertyHandle::GetSize())             )
    size = AUTO;
  return(size);
}

/******************************************************************************/
/**
\brief  InitResult - 


\return term - Termination code

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical Operation :: InitResult (PropertyHandle &prophdl_ref )
{
  logical                 term = NO;
  if ( calling_object->GetNode() != prophdl_ref.GetNode() )
    Open(prophdl_ref);

  operation_decl->InitResult(calling_object);


  return(term);
}

/******************************************************************************/
/**
\brief  IsDefined - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDefined"

logical Operation :: IsDefined ( )
{

  return(operation_decl ? YES : NO);

}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  prophdl_ref - Reference to Property handle
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical Operation :: Open (PropertyHandle &prophdl_ref, OperEnvironment *operenv_w )
{
  logical        term = NO;
BEGINSEQ
  if ( operenv_w )
    oper_env = operenv_w;
    
  if ( calling_object )
    Close();
    
  if ( !(calling_object = &prophdl_ref) ||
       !calling_object->IsValid()           )        ERROR
       
// macht Probleme, wenn operation calling object ist
//  calling_object->get_nodeptr()->AddOperation(this);


RECOVER
  calling_object = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Operation - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  prophdl_ref - Reference to Property handle
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Operation"

     Operation :: Operation (PropertyHandle &prophdl_ref, OperEnvironment *operenv_w )
                     : PropertyHandle (),
  operation_decl(NULL),
  calling_object(NULL),
  expression(NULL),
  op_handle(NULL),
  is_owner(NO),
  oper_env(operenv_w)

{

  Open(prophdl_ref);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Operation"

     Operation :: Operation (OperEnvironment *operenv_w )
                     : PropertyHandle (),
  operation_decl(NULL),
  calling_object(NULL),
  expression(NULL),
  op_handle(NULL),
  is_owner(NO),
  oper_env(operenv_w)
{



}

/******************************************************************************/
/**
\brief  ProvAccessPath - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  obhandle - Database Object handle
\param  oper_bnf - 
\param  prop_path - Property path
\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvAccessPath"

logical Operation :: ProvAccessPath (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, BNFData *oper_bnf, char *prop_path, char *clsnames )
{
  DBStructDef            *strdef = NULL;
  logical                 term = NO;
BEGINSEQ
  PropertyHandle::Close();  // close property handle
  
  if ( operation_decl )
    Remove();
  
  if ( clsnames && *clsnames > ' ' ) 
  {
    TypeKey        tkey(dictptr,clsnames);
    strdef = dictptr->ProvideStructDef(tkey);
  }
  else if ( calling_object )
    strdef = calling_object->GetStructDef();
       
  operation_decl = new OPAccessPathDecl(dictptr,resobj,obhandle,strdef,
                                        calling_object,oper_bnf,oper_env);
                                                  SDBCERR
                                                  SDBOQLCERR
  is_owner = YES;
  CopyHandle(operation_decl->GetValue());
  
  set_expression(prop_path);

RECOVER
  delete operation_decl;
  operation_decl = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  obhandle - Database Object handle
\param  expr_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvAccessPath"

logical Operation :: ProvAccessPath (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, char *expr_string )
{
  char           *classname = calling_object ?
                              calling_object->GetCurrentType() : NULL;
  logical         term = NO;
BEGINSEQ
  PropertyHandle::Close();  // close property handle
  
  if ( operation_decl )
      Remove();
      
  if ( !(operation_decl = (OPDecl *)dictptr->ProvExpression(resobj,classname,expr_string,calling_object,
                                                     obhandle,oper_env)) )
  {
    SDBOQLCERR
    if ( !SDBERROR )
      SDBERR(99)
    ERROR
  }
  
  is_owner = YES;
  CopyHandle(operation_decl->GetValue());
  
  set_expression(expr_string);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i04 - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  obhandle - Database Object handle
\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvAccessPath"

logical Operation :: ProvAccessPath (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, BNFData *bnf_data )
{
  char           *classname = calling_object ?
                              calling_object->GetCurrentType() : NULL;
  logical                 term = NO;
BEGINSEQ
  PropertyHandle::Close();  // close property handle
  
  if ( operation_decl )
      Remove();
      
  if ( !(operation_decl = (OPDecl *)dictptr->ProvExpression(resobj,classname,bnf_data,calling_object,
                                                     obhandle,oper_env)) )
  {
    SDBOQLCERR
    ERROR
  }
  
  is_owner = YES;
  CopyHandle(operation_decl->GetValue());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvExpression - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  obhandle - Database Object handle
\param  clsnames - 
\param  exprnames - 
\param  parmlist - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

logical Operation :: ProvExpression (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, char *clsnames, char *exprnames, ParmList *parmlist, logical refresh_opt )
{
  DBStructDef            *strdef = NULL;
  logical                 term = NO;
BEGINSEQ
  PropertyHandle::Close();  // close property handle
  
  if ( operation_decl )
    Remove();
  
  if ( (!clsnames || !*clsnames) && calling_object )
    if ( strdef = calling_object->GetStructDef() )
      clsnames = strdef->smcbname;
       
  if ( !(operation_decl = dictptr->ProvExpression(resobj,clsnames,exprnames,
                                                  calling_object,parmlist,
                                                  obhandle,NULL,refresh_opt)) )
  {
    SDBOQLCERR
    ERROR
  }
  
  CopyHandle(operation_decl->GetValue());
  
  set_expression(exprnames);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  obhandle - Database Object handle
\param  expr_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

logical Operation :: ProvExpression (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, char *expr_string )
{
  char           *classname = calling_object ?
                              calling_object->GetCurrentType() : NULL;
  logical         term = NO;
BEGINSEQ
  PropertyHandle::Close();  // close property handle
  
  if ( operation_decl )
      Remove();
      
  if ( !(operation_decl = (OPDecl *)dictptr->ProvExpression(resobj,classname,expr_string,calling_object,
                                                     obhandle,oper_env)) )
  {
    SDBOQLCERR
    ERROR
  }
  
  is_owner = YES;
  CopyHandle(operation_decl->GetValue());
  
  set_expression(expr_string);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i04 - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  obhandle - Database Object handle
\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

logical Operation :: ProvExpression (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, BNFData *bnf_data )
{
  char           *classname = calling_object ?
                              calling_object->GetCurrentType() : NULL;
  logical                 term = NO;
BEGINSEQ
  PropertyHandle::Close();  // close property handle
  
  if ( operation_decl )
      Remove();
      
  if ( !(operation_decl = (OPDecl *)dictptr->ProvExpression(resobj,classname,bnf_data,calling_object,
                                                     obhandle,oper_env)) )
  {
    SDBOQLCERR
    ERROR
  }
  
  is_owner = YES;
  CopyHandle(operation_decl->GetValue());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvFunction - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  dictptr - Dictionary handle
\param  obhandle - Database Object handle
\param  clsnames - 
\param  fnames - 
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvFunction"

logical Operation :: ProvFunction (Dictionary *dictptr, ACObject *obhandle, char *clsnames, char *fnames, ParmList *parmlist )
{
  OPFunctionDecl    *fdecl = NULL;
  logical            term  = NO;
BEGINSEQ
  if ( operation_decl )
    Remove();
      
  if ( !(fdecl = dictptr->ProvFunction(obhandle,clsnames,fnames,calling_object,parmlist)) )
  {
                                                     SDBOQLCERR
                                                     SDBERR(99)
  }
  operation_decl = fdecl;

// retval wird im Konstruktor nicht mehr bestimmt, da OPFunctionDecl kein Init mehr macht.
// deshalb noch explicit Init(); wozu dann co vorher mitgeben ? 
  fdecl->Init(calling_object,parmlist);                                                   
  CopyHandle(operation_decl->GetValue());
  
  set_expression(fnames);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  dictptr - Dictionary handle
\param  clsnames - 
\param  fnames - 
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvFunction"

logical Operation :: ProvFunction (Dictionary *dictptr, char *clsnames, char *fnames, ParmList *parmlist )
{

  return ( ProvFunction(dictptr,dictptr,
                        clsnames,fnames,parmlist) );


}

/******************************************************************************/
/**
\brief  Remove - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical Operation :: Remove ( )
{

  if ( is_owner )
    delete operation_decl;
  operation_decl = NULL;
  
  PropertyHandle::Close();
  set_expression(NULL);
  return(NO);
}

/******************************************************************************/
/**
\brief  SetCallingObject - 



\param  prop_handle - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCallingObject"

void Operation :: SetCallingObject (PropertyHandle *prop_handle )
{

  calling_object = prop_handle;

}

/******************************************************************************/
/**
\brief  SetEnvironment - 



\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEnvironment"

void Operation :: SetEnvironment (OperEnvironment *operenv )
{

  oper_env = operenv;

}

/******************************************************************************/
/**
\brief  SetHandle - 



\param  operation_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHandle"

void Operation :: SetHandle (OperationHandle *operation_handle )
{

  op_handle = operation_handle;

}

/******************************************************************************/
/**
\brief  set_expression - 



\param  expr_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_expression"

void Operation :: set_expression (char *expr_string )
{

  if ( expression )
  {
    free(expression);
    expression = NULL;
  }

  if ( expr_string )
    expression = strdup(expr_string);

}

/******************************************************************************/
/**
\brief  ~Operation - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Operation"

     Operation :: ~Operation ( )
{

  Close();
  Remove();

  if ( op_handle )
    op_handle->Reset();

}


