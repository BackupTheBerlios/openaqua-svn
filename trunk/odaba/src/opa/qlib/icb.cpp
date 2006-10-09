/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    icb

\brief    


\date     $Date: 2006/03/29 19:17:30,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "icb"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <iNetConversion.h>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <sicbe.hpp>
#include  <smven.hpp>
#include  <smvll.hpp>
#include  <smvlp.hpp>
#include  <sicb.hpp>


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

int32 icb :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  mvll     *mvllptr = NULL;
  int16     sbnumber;
  char     *lastkey = NULL;
  int       cmpval  = YES;
  logical   neu     = NO;
  logical   add     = YES;
  logical   app     = NO;
  logical   extlock = stsclck();
  logical   pif     = struct_access->get_pif();
BEGINSEQ
  if ( Lock() )                                      ERROR
  
  if ( refglob )   // im Metzmode muß der ICBE in die Transaktion
    refmod = YES;  // sonst ist die Sperrung nicht gesichert!
    
  if ( (lindx0 = GetIndex(skey,ebsnum)) != AUTO ) 
  {
    if ( refsakcb->get_unique() )
    {
      SetKeyErrorVariables(skey);
      SDBERR(64)
    }
    LEAVESEQ
  }
  
  mvllptr  = (mvll *)icbmvlp;
  sbnumber = struct_access->get_struct_def()->get_sb_number();

  if ( !(lastkey = mvllptr->mvllast(NULL)) ||
       ( cmpval = refsakcb->get_key_def()->kcbkcp(skey,lastkey)) > 0 )
    app = YES;

  if ( index_lev > 1 && cmpval )
  {
    SDBRESET
    if ( app )
    {
      neu = !mvllptr->mvllap(icbmven,ebsnum,skey); 
      add = NO;
    }
    else
      neu = !mvllptr->mvllprv(skey,icbmven);     
    SDBCERR

    if ( !add && !neu )   
    {
      lindx0 = refcuri = icbmvlp->refcuri;                LEAVESEQ
    }  
  }
    
  if ( neu || index_lev == 1 )
  {
    if ( !icbmvlp->mvlfec() )
    {
      if ( Save() )                                             ERROR
      icbfst->mvencnts(icbmvlp->GetCount(),pif);
      *(EB_Number *)icbfst = *icbicbe;
      icbmvlp->mvllast(icbfst->mvenkeyg());
      icbmvlp->mvlsplt(icbfst,icbsec,neu ? icbmven->mvenkeyg() : skey);

      if ( index_lev > 1 )
      {
        mvllptr->mvlxcntc();
        if ( mvllptr->mvllead(icbmven) )        // last entry
          memcpy(icbsec->mvenkeyg(),icbmven->mvenkeyg(),refsakcb->get_key_def()->kcbklng()); 
        icbsec->mvencnts(icbsec->mvencntg(pif)+icbmven->mvencntg(pif),pif);
        if ( app )
          memcpy(icbsec->mvenkeyg(),skey,refsakcb->get_key_def()->kcbklng()); 
        neu = NO;
      }  
      
      if ( (*(EB_Number *)icbicbe = struct_access->CreateEBI(mb_number,cluster_number,sbnumber,GetVersion())).IsEmpty() )
                                                     ERROR
      refmod = YES;

      if ( !(mvllptr = new mvll(ob_handle,icbicbe,
                                cluster_number,refsakcb,icbmvlp,
                                index_lev,refglob)) )
                                		     SDBERR(95)
                                                     SDBCERR
      icbicbe->icbelevi();
      index_lev = icbicbe->get_icbelev();
      mvllptr->mvllead(icbfst);
      mvllptr->mvllead(icbsec);
      icbmvlp = mvllptr;
      if ( add )
        mvllptr->mvlxbsr(skey);
      else
        GetIndex(skey,UNDEF,YES);
    }  
  }      

  if ( neu )
    mvllptr->mvllead(icbmven);

  if ( add )
    if ( index_lev > 1 && app )
      mvllptr->mvllap(icbmven,ebsnum,skey);          
    else
      icbmvlp->AddExt(ebsnum,skey,lindx0);
  
  if ( (lindx0 = refcuri = icbmvlp->refcuri) == AUTO ) ERROR

RECOVER
  lindx0  = AUTO;
  if ( SDBERROR == 64 )
  {
    char    string[129];
    
    strcpy(string,"SID : ");
    gvtxitoa(refsid,&string[strlen(string)],10);
    strcat(string,"; KEY : ");
    memset(&string[strlen(string)],0,33);
    memcpy(&string[strlen(string)],skey ? skey : "NO KEY",32);
    SDBError().TraceMessage(string);
  }

ENDSEQ
  if ( Unlock(extlock) )
    lindx0 = AUTO;
  return(lindx0);

}

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

logical icb :: CheckIndex (NString &nresult, logical repair )
{
  logical                 term = NO;
BEGINSEQ
  if ( refs::CheckIndex(nresult,repair) )            ERROR 
  term = icbmvlp->CheckIndex(nresult,repair);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckVersion6

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckVersion6"

logical icb :: CheckVersion6 ( )
{
  int32                  *ebnum;
  int16                   levels;
  logical                 pif;
  logical                 term = NO;
  if ( ob_handle->GetDBVersion() < 6 && !exd_area->stscini() )
  {
    pif = exd_area->IsPIF();
    ebnum = (int32 *)exd_area->GetInstance();
    levels = *(int16 *)(ebnum+1);
    *(uint64 *)ebnum = BigToPIF(PIFToLong(*ebnum,pif),pif);
    *(int16 *)(ebnum+2) = levels;
    exd_area->SetLength(sizeof(icbe));
    exd_area->stssetini();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical icb :: CheckWProtect ( )
{
  logical   term = NO;
BEGINSEQ
  ILock();
  if ( ref::CheckWProtect() )                        ERROR
    
  if ( !icbmvlp->get_exd_area() )
    if ( icbrefr() )                                 ERROR
  
  if ( icbmvlp->CheckWProtect() )                    ERROR

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
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

logical icb :: DelExt (int32 lindx0 )
{
  logical   term = NO;
  logical   extlock = stsclck();

BEGINSEQ
  if ( Lock() )                                      ERROR

  if ( refglob )   // im Metzmode muß der ICBE in die Transaktion
    refmod = YES;  // sonst ist die Sperrung nicht gesichert!

  if ( lindx0 >= GetCount() )                        ERROR

  if ( icbmvlp->DelExt(lindx0) )
    term = YES;

  if ( !GetCount() )
  {
    icbmvlp->DeleteReference();
    icbicbe->icbeini();
    refmod  = YES;
    if ( Save() || icbres() )                         ERROR 
  }
RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = AUTO;
  refcuri = AUTO;
  return(term);

}

/******************************************************************************/
/**
\brief  GetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 icb :: GetCount ( )
{
  int32  count = AUTO;
  int       error;

BEGINSEQ
  ILock();
  if ( Refresh() )                                   ERROR
  if ( (count = icbmvlp->GetCount()) == AUTO )
  {
    if ( SDBERROR != -931 )                          ERROR
    if ( stsclck() || !refglob )                     SDBERR(931)
    SDBRESET
    if ( Lock() )                                    ERROR
    count = icbmvlp->GetCount();
    error = SDBERROR;
    Unlock(NO);
    if ( count == AUTO )
    {
      if ( error == -931 )                           SDBERR(931)
                                                     ERROR
    }
  }

RECOVER

ENDSEQ
  IUnlock();
  return(count);

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

EB_Number icb :: GetID (int32 lindx0 )
{
  EB_Number  ebsnum;
  int        error;

BEGINSEQ
  ILock();
  if ( !exd_area || (refcuri != lindx0 && lindx0 != AUTO) )                      
    if ( Refresh() )                                 ERROR

  if ( (ebsnum = icbmvlp->GetID(lindx0)).IsEmpty() )  
  {
    if ( SDBERROR != -931 )                          ERROR
    if ( stsclck() || !refglob )                     SDBERR(931)
    SDBRESET
    if ( Lock() )                                    ERROR
    ebsnum = icbmvlp->GetID(lindx0); 
    error = SDBERROR;
    Unlock(NO);
    if ( ebsnum.IsEmpty() )
    {
      if ( error == -931 )                           SDBERR(931)
                                                     ERROR
    }
  }

  if ( lindx0 != AUTO )
  {
    refcuri = lindx0;
    if ( refsakcb->get_field_def()->get_clst_table() )
      ebsnum = refcuri+1;  // solange, bis wir eine bessere Idee haben
  }

RECOVER
  refcuri = AUTO;
ENDSEQ
  IUnlock();
  return(ebsnum);

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

int32 icb :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  int32      cur_indx;
  int       error;
BEGINSEQ
  ILock();
  if ( Refresh() )                                   ERROR
  if ( (cur_indx = refcuri = icbmvlp->GetIndex(skey,ebsnum,exact)) == AUTO) 
  {
    if ( SDBERROR != -931 )                          ERROR
    if ( stsclck() || !refglob )                     SDBERR(931)
    SDBRESET
    if ( Lock() )                                    ERROR
    refcuri = icbmvlp->GetIndex(skey,ebsnum,exact); 
    error = SDBERROR;
    Unlock(NO);
    if ( refcuri == AUTO )
    {
      if ( error == -931 )                           SDBERR(931)
                                                     ERROR
    }
  }

RECOVER
  cur_indx = refcuri = AUTO;
ENDSEQ
  IUnlock();
  return(cur_indx);

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

char *icb :: GetKey (int32 lindx0, char *keyptr )
{
  int       error;
BEGINSEQ
  ILock();
  if ( lindx0 == AUTO && refcuri == AUTO )           ERROR
  if ( !keyptr )                                     SDBERR(99)

  if ( !exd_area || refcuri != lindx0  )                      
    if ( Refresh() )                                 ERROR

  if ( !(keyptr = icbmvlp->GetKey(lindx0,keyptr)) )  
  {
    if ( SDBERROR != -931 )                          ERROR
    if ( stsclck() || !refglob )                     SDBERR(931)
    SDBRESET
    if ( Lock() )                                    ERROR
    keyptr = icbmvlp->GetKey(lindx0,keyptr);
    error = SDBERROR;
    Unlock(NO);
    if ( !keyptr )
    {
      if ( error == -931 )                           SDBSET(931)
                                                     SDBRESET
                                                     ERROR
    }
  }

RECOVER
  keyptr = NULL;
ENDSEQ
  IUnlock();
  return(keyptr);

}

/******************************************************************************/
/**
\brief  GetModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 icb :: GetModCount ( )
{

  if ( !exd_area )
    Refresh();
  return( icbmvlp ? icbmvlp->GetModCount() : UNDEF);
}

/******************************************************************************/
/**
\brief  ILock

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical icb :: ILock ( )
{

  return(res_lock.ILock());

}

/******************************************************************************/
/**
\brief  IUnlock

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical icb :: IUnlock ( )
{

  return(res_lock.IUnlock());

}

/******************************************************************************/
/**
\brief  InitICB - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitICB"

logical icb :: InitICB ( )
{
  logical                 term = NO;
BEGINSEQ
  ILock();
  if ( !(exd_area = struct_access->ProvideEXD(refrex ? *refrex : EB_Number(0),
                       cluster_number,sizeof(icbe),IDB_ICBE,!refglob,
                       HasWorkspace(),GetVersion())) )
                                                     ERROR
  icbicbe = (icbe *)exd_area->GetInstance();
  ReserveReference();
//  if ( struct_access->get_pif() )
//    exd_area->SetPIF();
  
  if ( !icbicbe->get_icbelev() )
    icbicbe->icbeini();
  if ( ReadICBE() )                                  ERROR
  mod_count = exd_area->get_mod_count();
  icbicbe = (icbe *)exd_area->GetInstance();  // wir haben einige icbe's, die mit länge 8 gespeichert sind. Da kann es zu Bereichsverschiebungen kommen
  if ( !icbicbe->get_icbelev() )
    icbicbe->icbelevr();
  if ( exd_area->GetIEH()->get_iehtyp() != IDB_ICBE )
                                                     SDBERR(174)
  exd_area->SetLength(sizeof(icbe));
  
  if ( icbini() )                                    ERROR

RECOVER
  Reset();
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideEXD - 


\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEXD"

exd *icb :: ProvideEXD ( )
{

BEGINSEQ
  if( !exd_area && InitICB() )                       ERROR

RECOVER

ENDSEQ
  return(exd_area);
}

/******************************************************************************/
/**
\brief  ReadICBE

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadICBE"

logical icb :: ReadICBE ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( exd_area->Read(sizeof(icbe)) )                 ERROR
  CheckVersion6();
  if ( exd_area->IsPIF() )
  {
    icbicbe->FromPIF(YES);
    exd_area->ResetPIF();
if ( icbicbe->get_icbelev() > 100 )
term = NO;
  }
if ( icbicbe->get_icbelev() > 100 )
term = NO;

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

logical icb :: ReadIndexEntry (int32 lindx0, void *instptr )
{
  logical     term = NO;
BEGINSEQ
  if ( refcuri != lindx0 )                                 
    if ( Refresh() )                                 ERROR

  if ( icbmvlp->ReadIndexEntry(lindx0,instptr) )     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Recover - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Recover"

logical icb :: Recover ( )
{
  logical                 term = NO;
BEGINSEQ
// Funktion wird gerufen, wenn Indexhierarchie nicht ordnetlich gelesen werden konnte
// kann beim Rückschreiben von Transaktionen geschehen.

  if ( stsclck() || !refglob )                       ERROR
  if ( Lock() )                                      ERROR

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

logical icb :: Refresh ( )
{
  logical   pif = ob_handle->get_pif();
  logical   term = NO;
BEGINSEQ
  ILock();
  if ( !exd_area )        
  {
    if ( InitICB() )                                 ERROR
    LEAVESEQ
  }
  
  if ( !refrex || (*refrex).IsEmpty(pif) )           LEAVESEQ
    
  if ( !stsclck() )
  {
    if ( icbmvlp->mvlchck() || icbicbe->IsEmpty(pif) )
    {
      if ( !refrex->IsEmpty(pif) && 
           (mod_count != exd_area->get_mod_count() || exd_area->IsModified()) )
      {
        if ( ReadICBE() )                           ERROR
        mod_count = exd_area->get_mod_count();
        icbmvlp->Setup(icbicbe,cluster_number,mb_number);
        if ( index_lev != icbicbe->get_icbelev() || icbicbe->IsEmpty(pif) )
        {
          if ( icbres() )                            ERROR
                                                     LEAVESEQ
        }
      }    
      
      if ( icbrefr() )                               ERROR
    }
  }
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
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

logical icb :: Repair ( )
{
  logical                 term = NO;
BEGINSEQ
  ILock();
  if ( Refresh() )                                   ERROR
    
  term = icbmvlp->RepairMVL() || ref::Repair();
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
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

logical icb :: Reset ( )
{

  ILock();
  
  ReleaseReference();
  
  delete icbmvlp;
  icbmvlp = NULL;

  icbicbe = NULL;
  
  IUnlock();
  return(refs::Reset());


}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical icb :: Save ( )
{
  EB_Number ebsnum;
  logical   pif = ob_handle->get_pif();
  logical   term = NO;

BEGINSEQ
  ILock();
  if ( !icbicbe || !refrex )                         LEAVESEQ
  ebsnum = *icbicbe;
  if ( icbmvlp )
    if ( icbmvlp->Save() )                           ERROR

  if ( !icbmvlp->stscmod() && !refmod )              LEAVESEQ

  if ( refrex->IsEmpty(pif) )    
    stssmod();
    
  if ( (ebsnum = WriteICBE(ebsnum)).IsEmpty() )       ERROR
      
  *refrex = ebsnum;
  mod_count = exd_area->get_mod_count();
  icbmvlp->stsrmod();
  refmod = NO;

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  WriteICBE

\return entnr - 

\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteICBE"

EB_Number icb :: WriteICBE (EB_Number ebsnum )
{
  logical   pif = ob_handle->get_pif();
  exd      *exdptr;
  logical   term = NO;
BEGINSEQ
if ( icbicbe->get_icbelev() > 100 )
term = NO;
  if ( pif )
  {
    exdptr = exd_area->ProvidePIF();
    ((icbe *)exdptr->GetInstance())->ToPIF(pif);
    exdptr->SetPIF();
  }
  ebsnum = struct_access->WriteEXD(exd_area,sizeof(icbe),mb_number,AUTO,AUTO);
  if ( ebsnum.IsEmpty(pif) )                          ERROR

RECOVER
  ebsnum = 0;
ENDSEQ
  return(ebsnum);
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

logical icb :: WriteIndexEntry (int32 lindx0, void *instptr )
{
  logical     term = NO;
BEGINSEQ
  ILock();
  
  if ( refcuri != lindx0 )                                 
    if ( Refresh() )                                 ERROR
  
  if ( icbmvlp->WriteIndexEntry(lindx0,instptr) )    ERROR
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  icb - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "icb"

                        icb :: icb (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind )
                     : refs(lobhandle,extref,clnumb,IDB_ICBE,
  akcbptr,YES),
  icbicbe(NULL), icbmvlp(NULL), icbmven(NULL),
  icbfst(NULL), icbsec(NULL), index_lev(0),
  res_lock(YES)
{
  kcb      *kcbptr = akcbptr->get_key_def();
  int16 klen = ( kcbptr ? kcbptr->kcbklng() : 0);

BEGINSEQ
  SDBCERR

  if ( !(icbmven = mven::mvencrt(klen)) ||
       !(icbfst  = mven::mvencrt(klen)) ||
       !(icbsec  = mven::mvencrt(klen))   )             ERROR

  if ( refglob && struct_access && struct_access->IsNet() )
    stsssav();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  icbini - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "icbini"

logical icb :: icbini ( )
{
  logical   term = NO;

BEGINSEQ
  if ( !refrex || refrex->IsEmpty(ob_handle->get_pif()) || 
       exd_area->NewEntry() || !icbicbe->get_icbelev() )
    icbicbe->icbeini();

  index_lev = icbicbe->get_icbelev();
  if ( !(icbmvlp = mvll::mvllcrt(ob_handle,
                                 icbicbe,cluster_number,refsakcb,
                                 index_lev-1,refglob,version)) )
                                                      ERROR
  icbmvlp->Setup(icbicbe,cluster_number,mb_number);
  if ( !stscsav() && icbrefr() )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  icbrefr - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "icbrefr"

logical icb :: icbrefr ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !icbicbe->IsEmpty(ob_handle->get_pif()) )
  {
    icbmvlp->mvlrefis();
    if ( icbmvlp->Refresh() )                         ERROR
  }
  icbmvlp->mvlrefir();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  icbres - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "icbres"

logical icb :: icbres ( )
{

  delete icbmvlp;
  icbmvlp = NULL;

  return( icbini() );


}

/******************************************************************************/
/**
\brief  ~icb - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~icb"

                        icb :: ~icb ( )
{

  icb::Reset();
  delete icbmven;
  delete icbfst;
  delete icbsec;

}


