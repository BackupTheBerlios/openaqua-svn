/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/16|13:28:01,81}|(REF)
\class    SDB_TypeRef

\brief    


\date     $Date: 2006/03/20 19:27:18,45 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_TypeRef_HPP
#define   SDB_TypeRef_HPP

class     SDB_TypeRef;

#ifndef   P_SDB_Resource_HPP
#define   P_SDB_Resource_HPP
#include  <sPI.hpp>
class       SDB_Resource;
PI_dcl     (SDB_Resource)
#endif
#ifndef   P_SDB_Type_HPP
#define   P_SDB_Type_HPP
#include  <sPI.hpp>
class       SDB_Type;
PI_dcl     (SDB_Type)
#endif
#include  <cIncRef_Level.h>
#pragma pack(8)

class  SDB_TypeRef
{
protected  :         char                                         classname[40];                                             
protected  :         char                                         generictype[40];                                           
protected  :         IncRef_Level                                 inc_level;                                                 
protected  :         IncRef_Level                                 code_level;                                                
protected  :         logical                                      generated;                                                 
protected  :         PI(SDB_Resource)                             owner;                                                     //
protected  :         PI(SDB_Type)                                 type_ref;                                                  

public     :
                     char                                        *get_classname() { return(classname); }
                     char                                        *get_generictype() { return(generictype); }
                     IncRef_Level                                 get_inc_level() { return(inc_level); }
                     IncRef_Level                                 get_code_level() { return(code_level); }
                     logical                                      get_generated() { return(generated); }
                     PI(SDB_Resource)                            &get_owner() { return(owner); }
                     PI(SDB_Type)                                &get_type_ref() { return(type_ref); }
};

#pragma pack()
#endif
