/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:27:33,14}|(REF)
\class    SystemClass

\brief    


\date     $Date: 2006/03/13 08:27:41,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_SystemClass_H
#define   _IF_SystemClass_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sSystemClass.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl Date                                    ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl GetSYSDB                                ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl Message                                 ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl Time                                    ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
