/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewDef

\brief    Internal view defintion
          The  internal view definition defines the view base, sort orders, view
          properties,   filter,   post-   and   pre   conditions.  Internal view
          defintiions  are  either  defined  in  an  application  programm or by
          reading view definitions from the dictionary.

\date     $Date: 2006/03/12 19:13:05,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewDef_HPP
#define   DBViewDef_HPP

class     DBViewDef;

#include  <sDLL.h>
class     DBVFilter;
#include  <sDLL.h>
class     DBVOrder;
#include  <sDLL.h>
class     DBVProperty;
class     ACObject;
class     Dictionary;
#include  <cADT_Types.h>
#include  <sDBViewDef.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  DBViewDef
{
protected  :         char                                         name[40];                                                  // Name of view
protected  :         ACObject                                    *object_handle;                                             
protected  :         PropertyHandle                               property_handle;                                           // Property handle for simple view
protected  :         char                                        *scope;                                                     
protected  :         DictionaryHandle                             dictionary;                                                // Dictionary pointer
protected  :         char                                         structure_name[40];                                        // Structure name for structure based view
protected  :         char                                        *view_path;                                                 // View path
protected  :         char                                        *pre_condition;                                             // Pre condition for the view
protected  :         char                                        *post_condition;                                            // Post condition for the view
protected  :         DLL(DBVFilter)                              *filters;                                                   // List of defined filters
protected  :         DLL(DBVProperty)                            *properties;                                                // Properties for the view
protected  :         DLL(DBVOrder)                               *sort_orders;                                               // Defined sort orders

public     :
                     char                                        *get_name() { return(name); }
                     ACObject                                    *get_object_handle() { return(object_handle); }
                     PropertyHandle                              &get_property_handle() { return(property_handle); }
                     char                                        *get_scope() { return(scope); }
                     DictionaryHandle                            &get_dictionary() { return(dictionary); }
                     char                                        *get_structure_name() { return(structure_name); }
                     char                                        *get_view_path() { return(view_path); }
                     char                                        *get_pre_condition() { return(pre_condition); }
                     char                                        *get_post_condition() { return(post_condition); }
                     DLL(DBVFilter)                              *get_filters() { return(filters); }
                     DLL(DBVProperty)                            *get_properties() { return(properties); }
                     DLL(DBVOrder)                               *get_sort_orders() { return(sort_orders); }
public     :         opa7ImpExp                  logical AddFilter (char *prop_path, char *expression );
public     :         opa7ImpExp                  logical AddOrder (char *prop_path, char *sort_key_name );
public     :         opa7ImpExp                  logical AddProperty (char *prop_names, char *prop_source, ADT_Types source_type=ADT_PropertyPath, int32 size_w=UNDEF );
public     :         opa7ImpExp                  logical AddProperty (char *prop_names, DBViewDef &view_def, ADT_Types source_type=ADT_PropertyPath );
public     :         opa7ImpExp                                          DBViewDef (PropertyHandle &prop_hdl, char *view_name_w=NULL );
public     :         opa7ImpExp                                          DBViewDef (DictionaryHandle &dict_hdl, char *viewpath, char *strnames_w=NULL, char *view_name_w=NULL );
public     :         opa7ImpExp                                          DBViewDef ( );
public     :         opa7ImpExp                                          DBViewDef (char *view_name );
public     :                                     logical Initialize (char *viewpath, char *strname, char *viewname );
public     :         opa7ImpExp                  logical SetPostCondition (char *expression );
public     :         opa7ImpExp                  logical SetPreCondition (char *expression );
public     :         opa7ImpExp                  void SetStructureName (char *strname );
public     :         opa7ImpExp                  void SetViewName (char *viewname );
public     :         opa7ImpExp                  logical SetViewPath (char *viewpath );
public     :         opa7ImpExp                  void SetViewScope (char *scope_reference );
public     :                                     logical Setup (ACObject *obhandle, PropertyHandle &prop_hdl );
public     :                                     void set_dictionary (DictionaryHandle dicthdl );
public     :                                     void set_object_handle (ACObject *obhandle );
public     :         opa7ImpExp                                          ~DBViewDef ( );
};

#pragma pack()
#endif
