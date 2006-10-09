/********************************* Interface Class Declaration ***************************/
/**
\package  OPI - 
\class    PropertyHandle

\brief    Property Handle
          Property  handle are used  to handle persistent  or transient {\b data
          source}.  A  data  source  is  a  collection,  object  instance  or an
          elementary  database  field.  A  data  source  contains the data for a
          property of a specific object.
          A  property handle  usually handles  a collection of subsequent object
          instance.  In  special  cases  the  collection  is  singular (e.g. the
          'direction'  for a  persion is  exactly one 'Adress' object instance).
          In  other cases the instance is elementary (as eg the given names of a
          person). 
          A  property handle has a cursor function  that allows to select one of
          the  instances in the collection as  the "current" instance. Only from
          the  selected instance  you can  retrieve data  by means of subsequent
          property  handles or  Get-functions (GetString(),  GetTime(), ...) for
          elementary datasources. 

          {\b Generic Property handles}

          You  can  define  generic  property handles using the generic property
          handle  contructor (PH(type)()). This requires that you have created a
          C++  header file for the referenced type.  In this case you can access
          elementary  data  field  in  the  instance  directly  referring to the
          generated  class  members.  For  references  the  instance  contains 
          corresponding  generic  property  handles  that  you  can reference by
          class  member name  as well.  In this  case you need not to create the
          property  handle  you  want  to access. This makes programming simpler
          but  in this case you must recompile the application when changing the
          database  structure. This is not  necessary when referring to property
          handles hierarchies created in the appplication.  

          {\b Property handle hierarchies}

          Property  handles  form  a  tree  that  defines  a specific view in an
          application.  When defining  this view  once the property handles cann
          be  used  as  long  as  the application follows the defined view. When
          defining  a property  handle for  "AllPersons", which  is an extent in
          the  database,  you  can  define  sub-ordinated  property  handles for
          'name',  'children', and  'company', which  refer to the persons name,
          its  children  and  the  company  the  person  is  working  for.  When
          selecting  another  person  in  the  AllPerson  property  handle  the 
          datasources  for 'name',  'children' and  'company' will change. This,
          however,  is  maintained  automatically  by  the  systen,  i.e.  when 
          changing  the selection in  an upper property  handle the data sources
          for  all subordinated  property handles  are updated automatically and
          you can access them directly. 

          {\b Filter and temporaty datasources}

          Usually  a property handle shows all the elements that have been added
          to  the data source. You can  restrict the number of visible instances
          by  setting  a  filter  (SetSelection())  using an expression or a C++
          function.  You can  also create  a new  data source using the Select()
          function which creates a temporary data source. 

          {\b Operations with Property handles}

          Property  handes  provide  all  algebraic  and set operations. You can
          apply  most of algebraic  operations  (as +,  -, * etc.) on elementary
          {\u  and} collection  data sources.  In this  case eg the '-' operator
          corresponds  to  the  relational  Minus()  operation.  In  most cases,
          however,  the types  of operands  must be  comparable. You can compare
          string  data  with  numeric  data  but  you  cannot  compare  a person
          collection with a date field. 
          Set  operations  are  defined  on the operations defined in relational
          algebra  (Intersection, Union, Minus, Select) rather that by using SQL
          like Select statements.

\date     $Date: 2006/08/29 20:24:20,15 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   _IF_PropertyHandle_H
#define   _IF_PropertyHandle_H

class     PropertyHandle;
class     ParmList;
#include  <cExecutionTypes.h>

#include  <sPropertyHandle.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

_IF_ImpExp         logical __cdecl Add( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl AppendString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl CanUpdate( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ChangeMode( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl CheckWProtect( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Close( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Contains( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Copy( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl CopyData( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl CopySet( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Day( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Delete( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl DeleteIndexEntry( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl DeleteSet( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Distinct( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Exist( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl FindKey( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl First( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Format( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Get( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetCurrentIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetDay( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetGUID( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetHours( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetKey( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetLOID( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetMinutes( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetMonth( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetParentProperty( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetPropertyHandle( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetRelative( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetRelativeCount( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetRelativeIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetSeconds( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetSubString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetText( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GetYear( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl GoTop( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl HasData( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl HasDescription( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Inherits( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl InsertString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl InstanceToString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl IsA( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl IsEmpty( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl IsTrue( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl IsWriteProtected( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Last( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl LocateIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl LocateKey( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Month( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Next( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Open( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Position( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Previous( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Provide( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ProvideGlobal( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl RemoveFromCollection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl RemoveInstance( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl RemoveString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl RepairIndex( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ReplaceString( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ResetFilter( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ResetSelection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ResetWProtect( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ResetWriteProtection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Save( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl SetFilter( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl SetSelection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl SetWProtect( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl SetWriteProtection( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl ToTop( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );
_IF_ImpExp         logical __cdecl Year( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype );

#if defined (__cplusplus)
             }
#endif

#endif
