/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cImpClassList



\date     $Date: 2006/05/23 14:20:16,09 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cImpClassList"

#include  <pdesign.h>
#include  <spc1_SDB_Structure.hpp>
#include  <scImpClassList.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cImpClassList :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cImpClassList();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterHandleOpen

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleOpen"

int8 cImpClassList :: DoAfterHandleOpen ( )
{

  SetFilter(YES);
  return(NO);
}

/******************************************************************************/
/**
\brief  DoBeforeDataSet

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDataSet"

int8 cImpClassList :: DoBeforeDataSet ( )
{
  PropertyHandle  *resource_type = GetHighContext()->GetPropertyHandle()->GPH("resource_type");
  int8        executed          = NO;
BEGINSEQ
  if ( !resource_type )                              LEAVESEQ

  if ( pc1_SDB_Structure(GetBasePropertyHandle()).
             CheckContextClass(resource_type->GetString(),NULL,NULL) )
                                                     ERROR
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cImpClassList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cImpClassList"

     cImpClassList :: cImpClassList ( )
                     : CTX_Control ()
{
}

/******************************************************************************/
/**
\brief  ~cImpClassList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cImpClassList"

     cImpClassList :: ~cImpClassList ( )
{
}


