/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ObjectEntry

\brief    


\date     $Date: 2006/03/12 19:17:59,67 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ObjectEntry"

#include  <popa7.h>
#include  <sCSHandleList.hpp>
#include  <sCSLHandleList.hpp>
#include  <sEntryEvent.hpp>
#include  <sInstancePool.hpp>
#include  <sObjectEntryList.hpp>
#include  <sThreadEntry.hpp>
#include  <sacb.hpp>
#include  <stim.hpp>
#include  <sObjectEntry.hpp>


/******************************************************************************/
/**
\brief  Free - 



\param  instance_pool -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Free"

void ObjectEntry :: Free (InstancePool *instance_pool )
{

  active_handles.Close();

  if ( ext_inst )
  {
    instance_pool->RemoveInstance(ext_inst);
    ext_inst = NULL;
  }

  RessourceLock::Uninitialize();


}

/******************************************************************************/
/**
\brief  GenerateEvent - 


\return term - Termination code

\param  ev_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical ObjectEntry :: GenerateEvent (EntryEvent *ev_ptr )
{

  return ( active_handles.GenerateEvent(ev_ptr) );

}

/******************************************************************************/
/**
\brief  Initialize - 



\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ObjectEntry :: Initialize (acb *acbptr )
{

  InstanceDescriptor::Initialize(acbptr);
  RessourceLock::Initialize();
  RessourceLock::DeactivateLockList();

}

/******************************************************************************/
/**
\brief  Release - 



\param  lcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void ObjectEntry :: Release (CSHandleList *lcs_handle )
{

  if ( lcs_handle )
    active_handles.Remove(lcs_handle);

    
  



}

/******************************************************************************/
/**
\brief  ReleaseLocked


\param  instance_pool -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseLocked"

void ObjectEntry :: ReleaseLocked (InstancePool *instance_pool )
{

// das hängt alle gegenwärtigen Nutzer ab, 
// aber zur Zeit können wir noch keine Thread-Nutzer erkennen. 
  active_handles.Close();



}

/******************************************************************************/
/**
\brief  Reserve - 



\param  lcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

void ObjectEntry :: Reserve (CSHandleList *lcs_handle )
{

  if ( lcs_handle )
    active_handles.Add(lcs_handle);

}


