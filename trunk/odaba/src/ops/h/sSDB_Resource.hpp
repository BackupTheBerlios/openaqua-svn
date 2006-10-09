/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Resource

\brief    Metadata resource
          All  relevant metadata objects inherit directly or indirectly from the
          metadata  resource.  Typically,  structure definitions (SDB_Structure)
          and  member  definitions  (SDB_Member)  inherit  from  the  metadata 
          resource.

\date     $Date: 2006/03/13 21:30:12,17 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Resource_HPP
#define   SDB_Resource_HPP

class     SDB_Resource;

#ifndef   P_SDB_ResourceRef_HPP
#define   P_SDB_ResourceRef_HPP
#include  <sPI.hpp>
class       SDB_ResourceRef;
PI_dcl     (SDB_ResourceRef)
#endif
#ifndef   P_SDB_TypeRef_HPP
#define   P_SDB_TypeRef_HPP
#include  <sPI.hpp>
class       SDB_TypeRef;
PI_dcl     (SDB_TypeRef)
#endif
#include  <sSDB_Resource.hpp>
#include  <s__OBJECT.hpp>
#pragma pack(8)

class  SDB_Resource :public __OBJECT
{
protected  :         char                                         sys_ident[40] ATTR_ALIGN(4);                               // Resource name
protected  :         PI(SDB_ResourceRef)                          resource_ref;                                              // Reference to resource descriptor
protected  :         PI(SDB_TypeRef)                              type_references;                                           

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     PI(SDB_ResourceRef)                         &get_resource_ref() { return(resource_ref); }
                     PI(SDB_TypeRef)                             &get_type_references() { return(type_references); }
public     :         OPS7ImpExp                                          SDB_Resource ( );
public     :         OPS7ImpExp                  SDB_Resource &operator= (const SDB_Resource &resource_refc );
public     :         OPS7ImpExp                                          ~SDB_Resource ( );
};

#pragma pack()
#endif
