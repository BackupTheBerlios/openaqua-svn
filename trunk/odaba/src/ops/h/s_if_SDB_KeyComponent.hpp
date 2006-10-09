/********************************* Interface Class Declaration ***************************/
/**
\package  OPS
\class    SDB_KeyComponent

\brief    Key component
          A  key component defines refers to a single attribute, a key or a base
          structure. Key components can be referenced in different ways:
          -  by referring  to an  attribute of  the structure or one of its base
          structures using the attribute name
          - by referring to a near attribute property using a property path
          -  by  referring  to  a  key  name defined for a base structure, which
          provides the attributes defined for the referenced key
          -  by referring to a base  structure, which provides the attributes of
          its identifying key as key attributes
          When  a key component  refers to a  transient attribute, indexes based
          on  such keys are  not updated automatically,  i.e. the application is
          responsible  to update the index, when  the value of a transient field
          changes, which is defined as key component.

\date     $Date: 2006/05/11 13:10:40,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_SDB_KeyComponent_H
#define   _IF_SDB_KeyComponent_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sSDB_KeyComponent.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl KeyDataDecl( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
