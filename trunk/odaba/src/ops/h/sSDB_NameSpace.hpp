/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_NameSpace

\brief    Name space
          A  name space is an abstract  data type. Especially, each complex type
          definition  is a name space, but not each name space is a complex data
          type.

\date     $Date: 2006/03/13 21:30:10,45 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_NameSpace_HPP
#define   SDB_NameSpace_HPP

class     SDB_NameSpace;

#ifndef   P_SDB_Attribute_HPP
#define   P_SDB_Attribute_HPP
#include  <sPI.hpp>
class       SDB_Attribute;
PI_dcl     (SDB_Attribute)
#endif
#ifndef   P_SDB_BaseStruct_HPP
#define   P_SDB_BaseStruct_HPP
#include  <sPI.hpp>
class       SDB_BaseStruct;
PI_dcl     (SDB_BaseStruct)
#endif
#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
#ifndef   P_SDB_NameSpace_HPP
#define   P_SDB_NameSpace_HPP
#include  <sPI.hpp>
class       SDB_NameSpace;
PI_dcl     (SDB_NameSpace)
#endif
#ifndef   P_SDB_ODABA_Str_HPP
#define   P_SDB_ODABA_Str_HPP
#include  <sPI.hpp>
class       SDB_ODABA_Str;
PI_dcl     (SDB_ODABA_Str)
#endif
#ifndef   P_SDB_Reference_HPP
#define   P_SDB_Reference_HPP
#include  <sPI.hpp>
class       SDB_Reference;
PI_dcl     (SDB_Reference)
#endif
#ifndef   P_SDB_Relationship_HPP
#define   P_SDB_Relationship_HPP
#include  <sPI.hpp>
class       SDB_Relationship;
PI_dcl     (SDB_Relationship)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#ifndef   P_SDB_TypeDef_HPP
#define   P_SDB_TypeDef_HPP
#include  <sPI.hpp>
class       SDB_TypeDef;
PI_dcl     (SDB_TypeDef)
#endif
#ifndef   P_SDB_ValueList_HPP
#define   P_SDB_ValueList_HPP
#include  <sPI.hpp>
class       SDB_ValueList;
PI_dcl     (SDB_ValueList)
#endif
#include  <sSDB_Type.hpp>
#pragma pack(8)

class  SDB_NameSpace :public SDB_Type
{
protected  :         logical                                      active ATTR_ALIGN(4);                                      // Active name space
protected  :         char                                         reserved[81];                                              //
protected  :         PI(mem)                                      reserved1;                                                 //
protected  :         PI(mem)                                      reserved2;                                                 //
protected  :         PI(mem)                                      reserved3;                                                 //
protected  :         PI(mem)                                      reserved4;                                                 //
protected  :         PI(SDB_NameSpace)                            namespace_ref;                                             // Value lists
protected  :         PI(SDB_NameSpace)                            name_spaces;                                               // Subordinated name spaces
protected  :         PI(SDB_NameSpace)                            parent;                                                    // Parent name space
protected  :         PI(SDB_NameSpace)                            synonyms;                                                  //
protected  :         PI(SDB_Structure)                            structures;                                                //
protected  :         PI(SDB_ODABA_Str)                            pstructures;                                               
protected  :         PI(SDB_ValueList)                            value_lists;                                               
protected  :         PI(SDB_TypeDef)                              type_defs;                                                 
protected  :         PI(SDB_Reference)                            extents;                                                   //
protected  :         PI(SDB_NameSpace)                            origin;                                                    //

public     :
                     logical                                      get_active() { return(active); }
                     char                                        *get_reserved() { return(reserved); }
                     PI(mem)                                     &get_reserved1() { return(reserved1); }
                     PI(mem)                                     &get_reserved2() { return(reserved2); }
                     PI(mem)                                     &get_reserved3() { return(reserved3); }
                     PI(mem)                                     &get_reserved4() { return(reserved4); }
                     PI(SDB_NameSpace)                           &get_namespace_ref() { return(namespace_ref); }
                     PI(SDB_NameSpace)                           &get_name_spaces() { return(name_spaces); }
                     PI(SDB_NameSpace)                           &get_parent() { return(parent); }
                     PI(SDB_NameSpace)                           &get_synonyms() { return(synonyms); }
                     PI(SDB_Structure)                           &get_structures() { return(structures); }
                     PI(SDB_ODABA_Str)                           &get_pstructures() { return(pstructures); }
                     PI(SDB_ValueList)                           &get_value_lists() { return(value_lists); }
                     PI(SDB_TypeDef)                             &get_type_defs() { return(type_defs); }
                     PI(SDB_Reference)                           &get_extents() { return(extents); }
                     PI(SDB_NameSpace)                           &get_origin() { return(origin); }
};

#pragma pack()
#endif
