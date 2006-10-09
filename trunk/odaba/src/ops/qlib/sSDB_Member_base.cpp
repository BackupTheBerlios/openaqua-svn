/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    sSDB_Member_base



\date     $Date: 2006/05/13 18:03:42,68 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Member_base"

#include  <pops7.h>
#include  <scfte.hpp>
#include  <spc_SDB_Member.hpp>
#include  <ssSDB_Member_base.hpp>


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

logical sSDB_Member_base :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetScopedType",ALINK(this,sSDB_Member_base,GetScopedType)),
                           cfte("SetDefaults",ALINK(this,sSDB_Member_base,SetDefaults)),
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
\brief  GetScopedType

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScopedType"

logical sSDB_Member_base :: GetScopedType ( )
{
  PropertyHandle    *ph   = GetPropertyHandle();
  NString            nstring;
  logical            term = NO;
BEGINSEQ
  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_SDB_Member   mem_pc(ph); 
  SetResult(mem_pc.GetScopedType(nstring));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaults

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaults"

logical sSDB_Member_base :: SetDefaults ( )
{
  PropertyHandle    *prophdl   = GetPropertyHandle();
  char              *typenames = Parm(1);
  logical            term      = NO;
BEGINSEQ
  if ( prophdl->NoWrite() )                          ERROR

  if ( !typenames )
    typenames = "";
    
  SetDefaultsForSpecialType(prophdl->GetDBHandle(),
                            prophdl->GPH("sys_ident")->GetString(),
                            typenames);
  prophdl->Modify();
  prophdl->Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultsForSpecialType

\return term

\param  dbhandle - 
\param  propnames
\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultsForSpecialType"

logical sSDB_Member_base :: SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  sSDB_Member_base


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Member_base"

     sSDB_Member_base :: sSDB_Member_base ( )
                     : CTX_Structure ()
{
}

/******************************************************************************/
/**
\brief  ~sSDB_Member_base


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Member_base"

     sSDB_Member_base :: ~sSDB_Member_base ( )
{
}


