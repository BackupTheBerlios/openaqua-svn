/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    WSList



\date     $Date: 2006/04/26 19:40:54,42 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "WSList"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sDBIndexList.hpp>
#include  <sDictionary.hpp>
#include  <sEB_RBHeader.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sSDB_Workspace.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sWSList.hpp>


/******************************************************************************/
/**
\brief  Add

\return term - Termination code

\param  wsentry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical WSList :: Add (SDB_Workspace &wsentry )
{
  SDB_Workspace   *ws_entry;
  LDBHandle       *dbhandle;
  logical          extlock = stsclck();
  char             string[10];
  logical          term    = NO;
BEGINSEQ
   if ( Lock() )                                     ERROR
   
   dbhandle = ob_handle->GetDBHandle()->GetLocalDBHandle();
   wsentry.SetWSNumber(dbhandle->GetNextWSNumber());
   
   strcat(strcat(wsentry.get_location(),".WS"),gvtxltp(strcpy(string,"999999999"),wsentry.get_id(),9));
   if ( wsentry.Check(YES) )                         ERROR
   
   if ( AddExt(0,wsentry.get_name(),UNDEF) == AUTO ) ERROR
   refmod = YES;  
   
   ws_entry  = Get(wsentry.get_name());
   *ws_entry = wsentry;

   Save();
RECOVER
  term = YES;
ENDSEQ
  Unlock(extlock);
  return(term);
}

/******************************************************************************/
/**
\brief  Delete

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00


\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical WSList :: Delete (int32 lindx0 )
{
  logical    extlock = stsclck();
  logical    term    = NO;
BEGINSEQ
  if ( Lock() )                                     ERROR
  
  if ( mvlsrt->srtidl(lindx0+1) )                   ERROR


RECOVER
  term = YES;
ENDSEQ
  Unlock(extlock);
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  wsname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical WSList :: Delete (char *wsname )
{
  logical    extlock = stsclck();
  char       name[128];
  int32       lindx;
  logical    term    = NO;
BEGINSEQ
  if ( Lock() )                                      ERROR
  
  gvtxstb(name,wsname,sizeof(name));
  
  if ( !(lindx = mvlsrt->srtssr(name)) )             ERROR

  mvlsrt->srtidl(lindx);
  refmod = YES;  
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Exist

\return cond

\param  wsentry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical WSList :: Exist (SDB_Workspace &wsentry )
{
  SDB_Workspace          *wse;
  int32                    lindx0 = 0;
  logical                 cond = YES;
BEGINSEQ
  if ( (lindx0 = GetIndex(wsentry.get_name(),0,YES)) == AUTO )
                                                     ERROR
  wse = (SDB_Workspace *)mvlsrt->srtigt(lindx0+1);

  if ( *wse == wsentry )                             LEAVESEQ
 
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Get

\return wsentry
-------------------------------------------------------------------------------
\brief  i00


\param  wsentry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

SDB_Workspace *WSList :: Get (SDB_Workspace &wsentry )
{
  SDB_Workspace *ws_entry;
BEGINSEQ
  if ( ws_entry = Get(wsentry.get_name()) )
    if ( wsentry == *ws_entry )                      LEAVESEQ

  ERROR
RECOVER
  ws_entry = NULL;
ENDSEQ
  return(ws_entry);
}

/******************************************************************************/
/**
\brief  i01


\param  wsname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

SDB_Workspace *WSList :: Get (char *wsname )
{
  char         name[128];
  int32         lindx0;
  gvtxstb(name,wsname,sizeof(name));
  
  return( (lindx0 = mvlsrt->srtssr(name)) 
          ? Get(--lindx0)
          : (SDB_Workspace *)NULL          );

}

/******************************************************************************/
/**
\brief  i02


\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

SDB_Workspace *WSList :: Get (int32 lindx0 )
{

  return ( (SDB_Workspace *)mvlsrt->srtigt(lindx0+1) );


}

/******************************************************************************/
/**
\brief  Refresh

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical WSList :: Refresh ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( mvld::Refresh() )                             ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WSList

-------------------------------------------------------------------------------
\brief  i0


\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSList"

                        WSList :: WSList (DBHandle *dbhandle )
                     : mvld(
dbhandle->GetLocalDBHandle(),
&dbhandle->GetLocalDBHandle()->get_root_base()->
       IsODABARootBase()->get_rb_header()->
       get_work_spaces(),
UNDEF,
dbhandle->GetDictionary()->
       GetExtendDef("SDB_Workspace",0)->
       get_index_list()->GetHead(),
UNDEF,YES)
{

}

/******************************************************************************/
/**
\brief  i01


\param  rootbase - 
\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSList"

                        WSList :: WSList (db_RootBase *rootbase, DBHandle *dbhandle )
                     : mvld(
dbhandle->GetLocalDBHandle(),
&rootbase->IsODABARootBase()->get_rb_header()->get_work_spaces(),
UNDEF,
dbhandle->GetDictionary()->
       GetExtendDef("SDB_Workspace",0)->
       get_index_list()->GetHead(),
UNDEF,YES)
{
}

/******************************************************************************/
/**
\brief  ~WSList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~WSList"

                        WSList :: ~WSList ( )
{
}


