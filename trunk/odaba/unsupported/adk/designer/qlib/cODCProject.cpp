/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cODCProject



\date     $Date: 2006/05/23 14:17:16,48 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cODCProject"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <spc1_ODC_Project.hpp>
#include  <scODCProject.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cODCProject :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cODCProject();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterFillData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterFillData"

int8 cODCProject :: DoAfterFillData ( )
{
  pODE      *ode_ctx  = ODEContext(this);
  logical    term     = NO;
BEGINSEQ
  if ( UserState1() )                               LEAVESEQ
  if ( !ode_ctx )                                   ERROR

  ode_ctx->SelectProject("");  // nur Anfangsinitialisierung; durch pODE::DoAfterOpen gesetzt

  SetUserState1(YES);
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterHandleOpen

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleOpen"

int8 cODCProject :: DoAfterHandleOpen ( )
{

  SetFilter(YES);
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterSelect

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cODCProject :: DoAfterSelect ( )
{
  pODE     *ode_ctx = NULL;

BEGINSEQ
  if ( UserState2() )                               LEAVESEQ
  SetUserState2(YES);
  
  if ( ode_ctx = ODEContext(this) )
    ode_ctx->SelectProject(GetData()->GetString());

  SetUserState2(NO);

ENDSEQ
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

int8 cODCProject :: DoBeforeDataSet ( )
{
  pODE              *ode_ctx    = ODEContext(this);
  char               term    = NO;
BEGINSEQ
  if ( !ode_ctx->IsActionToggled("ProjectSelection") ) LEAVESEQ
  
  pc1_ODC_Project   prop_pc(GetBasePropertyHandle());
  
  if ( !prop_pc.Exist() )                            P_ERR(99)
  if ( !prop_pc.Get(AUTO) )                          P_SDBCERR
    
  if ( !prop_pc.IsImplemented(NO) )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cODCProject


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cODCProject"

     cODCProject :: cODCProject ( )
{
}

/******************************************************************************/
/**
\brief  ~cODCProject


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cODCProject"

     cODCProject :: ~cODCProject ( )
{
}


