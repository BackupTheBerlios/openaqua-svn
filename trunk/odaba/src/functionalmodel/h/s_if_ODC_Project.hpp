/********************************* Interface Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_Project



\date     $Date: 2006/05/10 19:45:50,21 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_ODC_Project_H
#define   _IF_ODC_Project_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sODC_Project.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetDocFileName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetProjectPath( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
