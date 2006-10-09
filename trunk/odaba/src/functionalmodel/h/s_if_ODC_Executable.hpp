/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Executable

\brief    


\date     $Date: 2006/03/13 21:30:31,46 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_ODC_Executable_H
#define   _IF_ODC_Executable_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sODC_Executable.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetDocFileName                          ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
