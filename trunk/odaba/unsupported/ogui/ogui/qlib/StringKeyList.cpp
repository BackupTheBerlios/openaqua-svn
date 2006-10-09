/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    StringKeyList



\date     $Date: 2006/03/13 21:36:26,35 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "StringKeyList"

#include  <pogui7.h>
#include  <sStringKeyList.hpp>


/******************************************************************************/
/**
\brief  OnCompare - 


\return

\param  pkey1 -
\param  pkey2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnCompare"

int32 StringKeyList :: OnCompare (void *pkey1, void *pkey2 )
{

  return ignoreCase 
         ? stricmp( (char*) pkey1, (char*) pkey2 ) 
         : strcmp( (char*) pkey1, (char*) pkey2 );


}

/******************************************************************************/
/**
\brief  OnFree - 



\param  pkey -
\param  pobj -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnFree"

void StringKeyList :: OnFree (void *pkey, void *pobj )
{

  if ( freeKey && pkey != NULL ) 
    free( pkey );
  if ( freeObj && pobj != NULL ) 
    free( pobj );

}

/******************************************************************************/
/**
\brief  OnInsert - 



\param  ppkey -
\param  ppitem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnInsert"

void StringKeyList :: OnInsert (void **ppkey, void **ppitem )
{

  if ( copyKey ) 
    *ppkey= strdup( (char*) *ppkey );

}

/******************************************************************************/
/**
\brief  StringKeyList - 



\param  fIgnoreCase -
\param  fCopyKey -
\param  fFreeKey -
\param  fFreeObj -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringKeyList"

                        StringKeyList :: StringKeyList (logical fIgnoreCase, logical fCopyKey, logical fFreeKey, logical fFreeObj )
                     : LookupList (),
  ignoreCase(NO),
  freeKey(NO),
  freeObj(NO),
  copyKey(NO)
{

ignoreCase= fIgnoreCase;
copyKey= fCopyKey;
freeKey= fFreeKey;
freeObj= fFreeObj;


}


