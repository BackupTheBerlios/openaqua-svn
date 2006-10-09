/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PoolTA_old



\date     $Date: 2006/03/12 19:18:02,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PoolTA_old"

#include  <popa7.h>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sTABuffer.hpp>
#include  <sacb.hpp>
#include  <sexd.hpp>
#include  <sexdBuffer.hpp>
#include  <srvr.hpp>
#include  <sPoolTA_old.hpp>


/******************************************************************************/
/**
\brief  Cancel

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical PoolTA_old :: Cancel ( )
{
  exd       *exdarea;
  int32       indx = GetCount();
  logical    term = NO;
  while ( indx )
    if ( exdarea = exdBuffer::Delete(indx--) )
    {
      if ( exdarea->get_use_count() )
      {
        ResetEntry(exdarea);
        exdarea->stsrnof();
        if ( level == 1 )
          ReleaseEntry(exdarea);
      }
      delete exdarea;
    }
  empty_count = 0;
  return(term);
}

/******************************************************************************/
/**
\brief  Check

\return term - Termination code

\param  exd_buffer -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical PoolTA_old :: Check (exdBBuffer *exd_buffer )
{
  TABuffer  *cur_TA = TABuffer::ob_handle->get_ta_buffer();
  exd       *exdarea;
  int32       indx = 0;
  int16      max  = GetCount();
  logical    term   = NO;
BEGINSEQ
  if ( max_entries == AUTO || 
       max_entries - GetCount() + empty_count >= exd_buffer->GetCount() )
                                                     LEAVESEQ
  TABuffer::ob_handle->SetTA(high_TA);
  while ( indx < max )
    if ( exdarea = GetEntry(++indx)->get_inst_area() )
    {
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
        if ( level == 1 )
        {
          if ( exd_buffer->Locate(exdarea->get_exdebsn(),exdarea->get_reqversion()) )
            TABuffer::UpdateEntry(exdarea);
          else
            ReleaseEntry(exdarea);
        }
        exdarea->set_use_count(0);
        empty_count++;
      }
  //    delete exdarea;
    }
ENDSEQ
  TABuffer::ob_handle->SetTA(cur_TA);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect

\return wpmode

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

UCHAR PoolTA_old :: CheckWProtect (exd *exdptr )
{
  exd                    *exdarea;
  uchar                   wpmode = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),CUR_VERSION)) )
                                                 SDBERR(99)

  wpmode = exdarea->get_exdacb()->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y");
RECOVER

ENDSEQ
  return(wpmode);
}

/******************************************************************************/
/**
\brief  Delete

\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical PoolTA_old :: Delete (exd *exdptr )
{
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
if ( !exdptr->stscwpt() || exdptr->stscwpt() == 2 )      // nur mal für 'ne Weile
{
  SDBSET(99)
  SDBRESET
}
  
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),exdptr->get_exdacb()->get_version_number())) )  
  {
    if ( ReserveEntry(exdptr) )                      ERROR
  
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
  
  if ( !exdarea->get_use_count() )
    Reserve();
  
  exdptr->stssdel();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetEBI

\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

logical PoolTA_old :: GetEBI (exd *exdptr )
{
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),exdptr->get_exdacb()->get_version_number())) )
                                                     ERROR

  *(EBI *)exdptr->get_exdacb() = *(EBI *)exdarea->get_exdacb();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetLength

\return longlen -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 PoolTA_old :: GetLength (acb *acbptr )
{
  exd       *exdptr;
  return ( (exdptr = Locate(acbptr->get_ebsnum(),acbptr->get_version_number())) && exdptr->get_use_count()
          ? max(exdptr->get_exdacb()->get_entry_length(),exdptr->get_write_end()+IEH)
          : 0 );


}

/******************************************************************************/
/**
\brief  GetUsedLength

\return longlen -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedLength"

int32 PoolTA_old :: GetUsedLength (acb *acbptr )
{
  exd       *exdptr;
  int32       len = 0;
  if ( (exdptr = Locate(acbptr->get_ebsnum(),acbptr->get_version_number())) && 
       exdptr->get_use_count() )
  {
    acbptr->get_acbieh() = exdptr->get_exdacb()->get_acbieh();
    len = acbptr->get_acbieh().get_iehlen();
  }


  return(len);
}

/******************************************************************************/
/**
\brief  LocateEntry

\return term - Termination code

\param  entnr -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateEntry"

logical PoolTA_old :: LocateEntry (EB_Number entnr, uint16 version_nr )
{
  exd       *exdarea;
  return( (exdarea = Locate(entnr,version_nr)) && exdarea->get_use_count() ? NO : YES);


}

/******************************************************************************/
/**
\brief  PoolTA


\param  lobhandle -
\param  highTABuf -
\param  tanumber -
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PoolTA"

void PoolTA_old :: PoolTA (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber, int16 w_maxnum )
                     : TABuffer (lobhandle,highTABuf,tanumber),
exdBuffer(lobhandle,msmop(UNDEF,NO),
  w_maxnum == AUTO ? 50 : w_maxnum,
  UNDEF,UNDEF,UNDEF),
max_entries(w_maxnum)
{

  del_proz = 0;

}

/******************************************************************************/
/**
\brief  Read

\return term - Termination code

\param  exdptr -
\param  w_instlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical PoolTA_old :: Read (exd *exdptr, int32 w_instlen )
{
  exd       *exdarea;
  char       wpm = exdptr->stscwpt();
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),exdptr->get_exdacb()->get_version_number())) ||
       !exdarea->get_use_count() )                     ERROR

//  exdptr->ChangeSize(w_instlen > 0 ? w_instlen : exdptr->GetLength());
  
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
\brief  Save

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical PoolTA_old :: Save ( )
{
  exd       *exdarea;
  int32       indx = GetCount();
  logical    term = NO;
BEGINSEQ
  TABuffer::ob_handle->get_local_dbhandle()->SaveBuffer();
  
  if ( level == 1 )
    if ( SaveRecovery() )
    {
      Cancel();                                      ERROR
    }
  
  while ( indx )
    if ( exdarea = GetEntry(indx--)->get_inst_area() )
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
  
  if ( level == 1 && !term )
    TABuffer::ob_handle->get_local_dbhandle()->RlsRecoveryHdl();
    
  indx = GetCount();
  while ( exdarea = exdBuffer::Delete(indx--) )
  {
    if ( exdarea->get_use_count() )
    {
      exdarea->stsrnof();
      if ( level == 1 )
        ReleaseEntry(exdarea);
    }
    delete exdarea;
  }
  empty_count = 0;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveRecovery

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveRecovery"

logical PoolTA_old :: SaveRecovery ( )
{
  rvr        *rec_handle;
  exd        *exdarea;
  int32        indx = GetCount();
  logical     term = NO;
BEGINSEQ
  if ( !(rec_handle = TABuffer::ob_handle->get_local_dbhandle()->GetRecoveryHdl()) )
                                                     LEAVESEQ
  while ( indx )
    if ( exdarea = GetEntry(indx--)->get_inst_area() )
      if ( exdarea->get_use_count() )
        if ( rec_handle->Write(exdarea->get_exdacb(),AUTO,exdarea->stscdel() ? 'D' : 'U',0) )
          term = YES;
      
  TABuffer::ob_handle->get_local_dbhandle()->SavRecoveryHdl(term);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Write

\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical PoolTA_old :: Write (exd *exdptr )
{
  exd       *exdarea;
  int        ext_wpt = exdptr->stscwpt();
  int32       wlen = exdptr->get_write_end();
  logical    ext_nof = exdptr->stscnof();
  logical    term = NO;
BEGINSEQ
if ( !exdptr->stscwpt() || exdptr->stscwpt() == 2 )      // nur mal für 'ne Weile
{
//  SDBSET(99)
  SDBRESET
}
  
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),
                          exdptr->get_exdcln(),
                          exdptr->GetIEH()->get_iehtyp(),
                          wlen != AUTO ? max(wlen,exdptr->get_exdacb()->get_acbieh().get_iehlen()) 
                                       : max(exdptr->get_exdacb()->get_acbieh().get_iehlen(),exdptr->get_exdacb()->get_entry_length()),
                          exdptr->get_exdacb()->get_version_number())) )
                                                     ERROR
  exdarea->CopyTo(exdptr);
  exdarea->stsrnof();
  
  if ( ext_wpt >= 2 )               // externe Reservierung wird in Transaktion nicht benötigt
    exdarea->stsswpt(ext_wpt-2);
    
  if ( !exdarea->get_use_count() )
  {
    if ( ReserveEntry(exdptr) )                      ERROR
    exdarea->set_use_count(1);
    Reserve();
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
\brief  ~PoolTA


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PoolTA"

void PoolTA_old :: ~PoolTA ( )
{

  Clear();
  FreeTable();
  
  msmcl(&ms_pool);



}


