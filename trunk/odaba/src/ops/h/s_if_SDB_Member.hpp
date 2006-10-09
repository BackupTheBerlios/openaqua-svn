/********************************* Interface Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Member

\brief    Structure member
          Structure  or  class  member  are  details  the  structure  definition
          consists   of.   Structure   member   may   appear  in ODABA structure
          definitions  as attributes, reference, relationship or base structure.
          In  ODABA  class  definition  members  appear  also  as  functions  or
          function,  windows  or  documents.  Members  are also used to describe
          function  parameters. In the scope of  a structure or class definition
          member names must be unique.

\date     $Date: 2006/05/15 20:14:17,70 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_SDB_Member_H
#define   _IF_SDB_Member_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sSDB_Member.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl BitSize( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl CharSize( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl DataTypeCString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetCOMType( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetPLType( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl IsAttrToBeAligned( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl KeyTypeCString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ParmTypeCString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
