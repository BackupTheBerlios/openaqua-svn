/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    sSDB_Structure



\date     $Date: 2006/05/11 16:13:47,43 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Structure"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sSDB_Structure.hpp>
#include  <scfte.hpp>
#include  <spc_SDB_Structure.hpp>
#include  <ssSDB_Structure.hpp>


/******************************************************************************/
/**
\brief  CheckExtentPath

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtentPath"

logical sSDB_Structure :: CheckExtentPath ( )
{
  PropertyHandle   *ph        = GetPropertyHandle();
  char             *prop_path = Parm(1);
  char             *prop_type = "";
  logical           term      = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)
    
  if ( !(prop_type = ((SDB_Structure *)ph->Get().GetData())->CheckExtentPath(prop_path)) )
    prop_type = "";

RECOVER
  term = YES;
ENDSEQ
  ph->SetActionResult(prop_type);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckPropertyPath

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPropertyPath"

logical sSDB_Structure :: CheckPropertyPath ( )
{
  PropertyHandle   *ph        = GetPropertyHandle();
  char             *prop_path = Parm(1);
  char             *prop_type = "";
  logical           term      = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)
    
  if ( !(prop_type = ((SDB_Structure *)ph->Get().GetData())->CheckPropertyPath(prop_path)) )
    prop_type = "";

RECOVER
  term = YES;
ENDSEQ
  ph->SetActionResult(prop_type);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckStructure

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckStructure"

logical sSDB_Structure :: CheckStructure ( )
{
  PropertyHandle  *ph            = GetPropertyHandle();
  char            *show_warnings = Parm(1);
  ErrorProtocol    protocol(SDBError());
  logical          term          = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)
    
  protocol.SetMessageIndent(4);
  protocol.SetWarningLevel(!show_warnings         ? 0 : 
                            *show_warnings == 'A' ? 2 :
                            *show_warnings == 'Y' ? 1 : 0 );
  pc_SDB_Structure   str_pc(ph);
  str_pc.Check(&protocol);

RECOVER
  term = YES;
ENDSEQ
  ph->SetActionResult(protocol);
  return(term);
}

/******************************************************************************/
/**
\brief  Create

\return rc

\param  strctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_Structure :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_Structure();
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

logical sSDB_Structure :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("CheckExtentPath",ALINK(this,sSDB_Structure,CheckExtentPath)),
                           cfte("CheckPropertyPath",ALINK(this,sSDB_Structure,CheckPropertyPath)),
                           cfte("CheckStructure",ALINK(this,sSDB_Structure,CheckStructure)),
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
\brief  sSDB_Structure


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Structure"

     sSDB_Structure :: sSDB_Structure ( )
                     : CTX_Structure ()
{
}

/******************************************************************************/
/**
\brief  ~sSDB_Structure


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Structure"

     sSDB_Structure :: ~sSDB_Structure ( )
{
}


