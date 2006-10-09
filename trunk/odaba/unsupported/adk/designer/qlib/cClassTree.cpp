/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassTree

\brief    


\date     $Date: 2006/06/01 16:57:21,01 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassTree"

#include  <pdesign.h>
#include  <scWorkspace.hpp>
#include  <spODE.hpp>
#include  <scClassTree.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return  - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassTree :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassTree();
  return(NO);


}

/******************************************************************************/
/**
\brief  DesignEntry - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DesignEntry"

logical cClassTree :: DesignEntry ( )
{
  CTX_Control * base_window;
  cWorkspace  * workspace;

BEGINSEQ
  base_window = (CTX_Control*)HighContext("designer", CTXT_Control);
  if ( !base_window )                                OADIERR(99)
  workspace   = (cWorkspace*)base_window->GetControlContext("workspace");
  if ( !workspace )                                  OADIERR(99)
  workspace->ShowControl(GetCurrentPropertyHandle());
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cClassTree :: DoAfterSelect ( )
{
  pODE            *ode_ctx  = ODEContext(this);
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
  char             executed = NO;
  if ( prophdl && prophdl->IsSelected() )
    ode_ctx->SetDocumentPH(prophdl);

  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cClassTree :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DesignEntry",ALINK(this,cClassTree,DesignEntry)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_Control::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cClassTree - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassTree"

     cClassTree :: cClassTree ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cClassTree - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassTree"

     cClassTree :: ~cClassTree ( )
{



}


