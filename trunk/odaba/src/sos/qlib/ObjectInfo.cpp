/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    ObjectInfo



\date     $Date: 2006/04/28 19:40:18,79 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ObjectInfo"

#include  <pdefault.h>
#include  <oi.h>
#include  <sObjectInfo.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *ObjectInfo :: CastPointer (char *typenames )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetObjectType

\return typename

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectType"

char *ObjectInfo :: GetObjectType ( )
{

  return("ObjectInfo");

}

/******************************************************************************/
/**
\brief  ObjectInfo


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectInfo"

     ObjectInfo :: ObjectInfo ( )
                     : vcls()
{
}

/******************************************************************************/
/**
\brief  StaticCast

\return pointer

\param  oinfo
\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StaticCast"

void *__cdecl ObjectInfo :: StaticCast (ObjectInfo *oinfo, char *typenames )
{

  return(oinfo ? oinfo->CastPointer(typenames) : NULL);

}

/******************************************************************************/
/**
\brief  ~ObjectInfo

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ObjectInfo"

     ObjectInfo :: ~ObjectInfo ( )
{


}


