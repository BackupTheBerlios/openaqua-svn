/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extMBHeader

\brief    


\date     $Date: 2006/03/12 19:17:30,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_extMBHeader"

#include  <popa7.h>
#include  <cMBHdr.h>
class     MBHdr;
#include  <iNetConversion.h>
#include  <sEB_extMBHeader.hpp>


/******************************************************************************/
/**
\brief  ConvertTo3


\param  old_header
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertTo3"

void EB_extMBHeader :: ConvertTo3 (MBHdr *old_header )
{
  logical       pif;
  if ( get_version() < 3 || 
       PIFToShort(get_version(),YES) < 3 )
  {  
    platform_indep = old_header->platform_indep;
    mb_number = PIFToShort(old_header->mb_number,platform_indep);
    sb_count  = PIFToShort(old_header->sb_count,platform_indep);
    last_EBS_num = PIFToLong(old_header->last_EBS_num,platform_indep);
    free_EBS_Numbers = PIFToLong(old_header->free_EBS_Numbers,platform_indep);
    level0_index = PIFToLong(old_header->level0_index,platform_indep);
    level1_index = PIFToLong(old_header->level1_index,platform_indep);
    level2_index = PIFToLong(old_header->level2_index,platform_indep);
    level3_index = PIFToLong(old_header->level3_index,platform_indep);
    level4_index = 0;
    level5_index = 0;
    dnm_opt = old_header->dnm_opt;
    memset(reserved1,0,sizeof(reserved1));
    
    EB_extSBHeader::FromPIF(platform_indep);
  }
  else
    FromPIF();


}

/******************************************************************************/
/**
\brief  EB_extMBHeader - 



\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_extMBHeader"

                        EB_extMBHeader :: EB_extMBHeader (uint16 len )
                     :   EB_extSBHeader(len), 
  mb_number(0), 
  sb_count(1), 
  last_EBS_num(0), free_EBS_Numbers(0),
  level0_index(0), level1_index(0),
  level2_index(0), level3_index(0), 
  level4_index(0), level5_index(0), 
  dnm_opt(NO),
  platform_indep(NO)
{

  memset(reserved1,0,sizeof(reserved1));

}

/******************************************************************************/
/**
\brief  FromPIF - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EB_extMBHeader :: FromPIF ( )
{

  if ( platform_indep )
  {
    EB_extSBHeader::FromPIF(platform_indep);
  
    set_mb_number(PIFToShort(get_mb_number(),platform_indep));
    set_sb_count(PIFToShort(get_sb_count(),platform_indep));
  
    set_last_EBS_num(get_last_EBS_num().FromPIF(platform_indep));
    set_free_EBS_Numbers(get_free_EBS_Numbers().FromPIF(platform_indep));
    set_level0_index(get_level0_index().FromPIF(platform_indep));
    set_level1_index(get_level1_index().FromPIF(platform_indep));
    set_level2_index(get_level2_index().FromPIF(platform_indep));
    set_level3_index(get_level3_index().FromPIF(platform_indep));
    set_level4_index(get_level4_index().FromPIF(platform_indep));
    set_level5_index(get_level5_index().FromPIF(platform_indep));
  }


}

/******************************************************************************/
/**
\brief  SetLevelIndex


\param  entnr -
\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLevelIndex"

void EB_extMBHeader :: SetLevelIndex (EB_Number entnr, int16 lev )
{

  switch ( lev )
  {
    case  0 : set_level0_index(entnr);
              break;
    case  1 : set_level1_index(entnr);
              break;
    case  2 : set_level2_index(entnr);
              break;
    case  3 : set_level3_index(entnr);
              break;
    case  4 : set_level4_index(entnr);
              break;
    case  5 : set_level5_index(entnr);
              break;
    default : ;
  }


}

/******************************************************************************/
/**
\brief  ToPIF - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EB_extMBHeader :: ToPIF ( )
{

  if ( platform_indep )
  {
    EB_extSBHeader::ToPIF(platform_indep);
  
    set_mb_number(ShortToPIF(get_mb_number(),platform_indep));
    set_sb_count(ShortToPIF(get_sb_count(),platform_indep));
  
    set_last_EBS_num(get_last_EBS_num().ToPIF(platform_indep));
    set_free_EBS_Numbers(get_free_EBS_Numbers().ToPIF(platform_indep));
    set_level0_index(get_level0_index().ToPIF(platform_indep));
    set_level1_index(get_level1_index().ToPIF(platform_indep));
    set_level2_index(get_level2_index().ToPIF(platform_indep));
    set_level3_index(get_level3_index().ToPIF(platform_indep));
    set_level4_index(get_level4_index().ToPIF(platform_indep));
    set_level5_index(get_level5_index().ToPIF(platform_indep));
  }

}

/******************************************************************************/
/**
\brief  get_free_EBS_Numbers - 


\return free_EBS_Numbers -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_free_EBS_Numbers"

EB_Number EB_extMBHeader :: get_free_EBS_Numbers ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&free_EBS_Numbers)
  return(entnr);
}

/******************************************************************************/
/**
\brief  get_last_EBS_num - 


\return last_EBS_num -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_last_EBS_num"

EB_Number EB_extMBHeader :: get_last_EBS_num ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&last_EBS_num)
  return(entnr);
}

/******************************************************************************/
/**
\brief  get_level0_index - 


\return level0_index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_level0_index"

EB_Number EB_extMBHeader :: get_level0_index ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&level0_index)
  return(entnr);
}

/******************************************************************************/
/**
\brief  get_level1_index - 


\return level1_index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_level1_index"

EB_Number EB_extMBHeader :: get_level1_index ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&level1_index)
  return(entnr);
}

/******************************************************************************/
/**
\brief  get_level2_index - 


\return level2_index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_level2_index"

EB_Number EB_extMBHeader :: get_level2_index ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&level2_index)
  return(entnr);
}

/******************************************************************************/
/**
\brief  get_level3_index - 


\return level3_index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_level3_index"

EB_Number EB_extMBHeader :: get_level3_index ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&level3_index)

  return(entnr);
}

/******************************************************************************/
/**
\brief  get_level4_index

\return level3_index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_level4_index"

EB_Number EB_extMBHeader :: get_level4_index ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&level4_index)

  return(entnr);
}

/******************************************************************************/
/**
\brief  get_level5_index

\return level3_index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_level5_index"

EB_Number EB_extMBHeader :: get_level5_index ( )
{
  uint64      entnr;
  LoadBigInt(entnr,&level5_index)

  return(entnr);
}

/******************************************************************************/
/**
\brief  get_mb_number - 


\return mb_number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_mb_number"

int16 EB_extMBHeader :: get_mb_number ( )
{
  int16     sval;
  LoadShort(sval,&mb_number)
  return(sval);
}

/******************************************************************************/
/**
\brief  get_sb_count - 


\return sb_count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_sb_count"

int16 EB_extMBHeader :: get_sb_count ( )
{
  int16     sval;
  LoadShort(sval,&sb_count)
  return(sval);
}

/******************************************************************************/
/**
\brief  set_free_EBS_Numbers - 



\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_free_EBS_Numbers"

void EB_extMBHeader :: set_free_EBS_Numbers (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&free_EBS_Numbers,lval);

}

/******************************************************************************/
/**
\brief  set_last_EBS_num - 



\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_last_EBS_num"

void EB_extMBHeader :: set_last_EBS_num (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&last_EBS_num,lval);

}

/******************************************************************************/
/**
\brief  set_level0_index - 



\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level0_index"

void EB_extMBHeader :: set_level0_index (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&level0_index,lval);

}

/******************************************************************************/
/**
\brief  set_level1_index - 



\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level1_index"

void EB_extMBHeader :: set_level1_index (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&level1_index,lval);

}

/******************************************************************************/
/**
\brief  set_level2_index - 



\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level2_index"

void EB_extMBHeader :: set_level2_index (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&level2_index,lval);

}

/******************************************************************************/
/**
\brief  set_level3_index - 



\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level3_index"

void EB_extMBHeader :: set_level3_index (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&level3_index,lval);

}

/******************************************************************************/
/**
\brief  set_level4_index


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level4_index"

void EB_extMBHeader :: set_level4_index (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&level4_index,lval);

}

/******************************************************************************/
/**
\brief  set_level5_index


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level5_index"

void EB_extMBHeader :: set_level5_index (EB_Number entnr )
{
  uint64      lval = entnr.get_ebsnum();
  StoreBigInt(&level5_index,lval);

}

/******************************************************************************/
/**
\brief  set_mb_number - 



\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_mb_number"

void EB_extMBHeader :: set_mb_number (int16 mbnumber )
{

  StoreShort(&mb_number,mbnumber);
  if ( mbnumber ) 
    set_last_EBS_num(1);

}

/******************************************************************************/
/**
\brief  set_platform_indep - 



\param  pindep -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_platform_indep"

void EB_extMBHeader :: set_platform_indep (logical pindep )
{

  platform_indep = pindep;

}

/******************************************************************************/
/**
\brief  set_sb_count - 



\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_sb_count"

void EB_extMBHeader :: set_sb_count (int32 count )
{
  int16      sval = MAX(0,count);

  StoreShort(&sb_count,sval);

}


