/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InternalTA

\brief    


\date     $Date: 2006/03/12 19:17:38,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InternalTA"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sPoolTA.hpp>
#include  <sTABuffer.hpp>
#include  <sacb.hpp>
#include  <sexd.hpp>
#include  <srvr.hpp>
#include  <sInternalTA.hpp>


/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical InternalTA :: Cancel ( )
{
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
  ta_error = YES;
  if ( use_count > 1 )                               LEAVESEQ
    
  while ( exdarea = (exd *)GetTail() )
  {
    ModBuffer::Delete(exdarea);
    ResetEntry(exdarea);
    exdarea->ReleaseInstance(NULL);
  }

  ReleaseDlists();
  ResetDIList(YES);    // remove global instances
  ReleaseFields();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return wpmode

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 InternalTA :: CheckWProtect (exd *exdptr )
{
  exd                    *exdarea;
  uint8                   wpmode = UNDEF;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),exdptr->get_shadow_base(),CUR_VERSION)) )
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

logical InternalTA :: Delete (exd *exdptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !Locate(exdptr->get_exdebsn(),exdptr->get_shadow_base(),exdptr->get_exdacb()->get_version_number()) ) 
  {
    if ( ReserveEntry(exdptr) )                      ERROR
    exdptr->ReserveInstance(NULL);
    if ( AddEntry(exdptr) )                          ERROR
  }
  
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

int32 InternalTA :: GetCount ( )
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

logical InternalTA :: GetEBI (exd *exdptr )
{
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),exdptr->get_shadow_base(),exdptr->get_exdacb()->get_version_number())) )
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

int32 InternalTA :: GetLength (acb *acbptr )
{
  exd       *exdptr;
  return ( (exdptr = Locate(acbptr->get_ebsnum(),AUTO,acbptr->get_version_number())) && exdptr->get_use_count()
          ? exdptr->get_exdacb()->get_entry_length()
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

int32 InternalTA :: GetUsedLength (acb *acbptr )
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
\brief  InternalTA - 



\param  lobhandle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InternalTA"

                        InternalTA :: InternalTA (LACObject *lobhandle )
                     : TABuffer (lobhandle,NULL,0),
ModBuffer (lobhandle),
use_count(0)
{



}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical InternalTA :: IsEmpty ( )
{

  return ( ModBuffer::GetCount() ? NO : YES );

}

/******************************************************************************/
/**
\brief  Locate - 


\return buffer -
-------------------------------------------------------------------------------
\brief i0


\param  entnum -
\param  clnumb -
\param  otyp -
\param  instlen -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *InternalTA :: Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr )
{

  return(exdBuffer::Locate(entnum,clnumb,otyp,instlen,version_nr));

}

/******************************************************************************/
/**
\brief i1


\param  entnr -
\param  shadow_opt -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *InternalTA :: Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr )
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

logical InternalTA :: LocateEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{
  exd       *exdarea;
  return( (exdarea = Locate(entnr,shadow_opt,version_nr)) && exdarea->get_use_count() ? NO : YES);


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

logical InternalTA :: Read (exd *exdptr, int32 w_instlen )
{
  exd        *exdarea;
  logical     term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(exdptr->get_exdebsn(),exdptr->get_shadow_base(),exdptr->get_exdacb()->get_version_number())) )
                                                     ERROR
  if ( CheckEntry(exdptr,exdarea) )                  ERROR

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

logical InternalTA :: Save ( )
{
  EB_Number  entnr(1);
  exd       *exdarea;
  logical    term = NO;
BEGINSEQ
  if ( !GetCount() )                                 LEAVESEQ
  if ( use_count > 1 )                               LEAVESEQ
  Optimize();
  
  if ( ta_error )
  {
    Cancel();                                        SDBERR(208)
  }
  if ( high_TA )
    if ( high_TA->Check(this) )                      ERROR
    
  if ( ta_level == 1 )
    if ( SaveRecovery() )   
    {
      Cancel();                                      ERROR
    }
    
  ModBuffer::Cancel();
  while ( exdarea = (exd *)GetPrevious() )
  {
    if ( exdarea->stscdel() )
    {
      if ( ModBuffer::ob_handle->Delete(exdarea) )
      {
        term = YES;
        SDBISET(242)
      }
    }
    else
    {
      if ( ModBuffer::ob_handle->Write(exdarea) )
      {
        term = YES;
        SDBISET(242)
      }
    }
  }
  
  if ( ta_level == 1 && !term )
    TABuffer::ob_handle->get_db_handle()->GetLocalDBHandle()->RlsRecoveryHdl();
  
  while ( exdarea = (exd *)GetTail() )
  {
    ModBuffer::Delete(exdarea);
    if ( ta_level == 1 )
      ReleaseEntry(exdarea);
    exdarea->SetInWork(NO);
    exdarea->ReleaseInstance(NULL);
  }

  if ( ConsolidateDlists() )
    term = YES;
  ResetDIList(NO);
  ReleaseFields();
RECOVER
  term = YES;
ENDSEQ
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

logical InternalTA :: SaveRecovery ( )
{
  rvr        *rec_handle;
  exd        *exdarea;
  logical     term = NO;
BEGINSEQ
  if ( !(rec_handle = TABuffer::ob_handle->get_db_handle()->GetLocalDBHandle()->GetRecoveryHdl()) )
                                                     LEAVESEQ
  ModBuffer::Cancel();
  while ( exdarea = (exd *)GetPrevious() )
  {
    if ( rec_handle->Write(exdarea->get_exdacb(),AUTO,exdarea->stscdel() ? 'D' : 'U',0) )
      term = YES;
  }
      
  TABuffer::ob_handle->get_db_handle()->GetLocalDBHandle()->SavRecoveryHdl(term);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Start - 


\return term - Termination code

\param  highTABuf -
\param  tanumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical InternalTA :: Start (TABuffer *highTABuf, int32 tanumber )
{
  logical                 term = NO;
BEGINSEQ
  if ( ++use_count > 1 )                             LEAVESEQ
  TABuffer::Start(highTABuf,tanumber);
  ta_error = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Stop - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

logical InternalTA :: Stop ( )
{

BEGINSEQ
  if ( --use_count )                                 LEAVESEQ

  high_TA  = NULL;
  ta_level = UNDEF;
  ta_count = UNDEF;
  ta_error = NO;
ENDSEQ
  return(ta_error);
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

logical InternalTA :: Write (exd *exdptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( Locate(exdptr->get_exdebsn(),exdptr->get_shadow_base(),exdptr->get_exdacb()->get_version_number()) )
                                                     LEAVESEQ
  if ( ReserveEntry(exdptr) )                        ERROR
  
  exdptr->ReserveInstance(NULL);
  
  if ( AddEntry(exdptr) )                            ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~InternalTA - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InternalTA"

                        InternalTA :: ~InternalTA ( )
{



}


