/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ObjectEntryList

\brief    


\date     $Date: 2006/08/29 13:39:57,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ObjectEntryList"

#include  <popa7.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <oel_coun.h>
#include  <sACObject.hpp>
#include  <sBinArray.hpp>
#include  <sBinArrayObjEntry.hpp>
#include  <sBinSArrayObjEntry.hpp>
#include  <sCSLHandleList.hpp>
#include  <sEvent.hpp>
#include  <sInstanceDescriptor.hpp>
#include  <sInstancePool.hpp>
#include  <sObjectEntry.hpp>
#include  <sStatistic.hpp>
#include  <sacb.hpp>
#include  <scfte.hpp>
#include  <sdb_RootBase.hpp>
#include  <seb_RootBase.hpp>
#include  <ifil.h>
#include  <stim.hpp>
#include  <sObjectEntryList.hpp>


/******************************************************************************/
/**
\brief  BuildIntermediate - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildIntermediate"

logical ObjectEntryList :: BuildIntermediate ( )
{
  logical                 term = NO;
  if ( !(intermediate = fopen(intermediate_path,"wb")) )
                                                     SDBSET(534)
  
  // hier müssen wir alle geänderten Entries (update_list) rausschreiben
  if ( intermediate )
    fclose(intermediate);
  intermediate = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  Flush - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical ObjectEntryList :: Flush ( )
{
  logical                 term = NO;
  if ( statistics )
    flush_stats.Start();

  if ( intermediate_path )
    BuildIntermediate();
    
  term = BinArray::Flush();

  if ( intermediate_path )
    RemoveIntermediate();
    
  if ( statistics )
  {
    flush_stats.Stop();
    total_stats += flush_stats;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  FreeObjEntry - 




\param  obj_entry - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeObjEntry"

void ObjectEntryList :: FreeObjEntry (BinSArrayObjEntry *obj_entry )
{

  BinArray::FreeObjEntry(obj_entry);
  ((ObjectEntry *)obj_entry)->Free(instance_pool);

}

/******************************************************************************/
/**
\brief  GetEntry - 



\return ob_entry - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

ObjectEntry *ObjectEntryList :: GetEntry (acb *acbptr )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();

  return((ObjectEntry *)BinArray::ProvideEntry(ebsnum.FromPIF(pif).get_ebsnum(),NO));


}

/******************************************************************************/
/**
\brief  GetInstance - 



\return term - Termination code

\param  object_entry - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

logical ObjectEntryList :: GetInstance (BinArrayObjEntry *object_entry )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  InitObjEntry - 




\param  obj_entry - 
\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitObjEntry"

void ObjectEntryList :: InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index )
{
  EB_Number           ebsnum(entry_index);
  acb                 acbenty(ebsnum.ToPIF(root_base->IsPIF()),0,CUR_VERSION);
  logical     term = NO;
BEGINSEQ
//  if ( statistics )
//    locate_stats.Start();
  
  ((ObjectEntry *)obj_entry)->stsrerr();;
  term = !root_base->getEBI(&acbenty);

  ((ObjectEntry *)obj_entry)->Free(instance_pool);
  BinArray::InitObjEntry(obj_entry,entry_index);

  ((ObjectEntry *)obj_entry)->Initialize(&acbenty);

  if ( term )                                        ERROR
    
//  if ( statistics )
//    locate_stats.Stop();

RECOVER
  ((ObjectEntry *)obj_entry)->stsserr();
ENDSEQ

}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical ObjectEntryList :: Lock (acb *acbptr, logical wait )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();

  return( BinArray::Lock(ebsnum.FromPIF(pif).get_ebsnum(),wait) );

}

/******************************************************************************/
/**
\brief  LockInternal - 



\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical ObjectEntryList :: LockInternal (acb *acbptr, logical wait )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();

  return( BinArray::LockInternal(ebsnum.FromPIF(pif).get_ebsnum(),wait) );

}

/******************************************************************************/
/**
\brief  ObjectEntryList - 




\param  erootbase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectEntryList"

     ObjectEntryList :: ObjectEntryList (eb_RootBase *erootbase )
                     : BinArray (sizeof(ObjectEntry),4096,12,YES),
  root_base(erootbase),
  statistics(NO),
  flush_interval(0),
  flush_stop(YES),
  release_quote(25),
  release_size(0),
  instance_pool(NULL),
  intermediate(NULL),
  intermediate_path(NULL),
  total_stats(),
  provide_stats(),
  locate_stats(),
  write_stats(),
  flush_stats()
{
  int32           mb_size = 0;
  char          *varstring;
  statistics = (varstring = GetSectionVariable("STATISTICS","CACHE")) &&
               !strcmp(varstring,"YES");

  if ( (varstring = GetSectionVariable("SIZE","CACHE")) && *varstring )
  {
    mb_size = atol(varstring);
    if ( mb_size > 0 )
    {
      auto_reorg = NO;
      release_quote = 25;
      if ( (varstring = GetSectionVariable("RELEASE","CACHE")) && *varstring )
      {
        release_quote = atol(varstring);
        if ( release_quote < 0 || release_quote > 100 )
        {
          SDBEV1(varstring,UNDEF)
          SDBSET(535)
          release_quote = 25;
        }
      }
      instance_pool = new InstancePool(this,mb_size*1024*1024);
      release_size = (mb_size*release_quote/100)*1024*1024;
    }
  }
  
  if ( (varstring = GetSectionVariable("CHECK","CACHE")) && *varstring )
  {
    flush_interval = atol(varstring);
    if ( flush_interval < 0 )
      flush_interval = 0;
    if ( flush_interval )
      StartFlushThread();
  }
  
  if ( (varstring = GetSectionVariable("INTERMEDIATE","CACHE")) && *varstring )
  {
    SDBEV1(varstring,UNDEF)
    intermediate_path = strdup(varstring);
    StoreIntermediate();
  }


}

/******************************************************************************/
/**
\brief  ProvideEntry - 



\return inst_descriptor - 

\param  acbptr - 
\param  create - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEntry"

InstanceDescriptor *ObjectEntryList :: ProvideEntry (acb *acbptr, logical create )
{
  ObjectEntry        *ob_entry;
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();
  InstanceDescriptor *inst_desc = NULL;
BEGINSEQ
  if ( statistics )
    provide_stats.Start();
  
  ILock();
  if ( !(ob_entry = (ObjectEntry *)BinArray::ProvideEntryIntern(ebsnum.FromPIF(pif).get_ebsnum(),create)) )
                                                     ERROR
  if ( ob_entry->stscerr() )                       
    InitObjEntry(ob_entry,acbptr->get_ebsnum().get_ebsnum());
  if ( ob_entry->stscerr() )                         ERROR
  
  if ( WaitForEntry(ob_entry) )                      ERROR
    
  inst_desc = ob_entry;
  if ( acbptr->get_version_number() < inst_desc->get_ebi().get_version() )
    if ( !(inst_desc = inst_desc->GetOldInstance(root_base,acbptr)) )
                                                     ERROR
  *(EBI *)acbptr = inst_desc->get_ebi();
//  acbptr->CheckError();  // nur zum Test. muss dann wieder raus!!
  acbptr->set_cluster_numb(inst_desc->get_cluster_number());
  
  if ( statistics )
    provide_stats.Stop();

RECOVER
  inst_desc = NULL;
ENDSEQ
  IUnlock();
  return(inst_desc);
}

/******************************************************************************/
/**
\brief  RelObjEntry - 




\param  obj_entry - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RelObjEntry"

void ObjectEntryList :: RelObjEntry (BinSArrayObjEntry *obj_entry )
{

  BinArray::RelObjEntry(obj_entry);
  ((ObjectEntry *)obj_entry)->ReleaseLocked(instance_pool);

}

/******************************************************************************/
/**
\brief  ReleaseEntry - 




\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

void ObjectEntryList :: ReleaseEntry (acb *acbptr )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();
  ObjectEntry        *ob_entry = NULL;

  ILock();
  
  if ( ob_entry = (ObjectEntry *)BinArray::ProvideEntryIntern(ebsnum.FromPIF(pif).get_ebsnum(),NO) )
    if ( !WaitForEntry(ob_entry) ) // vielleicht müssen wir noch den use_count mit abfragen (!=0) 5.2.2003      
    {
      if ( !acbptr->set_reserved(NO) )
        ob_entry->Release(&acbptr->get_active_handles());
      
      if ( ob_entry->BinArrayObjEntry::Release(last_used) )
      {
        RegUnusedEntry(ob_entry);
if ( ob_entry->get_active_handles().get_handle_lists()->GetCount() > 0 )
ob_entry->get_active_handles().get_handle_lists()->Clear();
      }
    }   
  IUnlock();


}

/******************************************************************************/
/**
\brief  RemoveIntermediate - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveIntermediate"

logical ObjectEntryList :: RemoveIntermediate ( )
{
  logical                 term = NO;
  remove(intermediate_path);
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveEntry - 



\return ob_entry - 

\param  acbptr - 
\param  upd_ebi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

ObjectEntry *ObjectEntryList :: ReserveEntry (acb *acbptr, logical upd_ebi )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();
  ObjectEntry        *ob_entry;
  ILock();
  if ( ob_entry = (ObjectEntry *)BinArray::ReserveEntry(ebsnum.FromPIF(pif).get_ebsnum(),NO) )
  {
    if ( acbptr->set_reserved(YES) == 1 )
      ob_entry->Reserve(&acbptr->get_active_handles());

if ( ob_entry->get_use_count() <= 0 )
if ( ob_entry->get_active_handles().get_handle_lists()->GetCount() > 0 )
ob_entry->get_active_handles().get_handle_lists()->Clear();
    
    if ( upd_ebi && acbptr->get_mod_count() != ob_entry->get_ebi().get_mod_count() )
    {
      *(EBI *)acbptr = ob_entry->get_ebi();
      acbptr->set_cluster_numb(ob_entry->get_cluster_number());
    }
  }

  IUnlock();
  return(ob_entry);
}

/******************************************************************************/
/**
\brief  SetupEntry - 



\return inst_descriptor - 

\param  acbptr - 
\param  inst_descr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupEntry"

InstanceDescriptor *ObjectEntryList :: SetupEntry (acb *acbptr, InstanceDescriptor *inst_descr )
{
  ObjectEntry        *ob_entry;
  ieh                *iehptr;
  if ( !inst_descr )
    inst_descr = ProvideEntry(acbptr,YES);

  inst_descr->get_ebi() = *(EBI *)acbptr;
  
  if ( instance_pool && (acbptr->get_mb_number() || acbptr->get_mb_ebsnum().get_ebsnum() > 1) )
    inst_descr->SetArea(instance_pool->CreateInstance(&acbptr->get_acbieh(),
                                                      inst_descr->get_ext_inst(),
                                                      !inst_descr->get_ebi().HasData()));
  return(inst_descr);
}

/******************************************************************************/
/**
\brief  StartFlushThread - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartFlushThread"

logical ObjectEntryList :: StartFlushThread ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
//  static cfte  cftenty("Watch",ALINK(this,ObjectEntryList,Watch));
  cfte  cftenty("Watch",ALINK(this,ObjectEntryList,Watch));
  
  cftenty.LINKINST(this);
  int i = cftenty.ThreadCall();
  if ( i == -1 )                 SDBERR(536)

  flush_stop = NO;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StopFlushThread - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopFlushThread"

logical ObjectEntryList :: StopFlushThread ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  if ( !flush_stop )
  {
    term_event.Reset();
    flush_stop = YES;
    term_event.WaitForSet(AUTO);
  }
  TWAIT(2);    


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StoreIntermediate - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreIntermediate"

logical ObjectEntryList :: StoreIntermediate ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !IsFile(intermediate_path) )                  ERROR

  if ( !(intermediate = fopen(intermediate_path,"wb")) )
                                                     SDBSET(534)

  // hier müssen wir alle Entries aus der intermediate-Datei lesen und in die Datenbank schreiben (EBI-Ebene)
RECOVER
  term = YES;
ENDSEQ
  if ( intermediate )
    fclose(intermediate);
  intermediate = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  StoreObjEntry - 




\param  array - 
\param  obj_entry - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreObjEntry"

void ObjectEntryList :: StoreObjEntry (BinArray *array, BinSArrayObjEntry *obj_entry )
{
  ObjectEntry         *objentry = (ObjectEntry *)obj_entry;
  EB_Number            entnr;
  if ( objentry )
  {
    entnr = objentry->get_object_id();
    instance_pool->StoreInstance(entnr,(EBI *)objentry,objentry->get_ext_inst(),objentry->get_cluster_number().get_ebsnum());
    BinArray::StoreObjEntry(array,obj_entry);
  }

}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical ObjectEntryList :: Unlock (acb *acbptr )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();

  return( BinArray::Unlock(ebsnum.FromPIF(pif).get_ebsnum()) );

}

/******************************************************************************/
/**
\brief  UnlockInternal - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical ObjectEntryList :: UnlockInternal (acb *acbptr )
{
  EB_Number           ebsnum = acbptr->get_ebsnum();
  logical             pif = root_base->IsPIF();

  return( BinArray::UnlockInternal(ebsnum.FromPIF(pif).get_ebsnum()) );


}

/******************************************************************************/
/**
\brief  Watch - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Watch"

logical ObjectEntryList :: Watch ( )
{
  int                     i;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  while ( !flush_stop )
  {
    i = flush_interval;
    while ( i-- && !flush_stop )
      TWAIT(10);   // one second
    
    Flush();
  }
  TWAIT(1); // wir warten ein bisschen, damit ShutDown das Wait einleiten kann!!
  term_event.Set();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ObjectEntryList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ObjectEntryList"

     ObjectEntryList :: ~ObjectEntryList ( )
{

  if ( flush_interval )
    StopFlushThread();
    
  if ( statistics )
  {
    provide_stats.Print("ProvideEntry",YES); // print with headline
    locate_stats.Print("LocateEntry",NO); 
    flush_stats.Print("Flush",NO); 
    total_stats.Print("Total",NO); 
  }

  Clear();
  
  delete intermediate_path;
  intermediate_path = NULL;

  delete instance_pool;
  instance_pool = NULL;

}


