/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NBuffer

\brief    


\date     $Date: 2006/03/12 19:21:45,53 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NBuffer"

#include  <pdefault.h>
#include  <sNBuffer.hpp>


/******************************************************************************/
/**
\brief  AddBuffer

\return buffer -

\param  buffer -
\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddBuffer"

char *NBuffer :: AddBuffer (char *buffer, size_t len )
{
  int32            nlen = get_cur_size() + len;
  char            *pos;
BEGINSEQ
  if ( !buffer || !len )                             LEAVESEQ
  if ( Resize(nlen,resize) )                         LEAVESEQ
    
  memcpy(pos = area+cur_size,buffer,len);
  cur_size = nlen;
  area[cur_size] = 0;

ENDSEQ
  return(pos);
}

/******************************************************************************/
/**
\brief  Cut

\return term - Success

\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cut"

logical NBuffer :: Cut (size_t len )
{
  logical                 term = NO;
BEGINSEQ
  if ( len > cur_size )                              LEAVESEQ

  cur_size = len;
  if ( area )
    area[cur_size] = 0;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCurrentSize

\return size -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentSize"

int32 NBuffer :: GetCurrentSize ( )
{

  return(area ? cur_size : 0);

}

/******************************************************************************/
/**
\brief  NBuffer

-------------------------------------------------------------------------------
\brief i0


\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NBuffer"

                        NBuffer :: NBuffer (int32 res_val )
                     :  NBase (),
  cur_size(0),
  resize(res_val)
{

  cur_size = 0;


}

/******************************************************************************/
/**
\brief i01


\param  string - String value
\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NBuffer"

                        NBuffer :: NBuffer (char *string, int32 res_val )
                     :  NBase (),
  cur_size(0),
  resize(res_val)
{

  cur_size = 0;
  SetBuffer(string,strlen(string));

}

/******************************************************************************/
/**
\brief i02


\param  buffer -
\param  len -
\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NBuffer"

                        NBuffer :: NBuffer (char *buffer, size_t len, int32 res_val )
                     :  NBase (),
  cur_size(0),
  resize(res_val)
{

  cur_size = 0;
  SetBuffer(buffer,len);

}

/******************************************************************************/
/**
\brief i03


\param  nbuffer -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NBuffer"

                        NBuffer :: NBuffer (NBuffer &nbuffer )
                     :  NBase (),
  cur_size(0)
{

  cur_size = 0;
  SetBuffer(nbuffer,nbuffer.get_cur_size());

}

/******************************************************************************/
/**
\brief i04


\param  len -
\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NBuffer"

                        NBuffer :: NBuffer (size_t len, int32 res_val )
                     :  NBase (),
  cur_size(0),
  resize(res_val)
{

  cur_size = 0;
  Resize(len);

}

/******************************************************************************/
/**
\brief  SetBuffer

\return string - String value

\param  buffer -
\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBuffer"

char *NBuffer :: SetBuffer (char *buffer, size_t len )
{

BEGINSEQ
  if ( Resize(len,resize) )                        LEAVESEQ
    
  cur_size = len;
  if ( !buffer || !len )
    cur_size = 0;
  else
    memcpy(area,buffer,len);
  
  area[cur_size] = 0;

ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  operator+=

\return term - Success
-------------------------------------------------------------------------------
\brief i00


\param  nbuffer -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NBuffer :: operator+= (NBuffer &nbuffer )
{

  return(AddBuffer(nbuffer,nbuffer.get_cur_size()) ? NO : YES);


}

/******************************************************************************/
/**
\brief i01


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NBuffer :: operator+= (char *string )
{

  return(AddBuffer(string,string ? strlen(string) : 0) ? NO : YES);

}

/******************************************************************************/
/**
\brief  operator= - Assign string buffer
        When assigning a string buffer the area is copied conpletely.

\return string - String value
-------------------------------------------------------------------------------
\brief i00


\param  nbuffer -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

char *NBuffer :: operator= (NBuffer &nbuffer )
{

  return(SetBuffer(nbuffer,nbuffer.get_cur_size()));

}

/******************************************************************************/
/**
\brief i01


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

char *NBuffer :: operator= (char *string )
{

  return(SetBuffer(string,string ? strlen(string) : 0));

}

/******************************************************************************/
/**
\brief  ~NBuffer


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~NBuffer"

                        NBuffer :: ~NBuffer ( )
{



}


