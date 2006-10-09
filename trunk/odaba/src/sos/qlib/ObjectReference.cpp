/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ObjectReference

\brief    


\date     $Date: 2006/06/03 12:24:27,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ObjectReference"

#include  <pdefault.h>
#include  <sObjectReferenceHandle.hpp>
#include  <sObjectReference.hpp>


/******************************************************************************/
/**
\brief  Connect - 



\param  obref_hdl_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

void ObjectReference :: Connect (ObjectReferenceHandle *obref_hdl_ptr )
{


  ILock(YES);

  if ( obref_hdl_ptr && !references.Find(obref_hdl_ptr) )
    references.AddTail(obref_hdl_ptr);

  IUnlock();
  



}

/******************************************************************************/
/**
\brief  Disconnect - 



\param  obref_hdl_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void ObjectReference :: Disconnect (ObjectReferenceHandle *obref_hdl_ptr )
{

  ILock(YES);

  if ( obref_hdl_ptr )
    references.Remove(obref_hdl_ptr);

  IUnlock();
  


}

/******************************************************************************/
/**
\brief  ObjectReference - 



\param  activate_llist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectReference"

     ObjectReference :: ObjectReference (logical activate_llist )
                     : ReferenceObject (activate_llist),
  references()
{



}

/******************************************************************************/
/**
\brief  Release - 


\return term - Success

\param  obref_hdl_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

logical ObjectReference :: Release (ObjectReferenceHandle *obref_hdl_ptr )
{
  logical      term     = NO;
  Disconnect(obref_hdl_ptr);

  ReferenceObject::Release();

  return(term);
}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Success

\param  obref_hdl_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical ObjectReference :: Reserve (ObjectReferenceHandle *obref_hdl_ptr )
{
  logical                 term = NO;
  Connect(obref_hdl_ptr);
  ReferenceObject::Reserve();
  

  return(term);
}

/******************************************************************************/
/**
\brief  ~ObjectReference - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ObjectReference"

     ObjectReference :: ~ObjectReference ( )
{
  ObjectReferenceHandle  *orhptr = NULL;
  res_lock.ILock(YES);

  while ( orhptr = references.RemoveTail() )
    orhptr->set_object_handle(NULL);

  res_lock.IUnlock();


}


