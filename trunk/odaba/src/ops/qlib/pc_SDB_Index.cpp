/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Index



\date     $Date: 2006/05/14 13:14:15,01 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Index"

#include  <pops7.h>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sErrorProtocol.hpp>
#include  <iopsi.h>
#include  <spc_SDB_Index.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  protocol
\param  str_ph - PropertyHandle of type SDB_Structure
\param  tkey
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Index :: Check (ErrorProtocol *protocol, PropertyHandle *str_ph, TypeKey &tkey )
{
  PropertyHandle   *skdname = GPH("skdname");
  char              string[512];
  logical           term    = NO;
BEGINSEQ
  if ( !skdname->IsEmpty() )
  { 
    if ( !str_ph->Get(tkey.GetKey()) )
    {
      protocol->Write(140,0,NULL,NULL,tkey.ScopedName(GetDBHandle(),string,sizeof(string)));
      ERROR
    }

    if ( !str_ph->GPH("smcepsmc")->Get(*skdname) )
    {
      protocol->Write(189,0,NULL,NULL,tkey.ScopedName(GetDBHandle(),string,sizeof(string)),skdname->GetString());
      ERROR
    }
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
\param  tkey
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAll"

logical pc_SDB_Index :: CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, TypeKey &tkey )
{
  int32       indx0 = 0;
  logical     term  = NO;
  while ( Get(indx0++) )
    if ( Check(protocol,str_ph,tkey) )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  Store

\return term

\param  dbidxdef
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_Index :: Store (DBIndex *dbidxdef )
{
  char        empty[ID_SIZE];
  char       *keyname =   dbidxdef->get_key_def() 
                        ? dbidxdef->get_key_def()->scbsmcb->smcbname
                        : empty;
  logical     term    = NO;
BEGINSEQ
  memset(empty,' ',sizeof(empty));

  Add(Key(keyname));                                  SDBCERR
  
  *GPH("skdtype")        = dbidxdef->get_set_type();
  *GPH("skdunique")      = dbidxdef->get_unique();
  *GPH("case_sensitive") = dbidxdef->get_case_sensitive();

  *GPH("skdtemp")        = dbidxdef->get_temporary();
  *GPH("no_empty")       = dbidxdef->get_no_empty();
  *GPH("skdmax")         = dbidxdef->get_max_count();
  
  Save();                                             SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StoreAll

\return term

\param  indexlist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreAll"

logical pc_SDB_Index :: StoreAll (DBIndexList *indexlist )
{
  DBIndex    *dbidxdef = NULL;
  logical     term     = NO;
BEGINSEQ
  if ( !indexlist )                                 LEAVESEQ
  
  indexlist->GoTop();  
  while ( dbidxdef = indexlist->GetNext() )
    if ( Store(dbidxdef) )
      term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Index


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Index"

     pc_SDB_Index :: pc_SDB_Index (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{
}


