/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    EBI



\date     $Date: 2006/05/04 19:21:41,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EBI"

#include  <popa7.h>
#include  <cEBIo.h>
#include  <sEBI.hpp>
#include  <iNetConversion.h>
#include  <sdb_RootBase.hpp>
#include  <seb_MainBase.hpp>
#include  <seb_RootBase.hpp>
#include  <seb_SubBase.hpp>
#include  <sEBI.hpp>


/******************************************************************************/
/**
\brief  CheckError - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckError"

logical EBI :: CheckError ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( mod_count == 0 )            
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Clear


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void EBI :: Clear ( )
{

  memset(this,0,S_EBI);

}

/******************************************************************************/
/**
\brief  ConvertTo3


\param  odbptr - 
\param  old_ebi
\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertTo3"

void EBI :: ConvertTo3 (eb_SubBase *odbptr, EBIo *old_ebi, logical pif )
{
  uint64         vpos;
  EBIo           voebi;
  EBI            vebi;
  *(bsts *)this = *old_ebi;

  vpos = 0;
  if ( old_ebi->version_list )
  {
    odbptr->Locate(0,PIFToLong(old_ebi->version_list,pif),20,&voebi);
    vebi.ConvertTo3(odbptr,&voebi,pif);
    vpos = odbptr->Append(S_EBI,S_EBI,0,&vebi);
  }

  mod_count     = old_ebi->mod_count;
  entry_length  = PIFToLong(old_ebi->entry_length,pif);
  da_position   = PIFToLong(old_ebi->da_position,pif);
  version_list  = vpos;
  version       = PIFToShort(old_ebi->version,pif);
  da_number     = 0;
  sb_number     = 0;
  access_rights = 0;

  ToPIF(pif);

}

/******************************************************************************/
/**
\brief  CreatePrevVersion

\return position64 - 

\param  odbptr - 
\param  version_nr - Internal version number
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePrevVersion"

uint64 EBI :: CreatePrevVersion (eb_SubBase *odbptr, uint16 version_nr, logical pif_opt )
{
  uint64                 position64 = 0;
BEGINSEQ
  version_list = 0; 
  SetPosition(0);
  
  ToPIF(pif_opt);
  position64 = odbptr->Append(S_EBI,S_EBI,0,this);
  FromPIF(pif_opt);
  if ( !position64 )                                 ERROR

RECOVER
  position64 = 0;
ENDSEQ
  return(position64);
}

/******************************************************************************/
/**
\brief  CreateVersionEBI

\return term - Termination code

\param  odbptr - 
\param  version_nr - Internal version number
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVersionEBI"

logical EBI :: CreateVersionEBI (eb_SubBase *odbptr, uint16 version_nr, logical pif_opt )
{
  uint64                position64 = 0;
  logical               term = NO;
BEGINSEQ
  if ( version_nr == USHORTMAX )
    version_nr = version+1; 
  if ( version_nr == USHORTMAX )                     SDBERR(177)
  if ( version_nr <= version )                       SDBERR(178)
  if ( stscold() )                                   SDBERR(179)

  stssold();
  ToPIF(pif_opt);
  position64 = odbptr->Append(S_EBI,S_EBI,0,this);
  FromPIF(pif_opt);
  if ( !position64 )                                 ERROR
 
  stsrold();
  version_list = position64; 
  version      = version_nr;
  SetPosition(0);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteVersionEBI

\return term - Termination code

\param  odbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteVersionEBI"

logical EBI :: DeleteVersionEBI (eb_SubBase *odbptr )
{
  logical    term = NO;
BEGINSEQ
  if ( !version_list )  
    memset(this,0,S_EBI);
  else
  {  
    if ( !odbptr->Locate(0,version_list,S_EBI,this)) ERROR
    odbptr->Delete(0,version_list);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EBI


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EBI"

     EBI :: EBI ( )
                     : bsts (),
  mod_count(UNDEF),
  entry_length(UNDEF),
  da_position(UNDEF),
  da_number(0),
  sb_number(0),
  version_list(0),
  version(0),
  access_rights(UNDEF)
{
}

/******************************************************************************/
/**
\brief  FromPIF


\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EBI :: FromPIF (logical pif )
{
  if ( pif )
  {  
    entry_length   = PIFToLong(entry_length,pif);   
    version        = PIFToShort(version,pif);
    mod_count      = PIFToShort(mod_count,pif);
    version_list   = PIFToBig(version_list,pif);   
    if ( !stscusr2() )    // nur, wenn nicht geclustert
      da_position  = PIFToBig(da_position,pif);   
  }

}

/******************************************************************************/
/**
\brief  GetPosition

\return position64 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

int64 EBI :: GetPosition ( )
{

  return( da_position );


}

/******************************************************************************/
/**
\brief  GetPrevEBI

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  odbptr - 
\param  version_nr - Internal version number
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevEBI"

logical EBI :: GetPrevEBI (eb_SubBase *odbptr, uint16 version_nr, logical pif_opt )
{
  logical                 term = NO;
BEGINSEQ
  if ( version_nr == USHORTMAX )
    version_nr = version ? version -1 : 0; 
    
  while ( version_nr < version )  
  {
    if ( !version_list )      
    {
      stssnof();
      stssdel();
      stssold();
      LEAVESEQ
    }
    if ( !odbptr->Locate(0,version_list,S_EBI,this)) ERROR
    FromPIF(pif_opt);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  rootbase - 
\param  version_nr - Internal version number
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevEBI"

logical EBI :: GetPrevEBI (db_RootBase *rootbase, uint16 version_nr, logical pif_opt )
{
  eb_MainBase       *mainbase;
  eb_SubBase        *subbase = NULL;
  logical            term    = NO;
BEGINSEQ
  if ( !rootbase )                                   ERROR
  if ( mainbase = ((eb_RootBase *)rootbase)->GetMainBase(0) )
    subbase = mainbase->GetSubBase(0);

  if ( !subbase )                                    SDBERR(99)

  term = GetPrevEBI(subbase,version_nr,pif_opt);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetStatus - 


\return ebi_status

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStatus"

int16 EBI :: GetStatus ( )
{
  EBI           emp_ebi;
  int16         status = UNDEF;
  if ( NewEntry() )
    status = 3;
  else if ( da_position )
    status = 2;
  else if ( !memcmp(this,&emp_ebi,S_EBI) )
    status = 1;
  return(status);
}

/******************************************************************************/
/**
\brief  HasData

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasData"

logical EBI :: HasData ( )
{

  return( !stscdel() && da_position );

}

/******************************************************************************/
/**
\brief  NewEntry

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewEntry"

logical EBI :: NewEntry ( )
{

  return ( stscwpt(2) || (stscold() && !da_position) );

}

/******************************************************************************/
/**
\brief  ResetVersionList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetVersionList"

void EBI :: ResetVersionList ( )
{

  version_list = 0;

}

/******************************************************************************/
/**
\brief  ResetWProtect


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

void EBI :: ResetWProtect ( )
{

  if ( stscwpt(1) )
  {
    stsrwpt(1);
    stssmod();
  }


}

/******************************************************************************/
/**
\brief  SetDANumber


\param  danumber - Number for DataArea
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDANumber"

void EBI :: SetDANumber (uint16 danumber )
{

  da_number = danumber;
}

/******************************************************************************/
/**
\brief  SetPosition


\param  position64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void EBI :: SetPosition (uint64 position64 )
{

  da_position = position64;

}

/******************************************************************************/
/**
\brief  SetSBNumber


\param  sbnumber - SubBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSBNumber"

void EBI :: SetSBNumber (uint16 sbnumber )
{

  sb_number = sbnumber;
}

/******************************************************************************/
/**
\brief  SetVersion


\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void EBI :: SetVersion (uint16 version_nr )
{
  version = version_nr;
}

/******************************************************************************/
/**
\brief  SetVersionList


\param  position64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersionList"

void EBI :: SetVersionList (uint64 position64 )
{

  version_list = position64;

}

/******************************************************************************/
/**
\brief  SetWProtect


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

void EBI :: SetWProtect ( )
{
  if ( !stscwpt(1) )
  {
    stsawpt(1);
    stssmod();
  }

}

/******************************************************************************/
/**
\brief  ToPIF


\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EBI :: ToPIF (logical pif )
{
  if ( pif )
  {  
    entry_length   = LongToPIF(entry_length,pif);   
    version        = ShortToPIF(version,pif);
    mod_count      = ShortToPIF(mod_count,pif);
    version_list   = BigToPIF(version_list,pif);   
    if ( !stscusr2() )    // nur, wenn nicht geclustert
      da_position    = BigToPIF(da_position,pif);   
  }
}

/******************************************************************************/
/**
\brief  UpdateModCount


\param  modcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateModCount"

void EBI :: UpdateModCount (int16 modcount )
{
  if ( mod_count != (uint8)modcount )
  {
    mod_count = (uint8)modcount;
    stssmod();
  }

}


