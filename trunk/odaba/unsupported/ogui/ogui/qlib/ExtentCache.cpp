/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ExtentCache

\brief    


\date     $Date: 2006/03/13 21:35:03,40 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExtentCache"

#include  <pogui7.h>
#include  <zlib.h>
#include  <sExtentCacheKey.hpp>
#include  <sHashTable.hpp>
#include  <sExtentCache.hpp>


/******************************************************************************/
/**
\brief  DoAdd - 



\param  ppkey -
\param  ppitem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAdd"

void ExtentCache :: DoAdd (void **ppkey, void **ppitem )
{

  *ppkey = new ExtentCacheKey(*(ExtentCacheKey *)*ppkey);


}

/******************************************************************************/
/**
\brief  DoCompare - 


\return cmpval -

\param  pkey1 -
\param  pkey2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCompare"

int ExtentCache :: DoCompare (void *pkey1, void *pkey2 )
{
  ExtentCacheKey  *a = (ExtentCacheKey *)pkey1;
  ExtentCacheKey  *b = (ExtentCacheKey *)pkey2;

  return *a == *b ? 0 : 1;


}

/******************************************************************************/
/**
\brief  DoDelete - 



\param  pkey -
\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoDelete"

void ExtentCache :: DoDelete (void *pkey, void *pitem )
{

  if ( pkey ) 
    delete (ExtentCacheKey *)pkey;
    
  if ( pitem ) 
    delete (PropertyHandle *)pitem;


}

/******************************************************************************/
/**
\brief  DoHash - 


\return indxu -

\param  pkey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoHash"

uint32 ExtentCache :: DoHash (void *pkey )
{
  ExtentCacheKey  *k = (ExtentCacheKey *)pkey;
  int              kl;
  kl = k->name.length();
   
  return crc32(kl,(const unsigned char *)(kl ? k->name.data() : ""),kl);


}


