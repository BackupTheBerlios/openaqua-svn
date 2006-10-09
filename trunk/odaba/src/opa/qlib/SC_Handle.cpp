/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    SC_Handle

\brief    


\date     $Date: 2006/07/24 16:17:35,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Handle"

#include  <popa7.h>
#include  <_cs_def.h>
#include  <perfchk.h>
#ifndef   DLL_SC_Handle_HPP
#define   DLL_SC_Handle_HPP
#include  <sSC_Handle.hpp>
#include  <sDLL.h>
#endif
#include  <sCSInstanceList.hpp>
#include  <sCS_Connection.hpp>
#include  <sSC_Handle.hpp>
#include  <sSC_Property.hpp>
#include  <sServerConnection.hpp>
#include  <sSC_Handle.hpp>


/******************************************************************************/
/**
\brief  AddHandleToParentList - 




\param  parent_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHandleToParentList"

void SC_Handle :: AddHandleToParentList (SC_Handle *parent_handle )
{
  SC_Handle    *prev_handle;
  if ( parent )
  {
    parent = parent_handle;
    parent->get_sub_handles()->AddTail(this);
    parent->get_sub_handles()->GetTail();
    if ( prev_handle = parent->get_sub_handles()->GetPrev() )
      current_index = prev_handle->get_current_index() + 1;
  }


}

/******************************************************************************/
/**
\brief  CheckHandle - 



\return term - Termination code

\param  dwServiceClass - 
\param  dwServiceFunc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckHandle"

logical SC_Handle :: CheckHandle (uint32 dwServiceClass, uint32 dwServiceFunc )
{
  logical          term = NO;
BEGINSEQ
  switch ( dwServiceClass )
  {
    case S_CACObject  : if ( dwServiceFunc == SF_CACObject_CACObject_ci  ||
                             dwServiceFunc == SF_CACObject_CACObject_ci1 ||
                             dwServiceFunc == SF_CACObject_CACObject_ci2    )
                                                     LEAVESEQ
                        break;
    case S_CDBHandle  : if ( dwServiceFunc == SF_CDBHandle_CDBHandle_ci0 )
                                                     LEAVESEQ
                        break;
    case S_CDictionary: if ( dwServiceFunc == SF_CDictionary_CDictionary_ci0 )
                                                     LEAVESEQ
                        break;
    case S_CNode      : if ( dwServiceFunc == SF_CNode_OpenCopyNode_ci      ||
                             dwServiceFunc == SF_CNode_OpenSubNode_ci       || 
                             dwServiceFunc == SF_CNode_OpenAccessPath_ci1     || 
                             dwServiceFunc == SF_CNode_OpenAccessPath_ci2     || 
                             dwServiceFunc == SF_CNode_OpenPathCopy_ci      ||
                             dwServiceFunc == SF_CNode_OpenBaseNode_ci      ||
                             dwServiceFunc == SF_CNode_OpenOperationNode_ci1|| 
                             dwServiceFunc == SF_CNode_OpenOperationNode_ci2  ) 
                                                     LEAVESEQ
                        break;
    case S_COperation : if ( dwServiceFunc == SF_COperation_Open_ci )
                                                     LEAVESEQ
                        break;
    case S_CClient    :                              LEAVESEQ
                        break;
  }

  if ( !this )                                       SDBERR(538)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillResult - 



\return term - Termination code

\param  result - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillResult"

logical SC_Handle :: FillResult (CSInstanceList *result )
{
  logical       conversion = result->get_conversion();
  logical       term = NO;
BEGINSEQ
  result->Reset();
  
  if ( !this )
  {
    result->get_inst_area().Fill((logical)YES,conversion,YES);
                                                     // 0 - term
    LEAVESEQ
  }
  result->get_inst_area().Fill((logical)NO,conversion,YES);
                                                     // 0 - term
  result->get_inst_area().Fill(GetName(),conversion,YES);
                                                     // 1 - ressource name
  result->get_inst_area().Fill(GetTypeName(),conversion,YES);
                                                     // 2 - ressource type
  result->get_inst_area().Fill(calls,conversion,YES);
                                                     // 3 - call for this handle
  result->get_inst_area().Fill((int32)(total_time/(perf_freq/1000)),conversion,YES);
                                                     // 4 - total time for this handle
  result->get_inst_area().Fill(all_calls,conversion,YES);
                                                     // 5 - call for this and sub handles
  result->get_inst_area().Fill((int32)(all_time/(perf_freq/1000)),conversion,YES);
                                                     // 6 - total time for this and sub-handles
  result->get_inst_area().Fill((int32)sub_handles->GetCount(),conversion,YES);
                                                     // 7 - # of subhandles
  result->get_inst_area().Fill(current_index,conversion,YES);
                                                     // 8 - handle number
  result->get_inst_area().Fill((logical)(start_time > 0 ? YES : NO),conversion,YES);
                                                     // 9 - IsActive
ENDSEQ
  result->Terminate();
  return(term);
}

/******************************************************************************/
/**
\brief  FireEvent - 



\return term - Termination code

\param  event_id - Ivend type
\param  parmstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FireEvent"

logical SC_Handle :: FireEvent (CSA_Events event_id, char *parmstring )
{
  logical                 term = NO;
  return(connection->FireEvent(this,event_id,parmstring));
  return(term);
}

/******************************************************************************/
/**
\brief  GetName - 



\return resource_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *SC_Handle :: GetName ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetSubHandle - 



\return sc_handle - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubHandle"

SC_Handle *SC_Handle :: GetSubHandle (int32 indx0 )
{
  SC_Handle    *sc_handle = NULL;
BEGINSEQ
  if ( !sub_handles || indx0 < 0 )                      ERROR
  sc_handle = sub_handles->GetHead();
  while ( sc_handle && indx0-- )
    sc_handle = sub_handles->GetNext();
RECOVER

ENDSEQ
  return (sc_handle);
}

/******************************************************************************/
/**
\brief  GetTypeName - 



\return resource_type - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *SC_Handle :: GetTypeName ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  InitHandle - 




\param  sconnection - 
\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandle"

void SC_Handle :: InitHandle (ServerConnection *sconnection, int64 client_handle )
{

  connection = sconnection;
  csconnection = sconnection;

  SetClientObject(client_handle);

}

/******************************************************************************/
/**
\brief  IsClosing - 



\return term - Termination code

\param  dwServiceClass - 
\param  dwServiceFunc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsClosing"

logical SC_Handle :: IsClosing (uint32 dwServiceClass, uint32 dwServiceFunc )
{
  logical          cond = YES;
BEGINSEQ
  switch ( dwServiceClass )
  {
    case S_CACObject  : if ( dwServiceFunc == SF_CACObject_CloseObject_ci )
                                                     LEAVESEQ
                        break;
    case S_CDBHandle  : if ( dwServiceFunc == SF_CDBHandle_CloseDBHandle_ci )
                                                     LEAVESEQ
                        break;
    case S_CDictionary: if ( dwServiceFunc == SF_CDictionary_CloseDictionary_ci )
                                                     LEAVESEQ
                        break;
    case S_CNode      : if ( dwServiceFunc == SF_CNode_Close_ci0 )
                                                     LEAVESEQ
                        break;
    case S_COperation : break;
    case S_CClient    : break;
  }

  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);

}

/******************************************************************************/
/**
\brief  MSG_Closed - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MSG_Closed"

void SC_Handle :: MSG_Closed ( )
{

  if ( connection && client_object )
    connection->FireEvent(this,CE_Closed,NULL);

  client_object = NULL;

}

/******************************************************************************/
/**
\brief  MSG_Dirty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MSG_Dirty"

void SC_Handle :: MSG_Dirty ( )
{

  if ( client_object )
    connection->FireEvent(this,CE_Dirty,NULL);

  client_object = NULL;

}

/******************************************************************************/
/**
\brief  Remove - 




\param  sc_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void SC_Handle :: Remove (SC_Handle *sc_handle )
{

  if ( sub_handles->Find(sc_handle) )
    sub_handles->RemoveAt();



}

/******************************************************************************/
/**
\brief  Reparent - 




\param  sc_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reparent"

void SC_Handle :: Reparent (SC_Handle *sc_handle )
{

  if ( this && sc_handle && 
       (sub_handles = sc_handle->sub_handles) )
  {
    sc_handle->sub_handles = NULL;
    sub_handles->GoTop();
    while ( sc_handle = sub_handles->GetNext() )
      sc_handle->parent = this;
  }

}

/******************************************************************************/
/**
\brief  SC_Handle - 




\param  cs_connection - 
\param  parent_handle - 
\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Handle"

     SC_Handle :: SC_Handle (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle )
                     : CSHandle (cs_connection),
  connection((ServerConnection *)cs_connection),
  parent(parent_handle),
  calls(0),
  start_time(0),
  total_time(0),
  perf_freq(1000000),
  sub_handles(NULL),
  current_index(1),
  all_calls(0),
  all_time(0)
{

  SetClientObject(client_handle);

  sub_handles = new DLL(SC_Handle);
  AddHandleToParentList(parent_handle);
  
#ifdef __CHECK_PERFORMANCE__

#ifndef __unix__
   QueryPerformanceFrequency( (LARGE_INTEGER*)&perf_freq );
#endif

#endif

}

/******************************************************************************/
/**
\brief  SetParent - 




\param  sc_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParent"

void SC_Handle :: SetParent (SC_Handle *sc_handle )
{

  parent = sc_handle;

}

/******************************************************************************/
/**
\brief  Start - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical SC_Handle :: Start ( )
{
  SC_Handle    *ph = this;
  logical       term = NO;

BEGINSEQ
  if ( !ValidHandle() )                              ERROR
    
  calls++;
  while ( ph )
  {
    ph->all_calls++;
    ph = ph->parent;
  }

#ifdef __CHECK_PERFORMANCE__
#ifdef __unix__
  start_time = clock();
#else
  QueryPerformanceCounter( (LARGE_INTEGER*) &start_time );
#endif
#endif
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Stop - 




\param  dwServiceClass - 
\param  dwServiceFunc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

void SC_Handle :: Stop (uint32 dwServiceClass, uint32 dwServiceFunc )
{
  SC_Handle    *ph = this;
  int64         exectim = 0;
BEGINSEQ
#ifdef __CHECK_PERFORMANCE__

  switch ( dwServiceClass )
  {
    case S_CACObject  : if ( dwServiceFunc == SF_CACObject_CloseObject_ci )
                                                     LEAVESEQ
                        break;
    case S_CDBHandle  : if ( dwServiceFunc == SF_CDBHandle_CloseDBHandle_ci )
                                                     LEAVESEQ
                        break;
    case S_CDictionary: if ( dwServiceFunc == SF_CDictionary_CloseDictionary_ci )
                                                     LEAVESEQ
                        break;
    case S_CNode      : if ( dwServiceFunc == SF_CNode_Close_ci0 )
                                                     LEAVESEQ
                        if ( ((SC_Property *)this)->IsDirty() )
                          MSG_Dirty();
                        break;
  }


#ifdef __unix__
  exectim = clock();
#else
  QueryPerformanceCounter( (LARGE_INTEGER*) &exectim );
#endif

  total_time += (exectim - start_time);
  while ( ph )
  {
    ph->all_time += (exectim - start_time);
    ph = ph->parent;
  }
  start_time = 0;

#endif



ENDSEQ

}

/******************************************************************************/
/**
\brief  set_current_index - 




\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_current_index"

void SC_Handle :: set_current_index (int32 index )
{

  current_index = index;

}

/******************************************************************************/
/**
\brief  ~SC_Handle - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Handle"

     SC_Handle :: ~SC_Handle ( )
{
  SC_Handle    *sc_handle;
  if ( sub_handles )
  {
    while ( sc_handle = sub_handles->RemoveTail() )
      delete sc_handle;
  
    delete sub_handles;
    sub_handles = NULL;
  }
  
  if ( parent )
    parent->Remove(this);


}


