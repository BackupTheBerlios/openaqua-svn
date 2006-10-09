/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDefineContext

\brief    


\date     $Date: 2006/06/01 17:01:54,12 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cDefineContext"

#include  <pdesign.h>
#include  <scDefineContext.hpp>


/******************************************************************************/
/**
\brief  AssociateEntry - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AssociateEntry"

logical cDefineContext :: AssociateEntry ( )
{
  CTX_Control *class_list       = GetFieldContext("context_class_selection");
  CTX_Control *associate_button = GetButtonContext("associate_bitmap");
  if ( class_list )
    class_list->SetHidden(NO);
  if ( associate_button )
    associate_button->SetHidden(YES);
  return(NO);
}

/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cDefineContext :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cDefineContext();
  return(NO);

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

logical cDefineContext :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("AssociateEntry",ALINK(this,cDefineContext,AssociateEntry)),
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
\brief  cDefineContext - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cDefineContext"

     cDefineContext :: cDefineContext ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cDefineContext - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cDefineContext"

     cDefineContext :: ~cDefineContext ( )
{



}


