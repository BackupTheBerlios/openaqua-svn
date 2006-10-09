/********************************* Interface Class Declaration ***************************/
/**
\package  OPS - 
\class    SDB_ValueList

\brief    Value list
          A  value  list  defines  a  list of enumerated values. Value lists are
          used  for  defining  value  domains,  which  describe the extension of
          permisible  values  in  terms  of  value domain items. A value list my
          define a hierarchical structure of values (classification).
          A  value list can be defined as  database resource, but also as ad hoc
          value list e.g. in a grouping clause.
          A  value  list  can  be  used  as  global  value  list  or  as list of
          sub-categories  for  another  value.  A  value list may act as list of
          sub-categories for any number of values.

\date     $Date: 2006/07/05 14:20:25,26 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_SDB_ValueList_H
#define   _IF_SDB_ValueList_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sSDB_ValueList.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetDocFileName( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
