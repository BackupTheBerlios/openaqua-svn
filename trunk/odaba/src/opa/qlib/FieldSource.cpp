/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FieldSource

\brief    


\date     $Date: 2006/03/12 19:17:34,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FieldSource"

#include  <popa7.h>
#include  <sFieldSource.hpp>


/******************************************************************************/
/**
\brief  FieldSource - 


-------------------------------------------------------------------------------
\brief i00


\param  expression - Expression
\param  key_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldSource"

                        FieldSource :: FieldSource (char *expression, char *key_name )
                     : ExpressionReference (NULL,expression)
{

  gvtxbts(order,key_name,sizeof(order)-1);


}

/******************************************************************************/
/**
\brief i01


\param  fld_source_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldSource"

                        FieldSource :: FieldSource (FieldSource &fld_source_ref )
                     : ExpressionReference (fld_source_ref)
{

  strncpy(order,fld_source_ref.order,sizeof(order));

}

/******************************************************************************/
/**
\brief i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldSource"

                        FieldSource :: FieldSource ( )
                     : ExpressionReference (NULL,(char *)NULL)
{

  memset(order,0,sizeof(order));

}

/******************************************************************************/
/**
\brief  GetOrder

\return string -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrder"

char *FieldSource :: GetOrder ( )
{

  return ( order );

}


