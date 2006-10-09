/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:38:31,48}|(REF)
\class    FileHandle

\brief    


\date     $Date: 2006/03/13 08:38:35,35 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_FileHandle_H
#define   _IF_FileHandle_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sFileHandle.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl AlignText                               ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl Close                                   ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl CurrentLine                             ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl IsOpened                                ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl LinePosition                            ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl Open                                    ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl Out                                     ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
