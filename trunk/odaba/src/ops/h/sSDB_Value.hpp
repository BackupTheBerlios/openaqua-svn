/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Value

\brief    Value in a value list
          A  value in a value  list defines the name  and numerical code for the
          value  in an enumeratel  value list. It  may also contain constraints,
          which define the condition for the value. 
          Each  value  can  be  subdivided  into sub-categories (sub-classes) in
          different ways bay any number of value lists.

\date     $Date: 2006/03/13 21:30:13,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Value_HPP
#define   SDB_Value_HPP

class     SDB_Value;

#ifndef   P_SDB_Value_HPP
#define   P_SDB_Value_HPP
#include  <sPI.hpp>
class       SDB_Value;
PI_dcl     (SDB_Value)
#endif
#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  SDB_Value :public SDB_Resource
{
protected  :         int32                                        __AUTOIDENT ATTR_ALIGN(4);                                 // Numerical value
protected  :         char                                         name[40];                                                  //
protected  :         char                                         scope[128];                                                
protected  :         char                                         type[40];                                                  // Data type
protected  :         PI(mem)                                      condition;                                                 // Value condition
protected  :         PI(SDB_Value)                                sub_values;                                                // Child lists
protected  :         PI(SDB_Value)                                parent;                                                    

public     :
                     int32                                        get___AUTOIDENT() { return(__AUTOIDENT); }
                     char                                        *get_name() { return(name); }
                     char                                        *get_scope() { return(scope); }
                     char                                        *get_type() { return(type); }
                     PI(mem)                                     &get_condition() { return(condition); }
                     PI(SDB_Value)                               &get_sub_values() { return(sub_values); }
                     PI(SDB_Value)                               &get_parent() { return(parent); }
};

#pragma pack()
#endif
