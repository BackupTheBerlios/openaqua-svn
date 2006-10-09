/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBStructDef

\brief    Definition for the internal presentation of data structures and enumerations
          Definitions  for  data  structures  are  usually  read  from an ODABA2
          dictionary.  However they can be provided  and filled directly in main
          storage.  Still  in  this  case  the definition should be provided via
          Dictionary functions to make them available for the ODABA2 kernel.
          From  an ODABA2 dictionary  structures are provided  only, if they are
          marked as checked and as ready for a non test environment.

\date     $Date: 2006/08/25 15:13:11,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBStructDef_HPP
#define   DBStructDef_HPP

class     DBStructDef;

#define  TEMPSID                                   -100
#include  <sDLL.h>
class     DBViewPath;
#include  <sDPA.h>
class     OPDecl;
#include  <sDPA.h>
class     OPExpressionDecl;
#include  <sDLL.h>
class     OPFunctionDecl;
class     ACNode;
class     ACObject;
class     ACProperty;
class     CTX_Base;
class     DBFieldDef;
class     DBHandle;
class     DBResource;
class     DBStructDef;
class     DBViewStructDef;
class     Dictionary;
class     ENUM_Value;
class     ENUM_ValueList;
class     FieldList;
class     LACObject;
class     ODC_View;
class     OPDecl;
class     OPExpressionDecl;
class     OPFunctionDecl;
class     OperEnvironment;
class     ParmList;
class     SDB_Attribute;
class     SDB_BaseStruct;
class     SDB_Index;
class     SDB_Key;
class     SDB_Reference;
class     SDB_Relationship;
class     SDB_Structure;
class     acc;
class     binti;
class     exd;
class     fmcb;
class     inti;
class     kcb;
class     node;
class     smcb;
class     srt;
#include  <cFunctionTypes.h>
#include  <cSDB_ST.h>
#include  <cTYP_TYPES.h>
#include  <sMemberInfo.hpp>
#include  <sPropertyHandle.hpp>
#include  <sStructDef.hpp>
#include  <sTypeKey.hpp>
#pragma pack(8)

class  DBStructDef :public StructDef
{
protected  :         MemberInfo                                   base_info;                                                 // 
protected  :         MemberInfo                                   attr_info;                                                 // 
protected  :         MemberInfo                                   refr_info;                                                 // 
protected  :         MemberInfo                                   rshp_info;                                                 // 
protected  :         int32                                        ext_length;                                                // 
protected  :         DBStructDef                                 *prev_struct_def;                                           // 
protected  :         uint16                                       schema_version;                                            // 
protected  :         int16                                        sb_number;                                                 // 
protected  :         logical                                      cluster_option;                                            // 
protected  :         logical                                      vf_opt;                                                    // 
protected  :         DLL(OPFunctionDecl)                         *function_list;                                             // 
protected  :         DPA(OPDecl)                                 *expression_list;                                           // 
protected  :         DBResource                                  *resource;                                                  // 
protected  :         logical                                      versioning;                                                // 
protected  :         char                                        *ext_area;                                                  // 
protected  :         int32                                        net_length;                                                // 
protected  :         logical                                      global_identity;                                           // 
protected  :         logical                                      based_on_object;                                           // 
protected  :         logical                                      check_del_empty;                                           // 
protected  :         DBViewStructDef                             *view_struct;                                               // 
protected  :         int32                                        guid_pos;                                                  // 
protected  :         int32                                        guid_pos_ext;                                              // 
protected  :         DBStructDef                                 *v5_strdef;                                                 // 
protected  :         srt                                         *undef_members;                                             // 

public     :
                     int32                                        get_ext_length() { return(ext_length); }
                     DBStructDef                                 *get_prev_struct_def() { return(prev_struct_def); }
                     logical                                      get_cluster_option() { return(cluster_option); }
                     logical                                      get_vf_opt() { return(vf_opt); }
                     DLL(OPFunctionDecl)                         *get_function_list() { return(function_list); }
                     DPA(OPDecl)                                 *get_expression_list() { return(expression_list); }
                     DBResource                                  *get_resource() { return(resource); }
                     logical                                      get_versioning() { return(versioning); }
                     char                                        *get_ext_area() { return(ext_area); }
                     logical                                      get_global_identity() { return(global_identity); }
                     logical                                      get_based_on_object() { return(based_on_object); }
                     DBViewStructDef                             *get_view_struct() { return(view_struct); }
                     int32                                        get_guid_pos() { return(guid_pos); }
                     int32                                        get_guid_pos_ext() { return(guid_pos_ext); }
                     srt                                         *get_undef_members() { return(undef_members); }
public     :                                        logical AddExpression (OPDecl *expr_decl, ParmList *parmlist );
public     :                  OPAImpExp             logical AddUndefinedMember (char *prop_names );
public     :                                        logical Check (int16 strsid, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames=NULL, logical w_vf_opt=NO );
public     :                                        logical Check (int16 strsid );
public     :                                        logical Check (Dictionary *dictptr, SDB_BaseStruct **baselist, SDB_Attribute **attrlist, SDB_Reference **refrlist, SDB_Relationship **rshplist );
public     :                                        logical CheckKeyDefs ( );
public     :                                        logical CheckKeyMod (void *instarea, void *oldinst );
public     :                                        logical ConvInstVersion (LACObject *lobhandle, void *instarea, uint8 schemaversion, logical *p_update );
public     :                  OPAImpExp             logical CopyDirect (void *targinst, DBStructDef *srcedef, void *srceinst );
public     :                                        logical CopyExtInst (LACObject *lobhandle, DBStructDef *srce_struct, logical *p_update );
public     :                                        logical CreateAttrNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff );
public     :                                        logical CreateBaseNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff );
public     :                                        logical CreateBaseNodes (binti *bintiptr, void *instptr );
public     :                                        OPDecl *CreateExprDecl (Dictionary *dictptr, PropertyHandle *expr_pi, PropertyHandle *retval, ACObject *obhandle, PropertyHandle *co, ParmList *parmlist, OperEnvironment *operenv_w=NULL );
public     :                                        OPFunctionDecl *CreateFctDecl (Dictionary *dictptr, PropertyHandle *fct_pi, ACObject *obhandle, PropertyHandle *co, ParmList *parmlist );
public     :                                        OPFunctionDecl *CreateFctDecl (char *opname );
public     :                                        logical CreateKeyDefs (PropertyHandle &ph );
public     :                                        logical CreateKeyDefs (SDB_Key *dbklistptr, int16 keycount=0 );
public     :                                        logical CreateKeyDefs (kcb *kcbptr );
public     :                                        logical CreateNodes (node *nodeptr, inti *sintiptr, void *instptr );
public     :                                        logical CreateRefrNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff );
public     :                                        logical CreateRshpNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff );
public     :                                        logical CreateSubNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff );
public     :                  OPAImpExp                  DBStructDef (TypeKey &tkey, int16 strsid, int32 intlen, int32 extlen, TYP_TYPES metatype, SDB_ST strtype, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames=NULL, logical w_vf_opt=NO, int16 w_schema_version=0, logical w_versioning=NO, logical glob_identity=NO );
public     :                  OPAImpExp                  DBStructDef ( );
public     : virtual                                logical DirToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, int16 replnum, int16 copynum );
public     :                  OPAImpExp             logical DisplayAlignInfo ( );
public     :                  OPAImpExp             logical ExtToInt (void *intinst, char *extinst, logical pif );
public     :                                        logical FillStructure (Dictionary *dictptr, PropertyHandle &ph );
public     :                                        logical FillV5StructDef (DBStructDef *strdef );
public     :                                        logical FillView (Dictionary *dictptr, PropertyHandle &ph );
public     : virtual                                acc *GetAccess (int16 atyp=UNDF );
public     :                  OPAImpExp             int32 GetAttrPath (int32 indx0, logical full_path, char *fld_path, int32 maxlen, logical with_generics=NO, logical search_in_sharebase=YES );
public     :                  OPAImpExp             DBStructDef *GetBaseStructure (int32 indx0 );
public     : static                                 DBStructDef *__cdecl GetDBStruct (smcb *smcbptr );
public     :                  OPAImpExp             Dictionary *GetDictionary ( );
public     :                  OPAImpExp             DBFieldDef *GetEntry (char *fldnames );
public     :                  OPAImpExp             DBFieldDef *GetEntry (int16 sindex );
public     :                                        int16 GetEntryCount ( );
public     :                                        OPDecl *GetExprDecl (char *fctnames, PropertyHandle *retval, PropertyHandle *co, ParmList *parameters, logical convopt, logical recurse_opt=NO );
public     :                                        int32 GetExtGUIDPosition (Dictionary *dictptr );
public     :                                        OPFunctionDecl *GetFctDecl (char *fctnames, PropertyHandle *retval, PropertyHandle *co, ParmList *parameters, logical convopt, logical recurse_opt=NO );
public     :                                        int32 GetGUIDPosition ( );
public     :                  OPAImpExp             smcb *GetKeySMCB ( );
public     : static                                 DBFieldDef *__cdecl GetMetaAttribute (char *prop_names );
public     :                  OPAImpExp             uint32 GetNetLength ( );
public     : static                                 OPFunctionDecl *__cdecl GetPHFctDecl (char *fctnames, PropertyHandle *retval, PropertyHandle *co, ParmList *parameters );
public     :                  OPAImpExp             int32 GetRefPath (int32 indx0, logical full_path, char *fld_path, int32 maxlen, logical with_generics=NO, logical search_in_sharebase=YES );
public     :                  OPAImpExp             int32 GetShareBasePath (int32 indx0, logical full_path, char *fld_path, int32 maxlen, logical search_in_sharebase=YES );
public     : virtual                                smcb *GetSortKeySMCB (char *fldnames );
public     :                  OPAImpExp             DBStructDef *GetStrDefVersion (Dictionary *dictptr, uint8 schemaversion );
public     : static                                 OPFunctionDecl *__cdecl GetSysFctDecl (char *fctnames, PropertyHandle *retval, ParmList *parameters );
public     :                                        TypeKey &GetTypeKey ( );
public     :                                        DBViewStructDef *GetViewStructDef ( );
public     :                                        void IncreaseAttrCount (int32 count );
public     :                                        void IncreaseBaseCount (int32 count );
public     :                                        void IncreaseRefrCount (int32 count );
public     :                                        void IncreaseRshpCount (int32 count );
public     :                  OPAImpExp             logical Inherits (char *strnames );
public     :                  OPAImpExp             void InitAttributes (void *instptr );
public     :                                        logical InitExtInst (void *targinst );
public     :                  OPAImpExp             logical InitInstance (void *instptr );
public     :                  OPAImpExp             logical Initialize (Dictionary *dictptr, PropertyHandle &ph );
public     :                  OPAImpExp             logical IntToExt (char *extinst, void *intinst, logical pif );
public     :                  OPAImpExp             logical IntToNet (char *netinst, void *intinst );
public     :                                        logical IsBaseCollection (Dictionary *dictptr, TypeKey &tkey, char *fldnames );
public     :                                        logical IsBased (Dictionary *dictptr, TypeKey &tkey, char *fldnames );
public     :                  OPAImpExp             logical IsBasedOn (char *strnames );
public     : static           OPAImpExp             logical __cdecl IsPathNode (char *prop_path );
public     : static           OPAImpExp             logical __cdecl IsPropertyPath (char *prop_path );
public     :                  OPAImpExp             logical IsUndefinedMember (char *prop_names );
public     : static           OPAImpExp             logical __cdecl IsViewPath (char *prop_path );
public     :                  OPAImpExp             logical NetToInt (void *intinst, char *netinst );
public     :                                        kcb *ProvideKCB (SDB_Key *sdbkey, int32 last_key_number );
public     :                                        kcb *ProvideKCB (char *keyname, int32 keynum );
public     :                                        kcb *ProvideKCB (PropertyHandle &ph, int32 last_key_number );
public     :                                        DBStructDef *ProvideV5StructDef ( );
public     : virtual                                logical RefToDir (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, int16 replnum, int16 copynum );
public     : virtual                                logical RefToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, int16 replnum, int16 copynum );
public     :                                        void RemExpr (OPDecl *expr_decl );
public     :                  OPAImpExp             DBFieldDef *SearchPathField (Dictionary *dictionary, char *fldpath, logical refr_opt, int32 *offsetpt, kcb *w_kcbptr=NULL, smcb **w_typsmcb=NULL );
public     :                                        void SetAccess ( );
public     :                                        logical SetEnumFieldList (Dictionary *dictptr );
public     :                                        logical SetFctTable (Dictionary *dictptr );
public     :                                        logical SetLength (int32 &intpos, int32 &extpos, int32 &netpos );
public     :                                        void SetMemberInfo (int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount );
public     :                  OPAImpExp             DBStructDef *Setup (void *mpool, DBFieldDef *fieldlist, char *idkeynames=NULL, char *keyfieldname=NULL );
public     :                  OPAImpExp             DBStructDef *Setup (Dictionary *dictptr );
public     :                  OPAImpExp             DBStructDef *Setup (Dictionary *dictptr, SDB_BaseStruct **baselist, SDB_Attribute **attrlist, SDB_Reference **refrlist, SDB_Relationship **rshplist, SDB_Key *dbklistptr, int16 keycount=0, int8 w_alignment=0, int32 w_resid=0 );
public     :                  OPAImpExp             DBStructDef *Setup (Dictionary *dictptr, FieldList *flistptr );
public     :                  OPAImpExp             DBStructDef *Setup (Dictionary *dictptr, ENUM_ValueList *enum_list );
public     :                  OPAImpExp             DBStructDef *SetupClient (Dictionary *dictptr );
public     :                                        void SetupCounts ( );
public     :                                        logical SetupKeyDefs (uint16 sys_version=0 );
public     :                                        logical SetupViewOrder (binti *bintiptr );
public     :                  OPAImpExp             MemberInfo &get_attr_info ( );
public     :                  OPAImpExp             MemberInfo &get_base_info ( );
public     :                                        logical get_check_del_empty ( );
public     :                  OPAImpExp             DLL(DBViewPath) *get_from ( );
public     :                  OPAImpExp             char *get_having ( );
public     :                  OPAImpExp             uint32 get_net_length ( );
public     :                  OPAImpExp             MemberInfo &get_refr_info ( );
public     :                  OPAImpExp             MemberInfo &get_rshp_info ( );
public     :                  OPAImpExp             int16 get_sb_number ( );
public     :                  OPAImpExp             int16 get_schema_ver ( );
public     :                  OPAImpExp             char *get_where ( );
public     :                  OPAImpExp             void set_global_identity (logical glob_identity=NO );
public     :                                        void set_prev_struct (DBStructDef *dbstrdef );
public     :                                        void set_resource (DBResource *resptr );
public     :                  OPAImpExp             void set_schema_vers (uint16 schema_vers );
public     :                                        void set_view_struct (DBViewStructDef *vstruct );
public     :                                        logical xCreateViewNodes (ACNode *acnodeptr, binti *bintiptr, void *instptr, node *high_node, logical init_nodes=YES );
public     : virtual          OPAImpExp                  ~DBStructDef ( );
};

#pragma pack()
#endif
