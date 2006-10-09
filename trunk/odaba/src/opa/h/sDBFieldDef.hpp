/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBFieldDef

\brief    Definition for the internal presentation of property data
          The  internal property  definition contains  all information available
          and  necessary accessing data of the property. Among basic information
          such  as type and  size it contains  special ODABA2 access information
          such as index and base collection definitions.
          Alls  these information are used for  reading and writing data just as
          to execute operations on properties.

\date     $Date: 2006/08/30 13:35:33,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBFieldDef_HPP
#define   DBFieldDef_HPP

class     DBFieldDef;

#define  DB_ENUM_SIZE                              2
#define  INVALID_VERSION                           0xFFFE
#include  <sDLL.h>
class     FieldSource;
#ifndef   DLL_DBIndex_HPP
#define   DLL_DBIndex_HPP
#include  <sDBIndex.hpp>
#include  <sDLL.h>
#endif
class     ACObject;
class     BNFData;
class     BNFExpData;
class     CAU_simpleAction;
class     DBExtend;
class     DBIndexList;
class     DBResource;
class     DBStructDef;
class     Dictionary;
class     ExpressionReference;
class     FieldSource;
class     LACObject;
class     ODC_Function;
class     ODC_Variable;
class     SDB_Attribute;
class     SDB_BaseStruct;
class     SDB_Index;
class     SDB_Member;
class     SDB_Property;
class     SDB_Reference;
class     SDB_Relationship;
class     smcb;
#include  <cMAT_Types.h>
#include  <cPIADEF.h>
#include  <cSDB_RLEV.h>
#include  <cSDB_SET.h>
#include  <cSystemPropertyTypes.h>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sFieldDef.hpp>
#include  <sPropertyHandle.hpp>
#include  <sRessourceLock.hpp>
#include  <sTypeKey.hpp>
#include  <sfmcb.hpp>
#pragma pack(8)

class  DBFieldDef :public FieldDef
{
protected  :         DBIndexList                                 *index_list;                                                // 
protected  :         int32                                        offset_ext;                                                // 
protected  :         int32                                        ext_length;                                                // 
protected  :         DBFieldDef                                  *inverse_field;                                             // 
protected  :         char                                         inverse_fname[40];                                         // 
protected  :         logical                                      cluster_opt;                                               // 
protected  :         int16                                        mb_number;                                                 // 
protected  :         MAT_Types                                    meta_field;                                                // 
protected  :         char                                         gen_type[40];                                              // 
protected  :         PIADEF                                       privilege;                                                 // 
protected  :         logical                                      static_field;                                              // 
protected  :         logical                                      virtual_field;                                             // 
protected  :         logical                                      dominant;                                                  // 
protected  :         logical                                      sec_reference;                                             // Secondary reference
protected  :         logical                                      log_reference;                                             // Logical reference
protected  :         int16                                        version;                                                   // 
protected  :         char                                        *extend;                                                    // 
protected  :         logical                                      owning;                                                    // 
protected  :         logical                                      create;                                                    // 
protected  :         logical                                      week_typed;                                                // 
protected  :         logical                                      depend;                                                    // 
protected  :         logical                                      update;                                                    // 
protected  :         logical                                      multikey;                                                  // 
protected  :         ExpressionReference                         *initval;                                                   // 
protected  :         DBResource                                  *resource;                                                  // 
protected  :         logical                                      clustered_table;                                           // 
protected  :         int8                                         is_base_coll;                                              // 
protected  :         RessourceLock                               *resource_lock;                                             // 
protected  :         int32                                        net_pos;                                                   // 
protected  :         uint32                                       net_length;                                                // 
protected  :         DBFieldDef                                  *prev_field;                                                // 
protected  :         logical                                      global_identity;                                           // 
protected  :         int8                                         set_operation;                                             // 
protected  :         logical                                      by_reference;                                              // 
protected  :         logical                                      del_empty;                                                 // 
protected  :         logical                                      shared;                                                    // 
protected  :         ExpressionReference                         *constraint;                                                // 
protected  :         DLL(FieldSource)                            *sources;                                                   // 

public     :
                     MAT_Types                                   &get_meta_field() { return(meta_field); }
                     int32                                        get_net_pos() { return(net_pos); }
                     logical                                      get_global_identity() { return(global_identity); }
                     int8                                         get_set_operation() { return(set_operation); }
                     logical                                      get_by_reference() { return(by_reference); }
                     ExpressionReference                         *get_constraint() { return(constraint); }
                     DLL(FieldSource)                            *get_sources() { return(sources); }
public     :                                        logical CanReference (DBFieldDef *fielddef );
public     :                                        logical ChangeTopIndex (DBIndex *dbindex_ptr );
public     :                                        logical CopyDescription (DBFieldDef &dbfield_ref );
public     :                                        logical CopyExtField_dtd (DBFieldDef *srce_flddef, void *targfld, void *srcefld, int32 tlen, int32 slen, logical pif );
public     :                                        logical CopyExtInst (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst, logical *p_update, logical pif );
public     :                                        logical CopyExtInst_dtd (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst, logical *p_update, logical pif );
public     :                                        logical CopyExtInst_dtr (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst );
public     :                                        logical CopyExtInst_rtd (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst );
public     :                                        logical CopyExtInst_rtr (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst, logical pif );
public     :                                        logical CopyTopIndex (DBFieldDef *flddefptr );
public     :                                        logical CreateIndex (Dictionary *dictptr, SDB_Index *dbiptr=NULL );
public     :                                        logical CreateIndex (char *key_names, logical uniopt, logical tempopt, logical caseopt, logical empopt, SDB_SET settyp );
public     :                                        logical CreateIndex (PropertyHandle &ph, Dictionary *dictptr );
public     :                                        logical CreateIndex ( );
public     :                                        logical CreateIndex (DBIndex *indxdef );
public     :                                        logical CreateIndexList (Dictionary *dictptr, SDB_Reference *dbrptr, logical crt_opt );
public     :                                        logical CreateIndexList (PropertyHandle &ph, Dictionary *dictptr, logical crt_opt );
public     :                                        logical CreateIndexList (SDB_Index *dbilistptr=NULL, int16 dbicount=0 );
public     :                                        logical CreateSourceList (SDB_Member *dbmptr );
public     :                                        logical CreateSourceList (char *init_string, int32 string_len );
public     :                                        logical CreateSourceList (PropertyHandle &ph );
public     :                                        logical CreateSynonymList (SDB_Member *dbmptr );
public     :                                        logical CreateSynonymList (PropertyHandle &ph );
public     :                  OPAImpExp             logical CreateViewSource (BNFData *bnf_data );
public     :                  OPAImpExp                  DBFieldDef (char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim, smcb *smcbptr, char *gentype, logical secrefr, char *extnames, char *irefname, DBIndex *indexptr );
public     :                  OPAImpExp                  DBFieldDef (fmcb *fmcbptr );
public     :                  OPAImpExp                  DBFieldDef (Dictionary *dictptr, PropertyHandle &ph, smcb *smcbptr, DBIndex *indexptr, logical domopt, logical logrefr, logical secrefr, logical depopt, char *extnames, char *irefname );
public     :                  OPAImpExp                  DBFieldDef ( );
public     :                  OPAImpExp                  DBFieldDef (Dictionary *dictptr, SDB_Reference *dbrptr, smcb *smcbptr, DBIndex *indexptr, logical domopt, logical logrefr, logical secrefr, logical depopt, char *extnames, char *irefname );
public     :                  OPAImpExp                  DBFieldDef (SDB_Property *dbyptr, smcb *smcbptr );
public     :                                        logical ExtToInt (char *intfld, char *extfld, logical pif );
public     :                                        logical ExtToIntDim (char *extfld, char *intfld, logical pif );
public     :                                        logical Fill (SDB_Attribute *dbaptr, Dictionary *dictptr );
public     :                                        logical Fill (DBStructDef *strdef, BNFData *bnf_data, Dictionary *dictptr );
public     :                                        logical Fill (SDB_BaseStruct *dbbptr, Dictionary *dictptr, logical setup );
public     :                                        logical Fill (SDB_Reference *dbrptr, Dictionary *dictptr, logical setup );
public     :                                        logical Fill (SDB_Relationship *dbpptr, Dictionary *dictptr, logical setup );
public     :                                        logical Fill (SDB_Property *dbyptr, Dictionary *dictptr );
public     :                                        logical Fill (SDB_Member *dbmptr, Dictionary *dictptr, logical transient );
public     :                                        logical FillAttribute (PropertyHandle &ph, Dictionary *dictptr, int32 nsid );
public     :                                        logical FillBaseStruct (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical setup );
public     :                                        logical FillFunction (PropertyHandle &ph, Dictionary *dictptr, int32 nsid );
public     :                                        logical FillMember (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical transient );
public     :                                        logical FillProperty (PropertyHandle &ph, Dictionary *dictptr, int32 nsid );
public     :                                        logical FillReference (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical setup );
public     :                                        logical FillRelationship (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical setup );
public     :                                        logical FillVariable (PropertyHandle &ph, Dictionary *dictptr, int32 nsid );
public     :                                        DBFieldDef *GetDBField (uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp             DBStructDef *GetDBStruct ( );
public     :                  OPAImpExp             DBStructDef *GetDBStruct (Dictionary *dictptr, int16 schema_version_w=CUR_VERSION );
public     :                  OPAImpExp             char *GetExtendName ( );
public     :                  OPAImpExp             DBIndex *GetIndexDef (int16 indx_pos );
public     :                  OPAImpExp             DBIndex *GetIndexDef (char *keyname );
public     :                  OPAImpExp             char *GetIndexName (int32 indx0 );
public     :                  OPAImpExp             int32 GetResourceID ( );
public     :                  OPAImpExp             char *GetSQLType (char *sql_type );
public     :                                        FieldSource *GetSource (int16 indx_pos );
public     : static           OPAImpExp             DBFieldDef *__cdecl GetStaticFieldDef (int16 ityp );
public     : static           OPAImpExp             DBFieldDef *__cdecl GetStaticFieldDef (char *strnames, DBStructDef *dbstrdef );
public     : static           OPAImpExp             DBFieldDef *__cdecl GetStaticFieldDef (char *prop_names );
public     : static           OPAImpExp             DBFieldDef *__cdecl GetStaticFieldDef (MAT_Types meta_type );
public     :                  OPAImpExp             DBStructDef *GetStructDef ( );
public     :                  OPAImpExp             DBStructDef *GetStructDef (DictionaryHandle &dict_hdl );
public     :                  OPAImpExp             DBStructDef *GetStructDef (DictionaryHandle &dict_hdl, uint8 schemaversion );
public     : static           OPAImpExp             SystemPropertyTypes __cdecl GetSysPropType (char *prop_names );
public     :                                        TypeKey &GetTypeKey ( );
public     :                                        logical HasGUID ( );
public     :                  OPAImpExp             logical ILock (logical wait );
public     :                  OPAImpExp             logical IUnlock ( );
public     :                                        void InitAttribute (void *instptr );
public     :                                        void InitExtInst (char *targ_inst );
public     :                  OPAImpExp             DBFieldDef *InitField (int16 ityp, int8 set_opt, logical stat_opt, logical v_opt );
public     :                  OPAImpExp             DBFieldDef *InitField (char *strnames, DBStructDef *dbstrdef, int8 set_opt, logical stat_opt, logical v_opt );
public     :                                        void Initialize ( );
public     :                                        logical IntToExt (char *extfld, char *intfld, logical pif );
public     :                                        logical IntToExtDim (char *extfld, char *intfld, logical pif );
public     :                  OPAImpExp             logical IntToNet (char *netfld, char *intfld );
public     :                  OPAImpExp             logical IsActive ( );
public     :                                        logical IsBaseCollection (Dictionary *dictptr, TypeKey &tkey );
public     :                                        logical IsBased (Dictionary *dictptr, TypeKey &tkey, char *fldnames );
public     :                  OPAImpExp             logical IsEnumeration ( );
public     :                                        logical IsGlobalInstance (Dictionary *dictionary, DBStructDef *strdef );
public     :                                        logical IsInverseBased (Dictionary *dictptr, TypeKey &tkey, char *fldnames );
public     :                  OPAImpExp             logical IsPIHandle ( );
public     :                  OPAImpExp             logical IsStructure ( );
public     :                  OPAImpExp             logical IsText ( );
public     :                  OPAImpExp             logical IsTransient ( );
public     :                  OPAImpExp             logical IsTyped ( );
public     :                  OPAImpExp             logical IsUniqueKey (char *keynames=NULL );
public     :                  OPAImpExp             logical IsViewStructure ( );
public     :                  OPAImpExp             logical NetToInt (char *intfld, char *netfld );
public     :                                        logical Release ( );
public     :                                        void Remove ( );
public     :                                        void RemoveSourceList ( );
public     :                  OPAImpExp             logical SetExpressionRef (ExpressionReference **expr_ref, char *init_string, int32 string_len );
public     :                  OPAImpExp             logical SetExpressionRef (ExpressionReference **expr_ref, ExpressionReference *exprref_ptr );
public     :                  OPAImpExp             logical SetExtent (char *extnames );
public     :                                        void SetPrevious (DBFieldDef *flddefptr );
public     :                                        logical SetupAttribute (int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupAttribute (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupAttribute (SDB_Attribute *dbaptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned );
public     :                                        logical SetupBaseStruct (int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupBaseStruct (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupBaseStruct (SDB_BaseStruct *dbbptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned );
public     :                                        logical SetupField (int32 &intpos, int32 &extpos, int16 allign, int8 &max_aligned );
public     :                                        logical SetupIndexList ( );
public     :                  OPAImpExp             void SetupIntern (smcb *smcbptr, char *extnames, char *irefname, DBIndex *indexptr );
public     :                                        logical SetupInverse ( );
public     :                                        logical SetupReference (int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupReference (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupReference (SDB_Reference *dbrptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned );
public     :                                        logical SetupRelation (int32 &intpos, int32 &extpos, int32 &netpos, logical old_version, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupRelation (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, logical old_version, int16 allign, int8 &max_aligned, logical is_v5=NO );
public     :                                        logical SetupRelation (SDB_Relationship *dbpptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, logical old_version, int16 allign, int8 &max_aligned );
public     :                                        logical SetupType (Dictionary *dictptr, logical dclopt );
public     :                                        logical UpdateDescription (DBFieldDef &dbfield_ref );
public     :                  OPAImpExp             logical get_clst_table ( );
public     :                                        logical get_cluster_opt ( );
public     :                  OPAImpExp             logical get_create ( );
public     :                                        logical get_del_empty ( );
public     :                  OPAImpExp             logical get_depend ( );
public     :                                        logical get_dominant ( );
public     :                                        int32 get_ext_length ( );
public     :                  OPAImpExp             const char *get_extend ( );
public     :                  OPAImpExp             const char *get_gen_type ( );
public     :                  OPAImpExp             const char *get_generic_type ( );
public     :                                        DBIndexList *get_index_list ( );
public     :                  OPAImpExp             const char *get_initval ( );
public     :                  OPAImpExp             ExpressionReference *get_initval_expr ( );
public     :                  OPAImpExp             DBFieldDef *get_inverse ( );
public     :                  OPAImpExp             const char *get_inverse_name ( );
public     :                                        logical get_is_base_coll ( );
public     :                  OPAImpExp             logical get_log_reference ( );
public     :                  OPAImpExp             int16 get_mb_number ( );
public     :                  OPAImpExp             logical get_multikey ( );
public     :                  OPAImpExp             uint32 get_net_length ( );
public     :                  OPAImpExp             int32 get_offset_ext ( );
public     :                  OPAImpExp             logical get_owning ( );
public     :                  OPAImpExp             DBFieldDef *get_prev_field ( );
public     :                  OPAImpExp             PIADEF get_privilege ( );
public     :                                        DBResource *get_resource ( );
public     :                                        logical get_sec_reference ( );
public     :                  OPAImpExp             logical get_shared ( );
public     :                  OPAImpExp             logical get_static ( );
public     :                  OPAImpExp             logical get_transient ( );
public     :                  OPAImpExp             logical get_update ( );
public     :                  OPAImpExp             int16 get_version ( );
public     :                  OPAImpExp             logical get_virtual ( );
public     :                  OPAImpExp             logical get_weak_typed ( );
public     :                  OPAImpExp             logical operator= (DBFieldDef &dbfield_ref );
public     :                                        void set_by_reference (logical log_ref );
public     :                                        void set_clst_table (logical clustopt );
public     :                                        void set_cluster_opt (logical option );
public     :                  OPAImpExp             logical set_constraint (char *init_string, int32 string_len );
public     :                  OPAImpExp             logical set_constraint (ExpressionReference *exprref_ptr );
public     :                  OPAImpExp             void set_create (logical option );
public     :                  OPAImpExp             void set_del_empty (logical del_empty_opt );
public     :                  OPAImpExp             void set_depend (logical option );
public     :                                        void set_dominant (logical option );
public     :                                        void set_ext_length (int32 length );
public     :                                        void set_gen_type (char *gtype );
public     :                  OPAImpExp             void set_global_identity (logical guid_opt );
public     :                                        void set_index_list (DBIndexList *indxlst );
public     :                  OPAImpExp             logical set_initval (char *init_string, int32 string_len );
public     :                  OPAImpExp             logical set_initval (ExpressionReference *exprref_ptr );
public     :                  OPAImpExp             void set_inverse_name (char *inv_name );
public     :                                        void set_is_base_coll (logical option );
public     :                                        void set_log_reference (logical log_ref );
public     :                  OPAImpExp             void set_multikey (logical multi_key );
public     :                                        void set_net_length (uint32 netlength );
public     :                                        void set_net_pos (int32 position );
public     :                                        void set_offset_ext (int32 offset );
public     :                  OPAImpExp             void set_owning (logical own_opt );
public     :                                        void set_prev_field (DBFieldDef *dbfield_ptr );
public     :                  OPAImpExp             void set_privilege (PIADEF accss_opt );
public     :                                        void set_resource (DBResource *resptr );
public     :                  OPAImpExp             void set_sec_reference (logical option );
public     :                  OPAImpExp             void set_set_operation (int8 int_option );
public     :                                        void set_shared (logical shared_opt );
public     :                  OPAImpExp             void set_transient (logical transient_opt );
public     :                  OPAImpExp             void set_update (logical update_opt );
public     :                  OPAImpExp             void set_version (uint16 version_nr=CUR_VERSION );
public     :                                        void set_virtual (logical option );
public     :                  OPAImpExp             void set_weak_typed (logical option );
public     :                  OPAImpExp                  ~DBFieldDef ( );
public     :                                        void set_inverse (DBFieldDef *dbfield_ptr ){

  inverse_field = dbfield_ptr;

}

public     :                                        logical set_log_ref (logical logref ){

    return(log_reference = logref);

}

public     :                                        void set_mb_number (int16 mbnumber ){

  mb_number = mbnumber;

}

public     :                                        void set_static_field (logical statopt ){

  static_field = statopt;

}

};

#pragma pack()
#endif
