/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    pc_SDB_Member

\brief    


\date     $Date: 2006/07/12 19:10:21,45 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Member"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Structure.hpp>
#include  <spc_SDB_Type.hpp>
#include  <spc_SDB_Member.hpp>


/******************************************************************************/
/**
\brief  BitSize - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BitSize"

char *pc_SDB_Member :: BitSize (NString &nstring )
{

  if ( *GPH("ddetype") == "BIT" )
  {
    nstring.Append(": ");
    nstring += GPH("ddesize")->GetString();
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  CharSize - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CharSize"

char *pc_SDB_Member :: CharSize (NString &nstring )
{
  char    string[13];
  int32   ddesize = UNDEF;
  int32   csiz    = 0;
  if ( GPH("reference_level")->GetInt() == RL_direct )
  {
    ddesize = GPH("ddesize")->GetInt();
    switch ( GetDictionary().BaseType(GPH("ddetype")->GetString()) )
    {
      case T_CCHAR   :
      case T_CHAR    : csiz = ddesize;                     break;
      case T_STRING  : csiz = ddesize+1;                   break;
      case UNDEF     : SDBRESET
      default        : break;
    }

    if ( csiz > 1 )
    {
      nstring += "[";
      nstring += gvtxitoa(csiz,string,10);
      nstring += "]";
    }
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  CheckType - 


\return term - 

\param  protocol - 
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckType"

logical pc_SDB_Member :: CheckType (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph )
{
  PropertyHandle  *structure = NULL;
  TypeKey          tkey;
  int32            ityp      = 0;
  logical          term      = NO;
BEGINSEQ
  GetTypeKey(tkey);
  
  if ( !str_ph->Get(tkey.GetKey())  && !cs_ph->Get(tkey.GetKey()) )
  {
    protocol->Write(140,0,NULL,NULL,GetScopedType());
    ERROR
  }

  if ( str_ph->IsPositioned() )
  {
    pc_SDB_Structure   structure(GPH("structure"));
    if ( !structure.Get(FIRST_INSTANCE) )           LEAVESEQ
    pc_SDB_Structure   str_pc(str_ph);
    if ( str_pc.IsBaseType() )                      LEAVESEQ
    
    if ( structure.GetID() != str_pc.GetID() )      LEAVESEQ

    if ( structure.IsPersistent(NULL) )
    { 
      if ( GPH("reference_level") > 0 )             LEAVESEQ
      if ( !str_pc.IsPersistent(&ityp) )
      {
        protocol->Write(384,0,NULL,NULL,GetScopedType());
        ERROR
      }      
      else if ( !ityp )
      {
        protocol->Write(385,0,NULL,NULL,GetScopedType());
        ERROR
      }      
      if ( !str_pc.IsChecked() )
        protocol->Write(141,1,NULL,NULL,GetScopedType());
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DataTypeCOMString - 


\return string - 

\param  nstring - 
\param  output_parm - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCOMString"

char *pc_SDB_Member :: DataTypeCOMString (NString &nstring, logical output_parm )
{
  NString   rstring;
  GetCOMTypeString(nstring,NULL,NO);
  GetRefLevelString(rstring);

  if ( output_parm )
    rstring += "*";
      
  nstring.Append(' ');
  nstring += rstring;

  return(nstring);
}

/******************************************************************************/
/**
\brief  DataTypeCString - 


\return string - 

\param  nstring - 
\param  align - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

char *pc_SDB_Member :: DataTypeCString (NString &nstring, int16 align )
{
  int16     size = 0;
  NString   rstring;

  GetCTypeString(nstring,NULL,NO);
  GetRefLevelString(rstring);

  if ( !align )
    nstring.Append(' ');
  else
    if ( (size = nstring.GetLength() + rstring.GetLength()) < align )
      nstring.Append(' ',align-size);

  nstring += rstring;

  return(nstring);
}

/******************************************************************************/
/**
\brief  Fill - 


\return term - 

\param  propnames - 
\param  proptypes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical pc_SDB_Member :: Fill (char *propnames, char *proptypes )
{
  PropertyHandle   *sys_ident = GPH("sys_ident");
  PropertyHandle   *ddetype   = GPH("ddetype");
  PropertyHandle   *ddesize   = GPH("ddesize");
  PropertyHandle   *ddeprec   = GPH("ddeprec");
  TypeKey     tkey;
  logical     term = NO;
BEGINSEQ
  if ( Initialize() )                               ERROR

  *sys_ident = propnames;
  *ddetype   = proptypes;
    
  if ( !*proptypes )
  {
    SetDefault();
    LEAVESEQ
  }
  
  if ( *ddetype == "CHAR" )
    *ddesize = ID_SIZE;
  else if ( *ddetype == "INT" )
    *ddesize = 10;
  else if ( *ddetype == "UINT" )
  {
    *ddesize = 10;
    *ddeprec = 2;
  }
  else if ( *ddetype == "STRING" )
    *ddesize = 80;
  else if ( *ddetype == "LOGICAL" )
    *ddesize = 1;
  
  if ( ddesize->GetInt() )                           LEAVESEQ
  
  PropertyHandle  cs_ph(GetDBHandle(),"SDB_ValueList",PI_Read);  
                                                     SDBCERR
  if ( cs_ph(GetTypeKey(tkey).GetKey()) )
    *ddesize = 2;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCOMSystemType - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  nstring - 
\param  itype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMSystemType"

char *pc_SDB_Member :: GetCOMSystemType (NString &nstring, int16 itype )
{
  int32     size   = GPH("ddesize")->GetInt();
  char     *string = NULL;
BEGINSEQ
  switch ( itype )
  {
    case T_CHAR    : 
    case T_CCHAR   : 
    case T_GUID    : 
    case T_MEMO    : 
    case T_STRING  : nstring += "BSTR";              
                     break;
    case T_UINT    : 
    case T_INT     : nstring += (char*)(size < 5 ? "short" 
                                                 : "long");
                     break;
    case T_BIT     : nstring += "long";              
                     break;
    case T_LO      : nstring += "VARIANT_BOOL";
                     break;
    case T_BLOB    : 
    case T_DATETIME: 
    case T_DATE    : 
    case T_TIME    : 
    case T_VOID    : 
    case T_NONE    : 
    case T_REAL    : nstring += "VARIANT";
                     break;
    default        : ERROR
  }
  
  string = nstring;
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  typstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMSystemType"

char *pc_SDB_Member :: GetCOMSystemType (NString &nstring, char *typstr )
{
  int32    ityp   = 0;
  NString  tstring;
  char    *string = NULL;
BEGINSEQ
  if ( !typstr )
    typstr = GetScopedType(tstring);

  pc_SDB_Type   type_pc(GetDBHandle());
  if ( !type_pc.GetTypeInfo(typstr,NULL,&ityp,NULL,NULL) )
                                                    ERROR
  string = GetCOMSystemType(nstring,ityp);
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetCOMTypeString - 


\return string - 

\param  nstring - 
\param  lchange - 
\param  keyfield - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMTypeString"

char *pc_SDB_Member :: GetCOMTypeString (NString &nstring, int16 *lchange, logical keyfield )
{
  PropertyHandle  *ddegent   = GPH("ddegent");
  PropertyHandle  *ddesize   = GPH("ddesize");
  int32            ref_level = GPH("referenve_level")->GetInt();
  pc_SDB_Type      type_pc(GetDBHandle());
  char             idkeyn[ID_SIZE+1];
  int32            ityp     = 0;
  int32            styp     = 0;
BEGINSEQ
  if ( type_pc.GetTypeInfo(GetScopedType(),&styp,&ityp,NULL,idkeyn))     
                                                     SDBCERR
  if ( lchange && styp != ST_CODE && styp != ST_BASE && ref_level <= 0 )
    *lchange = -1;

  if ( !GetCOMSystemType(nstring,ityp) )
    nstring += (keyfield && *idkeyn) ? idkeyn
                                     : GetScopedType();

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCSystemType - 


\return string - 

\param  nstring - 
\param  itype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCSystemType"

char *pc_SDB_Member :: GetCSystemType (NString &nstring, int16 itype )
{
  int32     size   = GPH("ddesize")->GetInt();
  char     *string = NULL;
BEGINSEQ
  if ( itype > 0 )
    itype = (-itype);
    
  switch ( itype )
  {
    case T_NONE    : break;
    case T_CHAR    : 
    case T_CCHAR   : 
    case T_STRING  : nstring += "char";              break;
    case T_GUID    : nstring += "guid";              break;
    case T_BIT     : nstring += "bit";               break;
    case T_LO      : nstring += "logical";           break;
    case T_DATETIME: nstring += "dttm";              break;
    case T_DATE    : nstring += "dbdt";              break;
    case T_TIME    : nstring += "dbtm";              break;
    case T_MEMO    : nstring += "mem";               break;
    case T_BLOB    : nstring += "void";              break;
    case T_VOID    : nstring += "void";              break;
    case T_INT     : nstring += (char *)(size < 3  ? "int8"  :
                                         size < 5  ? "int16" :
                                         size < 11 ? "int32" :
                                                     "int64" );
                     break;
    case T_UINT    : nstring += (char *)(size < 3  ? "uint8"  :
                                         size < 5  ? "uint16" :
                                         size < 11 ? "uint32" :
                                                     "uint64" );
                     break;
    case T_REAL    : nstring += (char *)(size < 8 ? "float" :
                                                    "double");
                     break;
    default        : ERROR
  }
  
  string = nstring;
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetCTypeString - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  nstring - 
\param  lchange - 
\param  keyfield - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCTypeString"

char *pc_SDB_Member :: GetCTypeString (NString &nstring, int16 *lchange, logical keyfield )
{
  PropertyHandle  *ddegent   = GPH("ddegent");
  PropertyHandle  *ddesize   = GPH("ddesize");
  int32            ref_level = GPH("reference_level")->GetInt();
  pc_SDB_Type      type_pc(GetDBHandle());
  char             idkeyn[ID_SIZE+1];
  int32            ityp     = 0;
  int32            styp     = 0;
  logical          term     = NO;
BEGINSEQ
  if ( type_pc.GetTypeInfo(GetScopedType(),&styp,&ityp,NULL,idkeyn))     
                                                     SDBCERR
  if ( !ddegent->IsEmpty() )
  {
    nstring += ddegent->GetString();
    nstring += "(";
    if ( lchange && ref_level <= 0 )
      *lchange = -1;
  }
  else
    if ( lchange && styp != ST_CODE && styp != ST_BASE && ref_level <= 0 )
      *lchange = -1;

  if ( !GetCSystemType(nstring,ityp) )
    nstring += keyfield && *idkeyn ? idkeyn
                                   : GetScopedType();
  if ( !ddegent->IsEmpty() )
    nstring += ")";

  if ( lchange )
    switch ( ityp )
    {
      case T_CHAR    : 
      case T_CCHAR   : *lchange = ddesize->GetInt() > 1 ? 1 : 0;  break;
      case T_STRING  : *lchange = ddesize->GetInt()     ? 1 : 0;  break;
      case T_GUID    : *lchange = ref_level             ? 0 : -1; break; 
      default        : ;
    }
RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  string - 
\param  leng - 
\param  lchange - 
\param  keyfield - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCTypeString"

char *pc_SDB_Member :: GetCTypeString (char *string, int16 leng, int16 *lchange, logical keyfield )
{
  NString          nstring;
  GetCTypeString(nstring,lchange,keyfield);
 
  strncpy(string,nstring,leng);
  string[leng] = 0;
  return(string);
}

/******************************************************************************/
/**
\brief  GetRefLevelString - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefLevelString"

char *pc_SDB_Member :: GetRefLevelString (NString &nstring )
{
  int32     ref_level = GPH("reference_level")->GetInt();
  switch ( ref_level )
  {
    case RL_reference : nstring = "&";          
    case RL_generic   : 
    case RL_direct    : break;
    default           : nstring.Append('*',abs(ref_level));
  }

  return(nstring);
}

/******************************************************************************/
/**
\brief  GetScopedType - 


\return scoped_name - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScopedType"

char *pc_SDB_Member :: GetScopedType (NString &nstring )
{
  PropertyHandle    *scope   = GPH("scope");
  PropertyHandle    *ddetype = GPH("ddetype");
  if ( !scope->IsEmpty() )
  {
    nstring += scope->GetString();
    nstring += "::";
  }
  nstring += ddetype->GetString();

  return(nstring);
}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScopedType"

char *pc_SDB_Member :: GetScopedType ( )
{
  static  NString    nstring;
  nstring = "";
  return ( GetScopedType(nstring) );

}

/******************************************************************************/
/**
\brief  GetTypeKey - 


\return tkey - 

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeKey"

TypeKey &pc_SDB_Member :: GetTypeKey (TypeKey &tkey )
{

BEGINSEQ
  tkey.Initialize("",0);
  
  if ( !IsPositioned() )                            ERROR
  
  tkey.Initialize(GetDBHandle(),
                  GPH("scope")->GetString(),
                  GPH("ddetype")->GetString());
RECOVER

ENDSEQ
  return(tkey);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical pc_SDB_Member :: Initialize ( )
{
  logical     term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR

  *GPH("ddetype")         = "";
  *GPH("ddegent")         = "";
  *GPH("ddeinit")         = "";
  *GPH("ddesize")         = 0;
  *GPH("ddedim")          = 1;
  *GPH("ddeprec")         = 0;
  *GPH("reference_level") = "RL_direct";
  *GPH("ddestat")         = (logical)NO;
  *GPH("ddevirt")         = (logical)NO;
  *GPH("ddeprv")          = "ODC_protected";
  *GPH("res_id")          = 0;
  *GPH("empty")           = (logical)YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  KeyTypeCString - 


\return string - 

\param  nstring - 
\param  align - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyTypeCString"

char *pc_SDB_Member :: KeyTypeCString (NString &nstring, int16 align )
{
  int16       size = 0;
  logical     term = NO;
  GetCTypeString(nstring,NULL,YES);
  
  if ( (size = nstring.GetLength()) < align )
    nstring.Append(' ',align-size);
  return(nstring);
}

/******************************************************************************/
/**
\brief  ParmTypeCString - 


\return string - 

\param  nstring - 
\param  align - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmTypeCString"

char *pc_SDB_Member :: ParmTypeCString (NString &nstring, int16 align )
{
  int16    level   = GPH("reference_level")->GetInt();
  int16    size    = 0;
  int16    lchange = 0;
  GetCTypeString(nstring,&lchange,NO);
  
  if ( (size = nstring.GetLength()) < align )
    nstring.Append(' ',align-size);
  
  if ( level < 0 )
    level = 0;
    
  if ( lchange == -1 )
  {
    if ( align )
      nstring.Append(' ',4);
    nstring.Append('&',1);
  }
  else
  {
    if ( !level )
      level += lchange;
    if ( align )
      nstring.Append(' ',5-level);
    nstring.Append('*',level);
  }
  return(nstring);
}

/******************************************************************************/
/**
\brief  SetDefault - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefault"

logical pc_SDB_Member :: SetDefault ( )
{
  PropertyHandle   *sys_ident       = GPH("sys_ident");
  PropertyHandle   *ddetype         = NULL;
  PropertyHandle   *ddesize         = NULL;
  PropertyHandle   *reference_level = NULL;
  char             *names           = NULL;
  char              idkey[ID_SIZE];
  logical           term            = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  PropertyHandle   mem_ph(GetDBHandle(),"SDB_Member",PI_Read);
                                                    SDBCERR
  if ( mem_ph.Get(*sys_ident) )
    Copy(mem_ph,ExtractKey(idkey),REPL_direct);
  else
  {
    ddetype         = GPH("ddetype");
    ddesize         = GPH("ddesize");
    reference_level = GPH("reference_level");
    names           = sys_ident->GetString();
    
    if ( strstr(names,"ndx") || strstr(names,"ndex") ||
         strstr(names,"num") )
    {
      *ddetype = "INT";
      *ddesize = 10;
    }  
    else if ( strstr(names,"str") )
    {
      *ddetype = "STRING";
      *ddesize = ID_SIZE;
    }
    else if ( strstr(names,"_ph") || strstr(names,"ph_") || !strcmp(names,"ph") )
    {
      *ddetype = "PropertyHandle";
      *ddesize = 0;
      *reference_level = (int32)RL_1;
    }
    else if ( strstr(names,"_phr") || strstr(names,"phr_") )
    {
      *ddetype = "PropertyHandle";
      *ddesize = ID_SIZE;
      *reference_level = (int32)RL_reference;
    }
    else
    {
      *ddetype = "CHAR";
      *ddesize = ID_SIZE;
    }

    *GPH("ddedim") = 1;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetProperty - 


\return term - 

\param  propnames - 
\param  string - 
\param  protocol - 
\param  remarks - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperty"

logical pc_SDB_Member :: SetProperty (char *propnames, char *string, ErrorProtocol *protocol, char *remarks )
{
  NString    parm1;
  logical    term  = NO;
  if ( protocol->WarningLevel() > YES )
  {
    parm1 += GetCurrentType();
    parm1 += "(";
    parm1 += GPH("sys_ident")->GetString();
    parm1 += ")";
  }
  
  term = SDBSetProperty(this,propnames,string,protocol,parm1,remarks);

  return(term);
}

/******************************************************************************/
/**
\brief  Store - 


\return term - 

\param  dbflddef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_Member :: Store (DBFieldDef *dbflddef )
{
  PropertyHandle  *ddedim      = GPH("ddedim");
  const char      *init_string = dbflddef->get_initval();
  char             string[ID_SIZE+1];
  int32            indx0       = 0;
  logical          term        = NO;
  *GPH("sys_ident") = gvtxbts(string,dbflddef->fmcbname,ID_SIZE);
  *GPH("ddetype")   = gvtxbts(string,dbflddef->fmcbtype,ID_SIZE);
  *GPH("ddegent")   = gvtxbts(string,dbflddef->get_gen_type(),ID_SIZE);
  *GPH("ddeinit")   = (char*)(init_string ? init_string : "");
  *GPH("ddesize")   = (int32)dbflddef->fmcbsize;
  *GPH("ddeprec")   = dbflddef->fmcbprec;
  *GPH("empty")     = dbflddef->fmcbempty;
  *GPH("ddevirt")   = dbflddef->get_virtual();
  *GPH("ddestat")   = dbflddef->get_static();
  *GPH("res_id")    = UNDEF; 
  *GPH("ddeprv")    = "ODC_protected";
  *GPH("reference_level") = dbflddef->ReferenceLevel();

  ddedim->Get(indx0);
  *ddedim = dbflddef->fmcbdim;
  while ( indx0 < 4 )
  {
    ddedim->Get(++indx0);
    *ddedim = 1;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Member - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Member"

     pc_SDB_Member :: pc_SDB_Member (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


