/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBEventList

\brief    


\date     $Date: 2006/03/12 19:16:53,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBEventList"

#include  <popa7.h>
#include  <sCTX_DBBase.hpp>
#include  <sDBEvent.hpp>
#include  <sDBEventList.hpp>


/******************************************************************************/
/**
\brief  Append - 


\return term - Termination code

\param  evtptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical DBEventList :: Append (DBEvent *evtptr )
{

  AddTail(evtptr);

  if ( evtptr->get_pre_condition() || evtptr->get_post_condition() )
    user_events = YES;

  return(NO);
}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  ctxptr -
\param  clear_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical DBEventList :: Check (CTX_DBBase *ctxptr, logical clear_event )
{
  DBEvent                *event;
  logical                 term = NO;
BEGINSEQ
  if ( !user_events )                                LEAVESEQ
  
  GoTop();
  while ( (event = GetNext()) )
    event->CheckEvent(ctxptr,clear_event);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBEventList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBEventList"

                        DBEventList :: DBEventList ( )
                     : DLL(DBEvent) (),
  user_events(NO)
{



}

/******************************************************************************/
/**
\brief  Search - 


\return evtptr -

\param  evtnames -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Search"

DBEvent *DBEventList :: Search (char *evtnames )
{
  DBEvent     *evtptr = NULL;
  char         evtname[ID_SIZE];
BEGINSEQ
  if ( !this)                                        ERROR
  
  gvtxstb(evtname,evtnames,ID_SIZE);
  
  GoTop();
  while ( evtptr = GetNext() )
    if ( !memcmp(evtptr->get_name(),evtname,ID_SIZE) )    LEAVESEQ

RECOVER

ENDSEQ
  return(evtptr);
}

/******************************************************************************/
/**
\brief  ~DBEventList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBEventList"

                        DBEventList :: ~DBEventList ( )
{
  DBEvent  *evtptr;
  while ( evtptr = RemoveTail() )
    delete evtptr;
    


}


