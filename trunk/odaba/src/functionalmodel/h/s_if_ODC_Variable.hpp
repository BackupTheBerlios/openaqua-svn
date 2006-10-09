/********************************* Interface Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_Variable



\date     $Date: 2006/05/10 20:49:09,54 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_ODC_Variable_H
#define   _IF_ODC_Variable_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sODC_Variable.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetCastType( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
