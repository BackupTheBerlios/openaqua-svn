/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_BaseStruct



\date     $Date: 2006/05/13 17:32:43,59 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_BaseStruct"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>
#include  <iopsi.h>
#include  <spc_SDB_BaseStruct.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
\param  ext_ph - PropertyHandle of type SDB_Extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_BaseStruct :: Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph )
{
  logical   term = NO;
BEGINSEQ
  protocol->SetErrorVariable(2,GPH("sys_ident")->GetString(),0);

  if ( GPH("ddeext")->IsEmpty() )
    SetProperty("ddeinv","",protocol,"required when no base extent");
  else 
    SetProperty("update","Y",protocol,"required when base extent");
    
  if ( pc_SDB_Relationship::Check(protocol,str_ph,cs_ph,ext_ph,YES) )
                                                     ERROR
  SetProperty("ddedim","1",protocol,"mandatory for base structures");
  if ( GPH("ddeindx")->GetCount() > 1 )
  {
    protocol->Write(196,0);
    ERROR
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

logical pc_SDB_BaseStruct :: CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph )
{
  int32     indx0 = 0;
  logical   term  = NO;
  while ( Get(indx0++) )
    if ( Check(protocol,str_ph,cs_ph,ext_ph) )
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

logical pc_SDB_BaseStruct :: Store (DBFieldDef *dbflddef )
{
  logical   term = NO;
BEGINSEQ
  if ( pc_SDB_Relationship::Store(dbflddef) )       ERROR

  *GPH("smcedom") = dbflddef->get_dominant();
  
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

logical pc_SDB_BaseStruct :: StoreAll (DBStructDef *strdefptr )
{
  DBFieldDef *dbflddef = NULL;
  int32       indx0    = 0;
  int32       count    = strdefptr->get_base_info().get_count();
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
\brief  pc_SDB_BaseStruct


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_BaseStruct"

     pc_SDB_BaseStruct :: pc_SDB_BaseStruct (PropertyHandle *prophdl )
                     : pc_SDB_Relationship(prophdl)
{
}


