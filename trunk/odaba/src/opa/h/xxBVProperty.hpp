/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBVProperty

\brief    Property definition for view


\date     $Date: 2006/03/12 19:13:05,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBVProperty_HPP
#define   DBVProperty_HPP

class     DBVProperty;

class     PropAllocation;
class     node;
#include  <cADT_Types.h>
#include  <sDBViewDef.hpp>
#pragma pack(8)

class  DBVProperty
{
protected  :         char                                         name[40];                                                  // Property name
protected  :         char                                        *source;                                                    // Source definition for property
protected  :         ADT_Types                                    type;                                                      // Source type
protected  :         int32                                        size;                                                      // Maximal size in relevant figures or characters
protected  :         DBViewDef                                   *view_definition;                                           

public     :
                     char                                        *get_name() { return(name); }
                     char                                        *get_source() { return(source); }
                     ADT_Types                                    get_type() { return(type); }
                     int32                                        get_size() { return(size); }
                     DBViewDef                                   *get_view_definition() { return(view_definition); }
public     :                                     PropAllocation *CreateAllocation (node *source_node, node *target_node, char *view_name );
public     :                                                             DBVProperty (char *prop_name, char *source_path, ADT_Types source_type=ADT_PropertyPath, int32 size_w=UNDEF );
public     :                                                             DBVProperty (char *prop_name, DBViewDef &view_def, ADT_Types source_type=ADT_PropertyPath );
public     :                                                             ~DBVProperty ( );
};

#pragma pack()
#endif
