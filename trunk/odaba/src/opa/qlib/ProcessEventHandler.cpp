/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ProcessEventHandler

\brief    


\date     $Date: 2006/07/18 13:27:49,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ProcessEventHandler"

#include  <popa7.h>
#include  <cEventClasses.h>
#include  <sACObject.hpp>
#include  <sbnode.hpp>
#include  <sProcessEventHandler.hpp>


/******************************************************************************/
/**
\brief  EmitEvents - 



\return term - Termination code

\param  emit_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EmitEvents"

logical ProcessEventHandler :: EmitEvents (logical emit_opt )
{
  DLL(EventLink)    cursor(*this);
  EventLink        *evt_link;
  DB_Event          event;
  int8              indx0 = MAX_EVENTS;
  logical           term  = NO;
  if ( emit_opt )
    while ( indx0-- )
      if ( event_cash[indx0] )
      {
        event = event_cash[indx0];
        event_cash[indx0] = DB_undefined;
        cursor.GoTop();
        while ( !term && (evt_link = cursor.GetNext()) )
          term = evt_link->Call(event);
      }
  
  InitCash();
  ob_handle->RemoveEventNode(causer);

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateEvent - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical ProcessEventHandler :: GenerateEvent (DB_Event intevent )
{
  int32             ec   = intevent >> 8;
  logical           term = NO;
BEGINSEQ
if ( ec > 8 )                                        
SDBERR(99)

  if ( ec && ob_handle->EventHandling() )
  {
    if ( ob_handle->AddEventNode(causer,SequenceOption(intevent)) )   
                                                    ERROR
    event_cash[--ec] = intevent;
    while ( ec )
      event_cash[--ec] = DB_undefined;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitCash - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitCash"

void ProcessEventHandler :: InitCash ( )
{

  memset(event_cash,0,sizeof(event_cash));

}

/******************************************************************************/
/**
\brief  ProcessEventHandler - 




\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessEventHandler"

     ProcessEventHandler :: ProcessEventHandler (bnode *bnodeptr )
                     : EventLinkList (),
  ob_handle(bnodeptr ? bnodeptr->get_object_ref() : NULL),
  causer(bnodeptr),
  registered(NO)
{

  InitCash();


}

/******************************************************************************/
/**
\brief  SequenceOption - 



\return seq_opt - Sequence option

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SequenceOption"

int8 ProcessEventHandler :: SequenceOption (DB_Event intevent )
{
  int8     seq_opt = 0;
  switch ( intevent )
  {
    case DBO_Stored  : 
    case DBO_Reset   : 
    case DBO_Deleted : 
    case DBO_Removed : 
    case DBO_Close   : seq_opt = -1;        
                       break;
    default          : seq_opt = 1;
  }

  return(seq_opt);
}

/******************************************************************************/
/**
\brief  set_causer - 




\param  bnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_causer"

void ProcessEventHandler :: set_causer (bnode *bnodeptr )
{

  causer = bnodeptr;

}

/******************************************************************************/
/**
\brief  ~ProcessEventHandler - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ProcessEventHandler"

     ProcessEventHandler :: ~ProcessEventHandler ( )
{



}


