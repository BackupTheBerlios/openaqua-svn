/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/16|13:28:01,81}|(REF)
\class    SDB_Type

\brief    Data types
          Data types are defined as data types of different categories. 
          Structures  of different types can be defined depending on the purpose
          of  use.  Usually,  structures  are  user-defined  types.  Internally,
          however,  key  structures  are  created  from  key  definitions  for a
          structure.  System structures refer  to structure definitions provided
          by  ODABA.  View  structures  are structures, which are implemented as
          views. 
          лллллллл■

\date     $Date: 2006/03/21 16:51:52,03 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Type_HPP
#define   SDB_Type_HPP

class     SDB_Type;

#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
#ifndef   P_SDB_Type_HPP
#define   P_SDB_Type_HPP
#include  <sPI.hpp>
class       SDB_Type;
PI_dcl     (SDB_Type)
#endif
#ifndef   P_SDB_TypeRef_HPP
#define   P_SDB_TypeRef_HPP
#include  <sPI.hpp>
class       SDB_TypeRef;
PI_dcl     (SDB_TypeRef)
#endif
#ifndef   P_SDB_ViewPath_HPP
#define   P_SDB_ViewPath_HPP
#include  <sPI.hpp>
class       SDB_ViewPath;
PI_dcl     (SDB_ViewPath)
#endif
class     smcb;
#include  <cPIREPL.h>
#include  <cSDB_AT.h>
#include  <cTYP_TYPES.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  SDB_Type :public SDB_Resource
{
protected  :         int32                                        namespace_id ATTR_ALIGN(4);                                // Internal name space identifier
protected  :         TYP_TYPES                                    typetype;                                                  // Meta type of the data type
protected  :         int16                                        itype;                                                     // Internal type number
protected  :         SDB_AT                                       access_type;                                               // Access type
protected  :         PI(SDB_Type)                                 impl_ref;                                                  // Type specialization
protected  :         PI(SDB_Member)                               member_ref;                                                // Member reference list
protected  :         PI(SDB_TypeRef)                              typeref_in;                                                //

public     :
                     int32                                        get_namespace_id() { return(namespace_id); }
                     TYP_TYPES                                    get_typetype() { return(typetype); }
                     int16                                        get_itype() { return(itype); }
                     SDB_AT                                       get_access_type() { return(access_type); }
                     PI(SDB_Type)                                &get_impl_ref() { return(impl_ref); }
                     PI(SDB_Member)                              &get_member_ref() { return(member_ref); }
                     PI(SDB_TypeRef)                             &get_typeref_in() { return(typeref_in); }
public     :         OPSImpExp                   logical CheckType (DatabaseHandle &dbhandle, TYP_TYPES typtyp );
public     : static  OPSImpExp                   int16 __cdecl ExistCodeSet (DatabaseHandle &dbhandle, char *datype );
public     : static  OPSImpExp                   int16 __cdecl ExistStructure (DatabaseHandle &dbhandle, char *datype, int16 *pstyp, char *idkeyn );
public     : static                              logical __cdecl GetAlignInfo (char *strname, char *propname, int16 &size_info, int16 &offset_info );
public     : static  OPSImpExp                   logical __cdecl GetTypeInfo (DatabaseHandle &dbhandle, char *datype, int16 *pstyp, int16 *pityp, char *idkeyn );
public     : static  OPSImpExp                   TYP_TYPES __cdecl GetTypeType (DatabaseHandle &dbhandle, char *names );
public     :         OPSImpExp                                           SDB_Type ( );
public     :                                     void SetAccessType (SDB_AT acctype );
public     :         OPSImpExp                   void SetInternType (int16 interntyp );
public     :         OPSImpExp                   void SetType (TYP_TYPES typtyp );
public     :         OPSImpExp                                           ~SDB_Type ( );
};

#pragma pack()
#endif
