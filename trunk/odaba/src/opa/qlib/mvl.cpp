/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    mvl



\date     $Date: 2006/05/09 16:18:39,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvl"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sDifferenceList.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <iNetConversion.h>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <skcb.hpp>
#include  <sksrt.hpp>
#include  <smven.hpp>
#include  <smvlx.hpp>
#include  <ssrt.hpp>
#include  <smvl.hpp>


/******************************************************************************/
/**
\brief  AutoCorrection

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoCorrection"

logical mvl :: AutoCorrection ( )
{
  logical                 extlock = stsclck();
  int32                   lindx = 0;
  char                   *entry;
  EB_Number               entnr;
  logical                 pif;
  logical                 term = NO;
BEGINSEQ
  if ( mvlsrt->srtlen() != 8 || mvlsrt->srtkln() != 4 || mvlsrt->srtkps() != 5)
                                                     LEAVESEQ
  SetupTable(); // koennte zuviel sein

  if ( (entry = (char *)mvlsrt->srtigt(1)) && !memcmp(entry+4,"    ",4 ) )
  {
    pif = struct_access->get_pif();
    Lock();
    while ( entry = (char *)mvlsrt->srtigt(++lindx) )
    {
      entnr = *((EB_Number *)entry);
      entnr.FromPIF(pif);
      memcpy(entry+4,&entnr,4);
    }
    mvlsrt->srtsor(5,4,'I');
    if ( ob_handle->GetAccess() > PI_Read )
    {
      ob_handle->StartTAIntern(NO,YES,AUTO);    
      Modify();
      Save();
      ob_handle->StopTA(AUTO,NO);    
    }
  }
ENDSEQ
  Unlock(extlock);
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

logical mvl :: CheckVersion6 ( )
{
  char                   *entry;
  char                   *newent;
  char                   *newtab;
  int32                   len;
  int32                   area_len;
  int32                   count;
  int32                   indx = 0;
  logical                 pif;
  logical                 term = NO;
BEGINSEQ
  if ( ob_handle->GetDBVersion() < 6 && !exd_area->stscini() &&
       exd_area->GetLength() > 0 && refsotyp != IDB_MVLY )
  {
    pif   = exd_area->IsPIF();
    
    if ( refsotyp == IDB_MVLD )
    {
      logical     update;
      DBStructDef *strv5def = struct_access->get_struct_def()->ProvideV5StructDef();
      len   = strv5def->get_ext_length();
      count = exd_area->GetLength()/len;
      srt     tmptab(count,len,0,0,' ',NO);
      tmptab.srtsete(exd_area->GetLength());
    
      int32   newlen = mvlsrt->srtlen();
      memcpy(tmptab.srtigt(1),exd_area->GetInstance(),exd_area->GetLength());
      exd_area->ChangeSize(newlen*count);
      newtab = exd_area->GetInstance();
      
      while ( entry = (char *)tmptab.srtigt(++indx) )
      {
        newent = newtab + (indx-1)*newlen;
        memcpy(strv5def->get_ext_area(),entry,strv5def->get_ext_length());
        struct_access->get_struct_def()->CopyExtInst(ob_handle,strv5def,&update);
        memcpy(newent,struct_access->get_struct_def()->get_ext_area(),newlen);
      }
    }
    else
    { 
      len   = mvlsrt->srtlen()-4;
      area_len = exd_area->GetLength();
      while ( area_len%len && len )
        len--;
      if ( len < 4 )                                    SDBERR(99)
      count = area_len/len;
      srt     tmptab(count,len,0,0,' ',NO);
      tmptab.srtsete(exd_area->GetLength());
    
      memcpy(tmptab.srtigt(1),exd_area->GetInstance(),exd_area->GetLength());
      exd_area->ChangeSize(mvlsrt->srtlen()*count);
      newtab = exd_area->GetInstance();
      while ( entry = (char *)tmptab.srtigt(++indx) )
      {
        newent = newtab + (indx-1)*mvlsrt->srtlen();
        *(uint64 *)newent = BigToPIF(PIFToLong(*(int32 *)entry,pif),pif);
        if ( len > 4 )
          memcpy(newent+8,entry+4,len-4); 
      }
    }
    exd_area->SetLength(mvlsrt->srtlen()*count);
    exd_area->stssetini();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTable

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTable"

logical mvl :: CreateTable ( )
{
  EB_Number  entnr;
  int16      sbnumber = struct_access->get_struct_def()->get_sb_number();
  logical    term = NO;
BEGINSEQ
  ReleaseReference();
  
  if ( (entnr = struct_access->CreateEBI(mb_number,cluster_number,sbnumber,GetVersion())).IsEmpty() )
                                                     ERROR
  if ( ProvideTable(entnr) )                         ERROR
  exd_area->NewEntry();
  
  mvlsrt->srtsett(exd_area->GetInstance());
  mvlsrt->srtsetm(mvlmaxl/mvlsrt->srtlen());
  mvlsrt->srtsetc(0);
  mod_count = exd_area->get_mod_count();
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical mvl :: DelExt (int32 lindx0 )
{
  logical   term = NO;
  logical   extlock = stsclck();
BEGINSEQ
  if ( Lock() )                                         ERROR

  if ( lindx0 < 0 || lindx0 >= mvlsrt->srtcnt() )       ERROR

  refcuri = AUTO;
  
  mvlsrt->srtidl(lindx0+1);
  Modify();
RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  FromPIF

\return term - Termination code

\param  exdarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

logical mvl :: FromPIF (exd *exdarea )
{
  int32                    count;
  logical                 term = NO;
  if ( !exdarea )
    exdarea = exd_area;

  if ( IsPD() && exdarea->IsPIF() )
  {
    count = mvlsrt->srtcnt();
    mvlsrt->srtsett(exdarea->GetInstance());
    mvlsrt->srtsete(exdarea->GetLength());
    mvlsrt->FromPIF();
    exdarea->ResetPIF();
    mvlsrt->srtsett(exd_area->GetInstance());
    mvlsrt->srtsetc(count);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  GetCount

\return count

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 mvl :: GetCount ( )
{
  int32  count = AUTO;

BEGINSEQ

  if ( Refresh() )                                         ERROR
  count = mvlsrt->srtcnt();

RECOVER
ENDSEQ
  return(count);

}

/******************************************************************************/
/**
\brief  GetTable

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTable"

logical mvl :: GetTable ( )
{
  EB_Number      ebsnum;
  logical        newref  = !exd_area;
  logical        term    = NO;

BEGINSEQ
  mvlsrt->stssini();
  
  if ( refrex )
  {
    ebsnum  = *refrex;
    if ( exd_area && *refrex != exd_area->get_exdebsn() )
    {
      if ( refmod )  // kann eigentlich nicht vorkommen, aber man weiß ja nie
      {
        Save();
        *refrex = ebsnum;
      }
      ReleaseReference();
      newref   = YES;
    }
  }
    
  if ( !exd_area )
    if ( ProvideTable(ebsnum) )                      ERROR
  
  if ( !ebsnum.IsEmpty(ob_handle->get_pif()) && (mvlrefi || newref) )
    if ( Read() )                                    ERROR
  
  if ( exd_area && exd_area->IsPIF() && IsPD() )
    term = YES;

  SetupTable();
RECOVER
  if ( !exd_area )
  {
    mvlsrt->srtsett(NULL);
    mvlsrt->srtsetm(0);
  }  
  mvlsrt->srtsetc(0);
  term = YES;

ENDSEQ
  refcuri = AUTO;
  return(term);

}

/******************************************************************************/
/**
\brief  IsMemoKey

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMemoKey"

logical mvl :: IsMemoKey ( )
{

  return( refsakcb && refsakcb->get_key_def()->IsMemoKey() );


}

/******************************************************************************/
/**
\brief  IsPD

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPD"

logical mvl :: IsPD ( )
{
  kcb                    *kcbptr = refsakcb->get_key_def();

  return ( refsotyp != IDB_MVLP && 
           (kcbptr && kcbptr->IsPD()) ||
           (!kcbptr && mvlsrt->srtktp() == 'I') );


}

/******************************************************************************/
/**
\brief  Modify


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void mvl :: Modify ( )
{
  if ( exd_area )
    exd_area->SetLength(mvlsrt->srtlen() * mvlsrt->srtcnt());
  refmod = YES;
}

/******************************************************************************/
/**
\brief  ProvideEXD

\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEXD"

exd *mvl :: ProvideEXD ( )
{
BEGINSEQ
  if ( !exd_area )
    if ( !refrex || ProvideTable(*refrex) )          ERROR


RECOVER
ENDSEQ
  return(exd_area);
}

/******************************************************************************/
/**
\brief  ProvideTable

\return term - Termination code

\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideTable"

logical mvl :: ProvideTable (EB_Number ebsnum )
{
  int32       maxe = mvlmaxl > 0 ? mvlmaxl/mvlsrt->srtlen() : 0;
  logical    pif  = ob_handle->get_pif();
  int32       len  = 0;
  uint16     version_nr;
  uint8      wslevel;
  logical    term = NO;
BEGINSEQ
  if ( !exd_area )
  {
    mod_count  = 0;
    version_nr = GetVersion();
    if ( !ebsnum.IsEmpty(pif) )
      exd_area = struct_access->GetEXD(ebsnum,version_nr);
      
    if ( !exd_area )
    {
      if ( !maxe && !ebsnum.IsEmpty(pif) )
      {
        wslevel = !HasWorkspace() ? 255 : refsotyp != IDB_MVLF ? 0 : ((DifferenceList *)this)->get_ws_level();
        len     = struct_access->GetDBEntryLength(ebsnum,wslevel,version_nr);
        maxe    = len/mvlsrt->srtlen();
      }
      
      if ( !(exd_area = struct_access->ProvideEXD(ebsnum,cluster_number,
                              (int32)(maxe ? maxe : 3)*mvlsrt->srtlen(),
                              (char)refsotyp,!refglob,HasWorkspace(),
                              version_nr,stsctrans())) ) 
                                                     ERROR   
      exd_area->SetLength(len);
    }
    ReserveReference();
    if ( struct_access->get_pif() && !IsPD() )
      exd_area->SetPIF();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read

\return term - Termination code

\param  skip_ta
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical mvl :: Read (logical skip_ta )
{
  logical    term = NO;
BEGINSEQ
  if ( !exd_area->NewEntry() )
  {
    if ( !exd_area->GetLength() && mvlmaxl > 0 )
      exd_area->SetLength(mvlmaxg());
    if ( exd_area->Read(AUTO,skip_ta) )  
    {
      if ( SDBERROR != 3 )                           ERROR
      SDBRESET
      *refrex = 0;
      exd_area->SetLength(0);
    }
    if ( refsotyp != exd_area->get_exdacb()->get_acbieh().get_iehtyp() )
                                                     SDBERR(105)
    CheckVersion6();
    if ( exd_area->IsPIF() )
      FromPIF(NULL);
    if ( IsIdentityOrder() )    // kann dann mal wieder raus, wenn alle korrigiert sind
      AutoCorrection();         // 31.8.2004
  }
  else
    exd_area->SetLength(0);

  if ( mvlmaxl > 0 && mvlmaxl < exd_area->GetDBLength() )
                                                     SDBERR(99)
//  stsrusr2();   muß von Refresh() gehandelt werden!
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical mvl :: Refresh ( )
{
  logical   term = NO;

BEGINSEQ
  if ( !mvlsrt )                                     ERROR
  
  mvlsrt->stssold();

  if ( !mvlchck() )                                  LEAVESEQ
  
  if ( GetTable() )                                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Reset

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical mvl :: Reset ( )
{
//  Save();
  if ( mvlsrt )
  {
    mvlsrt->srtsett(NULL);
    mvlsrt->srtsetm(UNDEF);
    mvlsrt->srtres();
    mvlsrt->stssini();
  }
  return(refs::Reset());
}

/******************************************************************************/
/**
\brief  ResetTable

\return term - Termination code

\param  mvenptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetTable"

logical mvl :: ResetTable (mven *mvenptr )
{
  logical   term = NO;

BEGINSEQ
  if ( Save() )                                      ERROR
//  Reset(); --> wird im CreateTable behandelt
  
  if ( CreateTable() )                               ERROR
  mvenptr->mvencntr();                                                           
  *(EB_Number *)mvenptr = *refrex = exd_area->get_exdebsn();                                                           
  
  memset(mvenptr->mvenkeyg(),' ',mvlsrt->srtkln());

RECOVER
  term = YES;
ENDSEQ
  refcuri = AUTO;
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

logical mvl :: Save ( )
{
  int32    	 size;
  EB_Number      entnr;
  int32           len;
  logical        term = NO;

BEGINSEQ
  if ( !exd_area || !refmod )                         LEAVESEQ
  
  len = size = mvlsrt->srtlen()*mvlsrt->srtcnt();
  if ( mvlmaxl > 0 )
    size = mvlmaxg();
  else
  {
    if ( exd_area->GetDBLength() < len )
    {
      mvlexp(mvlsrt->srtcnt()+(!cluster_number.IsEmpty() ? 0 : MIN(mvlexte,mvlsrt->srtcnt())));
      size = mvlsrt->srtlen() * mvlsrt->srtmax();
    }
  }  
  exd_area->SetLength(len);

  entnr = exd_area->get_exdebsn();
  if ( struct_access->get_pif() )
    ToPIF(NULL);
  if ( struct_access->WriteEXD(exd_area,size,mb_number,AUTO,AUTO).IsEmpty(struct_access->get_pif()) )
                                                     ERROR
  
  if ( entnr != exd_area->get_exdebsn() )
  {
    stssmod();
    if ( refrex )
      *refrex = exd_area->get_exdebsn();
  }
 
  mod_count = exd_area->get_mod_count();
  refmod = NO;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupTable


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTable"

void mvl :: SetupTable ( )
{
  mvlsrt->srtsett(exd_area->GetInstance());
  mvlsrt->srtsetm((mvlmaxl > 0 ? (int32)mvlmaxl : exd_area->get_entry_size())/mvlsrt->srtlen());
  mvlsrt->srtsete(exd_area->GetLength());
  mod_count = exd_area->get_mod_count();

//  if ( exd_area->IsPIF() )
//    FromPIF(NULL);

}

/******************************************************************************/
/**
\brief  ToPIF

\return term - Termination code

\param  exdarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

logical mvl :: ToPIF (exd *exdarea )
{
  exd                    *exdptr;
  int32                    count;
  logical                 term = NO;
  if ( !exdarea )
    exdarea = exd_area;
  
  if ( IsPD() && !exdarea->IsPIF() )
  {
    count = mvlsrt->srtcnt();
    exdptr = exdarea->ProvidePIF();
    mvlsrt->srtsett(exdptr->GetInstance());
    mvlsrt->srtsete(exdptr->GetLength());
    mvlsrt->ToPIF();
    exdptr->SetPIF();
    mvlsrt->srtsett(exd_area->GetInstance());
    mvlsrt->srtsetc(count);
  }
  else
    exdarea->SetPIF();

  return(term);
}

/******************************************************************************/
/**
\brief  mvl


\param  lobhandle - 
\param  extref - 
\param  clnumb
\param  otyp - 
\param  extcnt - 
\param  maxl - 
\param  akcbptr
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvl"

     mvl :: mvl (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, char otyp, int16 extcnt, int16 maxl, DBIndex *akcbptr, logical globind )
                     : refs(lobhandle,extref,clnumb,otyp,akcbptr,globind),
  mvlsrt(NULL),
  mvlmaxl(maxl), 
  mvlexte(extcnt > 0 ? extcnt : MVL_ECT),
  mvlrefi(NO)

{
  if ( stscsav() )
    mvlrefi = YES;

}

/******************************************************************************/
/**
\brief  mvlchck

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlchck"

logical mvl :: mvlchck ( )
{
  logical    term = NO;
BEGINSEQ
  if ( !refrex )                                     LEAVESEQ
  if ( !exd_area || *refrex != exd_area->get_exdebsn() )
                                                     ERROR
  if ( mod_count != exd_area->get_mod_count() )      ERROR
    
  if ( refrex->IsEmpty(ob_handle->get_pif()) || stsclck() )          
                                                     LEAVESEQ
  
  if ( exd_area->IsModified() )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  mvlchk

\return indx - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlchk"

int32 mvl :: mvlchk (int32 lindx0 )
{
  int32  indx = lindx0+1;

BEGINSEQ
  if ( !indx ) 
    indx = mvlsrt->srtcnt()+1;
  if ( indx < 1 || indx > mvlsrt->srtcnt()+1 )             SDBERR(59)
    
  if ( !mvlfec() ) 
    if ( mvlexp(mvlsrt->srtmax()+10) )                     ERROR
RECOVER
  indx = 0;
ENDSEQ
  return(indx);

}

/******************************************************************************/
/**
\brief  mvlcrt

\return term - Termination code

\param  elen - 
\param  kpos - 
\param  kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlcrt"

logical mvl :: mvlcrt (int16 elen, int16 kpos, kcb *kcbptr )
{
  logical        term    = NO;

BEGINSEQ
  if ( kcbptr->IsMemoKey() )
  {
//    if ( !(mvlsrt = new msrt(kcbptr,0,elen,sizeof(EB_Number),
//                             kpos,NO)) )	       SDBERR(95)
SDBERR(99)    
  }
  else
    if ( !(mvlsrt = new ksrt(kcbptr,0,elen,
	                     (int16)(kcbptr ? kcbptr->scbsmcb->GetInstLength(NO) : 0),
                             kpos, kcbptr ? (refsotyp == IDB_MVLD ? 'S' : 'K') : UNDEF, NULL,NO)) )	   
                                                       SDBERR(95)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  mvlexp

\return term - Termination code

\param  maxent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlexp"

logical mvl :: mvlexp (int64 maxent )
{
  int32   	 size = (int32)maxent*mvlsrt->srtlen();
  void          *tblptr = mvlsrt->srttbl();
  logical        term = NO;
BEGINSEQ
  if ( mvlmaxl > 0 )                                 SDBERR(99)
    
  if ( size > exd_area->ChangeSize(size) )           ERROR
  
  mvlsrt->srtsetm(maxent);
  mvlsrt->srtsett(exd_area->GetInstance());
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  mvlfec

\return count
-------------------------------------------------------------------------------
\brief  MVLFEC


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlfec"

int32 mvl :: mvlfec ( )
{
  return( mvlsrt->srtmax() - mvlsrt->srtcnt() );

}

/******************************************************************************/
/**
\brief  MVLFEC_


\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlfec"

int32 mvl :: mvlfec (EB_Number ebsnum )
{
  int32     size;
  uint16    version_nr;
  uint8     wslevel;
  int32     count;
BEGINSEQ
  SDBRESET
      
  version_nr = GetVersion();
  wslevel    = !HasWorkspace() ? 255 : refsotyp != IDB_MVLF ? 0 : ((DifferenceList *)this)->get_ws_level();

  size = struct_access->GetDBEntryLength(ebsnum,wslevel,version_nr)-
         struct_access->GetDBUsedLength(ebsnum,wslevel,version_nr);  
                                                       SDBCERR
  count = size/mvlsrt->srtlen();

RECOVER
ENDSEQ
  return(count);

}

/******************************************************************************/
/**
\brief  mvllast

\return keyptr - 

\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvllast"

char *mvl :: mvllast (char *keyptr )
{

BEGINSEQ
  if ( !mvlsrt->srtkln() || !mvlsrt->srtcnt() )             ERROR

  keyptr = mvlsrt->ExtractKey(mvlsrt->srtigt(mvlsrt->srtcnt()),keyptr);


RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  mvlmaxg

\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlmaxg"

int32 mvl :: mvlmaxg ( )
{
  return((mvlmaxl/mvlsrt->srtlen())*mvlsrt->srtlen());

}

/******************************************************************************/
/**
\brief  mvlrmv - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlrmv"

void mvl :: mvlrmv ( )
{
  mvl::Reset();
  if ( IsMemoKey() )
; //    delete (msrt *)mvlsrt;
  else
    delete (ksrt *)mvlsrt;
  mvlsrt = NULL;

}

/******************************************************************************/
/**
\brief  mvlshft

\return cmpval

\param  mvenlow - 
\param  mvenhigh - 
\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlshft"

int8 mvl :: mvlshft (mven *mvenlow, mven *mvenhigh, char *skey )
{
  exd     *lowexd  = NULL;
  exd     *highexd = NULL;
  char    *lowtab  = NULL;
  char    *hightab = NULL;
  int32     highlen;
  int32     lowlen;
  int32  lowcnt;
  int32  highcnt;
  int32      diff;
  int32      len;
  int16     size = mvlmaxg();
  int       cmpval;
  logical   pif  = struct_access->get_pif();

BEGINSEQ
  refcuri = AUTO;

  if ( !(lowexd = struct_access->ProvideEXD((EB_Number)*mvenlow,cluster_number,size,
                                            (char)refsotyp,!refglob,HasWorkspace(),GetVersion())) )
                                                     ERROR
  lowexd->ReserveInstance(NULL);
  if ( !(highexd = struct_access->ProvideEXD((EB_Number)*mvenhigh,cluster_number,size,
                                             (char)refsotyp,!refglob,HasWorkspace(),GetVersion())) )
                                                     ERROR
  highexd->ReserveInstance(NULL);
  
  ReleaseReference();
  if ( ProvideTable(0) )                             ERROR
  mvlsrt->srtsett(exd_area->GetInstance());
  mvlsrt->srtsetm(mvlmaxl/mvlsrt->srtlen());
  mvlsrt->srtsetc(0);  
  
  if ( lowexd->Read(size) )                          ERROR
  if ( lowexd->IsPIF() )
    FromPIF(lowexd);
  if ( highexd->Read(size) )                         ERROR
  if ( highexd->IsPIF() )
    FromPIF(highexd);

  hightab = highexd->GetInstance();
  lowtab  = lowexd->GetInstance();
  highlen = highexd->GetLength();
  lowlen  = lowexd->GetLength();
  diff = (highlen - lowlen)/mvlsrt->srtlen();

  if ( diff < 0 )
  {
    len = (-diff/2)*mvlsrt->srtlen();
    memcpy(mvlsrt->srttbl(),lowtab+lowlen-len,(int)len);
    memcpy((char *)mvlsrt->srttbl()+len,hightab,(int)highlen);
    exd_area->SetLength(highlen+len);
    lowexd->SetLength(lowlen-len);
    highexd->CopyTo(exd_area);
    mvlsrt->srtsete(exd_area->GetLength());
    switch ( refsotyp ) 
    {
      case IDB_MVLN :
      case IDB_MVLL : highcnt = ((mvlx *)this)->mvlxcntc();
                      break;
      default       : highcnt = mvlsrt->srtcnt();                      
    }
    lowcnt = mvenlow->mvencntg(pif) - (highcnt-mvenhigh->mvencntg(pif));
  }
  else
  {
    len = ((diff+1)/2)*mvlsrt->srtlen();
    exd_area->CopyTo(lowexd);
    memcpy((char *)mvlsrt->srttbl()+lowlen,hightab,(int)len);
    memcpy(hightab,hightab+len,(int)(highlen-len));
    exd_area->SetLength(lowlen+len);
    highexd->SetLength(highlen-len);
    lowexd->CopyTo(exd_area);
    mvlsrt->srtsete(exd_area->GetLength());
    switch ( refsotyp ) 
    {
      case IDB_MVLN :
      case IDB_MVLL : lowcnt = ((mvlx *)this)->mvlxcntc();
                      break;
      default       : lowcnt = mvlsrt->srtcnt();                      
    }
    highcnt = mvenhigh->mvencntg(pif) - (lowcnt-mvenlow->mvencntg(pif));
  }

  mvlsrt->ExtractKey(lowtab+lowexd->GetLength()-mvlsrt->srtlen(),mvenlow->mvenkeyg());
  mvenlow->mvencnts(lowcnt,pif);

  if ( struct_access->get_pif() )
    ToPIF(lowexd);
  if ( struct_access->WriteEXD(lowexd,mvlsrt->srtlen()*mvlsrt->srtmax(),
                   mb_number,AUTO,AUTO).IsEmpty() )          ERROR
                   
  mvlsrt->ExtractKey(hightab+highexd->GetLength()-mvlsrt->srtlen(),mvenhigh->mvenkeyg());
  mvenhigh->mvencnts(highcnt,pif);
  
  if ( struct_access->get_pif() )
    ToPIF(highexd);
  if ( struct_access->WriteEXD(highexd,mvlsrt->srtlen()*mvlsrt->srtmax(),
                               mb_number,AUTO,AUTO).IsEmpty() )
                                                             ERROR
  ReleaseReference();
  switch ( cmpval = refsakcb->get_key_def()->kcbkcp(skey,mvenlow->mvenkeyg()) )
  {
    case  1 : exd_area = highexd;
              lowexd->ReleaseInstance(NULL);
              lowexd   = NULL;
              break;
    case -1 : 
    default : exd_area = lowexd;
              highexd->ReleaseInstance(NULL);
              highexd = NULL;
              break;
  }
  mvlsrt->srtsete(exd_area->GetLength());
  mvlsrt->srtsett(exd_area->GetInstance());
  mod_count = 0; // force refresh

RECOVER
  Reset();
  lowexd->ReleaseInstance(NULL);
  highexd->ReleaseInstance(NULL);
  cmpval = UNDEF;
ENDSEQ
  return(cmpval);

}

/******************************************************************************/
/**
\brief  mvlsplt

\return term - Termination code

\param  mvenptr - 
\param  mvennew - 
\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlsplt"

logical mvl :: mvlsplt (mven *mvenptr, mven *mvennew, char *skey )
{
  char      work[MAX_KEYLEN+MVEN];
  int16     elen;
  logical   term = NO;

BEGINSEQ
  if ( CreateTable() )                                  ERROR
  *(EB_Number *)mvennew = exd_area->get_exdebsn();
  mvennew->mvencntr();

  switch ( mvlshft(mvennew,mvenptr,skey) )     
  {
    case -1 : break;
    case  1 : elen = MVEN+mvlsrt->srtkln();
              memcpy(work,mvenptr,elen);
              memcpy(mvenptr,mvennew,elen);
              memcpy(mvennew,work,elen);
              break;
    default :                                              ERROR         
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~mvl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvl"

     mvl :: ~mvl ( )
{
  mvlrmv();
}


