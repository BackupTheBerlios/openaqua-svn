/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSLHandleList

\brief    


\date     $Date: 2006/03/12 19:16:44,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSLHandleList"

#include  <popa7.h>
#ifndef   DLL_CSHandleList_HPP
#define   DLL_CSHandleList_HPP
#include  <sCSHandleList.hpp>
#include  <sDLL.h>
#endif
#include  <sCSHandleList.hpp>
#include  <sCS_Message.hpp>
#include  <sEntryEvent.hpp>
#include  <sacb.hpp>
#include  <sCSLHandleList.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  lcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical CSLHandleList :: Add (CSHandleList *lcs_handle )
{
  logical                 term = NO;
  if ( !handle_lists )
    handle_lists = new DLL(CSHandleList)();
    
  handle_lists->AddTail(lcs_handle);

  return(term);
}

/******************************************************************************/
/**
\brief  CSLHandleList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSLHandleList"

                        CSLHandleList :: CSLHandleList ( )
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

void CSLHandleList :: Close ( )
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

logical CSLHandleList :: GenerateEvent (EntryEvent *ev_ptr )
{
  CSHandleList           *lcshandle = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !handle_lists )                                LEAVESEQ
  
  handle_lists->GoTop();
  while ( lcshandle = handle_lists->GetNext() ) 
    lcshandle->GenerateEvent(ev_ptr);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 


\return lcs_handle -

\param  lcs_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

CSHandleList *CSLHandleList :: Remove (CSHandleList *lcs_handle )
{
  CSHandleList           *lcshandle = NULL;

BEGINSEQ
  if ( !handle_lists )                                ERROR
    
  if ( handle_lists->Find(lcs_handle) )
    lcshandle = handle_lists->RemoveAt();
RECOVER
  lcshandle = NULL;
ENDSEQ
  return(lcshandle);
}

/******************************************************************************/
/**
\brief  ~CSLHandleList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSLHandleList"

                        CSLHandleList :: ~CSLHandleList ( )
{

  Close();

}


