/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    CS_ServerClient

\brief    


\date     $Date: 2006/08/27 18:23:49,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_ServerClient"

#include  <pdefault.h>
#include  <sCS_Message.hpp>
#include  <sCS_Server.hpp>
#include  <stim.hpp>
#include  <sCS_ServerClient.hpp>


/******************************************************************************/
/**
\brief  CS_ServerClient - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_ServerClient"

     CS_ServerClient :: CS_ServerClient ( )
                     : CS_Connection (),
  client_ptr_size(0),
  client_mtype(MT_undefined),
  server(NULL)
{



}

/******************************************************************************/
/**
\brief  Execute - 



\return term - Success

\param  dwServiceClass - 
\param  dwServiceFunc - 
\param  pParams - 
\param  pResult - 
\param  pError - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical CS_ServerClient :: Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult, logical *pError )
{
  CS_Message              msg;

  char                   *area2 = "DR";
  char                   *area = "angekommen";
  logical                 term = NO;
  // nur zum Test;
  
  msg.SetData(area);
  msg.SetLength(11);
  
  Output("Daten: %s",pParams->GetData());
  if ( dwServiceClass == 1 && dwServiceFunc == 1 )
  {
    SendCSMessage(dwServiceClass,dwServiceFunc,&msg,NULL);
    pResult->SetData(area2);
    pResult->SetLength(3);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  GetClientObject - 



\return client_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientObject"

int64 CS_ServerClient :: GetClientObject ( )
{
  int64                 client_handle = 0;

  return(client_handle);
}

/******************************************************************************/
/**
\brief  KillClient - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KillClient"

logical CS_ServerClient :: KillClient ( )
{
  logical                 term = NO;
  server->RemClient( this );
//  SendCSBye();  das geht nicht, wenn der client nicht mehr lebt, ist aber besser, wenn er noch lebt
  StopThreads();
  delete this;
  return(term);
}

/******************************************************************************/
/**
\brief  OnExecTerm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnExecTerm"

logical CS_ServerClient :: OnExecTerm ( )
{
  logical                 term = NO;
BEGINSEQ
SOSTRY
{
  if ( closedbypeer )
  {
    while ( threadSpool )
      TWAIT(5);
    server->RemClient(this);
    delete this;
  }
}
SOSCATCH
{
  SOSERR(518)
}

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCMachineType - 




\param  mach_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCMachineType"

void CS_ServerClient :: SetCMachineType (MachineTypes mach_type )
{

  client_mtype = mach_type;

}

/******************************************************************************/
/**
\brief  SetCPointerSize - 




\param  ptr_size - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCPointerSize"

void CS_ServerClient :: SetCPointerSize (int16 ptr_size )
{

  client_ptr_size = ptr_size;

}

/******************************************************************************/
/**
\brief  ~CS_ServerClient - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CS_ServerClient"

     CS_ServerClient :: ~CS_ServerClient ( )
{



}


