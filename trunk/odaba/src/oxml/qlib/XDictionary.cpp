/********************************* Class Source Code ***************************/
/**
\package  OXML - 
\class    XDictionary

\brief    


\date     $Date: 2006/08/26 12:57:48,71 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XDictionary"

#include  <pOXML.h>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBStructDef.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sNString.hpp>
#include  <sXMLElement.hpp>
#include  <sXMLString.hpp>
#include  <igvts.h>
#include  <igvtx.h>
#include  <sXDictionary.hpp>


/******************************************************************************/
/**
\brief  CreateAttribute - 



\return term - Termination code

\param  strdefptr - 
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAttribute"

logical XDictionary :: CreateAttribute (DBStructDef *strdefptr, XMLElement *xelement )
{
  char           *value = NULL;
  DBFieldList    *flist = (DBFieldList *)strdefptr->smcbfmcl;
  DBFieldDef     *fielddef;
  logical         term = NO;
BEGINSEQ
  if ( !(fielddef = flist->CreateField(strdefptr->get_base_info().get_count()+
                                       strdefptr->get_attr_info().inc_count() ) ) )
                                                    SDBERR(99)
  fielddef->fmcbdim = 0;
  InitMember(fielddef,xelement);
  if ( !fielddef->fmcbdim )                         SDBERR(99)


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateInheritance - 



\return term - Termination code

\param  strdefptr - 
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInheritance"

logical XDictionary :: CreateInheritance (DBStructDef *strdefptr, XMLElement *xelement )
{
  char           *value = NULL;
  DBFieldList    *flist = (DBFieldList *)strdefptr->smcbfmcl;
  DBFieldDef     *fielddef;
  logical         term = NO;
BEGINSEQ
  if ( !(fielddef = flist->CreateField(strdefptr->get_base_info().inc_count() )) )
                                                    SDBERR(99)
  fielddef->fmcbbstr = YES;
  InitRelationship(fielddef,xelement);
  gvtxstb(fielddef->fmcbname,fielddef->fmcbtype,ID_SIZE);
  fielddef->fmcbdim  = 1;
  fielddef->fmcbrlev = R_DIRECT;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateKey - 



\return term - Termination code

\param  strdefptr - 
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKey"

logical XDictionary :: CreateKey (DBStructDef *strdefptr, XMLElement *xelement )
{
  char           *value = NULL;
  logical         term = NO;
// name
// <xs:attribute name="keyComponents" type="xs:string"/> <!-- one or more order key components separated by comma, e.g. "name(descending),first_name" -->
// <xs:attribute name="identKey" type="xs:boolean" default="false"/>
// <xs:attribute name="descending" type="xs:boolean" default="false"/>
// <xs:attribute name="ignoreCase" type="xs:boolean" default="false"/>

  return(term);
}

/******************************************************************************/
/**
\brief  CreateMember - 



\return term - Termination code

\param  strdefptr - 
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMember"

logical XDictionary :: CreateMember (DBStructDef *strdefptr, XMLElement *xelement )
{
  char           *value = NULL;
  DBFieldDef      temp_field;
  int32           min_dim = 1;
  int32           max_dim = 1;
  logical         term = NO;
BEGINSEQ
  InitMember(&temp_field,xelement);
  
  if ( !xelement->GetAttributeValue(NULL,"type") )  // inline definition, supported for collections, only
  {
    if ( CreateReference(strdefptr,xelement) )      ERROR
  }
  else 
    if ( CreateAttribute(strdefptr,xelement) )   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateReference - 



\return term - Termination code

\param  strdefptr - 
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReference"

logical XDictionary :: CreateReference (DBStructDef *strdefptr, XMLElement *xelement )
{
  char           *value = NULL;
  DBFieldList    *flist = (DBFieldList *)strdefptr->smcbfmcl;
  DBFieldDef     *fielddef;
  logical         term = NO;
BEGINSEQ
  if ( !(fielddef = flist->CreateField(strdefptr->get_base_info().get_count()+
                                       strdefptr->get_attr_info().get_count()+
                                       strdefptr->get_refr_info().inc_count() ) ) )
                                                    SDBERR(99)
  fielddef->fmcbdim = 0;
  InitCollection(fielddef,xelement);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRelationship - 



\return term - Termination code

\param  strdefptr - 
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRelationship"

logical XDictionary :: CreateRelationship (DBStructDef *strdefptr, XMLElement *xelement )
{
  char           *value = NULL;
  DBFieldList    *flist = (DBFieldList *)strdefptr->smcbfmcl;
  DBFieldDef     *fielddef;
  logical         term = NO;
BEGINSEQ
  if ( !(fielddef = flist->CreateField(strdefptr->get_base_info().get_count()+
                                       strdefptr->get_attr_info().get_count()+
                                       strdefptr->get_refr_info().get_count()+
                                       strdefptr->get_rshp_info().inc_count() ) ) )
                                                    SDBERR(99)
  fielddef->fmcbdim = 0;
  InitRelationship(fielddef,xelement);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetExtent - 



\return ext_name - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtent"

char *XDictionary :: GetExtent (int32 indx0 )
{
  DBExtend   *extdef   = NULL;
  char       *ext_name = NULL;
BEGINSEQ
  if ( !(extdef = extdef_list.Get(indx0)) )        ERROR
  ext_name = extdef->fmcbname;
RECOVER
  ext_name = NULL;
ENDSEQ
  return(ext_name);
}

/******************************************************************************/
/**
\brief  InitCollection - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitCollection"

logical XDictionary :: InitCollection (DBFieldDef *fielddef, XMLElement *xelement )
{
  XMLElement     *xlm;
  char           *value = NULL;
  char           *pos;
  logical         term = NO;

BEGINSEQ
// Extents are created when being defined as root elements in the schema or within the OXMLDatabase element
//  <xs:element minOccurs="0" maxOccurs="1" name="extentname" /> 
//    <xs:complexType>
//      <xs:sequence>
//        <xs:element minOccurs="0" maxOccurs="unbounded" type="datatype" />
//      </xs:sequence>
//    </xs:complexType>
//  </xs:element" /> 
  if ( !fielddef->fmcbbstr )  // not a base structure
  {
    if ( !(value = xelement->GetAttributeValue("name")) )  SDBERR(385)
    TypeKey    tkey(value,0);
    gvtxstb(fielddef->fmcbname,tkey.Name(),ID_SIZE);

    if ( !(xlm = xelement->GetElement(xs_prefix,"complexType")) ) // collections must have an imbedded type definition
                                                    SDBERR(99)
    xlm->ResetCurrent();
    if ( !(xlm = xlm->GetNextElement()) || // sequence, choice or all
         !(xlm = xlm->GetElement(xs_prefix,"element")) )
                                                    SDBERR(388)
    xelement = xlm;
  }
  InitMember(fielddef,xelement);
  fielddef->fmcbrlev = R_REFR;
  
// init options
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"multipleKey") )      
    fielddef->set_multikey(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"noCreate") )      
    fielddef->set_create(NO);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"update") )      
    fielddef->set_update(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"weakTyped") )      
    fielddef->set_weak_typed(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"owner") )      
    fielddef->set_owning(YES);

// init order keys
  if ( value = xelement->GetAttributeValue(oxs_prefix,"orderKeys") )      
    InitIndexes(fielddef,value);
  else  // create default index
    fielddef->CreateIndex();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitExtent - 



\return term - Termination code

\param  extdef - Internal extent definition
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExtent"

logical XDictionary :: InitExtent (DBExtend *extdef, XMLElement *xelement )
{
  char           *value = NULL;
  char           *pos;
  logical         term = NO;

  InitCollection(extdef,xelement);

// init options
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"complete") )      
    extdef->set_union_set(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"distinct") )      
    extdef->set_disjunct(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"intersect") )      
    extdef->set_intersect(YES);
  extdef->set_acctype(AT_ODABA);
// missing
// super sets : <xs:attribute name="subSet" type="xs:string"/>
// sub sets   : <xs:attribute name="superSet" type="xs:string"/>

  return(term);
}

/******************************************************************************/
/**
\brief  InitIndex - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  indexes_str - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitIndex"

logical XDictionary :: InitIndex (DBFieldDef *fielddef, char *indexes_str )
{
  char           *pos;
  logical         term = NO;

// key_name1(unique,temporary,caseSensitive,noEmpty)
//

  return(term);
}

/******************************************************************************/
/**
\brief  InitIndexes - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  indexes_str - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitIndexes"

logical XDictionary :: InitIndexes (DBFieldDef *fielddef, char *indexes_str )
{
  char           *pos;
  logical         term = NO;

// one or more order keys separated by comma, e.g. "key_name1(unique),keyname2"
  while ( pos = strchr(indexes_str,',') )
  {
    *pos = 0;
    InitIndex(fielddef,indexes_str);
    *pos = ',';
    indexes_str = pos+1;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  InitMember - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMember"

logical XDictionary :: InitMember (DBFieldDef *fielddef, XMLElement *xelement )
{
  static char    *xtypes[] = {"string", "int", "decimal", "boolean", "date", "time", "dateTime", "double", "float"};
  static char    *privs[] = {"private", "public", "protected"};
  static char    *rlevs[] = {"byValue", "byReference", "byPointer", "byPointerPointer", "generic"};
  char           *value = NULL;
  char           *pos;
  int8            max_align = 0;
  logical         term = NO;

BEGINSEQ
  fielddef->set_mb_number(0);

// init Name
  if ( *fielddef->fmcbname <= ' ' )
    if ( value = xelement->GetAttributeValue("name") )
      gvtxstb(fielddef->fmcbname,value,ID_SIZE);
  
// init Type
  if ( !(value = xelement->GetAttributeValue(oxs_prefix,"dataType")) )      
    if ( !(value = xelement->GetAttributeValue("base")) )      
      value = xelement->GetAttributeValue("type");
  if ( value )      
  {
    if ( pos = strchr(value,':') )
      value = pos+1;
    switch ( STRToPosition(value,sizeof(xtypes)/sizeof(xtypes[0]),xtypes) )
    {
      case 1 : value = "STRING";
               fielddef->fmcbityp = T_STRING;
               fielddef->fmcbsize = 255;
               break;
      case 2 : value = "INT";
               fielddef->fmcbityp = T_INT;
               fielddef->fmcbsize = 10;
               break;
      case 3 : value = "REAL";
               fielddef->fmcbityp = T_REAL;
               fielddef->fmcbsize = 17;
               break;
      case 4 : value = "LOGICAL";
               fielddef->fmcbityp = T_LO;
               fielddef->fmcbsize = 1;
               break;
      case 5 : value = "DATE";
               fielddef->fmcbityp = T_DATE;
               fielddef->fmcbsize = 10;
               break;
      case 6 : value = "TIME";
               fielddef->fmcbityp = T_TIME;
               fielddef->fmcbsize = 8;
               break;
      case 7 : value = "DATETIME";
               fielddef->fmcbityp = T_DATETIME;
               fielddef->fmcbsize = 19;
               fielddef->fmcbesu(GetStructDef("DATETIME"),0,0,max_align);
               break;
      case 8 : value = "REAL";
               fielddef->fmcbityp = T_REAL;
               fielddef->fmcbsize = 17;
               break;
      case 9 : value = "REAL";
               fielddef->fmcbityp = T_REAL;
               fielddef->fmcbsize = 7;
               break;
//      default: if ( !(fielddef->fmcbsmcb = ProvideTempStructDef(value)) )
//                                                    SDBERR(99)
    }
  } 
  if ( !value )
    value = "VOID";
  gvtxstb(fielddef->fmcbtype,value,ID_SIZE);

// init dimension
  if ( !(value = xelement->GetAttributeValue(oxs_prefix,"dimension")) )
    if ( !(value = xelement->GetAttributeValue("maxOccurs")) )
      value = xelement->GetAttributeValue("minOccurs");
  if ( value )
    fielddef->fmcbdim = atoi(value);
    
// init size
  if ( value = xelement->GetAttributeValue(oxs_prefix,"size") )
    fielddef->fmcbdim = atoi(value);

// init precision
  if ( value = xelement->GetAttributeValue(oxs_prefix,"precision") )
    fielddef->fmcbprec = atoi(value);

// init privilege
  if ( value = xelement->GetAttributeValue(oxs_prefix,"privilege") )      
  {
    if ( pos = strchr(value,':') )
      value = pos+1;
    switch ( STRToPosition(value,sizeof(privs)/sizeof(privs[0]),privs) )
    {
      case 1 : fielddef->set_privilege(PI_Exclusive);
               break;
      case 2 : fielddef->set_privilege(PI_Share);
               break;
      case 3 : fielddef->set_privilege(PI_unknown);
               break;
    }
  } 

// init reference level
  if ( value = xelement->GetAttributeValue(oxs_prefix,"privilege") )      
  {
    if ( pos = strchr(value,':') )
      value = pos+1;
    switch ( STRToPosition(value,sizeof(rlevs)/sizeof(rlevs[0]),rlevs) )
    {
      case 1 : fielddef->fmcbrlev = R_DIRECT;
               break;
      case 2 : fielddef->fmcbrlev = R_REFR;
               break;
      case 3 : fielddef->fmcbrlev = 1;
               break;
      case 4 : fielddef->fmcbrlev = 2;
               break;
      case 5 : fielddef->fmcbrlev = R_GENERIC;
               break;
    }
  } 

// init version
  if ( value = xelement->GetAttributeValue(oxs_prefix,"version") )      
    fielddef->set_version(atoi(value));

// init default
  if ( value = xelement->GetAttributeValue("default") )      
    fielddef->set_initval(value,UNDEF);

// init options
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"static") )      
    fielddef->fmcbstat = YES;
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"virtual") )      
    fielddef->fmcbvirt = YES;
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"deleteEmpty") )      
    fielddef->set_del_empty(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"guid") )      
    fielddef->set_global_identity(YES);
//  if ( xelement->IsAttributeValueTrue(oxs_prefix,"notEmpty") )      
//    fielddef->set_no_empty(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"transient") )      
    fielddef->set_transient(YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitRelationship - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRelationship"

logical XDictionary :: InitRelationship (DBFieldDef *fielddef, XMLElement *xelement )
{
  char           *value = NULL;
  char           *pos;
  logical         term = NO;

  InitCollection(fielddef,xelement);

// init base collection
  if ( value = xelement->GetAttributeValue(oxs_prefix,"baseCollection") )      
    fielddef->SetExtent(value);

// init inverse
  if ( value = xelement->GetAttributeValue(oxs_prefix,"inverse") )      
    fielddef->set_inverse_name(value);

// init options
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"dependent") )      
    fielddef->set_depend(YES);
  if ( xelement->IsAttributeValueTrue(oxs_prefix,"secondary") )      
    fielddef->set_sec_reference(YES);

  return(term);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  cpath - Complete path
\param  xs_prefix - 
\param  oxs_prefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical XDictionary :: Open (char *cpath, char *xs_prefix, char *oxs_prefix )
{
  XMLString   xs(cpath);
  XMLElement *xelement;
  XMLElement *xschema;
  NString     prefix, schema, element, simple_type, complex_type;
  logical     term = NO;
BEGINSEQ
  if ( xs_prefix )
    this->xs_prefix = strdup(xs_prefix);
  if ( oxs_prefix )
    this->oxs_prefix = strdup(oxs_prefix);

  if ( xs_prefix && *xs_prefix )
    prefix << xs_prefix << ':';
  schema << prefix << "schema";
  if ( !(xschema = xs.GetElementRecursive(schema)) ) SDBERR(384)

  element      << prefix << "element";
  simple_type  << prefix << "simpleType";
  complex_type << prefix << "complexType";

  xschema->ResetCurrent();
  while ( xelement = xschema->GetNextElement() )
  {
    switch ( xelement->GetTypeNumber(element,simple_type,complex_type) )
    {
      case 1 : if ( ReadXExtents(xelement) )        ERROR
               break;
      case 2 : if ( ReadXEnum(xelement) )           ERROR
               break;
      case 3 : if ( ReadXStruct(xelement) )         ERROR
               break;
      default: ; // skip other elements as e.g. ?xml or comments
    }
  }
  SetupTempStructures();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadXEnum - 



\return term - Termination code

\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadXEnum"

logical XDictionary :: ReadXEnum (XMLElement *xelement )
{
  XMLElement     *xlm;
  XMLAttribute   *xattr;
  DBExtend       *extdef;
  DBStructDef    *strdefptr;
  ENUM_ValueList *vlist;
  char           *value = NULL;
  int32           code;
  logical         term = NO;
BEGINSEQ
  if ( !(xattr = xelement->GetAttribute("name")) )  SDBERR(385)
  TypeKey    tkey(xattr->GetValue(),0);
  SDBEV1(tkey.Name(),ID_SIZE)

  strdefptr = ProvideCSDecl(tkey,NULL,UNDEF);
  extdef = new DBExtend (this,xelement->GetAttributeValue(oxs_prefix,"dataType"),
                         NULL,strdefptr,0);
  strdefptr->smcbacc = (vlist = extdef->get_cs_values());
  if ( !strdefptr->smcbityp )
    strdefptr->smcbityp = TEMPSID;
  strdefptr->smcbatyp = AT_CODE;
  
  if ( xlm = xelement->GetElement(xs_prefix,"restriction") )
    xelement = xlm;
  
  xlm->ResetCurrent();
  while ( xlm = xelement->GetNextElement() )
    if ( xlm->IsElement(xs_prefix,"enumeration") )
    {
      if ( value = xlm->GetAttributeValue(oxs_prefix,"enumVal") )
        code = atoi(value);
      else
        code = vlist->NextCode();
      vlist->AddValue(code,xlm->GetAttributeValue(NULL,"value"),
                      xlm->GetAttributeValue(oxs_prefix,"dataType"),
                      NULL,NULL,NULL);
    }

  extdef_list.Insert(extdef);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadXExtent - 



\return term - Termination code

\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadXExtent"

logical XDictionary :: ReadXExtent (XMLElement *xelement )
{
  XMLElement     *xlm;
  DBExtend       *extdef = NULL;
  DBStructDef    *strdefptr;
  char           *value = NULL;
  logical         term = NO;
// Extents are created when being defined as root elements in the schema or within the OXMLDatabase element
//  <xs:element minOccurs="0" maxOccurs="1" name="extentname" /> 
//    <xs:complexType>
//      <xs:sequence>
//        <xs:element minOccurs="0" maxOccurs="unbounded" type="datatype" />
//      </xs:sequence>
//    </xs:complexType>
//  </xs:element" /> 

  extdef = new DBExtend();

  InitExtent(extdef,xelement);
  extdef->SetupNameKey();
  extdef->fmcbvirt = true;   // internally created extent
//extdef->set_transient(YES);// not stored in DB, geht nicht, ist ja auch nicht transient
  extdef_list.Insert(extdef);
  
  

  return(term);
}

/******************************************************************************/
/**
\brief  ReadXExtents - 



\return term - Termination code

\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadXExtents"

logical XDictionary :: ReadXExtents (XMLElement *xelement )
{
  XMLElement     *xlm;
  char           *value = NULL;
  logical         term = NO;
BEGINSEQ
// Extents are created when being defined as root elements in the schema 
// <xs:element name="OXMLDatabase"> <!-- DatabaseExtents, may have any name -->
//   <xs:complexType> 
//     <xs:all> all sugested, but not mandatory (could also be sequence
//       <xs:element minOccurs="0" maxOccurs="1" name="extentname" /> 
//         <xs:complexType>
//           <xs:sequence>
//             <xs:element minOccurs="0" maxOccurs="unbounded" type="datatype" />
//           </xs:sequence>
//         </xs:complexType>
//       </xs:element" /> 
//       ... any number of extents can be defined
//     </xs:all> 
//   </xs:complexType> 

  if ( !(value = xelement->GetAttributeValue("name")) )  SDBERR(385)
  if ( strcmp(value,"OXMLDatabase") ) // not an ODABA XML Extent definition
  {
    if ( ReadXExtent(xelement) )                      ERROR
    LEAVESEQ
  }

  if ( (xlm = xelement->GetElement(xs_prefix,"complexType")) &&   // complexType
       (xlm = xlm->GetElement(0)) )                               // all, sequence or choice
  {
    xlm->ResetCurrent();
    while ( xelement = xlm->GetNextElement() )                   // Get Extent-Element definition
      if ( ReadXExtent(xelement) )
        term = YES;
  }
  
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadXStruct - 



\return term - Termination code

\param  xelement - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadXStruct"

logical XDictionary :: ReadXStruct (XMLElement *xelement )
{
  XMLElement     *xlm;
  DBStructDef    *strdefptr;
  char           *mem_types[] = {"BaseType", "Attribute", "Reference", "Relationship", "Key"};
  char           *value;
  char           *strnames;
  logical         term = NO;
BEGINSEQ
// hier müssen wir element 'Extent' besonders behandeln (ReadOXExtent)

  if ( !(strnames = xelement->GetAttributeValue(NULL,"name")) )   
                                                    SDBERR(385)
  SDBEV1(strnames,UNDEF)
  strdefptr = ProvideTempStructDef(strnames);
  if ( value = xelement->GetAttributeValue(oxs_prefix,"version") )
    strdefptr->set_schema_vers(atoi(value));
  if ( value = xelement->GetAttributeValue(oxs_prefix,"alignment") )
    strdefptr->defined_align = atoi(value);
  if ( (value = xelement->GetAttributeValue(oxs_prefix,"guid")) && !strcmp(value,"true") )
    strdefptr->set_global_identity(YES);
    
  if ( xlm = xelement->GetElement(xs_prefix,"complexContent") )
  {
    xelement = xlm;
    if ( xlm = xelement->GetElement(xs_prefix,"extension") )
    {
      if ( CreateInheritance(strdefptr,xlm) )
                                                     ERROR
      xelement = xlm;
    }
  }
  if ( xelement->GetElement(xs_prefix,"choice") )    SDBERR(386) // choice not supported yet (union)
  if ( (xlm = xelement->GetElement(xs_prefix,"sequence")) ||
       (xlm = xelement->GetElement(xs_prefix,"all"))    )
    xelement = xlm;
  
  xlm->ResetCurrent();
  while ( xlm = xelement->GetNextElement() )
  {
    if ( xlm->IsElement(xs_prefix,"element") )
    {
      if ( value = xlm->GetAttributeValue(oxs_prefix,"elementType") )
        switch ( STRToPosition(value,sizeof(mem_types)/sizeof(mem_types[1]),mem_types) )
        {
          case 1 : if ( CreateInheritance(strdefptr,xlm) )
                                                    ERROR
                   break;
          case 2 : if ( CreateMember(strdefptr,xlm) )
                                                    ERROR
                   break;
          case 3 : if ( CreateReference(strdefptr,xlm) )
                                                    ERROR
                   break;
          case 4 : if ( CreateRelationship(strdefptr,xlm) )
                                                    ERROR
                   break;
          case 5 : if ( CreateKey(strdefptr,xlm) )  ERROR
                   break;
          default: if ( CreateMember(strdefptr,xlm) )
                                                    ERROR
        }
      else if ( CreateMember(strdefptr,xlm) )       ERROR
    }
  }
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  XDictionary - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  cpath - Complete path
\param  accopt - Access mode
\param  xs_prefix - 
\param  oxs_prefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XDictionary"

     XDictionary :: XDictionary (char *cpath, PIACC accopt, char *xs_prefix, char *oxs_prefix )
                     : Dictionary(),
  xs_prefix(NULL),
  oxs_prefix(NULL)
{
  XMLString   xs(cpath);
  XMLElement *xelement;
  XMLElement *xschema;
  NString     prefix, schema, element, simple_type, complex_type;
  int32       indx0 = 0;
  logical     term = NO;
  OpenDictionary();

  Open(cpath,xs_prefix,oxs_prefix);

}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XDictionary"

     XDictionary :: XDictionary ( )
                     :   Dictionary(),
    xs_prefix(NULL),
    oxs_prefix(NULL)

{

  OpenDictionary();

}


