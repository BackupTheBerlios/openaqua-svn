/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    exd

\brief    


\date     $Date: 2006/07/23 18:26:33,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "exd"

#include  <popa7.h>
#include  <exdext.h>
#include  <sACObject.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCSHandleList.hpp>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sPCSHandle.hpp>
#include  <sacb.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sexdBBuffer.hpp>
#include  <sexdBuffer.hpp>
#include  <sieh.hpp>
#include  <sexd.hpp>

int32 exd_count = 0;

/******************************************************************************/
/**
\brief  Cancel - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

void exd :: Cancel ( )
{

  if ( this )
    set_exdebsn(0);


}

/******************************************************************************/
/**
\brief  ChangeSize - 


\return longlen - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  longlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeSize"

int32 exd :: ChangeSize (int32 longlen )
{
  int32      newlen;
  logical    reserve = NO;
BEGINSEQ
  if ( longlen <= entry_size )                       LEAVESEQ
  newlen = (longlen+=sizeof(acb));

  if ( ob_handle && exdacb->get_reserved() )
//if ( ob_handle && use_count > 0 )
  {      
    ob_handle->ReleaseInstance(exdacb);
    reserve = YES;
  }
      
  exdacb->get_active_handles().Uninitialize();
  newlen = (int32)msmcs((void **)&exdacb,longlen);
  exdacb->get_active_handles().Initialize();
  if ( longlen > newlen )                            SDBERR(95)
/*
  if ( exd_buffer )
  {      
    if ( longlen > (newlen = (int32)msmcs((void **)&exdacb,longlen)) )
                                                     SDBERR(95)
  }
  else
  {
    if ( !(newacb = acb::Create(longlen)) )          ERROR
    *newacb = *exdacb;
    newacb->get_active_handles().Move(exdacb->get_active_handles());
    memcpy(newacb+1,exdacb+1,(int)entry_size);
    delete [] (char *)exdacb;
    exdacb = newacb;
  }
*/
  if ( reserve )
    ob_handle->ReserveInstance(exdacb);
         
  longlen -= sizeof(acb);
  entry_size = longlen;
  SetLength(longlen);

RECOVER
  longlen = 0;
ENDSEQ
  return(longlen);

}

/******************************************************************************/
/**
\brief  i1 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeSize"

int32 exd :: ChangeSize ( )
{

  return ( ChangeSize(exdacb->get_entry_length() - IEH) );

}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return wpmode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 exd :: CheckWProtect ( )
{

  return(get_exdebsn().IsEmpty(ob_handle->get_pif()) || stsctrans()
             ? NO 
             : ob_handle->CheckWProtect(this));

}

/******************************************************************************/
/**
\brief  CopySettings - 



\param  srceexd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySettings"

void exd :: CopySettings (exd *srceexd )
{

  *(sts *)this = *srceexd;
    
//  prev_exd = srceexd->get_prev_exd();
  inst_sid     = srceexd->get_inst_sid();
  shadow_base  = srceexd->get_shadow_base();
  write_shadow = srceexd->get_write_shadow();



}

/******************************************************************************/
/**
\brief  CopyTo - 



\param  srceexd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyTo"

void exd :: CopyTo (exd *srceexd )
{
  logical    nof = stscnof();
  logical    res = stscres();
  char       wpm = stscwpt();
BEGINSEQ
  if ( entry_size < srceexd->get_exdacb()->get_acbieh().get_iehlen() )
                                                     SDBERR(99)
  exdacb->CopyTo(srceexd->get_exdacb());  
  CopySettings(srceexd);
  if ( srceexd->IsPIF() )
    SetPIF();
  else
    ResetPIF();

  if ( nof )
    stssnof();
  if ( res )
    stssres();
  if ( wpm > stscwpt() )
    stsswpt(wpm);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  unlock - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical exd :: Delete (logical unlock )
{
  logical                 term = NO;
BEGINSEQ
  if ( stsclck() && !unlock )                        SDBERR(6)

  stssdel();
  if ( stsctrans() )                                 LEAVESEQ
    
  if ( ob_handle->Delete(this) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FlushCluster - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushCluster"

logical exd :: FlushCluster ( )
{

  return ( stsctrans() ? NO : ob_handle->FlushCluster(exdacb) );

}

/******************************************************************************/
/**
\brief  GetDBLength - 


\return longlen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBLength"

int32 exd :: GetDBLength ( )
{
  int32       longlen;
  if ( !exdacb->get_mod_count() && !stsctrans() )
    longlen = ob_handle->GetLength(exdacb);
  else
    if ( longlen = exdacb->get_entry_length() )
      longlen -= IEH;
    else
      longlen = GetLength();
    
  if ( write_end != AUTO && write_end > longlen )
    longlen = write_end;

  return(longlen);
}

/******************************************************************************/
/**
\brief  GetIEH - 


\return iehref - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIEH"

ieh *exd :: GetIEH ( )
{

  return ( &exdacb->get_acbieh() );

}

/******************************************************************************/
/**
\brief  ILock - 


\return term - Termination code

\param  wait - 
\param  mod_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical exd :: ILock (logical wait, char *mod_id )
{
  char                    string[33];
  logical                 term = NO;
  res_lock.ILock(wait); 
//  gvtxltoa(exdacb->get_ebsnum().get_ebsnum(),string,10);
//  SDBError().TraceMessage("Lock: ",mod_id,", EBI-Nr.: ",string);
  return(term);
}

/******************************************************************************/
/**
\brief  IUnlock - 


\return term - Termination code

\param  mod_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical exd :: IUnlock (char *mod_id )
{
  char                    string[33];
  logical                 term = NO;
//  gvtxltoa(exdacb->get_ebsnum().get_ebsnum(),string,10);
//  SDBError().TraceMessage("Unlock: ",mod_id,", EBI-Nr.: ",string);
  res_lock.IUnlock(); 

  return(term);
}

/******************************************************************************/
/**
\brief  InitEXD - 



\param  ebsnum - 
\param  clnumb - 
\param  loc_exact - 
\param  shadow_read - 
\param  shadow_write - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitEXD"

void exd :: InitEXD (EB_Number ebsnum, EB_Number clnumb, logical loc_exact, logical shadow_read, logical shadow_write )
{

  // sollte nur für EXDs im Buffer aufgerufen werden. Sonst reicht set_exdebsn.
  exdacb->set_ws_level(0,0);
  exdacb->set_cluster_numb(clnumb);
  if ( exd_buffer )
    exd_buffer->Setup(exd_ebsnum,ebsnum);
  set_exdebsn(ebsnum);
  *(sts *)this = sts();
  
  exdacb->set_locate_exact(loc_exact);
  shadow_base  = shadow_read;
  write_shadow = shadow_write;
  
  


}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical exd :: Initialize (uint16 version_nr )
{
  int32                    instlen = entry_size+sizeof(acb);
  logical                 term = NO;
BEGINSEQ
  if ( !(exdacb = acb::Create(instlen,version_nr)) ) ERROR
  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsInWork - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInWork"

logical exd :: IsInWork ( )
{

  return(stscusr2());

}

/******************************************************************************/
/**
\brief  IsInstance - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInstance"

logical exd :: IsInstance ( )
{

  return(exdacb->IsInstance());

}

/******************************************************************************/
/**
\brief  IsModified - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

int8 exd :: IsModified ( )
{
  int8                 cond = NO;
BEGINSEQ
  if ( get_exdebsn().IsEmpty(ob_handle->get_pif()) || stsctrans() )      
                                                     LEAVESEQ
  if ( exdacb->stsctrans() )
  {
    stsrdel();
    stsrmod();
    stsrsav();                                       ERROR
  }

  if ( !stscfil() || stscold() )                     ERROR
  if ( stsclck()               )                     LEAVESEQ

  if ( (cond = ob_handle->IsModified(this)) == YES )
    stssold();
RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsTALocked - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTALocked"

logical exd :: IsTALocked ( )
{

  return(ob_handle && ob_handle->LocateTAEntry(get_exdebsn(),get_reqversion()));


}

/******************************************************************************/
/**
\brief  LocateVersion - 


\return exdarea - 

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateVersion"

exd *exd :: LocateVersion (uint16 version_nr )
{
  exd                 *exdarea = this;
  exd                 *exdptr = this;
BEGINSEQ
  if ( version_nr == get_reqversion() || 
       version_nr == CUR_VERSION         )           LEAVESEQ

  if ( version_nr > get_reqversion() )               ERROR
    
  while ( (exdarea = exdarea->get_prev_exd()) && 
          version_nr < exdarea->get_reqversion() ) ;


RECOVER
  exdarea = NULL;
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical exd :: Lock ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( exd_buffer ) ILock(YES,MOD_ID);
  if ( !exdacb )                                     LEAVESEQ
  
  if ( stsclck() )                                   SDBERR(6)
  if ( stscdel() )                                   SDBERR(3)

  if ( !stsctrans() )
  {
    if ( exd_buffer ) IUnlock(MOD_ID);
    term = ob_handle->Lock(exdacb);
    if ( exd_buffer ) ILock(YES,MOD_ID);
    if ( term )                                      ERROR
  }

  stsslck();
RECOVER
  term = YES;
ENDSEQ
  if ( exd_buffer ) IUnlock(MOD_ID);
  return(term);
}

/******************************************************************************/
/**
\brief  LockInternal - 


\return term - Termination code

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical exd :: LockInternal (logical wait )
{
  logical                 term = NO;
BEGINSEQ
  if ( exd_buffer ) ILock(YES,MOD_ID);
  if ( !exdacb )                                     LEAVESEQ
  
  switch ( stscwpt() )  
  {
    case  0 : if ( !IsTALocked() && !stsctrans() )
              {
                if ( exd_buffer ) IUnlock(MOD_ID);
                term = ob_handle->LockInternal(this,wait);
                if ( exd_buffer ) ILock(YES,MOD_ID);
                if ( term )                          ERROR
              }
              stsswpt(1);
              break;
    case  2 : stsswpt(3);
              break;
    default : ;
  }
RECOVER
  term = YES;
ENDSEQ
  if ( exd_buffer ) IUnlock(MOD_ID);
  return(term);
}

/******************************************************************************/
/**
\brief  LockUntilReserveInstance - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockUntilReserveInstance"

void exd :: LockUntilReserveInstance ( )
{

  top_exd->ILock(YES,MOD_ID);
  if ( !top_exd->stscres() )
    top_exd->stssres();
  else
    top_exd->IUnlock(MOD_ID);


}

/******************************************************************************/
/**
\brief  NewEntry - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewEntry"

logical exd :: NewEntry ( )
{
  logical    term = NO;
BEGINSEQ
  if ( stsctrans() )                                 LEAVESEQ
  if ( exdacb->get_mod_count() && !exdacb->NewEntry() )
                                                     LEAVESEQ
  if ( !exdacb->get_mod_count() )
    if ( ob_handle->CheckEBI(this) )
    {
      if ( !exdacb->get_ebi_position() )             ERROR
    }

  
  if ( ta_count )                                    LEAVESEQ
  
  if ( exdacb->NewEntry() )
  {
    if ( ob_handle->LocateTAEntry(get_exdebsn(),shadow_base,get_reqversion()) )
                                                     LEAVESEQ
    if ( !stscfil() )
      Setup();
    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvidePIF - 


\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvidePIF"

exd *exd :: ProvidePIF ( )
{

BEGINSEQ
  if ( !pif_exd )
  {
    pif_exd = new exd(*this);
  }
  else
    if ( pif_exd->ChangeSize(entry_size) != entry_size )ERROR

  pif_exd->CopyTo(this);
                                                     
    
  


RECOVER

ENDSEQ
  return(pif_exd);
}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

\param  w_instlen - 
\param  skip_ta - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical exd :: Read (int32 w_instlen, logical skip_ta )
{
  int32       instlen;
  logical    term = NO;
BEGINSEQ
  if ( exd_buffer ) ILock(YES,MOD_ID);
// war vorher nach IsModified(), 26.5.2004
  if ( stscdel() )                                   SDBERR(3)
  
  switch ( IsModified() )
  {
    case NO   : LEAVESEQ
    case AUTO : ERROR
  }

  if ( stsctrans() )                                 LEAVESEQ
  
  if ( instlen = GetDBLength() )
    if ( ChangeSize(instlen) != instlen )            ERROR
      
  if ( NewEntry() )
    SetLength(0);
  else
  { 
    stsrmod();
    stsrini();
    if ( ob_handle->Read(this,w_instlen==AUTO ? instlen : w_instlen,skip_ta) )
                                                     ERROR
  }
  if ( Setup() )                                     ERROR
RECOVER
  stssini();
  mod_count = 0;
  term = YES;
ENDSEQ
  if ( exd_buffer ) IUnlock(MOD_ID);
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseInstance - 



\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseInstance"

void exd :: ReleaseInstance (PCSHandle *pcs_handle )
{

  if ( exd_buffer ) ILock(YES,MOD_ID);
  
  if ( pcs_handle && exd_buffer && exdacb )
    exdacb->UnregActHandles(pcs_handle);

  if ( exd_buffer ) IUnlock(MOD_ID);
  
  top_exd->ReleaseTop();



}

/******************************************************************************/
/**
\brief  ReleasePIF - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleasePIF"

void exd :: ReleasePIF ( )
{

  delete pif_exd;
  pif_exd = NULL;


}

/******************************************************************************/
/**
\brief  ReleaseTop - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseTop"

void exd :: ReleaseTop ( )
{

  ILock(YES,MOD_ID); 
  if ( stscres() ) // hat exdBuffer schon gelockt?
  {
    stsrres();
    IUnlock(MOD_ID); 
  }
    
  if ( this && use_count )
  {
    if ( !(--use_count) )
    {
      if ( !stscerr() )
      {
        UnlockInternal();
        if ( !stsctrans() )
          ob_handle->ReleaseInstance(exdacb);
        if ( exd_buffer )
          exd_buffer->Release(this);
      }
      if ( ta_count || exdacb->NewEntry() )
      {
        stssini();
        stsrdel();
        exdacb->SetModCount(0);
      }
      read_ta  = 0;
      ta_count = 0;
      if ( !stscwpt() || stscwpt() == 2 )
        stsrnof();
    }
//TraceUSE(NO);
  }
  IUnlock(MOD_ID); 


}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Termination code

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical exd :: Reserve (logical wait )
{
  logical     term = NO;
BEGINSEQ
  if ( stscwpt() >= 2 )                              ERROR
  
  if ( stscnof() )
  {
    if ( exdacb->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") )
                                                     ERROR
    stsswpt(3);
  }
  else
    switch ( stscwpt() )  
    {
      case  0 : if ( !IsTALocked() && !stsctrans() )
                  if ( ob_handle->Reserve(this,wait) )
                                                     ERROR
                stsswpt(2);
                break;
      case  1 : stsswpt(3);
                break;
      default : ;
    }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveInstance - 



\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveInstance"

void exd :: ReserveInstance (PCSHandle *pcs_handle )
{

  if ( exd_buffer ) ILock(YES,MOD_ID);
  
  if ( pcs_handle && exd_buffer && exdacb )
    exdacb->RegActHandles(pcs_handle);

  if ( exd_buffer ) IUnlock(MOD_ID);

  top_exd->ReserveTop();


}

/******************************************************************************/
/**
\brief  ReserveTop - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveTop"

logical exd :: ReserveTop ( )
{
  logical    term = NO;
  if ( stscres() ) // hat exdBuffer schon gelockt?
    stsrres();
  else
    ILock(YES,MOD_ID);
    
  if ( !use_count && !stscerr() )
  {
    if ( !stsctrans() )
      term = ob_handle->ReserveInstance(exdacb); 
  }
  use_count++;
//TraceUSE(YES);
  IUnlock(MOD_ID);
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

logical exd :: Reset ( )
{
  logical    term = NO;
  switch ( stscwpt() )
  {
    case  2 : stsrwpt();
              if ( IsTALocked() )
                stsswpt(1);
              else
                if ( !stsctrans() )
                  ob_handle->UnlockInternal(this);
              break;
    case  3 : stsswpt(1);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ResetACB - 



\param  tanumber - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetACB"

void exd :: ResetACB (int32 tanumber )
{

  if ( read_ta != tanumber )
  {
    read_ta = tanumber;
    ta_count = tanumber;
    exdacb->ResetACB();
  }


}

/******************************************************************************/
/**
\brief  ResetEBI - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetEBI"

logical exd :: ResetEBI ( )
{
  logical  term = NO;
BEGINSEQ
  exdacb->Clear();
  exdacb->stssres();
  exdacb->stssmod();
  write_start = write_end = AUTO;
  if ( Write(AUTO,0) )                              ERROR
  stsrmod();           // write EBI, only (see LDBHandle::Write)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical exd :: ResetWProtect ( )
{
  logical    lock = NO;
  logical    term = NO;
BEGINSEQ
  if ( stsctrans() )                                 LEAVESEQ
  if ( !stscwpt() )
  {
    if ( LockInternal(NO) )                          ERROR
    lock = YES;
  }

  exdacb->ResetWProtect();
  if ( ob_handle->Write(this) )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( lock )
    UnlockInternal();
  return(term);
}

/******************************************************************************/
/**
\brief  ResetWriteLen - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWriteLen"

void exd :: ResetWriteLen ( )
{

  write_start = AUTO;
  write_end   = AUTO;
  stsrmod();


}

/******************************************************************************/
/**
\brief  SetIEH - 



\param  instlen - 
\param  sid - 
\param  otyp - 
\param  version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIEH"

void exd :: SetIEH (int32 instlen, int16 sid, char otyp, uint16 version )
{

  inst_sid       = sid;
  schema_version = (uint8)version;

  exdacb->SetIEH(instlen,sid,otyp,version);

}

/******************************************************************************/
/**
\brief  SetInWork - 


\return workopt - 

\param  workopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInWork"

logical exd :: SetInWork (logical workopt )
{
  logical    int_workopt = stscusr2();
  if ( workopt )
    stssusr2();
  else
    stsrusr2();
  return(int_workopt);
}

/******************************************************************************/
/**
\brief  SetLength - 



\param  longlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLength"

void exd :: SetLength (int32 longlen )
{

  exdacb->SetLength(longlen);
  
  if ( !longlen && mod_count )           // 6.10.03 sonst bleiben alte infos beim Rücksetzen der EXDs im Fehlerfall stehen (Cnacel Transaction)
    memset(GetInstance(),0,entry_size);


}

/******************************************************************************/
/**
\brief  SetPIF - 


/******************************************************************************/
/**
\brief  i01 - 


\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPIF"

void exd :: SetPIF (logical pif )
{

  if ( pif )
    exdacb->SetPIF();
  else
    exdacb->ResetPIF();


}

/******************************************************************************/
/**
\brief  SetTopEXD - 



\param  exdarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTopEXD"

void exd :: SetTopEXD (exd *exdarea )
{

  top_exd = exdarea;
  if ( prev_exd )
    prev_exd->SetTopEXD(exdarea);

}

/******************************************************************************/
/**
\brief  SetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical exd :: SetWProtect ( )
{
  logical     term = NO;
BEGINSEQ
  if ( stsctrans() )                                 LEAVESEQ
    
  exdacb->SetWProtect();
  term = ob_handle->Write(this);
  
  Reset();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical exd :: Setup ( )
{
  logical  term = NO;
  char     string[13];
  logical  mod  = stscmod();
BEGINSEQ
  if ( inst_sid &&
       (inst_sid != exdacb->get_acbieh().get_iehsid()) )
  {
    SDBEV4(gvtxitoa(exdacb->get_acbieh().get_iehsid(),string,10),UNDEF)
    SDBEV5(gvtxitoa(inst_sid,string,10),UNDEF)
    SDBERR(105)
  }
  mod_count++;
  stssfil();
  stsrold();
  if ( mod )
    stssmod();
RECOVER
  GetIEH()->set_iehsid(inst_sid);
  mod_count = UNDEF;
  stssini();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  TraceUSE - 


\return term - Termination code

\param  reserve - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceUSE"

logical exd :: TraceUSE (logical reserve )
{
  char                    string[120];
  char                    cnum[11];
  logical                 term = NO;
if ( exdacb->get_ebsnum().get_ebsnum() == 268179 )
  term = NO;
  strcpy(string,reserve ? "RESERVE: " :
                          "RELEASE: "   );
  gvtxltp(strcpy(cnum,"9999999999"),exdacb->get_ebsnum().get_ebsnum(),10);
  strcat(string,cnum);
  
  strcat(string,"(use ");
  gvtxitp(strcpy(cnum,"999"),use_count,3);
  strcat(string,cnum);
  
  strcat(string,")   total count : ");
  lck_cnt += reserve ? 1 : -1;
  gvtxitp(strcpy(cnum,"99999"),lck_cnt,5);
  strcat(string,cnum);
  SDBError().TraceMessage(string);
  return(term);
}

/******************************************************************************/
/**
\brief  TraceWPT - 


\return term - Termination code

\param  reset_wpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceWPT"

logical exd :: TraceWPT (logical reset_wpt )
{
  char                    string[120];
  char                    cnum[11];
  logical                 term = NO;
  strcpy(string,reset_wpt ? "RESET-WPT: " :
                            "Set-WPT  : "   );
  gvtxltp(strcpy(cnum,"9999999999"),exdacb->get_ebsnum().get_ebsnum(),10);
  strcat(string,cnum);
  
  strcat(string,"   count : ");
  lck_cnt += reset_wpt ? -1 : 1;
  gvtxitp(strcpy(cnum,"999"),lck_cnt,3);
  strcat(string,cnum);
  SDBError().TraceMessage(string);
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical exd :: Unlock ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( exd_buffer ) ILock(YES,MOD_ID);
  if ( !exdacb )                                     LEAVESEQ
  
  if ( !stsclck() )                                  SDBERR(6)

  if ( !stsctrans() )
  {
    if ( exd_buffer ) IUnlock(MOD_ID);
    ob_handle->Unlock(exdacb);
    if ( exd_buffer ) ILock(YES,MOD_ID);
  }

  stsrlck();
RECOVER
  term = YES;
ENDSEQ
  if ( exd_buffer ) IUnlock(MOD_ID);
  return(term);
}

/******************************************************************************/
/**
\brief  UnlockInternal - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical exd :: UnlockInternal ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( exd_buffer ) ILock(YES,MOD_ID);
  if ( !exdacb )                                     LEAVESEQ
  
  switch ( stscwpt() )  
  {
    case  1 : if ( !IsTALocked() )
              {
                if ( !stsctrans() )
                {
                  if ( exd_buffer ) IUnlock(MOD_ID);
                  ob_handle->UnlockInternal(this);
                  if ( exd_buffer ) ILock(YES,MOD_ID);
                }
                stsrwpt();
              }
              break;
    case  3 : stsswpt(2);
              break;
    default : ;
  }

ENDSEQ
  if ( exd_buffer ) IUnlock(MOD_ID);
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateFromPIF - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateFromPIF"

void exd :: UpdateFromPIF ( )
{

BEGINSEQ
  if ( !pif_exd )                                    LEAVESEQ

  *(sts *)this = *pif_exd;
  *(EBI *)exdacb = *pif_exd->get_exdacb();
ENDSEQ

}

/******************************************************************************/
/**
\brief  UpdatePIF - 


\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePIF"

exd *exd :: UpdatePIF ( )
{
  exd             *exdptr = this;
BEGINSEQ
  if ( !pif_exd )                                    LEAVESEQ

  pif_exd->CopySettings(this);
  *(EBI *)pif_exd->get_exdacb() = *(EBI *)exdacb;
  exdptr = pif_exd;
ENDSEQ
  return(exdptr);
}

/******************************************************************************/
/**
\brief  VerifyVersion - 


\return exdarea - 

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VerifyVersion"

exd *exd :: VerifyVersion (uint16 version_nr )
{
  exd                    *exdarea = this;
  exd                    *exdptr  = top_exd;
BEGINSEQ
  if ( version_nr == get_reqversion() )              LEAVESEQ

  exdarea = top_exd;
  while ( version_nr < exdarea->get_reqversion() &&
          (exdarea = exdarea->get_prev_exd())       )
    exdptr = exdarea;
  
  exdarea = exdptr;
  if ( version_nr != exdarea->get_reqversion() )  
  {
    exdarea = new exd(*this);
    exdarea->get_exdacb()->set_version(version_nr);
  
    if ( version_nr < exdptr->get_reqversion() )
      exdarea->set_prev_exd(exdptr->set_prev_exd(exdarea));
    else  // jetzt muß der EXD vor den aktuellen eingehängt werden
    {
      exdarea->set_prev_exd(top_exd);
      top_exd->ob_handle->GetEBI(top_exd);
      if ( exd_buffer )
      {
        exd_buffer->Replace(exdarea);
        exdarea->SetTopEXD(exdarea);
      }
    }
  }
  exdarea->InitEXD(get_exdebsn(),get_exdcln(),exdacb->get_locate_exact(),shadow_base,write_shadow);
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  Write - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  l_size - 
\param  sbnumber - SubBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical exd :: Write (int32 l_size, uint16 sbnumber )
{
  EB_Number  entnr;
  logical    term = NO;
BEGINSEQ
  if ( exd_buffer ) ILock(YES,MOD_ID);
  if ( stsctrans() )                                 LEAVESEQ
  if ( stscdel() )                                   SDBERR(3)
  if ( !exdacb )                                     SDBERR(99)

  if ( exdacb->get_ebsnum().IsEmpty(ob_handle->get_pif()) )
  {
    if ( (entnr = ob_handle->CreateEntry(exdacb->get_mb_number(),
                                         sbnumber,exdacb->get_cluster_number(),
                                         exdacb->get_version_number())).IsEmpty() )  
                                                     ERROR
    if ( exd_buffer )
      exd_buffer->Setup(exd_ebsnum,entnr);
    else
      exdacb->set_ebsnum(entnr);
    if ( pif_exd )
      pif_exd->get_exdacb()->set_ebsnum(entnr);
    if ( use_count )
      ob_handle->ReserveInstance(exdacb); 
  }
  
  if ( Write(l_size,(int32)AUTO) )                    ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( exd_buffer ) IUnlock(MOD_ID);
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  l_size - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical exd :: Write (int32 l_size, int32 offset )
{
  logical    term = NO;
BEGINSEQ
  if ( stsctrans() )                                 LEAVESEQ
  
  if ( exdacb->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") ) 
                                                     SDBERR(28)
  set_write_length(l_size,offset);
  stssmod();
  if ( pif_exd )
    pif_exd->set_write_length(l_size,offset);
    
  if ( ob_handle->Write(this) )                      ERROR
  if ( Setup() )                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  exd - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  lobhandle - 
\param  exdbuf - 
\param  instlen - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exd"

     exd :: exd (LACObject *lobhandle, exdBuffer *exdbuf, int32 instlen, uint16 version_nr )
                     : sts (),
  ob_handle(lobhandle),
  use_count(0),
  prev_exd(NULL),
  mod_count(0),
  ta_count(0),
  read_ta(0),
  inst_sid(0),
  entry_size(instlen),
  write_start(AUTO),
  write_end(AUTO),
  schema_version(0),
  exd_buffer(exdbuf),
  top_exd(this),
  shadow_base(UNDEF),
  write_shadow(UNDEF),
  pif_exd(NULL),
  res_lock(YES),
  exdacb(NULL)
{

if ( instlen < 0 )
  entry_size = 0;
  Initialize(version_nr);
exd_count++;
}

/******************************************************************************/
/**
\brief  i02 - 


\param  lobhandle - 
\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exd"

     exd :: exd (LACObject *lobhandle, acb *acbptr )
                     : sts (),
  ob_handle(lobhandle),
  use_count(0),
  prev_exd(NULL),
  mod_count(0),
  ta_count(0),
  read_ta(0),
  inst_sid(0),
  entry_size(0),
  write_start(AUTO),
  write_end(AUTO),
  schema_version(0),
  exd_buffer(NULL),
  top_exd(this),
  shadow_base(UNDEF),
  write_shadow(UNDEF),
  pif_exd(NULL),
  res_lock(YES),
  exdacb(acbptr)
{
  db_RootBase        *rb;
BEGINSEQ
  if ( !(rb = ob_handle->get_local_dbhandle()->GetRootBase(AUTO)) )
                                                     SDBERR(99)
  
  if ( !rb->Locate(acbptr,IEH) )                     SDBERR(99)
  ChangeSize(acbptr->get_acbieh().get_iehlen());
  exd_ebsnum = acbptr->get_ebsnum();
RECOVER

ENDSEQ
exd_count++;
}

/******************************************************************************/
/**
\brief  i1 - 


\param  exdref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exd"

     exd :: exd (exd &exdref )
                     : sts (),
ob_handle(exdref.get_ob_handle()),
use_count(exdref.get_use_count()),
prev_exd(NULL),
mod_count(0),
ta_count(0),
read_ta(0),
inst_sid(exdref.get_inst_sid()),
entry_size(exdref.get_entry_size()),
write_start(AUTO),
write_end(AUTO),
schema_version(exdref.get_schema_version()),
exd_buffer(exdref.get_exd_buffer()),
top_exd(exdref.get_top_exd()),
shadow_base(exdref.get_shadow_base()),
write_shadow(exdref.get_write_shadow()),
pif_exd(NULL),
res_lock(YES),
exdacb(NULL)
{

  Initialize();

  if ( exdacb ) 
  {
    *exdacb = *exdref.get_exdacb();
    exd_ebsnum = exdacb->get_ebsnum();
  }
exd_count++;
}

/******************************************************************************/
/**
\brief  get_version - 


\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_version"

uint16 exd :: get_version ( )
{

  return(exdacb->get_version());

}

/******************************************************************************/
/**
\brief  oRegActHandles - 



\param  lcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "oRegActHandles"

void exd :: oRegActHandles (CSHandleList *lcs_handle )
{



}

/******************************************************************************/
/**
\brief  oUnregActHandles - 



\param  lcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "oUnregActHandles"

void exd :: oUnregActHandles (CSHandleList *lcs_handle )
{



}

/******************************************************************************/
/**
\brief  set_exdacb - 



\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_exdacb"

void exd :: set_exdacb (acb *acbptr )
{

  exdacb = acbptr;
  exd_ebsnum = acbptr->get_ebsnum();

}

/******************************************************************************/
/**
\brief  set_exdebsn - 



\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_exdebsn"

void exd :: set_exdebsn (EB_Number ebsnum )
{
  logical    transient = stsctrans();
  exd_ebsnum = ebsnum;
  exdacb->set_ebsnum(ebsnum);
  mod_count    = UNDEF;
  ResetWriteLen();
  ta_count     = 0;
  read_ta      = 0;
  *(sts *)this = sts();
  if ( transient )
    stsstrans();
    
  if ( pif_exd )
    pif_exd->set_exdebsn(ebsnum);

}

/******************************************************************************/
/**
\brief  set_prev_exd - 


\return exdarea - 

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_prev_exd"

exd *exd :: set_prev_exd (exd *exdptr )
{
  exd                    *exdarea = prev_exd;
  prev_exd = exdptr;
  return(exdarea);
}

/******************************************************************************/
/**
\brief  set_schema_ver - 



\param  version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_schema_ver"

void exd :: set_schema_ver (uint16 version )
{

  exdacb->get_acbieh().set_iehver(version);

}

/******************************************************************************/
/**
\brief  set_write - 



\param  bwrite_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_write"

void exd :: set_write (logical bwrite_opt )
{

  if ( bwrite_opt || !ob_handle->get_db_handle()->get_net_option() )
    stssusr1();
  else
    stsrusr1();

}

/******************************************************************************/
/**
\brief  set_write_length - 



\param  longlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_write_length"

void exd :: set_write_length (int32 longlen, int32 offset )
{
  int32       startpos = offset == AUTO ? 0 : offset;
  if ( (write_start == AUTO && write_end == AUTO) ||
        offset < write_start                            )
    write_start = offset;
      
  if ( longlen + startpos > write_end )
    write_end = longlen + startpos;

}

/******************************************************************************/
/**
\brief  ~exd - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~exd"

     exd :: ~exd ( )
{

  delete prev_exd;
  if ( exdacb )
  {
    if ( exd_buffer )
      exdacb->Uninitialize();
    msmfs((void **)&exdacb);
  }
  ReleasePIF();

exd_count--;
}


