/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    db_ODE

\brief    


\date     $Date: 2006/04/21 17:41:46,51 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "db_ODE"

#include  <padkctxi.h>
#include  <spc_ODC_Project.hpp>
#include  <sdb_ODE.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  dbctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 db_ODE :: Create (CTX_DataBase **dbctx_ptrp )
{

  *dbctx_ptrp = new db_ODE();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return term - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical db_ODE :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GenerateCompile",ALINK(this,db_ODE,GenerateCompile)),
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
    term = CTX_DataBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateCompile

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCompile"

logical db_ODE :: GenerateCompile ( )
{
  char       *prjnames = Parm(1);
  logical     term     = NO;
BEGINSEQ
  if ( !prjnames )                                   CTXERR(104)

  pc_ODC_Project    prj_pc(GetDBHandle(),PI_Read);   SDBCERR
  PropertyHandle phPrjnames(prjnames);
  if ( !prj_pc.Get(phPrjnames) )       CTXERR(105)
  prj_pc.CreateCompAll(CPS_undefined,NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  db_ODE


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "db_ODE"

                        db_ODE :: db_ODE ( )
                     : CTX_DataBase ()
{



}

/******************************************************************************/
/**
\brief  ~db_ODE - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~db_ODE"

                        db_ODE :: ~db_ODE ( )
{



}


