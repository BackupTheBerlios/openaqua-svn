/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extDAHeader

\brief    


\date     $Date: 2006/03/12 19:17:29,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_extDAHeader"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sEB_extDAHeader.hpp>


/******************************************************************************/
/**
\brief  EB_extDAHeader - 



\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_extDAHeader"

                        EB_extDAHeader :: EB_extDAHeader (uint16 len )
                     :   EB_extHeader(len),
  da_number(UNDEF), da_size(UNDEF), 
  next_position(len),
  version(CURRENT_VERSION)
{

  memset(eb_reserved,0,sizeof(eb_reserved));
  memset(reserved1,0,sizeof(reserved1));

}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EB_extDAHeader :: FromPIF (logical pif )
{

  if ( pif )
  {
    EB_extHeader::FromPIF(pif);
  
    set_da_number(PIFToShort(get_da_number(),pif));
    set_da_size(PIFToBig(get_da_size(),pif));
    set_version(PIFToShort(get_version(),pif));
    set_next_position(PIFToBig(get_next_position(),pif));
  }


}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void EB_extDAHeader :: ToPIF (logical pif )
{

  if ( pif )
  {
    EB_extHeader::ToPIF(pif);
  
    set_da_number(ShortToPIF(get_da_number(),pif));
    set_da_size(BigToPIF(get_da_size(),pif));
    set_version(ShortToPIF(get_version(),pif));
    set_next_position(BigToPIF(get_next_position(),pif));
  }
  
  


}

/******************************************************************************/
/**
\brief  get_da_number - 


\return da_number -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_da_number"

int16 EB_extDAHeader :: get_da_number ( )
{
  int16      sval;
  LoadShort(sval,&da_number)
  return(sval);
}

/******************************************************************************/
/**
\brief  get_da_size - 


\return da_size -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_da_size"

int64 EB_extDAHeader :: get_da_size ( )
{
  int64    bval;
  LoadBigInt(bval,&da_size)
  return(bval);
}

/******************************************************************************/
/**
\brief  get_next_position - 


\return next_position -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_next_position"

int64 EB_extDAHeader :: get_next_position ( )
{
  int64    bval;
  LoadBigInt(bval,&next_position)
  return(bval);
}

/******************************************************************************/
/**
\brief  get_version - 


\return version -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_version"

int16 EB_extDAHeader :: get_version ( )
{
  int16      sval;
  LoadShort(sval,&version)
  return(sval);
}

/******************************************************************************/
/**
\brief  set_da_number - 



\param  danumber - Number for DataArea
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_da_number"

void EB_extDAHeader :: set_da_number (uint16 danumber )
{

  StoreShort(&da_number,danumber);

}

/******************************************************************************/
/**
\brief  set_da_size - 



\param  dasize64 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_da_size"

void EB_extDAHeader :: set_da_size (int64 dasize64 )
{

  StoreBigInt(&da_size,dasize64);

}

/******************************************************************************/
/**
\brief  set_next_position - 



\param  position64 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_next_position"

void EB_extDAHeader :: set_next_position (uint64 position64 )
{

  StoreBigInt(&next_position,position64);

}

/******************************************************************************/
/**
\brief  set_version - 



\param  new_version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_version"

void EB_extDAHeader :: set_version (int16 new_version )
{

  StoreShort(&version,new_version);

}


