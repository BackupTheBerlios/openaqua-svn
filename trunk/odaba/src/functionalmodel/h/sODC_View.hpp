/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_View

\brief    View definition
          A  view definition allows defining the  elements of a database view. A
          view  is  considered  as  method  of  a structure (or a combination of
          structures),  which is called the  structural (or intensional) base of
          the  view. The structural base is defined  in the 'from' clause of the
          view.
          The  result of a view  can be stored as  persistent view by making the
          view  persistent. This allows  defining one or  more ODABA extents for
          storing  the view. Persistent views are not updated automatically, but
          must be updated by the user.
          The  view  structure  is  defined  by  the  properties (attributes and
          references)  in the  view. Defining  relationships makes sense in case
          of  persistent views, only.  All properties defined  for a view should
          have  a  constraint,  which  defines  the  expression  or path for the
          property.  Properties, which do not  have a constraint definition, can
          be  evaluated in an appropriate context class or the view structure or
          the property. 
          You  may  define  views  based  on  views  or properties based on view
          structures.  When a property is defined with a view structure as type,
          the  view applies on the source for  the property, which is defined in
          the  constraint.  When  applying  a  view to a property, you may refer
          directly  to a source property (or  property path or expression) or to
          a local view extent. 
          Aggregated  view  can  be  defined  by  using  the  'group_by' clause.
          Aggregated  views always contain a 'value' and a 'partition' property.
          Other  properties can  be defined  by means of aggregation expressions
          for the 'partition' collection.
          You  can define one or  more keys for the  view, which consist of view
          attributes.  Those  keys  can  be  used  for  creating  indexes  for 
          persistent  views. Aggregated views do  always have an identifying key
          '__ident_key'.
          Views  can  be  used  as  reading or updating views. You can, however,
          update  only  those  properties,  which  are connected with its source
          directly  via property paths. This is possible also via several steps,
          i.e.  when  defining  views  on  views.  As  soon,  as  at  least  one
          expression  is  defined  on  the  way  to  the  database  source for a
          property, this property cannot be updated.

\date     $Date: 2006/03/13 21:30:34,75 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_View_HPP
#define   ODC_View_HPP

class     ODC_View;

#ifndef   P_ODC_Module_HPP
#define   P_ODC_Module_HPP
#include  <sPI.hpp>
class       ODC_Module;
PI_dcl     (ODC_Module)
#endif
#ifndef   P_ODC_ViewPath_HPP
#define   P_ODC_ViewPath_HPP
#include  <sPI.hpp>
class       ODC_ViewPath;
PI_dcl     (ODC_ViewPath)
#endif
#ifndef   P_SDB_ValueList_HPP
#define   P_SDB_ValueList_HPP
#include  <sPI.hpp>
class       SDB_ValueList;
PI_dcl     (SDB_ValueList)
#endif
#include  <sSDB_Structure.hpp>
#pragma pack(8)

class  ODC_View :public SDB_Structure
{
protected  :         PI(ODC_ViewPath)                             from;                                                      // Structural base
protected  :         PI(mem)                                      where;                                                     // Pre-condition
protected  :         PI(SDB_ValueList)                            group_by;                                                  // Aggregated view
protected  :         PI(mem)                                      having;                                                    // Post condition
protected  :         PI(ODC_Module)                               module;                                                    

public     :
                     PI(ODC_ViewPath)                            &get_from() { return(from); }
                     PI(mem)                                     &get_where() { return(where); }
                     PI(SDB_ValueList)                           &get_group_by() { return(group_by); }
                     PI(mem)                                     &get_having() { return(having); }
                     PI(ODC_Module)                              &get_module() { return(module); }
public     :                                     char *GetCollection ( );
public     :                                     char GetExpression ( );
public     :                                     char *GetPostCondition ( );
public     :                                     char *GetPreCondition ( );
public     :                                     char GetViewPath ( );
public     :                                                             ODC_View ( );
public     :                                     logical SetProperties (char view_def );
};

#pragma pack()
#endif
