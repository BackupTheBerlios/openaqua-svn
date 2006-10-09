/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sSDB_CodeSet



\date     $Date: 2006/04/11 19:48:50,39 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_CodeSet"

#include  <pops7.h>
#include  <scfte.hpp>
#include  <ssSDB_CodeSet.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_CodeSet :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_CodeSet();
  return(NO);

}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical sSDB_CodeSet :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("ProvideSDB_ValueList",ALINK(this,sSDB_CodeSet,ProvideSDB_ValueList)),
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
\brief  ProvideSDB_ValueList

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideSDB_ValueList"

logical sSDB_CodeSet :: ProvideSDB_ValueList ( )
{
  PropertyHandle    *ph   = GetPropertyHandle();
  PropertyHandle     v8_ident("");
  logical            term = NO;
BEGINSEQ
  if ( !ph->IsPositioned() )                        ERROR
  
  PropertyHandle   vlist(ph->GetDBHandle(),"SDB_ValueList",PI_Write);
  TypeKey          tkey(GPH("sys_ident")->GetString(),0);

  if ( !vlist.Get(tkey.GetKey()) )
  {
    v8_ident = *GPH("sys_ident") + PropertyHandle("V8");
    TypeKey    v8_tkey(v8_ident.GetString(),0);
    if ( vlist.Get(tkey.GetKey()) )
      if ( vlist.Rename(tkey.GetKey()) )            ERROR
  }

  if ( !vlist.Get(tkey.GetKey()) )
    vlist.Add(tkey.GetKey());                       SDBCERR
    
  *vlist.GPH("typetype")    = 3; // TYP_Codeset
  *vlist.GPH("access_type") = 2; // AT_CODE
  *vlist.GPH("itype")       = *GPH("itype");

  vlist.Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sSDB_CodeSet


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_CodeSet"

                        sSDB_CodeSet :: sSDB_CodeSet ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sSDB_CodeSet


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_CodeSet"

                        sSDB_CodeSet :: ~sSDB_CodeSet ( )
{



}


