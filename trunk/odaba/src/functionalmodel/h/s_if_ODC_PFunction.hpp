/********************************* Interface Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_PFunction



\date     $Date: 2006/04/27 12:45:20,75 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_ODC_PFunction_H
#define   _IF_ODC_PFunction_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sODC_PFunction.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl SetLineCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
