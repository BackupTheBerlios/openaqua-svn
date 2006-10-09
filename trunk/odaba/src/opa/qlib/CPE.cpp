/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CPE

\brief    


\date     $Date: 2006/03/12 19:16:36,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CPE"

#include  <popa7.h>
#include  <sEBI.hpp>
#include  <sacb.hpp>
#include  <scte.hpp>
#include  <sctr.hpp>
#include  <seb_Buffer.hpp>
#include  <seb_BufferEntry.hpp>
#include  <seb_MainBase.hpp>
#include  <sCPE.hpp>


/******************************************************************************/
/**
\brief  CPE - 



\param  mbhandle -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPE"

                        CPE :: CPE (eb_MainBase *mbhandle, EB_Number entnr )
                     : sts(),
  ebsptr(mbhandle), cpeebsn(entnr), cpeebsi(),
  cpeobuf(NULL), cpeucnt(0), cpemod(NO), 
  ctracb(NULL)
{


  SDBRESET



}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical CPE :: Initialize ( )
{
  int32  maxbuf = 256;
  logical   term = NO;

BEGINSEQ
  if ( cpeebsn.IsEmpty() )                           SDBERR(99)
  if ( !(ctracb  = (acb *)new char[sizeof(acb)+CTR_HEADER_LEN]) )
                                                     SDBERR(95)
  memset(ctracb,0,sizeof(acb)+CTR_HEADER_LEN);
  ctracb->set_ebsnum(cpeebsn);
  ctracb->get_mb_ebsnum() = ebsptr->RBNtoMBN(cpeebsn);
    
  if ( ebsptr->GetEBI(ctracb,NO) )                 ERROR
  if ( ctracb->stscdel() )                         SDBERR(3)
  if ( !ctracb->NewEntry() )  
    maxbuf = ctracb->get_entry_length()+S_ACB-IEH;
  
  if ( !(cpeobuf = new eb_Buffer(maxbuf,YES)) )      SDBERR(95)
                                                     SDBCERR
  if ( !ctracb->NewEntry() )  
  {
    if ( cperead() )                                 ERROR
  }
  else
    cpeinit();

  SDBRESET

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical CPE :: Lock ( )
{
  logical                 term = NO;

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

logical CPE :: Refresh ( )
{
  acb       *acbptr;
  uint16     modcount;
  logical    term = NO;
BEGINSEQ
  if ( !ctracb )
    if ( Initialize() )                              ERROR
  if ( ctracb->stscdel() )                         SDBERR(3)
  
  acbptr   = (acb *)cpeobuf->Get(0);
  modcount = acbptr->get_mod_count();
  
  if ( !ebsptr->get_mb_netopt() || ebsptr->Get_Mod(acbptr) == modcount )
                                                     LEAVESEQ
  *ctracb = *acbptr;
  
  if ( !ebsptr->Locate(ctracb,CTR_HEADER_LEN) )      ERROR
  cpeobuf->Clear();
  if ( !(acbptr = (acb *)cpeobuf->Initialize(ctracb->get_entry_length()+S_ACB,0)) )
                                                     ERROR
  *acbptr = *ctracb;  
  cpeobuf->Clear();
  if ( cperead() )                                   ERROR
RECOVER
  term = YES;
ENDSEQ
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

logical CPE :: Unlock ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  cpeadd - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpeadd"

logical CPE :: cpeadd (acb *acbptr )
{
  logical            pif = ebsptr->get_pif();
  logical            term = NO;

BEGINSEQ
  if ( cpelcki() )                                   ERROR
  
  if ( cpeobuf->Add(acbptr->get_entry_length(),acbptr->get_mb_ebsnum(),NULL) ) 
                                                        ERROR
  acbptr->get_acbieh().ToPIF(pif);
  memcpy(cpeobuf->Get(acbptr->get_mb_ebsnum()),&acbptr->get_acbieh(),
         (uint16)acbptr->get_entry_length());
  acbptr->get_acbieh().FromPIF(pif);
  
  cpemod = YES;
RECOVER
  term = YES;
ENDSEQ
  cpeunli();
  return(term);

}

/******************************************************************************/
/**
\brief  cpedel - 


\return term - Termination code

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpedel"

logical CPE :: cpedel (acb *acbptr )
{
  logical   term = NO;

BEGINSEQ
  if ( cpelcki() )                                       ERROR
  
  if ( !cpeobuf->ChangeEntrySize(0,acbptr->get_ebsnum()) ) 
                                                         ERROR
  if ( cpeobuf->Delete(acbptr->get_mb_ebsnum()) )        ERROR
  cpemod = YES;
RECOVER
  term = YES;
ENDSEQ
  cpeunli();
  return(term);

}

/******************************************************************************/
/**
\brief  cpeget - 


\return odblen -

\param  acbptr -
\param  entlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpeget"

int32 CPE :: cpeget (acb *acbptr, int32 entlen )
{
  eb_BufferEntry  *obufenty;
  logical          pif = ebsptr->get_pif();
  int32         odblen = 0;
BEGINSEQ
  if ( Refresh() )                                   ERROR
  
  if ( obufenty = cpeobuf->GetTableEntry(acbptr->get_mb_ebsnum()) )
  {
    odblen = obufenty->get_length();
    memcpy(&acbptr->get_acbieh(),obufenty->get_buffer_pointer(),(int)MIN(entlen,odblen));
    acbptr->get_acbieh().FromPIF(pif);
    acbptr->SetEBILen(odblen);
    acbptr->SetPosition(ctracb->get_mb_ebsnum().get_ebsnum());
  }

RECOVER

ENDSEQ
  return(odblen);

}

/******************************************************************************/
/**
\brief  cpeinit - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpeinit"

logical CPE :: cpeinit ( )
{
  acb      *table;
  logical   term = NO;

  table  = (acb *)cpeobuf->Initialize(CTR_HEADER_LEN+S_ACB,0);
  *table = *ctracb; 
  ((ctr *)&table->get_acbieh())->Initialize();
  return(term);

}

/******************************************************************************/
/**
\brief  cpelcki - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpelcki"

logical CPE :: cpelcki ( )
{
  logical    term = NO;
BEGINSEQ
  if ( stsclck() )                                   SDBERR(6)
  
  if ( !ctracb )
    if ( Initialize() )                              ERROR
  
  if ( ebsptr->get_mb_netopt() )
  {
    if (ebsptr->Lock((acb *)cpeobuf->Get(0),YES) )   ERROR
    term = Refresh();
  }
  
  stsslck();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cpeleng - 


\return odblen -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpeleng"

int32 CPE :: cpeleng (acb *acbptr )
{
  eb_BufferEntry    *obufenty;
  int32           odblen  = 0;
BEGINSEQ
  if ( Refresh() )                                   ERROR
  
  if ( obufenty = cpeobuf->GetTableEntry(acbptr->get_mb_ebsnum()) )
  {
    acbptr->SetEBILen((odblen = obufenty->get_length()));
    acbptr->SetPosition(ctracb->get_mb_ebsnum().get_ebsnum());
  }
RECOVER

ENDSEQ
  return(odblen);

}

/******************************************************************************/
/**
\brief  cperead

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cperead"

logical CPE :: cperead ( )
{
  ctr      *ctrptr;
  cte       wcte;     // upgrade to data version 4
  int       version = ebsptr->get_mb_header()->get_version();
  cte      *cteptr;
  int16 tablelen = CTR_HEADER_LEN+S_ACB;
  int16 tablecnt;
  acb      *table;
  int16 i;
  logical   pif = ebsptr->get_pif();
  logical   term = NO;
BEGINSEQ
  ctrptr = (ctr *)(&ctracb->get_acbieh());
  if ( !ebsptr->Locate(ctracb,CTR_HEADER_LEN) )      ERROR

  if ( version > 3 )  // upgrade to v4
    tablelen += (tablecnt = ctrptr->get_ctrecnt())*sizeof(cte);
  else                // version 3 ro lower, 0nly
    tablelen += (tablecnt = ctrptr->get_ctrecnt())*12;
  
  table = (acb *)cpeobuf->Initialize(tablelen,0);
  *table = *ctracb; 
  ctrptr = (ctr *)(&table->get_acbieh());
  if ( !ebsptr->Locate(table,ctrptr->get_ctrlen()))  ERROR
  
  for ( i=0; i < tablecnt; i++)
  {
    cteptr = ctrptr->ctrget(i,pif,wcte,version);
    term = cpeobuf->Add(cteptr->get_ctelen(),cteptr->get_cteebsn(),(char *)ctrptr+cteptr->get_ctepos());
    if ( pif )
      cteptr = ctrptr->ctrget(i,pif,wcte,version);  // buffer kann sich geändert haben (ChangeSize)
    if ( term )                                      SDBERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cpermv - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpermv"

void CPE :: cpermv ( )
{

  delete (char *)ctracb;
  ctracb = NULL;
  delete cpeobuf;
  cpeobuf = NULL;

}

/******************************************************************************/
/**
\brief  cpeunli - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpeunli"

logical CPE :: cpeunli ( )
{
  logical    term = NO;
BEGINSEQ
  if ( !stsclck() )                                  SDBERR(6)
  stsrlck();
  
  if ( ebsptr->get_mb_netopt() )
  {
    term = cpewrit();
    if (ebsptr->Unlock((acb *)cpeobuf->Get(0)) )     ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cpeupd - 


\return term - Termination code

\param  acbptr -
\param  length -
\param  offset -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpeupd"

logical CPE :: cpeupd (acb *acbptr, int32 length, int32 offset )
{
  void              *entry = NULL;
  eb_BufferEntry    *bufptr;
  logical            pif = ebsptr->get_pif();
  logical            term  = NO;

BEGINSEQ
  if ( cpelcki() )                                   ERROR
  
  if ( !(bufptr = cpeobuf->GetTableEntry(acbptr->get_mb_ebsnum())) )
                                                     SDBERR(99)
  
  if ( acbptr->get_entry_length() == length || offset != AUTO )
  {
    if ( offset == AUTO )
      offset = 0;
    if ( length+offset > cpeleng(acbptr) )           SDBIERR(52)
    entry = bufptr->get_buffer_pointer();
  }  
  else
  {
    offset = 0;
    if ( !(entry = cpeobuf->ChangeEntrySize(length,acbptr->get_mb_ebsnum())) ) 
                                                     ERROR
    acbptr->SetEBILen(length);
  }
  acbptr->get_acbieh().ToPIF(pif);
  memcpy((char *)entry+offset,
         ((char *)&acbptr->get_acbieh())+offset,
         (uint16)length);
  acbptr->get_acbieh().FromPIF(pif);
  
//  bufptr->SetModified();
  cpemod = YES;
RECOVER
  term = YES;
ENDSEQ
  cpeunli();
  return(term);

}

/******************************************************************************/
/**
\brief  cpewrit - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cpewrit"

logical CPE :: cpewrit ( )
{
  acb                acbenty(0,0);
  acb               *table;
  int16          tablecnt;
  int16          i;
  int32           pos;
  int32           len;
  eb_BufferEntry    *bufptr;
  ctr               *ctrptr;
  cte               *cteptr;
  logical            pif = ebsptr->get_pif();
  logical            term = NO;

BEGINSEQ
  if ( !cpemod )                                     LEAVESEQ

  if ( !ctracb )
    Initialize();
  
  tablecnt = cpeobuf->GetEntryCount()-1;
  if ( !cpeobuf->ChangeEntrySize(tablecnt*sizeof(cte)+CTR_HEADER_LEN+S_ACB,0) )  
                                                     ERROR
  table  = (acb *)cpeobuf->Get(0);
  ctrptr = (ctr *)(&table->get_acbieh());

  for ( i=1; i <= tablecnt; i++)
  {
    bufptr = cpeobuf->GetTableEntry(i+1);
    cteptr = ctrptr->ctrget(i-1);
    EB_Number  entnr(bufptr->get_eb_position());

    cteptr->SetLength(bufptr->get_length());
    cteptr->SetNumber(entnr);
    cteptr->SetPosition((char *)bufptr->get_buffer_pointer() - (char *)cpeobuf->get_buffer_area() - S_ACB);
    cteptr->ToPIF(pif);
  }

  ctrptr->SetLength(cpeobuf->get_next_position()-S_ACB);
  ctrptr->SetCount(tablecnt);

  if ( tablecnt > 0 )
  {
    if ( ebsptr->Update(table,cpeobuf->get_buffer_size()-S_ACB+IEH,AUTO) )
                                                         ERROR
  }
  else
    if ( ebsptr->ebscdel(table) )                       ERROR
  
  cpemod = NO;
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~CPE - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CPE"

                        CPE :: ~CPE ( )
{

//  delete (char *)ctracb; jetzt in cpermv


}


