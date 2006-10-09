/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSPropPath

\brief    ODS Property path


\date     $Date: 2006/03/13 21:33:58,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSPropPath_HPP
#define   ODSPropPath_HPP

class     ODSPropPath;

#include  <cODSPropertyType.h>
#include  <sODSPropPath.hpp>
class  ODSPropPath
{
protected  :         char                                        *path;                                                      // Property path
protected  :         char                                        *struct_name;                                               //
protected  :         char                                        *order;                                                     //
protected  :         char                                        *filter;                                                    
protected  :         PIACC                                        acc_mode;                                                  // Access mode
protected  :         ODSPropertyType                              type;                                                      // Type of property handle
protected  :         logical                                      collection;                                                // Collection option
protected  :         logical                                      selection;                                                 

public     :
                     char                                        *get_path() { return(path); }
                     char                                        *get_struct_name() { return(struct_name); }
                     char                                        *get_order() { return(order); }
                     char                                        *get_filter() { return(filter); }
                     PIACC                                       &get_acc_mode() { return(acc_mode); }
                     ODSPropertyType                              get_type() { return(type); }
                     logical                                      get_collection() { return(collection); }
                     logical                                      get_selection() { return(selection); }
public     :                                     char *GetOrder ( );
public     :                                     logical IsReadOnly ( );
public     :                                     logical IsUndefined ( );
public     :         OGUI7ImpExp                                         ODSPropPath ( );
public     :         OGUI7ImpExp                                         ODSPropPath (char *prop_path, ODSPropertyType prop_type=PT_undefined );
public     :         OGUI7ImpExp                                         ODSPropPath (const ODSPropPath &rcODSPropPath );
public     :         OGUI7ImpExp                 ODSPropPath &Path ( );
public     :         OGUI7ImpExp                 void ResetPath ( );
public     :         OGUI7ImpExp                 void SetAccessMode (PIACC accmode );
public     :         OGUI7ImpExp                 void SetCollection (logical is_collection );
public     :                                     void SetFilter (char *expression, logical enable_opt );
public     :         OGUI7ImpExp                 logical SetOrder (char *sort_index_name );
public     :         OGUI7ImpExp                 void SetPath (char *prop_path, ODSPropertyType prop_type=PT_undefined );
public     :         OGUI7ImpExp                 void SetPath (const ODSPropPath &rcODSPropPath );
public     :         OGUI7ImpExp                 void SetPath (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type=PT_undefined, PIACC accmode_w=PI_Update );
public     :                                     void SetStructure (char *strnames );
public     :                                     void SetType (ODSPropertyType prop_type=PT_undefined );
public     :         OGUI7ImpExp                 logical operator== (ODSPropPath &rODSPropPath );
public     :         OGUI7ImpExp                                         ~ODSPropPath ( );
};

#endif
