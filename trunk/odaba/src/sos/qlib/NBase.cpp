/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    NBase

\brief    Base class for text and text array buffer
          The  buffer  is  allocating  dynamical  space for the text. It expands
          whenever  necessary.  The  buffer  guarantees  that  there is always a
          terminating 0 at the end of the buffer.

\date     $Date: 2006/07/28 11:53:17,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NBase"

#include  <pdefault.h>
#include  <sNBase.hpp>


/******************************************************************************/
/**
\brief  GetArea - 



\return area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

char *NBase :: GetArea ( )
{

  if ( !area )
    Resize(64);
  return(area);

}

/******************************************************************************/
/**
\brief  GetSize - Get total buffer size

        The  function returns the  text size allocated  for the buffer. The used
        size can be retrieved with GetCurrentSize().

\return size - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

size_t NBase :: GetSize ( )
{

  return(size);

}

/******************************************************************************/
/**
\brief  Initialize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void NBase :: Initialize ( )
{

  if ( area )
    msmfs((void **)&area);
  size = 0;
  area = NULL;

}

/******************************************************************************/
/**
\brief  IsEmpty - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical NBase :: IsEmpty ( )
{

  return ( !area ? YES : NO );

}

/******************************************************************************/
/**
\brief  NBase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NBase"

     NBase :: NBase ( )
                     : size(0),
  area(NULL)
{



}

/******************************************************************************/
/**
\brief  Resize - 



\return term - Success

\param  len - 
\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Resize"

logical NBase :: Resize (size_t len, int32 res_val )
{
//  char                   *oldarea = area;
  int32                   oldsize = size;
  logical                 term = NO;
BEGINSEQ
  if ( size < len || !size )
  {
    size = MAX(len,ID_SIZE);
    if ( res_val < 0 )
      size += size*(-res_val)/100;   
    if ( res_val > 0 )
      size += res_val;
    if ( !area )
      area = (char *)msmgs(size+1);
    else
      msmcs((void **)&area,size+1);
    if ( !area )                                     SOSERR(95)
/*      
    if ( !(area = new char[size+1]) )                SOSERR(95)
    memset(area,0,size+1);
    if ( oldarea )
      memcpy(area,oldarea,MIN(size,oldsize));
    delete oldarea;
*/
  }

RECOVER
  term = YES;
ENDSEQ
  return(!area);
}

/******************************************************************************/
/**
\brief  operator ! - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator !"

logical NBase :: operator ! ( )
{

  return(IsEmpty());

}

/******************************************************************************/
/**
\brief  operator char* - 



\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator char*"

NOTYPE NBase :: operator char* ( )
{

  return(GetArea());

}

/******************************************************************************/
/**
\brief  ~NBase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~NBase"

     NBase :: ~NBase ( )
{

  if ( area )
    msmfs((void **)&area);
//  delete area;
//  area = NULL;
  size = 0;

}


