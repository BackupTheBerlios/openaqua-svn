/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    mvln

\brief    


\date     $Date: 2006/06/29 20:44:21,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvln"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <smven.hpp>
#include  <smvln.hpp>


/******************************************************************************/
/**
\brief  AddExt - 


\return ebsnum - 

\param  ebsnum - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 mvln :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  mven     *mvenptr = (mven *)mvlpenty;
  logical   extlock = stsclck();
  int32      indx    = mvlxindx;

BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( !exd_area )
    if ( GetTable() )                                ERROR

  if ( GetIndex(skey,ebsnum) != AUTO )
    if ( !ebsnum.IsEmpty() )
    {
      SetKeyErrorVariables(NULL);
      SDBERR(64)
    }

  if ( !(mvlxindx = mvlsrt->srtssr(skey)) )    
  {
    refcuri = AUTO;
    if ( mvlxmvlp->refmod && indx )
    {
      if ( mvlxmvlp->Save() )                        ERROR
      memcpy(mvlsrt->srtigt(indx),mvlpenty,mvlsrt->srtlen());
    }
    
    mvenptr->mvenini(mvlsrt->srtkln());
    memcpy(mvenptr->mvenkeyg(),skey,mvlsrt->srtkln());

    if ( !mvlchk(AUTO) )                             ERROR
    mvlxmvlp->Setup(mvlpenty,cluster_number,mb_number);
    if ( mvlxmvlp->InitialWrite() )                  ERROR
    mvlxindx = mvlsrt->srtkad(mvenptr);    
    Modify();
    
    mvlxstrc(0);

    if ( mvlxmvlp->GetTable() )                      ERROR
  } 

  mvlxmvlp->refcuri = AUTO;
  if ( mvlxmvlp->AddExt(ebsnum,NULL,AUTO) == AUTO)   ERROR
  if ( mvlxicr() )                                   ERROR

  lindx0 = refcuri = mvlxstrt + mvlxmvlp->refcuri;

RECOVER
  mvlxindx = 0;
  lindx0   = AUTO;
ENDSEQ
  if ( Unlock(extlock) )
    lindx0 = AUTO;
  return(lindx0);

}

/******************************************************************************/
/**
\brief  AddID - 


\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical mvln :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{

  return(ref::AddID(intiptr,entnr,lindx0));

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

logical mvln :: DelExt (int32 lindx0 )
{
  logical   extlock = stsclck();
  logical   term = NO;

BEGINSEQ
  if ( Lock() )                                        ERROR
  if ( mvlxidl(lindx0) )                               ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  refcuri = AUTO;
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteID - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical mvln :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return(ref::DeleteID(intiptr,oldinst,entnr));

}

/******************************************************************************/
/**
\brief  i1 - 


\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical mvln :: DeleteID (EB_Number entnr )
{
  logical                 term = NO;

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

logical mvln :: FillIndexEntry (int32 lindx0 )
{
  logical   term = NO;

BEGINSEQ

  if ( refcuri != lindx0 && lindx0 != AUTO )                      
    if ( mvlx::FillIndexEntry(lindx0) )                 ERROR

  if ( lindx0 != AUTO )
    lindx0-=mvlxstrt;
  mvlnebs = mvlxmvlp->GetID(lindx0);

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

int32 mvln :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  int32  lindx0 = 0;
  int32  indx;

BEGINSEQ
  if ( Refresh() )                                          ERROR
  if ( (lindx0 = mvlxbsr(skey)) == AUTO || 
       (exact && mvlsrt->stscerr())       )                 ERROR

  if ( !ebsnum.IsEmpty() )
  {
    if ( (indx = mvlxmvlp->mvlpidxg(ebsnum)) == AUTO )      ERROR 
    lindx0 += indx;
    mvlnebs = ebsnum;
    refcuri = lindx0;
  }

RECOVER
  lindx0 = AUTO;

ENDSEQ
  return(lindx0);  

}

/******************************************************************************/
/**
\brief  UpdateID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical mvln :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return(ref::UpdateID(intiptr,oldinst,entnr));

}

/******************************************************************************/
/**
\brief  mvln - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  maxl - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvln"

     mvln :: mvln (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 maxl, logical globind )
                     : mvlx(lobhandle,extref,clnumb,akcbptr,IDB_MVLN,maxl,globind),
 mvlnebs(0)

{

BEGINSEQ
  if ( !(mvlxmvlp = new mvlp(ob_handle,
                             mvlpenty,cluster_number,IDB_MVLP,MVLP_OLN,
                             AUTO,akcbptr,globind)) )     SDBERR(95)
                                                     
  mvlxmvlp->stsrsav();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~mvln - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvln"

     mvln :: ~mvln ( )
{



}


