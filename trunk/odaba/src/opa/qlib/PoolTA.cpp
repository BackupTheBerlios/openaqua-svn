/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    PoolTA

\brief    


\date     $Date: 2006/06/18 12:44:37,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PoolTA"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBinSArrayObjEntry.hpp>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sTABuffer.hpp>
#include  <sacb.hpp>
#include  <sexd.hpp>
#include  <sexdBEntry.hpp>
#include  <srvr.hpp>
#include  <sPoolTA.hpp>


/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical PoolTA :: Cancel ( )
{
  exd       *exdarea;
  exdBEntry *eb_entry;
  logical    term = NO;
  while ( exdarea = (exd *)GetTail() )
  {
    exdBuffer::Delete(exdarea);
    ResetEntry(exdarea);
    exdarea->stsrnof();
    if ( ta_level == 1 )
      TABuffer::ReleaseEntry(exdarea);
    delete exdarea;
  }
    
  ReleaseDlists();
  ResetDIList(YES);    // remove global instances
  return(term);
}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  low_ta - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical PoolTA :: Check (TABuffer *low_ta )
{
  TABuffer  *cur_TA = TABuffer::ob_handle->get_ta_buffer();
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
  if ( max_entries == AUTO || 
       max_entries - GetCount() >= low_ta->GetCount() )
                                                     LEAVESEQ
  ResetDIList(NO);
  
  TABuffer::ob_handle->SetTA(high_TA);
  while ( exdarea = (exd *)GetHead() )
  {
    exdBuffer::Delete(exdarea);
    if ( exdarea->get_use_count() )
    {
      if ( exdarea->stscdel() )
      {
        if ( TABuffer::ob_handle->Delete(exdarea) )
          term = YES;
      }
      else
      {
        if ( TABuffer::ob_handle->Write(exdarea) )
          term = YES;
      }
      exdarea->stsrnof();
      if ( ta_level == 1 )
      {
        if ( low_ta->Locate(exdarea->get_exdebsn(),AUTO,exdarea->get_reqversion()) )
          TABuffer::UpdateEntry(exdarea);
        else
          TABuffer::ReleaseEntry(exdarea);
      }
      exdarea->set_use_count(0);
    }
    delete exdarea;
  }

ENDSEQ
  TABuffer::ob_handle->SetTA(cur_TA);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return wpmode - 

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 PoolTA :: CheckWProtect (exd *exdptr )
{
  exd                    *exdarea;
  uint8                   wpmode = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),AUTO,CUR_VERSION)) )
                                                 SDBERR(99)

  wpmode = exdarea->get_exdacb()->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y");
RECOVER

ENDSEQ
  return(wpmode);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical PoolTA :: Delete (exd *exdptr )
{
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
if ( !exdptr->stscwpt() || exdptr->stscwpt() == 2 )      // nur mal für 'ne Weile
{
  SDBSET(99)
  SDBRESET
}
  
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),AUTO,exdptr->get_exdacb()->get_version_number())) )  
  {
    if ( TABuffer::ReserveEntry(exdptr) )             ERROR
  
    if ( !(exdarea = Locate(exdptr->get_exdebsn(),
                            exdptr->get_exdcln(),
                            exdptr->GetIEH()->get_iehtyp(),
                            UNDEF,exdptr->get_exdacb()->get_version_number())) )  
                                                     ERROR
  }
  exdarea->set_use_count(1);
  *exdarea->get_exdacb() = *exdptr->get_exdacb();
  *(sts *)exdarea = *(sts *)exdptr;
  exdarea->stsrnof();
  exdarea->stsswpt(1);
  exdarea->stssdel();
  exdarea->set_ta_count(ta_count);
  exdarea->set_read_ta(exdptr->get_read_ta());
  
  exdptr->stssdel();
RECOVER
  term = YES;
ENDSEQ
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

int32 PoolTA :: GetCount ( )
{

  return(exdBuffer::GetCount());

}

/******************************************************************************/
/**
\brief  GetEBI - 


\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

logical PoolTA :: GetEBI (exd *exdptr )
{
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),AUTO,exdptr->get_exdacb()->get_version_number())) )
                                                     ERROR

  *(EBI *)exdptr->get_exdacb() = *(EBI *)exdarea->get_exdacb();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetLength - 


\return longlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 PoolTA :: GetLength (acb *acbptr )
{
  exd       *exdptr;
  return ( (exdptr = Locate(acbptr->get_ebsnum(),AUTO,acbptr->get_version_number())) && exdptr->get_use_count()
          ? MAX(exdptr->get_exdacb()->get_entry_length(),exdptr->get_write_end()+IEH)
          : 0 );


}

/******************************************************************************/
/**
\brief  GetUsedLength - 


\return longlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedLength"

int32 PoolTA :: GetUsedLength (acb *acbptr )
{
  exd       *exdptr;
  int32       len = 0;
  if ( (exdptr = Locate(acbptr->get_ebsnum(),AUTO,acbptr->get_version_number())) && 
       exdptr->get_use_count() )
  {
    acbptr->get_acbieh() = exdptr->get_exdacb()->get_acbieh();
    len = acbptr->get_acbieh().get_iehlen();
  }


  return(len);
}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical PoolTA :: IsEmpty ( )
{

  return ( GetCount() ? NO : YES );

}

/******************************************************************************/
/**
\brief  Locate - 


\return buffer - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  entnum - 
\param  clnumb - 
\param  otyp - 
\param  instlen - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *PoolTA :: Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr )
{
  exd     *exdarea;
  return(exdBuffer::Locate(entnum,clnumb,otyp,instlen,version_nr));


}

/******************************************************************************/
/**
\brief  i1 - 


\param  entnr - 
\param  shadow_opt - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *PoolTA :: Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{

  return(exdBuffer::Locate(entnr,shadow_opt,version_nr));

}

/******************************************************************************/
/**
\brief  LocateEntry - 


\return term - Termination code

\param  entnr - 
\param  shadow_opt - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateEntry"

logical PoolTA :: LocateEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{
  exd       *exdarea;
  return( (exdarea = Locate(entnr,shadow_opt,version_nr)) && exdarea->get_use_count() ? NO : YES);


}

/******************************************************************************/
/**
\brief  PoolTA - 



\param  lobhandle - 
\param  highTABuf - 
\param  tanumber - 
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PoolTA"

     PoolTA :: PoolTA (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber, int16 w_maxnum )
                     : TABuffer (lobhandle,highTABuf,tanumber),
exdBuffer(lobhandle,
           w_maxnum == AUTO ? 512 : w_maxnum,
           UNDEF,UNDEF,UNDEF,NO),
max_entries(w_maxnum)
{



}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

\param  exdptr - 
\param  w_instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical PoolTA :: Read (exd *exdptr, int32 w_instlen )
{
  exd       *exdarea;
  char       wpm = exdptr->stscwpt();
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),AUTO,exdptr->get_exdacb()->get_version_number())) ||
       !exdarea->get_use_count() )                   ERROR
  if ( CheckEntry(exdptr,exdarea) )                  ERROR

//  exdptr->ChangeSize(w_instlen > 0 ? w_instlen : exdptr->GetLength());
  
  if ( exdarea->GetLength() > exdptr->get_entry_size() )
                                                     SDBERR(99)
  exdptr->CopyTo(exdarea);
  exdptr->stsrmod();
  exdptr->set_ta_count(ta_count);
  exdptr->set_read_ta(exdarea->get_read_ta());
  *exdptr->get_exdacb() = *exdarea->get_exdacb();
    
  switch ( wpm )
  {
    case  1 : exdptr->stsswpt(1);                    break;   // war case 0: bis 8.10.98
    case  2 : exdptr->stsswpt(3);                    break;
    default : ;
  }

  SetupEntry(exdptr);
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

logical PoolTA :: Save ( )
{
  exd       *exdarea;
  exdBEntry *eb_entry;
  logical    term = NO;
BEGINSEQ
  TABuffer::ob_handle->get_local_dbhandle()->SaveBuffer();
  
  if ( ta_level == 1 )
    if ( SaveRecovery() )
    {
      Cancel();                                      ERROR
    }
  
  exdBuffer::Cancel();
  while ( exdarea = (exd *)GetNext() )
  {
    if ( exdarea->get_use_count() )
    {
      if ( exdarea->stscdel() )
      {
        if ( TABuffer::ob_handle->Delete(exdarea) )
        {
          term = YES;
          SDBISET(242)
        }
      }
      else
      {
        if ( TABuffer::ob_handle->Write(exdarea) )
        {
          term = YES;
          SDBISET(242)
        }
      }
    }
  }
  
  if ( ta_level == 1 && !term )
    TABuffer::ob_handle->get_local_dbhandle()->RlsRecoveryHdl();
    
  while ( exdarea = (exd *)GetTail() )
  {
    exdBuffer::Delete(exdarea);
    if ( exdarea->get_use_count() )
    {
      exdarea->stsrnof();
      if ( ta_level == 1 )
        TABuffer::ReleaseEntry(exdarea);
    }
    delete exdarea;
  }
  
  if ( ConsolidateDlists() )
    term = YES;

RECOVER
  term = YES;
ENDSEQ
  ResetDIList(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SaveRecovery - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveRecovery"

logical PoolTA :: SaveRecovery ( )
{
  rvr        *rec_handle;
  exd        *exdarea;
  logical     term = NO;
BEGINSEQ
  if ( !(rec_handle = TABuffer::ob_handle->get_local_dbhandle()->GetRecoveryHdl()) )
                                                     LEAVESEQ
  exdBuffer::Cancel();
  while ( exdarea = (exd *)GetNext() )
    if ( exdarea->get_use_count() )
      if ( rec_handle->Write(exdarea->get_exdacb(),AUTO,exdarea->stscdel() ? 'D' : 'U',0) )
        term = YES;
      
  TABuffer::ob_handle->get_local_dbhandle()->SavRecoveryHdl(term);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Write - 


\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical PoolTA :: Write (exd *exdptr )
{
  exd       *exdarea;
  int        ext_wpt = exdptr->stscwpt();
  int32       wlen = exdptr->get_write_end();
  logical    ext_nof = exdptr->stscnof();
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),
                          exdptr->get_exdcln(),
                          exdptr->GetIEH()->get_iehtyp(),
                          wlen != AUTO ? MAX(wlen,exdptr->get_exdacb()->get_acbieh().get_iehlen()) 
                                       : MAX(exdptr->get_exdacb()->get_acbieh().get_iehlen(),exdptr->get_exdacb()->get_entry_length()),
                          exdptr->get_exdacb()->get_version_number())) )
                                                     ERROR
  exdarea->CopyTo(exdptr->UpdatePIF());
  exdarea->stsrnof();
  
// die PoolTA mag nur Entries aus anderen Transaktionen (mindestens internal). Sonst kann es zu Lockproblemen kommen
  if ( ext_wpt >= 2 )               // externe Reservierung wird in Transaktion nicht benötigt
    exdarea->stsswpt(ext_wpt-2);
    
  if ( !exdarea->get_use_count() )
  {
    if ( TABuffer::ReserveEntry(exdptr) )            ERROR
    exdarea->set_use_count(1);
  }
  exdarea->set_ta_count(ta_count);
  exdarea->set_read_ta(exdptr->get_read_ta());
  *exdarea->get_exdacb() = *exdptr->get_exdacb();
  if ( exdptr->get_write_start() != AUTO )
    wlen -= exdptr->get_write_start();
  exdarea->set_write_length(wlen,exdptr->get_write_start());
  exdptr->set_ta_count(ta_count);
  exdptr->ResetWriteLen();

// kein InternTA Exd und in Structure-Buffer
  if ( !ext_nof && (exdarea = TABuffer::ob_handle->GetEXD(exdptr)) )  
    exdarea->set_ta_count(ta_count);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~PoolTA - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PoolTA"

     PoolTA :: ~PoolTA ( )
{

  Clear();


}


