/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    gvtc



\date     $Date: 2006/03/12 19:22:30,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "gvtc"

#include  <pdefault.h>
#include  <czlib.h>

#include  <igvtc.h>

/******************************************************************************/
/**
\brief  Pack

\return term - Success

\param  dest_buffer -
\param  pdest_size -
\param  source_buffer -
\param  source_size -
\param  level_AUTO -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pack"

logical __cdecl Pack (void *dest_buffer, size_t *pdest_size, void *source_buffer, size_t source_size, int level_AUTO )
{
  uLongf           dl   = *pdest_size;
  logical                 term = NO;
BEGINSEQ
  if ( level_AUTO < -1 || level_AUTO > 9 ) 
    level_AUTO= -1;

  switch ( compress2((Bytef*)dest_buffer,&dl,(Bytef*)source_buffer,source_size,level_AUTO) )
  {
    case Z_OK        : LEAVESEQ
    case Z_BUF_ERROR : SOSERR(201)
    case Z_MEM_ERROR : SOSERR(95)
    default : ;
  }
RECOVER
  term = YES;
ENDSEQ
  *pdest_size= dl;
  return(term);
}

/******************************************************************************/
/**
\brief  Unpack

\return term - Success

\param  dest_buffer -
\param  pdest_size -
\param  source_buffer -
\param  source_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unpack"

logical __cdecl Unpack (void *dest_buffer, size_t *pdest_size, void *source_buffer, size_t source_size )
{
  uLongf           dl   = *pdest_size;
  logical          term = NO;
BEGINSEQ
  switch ( uncompress((Bytef*)dest_buffer,&dl,(Bytef*)source_buffer,source_size) )
  {
    case Z_OK        : LEAVESEQ
    case Z_BUF_ERROR : SOSERR(201)
    case Z_MEM_ERROR : SOSERR(95)
    default : ;
  }
RECOVER
  term = YES;
ENDSEQ
  *pdest_size= dl;
  return(term);
}

