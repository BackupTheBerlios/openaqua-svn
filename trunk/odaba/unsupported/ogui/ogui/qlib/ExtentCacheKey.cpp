/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ExtentCacheKey

\brief    


\date     $Date: 2006/03/13 21:35:03,56 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExtentCacheKey"

#include  <pogui7.h>
#include  <sExtentCacheKey.hpp>


/******************************************************************************/
/**
\brief  ExtentCacheKey - 



\param  _obhandle -
\param  rcsName -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtentCacheKey"

                        ExtentCacheKey :: ExtentCacheKey (DBObjectHandle &_obhandle, const std_string &rcsName )
                     : db(_obhandle),
  name(rcsName)
{



}

/******************************************************************************/
/**
\brief  operator== - 


\return cond -

\param  rcExtentCacheKey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical ExtentCacheKey :: operator== (const ExtentCacheKey &rcExtentCacheKey )
{

  DBObjectHandle  &kdb= *(DBObjectHandle *)&rcExtentCacheKey.db;
    
  return ( db   == kdb  && 
           name == rcExtentCacheKey.name );


}


