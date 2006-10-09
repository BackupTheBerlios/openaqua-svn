/********************************* Interface Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_FunctImp



\date     $Date: 2006/05/10 20:01:27,54 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_ODC_FunctImp_H
#define   _IF_ODC_FunctImp_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sODC_FunctImp.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetCIFunctName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetCIRetValue( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetCOMParmList( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetParmCallList( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetParmList( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl IsIFImplement( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl SetLineCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl UpdatePrototype( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl UpdateSource( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
