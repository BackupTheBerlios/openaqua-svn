/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSLLHandleList

\brief    


\date     $Date: 2006/03/12 19:16:44,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSLLHandleList"

#include  <popa7.h>
#ifndef   DLL_CSLHandleList_HPP
#define   DLL_CSLHandleList_HPP
#include  <sCSLHandleList.hpp>
#include  <sDLL.h>
#endif
#include  <sCSLHandleList.hpp>
#include  <sCS_Message.hpp>
#include  <sEntryEvent.hpp>
#include  <sacb.hpp>
#include  <sCSLLHandleList.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  llcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical CSLLHandleList :: Add (CSLHandleList *llcs_handle )
{
  logical                 term = NO;
  if ( !handle_lists ) 
    handle_lists = new DLL(CSLHandleList)();
    
  handle_lists->AddTail(llcs_handle);

  return(term);
}

/******************************************************************************/
/**
\brief  CSLLHandleList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSLLHandleList"

                        CSLLHandleList :: CSLLHandleList ( )
                     :   handle_lists(NULL)
{



}

/******************************************************************************/
/**
\brief  Close - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void CSLLHandleList :: Close ( )
{

  delete handle_lists;
  handle_lists = NULL;

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

logical CSLLHandleList :: GenerateEvent (EntryEvent *ev_ptr )
{
  CSLHandleList          *llcshandle = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !handle_lists )                                LEAVESEQ
  
  handle_lists->GoTop();
  while ( llcshandle = handle_lists->GetNext() ) 
    llcshandle->GenerateEvent(ev_ptr);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 


\return llcs_handle -

\param  llcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

CSLHandleList *CSLLHandleList :: Remove (CSLHandleList *llcs_handle )
{
  CSLHandleList             *llcshandle = NULL;
BEGINSEQ
  if ( !handle_lists )                                ERROR
    
  if ( handle_lists->Find(llcs_handle) )
    llcshandle = handle_lists->RemoveAt();
RECOVER
  llcshandle = NULL;
ENDSEQ
  return(llcshandle);
}

/******************************************************************************/
/**
\brief  ~CSLLHandleList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSLLHandleList"

                        CSLLHandleList :: ~CSLLHandleList ( )
{

  Close();

}


