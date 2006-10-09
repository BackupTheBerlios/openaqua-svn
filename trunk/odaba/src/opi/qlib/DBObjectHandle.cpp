/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    DBObjectHandle

\brief    Database Object handle
          Database  object  handles  are  necessary  for  accessing  data  in an
          database  object. A  database object  can be  considered as a database
          within  a database. Each  database has a  root database object on top.
          Below  each  database  object  any  number  of  subordinated  database
          objects can be created. 
          Database  objects  in  a  database  are  logically  separated  but not
          physically.  Thus,  it  becomes  possible  to  establish links between
          structure  instances  in  different  database  objects.  Each database
          object  has, however, its own  extents containing the global instances
          of the database object. 
          The  database object  handle for  the root  database object is part of
          the  database  handle  (->  DatabaseHandle)  and need not to be opened
          explicitly. 
          A  database  object  handle  is  required  for opening extent property
          handles for accessing structure instances stored in extents.
          The  database  object  handle administrates transactions. Transactions
          can  be  started  and  stopped  for  each  object handle. The database
          object  handle is not thread save,  i.e. a database object handle must
          not be used simultaneously in different threads. 
          The  database  object  supports  version  slices,  i.e.  each database
          object may have its own current version.

\date     $Date: 2006/08/27 20:20:41,68 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBObjectHandle"

#include  <pdefault.h>
#include  <igvtx.h>
#ifndef   GSRT_ExtentListEntry_HPP
#define   GSRT_ExtentListEntry_HPP
#include  <sExtentListEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sACObject.hpp>
#include  <sCACObject.hpp>
#include  <sCClient.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sDictionary.hpp>
#include  <sLACObject.hpp>
#include  <snode.hpp>
#include  <sDBObjectHandle.hpp>


/******************************************************************************/
/**
\brief  BeginTransaction - Start transaction

        When  starting  a  transaction  all  modification  for  the database are
        stored  in a transaction buffer. A  transaction can start as an internal
        or external transaction. 
        Internal  transactions  are  used  for  small  transactions  upto  10000
        updated  database entries. Usually a small  transaction takes just a few
        seconds.  By defining a maximum buffer count for the transaction you can
        define  a  dynamical  transaction  buffer  for  speeding up processes as
        copying  data.  In  this  case  the  transaction  buffer will be cleared
        automatically when the buffer limit is reached.
        External  transactions  are  stored  in  a transaction database which is
        created  in a  path defined  in the  TABASE system variable (or ini-file
        variable).  External transactions are a  little bit slower than internal
        ones but they are not limited in capacity. 
        Transactions  can be  nested. When  starting a transaction while another
        transaction  is running the new transaction creates a transaction within
        a  transaction. The nesting level (>0) is returned as transaction level.
        When the function returns 0 the transaction could not be started. 
        Entries,  wich are  stored in  a transaction  are locked for other users
        until the top-transaction has been terminated. 
        Updates  can be moved to the upper transaction or stored in the database
        using  CommitTransaction().  Only  commiting  the  top  transaction will
        store  the updates  to the  database. Updates  made within a transaction
        become  visible in an upper transaction  when the transaction is closed.
        They  become visible for other users  when the top transaction is closed
        (CommitTransaction).
        RoleBack() can be used to undo all updates made within a transaction.

\return talevel - Transaction level
/******************************************************************************/
/**
\brief  ci - 



\param  ext_TA - External transaction
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BeginTransaction"

int16 DBObjectHandle :: BeginTransaction (logical ext_TA, int16 w_maxnum )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->StartTA(ext_TA,w_maxnum)
                    : UNDEF );

}

/******************************************************************************/
/**
\brief  ChangeTimeStamp - Change time stamp for current version

        Each  version for a database  object has a final  time limit. As long as
        the  time limit  for the  version lies  in the future you can change the
        version  end by setting a new time stamp. The new time stamp must always
        lie in the future.

\return term - Termination code

\param  version_nr - Internal version number
\param  timestamp - Timestamp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeTimeStamp"

logical DBObjectHandle :: ChangeTimeStamp (uint16 version_nr, dttm timestamp )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->ChangeTimeStamp(version_nr,timestamp)
                    : YES );

}

/******************************************************************************/
/**
\brief  Close - Close Object Handle

        Closing  the database  object handle  will reduce  the use count for the
        access  block. The database object access block is removed, when the use
        count  becomes 0, i.e. when the last database object handle referring to
        this resource is closed or destroyed.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical DBObjectHandle :: Close ( )
{
  ACObject        *obhandle = get_obhandle();
  int              saveerr  = 0;
  if ( obhandle )
  {
    saveerr = obhandle->GetErrorCode();
    
    ObjectReferenceHandle::Close();
  
    if ( saveerr )
      SDBISET(saveerr);
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  CommitTransaction - Commit transaction

        The  function stores all  changes made in  the transaction to the higher
        transaction   level.   When   terminating   a   transaction  for a given
        transaction  level  transactions  on  lower levels are commited as well.
        In  contrast  to  other  functions  CommitTransaction will not reset the
        error,  i.e. after committing  the transaction any  error or warning set
        during the transaction is still set. 
        The  function returns an error (YES),  when the transaction could not be
        stored  because  of  an  error.  This  may happen when a top transaction
        tries  to write to the database or when the transaction has set an error
        within  the transaction that does not  allow storing the transaction. In
        this  case  the  error  signaled  while  committing the transaction will
        overwrite any previously set error.
        When  ppassing  AUTO  (-1)  as  transaction  level,  the  current  (last
        recently opened) transaction will be closed.

\return term - Termination code
/******************************************************************************/
/**
\brief  ci - 



\param  talevel - Transaction level
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CommitTransaction"

logical DBObjectHandle :: CommitTransaction (int16 talevel )
{
  int          saverr   = SDBERROR;
  ACObject    *obhandle = get_obhandle();
  logical      term     = NO;
BEGINSEQ
  if ( !obhandle )                                   ERROR
    
  term = obhandle->StopTA(talevel,NO);
  
  if ( !SDBERROR )
    SDBISET(saverr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTempPropertyHandle - Create node for temporary extent



\return prophandle - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbfielddef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempPropertyHandle"

PropertyHandle DBObjectHandle :: CreateTempPropertyHandle (DBFieldDef *dbfielddef )
{
  ACObject         *obhandle = get_obhandle();
  node             *nodeptr = NULL;
  if ( obhandle )
    nodeptr = obhandle->CreateTempNode(dbfielddef);


  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prophdl_ref - Reference to Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempPropertyHandle"

PropertyHandle DBObjectHandle :: CreateTempPropertyHandle (PropertyHandle &prophdl_ref )
{
  ACObject         *obhandle = get_obhandle();
  node             *nodeptr = NULL;
  if ( obhandle )
    nodeptr = obhandle->CreateTempNode(prophdl_ref.get_nodeptr());


  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  prophdl_ref - Reference to Property handle
\param  grouping_rule - Grouping rule
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempPropertyHandle"

PropertyHandle DBObjectHandle :: CreateTempPropertyHandle (PropertyHandle &prophdl_ref, char *grouping_rule )
{
  ACObject         *obhandle = get_obhandle();
  node             *nodeptr = NULL;
  if ( obhandle )
    nodeptr = obhandle->CreateTempNode(prophdl_ref.get_nodeptr(),grouping_rule);


  return(nodeptr);
}

/******************************************************************************/
/**
\brief  DBObjectHandle - Create an Database Object handle

        The function creates a new database object handle.

-------------------------------------------------------------------------------
\brief  ci - Create database object handle

        The  constructor  creates  a  database  object  handle  from  a database
        handle.  The  constructor  creates  a  new access block for the database
        object handle, that refers to the root object of the database handle.

\param  dbhandle - Pointer to database handle
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle (DatabaseHandle &dbhandle, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
                     : ObjectReferenceHandle()
{

  Open(dbhandle,accopt,version_nr,local_ressources);

}

/******************************************************************************/
/**
\brief  ci1 - Create sub-ordinated object handle by identity

        The  constructor creates  a sub-ordinated  object handle by locating the
        database  object using the database  object identification number. A new
        access block is created and associated with the database object handle.

\param  dbobject - Database Object handle
\param  objid - Local object identity (LOID)
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle (DBObjectHandle &dbobject, int32 objid, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
                     : ObjectReferenceHandle()
{

  Open(dbobject,objid,accopt,version_nr,local_ressources);
 



}

/******************************************************************************/
/**
\brief  ci2 - Create sub-ordinated object handle by name

        The  constructor creates  a sub-ordinated  object handle by locating the
        database  object using the  database object name.  A new access block is
        created and associated with the database object handle.

\param  dbobject - Database Object handle
\param  objname - Database object name
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle (DBObjectHandle &dbobject, char *objname, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
                     : ObjectReferenceHandle()
{

  Open(dbobject,objname,accopt,version_nr,local_ressources);

}

/******************************************************************************/
/**
\brief  ci3 - Create database object for data source

        This  constructor  creates  a  database  object  handle according to the
        specification  in  a  data  source.  The  passed  access  mode  allows 
        overwriting  the access mode defined in the data source. The data source
        must  be described either  in the ini-file  passed to the application or
        in the data catalogue defined in the ini-file.

\param  odaba_client - ODABA Client Handle
\param  data_source_name - Data source name
\param  access_mode - Access mode
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle (ODABAClient &odaba_client, char *data_source_name, PIACC access_mode, ResourceTypes local_ressources )
                     : ObjectReferenceHandle()
{

  Open(odaba_client,data_source_name,access_mode,local_ressources);

}

/******************************************************************************/
/**
\brief  i05 - Copy constructor

        The  function creates a database object handle that uses the same access
        block as the handle passed to the constructor.

\param  obhandle_refc - Const reference to database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle (const DBObjectHandle &obhandle_refc )
                     : ObjectReferenceHandle()
{

  if ( obhandle_refc )
    *this = obhandle_refc;

}

/******************************************************************************/
/**
\brief  i3 - Internal constructor

        This constructor is used internally, only.

\param  acobject - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle (ACObject *acobject )
                     : ObjectReferenceHandle(acobject)
{



}

/******************************************************************************/
/**
\brief  i4 - Dummy constructor

        The  constructor creates a database  object handle without access block.
        This  handle cannot be used until  it opened explicitly using the Open()
        function.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBObjectHandle"

     DBObjectHandle :: DBObjectHandle ( )
                     : ObjectReferenceHandle()
{



}

/******************************************************************************/
/**
\brief  DeleteExtent - Delete extent

        The  function deletes an extent. This is not done automatically when the
        extent has no instances anymore.

\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtent"

logical DBObjectHandle :: DeleteExtent (char *extnames )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->DeleteExtent(extnames)
                    : YES );

}

/******************************************************************************/
/**
\brief  DeleteExtentRef - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtentRef"

logical DBObjectHandle :: DeleteExtentRef (char *extnames )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->DeleteExtendRef(extnames)
                    : YES );



}

/******************************************************************************/
/**
\brief  DisableEventHandling - Disable event handling

        The  function  will  disable  external  event  handlingfor  the database
        (object),  i.e. events are  not sent to  external event handlers set for
        property handles or to the client.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableEventHandling"

void DBObjectHandle :: DisableEventHandling ( )
{
  ACObject    *obhandle = get_obhandle();
  if ( obhandle )
    obhandle->DisableEventHandling();

}

/******************************************************************************/
/**
\brief  EnableEventHandling - 

        The  function  will  enable  external  event  handling  for the database
        (object)  after  it  has  been  disabled,  i.e. events are sent again to
        external event handlers set for property handles or to the client.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableEventHandling"

void DBObjectHandle :: EnableEventHandling ( )
{
  ACObject    *obhandle = get_obhandle();
  if ( obhandle )
    obhandle->EnableEventHandling();

}

/******************************************************************************/
/**
\brief  EventHandling - Is event handling enabled?

        The  function returns  whether external  events are  enabled or not (see
        EnableEventHandling() and DisableEventHandling())

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventHandling"

logical DBObjectHandle :: EventHandling ( )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->EventHandling()
                    : NO );

}

/******************************************************************************/
/**
\brief  ExecuteDBObjectAction - Execute object context function

        The  function  calls  an  action  that is defined in the database object
        context.  The function is executed  on the  server side first. If it was
        executed  successfully,  the  function  is  executed on the client side,
        too.
        The  action may use the SetActionResult() function to pass the result of
        the  action to the  client application. If  execution of the function on
        the  client side returns NO the result passed from the server overwrites
        any  result set by the client function. The result can be retrieved from
        the client application using the function GetActionResult().

\return term - Termination code

\param  action_name - 
\param  parm_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDBObjectAction"

logical DBObjectHandle :: ExecuteDBObjectAction (char *action_name, char *parm_string )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->ExecObjCtxFunc(action_name,parm_string)
                    : YES );

}

/******************************************************************************/
/**
\brief  ExecuteExpression - Execute expression

        Execute  expression  allows  running  inline  expresions  or  persistent
        expressions.  When running  an inline  expression containing one or more
        statements,  the  expression  must  be  enclosed  in  {}.  The result is
        returned  as  property  handle,  which  allows  an  expression returning
        elementary or complex instances as well as instance collections.
        When  calling  a  persistent  expression stored in the resource database
        the  expression name must be preceeded  by the Class name the expression
        belongs to (scope name).

\return prophdl - 

\param  res_obhandle - 
\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteExpression"

PropertyHandle DBObjectHandle :: ExecuteExpression (DBObjectHandle &res_obhandle, char *expression )
{
  ACObject        *obhandle = get_obhandle();
  PropertyHandle   ph;
  return (   obhandle 
           ? &obhandle->ExecuteExpression(res_obhandle.get_obhandle(),
                                          expression)
           : &ph );

}

/******************************************************************************/
/**
\brief  ExtentExist - Does Extent exist in database object

        An  extent defined logically in the database  schema need not exist in a
        database  or database object. Extents are created in the database object
        automatically  when accessing it  the first time  with write access. The
        function  returns  whether  an  extent  has  been already created in the
        given object (YES) or not (NO).

\return cond - Return value

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtentExist"

logical DBObjectHandle :: ExtentExist (char *extnames )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->ExtentExist(extnames)
                    : PI_undefined );

}

/******************************************************************************/
/**
\brief  GetAccess - Get access mode for object handle

        The  function  returns  the  access  mode set for the object handle when
        opening it.

\return accopt - Access option

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccess"

PIACC DBObjectHandle :: GetAccess ( )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->GetAccess()
                    : PI_undefined );

}

/******************************************************************************/
/**
\brief  GetActionResult - Get result from last action executed

        The  function  returns  the  resultstring from the last action executed.
        The  result string is  available until the  next action call, only. When
        the action does not return a result the function returns NULL.

\return result_string - Result string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActionResult"

char *DBObjectHandle :: GetActionResult ( )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? (char *)obhandle->get_nstring()
                    : (char *)NULL );

}

/******************************************************************************/
/**
\brief  GetDBHandle - Provide database handle

        The  function  returns  the  database  handle  the  for the database the
        referenced database object belongs to.

\return dbhandle - Pointer to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBHandle"

DatabaseHandle &DBObjectHandle :: GetDBHandle ( )
{
static DatabaseHandle   stat_dbhandle;
       ACObject        *obhandle = get_obhandle();
  return ( obhandle 
           ? *obhandle->GetDBHandle()->GetDatabaseHandle() 
           : stat_dbhandle );

}

/******************************************************************************/
/**
\brief  GetDataSource - 



\return dshandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataSource"

DataSourceHandle *DBObjectHandle :: GetDataSource ( )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle 
           ? obhandle->GetDataSource() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetDictionary - Get dictionary handle

        The function returns the dictionary handle for the database.

\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

DictionaryHandle &DBObjectHandle :: GetDictionary ( ) const
{
static         DictionaryHandle   stat_dict;
  ACObject    *obhandle = get_obhandle();
  return ( obhandle 
           ? *obhandle->GetDictionary()->GetDictionaryHandle() 
           : stat_dict );

}

/******************************************************************************/
/**
\brief  GetExtInstModCount - Get external modification count

        The  external  modification  count  for  a  database entry is increased,
        whenever  the instance is  stored to the  database. After reacing 255 it
        starts  with 1  again. The  modification count  can be used to determin,
        wether the database entry has been changed or not after the last check. 
        The  object  identifier  passed  to  the  function adresses the database
        entry,  which is typically an object  instance bur could be a collection
        index as well.

\return modcount - Modification count

\param  objid - Local object identity (LOID)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInstModCount"

int16 DBObjectHandle :: GetExtInstModCount (int32 objid )
{
  ACObject    *obhandle = get_obhandle();

  return ( obhandle ? obhandle->GetModCount(objid)
                    : UNDEF );

}

/******************************************************************************/
/**
\brief  GetExtent - Provide extent form Database Object

        The  function returns the name of the n-th extent in the list of extents
        that  are allocated for the database object. The collection of allocated
        extents  does not necessarily include  all defined extents. Extent names
        are provided in alphabetic order. The first extent has the index 0.
        After  providing the last extent name  the function returns NULL for the
        next extent name.

\return extentname - Extent name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtent"

char *DBObjectHandle :: GetExtent (int32 indx0 )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->GetExtent(indx0)
                    : NULL );

}

/******************************************************************************/
/**
\brief  GetExtentList - 



\return extent_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentList"

GSRT(ExtentListEntry) *DBObjectHandle :: GetExtentList ( )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->GetExtentList()
                    : (GSRT(ExtentListEntry) *)NULL );

}

/******************************************************************************/
/**
\brief  GetHighObject - Get parent object

        The function returns the parent database object handle.

\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighObject"

DBObjectHandle &DBObjectHandle :: GetHighObject ( )
{
static         DBObjectHandle   stat_obhandle;
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? *(DBObjectHandle *)obhandle->GetHighObjectPtr() 
                    : stat_obhandle );

}

/******************************************************************************/
/**
\brief  GetObject - Get Database Object

        The  function returns the  name of the  n-th database object in the list
        of  sub-ordinated  objects.  Database  object  names  are  provided  in 
        alphabetic order. The first object has the index 0.
        After  providing  the  last  database  object  name the function returns
        NULL.

\return obj_name - Database object name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObject"

char *DBObjectHandle :: GetObject (int32 indx0 )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->GetObject(indx0)
                    : (char *)NULL );

}

/******************************************************************************/
/**
\brief  GetServerVariable - Get system variable from server

        The  function returns the value for a  system variable set on the server
        side.

\return var_string - Value for the system variable

\param  var_name - System variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerVariable"

char *DBObjectHandle :: GetServerVariable (char *var_name )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle->GetClient() 
           ? obhandle->GetClient()->GetServerVariable(var_name)
           : GetSysVariable(var_name) );

}

/******************************************************************************/
/**
\brief  GetStructDef - Get structure definition

        The  function  returns  the  structure definition for the structure name
        passed.  The  structure  definition  is  provided  from  the  dictionary
        associated with the database object handle.

\return struct_def - Pointer to generel structure definition

\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *DBObjectHandle :: GetStructDef (char *scoped_name )
{
  ACObject    *obhandle   = get_obhandle();
  DBStructDef *struct_def = NULL;
  smcb        *smcbptr;
BEGINSEQ
  if ( !obhandle )                                   ERROR

  TypeKey  tkey(obhandle->GetDictionary(),scoped_name);
  if ( !(smcbptr = obhandle->GetSMCB(tkey)) )        ERROR
  if ( !smcbptr->smcbsts.stscnof() )                 SDBERR(20)

  struct_def = (DBStructDef *)smcbptr;

RECOVER

ENDSEQ
  return(struct_def);
}

/******************************************************************************/
/**
\brief  GetSystemVersion - Get system version

        The  fiunction provides the schema version of the ODABA system, which is
        the dictionary for a dictionary.

\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemVersion"

uint16 DBObjectHandle :: GetSystemVersion ( )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->GetSystemVersion()
                    : CUR_VERSION );

}

/******************************************************************************/
/**
\brief  GetTimeStamp - Get date/time for version

        The  function returns the termination time for the version number passed
        to the function.

\return timestamp - Timestamp

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimeStamp"

dttm DBObjectHandle :: GetTimeStamp (uint16 version_nr )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->GetTimeStamp(version_nr)
                    : dttm() );

}

/******************************************************************************/
/**
\brief  GetTransactionLevel - 



\return talevel - Transaction level

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTransactionLevel"

int16 DBObjectHandle :: GetTransactionLevel ( )
{
  ACObject    *obhandle = get_obhandle();
  return ( obhandle ? obhandle->GetTALevel()
                    : UNDEF );

}

/******************************************************************************/
/**
\brief  GetVersion - Get version number for the time point

        The  function returns the  veriosn number that  includes the passed time
        point.

\return version_nr - Internal version number

\param  timestamp - Timestamp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 DBObjectHandle :: GetVersion (dttm timestamp )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->GetVersion(timestamp)
                    : CUR_VERSION );

}

/******************************************************************************/
/**
\brief  IsClient - Is database object client object?

        The  function returns, whether  the database object  has been created on
        the  client  side  (YES)  or  not  (NO).  Database  objects  in  local 
        applications are both, client and server objects.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsClient"

logical DBObjectHandle :: IsClient ( )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->IsClientObject() : NO );

}

/******************************************************************************/
/**
\brief  IsEmpty - Is database object empty?

        The  function returns whether the database  object has been opened (YES)
        or not (NO), i.e. whether an access block is asociated with the handle.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical DBObjectHandle :: IsEmpty ( )
{

  return ( IsValid() ? NO : YES );

}

/******************************************************************************/
/**
\brief  IsEventHandlingEnabled - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEventHandlingEnabled"

void DBObjectHandle :: IsEventHandlingEnabled ( )
{
  ACObject    *obhandle = get_obhandle();
  if ( obhandle )
    obhandle->DisableEventHandling();

}

/******************************************************************************/
/**
\brief  IsOpened - Is database object opened?

        The  function returns whether the database  object has been opened (YES)
        or not (NO), i.e. whether an access block is asociated with the handle.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOpened"

logical DBObjectHandle :: IsOpened ( )
{
  ACObject       *obhandle = get_obhandle();
  CACObject      *cobj = NULL;
  logical         cond = YES;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  if ( !(cobj = obhandle->GetClientACObject()) )
                                                     LEAVESEQ
  if ( !cobj->IsConnected() )                        ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsServer - Is database object server object?

        The  function returns, whether  the database object  has been created on
        the  server  side  (YES)  or  not  (NO).  Database  objects  in  local 
        applications are both, client and server objects.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsServer"

logical DBObjectHandle :: IsServer ( )
{
  ACObject        *obhandle = get_obhandle();

  return ( obhandle->IsValid() ? obhandle->IsServerObject() : NO );

}

/******************************************************************************/
/**
\brief  IsValid - Is database object valid?

        The  function returns  whether the  database object  has been opened and
        whether the associated access block is valid (YES) or not (NO).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical DBObjectHandle :: IsValid ( ) const
{
  ACObject        *obhandle = get_obhandle();

  return ( obhandle ? YES : NO );

}

/******************************************************************************/
/**
\brief  NewVersion - Create new version

        The  function creates a  new version slice  for the database object. The
        timestamp  passed indicates,  when the  current version  is to be closed
        and  when the new  version will start.  You cannot define a timepoint in
        the  passed  for  ctrating  a  new  version, i.e. the time point must be
        'now' (empty) or a value that is in the future.
        New  versions can be created for  databases enabled for workspaces only,
        when all workspaces are empty (consolidated or discarded).

\return term - Termination code

\param  timestamp - Timestamp
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewVersion"

logical DBObjectHandle :: NewVersion (dttm timestamp, uint16 version_nr )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->NewVersion(timestamp,version_nr)
                    : YES );

}

/******************************************************************************/
/**
\brief  Open - Open database object handle

        The  function opens  a database  object handle.  When an access block is
        opened for the object handle it will be closed before.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci - Open database object handle

        The  function opens  a database  object handle  for the database handle.
        The  function creates a new access block for the database object handle,
        that refers to the root object of the database handle.

\param  dbhandle - Pointer to database handle
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DBObjectHandle :: Open (DatabaseHandle &dbhandle, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
{
  DBHandle  *db_handle = dbhandle.get_dbhandle();
  ACObject  *obhandle = NULL;
  logical    is_server = NO;
  logical    term = NO;
BEGINSEQ
  Close();
  SDBRESET
  if ( !db_handle )                                  SDBERR(521)
 
  switch ( db_handle->GetResourceType(local_ressources) )
  {
    case RES_server: obhandle = new CACObject(db_handle,accopt,version_nr);
                     break;
    case RES_server_intern : is_server = YES;
    case RES_local : obhandle = new LACObject(db_handle,accopt,version_nr,is_server);
                     break;
    default        : SDBERR(99)
  }
  if ( !(object_handle = obhandle) )                 SDBERR(95)
                                                     SDBCERR
  object_handle->Connect(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ci1 - Open sub-ordinated object handle by identity

        The  function  opens  a  sub-ordinated  object  handle  by  locating the
        database  object using the database  object identification number. A new
        access block is created and associated with the database object handle.

\param  dbobject - Database Object handle
\param  objid - Local object identity (LOID)
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DBObjectHandle :: Open (DBObjectHandle &dbobject, int32 objid, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
{
  ACObject  *parent   = dbobject.get_obhandle();
  ACObject  *obhandle = NULL;
  logical    term = NO;
BEGINSEQ
  Close();
  SDBRESET
  if ( !parent )                                    SDBERR(521)
 
  switch ( parent->GetResourceType(local_ressources) )
  {
    case RES_server: if ( TestSysVariable("MAINTENANCE_PROCESS","YES") )
                       parent->GetClient()->SetServerVariable("MAINTENANCE_PROCESS","YES");
                     obhandle = new CACObject(parent,objid,accopt,version_nr);
                     break;
    case RES_local : obhandle = new LACObject(parent,objid,accopt,version_nr);
                     break;
    default        : SDBERR(99)
  }
  if ( !(object_handle = obhandle) )                 SDBERR(95)
                                                     SDBCERR
  object_handle->Connect(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ci2 - Open sub-ordinated object handle by identity

        The  function  opens  a  sub-ordinated  object  handle  by  locating the
        database  object using the  database object name.  A new access block is
        created and associated with the database object handle.

\param  dbobject - Database Object handle
\param  objname - Database object name
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DBObjectHandle :: Open (DBObjectHandle &dbobject, char *objname, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
{
  ACObject  *parent   = dbobject.get_obhandle();
  ACObject  *obhandle = NULL;
  logical    term = NO;
BEGINSEQ
  Close();
  SDBRESET
  if ( !parent )                                    SDBERR(521)
 
  switch ( parent->GetResourceType(local_ressources) )
  {
    case RES_server: obhandle = new CACObject(parent,objname,accopt,version_nr);
                     break;
    case RES_local : obhandle = new LACObject(parent,objname,accopt,version_nr);
                     break;
    default        : SDBERR(99)
  }
  if ( !(object_handle = obhandle) )                 SDBERR(95)
                                                     SDBCERR
  object_handle->Connect(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ci3 - Open Database Object Handle for Data Source

        This  function  opens  a  database  object  handle  according  to  the 
        specification  in  a  data  source.  The  passed  access  mode  allows 
        overwriting  the access mode defined in the data source. The data source
        must  be described either  in the ini-file  passed to the application or
        in the data catalogue defined in the ini-file.

\param  odaba_client - ODABA Client Handle
\param  data_source_name - Data source name
\param  access_mode - Access mode
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DBObjectHandle :: Open (ODABAClient &odaba_client, char *data_source_name, PIACC access_mode, ResourceTypes local_ressources )
{
  Services               *services = SystemServices();
  ACObject               *obhandle = NULL;
  DataSourceHandle       *ds_handle;
  logical                 term = NO;
BEGINSEQ
  Close();
  SDBRESET
  ds_handle = new DataSourceHandle();
  strcpy(ds_handle->data_source,data_source_name);
  
  if ( !odaba_client || !odaba_client.IsConnected() )
    local_ressources = RES_local;
  else
    if ( local_ressources == RES_automatic && data_source_name )
      local_ressources = *data_source_name == '%' ? RES_server : RES_local;
  
  switch ( local_ressources )
  {
    case RES_server : odaba_client.GetClientPtr()->SetupDataSource(ds_handle);
                      break;
    case RES_local  : services->SetupDataSource(ds_handle);
                      break;
    default         : SDBERR(99)
  }
    
  if ( access_mode < ds_handle->accmode )
    ds_handle->accmode = access_mode;
    
  if ( ds_handle->Open(odaba_client,PI_Read) )       ERROR
    
// der use count bleibt 1, damit das object_handle destruiert wird!!  
  if ( !(object_handle = ds_handle->object_handle.get_object_handle()) ) 
                                                     ERROR
  object_handle->Connect(this);
  ds_handle->object_handle->SetDataSource(ds_handle);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenObject - 



\return term - Termination code

\param  dbobject - Database Object handle
\param  objname - Database object name
\param  accopt - Access option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenObject"

logical DBObjectHandle :: OpenObject (DBObjectHandle &dbobject, char *objname, PIACC accopt, uint16 version_nr, ResourceTypes local_ressources )
{

 return( Open(dbobject,objname,accopt,version_nr,local_ressources) );

}

/******************************************************************************/
/**
\brief  Reset - Reset object handle

        Used intrnally to set the object handle to 0.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void DBObjectHandle :: Reset ( )
{

  object_handle = NULL;

}

/******************************************************************************/
/**
\brief  ResetError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetError"

void DBObjectHandle :: ResetError ( )
{
  ACObject    *obhandle = get_obhandle();

  if ( obhandle )
    obhandle->SetErrorVariables("","","","","");

}

/******************************************************************************/
/**
\brief  ResetErrorObject - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetErrorObject"

void DBObjectHandle :: ResetErrorObject ( )
{
  ACObject    *obhandle = get_obhandle();

  if ( obhandle )
    obhandle->ResetErrorObject();

}

/******************************************************************************/
/**
\brief  RollBack - Roll back transaction

        The  function  discards  all  changes  made  in  the  transaction.  When
        terminating  a  transaction  for  a given transaction level transactions
        all  lower levels are discarded as  well. In contrast to other functions
        RollBack  will  not  reset  the  error,  i.e.  after  rolling  back  the
        transaction an error set during the transaction is still set. 
        The  function returns an error (YES),  when the transaction could not be
        reset  because of  an error.  This may  happen when some of the included
        access  blocks  could  not  be  reset  properly.  In this case the error
        signaled  during roll  back of  transaction will  overwrite an error set
        during the transaction.

\return term - Termination code
/******************************************************************************/
/**
\brief  ci - 



\param  talevel - Transaction level
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RollBack"

logical DBObjectHandle :: RollBack (int16 talevel )
{
  ACObject    *obhandle = get_obhandle();
  int          saverr   = SDBERROR;
  logical      term     = NO;
BEGINSEQ
  if ( !obhandle )                                     ERROR
    
  term = obhandle->StopTA(talevel,YES);
  
  if ( !SDBERROR )
    SDBISET(saverr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveExtentList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveExtentList"

logical DBObjectHandle :: SaveExtentList ( )
{
  ACObject        *obhandle = get_obhandle();

  return ( obhandle 
           ? obhandle->SaveExtentList()
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionResult - Set result string

        The  function allows setting a result string for the database object (or
        the  database)  handle.  The  result  string  can  be retrieved with the
        GetActionResult  function. Thus  you can  pass the  result of any action
        also  to a client application while the action is running on the server.
        The  result is  passed as  string, i.e.  the result must not contain any
        0-characters except the terminating 0.


\param  result_string - Result string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionResult"

void DBObjectHandle :: SetActionResult (char *result_string )
{
  ACObject    *obhandle = get_obhandle();
  if ( obhandle )
    obhandle->set_result_string(result_string,UNDEF);

}

/******************************************************************************/
/**
\brief  SetOverload - Set object overload

        The  function activates the object overload feature. When this option is
        activated,  extents in the current database object will overload extents
        with  the same  name in  parent objects.  An extent contains the objects
        from all instances allong the database object hierarchy.

\return overload_opt - Overload option

\param  overload_opt - Overload option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOverload"

int8 DBObjectHandle :: SetOverload (logical overload_opt )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->SetOverload(overload_opt)
                    : YES );

}

/******************************************************************************/
/**
\brief  SetServerVariable - Set system variable on server

        Systemvariables  can  be  set  for  the  server.  This  is necessary for
        controlling functions running on the server side.
        Server variables are valid on the server only for the connected client.

\return term - Termination code

\param  var_name - System variable name
\param  var_string - Value for the system variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServerVariable"

logical DBObjectHandle :: SetServerVariable (char *var_name, char *var_string )
{
  ACObject    *obhandle   = get_obhandle();

  return ( obhandle->GetClient() 
           ? obhandle->GetClient()->SetServerVariable(var_name,var_string)
           : SetSysVariable(var_name,var_string) );

}

/******************************************************************************/
/**
\brief  SetUserDefinedIdentity - 



\return term - Termination code

\param  identity_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserDefinedIdentity"

logical DBObjectHandle :: SetUserDefinedIdentity (logical identity_opt )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->SetUserDefinedIdentity(identity_opt)
                    : YES );

}

/******************************************************************************/
/**
\brief  SetVersion - Set current version

        The  function sets the current version  slice that should be active when
        accessing  instances  in  the  object.  Since the function may influence
        data  selected in property handles all  property handles should be saved
        and  cancelled before calling the  function. Data might get incompatible
        when accessing another version and must be refreshed if not cancelled.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - Set verion according to number

        The  current  database  version  is  set according to the passed version
        number.  The version  number must  be less  or equal to the last version
        number created for the database object.

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical DBObjectHandle :: SetVersion (uint16 version_nr )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->SetVersion(version_nr)
                    : YES );

}

/******************************************************************************/
/**
\brief  i1 - Set verion according to date

        The  current database version is set  according to the passed date, i.e.
        to  the version  slice (version  number) that  includes the passed date.
        The date should be the current date or a darte in the passed.

\param  date - Date
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical DBObjectHandle :: SetVersion (dbdt date )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  i2 - Set verion according to timestamp

        The  current database version is set  according to the passed timepoint,
        i.e.  to  the  version  slice  (version number) that includes the passed
        timepoint.  The  date  should  be  the  current  date  or a darte in the
        passed.

\param  timestamp - Timestamp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical DBObjectHandle :: SetVersion (dttm timestamp )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  UpdateTimestamp - Enable/Disable time stamp updating

        Whenb  objects are derived from __OBJECT,  the timestamp in the __OBJECT
        base  structure  is  updated  automatically,  whenever  an  object  is 
        modified.  The  application  may  supress time stamp updating by calling
        this  function  passing  NO  for  time_stamp_enabled.  After  disabling 
        automatic  time  stamping,  the  application  must  enable  this feature
        explicitly, when time stamping is requested again.
        The functiojn returns the old value for automatic time stamp update.

\return time_stamp_enable - Enable automatic time stamping

\param  time_stamp_enable - Enable automatic time stamping
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTimestamp"

logical DBObjectHandle :: UpdateTimestamp (logical time_stamp_enable )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->UpdateTimestamp(time_stamp_enable)
                    : YES );

}

/******************************************************************************/
/**
\brief  VersionCount - Get number of versions

        The  function returns  the number  of versions  defined for the database
        object.  The number  is identical  with the  last version number defined
        for  the database object.  When no version  has created for the database
        object the function returns 0.

\return count - Number of entries

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCount"

int32 DBObjectHandle :: VersionCount ( )
{
  ACObject    *obhandle   = get_obhandle();
  return ( obhandle ? obhandle->VersionCount()
                    : 0 );

}

/******************************************************************************/
/**
\brief  VersionIntervall - Get version interval

        The  function returns  the version  interval, i.e.  the begin and end of
        the version slice with the passed version number.

\return timeint - Time interval

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionIntervall"

INTERVAL(dttm) DBObjectHandle :: VersionIntervall (uint16 version_nr )
{
  ACObject       *obhandle   = get_obhandle();
  INTERVAL(dttm)  timint;
  return ( obhandle ? obhandle->VersionIntervall(version_nr)
                    : timint );

}

/******************************************************************************/
/**
\brief  get_obhandle - 



\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_obhandle"

ACObject *DBObjectHandle :: get_obhandle ( ) const
{
  ACObject     *obhandle = NULL;
BEGINSEQ
  if ( !this || !object_handle )                     ERROR
  obhandle = (ACObject *)object_handle;
  
  if ( !obhandle->IsValid() )                        SDBERR(401)
  

RECOVER

ENDSEQ
  return(obhandle);
}

/******************************************************************************/
/**
\brief  operator bool - DBObjectHandle opened?

        The  function returns YES (true) when  the database object is opened and
        NO  (false) when the database object is  not opened or when an error had
        occured while constructing the dictionary handle.

\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator bool"

NOTYPE DBObjectHandle :: operator bool ( ) const
{

  return ( IsValid() ? YES : NO );

}

/******************************************************************************/
/**
\brief  operator-> - 



\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator->"

ACObject *DBObjectHandle :: operator-> ( ) const
{

 return(get_obhandle());

}

/******************************************************************************/
/**
\brief  operator= - Assigning a database object handle

        The  function will close the odatabase object handle, when it is opened.
        The  access block from  the passed database  object handle is associated
        with the current handle increasing the use count by 1.

\return obhandle - 

\param  obhandle_refc - Const reference to database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DBObjectHandle &DBObjectHandle :: operator= (const DBObjectHandle &obhandle_refc )
{

  if ( get_obhandle() != obhandle_refc.get_obhandle() )
  {
    Close();
    ObjectReferenceHandle::Open(obhandle_refc.get_obhandle());
  }
  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - Are handles using the same access blocks?

        The  operator  returns  whether  the  handles refer to the same database
        object, i.e. to the same access block.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  obhandle_refc - Const reference to database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DBObjectHandle :: operator== (const DBObjectHandle &obhandle_refc )
{

  return(   this && &obhandle_refc &&
            object_handle == obhandle_refc.object_handle
          ? YES
          : NO   );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DBObjectHandle :: operator== (const DatabaseHandle &dbhandle_refc )
{

  return (   this && &dbhandle_refc &&
             object_handle == ((DBObjectHandle)dbhandle_refc).object_handle
           ? YES 
           : NO   );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictionary_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DBObjectHandle :: operator== (const DictionaryHandle &dictionary_refc )
{

  return (   this && &dictionary_refc && 
             object_handle == ((DBObjectHandle)dictionary_refc).object_handle
           ? YES
           : NO    );

}

/******************************************************************************/
/**
\brief  ~DBObjectHandle - Destructor

        The  destructor closes the database  object handle. Closing the database
        object  handle will  reduce the  use count.  The internal resources, the
        database  object access block is removed,  when the use count becomes 0,
        i.e.  when the last database object handle referring to this resource is
        closed or destroyed.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBObjectHandle"

     DBObjectHandle :: ~DBObjectHandle ( )
{

  Close();

}


