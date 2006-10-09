/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Relationship



\date     $Date: 2006/05/14 13:14:05,43 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Relationship"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Structure.hpp>
#include  <spc_SDB_Relationship.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
\param  ext_ph - PropertyHandle of type SDB_Extent
\param  base_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Relationship :: Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph, logical base_opt )
{
  PropertyHandle  *ddetype  = GPH("ddetype");
  PropertyHandle  *ddeinv   = GPH("ddeinv");
  PropertyHandle  *ddeext   = GPH("ddeext");
  PropertyHandle  *ddesecr  = GPH("ddesecr");
  PropertyHandle  *str_rshp = NULL;
  PropertyHandle  *str_base = NULL;
  PropertyHandle  *inv_ph   = NULL;
  TypeKey          tkey;
  logical          term         = NO;
BEGINSEQ
  protocol->SetErrorVariable(2,GPH("sys_ident")->GetString(),0);

  term = pc_SDB_Reference::Check(protocol,str_ph,cs_ph,base_opt);
  GetTypeKey(tkey);

  if ( CheckExtend(protocol,str_ph,ext_ph,NULL) )
    term = YES;
    
  if ( !GPH("ddeext")->IsEmpty() )
    SetProperty("owning","N",protocol,"required when base extent");
  
  if ( !ddeinv->IsEmpty() )
  {
    if ( !str_ph->Get(tkey.GetKey()) )
    {
      if ( !term )
        protocol->Write(140,0);
      ERROR
    } 
    if ( GPH("week_typed")->IsTrue() && *ddetype == *GetParentProperty()->GPH("sys_ident") )
                                                     LEAVESEQ
    str_rshp = str_ph->GPH("smcershp");
    str_base = str_ph->GPH("smcebase");
    
    if ( str_rshp->Get(*ddeinv) )
      inv_ph = str_rshp;
    else
    {
      if ( !str_base->Get(*ddeinv) )
      {
        protocol->Write(191,0,NULL,NULL,GetScopedType(),ddeinv->GetString());
        ERROR
      }
      else if ( base_opt )
      {
        protocol->Write(195,0,NULL,NULL,GetScopedType(),ddeinv->GetString());
        ERROR
      }
      inv_ph = str_base;
    }
          
    switch ( inv_ph->GPH("ddesecr")->GetInt() + ddesecr->GetInt() )
      {
        case 0  : if ( base_opt )
                  {
                    *inv_ph->GPH("ddesecr") = (logical)YES;
                    protocol->Write(194,0,NULL,NULL,GetScopedType(),ddeinv->GetString());
                  }
                  else
                  {
                    *ddesecr = (logical)YES;
                    protocol->Write(192,0);
                  }
                  break;
        case 2  : *ddesecr = (logical)NO;
                  protocol->Write(193,0);
                  break;
        case 1  : 
        default : break;
      }
    
    if ( !ddesecr->IsTrue() && ddeext->IsEmpty() )
      SetProperty("owning","Y",protocol,"required for primary and no extend");
    SetProperty("update","Y",protocol,"required for inverse");
  }
  else
  {
    SetProperty("ddesecr","N",protocol,"default for no inverse");
    if ( ddeext->IsEmpty() )
      SetProperty("owning","Y",protocol,"reqired for no inverse and no extend");
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckAll

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
\param  ext_ph - PropertyHandle of type SDB_Extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAll"

logical pc_SDB_Relationship :: CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph )
{
  int       indx0 = 0;
  logical   term  = NO;
  while ( Get(indx0++) )
    if ( Check(protocol,str_ph,cs_ph,ext_ph,NO) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckExtend

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  ext_ph - PropertyHandle of type SDB_Extent
\param  extent_path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtend"

logical pc_SDB_Relationship :: CheckExtend (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *ext_ph, char *extent_path )
{
  TypeKey           tkey;
  TypeKey           ekey;
  char              string[512];
  logical           term      = NO;
BEGINSEQ
  if ( !extent_path )
    extent_path = GPH("ddeext")->GetString();
  
  if ( *extent_path > ' ' && *extent_path != '*' )
  {
    pc_SDB_Structure   struct_pc(GetParentProperty());
    pc_SDB_Structure   str_pc(str_ph);

    GetExtentKey(ekey,extent_path);
     
    if ( *extent_path == '.' )
    {
      if ( strlen(extent_path) < 3 || extent_path[1] != '.' || extent_path[2] == '.' ) 
      {
        protocol->Write(307,0,struct_pc.ScopedName(string,sizeof(string)),GPH("sys_ident")->GetString(),NULL,ekey.ScopedName(GetDBHandle(),string,sizeof(string)));
        ERROR
      }                                     
      if ( !str_pc(struct_pc.GetTypeKey(tkey).GetKey()) )
      {
        protocol->Write(99,0);
        ERROR
      }                                     
      if ( str_pc.CheckBasePath(protocol,extent_path+2,GetTypeKey(tkey)) )
          ERROR
    }
    else
    {
      if ( !ext_ph->Get(ekey.GetKey()) )
      {
        protocol->Write(190,0,struct_pc.ScopedName(string,sizeof(string)),GPH("sys_ident")->GetString(),NULL,ekey.ScopedName(GetDBHandle(),string,sizeof(string)));
        ERROR
      }                                     
      SetProperty("owning","N",protocol,"empty or invalid extend");
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetExtentKey

\return tkey

\param  tkey
\param  extent_path_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentKey"

TypeKey &pc_SDB_Relationship :: GetExtentKey (TypeKey &tkey, char *extent_path_w )
{

BEGINSEQ
  if ( !extent_path_w )
    extent_path_w = GPH("ddeext")->GetString();

  tkey.Initialize("",0);
  
  if ( !IsPositioned() )                            ERROR
  
  tkey.Initialize(GetDBHandle(),
                  GPH("scope")->GetString(),
                  extent_path_w);
RECOVER

ENDSEQ
  return(tkey);
}

/******************************************************************************/
/**
\brief  Store

\return term

\param  dbflddef
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_Relationship :: Store (DBFieldDef *dbflddef )
{
  logical   term = NO;
BEGINSEQ
  if ( pc_SDB_Reference::Store(dbflddef) )          ERROR

  *GPH("ddeext")  = (char *)dbflddef->get_extend();
  *GPH("ddeinv")  = (char *)dbflddef->get_inverse_name();
  *GPH("ddesecr") = dbflddef->get_sec_reference();
  *GPH("dderlog") = dbflddef->get_log_reference();
  *GPH("depend")  = dbflddef->get_depend();
  
  Save();                                           SDBCERR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StoreAll

\return term

\param  strdefptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreAll"

logical pc_SDB_Relationship :: StoreAll (DBStructDef *strdefptr )
{
  DBFieldDef *dbflddef = NULL;
  int32       indx0    = strdefptr->get_base_info().get_count() +
                         strdefptr->get_attr_info().get_count() +
                         strdefptr->get_refr_info().get_count();
  int32       count    = indx0 + strdefptr->get_rshp_info().get_count();
  logical     term     = NO;
BEGINSEQ
  DeleteSet();                                       SDBCERR
  
  while ( indx0 < count )
    if ( dbflddef = strdefptr->GetEntry(++indx0) )
    {
      ToTop();
      Add();                                         SDBCERR
      if ( Store(dbflddef) )
        term = YES;
    }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Relationship


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Relationship"

     pc_SDB_Relationship :: pc_SDB_Relationship (PropertyHandle *prophdl )
                     : pc_SDB_Reference(prophdl)
{
}


