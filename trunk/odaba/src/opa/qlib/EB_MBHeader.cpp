/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_MBHeader

\brief    


\date     $Date: 2006/03/12 19:17:27,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_MBHeader"

#include  <popa7.h>
#include  <cEBIo.h>
#include  <cRBHdr.h>
#include  <sEBI.hpp>
#include  <sEBMainBase.hpp>
#include  <iNetConversion.h>
#include  <sacb.hpp>
#include  <seb_SubBase.hpp>
#include  <sEB_MBHeader.hpp>


/******************************************************************************/
/**
\brief  Close - 



\param  odbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void EB_MBHeader :: Close (eb_SubBase *odbptr )
{

  if ( odbptr )
  {
    SaveBuffer(odbptr,0);
    SaveBuffer(odbptr,1);
    SaveBuffer(odbptr,2);
    SaveBuffer(odbptr,3);
    SaveBuffer(odbptr,4);
    SaveBuffer(odbptr,AUTO);
  }
  
  delete ebi_buffer[0];
  delete ebi_buffer[1];
  delete ebi_buffer[2];
  delete ebi_buffer[3];
  delete ebi_buffer[4];
  delete[] low_ebi_buffer;
  ebi_buffer[0]  = NULL;
  ebi_buffer[1]  = NULL;
  ebi_buffer[2]  = NULL;
  ebi_buffer[3]  = NULL;
  ebi_buffer[4]  = NULL;
  low_ebi_buffer = NULL;


}

/******************************************************************************/
/**
\brief  EB_MBHeader - 



\param  len -
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_MBHeader"

                        EB_MBHeader :: EB_MBHeader (uint16 len, logical netopt )
                     : EB_SBHeader(len,netopt), 
  ebi_buffer_mod(NO),
  lebi_buffer_mod(NO),
  low_ebi_buffer(NULL)
{

  memcpy(eb_ident+2,"MB",2);
  memset(ebi_buffer,0,sizeof(ebi_buffer));

}

/******************************************************************************/
/**
\brief  GetEBIPos

\return position64 -

\param  odbptr -
\param  position64 -
\param  lev -
\param  entnum -
\param  provide -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBIPos"

int64 EB_MBHeader :: GetEBIPos (eb_SubBase *odbptr, uint64 position64, int16 lev, EB_Number entnum, logical provide )
{
  uint64       *posptr = NULL;
BEGINSEQ
  while ( position64 && lev-- )
  {
    if ( *ebi_buffer[lev] != position64 )
    {
      if ( (ebi_buffer_mod & 1<<lev) && SaveBuffer(odbptr,lev) )
                                                     ERROR
      if ( !ReadBuffer(odbptr,position64,ebi_buffer[lev]+1,256) )
                                                     ERROR
      *ebi_buffer[lev] = position64;
    }
    
    posptr = ebi_buffer[lev]+1+entnum.Position(lev+1);
    if ( !*posptr && odbptr->get_sb_netopt() )
    {
      if ( !odbptr->Locate(0,(*ebi_buffer[lev])+8*entnum.Position(lev+1),8,posptr) ) 
                                                     ERROR
      *posptr = PIFToBig(*posptr,platform_indep);   
    }
    position64 = *posptr;
  }
    
  if ( !position64 )
  {
    if ( !provide )                                  ERROR
    position64 = PutEBI(odbptr,lev,entnum);
  }

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  GetEBIoPos

\return position64 -

\param  odbptr -
\param  position64 -
\param  lev -
\param  entnum -
\param  provide -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBIoPos"

int64 EB_MBHeader :: GetEBIoPos (eb_SubBase *odbptr, uint64 position64, int16 lev, EB_Number entnum, logical provide )
{
  uint64       *posptr = NULL;
  uint64        newpos = position64;
BEGINSEQ
  while ( position64 && lev-- )
  {
    newpos = position64;
    if ( *ebi_buffer[lev] != position64 )
    {
      if ( (ebi_buffer_mod & 1<<lev) && SaveBuffer(odbptr,lev) )
                                                     ERROR
      if ( !(newpos = ReadBuffer(odbptr,position64,ebi_buffer[lev]+1,256)) )
                                                     ERROR
      *ebi_buffer[lev] = newpos;
    }
    
    // Version3 update
    if ( newpos != position64 )
    {
      if ( posptr )
      {
        *posptr = newpos;
        ebi_buffer_mod |= 1<<(lev+1);
      }
      else
        SetLevelIndex(newpos,lev+1);
      position64 = newpos;
    }
    // end Version3 update
    
    posptr = ebi_buffer[lev]+1+entnum.Position(lev+1);
    if ( !*posptr && odbptr->get_sb_netopt() )
    {
      if ( !odbptr->Locate(0,(*ebi_buffer[lev])+8*entnum.Position(lev+1),8,posptr) ) 
                                                     ERROR
      *posptr = PIFToBig(*posptr,platform_indep);   
    }
    position64 = *posptr;
  }
    
  if ( !position64 )
  {
    if ( !provide )                                  ERROR
    position64 = PutEBI(odbptr,lev,entnum);
  }

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  GetNextEBIPos - 


\return position64 -

\param  odbptr -
\param  position64 -
\param  lev -
\param  entnr_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextEBIPos"

int64 EB_MBHeader :: GetNextEBIPos (eb_SubBase *odbptr, uint64 position64, int16 lev, EB_Number &entnr_ref )
{

BEGINSEQ
  while ( lev-- )
  {
    if ( position64 )
    {
      if ( *ebi_buffer[lev] != position64 )
      {
        if ( (ebi_buffer_mod & 1<<lev) && SaveBuffer(odbptr,lev) )   ERROR
        if ( !ReadBuffer(odbptr,position64,ebi_buffer[lev]+1,256) )
                                                     ERROR
      }
      *ebi_buffer[lev] = position64;
    }
    
    while ( !(position64 = *(ebi_buffer[lev]+1+entnr_ref.Position(lev+1))) )
    {
      if ( entnr_ref > get_last_EBS_num() )          ERROR
      
      if ( entnr_ref.Position(lev+1) < 255 )
        entnr_ref.SetPosition(lev+1,entnr_ref.Position(lev+1)+1);
      else
      {
        if ( lev == 4 )                              ERROR
        lev += 2;
        entnr_ref.SetPosition(lev-1,0);
        entnr_ref.SetPosition(lev,entnr_ref.Position(lev)+1);
        if ( lev == 5 || !entnr_ref.Position(lev+1) ) 
          position64 = ebshipg(lev);
        else  
          position64 = *(ebi_buffer[lev]+1+entnr_ref.Position(lev+1));
        break;
      }
    }
  }

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  GetNextEBNumber - 


\return position64 -

\param  odbptr -
\param  entnr_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextEBNumber"

int64 EB_MBHeader :: GetNextEBNumber (eb_SubBase *odbptr, EB_Number &entnr_ref )
{
  int32        lev;
  int64        position64;

BEGINSEQ
//  if ( large_db )                                    SDBERR(99) // wat soll dat ?? 13.9.01
    
  entnr_ref = entnr_ref.get_ebsnum()+1;
  if ( entnr_ref > get_last_EBS_num() )                     ERROR
  
  lev = entnr_ref.GetLevel();  
  if ( !ebshipg(lev) )  
    while ( lev < 4 )
      if ( !ebshipg(lev) )
      {
        lev++;
        entnr_ref = 1 << (lev*8);
      }
      else
        break;

  if ( !(position64 = GetNextEBIPos(odbptr,ebshipg(lev),lev,entnr_ref)) )
                                                     ERROR
  position64 += (uint64)(S_EBI*entnr_ref.Position(0));
RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical EB_MBHeader :: Open ( )
{

  ebi_buffer[0] = new uint64[257];
  ebi_buffer[1] = new uint64[257];
  ebi_buffer[2] = new uint64[257];
  ebi_buffer[3] = new uint64[257];
  ebi_buffer[4] = new uint64[257];
  low_ebi_buffer = new EBI[257];
     
  memset(ebi_buffer[0],0,257*sizeof(uint64));
  memset(ebi_buffer[1],0,257*sizeof(uint64));
  memset(ebi_buffer[2],0,257*sizeof(uint64));
  memset(ebi_buffer[3],0,257*sizeof(uint64));
  memset(ebi_buffer[4],0,257*sizeof(uint64));
  memset(low_ebi_buffer,0,257*sizeof(EBI));

  return(NO);
}

/******************************************************************************/
/**
\brief  PutEBI - 


\return position64 -

\param  odbptr -
\param  lev -
\param  entnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutEBI"

int64 EB_MBHeader :: PutEBI (eb_SubBase *odbptr, int16 lev, EB_Number entnum )
{
  uint64        local_pos;
  uint64        curpos;
  uint64       *posptr = &local_pos; 
  uint64        position64;    
  uint16        entnr_lev = entnum.GetLevel();
  uint16        entlen  = lev ? sizeof(uint64) : S_EBI;
BEGINSEQ
  if ( entnr_lev > lev )
    posptr = ebi_buffer[lev]+1+entnum.Position(lev+1);
  if ( !(*posptr = odbptr->CreateIndexEntry(256*entlen)) ) 
                                                     ERROR
  position64 = *posptr;
  if ( entnr_lev > lev )
    if ( odbptr->get_sb_netopt() )
    {
      curpos = BigToPIF(*posptr,platform_indep);
      if ( *ebi_buffer[lev] )
        if ( odbptr->Update(0,(*ebi_buffer[lev])+8*entnum.Position(lev+1),
                            8,&curpos) )              ERROR
    }
    else
      ebi_buffer_mod = (ebi_buffer_mod | 1<<lev);
  
  if ( lev-- )
  {
    if ( SaveBuffer(odbptr,lev) )                    ERROR
    memset(ebi_buffer[lev]+1,0,2048);
    *ebi_buffer[lev] = position64;
  
    position64 = PutEBI(odbptr,lev,entnum);
  }
RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  ReadBuffer - 


\return position - Position

\param  odbptr -
\param  position64 -
\param  pos_buffer -
\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBuffer"

uint64 EB_MBHeader :: ReadBuffer (eb_SubBase *odbptr, uint64 position64, uint64 *pos_buffer, int32 count )
{
  int32           ecount = count;
  logical         term = NO;
BEGINSEQ
// for upgrade6
if ( get_version() < 3 )
{
  if ( !odbptr->Locate(0,position64,count*sizeof(uint32),pos_buffer) )
                                                   ERROR
  while ( ecount-- )
    *(pos_buffer+ecount) = BigToPIF(PIFToLong(*(((int32 *)pos_buffer)+ecount),platform_indep),platform_indep);
  if ( !(position64 = odbptr->Append(count*sizeof(uint64),256*sizeof(uint64),0,pos_buffer)) )
                                                   ERROR
}
else
  
  if ( !odbptr->Locate(0,position64,count*sizeof(uint64),pos_buffer) )
                                                   ERROR
  if ( platform_indep )
  {
    while ( count-- )
      *(pos_buffer+count) = PIFToBig(*(pos_buffer+count),YES);
  }

  

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical EB_MBHeader :: Reset ( )
{
  logical                 term = NO;
  Close(NULL);
  
  EB_SBHeader::Reset();
  set_sb_count(1);
  set_last_EBS_num(0);
  set_level0_index(0);
  set_level1_index(0);
  set_level2_index(0);
  set_level3_index(0);
  set_level4_index(0);
  set_level5_index(0);
//  set_dnm_opt(NO);
//  set_free_EBS_Numbers(0);

  set_next_position(get_header_length() + sizeof(EBMainBase));

  Open();
  return(term);
}

/******************************************************************************/
/**
\brief  SaveBuffer - 


\return term - Termination code

\param  odbptr -
\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveBuffer"

logical EB_MBHeader :: SaveBuffer (eb_SubBase *odbptr, int16 lev )
{
  logical                 term = NO;
BEGINSEQ
  if ( lev == AUTO )
  {
    if ( lebi_buffer_mod )
      if ( odbptr->Update(0,*(uint64 *)low_ebi_buffer,256*S_EBI,low_ebi_buffer+1) )
                                                     ERROR
    lebi_buffer_mod = NO;
    LEAVESEQ
  }
  if ( *ebi_buffer[lev] && ebi_buffer_mod & 1<<lev )    
  {
    ebi_buffer_mod -= (1<<lev);
    if ( UpdateBuffer(odbptr,ebi_buffer[lev][0],ebi_buffer[lev]+1,256) )
                                                     ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateBuffer - 


\return term - Termination code

\param  odbptr -
\param  position64 -
\param  pos_buffer -
\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateBuffer"

logical EB_MBHeader :: UpdateBuffer (eb_SubBase *odbptr, uint64 position64, uint64 *pos_buffer, int32 count )
{
  int                     old_count = count;
  logical                 term = NO;
  if ( platform_indep )
  {
    while ( count-- )
      *(pos_buffer+count) = BigToPIF(*(pos_buffer+count),YES);
  }
  
  count = old_count;
  term = odbptr->Update(0,position64,count*sizeof(uint64),pos_buffer);
  
  if ( platform_indep )
  {
    while ( count-- )
      *(pos_buffer+count) = PIFToBig(*(pos_buffer+count),YES);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Version1

\return term - Termination code

\param  odbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version1"

logical EB_MBHeader :: Version1 (eb_SubBase *odbptr )
{
  EB_Number               entnum;
  uint64                  position;
  uint64                  pos;
  int32                   lev;
  int32                   i;
  char                    oldebi[256*14];
  logical                 term = NO;
BEGINSEQ
  while ( entnum.get_ebsnum() <= get_last_EBS_num().get_ebsnum() )
  {
    lev = entnum.GetLevel();
    if ( pos = GetEBIPos(odbptr,ebshipg(lev),lev,entnum,NO) )
    {
      if ( !odbptr->Locate(0,pos,256*14,oldebi) )    
                                                     ERROR
      memset(low_ebi_buffer,0,256*S_EBI);
      for ( i=0; i < 256; i++ )
        memcpy(low_ebi_buffer+i,oldebi+i*14,14);
      
      if ( !(position = odbptr->Append(256*S_EBI,256*S_EBI,0,low_ebi_buffer)) )
                                                     ERROR
      if ( lev )
        *(ebi_buffer[0]+1+entnum.Position(1)) = position;
      else
        set_level0_index(position);
      
      if ( lev )
        if ( odbptr->Update(0,(*ebi_buffer[0])+4*entnum.Position(1),
                            4,&position) )           ERROR
    }
    entnum = entnum.get_ebsnum()+256;
  }
  
  SetVersion(1);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Version2 - 


\return term - Termination code

\param  odbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version2"

logical EB_MBHeader :: Version2 (eb_SubBase *odbptr )
{
  EB_Number               entnum;
  logical                 term = NO;
  while ( entnum.get_ebsnum() <= get_last_EBS_num().get_ebsnum() )
  {
    acb    acbenty(entnum,0,0);
    acbenty.set_mb_ebsnum(entnum);
    if ( !ebshigt(odbptr,&acbenty) )
    {
      acbenty.SetVersion(0);
      acbenty.ResetVersionList();
      ebshipt(odbptr,&acbenty);
    }
    entnum = entnum.get_ebsnum()+1;
  }
  
  SetVersion(2);
  return(term);
}

/******************************************************************************/
/**
\brief  Version3

\return term - Termination code

\param  odbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version3"

logical EB_MBHeader :: Version3 (eb_SubBase *odbptr )
{
  EB_Number               entnum;
  uint64                  position;
  int64                   pos;
  int32                   lev;
  int32                   i;
  EBIo                   *oldebi;
  int32                   ebi_count;
  logical                 term = NO;
BEGINSEQ
  ebi_count = 256;
  oldebi = (EBIo *)malloc(ebi_count * sizeof(EBIo));
  
  while ( entnum.get_ebsnum() <= get_last_EBS_num().get_ebsnum() )
  {
    lev = entnum.GetLevel();
    if ( pos = GetEBIoPos(odbptr,ebshipg(lev),lev,entnum,NO) )
    {
      if ( !odbptr->Locate(0,pos,ebi_count*20,oldebi) )    
                                                     ERROR
      memset(low_ebi_buffer,0,ebi_count*S_EBI);
      for ( i=0; i < ebi_count; i++ )
        (low_ebi_buffer+i)->ConvertTo3(odbptr,oldebi+i,platform_indep);
      
      if ( !(position = odbptr->Append(ebi_count*S_EBI,ebi_count*S_EBI,0,low_ebi_buffer)) )
                                                     ERROR
      if ( lev )
      {
        *(ebi_buffer[0]+1+entnum.Position(1)) = position;
        ebi_buffer_mod |= 1;  // buffer level 0 modified
      }
      else
        set_level0_index(position);
      
      if ( lev )
        if ( odbptr->Update(0,(*ebi_buffer[0])+8*entnum.Position(1),
                            8,&position) )           ERROR
    }
    entnum = entnum.get_ebsnum()+256;
  }
  
  SaveBuffer(odbptr,2);
  SaveBuffer(odbptr,1);
  SaveBuffer(odbptr,0);
  SetVersion(3);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ebshigt - 


\return term - Termination code

\param  odbptr -
\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshigt"

logical EB_MBHeader :: ebshigt (eb_SubBase *odbptr, acb *acbptr )
{
  uint64      bufpos;
  logical    term = NO;
BEGINSEQ
  if ( ebshipp(odbptr,acbptr,NO) )                   ERROR
  if ( acbptr->stscusr3() )                          LEAVESEQ // gepufferter EBI
  
  if ( !odbptr->get_sb_netopt() )
  {
    bufpos = (acbptr->get_ebi_position() - *(uint64 *)low_ebi_buffer)/S_EBI;
    if ( bufpos >= 0 && bufpos < 256 )
    {
      *(EBI *)acbptr = *(low_ebi_buffer + 1 + acbptr->get_mb_ebsnum().Position(0));
      acbptr->FromPIF(platform_indep);                                                     
      LEAVESEQ
    }
  }
  if ( !odbptr->Locate(0,acbptr->get_ebi_position(),S_EBI,acbptr) )     
                                                     ERROR
  acbptr->FromPIF(platform_indep);
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ebshilk - 


\return term - Termination code

\param  odbptr -
\param  acbptr -
\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshilk"

logical EB_MBHeader :: ebshilk (eb_SubBase *odbptr, acb *acbptr, logical wait )
{
  logical   term = NO;
BEGINSEQ
  if ( ebshipp(odbptr,acbptr,NO) )                   ERROR

  if ( odbptr->Lock(0,acbptr->get_ebi_position(),S_EBI,wait) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ebshipg - 


\return idxptr -

\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshipg"

uint64 EB_MBHeader :: ebshipg (int16 lev )
{

  switch ( lev )
  {
    case  0 : return(get_level0_index().get_ebsnum());
    case  1 : return(get_level1_index().get_ebsnum());
    case  2 : return(get_level2_index().get_ebsnum());
    case  3 : return(get_level3_index().get_ebsnum());
    case  4 : return(get_level4_index().get_ebsnum());
    case  5 : return(get_level5_index().get_ebsnum());
    default : return(UNDEF);
  }



}

/******************************************************************************/
/**
\brief  ebshipp - 


\return term - Termination code

\param  odbptr -
\param  acbptr -
\param  provide -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshipp"

logical EB_MBHeader :: ebshipp (eb_SubBase *odbptr, acb *acbptr, logical provide )
{
  EB_Number      entnr = acbptr->get_mb_ebsnum();
  int16          lev   = entnr.GetLevel();
  uint64         odbpos = 0;
  logical        mod    = NO;
  logical        term   = NO;
BEGINSEQ
  if ( odbpos = acbptr->get_ebi_position() )         LEAVESEQ

  if ( entnr > get_last_EBS_num() && odbptr->get_sb_netopt() )
    if ( Read() )                                     ERROR
  if ( entnr > get_last_EBS_num() )                         
  {
    if ( !odbptr->get_sb_outopt() )                   SDBERR(44)
    ERROR
  }

  if ( !ebshipg(lev) )
    if ( Read() )                                    ERROR
      
  if ( !ebshipg(lev) )
  {
    if ( !provide || !odbptr->get_sb_outopt() )      ERROR
    mod = YES;
  }
  
  if ( !(odbpos = GetEBIPos(odbptr,ebshipg(lev),lev,entnr,provide) ) )
                                                     ERROR
  if ( mod )
  {
    ebships(lev ? *ebi_buffer[lev-1] : odbpos,lev);
    stssmod();
  }
  
  if ( !odbptr->get_sb_netopt() && odbpos != *(uint64 *)low_ebi_buffer )
  {
    SaveBuffer(odbptr,AUTO);
    if ( !odbptr->Locate(0,odbpos,256*S_EBI,low_ebi_buffer+1) ) 
                                                     ERROR
    *(uint64 *)low_ebi_buffer = odbpos;
  }
  acbptr->set_ebi_position(odbpos + S_EBI*acbptr->get_mb_ebsnum().Position(0));

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ebships - 



\param  idxptr -
\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebships"

void EB_MBHeader :: ebships (uint64 idxptr, int16 lev )
{

  switch ( lev )
  {
    case  0 : set_level0_index(idxptr);  break;
    case  1 : set_level1_index(idxptr);  break;
    case  2 : set_level2_index(idxptr);  break;
    case  3 : set_level3_index(idxptr);  break;
    case  4 : set_level4_index(idxptr);  break;
    case  5 : set_level5_index(idxptr);  break;
    default : ;
  }

}

/******************************************************************************/
/**
\brief  ebshipt - 


\return term - Termination code

\param  odbptr -
\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshipt"

logical EB_MBHeader :: ebshipt (eb_SubBase *odbptr, acb *acbptr )
{
  uint64     bufpos;
  logical    term = NO;

BEGINSEQ
  if ( ebshipp(odbptr,acbptr,YES) )                  ERROR
  
  acbptr->ToPIF(platform_indep);
  
  if ( !odbptr->get_sb_netopt() )
  {
    bufpos = (acbptr->get_ebi_position() - *(uint64 *)low_ebi_buffer)/S_EBI;
    if ( bufpos >= 0 && bufpos < 256 )
    {
      *(low_ebi_buffer + 1 + acbptr->get_mb_ebsnum().Position(0)) = *acbptr;
      lebi_buffer_mod = YES;
      acbptr->FromPIF(platform_indep);
      LEAVESEQ
    }
  }
  
  term = odbptr->Update(0,acbptr->get_ebi_position(),S_EBI,acbptr);
  
  acbptr->FromPIF(platform_indep);
  if ( term )                                        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ebshiul - 


\return term - Termination code

\param  odbptr -
\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshiul"

logical EB_MBHeader :: ebshiul (eb_SubBase *odbptr, acb *acbptr )
{
  logical    term = NO;
BEGINSEQ
  if ( ebshipp(odbptr,acbptr,NO) )                   ERROR

  if ( odbptr->Unlock(0,acbptr->get_ebi_position(),S_EBI) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ebshngt - 


\return entnr -

\param  odbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ebshngt"

EB_Number EB_MBHeader :: ebshngt (eb_SubBase *odbptr )
{
  EB_Number     entnr(0);
  uint32        maxi = 0;

BEGINSEQ
  if ( odbptr->get_sb_netopt() )
    if ( Read() )                                     ERROR
  SDBRESET
/*
  if ( dnm_opt )
    if ( !(entnr = ebsn::ebsnget(odbptr,ebshnlst,odbptr->odbnogt())) )       
                                                      SDBCERR
*/
  if ( entnr.IsEmpty(platform_indep) )
  {
    if ( get_last_EBS_num().get_ebsnum() >= 281474976710655 ) // 0x0000FFFFFFFFFFFF
                                                     SDBERR(54)
    entnr = get_last_EBS_num().get_ebsnum()+1;
    set_last_EBS_num(entnr.get_ebsnum());
    stssmod();
  }
RECOVER

ENDSEQ
  return(entnr);  

}


