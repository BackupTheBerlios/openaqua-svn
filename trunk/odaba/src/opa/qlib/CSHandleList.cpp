/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSHandleList

\brief    


\date     $Date: 2006/03/12 19:16:37,65 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSHandleList"

#include  <popa7.h>
#ifndef   DLL_CSA_Handle_HPP
#define   DLL_CSA_Handle_HPP
#include  <sCSA_Handle.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_PCSHandle_HPP
#define   DLL_PCSHandle_HPP
#include  <sPCSHandle.hpp>
#include  <sDLL.h>
#endif
#include  <sCSA_Handle.hpp>
#include  <sCSHandle.hpp>
#include  <sCS_Message.hpp>
#include  <sEntryEvent.hpp>
#include  <sEventParms.hpp>
#include  <sPCSHandle.hpp>
#include  <sacb.hpp>
#include  <sCSHandleList.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  pcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical CSHandleList :: Add (PCSHandle *pcs_handle )
{
  logical                 term = NO;
//  ILock(YES);
// wir muessen das beim CopyACB beachten (=operator)
  if ( !conn_handle )
    conn_handle = new DLL(PCSHandle)();
    
  conn_handle->AddTail(pcs_handle);

//  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CSHandleList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSHandleList"

                        CSHandleList :: CSHandleList ( )
                     : conn_handle(NULL),
  res_lock(YES)
{



}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical CSHandleList :: Clear ( )
{
  logical      term = NO;
//  ILock(YES);
  term = conn_handle->Clear();
//  IUnlock();
  return(term);


}

/******************************************************************************/
/**
\brief  Close - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void CSHandleList :: Close ( )
{

  if ( conn_handle )
  {
//    GenerateEvent(0,NULL);   // disconnect event
    delete conn_handle;
    conn_handle = NULL;
  }


}

/******************************************************************************/
/**
\brief  Copy - 


\return term - Termination code

\param  hdl_list_refc -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical CSHandleList :: Copy (const CSHandleList &hdl_list_refc )
{
  logical      term = NO;
//  ILock(YES);
  term = conn_handle->Copy(* const_cast<CSHandleList&>(hdl_list_refc).conn_handle);
//  IUnlock();
  return(term);


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

logical CSHandleList :: GenerateEvent (EntryEvent *ev_ptr )
{
  PCSHandle              *pcshandle = NULL;
  logical                 term = NO;
BEGINSEQ
//  ILock(YES);
  if ( !conn_handle )                                LEAVESEQ
  
  conn_handle->GoTop();
  while ( pcshandle = conn_handle->GetNext() ) 
  {
    if ( pcshandle->Get() )
    {
      EventParms  ps(ev_ptr->get_is_instance(),ev_ptr->ebsnum);
      (*pcshandle)->FireEvent(ev_ptr->get_event(),(char *)&ps);  // calls CSA_Handle for local events and SC_Handle for server events
    }
  }
ENDSEQ
//  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ILock - 


\return term - Termination code

\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical CSHandleList :: ILock (logical wait )
{

//  return(res_lock.ILock(wait));
  return(NO);


}

/******************************************************************************/
/**
\brief  IUnlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical CSHandleList :: IUnlock ( )
{

//  return(res_lock.IUnlock());
  return(NO);

}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CSHandleList :: Initialize ( )
{

//    res_lock.Initialize();

}

/******************************************************************************/
/**
\brief  Move - 


\return term - Termination code

\param  hdl_list_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

logical CSHandleList :: Move (CSHandleList &hdl_list_ref )
{

//  ILock(YES);
  
  delete conn_handle;
  conn_handle = hdl_list_ref.conn_handle;
  hdl_list_ref.conn_handle = NULL;
  
//  IUnlock();

  return(NO);
}

/******************************************************************************/
/**
\brief  Remove - 


\return cs_handle -

\param  pcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

CSA_Handle *CSHandleList :: Remove (PCSHandle *pcs_handle )
{
  CSA_Handle            *csa_handle;
  PCSHandle             *pcshandle = NULL;
BEGINSEQ
//  ILock(YES);
  if ( !conn_handle )                                ERROR
    
  if ( conn_handle->Find(pcs_handle) )
    pcshandle = conn_handle->RemoveAt();
  
  csa_handle = pcshandle->Get();

RECOVER
  csa_handle = NULL;
ENDSEQ
//  IUnlock();
  return(csa_handle);
}

/******************************************************************************/
/**
\brief  Uninitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Uninitialize"

void CSHandleList :: Uninitialize ( )
{

//    res_lock.Uninitialize();

}

/******************************************************************************/
/**
\brief  get_conn_handle - 


\return conn_handle -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_conn_handle"

DLL(PCSHandle) *CSHandleList :: get_conn_handle ( ) const
{


  return(conn_handle);
}

/******************************************************************************/
/**
\brief  set_conn_handle - 



\param  pcs_handle_list -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_conn_handle"

void CSHandleList :: set_conn_handle (DLL(PCSHandle) *pcs_handle_list )
{

  conn_handle = pcs_handle_list;

}

/******************************************************************************/
/**
\brief  ~CSHandleList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSHandleList"

                        CSHandleList :: ~CSHandleList ( )
{

  Close();

}


