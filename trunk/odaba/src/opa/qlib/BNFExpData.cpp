/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    BNFExpData

\brief    Expression BNF data
          This  class is used to add additional functionality for Expression BNF
          data trees.

\date     $Date: 2006/08/25 11:32:01,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFExpData"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFExpData.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOperEnvironment.hpp>
#include  <sfmcb.hpp>
#include  <ssmcb.hpp>
#include  <sBNFExpData.hpp>


/******************************************************************************/
/**
\brief  GetAccessPath - 


\return parm_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccessPath"

BNFExpData *BNFExpData :: GetAccessPath ( )
{
  BNFExpData                *bdata = this;
BEGINSEQ
  if ( IsA("coll_operand") )
    bdata = GetElement(1);
    
  if ( bdata->IsA("parameter") )
    bdata = bdata->GetElement(0);
  
  if ( bdata->IsA("operand") )
    bdata = bdata->GetElement(0);
  
  if ( bdata->IsA("operation") )
    bdata = bdata->GetElement(0);
  
  if ( bdata->IsA("simple_op") )
    bdata = bdata->GetElement(0);
  
  if ( !bdata->IsA("access_path") )                 ERROR

RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetBNFExpData - 


\return bexp_data - 

\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBNFExpData"

BNFExpData *__cdecl BNFExpData :: GetBNFExpData (BNFData *bnf_data )
{


  return((BNFExpData *)bnf_data);
}

/******************************************************************************/
/**
\brief  GetDimension - 


\return dimension - Dimension of property

\param  indx_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 BNFExpData :: GetDimension (int32 &indx_ref )
{
  BNFData        *array_size;
  int32           dimension = 1;
  logical         first     = YES;
BEGINSEQ
  while ( (array_size = GetElement(indx_ref)) && 
           array_size->IsSymbol("fixed_array_size") )
  {
    if ( !first )                                       SDBERR(442)
    dimension = atoi(array_size->GetElement("std_integer")->StringValue());
    first = NO;
    indx_ref++;
  }

RECOVER
  dimension = -1;
ENDSEQ
  return(dimension);
}

/******************************************************************************/
/**
\brief  GetElement - 


\return bdata - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  index0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

BNFExpData *BNFExpData :: GetElement (int32 index0 )
{

  return( GetBNFExpData(BNFData::GetElement(index0)) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  symbol - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

BNFExpData *BNFExpData :: GetElement (char *symbol )
{

  return( GetBNFExpData(BNFData::GetElement(symbol)) );

}

/******************************************************************************/
/**
\brief  GetElementCount - 


\return elmcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementCount"

int16 BNFExpData :: GetElementCount ( )
{
  BNFExpData                *elm_data;
  BNFExpData                *elm_list = GetAccessPath();
  int                        elmcount = 0;
BEGINSEQ
  if ( !elm_list )                                  ERROR
  if ( !elm_list->IsA("parm_list") )                LEAVESEQ
    
  elm_data = elm_list->GetElement(elmcount);      // parameter
  while ( elm_data )
  {
    elmcount++;
    elm_data = elm_list->GetElement(elmcount);    // param_ext
  }

RECOVER
  elmcount = AUTO;
ENDSEQ
  return(elmcount);
}

/******************************************************************************/
/**
\brief  GetElementaryView - 


\return bdata - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementaryView"

BNFData *BNFExpData :: GetElementaryView ( )
{
  BNFData                *bdata = NULL;
BEGINSEQ
  // (a,b) or (a)
  if ( IsSymbol("operand_list") )
  {
    bdata = GetElement("parm_list");
    if ( bdata->GetElementCount() > 1 )              LEAVESEQ
    if ( bdata->IsSymbol("operand") )
      bdata = bdata->GetSymbol("operand");
    else
      if ( !bdata->IsValue("*") )                    ERROR
  }
  else if ( IsSymbol("sngl_operand") )
    bdata = GetElement("operand");
  if ( !bdata )                                      ERROR
    
  if ( bdata->IsValue("*") )                         LEAVESEQ
    
  if ( !(bdata = bdata->GetSymbol("access_path")) )  ERROR
  
  // must have at least two path elements: a.b
  if ( bdata->GetElementCount() <= 1 )               ERROR
RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetIntegerConstant - 


\return intval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIntegerConstant"

int32 BNFExpData :: GetIntegerConstant ( )
{
  BNFExpData                *bdata = this;
  char                      *string = NULL;
  int                        intval;
BEGINSEQ
  if ( !bdata->IsA("std_constant") )
  {
    if ( !(bdata = bdata->GetSimpleOp()) )           ERROR
    if ( !bdata->IsA("std_constant") )               ERROR
  }
  if ( !(bdata = bdata->GetElement("std_integer")) ) ERROR
  if ( !(string = bdata->GetStringValue(NULL,NULL)) )ERROR
  
  intval = atol(string);
  

RECOVER
  intval = 0;
ENDSEQ
  return(intval);
}

/******************************************************************************/
/**
\brief  GetOperand - 


\return operand - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOperand"

BNFData *BNFExpData :: GetOperand ( )
{
  BNFData                *bdata = this;
BEGINSEQ
  // parameters, which are not operands are '*'
  
  if ( bdata = GetSymbol("condition") )
    bdata = bdata->GetElement("operand");
  else if ( bdata = GetSymbol("operand_list") )
    bdata = bdata->GetElement("parm_list");
  else
    bdata = this;
  
  bdata = bdata->GetSymbol("operand");
  
  if ( !bdata->IsA("operand") )                       ERROR

RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetOperandCount - 


\return parmcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOperandCount"

int16 BNFExpData :: GetOperandCount ( )
{
  BNFExpData                *bin_operand;
  BNFExpData                *operation = this;
  int16                        opcount = 1;
BEGINSEQ
  if ( !IsA("operation") )
  {
    if ( !IsA("operand") )                           ERROR
    operation = GetElement(0);
    opcount = 1;
    if ( operation->IsA("un_operation") )            LEAVESEQ
  }
    
  if ( !(bin_operand = GetElement(1)) )              LEAVESEQ
  opcount++;
  opcount += bin_operand->GetElement(1)->GetOperandCount();
    

RECOVER
  opcount = 0;
ENDSEQ
  return(opcount);
}

/******************************************************************************/
/**
\brief  GetParmCount - 


\return parmcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmCount"

int16 BNFExpData :: GetParmCount ( )
{
  BNFData     *parm_list = GetParmList(); // nicht BNFExpData, damit BNFData-function gerufen wird
  int          parmcount = 1;
BEGINSEQ
  if ( IsSymbol("condition") )                       LEAVESEQ
  if ( !parm_list )                                  ERROR
    
  parmcount = parm_list->GetElementCount();         // parameter

RECOVER
  parmcount = AUTO;
ENDSEQ
  return(parmcount);
}

/******************************************************************************/
/**
\brief  GetParmList - 


\return parm_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmList"

BNFExpData *BNFExpData :: GetParmList ( )
{
  BNFExpData       *bdata     = this;
  BNFExpData       *parm_list = this;
BEGINSEQ
  if ( IsA("name_index") )
    parm_list = GetElement(1);  // '[' operand ']'
  else
  {
    if ( IsA("path_operand") )
      bdata = GetElement(0);
  
    if ( bdata->IsA("operand_list") )
    {
      parm_list = bdata->GetElement(1);
      if ( !parm_list->IsA("parm_list") )           LEAVESEQ  // '()'
    }  
  
    if ( !parm_list->IsA("parm_list") )             ERROR
  }
RECOVER
  parm_list = NULL;
ENDSEQ
  return(parm_list);
}

/******************************************************************************/
/**
\brief  GetPathElement - 


\return fmcbptr - 

\param  dictptr - Dictionary handle
\param  bnf_data - 
\param  smcbptr - Pointer to general structure definition
\param  operenv - 
\param  var_type - 
\param  path_opt_ref - Type of property path
\param  autopos - 
\param  autokey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathElement"

fmcb *BNFExpData :: GetPathElement (Dictionary *dictptr, BNFData *bnf_data, smcb *smcbptr, OperEnvironment *operenv, FunctionTypes &var_type, int8 &path_opt_ref, int32 &autopos, char **autokey )
{
  fmcb            *fmcbptr = NULL;
  int              indx0   = 0;
  int              offset  = 0;
  BNFData         *name;
  BNFData         *strname;
  logical          cond    = YES;
BEGINSEQ
// path_opt_ref : 0 -
//                1 - indexed property: name(constant)
//                2 - indexed property: name[constant]
//                3 - indexed by expression: name(a+b)
//                4 - iteration: name(*) or name()

  path_opt_ref = NO;
    
  if ( bnf_data->IsSymbol("scoped_name") )
    name = bnf_data->GetSymbol("scoped_name");
  else
  {
    if ( !bnf_data->IsA("path_element") )            ERROR
    if ( bnf_data->IsSymbol("path_name") )      // a or a[3]
    {
      bnf_data = bnf_data->GetElement(0);       // path_operand
      name = bnf_data = bnf_data->GetElement(0);// path_name
      if ( !bnf_data->IsSymbol("pname") )       // a[3]
      {
        path_opt_ref = 2;
        bnf_data = bnf_data->GetElement(1);    // name_index
        bnf_data = bnf_data->GetElement(1);    // operand
        if ( !bnf_data->IsSymbol("std_constant") )   ERROR
      }
    }
    else                                      // a(3), a()
    {
      path_opt_ref = 1;
      name  = bnf_data->GetElement(0);        // path_operand
      if ( !name->IsSymbol("path_name") )            ERROR
      name  = name->GetElement(0);            // path_name
      if ( !name->IsSymbol("pname") )                ERROR
      bnf_data = bnf_data->GetElement(1);     // operand_list
      if ( bnf_data = bnf_data->GetElement("parm_list") )
      { // more than one parameter
        if ( bnf_data->GetElementCount() > 1 )      ERROR
        bnf_data = bnf_data->GetElement("parameter");
        if ( !bnf_data->IsSymbol("std_constant") && !bnf_data->IsSymbol("sys_variable") ) 
        {
          if ( bnf_data->IsValue("*") )
            path_opt_ref = 4;   
          else if ( bnf_data->IsSymbol("operand") ) 
            path_opt_ref = 3;   
          else                                      ERROR
        }
      }
      else
        path_opt_ref = 4;                     
    }
    name = name->GetElement(0)->GetElement(0);
  }

  if ( !name->IsSymbol("scoped_name") )              ERROR
  if ( !name->IsSymbol("identifier") )
  {
    TypeKey     tkey;
    tkey.InitPropertyType(dictptr,name->StringValue());
    smcbptr = dictptr->ProvideStructDef(tkey); 
    name = name->GetLastElement()->GetElement(1);  // member name
  }
  
  if ( smcbptr )
    if ( fmcbptr = smcbptr->SearchField(name->StringValue(),&offset) )
      var_type = FT_Property;
    else if ( fmcbptr = DBStructDef::GetMetaAttribute(name->StringValue()) )
      var_type = FT_MetaAttribute;

// function should be checked as well ...

// not first element
  if ( !fmcbptr && var_type != FT_undefined )       ERROR

  if ( !fmcbptr && operenv )
  {
    if ( fmcbptr = operenv->GetVariableDef(name->StringValue()) )
      var_type = FT_Variable;
    else if ( fmcbptr = operenv->GetParameterDef(name->StringValue()) )
      var_type = FT_Parameter;
  }
  
  if ( !fmcbptr && !dictptr->CheckExtendDef(name->StringValue()) )
    if ( fmcbptr = dictptr->ProvideExtendDef(name->StringValue()) )
      var_type = FT_Extent;

  if ( !fmcbptr ) 
    if ( fmcbptr = dictptr->GetGlobalVariable(name->StringValue())->GetDescription() )
      var_type = FT_Global;

  if ( !fmcbptr )                                    ERROR
  
  autopos = AUTO;
  if ( autokey && path_opt_ref > 0 && path_opt_ref < 4 )
  {
    if ( bnf_data->IsSymbol("std_integer") )
      autopos = atoi(bnf_data->StringValue());
    else if ( bnf_data->IsSymbol("std_string") )
      *autokey = strdup(bnf_data->GetConstantString());
    else if ( bnf_data->IsSymbol("sys_variable") )
    {
      if ( *autokey = GetSysVariable(bnf_data->GetElement("identifier")->StringValue()) )
        *autokey = strdup(*autokey);
    }
    else if ( bnf_data->IsSymbol("operand") )
      *autokey = strdup(bnf_data->StringValue());
    else                                             ERROR
  }

RECOVER
  fmcbptr = NULL;
ENDSEQ
  return(fmcbptr);
}

/******************************************************************************/
/**
\brief  GetPathType - 


\return ptype - 

\param  obhandle - Database Object handle
\param  structdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathType"

PathTypes BNFExpData :: GetPathType (ACObject *obhandle, DBStructDef *structdef )
{
  int8              path_opt = NO;
  FunctionTypes     path_type = FT_undefined;
  PathTypes         ptype    = OPT_undefined;
  if ( GetElementaryView() )              // (a,b) or (a)
    ptype = OPT_ElementaryView;
  else if ( IsPropertyPath(obhandle,structdef,NULL,path_type,path_opt) )
  {
    if ( path_opt < 1 ) // Property path: a, a.b, a[2].b, a(2).b
      ptype = OPT_PropertyPath;
    else
      ptype = OPT_PathProperty;
  }
  return(ptype);
}

/******************************************************************************/
/**
\brief  GetPrivilege - 


\return privilege - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrivilege"

ODC_Privilege BNFExpData :: GetPrivilege ( )
{
  ODC_Privilege    privilege = ODC_undefined;
  switch ( GetSymbolCode("_public","_private","_protected") )
  {
    case 1 : privilege = ODC_public;     break;
    case 2 : privilege = ODC_private;    break;
    case 3 : privilege = ODC_protected;  break;
    default: privilege = ODC_undefined;
  }


  return(privilege);
}

/******************************************************************************/
/**
\brief  GetReferenceLevel - 


\return ref_level - Level, data is referenced

\param  indx_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReferenceLevel"

int32 BNFExpData :: GetReferenceLevel (int32 &indx_ref )
{
  BNFData                *ref_symbol;
  int32                   ref_level = 0;
BEGINSEQ
// declarator := ref_symbol(*)

  while ( (ref_symbol = GetElement(indx_ref)) && 
          ref_symbol->IsSymbol("ref_symbol")              )
  {
    if ( ref_symbol->IsValue("*") )
      ref_level++;
    else
      ref_level--;
    indx_ref++;
  }
  if ( ref_level < -1 || ref_level > 3 )             SDBERR(441)

RECOVER
  ref_level = ERIC;
ENDSEQ
  return(ref_level);
}

/******************************************************************************/
/**
\brief  GetScopeName - 


\return scope_name - 

\param  scope_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScopeName"

char *BNFExpData :: GetScopeName (char *scope_name )
{
  BNFData         *name;

BEGINSEQ
  if ( !IsA("path_element") )                        ERROR
  if ( !(name = GetElement("pname")) )               ERROR
    
  name = name->GetElement(0);
  if ( !name->IsSymbol("scoped_name") )              ERROR
  if ( name->IsSymbol("identifier") )                ERROR
    
  strcpy(scope_name,name->GetElement(0)->GetStringValue(NULL,NULL));

RECOVER
  scope_name = NULL;
ENDSEQ
  return(scope_name);
}

/******************************************************************************/
/**
\brief  GetSimpleOp - 


\return operand - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSimpleOp"

BNFExpData *BNFExpData :: GetSimpleOp ( )
{
  BNFExpData                *bdata = this;
BEGINSEQ
// function returns: operation | un_operation | access_path | block | constant 
// without any outer parenthesis, i.e. operations are either unary operations or binary
// operations with several operands

  if ( bdata->IsA("operand_list") )
    bdata = bdata->GetElement(1);
  
  if ( bdata->IsA("parm_list") )
  {
    if ( GetParmCount() != 1 )                       ERROR
    bdata = bdata->GetElement(0);
  }  

  if ( bdata->IsA("parameter") )
    if ( !(bdata = (BNFExpData *)bdata->GetOperand()) )            ERROR
  
  if ( bdata->IsA("operand") )
  {
    bdata = bdata->GetElement(0);
    if ( bdata->IsA("un_operation") )                LEAVESEQ
  }
  
  if ( bdata->IsA("operation") )
  {
    if ( bdata->GetOperandCount() > 1 )              LEAVESEQ
    
    bdata = bdata->GetElement(0)->GetElement(0); // bdata->?
    if ( bdata->IsA("operand_list") )
      bdata = bdata->GetSimpleOp();
    LEAVESEQ
  }

  ERROR
RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetStringConstant - 


\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringConstant"

char *BNFExpData :: GetStringConstant ( )
{
  BNFExpData                *bdata = this;
  char                      *string = NULL;
  int                        len;
BEGINSEQ
  if ( strcmp(bdata->Name(),"std_string") )
  {
    if ( !bdata->IsA("std_constant") )
    {
      if ( !(bdata = bdata->GetSimpleOp()) )         ERROR
      if ( !bdata->IsA("std_constant") )             ERROR
    }
    if ( !(bdata = bdata->GetElement("std_string")) )ERROR
  }
  if ( !(string = bdata->GetStringValue(NULL,NULL)) )ERROR
  
  string++;
  string[len = strlen(string)-1] = 0;
  STRExchange(string,"\\\"","\"",len);
  STRExchange(string,"\\\'","\'",len);

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetTypeSpec - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  type_name - 
\param  generic_type - 
\param  size_ref - 
\param  dim_ref - 
\param  prec_ref - 
\param  unicode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeSpec"

logical BNFExpData :: GetTypeSpec (char *type_name, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref )
{
  BNFData                *bdata = this;
  logical                 is_string = NO;
  logical                 term = NO;
BEGINSEQ
// simple_type_spec  := base_type_spec | extended_type_spec
// extended_type_spec:= array_type | gstring_type | coll_type | generic_type | interval_type | scoped_name

  dim_ref       = 1;
  size_ref      = 1;
  prec_ref      = 0;
  *type_name    = 0;
  *generic_type = 0;
  
  // string is not recognized as base type but as scoped name!!
  is_string = !strcmp(bdata->StringValue(),"string");

  if ( bdata->IsSymbol("simple_type_spec") )
    bdata = bdata->GetElement(0);
  if ( is_string || bdata->IsSymbol("base_type_spec") )
  {
    bdata = bdata->GetElement(0);
    if ( bdata->IsSymbol("floating_pt_type") )
    {
      strcpy(type_name,"REAL");
      size_ref = 17;
      if ( bdata->GetElement(0)->IsSymbol("float") )
        size_ref = 7;
    }
    else if ( bdata->IsSymbol("integer_type") )
    {
      strcpy(type_name,"INT");
      size_ref = 10;
      if ( bdata->GetElement("_unsigned") )
        strcpy(type_name,"UINT");
      bdata = bdata->GetElement("int_types");
      if ( bdata->IsSymbol("short_int") )
        size_ref = 4;
      else if ( bdata->IsSymbol("long_int") )
        size_ref = 10;
      else if ( bdata->IsSymbol("long_long_int") )
        size_ref = 20;
      else if ( bdata->IsSymbol("char_type") )
        size_ref = 2;
      else if ( bdata->IsSymbol("int_spec") )
      {
        size_ref = 10;
        if ( bdata->GetElement("size") )
          size_ref = bdata->GetElement("size")->IntValue();
        if ( bdata->GetElement("precision_val") )
          prec_ref = bdata->GetElement("precision_val")->IntValue();
      }
    }
    else if ( is_string || bdata->IsSymbol("char_len_types") || bdata->IsSymbol("char_types") )
    {
      if ( bdata->GetElement(0)->IsSymbol("char_type") )
      {
        strcpy(type_name,"CHAR");
        size_ref = 40;
      }
      if ( bdata->GetElement(0)->IsSymbol("coded_type") )
      {
        strcpy(type_name,"CCHAR");
        size_ref = 40;
      }
      if ( bdata->GetElement(0)->IsSymbol("wstring_type") )
      {
        strcpy(type_name,"STRING");
        size_ref = 0;                // auto-resize, when no size defined
        unicode_ref = YES;
      }
      if ( is_string || bdata->GetElement(0)->IsSymbol("string_type") )
      {
        strcpy(type_name,"STRING");
        size_ref = 0;                // auto-resize, when no size defined
      }
      bdata = bdata->GetElement(1);
      if ( bdata && bdata->IsSymbol("len_spec") )
        if ( bdata->GetElement("size") )
          size_ref = bdata->GetElement("size")->IntValue();
    }
    else if ( bdata->IsSymbol("boolean_type") )
    {
      strcpy(type_name,"LOGICAL");
      size_ref = 1;
    }
    else if ( bdata->IsSymbol("any_type") )
    {
      strcpy(type_name,"VOID");
      size_ref = 0;
    }
    else if ( bdata->IsSymbol("date_type") )
    {
      strcpy(type_name,"DATE");
      size_ref = 8;
    }
    else if ( bdata->IsSymbol("time_type") )
    {
      strcpy(type_name,"TIME");
      size_ref = 8;
    }
    else if ( bdata->IsSymbol("timestamp_type") )
    {
      strcpy(type_name,"DATETIME");
      size_ref = 16;
    }
    else if ( bdata->IsSymbol("bit_type") )
    {
      strcpy(type_name,"BIT");
      size_ref = 1;
    }
    else if ( bdata->IsSymbol("binary_type") )
    {
      strcpy(type_name,"BLOB");
      size_ref = 0;
    }
    else if ( bdata->IsSymbol("octet_type") )             SDBERR(437)
  }
  else if ( bdata->IsSymbol("extended_type_spec") )
  {
// extended_type_spec := array_type | gstring_type | coll_type | generic_type | scoped_name
    bdata = bdata->GetElement(0);
    if ( bdata->IsSymbol("gstring_type") )
    {
//      strcpy(generic_type,"STRING");
      strcpy(type_name,"STRING");
      size_ref = 0;                // dynamic string;
      if ( bdata = bdata->GetElement("string_size_ref") )
        size_ref = atoi(bdata->StringValue());
    }
    else if ( bdata->IsSymbol("array_type") )
    {
      if ( ((BNFExpData *)bdata->GetElement("simple_typ_spec"))->GetTypeSpec(type_name,generic_type,size_ref,dim_ref,prec_ref,unicode_ref) )
                                                     ERROR
      if ( *generic_type )                           SDBERR(439)
      strcpy(generic_type,"ARRAY");
      if ( bdata->GetElement("sequence") )
        strcpy(generic_type,"SEQUENCE");
      if ( bdata = bdata->GetElement("const_exp") )
        dim_ref = bdata->IntValue();
    }
    else if ( bdata->IsSymbol("coll_type") )
    {
// coll_type := dict_coll | coll_coll
      if ( bdata->GetSymbol("dict_coll") )            SDBERR(440)
      if ( ((BNFExpData *)bdata->GetElement("simple_type_spec"))->GetTypeSpec(type_name,generic_type,size_ref,dim_ref,prec_ref,unicode_ref) )
                                                     ERROR
      if ( *generic_type )                           SDBERR(439)
      strcpy(generic_type,"SET");
      if ( bdata->GetElement("list") )
        strcpy(generic_type,"LIST");
      if ( bdata->GetElement("bag") )
        strcpy(generic_type,"BAG");
      dim_ref = 0;
    }
    else if ( bdata->IsSymbol("generic_type") )
    {
      if ( ((BNFExpData *)bdata->GetElement("simple_type_spec"))->GetTypeSpec(type_name,generic_type,size_ref,dim_ref,prec_ref,unicode_ref) )
                                                     ERROR
      if ( *generic_type )                           SDBERR(439)
      strcpy(generic_type,bdata->GetElement("identifier")->StringValue());
    }
    else if ( bdata->IsSymbol("scoped_name") )
    {
      if ( bdata->GetValueLength() > 40 )            SDBERR(438)
      strcpy(type_name,bdata->StringValue());
    }
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  type_name - 
\param  generic_type - 
\param  size_ref - 
\param  dim_ref - 
\param  prec_ref - 
\param  unicode_ref - 
\param  priv_ref - 
\param  virt_ref - 
\param  stat_ref - 
\param  trans_ref - 
\param  coll_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeSpec"

logical BNFExpData :: GetTypeSpec (char *type_name, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref, ODC_Privilege &priv_ref, logical &virt_ref, logical &stat_ref, logical &trans_ref, logical &coll_ref )
{
  BNFData                *bdata = this;
  BNFExpData             *dtype;
  BNFData                *options;
  int32                   index = 0;
  logical                 term = NO;
BEGINSEQ
// type_ref         := [type_ref_options(*)] domain_type             // ODABA extension
// mtype_ref        := [type_ref_options(*)] simple_type_spec        // ODABA extension
// base_type        := [base_option(*)] extended_type_spec
// type_spec        := simple_type_spec | constr_type_spec
// simple_type_spec
  
  if ( !(dtype = (BNFExpData *)bdata->GetSymbol("simple_type_spec")) )
  {
    while ( options = bdata->GetElement(index) )
    {
      if ( options->IsSymbol("type_ref_options") || options->IsSymbol("base_option"))
      {
        switch ( options->GetSymbolCode("priv_option","prop_option") )
        {
          case 1 : priv_ref = ((BNFExpData *)options->GetElement(0))->GetPrivilege();
                   break;
          case 2 : switch ( options->GetElement(0)->GetSymbolCode(
                      "_static","_transient","_virtual","_collection") )
                   {
                     case 1 : stat_ref  = YES;  break;
                     case 2 : trans_ref = YES;  break;
                     case 3 : virt_ref  = YES;  break;
                     case 4 : coll_ref  = YES;  break;
                   }
        }
        index++;
      }
      else
        break;
    }
  
    dtype = (BNFExpData *)bdata->GetElement(index);
    if ( dtype->IsSymbol("domain_type") )
      dtype = (BNFExpData *)dtype->GetElement(0);
  }
  if ( !dtype )                                      ERROR  // constr_type_spec fehlt noch
  if ( dtype->GetTypeSpec(type_name,generic_type,size_ref,dim_ref,prec_ref,unicode_ref) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsBlock - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBlock"

logical BNFExpData :: IsBlock ( )
{

  return( this && 
         (!strcmp(Name(),"block") || !strcmp(Name(),"expr_code")));  


}

/******************************************************************************/
/**
\brief  IsExpression - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpression"

logical BNFExpData :: IsExpression ( )
{
  BNFExpData                *bdata = this;
  logical                    cond = YES;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !strcmp(Name(),"block") || !strcmp(Name(),"expr_code") )
                                                     LEAVESEQ
  
  if ( bdata = GetSimpleOp() )
    if ( bdata->IsBlock() || bdata->IsA("operation") ||
         IsA("un_operation")                      )  LEAVESEQ
      
  ERROR


RECOVER
  cond = NO;
ENDSEQ
  return (cond);
}

/******************************************************************************/
/**
\brief  IsPropertyPath - 


\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  obhandle - Database Object handle
\param  smcbptr - Pointer to general structure definition
\param  operenv - 
\param  path_type - 
\param  path_opt_ref - Type of property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPropertyPath"

logical BNFExpData :: IsPropertyPath (ACObject *obhandle, smcb *smcbptr, OperEnvironment *operenv, FunctionTypes &path_type, int8 &path_opt_ref )
{
  Dictionary      *dictptr = obhandle->GetDictionary();

  return( IsPropertyPath(smcbptr,dictptr,operenv,path_type,path_opt_ref) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  smcbptr - Pointer to general structure definition
\param  dictptr - Dictionary handle
\param  operenv - 
\param  path_type - 
\param  path_opt_ref - Type of property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPropertyPath"

logical BNFExpData :: IsPropertyPath (smcb *smcbptr, Dictionary *dictptr, OperEnvironment *operenv, FunctionTypes &path_type, int8 &path_opt_ref )
{
  fmcb            *fmcbptr = NULL;
  BNFData         *path_extension;
  int              indx0   = 0;
  int              offset  = 0;
  char            *autokey = NULL;         
  int8             path_opt;
  BNFData         *acp;
  BNFData         *bdata;
  FunctionTypes    vtype = FT_undefined;
  logical          cond    = YES;
BEGINSEQ
  path_opt_ref = NO;

  if ( !(acp = GetSymbol("access_path")) )
  {
    if ( IsSymbol("path_element") )
      bdata = this;
    else
    {
      if ( !IsSymbol("pname") )                        ERROR
      switch ( GetSymbolCode("oql_oper","scoped_name","any_type","db_name") )
      {
        case 1 : ERROR                                 // OQL operation
        case 2 : bdata = this;
                 break;
        case 3 :
        case 4 : LEAVESEQ                              // VOID or overlay extent
      }
    }
  }
  else if ( !(bdata = acp->GetElement(indx0++)) )    ERROR
  
  if ( !smcbptr )
  { 
    if ( !bdata->IsA("path_element") && !bdata->IsSymbol("pname") ) 
                                                     ERROR
    if ( !(fmcbptr = GetPathElement(dictptr,bdata,NULL,operenv,vtype,path_opt,offset,NULL)) )
                                                     ERROR
    path_type = vtype;
    if ( !(smcbptr = fmcbptr->fmcbsmcb) )            ERROR
    
    if ( !acp )                                      LEAVESEQ
    bdata = (path_extension = acp->GetElement(indx0++))
            ? path_extension->GetElement(1) : NULL;
  }
  
  while ( bdata && smcbptr )
  {
    if ( !(fmcbptr = GetPathElement(dictptr,bdata,smcbptr,operenv,vtype,path_opt,offset,NULL)) )
                                                     ERROR
    if ( path_type == FT_undefined ) // first element 
      path_type = vtype;             // type of first element
      
    if ( path_opt > path_opt_ref )
      path_opt_ref = path_opt;
      
    if ( smcbptr = fmcbptr->fmcbsmcb )
      if ( smcbptr->smcbityp == UNDEF && dictptr )
        if ( !(smcbptr = dictptr->ProvideStructDef(smcbptr->smcbname)) )
                                                     ERROR
    
    if ( !acp )                                      LEAVESEQ
    if ( bdata = (path_extension = acp->GetElement(indx0++))
                       ? path_extension->GetElement(1) : NULL  )
      if ( !smcbptr )                                ERROR  
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}


