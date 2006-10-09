/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    LDictionary

\brief    Dictionary
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/08/26 12:57:29,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LDictionary"

#include  <popa7.h>
#include  <coctp.h>
#include  <ifil.h>
#ifndef   GSRT_OBH_ListEntry_HPP
#define   GSRT_OBH_ListEntry_HPP
#include  <sOBH_ListEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDBHeader.hpp>
#include  <sDBInfo.hpp>
#include  <sDLL_Handle.hpp>
#include  <sLDictionary.hpp>
#include  <sOBH_ListEntry.hpp>
#include  <sSDB_Attribute.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Extend.hpp>
#include  <sSDB_Key.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_ViewExtent.hpp>
#include  <smvli.hpp>
#include  <sLDictionary.hpp>


/******************************************************************************/
/**
\brief  CreateDBHandle - 



\return dbhandle - Database handle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBHandle"

DBHandle *LDictionary :: CreateDBHandle (char *cpath, PIACC accopt, logical netopt, uint16 version_nr, char sysenv )
{
  DBHandle   *dbhandle   = NULL;

BEGINSEQ
  if ( !(dbhandle = new LDBHandle(this,cpath,accopt,netopt,version_nr,sysenv)) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  delete dbhandle;
  dbhandle = NULL;
ENDSEQ
  return(dbhandle);
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBHandle"

DBHandle *LDictionary :: CreateDBHandle ( )
{

  return(new LDBHandle());

}

/******************************************************************************/
/**
\brief  i2 - 



\param  cpath - Complete path
\param  dasize - Size of data area in byte
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBHandle"

DBHandle *LDictionary :: CreateDBHandle (char *cpath, int32 dasize )
{
  DBHandle   *dbhandle   = NULL;

BEGINSEQ
  if ( !(dbhandle = new LDBHandle(cpath,dasize)) )
                                                     SDBERR(95)
                                                     SDBCERR

RECOVER

ENDSEQ
  return(dbhandle);
}

/******************************************************************************/
/**
\brief  CreateExtentDef - 



\return dbextdef - Extent definition

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtentDef"

DBExtend *LDictionary :: CreateExtentDef (TypeKey &tkey )
{
  PropertyHandle          extpi;
  PropertyHandle         *ref_ph = NULL;
  DBStructDef            *dbstrdef = NULL;
  logical                 reserved = NO;
  DBExtend               *dbextdef = NULL;
BEGINSEQ
  ILock(YES);
  reserved = Reserve_extent_pi(extpi);
  
  if ( extpi(tkey.GetKey()) )
    ref_ph = &extpi;
  else if (  (*refr_pi)(tkey.GetKey()) )
    ref_ph = refr_pi;
  else if ( codeset_pi->Get(tkey.GetKey()) )   
  {
    if ( !(dbextdef = new DBExtend(this,codeset_pi,dbstrdef)) ) 
                                                     SDBERR(95)
                                                     SDBCERR
    LEAVESEQ
  }
      
  SDBEV1(tkey.Name(),ID_SIZE)
  if ( !ref_ph )                                      SDBERR(68)
  
  if ( !(dbstrdef = ProvideType(*ref_ph)) )
  {
    switch ( ref_ph->GetInt("ddeatyp") )
    {
      case AT_BIN   : if ( !(dbstrdef = DLLHandle()->CreateStructDef("OBINA.DLL",this,tkey.Name())) )
                                                      SDBCERR
                      break;
      case AT_ODBC  : if ( !(dbstrdef = DLLHandle()->CreateStructDef("OODBC.DLL",this,tkey.Name())) )
                                                      SDBCERR
                      break;
      case AT_ODABA :
      case AT_CODE  :
      case AT_NONE  :  
      default       : ;
    }
  }
  if ( !dbstrdef )                                    SDBERR(20)
  
  if ( dbextdef   = GetExtendDef(tkey) )              LEAVESEQ
  
  if ( extpi.Get(tkey.GetKey()) )   
  {
    if ( !(dbextdef = new DBExtend(extpi,this,dbstrdef,NULL)) ) 
                                                     SDBERR(95)
                                                     SDBCERR
  }
  else if ( viewext_pi->Get(tkey.GetKey()) )
  {
    if ( !(dbextdef = new DBExtend(this,dbstrdef,*viewext_pi)) ) 
                                                     SDBERR(95)
                                                     SDBCERR
  }
  else if ( refr_pi->Get(tkey.GetKey()) )
  {
    if ( !(dbextdef = new DBExtend(*refr_pi,this,dbstrdef)) ) 
                                                     SDBERR(95)
                                                     SDBCERR
    dbextdef->set_log_ref(YES);
  }
  else
  {
    SDBEV1(tkey.Name(),ID_SIZE)
    SDBERR(20)
  }
RECOVER
  delete     dbextdef;
  dbextdef = NULL;
ENDSEQ
  Release_extent_pi(reserved);
  IUnlock();
  return(dbextdef);
}

/******************************************************************************/
/**
\brief  CreateStructDef - 



\return strdef - Structure definition

\param  tkey - 
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStructDef"

DBStructDef *LDictionary :: CreateStructDef (TypeKey &tkey, DBStructDef *strdef )
{
  PropertyHandle    strpi;
  DBStructDef      *struct_def = NULL;
  logical           reserved = NO;
  char              strname[ID_SIZE];
  ILock(YES);
  
  SDBEV1(tkey.Name(),ID_SIZE)
  reserved = Reserve_struct_pi(strpi);

  if ( strpi(tkey.GetKey()) )
  {
    if ( strpi.GetInt("smcestyp") == ST_VIEW )
      struct_def = ReadVD(tkey,strdef);
    else
      struct_def = ReadSD(strpi,tkey,strdef);
  }
  else if ( (*codeset_pi)(tkey.GetKey()) )           
    struct_def = ReadVL(tkey,strdef);
    
  strpi.Cancel();
  codeset_pi->Cancel();
  Release_struct_pi(reserved);
  IUnlock();
  return(struct_def);
}

/******************************************************************************/
/**
\brief  DictDisplay - 



\return term - Termination code

\param  cpath - Complete path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictDisplay"

logical __cdecl LDictionary :: DictDisplay (char *cpath, char *ppath )
{
  logical         term   = NO;
BEGINSEQ
  LDictionary dict(cpath,PI_Read,YES);                SDBCERR 
  term = dict.Display(ppath);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetLastStructureID - 



\return sid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastStructureID"

int16 LDictionary :: GetLastStructureID ( )
{
  int16                   sid = 1000;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( db_header )
    sid = db_header->get_last_str_number();
RECOVER
  sid = 1000;
ENDSEQ
  return(sid);
}

/******************************************************************************/
/**
\brief  GetLocalDictionary - 



\return ldictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalDictionary"

LDictionary *LDictionary :: GetLocalDictionary ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  GetOBHandle - 



\return obhandle - Database Object handle

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOBHandle"

ACObject *LDictionary :: GetOBHandle (uint16 version_nr )
{
  OBH_ListEntry          *obh_ent;
  ACObject               *obhandle = NULL;
BEGINSEQ
  // work dictionary does not support structure versions
  if ( !obh_list )                                   SDBERR(99)

  if ( obh_ent = obh_list->GetEntry(&version_nr) )
    obhandle = obh_ent->get_ob_handle();
  else
  {
    if ( !(obhandle = new LACObject(this,access_mode,version_nr)) )
                                                     SDBERR(95)
                                                     SDBCERR
    OBH_ListEntry   obh_entry(obhandle,obhandle->get_version());
    if ( !obh_list->AddEntry(&obh_entry) )           ERROR
  }

RECOVER
  delete obhandle;
  obhandle = NULL;
ENDSEQ
  return(obhandle);
}

/******************************************************************************/
/**
\brief  LDictionary - Create dictionary handle



-------------------------------------------------------------------------------
\brief  i0 - 



\param  cpath - Complete path
\param  accopt - Access mode
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  sysenv - System application
\param  is_server - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDictionary"

     LDictionary :: LDictionary (char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, char sysenv, logical is_server )
                     : Dictionary (),
LDBHandle (),
DBHandle(),
ACObject()
{
  OBH_ListEntry        *ob_entry;

BEGINSEQ
  SDBEV1(cpath,UNDEF)
  SDBCERR
  
  Dictionary::Initialize(cpath,accopt,w_netopt,version_nr,sysenv);
  LDBHandle::Initialize(NULL,cpath,accopt,w_netopt,(logical)YES,version_nr,sysenv,is_server);
                                                     SDBCERR
  local_dictionary = this;
  if ( OpenDictionary() )                            ERROR
  
  if ( OpenRootObject() )                            SDBCERR
  UpdateVersionList();                               // Version might have changed
    
  if ( OpenPIs() )                                   ERROR
  
  delete database_info;
  database_info = new DBInfo(this,NULL);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDictionary"

     LDictionary :: LDictionary ( )
                     : Dictionary (),
LDBHandle (),
DBHandle (),
ACObject()
{

BEGINSEQ
  SDBCERR
  local_dictionary = this;
  if ( OpenDictionary() )                            ERROR
    

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDictionary"

     LDictionary :: LDictionary (DBHandle *dbhandle )
                     : Dictionary (),
LDBHandle (),
DBHandle ()
{
  LDBHandle        *ldbhandle = dbhandle->GetLocalDBHandle();
BEGINSEQ
  SDBCERR
  local_dictionary = this;
  if ( OpenDictionary() )                            ERROR
  
  if ( !ldbhandle )                                  ERROR
    
  extend_list     = ldbhandle->get_extend_list();
  temp_extend_list= ldbhandle->get_temp_extend_list();
  acextent_tree   = ldbhandle->get_acextent_tree();
  acextent_list.SetTree(acextent_tree);
  object_instance = ldbhandle->get_object_instance();
  root_base       = ldbhandle->get_root_base();
  current_rb      = ldbhandle->get_root_base();
  db_header       = ldbhandle->get_db_header();
  db_handle       = this;
  original_sal    = struct_acc_list = new DPA(StructAccess)(256);
  
  OpenPIs(dbhandle,NO);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SaveExtList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveExtList"

logical LDictionary :: SaveExtList ( )
{

    extend_list->set_refmod();
    return(extend_list->Save());


}

/******************************************************************************/
/**
\brief  UpdateVersion - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateVersion"

logical LDictionary :: UpdateVersion ( )
{
  uint16                  version;
  logical                 term = NO;
BEGINSEQ
  while ( (version = GetVersion()) < last_schemav )
  {
    NewVersion();                                     SDBCERR
    SetVersion(version+1);
    UpdateVersionList();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~LDictionary - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~LDictionary"

     LDictionary :: ~LDictionary ( )
{

  if ( !*db_path )
  {
    ClosePIs();  
    
    db_handle       = NULL;
    extend_list     = NULL;
    temp_extend_list= NULL;
    object_instance = NULL;
    root_base       = NULL;
    current_rb      = NULL;
    db_header       = NULL;
    acextent_tree   = NULL;
    acextent_list.SetTree(NULL);
  }
  CloseDictionary();
  


}


