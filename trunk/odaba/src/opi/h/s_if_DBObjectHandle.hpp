/********************************* Interface Class Declaration ***************************/
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

\date     $Date: 2006/08/27 20:20:39,59 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_DBObjectHandle_H
#define   _IF_DBObjectHandle_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sDBObjectHandle.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl BeginTransaction( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl CommitTransaction( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl RollBack( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
