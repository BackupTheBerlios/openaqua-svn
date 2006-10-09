/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cPFunctionRetParms



\date     $Date: 2006/04/24 13:43:00,44 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cPFunctionRetParms"

#include  <pdesign.h>
#include  <scPFunctionRetParms.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cPFunctionRetParms :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cPFunctionRetParms();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoBeforeFillData

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cPFunctionRetParms :: DoBeforeFillData ( )
{
  char   executed = NO;
BEGINSEQ
  if ( cNotifyHighContext::DoBeforeFillData() == YES ||
       !GetPropertyHandle()->IsSelected() )              ERROR

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cPFunctionRetParms


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cPFunctionRetParms"

                        cPFunctionRetParms :: cPFunctionRetParms ( )
                     : cNotifyHighContext()
{



}

/******************************************************************************/
/**
\brief  ~cPFunctionRetParms


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cPFunctionRetParms"

                        cPFunctionRetParms :: ~cPFunctionRetParms ( )
{



}


