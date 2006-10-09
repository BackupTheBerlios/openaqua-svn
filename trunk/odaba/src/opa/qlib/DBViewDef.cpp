/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewDef

\brief    Internal view defintion
          The  internal view definition defines the view base, sort orders, view
          properties,   filter,   post-   and   pre   conditions.  Internal view
          defintiions  are  either  defined  in  an  application  programm or by
          reading view definitions from the dictionary.

\date     $Date: 2006/03/12 19:17:15,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBViewDef"

#include  <popa7.h>
#ifndef   DLL_DBVFilter_HPP
#define   DLL_DBVFilter_HPP
#include  <sDBVFilter.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DBVOrder_HPP
#define   DLL_DBVOrder_HPP
#include  <sDBVOrder.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DBVProperty_HPP
#define   DLL_DBVProperty_HPP
#include  <sDBVProperty.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sDictionary.hpp>
#include  <sDBViewDef.hpp>


/******************************************************************************/
/**
\brief  AddFilter - Setting filter condition
        Set  filter  allows  setting  a  filter  condition  for  each collection
        defined  in  the  view  path.  The  property  path  must be a valid path
        defined  in the view path, i.e. a property path or the leading part of a
        property  path defined in  the view path.  The filter expression defines
        an  expression  in  the  scope  of  the  structure  of  the  referenced 
        collection.

\return term - Termination code

\param  prop_path - Property path
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddFilter"

logical DBViewDef :: AddFilter (char *prop_path, char *expression )
{
  DBVFilter              *filter;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(expression,UNDEF)
  SDBEV2(prop_path,UNDEF)
  SDBEV3(name,ID_SIZE)
  
  if ( view_path && *view_path && !prop_path )  SDBERR(554)
  if ( !expression )                            SDBERR(554)
  
  filter = new DBVFilter(prop_path,expression);
  
  filters->AddTail(filter);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddOrder - Set order for view path collection
        The  function allows defining the sort order for a collection defined in
        the  view path.  The property  path must  be a valid path defined in the
        view  path, i.e. a property path or  the leading part of a property path
        defined in the view path.
        The  passed  key  name  must  be  a  valid  order  for  the  referenced 
        collection.

\return term - Termination code

\param  prop_path - Property path
\param  sort_key_name - Sort key name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddOrder"

logical DBViewDef :: AddOrder (char *prop_path, char *sort_key_name )
{
  DBVOrder               *order;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(sort_key_name,ID_SIZE)
  SDBEV2(prop_path,UNDEF)
  SDBEV3(name,ID_SIZE)
  
  if ( view_path && *view_path && !prop_path )  SDBERR(554)
  
  order = new DBVOrder(prop_path,sort_key_name);
  
  sort_orders->AddTail(order);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddProperty - Add property to view
        The  function  adds  a  property  to  the  view definition. The property
        source  and  type  define  the  way  the  value  for  the  property  is 
        calculates.  When passing  an expression  the expression must be defined
        in  the  scope  of  the  view  base, i.e. it must refer to properties of
        instances  involved  in  the  view  via  the  view path. The size allows
        changing the size of the original field. 
        The  function must be  called before creating  a property handle for the
        view.  When calling the function after the view property handle has been
        constructed  the  new  property  will  not be pert of the view currently
        executed.

\return term - Termination code
-------------------------------------------------------------------------------
\brief i00 - Create view property from source
        This  implementation  creates  a  view  property  directly  from  source
        definition.

\param  prop_names - Property name
\param  prop_source - Property source
\param  source_type - Source type
\param  size_w - Field size
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddProperty"

logical DBViewDef :: AddProperty (char *prop_names, char *prop_source, ADT_Types source_type, int32 size_w )
{
  DBVProperty            *property;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(prop_source,UNDEF)
  SDBEV2(prop_names,UNDEF)
  SDBEV3(name,ID_SIZE)
  
  if ( !prop_names || !prop_source )                  SDBERR(555)
  if ( !strcmp(prop_source,"__SORTKEY") )
    source_type = ADT_SortKey;
  if ( !strcmp(prop_source,"__SORTKEY_STRING") )
    source_type = ADT_SortKey_String;
  if ( !strcmp(prop_source,"__IDENTITY") )
    source_type = ADT_GUID;
  if ( !strcmp(prop_source,"__LOID") )
    source_type = ADT_LOID;
  if ( !strcmp(prop_source,"__GUID") )
    source_type = ADT_GUID;
  if ( !strcmp(prop_source,"__TYPE") )
    source_type = ADT_Type;
  
  if ( source_type != ADT_PropertyPath && source_type != ADT_Expression     &&
       source_type != ADT_SortKey      && source_type != ADT_SortKey_String &&
       source_type != ADT_Type  && source_type != ADT_GUID && source_type != ADT_LOID )
                                                      SDBERR(556)
  property = new DBVProperty(prop_names,prop_source,source_type,size_w);
  
  properties->AddTail(property);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01 - Create view property for relative view
        This  implementation creates a  view property that  refers to a sub-view
        (relative  view). The view definition  passed contains the structure and
        the  domain definition of the related  view. The view definition will be
        copied to the property definition referring to the view definition.

\param  prop_names - Property name
\param  view_def - Internal view definition
\param  source_type - Source type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddProperty"

logical DBViewDef :: AddProperty (char *prop_names, DBViewDef &view_def, ADT_Types source_type )
{
  DBVProperty            *property;
  logical                 term = NO;
  property = new DBVProperty(prop_names,view_def,source_type);
  
  properties->AddTail(property);
  return(term);
}

/******************************************************************************/
/**
\brief  DBViewDef - Constructor
        A  view can be defined based on a  defined view expression or based on a
        given  property handle. For  defining a view  in a given structure scope
        (structure based view) the structure name must be passed.
        You  may pass  a view  name. When  not passing  a view name the function
        creates a view name automatically.

-------------------------------------------------------------------------------
\brief i0 - Create view definition collection
        The  constructor creates a view definition  for the collection passed in
        the property handle. .

\param  prop_hdl - Property Handle
\param  view_name_w - View name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewDef"

                        DBViewDef :: DBViewDef (PropertyHandle &prop_hdl, char *view_name_w )
                     : object_handle(prop_hdl.GetObjectHandle().get_obhandle()),
property_handle(),
dictionary(prop_hdl.GetDictionary().get_dictionary()),
view_path(NULL),
pre_condition(NULL),
post_condition(NULL),
filters(new DLL(DBVFilter)),
properties(new DLL(DBVProperty)),
sort_orders(new DLL(DBVOrder)),
scope(NULL)
{
  PropertyHandle  *parent;
  gvtxstb(name,view_name_w ? view_name_w : "",ID_SIZE);
  memset(structure_name,' ',sizeof(structure_name));

  if ( prop_hdl.IsValid() )
  {
    if ( parent = prop_hdl.GetParentProperty() )
      property_handle = *parent;
    view_path = strdup(prop_hdl.GetPropertyPath());
  }

}

/******************************************************************************/
/**
\brief i01 - Create view definition
        This  constructor  creates  a  view  definition  in  the  context  of  a
        structure,  when a valid structure name  has been passed (relative view)
        or  as  global  view  outside  any context, when not passing a structure
        name.

\param  dict_hdl - Dictionary handle
\param  viewpath - View path
\param  strnames_w - Structure name
\param  view_name_w - View name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewDef"

                        DBViewDef :: DBViewDef (DictionaryHandle &dict_hdl, char *viewpath, char *strnames_w, char *view_name_w )
                     :   object_handle(NULL),
  property_handle(),
  dictionary(dict_hdl),
  view_path(NULL),
  pre_condition(NULL),
  post_condition(NULL),
  filters(new DLL(DBVFilter)),
  properties(new DLL(DBVProperty)),
  sort_orders(new DLL(DBVOrder)),
  scope(NULL)
{

  Initialize(viewpath,strnames_w,view_name_w);


}

/******************************************************************************/
/**
\brief i02 - Dummy constructor
        The constructor creates an empty view definition.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewDef"

                        DBViewDef :: DBViewDef ( )
                     :   object_handle(NULL),
  property_handle(),
  dictionary(NULL),
  view_path(NULL),
  pre_condition(NULL),
  post_condition(NULL),
  filters(new DLL(DBVFilter)),
  properties(new DLL(DBVProperty)),
  sort_orders(new DLL(DBVOrder)),
  scope(NULL)
{

  memset(name,' ',ID_SIZE);
  memset(structure_name,' ',sizeof(structure_name));


}

/******************************************************************************/
/**
\brief i03


\param  view_name - View name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBViewDef"

                        DBViewDef :: DBViewDef (char *view_name )
                     :   object_handle(NULL),
  property_handle(),
  dictionary(NULL),
  view_path(NULL),
  pre_condition(NULL),
  post_condition(NULL),
  filters(new DLL(DBVFilter)),
  properties(new DLL(DBVProperty)),
  sort_orders(new DLL(DBVOrder)),
  scope(NULL)
{

  gvtxstb(name,view_name ? view_name : "",ID_SIZE);
  memset(structure_name,' ',sizeof(structure_name));


}

/******************************************************************************/
/**
\brief  Initialize - Initialize the view definition


\return term - Termination code

\param  viewpath - View path
\param  strname - Type name
\param  viewname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBViewDef :: Initialize (char *viewpath, char *strname, char *viewname )
{
  logical                 term = NO;
BEGINSEQ
  SetViewName(viewname);
  SetStructureName(strname);
  if ( SetViewPath(viewpath) )                       ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPostCondition - Defining condition for post-selection
        Post-selection  are defined by means of  expressions in the scope of the
        view.  The post-condition  is checked  after calculating view properties
        and may refer to view properties, only.

\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPostCondition"

logical DBViewDef :: SetPostCondition (char *expression )
{
  logical                 term = NO;
  if ( post_condition )
    free(post_condition);
  post_condition = NULL;
  
  if ( expression )
    post_condition = strdup(expression);
  return(term);
}

/******************************************************************************/
/**
\brief  SetPreCondition - Defining condition for pre-selection
        Pre-selection  are defined by  means of expressions  in the scope of the
        view  base.  The  pre-condition  is  checked  before  calculating  view 
        properties and must not refer to those.

\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPreCondition"

logical DBViewDef :: SetPreCondition (char *expression )
{
  logical                 term = NO;
  if ( pre_condition )
    free(pre_condition);
  pre_condition = NULL;
  
  if ( expression )
    pre_condition = strdup(expression);
  return(term);
}

/******************************************************************************/
/**
\brief  SetStructureName - 



\param  strname - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructureName"

void DBViewDef :: SetStructureName (char *strname )
{

  gvtxstb(structure_name,strname ? strname : "",ID_SIZE);


}

/******************************************************************************/
/**
\brief  SetViewName - 



\param  viewname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetViewName"

void DBViewDef :: SetViewName (char *viewname )
{

  gvtxstb(name,viewname ? viewname : "",ID_SIZE);


}

/******************************************************************************/
/**
\brief  SetViewPath - 


\return term - Termination code

\param  viewpath - View path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetViewPath"

logical DBViewDef :: SetViewPath (char *viewpath )
{
  logical                 term = NO;
BEGINSEQ
  if ( viewpath )
  {
    if ( view_path )
      free(view_path);
    view_path = strdup(viewpath);
  }
  else                                               SDBERR(550)


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetViewScope - Set view context
        The  context of a view can be dfined by passing a property handle to the
        view  or by setting  a context identifier  as a local or global instance
        identity  (GUID  or  LOID)  that  refers to the object instance the view
        applies on.


\param  scope_reference - Context idetifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetViewScope"

void DBViewDef :: SetViewScope (char *scope_reference )
{

  scope = strdup(scope_reference);

}

/******************************************************************************/
/**
\brief  Setup - Setup view definition


\return term - Termination code

\param  obhandle - Database Object handle
\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical DBViewDef :: Setup (ACObject *obhandle, PropertyHandle &prop_hdl )
{
  logical   term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( &prop_hdl )
  {
    if ( property_handle.RegisterNode(prop_hdl.get_nodeptr()) )  
                                                     ERROR
      
    object_handle = property_handle.GetObjectHandle().get_obhandle();
  }
  else
    if ( obhandle )
      object_handle = obhandle;
    
  if ( !object_handle )                              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  set_dictionary - 



\param  dicthdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_dictionary"

void DBViewDef :: set_dictionary (DictionaryHandle dicthdl )
{

  dictionary = dicthdl;

}

/******************************************************************************/
/**
\brief  set_object_handle - Set object handle



\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_object_handle"

void DBViewDef :: set_object_handle (ACObject *obhandle )
{

  object_handle = obhandle;

}

/******************************************************************************/
/**
\brief  ~DBViewDef - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBViewDef"

                        DBViewDef :: ~DBViewDef ( )
{
  DBVFilter       *filter;
  DBVProperty     *property;
  DBVOrder        *order;
  if ( view_path )
    free(view_path);
  view_path = NULL;

  SetPreCondition(NULL);
  SetPostCondition(NULL);
  
  while ( filter = filters->RemoveTail() )
    delete filter;
  delete filters;
  filters = NULL;
  
  while ( property = properties->RemoveTail() )
    delete property;
  delete properties;
  properties = NULL;
  
  while ( order = sort_orders->RemoveTail() )
    delete order;
  delete sort_orders;
  sort_orders = NULL;

  if ( scope )
    delete scope;
  scope = NULL;

}


