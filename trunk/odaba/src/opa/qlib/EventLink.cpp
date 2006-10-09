/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EventLink

\brief    Event Link
          This  is a function link object for handling events. The function link
          stores  a pointer to the handler class instance and the function to be
          called.
          The following status indicators are used:
          stsini - handler is active and will be executed

\date     $Date: 2006/03/12 19:17:33,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EventLink"

#include  <popa7.h>
#include  <cevtp.h>
#include  <svcls.hpp>
#include  <sEventLink.hpp>


/******************************************************************************/
/**
\brief  Activate - Activate handler



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

void EventLink :: Activate ( )
{

  if ( this ) 
    stssini();

}

/******************************************************************************/
/**
\brief  Call - Call handler function
        The function calls the event handler.

\return term - Termination code
-------------------------------------------------------------------------------
\brief i00


\param  event_id - Ivend type
\param  identity - Local Instance identity (LOID)
\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical EventLink :: Call (CSA_Events event_id, int64 identity, PropertyHandle &prophdl_ref )
{

  return(flnkinst ? (flnkinst->*((EVTP)flnkfct))(event_id,identity,prophdl_ref) : YES);

}

/******************************************************************************/
/**
\brief i01


\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical EventLink :: Call (DB_Event intevent )
{

  return(flnkinst ? (flnkinst->*((EVTPL)flnkfct))(intevent) : YES);

}

/******************************************************************************/
/**
\brief  Deactivate - Deactivate handler



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

void EventLink :: Deactivate ( )
{

  if ( this ) 
    stsrini();

}

/******************************************************************************/
/**
\brief  EventLink - Constructor
        The  constructor creates an  event link that  defines a link to an event
        handler.

-------------------------------------------------------------------------------
\brief i0 - Event link
        This   constructor   creates   an   event   link.   Instead of using the
        constructor directly the macro 
        ELINK( instptr, clsname, funcname )
        should  be used. This  allows easily defining  an event link passing the
        instance pointer, the class name and the handler function name.
        The calling conventions for thr linked function are as
        logical vcls::handler(CSA_Events event, long loid, PropertyHandle &ph)

\param  vclsptr - Virtual class pointer
\param  evtptri - Event handler pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventLink"

                        EventLink :: EventLink (vcls *vclsptr, EVTP evtptri )
                     : flnk (vclsptr,(FCTP)evtptri)
{

  stssini();

}

/******************************************************************************/
/**
\brief i01 - Dummy constructor


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventLink"

                        EventLink :: EventLink ( )
                     : flnk ()
{



}

/******************************************************************************/
/**
\brief i02


\param  vclsptr - Virtual class pointer
\param  evtptril - Event handler pointer for local events
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventLink"

                        EventLink :: EventLink (vcls *vclsptr, EVTPL evtptril )
                     : flnk (vclsptr,(FCTP)evtptril)
{

  stssini();

}

/******************************************************************************/
/**
\brief  IsActive - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActive"

logical EventLink :: IsActive ( )
{

  return(stscini());

}

/******************************************************************************/
/**
\brief  ~EventLink - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EventLink"

                        EventLink :: ~EventLink ( )
{



}


