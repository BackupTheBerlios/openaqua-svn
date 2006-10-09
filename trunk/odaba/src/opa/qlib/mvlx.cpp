/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvlx

\brief    


\date     $Date: 2006/03/12 19:19:03,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvlx"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <smven.hpp>
#include  <smvlp.hpp>
#include  <smvlx.hpp>


/******************************************************************************/
/**
\brief  CheckIndex

\return term - Termination code

\param  nresult -
\param  repair
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckIndex"

logical mvlx :: CheckIndex (NString &nresult, logical repair )
{
  int32                   indx = 0;
  mven                   *mvenptr;
  char                   *keyptr;
  char                    keystr[513];
  char                    keyarea[513];
  char                    stringo[513];
  char                    stringn[513];
  int16                   klen = mvlsrt->srtkln();
  int32                   count;
  NString                 nstring;
  logical                 pif = struct_access->get_pif();
  logical                 term = NO;
BEGINSEQ
  if ( mvlp::CheckIndex(nresult,repair) )            ERROR 
    
  Refresh();
  while (mvenptr = (mven *)mvlsrt->srtigt(++indx) ) 
  {
    memcpy(mvlpenty,mvenptr,mvlsrt->srtlen());
    if ( mvlxmvlp->CheckIndex(nresult,repair) )
      term = YES;
    
    refsakcb->get_key_def()->scbsmcb->ConvertToString(mvenptr->mvenkeyg(),keystr,255);
    if ( (count = mvlxmvlp->GetCount()) != mvenptr->mvencntg(pif) )
    {
      gvtxltoa(mvenptr->mvencntg(pif),stringo,10);
      gvtxltoa(count,stringn,10);
      if ( count > 0 )
      {
        nresult += "\n        Invalid count for index entry '";
        nresult += keystr;
        nresult += '(';
        nresult += stringo;
        nresult += ")'";
        if ( repair )
        {
          mvenptr->mvencnts(count,pif);
          nresult += " - count replaced by";
          nresult += ' ';
          nresult += stringn;
        }
        else
          nresult += " - not repaired";
      }
      else
      {
        nresult += "\n         Entry count for index entry '";
        nresult += keystr;
        nresult += "' is 0";
        if ( repair )
        {
          mvlsrt->srtidl(indx--);
          nresult += " - Index entry deleted.";
        }
        else
          nresult += " - not repaired";
      }
      if ( repair )
        refmod = YES;
      term = YES;
    }
    if ( keyptr = mvlxmvlp->mvllast(keyarea) )
      if ( count > 0 && memcmp(keyptr,mvenptr->mvenkeyg(),klen) )
      {
        refsakcb->get_key_def()->scbsmcb->ConvertToString(keyarea,stringn,255);
        nresult += "\n         Invalid key '";
        nresult += keystr;
        nresult += "' for index entry";
        if ( repair )
        {
          memcpy(mvenptr->mvenkeyg(),keyarea,klen);
          refmod = YES;
          nresult += " - key replaced by '";
          nresult += stringn;
          nresult += '\'';
        }
        else
          nresult += " - not repaired";
      }
    if ( refmod )
      Save();
  }
  mvlxcntc();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillIndexEntry - 


\return term - Termination code

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillIndexEntry"

logical mvlx :: FillIndexEntry (int32 lindx0 )
{
  mven     *mvenptr = (mven *)mvlpenty;
  logical   pif     = struct_access->get_pif();
  logical   term    = NO;
  int16 indx    = mvlxindx;

BEGINSEQ
  if ( lindx0 < 0 )                                     ERROR
  if ( refcuri == lindx0 )                              LEAVESEQ

  if ( refcuri == AUTO || 
       !(lindx0  >= mvlxstrt && lindx0 < mvlxstrt + mvenptr->mvencntg(pif)) )
  {
    for ( mvlxstrt = 0, indx = 0;
	  (mvenptr = (mven *)mvlsrt->srtigt(++indx)) &&
          (lindx0  < mvlxstrt || lindx0 >= (mvlxstrt + mvenptr->mvencntg(pif)));
          mvlxstrt+= mvenptr->mvencntg(pif)        ) ;

    if ( !mvenptr )                                  ERROR

    if ( *mvlpenty != *(EB_Number *)mvenptr || !mvlxindx )
    {
      if ( mvlxindx )
        if ( Save() )                                ERROR
      
      memcpy(mvlpenty,mvenptr,mvlsrt->srtlen());
      if ( mvlxmvlp->GetCount() != mvenptr->mvencntg(pif) )
                                                     SDBIERR(-931)
    }
    mvlxindx = indx;
  }
  refcuri = lindx0;

RECOVER
  mvlxindx = 0;
  refcuri = AUTO;
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetCount - 


\return inst_count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 mvlx :: GetCount ( )
{

BEGINSEQ
  if ( Refresh() )                                        ERROR
  if ( !mvlsrt->stscold() )
    mvlxcntc();

RECOVER
  mvlxcnt = AUTO;
ENDSEQ
  return(mvlxcnt);

}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum -

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number mvlx :: GetID (int32 lindx0 )
{
  EB_Number  ebsnum;

BEGINSEQ
  if ( refcuri != lindx0 && lindx0 != AUTO )                      
  {
    if ( Refresh() )                                     ERROR
    if ( FillIndexEntry(lindx0) )                        ERROR
  }  

  if ( lindx0 != AUTO )
    lindx0-=mvlxstrt;

  if ( (ebsnum = mvlxmvlp->GetID(lindx0)).IsEmpty() )   ERROR

RECOVER

ENDSEQ
  return(ebsnum);

}

/******************************************************************************/
/**
\brief  GetKey - 


\return skey -

\param  lindx0 -
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *mvlx :: GetKey (int32 lindx0, char *keyptr )
{
  mven     *mvenptr = (mven *)mvlpenty;

BEGINSEQ
  if ( !keyptr )                                     SDBERR(99)

  if ( lindx0 == AUTO )
  {
    if ( refcuri == AUTO )                           ERROR
  }
  else   
  {
    if ( Refresh() )                                 ERROR
    if ( FillIndexEntry(lindx0) )                    ERROR
  }
  
  memcpy(keyptr,mvenptr->mvenkeyg(),mvlsrt->srtkln());

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  GetTable - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTable"

logical mvlx :: GetTable ( )
{
  mven     *mvenptr = (mven *)mvlpenty;
  logical   term = NO;

BEGINSEQ
  if ( mvl::GetTable() )                                   ERROR 

  mvlxcntc();
  if ( mvlrefi )
    mvlxmvlp->mvlrefis();
  else
    mvlxmvlp->mvlrefir();

  mvenptr->mvenini(mvlsrt->srtkln());
  mvlxindx = 0;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ReadIndexEntry - 


\return term - Termination code

\param  lindx0 -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadIndexEntry"

logical mvlx :: ReadIndexEntry (int32 lindx0, void *instptr )
{
  logical     term = NO;
BEGINSEQ
  if ( lindx0 == AUTO )                              ERROR
    
  if ( refcuri != lindx0 )                      
  {
    if ( Refresh() )                                 ERROR
    if ( FillIndexEntry(lindx0) )                    ERROR
  }
  
  lindx0-=mvlxstrt;
  
  if ( mvlxmvlp->ReadIndexEntry(lindx0,instptr) )    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical mvlx :: Refresh ( )
{
  logical   term = NO;

BEGINSEQ
  if ( mvlrefi )
    mvlxmvlp->mvlrefir();

  if ( mvl::Refresh() )                                ERROR

  if ( !stscsav() )
    mvlrefir();
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  RepairMVL

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RepairMVL"

logical mvlx :: RepairMVL ( )
{
  int32                   indx = 0;
  mven                   *mvenptr;
  char                    keystr[513];
  char                    keyarea[513];
  char                    stringo[513];
  char                    stringn[513];
  int16                   klen = mvlsrt->srtkln();
  int32                   count;
  logical                 pif = struct_access->get_pif();
  logical                 term = NO;
  Refresh();
  while (mvenptr = (mven *)mvlsrt->srtigt(++indx) ) 
  {
    memcpy(mvlpenty,mvenptr,mvlsrt->srtlen());
    mvlxmvlp->RepairMVL();
    
    refsakcb->get_key_def()->scbsmcb->ConvertToString(mvenptr->mvenkeyg(),keystr,255);
    if ( (count = mvlxmvlp->GetCount()) != mvenptr->mvencntg(pif) )
    {
      gvtxltoa(mvenptr->mvencntg(pif),stringo,10);
      gvtxltoa(count,stringn,10);
      if ( count > 0 )
      {
        SDBError().DisplayMessage(369,keystr,stringo,stringn);
        mvenptr->mvencnts(count,pif);
      }
      else
      {
        SDBError().DisplayMessage(371,keystr);
        mvlsrt->srtidl(indx--);
      }
      refmod = YES;
    }
    if ( count > 0 && memcmp(mvlxmvlp->mvllast(keyarea),mvenptr->mvenkeyg(),klen) )
    {
      refsakcb->get_key_def()->scbsmcb->ConvertToString(keyarea,stringn,255);
      SDBError().DisplayMessage(370,keystr,stringn);
      
      memcpy(mvenptr->mvenkeyg(),keyarea,klen);
      refmod = YES;
    }
    if ( refmod )
      Save();
  }
  mvlxcntc();

  

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical mvlx :: Reset ( )
{

  mvlxmvlp->Reset();
  mvl::Reset();
  mvlxindx = 0;
  mvlxstrt = 0;
  mvlxcnt  = 0;


  return(NO);

}

/******************************************************************************/
/**
\brief  ResetTable - 


\return term - Termination code

\param  mvenptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetTable"

logical mvlx :: ResetTable (mven *mvenptr )
{
  logical   term  = NO;

BEGINSEQ

  if ( mvl::ResetTable(mvenptr) )                          ERROR
  mvlxcnt  = 0;
  mvlxindx = 0;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical mvlx :: Save ( )
{
  logical        term = NO;

BEGINSEQ
  if ( mvlxmvlp->Save() )                            ERROR
  if ( mvlxmvlp->stscmod() )
  {
    refmod = YES;
    mvlxmvlp->stsrmod();
  }  
  if ( !refmod )                                     LEAVESEQ
  term = NO;

  if ( mvlxindx )
    memcpy(mvlsrt->srtigt(mvlxindx),mvlpenty,mvlsrt->srtlen());

  if ( mvl::Save() )                                 ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetVersion - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void mvlx :: SetVersion (uint16 version_nr )
{

  if ( mvlxmvlp )
    mvlxmvlp->SetVersion(version_nr);
  mvl::SetVersion(version_nr);


}

/******************************************************************************/
/**
\brief  Setup - 


\return term - Termination code

\param  extref -
\param  clnumb -
\param  w_mbnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical mvlx :: Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber )
{

  ref::Setup(extref,clnumb,w_mbnumber);
  return(mvlxmvlp->Setup(mvlpenty,clnumb,w_mbnumber));

}

/******************************************************************************/
/**
\brief  WriteIndexEntry - 


\return term - Termination code

\param  lindx0 -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteIndexEntry"

logical mvlx :: WriteIndexEntry (int32 lindx0, void *instptr )
{
  logical     term = NO;
BEGINSEQ
  if ( lindx0 == AUTO )                              ERROR
    
  if ( refcuri != lindx0 )                      
  {
    if ( Refresh() )                                 ERROR
    if ( FillIndexEntry(lindx0) )                    ERROR
  }
  
  lindx0-=mvlxstrt;
  
  if ( mvlxmvlp->WriteIndexEntry(lindx0,instptr) )   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  mvlx - 



\param  lobhandle -
\param  extref -
\param  clnumb -
\param  akcbptr -
\param  otyp -
\param  maxl -
\param  globind -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlx"

                        mvlx :: mvlx (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, char otyp, int16 maxl, logical globind )
                     : mvlp(lobhandle,extref,clnumb,otyp,MVLX_OLN,maxl,akcbptr,globind),
 mvlxcnt(AUTO), mvlxmvlp(NULL), mvlxstrt(AUTO), 
 mvlxindx(0)

{



}

/******************************************************************************/
/**
\brief  mvlxbsr - 


\return lindx0 -

\param  skey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlxbsr"

int32 mvlx :: mvlxbsr (char *skey )
{
  int32  lindx0   = 0;
  logical   pif      = struct_access->get_pif();
  logical   notfound = NO;
  int       indx;

BEGINSEQ
  if ( !(indx = mvlsrt->srtbsr(skey)) )                 ERROR
  notfound = mvlsrt->stscerr();

  while ( --indx )
    lindx0 += ((mven *)mvlsrt->srtigt(indx))->mvencntg(pif);

  if ( FillIndexEntry(lindx0) )                         ERROR

RECOVER
  lindx0  = AUTO;
ENDSEQ
  if ( notfound )
    mvlsrt->stsserr();
  return(lindx0);  

}

/******************************************************************************/
/**
\brief  mvlxcntc - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlxcntc"

int32 mvlx :: mvlxcntc ( )
{
  mven              *mvenptr;
  logical            pif  = struct_access->get_pif();
  int32               indx = 0;
  mvlxcnt = 0;

  while ( mvenptr = (mven *)mvlsrt->srtigt(++indx) )
    mvlxcnt += mvenptr->mvencntg(pif);

  return(mvlxcnt);

}

/******************************************************************************/
/**
\brief  mvlxdcr - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlxdcr"

logical mvlx :: mvlxdcr ( )
{
  mven     *mvenptr = (mven *)mvlpenty; 
  logical   pif  = struct_access->get_pif();
  logical   term = NO;

BEGINSEQ
  mvlxcnt--;

  if ( mvenptr->mvendcr(pif) )
  {
    ((mven *)mvlsrt->srtigt(mvlxindx))->mvendcr(pif);
    if ( !refmod )
    {
      if ( pif && IsPD() )
      {
        refmod = YES;
        if ( Save() )                                  ERROR
      }
      else
      {
        if ( struct_access->WriteEXD(exd_area,4L,mb_number,AUTO,(int32)mvlsrt->srtlen()*(mvlxindx-1)+MVEN-4).IsEmpty() )
                                                     ERROR
        mod_count = exd_area->get_mod_count();
      }
    }
  }
  else
  {
    mvlxmvlp->DeleteReference();
    mvlsrt->srtidl(mvlxindx);
    mvlxindx = 0;
    refcuri = AUTO;
    Modify();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  mvlxicr - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlxicr"

logical mvlx :: mvlxicr ( )
{
  mven     *mvenptr = (mven *)mvlpenty; 
  logical   pif  = struct_access->get_pif();
  logical   to_pif;
  logical   term = NO;

BEGINSEQ
  mvlxcnt++;

  mvenptr->mvenicr(pif);
  ((mven *)mvlsrt->srtigt(mvlxindx))->mvenicr(pif);

  if ( !refmod )
  {
    if ( pif && IsPD() )
    {
      refmod = YES;
      if ( Save() )                                  ERROR
    }
    else
    {
      if ( struct_access->WriteEXD(exd_area,mvlsrt->srtlen(),mb_number,AUTO,(int32)mvlsrt->srtlen()*(mvlxindx-1)).IsEmpty() )
                                                     ERROR
      mod_count = exd_area->get_mod_count();
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  mvlxidl - 


\return term - Termination code

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlxidl"

logical mvlx :: mvlxidl (int32 lindx0 )
{
  mven     *mvenptr = (mven *)mvlpenty;
  srt      *srtptr;
  char     *entptr;
  char     *keyptr;
  char      keyarea[MAX_KEYLEN];
  logical   pif  = struct_access->get_pif();
  logical   keyupd;
  logical   to_pif;
  logical   term = NO;

BEGINSEQ
  if ( lindx0 < 0 || lindx0 >= GetCount() )          SDBERR(99)
  if ( FillIndexEntry(lindx0) )                      ERROR

  keyupd = lindx0-mvlxstrt+1 == mvlxmvlp->GetCount() ? YES : NO;
  if ( mvlxmvlp->DelExt(lindx0-mvlxstrt) )           ERROR

  if ( mvlxdcr() )                                   ERROR
  
  if ( mvlxindx && keyupd && (srtptr = mvlxmvlp->mvlsrt)->srtkln() )
  {
    entptr = (char *)srtptr->srtigt(srtptr->srtcnt()); 
    keyptr = srtptr->srtktp() == 'S'   
             ? refsakcb->get_key_def()->GetKey(entptr,keyarea)
             : entptr + srtptr->srtkps()-1;
             
    memcpy(mvenptr->mvenkeyg(),keyptr,mvlsrt->srtkln()); 
    memcpy(mvlsrt->srtigt(mvlxindx),mvenptr,mvlsrt->srtlen()); 

    if ( !refmod )
    {
      if ( pif && IsPD() )
      {
        refmod = YES;
        if ( Save() )                                  ERROR
      }
      else
      {
        if ( struct_access->WriteEXD(exd_area,mvlsrt->srtkln(),mb_number,AUTO,(int32)mvlsrt->srtlen()*(mvlxindx-1)+MVEN).IsEmpty() )
                                                     ERROR
        mod_count = exd_area->get_mod_count();
      }
    }
  }
RECOVER
  term = YES;
ENDSEQ
  refcuri = AUTO;
  return(term);

}

/******************************************************************************/
/**
\brief  mvlxstrc - 


\return count -

\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlxstrc"

int32 mvlx :: mvlxstrc (int16 indx )
{
  mven              *mvenptr;
  logical            pif = struct_access->get_pif();

  if ( !indx ) 
    indx = mvlxindx;
    
  mvlxstrt = 0;

  while ( mvenptr = (mven *)mvlsrt->srtigt(--indx) )
    mvlxstrt += mvenptr->mvencntg(pif);


  return(mvlxstrt);

}

/******************************************************************************/
/**
\brief  ~mvlx - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvlx"

                        mvlx :: ~mvlx ( )
{

  mvlx::Reset();
  delete mvlxmvlp;


}


