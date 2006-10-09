/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Attribute



\date     $Date: 2006/05/11 15:52:17,90 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Attribute"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sPropertyHandle.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Attribute.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  cs_ph - PropertyHandle of type SDB_ValueList
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Attribute :: Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph )
{
  logical     term = NO;
BEGINSEQ
  protocol->SetErrorVariable(2,GPH("sys_ident")->GetString(),0);

  term = CheckType(protocol,str_ph,cs_ph);

  if ( !GPH("ddesize")->GetInt() && 
       GetDictionary().IsBasicType(GPH("ddetype")->GetString()) )
  {
    protocol->Write(650,0);
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
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAll"

logical pc_SDB_Attribute :: CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph )
{
  logical     term  = NO;
  int32       indx0 = 0;
  while ( Get(indx0++) )
    if ( Check(protocol,str_ph,cs_ph) )
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

logical pc_SDB_Attribute :: Store (DBFieldDef *dbflddef )
{
  logical     term = NO;
BEGINSEQ
  if ( pc_SDB_Property::Store(dbflddef) )           ERROR
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

logical pc_SDB_Attribute :: StoreAll (DBStructDef *strdefptr )
{
  DBFieldDef *dbflddef = NULL;
  int32       indx0    = strdefptr->get_base_info().get_count();
  int32       count    = indx0 + strdefptr->get_attr_info().get_count();
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
\brief  pc_SDB_Attribute


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Attribute"

     pc_SDB_Attribute :: pc_SDB_Attribute (PropertyHandle *prophdl )
                     : pc_SDB_Property(prophdl)
{
}


