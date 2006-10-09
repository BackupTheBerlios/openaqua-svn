/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Structure



\date     $Date: 2006/05/13 17:26:44,48 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Structure"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Attribute.hpp>
#include  <spc_SDB_BaseStruct.hpp>
#include  <spc_SDB_Key.hpp>
#include  <spc_SDB_Reference.hpp>
#include  <spc_SDB_Relationship.hpp>
#include  <spc_SDB_Structure.hpp>


/******************************************************************************/
/**
\brief  Check

\return term
-------------------------------------------------------------------------------
\brief  i00


\param  protocol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Structure :: Check (ErrorProtocol *protocol )
{
  logical     term = NO;
BEGINSEQ
  PropertyHandle      str_ph(GetDBHandle(),"SDB_Structure",PI_Read);
                                                     SDBCERR
  PropertyHandle      cs_ph(GetDBHandle(),"SDB_ValueList",PI_Read);
                                                     SDBCERR
  PropertyHandle      ext_ph(GetDBHandle(),"SDB_Extend",PI_Read);
                                                     SDBCERR
  
  if ( Check(protocol,&str_ph,&cs_ph,&ext_ph) )      ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
\param  ext_ph - PropertyHandle of type SDB_Extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Structure :: Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph )
{
  logical   term = NO;
BEGINSEQ
  protocol->SetErrorVariable(1,GPH("sys_ident")->GetString(),0);
  
  pc_SDB_BaseStruct  base_pc(GPH("smcebase"));
  if ( base_pc.CheckAll(protocol,str_ph,cs_ph,ext_ph) )
                                                    ERROR
  pc_SDB_Attribute  attr_pc(GPH("smcepdde"));
  if ( attr_pc.CheckAll(protocol,str_ph,cs_ph) ) 
                                                    ERROR
  pc_SDB_Reference  refr_pc(GPH("smcepref"));
  if ( refr_pc.CheckAll(protocol,str_ph,cs_ph) )
                                                    ERROR
  pc_SDB_Relationship  rshp_pc(GPH("smcershp"));
  if ( rshp_pc.CheckAll(protocol,str_ph,cs_ph,ext_ph) )
                                                    ERROR
  pc_SDB_Key  key_pc(GPH("smcepsmc"));
  if ( key_pc.CheckAll(protocol) )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  SetChecked(!term);
  protocol->Append(' ',2);
  protocol->Append(GPH("sys_ident")->GetString(),0);
  protocol->Append((char*)(term ? "...CheckError(s)\n" : "...Checked\n"),0);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckBasePath

\return term

\param  protocol
\param  prop_path
\param  tkey
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckBasePath"

logical pc_SDB_Structure :: CheckBasePath (ErrorProtocol *protocol, char *prop_path, TypeKey &tkey )
{
  PropertyHandle    *prop_ph   = NULL;
  TypeKey            prop_tkey;
  char              *work_path = strdup(prop_path);
  char              *next_prop = NULL;
  logical            term      = NO;
BEGINSEQ
  if ( next_prop = strchr(work_path,'.') )
    *next_prop = 0;

  if ( !(prop_ph = GetMember(protocol,work_path,YES,YES)) || !prop_ph->IsA("SDB_Relationship") )
  {
    protocol->Write(308,0,NULL,NULL,NULL,prop_path,work_path,NULL);
    ERROR
  }

  pc_SDB_Relationship  rel_pc(prop_ph);
  rel_pc.GetTypeKey(prop_tkey);

  if ( rel_pc.GPH("ddeinv")->IsEmpty() && next_prop )                
    protocol->Write(309,1,NULL,NULL,NULL,prop_path,work_path,NULL);

  if ( !next_prop ) 
  {
    if ( prop_tkey != tkey )
    {
      if ( !rel_pc.GPH("week_typed")->IsTrue() ||
           !IsBasedOn(tkey,prop_tkey)             )
      {
        protocol->Write(313,0,NULL,NULL,NULL,prop_path,NULL,NULL);
        ERROR
      }
    }
  }
  else
  {  
    if ( rel_pc.GPH("ddedim")->GetInt() != 1 )            
      protocol->Write(310,1,NULL,NULL,NULL,prop_path,work_path,NULL);
    
    if ( !rel_pc.GPH("owning")->IsTrue()  && 
         !rel_pc.GPH("depend")->IsTrue()  &&
         !rel_pc.GPH("ddesecr")->IsTrue()   ) 
      protocol->Write(311,1,NULL,NULL,NULL,prop_path,work_path,NULL);

    pc_SDB_Structure     str_copy_pc(*this);
    if ( !str_copy_pc.Get(prop_tkey.GetKey()) )
    {
      protocol->Write(312,0,NULL,NULL,rel_pc.GetScopedType(),prop_path,work_path,NULL);
      ERROR
    }
  
    if ( str_copy_pc.CheckBasePath(protocol,next_prop+1,tkey) )
                                                    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  free(work_path);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckKeyField

\return term

\param  protocol
\param  prop_path
\param  refr_accept
\param  mult_accept
\param  base_accept
\param  err_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckKeyField"

logical pc_SDB_Structure :: CheckKeyField (ErrorProtocol *protocol, char *prop_path, logical refr_accept, logical mult_accept, logical base_accept, logical err_opt )
{
  PropertyHandle   *prop_ph   = NULL;
  PropertyHandle   *ph        = NULL;
  TypeKey           tkey;
  char             *pkt       = NULL;
  char             *work_path = strdup(prop_path);
  char             *savev1    = strdup(protocol->GetErrorVariable(1,""));
  char             *savev2    = strdup(protocol->GetErrorVariable(2,""));
  int32             indx0     = 0;
  logical           term      = NO;
BEGINSEQ
  if ( pkt = strchr(work_path,'.') )
    *pkt = 0;
  
  if ( strlen(work_path) > ID_SIZE )
  {
    protocol->Write(151,0,NULL,work_path);
    ERROR
  }
    
  if ( !(prop_ph = GetMember(work_path,NO,NO)) ) 
  {
    PropertyHandle phwork_path(work_path);
    if ( !pkt && base_accept &&
         GPH("smcepsmc")->Get(phwork_path) )        LEAVESEQ
    if ( (ph = GPH("smcebase"))->GetCount() > 0 )
    {
      pc_SDB_Structure   str_copy_pc(*this);
      pc_SDB_BaseStruct  base_pc(ph);
      while ( base_pc.Get(indx0++) )
      {
        base_pc.GetTypeKey(tkey);
        if ( !str_copy_pc.Get(tkey.GetKey()) )
        {
          protocol->Write(20,0,base_pc.GetScopedType());
          ERROR
        }
        if ( !str_copy_pc.CheckKeyField(protocol,prop_path,refr_accept,mult_accept,NO,NO) )
                                                    LEAVESEQ
      }
    }
  }
  else
  {
    pc_SDB_Property   prop_pc(prop_ph);

    protocol->SetErrorVariable(3,work_path,0);
    protocol->SetErrorVariable(4,prop_pc.GPH("sys_ident")->GetString(),0);

    if ( prop_pc.CheckKeyField(protocol) )
                                                    ERROR
    if ( prop_pc.IsA("SDB_Reference") )
    {
      if ( !refr_accept )
      {
        protocol->Write(148,0);
        ERROR
      }
      refr_accept = NO;
    }
    else if ( prop_pc.IsA("SDB_Relationship") )
    {
      protocol->Write(149,0);
      ERROR
    }
    if ( prop_pc.GPH("ddedim")->GetInt() != 1 && *prop_pc.GPH("reference_level") != "RL_generic" )
    {
      if ( !mult_accept )
      {
        protocol->Write(150,0);
        ERROR
      }
      mult_accept = NO;
    }
    
    if ( pkt )
    {
      prop_pc.GetTypeKey(tkey);

      pc_SDB_Structure   str_copy_pc(*this);
      if ( !str_copy_pc.Get(tkey.GetKey()) )
      {
        protocol->Write(20,0,prop_pc.GetScopedType());
        ERROR
      }
      if ( str_copy_pc.CheckKeyField(protocol,pkt+1,refr_accept,mult_accept,NO,YES) )
                                                     ERROR
    }
    LEAVESEQ
  }
  
  if ( err_opt )
    protocol->Write(21,0,GPH("sys_ident")->GetString(),work_path);
  ERROR

RECOVER
  term = YES;
ENDSEQ
  SDBEV1(savev1,UNDEF)
  SDBEV2(savev2,UNDEF)
  free(savev1);
  free(savev2);
  free(work_path);
  return(term);
}

/******************************************************************************/
/**
\brief  GetMember

\return prophdl
-------------------------------------------------------------------------------
\brief  i00


\param  protocol
\param  propnames
\param  recursiv
\param  err_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *pc_SDB_Structure :: GetMember (ErrorProtocol *protocol, char *propnames, logical recursiv, logical err_opt )
{
  PropertyHandle   *members = GPH("members");
  PropertyHandle    idkey_ph(propnames);
  TypeKey           tkey;
  TypeKey           my_tkey;
  char             *savev1  = NULL;
  int32             indx0   = 0;
  logical           term    = NO;
  PropertyHandle   *prophdl = NULL;
BEGINSEQ
  if ( members->Get(idkey_ph) )
  {
    if ( members->IsA("SDB_Attribute") &&
         (prophdl = GPH("smcepdde"))->Get(idkey_ph) )
                                                    LEAVESEQ
    if ( members->IsA("SDB_Reference") &&
         (prophdl = GPH("smcepref"))->Get(idkey_ph) )
                                                    LEAVESEQ
    if ( members->IsA("SDB_Relationship") &&
         (prophdl = GPH("smcershp"))->Get(idkey_ph) )
                                                    LEAVESEQ
    if ( members->IsA("SDB_BaseStruct") &&
         (prophdl = GPH("smcebase"))->Get(idkey_ph) )
                                                    LEAVESEQ
  }

  if ( !recursiv || (prophdl = GPH("smcebase"))->GetCount() <= 0 )
                                                    ERROR
  pc_SDB_BaseStruct  base_pc(prophdl);
  GetTypeKey(my_tkey);
  
  while ( base_pc.Get(indx0++) )
  {
    base_pc.GetTypeKey(tkey);
    if ( !Get(tkey.GetKey()) )
    {
      if ( err_opt )
      {
        if ( protocol )
        {
          savev1 = strdup(protocol->GetErrorVariable(1,""));
          protocol->Write(20,0,base_pc.GetScopedType());
          SDBEV1(savev1,UNDEF)
          free(savev1);
        }
        term = YES;
      }
    }
    else if ( prophdl = GetMember(protocol,propnames,recursiv,err_opt) )
    {
      SDBRESET
      LEAVESEQ
    }
    Get(my_tkey.GetKey());
    if ( term )                                     ERROR
  }
  
  ERROR
RECOVER
  prophdl = NULL;
ENDSEQ
  return(prophdl);
}

/******************************************************************************/
/**
\brief  i01


\param  propnames
\param  recursiv
\param  err_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *pc_SDB_Structure :: GetMember (char *propnames, logical recursiv, logical err_opt )
{

  return ( GetMember(NULL,propnames,recursiv,err_opt) );

}

/******************************************************************************/
/**
\brief  IsBasedOn

\return cond - 

\param  mkey
\param  tkey
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasedOn"

logical pc_SDB_Structure :: IsBasedOn (TypeKey mkey, TypeKey &tkey )
{
  int32                indx0 = 0;
  logical              cond  = YES;
BEGINSEQ
  if ( !Get(mkey.GetKey()) )                        ERROR

  if ( mkey == tkey )                               LEAVESEQ
  
  pc_SDB_Structure     str_pc(*this);
  pc_SDB_BaseStruct    base_str(str_pc.GPH("smcebase"));
  
  while ( base_str(indx0++) )
    if ( str_pc.IsBasedOn(base_str.GetTypeKey(mkey),tkey) )
                                                    LEAVESEQ
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsChecked

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsChecked"

logical pc_SDB_Structure :: IsChecked ( )
{

  return ( IsPositioned() && GPH("checked")->IsTrue() ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsKeyComponent

\return cond - 

\param  fldnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsKeyComponent"

logical pc_SDB_Structure :: IsKeyComponent (char *fldnames )
{

  return ( pc_SDB_Key(GPH("smcepsmc")).IsKeyComponent(fldnames) );

}

/******************************************************************************/
/**
\brief  SetChecked

\return term

\param  option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetChecked"

logical pc_SDB_Structure :: SetChecked (logical option )
{
  logical     term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  *GPH("checked") = option;
  
  if ( !option ) 
    *GPH("ready") = option;
    
  Save();                                           SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Store

\return term

\param  strdefptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_Structure :: Store (DBStructDef *strdefptr )
{
  logical     term = NO;
BEGINSEQ
  if ( NoWrite() )                                   ERROR
  
  *GPH("typetype")    = TYP_Structure;
  *GPH("itype")       = MAX(0,strdefptr->smcbityp);
  *GPH("access_type") = strdefptr->smcbatyp;
  *GPH("smcestyp")    = ST_USER;
  
  GPH("members")->DeleteSet();                       SDBCERR
  
  if ( pc_SDB_BaseStruct(GPH("smcebase")).StoreAll(strdefptr) )
    term = YES;
  if ( pc_SDB_Attribute(GPH("smcepdde")).StoreAll(strdefptr) )
    term = YES;
  if ( pc_SDB_Reference(GPH("smcepref")).StoreAll(strdefptr) )
    term = YES;
  if ( pc_SDB_Relationship(GPH("smcershp")).StoreAll(strdefptr) )
    term = YES;

  pc_SDB_Key  key_pc(GPH("smcepsmc"));
  if ( key_pc.StoreAll(strdefptr->smcbskey) ||
       key_pc.CheckAll(NULL)                   )
    term = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Structure

-------------------------------------------------------------------------------
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Structure"

     pc_SDB_Structure :: pc_SDB_Structure (PropertyHandle *prophdl )
                     : pc_SDB_NameSpace(prophdl)
{
}

/******************************************************************************/
/**
\brief  i01


\param  dbhandle - 
\param  accopt_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Structure"

     pc_SDB_Structure :: pc_SDB_Structure (DatabaseHandle &dbhandle, PIACC accopt_w )
                     : pc_SDB_NameSpace(dbhandle,"SDB_Structure",accopt_w)
{
}

/******************************************************************************/
/**
\brief  i02


\param  dbhandle - 
\param  strnames
\param  accopt_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Structure"

     pc_SDB_Structure :: pc_SDB_Structure (DatabaseHandle &dbhandle, char *strnames, PIACC accopt_w )
                     : pc_SDB_NameSpace(dbhandle,strnames,accopt_w)
{
}


