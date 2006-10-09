/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    eb_MainBase

\brief    


\date     $Date: 2006/07/23 18:33:58,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "eb_MainBase"

#include  <popa7.h>
#include  <fileacc.h>
#include  <sEBI.hpp>
#include  <sEBRootBase.hpp>
#include  <sEB_Header.hpp>
#include  <sEB_MBHeader.hpp>
#include  <sEB_Number.hpp>
#include  <sEB_extMBHeader.hpp>
#include  <iNetConversion.h>
#include  <sacb.hpp>
#include  <scte.hpp>
#include  <sctr.hpp>
#include  <seb_ClusterPool.hpp>
#include  <seb_DataArea.hpp>
#include  <seb_MainBase.hpp>
#include  <seb_SubBase.hpp>
#include  <ssrt.hpp>
#include  <seb_MainBase.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical eb_MainBase :: Add (acb *acbptr )
{
  logical       term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( !mb_outopt )                                  SDBERR(40)

  if ( acbptr->get_ebsnum().IsEmpty(pif) )              ERROR
  if ( GetEBI(acbptr) )                              ERROR

  if ( acbptr->stscold() )                           SDBERR(179)
  
  if ( acbptr->stscusr2() ) // clustered Entry
  {
    if ( cluster_pool->AddClusterEntry(acbptr) )     ERROR
  }
  else
    if ( Append(acbptr) )                            ERROR
  
  acbptr->stsrwpt(2);
  if ( PutEBI(acbptr) )                              ERROR

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  Append - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical eb_MainBase :: Append (acb *acbptr )
{
  uint32                  len;
  logical                 term = NO;
BEGINSEQ
  mb_lock.ILock();
  
  if ( pif && !acbptr->IsPIF() )                     SDBERR(99)
    
  if ( acbptr->get_mb_ebsnum().get_ebsnum() == 1 || acbptr->stscusr1() ) // oder cluster
    len = acbptr->get_entry_length();
  else
    len = acbptr->GetLength()+IEH;
  
  if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )                        // nicht DBHeader
    acbptr->get_acbieh().ToPIF(pif);
  acbptr->SetPosition((sub_bases+acbptr->get_sb_number())->Append(len,acbptr->get_entry_length(),USHORTMAX,&acbptr->get_acbieh()));
  if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )                        // nicht DBHeader
    acbptr->get_acbieh().FromPIF(pif);
  if ( !acbptr->GetPosition() )
                                                     ERROR
  acbptr->SetDANumber((sub_bases+acbptr->get_sb_number())->GetActDA());

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CheckEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical eb_MainBase :: CheckEBI (acb *acbptr )
{
  EBI     emp_ebi;
  logical term = NO;
BEGINSEQ
  mb_lock.ILock();
//if ( acbptr->get_mb_ebsnum() <= mb_header->get_last_EBS_num() )
  if ( acbptr->get_mb_ebsnum() > mb_header->get_last_EBS_num() )
                                                     ERROR
  if ( !acbptr->stscusr3() && (!acbptr->get_ebi_position() || !acbptr->get_mod_count()) )   
    if ( mb_header->ebshigt(sub_bases,acbptr) )      ERROR

  if ( acbptr->stscdel() )                           ERROR
  
  if ( !memcmp(acbptr,&emp_ebi,sizeof(EBI)) )
  {
    acbptr->stsswpt(2);                           // new entry, 2.1.99
    acbptr->SetModCount(1);                       // 7.12.01
  }
  acbptr->set_cluster_numb(acbptr->stscusr2() 
                           ? MBNtoRBN(acbptr->GetPosition()) 
                           : EB_Number(0) );

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Check_WProtect - 


\return wptmode - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_WProtect"

uint8 eb_MainBase :: Check_WProtect (acb *acbptr )
{
  uint8   wptmode = 1;

BEGINSEQ
  mb_lock.ILock();
  if ( ebsprv(acbptr,YES) )                          ERROR
  if ( acbptr->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") ) 
                                                     LEAVESEQ

  wptmode = 2;
  if ( LockInternal(acbptr,NO))                      LEAVESEQ
  UnlockInternal(acbptr);

  wptmode = 0;
RECOVER
  wptmode = 3;
ENDSEQ
  mb_lock.IUnlock();
  return(wptmode);

}

/******************************************************************************/
/**
\brief  ClearEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearEBI"

logical eb_MainBase :: ClearEBI (acb *acbptr )
{
  logical term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( acbptr->GetPosition() > mb_header->get_next_position() )
                                                     SDBERR(41)
  acbptr->Clear();
  if ( mb_header->ebshipt(sub_bases,acbptr) )        ERROR
RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical eb_MainBase :: Close ( )
{
  logical   term = NO;

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  delete cluster_pool;
  cluster_pool = NULL;
  
  if ( mb_header )
  {
    mb_header->Close(sub_bases);
    if ( mb_number && mb_header->stscmod() )
      mb_header->Write();
  }

  if ( sub_bases )
    while ( number_sb-- )
      (sub_bases+number_sb)->Close();

  delete[] sub_bases;
  sub_bases = NULL;

  if ( mb_number > 0 )
    delete mb_header;
  mb_header = NULL;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 


\return term - Termination code

\param  sourcemain - 
\param  consol_appl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical eb_MainBase :: Copy (eb_MainBase *sourcemain, logical consol_appl )
{
  uint64     i;
  uint64     maxnum;
  uint64     previous;
  int32      len = 65000+ACB;
  char      *area = new char[len];
  acb       *acbptr = (acb *)area;
  acb        new_acb(0,0);
  EB_Number  clnumb;
  int32      j = 0;
  char       ebistring[64];
  logical    ignore = NO;
  logical    term = NO;
BEGINSEQ
  memset(ebistring,' ',sizeof(ebistring));
  ebistring[sizeof(ebistring)-1] = 0;
  if ( consol_appl )
    printf("Copying MainBase %l\n\r",(int16)mb_number);
   
  SetNetOpt(YES); // machen wir, um EBI-Buffer zu deaktivieren
   
  maxnum = sourcemain->get_mb_header()->get_last_EBS_num().get_ebsnum();
  
  if ( !acbptr )                                     SDBERR(95)
  memset(acbptr,0,len);
  acbptr->set_mb_number(mb_number);
  for ( i=1; i <= maxnum; i++)
  {  
    SDBRESET;
    if ( consol_appl && (i%1000) == 1 )
      printf(".");
 
    acbptr->set_ebsnum(BigToPIF(i,pif));
    acbptr->set_mb_ebsnum(RBNtoMBN(acbptr->get_ebsnum().get_ebsnum()));
    if ( !sourcemain->GetEBI(acbptr,NO) )
    {
      if ( len < acbptr->get_entry_length() )
      {
        len = acbptr->get_entry_length() + 16*1024;
        delete area;
        if ( !(area = new char [len] ) )             SDBERR(95)
        acbptr = (acb *)area;
        memset(acbptr,0,len);
        acbptr->set_mb_number(mb_number);
        acbptr->set_ebsnum(BigToPIF(i,pif));
        acbptr->set_mb_ebsnum(RBNtoMBN(acbptr->get_ebsnum().get_ebsnum()));
        sourcemain->GetEBI(acbptr,NO);
      }

      previous = acbptr->get_version_list();

if ( !acbptr->GetPosition() )
  acbptr->stsswpt(2);      
      if ( acbptr->stscdel() || acbptr->NewEntry() ) 
      {
        ++j;
        if ( acbptr->stscdel() ) 
        {
          acbptr->SetVersionList(0);
          if ( Create(acbptr).IsEmpty(pif) )            ERROR
          if ( previous )
            CopyPrevious(sourcemain,acbptr,previous);
        }
        else
        {
          acbptr->set_version_number(acbptr->get_version());
          new_acb = *acbptr;
          if ( !Create(&new_acb).IsEmpty(pif) ) 
            PutEBI(&new_acb);
        }
      }
      else
      {
        acbptr->set_version_number(acbptr->get_version());
        new_acb = *acbptr;
        if ( Create(&new_acb).IsEmpty(pif) )            ERROR
        if ( !acbptr->stscusr2() )  // clustered entry 
        {
          if ( sourcemain->Locate(acbptr,AUTO) )
          {
            acbptr->set_ebi_position(new_acb.get_ebi_position());
            if ( i>1 && acbptr->get_entry_length() < acbptr->GetLength() + IEH )  // Autokorrektur. Kann dann wieder raus.
              acbptr->SetLength(acbptr->get_entry_length() - IEH);
            acbptr->SetVersionList(0);
            if ( Add(acbptr) )                         ERROR
            if ( previous )
              CopyPrevious(sourcemain,acbptr,previous);
          }
          else if ( consol_appl )
          {
            if ( !ignore )
            {
              printf("\n\rerror reading entry %l. Continue (y/n/a)?",i);
              switch ( getchar() )
              {
                case 'n' :                             ERROR
                case 'a' : ignore = YES;
                           break;
                case 'y' : break;
              }
              getchar();
            }
            else
            {
              gvtxlth(ebistring,*(int32 *)acbptr);
              gvtxlth(ebistring+9,*(((int32 *)acbptr)+1));
              gvtxlth(ebistring+18,*(((int32 *)acbptr)+2));
              gvtxlth(ebistring+27,*(((int32 *)acbptr)+3));
              gvtxlth(ebistring+36,*(((int32 *)acbptr)+4));
              gvtxlth(ebistring+45,*(((int32 *)acbptr)+5));
              gvtxlth(ebistring+54,*(((int32 *)acbptr)+6));
              printf("\n\rerror reading EBI %s(%d). ",ebistring,i);
            }
          }
        }
      }
    }
  }

  if ( consol_appl )
  {
    printf("\nMainBase copied successfully");
    printf("\nMainBase contains %d entries.",i-1); 
    printf("%d are not used\n",j); 
  }
RECOVER
  term = YES;
ENDSEQ
  delete area;
  return(term);
}

/******************************************************************************/
/**
\brief  CopyPrevious - 


\return term - Termination code

\param  sourcemain - 
\param  acbptr - 
\param  previous - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyPrevious"

logical eb_MainBase :: CopyPrevious (eb_MainBase *sourcemain, acb *acbptr, int64 previous )
{
  uint64     position;
  int32      len;
  acb       prev_acb(0,0);
  char      string[33];
  logical   term = NO;
BEGINSEQ
  len = acbptr->get_entry_length();  
  prev_acb = *acbptr;                                // acb, mit dem gerade geschrieben wurde
  acbptr->set_ebi_position(previous);
  if ( sourcemain->GetEBI(acbptr,YES) )              ERROR
  if ( sourcemain->ValidateEBI(acbptr) )
  {               
    SDBError().TraceMessage("Last Version accessed: ",gvtxitoa(prev_acb.get_version(),string,10));
    ERROR
  }
  if ( !(position = acbptr->CreatePrevVersion(sub_bases,acbptr->get_version(),pif)) )
                                                     ERROR
  prev_acb.SetVersionList(position);
  prev_acb.ToPIF(pif);
  sub_bases->Update(0,prev_acb.get_ebi_position(),S_EBI,&prev_acb);
  prev_acb.FromPIF(pif);
  
  // für clustered entries ist hier schluss, Cluster werden nicht versioniert
  if ( acbptr->stscusr2() )                          LEAVESEQ 
  
  // jetzt müssen wir noch mal lesen
  acbptr->set_ebi_position(previous);
  sourcemain->GetEBI(acbptr,YES);
  previous = acbptr->get_version_list();
  
  // wir bekommen die maximale entry-size nicht raus
//  if ( len < acbptr->get_entry_length() )          SDBERR(99)
  
  if ( acbptr->NewEntry() )                          LEAVESEQ
  if ( sourcemain->Locate(acbptr,AUTO) )
  {
    acbptr->set_ebi_position(position);
    acbptr->SetVersionList(0);
    if ( Append(acbptr) )                            ERROR
    acbptr->ToPIF(pif);
    term = sub_bases->Update(0,position,S_EBI,acbptr);
    acbptr->FromPIF(pif);
    if ( term )                                      ERROR
  }
  
  if ( previous )
    CopyPrevious(sourcemain,acbptr,previous);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 


\return entnr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  sbnumber - SubBase number
\param  clnumb - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number eb_MainBase :: Create (uint16 sbnumber, EB_Number clnumb, uint16 version_nr )
{
  EB_Number     entnr(0);
  acb           acbenty(0,clnumb);
  logical       extlock;

BEGINSEQ
  mb_lock.ILock();
  extlock = mb_header->stsclck();
  
  if ( !mb_outopt )                                 SDBERR(40)
  if ( sbnumber >= number_sb )                      SDBERR(45)

  if ( !extlock )
    if ( mb_header->Lock() )                        ERROR
  
  if ( (entnr = GetNewEBNumber()).IsEmpty() )       ERROR
  acbenty.set_ebsnum(MBNtoRBN(entnr));
  acbenty.get_mb_ebsnum() = entnr;
  acbenty.set_mb_number(mb_number);
  acbenty.SetSBNumber(sbnumber);
  acbenty.stsswpt(2);                 // indicates new entry
  
  if ( !clnumb.IsEmpty(pif) )
  {
    acbenty.stssusr1();
    if ( PutEBI(&acbenty) )             	    ERROR
    clnumb = entnr;
    if ( (entnr = GetNewEBNumber()).IsEmpty(pif) )     ERROR
    
    acb       tacb(MBNtoRBN(entnr),clnumb);
    acbenty = tacb;
    acbenty.get_mb_ebsnum() = entnr;
    acbenty.set_mb_number(mb_number);
    acbenty.SetSBNumber(sbnumber);
    acbenty.stsswpt(2);                 // indicates new entry
  }
  
  acbenty.set_cluster_numb(MBNtoRBN(clnumb));
  if ( clnumb.get_ebsnum() )
  {
    acbenty.stssusr2();
    acbenty.SetPosition(clnumb.get_ebsnum());
  }
  
  acbenty.SetVersion(version_nr != USHORTMAX ? version_nr : 0);
  if ( PutEBI(&acbenty) )             		    ERROR

RECOVER
  entnr = 0;
ENDSEQ
  if ( !extlock )
    mb_header->Unlock();
  mb_lock.IUnlock();
  return(entnr);

}

/******************************************************************************/
/**
\brief  i1 - 


\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number eb_MainBase :: Create (acb *acbptr )
{
  EB_Number     entnr;
  logical       extlock;
BEGINSEQ
  mb_lock.ILock();
  extlock = mb_header->stsclck();
  
  if ( !mb_outopt )                                  SDBERR(40)
  if ( acbptr->get_sb_number() >= number_sb)         SDBERR(45)
  if ( acbptr->get_ebsnum().IsEmpty(pif) )           SDBERR(99)
  CheckEBI(acbptr);   // früher Err 99 bei Fehler - 12.09.01
  
  if ( !extlock )
    if ( mb_header->Lock() )                          ERROR
  
  acbptr->SetDANumber(0);
  acbptr->set_ebi_position(0);
  acbptr->get_mb_ebsnum() = RBNtoMBN(acbptr->get_ebsnum());
  mb_header->SetLastNum(acbptr->get_mb_ebsnum().get_ebsnum());
  if ( !acbptr->stscusr2() )
  {
    acbptr->SetPosition(0);
    acbptr->stsswpt(2);              // new entry
  }
  acbptr->SetModCount(0);
  
  acbptr->SetVersion(acbptr->get_version_number() != USHORTMAX ? acbptr->get_version_number() : 0);
  if ( PutEBI(acbptr) )                               ERROR
  
  entnr = acbptr->get_ebsnum();
RECOVER
  entnr = 0;
ENDSEQ
  if ( !extlock )
    mb_header->Unlock();
  mb_lock.IUnlock();
  return(entnr);
}

/******************************************************************************/
/**
\brief  CreateNewVersion - 


\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNewVersion"

logical eb_MainBase :: CreateNewVersion (acb *acbptr, int32 entlen, uint16 version_nr )
{
  EBI                     save_ebi;
  logical                 term = NO;
BEGINSEQ
  mb_lock.ILock();
  save_ebi = *acbptr;
  if ( acbptr->CreateVersionEBI(sub_bases,version_nr,pif) )
                                                     ERROR
  if ( !acbptr->NewEntry() )  // not a new entry
  {
    if ( acbptr->stscusr2() )    // ClusterEntries werden entclustert (vorerst) !!!!!!!!!!!!
      acbptr->stsrusr2();       
    if ( entlen && entlen > acbptr->get_entry_length() )
      acbptr->SetEBILen(entlen);
    if ( entlen > 0 )
      if ( Append(acbptr) )                          ERROR
    if ( PutEBI(acbptr) )                            ERROR
  }
RECOVER
  *(EBI *)acbptr = save_ebi;
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical eb_MainBase :: Delete (acb *acbptr )
{
  logical       term = NO;

BEGINSEQ
  mb_lock.ILock();
  if ( !mb_outopt )                                  SDBERR(40)

  if ( ebsprv(acbptr,YES) )                          ERROR
  if ( acbptr->stscold() )                           SDBERR(180)
  
//  if ( acbptr->stscdel() )                         SDBIERR(3)
  if ( acbptr->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y"))
                                                     SDBIERR(47)
  if ( acbptr->stscusr1() )                          SDBERR(48)

  if ( acbptr->get_sb_number() >= number_sb)         SDBERR(45)
  
  if ( acbptr->get_version_number() != CUR_VERSION && 
       acbptr->get_version_number() >  acbptr->get_version()  )
  {
    if ( acbptr->CreateVersionEBI(sub_bases,acbptr->get_version_number(),pif) )
                                                     ERROR
  }
  else
  {
    if ( Remove(acbptr) )                            ERROR
    if ( acbptr->stscusr2() && !acbptr->NewEntry() )
      if ( cluster_pool->DelClusterEntry(acbptr) )   ERROR
  }
  
  acbptr->stssdel();
  acbptr->stsrwpt(2);
  if ( PutEBI(acbptr) )                                ERROR
RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteVersion - 


\return term - Termination code

\param  acbptr - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteVersion"

logical eb_MainBase :: DeleteVersion (acb *acbptr, uint16 version_nr )
{
  EBI                     save_ebi;
  logical                 term = NO;
BEGINSEQ
  mb_lock.ILock();
  save_ebi = *acbptr;

  while ( acbptr->get_version() >= version_nr )
  {
    if ( Remove(acbptr) )                            ERROR
    if ( acbptr->DeleteVersionEBI(sub_bases) )       ERROR
  }
  term = PutEBI(acbptr);

RECOVER
  *(EBI *)acbptr = save_ebi;
  acbptr->ResetVersionList();
  PutEBI(acbptr);
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ExistEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistEBI"

logical eb_MainBase :: ExistEBI (acb *acbptr )
{
  EBI              emp_ebi;
  logical          cond = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( mb_header->ebshigt(sub_bases,acbptr) )        ERROR
    
  if ( !memcmp(acbptr,&emp_ebi,sizeof(EBI)) )        ERROR
  cond = YES;
RECOVER

ENDSEQ
  mb_lock.IUnlock();
  return(cond);
}

/******************************************************************************/
/**
\brief  Flush - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical eb_MainBase :: Flush ( )
{
  int         sbnumber = number_sb;
  logical     term     = NO;
  mb_lock.ILock();
  
  if ( sub_bases )
    while ( sbnumber-- )
      (sub_bases+sbnumber)->Flush();

  if ( mb_number && mb_header->stscmod() )
    mb_header->Write();
  
  mb_lock.IUnlock();

  return(term);
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

logical eb_MainBase :: FlushCluster (acb *acbptr )
{
  logical     term     = NO;
  mb_lock.ILock();
  term = cluster_pool->FlushCluster(acbptr);
  mb_lock.IUnlock();


  return(term);
}

/******************************************************************************/
/**
\brief  FlushClusterPool - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical eb_MainBase :: FlushClusterPool ( )
{
  logical     term     = NO;
  mb_lock.ILock();
  term = cluster_pool->Flush();
  mb_lock.IUnlock();

  return(term);
}

/******************************************************************************/
/**
\brief  GetDataVersion - 


\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataVersion"

int16 eb_MainBase :: GetDataVersion ( )
{

  return(mb_header->get_version());

}

/******************************************************************************/
/**
\brief  GetEBI - 


\return term - Termination code

\param  acbptr - 
\param  real - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

logical eb_MainBase :: GetEBI (acb *acbptr, logical real )
{
  EBI     emp_ebi;
  logical term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( real || !acbptr->get_ebi_position() || !acbptr->get_mod_count() )   
    if ( mb_header->ebshigt(sub_bases,acbptr) )      SDBERR(7)
  
  if ( !memcmp(acbptr,&emp_ebi,sizeof(EBI)) )
  {
    acbptr->stsswpt(2);                           // new entry
    acbptr->SetModCount(1);                       
  }
  
  acbptr->set_cluster_numb(acbptr->stscusr2() ? MBNtoRBN(acbptr->GetPosition()) : EB_Number(0));

  acbptr->stsrusr3();  // reset "EBI in buffer"
RECOVER
  if ( SDBERROR )
    PrintMessage(acbptr);
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  GetNewEBNumber - 


\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewEBNumber"

EB_Number eb_MainBase :: GetNewEBNumber ( )
{
  EB_Number     entnr;
BEGINSEQ
  mb_lock.ILock();
  if ( (entnr = mb_header->ebshngt(sub_bases)).IsEmpty() )
                                                     ERROR

RECOVER

ENDSEQ
  mb_lock.IUnlock();
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetNextEBNumber - 


\return entnr - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextEBNumber"

EB_Number eb_MainBase :: GetNextEBNumber (EB_Number entnr )
{
  uint64        ebsidbp;
  EBI           ebi_area;
  EBI           emp_ebi;
BEGINSEQ
  while ( ebsidbp = mb_header->GetNextEBNumber(sub_bases,entnr) )
  {
    if ( !sub_bases->Locate(0,ebsidbp,S_EBI,&ebi_area) )     
                                                     ERROR
    if ( memcmp(&ebi_area,&emp_ebi,sizeof(EBI)) )    LEAVESEQ
  }
 
  ERROR
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetPrevInstance - 


\return term - Termination code

\param  acbptr - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevInstance"

logical eb_MainBase :: GetPrevInstance (acb *acbptr, uint16 version_nr )
{
  EBI                     save_ebi;
  logical                 term = NO;
BEGINSEQ
  save_ebi = *acbptr;
  if ( acbptr->GetPrevEBI(sub_bases,version_nr,pif) )ERROR
  
  if ( !Locate(acbptr,AUTO) )                        ERROR
RECOVER
  *(EBI *)acbptr = save_ebi;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetSubBase - 


\return subbase - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubBase"

eb_SubBase *eb_MainBase :: GetSubBase (int32 indx0 )
{
  eb_SubBase        *subbase = NULL;
BEGINSEQ
  if ( indx0 >= number_sb )                          ERROR
    
  subbase = sub_bases+indx0;                  

RECOVER

ENDSEQ
  return(subbase);
}

/******************************************************************************/
/**
\brief  GetVersionNumber - 


\return version_nr - Internal version number

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionNumber"

int32 eb_MainBase :: GetVersionNumber (acb *acbptr )
{

  return(acbptr->get_version());

}

/******************************************************************************/
/**
\brief  Get_Length - 


\return entlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Length"

int32 eb_MainBase :: Get_Length (acb *acbptr )
{
  int32      length = 0;
BEGINSEQ
  mb_lock.ILock();
/*  
  if ( !acbptr->get_cluster_number().IsEmpty(pif) )
    length = cluster_pool->GetEntryLength(acbptr);
  else
  {
    if ( ebsprv(acbptr) )                                ERROR
    length= acbptr->get_entry_length();
  }
*/
  if ( ebsprv(acbptr) )                                ERROR
  length= acbptr->get_entry_length();

RECOVER

ENDSEQ
  mb_lock.IUnlock();
  return(length);

}

/******************************************************************************/
/**
\brief  Get_Mod - 


\return modcnt - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Mod"

uint16 eb_MainBase :: Get_Mod (acb *acbptr )
{
  acb           acbenty(0,0);
  uint16        modcnt = 0;
BEGINSEQ
  mb_lock.ILock();
  acbenty = *acbptr;
  if ( GetEBI(&acbenty,YES) )                        ERROR
  
  if ( !acbenty.CheckVersion() )
    *acbptr = acbenty;
  else
  {
    if ( !acbptr->stscold() )
      ebsprv(acbptr,YES);
    acbptr->SetModCount(acbenty.get_mod_count());
  }
  
  if ( acbptr->stscdel() )                         SDBERR(3)
// kann fuer die oberste mvl im icb nach loeschen des letzten passieren    
  modcnt = acbptr->get_mod_count();


RECOVER

ENDSEQ
  mb_lock.IUnlock();
  return(modcnt);

}

/******************************************************************************/
/**
\brief  InitHeader - 


\return term - Termination code

\param  sbnumber - SubBase number
\param  pheader - 
\param  filename - File name for DataArea file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHeader"

logical eb_MainBase :: InitHeader (uint16 sbnumber, EB_Header *pheader, char *filename )
{
  eb_DataArea     *dataarea = GetDataArea0();
  EBSubBase        sbentry(NULL);
  EBSubBase        sbnew(filename);
  uint64           position;
  logical          term = NO;
BEGINSEQ
  if ( sbnumber != AUTO )
  {
    if ( sbnumber >= number_sb )                      SDBERR(45)                  
    if ( (sub_bases+sbnumber)->InitHeader(pheader,filename) )
                                                      ERROR
    LEAVESEQ
  }

  if ( dataarea->Read(mb_header->get_header_length(),sizeof(EBSubBase),&sbentry) )
                                                      SDBERR(30)
  sbnumber = 1;
  position = mb_header->get_header_length();
  while ( sbentry.get_next_sb() )
  {
    position = sbentry.get_next_sb();
    sbnumber++;
    if ( dataarea->Read(position,sizeof(EBSubBase),&sbentry) )
                                                      SDBERR(31)
  }
  if ( !sbentry.SetNext(dataarea->Append(sizeof(EBSubBase),sizeof(EBSubBase),&sbnew)) )
                                                      ERROR
  mb_header->Lock();
  mb_header->set_sb_count(mb_header->get_sb_count()+1);
  mb_header->stssmod();
  mb_header->Unlock();
  if ( dataarea->Write(position,sizeof(EBSubBase),&sbentry) )
                                                      ERROR
  if ( eb_DataArea::InitFile(pheader,&sbnew,sizeof(EBDataArea)) )
                                                      ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Locate - 


\return area - 

\param  acbptr - 
\param  entlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *eb_MainBase :: Locate (acb *acbptr, int32 entlen )
{
  void         *area = &acbptr->get_acbieh();
BEGINSEQ
  mb_lock.ILock();
  SDBRESET
  
  if ( ebsprv(acbptr) )                              ERROR
      
  if ( acbptr->NewEntry() )                          LEAVESEQ
  
  entlen = entlen == AUTO ? acbptr->get_entry_length() : MIN(entlen,acbptr->get_entry_length());
  
  if ( !entlen && acbptr->GetPosition() && !acbptr->stscusr2() )      // autokorrektur
  {
    *(EBI *)acbptr = EBI();
    acbptr->stsswpt(2);                 // indicates new entry
    if ( mb_outopt )
      PutEBI(acbptr);
    SDBSET(42)
    SDBRESET
    LEAVESEQ
  }

  if ( !acbptr->get_cluster_number().IsEmpty(pif) )
    if ( cluster_pool->GetClusterEntry(acbptr,entlen) )
      LEAVESEQ                 
  
  if ( acbptr->stscusr2() )
  {
    if ( !cluster_pool->GetClusterEntry(acbptr,entlen) )
                                                    SDBERR(42)
    LEAVESEQ
  }  
  
  if ( !(sub_bases+acbptr->get_sb_number())->
    Locate(acbptr->get_da_number(),acbptr->GetPosition(),entlen,&acbptr->get_acbieh()) )
                                                     ERROR
  if ( pif )
  {
    if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )      // nicht DBHeader
      acbptr->get_acbieh().FromPIF(pif);
    acbptr->SetPIF();
  }
RECOVER
  if ( SDBERROR )
    PrintMessage(acbptr);
  area = NULL;
ENDSEQ
  mb_lock.IUnlock();
  return(area);

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical eb_MainBase :: Lock (acb *acbptr, logical wait )
{
  logical   term = NO;

BEGINSEQ
  mb_lock.ILock();
  if ( mb_header->ebshilk(sub_bases,acbptr,wait) )   SDBERR(6)
//TraceLock(acbptr,YES);
RECOVER
  if ( SDBERROR )
    PrintMessage(acbptr);
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  LockInternal - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical eb_MainBase :: LockInternal (acb *acbptr, logical wait )
{
  logical   term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( acbptr->get_mb_ebsnum().IsEmpty() )           ERROR

  if ( mb_header->LockInternal(acbptr->get_mb_ebsnum().GetLockPos(),1,wait) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  MBNtoRBN - 


\return entnr - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MBNtoRBN"

EB_Number eb_MainBase :: MBNtoRBN (EB_Number entnr )
{
  uint64     ebsnum = entnr.get_ebsnum();

  if ( !entnr.IsEmpty(NO) )
  {
    ebsnum += (((uint64)mb_number)<<48);
    ebsnum = BigToPIF(ebsnum,pif);
  }
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  mbheader - 
\param  path - 
\param  outopt - 
\param  netopt - Multi-user access
\param  sysenv - System application
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical eb_MainBase :: Open (EB_MBHeader *mbheader, char *path, logical outopt, logical netopt, char sysenv, logical pif_opt )
{
  eb_SubBase      subbase;
  EBSubBase       sbentry(NULL);
  uint64          position;
  int16           sbnumber = 0;
  logical         term     = NO;
  int16           errsav;
BEGINSEQ
  sys_application = sysenv;
  mb_outopt = outopt;
  mb_netopt = netopt;
  
  if ( mbheader )
    mb_header = mbheader;
  else
    mb_header = new EB_MBHeader(sizeof(EB_extMBHeader),netopt);
  
  if ( subbase.Open(mb_header,path,outopt,netopt,pif_opt) )
                                                     ERROR
  mb_number    = mb_header->get_mb_number();
  pif = mbheader ? mbheader->get_platform_indep() : pif_opt;
  
  if ( mb_header->Open() )                           ERROR

  if ( !subbase.Locate(0,mb_header->get_header_length(),sizeof(EBSubBase),&sbentry) )
                                                      SDBERR(33)
  sbentry.FromPIF(pif);
  sub_bases = new eb_SubBase[number_sb = mb_header->get_sb_count()];
  *sub_bases = subbase;

  while ( position = sbentry.get_next_sb() )
  {
    sbnumber++;
    if ( !subbase.Locate(0,position,sizeof(EBSubBase),&sbentry) )
                                                     SDBERR(33)
    sbentry.FromPIF(pif);
    (sub_bases+sbnumber)->Open(NULL,sbentry.get_file_name(),outopt,netopt,pif);
  }

/*
  if ( dsmopt  &&  outopt == WT )
  {
    ebshdsm = (dsmopt==' ' ? UNDEF : dsmopt);
    ebshmod = YES;
  }  
*/   
  if ( VersionCheck() )                              ERROR
    
  if ( mb_number )
    if ( mb_header->Write() )                         ERROR

  if ( !(cluster_pool = new eb_ClusterPool(this)) )   SDBERR(95)
                                                      SDBCERR
  SDBRESET
RECOVER
  errsav = SDBERROR;
  Close();
  term = YES;
  SDBISET(errsav);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenTemp - 


\return term - Termination code

\param  mbnumber - MainBase number
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenTemp"

logical eb_MainBase :: OpenTemp (int16 mbnumber, logical pif_opt )
{
  eb_SubBase      subbase;
  EBSubBase       sbentry(NULL);
  int16           sbnumber = 0;
  logical         term     = NO;
  int16           errsav;
BEGINSEQ
  sys_application = NO;
  mb_outopt       = YES;
  mb_netopt       = NO;
  pif             = pif_opt;
  
  mb_number = mbnumber;
  mb_header = new EB_MBHeader(sizeof(EB_extMBHeader),NO);

  if ( subbase.Open(mb_header,"*_temp",YES,NO) )     ERROR
    
  if ( mb_header->Open() )                           ERROR
  
  sub_bases = new eb_SubBase[number_sb = mb_header->get_sb_count()];
  *sub_bases = subbase;

  mb_header->stssmod();
  if ( mb_header->Write() )                          ERROR

  if ( !(cluster_pool = new eb_ClusterPool(this)) )  SDBERR(95)
                                                     SDBCERR
  SDBRESET
RECOVER
  errsav = SDBERROR;
  Close();
  term = YES;
  SDBISET(errsav);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PrintMessage - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrintMessage"

logical eb_MainBase :: PrintMessage (acb *acbptr )
{
  char                    sid[33];
  char                    type[33];
  char                    size[33];
  char                    ebsnum[33];
  char                    string[33];
  logical                 term = NO;
  strcpy(ebsnum,"Number: ");
  strcpy(sid,"; SID: ");
  strcpy(type,"; Type: ");
  strcpy(size,"; Size: ");
  
  gvtxitoa(acbptr->get_entry_length(),string,10);
  strcat(size,string);
  gvtxbtoa(acbptr->get_mb_ebsnum().get_ebsnum(),string,10);
  strcat(ebsnum,string);
  
  if ( acbptr->GetPosition() > 0 && acbptr->get_acbieh().get_iehlen() >= 8 )
  {
    gvtxitoa(acbptr->get_acbieh().get_iehsid(),string,10);
    strcat(sid,string);
    gvtxitoa(acbptr->get_acbieh().get_iehtyp(),string,10);
    strcat(type,string);
  }
  else
  {
    strcat(sid,"unknown");
    strcat(type,"unknown");
  }
  SDBError().TraceMessage(ebsnum,sid,type,size);
  return(term);
}

/******************************************************************************/
/**
\brief  PutEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutEBI"

logical eb_MainBase :: PutEBI (acb *acbptr )
{
  logical term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( acbptr->GetPosition() > mb_header->get_next_position() )
                                                     SDBERR(41)
  acbptr->stsrusr3();  // reset "EBI in buffer"
  acbptr->IncModCount();
  if ( mb_header->ebshipt(sub_bases,acbptr) )        ERROR
RECOVER
  if ( SDBERROR )
    PrintMessage(acbptr);
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  RBNtoMBN - 


\return entnr - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RBNtoMBN"

EB_Number eb_MainBase :: RBNtoMBN (EB_Number entnr )
{
  uint64     ebsnum = (uint64)PIFToBig(entnr.get_ebsnum(),pif);

BEGINSEQ
  if ( EB_Number(ebsnum).IsEmpty() )                 LEAVESEQ
  if ( EB_Number(ebsnum).IsEmpty(NO) )               ERROR
  ebsnum = (ebsnum << 16) >> 16;
RECOVER
  ebsnum = 0;
ENDSEQ
  return(ebsnum);
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

logical eb_MainBase :: ReleaseCluster (acb *acbptr )
{
  logical     term     = NO;
  mb_lock.ILock();
  term = cluster_pool->ReleaseCluster(acbptr);
  mb_lock.IUnlock();


  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical eb_MainBase :: Remove (acb *acbptr )
{
  logical                 term = NO;
BEGINSEQ
  mb_lock.ILock();
  switch ( (sub_bases+acbptr->get_sb_number())->Delete(acbptr->get_da_number(),acbptr->GetPosition()) )
  {
    case  YES :                                      ERROR
    case  NO  : acbptr->SetDANumber(0);
                acbptr->SetPosition(0);
                break;
    case AUTO : ;
  }
                                                     

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical eb_MainBase :: Reserve (acb *acbptr, logical wait )
{
  logical       term = NO;

BEGINSEQ
  mb_lock.ILock();
  if ( ebsprv(acbptr,YES) )                          ERROR

  if ( (acbptr->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y"))
       || LockInternal(acbptr,wait) ) 
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  ResetSize - 


\return term - Termination code

\param  sb_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSize"

logical eb_MainBase :: ResetSize (int32 sb_number )
{

  return(sub_bases[sb_number].ResetSize(0));


}

/******************************************************************************/
/**
\brief  SaveBuffer - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveBuffer"

logical eb_MainBase :: SaveBuffer ( )
{
  logical                 term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( mb_header->SaveBuffer(sub_bases,AUTO) )       ERROR
  if ( !mb_netopt )
    mb_header->Write();
RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  SetNetOpt - 


\return term - Termination code

\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNetOpt"

logical eb_MainBase :: SetNetOpt (logical netopt )
{
  int32                    sbn = number_sb;
  logical                 term = NO;
  mb_netopt = netopt;

  if ( sub_bases && sbn > 0 )
    while ( sbn-- )
      (sub_bases+sbn)->SetNetOpt(netopt);

  return(term);
}

/******************************************************************************/
/**
\brief  TraceLock - 


\return term - Termination code

\param  acbptr - 
\param  lock_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceLock"

logical eb_MainBase :: TraceLock (acb *acbptr, logical lock_opt )
{
  static int              count = 0;
  char                    string[255];
  char                    cnum[22];
  logical                 term = NO;
if ( pif && acbptr->get_mb_ebsnum().get_ebsnum() == 4 )
{  
  strcpy(string,lock_opt ? "LOCK   : " :
                           "UNLOCK : "   );
  gvtxbtoa(acbptr->get_ebsnum().get_ebsnum(),cnum,10);
  strcat(string,cnum);
  
  strcat(string,"   count : ");
  count += lock_opt ? -1 : 1;
  gvtxitp(strcpy(cnum,"999"),count,3);
  strcat(string,cnum);
  SDBError().TraceMessage(string);
}
  return(term);
}

/******************************************************************************/
/**
\brief  Undelete - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Undelete"

logical eb_MainBase :: Undelete (acb *acbptr )
{
  logical   term = NO;

BEGINSEQ
  mb_lock.ILock();
  if ( !mb_outopt )                                  SDBIERR(40)
  if ( Lock(acbptr,NO) )                             ERROR

  acbptr->set_ebi_position(0);
  CheckEBI(acbptr);

  if ( !acbptr->stscdel() )                          SDBIERR(3)
  acbptr->stsrdel();

  if ( PutEBI(acbptr) )                              ERROR
RECOVER
  term = YES;
ENDSEQ
  Unlock(acbptr);
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical eb_MainBase :: Unlock (acb *acbptr )
{
  logical   term = NO;

BEGINSEQ
  mb_lock.ILock();
  if ( mb_header->ebshiul(sub_bases,acbptr) )         SDBERR(6)
//TraceLock(acbptr,NO);
RECOVER
  if ( SDBERROR )
    PrintMessage(acbptr);
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

}

/******************************************************************************/
/**
\brief  UnlockInternal - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical eb_MainBase :: UnlockInternal (acb *acbptr )
{
  logical    term = NO;
BEGINSEQ
  mb_lock.ILock();
  if ( acbptr->get_mb_ebsnum().IsEmpty() )           ERROR

  if ( mb_header->UnlockInternal(acbptr->get_mb_ebsnum().GetLockPos(),1) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Update - 


\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical eb_MainBase :: Update (acb *acbptr, int32 entlen, int32 offset )
{
  int32          oldlen = acbptr->get_entry_length();
  logical       modopt = NO;
  logical       term   = NO;

BEGINSEQ
  mb_lock.ILock();
  if ( !mb_outopt )                                  SDBERR(40)  // war SDBIERR
  if ( entlen < 0  )                                 SDBERR(9)   // war SDBIERR
  if ( acbptr->stscres() )      
    entlen = 0;
  if ( pif && !acbptr->IsPIF() && offset <= 0 && entlen )      
                                                     SDBERR(99)

  if ( acbptr->stscmod() ) // EBI gesperrt/modifiziert, neu setzen
  {
    acbptr->stsrmod();
    modopt = YES;
  }
  else
    if ( ebsprv(acbptr,NO) )                         ERROR

  if ( acbptr->stscold() )                           SDBERR(179)
    
  if ( acbptr->get_version_number() != USHORTMAX && 
       acbptr->get_version_number() > acbptr->get_version()       )
    if ( CreateNewVersion(acbptr,offset > 0 ? entlen+offset : entlen,acbptr->get_version_number()) )    
                                                     ERROR

  if ( acbptr->stscres() )    // ResetEBI
  {
    acbptr->stsrres();
    acbptr->stsswpt(2);
    // something missing for release area ...
    PutEBI(acbptr);                                 LEAVESEQ
  }

  if ( acbptr->NewEntry() && entlen > 0 )  // create new entry
  {
//    acbptr->SetEBILen(MAX(entlen,acbptr->GetLength()+IEH)); geht nicht, da im db_header kein ieh steht
    acbptr->SetEBILen(entlen);
    if ( Add(acbptr) )                               ERROR
    LEAVESEQ
  }
  
  if ( !modopt && acbptr->stscdel() )                SDBERR(3) 
  if ( !modopt && acbptr->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") )
                                                     SDBERR(6) 

  if ( entlen > 0 )
  {
    if ( acbptr->stscusr2() )
    {
      if ( cluster_pool->PutClusterEntry(acbptr,entlen,offset) )   
                                                     ERROR
    }
    else
      if ( ebseupd(acbptr,entlen,offset) )             ERROR
  }
  
  if ( acbptr->stscmod() ) // EBI modifiziert
  {
    acbptr->stsrmod();
    modopt = YES;
  }
  if ( acbptr->get_entry_length() != oldlen || mb_netopt || modopt )
    PutEBI(acbptr);

RECOVER
  term = YES;
ENDSEQ
  mb_lock.IUnlock();
  return(term);

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

logical eb_MainBase :: UseCluster (acb *acbptr )
{
  logical     term     = NO;
  mb_lock.ILock();
  term = cluster_pool->UseCluster(acbptr);
  mb_lock.IUnlock();



  return(term);
}

/******************************************************************************/
/**
\brief  ValidateEBI - 


\return term - Termination code

\param  ebiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateEBI"

logical eb_MainBase :: ValidateEBI (EBI *ebiptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( ebiptr->GetPosition() + ebiptr->get_entry_length() > mb_header->get_next_position() )
                                                     SDBERR(41)
  if ( ebiptr->get_version_list() > mb_header->get_next_position() )
                                                     SDBERR(41)
  if ( ebiptr->get_sb_number() > number_sb ) SDBERR(41)

  if ( ebiptr->get_da_number() > sub_bases[ebiptr->get_sb_number()].get_number_da() )
                                                     SDBERR(41)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Version1 - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version1"

logical eb_MainBase :: Version1 ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( mb_header->get_version() >= 1 )               LEAVESEQ
  if ( !mb_outopt )                                  SDBERR(175)
  
  if (mb_header->Version1(sub_bases))                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Version2 - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version2"

logical eb_MainBase :: Version2 ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( mb_header->get_version() >= 2 )               LEAVESEQ
  if ( !mb_outopt )                                  LEAVESEQ
    //SDBERR(175)
  
  if (mb_header->Version2(sub_bases))                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Version3 - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version3"

logical eb_MainBase :: Version3 ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( mb_header->get_version() >= 3 )               LEAVESEQ
  if ( !mb_outopt )                                  SDBERR(175)
  
  if (mb_header->Version3(sub_bases))                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  VersionCheck - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCheck"

logical eb_MainBase :: VersionCheck ( )
{
  logical    extlock = mb_header->stsclck();
  logical    term    = NO;
BEGINSEQ
  if ( !extlock && mb_header->Lock() )               ERROR
  if ( mb_header->get_version() > CURRENT_VERSION )  SDBERR(176)
  
  if ( Version1() || Version2() || Version3() )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( !extlock )
    mb_header->Unlock();
  return(term);
}

/******************************************************************************/
/**
\brief  WriteInitial - 


\return position - Position

\param  rbentry - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteInitial"

uint64 eb_MainBase :: WriteInitial (EBRootBase *rbentry, int32 length )
{

  return(sub_bases->Append(length,length,0,rbentry));

}

/******************************************************************************/
/**
\brief  eb_MainBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eb_MainBase"

     eb_MainBase :: eb_MainBase ( )
                     : mb_lock(YES),
mb_header(NULL),
mb_number(AUTO), sub_bases(NULL), number_sb(0), cluster_pool(NULL), sys_application(NO), mb_outopt(NO), mb_netopt(NO),
pif(NO)
{



}

/******************************************************************************/
/**
\brief  ebscdel - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebscdel"

logical eb_MainBase :: ebscdel (acb *acbptr )
{
  logical       term = NO;

BEGINSEQ
// Wird nur beim Clusterschreiben aufgerufen, Version noch nicht beachtet
  if ( GetEBI(acbptr,NO) )                              ERROR

//  if ( ebshnrl(ebsodb,clnumb) )                         ERROR
//  if ( ebsharl(ebsodb,ebsipos,ebsilen) )                ERROR
  
  acbptr->stssdel();
  if ( PutEBI(acbptr) )                                 ERROR
  
//  if ( ebshunl(ebsodb) )                                ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ebseupd - 


\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebseupd"

logical eb_MainBase :: ebseupd (acb *acbptr, int32 entlen, int32 offset )
{
  int64       position;
  int64       oldpos;
  int16       sbnumber;
  int32       oldlen;
  int32       datalen;
  int16       oldda;
  logical     mod  = NO;
  logical     term = NO;

BEGINSEQ
  oldpos   = acbptr->GetPosition();
  oldlen   = acbptr->get_entry_length();
  oldda    = acbptr->get_da_number();
  if ( (sbnumber = acbptr->get_sb_number()) >= number_sb ) 
                                                     SDBERR(45)

  if ( offset != AUTO && entlen+offset > oldlen )    SDBERR(52)
  if ( entlen <= oldlen || offset != AUTO )
  {
    if ( offset == AUTO )
      offset = 0;
    if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )      // nicht DBHeader
      acbptr->get_acbieh().ToPIF(pif);
    term = (sub_bases+sbnumber)->Update(oldda,oldpos+offset,entlen,
                                      ((char *)&acbptr->get_acbieh())+offset);
    if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )      // nicht DBHeader
      acbptr->get_acbieh().FromPIF(pif);
    if ( term )                                      ERROR
  }
  else
  {
//    if ( ebsharl(ebsodb,oldpos,oldlen) )           ERROR
//    if ( position = ebshagt(ebsodb,entlen,ebshdsm) )
//    {
//      if ( ebsodb->odbupd(area,odbpos,entlen) )    ERROR
//    }
//    else
    datalen = acbptr->GetLength();
    if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )      // nicht DBHeader
      acbptr->get_acbieh().ToPIF(pif);
    term = !(position = (sub_bases+sbnumber)->Append(datalen+IEH,entlen,AUTO,&acbptr->get_acbieh()));
    if ( acbptr->get_mb_ebsnum().get_ebsnum() > 1 )      // nicht DBHeader
      acbptr->get_acbieh().FromPIF(pif);
    if ( term )                                      ERROR
    
    (sub_bases+sbnumber)->Delete(oldda,oldpos);
    acbptr->SetEBILen(entlen);
    acbptr->SetPosition(position);
    acbptr->SetDANumber((sub_bases+sbnumber)->GetActDA());
    acbptr->stssmod();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ebsprv - 


\return term - Termination code

\param  acbptr - 
\param  real - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebsprv"

logical eb_MainBase :: ebsprv (acb *acbptr, logical real )
{
  logical       term = NO;

BEGINSEQ
  if ( acbptr->stscusr3() )                          LEAVESEQ
    
  mb_lock.ILock();
  if ( GetEBI(acbptr,real) )                         ERROR
  if ( acbptr->CheckVersion() )
    if ( acbptr->GetPrevEBI(sub_bases,acbptr->get_version_number(),pif) )
                                                     ERROR
                                                     
  if ( acbptr->stscdel() )                           SDBERR(3)
  if ( acbptr->stscold() )
    acbptr->stsswpt(1);
  
  mb_lock.IUnlock();
/*
  Wiederherstellung ist inhaltlich abhängig zu machen und von dieser Ebene nicht zu klären !!  
  {
    if ( sys_application == YES )
    {
      SDBIERR(3)                                      ERROR
    }
    if ( !mb_outopt || acbptr->stscusr1() || acbptr->stscusr2()) 
                                                      SDBERR(3)
    acbptr->stsrdel();
    if ( PutEBI(acbptr) )                             ERROR
    SDBSET(88)
  }
*/
RECOVER
  mb_lock.IUnlock();
  if ( SDBERROR )
    PrintMessage(acbptr);
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ebstwerr - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebstwerr"

void eb_MainBase :: ebstwerr ( )
{



}

/******************************************************************************/
/**
\brief  operator= - 


\return rmainbase - 

\param  rmainbase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

eb_MainBase &eb_MainBase :: operator= (eb_MainBase &rmainbase )
{

  mb_header    = rmainbase.mb_header;
  mb_number    = rmainbase.mb_number;
  sub_bases    = rmainbase.sub_bases;
  number_sb    = rmainbase.number_sb;
  cluster_pool = rmainbase.cluster_pool;
  sys_application = rmainbase.sys_application;
  mb_outopt    = rmainbase.mb_outopt;
  mb_netopt    = rmainbase.mb_netopt;
  pif          = rmainbase.pif;
  
  cluster_pool->SetMainBase(this);

  return(*this);
}

/******************************************************************************/
/**
\brief  ~eb_MainBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~eb_MainBase"

     eb_MainBase :: ~eb_MainBase ( )
{



}


