/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    DictionaryHandle

\brief    Dictionary Handle
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/06/29 18:08:22,25 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DictionaryHandle"

#include  <pdefault.h>
#include  <cPIREPL.h>
#include  <sBNFData.hpp>
#include  <sBNFParser.hpp>
#include  <sCDictionary.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionary.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sLDictionary.hpp>
#include  <sODABAClient.hpp>
#include  <sXDictionary.hpp>
#include  <sDictionaryHandle.hpp>


/******************************************************************************/
/**
\brief  BaseType - Returns internal number for elementary types
        The  function returns the internal  number for elementary types (STRING,
        CHAR,  INT,...). If the  type name (strnames)  passed is not a supported
        basic type the function returns UNDEF.

\return ityp - Internal structure number

\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BaseType"

int32 DictionaryHandle :: BaseType (char *strnames )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->BaseType(strnames) 
                      : UNDEF );

}

/******************************************************************************/
/**
\brief  CheckExpression - Check expression syntax
        The  function  terurns  YES  when  the expression is invalid or no valid
        object handle has been passed.

\return term - Termination code
-------------------------------------------------------------------------------
\brief  I00 - 


\param  expression - 
\param  dbobj_handle - 
\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical DictionaryHandle :: CheckExpression (char *expression, DBObjectHandle &dbobj_handle, char *clsnames )
{
  Dictionary   *dictionary = get_dictionary();
  ACObject     *ob_handle  = dbobj_handle.get_obhandle();
  return (   dictionary && ob_handle 
           ? dictionary->CheckExpression(expression,ob_handle,clsnames)
           : YES );

}

/******************************************************************************/
/**
\brief  InClass - 


\param  resobj - 
\param  clsnames - 
\param  exprnames - 
\param  implnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical DictionaryHandle :: CheckExpression (DBObjectHandle &resobj, char *clsnames, char *exprnames, char *implnames )
{
  Dictionary   *dictionary = get_dictionary();
  ACObject     *ob_handle  = resobj.get_obhandle();
  return (   dictionary  
           ? dictionary->CheckExpression(ob_handle,clsnames,exprnames,implnames)
           : YES );

}

/******************************************************************************/
/**
\brief  CheckExtentDef - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  extname - Extent name
\param  namespace_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtentDef"

logical DictionaryHandle :: CheckExtentDef (char *extname, int32 namespace_id )
{
  TypeKey       tkey(extname,namespace_id);
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CheckExtendDef(tkey) 
                      : YES );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtentDef"

logical DictionaryHandle :: CheckExtentDef (char *scoped_name )
{
  Dictionary   *dictionary = get_dictionary();
  logical       term = NO;
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  TypeKey       tkey(dictionary,scoped_name);
  
  if ( dictionary->CheckExtendDef(tkey) )            ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CheckValueSet - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  extname - Extent name
\param  namespace_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValueSet"

logical DictionaryHandle :: CheckValueSet (char *extname, int32 namespace_id )
{
  TypeKey       tkey(extname,namespace_id);
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CheckValueSet(tkey) 
                      : YES );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValueSet"

logical DictionaryHandle :: CheckValueSet (char *scoped_name )
{
  Dictionary   *dictionary = get_dictionary();
  logical       term = NO;
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  TypeKey       tkey(dictionary,scoped_name);
  
  if ( dictionary->CheckValueSet(tkey)  )            ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code
/******************************************************************************/
/**
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical DictionaryHandle :: Close ( )
{

  return ( DatabaseHandle::Close() );

}

/******************************************************************************/
/**
\brief  CopyCodeset - Copy enumeration
        The  function  copies  an  enumeration  (Codeset) from one dictionary to
        another.

\return term - Termination code

\param  srce_dicthandle - 
\param  strname - Type name
\param  namespace_id - 
\param  newnames - New name for an extent or type
\param  db_replace - 
\param  retainSID - Retain internal type numbers
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyCodeset"

logical DictionaryHandle :: CopyCodeset (DictionaryHandle &srce_dicthandle, char *strname, int32 namespace_id, char *newnames, PIREPL db_replace, logical retainSID, logical retain_schemav )
{
  Dictionary *dictionary      = get_dictionary();
  TypeKey     tkey(strname,namespace_id);
  TypeKey     nkey(newnames,namespace_id);
  Dictionary *srce_dictionary = srce_dicthandle.get_dictionary();
  return (   dictionary && srce_dictionary
           ? dictionary->CopyCodeset(srce_dictionary,tkey,nkey,db_replace,retainSID) 
           : YES );

}

/******************************************************************************/
/**
\brief  CopyExtentDef - Copy extent definition
        The  function  copies  an  extent  definition  from  one  dictionary  to
        another.

\return term - Termination code

\param  srce_dicthandle - 
\param  extentname - Extent name
\param  newnames - New name for an extent or type
\param  targ_struct - Target type
\param  transaction - Transaction option
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtentDef"

logical DictionaryHandle :: CopyExtentDef (DictionaryHandle &srce_dicthandle, char *extentname, char *newnames, char *targ_struct, logical transaction, logical retain_schemav )
{
  Dictionary *dictionary      = get_dictionary();
  TypeKey     tkey(dictionary,extentname);
  TypeKey     nkey(newnames,tkey.GetID());
  Dictionary *srce_dictionary = srce_dicthandle.get_dictionary();
  return (   dictionary && srce_dictionary
           ? dictionary->CopyExtentDef(srce_dictionary,tkey,nkey,targ_struct,transaction) 
           : YES );

}

/******************************************************************************/
/**
\brief  CopyStructure - Copy structure definition
        The  function  copies  a  structure  definition  from  one dictionary to
        another.

\return term - Termination code

\param  srce_dicthandle - 
\param  strname - Type name
\param  namespace_id - 
\param  newnames - New name for an extent or type
\param  topname - Name of top-type
\param  db_replace - 
\param  retainSID - Retain internal type numbers
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyStructure"

logical DictionaryHandle :: CopyStructure (DictionaryHandle &srce_dicthandle, char *strname, int32 namespace_id, char *newnames, char *topname, PIREPL db_replace, logical retainSID, logical retain_schemav )
{
  Dictionary *dictionary      = get_dictionary();
  TypeKey     tkey(strname,namespace_id);
  TypeKey     nkey(newnames,namespace_id);
  Dictionary *srce_dictionary = srce_dicthandle.get_dictionary();
  return (   dictionary && srce_dictionary
           ? dictionary->CopyStructure(srce_dictionary,tkey,nkey,topname,db_replace,retainSID,retain_schemav) 
           : YES );

}

/******************************************************************************/
/**
\brief  CopyType - Copy type definition
        The function copies a type definition from one dictionary to another.

\return term - Termination code

\param  srce_dicthandle - 
\param  strnames - Structure name
\param  newnames - New name for an extent or type
\param  topname - Name of top-type
\param  db_replace - 
\param  retainSID - Retain internal type numbers
\param  transaction - Transaction option
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyType"

logical DictionaryHandle :: CopyType (DictionaryHandle &srce_dicthandle, char *strnames, char *newnames, char *topname, PIREPL db_replace, logical retainSID, logical transaction, logical retain_schemav )
{
  Dictionary *tdictionary      = get_dictionary();
  Dictionary *sdictionary      = srce_dicthandle.get_dictionary();
  TypeKey     skey(sdictionary,strnames);
  TypeKey     nkey(tdictionary,newnames);
  Dictionary *srce_dictionary = srce_dicthandle.get_dictionary();
  return (   tdictionary && srce_dictionary
           ? tdictionary->CopyType(srce_dictionary,skey,nkey,topname,db_replace,retainSID,retain_schemav,transaction) 
           : YES );

}

/******************************************************************************/
/**
\brief  CreateEnum - Create new enumeration
        he  function creates a new enumeration. The dictionary must be opened in
        write mode.
        When  defining a  new enumeration  in a  dictionary it has to be created
        before it can be opened for adding the enumeration items.

\return term - Termination code

\param  enum_name - Enumeration name
\param  basetype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEnum"

logical DictionaryHandle :: CreateEnum (char *enum_name, char *basetype )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CreateEnum(enum_name,basetype) 
                      : YES );

}

/******************************************************************************/
/**
\brief  CreateGlobalVariable - Create Global variable
        The  property  handle  passed  is  used  pattern  for  creating a global
        variable.  For  defining  the  global  variable,  a copy of the property
        handle  will be defined and returned.  Global variables must have unique
        names  in the field name of the property handle. You may pass a variable
        name,  which  will  be  used  for the variable instead of the field name
        defined  in the property handle passed. A global variable can be created
        only once for the same variable name.
        In  case of  multi threading  applications, global variables are defined
        separately for each thread and must be unique for each thread, only.

\return prophdl - 

\param  prophdl - 
\param  var_name - System variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGlobalVariable"

PropertyHandle *DictionaryHandle :: CreateGlobalVariable (PropertyHandle &prophdl, char *var_name )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CreateGlobalVariable(prophdl,var_name) 
                      : (PropertyHandle *)NULL );

}

/******************************************************************************/
/**
\brief  CreateParser - 


\return parser - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateParser"

BNFParser *DictionaryHandle :: CreateParser ( )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CreateParser() 
                      : NULL );

}

/******************************************************************************/
/**
\brief  CreateTempExtent - Create temporary extent
        A  temporary extent can be created for storing results of a qeuery (e.g.
        a  selection)  within  an  application. Temporary extents are created in
        main  storage or  in a  temporary database  and are available as long as
        the  database handle is opened. They  will be removed automatically when
        closing the database handle.
        When  a temporary extent has been created  once, you can open any number
        of property handles for accessing the extent.
        You  can  define  an  extent  for  a structure definition defined in the
        external  dictionary  by  referring  to  the  tsructure  name)  or by an
        internal  structure definition that has  been created by the application
        and is referenced by the field definition passed to the function.

\return extnames - Extent name
-------------------------------------------------------------------------------
\brief  ci - 


\param  strnames - Structure name
\param  extnames_w - Extent name
\param  key_name_w - Key name for conversion
\param  baseexts_w - Name for base extent
\param  weak_opt_w - Weak-typed option
\param  own_opt_w - Owning collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *DictionaryHandle :: CreateTempExtent (char *strnames, char *extnames_w, char *key_name_w, char *baseexts_w, logical weak_opt_w, logical own_opt_w )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CreateTempExtent(strnames,extnames_w,key_name_w,baseexts_w,weak_opt_w,own_opt_w) 
                      : (char *)NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  field_def - Property definition
\param  extnames_w - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *DictionaryHandle :: CreateTempExtent (DBFieldDef *field_def, char *extnames_w )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->CreateTempExtent(field_def,extnames_w) 
                      : (char *)NULL );

}

/******************************************************************************/
/**
\brief  DeleteEnum - 


\return term - Termination code

\param  enum_name - Enumeration name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEnum"

logical DictionaryHandle :: DeleteEnum (char *enum_name )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->DeleteEnum(enum_name) 
                      : YES );

}

/******************************************************************************/
/**
\brief  DictionaryHandle - Create dictionary handle
        Usually  the  dictionary  is  created  as  local  dictionary,  i.e.  the
        external dictionary must be provided in the local environment. 
        When  the  application  wants  to  refer  to  databases  on a server the
        dictionary  has  to  be  opened  as  server dictionary as well using the
        external  dictionary on the server. In  this case an ODABAClient with an
        opened  connection has to  be passed. When  the connection is not opened
        the system tries to open the dictionary as local dictionary.

-------------------------------------------------------------------------------
\brief  ci0 - 


\param  odaba_client - ODABA Client Handle
\param  cpath - Complete path
\param  accopt - Access option
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictionaryHandle"

     DictionaryHandle :: DictionaryHandle (ODABAClient &odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, ResourceTypes local_ressources, logical sysenv )
                     : DatabaseHandle ()
{

  Open(odaba_client,cpath,accopt,w_netopt,version_nr,local_ressources,sysenv);

}

/******************************************************************************/
/**
\brief  i02 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictionaryHandle"

     DictionaryHandle :: DictionaryHandle ( )
                     : DatabaseHandle ()
{



}

/******************************************************************************/
/**
\brief  i03 - 


\param  _dictionary - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictionaryHandle"

     DictionaryHandle :: DictionaryHandle (Dictionary *_dictionary )
                     : DatabaseHandle (_dictionary)
{



}

/******************************************************************************/
/**
\brief  i04 - 


\param  dictionary_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictionaryHandle"

     DictionaryHandle :: DictionaryHandle (const DictionaryHandle &dictionary_refc )
                     : DatabaseHandle ( )
{

  if ( dictionary_refc )
    *this = dictionary_refc;

}

/******************************************************************************/
/**
\brief  i1 - 


\param  db_handle - Pointer to database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictionaryHandle"

     DictionaryHandle :: DictionaryHandle (DatabaseHandle &db_handle )
                     : DatabaseHandle ()
{

  Open(db_handle);

}

/******************************************************************************/
/**
\brief  EnumToString - 


\return enum_string - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  enumeration - 
\param  enum_val - 
\param  string - String area
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnumToString"

char *DictionaryHandle :: EnumToString (char *enumeration, int32 enum_val, char *string, int32 len )
{
  Dictionary       *dictionary = get_dictionary();
  ENUM_ValueList   *vlist;
BEGINSEQ
  if ( !dictionary ||
       !(vlist = dictionary->GetValueList(enumeration)) )
                                                    ERROR
  string = vlist->GetString(enum_val,string,len);


RECOVER
  if ( string && len > 0 )
    *string = 0;
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  enumeration - 
\param  ph - 
\param  string - String area
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnumToString"

char *DictionaryHandle :: EnumToString (char *enumeration, PropertyHandle &ph, char *string, int32 len )
{

  return ( ph.IsNumeric() 
           ? EnumToString(enumeration,ph.GetInt(),string,len)
           : ph.IsText() && StringToEnum(enumeration,ph.GetString()) != CS_U 
             ? ph.GetString() : NULL                            );



}

/******************************************************************************/
/**
\brief  GetExtentDef - Get extent definition
        The  function returns the  extend definition for  the passed extent name
        from  the internal dictionary.  When the extent  definition has not been
        found  in the internal dictionary the  function will not read the extent
        definition from the external dictionary (see ProvideExtendDef()).

\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 


\param  extname - Extent name
\param  namespace_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentDef"

DBExtend *DictionaryHandle :: GetExtentDef (char *extname, int32 namespace_id )
{
  TypeKey       tkey(extname,namespace_id);
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->GetExtendDef(tkey) 
                      : (DBExtend *)NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentDef"

DBExtend *DictionaryHandle :: GetExtentDef (char *scoped_name )
{
  Dictionary   *dictionary = get_dictionary();
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  TypeKey       tkey(dictionary,scoped_name);
  
  return ( dictionary->GetExtendDef(tkey) );
RECOVER
  return((DBExtend *)NULL);
ENDSEQ


}

/******************************************************************************/
/**
\brief  GetGlobalVariable - Get global variable
        Global  variables  are  defined  as  elementary  values,  instances  or 
        collections.   Global   variables   can   be   defined   using   the  
        CreateGlobalVariable()   function.   Usually,   global   variables   are
        elementary   values   or   instances   referred   in   the context of an
        application  or  thread,  In  case of multi treading applicatins, global
        variables are defined separately for each thread.

\return prophdl - 

\param  var_name - System variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalVariable"

PropertyHandle *DictionaryHandle :: GetGlobalVariable (char *var_name )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->GetGlobalVariable(var_name) 
                      : (PropertyHandle *)NULL );

}

/******************************************************************************/
/**
\brief  GetID_SIZE - Size for identifying names in ODABA
        ODABA  has  a  unique  size  for identifying names. Since the identifier
        size  may change between different  ODABA versions this function returns
        the identifier size for the current version.

\return size - Size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID_SIZE"

int16 DictionaryHandle :: GetID_SIZE ( )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->GetID_SIZE() 
                      : UNDEF );

}

/******************************************************************************/
/**
\brief  GetLastSchemaVersion - Get highest schema version
        for internal use, only

\return schema_version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastSchemaVersion"

uint16 DictionaryHandle :: GetLastSchemaVersion ( )
{
  Dictionary   *dictionary = get_dictionary();
  return( dictionary ? dictionary->get_last_schemav() : UNDEF );

}

/******************************************************************************/
/**
\brief  GetStructDef - Get Structure definition
        Maintained for compatibility reasons. See ProvideStructureDef.

\return strdef - Structure definition

\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *DictionaryHandle :: GetStructDef (char *strnames )
{

  return(ProvideStructureDef(strnames));

}

/******************************************************************************/
/**
\brief  GetTempName - Get unique name for temporary resource
        The  function  provides  a  unique  internal  name  that can be used for
        creating temporary extents or other resources.

\return extname - Extent name

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempName"

char *DictionaryHandle :: GetTempName (char *extnames )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->GetTempName(extnames) 
                      : (char *)NULL );

}

/******************************************************************************/
/**
\brief  IsBasicType - Is type an elementary type?
        The  function returns YES when the passed  type is one of the elementary
        ODABA data types.

\return term - Termination code

\param  typenames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasicType"

logical DictionaryHandle :: IsBasicType (char *typenames )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->IsBasicType(typenames) 
                      : NO );

}

/******************************************************************************/
/**
\brief  LocateExtentDef - Provide extend definition
        The  function returns the  extend definition for  the passed extent name
        from  the internal dictionary.  When the extent  definition has not been
        found  in the internal  dictionary the function  will provide the extent
        definition  in the internal  dictionary by reading  it from the external
        dictionary.
        In  contrast to  ProvideExtentDef() the  function does  not set a system
        error when the extent definition coud not be found.

\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 


\param  extname - Extent name
\param  namespace_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateExtentDef"

DBExtend *DictionaryHandle :: LocateExtentDef (char *extname, int32 namespace_id )
{
  Dictionary   *dictionary = get_dictionary();
  TypeKey     tkey(extname,namespace_id);
  return ( dictionary ? dictionary->LocateExtentDef(tkey) 
                      : (DBExtend *)NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateExtentDef"

DBExtend *DictionaryHandle :: LocateExtentDef (char *scoped_name )
{
  Dictionary   *dictionary = get_dictionary();
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  TypeKey       tkey(dictionary,scoped_name);
  
  return ( dictionary->LocateExtentDef(tkey) );
RECOVER
  return((DBExtend *)NULL);
ENDSEQ

}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code
/******************************************************************************/
/**
\brief  ci0 - 


\param  odaba_client - ODABA Client Handle
\param  cpath - Complete path
\param  accopt - Access option
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DictionaryHandle :: Open (ODABAClient &odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, ResourceTypes local_ressources, logical sysenv )
{
  Dictionary *dictionary = NULL;
  logical     is_server  = NO;
  char       *xs_pref    = NULL;
  char       *oxs_pref   = NULL;
  logical     term = NO;
BEGINSEQ
  Close(); 
  SDBRESET
  
  if ( local_ressources != RES_server_intern )
  {
    if ( !odaba_client || !odaba_client.IsConnected() )
      local_ressources = RES_local;
    else
      if ( local_ressources == RES_automatic && cpath )
        local_ressources = *cpath == '%' ? RES_server : RES_local;
    if ( !cpath )
      local_ressources = RES_automatic;
  }
  
  switch ( local_ressources )
  {
    case RES_automatic: if ( !(dictionary = new LDictionary()) )
                                                     SDBERR(95)
                                                     SDBCERR
                        break;
    
    // Dictionaries werden immer ohne Context abgearbeitet (sysenv = YES), sonst gibt es Probleme beim Kopieren der SysDB
    // 8.3.2006 (ein Jahr später): das geht aber nicht. Wir müssen also von aussen dafür sorgen, dass sysenv beim Kopieren auf 1 gesetzt ist
    
    case RES_server_intern : is_server = YES;
    case RES_local : if ( !IsFile(cpath) || LDBHandle::Exist(cpath,NO) )
                       dictionary = new LDictionary(cpath,accopt,w_netopt,version_nr,sysenv,is_server);
                     else
                     {
                       xs_pref = GetSysVariable("XS_NAMESPACE");
                       oxs_pref = GetSysVariable("OXS_NAMESPACE");
                       dictionary = new XDictionary(cpath,accopt,xs_pref,oxs_pref);
                     }
                     SDBCERR
                     break;
    case RES_server   : if ( !(dictionary = new CDictionary(odaba_client.GetClientPtr(),cpath,accopt,w_netopt,version_nr,local_ressources,sysenv)) )
                                                     SDBERR(95)
                                                     SDBCERR
                        break;
    default           : SDBERR(99)
  }
  object_handle = dictionary;
  object_handle->Connect(this);
RECOVER
  delete dictionary;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  db_handle - Pointer to database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical DictionaryHandle :: Open (DatabaseHandle &db_handle )
{
  DBHandle   *db_hdl     = db_handle.get_dbhandle();
  Dictionary *dictionary = NULL;
  logical     term = NO;
BEGINSEQ
  SDBRESET
  if ( db_hdl )
  {
    if ( db_hdl->GetClientDBHandle() )
      dictionary = new CDictionary(db_hdl);
    else
      dictionary = new LDictionary(db_hdl);
    if ( !dictionary )                               SDBERR(95)
                                                     SDBCERR
    object_handle = dictionary;
  }
  else
    object_handle = new LDictionary(NULL);  // system dictionary
  object_handle->Connect(this);
RECOVER
  delete dictionary;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenDictionary - 


\return term - Termination code

\param  odaba_client - ODABA Client Handle
\param  cpath - Complete path
\param  accopt - Access option
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  local_ressources - Resource type
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDictionary"

logical DictionaryHandle :: OpenDictionary (ODABAClient &odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, ResourceTypes local_ressources, logical sysenv )
{

  return( Open(odaba_client, cpath, accopt, w_netopt, version_nr,local_ressources,sysenv ) );

}

/******************************************************************************/
/**
\brief  ParseExpression - Parse expression
        The  function allows parsing an expression according to the common ODABA
        syntax   specification   for   OQL   expressions   and   ODL  data model
        definiitions.  The function  returns a  BNFData tree,  which can be used
        for  further evaluation.  In case  of an  error the function produces an
        error in the trace file. 
        The  application must  destroy the  BNFData object,  when not being used
        anymore.

\return bdata - 

\param  expression - 
\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParseExpression"

BNFData *DictionaryHandle :: ParseExpression (char *expression, char *symbol )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->ParseExpression(expression,symbol,NULL) 
                      : (BNFData *)NULL );

}

/******************************************************************************/
/**
\brief  ParseFile - Parse file
        The  function  allows  parsing  a  file,  which  contains  an expression
        according  to the common ODABA  syntax specification for OQL expressions
        and  ODL data model  definiitions. The function  returns a BNFData tree,
        which  can  be  used  for  further  evaluation.  In case of an error the
        function produces an error in the trace file. 
        The  application must  destroy the  BNFData object,  when not being used
        anymore.

\return bdata - 

\param  cpath - Complete path
\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParseFile"

BNFData *DictionaryHandle :: ParseFile (char *cpath, char *symbol )
{
  Dictionary   *dictionary = get_dictionary();
  return ( dictionary ? dictionary->ParseFile(cpath,symbol) 
                      : (BNFData *)NULL );

}

/******************************************************************************/
/**
\brief  ProvideExtentDef - Provide extent definition
        The  function returns the  extend definition for  the passed extent name
        from  the internal dictionary.  When the extent  definition has not been
        found  in the internal  dictionary the function  will provide the extent
        definition  in the internal  dictionary by reading  it from the external
        dictionary.

\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 


\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtentDef"

DBExtend *DictionaryHandle :: ProvideExtentDef (char *scoped_name )
{
  Dictionary   *dictionary = get_dictionary();
  TypeKey       tkey(dictionary,scoped_name);
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  TypeKey       tkey(dictionary,scoped_name);
  

RECOVER
  return((DBExtend *)NULL);
ENDSEQ
  return ( dictionary->ProvideExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  extnames - Extent name
\param  namespace_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtentDef"

DBExtend *DictionaryHandle :: ProvideExtentDef (char *extnames, int32 namespace_id )
{
  Dictionary   *dictionary = get_dictionary();
  TypeKey       tkey(extnames,namespace_id);
  return ( dictionary ? dictionary->ProvideExtendDef(tkey) 
                      : (DBExtend *)NULL );

}

/******************************************************************************/
/**
\brief  ProvideStructureDef - Provide structure definition from internal or external dictionary
        The  function returns the structure  definition for the passed structure
        name  from  the  internal  dictionary. When the structure definition has
        not  been found in the internal dictionary the function will provide the
        extent  definition  in  the  internal  dictionary by reading it from the
        external dictionary.

\return strdef - Structure definition
-------------------------------------------------------------------------------
\brief  i0 - 


\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructureDef"

DBStructDef *DictionaryHandle :: ProvideStructureDef (char *scoped_name )
{
  Dictionary   *dictionary = get_dictionary();
  DBStructDef  *struct_def = NULL;
  smcb         *smcbptr;
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  TypeKey       tkey(dictionary,scoped_name);
  
  if ( !(smcbptr = dictionary->GetSMCB(tkey)) )     ERROR
  if ( !smcbptr->smcbsts.stscnof() )                 SDBERR(20)
    
  struct_def = (DBStructDef *)smcbptr;
RECOVER

ENDSEQ
  return(struct_def);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  strnames - Structure name
\param  namespace_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructureDef"

DBStructDef *DictionaryHandle :: ProvideStructureDef (char *strnames, int32 namespace_id )
{
  Dictionary   *dictionary = get_dictionary();
  TypeKey       tkey(strnames,namespace_id);
  DBStructDef  *struct_def = NULL;
  smcb         *smcbptr;
BEGINSEQ
  if ( !dictionary )                                 ERROR
    
  if ( !(smcbptr = dictionary->GetSMCB(tkey)) )     ERROR
  if ( !smcbptr->smcbsts.stscnof() )                 SDBERR(20)
    
  struct_def = (DBStructDef *)smcbptr;
RECOVER

ENDSEQ
  return(struct_def);
}

/******************************************************************************/
/**
\brief  SetLastSchemaVersion - Set highest schema version
        for internal use, only


\param  schema_version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastSchemaVersion"

void DictionaryHandle :: SetLastSchemaVersion (uint16 schema_version )
{
  Dictionary   *dictionary = get_dictionary();
  dictionary->SetLastSchemaVersion(schema_version);

}

/******************************************************************************/
/**
\brief  StringToEnum - 


\return enum_val - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  enumeration - 
\param  enum_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringToEnum"

int32 DictionaryHandle :: StringToEnum (char *enumeration, char *enum_string )
{
  Dictionary       *dictionary = get_dictionary();
  ENUM_ValueList   *vlist      = NULL;
  int32             enum_val   = CS_U;
BEGINSEQ
  if ( !dictionary || 
       !(vlist = dictionary->GetValueList(enumeration)) )
                                                    ERROR
  enum_val = vlist->GetCode(enum_string);
RECOVER
  enum_val = CS_U;
ENDSEQ
  return(enum_val);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  enumeration - 
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringToEnum"

int32 DictionaryHandle :: StringToEnum (char *enumeration, PropertyHandle &ph )
{
  char     string[ID_SIZE+1];
  return ( ph.IsText() 
           ? StringToEnum(enumeration,ph.GetString()) 
           : ph.IsNumeric() && EnumToString(enumeration,ph.GetInt(),string,sizeof(string)) 
             ? ph.GetInt() : CS_U                      );



}

/******************************************************************************/
/**
\brief  UpdateVersion - Update highest schema version
        for internal use, only.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateVersion"

logical DictionaryHandle :: UpdateVersion ( )
{
  Dictionary   *dictionary = get_dictionary();
  return (   dictionary 
           ? dictionary->UpdateVersion() 
           : YES );


}

/******************************************************************************/
/**
\brief  get_dictionary - Get dictionary pointer
        for internal use, only.

\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_dictionary"

Dictionary *DictionaryHandle :: get_dictionary ( )
{
  ACObject     *obhandle = get_obhandle();

  return ( obhandle ? obhandle->GetThisDictionary() : NULL );
}

/******************************************************************************/
/**
\brief  operator bool - Dictionary opened
        The  function returns  YES (true)  when the  dictionary handle is opened
        and  NO (false) when the  dictionary is not opened  or when an error had
        occured while constructing the dictionary handle.

\return notype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator bool"

NOTYPE DictionaryHandle :: operator bool ( ) const
{

  return ( object_handle ? YES : NO );

}

/******************************************************************************/
/**
\brief  operator-> - Get dictionary pointer
        for internal use, only.

\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator->"

Dictionary *DictionaryHandle :: operator-> ( )
{

  return(get_dictionary());

}

/******************************************************************************/
/**
\brief  operator= - 


\return dicthandle - 

\param  dictionary_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DictionaryHandle &DictionaryHandle :: operator= (const DictionaryHandle &dictionary_refc )
{

  if ( get_obhandle() != dictionary_refc.get_obhandle() )
  {
    Close();
    ObjectReferenceHandle::Open(dictionary_refc.get_obhandle());
  }
  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - Compare dictionary handles
        The  function  returns  YES  (true) when the dictionary handles compared
        are identical.

\return cond - Return value

\param  dictionary_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DictionaryHandle :: operator== (const DictionaryHandle &dictionary_refc )
{

  return(this && &dictionary_refc ? object_handle == dictionary_refc.object_handle : NO);

}

/******************************************************************************/
/**
\brief  ~DictionaryHandle - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DictionaryHandle"

     DictionaryHandle :: ~DictionaryHandle ( )
{

  Close();

}


