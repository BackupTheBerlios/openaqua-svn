/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    refp



\date     $Date: 2006/05/22 17:04:00,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "refp"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <iNetConversion.h>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <srefx.hpp>
#include  <srefp.hpp>


/******************************************************************************/
/**
\brief  AddExt

\return lindx0 - 

\param  ebsnum - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 refp :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  logical   extlock = stsclck();

BEGINSEQ
  if ( Lock() )                                       ERROR
  if ( !exd_area && !ProvideEXD() )                   ERROR

  if ( (refcuri = refprefx->AddExt(ebsnum,skey,lindx0)) == AUTO )
                                                      ERROR
  if ( refprefx->stscmod() )
  {
    refmod  = YES;
    refprefx->stsrmod();
  }
RECOVER
  refcuri = AUTO;
ENDSEQ
  if ( Unlock(extlock) )
    refcuri = AUTO;
  return(refcuri);

}

/******************************************************************************/
/**
\brief  AddID

\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical refp :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  return ( AddExt(entnr,NULL,lindx0) == AUTO );
}

/******************************************************************************/
/**
\brief  CheckVersion6

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckVersion6"

logical refp :: CheckVersion6 ( )
{
  int32                  *ebnum;
  logical                 pif;
  logical                 term = NO;
  if ( ob_handle->GetDBVersion() < 6 && !exd_area->stscini() )
  {
    pif = exd_area->IsPIF();
    ebnum = (int32 *)exd_area->GetInstance();
    *(uint64 *)ebnum = BigToPIF(PIFToLong(*ebnum,pif),pif);
    exd_area->SetLength(sizeof(EB_Number));
    exd_area->stssetini();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical refp :: CheckWProtect ( )
{

//  return ( ref::CheckWProtect() || refprefx->CheckWProtect() );
  return ( ref::CheckWProtect() );


}

/******************************************************************************/
/**
\brief  DelExt

\return term - Termination code

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelExt"

logical refp :: DelExt (int32 lindx0 )
{
  logical   extlock = stsclck();
  logical   term    = NO;

BEGINSEQ
  if ( Lock() )                                       ERROR
  if ( !exd_area && !ProvideEXD() )                   ERROR

  if ( refprefx->DelExt(lindx0) )                     ERROR
  
  if ( refprefx->stscmod() )
  {
    refmod  = YES;
    refprefx->stsrmod();
  }
RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteID

\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical refp :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  return(DelExt(0));
}

/******************************************************************************/
/**
\brief  GetCount

\return count

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 refp :: GetCount ( )
{
  int32  count = AUTO;

BEGINSEQ
  if ( Refresh() )                                         ERROR
  count = refprefx->GetCount();

RECOVER
ENDSEQ
  return(count);

}

/******************************************************************************/
/**
\brief  GetID

\return ebsnum - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number refp :: GetID (int32 indx0 )
{
  EB_Number     ebsnum;
BEGINSEQ
  if ( Refresh() )                                   ERROR
  if ( indx0 != 0 )                                  ERROR
  ebsnum = refprefx->GetID(indx0);
RECOVER
ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  GetIndex

\return lindx0 - 

\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 refp :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{

BEGINSEQ
  if ( Refresh() )                                          ERROR
  refcuri = refprefx->GetIndex(skey,ebsnum,exact);
RECOVER
  refcuri = AUTO;
ENDSEQ
  return(refcuri);
}

/******************************************************************************/
/**
\brief  ProvideEXD

\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEXD"

exd *refp :: ProvideEXD ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !refrex )                                     ERROR
  if ( exd_area && *refrex != exd_area->get_exdebsn() )
  {
    ReleaseReference();
    Reset();
  }
    
  if ( !exd_area )
  {
    if ( !(exd_area = struct_access->ProvideEXD(*refrex,cluster_number,
                                                sizeof(EB_Number),(char)refsotyp,!refglob,
                                                HasWorkspace(),GetVersion())) )
                                                     ERROR
    if ( refrex->IsEmpty(ob_handle->get_pif()) || exd_area->NewEntry() )
      *(EB_Number *)exd_area->GetInstance() = 0;
    ReserveReference();
    if ( struct_access->get_pif() )
      exd_area->SetPIF();
  
  }
  refprefx->Setup((EB_Number *)exd_area->GetInstance(),cluster_number);
RECOVER
ENDSEQ
  return(exd_area);
}

/******************************************************************************/
/**
\brief  Refresh

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical refp :: Refresh ( )
{
  logical   term = NO;

BEGINSEQ
  if ( !ProvideEXD() )                               ERROR
  
  if ( refrex->IsEmpty(ob_handle->get_pif()) || stsclck() ) 
                                                     LEAVESEQ
  if ( mod_count != exd_area->get_mod_count() || exd_area->IsModified() )
  {
    if ( exd_area->Read(sizeof(EB_Number)) )
    {
      if ( SDBERROR != 3 )                           ERROR
      SDBRESET
      *refrex = 0;
    }
    CheckVersion6();
    mod_count = exd_area->get_mod_count();
    refprefx->Setup((EB_Number *)exd_area->GetInstance(),cluster_number);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Save

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical refp :: Save ( )
{
  EB_Number ebsnum;
  logical   term   = NO;

BEGINSEQ
  if ( !refmod )                                           LEAVESEQ

  exd_area->SetLength(sizeof(EB_Number));
  if ( (ebsnum = struct_access->WriteEXD(exd_area,sizeof(EB_Number),mb_number,AUTO,AUTO)).IsEmpty() )
                                                           ERROR
  mod_count = exd_area->get_mod_count();

  if ( *refrex != ebsnum )
  {
    *refrex = ebsnum;
    stssmod();
  }
  refmod = NO;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetVersion


\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void refp :: SetVersion (uint16 version_nr )
{
  if ( refprefx )
    refprefx->SetVersion(version_nr);
  refs::SetVersion(version_nr);

}

/******************************************************************************/
/**
\brief  UpdateID

\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical refp :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  return(NO);
}

/******************************************************************************/
/**
\brief  refp


\param  lobhandle - 
\param  extref - 
\param  clnumb
\param  akcbptr
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refp"

     refp :: refp (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind )
                     : refs(lobhandle,extref,clnumb,R_REFS,akcbptr,
     globind),
refprefx(NULL)
{
BEGINSEQ
  if ( !(refprefx = new refx(lobhandle,
                             exd_area ? (EB_Number *)exd_area->GetInstance() : (EB_Number*)NULL,
                             clnumb,akcbptr,globind)) )
                                                     ERROR
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  ~refp


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~refp"

     refp :: ~refp ( )
{
  ReleaseReference();
  delete refprefx;
  refprefx = NULL;
}


