/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF) - Context that communicates with the output area
\class    cResRefDockingWin



\date     $Date: 2006/03/28 19:14:49,62 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cResRefDockingWin"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <scResRefDockingWin.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cResRefDockingWin :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cResRefDockingWin();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterDock

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDock"

int8 cResRefDockingWin :: DoAfterDock ( )
{
  CTX_Control  *doc_ctx = GetControlContext("edit_dockwin");
  DSize         size(700,40);
  int8          executed = NO;
  doc_ctx->SetDisplayLevel(1); 
  SetSize(size,YES,NO);

  return(executed);
}

/******************************************************************************/
/**
\brief  DoAfterOpen

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 cResRefDockingWin :: DoAfterOpen ( )
{
  pODE            *ode_ctx  = ODEContext(this);
  if ( ode_ctx )
    ode_ctx->SetDocumentContext(this);
  else
  {
    P_SET(99)
    P_RESET
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterUndock

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterUndock"

int8 cResRefDockingWin :: DoAfterUndock ( )
{
  CTX_Control  *doc_ctx = GetControlContext("edit_dockwin");
  DSize  size(350,270);
  int8   executed = NO;
  doc_ctx->SetDisplayLevel(2); 
  SetSize(size,YES,YES);

  return(executed);
}

/******************************************************************************/
/**
\brief  cResRefDockingWin


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cResRefDockingWin"

                        cResRefDockingWin :: cResRefDockingWin ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cResRefDockingWin


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cResRefDockingWin"

                        cResRefDockingWin :: ~cResRefDockingWin ( )
{



}


