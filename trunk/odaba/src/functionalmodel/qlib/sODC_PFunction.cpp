/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/19|19:04:48,89}|(REF)
\class    sODC_PFunction

\brief    


\date     $Date: 2006/03/21 13:59:57,01 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODC_PFunction"

#include  <pfmodel.h>
#include  <sCTX_Structure.hpp>
#include  <spc_ODC_PFunction.hpp>
#include  <ssODC_PFunction.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  CTX_Structure_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODC_PFunction :: Create (CTX_Structure **CTX_Structure_ptrp )
{

  *CTX_Structure_ptrp = new sODC_PFunction();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreate - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical sODC_PFunction :: DBCreate ( )
{
  PropertyHandle   *prophdl = GetPropertyHandle();
  *prophdl->GPH("ddeprv") = "ODC_public";
  return(NO);
}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return term

\param  fname -
\param  chk_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical sODC_PFunction :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetLineCount",ALINK(this,sODC_PFunction,SetLineCount)),
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
\brief  SetLineCount - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineCount"

logical sODC_PFunction :: SetLineCount ( )
{
  PropertyHandle  *ph        = GetPropertyHandle();
  char            *count_str = Parm(1);
  int              count     = 0;
  logical          term      = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( ph->NoWrite() )                               ERROR
    
  if ( count_str )
    count = atoi(count_str);
    
  pc_ODC_PFunction  pfunct_pc(ph);
  term = pfunct_pc.SetLineCount(count);

  ph->Save();                                        SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sODC_PFunction - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODC_PFunction"

                        sODC_PFunction :: sODC_PFunction ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~sODC_PFunction - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODC_PFunction"

                        sODC_PFunction :: ~sODC_PFunction ( )
{



}


