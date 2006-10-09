/********************************* Interface Class Declaration ***************************/
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

\date     $Date: 2006/06/25 17:07:39,57 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_DatabaseHandle_H
#define   _IF_DatabaseHandle_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sDatabaseHandle.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl Close( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Open( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
