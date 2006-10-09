/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cFont

\brief    


\date     $Date: 2006/06/01 17:07:12,54 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cFont"

#include  <pdesign.h>
#include  <scFont.hpp>


/******************************************************************************/
/**
\brief  Changed - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Changed"

logical cFont :: Changed ( )
{
  CTX_Control        * preview = NULL;
  DFont                font;
  font.FromADKFont(GetPropertyHandle());
  if ( preview = GetFieldContext("preview") )
    preview->SetFont(font);
  return (cNotifyHighContext::Changed());
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

int32 cFont :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cFont();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoBeforeFillData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cFont :: DoBeforeFillData ( )
{
  int8                    executed = NO;
  Changed();
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

logical cFont :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Changed",ALINK(this,cFont,Changed)),
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
    term = cNotifyHighContext::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}


