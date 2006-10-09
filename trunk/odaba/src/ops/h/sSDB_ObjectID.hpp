/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ObjectID

\brief    Database object instance (internal)
          When  accessing  a  database  object  in  the  database,  the external
          database  object  is  provided  in  an internal form, which transforms
          database addresses into access handles (property handle). 
          This  structure  is  equivalent  to  SDB_ObjectExt,  but  defines  the
          internal presentation of a database object instance.

\date     $Date: 2006/03/13 21:30:11,04 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ObjectID_HPP
#define   SDB_ObjectID_HPP

class     SDB_ObjectID;

#ifndef   P_SDB_ExtendRef_HPP
#define   P_SDB_ExtendRef_HPP
#include  <sPI.hpp>
class       SDB_ExtendRef;
PI_dcl     (SDB_ExtendRef)
#endif
#ifndef   P_SDB_Object_HPP
#define   P_SDB_Object_HPP
#include  <sPI.hpp>
class       SDB_Object;
PI_dcl     (SDB_Object)
#endif
#pragma pack(8)

class  SDB_ObjectID
{
protected  :         int32                                        object_id;                                                 // Internal database object number
protected  :         PI(SDB_Object)                               derivates;                                                 // Reserved for future
protected  :         PI(SDB_ExtendRef)                            extends;                                                   // Address of extent list

public     :
                     int32                                        get_object_id() { return(object_id); }
                     PI(SDB_Object)                              &get_derivates() { return(derivates); }
                     PI(SDB_ExtendRef)                           &get_extends() { return(extends); }
};

#pragma pack()
#endif
