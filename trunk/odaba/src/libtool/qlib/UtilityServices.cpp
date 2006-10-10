/********************************* Class Source Code ***************************/
/**
\package  Utilities - 
\class    UtilityServices

\brief    


\date     $Date: 2006/06/18 12:16:06,39 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UtilityServices"

#include  <puti.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <ctfctp.h>
#include  <ifil.h>
#include  <igvts.h>
#include  <sCClient.hpp>
#include  <sCSUtilityHandle.hpp>
#include  <sClientObject.hpp>
#include  <sFileHandle.hpp>
#include  <sHandleInfo.hpp>
#include  <sNString.hpp>
#include  <sODABAServer.hpp>
#include  <sThreadLink.hpp>
#include  <sbnode.hpp>
#include  <stim.hpp>

#include  <iUtilityServices.h>

/******************************************************************************/
/**
\brief  BackupDB - 


\return term - Termination code

\param  uti_handle - 
\param  target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical __cdecl BackupDB (CSUtilityHandle &uti_handle, char *target )
{
  char                   *srce = NULL;
  char                   *targ = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( uti_handle.sdbures->Open(uti_handle.connection) )
                                                     ERROR
  srce = strdup(uti_handle.sdbures->dbhandle.GetPath());
  targ = strdup(target ? target : srce);
  if ( !target )
    filextr(targ,"ozi");
  
  if ( uti_handle.sdbures->client.BackupDB(srce,targ))
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( srce ) free(srce);
  if ( targ ) free(targ);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckCS - 


\return term - Termination code

\param  uti_handle - 
\param  extent_name - 
\param  distance - 
\param  max_count - 
\param  max_objects - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckCS"

logical __cdecl CheckCS (CSUtilityHandle &uti_handle, char *extent_name, int32 distance, int32 max_count, int32 max_objects )
{
  ClientObject           *co;
  int32                    client_num = 0;
  int32                    client_count = 0;
  logical                 term = NO;
BEGINSEQ
  Statistic               stats;
  stats.Start();
  
  if ( max_count <= 0 )
    max_count = 100;
    
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR
  
  while ( max_count-- )
  {
    co = new ClientObject(uti_handle,extent_name,max_objects,++client_num,&client_count);
    TLINK(co,ClientObject,Start).ThreadCall();
    TWAIT(distance);    
    printf("\n%i clients running",client_count);
  }

  if ( distance <= 10 )
    distance = 10;
    
  while ( client_count > 0 )
  {
    TWAIT(distance);    
    printf("\n%i clients running",client_count);
  }

  stats.Stop();
  printf("\nAll clients terminated. Total time: %s",stats.GetTotalTime());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDB - 


\return term - Termination code

\param  uti_handle - 
\param  check_opts - 
\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical __cdecl CheckDB (CSUtilityHandle &uti_handle, CheckOptions check_opts, char *source )
{
  char                   *check;
  char                   *ctype = "nothing";
  logical                 term = NO;
BEGINSEQ
  
  if (check_opts.repair_all) check = "Repair";
  else  check = "Check";
  
  if ( check_opts.instances && check_opts.collections )
    ctype = "instances references and collections";
  else if ( check_opts.instances )
    ctype = "instances references";
  else if ( check_opts.collections )
    ctype = "collections";
  
  if ( check_opts.guids )
    printf("\n      - %s GUIDs for %s",check,ctype);
  if ( check_opts.deleted_references )
    printf("\n      - %s references for %s",check,ctype);
  if ( check_opts.inverse_references )
    printf("\n      - %s inverse references for instance references",check);
  if ( check_opts.key_values )
    printf("\n      %s index key values for %s",check,ctype);
    
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR

  uti_handle.sdbures->dbhandle.CheckDB(check_opts,source);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckRuntimeParms - 


\return term - Termination code

\param  argc - 
\param  argv[] - 
\param  min_parms - 
\param  max_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckRuntimeParms"

logical __cdecl CheckRuntimeParms (int argc, char *argv[], int16 min_parms, int16 max_parms )
{
  logical                 term = NO;
BEGINSEQ
  if ( argc < min_parms )
  {
    printf("\n  Missing mandatory parameter");
    printf("\n  %s",GetCommandPrototype(argv[0]));
    ERROR
  }
  if ( argc > max_parms )
  {
    printf("\n  To many parameters");
    printf(GetCommandPrototype(argv[0]));
    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CommandLineServices - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommandLineServices"

logical __cdecl CommandLineServices ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  CopyDB - 


\return term - Termination code

\param  uti_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDB"

logical __cdecl CopyDB (CSUtilityHandle &uti_handle )
{
  char            *datasource = NULL;
  char            *collection;
  char            *replopt;
  logical          term = NO;
BEGINSEQ
  uti_handle.sdbures->accmode = PI_Read;
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR

  uti_handle.sdbudat->accmode = PI_Write;

  if ( uti_handle.sdbudat->Open(uti_handle.connection) ) ERROR

  if ( *uti_handle.sdbudat->db_path && *uti_handle.sdbures->db_path )
    uti_handle.sdbuinstonly = YES;

  SDBEV2(uti_handle.sdbures->db_path,UNDEF)

  uti_handle.sdburepl     = REPL_local;
  if ( replopt = GetSysVariable("REPLACE") )
  {
    if ( !gvtsicmp(replopt,"all",0) )
          uti_handle.sdburepl = REPL_all;
    else if ( !gvtsicmp(replopt,"local",0) )
      uti_handle.sdburepl = REPL_local;
    else if ( !gvtsicmp(replopt,"none",0) )
      uti_handle.sdburepl = REPL_none;
    else if ( !gvtsicmp(replopt,"no_create",0) )
      uti_handle.sdburepl = REPL_no_create;
    else if ( !gvtsicmp(replopt,"database",0) )
      uti_handle.sdburepl = REPL_instance;
  }
  if ( TestSysVariable("RETAIN_SID","YES") )
  uti_handle.retain_sid = YES;
  if ( TestSysVariable("RETAIN_SCHEMAVERSION","YES") )
  uti_handle.retain_schemaversion = YES;

  if ( collection = GetSysVariable("COPY_COLLECTION") )
  {
      strcpy(uti_handle.sdbudat->extent_name,collection);
      uti_handle.sdbudat->collopt = YES;
  }

  if ( uti_handle.CopyDB() )                            ERROR
  if ( uti_handle.sdburepl == REPL_instance )
  {
    uti_handle.sdburepl = REPL_relationships;
    SetSysVariable("__IGNORE_WPT__","Y");
    if ( uti_handle.CopyDB() )                          ERROR
  }

  uti_handle.sdbudat->Close();
  uti_handle.sdbures->Close();

//  statistics.Print("CopyInst",YES);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyResDB - 


\return term - Termination code

\param  uti_handle - 
\param  renamed - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyResDB"

logical __cdecl CopyResDB (CSUtilityHandle &uti_handle, logical renamed )
{
  DictionaryHandle        dummy_handle;
  char                   *datasource = NULL;
  logical                 term = NO;
BEGINSEQ
  uti_handle.sdbures->sys_appl = YES;
  uti_handle.sdbures->SetDBObject(dummy_handle,"*");
  uti_handle.sdbures->netopt  = YES;
  uti_handle.sdbures->accmode = PI_Read;

  if ( renamed )
  {
    uti_handle.sdbudat->SetDictionary(dummy_handle,uti_handle.sdbures->dict_path);
    uti_handle.sdbudat->SetDatabase(dummy_handle,uti_handle.sdbures->db_path);
    filextr(uti_handle.sdbudat->db_path,"#_O");
  }
  uti_handle.sdbudat->sys_appl = YES;

//          uti_handle->retain_schemav = YES;

  if ( TestSysVariable("RETAIN_SID","YES") )
    uti_handle.retain_sid = YES;
  if ( TestSysVariable("RETAIN_SCHEMAVERSION","YES") )
    uti_handle.retain_schemaversion = YES;

  if ( uti_handle.CopyResDB(NULL) )                     ERROR
  if ( renamed )
  {
    remove(uti_handle.sdbures->db_path);
    if ( rename(uti_handle.sdbudat->db_path,uti_handle.sdbures->db_path) != 0 )
                                                     SDBERR(217)
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBDictStatistics - 


\return term - Termination code

\param  uti_client - 
\param  db_path - 
\param  temp_path - Temporary path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBDictStatistics"

logical __cdecl DBDictStatistics (ODABAClient &uti_client, char *db_path, char *temp_path )
{
  CClient         *client;
  logical          term = NO;
BEGINSEQ
  if ( uti_client.IsConnected() )
    printf("\n  Connected to ODABA Server");

  printf("\n  Output File: %s",temp_path);

  client = uti_client.GetClientPtr();
  if ( !client->DictDisplay(db_path,temp_path)) ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBPerformance - 


\return term - Termination code

\param  uti_handle - 
\param  extent - 
\param  blocksize - 
\param  attribute - 
\param  sort_order - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBPerformance"

logical __cdecl DBPerformance (CSUtilityHandle &uti_handle, char *extent, int32 blocksize, char *attribute, char *sort_order )
{
  Statistic        stats;
  ODABAClient      local;
  char             string[32];
  CClient         *client;
  HandleInfo       hi;
  int32            indx0 = 0;
  int32            maxcomm = 10000;
  int32            s_time;
  char            *area;
  logical          term = NO;
BEGINSEQ
  local = uti_handle.connection;
  client = uti_handle.connection.GetClientPtr();
  
  client->GetHandleInfo(client,hi);
  s_time = hi.all_calls_time;
  stats.Start();
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR
  stats.Stop();
  client->GetHandleInfo(client,hi);
  s_time = hi.all_calls_time - s_time;
  printf("\nOpening server:            %s(%i msec)\n",stats.GetTotalTime(),s_time);
  
  SetSysVariable("ONLINE_VERSION","YES");
  local.SetServerVariable("_USER_NAME","PowerUser"); 
  local.SetServerVariable("_USER_PWD","pu"); 
  if ( !GetSysVariable("ThesaLang") )
  {
    local.SetServerVariable("ThesaLang","English"); 
    SetSysVariable("ThesaLang","English");
  }
  if ( (!extent || !*extent) && uti_handle.sdbures->server_name && *uti_handle.sdbures->server_name)
  {
    area = new char[blocksize+1];
    printf("\n%s / %s say hellos\n",uti_handle.sdbures->server_name ? uti_handle.sdbures->server_name : "Local Database",
                              gvtxitoa(maxcomm,string,10));
    DBPerformancePrint(AUTO,stats,s_time);
    client->GetHandleInfo(client,hi);
    s_time = hi.all_calls_time;
    stats.Initialize();
    stats.Start();
    while ( indx0++ < maxcomm ) client->SayHello(area,blocksize);
    stats.Stop();
    client->GetHandleInfo(client,hi);
    s_time = hi.all_calls_time - s_time;
    DBPerformancePrint(indx0-1,stats,s_time);
    delete area;
  }
  
  if ( !extent || !*extent )         LEAVESEQ
  
  client->GetHandleInfo(client,hi);
  s_time = hi.all_calls_time;
  stats.Initialize();
  stats.Start();
  
  PropertyHandle    coll(uti_handle.sdbures->dbhandle,extent,PI_Read);  SDBCERR
  
  *string = 0;
  if ( blocksize )
  {
    coll.ChangeBuffer(blocksize);
    strcpy(string,"ZZZ9");
    gvtxltp(string,blocksize,4);
  }
  if ( sort_order && *sort_order )
    coll.SetOrder(sort_order);
  
  stats.Stop();
  client->GetHandleInfo(client,hi);
  s_time = hi.all_calls_time - s_time;
  printf("Opening Collection:        %s(%i msec)\n",stats.GetTotalTime(),s_time);
  
  client->GetHandleInfo(client,hi);
  s_time = hi.all_calls_time;
  stats.Initialize();
  stats.Start();
  
  coll.Get(0);
  coll.Cancel(); 
  
  stats.Stop();
  client->GetHandleInfo(client,hi);
  s_time = hi.all_calls_time - s_time;
  printf("Initial read:              %s(%i msec)\n",stats.GetTotalTime(),s_time);
  
  printf("\n%s / %s (%s)\n",*uti_handle.sdbures->server_name > ' '? uti_handle.sdbures->server_name : "Local Database",
                            extent,string);
  DBPerformancePrint(AUTO,stats,s_time);
    
  client->GetHandleInfo((bnode *)coll.get_nodeptr(),hi);
  s_time = hi.all_calls_time;
  stats.Initialize();
  stats.Start();
  while ( (coll++).Exist() ) 
  {
    indx0++; 
    if ( attribute )
      printf("\n%s",coll.GetString(attribute)); 
  }
  stats.Stop();
  client->GetHandleInfo((bnode *)coll.get_nodeptr(),hi);
  s_time = hi.all_calls_time - s_time;
  DBPerformancePrint(indx0,stats,s_time);
  
  indx0 = 0;
  coll.Cancel();
  client->GetHandleInfo((bnode *)coll.get_nodeptr(),hi);
  s_time = hi.all_calls_time;
  stats.Initialize();
  stats.Start();
  while ( (coll++).Exist() ) 
  {
    indx0++; 
    if ( attribute )
      printf("\n%s",coll.GetString(attribute)); 
  }
  stats.Stop();
  client->GetHandleInfo((bnode *)coll.get_nodeptr(),hi);
  s_time = hi.all_calls_time - s_time;
  DBPerformancePrint(indx0,stats,s_time);

RECOVER
  term = YES;
ENDSEQ
  uti_handle.sdbures->Close();
  return(term);
}

/******************************************************************************/
/**
\brief  DBPerformancePrint - 


\return term - Termination code

\param  no_items - 
\param  stats - 
\param  s_time - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBPerformancePrint"

logical __cdecl DBPerformancePrint (int32 no_items, Statistic &stats, int32 s_time )
{
  struct           pl {
                        char  newline;
                        char  no_items[10];
                        char  sep1[3];
                        char  total_time[12];
                        char  sep2[3];
                        char  server_time[12];
                        char  sep3[3];
                        char  comm_time[12];
                        char  end;
                   } line;
  logical          term = NO;
  memset(&line,' ',sizeof(line));
  line.newline = '\n';
  line.end     = 0;
  line.sep1[1] = '|';
  line.sep2[1] = '|';
  line.sep3[1] = '|';
  if ( no_items < 0 )  // print headline
  {
    memcpy(line.no_items,"NO. items  ",sizeof(line.no_items));
    memcpy(line.total_time,"  total time",sizeof(line.total_time));
    memcpy(line.server_time," server time",sizeof(line.server_time));
    memcpy(line.comm_time,"  comm. time",sizeof(line.comm_time));
    printf((char *)&line);
    memset(line.no_items,'-',sizeof(line)-2);
  }
  else
  {
    memcpy(line.no_items,"ZZZZZZZZZZ9",sizeof(line.no_items));
    gvtxltp(line.no_items,no_items,sizeof(line.no_items));
    gvtxstb(line.total_time,stats.GetTime(stats.get_total_time(),1),sizeof(line.total_time));
    memcpy(line.server_time,"ZZZZZZZ9,999",sizeof(line.server_time));
    gvtxltp(line.server_time,s_time,sizeof(line.server_time));
    memcpy(line.comm_time,"ZZZZZZZ9,999",sizeof(line.comm_time));
    if (s_time )
      gvtxltp(line.comm_time,(int32)stats.GetTimeLong(stats.get_total_time(),1)-s_time,sizeof(line.comm_time));
    else
      memcpy(line.comm_time,"       0,000",sizeof(line.comm_time));
  }
  printf((char *)&line);

  return(term);
}

/******************************************************************************/
/**
\brief  DBStatistics - 


\return term - Termination code

\param  uti_client - 
\param  db_path - 
\param  temp_path - Temporary path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStatistics"

logical __cdecl DBStatistics (ODABAClient &uti_client, char *db_path, char *temp_path )
{
  logical                 term = NO;
BEGINSEQ
  if ( uti_client.IsConnected() )
    printf("\n  Connected to ODABA Server");

  printf("\n  Output File: %s",temp_path);

  if ( !uti_client.StatDisplay(db_path,temp_path)) ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBSystemInfo - 


\return term - Termination code

\param  uti_client - 
\param  db_path - 
\param  temp_path - Temporary path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBSystemInfo"

logical __cdecl DBSystemInfo (ODABAClient &uti_client, char *db_path, char *temp_path )
{
  logical                 term = NO;
BEGINSEQ
  if ( uti_client.IsConnected() )
    printf("\n  Connected to ODABA Server");

  printf("\n  Output File: %s",temp_path);

  if ( !uti_client.SysInfoDisplay(db_path,temp_path) ) ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCommandPrototype - 


\return string - String area

\param  command - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCommandPrototype"

char *__cdecl GetCommandPrototype (char *command )
{
  char     names[65];
  char     ext[65];
  char    *string;
  GetFileNameInfo(command,names,ext,sizeof(names)-1,sizeof(ext)-1);
  
  string = "Invalid command";
  if ( !gvtsicmp(names,"CopyDB",0) )
    string = "CopyDB ini_file  from  to"; 
  if ( !gvtsicmp(names,"CopyResDB",0) )
    string = "CopyResDB ini_file  from [to]";
  if ( !gvtsicmp(names,"DBStatistics",0) )
    string = "DBStatistics db_name [print_path]";
  if ( !gvtsicmp(names,"DBSystemInfo",0) )
    string = "DBSystemInfo db_name [print_path]"; 
  if ( !gvtsicmp(names,"Licence",0) )
    string = "Licence owner_ini_file"; 
  if ( !gvtsicmp(names,"PackDB",0) )
    string = "PackDB db_name [ temp_path ]"; 
  if ( !gvtsicmp(names,"SetSysVersion",0) )
    string = "SetSysVersion db_name version_nr"; 
  if ( !gvtsicmp(names,"ResetSysVersion",0) )
    string = "ResetSysVersion db_name [version_nr]"; 
  if ( !gvtsicmp(names,"ResetSchemaVersion",0) )
    string = "ResetSchemaVersion db_name [system_version]"; 
  if ( !gvtsicmp(names,"SetupDB",0) )
    string = "SetupDB ini_file from [to]"; 
  if ( !gvtsicmp(names,"DBPerformance",0) )
    string = "DBPerformance ini_file [Extent()] [Blocksize(0)] [Attribute()]"; 
  if ( !gvtsicmp(names,"CheckDB",0) )
    string = "CheckDB ini_file [-C:checks] [-S:srce] [-T:type] [-R] [-W]"; 
  if ( !gvtsicmp(names,"TestCS",0) )
    string = "TestCS ini_file [extent | query_root [distance [clients [objects]]]] "; 
  if ( !gvtsicmp(names,"Workspace",0) )
    string = "Workspace ini_file data-source operation:Enable|Disable|Create|Delete|Consolidate|List ws_name [user] [-options] "; 
  if ( !gvtsicmp(names,"TestAlignment",0) )
    string = "TestAlignment ini_file [strname] "; 
  if ( !gvtsicmp(names,"LoadSchema",0) )
    string = "OSI schema-file [-I:ini-file | -D:dict_path]";
  if ( !gvtsicmp(names,"OSI",0) )
    string = "OSI script-file [-I:ini-file | -D:dict_path] [-E:entry_point] [-P:parameters] [-DB]";

  return(string);
}

/******************************************************************************/
/**
\brief  Licence - 


\return term - Termination code

\param  uti_handle - 
\param  ini_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Licence"

logical __cdecl Licence (CSUtilityHandle &uti_handle, char *ini_path )
{
  svel             list(40);
  logical          term = NO;
BEGINSEQ
  list.svelfini(ini_path,"Licence");
  GetSysVariable("DICTIONARY");
  ConnectSystemVariables(&list);
  if ( uti_handle.Licence() )                        ERROR

RECOVER
  term = YES;
ENDSEQ
  DisconnectSystemVariables(list.Parent());
  return(term);
}

/******************************************************************************/
/**
\brief  PackDB - 


\return term - Termination code

\param  uti_client - 
\param  db_path - 
\param  temp_path - Temporary path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PackDB"

logical __cdecl PackDB (ODABAClient &uti_client, char *db_path, char *temp_path )
{
  logical                 term = NO;
BEGINSEQ
  if ( uti_client.PackDatabase(db_path,temp_path) ) ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PrintWS - 


\return term - Termination code

\param  dbhandle - Pointer to database handle
\param  ws_root - Workspace root
\param  user_name - User name
\param  level - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrintWS"

logical __cdecl PrintWS (DatabaseHandle &dbhandle, char *ws_root, char *user_name, int16 level, logical recursive )
{
  int32                    lindx0 = 0;
  char                    ws_name[65];
  char                    ws_info[512];
  char                    root[512];
  char                    line[512];
  char                    uname[81];
  logical                 term = NO;
BEGINSEQ
  memset(root,0,sizeof(root));
  memset(line,0,sizeof(line));
  memset(line,' ',level*2);

  if ( ws_root && *ws_root > ' ' )
    if ( dbhandle.OpenWorkspace(ws_root,user_name) ) ERROR
    
  *uname = 0;
    
  while ( dbhandle.GetWorkspace(NULL,lindx0++,uname,ws_name,YES,ws_info) )
  {
    printf("\n  %s%s",line,ws_info);
    if ( recursive && ws_name && *ws_name > ' ' )
      PrintWS(dbhandle,ws_name,uname,level+1,recursive);
    *uname = 0;
  }

  if ( ws_root && *ws_root > ' ' )
    dbhandle.CloseWorkspace();
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  QueryLater - 


\return term - Termination code

\param  uti_handle - 
\param  exp_path - 
\param  src_path - 
\param  res_path - 
\param  cls_name - 
\param  dboutput - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "QueryLater"

logical __cdecl QueryLater (CSUtilityHandle &uti_handle, char *exp_path, char *src_path, char *res_path, char *cls_name, logical dboutput )
{
  PropertyHandle   src_pi;
  char            *expression = NULL;
  char             string_area[4003];
  PropertyHandle   result;
  int32             indx0 = 0;
  logical          term = NO;
BEGINSEQ
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR

  if ( !(expression = ReadTextFile(exp_path)) )      SDBERR(991)
  if ( cls_name )  // check expression, only
  {
    OperationHandle  oph;
    if ( oph.CheckExpression(uti_handle.sdbures->dictionary,expression,
                             uti_handle.sdbures->dbhandle,cls_name) )
                                                     ERROR
    LEAVESEQ
  }
  
  if ( !src_path )
    src_path = GetSysVariable("SOURCE_COLLECTION");
  if ( src_path )
    if ( src_pi.Open(uti_handle.sdbudat->dbhandle,res_path,PI_Write) )
                                                     SDBCERR

  OperationHandle  oph(src_pi);
  if ( oph.ProvideExpression(uti_handle.sdbudat->dictionary,
                             uti_handle.sdbudat->dictionary,
                             uti_handle.sdbudat->dbhandle,expression) )      
                                                     SDBERR(992)
  result = oph.Execute(NULL); 

  if ( dboutput )
  {
    if ( !res_path )
      res_path = GetSysVariable("RESULT_COLLECTION");
    if ( !res_path )                                 SDBERR(999)
    uti_handle.sdbudat->accmode = PI_Write;
    if ( uti_handle.sdbudat->Open(uti_handle.connection) ) ERROR
    PropertyHandle  res_pi(uti_handle.sdbudat->dbhandle,res_path,PI_Write);
                                                     SDBCERR
    res_pi = result;
    res_pi.Close();
  }
  else
  {
    PropertyHandle   res_pi(string_area,sizeof(string_area-3));
    while ( result(indx0++) )
    {
      res_pi = result;
      strcat(res_pi.GetArea(),"\n");
      printf(res_pi.GetArea());
    }
  }


RECOVER
  term = YES;
ENDSEQ
  uti_handle.sdbudat->Close();
  uti_handle.sdbures->Close();
  return(term);
}

/******************************************************************************/
/**
\brief  RestoreDB - 


\return term - Termination code

\param  uti_handle - 
\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical __cdecl RestoreDB (CSUtilityHandle &uti_handle, char *source )
{
  char                   *srce = NULL;
  char                   *targ = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR
  targ = strdup(uti_handle.sdbures->dbhandle.GetPath());
  uti_handle.sdbures->object_handle.Close();
  uti_handle.sdbures->dbhandle.Close();
  uti_handle.sdbures->dictionary.Close();

  srce = strdup(source ? source : targ);
  if ( !source )
    filextr(srce,"ozi");

  if ( uti_handle.sdbures->client.RestoreDB(targ,srce))
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( srce ) free(srce);
  if ( targ ) free(targ);
  return(term);
}

/******************************************************************************/
/**
\brief  Server - 


\return term - Termination code

\param  ini_file - Application ini-file
\param  spath - 
\param  port_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Server"

logical __cdecl Server (char *ini_file, char *spath, int32 port_number )
{
  logical                 term = NO;
  printf("Server is starting ....\n");
  
  ODABAServer    server(ini_file,spath);

  if ( !server.Start(port_number) )
  {
    printf("Server started. Press enter for terminating server.\n");
    getchar();
    printf("Server is shutting down. Please wait ....\n");
    server.Stop();
    printf("Server stopped. See you later ...\n");
  }
  else
    printf("Server not started. See error log for details.\n");
  return(term);
}

/******************************************************************************/
/**
\brief  SetupDB - 


\return term - Termination code

\param  uti_handle - 
\param  renamed - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDB"

logical __cdecl SetupDB (CSUtilityHandle &uti_handle, logical renamed )
{
  DictionaryHandle        dummy_handle;
  char                   *collection = NULL;
  char                   *datasource = NULL;
  Statistic               uti_stat;
  logical                 term = NO;
BEGINSEQ
//  uti_stat.Start();
  
  uti_handle.sdbures->sys_appl = YES;
  uti_handle.sdbures->SetDBObject(dummy_handle,"*");
  uti_handle.sdbures->netopt  = YES;
  uti_handle.sdbures->accmode = PI_Read;
  if ( *uti_handle.sdbures->extent_name <= ' ' )
    strcpy(uti_handle.sdbures->extent_name, "*");
  if ( *uti_handle.sdbures->inst_key <= ' ' )
    strcpy(uti_handle.sdbures->inst_key, "*");
    if ( uti_handle.sdbures->Open(uti_handle.connection) )       ERROR

  if ( renamed )
  {
    uti_handle.sdbudat->SetDictionary(dummy_handle,uti_handle.sdbures->dict_path);
    uti_handle.sdbudat->SetDatabase(dummy_handle,uti_handle.sdbures->db_path);
    filextr(uti_handle.sdbudat->db_path,"#_O");
  }
  uti_handle.sdbudat->SetDBObject(dummy_handle,"");
  uti_handle.sdbudat->netopt   = NO;
  if ( uti_handle.sdbudat->sys_appl == AUTO )
    uti_handle.sdbudat->sys_appl = YES;
  uti_handle.sdbudat->accmode = PI_Write;

  if ( collection = GetSysVariable("COPY_COLLECTION") )
  {
      strcpy(uti_handle.sdbures->extent_name,collection);
      uti_handle.sdbures->collopt = YES;
    }

  if ( IsFile(uti_handle.sdbudat->db_path) ) // target already exist
    if ( SDBError().GetDecision(USHORTMAX,"File '",uti_handle.sdbudat->db_path,"' does already exist. Delete ?") )
      if ( remove(uti_handle.sdbudat->db_path) )    SDBERR(99)

  SetSysVariable("ONLINE_VERSION","YES");
    if ( uti_handle.sdbudat->Open(uti_handle.connection) )     ERROR

//  strcpy(uti_handle.sdbures->extent_name,"*");
//  strcpy(uti_handle.sdbures->inst_key,"*");
  uti_handle.sdbuinstonly = YES;

  SDBEV2(uti_handle.sdbures->db_path,UNDEF)

  uti_handle.sdburepl     = REPL_instance;
  if ( uti_handle.CopyDB() )                                    ERROR

  uti_handle.sdburepl     = REPL_relationships;
  if ( uti_handle.CopyDB() )                                    ERROR

  uti_handle.sdbudat->Close();
  uti_handle.sdbures->Close();
  if ( renamed )
  {
    remove(uti_handle.sdbures->db_path);
    if ( rename(uti_handle.sdbudat->db_path,uti_handle.sdbures->db_path) != 0 )
                                                         SDBERR(217)
  }

//  uti_stat.Stop();
//  uti_stat.Print("SetupDB",YES);
//  statistics0.Print("Add",NO);
//  statistics1.Print("Get",NO);
//  statistics2.Print("Save",NO);
//  statistics3.Print("Check",NO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  TestAlignment - 


\return term - Termination code

\param  uti_handle - 
\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TestAlignment"

logical __cdecl TestAlignment (CSUtilityHandle &uti_handle, char *strnames )
{
  DBStructDef     *struct_def;
  logical          term = NO;
BEGINSEQ
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR
  
  if ( strnames && *strnames > ' ' )
  {
    if ( !(struct_def = uti_handle.sdbures->dictionary.GetStructDef(strnames)) )
                                                     ERROR
    struct_def->DisplayAlignInfo();
  }
  else
    ;
    


RECOVER
  term = YES;
ENDSEQ
  uti_handle.sdbures->Close();
  return(term);
}

/******************************************************************************/
/**
\brief  TestVarious - 


\return term - Termination code

\param  uti_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TestVarious"

logical __cdecl TestVarious (CSUtilityHandle &uti_handle )
{
//  FileHandle       DocFile;
  PropertyHandle     ph1;
  PropertyHandle     ph2;
  PropertyHandle     ph3;
  PropertyHandle     ph4;
  PropertyHandle     DocFileO;
  PropertyHandle    *DocFileC   = NULL;
  PropertyHandle    *DocFileG   = NULL;
  PropertyHandle    *loid_ph    = NULL;
  PropertyHandle    *guid_ph    = NULL;
  PropertyHandle    *skey_ph    = NULL;
  char              *str1       = NULL;
  char              *str2       = NULL;
  char              *fctnames_i = "Test%sFunction";
  char              *id8        = "TestImpl";
  int32              curline    = 0;
  logical            trace_calls= NO;
  logical            term       = NO;
BEGINSEQ
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR
  if ( trace_calls )
    SetSysVariable("TRACE_CALLS","YES");
  
  SetSysVariable("IMPCLASS","db_ODE");
  
  PropertyHandle   class_ph(uti_handle.sdbures->dbhandle,"ODC_ImpClass",PI_Write);

  ph1 = class_ph.ExecuteExpression(uti_handle.sdbures->dbhandle,"ClassSourceCode()");
  ph1 = class_ph.ExecuteExpression(uti_handle.sdbures->dbhandle,"ClassInclude()");
  
  ph2 = uti_handle.sdbures->dbhandle.ExecuteExpression(uti_handle.sdbures->dbhandle,
       "ODC_ImpClass::ClassSourceCode()"           );

{  
  if ( uti_handle.sdbudat->SetupVariables("OPA7") )      ERROR
  if ( uti_handle.sdbudat->Open(uti_handle.connection) ) ERROR
  
  PropertyHandle   cls_ph(uti_handle.sdbudat->dbhandle,"ODC_ImpClass",PI_Write);
  PropertyHandle   dict_ph("Dictionary");
  if ( cls_ph.Get(dict_ph) )
  {
    cls_ph.ExecuteExpression(uti_handle.sdbures->dbhandle,"ClassSourceCodeO()");
    cls_ph.ExecuteExpression(uti_handle.sdbures->dbhandle,"ClassIncludeO()");
  }  
//  PropertyHandle   prj_ph(uti_handle.sdbudat->dbhandle,"ODC_Project",PI_Write);
//  if ( prj_ph.Get(PropertyHandle("opa7")) )
//    prj_ph.ExecuteExpression(uti_handle.sdbures->dbhandle,"proj_classes().ClassSourceCodeO()");
  
  uti_handle.sdbudat->Close();
}
  
  if ( DocFileO.Open(uti_handle.sdbures->dictionary,"FileHandle") )
                                                     ERROR
  if ( !uti_handle.sdbures->dictionary.CreateGlobalVariable(DocFileO,"DocFile") )
                                                     ERROR
  DocFileG = uti_handle.sdbures->dictionary.GetGlobalVariable("DocFile");

  ph1 = uti_handle.sdbures->dbhandle.ExecuteExpression(uti_handle.sdbures->dbhandle,
       "DocFile.Open('e:/tmp/test.cpp',3)"           );
  ph2 = uti_handle.sdbures->dbhandle.ExecuteExpression(uti_handle.sdbures->dbhandle,
       "DocFile.Out('//**\n')"                       );
  ph3 = uti_handle.sdbures->dbhandle.ExecuteExpression(uti_handle.sdbures->dbhandle,
       "DocFile.CurrentLine()"                       );
  ph4 = uti_handle.sdbures->dbhandle.ExecuteExpression(uti_handle.sdbures->dbhandle,
       "DocFile.Close()"                             );
  
  ph1 = DocFileG->ExecuteExpression(uti_handle.sdbures->dbhandle,"Open('e:/tmp/test2.cpp',3)");
  ph2 = DocFileG->ExecuteExpression(uti_handle.sdbures->dbhandle,"Out('//**\n')");
  ph3 = DocFileG->ExecuteExpression(uti_handle.sdbures->dbhandle,"CurrentLine()");
  ph4 = DocFileG->ExecuteExpression(uti_handle.sdbures->dbhandle,"Close()");


/*
  if ( DocFile.Open("e:/tmp/test.cpp",PI_Write) )       ERROR
  
  DocFile.Out("//**************************************************************************************************\n");
  DocFile.Out("//**   test:  %s(%s)\n",fctnames_i,id8);
  DocFile.Out("//**************************************************************************************************\n");
  DocFile.Out("\n");

  DocFile.Out("//**   TestLine5: ");
  DocFile.LinePosition(40);
  DocFile.Out("ende auf pos 40\n");
  
  DocFile.Out("//**   TestLine6: **********************************************************************************");
  DocFile.LinePosition(40);
  DocFile.Out("ende auf pos 40\n");
  
  DocFile.Out("//**   TestLine7-10: \n\n\n//**\nxxxxxxxxxxxxxxx");
 
  DocFile.Out("\n//**   TestLine11: ");
  DocFile.LinePosition(40);
  curline = DocFile.CurrentLine();
  DocFile.Out("curline %s\n",PropertyHandle(curline).GetString());
  
  DocFile.Close();
*/
/*
  PropertyHandle   struct_ph(uti_handle.sdbures->dbhandle,"SDB_Structure",PI_Write);
  loid_ph = struct_ph.GPH("__loid");
  guid_ph = struct_ph.GPH("__guid");
  skey_ph = struct_ph.GPH("__sortkey");
  
  struct_ph.Get(3);
  str1 = loid_ph->GetString();
  str2 = struct_ph.GetString("__LOID");
  str1 = guid_ph->GetString();
  str2 = struct_ph.GetString("__GUID");
  str1 = struct_ph.GPH("__type")->GetString();
  str2 = struct_ph.GetString("__TYPE");
  str1 = skey_ph->GetString();
  str1 = struct_ph.GPH("__sortkey")->GetString();
  str2 = struct_ph.GPH("__key")->GetString();
  
  struct_ph.SetOrder("sk_SDB_Structure");
  struct_ph.Get(LAST_INSTANCE);
  str1 = skey_ph->GetString();
  str2 = struct_ph.GPH("__key")->GetString();
  struct_ph.Position(-1);
  str1 = skey_ph->GetString();
  str2 = struct_ph.GPH("__key")->GetString();
  
  *skey_ph= "xxx";
*/                                                     

RECOVER
  term = YES;
ENDSEQ
  uti_handle.sdbures->Close();
  return(term);
}

/******************************************************************************/
/**
\brief  UWorkspace - 


\return term - Termination code

\param  uti_handle - 
\param  oper_string - 
\param  ws_name - Work space name
\param  user_name - User name
\param  options - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UWorkspace"

logical __cdecl UWorkspace (CSUtilityHandle &uti_handle, char *oper_string, char *ws_name, char *user_name, char *options )
{
  ODABAClient      local;
  logical          term = NO;
BEGINSEQ
  uti_handle.sdbures->online_version = YES;
  uti_handle.sdbures->accmode = !strcmp(oper_string,"List") ? PI_Read : PI_Write;
  uti_handle.sdbures->netopt  = !strcmp(oper_string,"Enable")     ||
                                !strcmp(oper_string,"Disable")    ||
                                !strcmp(oper_string,"Consolidate") ? NO : YES;
  
  if ( !strcmp(oper_string,"Enable") || !strcmp(oper_string,"Disable") )
    *uti_handle.sdbures->workspace = 0;
  
  if ( uti_handle.sdbures->Open(uti_handle.connection) ) ERROR
  
  if ( !strcmp(oper_string,"Enable") )
  {
    term = uti_handle.sdbures->dbhandle.EnableWorkspace(ws_name);
    LEAVESEQ
  }
  
  if ( !strcmp(oper_string,"Disable") )
  {
    term = uti_handle.sdbures->dbhandle.DisableWorkspace();
    LEAVESEQ
  }
  
  if ( ws_name && !strcmp(ws_name,"*") )
    ws_name = NULL;
  if ( user_name && !strcmp(user_name,"*") )
    user_name = NULL;
    
  if ( !strcmp(oper_string,"List") )
  {
    term = PrintWS(uti_handle.sdbures->dbhandle,ws_name,user_name,0,
                   options && (!strcmp(options,"/T") || !strcmp(options,"-T")) ? YES : NO);
    LEAVESEQ
  }
  
  if ( !strcmp(oper_string,"Delete") && ws_name )
  {
    term = uti_handle.sdbures->dbhandle.DeleteWorkspace(ws_name,user_name);
    LEAVESEQ
  }
  
  if ( ws_name )
    if ( uti_handle.sdbures->dbhandle.OpenWorkspace(ws_name,user_name,YES) )
                                                     SDBERR(999)
  
  if ( !strcmp(oper_string,"Create") )               LEAVESEQ

  if ( !strcmp(oper_string,"Discard") )
  {
    term = uti_handle.sdbures->dbhandle.DiscardWorkspace();
    LEAVESEQ
  }

  if ( !strcmp(oper_string,"Consolidate") )
  {
    term = uti_handle.sdbures->dbhandle.ConsolidateWorkspace();
    LEAVESEQ
  }
RECOVER
  term = YES;
ENDSEQ
  uti_handle.sdbures->Close();
  return(term);
}

