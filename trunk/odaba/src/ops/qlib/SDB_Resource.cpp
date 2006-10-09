/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Resource

\brief    Metadata resource
          All  relevant metadata objects inherit directly or indirectly from the
          metadata  resource.  Typically,  structure definitions (SDB_Structure)
          and  member  definitions  (SDB_Member)  inherit  from  the  metadata 
          resource.

\date     $Date: 2006/03/13 21:30:22,46 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Resource"

#include  <pops7.h>
#ifndef   P_SDB_TypeRef_HPP
#define   P_SDB_TypeRef_HPP
#include  <sPI.hpp>
class       SDB_TypeRef;
PI_dcl     (SDB_TypeRef)
#endif
#include  <sSDB_Resource.hpp>


/******************************************************************************/
/**
\brief  SDB_Resource - Resource definition
        Each  defined data  type is  a metadata  resource. The resource contains
        the  resource name and a link to the topic describing the concept of the
        type.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Resource"

                        SDB_Resource :: SDB_Resource ( )
                     : __OBJECT ()
{

  memset(sys_ident,' ',sizeof(sys_ident));


}

/******************************************************************************/
/**
\brief  operator= - 


\return resource

\param  resource_refc -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

SDB_Resource &SDB_Resource :: operator= (const SDB_Resource &resource_refc )
{

  __LAST_UPDATE = resource_refc.__LAST_UPDATE;
  memcpy(&__GUID,&resource_refc.__GUID,sizeof(__GUID));
  memcpy(sys_ident,resource_refc.sys_ident,sizeof(sys_ident));

  return(*this);
}

/******************************************************************************/
/**
\brief  ~SDB_Resource - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Resource"

                        SDB_Resource :: ~SDB_Resource ( )
{



}


