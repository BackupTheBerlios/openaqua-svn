/********************************* Interface Class Declaration ***************************/
/**
\package  OPI - 
\class    DictionaryHandle

\brief    Dictionary Handle
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/06/25 17:15:37,25 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_DictionaryHandle_H
#define   _IF_DictionaryHandle_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sDictionaryHandle.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl Close( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Open( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
