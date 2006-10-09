/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    SDB_Member

\brief    Structure member
          Structure  or  class  member  are  details  the  structure  definition
          consists   of.   Structure   member   may   appear  in ODABA structure
          definitions  as attributes, reference, relationship or base structure.
          In  ODABA  class  definition  members  appear  also  as  functions  or
          function,  windows  or  documents.  Members  are also used to describe
          function  parameters. In the scope of  a structure or class definition
          member names must be unique.

\date     $Date: 2006/07/12 19:11:38,07 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Member"

#include  <pops7.h>
#include  <ctype.h>
#include  <cutimac.h>
#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
class     SDB_NameSpace;
#include  <sDBFieldDef.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_ResourceRef.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_Type.hpp>
#include  <sk40.hpp>
#include  <spc_SDB_Member.hpp>
#include  <sSDB_Member.hpp>


/******************************************************************************/
/**
\brief  BitSize - 


\return bitstring - 
/******************************************************************************/
/**
\brief  i02 - 


\param  prophdl - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BitSize"

char *SDB_Member :: BitSize (PropertyHandle *prophdl, NString &nstring )
{
  char            *string = NULL;
  nstring = "";
  string = pc_SDB_Member(prophdl).BitSize(nstring);
  return(string);
}

/******************************************************************************/
/**
\brief  CharSize - 


\return string - 
/******************************************************************************/
/**
\brief  i02 - 


\param  prophdl - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CharSize"

char *SDB_Member :: CharSize (PropertyHandle *prophdl, NString &nstring )
{
  int16 csiz = 0;

  nstring = "";
  return ( pc_SDB_Member(prophdl).CharSize(nstring) );

  if ( reference_level == RL_direct )
  {
    switch ( prophdl->GetDictionary().BaseType(ddetype) )
    {
      case T_CCHAR   :
      case T_CHAR    : csiz = ddesize;                     break;
      case T_STRING  : csiz = ddesize+1;                   break;
      case UNDEF     : SDBRESET
      default        : break;
    }

    if ( csiz > 1 )
    {
      nstring += '[';
      nstring += csiz;
      nstring += ']';
    }
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  CreateFieldDef - 


\return fieldptr - 

\param  fieldptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFieldDef"

FieldDef *SDB_Member :: CreateFieldDef (FieldDef *fieldptr )
{


  if ( this ) 
  {  
    memcpy(fieldptr->fmcbname,sys_ident,ID_SIZE);
    memcpy(fieldptr->fmcbtype,ddetype,ID_SIZE);

    fieldptr->fmcbsize = ddesize;
    fieldptr->fmcbdim  = ddedim[0];
    fieldptr->fmcbprec = ddeprec;
    fieldptr->fmcbrlev = reference_level;
  }
  return(fieldptr);

}

/******************************************************************************/
/**
\brief  DataTypeCOMString - 


\return string - 

\param  dbhandle - 
\param  string - 
\param  output_parm - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCOMString"

char *SDB_Member :: DataTypeCOMString (DatabaseHandle &dbhandle, char *string, logical output_parm )
{
  int16 lchange = 0;
  char      rlevel[6];
  logical   term    = NO;

BEGINSEQ
  if ( GetCOMTypeString(dbhandle,string,&lchange) )    ERROR

  memset(rlevel,0,sizeof(rlevel));
  switch ( reference_level )
  {
    case RL_reference : *rlevel = '&';          
    case RL_generic   : 
    case RL_direct    : break;
    default           : memset(rlevel,'*',MIN(sizeof(rlevel),abs(reference_level)));
  }

  if ( output_parm )
    strcat(rlevel,"*");
      
  strcat(strcat(string," "),rlevel);

RECOVER
  *string = 0;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  DataTypeCString - 


\return string - 
/******************************************************************************/
/**
\brief  i01 - 


\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

char *SDB_Member :: DataTypeCString (uint16 len )
{
  DatabaseHandle  dbhandle = structure.GetDBHandle();
  static char     string[DEF_BUFLEN+1];
  return ( DataTypeCString(dbhandle,string,MIN(sizeof(string)-1,len)) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  dbhandle - 
\param  string - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

char *SDB_Member :: DataTypeCString (DatabaseHandle &dbhandle, char *string, uint16 len )
{
  int16 lchange = 0;
  int16 rlen;
  char      rlevel[6];
  logical   term    = NO;

BEGINSEQ
// --> pc_SDB_Member::DataTypeCString(nstring,align=len)

  if ( GetCTypeString(dbhandle,string,&lchange) )    ERROR

  memset(rlevel,0,sizeof(rlevel));
  switch ( reference_level )
  {
    case RL_reference : *rlevel = '&';          
    case RL_generic   : 
    case RL_direct    : break;
    default           : memset(rlevel,'*',MIN(sizeof(rlevel),abs(reference_level)));
  }

  if ( !len )
    strcat(strcat(string," "),rlevel);
  else
  {  
    gvtxstb(string,string,len);
    string[len] = 0;
    if ( rlen = strlen(rlevel) )
      memcpy(string+len-rlen,rlevel,rlen);
  }
RECOVER
  *string = 0;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  Fill - 


\return term - 

\param  dbhandle - 
\param  propnames - 
\param  proptypes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical SDB_Member :: Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes )
{
  char                   *pos  = NULL;
  int32                   nsid;
  logical                 term = NO;
BEGINSEQ
  Initialize();
  gvtxstb(sys_ident,propnames,sizeof(sys_ident));
  if ( pos = strchr(proptypes,'|') )
  {
    *pos = 0;
    gvtxstb(ddetype,proptypes,sizeof(ddetype));
    if ( nsid = atoi(pos+1) )
    {
      TypeKey       tkey(ddetype,nsid);
      tkey.Scope(dbhandle,scope,sizeof(scope)-1);
    }
    *pos = '|';
  }
  else if ( pos = strchr(proptypes,':') )
  {
    if ( pos = TypeKey::GetScopeName(proptypes,scope,sizeof(scope)-1) )
      gvtxstb(ddetype,pos,ID_SIZE);
  }
  else 
    gvtxstb(ddetype,proptypes,sizeof(ddetype));
    
  if ( !*proptypes )
  {
    SetDefault(dbhandle);                            LEAVESEQ
  }
  
  if ( !memcmp(ddetype,"CHAR ",5) )
    ddesize = ID_SIZE;
  if ( !memcmp(ddetype,"INT ",4) )
    ddesize = 10;
  if ( !memcmp(ddetype,"UINT ",5) )
  {
    ddesize = 10;
    ddeprec = 2;
  }
  if ( !memcmp(ddetype,"STRING ",6) )
    ddesize = 80;
  if ( !memcmp(ddetype,"LOGICAL ",8) )
    ddesize = 1;
  
  if ( ddesize )                                     LEAVESEQ
  
  TypeKey          type_key(ddetype,0);
  PropertyHandle   enum_pi(dbhandle,"SDB_ValueList",PI_Read);  
                                                     SDBCERR
  if ( enum_pi(type_key.GetKey()) )
    ddesize = 4;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCOMType - 


\return typestring - 
/******************************************************************************/
/**
\brief  i0 - 


\param  itype - 
\param  typestring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMType"

char *SDB_Member :: GetCOMType (int16 itype, char *typestring )
{

// --> pc_SDB_Member::GetCOMSystemType(nstring,itype)

  switch ( itype )
  {
    case T_CHAR    : 
    case T_CCHAR   : 
    case T_GUID    : 
    case T_MEMO    : 
    case T_STRING  : strcpy(typestring,"BSTR");              
                     break;
    case T_UINT    : 
    case T_INT     : strcpy(typestring,ddesize < 5 ? "short" : "long");
                     break;
    case T_BIT     : strcpy(typestring,"long");              
                     break;
    case T_LO      : strcpy(typestring,"VARIANT_BOOL");
                     break;
    case T_BLOB    : 
    case T_DATETIME: 
    case T_DATE    : 
    case T_TIME    : 
    case T_VOID    : 
    case T_NONE    : 
    case T_REAL    : strcpy(typestring,"VARIANT");
                     break;
    default        : typestring = NULL;
  }
  return(typestring);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  typstr - 
\param  typestring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMType"

char *SDB_Member :: GetCOMType (char *typstr, char *typestring )
{

// --> pc_SDB_Member::GetCOMSystemType(nstring,typstr)

  if ( !strcmp(typstr,"CHAR")        ||
       !strcmp(typstr,"CCHAR")       ||
       !strcmp(typstr,"GUID")        ||
       !strcmp(typstr,"MEMO")        ||
       !strcmp(typstr,"STRING")         )
    strcpy(typestring,"BSTR");
  else if ( !strcmp(typstr,"UINT")   ||
       !strcmp(typstr,"INT")            )
    strcpy(typestring,(char*)(ddesize < 5 ? "short" : "long"));
  else if ( !strcmp(typstr,"BIT") )
    strcpy(typestring,"long");
  else if ( !strcmp(typstr,"LO") )
    strcpy(typestring,"VARIANT_BOOL");
  else if ( !strcmp(typstr,"VOID") )
    strcpy(typestring,"");
  else if ( !strcmp(typstr,"BLOB")   ||
       !strcmp(typstr,"T_DATETIME")  ||
       !strcmp(typstr,"DATE")        ||
       !strcmp(typstr,"TIME")        ||
       !strcmp(typstr,"NONE")        ||
       !strcmp(typstr,"REAL")        ||
       !strcmp(typstr,"VOID")           )
    strcpy(typestring,"VARIANT");
  else
    strcpy(typestring,typstr);

  return(typestring);
}

/******************************************************************************/
/**
\brief  GetCOMTypeString - 


\return term - 

\param  dbhandle - 
\param  typstr - 
\param  lchange - 
\param  keyfield - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMTypeString"

logical SDB_Member :: GetCOMTypeString (DatabaseHandle &dbhandle, char *typstr, int16 *lchange, logical keyfield )
{
  char      idkeyn[ID_SIZE];
  char      systypstr[ID_SIZE+1];
  int16     ityp  = 0;
  int16     styp  = 0;
  logical   term  = NO;

BEGINSEQ
  *typstr = 0;

  if ( SDB_Type::GetTypeInfo(dbhandle,ddetype,&styp,&ityp,idkeyn))     
                                                     SDBCERR
  if ( styp != ST_CODE && styp != ST_BASE && reference_level <= 0 )
    *lchange = -1;

  if ( GetCOMType(ityp,systypstr) )
    strcat(typstr,systypstr);
  else
    gvtxbts(typstr+strlen(typstr),keyfield && *idkeyn != ' ' ? idkeyn : ddetype,ID_SIZE);

RECOVER
  *typstr = 0;
  term    = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCTypeString - 


\return term - 

\param  dbhandle - 
\param  typstr - 
\param  lchange - 
\param  keyfield - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCTypeString"

logical SDB_Member :: GetCTypeString (DatabaseHandle &dbhandle, char *typstr, int16 *lchange, logical keyfield )
{
  char      idkeyn[ID_SIZE];
  char      systypstr[ID_SIZE+1];
  int16     ityp  = 0;
  int16     styp  = 0;
  logical   term  = NO;

BEGINSEQ
// --> pc_SDB_Member::GetCTypeString(string,leng,lchange,keyfield)
  *typstr = 0;

  if ( SDB_Type::GetTypeInfo(dbhandle,ddetype,&styp,&ityp,idkeyn))     
                                                     SDBCERR
  if ( *ddegent != ' ' )
  {
    gvtxbts(typstr,ddegent,sizeof(ddegent));
    strcat(typstr,"(");
    if ( reference_level <= 0 )
      *lchange = -1;
  }
  else
    if ( styp != ST_CODE && styp != ST_BASE && reference_level <= 0 )
      *lchange = -1;

  if ( GetSystemType(ityp,systypstr) )
    strcat(typstr,systypstr);
  else
    gvtxbts(typstr+strlen(typstr),keyfield && *idkeyn != ' ' ? idkeyn : ddetype,ID_SIZE);

  if ( *ddegent != ' ' )
    strcat(typstr,")");

  switch ( ityp )
  {
    case T_CHAR    : 
    case T_CCHAR   : *lchange = ddesize > 1 ? 1 : 0;   break;
    case T_STRING  : *lchange = ddesize     ? 1 : 0;   break;
    case T_GUID    : *lchange = reference_level? 0 : -1;      break; 
    default        : ;
  }
RECOVER
  *typstr = 0;
  term    = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetInternType - 


\return term - 

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInternType"

logical SDB_Member :: GetInternType (char *string )
{
  logical                 term = NO;
  ddesize = 1;
  ddeprec = 0;
  ddedim[0] = 1;
  ddedim[1] = 1;
  ddedim[2] = 1;
  ddedim[3] = 1;
  ddedim[4] = 1;
  
  memset (ddetype,' ',sizeof(ddetype));
  if ( !strcmp(string,"BOOL") || !strcmp(string,"logical") )
    gvtxstb(ddetype,"LOGICAL",ID_SIZE);
  else if ( !strcmp(string,"void") )
    gvtxstb(ddetype,"VOID",ID_SIZE);
  else if ( !strcmp(string,"char") )
    gvtxstb(ddetype,"CHAR",ID_SIZE);
  else if ( !strcmp(string,"bit") )
    gvtxstb(ddetype,"BIT",ID_SIZE);
  else if ( !strcmp(string,"short") ||  
            !strcmp(string,"SHORT"))
  {
    gvtxstb(ddetype,"INT",ID_SIZE);
    ddesize = 4; 
  }
  else if ( !strcmp(string,"ushort") ||  
            !strcmp(string,"USHORT"))
  {
    gvtxstb(ddetype,"UINT",ID_SIZE);
    ddesize = 4; 
  }
  else if ( !strcmp(string,"long") ||  
            !strcmp(string,"int")  ||
            !strcmp(string,"LONG"))
  {
    gvtxstb(ddetype,"INT",ID_SIZE);
    ddesize = 10; 
  }
  else if ( !strcmp(string,"ulong") ||  
            !strcmp(string,"ULONG"))
  {
    gvtxstb(ddetype,"UINT",ID_SIZE);
    ddesize = 10; 
  }
  else if ( !strcmp(string,"float") )
  {
    gvtxstb(ddetype,"REAL",ID_SIZE);
    ddesize = 7; 
  }
  else if ( !strcmp(string,"double") )
  {
    gvtxstb(ddetype,"REAL",ID_SIZE);
    ddesize = 17; 
  }
  else if ( !strcmp(string,"dbdt") )
  {
    gvtxstb(ddetype,"DATE",ID_SIZE);
    ddesize = 0; 
  }
  else if ( !strcmp(string,"dbtm") )
  {
    gvtxstb(ddetype,"TIME",ID_SIZE);
    ddesize = 0; 
  }
  else
    gvtxstb(ddetype,string,sizeof(ddetype));

  return(term);
}

/******************************************************************************/
/**
\brief  GetPLType - 


\return typestring - 
/******************************************************************************/
/**
\brief  i01 - 


\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPLType"

char *SDB_Member :: GetPLType (char *clsnames )
{
  DatabaseHandle   dbhandle   = structure.GetDBHandle();
  char             class_name[ID_SIZE];
  char             short_name[ID_SIZE+1];
  static char      typestring[DEF_BUFLEN+1];
BEGINSEQ
  if ( !memcmp(sys_ident,gvtxstb(class_name,clsnames,ID_SIZE),ID_SIZE) )
    strcpy(typestring,"_HANDLE");
  else
    GetPLType(dbhandle,typestring);

  short_name[0] = 0;
  if ( !strcmp(typestring,"_HANDLE") )
  {
    PropertyHandle    inst_coll(dbhandle,"InstCollection",PI_Read);
                                                     SDBCERR
    strcpy(short_name,"IFO");
    if ( *ddetype > ' ' )
      inst_coll(Key(ddetype));
    else
      inst_coll(Key(class_name));
    if ( inst_coll.Exist() )
      strcpy(short_name,inst_coll.GetString("type"));
    gvtssin(typestring,short_name,sizeof(typestring));
  }
RECOVER
  *typestring = 0;
ENDSEQ
  return(typestring);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  dbhandle - 
\param  typestring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPLType"

char *SDB_Member :: GetPLType (DatabaseHandle &dbhandle, char *typestring )
{
  char      idkeyn[ID_SIZE];
  int16     ityp  = 0;
  int16     styp  = 0;
BEGINSEQ
  if ( *ddetype <= ' ' )                             ERROR
      
  SDB_Type::GetTypeInfo(dbhandle,ddetype,&styp,&ityp,idkeyn);
  
  strcpy(typestring,"BINARY_INTEGER");
  switch ( ityp )
  {
    case T_CHAR    : 
    case T_CCHAR   : 
    case T_GUID    : 
    case T_MEMO    : 
    case T_STRING  : if ( reference_level == 1 )
                       strcpy(typestring,"VARCHAR2");          
                     break;
    case T_REAL    : 
                     strcpy(typestring,"DOUBLE PRECISION");
                     break;
    case T_UINT    : 
    case T_INT     : 
    case T_BIT     : 
    case T_LO      : 
    case T_DATETIME: 
    case T_DATE    : 
    case T_TIME    : 
    case T_VOID    : 
    case T_BLOB    : 
    case T_NONE    : 
                     break;
    default        : if ( reference_level >= 1 )
                     {
                       strcpy(typestring,"_HANDLE");  
                       if ( !memcmp(ddetype,"const char",10) )
                         strcpy(typestring,"VARCHAR2");          
                     }        
  }
RECOVER
  *typestring = 0;
ENDSEQ
  return(typestring);
}

/******************************************************************************/
/**
\brief  GetResID - 


\return resid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResID"

int32 SDB_Member :: GetResID ( )
{

  return (   res_id >= 0 
           ? res_id  
           : resource_ref.Get(FIRST_INSTANCE)
           ? resource_ref->GetResID() : 0  );


}

/******************************************************************************/
/**
\brief  GetStructDef - 


\return sdb_struct - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

SDB_Structure *SDB_Member :: GetStructDef ( )
{
  SDB_Type         *sdb_type = NULL;
  SDB_Structure    *sdb_struct = NULL;
  if ( (sdb_type = GetTypeDef()) && sdb_type->get_impl_ref()(0) &&
       sdb_type->get_impl_ref().IsA("SDB_Structure") )
    sdb_struct = (SDB_Structure *)sdb_type;

  return(sdb_struct);
}

/******************************************************************************/
/**
\brief  GetSystemType - 


\return typestring - 

\param  itype - 
\param  typestring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemType"

char *SDB_Member :: GetSystemType (int16 itype, char *typestring )
{

// --> pc_SDB_Member::GetCSystemType(nstring,itype)
  switch ( itype )
  {
    case T_CHAR    : 
    case T_CCHAR   : 
    case T_STRING  : strcpy(typestring,"char");              break;
    case T_GUID    : strcpy(typestring,"guid");              break;
    case T_BIT     : strcpy(typestring,"bit");               break;
    case T_LO      : strcpy(typestring,"logical");           break;
    case T_DATETIME: strcpy(typestring,"dttm");              break;
    case T_DATE    : strcpy(typestring,"dbdt");              break;
    case T_TIME    : strcpy(typestring,"dbtm");              break;
    case T_MEMO    : strcpy(typestring,"mem");               break;
    case T_BLOB    : strcpy(typestring,"void");              break;
    case T_VOID    : strcpy(typestring,"void");              break;
    case T_NONE    : strcpy(typestring,"");                  break;
    case T_INT     : strcpy(typestring,ddesize < 3  ? "int8"  :
                                       ddesize < 5  ? "int16" :
                                       ddesize < 11 ? "int32" :
                                                      "int64");
                     break;
    case T_UINT    : strcpy(typestring,ddesize < 3  ? "uint8"  :
                                       ddesize < 5  ? "uint16" :
                                       ddesize < 11 ? "uint32" :
                                                      "uint64");
                     break;
    case T_REAL    : strcpy(typestring,ddesize < 8 ? "float" :
                                                 "double");
                     break;
    default        : typestring = NULL;
  }
  return(typestring);
}

/******************************************************************************/
/**
\brief  GetTypeDef - 


\return sdb_type - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeDef"

SDB_Type *SDB_Member :: GetTypeDef ( )
{
  SDB_Type         *sdb_type = NULL;
  if ( sdb_type = type(0) ) 
    sdb_type = sdb_type->get_impl_ref()(0); 

  return(sdb_type);
}

/******************************************************************************/
/**
\brief  ImportMember - 


\return term - 

\param  xddeptr - 
\param  fdlptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportMember"

logical SDB_Member :: ImportMember (void *xddeptr, void *fdlptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitFromString - 


\return term - 

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFromString"

logical SDB_Member :: InitFromString (char *string )
{
  char                   *pPos;
  char                   *pEnd;
  char                    aTypeStr[40];
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  aTypeStr[0] = 0;
  ddeprv = ODC_public;
  
  pPos = string + strlen(string);
  while ( *(--pPos) == ' ' && pPos > string) ;
  if ( pPos == string )                              LEAVESEQ
    
  // Reference-Level setzen
  reference_level = RL_direct;
  switch ( *pPos )
  {
    case '*' : reference_level = RL_1;
               break;
    case '&' : reference_level = RL_reference;
               break;
    default  : pPos++;
  }
  
  while ( !isalnum(*(--pPos)) && *pPos != '_' ) ;
  pEnd = pPos+1;
  *pEnd = 0;
  while ( isalnum(*(--pPos)) || *pPos == '_' ) ;
  pPos++;

  if ( strstr(string,"unsigned") )
    strcat(aTypeStr,"u");
  if ( strstr(string,"short") )
    strcat(aTypeStr,"short");
  if ( strstr(string,"ushort") )
    strcpy(aTypeStr,"ushort");
  if ( strstr(string,"long") )
    strcat(aTypeStr,"long");
  if ( strstr(string,"ulong") )
    strcpy(aTypeStr,"ulong");
  if ( !strcmp(aTypeStr,"u") )
  {
    if ( strstr(string,"int") )
      strcat(aTypeStr,"long");
    else
      strcat(aTypeStr,"char");
  }

  // Type setzen
  GetInternType(*aTypeStr ? aTypeStr : pPos);
  *pEnd = ' ';
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void SDB_Member :: Initialize ( )
{

  memset(ddetype,' ',sizeof(ddetype));
  memset(ddegent,' ',sizeof(ddegent));
  memset(ddeinit,' ',ID_SIZE);
  ddesize             = UNDEF;
  ddedim[0]           = 1;
  ddedim[1]           = 1;
  ddedim[2]           = 1;
  ddedim[3]           = 1;
  ddedim[4]           = 1;
  ddeprec             = UNDEF;
  reference_level     = RL_direct;
  ddestat             = NO;
  ddevirt             = NO;
  ddeprv              = ODC_protected;
  res_id              = UNDEF;
  empty               = YES;

}

/******************************************************************************/
/**
\brief  IsAttrToBeAligned - 


\return allignment - 
/******************************************************************************/
/**
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttrToBeAligned"

int16 SDB_Member :: IsAttrToBeAligned ( )
{
  DatabaseHandle   dbhandle   = structure.GetDBHandle();
  PropertyHandle  *memb_ph    = structure.GetParentProperty();
  PropertyHandle  *base_ph    = structure.GPH("smcebase");
  int16            allignment = UNDEF;
BEGINSEQ
  if ( !memb_ph )                                    SDBERR(99)
  
  if ( memb_ph->GetCurrentIndex() != 0 )             LEAVESEQ
  if ( memcmp(memb_ph->GetFieldDef()->fmcbname,"smcepdde",8) )
                                                     LEAVESEQ
  if ( !structure(FIRST_INSTANCE) )                  LEAVESEQ
  if ( !base_ph->Get(LAST_INSTANCE) )                LEAVESEQ
    
  allignment = structure.GPH("allignment")->GetInt();
  
  PI(SDB_Structure)  dbs_ph(dbhandle,"SDB_Structure",PI_Read);  
                                                     SDBCERR
  TypeKey  type_key(base_ph->GPH("ddetype")->GetString(),0);
  if ( !(dbs_ph.Get(type_key.GetKey())) )            ERROR
  allignment = dbs_ph.GPH("allignment")->GetInt();
RECOVER

ENDSEQ
  return(MIN(allignment,4));
}

/******************************************************************************/
/**
\brief  IsBasicType - 


\return cond - 

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasicType"

logical SDB_Member :: IsBasicType (DatabaseHandle &dbhandle )
{

// --> DictionaryHandle::IsBasicType(ddetype)

  return ( SDB_Type::GetTypeType(dbhandle,ddetype) == TYP_Base
           ? YES : NO );


}

/******************************************************************************/
/**
\brief  KeyTypeCString - 


\return string - 
/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyTypeCString"

char *SDB_Member :: KeyTypeCString ( )
{
  DatabaseHandle  dbhandle = structure.GetDBHandle();
  static char     string[DEF_BUFLEN+1];
  return ( KeyTypeCString(dbhandle,string) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  dbhandle - 
\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyTypeCString"

char *SDB_Member :: KeyTypeCString (DatabaseHandle &dbhandle, char *string )
{
  int16 lchange = 0;
BEGINSEQ
// --> pc_SDB_Member::KeyTypeCString(nstring,align=22)

  if ( GetCTypeString(dbhandle,string,&lchange,YES) )     ERROR
  gvtxstb(string,string,22);
  string[22] = 0;
RECOVER
  *string = 0;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  ParmTypeCString - 


\return string - 
/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmTypeCString"

char *SDB_Member :: ParmTypeCString ( )
{
  DatabaseHandle  dbhandle = structure.GetDBHandle();
  static char     string[DEF_BUFLEN+1];
  return ( ParmTypeCString(dbhandle,string) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  dbhandle - 
\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmTypeCString"

char *SDB_Member :: ParmTypeCString (DatabaseHandle &dbhandle, char *string )
{
  int16    level   = MAX(0,reference_level);
  int16    lchange = 0;
BEGINSEQ
// --> pc_SDB_Member::DataTypeCString(nstring,align=ID_SIZE+5)

  if ( GetCTypeString(dbhandle,string,&lchange,NO) )      ERROR
  gvtxstb(string,string,ID_SIZE+10);
  string[ID_SIZE+5] = 0;

  if ( lchange == -1 )
    string[ID_SIZE+4] = '&';
  else
  {
    if ( !level )
      level += lchange;
    memset(string+ID_SIZE+5-level,'*',level);
  }

RECOVER
  *string = 0;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  Privilege - 


\return string - 

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Privilege"

char *SDB_Member :: Privilege (char *string )
{

  switch ( ddeprv )
  {
    case ODC_public    : strcpy(string,"public");         break;
    case ODC_private   : strcpy(string,"private");        break;
    case ODC_protected : 
    default            : strcpy(string,"protected");      break;
  }

  return(string);
}

/******************************************************************************/
/**
\brief  ProvideType - 


\return term - 

\param  xddeptr - 
\param  fdlptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideType"

logical SDB_Member :: ProvideType (void *xddeptr, void *fdlptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SDB_Member - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  fldnames - 
\param  fldtypes - 
\param  fldreflev - 
\param  fldsize - 
\param  fldprec - 
\param  flddim - 
\param  gentype - 
\param  statopt - 
\param  virtopt - 
\param  w_resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Member"

     SDB_Member :: SDB_Member (char *fldnames, char *fldtypes, SDB_RLEV fldreflev, uint16 fldsize, uint16 fldprec, uint16 flddim, char *gentype, logical statopt, logical virtopt, int32 w_resid )
                     : SDB_Resource (),
  res_id(w_resid),
  ddesize(fldsize),
  ddeprec(fldprec),
  reference_level(fldreflev),
  ddeprv(ODC_undefined),
  ddestat(statopt),
  ddevirt(virtopt),
  clustered_table(NO),
  delete_empty(NO),
  global_identity(NO),
  empty(YES)

{

  gvtxstb(sys_ident,fldnames,sizeof(sys_ident));
  gvtxstb(ddetype,fldtypes,sizeof(ddetype));
  gvtxstb(ddegent,gentype,sizeof(ddegent));
  memset(ddeinit,' ',sizeof(ddeinit));
  ddedim[0] = flddim;
  ddedim[1] = 1;
  ddedim[2] = 1;
  ddedim[3] = 1;
  ddedim[4] = 1;


}

/******************************************************************************/
/**
\brief  i1 - 


\param  dbmptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Member"

     SDB_Member :: SDB_Member (SDB_Member *dbmptr )
{

  *this = *dbmptr;

}

/******************************************************************************/
/**
\brief  i2 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Member"

     SDB_Member :: SDB_Member ( )
                     : SDB_Resource ()
{

  Initialize();

}

/******************************************************************************/
/**
\brief  SetCSDefault - 


\return term - 

\param  csname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCSDefault"

logical SDB_Member :: SetCSDefault (char *csname )
{

  gvtxstb(sys_ident,csname,ID_SIZE);
  gvtxstb(ddetype,"CHAR",ID_SIZE);
  ddesize = 32;
  ddedim[0] = 1;
  ddedim[1] = 1;
  ddedim[2] = 1;
  ddedim[3] = 1;
  ddedim[4] = 1;

  return(NO);
}

/******************************************************************************/
/**
\brief  SetDefault - 


\return term - 

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefault"

logical SDB_Member :: SetDefault (DatabaseHandle &dbhandle )
{
  char        names[ID_SIZE+1];
  logical     term = NO;
BEGINSEQ
  PI(SDB_Member)  dde_pi(dbhandle,"SDB_Member",PI_Read);  SDBCERR

  ddedim[0] = 1;
  ddedim[1] = 1;
  ddedim[2] = 1;
  ddedim[3] = 1;
  ddedim[4] = 1;
  if ( dde_pi(sys_ident) )
    *this = *dde_pi(sys_ident);
  else
  {
    gvtxbts(names,sys_ident,ID_SIZE);
    if ( strstr(names,"ndx") || strstr(names,"ndex") ||
         strstr(names,"num") )
    {
      gvtxstb(ddetype,"INT",ID_SIZE);
      ddesize = 10;
    }  
    else if ( strstr(names,"str") )
    {
      gvtxstb(ddetype,"STRING",ID_SIZE);
      ddesize = ID_SIZE;
    }
    else if ( strstr(names,"_ph") || strstr(names,"ph_") || !strcmp(names,"ph") )
    {
      gvtxstb(ddetype,"PropertyHandle",ID_SIZE);
      ddesize = UNDEF;
      reference_level = RL_1;
    }
    else if ( strstr(names,"_phr") || strstr(names,"phr_") )
    {
      gvtxstb(ddetype,"PropertyHandle",ID_SIZE);
      ddesize = ID_SIZE;
      reference_level = RL_reference;
    }
    else
    {
      gvtxstb(ddetype,"CHAR",ID_SIZE);
      ddesize = ID_SIZE;
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetVirtual - 



\param  virtopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVirtual"

void SDB_Member :: SetVirtual (logical virtopt )
{

  ddevirt = virtopt;

}

/******************************************************************************/
/**
\brief  get_ddedim - 


\return ddedim - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_ddedim"

uint32 *SDB_Member :: get_ddedim ( )
{


  return(ddedim);
}

/******************************************************************************/
/**
\brief  operator= - 


\return dbmref - 

\param  dbm_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

SDB_Member &SDB_Member :: operator= (const SDB_Member &dbm_refc )
{

  *(SDB_Resource *)this = *(SDB_Resource *)&dbm_refc;
  
  res_id          = dbm_refc.res_id;
  ddesize         = dbm_refc.ddesize;
  ddedim[0]       = dbm_refc.ddedim[0];
  ddedim[1]       = dbm_refc.ddedim[1];
  ddedim[2]       = dbm_refc.ddedim[2];
  ddedim[3]       = dbm_refc.ddedim[3];
  ddedim[4]       = dbm_refc.ddedim[4];
  ddeprec         = dbm_refc.ddeprec;
  ddeprv          = dbm_refc.ddeprv;
  ddestat         = dbm_refc.ddestat;
  ddevirt         = dbm_refc.ddevirt;
  reference_level = dbm_refc.reference_level;
  clustered_table = dbm_refc.clustered_table;
  delete_empty    = dbm_refc.delete_empty;
  global_identity = dbm_refc.global_identity;
  empty           = dbm_refc.empty;

  memcpy(ddetype,dbm_refc.ddetype,sizeof(ddetype));
  memcpy(ddegent,dbm_refc.ddegent,sizeof(ddegent));
  memcpy(ddeinit,dbm_refc.ddeinit,sizeof(ddeinit));



  return(*this);
}

/******************************************************************************/
/**
\brief  set_ddeprv - 



\param  privilege - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ddeprv"

void SDB_Member :: set_ddeprv (ODC_Privilege privilege )
{

  ddeprv = privilege;

}

/******************************************************************************/
/**
\brief  set_reference - 



\param  reflevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_reference"

void SDB_Member :: set_reference (SDB_RLEV reflevel )
{

  reference_level = reflevel;

}

/******************************************************************************/
/**
\brief  ~SDB_Member - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Member"

     SDB_Member :: ~SDB_Member ( )
{



}


