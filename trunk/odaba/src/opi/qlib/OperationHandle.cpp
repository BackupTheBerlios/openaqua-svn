/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    OperationHandle

\brief    Operation Handle
          Operation  handles can be used for executing operations as expressions
          or  function  calls.  Usually,  an  operation  is  associated  with  a
          property  handle defining the instance that is passed to the operation
          as calling object.

\date     $Date: 2006/06/22 18:36:13,39 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OperationHandle"

#include  <pdefault.h>
#include  <sBNFData.hpp>
#include  <sCOperation.hpp>
#include  <sDictionary.hpp>
#include  <sLOperation.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <snode.hpp>
#include  <sOperationHandle.hpp>


/******************************************************************************/
/**
\brief  CheckExpression - Check validity of an expression
        The  function checks  whether the  expression passed  to the function is
        syntactically correct (NO) or not (YES, error).

\return term - Termination code
-------------------------------------------------------------------------------
\brief  I00 - 


\param  dictptr - Dictionary handle
\param  expression - 
\param  obhandle - 
\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical OperationHandle :: CheckExpression (DictionaryHandle &dictptr, char *expression, DBObjectHandle &obhandle, char *clsnames )
{
  logical          term = NO;
BEGINSEQ
  dictptr.get_dictionary()->CheckExpression(expression,obhandle.get_obhandle(),clsnames);
                                                     SDBCERR
  if ( OQLERROR )                                    SDBERR(OQL_ERROR)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InClass - 


\param  dictptr - Dictionary handle
\param  resobj - 
\param  clsnames - 
\param  exprnames - 
\param  impnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical OperationHandle :: CheckExpression (DictionaryHandle &dictptr, DBObjectHandle &resobj, char *clsnames, char *exprnames, char *impnames )
{
  logical          term = NO;
BEGINSEQ
  dictptr.get_dictionary()->CheckExpression(resobj.get_obhandle(),
                                            clsnames,exprnames,impnames);
                                                     SDBCERR
  if ( OQLERROR )                                    SDBERR(OQL_ERROR)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - Execute operation
        The  function executes  a predefined  opoeration. The result is returned
        as property handle. 
        It  is  possible  to  pass  a  property  handle as calling object. If no
        property  handle  is  passed  the  one  that  was  used for creating the
        operation  is used as calling object. When using amother property handle
        than the originating one, the type of the properties must be identical.
        The  result  of  the  operation  can  be  provided  with the GetResult()
        function.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci - Calling expression with fixed property handle
        This  implementation  calls  the  expression  with  the  property handle
        passed  when  the  operation  has  been  created.  The  selection in the
        property handle may change but not the property handle.

\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical OperationHandle :: Execute (ParmList *parameters )
{

  return ( IsValid() 
           ? operation->Execute(parameters)
           : YES );

}

/******************************************************************************/
/**
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical OperationHandle :: Execute ( )
{

  return ( IsValid() 
           ? operation->Execute(NULL)
           : YES );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  call_object - 
\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical OperationHandle :: Execute (PropertyHandle &call_object, ParmList *parameters )
{
  PropertyHandle    *temp_ph;
  logical            term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR

  temp_ph = operation->get_calling_object();
  operation->SetCallingObject(&call_object);

  term = operation->Execute(parameters);

  operation->SetCallingObject(temp_ph);

RECOVER
  return(term);
ENDSEQ

}

/******************************************************************************/
/**
\brief  GetDimension - Get dimension of returned value
        The  function  returns  the  dimension  for  the instance created by the
        function.  If the  result dimension  can not  be determined the function
        returns -1 (AUTO).
        In  some  cases  the  dimension  for  the  result  can  be provided ater
        executing  the  expression.  In  this  cate the function also returns -1
        (AUTO).

\return dimension - Dimension

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 OperationHandle :: GetDimension ( )
{

  return ( operation->IsValid()
           ? operation->GetDimension()
           : UNDEF );

}

/******************************************************************************/
/**
\brief  GetResult - Get result from the operation
        The  function returns a property handle  that contains the result of the
        last execution of the expression.

\return result - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResult"

PropertyHandle &OperationHandle :: GetResult ( )
{
  static     PropertyHandle    stat_ph;
  if ( this && operation )
    return( *(PropertyHandle *)operation );
  else 
    return( stat_ph );



}

/******************************************************************************/
/**
\brief  GetSize - Get size of returned value
        The  function  returns  the  area  size  for the instance created by the
        function.  If the result size can not be determined the function returns
        -1 (AUTO).

\return size - Size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

int32 OperationHandle :: GetSize ( )
{

  return ( operation->IsValid()
           ? operation->GetSize()
           : UNDEF );

}

/******************************************************************************/
/**
\brief  IsValid - Is operation handle valid
        The  function returns whether the operation handle is valid (YES) or not
        (NO). Only valid operation handles may be used for execution.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical OperationHandle :: IsValid ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( !this || !operation )                         ERROR

  if ( operation->get_nodeptr() && !operation->IsValid() ) ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Open - Open operation handle
        To  execute operations the opration handle must be opened. After opening
        the  operation handle an expression or a function can be associated with
        the operation handle for being executed.

\return term - Termination code

\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OperationHandle :: Open (PropertyHandle &prophdl_ref )
{
  PropertyHandle *oph = NULL;
  logical    term = NO;

BEGINSEQ
  if ( !prophdl_ref.IsValid() )                      ERROR
    
  oph = prophdl_ref.GetPropertyHandle(NULL);
  if ( oph->IsServer() )
    operation = new LOperation(*oph);
  else
    operation = new COperation(*oph);
  
  if ( !operation )                                  SDBERR(95)
  SDBCERR
  operation->SetHandle(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OperationHandle - Constructor
        The  constructor  creates  an  operation handle with the passed property
        handle as calling object.

-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OperationHandle"

     OperationHandle :: OperationHandle (PropertyHandle &prophdl_ref )
                     :   operation(NULL)
{

  Open(prophdl_ref);

}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OperationHandle"

     OperationHandle :: OperationHandle ( )
                     : operation(NULL)
{



}

/******************************************************************************/
/**
\brief  ProvideExpression - Create expression definition
        The  function  checks  the  expression and creates an internal epression
        presentation.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci - 


\param  dictionary - 
\param  resobj - 
\param  obhandle - 
\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExpression"

logical OperationHandle :: ProvideExpression (DictionaryHandle &dictionary, DBObjectHandle &resobj, DBObjectHandle &obhandle, char *expression )
{

  return ( dictionary.IsValid() 
           ? operation->ProvExpression(dictionary.get_dictionary(),
                                       resobj.get_obhandle(),
                                       obhandle.get_obhandle(),
                                       expression)
           : YES );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  dictionary - 
\param  resobj - 
\param  obhandle - 
\param  class_names - 
\param  expr_names - 
\param  parameters - 
\param  refresh_opt - Refresh option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExpression"

logical OperationHandle :: ProvideExpression (DictionaryHandle &dictionary, DBObjectHandle &resobj, DBObjectHandle &obhandle, char *class_names, char *expr_names, ParmList *parameters, logical refresh_opt )
{

  return ( dictionary.IsValid() 
           ? operation->ProvExpression(dictionary.get_dictionary(),
                                       resobj.get_obhandle(),
                                       obhandle.get_obhandle(),
                                       class_names, expr_names, parameters, refresh_opt)
           : YES );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  dictionary - 
\param  resobj - 
\param  obhandle - 
\param  expr_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExpression"

logical OperationHandle :: ProvideExpression (DictionaryHandle &dictionary, DBObjectHandle &resobj, DBObjectHandle &obhandle, BNFData *expr_data )
{

  return ( dictionary.IsValid() 
           ? operation->ProvExpression(dictionary.get_dictionary(),
                                       resobj.get_obhandle(),
                                       obhandle.get_obhandle(),
                                       expr_data)
           : YES );

}

/******************************************************************************/
/**
\brief  i03 - 


\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExpression"

logical OperationHandle :: ProvideExpression (char *expression )
{
  DictionaryHandle        dict;
  DBObjectHandle          dbo;
  DBObjectHandle          rdbo;

  return( ProvideExpression(dict,rdbo,dbo,expression) );

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OperationHandle :: Reset ( )
{

  operation = NULL;

}

/******************************************************************************/
/**
\brief  ~OperationHandle - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OperationHandle"

     OperationHandle :: ~OperationHandle ( )
{

  delete operation;
  operation = NULL;

}


