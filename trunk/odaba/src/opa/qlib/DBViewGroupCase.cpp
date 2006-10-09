/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBViewGroupCase

\brief    Group Case


\date     $Date: 2006/08/28 12:49:04,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBViewGroupCase"

#include  <popa7.h>
#include  <sBNFData.hpp>
#include  <sDBViewGroupCase.hpp>


/******************************************************************************/
/**
\brief  DBViewGroupCase - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  namestr - 
\param  value - 
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewGroupCase"

     DBViewGroupCase :: DBViewGroupCase (char *namestr, int32 value, char *expression )
                     :   code(value),
  condition(NULL)
{

  if ( name && *name )
    gvtxbts(name,namestr,sizeof(name)-1);

  if ( expression && *expression )
    condition = strdup(expression);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewGroupCase"

     DBViewGroupCase :: DBViewGroupCase (BNFData *bnf_data )
                     :   code(UNDEF),
  condition(NULL)
{
  BNFData               *bdata;
// category_spec         := cat_name [ cat_condition ]
// cat_condition         := ':' operand
// cat_name              := identifier | string | number

  bdata = bnf_data->GetSymbol("cat_name");
  if ( bdata->IsSymbol("std_number") )
    code = atoi(bdata->GetElement("std_number")->StringValue());
  else if ( bdata->IsSymbol("std_string") )
    bdata->GetSymbol("std_string")->GetStringConstant();
  else if ( bdata->IsSymbol("identifier") )
    bdata->GetSymbol("std_string")->GetValue(name,sizeof(name));

  if ( bdata = bnf_data->GetElement("cat_condition") )
    condition = strdup(bdata->GetElement(1)->StringValue());

}

/******************************************************************************/
/**
\brief  ~DBViewGroupCase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBViewGroupCase"

     DBViewGroupCase :: ~DBViewGroupCase ( )
{

  if ( condition ) 
    free(condition);
  condition = NULL;

}


