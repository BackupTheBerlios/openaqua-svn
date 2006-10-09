/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ResourceRef

\brief    Resource descriptor
          A  resource descriptor can  be linked to  one metadata resource in the
          repository. 
          Typical  resources are  structures and  property definitions, but also
          under-defined  resources  as  GUI  elements  (forms  and  controls) or
          document templates can be defined as resource or schema element.

\date     $Date: 2006/03/13 21:30:12,28 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ResourceRef_HPP
#define   SDB_ResourceRef_HPP

class     SDB_ResourceRef;

#ifndef   P_DSC_Topic_HPP
#define   P_DSC_Topic_HPP
#include  <sPI.hpp>
class       DSC_Topic;
PI_dcl     (DSC_Topic)
#endif
#ifndef   P_SDB_Resource_HPP
#define   P_SDB_Resource_HPP
#include  <sPI.hpp>
class       SDB_Resource;
PI_dcl     (SDB_Resource)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#include  <cCTX_Types.h>
#pragma pack(8)

class  SDB_ResourceRef
{
protected  :         int32                                        __AUTOIDENT;                                               // Auto-numbering of resource references
protected  :         CTX_Types                                    type;                                                      // Context type of resource
protected  :         int32                                        local_id;                                                  // Resource identifier
protected  :         PI(SDB_Structure)                            context_class;                                             // Associated Context Class
protected  :         PI(SDB_Resource)                             type_ref;                                                  // Refers to type specific metadata resource
protected  :         PI(DSC_Topic)                                description;                                               // Resource description

public     :
                     int32                                        get___AUTOIDENT() { return(__AUTOIDENT); }
                     CTX_Types                                    get_type() { return(type); }
                     int32                                        get_local_id() { return(local_id); }
                     PI(SDB_Structure)                           &get_context_class() { return(context_class); }
                     PI(SDB_Resource)                            &get_type_ref() { return(type_ref); }
                     PI(DSC_Topic)                               &get_description() { return(description); }
public     :         OPS7ImpExp                  int32 GetResID ( );
};

#pragma pack()
#endif
