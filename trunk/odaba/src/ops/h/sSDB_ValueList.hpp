/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/07/05 14:20:22,01 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ValueList_HPP
#define   SDB_ValueList_HPP

class     SDB_ValueList;

#ifndef   P_SDB_NameSpace_HPP
#define   P_SDB_NameSpace_HPP
#include  <sPI.hpp>
class       SDB_NameSpace;
PI_dcl     (SDB_NameSpace)
#endif
#ifndef   P_SDB_TopValue_HPP
#define   P_SDB_TopValue_HPP
#include  <sPI.hpp>
class       SDB_TopValue;
PI_dcl     (SDB_TopValue)
#endif
#ifndef   P_SDB_Value_HPP
#define   P_SDB_Value_HPP
#include  <sPI.hpp>
class       SDB_Value;
PI_dcl     (SDB_Value)
#endif
#ifndef   P_SDB_ValueListRef_HPP
#define   P_SDB_ValueListRef_HPP
#include  <sPI.hpp>
class       SDB_ValueListRef;
PI_dcl     (SDB_ValueListRef)
#endif
#include  <sSDB_Resource.hpp>
#include  <sSDB_Type.hpp>
#pragma pack(8)

class  SDB_ValueList :public SDB_Type
{
protected  :         char                                         scope[128];                                                // 
protected  :         char                                         base_type[40];                                             // 
protected  :         PI(mem)                                      expression;                                                // 
protected  :         PI(SDB_TopValue)                             values;                                                    // List of values
protected  :         PI(SDB_NameSpace)                            name_space;                                                // 

public     :
                     char                                        *get_scope() { return(scope); }
                     char                                        *get_base_type() { return(base_type); }
                     PI(mem)                                     &get_expression() { return(expression); }
                     PI(SDB_TopValue)                            &get_values() { return(values); }
                     PI(SDB_NameSpace)                           &get_name_space() { return(name_space); }
public     :                  OPSImpExp             char *GetDocFileName (PropertyHandle *prophdl, NString &nstring );
};

#pragma pack()
#endif
