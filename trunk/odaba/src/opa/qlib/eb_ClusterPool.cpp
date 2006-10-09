/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    eb_ClusterPool

\brief    


\date     $Date: 2006/03/12 19:18:39,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "eb_ClusterPool"

#include  <popa7.h>
#include  <sCPE.hpp>
#include  <sEBI.hpp>
#include  <sEB_MBHeader.hpp>
#include  <sEB_Number.hpp>
#include  <sacb.hpp>
#include  <seb_MainBase.hpp>
#include  <seb_ClusterPool.hpp>


/******************************************************************************/
/**
\brief  AddClusterEntry - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddClusterEntry"

logical eb_ClusterPool :: AddClusterEntry (acb *acbptr )
{
  CPE        *cpeptr;
  logical     term = NO;
BEGINSEQ
  if ( !(cpeptr = GetCluster(acbptr)) )              SDBERR(49)

  if ( acbptr->get_ebsnum().IsEmpty() )              SDBERR(99)
  
  if ( cpeptr->cpeadd(acbptr) )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical eb_ClusterPool :: Clear ( )
{
  CPE       *cpeptr;
  int16      indx;
  for ( indx=srtcnt(); indx; indx-- )
    if ( (cpeptr = GetEntry(indx))->get_cpeucnt() <= 0 )
    {
      cpeptr->cpewrit();
      cpeptr->cpermv();
      DeleteEntry(indx);
    }

  return(NO);
}

/******************************************************************************/
/**
\brief  DelClusterEntry - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelClusterEntry"

logical eb_ClusterPool :: DelClusterEntry (acb *acbptr )
{
  CPE     *cpeptr;
  logical  term = NO;
BEGINSEQ
  if ( acbptr->get_cluster_number().IsEmpty() )      SDBERR(99)
  
  if ( !(cpeptr = GetCluster(acbptr)) )              SDBERR(49)
  if ( cpeptr->cpedel(acbptr) )                      SDBERR(51)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Flush - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical eb_ClusterPool :: Flush ( )
{
  CPE       *cpeptr;
  int16      indx;
  if ( this )
    for ( indx=srtcnt(); indx; indx-- )
      if ( (cpeptr = GetEntry(indx))->get_cpeucnt() <= 0 )
        cpeptr->cpewrit();

  return(NO);
}

/******************************************************************************/
/**
\brief  FlushCluster - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushCluster"

logical eb_ClusterPool :: FlushCluster (acb *acbptr )
{
  CPE     *cpeptr;
  logical  term = NO;
BEGINSEQ
  if ( !(cpeptr = GetEntry(&acbptr->get_cluster_number())) )
                                                     SDBERR(49)
  cpeptr->cpewrit();
  SDBCERR     

RECOVER
  term = YES;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  GetCluster - 


\return cpeptr -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCluster"

CPE *eb_ClusterPool :: GetCluster (acb *acbptr )
{
  CPE      *cpeptr = NULL;
  int16 indx;

BEGINSEQ
  if ( !(cpeptr = GetEntry(&acbptr->get_cluster_number())) )
  {
    if ( srtcnt() >= 20 )
      Clear();
    CPE     cpeenty(mb_handle,acbptr->get_cluster_number());
                                                      SDBCERR
    if ( !(indx = AddEntry(&cpeenty)) )               SDBERR(95)
    cpeptr = GetEntry(indx); 
    acbptr->set_cluster_numb(cpeptr->get_cpeebsn());
  }

RECOVER
  cpeptr = NULL;
ENDSEQ
  return(cpeptr);
}

/******************************************************************************/
/**
\brief  GetClusterEntry - 


\return length -

\param  acbptr -
\param  entlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClusterEntry"

int32 eb_ClusterPool :: GetClusterEntry (acb *acbptr, int32 entlen )
{
  CPE     *cpeptr;
  int32     length = 0;
BEGINSEQ
  if ( acbptr->get_cluster_number().IsEmpty() )      SDBERR(99)
  
  if ( !(cpeptr = GetCluster(acbptr)) )              ERROR
  length = cpeptr->cpeget(acbptr,entlen);
  

RECOVER

ENDSEQ
  return(length);
}

/******************************************************************************/
/**
\brief  GetEntryLength - 


\return length -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryLength"

int32 eb_ClusterPool :: GetEntryLength (acb *acbptr )
{
  CPE     *cpeptr;
  int32     length = 0;
BEGINSEQ
  if ( acbptr->get_cluster_number().IsEmpty() )   ERROR
  
  if ( !(cpeptr = GetCluster(acbptr)) )           ERROR
  length = cpeptr->cpeleng(acbptr);

RECOVER

ENDSEQ
  return(length);
}

/******************************************************************************/
/**
\brief  PutClusterEntry - 


\return term - Termination code

\param  acbptr -
\param  entlen -
\param  offset -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutClusterEntry"

logical eb_ClusterPool :: PutClusterEntry (acb *acbptr, int32 entlen, int32 offset )
{
  CPE     *cpeptr;
  logical  term = NO;
BEGINSEQ
// clusternummer aus dem EBI ?!
  if ( !(cpeptr = GetCluster(acbptr)) )              SDBERR(49)
  if ( cpeptr->cpeupd(acbptr,entlen,offset) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseCluster - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseCluster"

logical eb_ClusterPool :: ReleaseCluster (acb *acbptr )
{
  CPE          *cpeptr;
  int16     indx;      
  logical       term = NO;

BEGINSEQ
  if ( !(cpeptr = GetEntry(indx = FindEntry(&acbptr->get_cluster_number()))) )
                                                      SDBERR(49)
  if ( cpeptr->get_cpeucnt() > 0 )
    cpeptr->cpeucntd();
  else                                                SDBSET(53)

  if ( srtcnt() >= 20 )
    Clear();

RECOVER
  term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetMainBase - 



\param  mainbase -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMainBase"

void eb_ClusterPool :: SetMainBase (eb_MainBase *mainbase )
{

  mb_handle = mainbase;

}

/******************************************************************************/
/**
\brief  UseCluster - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UseCluster"

logical eb_ClusterPool :: UseCluster (acb *acbptr )
{
  CPE          *cpeptr;
  logical       term = NO;

BEGINSEQ
  if ( acbptr->get_cluster_number().IsEmpty() )      SDBERR(99)
  
  if ( !(cpeptr = GetCluster(acbptr)) )               ERROR
  cpeptr->cpeucnti();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  eb_ClusterPool - 



\param  mbhandle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eb_ClusterPool"

                        eb_ClusterPool :: eb_ClusterPool (eb_MainBase *mbhandle )
                     :   GSRT(CPE)(20,sizeof(CPE),8,offsetof(CPE,cpeebsn)+1,'I',YES),
  mb_handle(mbhandle)
{



}

/******************************************************************************/
/**
\brief  ~eb_ClusterPool - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~eb_ClusterPool"

                        eb_ClusterPool :: ~eb_ClusterPool ( )
{
  CPE     *cpeptr;
    Clear();

    if ( srtcnt() )                                   SDBSET(50)
  
    while ( cpeptr = GetEntry(1) )
    {
      cpeptr->cpewrit();
      cpeptr->cpermv();
      DeleteEntry(1);
    }


}


