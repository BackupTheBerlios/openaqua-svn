/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ObjectReferenceHandle



\date     $Date: 2006/05/31 18:10:36,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ObjectReferenceHandle"

#include  <pdefault.h>
#include  <sObjectReference.hpp>
#include  <sObjectReferenceHandle.hpp>


/******************************************************************************/
/**
\brief  Close

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ObjectReferenceHandle :: Close ( )
{
  logical                 term = NO;
  if ( object_handle )
    object_handle->Release(this);
  object_handle = NULL;

  return(term);
}

/******************************************************************************/
/**
\brief  ObjectReferenceHandle

-------------------------------------------------------------------------------
\brief  i0


\param  obj_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectReferenceHandle"

     ObjectReferenceHandle :: ObjectReferenceHandle (ObjectReference *obj_ref )
                     : object_handle(NULL)
{
  Open(obj_ref);
}

/******************************************************************************/
/**
\brief  i01


\param  obref_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectReferenceHandle"

     ObjectReferenceHandle :: ObjectReferenceHandle (ObjectReferenceHandle &obref_handle )
                     : object_handle(NULL)
{
  Open(obref_handle.object_handle);
}

/******************************************************************************/
/**
\brief  i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectReferenceHandle"

     ObjectReferenceHandle :: ObjectReferenceHandle ( )
                     : object_handle(NULL)
{
}

/******************************************************************************/
/**
\brief  Open

\return term - Success

\param  obj_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ObjectReferenceHandle :: Open (ObjectReference *obj_ref )
{
  logical                 term = NO;
BEGINSEQ
  if ( object_handle == obj_ref )                 LEAVESEQ
    
  Close();
   
  if ( object_handle = obj_ref )
    object_handle->Reserve(this);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  operator!=

\return cond - Return value

\param  obref_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical ObjectReferenceHandle :: operator!= (ObjectReferenceHandle &obref_handle )
{

  return ( !(*this == obref_handle) );


}

/******************************************************************************/
/**
\brief  operator=

\return objref_handle

\param  obref_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

ObjectReferenceHandle &ObjectReferenceHandle :: operator= (ObjectReferenceHandle &obref_handle )
{

  Open(obref_handle.get_object_handle());

  return(*this);
}

/******************************************************************************/
/**
\brief  operator==

\return cond - Return value

\param  obref_handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical ObjectReferenceHandle :: operator== (ObjectReferenceHandle &obref_handle )
{

  return ( this && &obref_handle &&
           object_handle == obref_handle.get_object_handle()
           ? YES : NO );



}

/******************************************************************************/
/**
\brief  set_object_handle


\param  obj_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_object_handle"

void ObjectReferenceHandle :: set_object_handle (ObjectReference *obj_ref )
{

  object_handle = obj_ref;

}

/******************************************************************************/
/**
\brief  ~ObjectReferenceHandle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ObjectReferenceHandle"

     ObjectReferenceHandle :: ~ObjectReferenceHandle ( )
{
}


