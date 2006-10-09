/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    OPAGlobals

\brief    


\date     $Date: 2006/03/12 19:17:59,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPAGlobals"

#include  <popa7.h>
#include  <cglobals.h>
#ifndef   DLL_RootBaseEntry_HPP
#define   DLL_RootBaseEntry_HPP
#include  <sRootBaseEntry.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sRessourceLock.hpp>
#include  <seb_RootBase.hpp>
#include  <snode.hpp>
#include  <stim.hpp>
#include  <sOPAGlobals.hpp>


/******************************************************************************/
/**
\brief  ILockGlobal - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILockGlobal"

logical OPAGlobals :: ILockGlobal ( )
{

  if ( !reslock )
    reslock = new RessourceLock(YES);

  return (reslock->ILock());

}

/******************************************************************************/
/**
\brief  IUnlockGlobal - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlockGlobal"

logical OPAGlobals :: IUnlockGlobal ( )
{

  return ( reslock ? reslock->IUnlock() : YES );

}

/******************************************************************************/
/**
\brief  OPAGlobals - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPAGlobals"

                        OPAGlobals :: OPAGlobals ( )
                     :   rootbase_list(NULL),
  reslock(NULL),
  active_transactions(0),
  paused(NO)
{



}

/******************************************************************************/
/**
\brief  ProvideRootBase - 


\return rootbase -

\param  database_id -
\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideRootBase"

db_RootBase *OPAGlobals :: ProvideRootBase (char *database_id, char *cpath )
{
  RootBaseEntry          *rb_entry;
  db_RootBase            *rootbase = NULL;
  if ( rootbase_list )
  {
    rootbase_list->GoTop();
    while ( !rootbase && (rb_entry = rootbase_list->GetNext()) )
#ifdef __unix__ 
      if ( !strcmp(rb_entry->get_database_path(),cpath) )
#else
      if ( !gvtsicmp(rb_entry->get_database_path(),cpath,UNDEF) )
#endif
//      && !memcmp(rb_entry->get_database_id(),database_id,10) )
        rootbase = rb_entry->get_root_base();
  }
  return(rootbase);
}

/******************************************************************************/
/**
\brief  RegisterRootBase - 



\param  rootbase -
\param  database_id -
\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterRootBase"

void OPAGlobals :: RegisterRootBase (db_RootBase *rootbase, char *database_id, char *cpath )
{

  if ( rootbase_list )
    rootbase_list->AddTail(new RootBaseEntry(database_id,rootbase,cpath));


}

/******************************************************************************/
/**
\brief  RegisterTA - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterTA"

logical OPAGlobals :: RegisterTA ( )
{
  int32          seconds = 10*60;
  logical       term    = NO;
BEGINSEQ
  while ( paused && seconds-- )
    TWAIT(10);
      
  if ( paused )                                      SDBERR(324)
  
  active_transactions++;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RootBaseShared - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RootBaseShared"

logical OPAGlobals :: RootBaseShared ( )
{

  return ( rootbase_list ? YES : NO );

}

/******************************************************************************/
/**
\brief  ShareRootBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShareRootBase"

void OPAGlobals :: ShareRootBase ( )
{

  rootbase_list = new DLL(RootBaseEntry)();

}

/******************************************************************************/
/**
\brief  StartPause - 


\return term - Termination code

\param  wait_sec -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartPause"

logical OPAGlobals :: StartPause (int32 wait_sec )
{
  int32          seconds = wait_sec > 0 ? wait_sec : 5*60;
BEGINSEQ
  paused = YES;  
  while ( active_transactions && seconds-- )
    TWAIT(10);  // wait 1 sec

  if( active_transactions )                          SDBERR(323)

RECOVER
  paused = NO;
ENDSEQ
  return(!paused);
}

/******************************************************************************/
/**
\brief  StopPause - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopPause"

void OPAGlobals :: StopPause ( )
{

  paused = NO;

}

/******************************************************************************/
/**
\brief  UnregisterRootBase - 



\param  rootbase -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterRootBase"

void OPAGlobals :: UnregisterRootBase (db_RootBase *rootbase )
{
  RootBaseEntry          *rb_entry;
BEGINSEQ
  if ( rootbase_list )
  {
    rootbase_list->GoTop();
    while ( rb_entry = rootbase_list->GetNext() )
      if ( rb_entry->get_root_base() == rootbase )
      {
        rootbase_list->RemoveAt();
        delete rb_entry;                          
        LEAVESEQ
      } 
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  UnregisterTA - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterTA"

void OPAGlobals :: UnregisterTA ( )
{

  if ( active_transactions > 0 )
    active_transactions--;

}

/******************************************************************************/
/**
\brief  ~OPAGlobals - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPAGlobals"

                        OPAGlobals :: ~OPAGlobals ( )
{
  int32        count;
  char        string[33];
  Error       err;
  if ( count = node::__TraceList(1) )
  {
    gvtxltoa(count,string,10);
    err.TraceMessage("Memory leak warning - Unclosed nodes: ",string);
  }
  if ( (count = QuList::__TraceList(1)) > 10 )
  {
    gvtxltoa(count,string,10);
    err.TraceMessage("Memory leak warning - Unclosed DLLs: ",string);
  }

  delete rootbase_list;
  rootbase_list = NULL;

}


