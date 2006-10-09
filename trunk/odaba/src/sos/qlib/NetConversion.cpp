/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NetConversion

\brief    


\date     $Date: 2006/03/12 19:21:47,75 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NetConversion"

#include  <pdefault.h>
#include  <cwinsock.h>

#include  <iNetConversion.h>

/******************************************************************************/
/**
\brief  BigToPIF

\return big_val -

\param  big_val -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BigToPIF"

int64 __cdecl BigToPIF (int64 big_val, logical convert )
{
  int32        val_lo = big_val;
  int32        val_hi = big_val >> 32;
  int64        bval;
  if ( !convert )
    return(big_val);
    
  *(int32 *)&bval       = htonl(val_hi);
  *(((int32 *)&bval)+1) = htonl(val_lo);
  
  return(bval);


}

/******************************************************************************/
/**
\brief  LongToPIF

\return long_val -

\param  long_val -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LongToPIF"

int32 __cdecl LongToPIF (int32 long_val, logical convert )
{

  if ( convert )
    return(htonl(long_val));
  return(long_val);


}

/******************************************************************************/
/**
\brief  PIFToBig

\return big_val -

\param  big_val -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PIFToBig"

int64 __cdecl PIFToBig (int64 big_val, logical convert )
{
  int32        val_hi = *(int32 *)&big_val;
  int32        val_lo = *(((int32 *)&big_val)+1);
  int64      bval;
  if ( !convert )
    return(big_val);
/*
  val_lo = ntohl(val_lo);
  val_hi = ntohl(val_hi);
  bval = val_hi;
  bval = ( bval << 32 ) + val_lo;
*/  
  *(int32 *)&bval       = ntohl(val_lo);
  *(((int32 *)&bval)+1) = ntohl(val_hi);
  
  return(bval);


}

/******************************************************************************/
/**
\brief  PIFToLong

\return long_val -

\param  long_val -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PIFToLong"

int32 __cdecl PIFToLong (int32 long_val, logical convert )
{

  if ( convert )
    return(ntohl(long_val));
  return(long_val);


}

/******************************************************************************/
/**
\brief  PIFToShort

\return short_val -

\param  short_val -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PIFToShort"

int16 __cdecl PIFToShort (int16 short_val, logical convert )
{

  if ( convert )
    return(ntohs(short_val));
  return(short_val);


}

/******************************************************************************/
/**
\brief  ShortToPIF

\return short_val -

\param  short_val -
\param  convert -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShortToPIF"

int16 __cdecl ShortToPIF (int16 short_val, logical convert )
{

  if ( convert )
    return(htons(short_val));
  return(short_val);


}

