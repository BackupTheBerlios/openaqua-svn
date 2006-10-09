/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    DatabaseHandle

\brief    Database Handle
          Database  handle  must  be  created  for  accessing  data  in an ODABA
          database.  An  ODABA  database  must  be  connected with a dictionary,
          which defines the object model for the database. 
          Each  ODABA database  consists of  at least  one Database Object (Root
          Object) that is the owner od extents and other data collections. 
          When  creating a database handle the object  handle this is based on a
          database  object handle (-> DBObjectHandle)  for the root object, i.e.
          the  database handle inherits all  the functionality from the database
          object handle. 
          A  database may consists of a  number of physical separated mainbases,
          sub-bases  and data areas. This  is, however, handles internally after
          creating  the database. For creating  a multiple resource database the
          database  handle provides several functions  for initializing main and
          sub bases and data areas. 
          Moreover,  the  database  handle  provides  log and recovery features,
          that  allow logging all changes made on the database or recovering the
          database in case of errors. 
          The  workspace feature supported  by the database  handle is a sort of
          persistent  transactions.  It  allows  storing  changes  for  a longer
          period  outside the  database and  consolidating or discarding changes
          when requested by the user.

\date     $Date: 2006/06/29 18:07:54,65 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DatabaseHandle"

#include  <pdefault.h>
#include  <sACObject.hpp>
#include  <sCDBHandle.hpp>
#include  <sDBHandle.hpp>
#include  <sDictionary.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sLDBHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sXDBHandle.hpp>
#include  <sDatabaseHandle.hpp>


/******************************************************************************/
/**
\brief  ActivateShadowBase - Activate Shadow Database
        When  running a shadow database (e.g.  when worspace support is enabled)
        you  might want to read information from the shadow database rather than
        from  the  original  database.  Since  the  shadow database contains the
        information  including  all  updates  made  in  workspeces  and  not yet
        published,  the  shadow  database  is  the  only  place  where  logical 
        consistency checks can be made. 
        The  function switches from the original database to the shadow database
        and  allows reading from  the shadow database,  i.e. all read operations
        are  directed to the  shadow database instead  of the original database.
        This  funktion  has  no  effect  when the shadow database feature is not
        enabled.
        When  the shadow  database is  activated restricted updates are possible
        on  instances (you may not change  properties that are referenced as key
        components). 
        After  performing the  checking or  other tasks  you must deactivate the
        shadow database (DeactivateShadowBase()).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateShadowBase"

logical DatabaseHandle :: ActivateShadowBase ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ActivateShadowBase()
                    : YES );

}

/******************************************************************************/
/**
\brief  BackupDB - 


\return term - Termination code

\param  target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical DatabaseHandle :: BackupDB (char *target )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->BackupDB(target)
                    : YES );

}

/******************************************************************************/
/**
\brief  ChangeRecovery - Enable/disable recovery support
        This  function allows you to enable  or disable the recovery support for
        the opened database. 
        To  disable  the  recovery  support  you  can  pass  'RECOVERY_none'  as
        recovery type. 
        To   enable   recobery   support   you   can   pass   'RECOVERY_full' or
        'RECOVERY_transaction'.   You   should   enable   the   recovery support
        immediately after the latest backup.

\return term - Termination code

\param  rec_type - Type of recovery support
\param  rec_path - Folder for recovery files
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeRecovery"

logical DatabaseHandle :: ChangeRecovery (RecoveryType rec_type, char *rec_path )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ChangeRecovery(rec_type,rec_path)
                    : YES );

}

/******************************************************************************/
/**
\brief  CheckDB - Check database consistency
        The  function checks database consistence for instances and indexes (see
        CheckDB utility). 
        Running  CheckDB in client/server mode will  close all clients using the
        database  to be checked. As long as  the CheckDB function is running, no
        new  clients can be started. In client/server, you may call the function
        with  a time interval,  which defines the  time period until clients are
        closed by the system.

\return term - Termination code

\param  check_opts - 
\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical DatabaseHandle :: CheckDB (CheckOptions check_opts, char *source )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->CheckDB(check_opts,source)
                    : YES );

}

/******************************************************************************/
/**
\brief  CheckLicence - Check Application License
        The  function  checks  the  license  number  for  the user. The function
        returns  an  error  (YES)  when  the  database or the application is not
        licensed.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i01 - Register costumer
        The  function checks the user name  and license number and registers the
        license  information  in  the  database. When licensing is requested the
        license information is checked whenever the database is opened.

\param  lic_owner - Owner of the licence
\param  lic_number - Licence number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical DatabaseHandle :: CheckLicence (char *lic_owner, char *lic_number )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->CheckLicence(lic_owner,lic_number)
                    : YES );

}

/******************************************************************************/
/**
\brief  i02 - Check application licence
        The  function checks the license for  the application name passed to the
        function.  Applications  may  request  specific  licences,  which can be
        checked with this function.

\param  applname_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical DatabaseHandle :: CheckLicence (char *applname_w )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->CheckLicence(applname_w)
                    : YES );

}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code
/******************************************************************************/
/**
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical DatabaseHandle :: Close ( )
{

  return(DBObjectHandle::Close());

}

/******************************************************************************/
/**
\brief  CloseRecovery - Close recovery file
        The  function  closes  the  recovery  file. Usually the recovery file is
        closed  when closing the  database and should  not be closed explicitely
        ba the application.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseRecovery"

logical DatabaseHandle :: CloseRecovery ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->CloseRecovery()
                    : YES );

}

/******************************************************************************/
/**
\brief  CloseWorkspace - Close Workspace
        Workspaces  are  closed  when  closing  the  database.  It  is possible,
        however,  to close the active workspace explicitly.Closing the workspace
        will  not save the  changes in the  database or lower workspace but keep
        until the workspace is opened again.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseWorkspace"

logical DatabaseHandle :: CloseWorkspace ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->CloseWorkspace()
                    : YES );

}

/******************************************************************************/
/**
\brief  ConsolidateWorkspace - Consolidate Workspace
        The  function will  consolidate all  changes made  in the workspace. You
        can  consolidate  the  currently  opened  workspace, only, i.e. you must
        open  the workspace before consolidating.  For consolidating a workspace
        it  must  be  opened  with  exclusive  use.  Only when no other user has
        access to the workspace it is possible to consolidate it.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateWorkspace"

logical DatabaseHandle :: ConsolidateWorkspace ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ConsolidateWorkspace()
                    : YES );

}

/******************************************************************************/
/**
\brief  DatabaseHandle - Konstructor
        A  database  can  be  opened  in local, in client/server mode or in file
        server  mode. Local mode usually  implies exclusive access. When running
        several  applications on a  local machine the  database should be opened
        in  file  servermode  to  provide  concurrent  access  to  the database.
        Client/server  mode  is  suggested  when  running  the  database  from 
        different clients on a central server.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  a1 - Create database handle
        The  function creates  a database  handle for  an opened dictionary. The
        database  path  (cpath)  passed  to  the  constructor may contain system
        variable references that are resolved before opening the database. 
        The  database can be opened in read or write mode (accopt). When running
        the  database  in  file  server  mode  the netoption defines whether the
        database  is  running  exclusive  or  can  be shared by other users. The
        local_resources parameter defines the way the database is opened. 
        For  opening an  older version  for the  database you may pass a version
        number in version_nr.

\param  dict_handle - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access option
\param  w_netopt - Multi-user option
\param  online_version - Online versioning option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DatabaseHandle"

     DatabaseHandle :: DatabaseHandle (DictionaryHandle &dict_handle, char *cpath, PIACC accopt, logical w_netopt, logical online_version, uint16 version_nr, ResourceTypes local_ressources, logical sysenv )
                     : DBObjectHandle ()
{

  Open(dict_handle,cpath,accopt,w_netopt,online_version,version_nr,local_ressources,sysenv);

}

/******************************************************************************/
/**
\brief  c1 - Copy constructor
        This  constructor creates a copy of  the database handle. Both, the copy
        and  the origin are referring to the same resources. The database handle
        is  closed  when  closing  the  last  database  handle  instance  for  a
        database, regardles on the sequence the handles have been opened.

\param  dbhandle_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DatabaseHandle"

     DatabaseHandle :: DatabaseHandle (const DatabaseHandle &dbhandle_refc )
                     : DBObjectHandle ()
{

  if ( dbhandle_refc )
    *this = dbhandle_refc;

}

/******************************************************************************/
/**
\brief  c2 - Create a copy of the handle
        This  constructor creates a copy of  the database handle. Both, the copy
        and  the origin are referring to the same resources. The database handle
        is  closed  when  closing  the  last  database  handle  instance  for  a
        database, regardles on the sequence the handles have been opened.

\param  _dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DatabaseHandle"

     DatabaseHandle :: DatabaseHandle (DBHandle *_dbhandle )
                     : DBObjectHandle (_dbhandle)
{



}

/******************************************************************************/
/**
\brief  d1 - Create database
        This  constructor  allows  creating  a  new database. Usually creating a
        database  explicitly is not necessary. When, however, special options as
        low  est  and  higest  local  identifiers  (LOID)  are to be passed this
        constructor can be used.

\param  cpath - Complete path
\param  dasize - Size for data area
\param  pindep - Platform independance option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DatabaseHandle"

     DatabaseHandle :: DatabaseHandle (char *cpath, int32 dasize, logical pindep )
                     : DBObjectHandle ()
{

  Open(cpath,dasize,pindep);

}

/******************************************************************************/
/**
\brief  d2 - Create database handle for dictionary
        The function creates a database handle from the dictionary handle.

\param  dict_handle - Dictionary handle
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DatabaseHandle"

     DatabaseHandle :: DatabaseHandle (DictionaryHandle &dict_handle, PIACC accopt )
                     : DBObjectHandle ()
{

  Open(dict_handle,accopt);

}

/******************************************************************************/
/**
\brief  x1 - Empty database handle
        The  constructor  creates  an  empty  database handle. A database can be
        opened later with this handle using the Open() function.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DatabaseHandle"

     DatabaseHandle :: DatabaseHandle ( )
                     : DBObjectHandle ()
{



}

/******************************************************************************/
/**
\brief  DeactivateShadowBase - Deactivate Shadow Database
        Deactivating  the shadow database causes  all read operations being sent
        to  the original  database again.  This funktion  has no effect when the
        shadow database feature is not enabled.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateShadowBase"

logical DatabaseHandle :: DeactivateShadowBase ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->DeactivateShadowBase()
                    : YES );

}

/******************************************************************************/
/**
\brief  DeleteWorkspace - Delete workspace
        The  function deletes an existing workspace. The workspace must be empty
        before deleting, i.e. discard or consolidate must run before.

\return term - Termination code

\param  ws_names - Workspace name
\param  user_name - User name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWorkspace"

logical DatabaseHandle :: DeleteWorkspace (char *ws_names, char *user_name )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->DeleteWorkspace(ws_names,user_name)
                    : YES );

}

/******************************************************************************/
/**
\brief  DisableWorkspace - Disabeling workspace feature
        Disabeling  the workspace feature requires that all workspaces have been
        discarded  or consolidated.  If this  is not  the case active workspaces
        must be consolidated before. 
        When  disabling the  workspace feature  sucsessfully the shadow database
        is removed as well.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableWorkspace"

logical DatabaseHandle :: DisableWorkspace ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->DisableWorkspace()
                    : YES );

}

/******************************************************************************/
/**
\brief  DiscardWorkspace - Discard Workspace
        The  function will  through away  all changes  made in the workspace for
        the  currently  opened  workspace.  The  workspace  will  be  closed and
        removed.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiscardWorkspace"

logical DatabaseHandle :: DiscardWorkspace ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->DiscardWorkspace()
                    : YES );

}

/******************************************************************************/
/**
\brief  EnableWorkspace - Enable workspace feature
        The  function enables the  usage of workspaces  and shadow database. The
        function can be executed only when the database is opened exclusive. 
        When  no  path  or  an  empty  path is passed as location for the shadow
        database  the shadow  database is  positioned in  the same folder as the
        original  database  and  with  the  same  name  as  the database but the
        extension  is  changed  to  .sdw  or  appended  if no extension has been
        defined for the database.

\return cond - Return value

\param  sdw_path - Complete path for shadow database
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableWorkspace"

logical DatabaseHandle :: EnableWorkspace (char *sdw_path )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->EnableWorkspace(sdw_path)
                    : NO );

}

/******************************************************************************/
/**
\brief  ExecuteDatabaseAction - 


\return term - Termination code

\param  action_name - 
\param  parm_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDatabaseAction"

logical DatabaseHandle :: ExecuteDatabaseAction (char *action_name, char *parm_string )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ExecDBCtxFunc(action_name,parm_string)
                    : YES );

}

/******************************************************************************/
/**
\brief  ExistWorkspace - Exist workspace?
        The  function returns whether a workspace with the passed workspace name
        (ws_name)  exists as  subordinated workspace  (YES) or not(NO). When the
        database  has  already  opened  a  workspace  the function looks for the
        workspace relatively to the opened one.

\return cond - Return value

\param  ws_names - Workspace name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistWorkspace"

logical DatabaseHandle :: ExistWorkspace (char *ws_names )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ExistWorkspace(ws_names)
                    : NO );

}

/******************************************************************************/
/**
\brief  FlushClusterPool - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical DatabaseHandle :: FlushClusterPool ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->FlushClusterPool()
                    : YES );

}

/******************************************************************************/
/**
\brief  GetDatabaseID - Get database resource number
        The function returns the database resource number.

\return db_id - Database resource number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDatabaseID"

int32 DatabaseHandle :: GetDatabaseID ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetDatabaseID()
                    : UNDEF );

}

/******************************************************************************/
/**
\brief  GetNewTypeID - Get next available type id


\return sid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewTypeID"

int16 DatabaseHandle :: GetNewTypeID ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetNewTypeID()
                    : UNDEF );

}

/******************************************************************************/
/**
\brief  GetPath - Get path for the opened database
        The  function  returns  the  database  path for the opened database. The
        path  returned refers to  the database path  and does not contain system
        variable references anymore.

\return dbpath - Complete database path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPath"

char *DatabaseHandle :: GetPath ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  char      *path     = "";
BEGINSEQ
  if ( !dbhandle )                                  ERROR
  
  if ( !(path = dbhandle->GetPath()) )              ERROR
RECOVER
  path = "";
ENDSEQ
  return(path);
}

/******************************************************************************/
/**
\brief  GetRecoveryFile - Provide name of recovery file
        The  function  returns  the  name  of the recovery file according to the
        passed recovery number.

\return rfilname - Name of recovery file

\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryFile"

char *DatabaseHandle :: GetRecoveryFile (uint16 recnum )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetRecoveryFile(recnum)
                    : (char *)NULL );

}

/******************************************************************************/
/**
\brief  GetRecoveryNum - Provide reacovery number
        The function returns the number for the current recovery file.

\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryNum"

uint16 DatabaseHandle :: GetRecoveryNum ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetRecoveryNum()
                    : 0 );

}

/******************************************************************************/
/**
\brief  GetRecoveryPath - Provide path for recovery folder
        The  function returns  the path  for the  folder containing the recovery
        files.

\return recpath - Recovery path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryPath"

char *DatabaseHandle :: GetRecoveryPath ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetRecoveryPath()
                    : (char *)NULL );

}

/******************************************************************************/
/**
\brief  GetRecoveryStartNumber - 


\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryStartNumber"

uint16 DatabaseHandle :: GetRecoveryStartNumber ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetRecoveryStartNumber()
                    : 0 );

}

/******************************************************************************/
/**
\brief  GetRecoveryType - 


\return rec_type - Type of recovery support

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryType"

RecoveryType DatabaseHandle :: GetRecoveryType ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetRecoveryType()
                    : RECOVERY_none );

}

/******************************************************************************/
/**
\brief  GetSchemaVersion - Get schema version
        The  function  returns  the  current  schema  version  number  for  the 
        database.

\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSchemaVersion"

uint16 DatabaseHandle :: GetSchemaVersion ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetSchemaVersion()
                    : CUR_SYSVERSION );

}

/******************************************************************************/
/**
\brief  GetSystemVersion - Get system version
        The  fiunction provides the schema version of the ODABA system, which is
        the dictionary for a dictionary.

\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemVersion"

uint16 DatabaseHandle :: GetSystemVersion ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetSystemVersion()
                    : CUR_SYSVERSION );

}

/******************************************************************************/
/**
\brief  GetVersionString - Provide database version
        The function provides the database version and sub version as string.

\return version_string - Version string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionString"

char *DatabaseHandle :: GetVersionString ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetVersionString()
                    : (char *)NULL );

}

/******************************************************************************/
/**
\brief  GetWorkspace - Get workspace names
        The  function returns the workspaces defined below an existing workspace
        or  database. The  function returns  workspace names  by index sorted in
        alphabetical  order  (first  entry  is  retrieved  with  index  0). Only
        workspaces  on a  given level  are returned.  To get workspaces on lower
        levels you must pass the root path for the lower level. 
        Workspace  information is buffered when retrieving it the first time. To
        refresh  the internal workspace list you  should pass the refresh option
        (YES). 
        For  retrieving workspaces owned by the user  a user name can be passed.
        Not passing a username will return all workspaces. 
        The  name  for  the  workspace  is  returned in ws_name in addition when
        passing  a pointer to a character  array. Otherwise the name is returned
        only  in  the  result  area  of  the  property  handle,  which  might be
        destroyed after the next property handle function call. 
        st deactivate the shadow database (DeactivateShadowBase()).

\return ws_name - Work space name

\param  ws_root - Workspace root
\param  ws_index - Number of workspace to be retrieved
\param  user_name - User name
\param  ws_name - Work space name
\param  refresh_opt - Refresh option
\param  ws_info - Workspace information
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspace"

char *DatabaseHandle :: GetWorkspace (char *ws_root, int32 ws_index, char *user_name, char *ws_name, logical refresh_opt, char *ws_info )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->GetWorkspace(ws_root,ws_index,user_name,ws_name,refresh_opt,ws_info)
                    : NULL );

}

/******************************************************************************/
/**
\brief  IgnoreWriteProtect - Ignor permanent write protection
        The  function  allows  disabling  the  permanent write protection. After
        disabling  permanent write protection instances that have been marked as
        permanent  write  protected  (->  SetWProtect()) can be updated for this
        database handle.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IgnoreWriteProtect"

logical DatabaseHandle :: IgnoreWriteProtect ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle && dbhandle->GetLocalDBHandle() ? dbhandle->IgnoreWriteProtect()
                    : YES );

}

/******************************************************************************/
/**
\brief  InitDataArea - Initialise DataArea
        The  function allows  initializing a  new data  area. Data areas must be
        created  consecutive order. A data area 0 is created automatically, when
        creating  the  upper  sub-base,  i.e.  the next data area to be crreated
        would be data area 1 etc.

\return term - Termination code

\param  mbnumber - Main base number
\param  sbnumber - Sub-base number
\param  danumber - Data area number
\param  filename - File name for DataArea file
\param  dasize - Size for data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDataArea"

logical DatabaseHandle :: InitDataArea (int16 mbnumber, int16 sbnumber, uint16 danumber, char *filename, int32 dasize )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->InitDataArea(mbnumber,sbnumber,danumber,filename,dasize,NULL,NULL)
                    : YES );

}

/******************************************************************************/
/**
\brief  InitMainBase - Initialize main base
        The  function allows  initializing a  new main  base. Main bases must be
        created  in consecutive order. The first  main base to be crreated would
        be  main  base  0,  the  next  main base 1 etc. A main base 0 is created
        automatically, when creating a single resource database. 
        Creating  a mainbase automatically creates a  sub-base 0 and a data area
        0. Data area size (dasize) and file name refer to data area 0. 
        Main  bases  are  generating  local  identities.  The  size  for  local 
        identities  depends  on  the  database  type  and  is  64  bit for large
        databases and 32 bit for small databases:
        large DB:  0xSSRRRRNNNNNNNNNN
        small DB: 0xRRNNNNNN
        'SS'  is used internally for  the system. RR or  RRRR is the part of the
        identity  that  is  described  by  the  range of identities for the main
        base,  i.e. a mainbase generates  identities with range values according
        to the low and high value passed (lowEBN, highEBN). 
        Usually  a  database  has  certain  limitations  to 2 or 4 giga byte (31
        bit).  This is sufficiant in many cases but some sutuations require more
        space.  Allocating  a  large  database  (YES)  will change the following
        limitations:
        Data area size: 2 GB to 262144 GB
        number of identities: ca 4 Giga to more than 16,000,000 Giga
        number of mainbases: 252 to 32760
        Large  databases  do  not  support,  however,  main  bases  splitted  in
        different  sub bases and data areas. This feature has been introduced to
        overcome  database limitations for small  databases and is not necessary
        for large databases. 
        Because  of  different  interger  presentations  on  different platforms
        databases  are  platform  dependent  and must be converted when changing
        the  platform. It is,  however, also possible  to store data in platform
        independent format when passing YES forte pindep parameter.

\return term - Termination code

\param  mbnumber - Main base number
\param  filename - File name for DataArea file
\param  lowEBN - First entry number in database
\param  highEBN - Last entry number in database
\param  dasize - Size for data area
\param  largedb - Large database option
\param  pindep - Platform independance option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMainBase"

logical DatabaseHandle :: InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize, logical largedb, logical pindep )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->InitMainBase(mbnumber,filename,lowEBN,highEBN,dasize,NULL,NULL,largedb,pindep)
                    : YES );

}

/******************************************************************************/
/**
\brief  InitRecovery - Initialise recovery file
        The function initializes a new recovery file.

\return term - Termination code

\param  recpath - Recovery path
\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRecovery"

logical DatabaseHandle :: InitRecovery (char *recpath, uint16 recnum )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->InitRecovery(recpath,recnum)
                    : YES );

}

/******************************************************************************/
/**
\brief  InitSubBase - Initialise sub-base
        The  function  allows  initializing  a  new  sub-base. Sub-bases must be
        created  in  consecutive  order.  A sub-base 0 is created automatically,
        when  creating  the  upper  main  base,  i.e.  the  next  sub-base to be
        crreated would be sub-base 1 etc.
        Data  area size  (dasize) and  File name  refer to data area 0, which is
        automatically allocated with the sub-base.

\return term - Termination code

\param  mbnumber - Main base number
\param  sbnumber - Sub-base number
\param  filename - File name for DataArea file
\param  dasize - Size for data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSubBase"

logical DatabaseHandle :: InitSubBase (int16 mbnumber, int16 sbnumber, char *filename, int32 dasize )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->InitSubBase(mbnumber,sbnumber,filename,dasize,NULL,NULL)
                    : YES );

}

/******************************************************************************/
/**
\brief  IsLicenced - Is database licensed
        The   function   returns   whether   the   database   has  been licensed
        successfully.  Usually the database will not be opened when a license is
        required  and the database  is not licensed.  When running with disabled
        license  services this function  can be used  to check the license after
        opening the database.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLicenced"

logical DatabaseHandle :: IsLicenced ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->IsLicenced()
                    : NO );

}

/******************************************************************************/
/**
\brief  IsShared - Is database shared by several users
        The  function returns YES when the database  has been opened in net mode
        on a local machine or when running in a client/server environment.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsShared"

logical DatabaseHandle :: IsShared ( )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->get_net_option()
                    : NO );

}

/******************************************************************************/
/**
\brief  LocateWorkspace - Locate an existing Workspace
        The  function checks  whether the  worspace with  the passed name exists
        relatively to the current workspace.

\return cond - Return value

\param  ws_names - Workspace name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateWorkspace"

logical DatabaseHandle :: LocateWorkspace (char *ws_names )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->LocateWorkspace(ws_names)
                    : NO );

}

/******************************************************************************/
/**
\brief  Open - Opening a database handle
        The  function allows opening a database handle. When the database handle
        is already opened it will be closed before re-opening it.
        A  database  can  be  opened  in local, in client/server mode or in file
        server  mode. Local mode usually  implies exclusive access. When running
        several  applications on a  local machine the  database should be opened
        in  file  servermode  to  provide  concurrent  access  to  the database.
        Client/server  mode  is  suggested  when  running  the  database  from 
        different clients on a central server.

\return term - Termination code
/******************************************************************************/
/**
\brief  a1 - Open database handle
        The  function creates  a database  handle for  an opened dictionary. The
        database  path  (cpath)  passed  to  the  function  may  contain  system
        variable references that are resolved before opening the database. 
        The  database can be opened in read or write mode (accopt). When running
        the  database  in  file  server  mode  the netoption defines whether the
        database  is  running  exclusive  or  can  be shared by other users. The
        local_resources parameter defines the way the database is opened. 
        For  opening an  older version  for the  database you may pass a version
        number in version_nr.

\param  dict_handle - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access option
\param  w_netopt - Multi-user option
\param  online_version - Online versioning option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DatabaseHandle :: Open (DictionaryHandle &dict_handle, char *cpath, PIACC accopt, logical w_netopt, logical online_version, uint16 version_nr, ResourceTypes local_ressources, logical sysenv )
{
  Dictionary  *dictionary = dict_handle.get_dictionary();
  DBHandle    *db_hdl = NULL;
  logical      is_server = NO;
  logical      term = NO;
BEGINSEQ
  Close();
  SDBRESET
  if ( !dictionary )                                 SDBERR(520)
  
  switch ( dictionary->GetResourceType(local_ressources,cpath) )
  {
    case RES_server: if ( !(db_hdl = new CDBHandle(dictionary,cpath,accopt,online_version,version_nr,sysenv)) )
                                                     SDBERR(95)
                                                     SDBCERR
                     break;
    case RES_server_intern : is_server = YES;
    case RES_local : if ( !IsFile(cpath) || LDBHandle::Exist(cpath,NO) )
                       db_hdl = new LDBHandle(dictionary,cpath,accopt,w_netopt,online_version,version_nr,sysenv,is_server);
                     else
                       db_hdl = new XDBHandle(dictionary,cpath,accopt);
                     SDBCERR
                     break;
    default        : SDBERR(99)
  }
  object_handle = db_hdl;
  object_handle->Connect(this);
RECOVER
  delete db_hdl;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  d1 - Create new database
        This  function  allows  creating  a  new  database.  Usually  creating a
        database  explicitly is not necessary. When, however, special options as
        low  est  and  higest  local  identifiers  (LOID)  are to be passed this
        constructor can be used.

\param  cpath - Complete path
\param  dasize - Size for data area
\param  pindep - Platform independance option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DatabaseHandle :: Open (char *cpath, int32 dasize, logical pindep )
{
  DBHandle    *db_hdl = NULL;
  logical      term = NO;
BEGINSEQ
  Close();
  SDBRESET
  if ( !(db_hdl = new LDBHandle(cpath,dasize,pindep)) )
                                                     SDBERR(95)
                                                     SDBCERR
  object_handle = db_hdl;
  object_handle->Connect(this);
RECOVER
  delete db_hdl;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  d2 - Creates database handle for dictionary
        The function creates a database handle from the dictionary handle.

\param  dict_handle - Dictionary handle
\param  accopt - Access option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DatabaseHandle :: Open (DictionaryHandle &dict_handle, PIACC accopt )
{
  Dictionary  *dictionary = dict_handle.get_dictionary();
  DBHandle    *db_hdl = NULL;
  logical      term = NO;
BEGINSEQ
  Close();
  SDBRESET
  if ( !dictionary )                                 SDBERR(520)
  
  if ( !(db_hdl = new LDBHandle(dictionary,accopt)) )SDBERR(95)
                                                     SDBCERR
  object_handle = db_hdl;
  object_handle->Connect(this);
RECOVER
  delete db_hdl;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenDatabase - 


\return term - Termination code

\param  dict_handle - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access option
\param  w_netopt - Multi-user option
\param  online_version - Online versioning option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDatabase"

logical DatabaseHandle :: OpenDatabase (DictionaryHandle &dict_handle, char *cpath, PIACC accopt, logical w_netopt, logical online_version, uint16 version_nr, ResourceTypes local_ressources, logical sysenv )
{

  return( Open(dict_handle, cpath, accopt, w_netopt, online_version, version_nr, local_ressources, sysenv ) );

}

/******************************************************************************/
/**
\brief  OpenRecovery - Open recovery file
        The   function   opens   the   recovery   file.   Usually   this is done
        automatically  when  opening  the  database  and  should  not  be opened
        explicitely by the user.

\return term - Termination code

\param  userinfo - Area for application recovery information
\param  uilen - Length of application data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRecovery"

logical DatabaseHandle :: OpenRecovery (char *userinfo, int16 uilen )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->OpenRecovery(userinfo,uilen)
                    : YES );

}

/******************************************************************************/
/**
\brief  OpenWorkspace - Open Workspace
        The  function creates or opens an  existing workspace. After opening the
        workspace  all  updates  are  stored  in  the opened workspace. When the
        workspace  is used the  first time it  is created automatically. When it
        does  already  exist  the  existing  workspace  is opened. You can check
        whether  a workspace exists using  the LocateWorkspace() function, which
        returns true when the workspace has already been created.
        Usually  the  workspace  file  is  created  in  the  same  folder as the
        database.  You may, however, pass an explicit location for the workspace
        via the ws_path parameter.

\return term - Termination code

\param  ws_names - Workspace name
\param  user_name - User name
\param  exclusive - 
\param  ws_path - Physical location for the workspace
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWorkspace"

logical DatabaseHandle :: OpenWorkspace (char *ws_names, char *user_name, logical exclusive, char *ws_path )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->OpenWorkspace(ws_names,user_name,exclusive,ws_path)
                    : NO );

}

/******************************************************************************/
/**
\brief  RecreateExtent - Recreate Index for an extent
        The  function  repairs  the  indexes  for  a corrupted extent index. The
        function  deletes all indexes for the extent and parses the database for
        instances  with the type of the extent. The function works correct only,
        when all instances in the database belong to the extent.

\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecreateExtent"

logical DatabaseHandle :: RecreateExtent (char *extnames )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->RecreateExtent(extnames)
                    : YES );

}

/******************************************************************************/
/**
\brief  ResetLastSchemaVersion - 


\return term - Termination code

\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastSchemaVersion"

logical DatabaseHandle :: ResetLastSchemaVersion (logical reset_opt )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ResetLastSchemaVersion(reset_opt)
                    : YES );

}

/******************************************************************************/
/**
\brief  ResetLastVersion - Reset last version activated
        The  function will reset the last version activated for the database. It
        will  remove all database entries with the new version and recreates the
        state of the database as it has been when starting the new version.

\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastVersion"

logical DatabaseHandle :: ResetLastVersion (uint16 version_nr )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->ResetLastVersion(version_nr)
                    : YES );

}

/******************************************************************************/
/**
\brief  RestoreDB - 


\return term - Termination code

\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical DatabaseHandle :: RestoreDB (char *source )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->RestoreDB(source)
                    : YES );

}

/******************************************************************************/
/**
\brief  SetupTypeID - Update type id


\return term - Termination code

\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTypeID"

logical DatabaseHandle :: SetupTypeID (int16 sid )
{
  DBHandle  *dbhandle = get_dbhandle();
  return ( dbhandle ? dbhandle->SetupTypeID(sid)
                    : YES );


}

/******************************************************************************/
/**
\brief  get_dbhandle - 


\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_dbhandle"

DBHandle *DatabaseHandle :: get_dbhandle ( )
{
  ACObject     *obhandle = get_obhandle();
BEGINSEQ
  if ( !obhandle )                                    SDBERR(402)
RECOVER

ENDSEQ
  return ( obhandle ? obhandle->GetThisDBHandle() : NULL );

}

/******************************************************************************/
/**
\brief  operator bool - Database handle opened?
        The  function returns YES (true) when  the database jandle is opened and
        NO  (false) when the databse is not  opened or when an error had occured
        while constructing the database handle.

\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator bool"

NOTYPE DatabaseHandle :: operator bool ( ) const
{

  return ( object_handle ? YES : NO );

}

/******************************************************************************/
/**
\brief  operator!= - Compare database handles
        The  function  returns  true  (YES)  when  the database handles refer to
        different database access blocks and false (NO) otherwise.

\return cond - Return value
-------------------------------------------------------------------------------
\brief  i00 - 


\param  dbhandle_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical DatabaseHandle :: operator!= (DatabaseHandle &dbhandle_ref )
{

  return (   !this || !dbhandle_ref || 
             object_handle != dbhandle_ref.get_object_handle() 
           ? YES
           : NO   );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  obhandle_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical DatabaseHandle :: operator!= (DBObjectHandle &obhandle_ref )
{

  return (   !this || !obhandle_ref || 
             object_handle != obhandle_ref.get_object_handle() 
           ? YES
           : NO   );

}

/******************************************************************************/
/**
\brief  operator-> - 


\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator->"

DBHandle *DatabaseHandle :: operator-> ( )
{

  return(get_dbhandle());

}

/******************************************************************************/
/**
\brief  operator= - Assignment operator
        The  operator assigns the  database access block  of the passed database
        handle  to  the  current  database  handle.  Before the current database
        handle is closed.

\return dbhandle - Pointer to database handle
-------------------------------------------------------------------------------
\brief  i00 - 


\param  dbhandle_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DatabaseHandle &DatabaseHandle :: operator= (const DatabaseHandle &dbhandle_refc )
{

  if ( get_obhandle() != dbhandle_refc.get_obhandle() )
  {
    Close();
    ObjectReferenceHandle::Open(dbhandle_refc.get_obhandle());
  }
  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  acobject - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DatabaseHandle &DatabaseHandle :: operator= (ACObject *acobject )
{

  object_handle = acobject;

  return(*this);
}

/******************************************************************************/
/**
\brief  ~DatabaseHandle - Destructur
        The  destructor closes the database  handle. Closing the database handle
        will  reduce the use count. The  internal resources, the database access
        block  is  removed,  when  the  use  count becomes 0, i.e. when the last
        database handle referring to this resource is closed or destroyed.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DatabaseHandle"

     DatabaseHandle :: ~DatabaseHandle ( )
{

  Close();

}


