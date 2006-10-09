/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_extSBHeader

\brief    


\date     $Date: 2006/03/12 19:17:31,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_extSBHeader"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sEB_extSBHeader.hpp>


/******************************************************************************/
/**
\brief  EB_extSBHeader - 



\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_extSBHeader"

                        EB_extSBHeader :: EB_extSBHeader (uint16 len )
                     :   EB_extDAHeader(len), 
  sb_number(0), act_da(UNDEF), da_count(1),
  max_entry_size(UNDEF)
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

void EB_extSBHeader :: FromPIF (logical pif )
{

  if ( pif )
  {
    EB_extDAHeader::FromPIF(pif);
  
    set_sb_number(PIFToShort(get_sb_number(),pif));
    set_act_da(PIFToShort(get_act_da(),pif));
    set_da_count(PIFToShort(get_da_count(),pif));
    set_max_entry_size(PIFToLong(get_max_entry_size(),pif));
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

void EB_extSBHeader :: ToPIF (logical pif )
{

  if ( pif )
  {
    EB_extDAHeader::ToPIF(pif);
  
    set_sb_number(ShortToPIF(get_sb_number(),pif));
    set_act_da(ShortToPIF(get_act_da(),pif));
    set_da_count(ShortToPIF(get_da_count(),pif));
    set_max_entry_size(LongToPIF(get_max_entry_size(),pif));
  }
  


}

/******************************************************************************/
/**
\brief  get_act_da - 


\return act_da -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_act_da"

int16 EB_extSBHeader :: get_act_da ( )
{
  int16    sval;
  LoadShort(sval,&act_da)
  return(sval);
}

/******************************************************************************/
/**
\brief  get_da_count - 


\return da_count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_da_count"

int16 EB_extSBHeader :: get_da_count ( )
{
  int16    sval;
  LoadShort(sval,&da_count)
  return(sval);
}

/******************************************************************************/
/**
\brief  get_max_entry_size - 


\return max_entry_size -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_max_entry_size"

int32 EB_extSBHeader :: get_max_entry_size ( )
{
  int32    lval;
  LoadLong(lval,&max_entry_size)
  return(lval);
}

/******************************************************************************/
/**
\brief  get_sb_number - 


\return sb_number -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_sb_number"

int16 EB_extSBHeader :: get_sb_number ( )
{
  int16    sval;
  LoadShort(sval,&sb_number)
  return(sval);
}

/******************************************************************************/
/**
\brief  set_act_da - 



\param  actda -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_act_da"

void EB_extSBHeader :: set_act_da (int16 actda )
{

  StoreShort(&act_da,actda);

}

/******************************************************************************/
/**
\brief  set_da_count - 



\param  dacount -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_da_count"

void EB_extSBHeader :: set_da_count (int32 dacount )
{
  int16      sval = MAX(0,dacount);
  StoreShort(&da_count,sval);

}

/******************************************************************************/
/**
\brief  set_max_entry_size - 



\param  entrysize -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_max_entry_size"

void EB_extSBHeader :: set_max_entry_size (int32 entrysize )
{

  StoreLong(&max_entry_size,entrysize);

}

/******************************************************************************/
/**
\brief  set_sb_number - 



\param  sbnumber - SubBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_sb_number"

void EB_extSBHeader :: set_sb_number (uint16 sbnumber )
{

  StoreShort(&sb_number,sbnumber);

}


