/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:31:15,81}|(REF)
\class    CTX_Structure

\brief    Structure Context
          A  structure context  is created  for each  structure type. It defines
          the  connection  between  the  instance  and the instance description.
          Moreover,  it allows determining the active con-text hierarchy for the
          structure  instance,  i.e.  the  parent property/extent, the structure
          the  parent property  is defined  in, the  parent parent property etc.
          Thus,  the structure context  defines the context  in which the object
          instance has been provided.
          The  parent  context  for  a  structure  context  is always a property
          context.  This  can  be  the  property  context  for  an extent or for
          another property within a structure instance.
          The  structure  context  allows  handling  read and updating events as
          well as creating or deleting events.

\date     $Date: 2006/03/13 08:31:20,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_CTX_Structure_H
#define   _IF_CTX_Structure_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sCTX_Structure.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetCollection                           ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl GetInstance                             ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);
_IF_ImpExp         logical __cdecl GetOldInstance                          ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
