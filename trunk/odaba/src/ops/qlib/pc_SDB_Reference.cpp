/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Reference



\date     $Date: 2006/05/11 15:49:58,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Reference"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Index.hpp>
#include  <spc_SDB_Reference.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
\param  base_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Reference :: Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, logical base_opt )
{
  PropertyHandle   *ddetype  = GPH("ddetype");
  PropertyHandle   *ddegent  = GPH("ddegent");
  TypeKey           tkey;
  logical           term     = NO;
  protocol->SetErrorVariable(2,GPH("sys_ident")->GetString(),0);

  SetProperty("reference_level","RL_direct",protocol,"auto-correkt for generation!");

  if ( !CheckType(protocol,str_ph,cs_ph) )
    GetTypeKey(tkey);
  else
    term = YES;
    
  if ( *ddegent == "PI" )
  {
    SetProperty("ddeatyp","AT_ODABA",protocol,"required for generic type PI");
    if ( *ddetype == "MEMO" )
      SetProperty("ddedim","1",protocol,"required for type MEMO");
  }
  
  pc_SDB_Index   index_pc(GPH("ddeindx"));
  if ( index_pc.GetCount() > 1 )
    SetProperty("multikey","Y",protocol,"required for more than one index");
    
  if ( !tkey.IsEmpty() )
    if ( index_pc.CheckAll(protocol,str_ph,tkey) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckAll

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAll"

logical pc_SDB_Reference :: CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph )
{
  int         indx0 = 0;
  logical     term  = NO;
  while ( Get(indx0++) )
    if ( Check(protocol,str_ph,cs_ph,NO) )
      term = YES;
  return(term);
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

logical pc_SDB_Reference :: Store (DBFieldDef *dbflddef )
{
  logical   term = NO;
BEGINSEQ
  if ( pc_SDB_Property::Store(dbflddef) )           ERROR
  
  *GPH("owning")     = dbflddef->get_owning();
  *GPH("create")     = dbflddef->get_create();
  *GPH("clustered")  = dbflddef->get_cluster_opt();
  *GPH("mb_number")  = dbflddef->get_mb_number();
  *GPH("week_typed") = dbflddef->get_weak_typed();
  *GPH("update")     = dbflddef->get_update();
  *GPH("multikey")   = dbflddef->get_multikey();
  *GPH("ddeatyp")    = *GPH("ddegent") == "PI" ? AT_ODABA : AT_NONE;

  if ( pc_SDB_Index(GPH("ddeindx")).StoreAll(dbflddef->get_index_list()) )
    term = YES;

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

logical pc_SDB_Reference :: StoreAll (DBStructDef *strdefptr )
{
  DBFieldDef *dbflddef = NULL;
  int32       indx0    = strdefptr->get_base_info().get_count() +
                         strdefptr->get_attr_info().get_count();
  int32       count    = indx0 + strdefptr->get_refr_info().get_count();
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
\brief  pc_SDB_Reference


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Reference"

     pc_SDB_Reference :: pc_SDB_Reference (PropertyHandle *prophdl )
                     : pc_SDB_Property(prophdl)
{
}


