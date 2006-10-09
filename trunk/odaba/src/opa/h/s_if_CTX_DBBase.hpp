/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:31:01,84}|(REF)
\class    CTX_DBBase

\brief    Base class for data base contexts
          The   base   class   for   database   contexts   provides   some basic
          functionality  for data base context  classes. In particular the class
          provides  most of the default event handlers that can be overloaded in
          specific  context  classes.  Overloaded  handlers need not to call the
          default  handlers  since  nothing  is  done  in  the default handlers.
          Handlers  for  database  events  are  usually  called  within internal
          transactions.  Thus, all  modifications made  by the event handler are
          reset when the transaction fails.
          For  a number of database operations Not-events are generated that are
          called   in   case   of   an   error.   An   error could be a database
          (consistency)  error but  the process  event (before event) could have
          denied the operation as well.

\date     $Date: 2006/03/13 08:31:10,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_CTX_DBBase_H
#define   _IF_CTX_DBBase_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sCTX_DBBase.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl HighDBContext                           ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
