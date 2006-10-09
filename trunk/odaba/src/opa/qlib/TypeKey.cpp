/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    TypeKey

\brief    


\date     $Date: 2006/08/24 20:42:01,87 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TypeKey"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sDictionary.hpp>
#include  <spc_SDB_NameSpace.hpp>
#include  <sTypeKey.hpp>


/******************************************************************************/
/**
\brief  Exact - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exact"

logical TypeKey :: Exact ( )
{

  return(namespace_id != AUTO ? YES : NO);

}

/******************************************************************************/
/**
\brief  GetID - 


\return nsid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

int32 TypeKey :: GetID ( )
{

  return(this ? namespace_id : AUTO);

}

/******************************************************************************/
/**
\brief  GetKey - 


\return key - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

Key TypeKey :: GetKey ( )
{

  return( Key((char *)this) );

}

/******************************************************************************/
/**
\brief  GetScopeName - 


\return strnames - Type name

\param  scoped_name - 
\param  string - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScopeName"

char *__cdecl TypeKey :: GetScopeName (char *scoped_name, char *string, uint16 len )
{
  char           *strnames = NULL;
  char           *end;
BEGINSEQ
  *string = 0;
  if ( scoped_name && *scoped_name )
  {
    end = scoped_name + strlen(scoped_name);
  
    while ( end > scoped_name && *(--end) != ':' ) ;

    strnames = end;
    if ( end > scoped_name )
      strnames++;
  
    if ( end > scoped_name )
    {
      end--;
      if ( *end != ':' )                               ERROR
      strncpy(string,scoped_name,MIN(len,end-scoped_name));
      if ( len < end-scoped_name )                     ERROR
    }
  }


RECOVER
  strnames = NULL;
ENDSEQ
  return(strnames);
}

/******************************************************************************/
/**
\brief  InitPropertyType - 


\return propname - 

\param  dictptr - Dictionary handle
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitPropertyType"

char *TypeKey :: InitPropertyType (Dictionary *dictptr, char *scoped_name )
{
  char           *propnames = NULL;
  char           *end;
  logical         term = NO;
BEGINSEQ
  if ( !scoped_name || !*scoped_name )              ERROR

  end = scoped_name + strlen(scoped_name);
  while ( end > scoped_name && *(--end) != ':' ) ;
  propnames = end;

  if ( end == scoped_name )                         LEAVESEQ

  propnames++;
  end--;
  if ( *end != ':' )                                SDBERR(99)
  *end = 0;
  if ( Initialize_intern(dictptr,NULL,scoped_name) )ERROR
  *end = ':';

RECOVER
  *sys_ident = 0;
  propnames = NULL;
ENDSEQ
  return(propnames);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  dictptr - Dictionary handle
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (Dictionary *dictptr, char *scoped_name )
{

  return ( Initialize_intern(dictptr,NULL,scoped_name) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  typenames - Type name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (char *typenames, int32 nsid )
{
  logical         term = NO;
  SetName(typenames);
  SetNamespace(nsid);
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 


\param  dictptr - Dictionary handle
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (Dictionary *dictptr, char *scope_name, char *strnames )
{

  return ( Initialize_intern(dictptr,NULL,scope_name,strnames) );

}

/******************************************************************************/
/**
\brief  i10 - 


\param  dicthdl_ref - 
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (DictionaryHandle &dicthdl_ref, char *scoped_name )
{

  return ( Initialize_intern(dicthdl_ref.get_dictionary(),NULL,
                             scoped_name)   );

}

/******************************************************************************/
/**
\brief  i13 - 


\param  dicthdl_ref - 
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (DictionaryHandle &dicthdl_ref, char *scope_name, char *strnames )
{

  return ( Initialize_intern(dicthdl_ref.get_dictionary(),NULL,
                             scope_name,strnames)    );

}

/******************************************************************************/
/**
\brief  i20 - 


\param  res_dbhandle - 
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (DatabaseHandle &res_dbhandle, char *scoped_name )
{

  return ( Initialize_intern(NULL,res_dbhandle.get_dbhandle(),
                             scoped_name)   );

}

/******************************************************************************/
/**
\brief  i23 - 


\param  res_dbhandle - 
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical TypeKey :: Initialize (DatabaseHandle &res_dbhandle, char *scope_name, char *strnames )
{

  return ( Initialize_intern(NULL,res_dbhandle.get_dbhandle(),
                             scope_name,strnames)   );

}

/******************************************************************************/
/**
\brief  Initialize_intern - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 


\param  dictptr - Dictionary handle
\param  dbhandle - Database handle
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize_intern"

logical TypeKey :: Initialize_intern (Dictionary *dictptr, DBHandle *dbhandle, char *scoped_name )
{
  char           *strnames = NULL;
  char            scope[512];
  logical         term = NO;
BEGINSEQ
  if ( scoped_name && *scoped_name )
  {
    if ( !(strnames = GetScopeName(scoped_name,scope,sizeof(scope)-1)) )
                                                     ERROR
    if ( *scope )
    {
      if ( Initialize_intern(dictptr,dbhandle,scoped_name,strnames) )
                                                    ERROR
    }
    else
      Initialize(strnames,0);
  }
  else
    Initialize("",AUTO);

RECOVER
  *sys_ident = 0;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 


\param  dictptr - Dictionary handle
\param  dbhandle - Database handle
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize_intern"

logical TypeKey :: Initialize_intern (Dictionary *dictptr, DBHandle *dbhandle, char *scope_name, char *strnames )
{
  int32           nsid = 0;
  logical         term = NO;
BEGINSEQ
  if ( strnames )
    SetName(strnames);
  
  if ( scope_name && *scope_name )
  {
    if ( dictptr )
      nsid = dictptr->GetNSID(scope_name);
    else if ( dbhandle )
    {
// hier fehlt noch die implementierung - lesen der SDB_NameSpace
// z.B. ueber Kontextfunction der DB (zum optimieren)
      SDBERR(777)
    }
    else                                            SDBERR(99)
    if ( nsid == AUTO )                             ERROR
  }
  
  SetNamespace(nsid);
RECOVER
  *sys_ident = 0;
  term       = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical TypeKey :: IsEmpty ( )
{

  return( !this || *sys_ident <= ' ' ? YES : NO );

}

/******************************************************************************/
/**
\brief  LookUp - 


\return nsid - 

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LookUp"

int32 TypeKey :: LookUp (Dictionary *dictptr )
{
  PropertyHandle          type_ph;
  NString                 nstring;
  Namespace              *ns = dictptr;
  logical                 reserved = NO;
  int32                   nsid = AUTO;
BEGINSEQ
  if ( namespace_id < 0 )                            ERROR
  if ( !namespace_id )                               LEAVESEQ
    
  if ( !(ns = dictptr->GetNamespace(namespace_id)) ) SDBERR(99)
  nsid = namespace_id;

  reserved = dictptr->Reserve_type_pi(type_ph);
  while ( ns && !type_ph(GetKey()) )
  {
    ns = ns->get_parent();
    namespace_id = ns->get_ns_id();
  }
  
  if ( !ns )
  {
    ns = dictptr->GetNamespace(nsid);
    ns->GetScopeName(nstring);
    nstring += "::";
    nstring.Append(sys_ident,ID_SIZE);
    SDBEV1(nstring,UNDEF)                            
    SDBERR(20)
  }

RECOVER
  nsid = AUTO;
ENDSEQ
  dictptr->Release_type_pi(reserved);
  return(nsid);
}

/******************************************************************************/
/**
\brief  Name - 


\return ns_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Name"

char *TypeKey :: Name ( )
{

  return(this ? sys_ident : NULL);

}

/******************************************************************************/
/**
\brief  Scope - 


\return string - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  dictptr - Dictionary handle
\param  string - 
\param  leng - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Scope"

char *TypeKey :: Scope (Dictionary *dictptr, char *string, int32 leng )
{
  Namespace    *ns;
  char         *nextpos = string;
  if ( (ns = dictptr->GetNamespace(namespace_id)) && ns != dictptr )
    nextpos = ns->GetScope(string,leng);
    
  *nextpos = 0;


  return(string);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  dicthdl - 
\param  string - 
\param  leng - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Scope"

char *TypeKey :: Scope (DictionaryHandle dicthdl, char *string, int32 leng )
{

  return( Scope(dicthdl->get_dictionary(),string,leng) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  res_dbhandle - 
\param  string - 
\param  rlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Scope"

char *TypeKey :: Scope (DatabaseHandle &res_dbhandle, char *string, int32 &rlen )
{
  char         *nextpos = string;
  char          names[ID_SIZE+1];
BEGINSEQ
  if ( namespace_id > 0 )
  {
    PropertyHandle   nsph(res_dbhandle,"SDB_Type",PI_Read);
    
    nsph.SetOrder("sk_TypeID");
    if ( !nsph.Get(Key(namespace_id)) )              ERROR
    
    PH(&nsph,impl_ref)
    if ( !impl_ref(0) )                              ERROR
    if ( impl_ref.IsA("SDB_NameSpace") )
    {
      pc_SDB_NameSpace  nspc(&impl_ref);
      nextpos = nspc.Scope(string,rlen);
      if ( rlen < 0 )                                ERROR
    }
    else if ( impl_ref.IsA("SDB_Structure") || impl_ref.IsA("SDB_ValueList") )
    {
      pc_SDB_NameSpace  nspc(impl_ref.GPH("name_space"));
      nextpos = nspc.Scope(string,rlen);
      if ( rlen < 2 )                                ERROR
      strcpy(nextpos,"::");
      rlen -= 2;
      nextpos += 2;

      gvtxbts(names,sys_ident,ID_SIZE);
      gvtxbts(nextpos,sys_ident,MIN(rlen,ID_SIZE));
      if ( strlen(names) > rlen )                    ERROR
    }
  }

RECOVER
  rlen = AUTO;
  nextpos = NULL;
ENDSEQ
  return(nextpos);
}

/******************************************************************************/
/**
\brief  ScopedName - 


\return string - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  dictptr - Dictionary handle
\param  string - 
\param  leng - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ScopedName"

char *TypeKey :: ScopedName (Dictionary *dictptr, char *string, int32 leng )
{
  Namespace    *ns      = NULL;
  char         *nextpos = string;
  char          names[ID_SIZE+1];
BEGINSEQ
  if ( (ns = dictptr->GetNamespace(namespace_id)) && ns != dictptr )
  {
    nextpos = ns->GetScope(string,leng);
    if ( leng < 2 )                                  ERROR
    strcpy(nextpos,"::");
    leng -= 2;
    nextpos += 2;
  }

  gvtxbts(names,sys_ident,ID_SIZE);
  gvtxbts(nextpos,sys_ident,MIN(leng,ID_SIZE));
  if ( strlen(names) > leng )                        ERROR

RECOVER
  strcpy(string+strlen(string)-3,"...");
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  dicthdl_ref - 
\param  string - 
\param  leng - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ScopedName"

char *TypeKey :: ScopedName (DictionaryHandle &dicthdl_ref, char *string, int32 leng )
{

  return( ScopedName(dicthdl_ref->get_dictionary(),string,leng) );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  res_dbhandle - 
\param  string - 
\param  leng - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ScopedName"

char *TypeKey :: ScopedName (DatabaseHandle &res_dbhandle, char *string, int32 leng )
{
  char         *nextpos = string;
  char          names[ID_SIZE+1];
BEGINSEQ
  if ( namespace_id > 0 )
  {
    nextpos = Scope(res_dbhandle,string,leng);
    if ( leng < 2 )                                  ERROR
    strcpy(nextpos,"::");
    leng -= 2;
    nextpos += 2;
  }

  gvtxbts(names,sys_ident,ID_SIZE);
  gvtxbts(nextpos,sys_ident,MIN(leng,ID_SIZE));
  if ( strlen(names) > leng )                        ERROR


RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  SetName - 



\param  typenames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetName"

void TypeKey :: SetName (char *typenames )
{

  if ( typenames )
    gvtxstb(sys_ident,typenames,ID_SIZE);
  else
    memset(sys_ident,' ',ID_SIZE);

}

/******************************************************************************/
/**
\brief  SetNamespace - 



\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNamespace"

void TypeKey :: SetNamespace (int32 nsid )
{

  namespace_id = nsid == AUTO ? 0 : nsid;

}

/******************************************************************************/
/**
\brief  TypeKey - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  dictptr - Dictionary handle
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (Dictionary *dictptr, char *scoped_name )
                     :   namespace_id(AUTO)
{

  Initialize(dictptr,scoped_name);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  typenames - Type name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (char *typenames, int32 nsid )
                     :   namespace_id(AUTO)
{

  Initialize(typenames,nsid);

}

/******************************************************************************/
/**
\brief  i02 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey ( )
                     :   namespace_id(AUTO)
{

  memset(sys_ident,0,ID_SIZE);

}

/******************************************************************************/
/**
\brief  i03 - 


\param  dictptr - Dictionary handle
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (Dictionary *dictptr, char *scope_name, char *strnames )
                     :   namespace_id(AUTO)
{

  Initialize(dictptr,scope_name,strnames);

}

/******************************************************************************/
/**
\brief  i10 - 


\param  dicthdl_ref - 
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (DictionaryHandle &dicthdl_ref, char *scoped_name )
                     :   namespace_id(AUTO)
{

  Initialize(dicthdl_ref,scoped_name);

}

/******************************************************************************/
/**
\brief  i13 - 


\param  dicthdl_ref - 
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (DictionaryHandle &dicthdl_ref, char *scope_name, char *strnames )
                     :   namespace_id(AUTO)
{

  Initialize(dicthdl_ref,scope_name,strnames);

}

/******************************************************************************/
/**
\brief  i20 - 


\param  res_dbhandle - 
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (DatabaseHandle &res_dbhandle, char *scoped_name )
                     :   namespace_id(AUTO)
{

  Initialize(res_dbhandle,scoped_name);

}

/******************************************************************************/
/**
\brief  i23 - 


\param  res_dbhandle - 
\param  scope_name - 
\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TypeKey"

     TypeKey :: TypeKey (DatabaseHandle &res_dbhandle, char *scope_name, char *strnames )
                     :   namespace_id(AUTO)
{

  Initialize(res_dbhandle,scope_name,strnames);

}

/******************************************************************************/
/**
\brief  operator bool - 


\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator bool"

NOTYPE TypeKey :: operator bool ( )
{

  return( this && namespace_id != AUTO ? true : false );

}

/******************************************************************************/
/**
\brief  operator char* - 


\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator char*"

NOTYPE TypeKey :: operator char* ( )
{

  return( (char *)this );

}

/******************************************************************************/
/**
\brief  operator! - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!"

logical TypeKey :: operator! ( )
{

  return( IsEmpty() );

}

/******************************************************************************/
/**
\brief  operator!= - 


\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical TypeKey :: operator!= (char *strnames )
{

  return( !operator==(strnames) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  tk_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical TypeKey :: operator!= (TypeKey &tk_ref )
{

  return( !operator==(tk_ref) );

}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical TypeKey :: operator== (char *strnames )
{
  char                    buffer[ID_SIZE];
  logical                 cond = YES;
BEGINSEQ
  if ( !strnames )                                   ERROR

  gvtxstb(buffer,strnames,ID_SIZE);
  if ( memcmp(buffer,sys_ident,ID_SIZE) )             ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  tk_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical TypeKey :: operator== (TypeKey &tk_ref )
{

  return( tk_ref == sys_ident && tk_ref.GetID() == namespace_id);

}


