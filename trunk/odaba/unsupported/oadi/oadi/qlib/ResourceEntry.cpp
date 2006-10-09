/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ResourceEntry

\brief    


\date     $Date: 2006/03/13 21:33:21,42 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ResourceEntry"

#include  <poadi.h>
#include  <sBinArrayObjEntry.hpp>
#include  <sOResource.hpp>
#include  <sResourceEntry.hpp>


/******************************************************************************/
/**
\brief  Free


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Free"

void ResourceEntry :: Free ( )
{

  delete resource;
  resource = NULL;


}

/******************************************************************************/
/**
\brief  Initialize


\param  pOResource -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ResourceEntry :: Initialize (OResource *pOResource )
{

  if ( resource )
    Free();
    
  resource = pOResource;


}

/******************************************************************************/
/**
\brief  ResourceEntry - 



\param  objid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResourceEntry"

                        ResourceEntry :: ResourceEntry (int64 objid )
                     : obj_id(objid),
  resource(NULL)
{



}

/******************************************************************************/
/**
\brief  ~ResourceEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ResourceEntry"

                        ResourceEntry :: ~ResourceEntry ( )
{

  Free();

}


