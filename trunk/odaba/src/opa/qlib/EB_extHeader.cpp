/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extHeader

\brief    


\date     $Date: 2006/03/12 19:17:29,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_extHeader"

#include  <fileacc.h>
#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sEB_extHeader.hpp>


/******************************************************************************/
/**
\brief  EB_extHeader - 



\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_extHeader"

                        EB_extHeader :: EB_extHeader (uint16 len )
                     :  reserved0(0),
 mod_count(0),
 header_length(len)
{



}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void EB_extHeader :: FromPIF (logical pif )
{

  if ( pif )
  {
    set_mod_count(PIFToShort(get_mod_count(),pif));
    set_header_length(PIFToShort(get_header_length(),pif));
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

void EB_extHeader :: ToPIF (logical pif )
{

  if ( pif )
  {
    set_mod_count(ShortToPIF(get_mod_count(),pif));
    set_header_length(ShortToPIF(get_header_length(),pif));
  }


}

/******************************************************************************/
/**
\brief  get_header_length - 


\return len -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_header_length"

uint16 EB_extHeader :: get_header_length ( )
{
  int16      sval;
  LoadShort(sval,&header_length)
  return(sval);
}

/******************************************************************************/
/**
\brief  get_mod_count - 


\return modcount -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_mod_count"

int16 EB_extHeader :: get_mod_count ( )
{
  int16      sval;
  LoadShort(sval,&mod_count)
  return(sval);
}

/******************************************************************************/
/**
\brief  set_header_length - 



\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_header_length"

void EB_extHeader :: set_header_length (uint16 len )
{

  StoreShort(&header_length,len);

}

/******************************************************************************/
/**
\brief  set_mod_count - 



\param  modcount -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_mod_count"

void EB_extHeader :: set_mod_count (int16 modcount )
{

  StoreShort(&mod_count,modcount);

}


