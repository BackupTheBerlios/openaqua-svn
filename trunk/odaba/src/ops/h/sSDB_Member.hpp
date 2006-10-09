/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Member

\brief    Structure member
          Structure  or  class  member  are  details  the  structure  definition
          consists   of.   Structure   member   may   appear  in ODABA structure
          definitions  as attributes, reference, relationship or base structure.
          In  ODABA  class  definition  members  appear  also  as  functions  or
          function,  windows  or  documents.  Members  are also used to describe
          function  parameters. In the scope of  a structure or class definition
          member names must be unique.

\date     $Date: 2006/05/15 20:14:14,04 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Member_HPP
#define   SDB_Member_HPP

class     SDB_Member;

#ifndef   P_SDB_CodeSet_HPP
#define   P_SDB_CodeSet_HPP
#include  <sPI.hpp>
class       SDB_CodeSet;
PI_dcl     (SDB_CodeSet)
#endif
#ifndef   P_SDB_NameSpace_HPP
#define   P_SDB_NameSpace_HPP
#include  <sPI.hpp>
class       SDB_NameSpace;
PI_dcl     (SDB_NameSpace)
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
#ifndef   P_SDB_ViewSource_HPP
#define   P_SDB_ViewSource_HPP
#include  <sPI.hpp>
class       SDB_ViewSource;
PI_dcl     (SDB_ViewSource)
#endif
#ifndef   P_k40_HPP
#define   P_k40_HPP
#include  <sPI.hpp>
class       k40;
PI_dcl     (k40)
#endif
class     DBFieldDef;
class     SDB_NameSpace;
class     SDB_Structure;
class     SDB_Type;
#include  <cADT_Types.h>
#include  <cODC_Privilege.h>
#include  <cSDB_RLEV.h>
#include  <cTYP_TYPES.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Resource.hpp>
#include  <sk40.hpp>
#pragma pack(8)

class  SDB_Member :public SDB_Resource
{
protected  :         int32                                        res_id;                                                    // Resource identifier
protected  :         char                                         ddetype[40];                                               // Member type
protected  :         char                                         scope[128];                                                // Scope for type
protected  :         uint32                                       ddesize;                                                   // Size
protected  :         uint32                                       ddedim[5];                                                 // Dimension
protected  :         uint16                                       ddeprec;                                                   // Precision
protected  :         SDB_RLEV                                     reference_level;                                           // Reference type
protected  :         char                                         ddegent[40];                                               // Template types
protected  :         ODC_Privilege                                ddeprv;                                                    // Access privilege
protected  :         logical                                      ddestat;                                                   // Static member
protected  :         logical                                      ddevirt;                                                   // Virtual member
protected  :         char                                         ddeinit[128];                                              // Default value
protected  :         logical                                      clustered_table;                                           // Clustered table
protected  :         logical                                      delete_empty;                                              // Delete instance, when field is empty
protected  :         logical                                      global_identity;                                           // Generate global identity
protected  :         logical                                      empty;                                                     // Allow empty values
protected  :         logical                                      unicode;                                                   // Indicates unicode string
protected  :         logical                                      compress;                                                  // Compress data when being stored
protected  :         char                                         reserved[32];                                              
protected  :         PI(SDB_ViewSource)                           source;                                                    // View Source
protected  :         PI(k40)                                      synonyms;                                                  // Synonyms
protected  :         PI(mem)                                      constraint;                                                // Property Constraint
protected  :         PI(SDB_Structure)                            structure;                                                 
protected  :         PI(SDB_Type)                                 type;                                                      // Member type

public     :
                     int32                                        get_res_id() { return(res_id); }
                     char                                        *get_ddetype() { return(ddetype); }
                     char                                        *get_scope() { return(scope); }
                     uint32                                       get_ddesize() { return(ddesize); }
                     uint16                                       get_ddeprec() { return(ddeprec); }
                     SDB_RLEV                                     get_reference_level() { return(reference_level); }
                     char                                        *get_ddegent() { return(ddegent); }
                     ODC_Privilege                                get_ddeprv() { return(ddeprv); }
                     logical                                      get_ddestat() { return(ddestat); }
                     logical                                      get_ddevirt() { return(ddevirt); }
                     char                                        *get_ddeinit() { return(ddeinit); }
                     logical                                      get_clustered_table() { return(clustered_table); }
                     logical                                      get_delete_empty() { return(delete_empty); }
                     logical                                      get_global_identity() { return(global_identity); }
                     logical                                      get_empty() { return(empty); }
                     logical                                      get_unicode() { return(unicode); }
                     logical                                      get_compress() { return(compress); }
                     char                                        *get_reserved() { return(reserved); }
                     PI(SDB_ViewSource)                          &get_source() { return(source); }
                     PI(k40)                                     &get_synonyms() { return(synonyms); }
                     PI(mem)                                     &get_constraint() { return(constraint); }
                     PI(SDB_Structure)                           &get_structure() { return(structure); }
                     PI(SDB_Type)                                &get_type() { return(type); }
public     :                  OPSImpExp             char *BitSize (PropertyHandle *prophdl, NString &nstring );
public     :                  OPSImpExp             char *CharSize (PropertyHandle *prophdl, NString &nstring );
public     :                  OPSImpExp             FieldDef *CreateFieldDef (FieldDef *fieldptr );
public     :                  OPSImpExp             char *DataTypeCOMString (DatabaseHandle &dbhandle, char *string, logical output_parm );
public     :                  OPSImpExp             char *DataTypeCString (uint16 len );
public     :                  OPSImpExp             char *DataTypeCString (DatabaseHandle &dbhandle, char *string, uint16 len );
public     :                  OPSImpExp             logical Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes );
public     :                  OPSImpExp             char *GetCOMType (int16 itype, char *typestring );
public     :                  OPSImpExp             char *GetCOMType (char *typstr, char *typestring );
public     :                  OPSImpExp             logical GetCOMTypeString (DatabaseHandle &dbhandle, char *typstr, int16 *lchange, logical keyfield=NO );
public     :                  OPSImpExp             logical GetCTypeString (DatabaseHandle &dbhandle, char *typstr, int16 *lchange, logical keyfield=NO );
public     :                  OPSImpExp             logical GetInternType (char *string );
public     :                  OPSImpExp             char *GetPLType (char *clsnames );
public     :                  OPSImpExp             char *GetPLType (DatabaseHandle &dbhandle, char *typestring );
public     :                  OPSImpExp             int32 GetResID ( );
public     :                                        SDB_Structure *GetStructDef ( );
public     :                  OPSImpExp             char *GetSystemType (int16 itype, char *typestring );
public     :                                        SDB_Type *GetTypeDef ( );
public     :                                        logical ImportMember (void *xddeptr, void *fdlptr );
public     :                  OPSImpExp             logical InitFromString (char *string );
public     :                  OPSImpExp             void Initialize ( );
public     :                  OPSImpExp             int16 IsAttrToBeAligned ( );
public     :                  OPSImpExp             logical IsBasicType (DatabaseHandle &dbhandle );
public     :                  OPSImpExp             char *KeyTypeCString ( );
public     :                  OPSImpExp             char *KeyTypeCString (DatabaseHandle &dbhandle, char *string );
public     :                  OPSImpExp             char *ParmTypeCString ( );
public     :                  OPSImpExp             char *ParmTypeCString (DatabaseHandle &dbhandle, char *string );
public     :                  OPSImpExp             char *Privilege (char *string );
public     :                                        logical ProvideType (void *xddeptr, void *fdlptr );
public     :                  OPSImpExp                  SDB_Member (char *fldnames, char *fldtypes, SDB_RLEV fldreflev, uint16 fldsize, uint16 fldprec, uint16 flddim, char *gentype, logical statopt, logical virtopt, int32 w_resid=0 );
public     :                  OPSImpExp                  SDB_Member (SDB_Member *dbmptr );
public     :                  OPSImpExp                  SDB_Member ( );
public     :                  OPSImpExp             logical SetCSDefault (char *csname );
public     :                  OPSImpExp             logical SetDefault (DatabaseHandle &dbhandle );
public     :                  OPSImpExp             void SetVirtual (logical virtopt );
public     :                                        uint32 *get_ddedim ( );
public     :                  OPSImpExp             SDB_Member &operator= (const SDB_Member &dbm_refc );
public     :                  OPSImpExp             void set_ddeprv (ODC_Privilege privilege );
public     :                  OPSImpExp             void set_reference (SDB_RLEV reflevel );
public     :                  OPSImpExp                  ~SDB_Member ( );
};

#pragma pack()
#endif
