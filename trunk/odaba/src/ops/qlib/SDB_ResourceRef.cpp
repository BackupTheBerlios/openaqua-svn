/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ResourceRef

\brief    Resource descriptor
          A  resource descriptor can  be linked to  one metadata resource in the
          repository. 
          Typical  resources are  structures and  property definitions, but also
          under-defined  resources  as  GUI  elements  (forms  and  controls) or
          document templates can be defined as resource or schema element.

\date     $Date: 2006/03/13 21:30:22,54 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_ResourceRef"

#include  <pops7.h>
#include  <sSDB_ResourceRef.hpp>


/******************************************************************************/
/**
\brief  GetResID

\return resid -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResID"

int32 SDB_ResourceRef :: GetResID ( )
{

  return ( this ? __AUTOIDENT : 0  );


}


