/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ClientConnection

\brief    Client Connection


\date     $Date: 2006/07/24 17:02:27,56 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ClientConnection"

#include  <popa7.h>
#include  <ctfctp.h>
#include  <cwinsock.h>
#include  <sofifct.h>
#include  <sCSA_Handle.hpp>
#include  <sCSInstanceList.hpp>
#include  <sCS_Client.hpp>
#include  <sCS_Handle.hpp>
#include  <sCS_Message.hpp>
#include  <sIFClass.hpp>
#include  <sInstance.hpp>
#include  <sServices.hpp>
#include  <sThreadLink.hpp>
#include  <sClientConnection.hpp>


/******************************************************************************/
/**
\brief  Check - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ClientConnection :: Check ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsAlive() )                                   LEAVESEQ
  
  connected = 0;                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ClientConnection - Konstruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClientConnection"

     ClientConnection :: ClientConnection ( )
                     : CS_Client (),
  is_local(YES),
  function_table(NULL),
  send_parms(32,NO,8*1024),
  send_result(16,NO,1024),
  rec_parms(32,NO,0),
  rec_result(NULL),
  error_check(NO),
  save_result(16,NO,1024),
  connected(0),
  msg_stack(),
  last_class(0),
  last_function(0),
  last_answer(0),
  client_reference(NULL)
{

#include  <_sc_tbl_OPA.hpp>
  
  function_table = ClientClasses;

  conversion   = YES;   // für test, später raus auch aus ServerConnection

  msg_stack.AddTail(rec_result = new CSInstanceList(16,NO,0));
  
  rec_parms.SetConversion(conversion);
  send_parms.SetConversion(conversion);
  rec_result->SetConversion(conversion);
  send_result.SetConversion(conversion);
  save_result.SetConversion(conversion);

}

/******************************************************************************/
/**
\brief  Disconnect - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void ClientConnection :: Disconnect ( )
{



}

/******************************************************************************/
/**
\brief  DisplayMessage - Display Message



\return term - Termination code

\param  msg_type - 
\param  cso_ptr - 
\param  csparms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

logical ClientConnection :: DisplayMessage (uint32 msg_type, void *cso_ptr, CSInstanceList *csparms )
{
  char                   *string;
  Error                  *error;
  logical                 term = NO;
BEGINSEQ
  if ( !csparms->GetCount() )                        LEAVESEQ

  if ( string=(*csparms)[0].GetString() )  // message text
    SDBEV1(string,UNDEF)
  if ( string=(*csparms)[1].GetString() )  // message box title
    SDBError().SetTitle(string);
  switch ( msg_type )
  {
    case APL_MSG_INFO    : SDBError().SetType('I');   break;
    case APL_MSG_WARNING : SDBError().SetType('W');   break;
    case APL_MSG_ERROR   :
    default              : SDBError().SetType('E');   break;
  }
  SDBError().SetError(AUTO,NULL,NULL);  
  error = &SDBError();
  TLINK(error,Error,DisplayMessage).ThreadCall();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 



\return term - Termination code

\param  dwServiceClass - 
\param  dwServiceFunc - 
\param  cpParams - 
\param  cpResult - 
\param  errptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ClientConnection :: Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *cpParams, CS_Message *cpResult, logical *errptr )
{
  logical                 term = NO;
BEGINSEQ
  rec_parms.Setup(cpParams);
  send_result.Reset();
  
  if ( errptr )
    *errptr = NO;
  
  switch ( dwServiceClass )
  {
    case UNDEF       : break;  // system call
    case CSA_EVENT   : GenerateEvent(dwServiceFunc,
                                     cpParams->GetHandle()->GetClientPointer(),
                                     &rec_parms);
                       break;
    case CSA_MESSAGE : DisplayMessage(dwServiceFunc,
                                     cpParams->GetHandle()->GetClientPointer(),
                                     &rec_parms);
                       break;
    default          : if ( shutting_down )
                         term = YES;
                       else
                         if ( !(term = function_table[dwServiceClass].
                                         Execute(dwServiceClass,dwServiceFunc,this,
                                                 cpParams->GetHandle()->GetClientPointer(),
                                                 &rec_parms,&send_result)) )
                           cpResult->Copy(send_result.GetCSMessage());
                       if ( errptr )
                       {
                         *errptr = term;
                         if ( !*errptr && SDBERROR )
                           *errptr = YES;
                       }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateEvent - 



\return term - Termination code

\param  dwServiceFunc - 
\param  cso_ptr - 
\param  csparms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical ClientConnection :: GenerateEvent (uint32 dwServiceFunc, void *cso_ptr, CSInstanceList *csparms )
{
  char                   *parmstring = NULL;
  char                    string[33];
  logical                 term = NO;
BEGINSEQ
SOSTRY
{
  if ( !cso_ptr )                                    ERROR
    
  if ( csparms->GetCount() ) 
  {
    parmstring=(*csparms)[0].GetString();
  }
  if ( ((CSA_Handle *)cso_ptr)->get_csconnection() )
    term = ((CSA_Handle *)cso_ptr)->ExecuteEvent(dwServiceFunc,parmstring);
}
SOSCATCH
{
  SDBEV1(gvtxltoa(dwServiceFunc,string,10),UNDEF)
  SDBERR(537) 
}

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClient - 



\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClient"

ODABAClient &ClientConnection :: GetClient ( )
{
  ODABAClient       stat_client;
  return( this ? *(ODABAClient *)&client_reference : stat_client);

}

/******************************************************************************/
/**
\brief  IsConnected - 



\return connected - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConnected"

logical ClientConnection :: IsConnected ( )
{

  return(connected > 0 ? YES : NO);

}

/******************************************************************************/
/**
\brief  PopResult - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopResult"

logical ClientConnection :: PopResult ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  msg_stack.Find(rec_result);
  rec_result->get_cs_message()->Reset();
  if ( !(rec_result = msg_stack.GetPrev()) )         ERROR
RECOVER
  if ( this )
    rec_result = msg_stack.GetHead();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PushResult - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushResult"

logical ClientConnection :: PushResult ( )
{
  logical     conversion = NULL;
  logical     term       = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  conversion = rec_result->get_conversion();
  
  msg_stack.Find(rec_result);
  if ( !(rec_result = msg_stack.GetNext()) )
  {
    msg_stack.AddTail(rec_result = new CSInstanceList(16,NO,0));
    rec_result->SetConversion(conversion);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SendCSMessage - 



\return term - Termination code

\param  handle - 
\param  dwServiceClass - 
\param  dwServiceFunc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendCSMessage"

logical ClientConnection :: SendCSMessage (CS_Handle *handle, uint32 dwServiceClass, uint32 dwServiceFunc )
{
  int32               err;
  Error             *errptr;
  logical            term = NO;
BEGINSEQ
  SDBRESET
 
  if ( !connected )                                  SDBERR(533)
  
if ( last_class )
  last_class = 0;
last_answer = 0;
last_class = dwServiceClass;
last_function = dwServiceFunc;

  send_parms.SetHandle(handle);
  term = CS_Client::SendCSMessage(dwServiceClass,dwServiceFunc,
                                  send_parms.GetCSMessage(),
                                  dwServiceClass ? rec_result->GetCSMessage() : NULL);
  
if ( last_answer )
  last_answer = 0;
last_answer = rec_result->GetCSMessage()->length;
last_class = 0;
last_function = 0;
  
  if ( !dwServiceClass )
                                                     LEAVESEQ
  
  switch ( term )
  {
    case NO   : rec_result->Setup(NULL);
                
                break;
    case 255  : break;
    default   : send_parms.Fill();
                send_parms.SetHandle(NULL);
                if ( !CS_Client::SendCSMessage(S_CClient,SF_CClient_GetDBError_ci,
                                               send_parms.GetCSMessage(),
                                               save_result.GetCSMessage()) )
                {
                  Error    *err;
                  save_result.Setup(NULL);
                  if ( err = (Error *)save_result[0].GetBuffer() )
                    SDBError().Copy(*err);
                  SDBIERR(SERVER_ERROR);
                }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetResult - 



\return term - Termination code

\param  datarea - 
\param  instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetResult"

logical ClientConnection :: SetResult (void *datarea, int32 instlen )
{
  CS_Message              cs_msg;
  logical                 term = NO;
  cs_msg.SetData((char *)datarea);
  cs_msg.SetLength(instlen);
  rec_result->Setup(&cs_msg);
  return(term);
}

/******************************************************************************/
/**
\brief  ~ClientConnection - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ClientConnection"

     ClientConnection :: ~ClientConnection ( )
{

  while (rec_result = msg_stack.RemoveHead())
    delete rec_result;

}


