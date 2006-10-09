/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvll

\brief    


\date     $Date: 2006/03/12 19:19:01,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvll"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <smven.hpp>
#include  <smvld.hpp>
#include  <smvli.hpp>
#include  <smvln.hpp>
#include  <smvlp.hpp>
#include  <smvll.hpp>


/******************************************************************************/
/**
\brief  AddExt - 


\return lindx0 -

\param  ebsnum -
\param  skey -
\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 mvll :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  mven     *mvenptr = (mven *)mvlpenty;

BEGINSEQ
  if ( Refresh() )                                   ERROR
  mvlxbsr(skey);                                     SDBCERR

  if ( mvlxmvlp->AddExt(ebsnum,skey,AUTO) == AUTO )  ERROR

  if ( mvlxicr() )                                   ERROR

  lindx0 = refcuri = mvlxstrt + mvlxmvlp->refcuri;
RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);

}

/******************************************************************************/
/**
\brief  DelExt - 


\return term - Termination code

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelExt"

logical mvll :: DelExt (int32 lindx0 )
{
  logical   term = NO;

BEGINSEQ
  if ( Refresh() )                                        ERROR
  if ( mvlxidl(lindx0) )                                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetIndex - 


\return lindx0 -

\param  skey -
\param  ebsnum -
\param  exact -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 mvll :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{

BEGINSEQ

  if ( Refresh() )                                         ERROR
  if ( mvlxbsr(skey) == AUTO )                             ERROR

  if ( (refcuri = mvlxmvlp->GetIndex(skey,ebsnum,exact)) == AUTO)ERROR
  refcuri += mvlxstrt;

RECOVER
  refcuri = AUTO;
ENDSEQ
  return(refcuri);

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

char *mvll :: GetKey (int32 lindx0, char *keyptr )
{

BEGINSEQ
  if ( !keyptr )                                     SDBERR(99)

  if ( refcuri != lindx0 && lindx0 != AUTO )                      
  {
    if ( Refresh() )                                 ERROR
    if ( !mvlx::GetKey(lindx0,keyptr) )              ERROR
  }
  
  if ( lindx0 != AUTO )
    lindx0-=mvlxstrt;
  if ( !(keyptr = mvlxmvlp->GetKey(lindx0,keyptr)) ) ERROR

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical mvll :: Refresh ( )
{
  logical   term = NO;

BEGINSEQ

  if ( mvlx::Refresh() )                                 ERROR
  mvlrefi = NO;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Repair

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Repair"

logical mvll :: Repair ( )
{
  srt                    *srtptr = mvlxmvlp->mvlsrt;
  char                    keyarea[MAX_KEYLEN];
  char                   *entptr;
  char                   *keyptr;
  logical                 term = NO;
  if ( mvlllev > 1 )
    ((mvll *)mvlxmvlp)->Repair();

  entptr = (char *)srtptr->srtigt(srtptr->srtcnt()); 
  keyptr = srtptr->srtktp() == 'S'   
           ? refsakcb->get_key_def()->GetKey(entptr,keyarea)
           : entptr + srtptr->srtkps()-1;
             
  memcpy(((char *)mvlsrt->srtigt(mvlsrt->srtcnt()))+mvlsrt->srtkps()-1,keyptr,mvlsrt->srtkln()); 
  Modify();
  return(term);
}

/******************************************************************************/
/**
\brief  mvll - 


-------------------------------------------------------------------------------
\brief MVLL_


\param  lobhandle -
\param  extref -
\param  clnumb -
\param  akcbptr -
\param  level -
\param  globind -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvll"

                        mvll :: mvll (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 level, logical globind )
                     : mvlx(lobhandle,extref,clnumb,akcbptr,IDB_MVLL,MVL_IDXL,globind),
 mvlllev(level)

{

BEGINSEQ
  SDBCERR

  if ( !(mvlxmvlp = mvllcrt(lobhandle,mvlpenty,clnumb,akcbptr,
                            --level,globind)) )      ERROR

RECOVER


ENDSEQ

}

/******************************************************************************/
/**
\brief MVLL_T


\param  lobhandle -
\param  extref -
\param  clnumb -
\param  akcbptr -
\param  mvlpptr -
\param  level -
\param  globind -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvll"

                        mvll :: mvll (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, mvlp *mvlpptr, int16 level, logical globind )
                     : mvlx(lobhandle,extref,clnumb,
     akcbptr,IDB_MVLL,MVL_IDXL,globind),
mvlllev(level)

{

BEGINSEQ
  SDBCERR
  
  mvlxmvlp = mvlpptr;

  mvlpptr->set_refrex(mvlpenty);

  mvlxcnt = 0;
  version = mvlpptr->get_version();
  if ( GetTable() )                                    ERROR
  
  stsrsav();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  mvllap - 


\return cond

\param  mvennew -
\param  ebsnum -
\param  skey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvllap"

logical mvll :: mvllap (mven *mvennew, EB_Number ebsnum, char *skey )
{
  mvll     *mvllptr = (mvll *)mvlxmvlp;
  mven     *mvenptr = (mven *)mvlpenty;
  logical   pif  = struct_access->get_pif();
  logical   cond = YES;

BEGINSEQ
  if ( FillIndexEntry(GetCount()-1) )                ERROR 

  if ( mvllptr->Refresh() )                          ERROR

  if ( mvlllev > 1 )
  {
    SDBRESET
    if ( mvllptr->mvllap(mvennew,ebsnum,skey) )   
    {
      refcuri = mvlxcnt;                             LEAVESEQ
    }
    SDBCERR  
  }
  
  if ( !mvlxmvlp->mvlfec() )                             
  {
    if ( mvlxmvlp->ResetTable(mvenptr) )             ERROR
    cond = NO;
  }
  
  if ( mvlllev > 1 )
    mvllptr->mvllead(mvennew);    
  else
    if ( mvlxmvlp->AddExt(ebsnum,skey,AUTO) == AUTO ) ERROR

  refcuri = mvlxcnt;
RECOVER
  refcuri = AUTO;
  cond = NO;
ENDSEQ
  memcpy(mvenptr->mvenkeyg(),skey,mvlsrt->srtkln()); 
  if ( cond )
  {
    memcpy(mvlsrt->srtigt(mvlxindx),mvenptr,mvlsrt->srtlen()); 
    if ( mvlxicr() )                                       ERROR
  }
  else
  {
    mvenptr->mvenicr(pif);
    memcpy(mvennew,mvenptr,mvlsrt->srtlen()); 
    mvlxindx = 0;
    refmod   = YES;
  }

  return(cond);

}

/******************************************************************************/
/**
\brief  mvllcrt - 


\return mvlpptr -

\param  lobhandle -
\param  extref -
\param  clnumb -
\param  akcbptr -
\param  level -
\param  globind -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvllcrt"

mvlp *__cdecl mvll :: mvllcrt (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 level, logical globind, uint16 version_nr )
{
  mvlp    *mvlpptr = NULL;
  logical  uniopt  = akcbptr ? akcbptr->get_unique() : YES;
  logical  cltable = akcbptr ? akcbptr->get_field_def()->get_clst_table() : NO;

BEGINSEQ
  if ( level )
    mvlpptr = new mvll(lobhandle,extref,clnumb,akcbptr,level,globind);
  else
    if ( cltable )
      mvlpptr = new mvld(lobhandle,extref,clnumb,akcbptr,MVL_IDCL,globind);
    else if ( uniopt )
      mvlpptr = new mvli(lobhandle,extref,clnumb,akcbptr,MVL_IDXL,globind);
    else
      mvlpptr = new mvln(lobhandle,extref,clnumb,akcbptr,MVL_IDXL,globind);

  if ( !mvlpptr )                                           SDBERR(95)

  mvlpptr->SetVersion(version_nr);
  mvlpptr->stsrsav();

RECOVER

ENDSEQ
  return(mvlpptr);

}

/******************************************************************************/
/**
\brief  mvllead - 


\return term - Termination code

\param  mvennew -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvllead"

logical mvll :: mvllead (mven *mvennew )
{
  logical   pif  = struct_access->get_pif();
  mvlxindx = mvlsrt->srtkad(mvennew);
  mvlxstrc(0);
  mvlxcnt += mvennew->mvencntg(pif);

  memcpy(mvlpenty,mvennew,mvlsrt->srtlen());
  refcuri = mvlxstrt;
  Modify();
  return(mvlxindx == mvlsrt->srtcnt() ? YES : NO);

}

/******************************************************************************/
/**
\brief  mvllprv - 


\return cond

\param  skey -
\param  mvennew -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvllprv"

logical mvll :: mvllprv (char *skey, mven *mvennew )
{
  mvll     *mvllptr = (mvll *)mvlxmvlp;
  mven     *mvenptr = (mven *)mvlpenty;
  mven     *mvencur;
  int32  leftcount  = 0;
  int32  rightcount = 0;
  mven     *leftmven;
  mven     *rightmven;
  logical   pif  = struct_access->get_pif();
  logical   cond = YES;
  logical   last;

BEGINSEQ
  mvlxbsr(skey);                                     SDBCERR
  mvencur = (mven *)mvlsrt->srtigt(mvlxindx);

  if ( mvllptr->Refresh() )                          ERROR

  if ( mvlllev > 1 )
  {
    SDBRESET
    if ( mvllptr->mvllprv(skey,mvennew) )            LEAVESEQ
    SDBCERR  
    mvenptr->mvencnts(mvllptr->mvlxcnt,pif);
    mvencur->mvencnts(mvllptr->mvlxcnt,pif);
    mvlxcntc();
  }

  if ( !mvlxmvlp->mvlfec() )                             
  {
    if ( mvlllev == 1 && mvlxmvlp->mvlsrt->srtssr(skey) )  LEAVESEQ
    if ( mvlxmvlp->Save() )                                ERROR
    
    if ( rightmven = (mven *)mvlsrt->srtigt(mvlxindx+1) )
      rightcount = mvlxmvlp->mvlfec(*rightmven);
    if ( leftmven = (mven *)mvlsrt->srtigt(mvlxindx-1) )
      leftcount  = mvlxmvlp->mvlfec(*leftmven);

    if ( MAX(leftcount,rightcount) >= 2 )
    {
      if ( leftcount > rightcount )
        switch ( mvlxmvlp->mvlshft(leftmven,mvencur,skey) )  
        {
          case -1 : memcpy(mvenptr,leftmven,mvlsrt->srtlen()); 
                    mvlxindx--;
                    mvencur = leftmven;
                    break;
          case  1 : memcpy(mvenptr,mvencur,mvlsrt->srtlen()); 
                    break;
          default :                                        ERROR
        }  
      else 
        switch ( mvlxmvlp->mvlshft(mvencur,rightmven,skey) )  
        {
          case  1 : memcpy(mvenptr,rightmven,mvlsrt->srtlen()); 
                    mvlxindx++;
                    mvencur = rightmven;
                    break;
          case -1 : memcpy(mvenptr,mvencur,mvlsrt->srtlen()); 
                    break;
          default :                                        ERROR
        }
    }  
    else
    {
      if ( mvlxmvlp->mvlsplt(mvencur,mvenptr,
                             mvlllev > 1 ? mvennew->mvenkeyg() : skey) )
                                                           ERROR  
      mvlxindx = 0;
      mvlxcntc();
      cond = NO;
    }  
    refmod = YES;
    if ( mvlllev > 1 )
      ((mvlx *)mvlxmvlp)->mvlxcntc();
    else if ( mvlxmvlp->get_refsotyp() == IDB_MVLN )  // muß für alle mehrstufigen Indextypen beachtet werden -> virtuell !
      ((mvln *)mvlxmvlp)->reset_mvlxindx();
  }

  if ( mvlllev > 1 )
  {
    last = mvllptr->mvllead(mvennew);
    if ( cond )
    {
      mvencur->mvencnts(mvllptr->mvlxcnt,pif);
      mvenptr->mvencnts(mvllptr->mvlxcnt,pif);
      mvlxcntc();
      if ( last )
      {
        memcpy(mvenptr->mvenkeyg(),mvennew->mvenkeyg(),mvlsrt->srtkln());
        memcpy(mvencur->mvenkeyg(),mvennew->mvenkeyg(),mvlsrt->srtkln());
      }
    }
    else
    {
      mvenptr->mvencnts(mvllptr->mvlxcnt,pif);
      if ( last )
        memcpy(mvenptr->mvenkeyg(),mvennew->mvenkeyg(),mvlsrt->srtkln());
    }
  }  

  if ( !cond )
    memcpy(mvennew,mvenptr,mvlsrt->srtlen());
RECOVER
  cond = NO;
ENDSEQ
  refcuri = AUTO;
  mvlxindx = 0;
  return(cond);

}

/******************************************************************************/
/**
\brief  ~mvll - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvll"

                        mvll :: ~mvll ( )
{



}


