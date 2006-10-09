/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Structure

\brief    Structure definition
          A  structure  represents  a  complex  view to a given object type. The
          structure  provides  usually  a  subset  of the characteristics of the
          object  type  considered.  A  structure represents the structural part
          for  an object type, while the functional  part is defined in the more
          specific  class  definition.  An  ODABA structure definition contains,
          however,  also dynamic model elements,  which allow defining reactions
          on system or user-defined events. 
          The  structure properties are defined  as properties of four different
          categories:    base    structures,    attributes,    references    and
          relationships.  Other members defined on the structure level are keys.
          A  structure may define  any number of  keys based on attribute values
          of the structure. 
          Structures  of different types can be defined depending on the purpose
          of  use.  Usually,  structures  are  user-defined  types.  Internally,
          however,  key  structures  are  created  from  key  definitions  for a
          structure.  System structures refer  to structure definitions provided
          by  ODABA.  View  structures  are structures, which are implemented as
          views. 
          One  may  refer  to  structures  as type of different sort of members.
          Before  being able to  store instances for  a structure, the structure
          itself  and all  types referenced  by its  members must be checked and
          free  from errors.  In order  to store  instances, the structure state
          must be ready.

\date     $Date: 2006/05/11 16:12:39,00 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Structure_HPP
#define   SDB_Structure_HPP

class     SDB_Structure;

#ifndef   P_CAU_Action_HPP
#define   P_CAU_Action_HPP
#include  <sPI.hpp>
class       CAU_Action;
PI_dcl     (CAU_Action)
#endif
#ifndef   P_CAU_GlobalEvent_HPP
#define   P_CAU_GlobalEvent_HPP
#include  <sPI.hpp>
class       CAU_GlobalEvent;
PI_dcl     (CAU_GlobalEvent)
#endif
#ifndef   P_ODC_ImpClass_HPP
#define   P_ODC_ImpClass_HPP
#include  <sPI.hpp>
class       ODC_ImpClass;
PI_dcl     (ODC_ImpClass)
#endif
#ifndef   P_ODS_Class_HPP
#define   P_ODS_Class_HPP
#include  <sPI.hpp>
class       ODS_Class;
PI_dcl     (ODS_Class)
#endif
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
#ifndef   P_SDB_CodeSet_HPP
#define   P_SDB_CodeSet_HPP
#include  <sPI.hpp>
class       SDB_CodeSet;
PI_dcl     (SDB_CodeSet)
#endif
#ifndef   P_SDB_Extend_HPP
#define   P_SDB_Extend_HPP
#include  <sPI.hpp>
class       SDB_Extend;
PI_dcl     (SDB_Extend)
#endif
#ifndef   P_SDB_GenType_HPP
#define   P_SDB_GenType_HPP
#include  <sPI.hpp>
class       SDB_GenType;
PI_dcl     (SDB_GenType)
#endif
#ifndef   P_SDB_Key_HPP
#define   P_SDB_Key_HPP
#include  <sPI.hpp>
class       SDB_Key;
PI_dcl     (SDB_Key)
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
#ifndef   P_SDB_Property_HPP
#define   P_SDB_Property_HPP
#include  <sPI.hpp>
class       SDB_Property;
PI_dcl     (SDB_Property)
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
#ifndef   P_SDB_Resource_HPP
#define   P_SDB_Resource_HPP
#include  <sPI.hpp>
class       SDB_Resource;
PI_dcl     (SDB_Resource)
#endif
#ifndef   P_SDB_ResourceRef_HPP
#define   P_SDB_ResourceRef_HPP
#include  <sPI.hpp>
class       SDB_ResourceRef;
PI_dcl     (SDB_ResourceRef)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#ifndef   P_SDB_Type_HPP
#define   P_SDB_Type_HPP
#include  <sPI.hpp>
class       SDB_Type;
PI_dcl     (SDB_Type)
#endif
#ifndef   P_SDB_View_HPP
#define   P_SDB_View_HPP
#include  <sPI.hpp>
class       SDB_View;
PI_dcl     (SDB_View)
#endif
#ifndef   P_k40_HPP
#define   P_k40_HPP
#include  <sPI.hpp>
class       k40;
PI_dcl     (k40)
#endif
class     BNFData;
class     DBStructDef;
class     SDB_Member;
#include  <cSDB_ST.h>
#include  <cStructModLevel.h>
#include  <cTYP_TYPES.h>
#include  <sCAU_Causality.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_NameSpace.hpp>
#include  <sSDB_Type.hpp>
#pragma pack(8)

class  SDB_Structure :public SDB_NameSpace,
public CAU_Causality
{
protected  :         int32                                        res_id;                                                    // Resource identifier
protected  :         SDB_ST                                       smcestyp;                                                  // Structure type
protected  :         char                                         smceiksm[40];                                              // Ident key for structure
protected  :         logical                                      modified;                                                  // Structure definition has been modified
protected  :         logical                                      checked;                                                   // Structure definition is checked
protected  :         logical                                      ready;                                                     // Structure definition ready for use
protected  :         uint8                                        version;                                                   // Structure version
protected  :         logical                                      local;                                                     // Locally used structure
protected  :         logical                                      vf_opt;                                                    // Virtual function option
protected  :         logical                                      versioning;                                                // Reserved
protected  :         int8                                         allignment;                                                // Reserved
protected  :         logical                                      compress;                                                  // Compress structure instance
protected  :         logical                                      global_identity;                                           // Reserved
protected  :         logical                                      abstract_type;                                             // Abstract data type
protected  :         char                                         reserved[10];                                              // Compress structure instance
protected  :         int32                                        last_key_num;                                              // Reserved
protected  :         PI(k40)                                      synonyms;                                                  
protected  :         PI(SDB_NameSpace)                            name_space;                                                // Structure attributes
protected  :         PI(SDB_Member)                               members;                                                   
protected  :         PI(SDB_BaseStruct)                           base_descr;                                                
protected  :         PI(SDB_Attribute)                            attribute_descr;                                           
protected  :         PI(SDB_Reference)                            reference_descr;                                           
protected  :         PI(SDB_Relationship)                         relationship_descr;                                        
protected  :         PI(SDB_Attribute)                            smcepdde;                                                  
protected  :         PI(SDB_Reference)                            smcepref;                                                  // Reference definitions
protected  :         PI(SDB_Key)                                  smcepsmc;                                                  // Key definitions
protected  :         PI(SDB_BaseStruct)                           smcebase;                                                  // Base structures
protected  :         PI(SDB_Relationship)                         smcershp;                                                  // Relationship definitions
protected  :         PI(SDB_ODABA_Str)                            smceodaba;                                                 // Persistent structure
protected  :         PI(SDB_Structure)                            smceclas;                                                  // Class definition
protected  :         PI(SDB_Structure)                            view;                                                      
protected  :         PI(SDB_GenType)                              generic_type;                                              
protected  :         PI(SDB_ResourceRef)                          ctx_ressource;                                             // Resource reference

public     :
                     int32                                        get_res_id() { return(res_id); }
                     SDB_ST                                       get_smcestyp() { return(smcestyp); }
                     char                                        *get_smceiksm() { return(smceiksm); }
                     logical                                      get_modified() { return(modified); }
                     logical                                      get_checked() { return(checked); }
                     logical                                      get_ready() { return(ready); }
                     uint8                                        get_version() { return(version); }
                     logical                                      get_local() { return(local); }
                     logical                                      get_vf_opt() { return(vf_opt); }
                     logical                                      get_versioning() { return(versioning); }
                     int8                                         get_allignment() { return(allignment); }
                     logical                                      get_compress() { return(compress); }
                     logical                                      get_global_identity() { return(global_identity); }
                     logical                                      get_abstract_type() { return(abstract_type); }
                     char                                        *get_reserved() { return(reserved); }
                     int32                                        get_last_key_num() { return(last_key_num); }
                     PI(k40)                                     &get_synonyms() { return(synonyms); }
                     PI(SDB_NameSpace)                           &get_name_space() { return(name_space); }
                     PI(SDB_Member)                              &get_members() { return(members); }
                     PI(SDB_BaseStruct)                          &get_base_descr() { return(base_descr); }
                     PI(SDB_Attribute)                           &get_attribute_descr() { return(attribute_descr); }
                     PI(SDB_Reference)                           &get_reference_descr() { return(reference_descr); }
                     PI(SDB_Relationship)                        &get_relationship_descr() { return(relationship_descr); }
                     PI(SDB_Attribute)                           &get_smcepdde() { return(smcepdde); }
                     PI(SDB_Reference)                           &get_smcepref() { return(smcepref); }
                     PI(SDB_Key)                                 &get_smcepsmc() { return(smcepsmc); }
                     PI(SDB_BaseStruct)                          &get_smcebase() { return(smcebase); }
                     PI(SDB_Relationship)                        &get_smcershp() { return(smcershp); }
                     PI(SDB_ODABA_Str)                           &get_smceodaba() { return(smceodaba); }
                     PI(SDB_Structure)                           &get_smceclas() { return(smceclas); }
                     PI(SDB_Structure)                           &get_view() { return(view); }
                     PI(SDB_GenType)                             &get_generic_type() { return(generic_type); }
                     PI(SDB_ResourceRef)                         &get_ctx_ressource() { return(ctx_ressource); }
public     :                                        char *CheckExtentPath (char *property_path );
public     :                                        SDB_Member *CheckMember (BNFData *bdata );
public     :                                        char *CheckPropertyPath (char *property_path );
public     :                  OPSImpExp             logical Check_Member (char *member_names );
public     :                  OPSImpExp             logical Check_MemberList (char *member_names, char *type_names );
public     :                  OPSImpExp             PI(CAU_Action) *GetAction (char *action_names, PI(SDB_Structure) *dbs_ptr );
public     :                  OPSImpExp             PI(SDB_Property) *GetMember (char *member_names, PI(SDB_Structure) *dbs_ptr );
public     :                  OPSImpExp             PI(SDB_Property) *GetMemberPath (char *prop_path, PI(SDB_Structure) *dbs_ptr );
public     :                  OPSImpExp             int32 GetResID ( );
public     :                                        SDB_Member *GetSDBMember (char *names );
public     :                  OPSImpExp             logical Initialize (char *strnames, DatabaseHandle &dbhandle, logical create_tid=YES );
public     :                                        logical IsBasedOn (PI(SDB_Structure) &dbs_pi, char *strnames );
public     :                  OPSImpExp             logical Reset ( );
public     :                                             SDB_Structure ( );
public     :                  OPSImpExp             logical SetCreate ( );
public     :                  OPSImpExp             logical SetModified (logical check, StructModLevel mod_level );
public     :                  OPSImpExp             logical SetOwning ( );
public     :                  OPSImpExp             logical SetReady ( );
public     :                  OPSImpExp             logical SetVersion (PI(SDB_Structure) dbs_dpi );
public     :                  OPSImpExp             void set_checked (logical checkopt );
public     :                  OPSImpExp             logical set_modified (logical mod_opt );
public     :                  OPSImpExp             void set_ready (logical readyopt );
public     :                  OPSImpExp             void set_smcestyp (SDB_ST str_type );
public     :                                        void set_typetype (TYP_TYPES metatype );
public     :                                        void set_version (uint16 version_nr=CUR_VERSION );
};

#pragma pack()
#endif
