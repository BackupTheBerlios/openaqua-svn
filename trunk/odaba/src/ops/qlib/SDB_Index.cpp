/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_Index

\brief    Index definition
          The  index definition provides the key name and some index options for
          the  collection  index.  Indexes  can  be defined for local and global
          collections.   The   collection   should   be   a  typed or weak-typed
          collection.  For untypical collections, only  the __IDENTITY index can
          be  defined, which  orders the  collection by local object identifiers
          (LOID).

\date     $Date: 2006/05/11 15:25:18,98 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Index"

#include  <pops7.h>
#include  <cutimac.h>
#include  <sSDB_Extend.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_Index.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  dbs_pi
\param  strname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical SDB_Index :: Check (PI(SDB_Structure) &dbs_pi, char *strname )
{
  SDB_Structure  *dbsptr = NULL;
  logical         term   = NO;
BEGINSEQ
  SDBUERV3(strname,ID_SIZE)
  
  if ( *skdname > ' ' )
  { 
    if ( !(dbsptr = dbs_pi(strname)) )             SDBERR(140)
    SDBUERV3(skdname,ID_SIZE)
    if ( !dbsptr->get_smcepsmc().Get(skdname) )    SDBERR(189)
  }  

RECOVER
  SDBError().DisplayMessage();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize


\param  idxnames
\param  settype
\param  uniopt
\param  sensiopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void SDB_Index :: Initialize (char *idxnames, int16 settype, logical uniopt, logical sensiopt )
{
  if ( idxnames )
    gvtxstb(skdname,idxnames,ID_SIZE);

  skdtype        = (SDB_SET)(settype ? settype : SET_SMAL);
  skdunique      = uniopt;
  case_sensitive = sensiopt;

  skdtemp    = NO;
  no_empty   = NO;
  skdmax     = UNDEF;
}

/******************************************************************************/
/**
\brief  SDB_Index


\param  keynams
\param  settyp
\param  uniopt
\param  tempopt
\param  case_sensopt
\param  empopt
\param  maxcount
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Index"

     SDB_Index :: SDB_Index (char *keynams, SDB_SET settyp, logical uniopt, logical tempopt, logical case_sensopt, logical empopt, int16 maxcount )
                     :   skdtype(settyp),
  skdunique(uniopt),
  skdtemp(tempopt),
  case_sensitive(case_sensopt),
  no_empty(empopt),
  skdmax(maxcount),
  compare()
{
  gvtxstb(skdname,keynams,ID_SIZE);
}


