/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cProjectInputHelp

\brief    


\date     $Date: 2006/06/21 16:44:16,76 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cProjectInputHelp"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <scProjectInputHelp.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cProjectInputHelp :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cProjectInputHelp();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterShow - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterShow"

int8 cProjectInputHelp :: DoAfterShow ( )
{
  pODE            *ode_ctx     = ODEContext(this);
  char             executed    = NO;
BEGINSEQ
  if ( SetDatasource(ode_ctx->GetClassInputHelpPH(NO)) )
                                                     ERROR    

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cProjectInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cProjectInputHelp"

     cProjectInputHelp :: cProjectInputHelp ( )
                     : cInputHelpBase ()
{



}

/******************************************************************************/
/**
\brief  ~cProjectInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cProjectInputHelp"

     cProjectInputHelp :: ~cProjectInputHelp ( )
{



}


