/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CServer

\brief    


\date     $Date: 2006/07/24 14:01:32,63 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CServer"

#include  <popa7.h>
#include  <coserver.h>
#ifndef   DLL_ServerConnection_HPP
#define   DLL_ServerConnection_HPP
#include  <sServerConnection.hpp>
#include  <sDLL.h>
#endif
#include  <sCClient.hpp>
#include  <sCSInstanceList.hpp>
#include  <sCS_Server.hpp>
#include  <sCS_ServerClient.hpp>
#include  <sDLL_Handle.hpp>
#include  <sIFClass.hpp>
#include  <sSC_Dictionary.hpp>
#include  <sServerConnection.hpp>
#include  <sServices.hpp>
#include  <stim.hpp>
#include  <sCServer.hpp>


/******************************************************************************/
/**
\brief  Block - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Block"

void CServer :: Block ( )
{

  blocking = YES;

}

/******************************************************************************/
/**
\brief  CServer - 




\param  inipath - 
\param  prog_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CServer"

     CServer :: CServer (char *inipath, char *prog_path )
                     : CS_Server (),
  client_list(NULL),
  dict_list(),
  services(NULL),
  main_client(NULL),
  shutting_down(NO),
  blocking(NO)
{
  extern ObjectReference  *c_client;
  char      progdir[129];
  char      drives[3];
  char      dirs[129];
BEGINSEQ
  RegisterProcess();
  ShareRootBase();
  if ( !c_client )
    main_client = new CClient(inipath,"SERVER",prog_path,APT_Console);   // damit initialisieren wir die Services!!
  
  if ( !(client_list = new DLL(ServerConnection)())) SDBERR(95)
  
  c_server = this;

  services = GetMainClient().GetClientPtr()->get_services();
  *progdir = 0;
  if ( prog_path )
  {
    fildirg(prog_path,drives,dirs);
    strcat(strcpy(progdir,drives),dirs);
  }
  services->SetProgPath(progdir);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CheckTimeout - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckTimeout"

logical CServer :: CheckTimeout ( )
{
  logical                 term = NO;
  term = connection_cache.Check();

  return(term);
}

/******************************************************************************/
/**
\brief  CreateClient - 



\return server_client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateClient"

CS_ServerClient *CServer :: CreateClient ( )
{
  ServerConnection  *client = NULL;
  int32               count;
BEGINSEQ
  lock->ILock();
  if ( shutting_down || blocking )                   SDBERR(532)
  if ( !(client = new ServerConnection(this)) )      SDBERR(95)

  Initialize(client);
  
  if ( (count = client_list->GetCount()) > 0 )
    client->set_current_index(GetClientHandle(count-1)->get_current_index() +1);

  client_list->AddTail(client);

RECOVER

ENDSEQ
  lock->IUnlock();
  return(client);
}

/******************************************************************************/
/**
\brief  GetCatlgName - 



\return filenames - 

\param  sym_nams - 
\param  cpath - Complete path
\param  maxlen - Size of the output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCatlgName"

char *CServer :: GetCatlgName (char *sym_nams, char *cpath, int32 maxlen )
{

  return(services ? services->GetFileName(sym_nams,cpath,maxlen) : NULL);

}

/******************************************************************************/
/**
\brief  GetClientHandle - 



\return sconnection - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientHandle"

ServerConnection *CServer :: GetClientHandle (int32 indx0 )
{
  ServerConnection   *sconnection = NULL;
  sconnection = client_list->GetObjectInst(indx0);
  return(sconnection);
}

/******************************************************************************/
/**
\brief  KillClient - 



\return term - Termination code

\param  sender - 
\param  client_id - 
\param  wait_sec - 
\param  send_message - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KillClient"

logical CServer :: KillClient (int32 sender, int32 client_id, int32 wait_sec, logical send_message )
{
  int32                    indx0 = client_list->GetCount();
  int32                    clid;
  SC_Handle              *sc_handle;
  char                    string2[80];
  char                    string[500];
  logical                 wait = YES;
  logical                 term = YES;  // client not killed
  if ( !client_id )  // Server shut down
    shutting_down = YES;
    
  while ( wait && wait_sec > 0 )
  {
    wait = NO;
    indx0 = 0;
    lock->ILock();
    while ( sc_handle = GetClientHandle(indx0++) )
    {
      strcpy(string2," will be closed");
      if ( wait_sec > 0 )
      {
        strcat(string2," after ");
        gvtxltoa(wait_sec,string2+strlen(string2),10);
        strcat(string2," sec.");
      }
      else
        strcat(string2," now");
      strcat(string2,"!");
    
      clid = sc_handle->get_current_index();
      if ( clid != sender && (!client_id || client_id == clid) )
      {
        if ( send_message )
        {
          strcat(strcat(strcpy(string,"Client '"),((ServerConnection *)sc_handle)->GetName()),string2);
          ((ServerConnection *)sc_handle)->SendClientMessage(string,"ODABA Server",'W');
        }
        wait = YES;
      }
      lock->IUnlock();
    }
    send_message = NO;
    TWAIT(10);
    wait_sec--;
  }
    
  lock->ILock();
  indx0 = client_list->GetCount();
  while ( --indx0 >= 0 )
  {
    if ( sc_handle = GetClientHandle(indx0) )
    {
      clid = sc_handle->get_current_index();
      if ( clid != sender && (!client_id || client_id == clid) )
        term = ((ServerConnection *)sc_handle)->KillClient();        
    }
  }
  lock->IUnlock();

  return(term);
}

/******************************************************************************/
/**
\brief  ProvideConnection - 



\return sc_connection - 

\param  sconnection - 
\param  connection_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideConnection"

SC_Connection *CServer :: ProvideConnection (ServerConnection *sconnection, char *connection_string )
{
  SC_Connection          *sc_connection = NULL;
  logical                 term = NO;
  if ( sc_connection = connection_cache.Provide(connection_string) )
    sc_connection->Setup(sconnection);
  else
  {
    sc_connection = new SC_Connection(sconnection);
    connection_cache.Create(sc_connection,connection_string);
  }
  return(sc_connection);
}

/******************************************************************************/
/**
\brief  ProvideDict - 



\return term - Termination code

\param  cpath - Complete path
\param  version - 
\param  sc_dict - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDict"

logical CServer :: ProvideDict (char *cpath, uint16 version, SC_Dictionary *sc_dict, PIACC accopt )
{
  DictDescriptor   *dict_des = NULL;
  ODABAClient       oclient;
  logical           netopt   = YES;
  logical           term     = NO;
BEGINSEQ
  lock->ILock();
  dict_list.GoTop();
  if ( accopt == PI_Read )
    while ( dict_des = dict_list.GetNext() )
    {
#ifdef __unix__ 
      if ( !strcmp(dict_des->get_path(),cpath) &&
#else
      if ( !gvtsicmp(dict_des->get_path(),cpath,UNDEF) &&
#endif
           dict_des->get_version() == version  &&
           dict_des->get_access_mode() == accopt  )
        break;
    }
  
  if ( !dict_des )
  {
    dict_des = new DictDescriptor(cpath,accopt,version);
    if ( dict_des->get_dicthdl().Open(oclient,cpath,accopt,netopt,version,RES_local,NO) )
    {
      delete dict_des;
      dict_des = NULL;
      ERROR
    }
    dict_des->get_dicthdl().ResetErrorObject();
    dict_list.AddTail(dict_des);
  }
  
  sc_dict->SetDictHdl(&dict_des->get_dicthdl());
  dict_des->get_dict_clients().AddTail(sc_dict);  

RECOVER
  term = YES;
ENDSEQ
  lock->IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseDict - 



\return term - Termination code

\param  dict_client - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDict"

logical CServer :: ReleaseDict (SC_Dictionary *dict_client )
{
  DictDescriptor         *dict_des;
  logical                 term = NO;
BEGINSEQ
  lock->ILock();
  dict_list.GoTop();
  while ( dict_des = dict_list.GetNext() )
    if ( dict_des->get_dicthdl() == *(DictionaryHdl *)&dict_client )
      if ( dict_des->get_dict_clients().Find(dict_client) )
      {
        dict_des->get_dict_clients().RemoveAt();
        if ( !dict_des->get_dict_clients().GetCount() )
        {
          dict_list.RemoveAt();
          dict_des->get_dicthdl().Close();
          delete dict_des;
        }
        LEAVESEQ
      }
  
  ERROR
RECOVER
  term = YES;
ENDSEQ
  lock->IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveClient - 




\param  server_client - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveClient"

void CServer :: RemoveClient (CS_ServerClient *server_client )
{
  ServerConnection *s_client = (ServerConnection *)server_client;
BEGINSEQ
  lock->ILock();
  if ( !server_client )                              LEAVESEQ
  
  s_client->ForceClose();
  if ( s_client->get_sc_connection() )
    connection_cache.Add(s_client->get_sc_connection());
  
  if ( client_list->Find(s_client) )
    client_list->RemoveAt();

ENDSEQ
  lock->IUnlock();

}

/******************************************************************************/
/**
\brief  SendClientMessage - 



\return term - Termination code

\param  sender - 
\param  client_id - 
\param  mtext - 
\param  mtitle - 
\param  mtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendClientMessage"

logical CServer :: SendClientMessage (int32 sender, int32 client_id, char *mtext, char *mtitle, uint8 mtype )
{
  int32                    indx0 = 0;
  int32                    clid;
  SC_Handle              *sc_handle;
  logical                 term = NO;
  while ( sc_handle = GetClientHandle(indx0++) )
  {
    clid = sc_handle->get_current_index();
    if ( clid != sender && (!client_id || client_id == clid) )
    {
      if ( !mtitle || !*mtitle )
        mtitle = "ODABA Server Message";
      ((ServerConnection *)sc_handle)->SendClientMessage(mtext,mtitle,mtype);
    }
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Start - 



\return term - Termination code

\param  wPort - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical CServer :: Start (int16 wPort )
{
  int32                    iresult;
  char                    string[20];
  logical                 term = NO;
BEGINSEQ
  SetSysVariable("NO_CONSOLE_MESSAGES","YES");
  if ( iresult = CS_Server::Start(wPort) )
  {
    SDBError().DisplayMessage(530,gvtxitoa(200+iresult,string,10));
    SDBERR(200+iresult);
  }
  SDBError().DisplayMessage(531,ODABA2Version());


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StartDBClients - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartDBClients"

void CServer :: StartDBClients ( )
{

  Unblock();

}

/******************************************************************************/
/**
\brief  Stop - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

void CServer :: Stop ( )
{
  ServerConnection *s_connection;
  KillClient(UNDEF,UNDEF,0);
  
  while ( s_connection = client_list->RemoveTail() )
    RemoveClient(s_connection);
    
  CS_Server::Stop();

}

/******************************************************************************/
/**
\brief  StopDBClients - 



\return term - Termination code

\param  sender - 
\param  cpath - Complete path
\param  nstring - 
\param  wait_sec - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopDBClients"

logical CServer :: StopDBClients (int32 sender, char *cpath, NString &nstring, int32 wait_sec )
{
  int32                    indx0 = 0;
  int32                    clid;
  ServerConnection        *sconnection = NULL;
  logical                  term = NO;
  Block();

  if ( wait_sec == AUTO )
    nstring = "\nThe following clients are using the database to be stopped:";
  
  while ( sconnection = (ServerConnection *)GetClientHandle(indx0++) )
  {
    clid = sconnection->get_current_index();
    if ( sconnection->IsUsingDB(cpath) )
    {
      if ( wait_sec != AUTO )
      {
        KillClient(sender,clid,wait_sec,YES);
        if ( sconnection != (ServerConnection *)GetClientHandle(indx0-1) )
          indx0--;
      }
      else
      {
        nstring += "\n  -";
        nstring += ' ';
        nstring += sconnection->GetName();
        nstring += " - client-ID:";
        nstring += clid;
        term = YES;
      }
    }
  }

  if ( wait_sec == AUTO )
  {
    if ( term )
      nstring += "\nStop the clients before tying again.";
    else
      nstring = "";
  }
  if ( term )
    Unblock();
  return(term);
}

/******************************************************************************/
/**
\brief  Unblock - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unblock"

void CServer :: Unblock ( )
{

  blocking = NO;

}

/******************************************************************************/
/**
\brief  ~CServer - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CServer"

     CServer :: ~CServer ( )
{
  logical        global_client;
  connection_cache.Close();
  
  global_client = main_client == GetMainClient().GetClientPtr();  
  
  main_client->ShutDown();
  if ( !global_client || GetMainClient().GetClientPtr() )
    delete main_client;
  main_client = NULL;  
  Stop();
  delete client_list;
  client_list = NULL;

  UnregisterProcess();

}


