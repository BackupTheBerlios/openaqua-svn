/********************************* Interface Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_CodeSet

\brief    Enumeration
          An  enumeration  is  a  simple  classification. It defines a number of
          categories  by its  name and  a number  of associated codes (numerical
          values). Enumerations are based on numerical values, always.
          Since  categories may generate new classes and thus, new object types,
          each  category  in  an  enumeration  can  be  associated  with  a type
          (structure).  In this case, the enumeration  must define the base type
          (base  structure) for all object types  generated by categories of the
          enumeration.  An enumeration for { 0: male, 1: female} based on Person
          may generate classes for each category as Man and Woman.

\date     $Date: 2006/03/13 21:30:08,29 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_SDB_CodeSet_H
#define   _IF_SDB_CodeSet_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sSDB_CodeSet.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl GetDocFileName                          ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype);

#if defined (__cplusplus)
             }
#endif

#endif
