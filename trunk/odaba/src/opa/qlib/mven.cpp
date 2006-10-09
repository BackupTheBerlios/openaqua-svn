/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    mven



\date     $Date: 2006/05/24 13:13:52,57 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mven"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <smven.hpp>
#include  <smven.hpp>


/******************************************************************************/
/**
\brief  mvencntg

\return mvencnt - 

\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvencntg"

int32 mven :: mvencntg (logical pif )
{
 return (PIFToLong(mvencnt,pif));
}

/******************************************************************************/
/**
\brief  mvencnts


\param  count
\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvencnts"

void mven :: mvencnts (int32 count, logical pif )
{
 mvencnt = LongToPIF(count,pif);
}

/******************************************************************************/
/**
\brief  mvencrt

\return mvenptr - 

\param  klen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvencrt"

mven *__cdecl mven :: mvencrt (int16 klen )
{
  mven     *mvenptr;

BEGINSEQ

  if ( !(mvenptr = (mven *)new char[sizeof(mven)-2+klen]) )  SDBERR(95)
  mvenptr->mvenini(klen);

RECOVER
 

  return(mvenptr);

ENDSEQ

  return(mvenptr);

}

/******************************************************************************/
/**
\brief  mvendcr

\return mvencnt - 

\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvendcr"

int32 mven :: mvendcr (logical pif )
{
  if ( pif )
    mvencnt = LongToPIF(PIFToLong(mvencnt,pif)-1,pif);
  else
    --mvencnt;

  return(mvencnt);
}

/******************************************************************************/
/**
\brief  mvenicr

\return mvencnt - 

\param  pif
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvenicr"

int32 mven :: mvenicr (logical pif )
{
  int32     count;
  if ( pif )
    mvencnt = LongToPIF(PIFToLong(mvencnt,pif)+1,pif);
  else
    ++mvencnt;
  return(mvencnt);
}

/******************************************************************************/
/**
\brief  mvenini


\param  klen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvenini"

void mven :: mvenini (int16 klen )
{
  *(EB_Number *)this = 0;
  mvencnt = 0;
  memset(mvenkey,' ',klen);

}


