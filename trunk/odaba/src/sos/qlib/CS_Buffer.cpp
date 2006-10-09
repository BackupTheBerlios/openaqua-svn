/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Buffer

\brief    


\date     $Date: 2006/03/12 19:21:22,89 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_Buffer"

#include  <pdefault.h>
#include  <swinsock.hpp>
#include  <sCS_Buffer.hpp>


/******************************************************************************/
/**
\brief  AddBuf


\param  buf -
\param  valSize_t -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddBuf"

void CS_Buffer :: AddBuf (void *buf, size_t valSize_t )
{
  size_t   &len = valSize_t;
  Grow(wpos + len);

  if ( buf != NULL ) 
    memcpy(this->buf + wpos,buf,len);
  wpos += len;

  if ( wpos > size ) 
    size = wpos;

}

/******************************************************************************/
/**
\brief  AddINT64


\param  val64 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddINT64"

void CS_Buffer :: AddINT64 (int64 val64 )
{
  uint32  val_lo;
  uint32  val_hi;
  val_lo = val64;
  val_hi = val64 >> 32;

  Grow(wpos + 8);
  
  val_lo = htonl(val_lo);
  StoreLong(buf+wpos,val_lo);
  wpos += 4;
  
  val_hi = htonl(val_hi);
  StoreLong(buf+wpos,val_hi);
  wpos+= 4;
  
  if ( wpos > size ) 
    size = wpos;

}

/******************************************************************************/
/**
\brief  AddReserve


\param  valSize_t -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddReserve"

void CS_Buffer :: AddReserve (size_t valSize_t )
{
  size_t   &len = valSize_t;
  Grow(wpos + len);

}

/******************************************************************************/
/**
\brief  AddULONG


\param  val -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddULONG"

void CS_Buffer :: AddULONG (uint32 val )
{

  Grow(wpos + 4);
  
  val = htonl(val);
  StoreLong(buf+wpos,val);
  wpos += 4;

  if ( wpos > size ) 
    size = wpos;

}

/******************************************************************************/
/**
\brief  CS_Buffer

-------------------------------------------------------------------------------
\brief i0


\param  threshold -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Buffer"

                        CS_Buffer :: CS_Buffer (size_t threshold )
                     : vcls (),
  threshold(),
  size(0),
  buf(NULL),
  wpos(0),
  rpos(0),
  capacity(0)
{

  this->threshold = threshold;


}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Buffer"

                        CS_Buffer :: CS_Buffer ( )
                     : vcls (),
  threshold(0),
  size(0),
  buf(NULL),
  wpos(0),
  rpos(0),
  capacity(0)
{



}

/******************************************************************************/
/**
\brief  Clear - 



\param  forcefree -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void CS_Buffer :: Clear (logical forcefree )
{

  size = 0;
  rpos = 0;
  wpos = 0;

  if ( capacity > threshold || forcefree )
  {
    free(buf);
    buf      = NULL;
    capacity = 0;
  }


}

/******************************************************************************/
/**
\brief  GetBPtr

\return datarea -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBPtr"

char *CS_Buffer :: GetBPtr ( )
{

  return buf;

}

/******************************************************************************/
/**
\brief  GetBuf

\return buf -

\param  buf -
\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBuf"

void *CS_Buffer :: GetBuf (void *buf, size_t len )
{

  if ( buf != NULL ) 
    memcpy(buf,this->buf + rpos,len);
  rpos += len;

  return(buf);
}

/******************************************************************************/
/**
\brief  GetINT64

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetINT64"

int64 CS_Buffer :: GetINT64 ( )
{
  int64   res= 0;
  uint32  val_lo;
  uint32  val_hi;
  LoadLong(val_lo,buf+rpos);
  val_lo = ntohl(val_lo);
  rpos  += 4;

  LoadLong(val_hi,buf+rpos);
  val_hi = ntohl(val_hi);
  rpos  += 4;

  res = val_hi;
  res = ( res << 32 ) + val_lo;

  return(res);
}

/******************************************************************************/
/**
\brief  GetRLeft

\return position -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRLeft"

size_t CS_Buffer :: GetRLeft ( )
{

  return( size - rpos );

}

/******************************************************************************/
/**
\brief  GetRPos

\return position -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRPos"

size_t CS_Buffer :: GetRPos ( )
{

  return( rpos );

}

/******************************************************************************/
/**
\brief  GetRPtr

\return datarea -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRPtr"

char *CS_Buffer :: GetRPtr ( )
{

  return( buf + rpos );

}

/******************************************************************************/
/**
\brief  GetSize

\return len -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

size_t CS_Buffer :: GetSize ( )
{

  return( size );

}

/******************************************************************************/
/**
\brief  GetULONG

\return result -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetULONG"

uint32 CS_Buffer :: GetULONG ( )
{
  uint32    res;
  LoadLong(res,buf+rpos);
  res   = ntohl(res);
  rpos += 4;
  return(res);
}

/******************************************************************************/
/**
\brief  GetWPos

\return position -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWPos"

size_t CS_Buffer :: GetWPos ( )
{

  return( wpos );

}

/******************************************************************************/
/**
\brief  GetWPtr

\return datarea -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWPtr"

char *CS_Buffer :: GetWPtr ( )
{

  return( buf + wpos );


}

/******************************************************************************/
/**
\brief  Grow


\param  minsize -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Grow"

void CS_Buffer :: Grow (size_t minsize )
{
  size_t    newcapacity = capacity;
  if ( newcapacity < 16 ) 
    newcapacity = 16;

  while ( newcapacity < minsize ) 
    newcapacity *= 2;

  if ( newcapacity > capacity )
    buf = (char *)realloc(buf,newcapacity);

  capacity = newcapacity;


}

/******************************************************************************/
/**
\brief  HasRData

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasRData"

logical CS_Buffer :: HasRData ( )
{

  return( rpos < size );

}

/******************************************************************************/
/**
\brief  SetRPos


\param  valSize_t -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRPos"

void CS_Buffer :: SetRPos (size_t valSize_t )
{
  size_t   &pos = valSize_t;
  rpos = pos;

}

/******************************************************************************/
/**
\brief  SetSize


\param  valSize_t -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void CS_Buffer :: SetSize (size_t valSize_t )
{
  size_t     &len = valSize_t;
  Grow(len);
  size = len;


}

/******************************************************************************/
/**
\brief  SetThreshold

\return term - Success

\param  threshold -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetThreshold"

logical CS_Buffer :: SetThreshold (size_t threshold )
{

  this->threshold = threshold;
  return(NO);
}

/******************************************************************************/
/**
\brief  SetWPos


\param  valSize_t -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWPos"

void CS_Buffer :: SetWPos (size_t valSize_t )
{
  size_t    &pos = valSize_t;
  Grow(pos);
  wpos = pos;

}

/******************************************************************************/
/**
\brief  ~CS_Buffer


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CS_Buffer"

                        CS_Buffer :: ~CS_Buffer ( )
{

if( buf != NULL ) free( buf );
buf = NULL;

}


