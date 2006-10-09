/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    SchemaResources



\date     $Date: 2006/04/12 11:39:37,42 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SchemaResources_HPP
#define   SchemaResources_HPP

class     SchemaResources;

class     ACObject;
class     BNFData;
class     DBFieldList;
class     ENUM_ValueList;
class     OperEnvironment;
class     kcb;
#include  <cODC_Privilege.h>
#include  <sDictionary.hpp>
#include  <sPropertyHandle.hpp>
class  SchemaResources
{
protected  :         ODABAClient                                  odaba_client;                                              // 
protected  :         Dictionary                                  *dictionary;                                                // 
protected  :         ACObject                                    *resources;                                                 // 
protected  :         ACObject                                    *database;                                                  // 
protected  :         int8                                         schema_only;                                               // 

public     :
                     Dictionary                                  *get_dictionary() { return(dictionary); }
                     ACObject                                    *get_resources() { return(resources); }
                     ACObject                                    *get_database() { return(database); }
                     int8                                         get_schema_only() { return(schema_only); }
public     :                                     logical CheckParameter (PropertyHandle &ph, BNFData *bdata, char *type, char *generic_type, uint16 size, uint32 dimension );
public     :                                     logical CreateBaseCollection (DBFieldDef *fielddef, BNFData *bdata );
public     :                                     logical CreateBaseCollection (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateBaseType (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef );
public     :                                     logical CreateBaseType (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateCategories (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateCategory (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateCollection (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef, logical rel_opt );
public     :                                     logical CreateCollection (PropertyHandle &ph, BNFData *bdata, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w=ODC_protected, logical virtual_w=NO, logical static_w=NO, logical transient_w=NO, logical guid_w=NO, logical weak_w=NO, logical update_w=NO, logical mkey_w=NO, logical create_w=YES, logical owner_w=YES, logical dependent_w=NO, logical secondary_w=NO, logical shared_w=NO );
public     :                                     logical CreateCollectionExtensions (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef, int32 index );
public     :                                     logical CreateCollectionExtensions (PropertyHandle &ph, BNFData *bdata, int32 index );
public     :                                     logical CreateEnumerator (ENUM_ValueList *vlist, BNFData *bdata );
public     :                                     logical CreateEnumerator (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateExtent (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateExtent (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateExtentRelation (DBExtend *db_ext, BNFData *bdata, logical sub_ext );
public     :                                     logical CreateExtentRelation (PropertyHandle &ph, BNFData *bdata, logical owning_w=YES );
public     :                                     logical CreateFunction (PropertyHandle &ph, BNFData *bdata, int32 &index_ref, BNFData **impl_ident );
public     :                                     logical CreateFunctionParameter (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateGrouping (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateInheritance (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateInheritance (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateInverse (DBFieldDef *fielddef, BNFData *bdata );
public     :                                     logical CreateInverse (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateKey (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateKey (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateKeyComponent (kcb *kcbptr, BNFData *bdata );
public     :                                     logical CreateKeyComponent (PropertyHandle &ph, BNFData *bdata, logical owning_w=YES );
public     :                                     logical CreateMember (DBFieldDef *fielddef, BNFData *bdata, DBFieldList *dbfieldlist, DBStructDef *strdef, int32 &index_ref, logical setup_opt );
public     :                                     logical CreateMember (PropertyHandle &ph, BNFData *bdata, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w=ODC_protected, logical virtual_w=NO, logical static_w=NO, logical transient_w=NO, logical collopt_w=NO );
public     :                                     logical CreateMembers (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateMembers (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateOrderKey (DBFieldDef *fielddef, BNFData *bdata );
public     :                                     logical CreateOrderKey (PropertyHandle &ph, BNFData *bdata, int8 max_size );
public     :                                     logical CreateOrderKeys (DBFieldDef *fielddef, BNFData *bdata );
public     :                                     logical CreateOrderKeys (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreatePathElement (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateReferences (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateReferences (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateRelationships (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateRelationships (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateSubSets (DBExtend *db_ext, BNFData *bdata );
public     :                                     logical CreateSubSets (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateSuperSets (DBExtend *db_ext, BNFData *bdata );
public     :                                     logical CreateSuperSets (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateTypeProperties (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical CreateTypeProperties (PropertyHandle &ph, char *name, BNFData *bdata, logical del_opt );
public     :                                     logical CreateViewBase (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical CreateViewSource (PropertyHandle &ph, BNFData *bd_ident, BNFData *bdata );
public     :                                     logical GetColOptions (DBFieldDef *fielddef, BNFData *bdata, int32 &index_ref );
public     :                                     logical GetColTypeSpec (DBFieldDef *fielddef, BNFData *bdata, int32 &index_ref, logical setup_opt );
public     :                                     BNFData *GetFileReference (BNFData *bdata, char *symbol );
public     :                                     logical GetPrivilege (BNFData *bdata );
public     :                                     logical GetTypeSpec (DBFieldDef *fielddef, BNFData *bdata, logical setup_opt );
public     :                                     logical GetTypeSpec (BNFData *bdata, char *type, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref );
public     :                                     logical GetTypeSpec (BNFData *bdata, char *type, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref, ODC_Privilege &priv_ref, logical &virt_ref, logical &stat_ref, logical &trans_ref, logical &collopt_ref );
public     :                                     logical InitMember (PropertyHandle &ph, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w=ODC_protected, logical virtual_w=NO, logical static_w=NO, logical transient_w=NO, logical collopt_w=NO );
public     :                                     logical InitReference (PropertyHandle &ph, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w=ODC_protected, logical virtual_w=NO, logical static_w=NO, logical transient_w=NO, logical guid_w=NO, logical weak_w=NO, logical update_w=NO, logical mkey_w=NO, logical create_w=YES, logical owning_w=YES, logical clust_w=NO, logical shared_w=NO );
public     :                                     logical LoadAttributeDcl (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadAttributeDcl (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadCPPCode (PropertyHandle &ph, BNFData *bdata, logical inl_opt );
public     :                                     logical LoadCPPFunction (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadClassDcl (BNFData *bdata );
public     :                                     logical LoadClassDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadClassMembers (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadClassMembers (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadConstDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadControl (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadDocumentTemplate (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadEnumType (BNFData *bdata );
public     :                                     logical LoadEnumType (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadEnumerators (BNFData *bdata );
public     :                                     logical LoadEnumerators (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadExceptDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadExports (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadExports (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadExpression (BNFData *bdata, DBStructDef *strdef, OperEnvironment *operenv_w=NULL );
public     :                                     logical LoadExpression (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadExtentSpec (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadExtentSpec (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadInterfaceDcl (BNFData *bdata );
public     :                                     logical LoadInterfaceDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadKeySpec (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadKeySpec (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadMethod (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadMethodDcl (DBFieldDef *fielddef, BNFData *bdata, int32 &indx_ref );
public     :                                     logical LoadMethodDcl (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadModule (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadModuleDefinition (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadModuleElement (PropertyHandle *ph_ptr, BNFData *bdata );
public     :                                     logical LoadNamespace (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadNamespaceElement (PropertyHandle *ph_ptr, BNFData *bdata );
public     :                                     logical LoadParmSpec (DBFieldDef *fielddef, BNFData *bdata );
public     :                                     logical LoadReferenceDcl (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadReferenceDcl (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadRelationshipDcl (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadRelationshipDcl (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical LoadSchema (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadSchemaElement (PropertyHandle *ph_ptr, BNFData *bdata );
public     :                                     logical LoadScriptDefinition (BNFData *bdata );
public     :                                     logical LoadStructType (BNFData *bdata );
public     :                                     logical LoadStructType (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadTypeDcl (BNFData *bdata );
public     :                                     logical LoadTypeDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadTypeDef (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadTypeReference (BNFData *bdata, PropertyHandle scope_ph, PropertyHandle type_ph );
public     :                                     logical LoadUnionType (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadViewDcl (BNFData *bdata );
public     :                                     logical LoadViewDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt );
public     :                                     logical LoadViewMembers (DBStructDef *strdef, BNFData *bdata );
public     :                                     logical LoadViewMembers (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     logical LoadWindow (PropertyHandle &ph, BNFData *bdata, logical del_opt );
public     :                                     DBStructDef *ProvideStructDef (char *strnames );
public     :                                                             SchemaResources (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle );
public     :                                     logical SetConstraint (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef );
public     :                                     logical SetConstraint (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical SetInitValue (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef );
public     :                                     logical SetInitValue (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical SetMemberExtensions (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef );
public     :                                     logical SetMemberExtensions (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical SetReferenceLevel (DBFieldDef *fielddef, BNFData *bdata, int32 &indx_ref );
public     :                                     logical SetReferenceLevel (PropertyHandle &ph, BNFData *bdata, int32 &index_ref );
public     :                                     logical SetSources (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef );
public     :                                     logical SetSources (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical SetVersion (DBFieldDef *fielddef, BNFData *bdata );
public     :                                     logical SetVersion (PropertyHandle &ph, BNFData *bdata );
public     :                                     logical Validate ( );
public     :                                                             ~SchemaResources ( );
public     :                                     void set_schema_only (int8 schema_opt ){

  schema_only = schema_opt;

}

};

#endif
