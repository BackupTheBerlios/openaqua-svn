/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    SchemaResources

\brief    


\date     $Date: 2006/08/25 15:17:12,15 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SchemaResources"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sBNFParser.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBViewPath.hpp>
#include  <sDBViewStructDef.hpp>
#include  <sENUM_Value.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sExpressionReference.hpp>
#include  <sOperEnvironment.hpp>
#include  <skcb.hpp>
#include  <sSchemaResources.hpp>


/******************************************************************************/
/**
\brief  CheckParameter - 



\return term - 

\param  ph - 
\param  bdata - 
\param  type - 
\param  generic_type - 
\param  size - 
\param  dimension - Dimension
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckParameter"

logical SchemaResources :: CheckParameter (PropertyHandle &ph, BNFData *bdata, char *type, char *generic_type, uint16 size, uint32 dimension )
{
  PropertyHandle         *bph;
  BNFData                *idata;
  char                    key[ID_SIZE];
  char                    init_value[1025];
  int32                   ref_level = 0;
  int                     index     = 0;
  int                     last      = 0;
  logical                 term      = NO;
BEGINSEQ
// declarator := [ref_symbol(*)] identifier [fixed_array_size(*)] [assigned_value] [attr_ext_decl]
  
  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  SDBEV2(key,ID_SIZE)
  
  if ( !(bph = ph.GetBaseProperty()) )               LEAVESEQ
  if ( !bph->Get(Key(key)) )                         LEAVESEQ 
  
  *init_value = 0;
  if ( idata = bdata->GetElement("assigned_value") )
    strcpy(init_value,idata->GetElement("operand")->StringValue());
    
  if ( *bph->GPH("ddetype") != type          ||
       *bph->GPH("ddegent") != generic_type  ||
       bph->GetInt("ddedim") != dimension       )    SDBERR(445)
       
  if ( (*init_value && !bph->GPH("initialize")->IsTrue()) ||
       (!*init_value && bph->GPH("initialize")->IsTrue())   )
                                                     SDBERR(445)
  if ( *init_value && strcmp(init_value,bph->GetString("ddeinit"))  )
                                                     SDBERR(445)
  
  if ( ref_level = ((BNFExpData *)bdata)->GetReferenceLevel(index) )
  {
    if ( *bph->GPH("reference_level")  != ref_level )SDBERR(445)
    else                                             LEAVESEQ
  }
    
  if ( bph->GetInt("ddesize") != size )              SDBERR(445)

RECOVER
  SDBError().DisplayMessage();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateBaseCollection - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseCollection"

logical SchemaResources :: CreateBaseCollection (DBFieldDef *fielddef, BNFData *bdata )
{
  logical                 term = NO;
// base_collection       := based_on base_path
// base_path             := extent_name | property_extension(*)
// extent_name           := identifier
// property_extension    := '.' identifier
 
  fielddef->SetExtent(bdata->GetElement("base_path")->StringValue());

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseCollection"

logical SchemaResources :: CreateBaseCollection (PropertyHandle &ph, BNFData *bdata )
{
  logical                 term = NO;

// base_collection       := based_on base_path
// base_path             := extent_name | property_extension(*)
// extent_name           := identifier
// property_extension    := '.' identifier
 
  *ph.GPH("ddeext") = bdata->GetElement("base_path")->StringValue();

  return(term);

}

/******************************************************************************/
/**
\brief  CreateBaseType - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseType"

logical SchemaResources :: CreateBaseType (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef )
{
  BNFData                *etypspc;
  BNFData                *declarator = NULL;
  char                    key[ID_SIZE];
  char                    type[ID_SIZE];
  logical                 virt_opt = NO;
  logical                 unicode  = NO;
  ODC_Privilege           privilege = ODC_undefined;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// base_type         := [base_option(*)] extended_type_spec [base_declarator]
// base_declarator   := identifier [col_ext_rel(*)] 

  strdef->IncreaseBaseCount(1);
  
  etypspc = bdata->GetElement("extended_type_spec");  
  if ( GetTypeSpec(fielddef,etypspc,NO) )             ERROR
    
  if ( declarator = bdata->GetElement("base_declarator") ) 
    gvtxstb(key,declarator->GetElement(0)->StringValue(),sizeof(key));
  else
    gvtxstb(key,type,sizeof(key));
  SDBEV2(key,ID_SIZE)  
  
  if ( declarator && declarator->GetElement(1) )
    CreateCollectionExtensions(fielddef,declarator,strdef,1);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseType"

logical SchemaResources :: CreateBaseType (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *ctypspc;
  BNFData                *base_option;
  BNFData                *declarator = NULL;
  char                    key[ID_SIZE];
  char                    type[ID_SIZE];
  char                    generic_type[ID_SIZE];
  int32                   dimension;
  uint32                  size;
  int16                   precision;
  logical                 virt_opt = NO;
  logical                 unicode  = NO;
  ODC_Privilege           privilege = ODC_undefined;
  int                     index = 0;
  logical                 term  = NO;
BEGINSEQ
// base_type         := [base_option(*)] extended_type_spec [base_declarator]
// base_declarator   := identifier [col_ext_rel(*)] 

  ctypspc = bdata->GetElement("extended_type_spec");  
  if ( GetTypeSpec(ctypspc,type,generic_type,size,dimension,precision,unicode) )
                                                     ERROR
  if ( declarator = bdata->GetElement("base_declarator") ) 
    gvtxstb(key,declarator->GetElement(0)->StringValue(),sizeof(key));
  else
    gvtxstb(key,type,sizeof(key));
  SDBEV2(key,ID_SIZE) 
  
  ph.Provide(Key(key));
  *ph.GPH("ddetype") = type;
  *ph.GPH("ddegent") = generic_type;
  *ph.GPH("ddesize") = 0;
  *ph.GPH("ddedim")  = (int32)dimension;
  *ph.GPH("ddeprec") = 0;
  *ph.GPH("ddestat") = NO;
 
  *ph.GPH("ddetrans") = NO;
  
  while ( (base_option = bdata->GetElement(index++)) && 
          base_option->IsSymbol("base_option")               )
  {
    if ( base_option->IsSymbol("_virtual") )
      *ph.GPH("ddevirt") = YES;
    if ( base_option->IsSymbol("priv_option") )
      *ph.GPH("ddeprv") = (int32)GetPrivilege(base_option->GetElement(0));
  }
 
  if ( declarator && declarator->GetElement(1) )
    CreateCollectionExtensions(ph,declarator,1);

  ph.Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCategories - 



\return is_string - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCategories"

logical SchemaResources :: CreateCategories (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *category;
  int                     index = 0;
  logical                 is_string = NO;
BEGINSEQ
// category_list := category_spec [category_ext(*)]
// category_ext  := ',' category_spec

  if ( !bdata )                                      LEAVESEQ
  category = bdata->GetElement(0);
  
  while ( category )  
  {
    if ( CreateCategory(ph,category) )
      is_string = YES;
    if ( category = bdata->GetElement(++index) )
      category = category->GetElement(1);
  }
ENDSEQ
  return(is_string);
}

/******************************************************************************/
/**
\brief  CreateCategory - 



\return is_string - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCategory"

logical SchemaResources :: CreateCategory (PropertyHandle &ph, BNFData *bdata )
{
  char                    name[ID_SIZE];
  BNFData                *vname;
  char                   *vstring;
  logical                 is_string = YES;

BEGINSEQ
// category_spec := cat_name [ cat_condition ]
// cat_condition := ':' operand
// cat_name      := identifier | string | number

  if ( !bdata )                                      LEAVESEQ
    
  vname = bdata->GetElement(0);
  
  if ( vname->IsSymbol("std_integer") )
    is_string = NO;
  
  if ( vname->IsSymbol("std_string") )
    vstring = vname->GetStringConstant();
  else
    vstring = vname->StringValue();

  gvtxstb(name,vstring,ID_SIZE);
  ph.Provide(name);
  if ( !is_string )
    *ph.GPH("value") = vstring;
    
  if ( bdata = bdata->GetElement("cat_condition") )
    *ph.GPH("condition") = bdata->GetElement(1)->StringValue();
ENDSEQ
  return(is_string);
}

/******************************************************************************/
/**
\brief  CreateCollection - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
\param  rel_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCollection"

logical SchemaResources :: CreateCollection (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef, logical rel_opt )
{
  DBFieldDef             *fd;
  BNFData                *dim;
  logical                 term = NO;
BEGINSEQ
// ref/rel_delarator     := collection [col_ext_ref/rel(*)] 
// collection            := identifier [col_dimension] [assigned_value]
// col_dimension         := '[' std_integer ']'                            

  fd = ((DBFieldList *)strdef->smcbfmcl)->CreateField();
  *fd = *fielddef;
  if ( rel_opt )
    strdef->IncreaseRshpCount(1);
  else
    strdef->IncreaseRefrCount(1);
    
  gvtxstb(fd->fmcbname,bdata->GetElement("identifier")->StringValue(),ID_SIZE);
  SDBEV2(fd->fmcbname,ID_SIZE)  
  
  if ( dim = bdata->GetElement("col_dimension") )
  {
    if ( !memcmp(fd->fmcbtype,"STRING ",7) )
    {
      fd->fmcbdim  = 1;
      fd->fmcbsize = dim->GetElement(1)->IntValue();
      gvtxstb(fd->fmcbtype,"MEMO",ID_SIZE);
    }
    else
      fd->fmcbdim  = dim->GetElement(1)->IntValue();
  }
  
  SetInitValue(fd,bdata,strdef);
  if ( CreateCollectionExtensions(fd,bdata,strdef,1) )      
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  type - 
\param  generic_type - 
\param  size - 
\param  dimension - Dimension
\param  precision - Precision
\param  unicode - 
\param  privilege_w - 
\param  virtual_w - 
\param  static_w - 
\param  transient_w - 
\param  guid_w - 
\param  weak_w - 
\param  update_w - 
\param  mkey_w - 
\param  create_w - 
\param  owner_w - 
\param  dependent_w - 
\param  secondary_w - 
\param  shared_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCollection"

logical SchemaResources :: CreateCollection (PropertyHandle &ph, BNFData *bdata, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w, logical virtual_w, logical static_w, logical transient_w, logical guid_w, logical weak_w, logical update_w, logical mkey_w, logical create_w, logical owner_w, logical dependent_w, logical secondary_w, logical shared_w )
{
  BNFData                *dim;
  char                    key[ID_SIZE];
  int32                   ref_level = 0;
  int                     index     = 0;
  int                     last      = 0;
  logical                 term = NO;
BEGINSEQ
// ref/rel_delarator     := collection [col_ext_ref/rel(*)] 
// collection            := identifier [col_dimension] [assigned_value]
// col_dimension         := '[' std_integer ']'                                // ODABA extension

  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  SDBEV2(key,ID_SIZE) 
  
  ph.Provide(Key(key));
  InitReference(ph,type,generic_type,size,dimension,precision,unicode,privilege_w,virtual_w,
                static_w,transient_w,guid_w,weak_w,update_w,mkey_w,create_w,owner_w,shared_w);
  
  if ( dependent_w )
    *ph.GPH("depend") = YES;
  if ( secondary_w )
    *ph.GPH("ddesecr") = YES;
  
  if ( dim = bdata->GetElement("col_dimension") )
  {
    if ( !strcmp(type,"STRING") )
    {
      *ph.GPH("ddedim")  = 1;
      *ph.GPH("ddesize") = dim->GetElement(1)->IntValue();
      *ph.GPH("ddetype") = "MEMO";
    }
    else
      *ph.GPH("ddedim") = dim->GetElement(1)->IntValue();
  }
  else
  {
    *ph.GPH("ddedim") = 1;
    if ( !strcmp(generic_type,"LIST") || 
         !strcmp(generic_type,"BAG") || 
         !strcmp(generic_type,"SET")     )
    {
      *ph.GPH("ddedim") = 0;
      *ph.GPH("ddegent") = "";
    }
  }

  SetInitValue(ph,bdata);
  
  if ( CreateCollectionExtensions(ph,bdata,1) )      ERROR

  ph.Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCollectionExtensions - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCollectionExtensions"

logical SchemaResources :: CreateCollectionExtensions (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef, int32 index )
{
  BNFData                *col_ext_rel;
  logical                 term = NO;
// ... col_ext_rel(*)
// col_ext_rel := inverse_spec | base_collection | order_keys | attr_ext_decl
 
  while ( (col_ext_rel = bdata->GetElement(index++)) && 
          col_ext_rel->IsSymbol("col_ext_rel")               )
    switch ( col_ext_rel->GetSymbolCode("inverse_spec","base_collection","order_keys","attr_ext_decl") )
    {
      case 1 : CreateInverse(fielddef,col_ext_rel->GetElement("inverse_spec"));           break;
      case 2 : CreateBaseCollection(fielddef,col_ext_rel->GetElement("base_collection")); break;
      case 3 : CreateOrderKeys(fielddef,col_ext_rel->GetElement("order_keys"));           break;
      case 4 : SetMemberExtensions(fielddef,col_ext_rel->GetElement("attr_ext_decl"),strdef);   break;
    }

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCollectionExtensions"

logical SchemaResources :: CreateCollectionExtensions (PropertyHandle &ph, BNFData *bdata, int32 index )
{
  BNFData                *col_ext_rel;
  logical                 term = NO;
// ... col_ext_rel(*)
// col_ext_rel := inverse_spec | base_collection | order_keys | attr_ext_decl
 
  while ( (col_ext_rel = bdata->GetElement(index++)) && 
          col_ext_rel->IsSymbol("col_ext_rel")               )
    switch ( col_ext_rel->GetSymbolCode("inverse_spec","base_collection","order_keys","attr_ext_decl") )
    {
      case 1 : CreateInverse(ph,col_ext_rel->GetElement("inverse_spec"));           break;
      case 2 : CreateBaseCollection(ph,col_ext_rel->GetElement("base_collection")); break;
      case 3 : CreateOrderKeys(ph,col_ext_rel->GetElement("order_keys"));           break;
      case 4 : SetMemberExtensions(ph,col_ext_rel->GetElement("attr_ext_decl"));    break;
    }
  return(term);
}

/******************************************************************************/
/**
\brief  CreateEnumerator - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  vlist - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEnumerator"

logical SchemaResources :: CreateEnumerator (ENUM_ValueList *vlist, BNFData *bdata )
{
  int                     num = AUTO;
  char                    key[257];
  char                   *typenames;
  int16                   value;
  BNFData                *enumval;
  BNFData                *reftyp;
  logical                 term = NO;
// enumerator := identifier [ref_type] [ enum_value ] [',']
  
  gvtxbts(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
    
  if ( enumval = bdata->GetElement("enum_value") )
    value = enumval->GetElement(1)->IntValue(); 
  else
    value = 0;
  if ( reftyp = bdata->GetElement("ref_type") )
    typenames = reftyp->GetElement(1)->StringValue();

  ENUM_Value  eval(value,key,typenames,NULL,NULL,NULL);
  vlist->AddValue(&eval);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEnumerator"

logical SchemaResources :: CreateEnumerator (PropertyHandle &ph, BNFData *bdata )
{
  int                     num = AUTO;
  char                    key[256];
  BNFData                *enumval;
  BNFData                *reftyp;
  logical                 term = NO;
BEGINSEQ
// enumerator := identifier [ref_type] [ enum_value ] [enum_def] [',']
// ref_type   := '(' scoped_name ')'
// enum_value := assign_op number

  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  ph.Provide(Key(key));                                 SDBCERR
    
  *ph.GPH("name") = bdata->GetElement("identifier")->StringValue();
  
  if ( reftyp = bdata->GetElement("ref_type") )
    LoadTypeReference(reftyp->GetElement("scoped_name"),
                      *ph.GPH("scope"),*ph.GPH("type"));
                      
  if ( enumval = bdata->GetElement("enum_value") )
    *ph.GPH("__AUTOIDENT") = enumval->GetElement(1)->IntValue();
  
  if ( bdata = bdata->GetElement("enum_def") )
    LoadEnumerators(*ph.GPH("values"),bdata);

  ph.Save();                                         SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExtent - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtent"

logical SchemaResources :: CreateExtent (DBStructDef *strdef, BNFData *bdata )
{
  DBExtend               *dbext     = NULL;
  BNFData                *options;
  logical                 allocated = NO;
  int32                   index_ref = 0;
  int8                    maxalign  = 0;
  logical                 term = NO;
BEGINSEQ
// extent_def       := identifier [rel_option(*)] [extent_option(*)]
// extent_option    := order_keys | super_sets | sub_sets

  if ( !bdata->IsSymbol("extent_def") )                 ERROR
  
  if ( !(dbext = dictionary->GetExtendDef(bdata->GetElement("identifier")->StringValue())) )
  {
    allocated = YES;
    dbext = new DBExtend();
    dbext->set_acctype(AT_ODABA);
    dbext->set_mb_number(0);
    gvtxstb(dbext->fmcbname,bdata->GetElement("identifier")->StringValue(),ID_SIZE);
  }
  SDBEV2(dbext->fmcbname,ID_SIZE) 
  memcpy(dbext->fmcbtype,strdef->smcbname,ID_SIZE);
  dbext->fmcbrlev = R_REFR;
  dbext->fmcbesu(strdef,0,0,maxalign);
  dbext->set_owning(YES);         
  dbext->fmcbvirt = YES;          // transient (osi) extent
  
  if ( GetColOptions(dbext,bdata,++index_ref) )      ERROR
  
  if ( allocated )
    dictionary->AddExtendDef(dbext);
  allocated = NO;
  
  while ( (options = bdata->GetElement(index_ref++)) && options->IsSymbol("extent_option") )
  {
    switch ( options->GetSymbolCode("order_keys","super_sets","sub_sets") )
    {
      case 1 : CreateOrderKeys(dbext,options->GetElement(0));
               break;
      case 2 : CreateSuperSets(dbext,options->GetElement(0));
               break;
      case 3 : CreateSubSets(dbext,options->GetElement(0));
               break;
    }
  }
  if ( dbext->get_base_extend()->GetCount() > 0 )
    dbext->set_owning(NO);

RECOVER
  if ( allocated )
    delete dbext;
  dbext = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtent"

logical SchemaResources :: CreateExtent (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *options;
  char                    key[ID_SIZE];
  logical                 mkey_opt  = YES;
  logical                 weak_opt  = NO;
  logical                 update_opt= YES;
  logical                 guid_opt  = NO;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// extent_def       := identifier [rel_option(*)] [extent_option(*)]
// extent_option    := order_keys | super_sets | sub_sets

  if ( !bdata->IsSymbol("extent_def") )                 ERROR
  
  PH(ph,extents)  // lokale extents des name spaces
  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  SDBEV2(key,ID_SIZE) 
   
  extents.Provide(Key(key));
  
  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("rel_option") )
  {
    switch ( options->GetElement(0)->GetSymbolCode("guid","weak_typed","update","multiple_key") )
    {
      case 1 : guid_opt = YES;              break;
      case 2 : weak_opt = YES;              break;
      case 3 : update_opt = YES;            break;
      case 4 : mkey_opt = YES;              break;
    }
  }
  
  InitReference(extents,ph.GetString("sys_ident"),NULL,0,0,0,NO,ODC_public,NO,
                YES,NO,guid_opt,weak_opt,update_opt,mkey_opt,YES,YES);

  while ( (options = bdata->GetElement(index++)) && options->IsSymbol("extent_option") )
  {
    switch ( options->GetSymbolCode("order_keys","super_sets","sub_sets") )
    {
      case 1 : CreateOrderKeys(extents,options->GetElement(0));
               break;
      case 2 : CreateSuperSets(extents,options->GetElement(0));
               break;
      case 3 : CreateSubSets(extents,options->GetElement(0));
               break;
    }
  }
  if ( extents.GPH("sexbase")->GetCount() > 0 )
    *extents.GPH("owning") = NO;
  ph.Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExtentRelation - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  db_ext - 
\param  bdata - 
\param  sub_ext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtentRelation"

logical SchemaResources :: CreateExtentRelation (DBExtend *db_ext, BNFData *bdata, logical sub_ext )
{
  DBExtend               *dbext;
  char                   *extname;
  logical                 term = NO;
// extent_name := identifier

  extname = bdata->GetElement("identifier")->StringValue();
  SDBEV2(extname,UNDEF) 
  
  if ( !(dbext = dictionary->GetExtendDef(extname)) )
  {
    dbext = new DBExtend();
    gvtxstb(dbext->fmcbname,extname,ID_SIZE);
  }
  
  if ( sub_ext )
  {
    db_ext->get_derived_extends()->AddTail(dbext);
    dbext->get_base_extend()->AddTail(db_ext);
    dbext->set_owning(NO);
  }
  else  // base collection/super set
  {
    db_ext->get_base_extend()->AddTail(dbext);
    dbext->get_derived_extends()->AddTail(db_ext);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  owning_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtentRelation"

logical SchemaResources :: CreateExtentRelation (PropertyHandle &ph, BNFData *bdata, logical owning_w )
{
  PropertyHandle         *parent;
  char                    key[ID_SIZE];
  logical                 term = NO;
// extent_name := identifier

  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  SDBEV2(key,ID_SIZE) 
  
  if ( ph.Get(Key(key)) )
  {
    parent = ph.GetParentProperty();
    ph.Copy(*parent,Key(key),REPL_direct);
    ph.GPH("ddeindx")->CopySet(parent->GPH("ddeindx"));
  }
  else
    ph.Add(Key(key));

  if ( !owning_w )
    *ph.GPH("owning") = NO;

  ph.Save(); 

  return(term);
}

/******************************************************************************/
/**
\brief  CreateFunction - 



\return term - 

\param  ph - 
\param  bdata - 
\param  index_ref - 
\param  impl_ident - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFunction"

logical SchemaResources :: CreateFunction (PropertyHandle &ph, BNFData *bdata, int32 &index_ref, BNFData **impl_ident )
{
  BNFData                *mid;
  char                    key[ID_SIZE];
  NString                 skey;
  char                    type[ID_SIZE];
  char                    generic_type[ID_SIZE];
  int32                   dimension = 0;
  uint32                  size = 0;
  int16                   precision = 0;
  ODC_Privilege           privilege = ODC_undefined;
  logical                 virt_opt  = NO;
  logical                 stat_opt  = NO;
  logical                 trans_opt = NO;
  logical                 unicode   = NO;
  logical                 collopt   = NO;
  logical                 term = NO;
BEGINSEQ
// meth_dcl       := .... mtype_ref [ref_symbol(*)] meth_ident ... 
// meth_ident     := ['~'] identifier [ impl_ident ] [cun_op]
// impl_ident     := '.' identifier

  skey = "";
  mid = bdata->GetElement("meth_ident");
  if ( !mid->GetElement(0)->IsSymbol("identifier") )
    skey += '~';
  skey += mid->GetElement("identifier")->StringValue();
  if ( mid->GetElement("cun_op") )
    skey += mid->GetElement("cun_op")->StringValue();
  SDBEV2(skey,UNDEF) 
  
  ph.Provide(Key(gvtxstb(key,skey,sizeof(key))));
  
  index_ref++;                           // ref_symbol
  SetReferenceLevel(ph,bdata,index_ref);
  
  if ( GetTypeSpec(bdata->GetElement("mtype_ref"),type,generic_type,size,dimension,precision,
                   unicode,privilege,virt_opt,stat_opt,trans_opt,collopt) )
                                                     ERROR
  
  InitMember(ph,type,generic_type,size,dimension,precision,unicode,privilege,virt_opt,stat_opt,trans_opt,collopt);
  
  ph.Save();
   
  if ( bdata->GetElement("impl_ident") )
    *impl_ident = bdata->GetElement("impl_ident")->GetElement(1); // identifier

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateFunctionParameter - 



\return term - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFunctionParameter"

logical SchemaResources :: CreateFunctionParameter (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *bdecl;
  char                    key[ID_SIZE+1];
  char                    generic_type[ID_SIZE];
  char                    type[ID_SIZE];
  int32                   dimension = 0;
  uint32                  size = 0;
  int16                   precision = 0;
  ODC_Privilege           privilege = ODC_undefined;
  logical                 virt_opt  = NO;
  logical                 stat_opt  = NO;
  logical                 trans_opt = NO;
  logical                 collopt   = NO;
  logical                 unicode   = NO;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// param_dcl             := [param_attribute] simple_type_spec declarator
// param_attribute       := in | out | inout

  if ( GetTypeSpec(bdata->GetElement("simple_type_spec"),type,generic_type,size,dimension,precision,unicode,
                   privilege,virt_opt,stat_opt,trans_opt,collopt) )
                                                     ERROR
  
  bdecl = bdata->GetElement("declarator");
  if ( CheckParameter(ph,bdecl,type,generic_type,size,dimension) )
  {
    strncpy(key,bdecl->GetElement("identifier")->StringValue(),ID_SIZE);
    gvtxstb(key,key,ID_SIZE);
    ph.Provide(Key(key));
  }
  else  
    CreateMember(ph,bdecl,type,generic_type,size,dimension,precision,unicode,
                    privilege,virt_opt,stat_opt,trans_opt,collopt);
  
  if ( !ph.GPH("ddeinit")->IsEmpty() )
    *ph.GPH("initialize") = YES;
  
/* in/out should be set here
  if ( bdata = bdata->GetElement("param_attribute") )
    switch ( bdata->GetSymbolCode("in","inout","out") ) 
    {
      case 1 : *ph.GPH("outopt") = "OO_output";       break;
      case 2 : *ph.GPH("outopt") = "OO_inout";        break;
      case 3 : *ph.GPH("outopt") = "OO_input";        break;
      default : ;
    }
*/

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateGrouping - 



\return term - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGrouping"

logical SchemaResources :: CreateGrouping (PropertyHandle &ph, BNFData *bdata )
{
  logical                 is_string = NO;
  PropertyHandle         *vph;
  logical                 term = NO;
BEGINSEQ
// group_spec    := group_by '(' categories ')'                   // automatically generates 'value' and 'partition' property in the structure
// categories    := category_list | operand
  
  if ( !bdata )                                      LEAVESEQ
  if ( !(bdata = bdata->GetElement("categories")) )  SDBERR(99)
    
  ph.Provide(FIRST_INSTANCE);
  switch ( bdata->GetSymbolCode("category_list","operand") )
  {
    case 1 : is_string = CreateCategories(*ph.GPH("values"),bdata->GetElement(0));
                                                                   break;
    case 2 : *ph.GPH("expression") = bdata->StringValue();         break;
  }

  vph = ph.GetParentProperty();

  // kreate default key
  PH(vph,smcepsmc)
  
  PropertyHandle  ik_value("ik_value");
  smcepsmc.Provide(ik_value);
  *vph->GPH("smceiksm") = "ik_value";
  
  PH(&smcepsmc,components)
  {
    PropertyHandle  value("value");
    components.Provide(value);
  }
  
  // create default value attribute
  PH(vph,smcepdde)
  {
    PropertyHandle  value("value");
    smcepdde.Provide(value);
  }
  if ( is_string )
    InitMember(smcepdde,"CHAR",NULL,40,1,0,NO);
  else
    InitMember(smcepdde,"INT",NULL,10,1,0,NO);

  // create default partition relationship
  PH(vph,smcershp)
  {
    PropertyHandle  partition("partition"); 
    smcershp.Provide(partition);
  }
  InitReference(smcershp,"VOID",NULL,UNDEF,UNDEF,UNDEF,NO,
                ODC_protected,NO,NO,YES,NO,NO,NO,NO,YES,NO,NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateInheritance - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInheritance"

logical SchemaResources :: CreateInheritance (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *base_type;
  DBFieldDef             *fielddef;
  int                     index = 0;
  logical                 term = NO;
// extends_spec          := extends base_types                            // handled as based_on inheritance in ODABA
// inheritance_spec      := ':' base_types
// base_types            := base_type [base_type_suc(*)]
// base_type_suc         := ',' base_type
  
  fielddef = (DBFieldDef *)strdef->smcbfmcl->srtfad();
  bdata = bdata->GetElement(1);  // base_types
  CreateBaseType(fielddef,bdata->GetElement(0),strdef);
  
  while ( base_type = bdata->GetElement(++index) )
  {
    fielddef = (DBFieldDef *)strdef->smcbfmcl->srtfad();
    base_type = base_type->GetElement(1);
    CreateBaseType(fielddef,base_type,strdef);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInheritance"

logical SchemaResources :: CreateInheritance (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *base_type;
  int                     index = 0;
  logical                 term  = NO;
// extends_spec          := extends base_types                            // handled as based_on inheritance in ODABA
// inheritance_spec      := ':' base_types
// base_types            := base_type [base_type_suc(*)]
// base_type_suc         := ',' base_type
  
  bdata = bdata->GetElement(1);  // base_types
  PH(&ph,smcebase)
  CreateBaseType(smcebase,bdata->GetElement(0));
  
  while ( base_type = bdata->GetElement(++index) )
  {
    base_type = base_type->GetElement(1);
    CreateBaseType(smcebase,base_type);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  CreateInverse - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInverse"

logical SchemaResources :: CreateInverse (DBFieldDef *fielddef, BNFData *bdata )
{
  BNFData                *identifier;
  logical                 term = NO;
// inverse_spec          := inverse inverse_traversal_path
// inverse_traversal_path:= identifier [typed_identifier]
// typed_identifier      := '::' identifier
 
  bdata = bdata->GetElement(1);
  if ( bdata->GetElement(1) )
    identifier = bdata->GetElement(1)->GetElement("identifier");
  else
    identifier = bdata->GetElement(0);

  fielddef->set_inverse_name(identifier->StringValue());
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInverse"

logical SchemaResources :: CreateInverse (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *identifier;
  logical                 term = NO;

// inverse_spec          := inverse inverse_traversal_path
// inverse_traversal_path:= identifier [typed_identifier]
// typed_identifier      := '::' identifier
 
  bdata = bdata->GetElement(1);
  if ( bdata->GetElement(1) )
    identifier = bdata->GetElement(1)->GetElement("identifier");
  else
    identifier = bdata->GetElement(0);
  
  *ph.GPH("ddeinv") = identifier->StringValue();
  return(term);
}

/******************************************************************************/
/**
\brief  CreateKey - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKey"

logical SchemaResources :: CreateKey (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *components;
  BNFData                *suc_comp;
  char                   *keyname;
  kcb                    *kcbptr;
  int                     index     = 0;
  logical                 term = NO;
BEGINSEQ
// key_def               := [ident_key] identifier [key_components_ext]
// key_components_ext    := key_components | key_components_odmg 
// key_components_odmg   := '(' key_components ')'
// key_components        := key_component [key_component_suc(*)]
// key_component_suc     := ',' key_component

  if ( !bdata->IsSymbol("key_def") )                      ERROR
  
  keyname = bdata->GetElement("identifier")->StringValue();
  SDBEV2(keyname,UNDEF) 
  
  kcbptr = new kcb(keyname,strdef);
  strdef->smcbidky = kcbptr;
  
  if ( components = bdata->GetElement("key_components_ext") )
  {
    if ( components->IsSymbol("key_components_odmg") )
      components = components->GetElement(0)->GetElement(1);
    else
      components = components->GetElement(0);
    kcbptr->CreateFieldList(components->GetElementCount(),NO);
    CreateKeyComponent(kcbptr,components->GetElement(0));
    while ( suc_comp = components->GetElement(++index) )
      CreateKeyComponent(kcbptr,suc_comp->GetElement(1));
  } 


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKey"

logical SchemaResources :: CreateKey (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *components;
  BNFData                *suc_comp;
  char                    key[ID_SIZE];
  int                     index     = 0;
  logical                 term = NO;
BEGINSEQ
// key_def               := [ident_key] identifier [key_components_ext]
// key_components_ext    := key_components | key_components_odmg 
// key_components_odmg   := '(' key_components ')'
// key_components        := key_component [key_component_suc(*)]
// key_component_suc     := ',' key_component

  if ( !bdata->IsSymbol("key_def") )                      ERROR
  
  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  SDBEV2(key,ID_SIZE) 
  
  PH(&ph,smcepsmc)
  smcepsmc.Provide(Key(key));
  
  if ( bdata->GetElement("ident_key") )
    *ph.GPH("smceiksm") = key;
  
  if ( components = bdata->GetElement("key_components_ext") )
  {
    if ( components->IsSymbol("key_components_odmg") )
      components = components->GetElement(0)->GetElement(1);
    else
      components = components->GetElement(0);
    CreateKeyComponent(smcepsmc,components->GetElement(0));
    while ( suc_comp = components->GetElement(++index) )
      CreateKeyComponent(smcepsmc,suc_comp->GetElement(1));
  } 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateKeyComponent - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  kcbptr - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyComponent"

logical SchemaResources :: CreateKeyComponent (kcb *kcbptr, BNFData *bdata )
{
  BNFData                *options;
  char                   *keypath;
  int32                   index = 0;
  logical                 ic = NO;
  logical                 desc = NO;
  logical                 term = NO;
// key_component         := member_path [component_option(*)]
// member_path           := identifier [property_extension(*)]
// component_option      := ignore_case | descending

  keypath = bdata->GetElement("member_path")->StringValue();
  SDBEV2(keypath,UNDEF) 
  
  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("component_option") )
  {
    switch ( options->GetSymbolCode("ignore_case","descending") )
    {
      case 1 : ic = YES;                 break;
      case 2 : desc = YES;               break;
    }
  }
  kcbptr->kcbfad(keypath,UNDEF,ic,desc);
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  owning_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyComponent"

logical SchemaResources :: CreateKeyComponent (PropertyHandle &ph, BNFData *bdata, logical owning_w )
{
  BNFData                *options;
  char                    key[256];
  int32                   index = 0;
  logical                 term = NO;
// key_component         := member_path [component_option(*)]
// member_path           := identifier [property_extension(*)]
// component_option      := ignore_case | descending

  memset(key,0,sizeof(key));
  strncpy(key,bdata->GetElement("member_path")->StringValue(),sizeof(key)-1);
  SDBEV2(key,ID_SIZE) 
  
  PH(&ph,components)
  components.Provide(Key(key));

  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("component_option") )
    switch ( options->GetSymbolCode("ignore_case","descending") )
    {
      case 1 : *components.GPH("ignore_case") = YES; break;
      case 2 : *components.GPH("descending")  = YES; break;
    }
  return(term);
}

/******************************************************************************/
/**
\brief  CreateMember - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  dbfieldlist - 
\param  strdef - 
\param  index_ref - 
\param  setup_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMember"

logical SchemaResources :: CreateMember (DBFieldDef *fielddef, BNFData *bdata, DBFieldList *dbfieldlist, DBStructDef *strdef, int32 &index_ref, logical setup_opt )
{
  int8                    maxalign = 0;
  BNFData                *avalue   = NULL;
  BNFData                *farray;
  int32                   index = 0;
  DBFieldDef             *fd;
  logical                 term = NO;
BEGINSEQ
// declarator     := [ref_symbol(*)] identifier [fixed_array_size(*)] [assigned_value] [attr_ext_decl]
// parm_spec      := ... [ref_symbol(*)] identifier [fixed_array_size(*)] assigned_value

  if ( dbfieldlist )
  {
    fd = dbfieldlist->CreateField();
    *fd = *fielddef;
    strdef->IncreaseAttrCount(1);
  }
  else 
    fd = fielddef;
    
  if ( SetReferenceLevel(fd,bdata,index_ref) )        ERROR
  
  gvtxstb(fd->fmcbname,bdata->GetElement("identifier")->StringValue(),ID_SIZE);
  SDBEV2(fd->fmcbname,ID_SIZE)  
  
  while ( farray = bdata->GetElement(++index) )
    if ( farray->IsSymbol("fixed_array_size") )
      break;
  if ( farray )
    fd->fmcbdim = ((BNFExpData *)farray)->GetDimension(index);
    
  SetInitValue(fielddef,bdata,strdef);
  if ( (avalue = bdata->GetLastElement()) &&
       avalue->IsA("attr_ext_decl")        )
    SetMemberExtensions(fielddef,avalue,strdef);
      
  if ( setup_opt )
  {
    if ( fd->SetupType(dictionary,NO) )          ERROR
    fd->fmcbesu(fd->fmcbsmcb,0,0,maxalign);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
\param  type - 
\param  generic_type - 
\param  size - 
\param  dimension - Dimension
\param  precision - Precision
\param  unicode - 
\param  privilege_w - 
\param  virtual_w - 
\param  static_w - 
\param  transient_w - 
\param  collopt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMember"

logical SchemaResources :: CreateMember (PropertyHandle &ph, BNFData *bdata, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w, logical virtual_w, logical static_w, logical transient_w, logical collopt_w )
{
  BNFData                *array_size;
  char                    key[ID_SIZE];
  int32                   ref_level = 0;
  int                     index     = 0;
  logical                 first     = YES;
  logical                 term      = NO;

BEGINSEQ
// declarator := [ref_symbol(*)] identifier [fixed_array_size(*)] [assigned_value] [attr_ext_decl]

  gvtxstb(key,bdata->GetElement("identifier")->StringValue(),sizeof(key));
  SDBEV2(key,ID_SIZE) 
  
  ph.Provide(Key(key));
  InitMember(ph,type,generic_type,size,dimension,precision,unicode,privilege_w,virtual_w,static_w,transient_w,collopt_w);
  
  SetReferenceLevel(ph,bdata,index);
    
  index++;  // skip identifier
  while ( (array_size = bdata->GetElement(index)) && 
           array_size->IsSymbol("fixed_array_size") )
  {
    if ( !first )                                    SDBERR(442)
    *ph.GPH("ddedim") = atoi(array_size->GetElement("std_integer")->StringValue());
    first = NO;
    index++;
  }
  
  SetInitValue(ph,bdata); 
  SetMemberExtensions(ph,bdata);

  ph.Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateMembers - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMembers"

logical SchemaResources :: CreateMembers (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *decl_suc;
  DBFieldDef              fielddef;
  int                     index     = 0;
  int32                   index_ref = 0;
  logical                 global    = NO;
  logical                 term = NO;
BEGINSEQ
// attr_spec      := [_global] type_ref declarators
// declarators    := declarator [ declarator_suc(*) ] 
// declarator_suc := ',' declarator

  if ( bdata->GetElement(0)->IsSymbol("_global") )
  {
    global = YES;
    index_ref++;
  }

  if ( GetTypeSpec(&fielddef,bdata->GetElement(index_ref++),NO) )
                                                     ERROR
  bdata = bdata->GetElement("declarators");  
  CreateMember(&fielddef,bdata->GetElement(0),(DBFieldList *)strdef->smcbfmcl,strdef,index_ref,NO);
  
  while ( decl_suc = bdata->GetElement(++index) )
    CreateMember(&fielddef,decl_suc->GetElement(1),(DBFieldList *)strdef->smcbfmcl,strdef,index_ref,NO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMembers"

logical SchemaResources :: CreateMembers (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *decl_suc;
  BNFData                *type_spec;
  char                    type[ID_SIZE];
  char                    generic_type[ID_SIZE];
  int32                   dimension;
  uint32                  size;
  int16                   precision;
  ODC_Privilege           privilege = ODC_undefined;
  logical                 virt_opt  = NO;
  logical                 stat_opt  = NO;
  logical                 trans_opt = NO;
  logical                 unicode   = NO;
  logical                 collopt   = NO;
  int                     index = 0;
  int32                   index_ref = 0;
  logical                 global = NO;
  logical                 term  = NO;
BEGINSEQ
// member         := [_global] type_spec declarators ';'
// attr_spec      := type_ref declarators
// declarators    := declarator [ declarator_suc(*) ]
// declarator_suc := ',' declarator

  if ( bdata->GetElement(0)->IsSymbol("_global") )
  {
    global = YES;
    index_ref = 1;
  }
  
  type_spec = bdata->GetElement(0)->GetElement(0);  // should be simple_type_spec
  
  if ( GetTypeSpec(type_spec,type,generic_type,size,dimension,precision,unicode,
                   privilege,virt_opt,stat_opt,trans_opt,collopt) )
                                                     ERROR
  bdata = bdata->GetElement(1);
  CreateMember(ph,bdata->GetElement(0),type,generic_type,size,dimension,precision,unicode,
                  privilege,virt_opt,stat_opt,trans_opt,collopt);
  
  while ( decl_suc = bdata->GetElement(++index) )
    CreateMember(ph,decl_suc->GetElement(1),type,generic_type,size,dimension,precision,unicode,
                    privilege,virt_opt,stat_opt,trans_opt,collopt);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateOrderKey - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOrderKey"

logical SchemaResources :: CreateOrderKey (DBFieldDef *fielddef, BNFData *bdata )
{
  char                    key[ID_SIZE];
  BNFData                *index_option;
  int32                   index   = 0;
  SDB_SET                 settyp  = SET_SMAL;
  logical                 uniopt  = NO;
  logical                 tempopt = NO;
  logical                 empopt  = NO;
  logical                 term = NO;
// index_spec      := key_name [index_option(*)]
// key_name        := identifier
// index_option    := unique | supress_empty | temporary

  gvtxstb(key,bdata->GetElement("key_name")->StringValue(),sizeof(key));
  SDBEV3(key,ID_SIZE) 
  
  if ( fielddef->fmcbdim || fielddef->fmcbdim > 1000 )
    settyp = SET_LARG;  

  while ( index_option = bdata->GetElement(++index) )
    switch( index_option->GetSymbolCode("unique","supress_empty","temporary") )
    {
      case 1 : uniopt = YES;     break;
      case 2 : empopt = YES;     break;
      case 3 : tempopt = YES;    break;
    }

  fielddef->CreateIndex(key,uniopt,tempopt,NO,empopt,settyp);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
\param  max_size - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOrderKey"

logical SchemaResources :: CreateOrderKey (PropertyHandle &ph, BNFData *bdata, int8 max_size )
{
  char                    key[ID_SIZE];
  BNFData                *index_option;
  int32                   index = 0;
  logical                 term = NO;
// index_spec      := key_name [index_option(*)]
// key_name        := identifier
// index_option    := unique | supress_empty | temporary

  gvtxstb(key,bdata->GetElement("key_name")->StringValue(),sizeof(key));
  SDBEV3(key,ID_SIZE) 
  
  ph.Provide(Key(key));
  *ph.GPH("skdunique") = NO;
  *ph.GPH("no_empty") = NO;
  *ph.GPH("skdtemp") = NO;
  *ph.GPH("skdtype") = SET_LARG;
  if ( max_size && max_size < 100 )
    *ph.GPH("skdtype") = SET_SMAL;  

  while ( index_option = bdata->GetElement(++index) )
    switch( index_option->GetSymbolCode("unique","supress_empty","temporary") )
    {
      case 1 : *ph.GPH("skdunique") = YES;  break;
      case 2 : *ph.GPH("no_empty") = YES;   break;
      case 3 : *ph.GPH("skdtemp") = YES;    break;
    }

  ph.Save();
  return(term);
}

/******************************************************************************/
/**
\brief  CreateOrderKeys - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOrderKeys"

logical SchemaResources :: CreateOrderKeys (DBFieldDef *fielddef, BNFData *bdata )
{
  int                     index = 0;
  BNFData                *index_spec_suc;
  logical                 term = NO;
// order_keys      := ordered_by '(' index_specs ')'                        // ODABA extension
// index_specs     := index_spec [index_spec_suc(*)]
// index_spec_suc  := ',' index_spec

  bdata = bdata->GetElement("index_specs");
  
  CreateOrderKey(fielddef,bdata->GetElement(0));

  while ( index_spec_suc = bdata->GetElement(++index) )
  {
    if ( !index_spec_suc->IsSymbol("index_spec_suc") )
      break;
    CreateOrderKey(fielddef,index_spec_suc->GetElement(1));
  }

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOrderKeys"

logical SchemaResources :: CreateOrderKeys (PropertyHandle &ph, BNFData *bdata )
{
  int                     index = 0;
  int32                   max_size;
  BNFData                *index_spec_suc;
  logical                 term = NO;
// order_keys      := ordered_by '(' index_specs ')'                        // ODABA extension
// index_specs     := index_spec [index_spec_suc(*)]
// index_spec_suc  := ',' index_spec

  PH(&ph,ddeindx)
  bdata = bdata->GetElement("index_specs");
  max_size = ph.GetInt("ddedim");
  
  CreateOrderKey(ddeindx,bdata->GetElement(0),max_size);

  while ( index_spec_suc = bdata->GetElement(++index) )
  {
    if ( !index_spec_suc->IsSymbol("index_spec_suc") )
      break;
    CreateOrderKey(ddeindx,index_spec_suc->GetElement(1),max_size);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  CreatePathElement - 



\return term - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathElement"

logical SchemaResources :: CreatePathElement (PropertyHandle &ph, BNFData *bdata )
{
  logical                 term = NO;
BEGINSEQ
// parameter      := parm_spec | operand | '*'
// parm_spec      := ... identifier assigned_value
// assigned_value := assign_op operand

  DBViewPath   vp_def(NULL,bdata,ph.GetCount()); SDBCERR
  
  ph.Add(AUTO);              
  *ph.GPH("sys_ident") = vp_def.get_name();              
  *ph.GPH("path") = vp_def.get_path();
  if ( *vp_def.get_struct_name() > ' ' )
    ph.GPH("structure")->Provide(vp_def.get_struct_name());
  ph.Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateReferences - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReferences"

logical SchemaResources :: CreateReferences (DBStructDef *strdef, BNFData *bdata )
{
  DBFieldDef              fielddef;
  BNFData                *ref_suc;
  int                     index     = 0;
  int32                   index_ref = 0;
  logical                 term = NO;
BEGINSEQ
// ref_def        := type_ref [ ref_option(*) ] references 
// ref_option     := guid | weak_typed | update | multiple_key  
// references     := ref_delarator [references_suc(*)] 
// references_suc := ',' ref_delarator
  
  if ( !bdata->IsSymbol("ref_def") )                 ERROR 
  
  if ( GetColTypeSpec(&fielddef,bdata,index_ref,NO) )ERROR
  
  bdata = bdata->GetElement("references"); 
  CreateCollection(&fielddef,bdata->GetElement(0),strdef,NO);
  
  while ( ref_suc = bdata->GetElement(++index) )
    CreateCollection(&fielddef,ref_suc->GetElement(1),strdef,NO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReferences"

logical SchemaResources :: CreateReferences (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *options;
  BNFData                *ref_suc;
  char                    type[ID_SIZE];
  char                    generic_type[ID_SIZE];
  int32                   dimension = 0;
  uint32                  size = 0;
  int16                   precision = 0;
  ODC_Privilege           privilege = ODC_undefined;
  logical                 virt_opt  = NO;
  logical                 stat_opt  = NO;
  logical                 trans_opt = NO;
  logical                 mkey_opt  = NO;
  logical                 weak_opt  = NO;
  logical                 update_opt= NO;
  logical                 unicode   = NO;
  logical                 guid_opt  = NO;
  logical                 collopt   = NO;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// ref_def        := type_ref [ ref_option(*) ] references 
// ref_option     := guid | weak_typed | update | multiple_key  
// references     := ref_delarator [references_suc(*)] 
// references_suc := ',' ref_delarator
  
  if ( !bdata->IsSymbol("ref_def") )                      ERROR 
  
  if ( GetTypeSpec(bdata->GetElement(0),type,generic_type,size,dimension,precision,unicode,
                   privilege,virt_opt,stat_opt,trans_opt,collopt) )
                                                     ERROR
  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("ref_option") )
  {
    switch ( options->GetSymbolCode("guid","weak_typed","update","multiple_key") )
    {
      case 1 : guid_opt = YES;                       break;
      case 2 : weak_opt = YES;                       break;
      case 3 : update_opt = YES;                     break;
      case 4 : mkey_opt = YES;                       break;
    }
  }
  
  bdata = bdata->GetElement("references"); 
  CreateCollection(ph,bdata->GetElement(0),type,generic_type,size,dimension,precision,unicode,
                   privilege,virt_opt,stat_opt,trans_opt,guid_opt,weak_opt,update_opt,mkey_opt);
  
  while ( ref_suc = bdata->GetElement(++index) )
    CreateCollection(ph,ref_suc->GetElement(1),type,generic_type,size,dimension,precision,unicode,
                    privilege,virt_opt,stat_opt,trans_opt,guid_opt,weak_opt,update_opt,mkey_opt);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRelationships - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRelationships"

logical SchemaResources :: CreateRelationships (DBStructDef *strdef, BNFData *bdata )
{
  DBFieldDef              fielddef;
  BNFData                *rel_suc;
  int                     index     = 0;
  int32                   index_ref = 0;
  logical                 term = NO;
BEGINSEQ
// rel_def           := type_ref [ rel_option(*) ] relationships
// rel_option        := ref_option | owner | no_create | dependent | secondary | shared
// relationships     := rel_delarator [relationships_suc(*)] 
// relationships_suc := ',' rel_delarator
  
  if ( !bdata->IsSymbol("rel_def") )                 ERROR 
  
  if ( GetColTypeSpec(&fielddef,bdata,index_ref,NO) )ERROR
  
  bdata = bdata->GetElement("relationships");
  CreateCollection(&fielddef,bdata->GetElement(0),strdef,YES);
  
  while ( rel_suc = bdata->GetElement(++index) )
    CreateCollection(&fielddef,rel_suc->GetElement(1),strdef,YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRelationships"

logical SchemaResources :: CreateRelationships (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *options;
  BNFData                *rel_suc;
  char                    type[ID_SIZE];
  char                    generic_type[ID_SIZE];
  int32                   dimension = 0;
  uint32                  size = 0;
  int16                   precision = 0;
  ODC_Privilege           privilege = ODC_undefined;
  logical                 virt_opt  = NO;
  logical                 stat_opt  = NO;
  logical                 trans_opt = NO;
  logical                 mkey_opt  = NO;
  logical                 weak_opt  = NO;
  logical                 update_opt= NO;
  logical                 guid_opt  = NO;
  logical                 create_opt= YES;
  logical                 owner_opt = NO;
  logical                 dep_opt   = NO;
  logical                 sec_opt   = NO;
  logical                 unicode   = NO;
  logical                 collopt   = NO;
  logical                 shared_opt= NO;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// rel_def           := type_ref [ rel_option(*) ] relationships
// rel_option        := ref_option | owner | no_create | dependent | secondary |shared
// relationships     := rel_delarator [relationships_suc(*)] 
// relationships_suc := ',' rel_delarator
  
  if ( !bdata->IsSymbol("rel_def") )                 ERROR
  
  if ( GetTypeSpec(bdata->GetElement(0),type,generic_type,size,dimension,precision,unicode,
                   privilege,virt_opt,stat_opt,trans_opt,collopt) )
                                                     ERROR
  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("rel_option") )
  {
    switch ( options->GetSymbolCode("ref_option","owner","no_create","dependent","secondary","shared") )
    {
      case 1 : switch ( options->GetElement(0)->GetSymbolCode("guid","weak_typed","update","multiple_key") )
               {
                 case 1 : guid_opt = YES;              break;
                 case 2 : weak_opt = YES;              break;
                 case 3 : update_opt = YES;            break;
                 case 4 : mkey_opt = YES;              break;
               }
               break;
      case 2 : owner_opt = YES;                        break;
      case 3 : create_opt= NO;                         break;
      case 4 : dep_opt   = YES;                        break;
      case 5 : sec_opt   = YES;                        break;
      case 6 : shared_opt= YES;                        break;
    }
  }
   
  bdata = bdata->GetElement("relationships");
  CreateCollection(ph,bdata->GetElement(0),type,generic_type,size,dimension,precision,unicode,
                   privilege,virt_opt,stat_opt,trans_opt,guid_opt,weak_opt,update_opt,
                   mkey_opt,create_opt,owner_opt,dep_opt,sec_opt,shared_opt);
  
  while ( rel_suc = bdata->GetElement(++index) )
    CreateCollection(ph,rel_suc->GetElement(1),type,generic_type,size,dimension,precision,unicode,
                     privilege,virt_opt,stat_opt,trans_opt,guid_opt,weak_opt,update_opt,
                     mkey_opt,create_opt,owner_opt,dep_opt,sec_opt,shared_opt);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSubSets - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  db_ext - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubSets"

logical SchemaResources :: CreateSubSets (DBExtend *db_ext, BNFData *bdata )
{
  int                     index = 0;
  BNFData                *options;
  BNFData                *ext_suc;
  logical                 term = NO;
// sub_sets              := subset [subset_options(*)] extent_names 
// subset_options        := distinct | complete
// extent_names          := extent_name [extent_names_suc(*)]
// extent_names_suc      := ',' extent_name
  
  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("subset_options") )
  {
    switch ( options->GetSymbolCode("distinct","complete") )
    {
      case 1 : db_ext->set_disjunct(YES);            break;
      case 2 : db_ext->set_union_set(YES);           break;
    }
  }
  
  bdata = bdata->GetElement("extent_names");
  
  CreateExtentRelation(db_ext,bdata->GetElement(0),YES);
  
  index = 0;
  while ( ext_suc = bdata->GetElement(++index) )
    CreateExtentRelation(db_ext,ext_suc->GetElement(1),YES);
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubSets"

logical SchemaResources :: CreateSubSets (PropertyHandle &ph, BNFData *bdata )
{
  int                     index = 0;
  BNFData                *options;
  BNFData                *ext_suc;
  logical                 term = NO;
// sub_sets              := subset [subset_options(*)] extent_names 
// subset_options        := distinct | complete
// extent_names          := extent_name [extent_names_suc(*)]
// extent_names_suc      := ',' extent_name
  
  while ( (options = bdata->GetElement(++index)) && options->IsSymbol("subset_options") )
  {
    switch ( options->GetSymbolCode("distinct","complete") )
    {
      case 1 : *ph.GPH("disjunct")  = YES;           break;
      case 2 : *ph.GPH("union_set") = YES;           break;
    }
  }
  
  PH(&ph,sexderi)
  bdata = bdata->GetElement("extent_names");
  
  CreateExtentRelation(sexderi,bdata->GetElement(0),NO);
  
  index = 0;
  while ( ext_suc = bdata->GetElement(++index) )
    CreateExtentRelation(sexderi,ext_suc->GetElement(1),NO);
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSuperSets - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  db_ext - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSuperSets"

logical SchemaResources :: CreateSuperSets (DBExtend *db_ext, BNFData *bdata )
{
  int                     index = 0;
  BNFData                *ext_suc;
  logical                 term = NO;
// super_sets            := superset [intersect] extent_names
// extent_names          := extent_name [extent_names_suc(*)]
// extent_names_suc      := ',' extent_name

  if ( bdata->GetElement("intersect") )
    db_ext->set_intersect(YES);
  
  bdata = bdata->GetElement("extent_names");
  
  CreateExtentRelation(db_ext,bdata->GetElement(0),NO);
  
  while ( ext_suc = bdata->GetElement(++index) )
    CreateExtentRelation(db_ext,ext_suc->GetElement(1),NO);

  db_ext->set_owning(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSuperSets"

logical SchemaResources :: CreateSuperSets (PropertyHandle &ph, BNFData *bdata )
{
  int                     index = 0;
  BNFData                *ext_suc;
  logical                 term = NO;
// super_sets            := superset [intersect] extent_names
// extent_names          := extent_name [extent_names_suc(*)]
// extent_names_suc      := ',' extent_name

  if ( bdata->GetElement("intersect") )
    *ph.GPH("intersect") = YES;
  
  PH(&ph,sexbase)
  bdata = bdata->GetElement("extent_names");
  
  CreateExtentRelation(sexbase,bdata->GetElement(0));
  
  while ( ext_suc = bdata->GetElement(++index) )
    CreateExtentRelation(sexbase,ext_suc->GetElement(1));

  *ph.GPH("owning") = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTypeProperties - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTypeProperties"

logical SchemaResources :: CreateTypeProperties (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *spec;
  int32                   index = 0;
  logical                 term = NO;
BEGINSEQ
// ... [type_property_list] ...
// type_property_list := '(' type_property(*) ')'
// type_property      := key_spec | extent_spec
  
  if ( !bdata )                                      LEAVESEQ
    
  if ( !bdata->IsA("type_property_list") )
    bdata = bdata->GetElement("type_property_list");
  
  if ( bdata )
  {
    while ( (spec = bdata->GetElement(++index)) &&
            spec->IsSymbol("type_property")             )
    {
      spec = spec->GetElement(0);
      switch ( spec->GetSymbolCode("key_spec","extent_spec") )
      {
        case 1 : LoadKeySpec(strdef,spec);            break;
        case 2 : LoadExtentSpec(strdef,spec);         break;
      }
    }
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  name - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTypeProperties"

logical SchemaResources :: CreateTypeProperties (PropertyHandle &ph, char *name, BNFData *bdata, logical del_opt )
{
  BNFData                *spec;
  int32                   index = 0;
  logical                 term  = NO;
BEGINSEQ
// ... [type_property_list] ...
// type_property_list := '(' type_property(*) ')'
// type_property      := key_spec | extent_spec
  
  if ( !bdata )                                      LEAVESEQ
    
  if ( !ph.Provide(name) )                           ERROR
  if ( del_opt )
    ph.GPH("smceextd")->DeleteSet();
  
  if ( !bdata->IsA("type_property_list") )
    bdata = bdata->GetElement("type_property_list");
  
  if ( bdata )
  {
    while ( (spec = bdata->GetElement(++index)) &&
            spec->IsSymbol("type_property")             )
    {
      spec = spec->GetElement(0);
      switch ( spec->GetSymbolCode("key_spec","extent_spec") )
      {
        case 1 : LoadKeySpec(ph,spec);                break;
        case 2 : LoadExtentSpec(ph,spec);             break;
      }
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateViewBase - 



\return term - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateViewBase"

logical SchemaResources :: CreateViewBase (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *parm;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// from_spec     := from operand_list 
// operand_list  := '(' [parm_list] ')' 
// parm_list     := parameter [parm_ext(*)]
// parm_ext      := ',' parameter
  
  if ( !bdata )                                      LEAVESEQ
  bdata = bdata->GetElement("operand_list");         
  if ( !(bdata = bdata->GetElement("parm_list")) )   SDBERR(99)
    
  parm = bdata->GetElement(0);
  
  while ( parm )
  {
    CreatePathElement(ph,parm);
    if ( parm = bdata->GetElement(++index) )
      parm = parm->GetElement(1);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateViewSource - 



\return term - 

\param  ph - 
\param  bd_ident - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateViewSource"

logical SchemaResources :: CreateViewSource (PropertyHandle &ph, BNFData *bd_ident, BNFData *bdata )
{
  char                   *string;
  logical                 term = NO;
  ph.Add(AUTO);
  
  string = bdata->StringValue();
  *ph.GPH("path")      = string;
  *ph.GPH("sys_ident") = bd_ident ? bd_ident->StringValue() : string;
        
  ph.Save();

  return(term);
}

/******************************************************************************/
/**
\brief  GetColOptions - 



\return term - 

\param  fielddef - Internal field defintion
\param  bdata - 
\param  index_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetColOptions"

logical SchemaResources :: GetColOptions (DBFieldDef *fielddef, BNFData *bdata, int32 &index_ref )
{
  BNFData                *options;
  logical                 term = NO;
// ref_def           := ... [ ref_option(*) ] ...
// rel_def           := ... [ rel_option(*) ] ...
// rel_option        := ref_option | owner | no_create | dependent | secondary | shared
// ref_option        := guid | weak_typed | update | multiple_key  
  
  while ( (options = bdata->GetElement(index_ref++)) && options->IsSymbol("rel_option") )
  {
    if ( options->IsSymbol("ref_option") )
    {
      options = options->GetSymbol("ref_option");
      switch ( options->GetElement(0)->GetSymbolCode("guid","weak_typed","update","multiple_key") )
      {
        case 1 : fielddef->set_global_identity(YES);     break;
        case 2 : fielddef->set_weak_typed(YES);          break;
        case 3 : fielddef->set_update(YES);              break;
        case 4 : fielddef->set_multikey(YES);            break;
      }
    }
    else if ( options->IsSymbol("ref_option") )
    {
      switch ( options->GetSymbolCode("owner","no_create","dependent","secondary","shared") )
      {
        case 1 : fielddef->set_owning(YES);              break;
        case 2 : fielddef->set_create(NO);               break;
        case 3 : fielddef->set_depend(YES);              break;
        case 4 : fielddef->set_sec_reference(YES);       break;
        case 5 : fielddef->set_shared(YES);              break;
      }
    }
    else
      break;
  }
   

  return(term);
}

/******************************************************************************/
/**
\brief  GetColTypeSpec - 



\return term - 

\param  fielddef - Internal field defintion
\param  bdata - 
\param  index_ref - 
\param  setup_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetColTypeSpec"

logical SchemaResources :: GetColTypeSpec (DBFieldDef *fielddef, BNFData *bdata, int32 &index_ref, logical setup_opt )
{
  logical                 term = NO;
BEGINSEQ
// ref_def           := type_ref [ ref_option(*) ] ...
// rel_def           := type_ref [ rel_option(*) ] ...
  
  if ( GetTypeSpec(fielddef,bdata->GetElement(index_ref++),setup_opt) )
                                                     ERROR
  fielddef->fmcbrlev = R_REFR;
  if ( GetColOptions(fielddef,bdata,index_ref) )    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetFileReference - 



\return bdata - 

\param  bdata - 
\param  symbol - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFileReference"

BNFData *SchemaResources :: GetFileReference (BNFData *bdata, char *symbol )
{
  BNFData                *file;
  BNFData                *def;
  int                     indx0 = 0;

BEGINSEQ
// .. [block_intro(*)]
// block_intro    := comment_block | pragma | member | file_reference
// file_reference := _include string  
  
  while ( def = bdata->GetElement(indx0++) )
  {
    if ( def->IsSymbol("file_reference") )          
    {  
      file = def->GetElement("string");
      if ( !(bdata = dictionary->ParseFile(file->GetStringValue(NULL,NULL),symbol)) )
                                                     ERROR
      LEAVESEQ
    }
    else if ( !def->IsSymbol("block_intro") )        ERROR
  }
RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetPrivilege - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrivilege"

logical SchemaResources :: GetPrivilege (BNFData *bdata )
{

  return(((BNFExpData *)bdata)->GetPrivilege());

}

/******************************************************************************/
/**
\brief  GetTypeSpec - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  setup_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeSpec"

logical SchemaResources :: GetTypeSpec (DBFieldDef *fielddef, BNFData *bdata, logical setup_opt )
{
  int8                    maxalign = 0;
  logical                 stat_opt;
  logical                 virt_opt;
  logical                 trans_opt;
  logical                 collopt   = NO;
  char                    type_name[ID_SIZE+1];
  ODC_Privilege           temp_privilege;  // bis es in Fielddef so etwas gibt
  logical                 term = NO;
BEGINSEQ
// mmtype_ref       := [type_ref_options(*)] simple_type_spec 
// type_ref         := [type_ref_options(*)] domain_type             // ODABA extension
// base_type        := [base_option(*)] extended_type_spec
// type_spec        := simple_type_spec | constr_type_spec
// simple_type_spec := base_type_spec | extended_type_spec
// domain_type      := simple_type_spec| struct_type | enum_type 
// struct_type and enum_type are not yet supported here

  if ( ((BNFExpData *)bdata)->GetTypeSpec(type_name,
                   (char *)fielddef->get_generic_type(),
                   fielddef->fmcbsize,
                   fielddef->fmcbdim,
                   fielddef->fmcbprec,
                   fielddef->fmcbunicode,
                   temp_privilege,virt_opt,stat_opt,trans_opt,collopt) ) 
                                                     ERROR
  fielddef->set_set_operation(collopt);
  
  gvtxstb(fielddef->fmcbtype,type_name,ID_SIZE);
  fielddef->fmcbvirt = virt_opt;
  fielddef->fmcbstat = stat_opt;
  fielddef->fmcbtrans= trans_opt;
  
  if ( setup_opt )
  {
    dictionary->ProvideStructDef(fielddef->fmcbtype);
    if ( fielddef->SetupType(dictionary,NO) )        ERROR
    fielddef->fmcbesu(fielddef->fmcbsmcb,0,0,maxalign);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  bdata - 
\param  type - 
\param  generic_type - 
\param  size_ref - 
\param  dim_ref - 
\param  prec_ref - 
\param  unicode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeSpec"

logical SchemaResources :: GetTypeSpec (BNFData *bdata, char *type, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref )
{

  return(((BNFExpData *)bdata)->GetTypeSpec(type,generic_type,size_ref,dim_ref,prec_ref,unicode_ref));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  bdata - 
\param  type - 
\param  generic_type - 
\param  size_ref - 
\param  dim_ref - 
\param  prec_ref - 
\param  unicode_ref - 
\param  priv_ref - 
\param  virt_ref - 
\param  stat_ref - 
\param  trans_ref - 
\param  collopt_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeSpec"

logical SchemaResources :: GetTypeSpec (BNFData *bdata, char *type, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref, ODC_Privilege &priv_ref, logical &virt_ref, logical &stat_ref, logical &trans_ref, logical &collopt_ref )
{

  return( ((BNFExpData *)bdata)->GetTypeSpec(type,generic_type,
          size_ref,dim_ref,prec_ref,unicode_ref,priv_ref,virt_ref,
          stat_ref,trans_ref,collopt_ref) );

}

/******************************************************************************/
/**
\brief  InitMember - 



\return term - 

\param  ph - 
\param  type - 
\param  generic_type - 
\param  size - 
\param  dimension - Dimension
\param  precision - Precision
\param  unicode - 
\param  privilege_w - 
\param  virtual_w - 
\param  static_w - 
\param  transient_w - 
\param  collopt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMember"

logical SchemaResources :: InitMember (PropertyHandle &ph, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w, logical virtual_w, logical static_w, logical transient_w, logical collopt_w )
{
  logical                 term = NO;
  *ph.GPH("ddetype") = type;
  *ph.GPH("ddegent") = generic_type;
  *ph.GPH("ddesize") = (int32)size;
  *ph.GPH("ddedim")  = (int32)dimension;
  *ph.GPH("ddeprec") = precision;
//*ph.GPH("unicode") = unicode;
//*ph.GPH("set_operation") = collopt_w;
  *ph.GPH("ddeprv")  = (int32)privilege_w;
  *ph.GPH("ddestat") = static_w;
  *ph.GPH("ddevirt") = virtual_w;
 
  if ( ph.Inherits("SDB_Property") )
    *ph.GPH("ddetrans") = transient_w;

  return(term);
}

/******************************************************************************/
/**
\brief  InitReference - 



\return term - 

\param  ph - 
\param  type - 
\param  generic_type - 
\param  size - 
\param  dimension - Dimension
\param  precision - Precision
\param  unicode - 
\param  privilege_w - 
\param  virtual_w - 
\param  static_w - 
\param  transient_w - 
\param  guid_w - 
\param  weak_w - 
\param  update_w - 
\param  mkey_w - 
\param  create_w - 
\param  owning_w - 
\param  clust_w - 
\param  shared_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitReference"

logical SchemaResources :: InitReference (PropertyHandle &ph, char *type, char *generic_type, uint16 size, uint32 dimension, uint16 precision, logical unicode, ODC_Privilege privilege_w, logical virtual_w, logical static_w, logical transient_w, logical guid_w, logical weak_w, logical update_w, logical mkey_w, logical create_w, logical owning_w, logical clust_w, logical shared_w )
{
  logical                 term = NO;
  InitMember(ph,type,generic_type,size,dimension,precision,unicode,privilege_w,virtual_w,static_w,transient_w);
  *ph.GPH("week_typed")      = weak_w;
  *ph.GPH("update")          = update_w;
  *ph.GPH("multikey")        = mkey_w;
  *ph.GPH("global_identity") = guid_w;
  *ph.GPH("create")          = create_w;
  *ph.GPH("owning")          = owning_w;
  *ph.GPH("clustered")       = clust_w;
  *ph.GPH("shared")          = shared_w;

  *ph.GPH("reference_level") = RL_reference;

  return(term);
}

/******************************************************************************/
/**
\brief  LoadAttributeDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadAttributeDcl"

logical SchemaResources :: LoadAttributeDcl (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *attrspc;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// attr_dcl   := attribute attr_def
// attr_def   := attr_spec | attr_specs
// attr_specs := '{' sattr_spec(*) '}'
// sattr_spec := attr_spec ';'

  if ( schema_only == NO )                           LEAVESEQ
  bdata = bdata->GetElement(1)->GetElement(0);
  if ( bdata->IsSymbol("attr_spec") )
    CreateMembers(strdef,bdata);
  else // attr_specs
    while ( (attrspc = bdata->GetElement(++index)) &&
            attrspc->IsSymbol("sattr_spec")                )
      CreateMembers(strdef,attrspc->GetElement(0));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadAttributeDcl"

logical SchemaResources :: LoadAttributeDcl (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *attrspc;
  int                     index = 0;
  logical                 term  = NO;
// attr_dcl   := attribute attr_def
// attr_def   := attr_spec | attr_specs
// attr_specs := '{' sattr_spec(*) '}'
// sattr_spec := attr_spec ';'

  bdata = bdata->GetElement(1)->GetElement(0);
  if ( bdata->IsSymbol("attr_spec") )
    CreateMembers(ph,bdata);
  else // attr_specs
    while ( (attrspc = bdata->GetElement(++index)) &&
            attrspc->IsSymbol("sattr_spec")                )
      CreateMembers(ph,attrspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  LoadCPPCode - 



\return term - 

\param  ph - 
\param  bdata - 
\param  inl_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadCPPCode"

logical SchemaResources :: LoadCPPCode (PropertyHandle &ph, BNFData *bdata, logical inl_opt )
{
  BNFData          *bdata_c;
  char             *code;
  char             *curpos;
  char             *end;
  char             *pos;
  char             *endseq;
  char             *recover;
  char             *string;
  logical           term  = NO;
BEGINSEQ
// function_text         := [ ini_code ] function_block
// ini_code              := ':' ini_line(*)
// ini_line              := blockstring | string | comment_block 
// function_block        := '{' [fct_line(*)] '}'
// fct_line              := comment_block | function_block | string | blockstring | _process | _on_error | _final 

  *ph.GPH("inline_funct") = inl_opt;
  
  string = "";
  if ( bdata_c = bdata->GetElement("ini_code") )
    string = bdata_c->StringValue()+1;   // : ueberspringen
  *ph.GPH("init_code") = string;

  code = bdata->GetElement("function_block")->StringValue()+1; // { ueberspringen
  while ( *code && *code < ' ' )
    code++;
  
  end  = code+strlen(code)-1;
  while ( *end != '}' )
    end--; 
  *end = 0;         
    
  curpos = code;
  while ( (pos = strstr(curpos,"BEGINSEQ")) || (pos = strstr(curpos,"PROCESS")) )
  {
    if ( *(pos-1) <= ' ' && pos[pos[1] == 'E' ? 8 : 7] <= ' ' )
      break;
    else
      curpos = pos+1;
  }
  
  string = "";
  if ( pos )
  {
    *pos = 0;
    string = code;
    *ph.GPH("sequence")   = YES;
    code = pos + (pos[1] == 'E' ? 8 : 7);
    while ( *code && *code < ' ' )
      code++;
  }
  *ph.GPH("start_code") = string;
    
  string = "";
  if ( (endseq = strstr(code,"ENDSEQ")) || (endseq = strstr(code,"FINAL")) )
  {
    *endseq = 0;
    endseq  = endseq + (endseq[1] == 'N' ? 6 : 5);
    while ( *endseq && *endseq < ' ' )
      endseq++;
    string = endseq;
  }
  *ph.GPH("term_code") = string;

  string = "";
  if ( (recover = strstr(code,"RECOVER")) || (recover = strstr(code,"ON_ERROR")) )
  {
    *recover = 0;
    recover  = recover + (recover[1] == 'E' ? 7 : 8);
    while ( *recover && *recover < ' ' )
      recover++;
    string = recover;
    *ph.GPH("recover")    = YES;
  }
  *ph.GPH("error_code") = string;
    
  *ph.GPH("code") = code;
  
  ph.Save();                                         SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadCPPFunction - 



\return term - 

\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadCPPFunction"

logical SchemaResources :: LoadCPPFunction (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  BNFData                *funct; 
  logical                 term  = NO;
BEGINSEQ
// cpp_function          := funct_dcl | funct_def
// funct_dcl             := meth_dcl ';'
// funct_def             := meth_dcl function_block

  PH(&ph,pfunctions)
  PH(&pfunctions,implementations)
  PH(&pfunctions,imp_type)
  
  funct = bdata->GetElement(0);
  if ( LoadMethodDcl(pfunctions,funct->GetElement(0)) )   
                                                     ERROR
  if ( funct->IsSymbol("funct_def") )
    if ( LoadCPPCode(implementations,funct->GetElement(1),NO) )
                                                     ERROR
  *pfunctions.GPH("imp_type") = "MT_CPPFunction";
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadClassDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadClassDcl"

logical SchemaResources :: LoadClassDcl (BNFData *bdata )
{
  DBStructDef            *strdef;
  BNFData                *spec;
  BNFData                *cheader;
  int32                   index = 0;
  char                    name[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
//   OSI version
// osi_class             := class_header [ osi_class_def ] 
  
  if ( !bdata )                                    LEAVESEQ
  
  cheader = bdata->GetElement(0);
  gvtxstb(name,cheader->GetElement("identifier")->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  
  if ( !(strdef = ProvideStructDef(name)) )        ERROR
  if ( schema_only )
  {
    if ( spec = cheader->GetElement("extends_spec") )
      CreateInheritance(strdef,spec);
  
    if ( spec = cheader->GetElement("inheritance_spec") )
      CreateInheritance(strdef,spec);
  
    if ( CreateTypeProperties(strdef,cheader) )      ERROR
  }
  
  if ( bdata = bdata->GetElement("osi_class_def") )
    LoadClassMembers(strdef,bdata);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadClassDcl"

logical SchemaResources :: LoadClassDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  DatabaseHandle          dbh(resources->GetDBHandle());
  PropertyHandle          cph;
  BNFData                *spec;
  BNFData                *cheader;
  int32                   index = 0;
  char                    name[ID_SIZE];
  logical                 term  = NO;
BEGINSEQ
//         ODL-Version
// class_dcl          := class_header [ class_def ] 
// class_header       := _class identifier [extends_spec] [inheritance_spec] [type_property_list]
  
  if ( !bdata )                                    LEAVESEQ
  
  while ( cheader = bdata->GetElement(index) )
    if ( cheader->IsSymbol("class_intro") )
      index++;
    else
      break;
      
  gvtxstb(name,cheader->GetElement("identifier")->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  
  if ( !ph_ptr )
  {
    if ( cph.Open(dbh,"ODC_ImpClass",PI_Write) )  ERROR
  }
  else
  {
    if ( cph.Open(ph_ptr,"classes") )                ERROR
  }

  if ( !cph.Provide(name) )                          ERROR
  *cph.GPH("typetype") = (int32)TYP_Structure;
  *cph.GPH("smcestyp") = (int32)ST_USER;
  *cph.GPH("access_type") = (int32)AT_ODABA;
  
  if ( del_opt )
  {
    cph.GPH("smcebase")->DeleteSet();
    cph.GPH("smcepsmc")->DeleteSet();
  }
  
  if ( spec = cheader->GetElement("extends_spec") )
    CreateInheritance(cph,spec);
  
  if ( spec = cheader->GetElement("inheritance_spec") )
    CreateInheritance(cph,spec);
  
  if ( bdata = bdata->GetElement("class_def") )
    LoadClassMembers(cph,bdata,del_opt);
  
  cph.Save();
  cph.Cancel();
 
  if ( CreateTypeProperties(cph,name,cheader,del_opt) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadClassMembers - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadClassMembers"

logical SchemaResources :: LoadClassMembers (DBStructDef *strdef, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *member;
  logical                 term = NO;
//   OSI version
// osi_class_def      := '{' osi_exports(*) '}'  
// osi_exports        := [ comment_block(*) ] osi_export_dcl
// osi_export_dcl     := attr_dcl | ref_dcl | rel_dcl | expr_def
  
  while ( (member = bdata->GetElement(++indx0)) &&
          member->IsSymbol("osi_exports")         )
  {
    member = member->GetElement("osi_export_dcl");
    switch ( member->GetSymbolCode("attr_dcl", "ref_dcl", 
                                   "rel_dcl", "expr_def") )
    {
      case 1 : LoadAttributeDcl(strdef,member->GetElement("attr_dcl"));    
               break;
      case 2 : LoadReferenceDcl(strdef,member->GetElement("ref_dcl"));    
               break;
      case 3 : LoadRelationshipDcl(strdef,member->GetElement("rel_dcl")); 
               break;
      case 4 : // instead of "method"
               LoadExpression(member->GetElement("expr_def"),strdef);  
               break;
      default : ;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadClassMembers"

logical SchemaResources :: LoadClassMembers (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  int                     indx0 = 0;
  BNFData                *member;
  logical                 term  = NO;
// class_def          := '{' exports(*) '}'  
// exports            := [ comment_block(*) ] export_dcl
// export_dcl         := type_dcl | const_dcl | attr_dcl | ref_dcl | rel_dcl | except_dcl | method

  PH(&ph,sys_ident)
  
  if ( del_opt )
  {
    ph.GPH("smcepdde")->DeleteSet();
    ph.GPH("smcepref")->DeleteSet();
    ph.GPH("smcershp")->DeleteSet();
    ph.GPH("members")->DeleteSet();
    ph.GPH("pfunctions")->DeleteSet();
    
    ph.GPH("constants")->DeleteSet();
    ph.GPH("pfunctions")->DeleteSet();
//    ph.GPH("enums")->DeleteSet();
//    ph.GPH("classes")->DeleteSet();
    ph.GPH("exceptions")->DeleteSet();
  }
  
  while ( (member = bdata->GetElement(++indx0)) &&
          member->IsSymbol("exports")         )
  {
    member = member->GetElement("export_dcl");
    switch ( member->GetSymbolCode("type_dcl", "const_dcl", "attr_dcl",
                                   "ref_dcl","rel_dcl","except_dcl","method") )
    {
      case 1 : // type_dcl not yet supported 
               break;
      case 2 : // const_dcl not yet supported 
               break;
      case 3 : LoadAttributeDcl(*ph.GPH("smcepdde"),member);    
               break;
      case 4 : LoadReferenceDcl(*ph.GPH("smcepref"),member);    
               break;
      case 5 : LoadRelationshipDcl(*ph.GPH("smcershp"),member); 
               break;
      case 6 : LoadExceptDcl(ph.GPH("exceptions"),member,NO);   
               break;
      case 7 : LoadMethod(ph,member);                           
               break;
      default : ;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  LoadConstDcl - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadConstDcl"

logical SchemaResources :: LoadConstDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  DatabaseHandle          dbh(resources->GetDBHandle());
  PropertyHandle          ph;
  char                    name[ID_SIZE];
  int                     indx0 = 0;
  logical                 term  = NO;
BEGINSEQ
// const_dcl := _const const_type identifier '=' const_exp
  if ( !bdata || !schema_only )                      LEAVESEQ
  
  SDBEV1(bdata->StringValue(),UNDEF) 
  if ( dictionary != database )                      SDBERR(435)
  
  if ( !ph_ptr )
  {
    if ( ph.Open(dbh,"ODC_Variable",PI_Write) ) ERROR
    ph_ptr = &ph;
  }
  
  gvtxstb(name,bdata->GetElement("identifier")->StringValue(),sizeof(name));
  if ( !ph_ptr->Provide(name) )                      ERROR
  *ph_ptr->GPH("ddetype") = bdata->GetElement("const_type")->StringValue();
  *ph_ptr->GPH("ddeinit") = bdata->GetElement("const_exp")->StringValue();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadControl - 



\return term - 

\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadControl"

logical SchemaResources :: LoadControl (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  logical                 term  = NO;
BEGINSEQ
// control        := _control identifier ';'

   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadDocumentTemplate - 



\return term - 

\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadDocumentTemplate"

logical SchemaResources :: LoadDocumentTemplate (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  logical                 term  = NO;
BEGINSEQ
// doc_template   := '<template>' dct_header [ dct_spec ] '</template>'
// dct_header     := '<header>' meth_dcl '</header>'
// dct_spec       := fixed_text | extended_text(*)
// fixed_text     := anychar(*)
// extended_text  := [fixed_text] imbedded_expr
// imbedded_expr  := comp_expr | output_expr
// output_expr    := '<:' expr_element(*) ':>'
// comp_expr      := '<%' expr_element(*) '%>'
// expr_element   := member | statement

  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadEnumType - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadEnumType"

logical SchemaResources :: LoadEnumType (BNFData *bdata )
{
  DBExtend               *extdef;
  char                    name[ID_SIZE];
  char                    basestruct[ID_SIZE];
  int32                   count = 0;
  BNFData                *enumerator;
  int32                   indx0    = 0;
  DBStructDef            *csdefptr = NULL;
  logical                 term     = NO;
BEGINSEQ
// enum_type := _enum identifier [base_class] [enum_def]
  if ( !bdata )                                      LEAVESEQ
  
  SDBEV1(bdata->StringValue(),UNDEF) 
  gvtxstb(name,bdata->GetElement("identifier")->StringValue(),sizeof(name));
  if ( bdata->GetElement("base_class") )
    gvtxstb(basestruct,bdata->GetElement("base_class")->GetElement(1)->StringValue(),ID_SIZE);
  else
    memset(basestruct,' ',ID_SIZE);
    
  TypeKey  tkey(name,UNDEF);   // hier brauchen wir den richtigen namespace!!
  if ( !(csdefptr = dictionary->ProvideCSDecl(tkey,NULL,dictionary->GetTempStructID())) )
                                                    ERROR
  if ( bdata = bdata->GetElement("enum_def") )
    count = bdata->GetElementCount();
    
  extdef = new DBExtend(dictionary,basestruct,NULL,csdefptr,count);
  csdefptr->Setup(dictionary,extdef->get_cs_values());

  if ( bdata )
    LoadEnumerators(bdata);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadEnumType"

logical SchemaResources :: LoadEnumType (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  PropertyHandle          ph;
  PropertyHandle          enum_ph;
  int                     indx0 = 0;
  BNFData                *base_class;
  logical                 term  = NO;
BEGINSEQ
// enum_type  := _enum identifier [base_class] [enum_def]
// base_class := '(' scoped_name ')'
// enum_def   := '{' enumerator(*) '}'
  if ( !bdata )                                      LEAVESEQ
  
  if ( !ph_ptr )
  {
    DatabaseHandle dbh(resources->GetDBHandle());
    if ( ph.Open(dbh,"SDB_ValueList",PI_Write) )    ERROR
  }
  else
    ph.Open(ph_ptr);
  
  SDBEV1(bdata->StringValue(),UNDEF) 
  
  TypeKey    tkey(bdata->GetElement("identifier")->StringValue(),0);
  if ( !ph.Provide(tkey.GetKey()) )                 ERROR
  *ph.GPH("typetype")    = "TYP_Codeset";
  *ph.GPH("access_type") = "AT_CODE";
  
  enum_ph.Open(ph.GPH("values"));
  if ( del_opt )
  {
    enum_ph.DeleteSet();
    *ph.GPH("base_type") = "";
    *ph.GPH("scope") = "";
  }   
  
  if ( base_class = bdata->GetElement("base_class") )
    LoadTypeReference(base_class->GetElement("scoped_name"),
                      *ph.GPH("scope"),*ph.GPH("base_type"));
                      
  if ( bdata = bdata->GetElement("enum_def") )
    LoadEnumerators(enum_ph,bdata);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadEnumerators - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadEnumerators"

logical SchemaResources :: LoadEnumerators (BNFData *bdata )
{
  DBExtend               *extdef;
  char                    name[ID_SIZE];
  char                    basestruct[ID_SIZE];
  BNFData                *enumerator;
  int32                   indx0    = 0;
  DBStructDef            *csdefptr = NULL;
  logical                 term     = NO;
BEGINSEQ
// enum_def   := '{' enumerator(*) '}'
  if ( !bdata )                                      LEAVESEQ
  
  while ( (enumerator = bdata->GetElement(++indx0)) &&
          enumerator->IsSymbol("enumerator")                )
    CreateEnumerator(extdef->get_cs_values(),enumerator);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadEnumerators"

logical SchemaResources :: LoadEnumerators (PropertyHandle &ph, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *enumerator;
  logical                 term  = NO;
BEGINSEQ
// enum_def   := '{' enumerator(*) '}'
  if ( !bdata )                                      LEAVESEQ
  
  while ( (enumerator = bdata->GetElement(++indx0)) &&
          enumerator->IsSymbol("enumerator")           )
    CreateEnumerator(ph,enumerator);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadExceptDcl - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExceptDcl"

logical SchemaResources :: LoadExceptDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  int                     indx0 = 0;
  logical                 term  = NO;
BEGINSEQ
// except_dcl
  if ( !bdata || !schema_only )                      LEAVESEQ
  
// not yet supported, ignored
  SDBEV1(bdata->StringValue(),UNDEF)                 SDBERR(434)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadExports - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExports"

logical SchemaResources :: LoadExports (DBStructDef *strdef, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *exports;
  logical                 term = NO;
// interface_spec := '{' [exports(*)] '}'
// exports        := export ';' 
// export         := type_dcl | const_dcl | except_dcl | attr_dcl | ref_dcl | rel_dcl | method

  while ( (exports = bdata->GetElement(++indx0)) &&
          exports->IsSymbol("exports")                   )
  {
    exports = exports->GetElement(0)->GetElement(0);
    switch ( exports->GetSymbolCode("type_dcl","const_dcl","except_dcl","attr_dcl",
                                   "ref_dcl","rel_dcl","expr_def","method") )
    {
      case 1 : // LoadTypeDcl((strdef,exports->GetElement("type_dcl"));
               break;
      case 2 : // LoadConstDcl((strdef,exports->GetElement("const_dcl"));
               break;
      case 3 : // LoadExceptDcl((strdef,exports->GetElement("except_dcl"));
               break;
      case 4 : LoadAttributeDcl(strdef,exports->GetElement("attr_dcl"));    
               break;
      case 5 : LoadReferenceDcl(strdef,exports->GetElement("ref_dcl"));    
               break;
      case 6 : LoadRelationshipDcl(strdef,exports->GetElement("rel_dcl")); 
               break;
      case 7 : LoadExpression(exports->GetElement("expr_def"),strdef);  
               break;
      case 8 : // LoadMethodDcl((strdef,exports->GetElement("type_dcl"));        
               break;
      default : ;
    }
  }  

  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExports"

logical SchemaResources :: LoadExports (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  int                     indx0 = 0;
  BNFData                *dcldata; 
  BNFData                *exports;
  logical                 term  = NO;
// interface_spec := '{' [exports(*)] '}'
// exports        := export ';'
// export         := type_dcl | const_dcl | except_dcl | attr_dcl | ref_dcl | rel_dcl | method

  if ( del_opt )
  {
    ph.GPH("smcepdde")->DeleteSet();
    ph.GPH("smcepref")->DeleteSet();
    ph.GPH("smcershp")->DeleteSet();
    ph.GPH("members")->DeleteSet();
    ph.GPH("pfunctions")->DeleteSet();
    
    ph.GPH("constants")->DeleteSet();
//    ph.GPH("enums")->DeleteSet();
//    ph.GPH("classes")->DeleteSet();
//    ph.GPH("exceptions")->DeleteSet();
  }
  
  while ( (exports = bdata->GetElement(++indx0)) &&
          exports->IsSymbol("exports")                   )
  {
    dcldata = exports->GetElement(0)->GetElement(0);
    switch ( dcldata->GetSymbolCode("type_dcl","const_dcl","except_dcl","attr_dcl",
                                    "ref_dcl","rel_dcl","method") )
    {
      case 1 : LoadTypeDcl(&ph,dcldata,NO);                      break;
      case 2 : LoadConstDcl(ph.GPH("constants"),dcldata,NO);     break;
      case 3 : LoadExceptDcl(ph.GPH("exceptions"),dcldata,NO);   break;
      case 4 : LoadAttributeDcl(*ph.GPH("smcepdde"),dcldata);    break;
      case 5 : LoadReferenceDcl(*ph.GPH("smcepref"),dcldata);    break;
      case 6 : LoadRelationshipDcl(*ph.GPH("smcershp"),dcldata); break;
      case 7 : LoadMethodDcl(*ph.GPH("pfunctions"),dcldata);     break;
      default : ;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  LoadExpression - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
\param  strdef - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExpression"

logical SchemaResources :: LoadExpression (BNFData *bdata, DBStructDef *strdef, OperEnvironment *operenv_w )
{
  BNFData                *exprdata; 
  BNFData                *scoped_name;
  char                   *clasname = NULL;
  logical                 term = NO;
BEGINSEQ
// expression      := ... expr_spec
// expr_spec       := expr_dcl | expr_def
// expr_dcl        := meth_dcl ';'
// expr_def        := meth_dcl expr_code
// meth_dcl        := [oneway] mtype_ref [ref_symbol(*)] meth_ident parameter_dcls [raises_expr] [context_expr]
// meth_ident      := ['~'] scoped_name [ impl_ident ] [cun_op]
// scoped_name     := identifier [ scoped_name_ext(*) ]
// scoped_name_ext := scope_op identifier

  if ( schema_only == YES )                         LEAVESEQ
    
  if ( !(exprdata = bdata->GetElement("expr_spec")) )
    exprdata = bdata;
  if ( !exprdata->IsSymbol("expr_def") )
    if ( !(exprdata = exprdata->GetSymbol("expr_def")) )
                                                     OQLERR(162)
  if ( strdef )
    clasname = strdef->smcbname;
  scoped_name = exprdata->GetElement("meth_dcl")->GetElement("meth_ident")->GetElement("scoped_name");
  if ( scoped_name->GetElementCount() > 2 )          OQLERR(162)
  if ( scoped_name->GetElementCount() == 2 )
    clasname = scoped_name->GetElement(0)->GetStringValue(NULL,NULL);

  if ( !dictionary->ProvExpression(resources,clasname,exprdata,NULL,
                                   database,NULL) )  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExpression"

logical SchemaResources :: LoadExpression (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  BNFData                *exprdata; 
  BNFData                *cppdata;
  BNFParser              *parser;
  char                   *string = NULL;
  logical                 term  = YES;
BEGINSEQ
// expression            := _expression expr_spec
// expr_spec             := expr_dcl | expr_def
// expr_dcl              := meth_dcl ';'
// expr_def              := meth_dcl expr_code ';'

// this is a short cut for expression import

  exprdata = bdata->GetElement(1);
  
  string   = strdup(exprdata->GetStringValue(NULL,NULL));
  if ( parser   = dictionary->CreateParser() )
  {  
    cppdata  = parser->Analyze(string,"cpp_function",YES);
    term = LoadCPPFunction(ph,cppdata->GetElement(0),del_opt);
    delete parser;
  }
  free(string);
  if ( term )                                        ERROR
    
  *ph.GPH("pfunctions")->GPH("imp_type") = "MT_OQLExpression";
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadExtentSpec - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExtentSpec"

logical SchemaResources :: LoadExtentSpec (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *extspc;
  int                     index = 0;
  logical                 term = NO;
// extent_spec   := extent extents_def                 
// extents_def   := extent_def | extent_specs
// extent_specs  := '{' sextent_spec(*) '}'
// sextent_spec  := extent_def ';'

  bdata = bdata->GetElement(1)->GetElement(0);
  if ( bdata->IsSymbol("extent_def") )
    CreateExtent(strdef,bdata);
  else // extent_specs
    while ( (extspc = bdata->GetElement(++index)) &&
            extspc->IsSymbol("sextent_spec")                 )
      CreateExtent(strdef,extspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadExtentSpec"

logical SchemaResources :: LoadExtentSpec (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *extspc;
  int                     index = 0;
  logical                 term  = NO;
// extent_spec   := extent extents_def                            // ODABA requires a semicolon, here
// extents_def   := extent_def | extent_specs
// extent_specs  := '{' sextent_spec(*) '}'
// sextent_spec  := extent_def ';'

  bdata = bdata->GetElement(1)->GetElement(0);
  if ( bdata->IsSymbol("extent_def") )
    CreateExtent(ph,bdata);
  else // extent_specs
    while ( (extspc = bdata->GetElement(++index)) &&
            extspc->IsSymbol("sextent_spec")                 )
      CreateExtent(ph,extspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  LoadInterfaceDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadInterfaceDcl"

logical SchemaResources :: LoadInterfaceDcl (BNFData *bdata )
{
  DBStructDef            *strdef;
  BNFData                *spec;
  BNFData                *iheader;
  int32                   index = 0;
  char                    name[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
// interface_dcl    := interface_header [ interface_spec ]
// interface_header := _interface identifier [ inheritance_spec ]
  
  if ( !bdata )                                    LEAVESEQ
  
  iheader = bdata->GetElement(0);
  gvtxstb(name,iheader->GetElement("identifier")->StringValue(),sizeof(name));
  
  if ( !(strdef = ProvideStructDef(name)) )        ERROR
  if ( schema_only )
    if ( spec = iheader->GetElement("inheritance_spec") )
      CreateInheritance(strdef,spec);
  
  if ( bdata = bdata->GetElement("class_def") )
    LoadExports(strdef,bdata);  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadInterfaceDcl"

logical SchemaResources :: LoadInterfaceDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  DatabaseHandle          dbh(resources->GetDBHandle());
  PropertyHandle          ph;
  BNFData                *inheritance;
  BNFData                *iheader;
  char                    name[ID_SIZE];
  logical                 term  = NO;
BEGINSEQ
// interface_dcl    := interface_header [ interface_spec ]
// interface_header := _interface identifier [ inheritance_spec ]
  if ( !bdata )                                  LEAVESEQ
  
  iheader = bdata->GetElement(0);
  gvtxstb(name,iheader->GetElement("identifier")->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  
  if ( !ph_ptr )
  {
    if ( ph.Open(dbh,"ODC_ImpClass",PI_Write) )      ERROR
  }
  else
  {
    if ( ph.Open(ph_ptr,"classes") )                 ERROR
  }
  ph_ptr = &ph;
  
  if ( !ph_ptr->Provide(name) )                      ERROR
  *ph_ptr->GPH("typetype") = "TYP_Structure";
  
  if ( del_opt )
  {
    ph_ptr->GPH("smcebase")->DeleteSet();
    ph_ptr->GPH("smcepsmc")->DeleteSet();
  }
  
  if ( inheritance = iheader->GetElement(2) )
    CreateInheritance(ph,inheritance);
    
  if ( bdata = bdata->GetElement("interface_spec") )
    LoadExports(*ph_ptr,bdata,del_opt);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadKeySpec - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadKeySpec"

logical SchemaResources :: LoadKeySpec (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *keyspc;
  int                     index = 0;
  logical                 term = NO;
// key_spec              := key keys_def                                  // ODABA requires a semicolon, here, instead of comma
// keys_def              := key_def | key_specs
// key_specs             := '{' skey_spec(*) '}'
// skey_spec             := key_def ';'

  bdata = bdata->GetElement(1)->GetElement(0);
  if ( bdata->IsSymbol("key_def") )
    CreateKey(strdef,bdata);
  else // extent_specs
    while ( (keyspc = bdata->GetElement(++index)) &&
            keyspc->IsSymbol("skey_spec")                 )
      CreateKey(strdef,keyspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadKeySpec"

logical SchemaResources :: LoadKeySpec (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *keyspc;
  int                     index = 0;
  logical                 term  = NO;
// key_spec              := key keys_def                                  // ODABA requires a semicolon, here, instead of comma
// keys_def              := key_def | key_specs
// key_specs             := '{' skey_spec(*) '}'
// skey_spec             := key_def ';'

  bdata = bdata->GetElement(1)->GetElement(0);
  if ( bdata->IsSymbol("key_def") )
    CreateKey(ph,bdata);
  else // extent_specs
    while ( (keyspc = bdata->GetElement(++index)) &&
            keyspc->IsSymbol("skey_spec")                 )
      CreateKey(ph,keyspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  LoadMethod - 



\return term - 

\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadMethod"

logical SchemaResources :: LoadMethod (PropertyHandle &ph, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *defdata; 
  logical                 term  = NO;
// method         := [block_intro(*)] method_spec
// method_spec    := doc_template | expression | cpp_function | window | control

  defdata = bdata->GetElement("method_spec");
  defdata = defdata->GetElement(0);
  switch ( defdata->GetSymbolCode("doc_template","expression","cpp_function",
                                  "window","control") )
  {
    case 1 : LoadDocumentTemplate(ph,defdata,NO);       break;
    case 2 : LoadExpression(ph,defdata,NO);             break;
    case 3 : LoadCPPFunction(ph,defdata,NO);            break;
    case 4 : LoadWindow(ph,defdata,NO);                 break;
    case 5 : LoadControl(ph,defdata,NO);                break;
    default : ;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  LoadMethodDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  indx_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadMethodDcl"

logical SchemaResources :: LoadMethodDcl (DBFieldDef *fielddef, BNFData *bdata, int32 &indx_ref )
{
  BNFData                *mid;
  BNFData                *scname;
  NString                 skey;
  int8                    maxalign = 0;
  logical                 term  = NO;
BEGINSEQ
// meth_dcl       := ... mtype_ref [ref_symbol(*)] ['__cdecl'] meth_ident ...
// meth_ident     := ['~'] identifier [ impl_ident ] [cun_op]
// impl_ident     := '.' identifier

  if ( !(bdata = bdata->GetSymbol("meth_dcl")) )     ERROR
  if ( GetTypeSpec(fielddef,bdata->GetElement(indx_ref++),NO) )
                                                     ERROR
  if ( SetReferenceLevel(fielddef,bdata,indx_ref) )  ERROR
    
  skey = "";
  while ( mid = bdata->GetElement(indx_ref++) )
    if ( mid->IsSymbol("meth_ident") )
      break;
  if ( !mid )                                        SDBERR(99)
    
  if ( mid->GetElement(0)->IsSymbol("~") )
    skey += '~';
  scname = mid->GetElement("scoped_name");
  if ( !scname->IsSymbol("identifier") )
    scname = scname->GetElement(scname->GetElementCount()-1)->GetElement(1);
  skey += scname->StringValue();
  if ( mid->GetElement("cun_op") )
    skey += mid->GetElement("cun_op")->StringValue();
  SDBEV2(skey,UNDEF) 
  
  gvtxstb(fielddef->fmcbname,skey,ID_SIZE);
  
  if ( fielddef->SetupType(dictionary,NO) )          ERROR
  fielddef->fmcbesu(fielddef->fmcbsmcb,0,0,maxalign);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadMethodDcl"

logical SchemaResources :: LoadMethodDcl (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *parmspc;
  BNFData                *parm_suc;
  BNFData                *impl_ident = NULL;
  int                     index = 0;
  char                    imp_name[ID_SIZE+1];
  logical                 term  = NO;
BEGINSEQ
// meth_dcl              := [oneway] mtype_ref [ref_symbol(*)] meth_ident parameter_dcls [raises_expr] [context_expr]
// parameter_dcls        := '(' [parameters] ')'
// parameters            := param_dcl [parameter_suc(*)]
// parameter_suc         := ',' param_dcl
// param_dcl             := param_attribute simple_type_spec declarator
// param_attribute       := in | out | inout

  if ( !(bdata = bdata->GetSymbol("meth_dcl")) )     ERROR
  while ( !bdata->GetElement(index)->IsSymbol("mtype_ref") )
    index++;
    
  CreateFunction(ph,bdata,index,&impl_ident);  // ... mtype_ref [ref_symbol(*)] [_static] meth_ident ...

  PH(&ph,implementations)
  if ( impl_ident )
    strcpy(imp_name,impl_ident->StringValue());
  else
    strcpy(imp_name,"i00");
  
  gvtxstb(imp_name,imp_name,sizeof(imp_name)-1);
  implementations.Provide(Key(imp_name));
    
  PH(&implementations,parameters)
  parameters.DeleteSet();
  
  parmspc = bdata->GetElement("parameter_dcls");
  if ( parmspc = parmspc->GetElement("params_dcl") )
  {
    index = 0;
    CreateFunctionParameter(parameters,parmspc->GetElement(index));
    while ( parm_suc = parmspc->GetElement(++index) )
      CreateFunctionParameter(parameters,parm_suc->GetElement(1));
  }
  
  implementations.Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadModule - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadModule"

logical SchemaResources :: LoadModule (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  int                     indx = 3;
  BNFData                *mod_element;
  BNFData                *id;
  char                    name[ID_SIZE];
  PropertyHandle          pph;
  logical                 term  = NO;
BEGINSEQ
// module_dcl  := _module identifier '{' mod_element(*) '}' 
  
  if ( !bdata )                                      LEAVESEQ
  id = bdata->GetElement(1);
    
  if ( !ph_ptr )
  {
    DatabaseHandle dbh(resources->GetDBHandle());
    if ( pph.Open(dbh,"SDB_Module",PI_Write) )       ERROR
  }
  else
    if ( pph.Open(ph_ptr,"sub_modules") )            ERROR
    
  gvtxstb(name,id->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  pph.Provide(name);                                 SDBCERR
  ph_ptr = &pph;
    
  if ( del_opt )
  {
      pph.GPH("sub_modules")->DeleteSet();
      pph.GPH("name_spaces")->DeleteSet();
  }
  
  while ( mod_element = bdata->GetElement(indx++) )  
    if ( mod_element->IsSymbol("mod_element") )
      LoadModuleElement(ph_ptr,mod_element);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadModuleDefinition - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadModuleDefinition"

logical SchemaResources :: LoadModuleDefinition (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  logical                 term  = NO;
BEGINSEQ
// mod_definition    := type_dcl | view_dcl | interface_dcl | class_dcl | const_dcl | module_dcl  
  
  if ( !bdata )                                      LEAVESEQ
  
  bdata = bdata->GetElement(0);
  switch ( bdata->GetSymbolCode("type_dcl", "view_dcl", "interface_dcl", 
                                 "class_dcl", "const_dcl", "module_dcl") )
  {
    case 1 : LoadTypeDcl(ph_ptr,bdata,del_opt);    
             break;
    case 2 : LoadViewDcl(ph_ptr->GPH("views"),bdata,del_opt); 
             break;
    case 3 : LoadInterfaceDcl(ph_ptr,bdata,del_opt);    
             break;
    case 4 : LoadClassDcl(ph_ptr,bdata,del_opt);    
             break;
    case 5 : LoadConstDcl(ph_ptr->GPH("constants"),bdata,del_opt); 
             break;
    case 6 : LoadModule(ph_ptr,bdata,del_opt); 
             break;
    default : ;
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadModuleElement - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadModuleElement"

logical SchemaResources :: LoadModuleElement (PropertyHandle *ph_ptr, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *build_def;
  BNFData                *def;
  BNFData                *upd_opt;
  logical                 del_opt;
  logical                 term  = NO;
BEGINSEQ
// mod_element      := [block_intro(*)] [update_option] mod_definition ';'
  
  if ( !bdata )                                      LEAVESEQ
  
  if ( def = GetFileReference(bdata,"mod_element") )
  {
    LoadModuleElement(ph_ptr,def);                   
    delete def;
  }
  
  del_opt = NO;
  if ( upd_opt = bdata->GetElement("update_option") )
    if ( upd_opt->GetSymbol("_new") )
      del_opt = YES;
    
  def = build_def->GetElement("mod_definition");     // definition
  LoadModuleDefinition(ph_ptr,def,del_opt);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadNamespace - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadNamespace"

logical SchemaResources :: LoadNamespace (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  int                     indx = 3;
  BNFData                *ns_element;
  BNFData                *id;
  char                    name[ID_SIZE];
  PropertyHandle          pph;
  logical                 term  = NO;
BEGINSEQ
// module_dcl  := _namespace identifier '{' ns_element(*) '}' 
  
  if ( !bdata )                                      LEAVESEQ
  id = bdata->GetElement(1);
    
  if ( !ph_ptr )
  {
    DatabaseHandle dbh(resources->GetDBHandle());
    if ( pph.Open(dbh,"SDB_NameSpace",PI_Write) )    ERROR
  }
  else
    if ( pph.Open(ph_ptr,"name_spaces") )            ERROR
    
  gvtxstb(name,id->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  pph.Provide(name);                                 SDBCERR
  ph_ptr = &pph;
    
  if ( del_opt )
  {
      pph.GPH("name_spaces")->DeleteSet();
      pph.GPH("type_defs")->DeleteSet();
      pph.GPH("value_lists")->DeleteSet();
  }
  
  while ( ns_element = bdata->GetElement(indx++) )  
    if ( ns_element->IsSymbol("ns_element") )
      LoadNamespaceElement(ph_ptr,ns_element);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadNamespaceElement - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadNamespaceElement"

logical SchemaResources :: LoadNamespaceElement (PropertyHandle *ph_ptr, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *def;
  BNFData                *upd_opt;
  logical                 del_opt;
  logical                 term  = NO;
BEGINSEQ
// ns_element      := [block_intro(*)] type_dcl ';'
  
  if ( !bdata )                                      LEAVESEQ
  
  if ( def = GetFileReference(bdata,"ns_element") )
  {
    LoadNamespaceElement(ph_ptr,def);
    delete def;
  }
  
  del_opt = NO;
  if ( upd_opt = bdata->GetElement("update_option") )
    if ( upd_opt->GetSymbol("_new") )
      del_opt = YES;
    
  LoadTypeDcl(ph_ptr,bdata->GetElement("type_dcl"),del_opt);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadParmSpec - 



\return term - 

\param  fielddef - Internal field defintion
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadParmSpec"

logical SchemaResources :: LoadParmSpec (DBFieldDef *fielddef, BNFData *bdata )
{
  int32                   index = 0;
  int8                    maxalign = 0;
  logical                 term = NO;
BEGINSEQ
// parm_spec      := [simple_type_spec] [ref_symbol(*)] identifier [fixed_array_size(*)] assigned_value

  if ( bdata->GetElement(index)->IsSymbol("simple_type_spec") )
  {
    if ( GetTypeSpec(fielddef,bdata->GetElement(index++),NO) )
                                                     ERROR
  }
  else
  {
    gvtxstb(fielddef->fmcbtype,"STRING",ID_SIZE);
    fielddef->fmcbbyte = (fielddef->fmcbsize = 255) +1;
  }
    
  if ( CreateMember(fielddef,bdata,NULL,NULL,index,YES) ) 
                                                     ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadReferenceDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadReferenceDcl"

logical SchemaResources :: LoadReferenceDcl (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *srefspc;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// ref_dcl    := reference refs_def
// refs_def   := ref_def | refspecs
// ref_specs  := '{' sref_spec(*) '}'
// sref_spec  := ref_def ';'

  if ( schema_only == NO )                           LEAVESEQ
  bdata = bdata->GetElement(1)->GetElement(0);  // ref_def
  if ( bdata->IsSymbol("ref_def") )
    CreateReferences(strdef,bdata);
  else // ref_specs
    while ( (srefspc = bdata->GetElement(++index)) &&
            srefspc->IsSymbol("sref_spec")                 )
      CreateReferences(strdef,srefspc->GetElement(0));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadReferenceDcl"

logical SchemaResources :: LoadReferenceDcl (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *srefspc;
  int                     index = 0;
  logical                 term  = NO;
// ref_dcl    := reference refs_def
// refs_def   := ref_def | refspecs
// ref_specs  := '{' sref_spec(*) '}'
// sref_spec  := ref_def ';'

  bdata = bdata->GetElement(1)->GetElement(0);  // ref_def
  if ( bdata->IsSymbol("ref_def") )
    CreateReferences(ph,bdata);
  else // ref_specs
    while ( (srefspc = bdata->GetElement(++index)) &&
            srefspc->IsSymbol("sref_spec")                 )
      CreateReferences(ph,srefspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  LoadRelationshipDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadRelationshipDcl"

logical SchemaResources :: LoadRelationshipDcl (DBStructDef *strdef, BNFData *bdata )
{
  BNFData                *srelspc;
  int                     index = 0;
  logical                 term = NO;
BEGINSEQ
// rel_dcl    := relationship rels_def
// rels_def   := rel_def | rel_specs
// rel_specs  := '{' srel_spec(*) '}'
// srel_spec  := rel_def ';'

  if ( schema_only == NO )                           LEAVESEQ
  bdata = bdata->GetElement(1)->GetElement(0);  // ref_def
  if ( bdata->IsSymbol("rel_def") )
    CreateRelationships(strdef,bdata);
  else // rel_specs
    while ( (srelspc = bdata->GetElement(++index)) &&
            srelspc->IsSymbol("srel_spec")                 )
      CreateRelationships(strdef,srelspc->GetElement(0));


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadRelationshipDcl"

logical SchemaResources :: LoadRelationshipDcl (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *srelspc;
  int                     index = 0;
  logical                 term  = NO;
// rel_dcl    := relationship rels_def
// rels_def   := rel_def | rel_specs
// rel_specs  := '{' srel_spec(*) '}'
// srel_spec  := rel_def ';'

  bdata = bdata->GetElement(1)->GetElement(0);  // ref_def
  if ( bdata->IsSymbol("rel_def") )
    CreateRelationships(ph,bdata);
  else // rel_specs
    while ( (srelspc = bdata->GetElement(++index)) &&
            srelspc->IsSymbol("srel_spec")                 )
      CreateRelationships(ph,srelspc->GetElement(0));

  return(term);
}

/******************************************************************************/
/**
\brief  LoadSchema - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadSchema"

logical SchemaResources :: LoadSchema (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  int                     indx0 = 0;
  BNFData                *sc_element;
  BNFData                *id;
  char                    name[ID_SIZE];
  PropertyHandle          pph;
  logical                 term  = NO;
BEGINSEQ
// schema_dcl       := schema [identifier] '{' sc_element(*) '}' 
  
  if ( !bdata )                                      LEAVESEQ
  if ( id = bdata->GetElement(++indx0) )
  {
    if ( !ph_ptr )
    {
      DatabaseHandle dbh(resources->GetDBHandle());
      if ( pph.Open(dbh,"ODC_Project",PI_Write) )    ERROR
    }
    else
      if ( pph.Open(ph_ptr,"sub_projects") )         ERROR
    
    gvtxstb(name,id->StringValue(),sizeof(name));
    SDBEV1(name,ID_SIZE) 
    pph.Provide(name);                               SDBCERR
    ph_ptr = &pph;
    indx0++;
    
    if ( del_opt )
    {
      pph.GPH("sub_projects")->DeleteSet();
      pph.GPH("proj_classes")->DeleteSet();
      pph.GPH("sub_modules")->DeleteSet();
      pph.GPH("name_spaces")->DeleteSet();
    }
  }
  
  while ( sc_element = bdata->GetElement(++indx0) )  
    if ( sc_element->IsSymbol("sc_element") )
      LoadSchemaElement(ph_ptr,sc_element);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadSchemaElement - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadSchemaElement"

logical SchemaResources :: LoadSchemaElement (PropertyHandle *ph_ptr, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *build_def;
  BNFData                *def;
  BNFData                *upd_opt;
  logical                 del_opt;
  logical                 term  = NO;
BEGINSEQ
// sc_element       := [block_intro(*)] [update_option] sc_definition ';'
// sc_definition    := mod_definition | schema_dcl  
  
  if ( !bdata )                                      LEAVESEQ
  
  while ( def = bdata->GetElement(indx0++) )
  {
    if ( !def->IsSymbol("block_intro") )
      break;
    else if ( def->IsSymbol("file_reference") )
      LoadSchemaElement(ph_ptr,def->GetSymbol("file_reference"));                   
  }
  
  del_opt = NO;
  if ( upd_opt = bdata->GetElement("update_option") )
    if ( upd_opt->GetSymbol("_new") )
      del_opt = YES;
    
  bdata = build_def->GetElement("sc_definition");     // definition
    
  if ( def = bdata->GetSymbol("mod_definition") )
    LoadModuleDefinition(ph_ptr,def,del_opt);
  else // schema_dcl
    LoadSchema(ph_ptr,bdata->GetSymbol("schema_dcl"),del_opt);


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadScriptDefinition - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadScriptDefinition"

logical SchemaResources :: LoadScriptDefinition (BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *build_def;
  BNFData                *def;
  BNFData                *upd_opt;
  logical                 del_opt;
  logical                 term  = NO;
BEGINSEQ
// osi_definition  := type_dcl | view_dcl | osi_class | expr_def

  if ( !bdata )                                      LEAVESEQ
  
  switch ( bdata->GetSymbolCode("type_dcl", "view_dcl", 
                                "osi_class", "expr_def") )
  {
    case 1 : term = LoadTypeDcl(bdata->GetSymbol("type_dcl"));
             break;
    case 2 : // term = LoadViewDcl(bdata->GetSymbol("view_dcl"));
             break;
    case 3 : term = LoadClassDcl(bdata->GetSymbol("osi_class"));
             break;
    case 4 : term = LoadExpression(bdata->GetSymbol("expr_def"),NULL);
             break;
    default: ;
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadStructType - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadStructType"

logical SchemaResources :: LoadStructType (BNFData *bdata )
{
//  DBFieldDef             *fielddef;
  char                    name[ID_SIZE];
  BNFData                *member;
  int32                   indx0      = 0;
  int32                   attr_count = 0;
  DBStructDef            *strdef     = NULL;
  logical                 term       = NO;
BEGINSEQ
// struct_type := _struct identifier [struct_def]
// struct_def  := '{' member(*) '}'
  if ( !bdata || !schema_only )                      LEAVESEQ
  
  gvtxstb(name,bdata->GetElement("identifier")->StringValue(),sizeof(name));
  
  if ( !(strdef = ProvideStructDef(name)) )          ERROR
  
  if ( bdata = bdata->GetElement("struct_def") )
    while ( (member = bdata->GetElement(++indx0)) &&
             member->IsSymbol("member")                )
      CreateMembers(strdef,member);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadStructType"

logical SchemaResources :: LoadStructType (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  DatabaseHandle          dbh(resources->GetDBHandle());
  PropertyHandle          ph;
  char                    name[ID_SIZE];
  int                     indx0 = 0;
  BNFData                *member;
  logical                 term  = NO;
BEGINSEQ
// struct_type := _struct identifier [struct_def]
  if ( !bdata )                                      LEAVESEQ
  
  SDBEV1(bdata->StringValue(),UNDEF) 
  gvtxstb(name,bdata->GetElement("identifier")->StringValue(),sizeof(name));
  
  if ( !ph_ptr )
  {
    if ( ph.Open(dbh,"SDB_Structure",PI_Write) )   ERROR
    ph_ptr = &ph;
  }
  
  if ( !ph_ptr->Provide(name) )                         ERROR
  *ph_ptr->GPH("typetype") = "TYP_Structure";
  if ( !ph_ptr->GetInt("itype") )
    *ph_ptr->GPH("itype")  = dbh.GetNewTypeID();
  
  if ( del_opt )
  {
    ph_ptr->GPH("smcepdde")->DeleteSet();
    ph_ptr->GPH("smcebase")->DeleteSet();
    ph_ptr->GPH("smcepref")->DeleteSet();
    ph_ptr->GPH("smcershp")->DeleteSet();
    ph_ptr->GPH("smcepsmc")->DeleteSet();
    ph_ptr->GPH("members")->DeleteSet();
  }
  if ( bdata = bdata->GetElement("struct_def") )
    while ( (member = bdata->GetElement(++indx0)) &&
            member->IsSymbol("member")                )
      CreateMembers(*ph_ptr->GPH("smcepdde"),member);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadTypeDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadTypeDcl"

logical SchemaResources :: LoadTypeDcl (BNFData *bdata )
{
  logical                 term = NO;
BEGINSEQ
// type_dcl := type_def | struct_type | union_type | enum_type
  if ( !bdata || !schema_only )                      LEAVESEQ
  
  bdata = bdata->GetElement(0);
  switch ( bdata->GetSymbolCode("enum_type","struct_type","type_def","union_type") )
  {
    case 1 : term = LoadEnumType(bdata);
             break;
    case 2 : term = LoadStructType(bdata);
             break;
    case 3 : // term = LoadTypeDef(bdata);
             // break;
    case 4 : // term = LoadUnionType(bdata);
             // break;
    default: SDBERR(380)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadTypeDcl"

logical SchemaResources :: LoadTypeDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  PropertyHandle          ph;
  int                     indx0 = 0;
  logical                 term  = NO;
BEGINSEQ
// type_dcl := namespace_dcl | type_def | struct_type | union_type | enum_type
  if ( !bdata )                                      LEAVESEQ
  
  bdata = bdata->GetElement(0);
  switch ( bdata->GetSymbolCode("namespace_dcl", "type_def", "struct_type", 
                                "union_type", "enum_type") )
  {
    case 1 : LoadNamespace(ph_ptr,bdata,del_opt);    
             break;
    case 2 : LoadTypeDef(ph_ptr->GPH("type_defs"),bdata,del_opt); 
             break;
    case 3 : LoadStructType(ph_ptr->GPH("structures"),bdata,del_opt);    
             break;
    case 4 : LoadUnionType(ph_ptr->GPH("unions"),bdata,del_opt);    
             break;
    case 5 : LoadEnumType(ph_ptr->GPH("value_lists"),bdata,del_opt); 
             break;
    default : ;
  }
  

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadTypeDef - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadTypeDef"

logical SchemaResources :: LoadTypeDef (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  PropertyHandle          ph;
  BNFData                *def;
  int                     indx0 = 0;
  logical                 term  = NO;
BEGINSEQ
// type_def := _typedef type_spec [declarators]
  if ( !bdata || !schema_only )                      LEAVESEQ
  
  def = bdata->GetElement(1);
  
  if ( def->IsSymbol("constr_type_spec") )
    LoadTypeDcl(ph_ptr,def,del_opt); 
  else ; // simple rype spec definition missing

  if ( def = bdata->GetElement(2) )
    OQLSET(99)  // declarators müssen vielleict noch unterstützt werden
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadTypeReference - 



\return term - 

\param  bdata - 
\param  scope_ph - 
\param  type_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadTypeReference"

logical SchemaResources :: LoadTypeReference (BNFData *bdata, PropertyHandle scope_ph, PropertyHandle type_ph )
{
  int                     count = bdata->GetElementCount();
  BNFData                *identifier = bdata->GetElement(0);
  int                     indx0 = 0;
  logical                 first = YES;
  logical                 term = NO;
// scoped_name     := identifier [ scoped_name_ext(*) ]
// scoped_name_ext := '::' identifier

  scope_ph = "";
  while ( ++indx0 < count )
  {
    if ( !first )
      scope_ph += "::";
    first = NO;
    scope_ph += identifier->StringValue();
    if ( identifier = bdata->GetElement(indx0) )
      identifier = identifier->GetElement(1);
  }
  if ( identifier )
    type_ph += identifier->StringValue();

  return(term);
}

/******************************************************************************/
/**
\brief  LoadUnionType - 



\return term - 

\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadUnionType"

logical SchemaResources :: LoadUnionType (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  int                     indx0 = 0;
  logical                 term  = NO;
BEGINSEQ
// union_dcl
  if ( !bdata )                                      LEAVESEQ
  
// not yet supported, ignored
  SDBEV1(bdata->StringValue(),UNDEF)                 SDBERR(434)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadViewDcl - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadViewDcl"

logical SchemaResources :: LoadViewDcl (BNFData *bdata )
{
  DBStructDef            *strdef;
  BNFData                *vheader;
  int32                   index = 0;
  char                    name[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
// view_dcl    := view_header [ view_def ]
// view_header := view identifier from_spec [where_spec] [group_spec] [having_spec] [type_property_list]
// where_spec  := where condition 
// having_spec := having condition 
// condition   := '(' operand ')'
  
  if ( !bdata )                                    LEAVESEQ
  
  vheader = bdata->GetElement(0);
  gvtxstb(name,vheader->GetElement("identifier")->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  
  if ( !(strdef = ProvideStructDef(name)) )        ERROR
  strdef->smcbstyp = ST_VIEW;
  strdef->smcbatyp = AT_VIEW;
  
  if ( schema_only )
  {
    strdef->set_view_struct(new DBViewStructDef(strdef,vheader));
    if ( CreateTypeProperties(strdef,vheader) )      ERROR
  }
  
  if ( bdata = bdata->GetElement("view_def") )
    LoadViewMembers(strdef,bdata);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph_ptr - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadViewDcl"

logical SchemaResources :: LoadViewDcl (PropertyHandle *ph_ptr, BNFData *bdata, logical del_opt )
{
  DatabaseHandle          dbh(resources->GetDBHandle());
  PropertyHandle          pph;
  PropertyHandle          vph;
  BNFData                *spec;
  BNFData                *vheader;
  int32                   index = 0;
  char                    name[ID_SIZE];
  logical                 term  = NO;
BEGINSEQ
// view_dcl    := view_header [ view_def ]
// view_header := view identifier from_spec [where_spec] [group_spec] [having_spec] [type_property_list]
// where_spec  := where condition 
// having_spec := having condition 
// condition   := '(' operand ')'
  
  if ( !bdata )                                      LEAVESEQ
  
  vheader = bdata->GetElement(0);
  gvtxstb(name,vheader->GetElement("identifier")->StringValue(),sizeof(name));
  SDBEV1(name,ID_SIZE) 
  
  if ( !ph_ptr )
  {
    if ( vph.Open(dbh,"SDB_View",PI_Write) )  ERROR
    if ( pph.Open(dbh,"SDB_ODABA_Str",PI_Write) ) ERROR
  }
  else
  {
    if ( vph.Open(ph_ptr,"views") )                ERROR
    if ( pph.Open(ph_ptr,"pstructures") )            ERROR
  }

  if ( !vph.Provide(name) )                            ERROR
  *vph.GPH("typetype") = (int32)TYP_Structure;
  *vph.GPH("smcestyp") = (int32)ST_VIEW;
  *vph.GPH("access_type") = (int32)AT_VIEW;
  
  if ( del_opt )
  {
    vph.GPH("smcebase")->DeleteSet();
    vph.GPH("smcepsmc")->DeleteSet();
    vph.GPH("from")->DeleteSet();
    vph.GPH("where")->DeleteSet();
    vph.GPH("group_by")->DeleteSet();
    vph.GPH("having")->DeleteSet();
    vph.GPH("smcepdde")->DeleteSet();
    vph.GPH("smcepref")->DeleteSet();
    vph.GPH("smcershp")->DeleteSet();
    vph.GPH("members")->DeleteSet();
    vph.GPH("pfunctions")->DeleteSet();
    
    vph.GPH("constants")->DeleteSet();
  }
  
  if ( spec = vheader->GetElement("from_spec") )
    CreateViewBase(*vph.GPH("from"),spec);
  if ( spec = vheader->GetElement("where_spec") )
    *vph.GPH("where") = spec->GetElement(1)->GetElement(1)->StringValue();
  if ( spec = vheader->GetElement("group_spec") )
    CreateGrouping(*vph.GPH("group_by"),spec);
  if ( spec = vheader->GetElement("having_spec") )
    *vph.GPH("having") = spec->GetElement(1)->GetElement(1)->StringValue();
  
  if ( bdata = bdata->GetElement("view_def") )
    LoadViewMembers(vph,bdata,NO);
  
  vph.Save();
  vph.Cancel();
  
  if ( CreateTypeProperties(pph,name,vheader,del_opt) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadViewMembers - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  strdef - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadViewMembers"

logical SchemaResources :: LoadViewMembers (DBStructDef *strdef, BNFData *bdata )
{
  int                     indx0 = 0;
  BNFData                *exports;
  logical                 term = NO;
// view_def    := '{' view_member(*) '}' 
// view_member := attr_dcl | ref_dcl | method

  while ( (exports = bdata->GetElement(++indx0)) &&
          exports->IsSymbol("view_member")                   )
  {
    exports = exports->GetElement(0)->GetElement(0);
    switch ( exports->GetSymbolCode("attr_dcl","ref_dcl","expr_def","method") )
    {
      case 1 : LoadAttributeDcl(strdef,exports->GetElement("attr_dcl"));    
               break;
      case 2 : LoadReferenceDcl(strdef,exports->GetElement("ref_dcl"));    
               break;
      case 3 : LoadExpression(exports->GetElement("expr_def"),strdef);  
               break;
      case 4 : // LoadMethodDcl((strdef,exports->GetElement("type_dcl"));        
               break;
      default : ;
    }
  }  

  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadViewMembers"

logical SchemaResources :: LoadViewMembers (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  int                     indx0 = 0;
  BNFData                *dcldata; 
  BNFData                *exports;
  logical                 term  = NO;
// view_def    := '{' view_member(*) '}' 
// view_member := attr_dcl | ref_dcl | method
  
  if ( del_opt )
  {
    ph.GPH("smcepdde")->DeleteSet();
    ph.GPH("smcepref")->DeleteSet();
    ph.GPH("smcershp")->DeleteSet();
    ph.GPH("members")->DeleteSet();
    ph.GPH("pfunctions")->DeleteSet();
    
    ph.GPH("constants")->DeleteSet();
//    ph.GPH("enums")->DeleteSet();
//    ph.GPH("classes")->DeleteSet();
//    ph.GPH("exceptions")->DeleteSet();
  }
  
  while ( (exports = bdata->GetElement(++indx0)) &&
          exports->IsSymbol("exports")                   )
  {
    dcldata = exports->GetElement(0)->GetElement(0);
    switch ( dcldata->GetSymbolCode("attr_dcl","ref_dcl","method") )
    {
      case 1 : LoadAttributeDcl(*ph.GPH("smcepdde"),dcldata);    break;
      case 2 : LoadReferenceDcl(*ph.GPH("smcepref"),dcldata);    break;
      case 3 : LoadMethodDcl(*ph.GPH("pfunctions"),dcldata);     break;
      default : ;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  LoadWindow - 



\return term - 

\param  ph - 
\param  bdata - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadWindow"

logical SchemaResources :: LoadWindow (PropertyHandle &ph, BNFData *bdata, logical del_opt )
{
  BNFData                *defdata; 
  logical                 term  = NO;
BEGINSEQ
// control        := _control identifier ';'

   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideStructDef - 



\return strdef - 

\param  strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDef"

DBStructDef *SchemaResources :: ProvideStructDef (char *strnames )
{
  DBStructDef            *strdef = NULL;
  SDBEV1(strnames,ID_SIZE) 
  strdef = (DBStructDef *)dictionary->GetStructDef(strnames);
  if ( schema_only && !strdef )
    strdef = dictionary->ProvideTempStructDef(strnames);

  return(strdef);
}

/******************************************************************************/
/**
\brief  SchemaResources - 




\param  dictptr - 
\param  resobj - 
\param  obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SchemaResources"

     SchemaResources :: SchemaResources (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle )
                     : odaba_client(),
  dictionary(dictptr),
  resources(resobj),
  database(obhandle),
  schema_only(AUTO)

{



}

/******************************************************************************/
/**
\brief  SetConstraint - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetConstraint"

logical SchemaResources :: SetConstraint (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef )
{
  logical                 term = NO;
BEGINSEQ
// ... [constraint] ...  
// constraint := _constraint '(' operand ')'
  
  if ( !bdata->IsA("constraint") )
    bdata = bdata->GetElement("constraint");
  if ( !bdata )                                      LEAVESEQ
    
  // constraints are not allowed for views, use init-values
  if ( strdef->smcbstyp == ST_VIEW )                 SDBERR(99)
  
  fielddef->fmcbinit = YES;
  fielddef->set_constraint(new ExpressionReference(strdef,bdata->GetElement("operand")));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetConstraint"

logical SchemaResources :: SetConstraint (PropertyHandle &ph, BNFData *bdata )
{
  PropertyHandle         *parent = ph.GetParentProperty();
  char                   *attr = "ddeinit";
  logical                 term = NO;
BEGINSEQ
// ... [constraint] ...  
// constraint := _constraint '(' operand ')'
  
  if ( !bdata->IsA("constraint") )
    bdata = bdata->GetElement("constraint");
  if ( !bdata )                                      LEAVESEQ
    
  // constraints are not allowed for views, use init-values
  if ( *parent->GPH("smcestyp") == (int32)ST_VIEW )   SDBERR(99)
  
  *ph.GPH("constraint") = bdata->GetElement("operand")->StringValue();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetInitValue - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInitValue"

logical SchemaResources :: SetInitValue (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef )
{
  BNFData                *avalue;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// ... [assigned_value] ...  
// assigned_value := assign_op operand
  
  if ( !fielddef->fmcbsmcb )
  {
    fielddef->GetDBStruct(dictionary);
  } 
  if ( bdata->IsA("assigned_value") )
    avalue = bdata->GetElement("assigned_value");
  else while ( avalue = bdata->GetElement(indx0++) )
    if ( avalue->IsA("assigned_value") )
      break;
      
  if ( !avalue )                                      LEAVESEQ
  
  if ( strdef && strdef->smcbstyp == ST_VIEW )
  {
    term = fielddef->CreateViewSource(avalue->GetElement("operand"));    
  }
  else
  {
    fielddef->fmcbinit = YES;
    fielddef->set_initval(new ExpressionReference(strdef,avalue->GetElement("operand")));
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInitValue"

logical SchemaResources :: SetInitValue (PropertyHandle &ph, BNFData *bdata )
{
  PropertyHandle         *parent = ph.GetParentProperty();
  BNFData                *avalue;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// ... [assigned_value] ...  
// assigned_value := assign_op operand
  
  if ( bdata->IsA("assigned_value") )
    avalue = bdata->GetElement("assigned_value");
  else while ( avalue = bdata->GetElement(indx0++) )
    if ( avalue->IsA("assigned_value") )
      break;
  
  if ( !avalue )                                      LEAVESEQ
    
  if ( *parent->GPH("smcestyp") == (int32)ST_VIEW )
  {
    term = CreateViewSource(*ph.GPH("source"),NULL,avalue->GetElement("operand"));
  }
  else
    *ph.GPH("ddeinit") = avalue->GetElement("operand")->StringValue();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetMemberExtensions - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMemberExtensions"

logical SchemaResources :: SetMemberExtensions (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef )
{
  logical                 term = NO;
BEGINSEQ
// ... [attr_ext_decl] ...  
// attr_ext_decl := sources | constraint | version
 
  if ( !bdata->IsA("attr_ext_decl") )
    bdata = bdata->GetElement("attr_ext_decl");
  if ( !bdata )                                      LEAVESEQ
  
  switch ( bdata->GetSymbolCode("sources","constraint","version") )
  {
    case 1 : SetSources(fielddef,bdata->GetElement(0),strdef);    break;
    case 2 : SetConstraint(fielddef,bdata->GetElement(0),strdef); break;
    case 3 : SetVersion(fielddef,bdata->GetElement(0));    break;
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMemberExtensions"

logical SchemaResources :: SetMemberExtensions (PropertyHandle &ph, BNFData *bdata )
{
  BNFData                *ival;
  PropertyHandle         *parent = ph.GetParentProperty();
  char                   *attr = "ddeinit";
  logical                 term = NO;
// attr_ext_decl := sources | constraint | version
  
  switch ( bdata->GetSymbolCode("sources","constraint","version") )
  {
    case 1 : SetSources(ph,bdata->GetElement(0));     break;
    case 2 : SetConstraint(ph,bdata->GetElement(0));  break;
    case 3 : SetVersion(ph,bdata->GetElement(0));     break;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetReferenceLevel - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  indx_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReferenceLevel"

logical SchemaResources :: SetReferenceLevel (DBFieldDef *fielddef, BNFData *bdata, int32 &indx_ref )
{
  char                   *gen_type;
  logical                 term  = NO;
BEGINSEQ
// meth_dcl       := .... [ref_symbol(*)] ... 
  
  switch ( fielddef->fmcbrlev = ((BNFExpData *)bdata)->GetReferenceLevel(indx_ref) )
  {
    case -1   : fielddef->set_by_reference(YES);
                fielddef->fmcbrlev = R_DIRECT;       break;
    case ERIC : ERROR
    default   : ;
  }
  
  if ( gen_type = (char *)fielddef->get_gen_type() )
    if ( !gvtsicmp(gen_type,"PI",UNDEF) || !gvtsicmp(gen_type,"SET",UNDEF) || 
         !gvtsicmp(gen_type,"BAG",UNDEF) || !gvtsicmp(gen_type,"LIST",UNDEF)  )
    {
      fielddef->fmcbrlev = R_REFR;
      fielddef->fmcbdim  = 0;
    }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i0 - 



\param  ph - 
\param  bdata - 
\param  index_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReferenceLevel"

logical SchemaResources :: SetReferenceLevel (PropertyHandle &ph, BNFData *bdata, int32 &index_ref )
{
  int32                   ref_level = 0;
  logical                 term = NO;
BEGINSEQ
// declarator := ref_symbol(*)

  if ( ref_level = ((BNFExpData *)bdata)->GetReferenceLevel(index_ref) < -1 )
                                                     ERROR
  *ph.GPH("reference_level") = ref_level;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetSources - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSources"

logical SchemaResources :: SetSources (DBFieldDef *fielddef, BNFData *bdata, DBStructDef *strdef )
{
  BNFData                *parameter;
  BNFData                *source_op;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// ... [sources] ...  
// sources        := _source operand_list
// operand_list   := '(' [parm_list] ')' 
// parm_list      := parameter [parm_ext(*)]
// parm_ext       := ',' parameter
// parameter      := parm_spec | operand | '*'
// parm_spec      := [simple_type_spec] [ref_symbol(*)] identifier [fixed_array_size(*)] [assigned_value]
  
  if ( !bdata->IsA("sources") )
    bdata = bdata->GetElement("sources");
  if ( !bdata )                                      LEAVESEQ
    
  // sources are allowed for views, only. use init-values
  if ( strdef->smcbstyp != ST_VIEW )                 SDBERR(99)
  
  if ( !(bdata = bdata->GetElement("parm_list")) )   ERROR
  parameter = bdata->GetElement(0);
  while ( parameter )
  {
    if ( source_op = parameter->GetElement("assigned_value") )
      source_op = source_op->GetElement("operand");
    fielddef->CreateViewSource(parameter->GetElement("assigned_value"));    
    if ( parameter = bdata->GetElement(++indx0) )
      parameter = parameter->GetElement(1);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSources"

logical SchemaResources :: SetSources (PropertyHandle &ph, BNFData *bdata )
{
  PropertyHandle         *parent = ph.GetParentProperty();
  BNFData                *parameter;
  BNFData                *source_op;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// ... [sources] ...  
// sources        := _source operand_list
// operand_list   := '(' [parm_list] ')' 
// parm_list      := parameter [parm_ext(*)]
// parm_ext       := ',' parameter
// parameter      := parm_spec | operand | '*'
// parm_spec      := [simple_type_spec] [ref_symbol(*)] identifier [fixed_array_size(*)] [assigned_value]
  
  if ( !bdata->IsA("sources") )
    bdata = bdata->GetElement("sources");
  if ( !bdata )                                      LEAVESEQ
    
  // sources are allowed for views, only. use init-values
  if ( *parent->GPH("smcestyp") != (int32)ST_VIEW )  SDBERR(99)
  
  if ( !(bdata = bdata->GetElement("parm_list")) )   ERROR
  parameter = bdata->GetElement(0);
  while ( parameter )
  {
    if ( source_op = parameter->GetElement("assigned_value") )
      source_op = source_op->GetElement("operand");
    CreateViewSource(*ph.GPH("source"),
                     parameter->GetElement("identifier"),
                     parameter->GetElement("assigned_value"));    
    if ( parameter = bdata->GetElement(++indx0) )
      parameter = parameter->GetElement(1);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetVersion - 



\return term - 
-------------------------------------------------------------------------------
\brief  d0 - 



\param  fielddef - Internal field defintion
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical SchemaResources :: SetVersion (DBFieldDef *fielddef, BNFData *bdata )
{
  logical                 term = NO;
BEGINSEQ
// version := _version number
  
  if ( !bdata )                                      LEAVESEQ
    
  fielddef->set_version(bdata->GetElement(1)->IntValue());

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical SchemaResources :: SetVersion (PropertyHandle &ph, BNFData *bdata )
{
  PropertyHandle         *parent = ph.GetParentProperty();
  char                   *attr = "ddeinit";
  logical                 term = NO;
BEGINSEQ
// version := _version number
  
  if ( !bdata )                                      LEAVESEQ
    
  *ph.GPH("version") = bdata->GetElement(1)->IntValue();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Validate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Validate"

logical SchemaResources :: Validate ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( dictionary->SetupTempStructures() )          ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~SchemaResources - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SchemaResources"

     SchemaResources :: ~SchemaResources ( )
{



}


