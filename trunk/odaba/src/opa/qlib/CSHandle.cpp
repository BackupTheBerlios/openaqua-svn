/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    CSHandle



\date     $Date: 2006/05/09 15:19:55,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSHandle"

#include  <popa7.h>
#include  <sCSA_Handle.hpp>
#include  <sCS_Connection.hpp>
#include  <sClientConnection.hpp>
#include  <sEventParms.hpp>
#include  <sServerConnection.hpp>
#include  <sacb.hpp>
#include  <sCSHandle.hpp>


/******************************************************************************/
/**
\brief  CConnection

\return cconnection

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CConnection"

ClientConnection *CSHandle :: CConnection ( )
{

  return( csconnection ? (ClientConnection *)csconnection : NULL);

}

/******************************************************************************/
/**
\brief  CSAClosed


\param  parmstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAClosed"

void CSHandle :: CSAClosed (char *parmstring )
{

  csconnection = NULL;


}

/******************************************************************************/
/**
\brief  CSHandle

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSHandle"

     CSHandle :: CSHandle ( )
                     : CSA_Handle (),
  ident(HNDL_ID),
  return_buffer(NULL)
{

}

/******************************************************************************/
/**
\brief  i01


\param  cs_connection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSHandle"

     CSHandle :: CSHandle (CS_Connection *cs_connection )
                     : CSA_Handle (cs_connection),
  ident(HNDL_ID),
  return_buffer(NULL)
{


}

/******************************************************************************/
/**
\brief  GenerateEvent

\return term - Termination code

\param  event_id - Ivend type
\param  identity - Local Instance identity (LOID)
\param  is_instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical CSHandle :: GenerateEvent (CSA_Events event_id, int64 identity, logical is_instance )
{
  logical                 term = NO;
BEGINSEQ
  if ( !ValidHandle() )                                 ERROR
      
  EventParms  ps(is_instance,identity);
  FireEvent(event_id,(char *)&ps);  // calls CSA_Handle for local events and SC_Handle for server events

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClient

\return client

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClient"

ODABAClient &CSHandle :: GetClient ( )
{

  return ( csconnection ? CConnection()->GetClient()
                      : GetMainClient() );


}

/******************************************************************************/
/**
\brief  Get_rec_result

\return result_r

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_rec_result"

CSInstanceList &CSHandle :: Get_rec_result ( )
{
  ClientConnection *cconnection = CConnection();
  return (   cconnection 
           ? *cconnection->get_rec_result()
           : *(CSInstanceList *)NULL       );

}

/******************************************************************************/
/**
\brief  Get_send_parms

\return parms_r

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_send_parms"

CSInstanceList &CSHandle :: Get_send_parms ( )
{
  ClientConnection *cconnection = CConnection();
  return (   cconnection 
           ? cconnection->get_send_parms()
           : *(CSInstanceList *)NULL       );

}

/******************************************************************************/
/**
\brief  InitHandle - 


\return term - Termination code

\param  alloc_buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandle"

logical CSHandle :: InitHandle (logical alloc_buffer )
{
  logical                 term = NO;
BEGINSEQ
  ident = HNDL_ID;
  
  if ( !return_buffer && alloc_buffer )
  {
    if ( !(return_buffer = new char[RET_BUF_LEN+1]) )  SDBERR(95)
    memset(return_buffer,0,RET_BUF_LEN+1);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsConnected

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConnected"

logical CSHandle :: IsConnected ( )
{
  ClientConnection *cconnection = CConnection();
  return ( ValidHandle() && cconnection && cconnection->get_connected() 
           ? YES : NO );

}

/******************************************************************************/
/**
\brief  LockSendParms

\return parms_r

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockSendParms"

CSInstanceList &CSHandle :: LockSendParms ( )
{

BEGINSEQ
  if ( !csconnection )                               ERROR
  
  csconnection->LockSend();
  return(Get_send_parms());

RECOVER
  return(*(CSInstanceList *)NULL);
ENDSEQ

}

/******************************************************************************/
/**
\brief  SConnection

\return sconnection

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SConnection"

ServerConnection *CSHandle :: SConnection ( )
{

  return( csconnection ? (ServerConnection *)csconnection : NULL);

}

/******************************************************************************/
/**
\brief  UninitHandle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UninitHandle"

void CSHandle :: UninitHandle ( )
{

  delete  return_buffer;
  return_buffer = NULL;

  ident = HNDL_IDD;


}

/******************************************************************************/
/**
\brief  UnlockSendParms

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockSendParms"

logical CSHandle :: UnlockSendParms ( )
{
  logical     term = NO;
BEGINSEQ
  if ( !csconnection )                               ERROR
  
  csconnection->UnlockSend();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ValidHandle

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidHandle"

logical CSHandle :: ValidHandle ( )
{
  logical     cond = YES;
BEGINSEQ
  try 
  {
    if ( !this || ident == HNDL_IDD  )               ERROR
    if ( ident != HNDL_ID )                          SDBIERR(9)
  }
  catch (...)
  {
    SDBIERR(9)
  }
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ~CSHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSHandle"

     CSHandle :: ~CSHandle ( )
{
  UninitHandle();
}


