/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_Number

\brief    Entry number
          A  database entry number is a  64-Bit number, which contains the entry
          number  in 48  low order  bytes. 15  high order bytes are reserved for
          database  and mainbase numbers. The top high  order byte is a flag and
          reserved for internal use. 
          0xFFFF0000  in the 32 high order bytes indicates an empty entry number
          regardless on the remaining part of the number.

\date     $Date: 2006/03/12 19:17:28,60 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EB_Number"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sEB_Number.hpp>


/******************************************************************************/
/**
\brief  EB_Number - 


-------------------------------------------------------------------------------
\brief i0


\param  ebsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EB_Number"

                        EB_Number :: EB_Number (uint64 ebsnumber )
                     :   ebsnum(ebsnumber)
{



}

/******************************************************************************/
/**
\brief  FromPIF - 


\return entnr -

\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

EB_Number EB_Number :: FromPIF (logical pif )
{

  return(ebsnum = PIFToBig(ebsnum,pif));

}

/******************************************************************************/
/**
\brief  GetLevel - 


\return ebilevel -

\param  largedb - Indicates a large database
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLevel"

int16 EB_Number :: GetLevel (logical largedb )
{
  int16     lev;
  lev = ebsnum > 1099511627775 ? 5 : 
        ebsnum > 4294967295    ? 4 : 
        ebsnum > 16777215      ? 3 : 
        ebsnum > 65535         ? 2 : 
        ebsnum > 255           ? 1 : 0;
  if ( largedb )
    lev /= 2;


  return(lev);
}

/******************************************************************************/
/**
\brief  GetLockPos - 


\return position64 -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLockPos"

int64 EB_Number :: GetLockPos ( )
{

  return((-(ebsnum<<32)>>32));

// can't lock EBI-numbers greater than 0x7ffffffff at the moment (_loking fails)
// finally, the code should look like
//  return((-(ebsnum<<16)>>16));

}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

\param  pif_opta
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical EB_Number :: IsEmpty (logical pif_opta )
{
  uint64        num = ebsnum;
  switch ( pif_opta )
  {
    case  YES : num = PIFToBig(num,YES);
    case  NO  : return ( num == 0 || 
                         (num >> 32) == 0xffffffff // sollte 0xffff sein (>>48), geht noch nicht, wegen enums
                         || num == 0x20202020 // for V5a, only
                         ? YES : NO );
    default   : return ( num == 0 ? YES : NO );
  }

//  return ( ebsnum == 0 || (ebsnum >> 24) == 255 ? YES : NO );

}

/******************************************************************************/
/**
\brief  Position - 


\return index_pos -

\param  ebilevel -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

uint16 EB_Number :: Position (int16 ebilevel )
{

  return( (uint16)((ebsnum << (7-ebilevel)*8) >> 56) );

}

/******************************************************************************/
/**
\brief  SetPosition - 



\param  ebilevel -
\param  position - Position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void EB_Number :: SetPosition (int16 ebilevel, int32 position )
{
  uint64       left_rest;
  uint64       right_rest;
  left_rest = (ebsnum << (8-ebilevel)*8) >> (8-ebilevel)*8;
  right_rest = (ebsnum >> (ebilevel+1)*8) << (ebilevel+1)*8;
  ebsnum = position;
  ebsnum = (ebsnum << ebilevel*8) + left_rest + right_rest;

}

/******************************************************************************/
/**
\brief  ToPIF - 


\return entnr -

\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

EB_Number EB_Number :: ToPIF (logical pif )
{

  return(ebsnum = BigToPIF(ebsnum,pif));

}

/******************************************************************************/
/**
\brief  operator++ - 


\return entnr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator++"

EB_Number EB_Number :: operator++ ( )
{

  return(++ebsnum);

}

/******************************************************************************/
/**
\brief  operator<= - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical EB_Number :: operator<= (EB_Number entnr )
{

  return( ebsnum <= entnr.get_ebsnum() );


}

/******************************************************************************/
/**
\brief i01


\param  entnr_val
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical EB_Number :: operator<= (uint64 entnr_val )
{

  return( ebsnum <= entnr_val );

}

/******************************************************************************/
/**
\brief  operator= - 


\return entnr -
-------------------------------------------------------------------------------
\brief i0


\param  entnr_val
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

EB_Number EB_Number :: operator= (uint64 entnr_val )
{

  ebsnum = entnr_val;
  return ( *this );

}

/******************************************************************************/
/**
\brief i1


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

EB_Number EB_Number :: operator= (EB_Number entnr )
{

  ebsnum = entnr.get_ebsnum();
  return ( *this );

}


