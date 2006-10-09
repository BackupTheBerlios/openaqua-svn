/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    StringHashTable



\date     $Date: 2006/03/12 19:21:59,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "StringHashTable"

#include  <pdefault.h>
#include  <zlib.h>
#include  <sStringHashTable.hpp>


/******************************************************************************/
/**
\brief  DoCompare

\return term - Success

\param  pvoidKey1 -
\param  pvoidKey2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCompare"

int StringHashTable :: DoCompare (void *pvoidKey1, void *pvoidKey2 )
{

return strcmp( (char*) pvoidKey1, (char*) pvoidKey2 );

}

/******************************************************************************/
/**
\brief  DoHash

\return term - Success

\param  pvoidKey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoHash"

uint32 StringHashTable :: DoHash (void *pvoidKey )
{

int kl= strlen( (char*) pvoidKey );
return crc32( kl, (unsigned char*) pvoidKey, kl );

}

/******************************************************************************/
/**
\brief  StringHashTable

\return term - Success
-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringHashTable"

                        StringHashTable :: StringHashTable ( )
                     : HashTable()
{



}

/******************************************************************************/
/**
\brief i01


\param  len -
\param  fAutoRehash -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringHashTable"

                        StringHashTable :: StringHashTable (size_t len, logical fAutoRehash )
                     : HashTable( len, fAutoRehash )
{



}


