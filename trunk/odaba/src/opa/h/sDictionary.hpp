/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    Dictionary

\brief    Dictionary
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/06/05 13:54:32,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Dictionary_HPP
#define   Dictionary_HPP

class     Dictionary;

#define  SYS_NSID                                  0
#define  TEMP_MAIN                                 254
#include  <sDLL.h>
class     DBHandle;
#include  <sGSRT.h>
class     OBH_ListEntry;
#include  <sDLL.h>
class     OPDecl;
#ifndef   BTI_DBExtend_HPP
#define   BTI_DBExtend_HPP
#include  <sDBExtend.hpp>
#include  <sBTI.h>
#endif
#ifndef   BTI_DBStructDef_HPP
#define   BTI_DBStructDef_HPP
#include  <sDBStructDef.hpp>
#include  <sBTI.h>
#endif
#ifndef   BTI_Namespace_HPP
#define   BTI_Namespace_HPP
#include  <sNamespace.hpp>
#include  <sBTI.h>
#endif
class     ACObject;
class     BNFData;
class     BNFExpData;
class     BNFParser;
class     BNF_OSI;
class     CDictionary;
class     DBExtend;
class     DBFieldDef;
class     DBFieldList;
class     DBStructDef;
class     DBViewStructDef;
class     Dictionary;
class     ENUM_Value;
class     LDictionary;
class     OPDecl;
class     OPExpressionDecl;
class     OPFunctionDecl;
class     OperEnvironment;
class     ParmList;
class     RessourceLock;
class     SDB_Attribute;
class     SDB_BaseStruct;
class     SDB_Key;
class     SDB_Reference;
class     SDB_Relationship;
class     StructDef;
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <cSDB_ST.h>
#include  <cTYP_TYPES.h>
#include  <sBinTree.hpp>
#include  <sDBHandle.hpp>
#include  <sNamespace.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
#include  <sdttm.hpp>
#pragma pack(8)

class  Dictionary :public virtual DBHandle,
public Namespace
{
protected  :         DLL(DBHandle)                               *handle_list;                                               // 
protected  :         BinTree                                     *extdef_tree;                                               // 
protected  :         BTI(DBExtend)                                extdef_list;                                               // 
protected  :         BinTree                                     *structure_tree;                                            // 
protected  :         BTI(DBStructDef)                             structure_list;                                            // 
protected  :         BinTree                                     *namespace_tree;                                            // 
protected  :         BTI(Namespace)                               namespace_list;                                            // 
protected  :         PropertyHandle                              *extend_pi;                                                 // 
protected  :         PropertyHandle                              *xxpers_struct_pi;                                          // 
protected  :         PropertyHandle                              *struct_pi;                                                 // 
protected  :         PropertyHandle                              *codeset_pi;                                                // 
protected  :         PropertyHandle                              *type_pi;                                                   // 
protected  :         logical                                      test_opt;                                                  // 
protected  :         logical                                      strpi_locked;                                              // 
protected  :         logical                                      extpi_locked;                                              // 
protected  :         logical                                      typepi_locked;                                             // 
protected  :         int32                                        ext_number;                                                // 
protected  :         PropertyHandle                              *refr_pi;                                                   // 
protected  :         char                                         ctxi_path[301];                                            // 
protected  :         RessourceLock                               *xxdict_lock;                                               // 
protected  :         GSRT(OBH_ListEntry)                         *obh_list;                                                  // 
protected  :         int16                                        last_schemav;                                              // 
protected  :         PropertyHandle                              *view_pi;                                                   // 
protected  :         PropertyHandle                              *viewext_pi;                                                // 
protected  :         BNF_OSI                                     *expression_parser;                                         // 
protected  :         DLL(OPDecl)                                 *expression_list;                                           // 
protected  :         int32                                        temp_struct_id;                                            // 

public     :
                     DLL(DBHandle)                               *get_handle_list() { return(handle_list); }
                     BinTree                                     *get_extdef_tree() { return(extdef_tree); }
                     BTI(DBExtend)                               &get_extdef_list() { return(extdef_list); }
                     BTI(DBStructDef)                            &get_structure_list() { return(structure_list); }
                     BinTree                                     *get_namespace_tree() { return(namespace_tree); }
                     BTI(Namespace)                              &get_namespace_list() { return(namespace_list); }
                     PropertyHandle                              *get_extend_pi() { return(extend_pi); }
                     PropertyHandle                              *get_xxpers_struct_pi() { return(xxpers_struct_pi); }
                     PropertyHandle                              *get_struct_pi() { return(struct_pi); }
                     PropertyHandle                              *get_codeset_pi() { return(codeset_pi); }
                     PropertyHandle                              *get_type_pi() { return(type_pi); }
                     logical                                      get_test_opt() { return(test_opt); }
                     logical                                      get_typepi_locked() { return(typepi_locked); }
                     int32                                        get_ext_number() { return(ext_number); }
                     PropertyHandle                              *get_refr_pi() { return(refr_pi); }
                     char                                        *get_ctxi_path() { return(ctxi_path); }
                     RessourceLock                               *get_xxdict_lock() { return(xxdict_lock); }
                     GSRT(OBH_ListEntry)                         *get_obh_list() { return(obh_list); }
                     int16                                        get_last_schemav() { return(last_schemav); }
                     PropertyHandle                              *get_view_pi() { return(view_pi); }
                     PropertyHandle                              *get_viewext_pi() { return(viewext_pi); }
                     DLL(OPDecl)                                 *get_expression_list() { return(expression_list); }
public     :                  OPAImpExp             logical AddExpression (DBStructDef *strdef, OPDecl *expr_decl );
public     :                  OPAImpExp             void AddExtendDef (DBExtend *db_ext );
public     :                                        void AddHandle (DBHandle *dbh_ptr );
public     :                  OPAImpExp             int32 BaseType (char *strnames );
public     :                  OPAImpExp             logical CheckExpression (ACObject *resobj, char *clsnames, char *exprnames, char *w_implnames=NULL );
public     :                  OPAImpExp             logical CheckExpression (char *expression, ACObject *obhandle, char *clsnames );
public     :                  OPAImpExp             logical CheckExtendDef (char *extname, int32 nsid );
public     :                  OPAImpExp             logical CheckExtendDef (TypeKey &tkey );
public     :                  OPAImpExp             logical CheckExtendDef (char *scoped_name );
public     :                  OPAImpExp             logical CheckValueSet (char *extname, int32 nsid );
public     :                  OPAImpExp             logical CheckValueSet (TypeKey &tkey );
public     :                  OPAImpExp             logical CheckValueSet (char *scoped_name );
public     : virtual          OPAImpExp             void CloseDictionary ( );
public     :                                        logical ClosePIs ( );
public     :                  OPAImpExp             logical CopyCodeset (Dictionary *srcedict, TypeKey tkey_d, TypeKey nkey_d, PIREPL db_replace=REPL_none, logical retainSID=NO, logical retain_schemav=NO );
public     :                  OPAImpExp             logical CopyExtentDef (Dictionary *srcedict, TypeKey &tkey, TypeKey &nkey, char *targ_struct=NULL, logical transaction=NO );
public     :                  OPAImpExp             logical CopyExtentDef (PropertyHandle &text_ph, PropertyHandle &sext_ph, TypeKey nkey_d, TypeKey &tstructkey );
public     :                  OPAImpExp             logical CopyMemberType (Dictionary *srcedict, PropertyHandle *memb_pi, TypeKey nkey_d, char *topname=NULL, PIREPL db_replace=REPL_none, logical retainSID=NO, logical retain_schemav=NO );
public     :                  OPAImpExp             logical CopyStructure (Dictionary *srcedict, TypeKey tkey_d, TypeKey nkey_d, char *topname=NULL, PIREPL db_replace=REPL_none, logical retainSID=NO, logical retain_schemav=NO );
public     :                  OPAImpExp             logical CopyToODABAStr (PropertyHandle &pers_pi, PropertyHandle &ext_pi );
public     :                  OPAImpExp             logical CopyType (Dictionary *srcedict, TypeKey tkey_d, TypeKey nkey_d, char *topname=NULL, PIREPL db_replace=REPL_none, logical retainSID=NO, logical retain_schemav=NO, logical transaction=NO );
public     : virtual          OPAImpExp             DBHandle *CreateDBHandle (char *cpath, PIACC accopt, logical netopt, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     : virtual          OPAImpExp             DBHandle *CreateDBHandle ( );
public     : virtual          OPAImpExp             DBHandle *CreateDBHandle (char *cpath, int16 lowEBN, int16 highEBN, int32 dasize=0, logical largedb=NO );
public     : virtual          OPAImpExp             logical CreateEnum (char *enum_name, char *basetype );
public     : virtual          OPAImpExp             DBExtend *CreateExtentDef (TypeKey &tkey );
public     :                                        PropertyHandle *CreateGlobalVariable (PropertyHandle &prophdl_ref, char *var_name );
public     :                                        BNFParser *CreateParser ( );
public     : virtual          OPAImpExp             DBStructDef *CreateStructDef (TypeKey &tkey, DBStructDef *strdef );
public     : virtual          OPAImpExp             char *CreateTempExtent (char *strnames, char *extnames_w=NULL, char *key_name_w=NULL, char *baseexts_w=NULL, logical weak_opt_w=NO, logical own_opt_w=NO );
public     : virtual          OPAImpExp             char *CreateTempExtent (DBFieldDef *dbfield_ptr, char *extnames_w=NULL );
public     : virtual          OPAImpExp             char *CreateTempExtent (DBExtend *db_ext, char *extnames_w=NULL );
public     :                                        DBStructDef *CreateTempStruct (DBFieldList *dbfieldlist, char *strnames_w=NULL );
public     :                                        DBStructDef *CreateTempStruct (DBFieldDef *field_def, char *strnames_w=NULL );
public     :                                        DBStructDef *CreateTempStruct (DBStructDef *strdef_ptr, char *pathes, char *strnames_w=NULL );
public     : virtual          OPAImpExp             logical DeleteEnum (char *enum_name );
public     :                  OPAImpExp                  Dictionary (char *cpath, PIACC accopt, logical w_netopt=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     :                  OPAImpExp                  Dictionary ( );
public     :                  OPAImpExp                  Dictionary (DBHandle *dbhandle );
public     :                                        logical Display (char *ppath );
public     :                                        char *GetCTXIPath ( );
public     : virtual          OPAImpExp             CDictionary *GetClientDictionary ( );
public     :                                        char *GetDLLPath (char *cpath, char *dll_name );
public     :                  OPAImpExp             DictionaryHandle *GetDictionaryHandle ( );
public     :                  OPAImpExp             OPDecl *GetExpression (char *clasname, char *exprname, ParmList *p_liste=NULL );
public     :                  OPAImpExp             DBExtend *GetExtendDef (char *extname, int32 nsid );
public     :                  OPAImpExp             DBExtend *GetExtendDef (TypeKey &tkey );
public     :                  OPAImpExp             DBExtend *GetExtendDef (char *scoped_name );
public     :                  OPAImpExp             char *GetExtentType (TypeKey &tkey );
public     :                  OPAImpExp             char *GetExtentType (char *extnames, int32 nsid );
public     :                  OPAImpExp             char *GetExtentType (char *scoped_name );
public     :                                        PropertyHandle *GetGlobalVariable (char *var_name );
public     :                  OPAImpExp             int16 GetID_SIZE ( );
public     : virtual          OPAImpExp             int16 GetLastStructureID ( );
public     : virtual          OPAImpExp             LDictionary *GetLocalDictionary ( );
public     :                                        char *GetNSPath (char *string, TypeKey &tkey );
public     :                  OPAImpExp             Namespace *GetNamespace (char *scope_name );
public     :                  OPAImpExp             Namespace *GetNamespace (TypeKey &tkey );
public     :                  OPAImpExp             Namespace *GetNamespace (int32 nsid );
public     : virtual          OPAImpExp             ACObject *GetOBHandle (uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp             BNFParser *GetParser ( );
public     :                  OPAImpExp             char *GetParserError ( );
public     :                                        int32 GetSType (int32 typetype );
public     : virtual          OPAImpExp             DBStructDef *GetServerDefinition (char *strname );
public     :                  OPAImpExp             DBStructDef *GetStrDefVersion (TypeKey &tkey, uint8 schemaversion );
public     :                  OPAImpExp             DBStructDef *GetStructDef (char *strnames, int32 nsid );
public     :                  OPAImpExp             DBStructDef *GetStructDef (char *strnames, int32 nsid, uint8 schemaversion );
public     :                  OPAImpExp             DBStructDef *GetStructDef (TypeKey &tkey );
public     :                  OPAImpExp             DBStructDef *GetStructDef (char *scoped_name );
public     : virtual          OPAImpExp             char *GetTempName (char *extnames );
public     :                                        int32 GetTempStructID ( );
public     : virtual          OPAImpExp             Dictionary *GetThisDictionary ( );
public     :                  OPAImpExp             logical GetTypeSpec (TypeKey &tkey, int16 *itypptr=NULL, int16 *stypptr=NULL, int16 *atypptr=NULL );
public     :                                        ENUM_ValueList *GetValueList (char *extnames );
public     :                                        void InitLists ( );
public     :                                        void Initialize (char *cpath, PIACC accopt, logical w_netopt=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     :                                        logical IsBasicType (char *typenames );
public     :                  OPAImpExp             DBExtend *LocateExtentDef (TypeKey &tkey );
public     :                                        logical Lock (logical wait );
public     :                  OPAImpExp             logical OpenDictionary ( );
public     :                                        logical OpenPIs (DBHandle *w_dbhandle=NULL, logical init_enums=YES );
public     :                  OPAImpExp             BNFData *ParseExpression (char *expression, char *symbol, char **expr_dup );
public     :                  OPAImpExp             BNFData *ParseFile (char *cpath, char *symbol );
public     :                  OPAImpExp             OPDecl *ProvExpression (ACObject *resobj, char *clasname, char *exprname, PropertyHandle *co, ParmList *p_liste=NULL, ACObject *w_obhandle=NULL, OperEnvironment *operenv_w=NULL, logical refresh_opt=NO );
public     :                  OPAImpExp             OPDecl *ProvExpression (ACObject *resobj, char *clasname, char *expression, PropertyHandle *co, ACObject *w_obhandle=NULL, OperEnvironment *operenv_w=NULL );
public     :                  OPAImpExp             OPDecl *ProvExpression (ACObject *resobj, char *clasname, BNFData *bnf_data, PropertyHandle *co, ACObject *w_obhandle=NULL, OperEnvironment *operenv_w=NULL, char *expr_dup_w=NULL );
public     :                  OPAImpExp             OPFunctionDecl *ProvFunction (ACObject *resobj, char *clasname, char *fnames, PropertyHandle *co, ParmList *p_liste=NULL, logical recurse_opt=NO );
public     :                  OPAImpExp             DBStructDef *ProvideCSDecl (TypeKey &tkey, DBStructDef *strdefptr, int32 itype );
public     :                  OPAImpExp             DBExtend *ProvideExtendDef (char *scoped_name );
public     :                  OPAImpExp             DBExtend *ProvideExtendDef (TypeKey &tkey, uint8 schemaversion );
public     :                  OPAImpExp             DBExtend *ProvideExtendDef (TypeKey &tkey );
public     :                  OPAImpExp             DBExtend *ProvideExtendDef (PropertyHandle &ph, DBStructDef *dbstrdef, DBExtend *baseext );
public     :                  OPAImpExp             DBStructDef *ProvideStructDcl (TypeKey &tkey, int16 strsid, int32 intlen, int32 extlen, TYP_TYPES metatype, SDB_ST strtype, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames=NULL, logical w_vf_opt=NO, int16 w_schema_version=0, logical w_versioning=NO, logical glob_identity=NO );
public     :                  OPAImpExp             DBStructDef *ProvideStructDcl (char *strnames, int16 strsid, int32 intlen, int32 extlen, TYP_TYPES metatype, SDB_ST strtype, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames=NULL, logical w_vf_opt=NO, int16 w_schema_version=0, logical w_versioning=NO, logical glob_identity=NO );
public     :                  OPAImpExp             DBStructDef *ProvideStructDcl (TypeKey &tkey );
public     :                  OPAImpExp             DBStructDef *ProvideStructDef (char *scoped_name );
public     :                  OPAImpExp             DBStructDef *ProvideStructDef (char *scoped_name, uint8 schemaversion );
public     :                  OPAImpExp             DBStructDef *ProvideStructDef (TypeKey &tkey );
public     :                  OPAImpExp             DBStructDef *ProvideStructDef (TypeKey &tkey, uint8 schemaversion );
public     :                  OPAImpExp             DBStructDef *ProvideStructDef (int16 sid, uint8 schemaversion );
public     :                  OPAImpExp             DBStructDef *ProvideTempStructDef (char *scoped_name );
public     :                                        DBStructDef *ProvideType (PropertyHandle &ph );
public     :                                        DBStructDef *ReadSD (PropertyHandle &strpi, TypeKey &tkey, DBStructDef *strdefptr );
public     :                                        DBStructDef *ReadVD (TypeKey &tkey, DBStructDef *strdefptr );
public     :                                        DBStructDef *ReadVL (TypeKey &tkey, DBStructDef *strdefptr );
public     :                                        void Release_extent_pi (logical reserved );
public     :                                        void Release_struct_pi (logical reserved );
public     :                                        void Release_type_pi (logical reserved );
public     :                                        void RemoveExpression (OPDecl *expr_decl, DBStructDef *strdef );
public     :                                        DBExtend *RemoveExtentDef (TypeKey &tkey );
public     :                                        DBExtend *RemoveExtentDef (char *extname, int32 nsid );
public     :                                        StructDef *RemoveStructDef (TypeKey &tkey );
public     :                                        StructDef *RemoveStructDef (char *strname, int32 nsid );
public     :                                        logical Reserve_extent_pi (PropertyHandle &extpi );
public     :                                        logical Reserve_struct_pi (PropertyHandle &strpi );
public     :                                        logical Reserve_type_pi (PropertyHandle &type_ph );
public     : virtual          OPAImpExp             void SetLastSchemaVersion (int16 schema_version );
public     :                                        logical SetupEnumeration (char *strnames, ENUM_Value **value_list, char *base_type, int16 ecount );
public     :                                        logical SetupStructDef (char *strnames, SDB_BaseStruct **baselist, SDB_Attribute **attrlist, SDB_Reference **refrlist, SDB_Relationship **rshplist, SDB_Key *dbklistptr, int16 keycount=0, int8 w_alignment=0, int32 w_resid=0 );
public     :                  OPAImpExp             logical SetupTempStructures ( );
public     :                                        logical Unlock ( );
public     :                  OPAImpExp             logical UpdateVersion ( );
public     :                                        logical UpdateVersionList ( );
public     : virtual          OPAImpExp                  ~Dictionary ( );
};

#pragma pack()
#endif
