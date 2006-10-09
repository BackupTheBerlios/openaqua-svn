/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODABA2_extern

\brief    


\date     $Date: 2006/03/13 21:30:30,84 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_ODABA2_extern_H
#define   _IF_ODABA2_extern_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sODABA2_extern.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetProjectPath                          ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
