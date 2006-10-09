/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPConstant

\brief    


\date     $Date: 2006/08/25 14:49:50,40 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPConstant"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <snode.hpp>
#include  <sOPConstant.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPConstant :: Initialize (int32 ini_opt )
{
  char                   *wstr = NULL;
  logical                 term = NO;
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : SetDescription(value.GetDescription());
    default : re_open = 0;
  }  
  

  return(term);
}

/******************************************************************************/
/**
\brief  OPConstant - 



\return term - 

\param  oper_bnf - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPConstant"

     OPConstant :: OPConstant (BNFData *oper_bnf, OPBase *parent_node )
                     : OPBase (oper_bnf,parent_node)
{

  op_type = NT_OPConstant;

  OpenValue(oper_bnf);  
  Initialize(0);

}

/******************************************************************************/
/**
\brief  OpenValue - 




\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenValue"

void OPConstant :: OpenValue (BNFData *oper_bnf )
{

  if ( oper_bnf->IsSymbol("std_string") )
    value.Open(oper_bnf->GetStringConstant());
  else 
  {
    if ( oper_bnf->IsSymbol("std_integer") )
      value.Open((int32)0);
    else if ( oper_bnf->IsSymbol("std_float") )
      value.Open(0.0);
    
    if ( oper_bnf->IsSymbol("std_bool") )
    {
      if ( oper_bnf->IsValue("true") )
        value.Open((logical)1);
      else
        value.Open((logical)0);
    }
    else
      value = oper_bnf->StringValue();
  }
  


}

/******************************************************************************/
/**
\brief  ResetValue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetValue"

void OPConstant :: ResetValue ( )
{

  // do not close value for constant

}

/******************************************************************************/
/**
\brief  ~OPConstant - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPConstant"

     OPConstant :: ~OPConstant ( )
{



}


