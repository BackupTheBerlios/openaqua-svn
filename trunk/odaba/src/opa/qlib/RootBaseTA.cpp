/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    RootBaseTA



\date     $Date: 2006/05/31 18:29:52,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RootBaseTA"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sTABuffer.hpp>
#include  <sacb.hpp>
#include  <sexd.hpp>
#include  <sRootBaseTA.hpp>


/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical RootBaseTA :: Cancel ( )
{
  EB_Number  entnr(1);
  exd       *exdptr  = NULL;
  exd       *exdarea = NULL;
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = new exd(ob_handle,NULL,0,0)) )    SDBERR(95)
                                                     SDBCERR
  while ( !(entnr = GetNextEBNumber(entnr)).IsEmpty() )
  {
    exdarea->set_exdebsn(entnr);
    exdarea->set_ta_count(ta_count);
    eb_RootBase::GetEBI(exdarea->get_exdacb());
    
    exdarea->stsrnof();
    if ( !eb_RootBase::Locate(exdarea->get_exdacb(),IEH) )
      if ( exdptr = ob_handle->GetEXD(exdarea) )
        exdptr->ResetACB(0);
    
    if ( level == 1 )
    {
      ResetEntry(exdarea);
      if ( exdptr )
        exdptr->stsrnof();
    }
  }
  ReleaseDlists();
  ResetDIList(YES);    // remove global instances
RECOVER
  term = YES;
ENDSEQ
  delete exdarea;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckEBI

\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical RootBaseTA :: CheckEBI (exd *exdptr )
{
  acb        acbenty(*exdptr->get_exdacb());

  exdptr->ResetACB(ta_count);
  return( eb_RootBase::CheckEBI(&acbenty) );

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

uint8 RootBaseTA :: CheckWProtect (exd *exdptr )
{

  return(Check_WProtect(exdptr->get_exdacb()));

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

logical RootBaseTA :: Delete (exd *exdptr )
{
  logical                 term = NO;
BEGINSEQ
  exdptr->ResetACB(ta_count);
  
  if ( !eb_RootBase::GetEBI(exdptr->get_exdacb()) )
  {
    if ( TABuffer::ReserveEntry(exdptr) )            ERROR
    if ( Create(exdptr->get_exdacb()).IsEmpty() )    ERROR
  }
  
  if ( !exdptr->get_exdacb()->stscdel() )
    term = eb_RootBase::Delete(exdptr->get_exdacb());
  SetupEntry(exdptr);
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

logical RootBaseTA :: GetEBI (exd *exdptr )
{
  EBI       *ebiptr;
  logical    term = NO;
BEGINSEQ
  exdptr->ResetACB(ta_count);
  if ( !(ebiptr = eb_RootBase::GetEBI(exdptr->get_exdacb())) )    ERROR
//  *(EBI *)exdptr->get_exdacb() = *ebiptr;
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

int32 RootBaseTA :: GetLength (acb *acbptr )
{
  acbptr->ResetACB();
  return(Get_Length(acbptr));
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

int32 RootBaseTA :: GetUsedLength (acb *acbptr )
{

  acbptr->ResetACB();
  return ( !eb_RootBase::Locate(acbptr,IEH) 
           ? AUTO
           : acbptr->get_acbieh().get_iehlen() );


}

/******************************************************************************/
/**
\brief  IsEmpty

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical RootBaseTA :: IsEmpty ( )
{
  EB_Number       entnr;
  return ( GetNextEBNumber(entnr).IsEmpty() ? YES : NO );


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

logical RootBaseTA :: LocateEntry (EB_Number entnr, uint16 version_nr )
{
  acb        acbenty(entnr,0,0);

// wat is mit de Version??
  return( eb_RootBase::CheckEBI(&acbenty) || acbenty.NewEntry() );
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

logical RootBaseTA :: Read (exd *exdptr, int32 w_instlen )
{
  char       wpm  = exdptr->stscwpt();
  acb        save_acb(0,0);
  logical    term = NO;
BEGINSEQ
//  memcpy(&save_acb,exdptr->get_exdacb(),S_ACB);
  exdptr->ResetACB(ta_count);
  if ( CheckEBI(exdptr) )                            ERROR
    
  if ( !eb_RootBase::Locate(exdptr->get_exdacb(),AUTO) )          ERROR

  if ( Check_WProtect(exdptr->get_exdacb()) == 1 )
    exdptr->stssusr3();
  
  switch ( wpm )
  {
    case  1 : exdptr->stsswpt(1);                    break;
    case  2 : exdptr->stsswpt(3);                    break;
    default : ;
  }
  SetupEntry(exdptr);
RECOVER
  term = YES;
ENDSEQ
//  memcpy(exdptr->get_exdacb(),&save_acb,S_ACB);
  return(term);
}

/******************************************************************************/
/**
\brief  RootBaseTA - 



\param  lobhandle - 
\param  highTABuf - 
\param  tanumber - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RootBaseTA"

     RootBaseTA :: RootBaseTA (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber )
                     : TABuffer (lobhandle,highTABuf,tanumber),
eb_RootBase (NO,NO)
{
  char      cpath[129];
  char      filename[13];
BEGINSEQ
/*  
  *cpath = 0;
  if ( !filevfd("TABASE",cpath) && !fildpgt(cpath,sizeof(cpath)) )
                                                     ERROR
  strcpy(filename,"tabase99.ODE");
  gvtxitp(filename,level,12);
  strcat(cpath,filename);
      
  if ( Exist(cpath,NO) )
    remove(cpath);
  if ( Exist(cpath,NO) )                             SDBERR(5)
  
  if ( InitRootBase(cpath,0,254,0,NO) )              SDBERR(5)
  if ( Open(cpath,PI_Write,NO,AUTO) )                SDBERR(5)
*/
  if ( OpenTemp() )                                  SDBERR(5)

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  Save

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical RootBaseTA :: Save ( )
{
  EB_Number  entnr(1);
  exd       *exdarea = NULL;
  exd       *exdptr = NULL;
  logical    wpt;
  int16      indx = 0;
  logical    term = NO;
BEGINSEQ
  if ( !(exdarea = new exd(ob_handle,NULL,1024L * 63,0)) ) 
                                                     SDBERR(95)
                                                     SDBCERR
  if ( SaveBuffer() )                                ERROR
    
  while ( !(entnr = GetNextEBNumber(entnr)).IsEmpty() )
  {
    exdarea->get_exdacb()->ResetACB();
    exdarea->set_exdebsn(entnr);
    if ( eb_RootBase::CheckEBI(exdarea->get_exdacb()) )
      if ( Create(exdarea->get_exdacb()).IsEmpty() ) 
        term = YES;
            
    if ( exdarea->get_exdacb()->stscdel() )
    {
      exdarea->get_exdacb()->ResetACB();
      if ( ob_handle->Delete(exdarea) )
      {
        term = YES;
        SDBISET(316)
      }
    }
    else
    {
      if ( !exdarea->ChangeSize() )                ERROR
      if ( !eb_RootBase::Locate(exdarea->get_exdacb(),AUTO) )
        term = YES;
      else
      {
        wpt = Check_WProtect(exdarea->get_exdacb()) == 1 ? YES : NO;
        exdarea->get_exdacb()->ResetACB();
        ob_handle->GetEBI(exdarea);
        exdarea->stssmod();
        exdarea->set_write_length(exdarea->get_exdacb()->get_entry_length()-IEH, AUTO);
        if ( wpt ? exdarea->SetWProtect()  // schreibt auch!
                 : ob_handle->Write(exdarea)                 )
        {
          term = YES;
          SDBISET(242)
        }
      }
    }
    exdarea->stsrnof();
    if ( exdptr = ob_handle->GetEXD(exdarea) )
{
      exdptr->ResetACB(0);
if ( exdptr->stscnof() && !exdptr->stscwpt() )
  exdptr->stsswpt(1); //müßte eigentlich gesetzt sein
}
    
    if ( level == 1 )
    {
      TABuffer::ReleaseEntry(exdarea);
      if ( exdptr )
        exdptr->stsrnof();
    }
  }
  
  if ( ConsolidateDlists() )
    term = YES;
  SDBCERR
RECOVER
  term = YES;
ENDSEQ
  ResetDIList(NO);
  delete exdarea;
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

logical RootBaseTA :: Write (exd *exdptr )
{
  int32       len  = exdptr->get_write_end();
  int32       pos  = exdptr->get_write_start();
  int32       maxlen = exdptr->get_exdacb()->get_entry_length();  
  acb        save_acb(0,0);
  logical    term = NO;
BEGINSEQ
//  memcpy(&save_acb,exdptr->get_exdacb(),S_ACB);
  exdptr = exdptr->UpdatePIF();
  
  maxlen = MAX(maxlen,IEH)-IEH;
  exdptr->ResetACB(ta_count);
  if ( CheckEBI(exdptr) )
  {
    if ( Create(exdptr->get_exdacb()).IsEmpty() )    ERROR
    if ( TABuffer::ReserveEntry(exdptr) )            ERROR
    exdptr->set_write_length(MAX(len,maxlen),AUTO);
  }
  else
    GetEBI(exdptr);
  
  maxlen = MAX(maxlen+IEH,exdptr->get_exdacb()->get_entry_length());  
  maxlen = MAX(maxlen,IEH)-IEH;
  if ( exdptr->get_exdacb()->get_entry_length() < maxlen+IEH )
    exdptr->set_write_length(MAX(len,maxlen),AUTO);
    
  len  = exdptr->get_write_end();
  pos  = exdptr->get_write_start();
  if ( len == AUTO && !exdptr->stscmod() )  // nur EBI geändert oder top-ref
    len = 0;
  else
  {
    if ( len == AUTO )
      len = exdptr->GetLength();

    if ( pos == AUTO )
      len += IEH;
    else
    {
      len -= pos;
      pos += IEH;
    }
  }
      
  term = Update(exdptr->get_exdacb(),len,pos);
  exdptr->ResetWriteLen();
  SetupEntry(exdptr);
RECOVER
  term = YES;
ENDSEQ
//  memcpy(exdptr->get_exdacb(),&save_acb,S_ACB);
  return(term);
}

/******************************************************************************/
/**
\brief  ~RootBaseTA - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~RootBaseTA"

     RootBaseTA :: ~RootBaseTA ( )
{
  Close();


}


