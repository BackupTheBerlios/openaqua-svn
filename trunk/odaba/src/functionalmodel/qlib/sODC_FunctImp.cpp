/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    sODC_FunctImp



\date     $Date: 2006/05/10 20:55:33,57 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODC_FunctImp"

#include  <pfmodel.h>
#include  <cProgramLanguage.h>
#include  <spc_ODC_FunctImp.hpp>
#include  <ssODC_FunctImp.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  CTX_Structure_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODC_FunctImp :: Create (CTX_Structure **CTX_Structure_ptrp )
{
  *CTX_Structure_ptrp = new sODC_FunctImp();
  return(NO);

}

/******************************************************************************/
/**
\brief  DBRead

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sODC_FunctImp :: DBRead ( )
{

  if ( TestSysVariable("ClassDevelopment","YES") )
    FillHeadLine();
  return(NO);
}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return 

\param  fname
\param  chk_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical sODC_FunctImp :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("FillHeadLine",ALINK(this,sODC_FunctImp,FillHeadLine)),
                           cfte("GetParmCallList",ALINK(this,sODC_FunctImp,GetParmCallList)),
                           cfte("SetupCodeBlockOptions",ALINK(this,sODC_FunctImp,SetupCodeBlockOptions)),
                           cfte("SetupCodeBlocks",ALINK(this,sODC_FunctImp,SetupCodeBlocks)),
                           cfte("SetupInitCode",ALINK(this,sODC_FunctImp,SetupInitCode)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = CTX_Structure::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillHeadLine

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillHeadLine"

logical sODC_FunctImp :: FillHeadLine ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
  logical          term = NO;
  pc_ODC_FunctImp    fcti_pc(ph);
  fcti_pc.Headline(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  FillHeadLineParmCallList

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillHeadLineParmCallList"

logical sODC_FunctImp :: FillHeadLineParmCallList ( )
{
  PropertyHandle   *ph            = GetPropertyHandle();
  char             *prototype     = Parm(1);
  NString           nstring;
  logical           term          = NO;
BEGINSEQ
  SetResult("");
  
  if ( !ph->IsPositioned() )                         CTXERR(99)
    
  pc_ODC_FunctImp    fcti_pc(ph);
  SetResult(fcti_pc.GetCParmList(nstring,(prototype && *prototype == 'Y') ? YES : NO,YES));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetParmCallList

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmCallList"

logical sODC_FunctImp :: GetParmCallList ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  NString           nstring;
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsPositioned() )                         CTXERR(99)

  pc_ODC_FunctImp    fcti_pc(ph);
  SetResult(fcti_pc.GetParmCallList(nstring));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCodeBlockOptions

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCodeBlockOptions"

logical sODC_FunctImp :: SetupCodeBlockOptions ( )
{
  PropertyHandle   *ph    = GetPropertyHandle();
  logical           term  = NO;
BEGINSEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)

  pc_ODC_FunctImp    fcti_pc(ph);
  if ( fcti_pc.SetupCodeBlockOptions() )             ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCodeBlocks

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCodeBlocks"

logical sODC_FunctImp :: SetupCodeBlocks ( )
{
  PropertyHandle   *ph       = GetPropertyHandle();
  char             *parm1    = Parm(1);
  char              glob_opt = AUTO;
  logical           term     = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)

  if ( parm1 )
    glob_opt = *parm1 == 'Y' ? YES :
               *parm1 == 'N' ? NO  : AUTO;

  pc_ODC_FunctImp    fcti_pc(ph);
  if ( fcti_pc.SetupCodeBlocks(glob_opt,Parm(2)) )   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupInitCode

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInitCode"

logical sODC_FunctImp :: SetupInitCode ( )
{
  PropertyHandle   *ph        = GetPropertyHandle();
  char             *clear_opt = Parm(1);
  logical           term      = NO;

BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)

  pc_ODC_FunctImp    fcti_pc(ph);
  if ( fcti_pc.SetupInitCode(NULL,clear_opt && *clear_opt == 'Y' ? YES : NO) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sODC_FunctImp


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODC_FunctImp"

     sODC_FunctImp :: sODC_FunctImp ( )
                     : CTX_Structure()
{
}

/******************************************************************************/
/**
\brief  ~sODC_FunctImp


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODC_FunctImp"

     sODC_FunctImp :: ~sODC_FunctImp ( )
{


}


