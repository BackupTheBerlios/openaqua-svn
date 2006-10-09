/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TProjectManager

\brief    


\date     $Date: 2006/08/22 12:10:42,09 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TProjectManager"

#include  <poadi.h>
#include  <cprjman.h>
#ifndef   GSRT_TAction_HPP
#define   GSRT_TAction_HPP
#include  <sTAction.hpp>
#include  <sGSRT.h>
#endif
#include  <sDAction.hpp>
#include  <sOApplicationO.hpp>
#include  <sOCBitmap.hpp>
#include  <sODControl.hpp>
#include  <sODSItem.hpp>
#include  <sODesktop.hpp>
#include  <sOGUIErrorHandle.hpp>
#include  <sOProject.hpp>
#include  <sOResource.hpp>
#include  <sOSplash.hpp>
#include  <sResourceCache.hpp>
#include  <sTProjectManager.hpp>
#include  <ifil.h>
#include  <sTProjectManager.hpp>

TProjectManager        * TProjectManager::TPM = NULL;

/******************************************************************************/
/**
\brief  Beep - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Beep"

void TProjectManager :: Beep ( )
{

  app->beep();

}

/******************************************************************************/
/**
\brief  Cache - 



\return resource_cache - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cache"

ResourceCache *TProjectManager :: Cache ( )
{

  if ( !cache )
    cache = new ResourceCache(&UCB()->sdbures->dbhandle,1);
  return(cache);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cache"

ResourceCache *TProjectManager :: Cache (PropertyHandle *ph )
{
  ResourceCache     *rc = NULL;
  DBObjectHandle     obh = ph->GetObjectHandle();
  if ( obh == UCB()->sdbures->dbhandle )
    rc = Cache();
  else
  {
    if ( !design_cache )
      design_cache = new ResourceCache(new DBObjectHandle(obh),2);
    
    if ( obh == *design_cache->get_res_db() )
      rc = design_cache;
  }


  return(rc);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  cache_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cache"

ResourceCache *TProjectManager :: Cache (int8 cache_id )
{

  return(cache_id == 1 ? cache : cache_id == 2 ? design_cache : NULL);


}

/******************************************************************************/
/**
\brief  Create - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  hInstance - 
\param  hPrevInstance - 
\param  lpCmdLine - 
\param  nCmdShow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical TProjectManager :: Create (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
  static int               argc = 0;
  static QVector<char *>   argv = QVector<char *>(8);
  logical           term = NO;
#ifdef __unix__
  // Call Create(int,char**)
#else
  qWinMain(hInstance,hPrevInstance,qstrdup(lpCmdLine),nCmdShow,
           argc,argv);
#endif       
  app = new OApplicationO(argc,argv.data(),YES);
//  app->installEventFilter(b);

  InitStandardActionTable();

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  argc - 
\param  argv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical TProjectManager :: Create (int argc, char **argv )
{
  logical term          = NO;
BEGINSEQ
  app = new OApplicationO(argc,argv,YES);
  if(!app)                                           ERROR
  InitStandardActionTable();

RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  CreateErrHandle - 




\param  obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateErrHandle"

void TProjectManager :: CreateErrHandle (DBObjectHandle &obhandle )
{
  CTX_Base           *context = NULL;
  ErrorHandle        *hdl     = NULL;
  if ( !errhdl )
    errhdl = new OGUIErrorHandle(obhandle);
    
  SetErrHandle();


}

/******************************************************************************/
/**
\brief  CreateProjectFromCmdLine - 



\return term - 

\param  pODesktop - 
\param  iCount - 
\param  ppArguments - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProjectFromCmdLine"

OProject *TProjectManager :: CreateProjectFromCmdLine (ODesktop *pODesktop, int iCount, char **ppArguments )
{
  OProject        *res     = NULL;
  char            *inipath = NULL; 
  char            *exename = NULL;
  char             applname[256];
  char             ext[16];
  std::vector<std::string>::iterator it;

BEGINSEQ
// Create ucb for project
// ucb is a combination from binary name and ini file
// if a second parameter is available it is assumed that
// this is the name of the binary
  exename = ppArguments[0];
  if ( iCount > 1 ) 
    inipath = ppArguments[1];
    
  if( iCount > 2 )
    exename = ppArguments[2];

  GetFileNameInfo(exename,applname,ext,sizeof(applname)-1,sizeof(ext)-1);
  if ( !*applname )
    strcpy(applname,"ODABA Application");
    
  ucb = new UtilityHandle(ODABAClient(),applname,inipath,"",exename,APT_Windows);
  if ( ucb->InitFromParms(iCount,ppArguments) )           ERROR

  if ( !(res = CreateProjectFromUtilityHandle(pODesktop,ucb)) )
                                                     ERROR

RECOVER
  res = NULL;
ENDSEQ
  return(res);
}

/******************************************************************************/
/**
\brief  CreateProjectFromUtilityHandle - 



\return term - 

\param  pODesktop - 
\param  pUtilityHandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProjectFromUtilityHandle"

OProject *TProjectManager :: CreateProjectFromUtilityHandle (ODesktop *pODesktop, UtilityHandle *pUtilityHandle )
{
  OProject          *res   = NULL;
  DataSourceHandle  *sysDB = NULL;
  DataSourceHandle  *resDB = NULL;
  char              *project;
  char               splash_png[256];
  std_string         application_icon;
  logical            system = NO;
BEGINSEQ
  if ( project = GetSysVariable("PROJECT") )
  {
    strcat(strcpy(splash_png,project),".png");
    splash = new OSplash(splash_png);
    splash->Message("starting up");
    application_icon = std_string(project) + ".xpm";
    app->setWindowIcon(QIcon(QString(application_icon.c_str())));
  }
  
  if ( TestSysVariable("SYSAPPL","YES") )
    system = YES;
  if ( !(sysDB = pUtilityHandle->OpenSYS()) )         ERROR
  CreateErrHandle(sysDB->object_handle);
  if ( splash )
    splash->Message("Open database ... ");  
  if ( !(resDB = pUtilityHandle->OpenRES()) )         ERROR
  SystemServices()->RegisterError(&P_Error(),&resDB->object_handle);
  SystemServices()->RegisterError(&CTXError(),&resDB->object_handle);
  SystemServices()->RegisterError(&OADIError(),system ? &resDB->object_handle : &sysDB->object_handle);
    
  
// open ODABA2_ini
{
/* *fixme*

  PropertyHandle ini_pi(resDB->object_handle,"ODABA2_ini",PI_Read); 
                                                     OADISDBCERR
  ini_pi(0L);
  
  long s_version;

// version
  {
    s_version = ini_pi.GetInt( "odaba2_version" );
    if( s_version > resDB->object_handle.GetVersion() ) 
    {
      s_version = resDB->object_handle.GetVersion();
      if ( resDB->object_handle.GetAccess() == PI_Write )
      {
        PropertyHandle    ini_wpi(resDB->object_handle,"ODABA2_ini",PI_Write); 
        ini_pi(0L);
        *ini_pi.GetPropertyHandle("odaba2_version") = s_version;
      }
    } 
   
    if ( s_version > 0 &&
         !TestSysVariable("ODABA2","TEST") &&
         !ini_pi.GetPropertyHandle("odaba2_productio")->IsTrue() )
      s_version--;
    

    resDB->object_handle.SetVersion((ushort)s_version);

    pUtilityHandle->sdbudat->schema_version = (ushort)s_version;
*/    
//  24.11.2004 erst in TProject::DoCreated nach create project context    
//    if ( !pUtilityHandle->OpenDAT(TestSysVariable("NOWRITE","YES") ? PI_Read : PI_Write,
//                        pUtilityHandle->sdbudat->netopt,system) )
//                                                       ERROR
  }                                                     


  SetSysVariable("ResDB",pUtilityHandle->sdbures->db_path);  

// ADK_WinAction
  splash->Message("Read Project: " + SZ2QS(GetSysVariable("PROJECT")));
  SetupStandardActions();
  res = Cache()->ReadProject(GetSysVariable("PROJECT"));


RECOVER
  if ( resDB ) 
    resDB->Close();
  res = NULL;
ENDSEQ
  return res;
}

/******************************************************************************/
/**
\brief  Desktop - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Desktop"

ODesktop *TProjectManager :: Desktop ( ) const
{

  return desktop;

}

/******************************************************************************/
/**
\brief  GetResource - 



\return resource - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResource"

OResource *TProjectManager :: GetResource (int id )
{
  OResource    *pOResource;
  pOResource = Cache()->ProvideEntry(id);

  return(pOResource);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResource"

OResource *TProjectManager :: GetResource (PropertyHandle *ph, char *name )
{
  OResource    *pOResource;
  pOResource = Cache(ph)->ProvideEntry(ph,name);

  return(pOResource);
}

/******************************************************************************/
/**
\brief  InitStandardActionTable - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitStandardActionTable"

void TProjectManager :: InitStandardActionTable ( )
{

  static TAction acttbl[] = 
  { 
      TAction("DoAfterHandleActivated",NULL),
      TAction("DoBeforeOpen",NULL),
      TAction("DoAfterOpen",NULL),
      TAction("DoAfterHandleOpen",NULL),
      TAction("DoBeforeClose",NULL),
      TAction("DoAfterShow",NULL),
      TAction("DoAfterHide",NULL),
      TAction("DoAfterEnter",NULL),
      TAction("DoBeforeLeave",NULL),
      TAction("DoBeforeSelect",NULL),
      TAction("DoAfterSelect",NULL),
      TAction("DoAfterKeyInput",NULL),
      TAction("DoBeforeDrag",NULL),
      TAction("DoAfterDrag",NULL),
      TAction("DoBeforeDrop",NULL),
      TAction("DoAfterDrop",NULL),
      TAction("DoAfterClearData",NULL),
      TAction("DoBeforeDeleteData",NULL),
      TAction("DoAfterDeleteData",NULL),
      TAction("DoBeforeFillData",NULL),
      TAction("DoAfterFillData",NULL),
      TAction("DoBeforeDataSet",NULL),
      TAction("DoAfterDataSet",NULL),
      TAction("DoBeforeInsertData",NULL),
      TAction("DoAfterInsertData",NULL),
      TAction("DoBeforeStoreData",NULL),
      TAction("DoAfterStoreData",NULL),
      TAction("DoBeforeSaveData",NULL),
      TAction("DoAfterSaveData",NULL),
      TAction("DoAfterMouseMove",NULL),
      TAction("DoAfterMouseClick",NULL),
      TAction("DoAfterMouseDoubleClick",NULL),
      TAction("DoValidateData",NULL),
      TAction("DoAfterDock",NULL),
      TAction("DoAfterUndock",NULL),
  
      TAction("DoAfterUpdateCollection",NULL),
      TAction("DoAfterUpdateInstance",NULL),
      TAction("DoAfterChangeSelection",NULL),
  
      TAction("EditEntry",NULL),  // nd: 20.2.2004 sollte irgendwann virtell in CTX_GUIBase werden
      TAction("InsertEntry",NULL),
      TAction("AppendEntry",NULL),
      TAction("CopyEntry",NULL),
      TAction("DeleteEntry",NULL),
      TAction("RemoveEntry",NULL),
      TAction("RenameEntry",NULL),
      TAction("DeleteSet",NULL),
      TAction("Associate",NULL),
      TAction("FindEntry",NULL),
      TAction("NewFindEntry",NULL),
      TAction("StoreEntry",NULL),
      TAction("UpdateEntries",NULL),
      TAction("MoveUp",NULL),
      TAction("MoveDown",NULL),
      TAction("ForceClose",NULL), // rk: darf nur als Standard-Aktion implementiert werden
      TAction("ValidateData",NULL),
      TAction("ZoomOut",NULL),
      TAction("ZoomIn",NULL),
      TAction("Refresh",NULL),
      TAction("ImportFile",NULL),
      TAction("BrowseWriteFiles",NULL),
      TAction("BrowseFiles",NULL),
      TAction("SetSelection",NULL),
      TAction("ResetSelection",NULL),
      TAction("SetCascadingSelection",NULL),
      TAction("ResetCascadingSelection",NULL),

      TAction("BookmarkStore",NULL),
      TAction("BookmarkRemove",NULL),
      TAction("BookmarkNext",NULL),
      TAction("BookmarkPrevious",NULL),
      
      TAction("CSVExport",NULL),
      TAction("LoadDynamicControl",NULL),
  };

  std_actions = new GSRT(TAction)(sizeof(acttbl)/sizeof(TAction),sizeof(TAction),
                                  UNDEF,UNDEF,UNDEF,acttbl,NO);
  std_actions->srtsor(1,TACTION_KEYLEN,'C');


}

/******************************************************************************/
/**
\brief  InvalidateCache - 



\return term - 

\param  cache_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InvalidateCache"

logical TProjectManager :: InvalidateCache (int8 cache_id )
{
  logical                 term = NO;
BEGINSEQ
  if ( !Cache(cache_id) )                            ERROR

  Cache(cache_id)->Invalidate();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenDAT - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDAT"

logical TProjectManager :: OpenDAT ( )
{
  logical   term   = NO;
BEGINSEQ
  if ( ucb->sdbudat->object_handle.IsValid() )       LEAVESEQ
    
  if ( !ucb->OpenDAT(TestSysVariable("NOWRITE","YES") ? PI_Read : PI_Write,
                     ucb->sdbudat->netopt,
                     TestSysVariable("SYSAPPL","YES")) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenProject - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenProject"

logical TProjectManager :: OpenProject ( )
{
  TControl      *tc;
  TProject      *tprj;
  OProject      *oprj;
  OApplication  *oappl;
  char          *def_app;
  logical        term = NO;
BEGINSEQ
  desktop = new ODesktop();
  tc = desktop->Open();
  if ( !(oprj = CreateProjectFromCmdLine(desktop,app->ArgumentCount(),app->get_argv())) )
                                                     OADIERR(99)
  splash->Message("Open Project");

/*
_CrtMemState checkPt1;
 // Send all reports to STDOUT, since this example is a console app
_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

 // Set the debug heap to report memory leaks when the process terminates,
 // and to keep freed blocks in the linked list.
 SET_CRT_DEBUG_FIELD( _CRTDBG_LEAK_CHECK_DF | _CRTDBG_DELAY_FREE_MEM_DF );
*/
  if ( !(tc = oprj->Open(tc,YES)) )                  OADIERR(99)
/*
_CrtMemDumpAllObjectsSince( &checkPt1 );
_CrtMemCheckpoint( &checkPt1 );
_CrtMemDumpStatistics( &checkPt1 );
_CrtCheckMemory( );
*/
  if ( !(tprj = OI_CAST(TProject,tc)) )              OADIERR(99)
  tprj->SetMainWindow();
  splash->Wait(tprj->get_complexWidget()->WidgetQ());
  projects.AddTail(tprj);

  splash->Message("Sub Applications");
  if ( def_app = GetSysVariable("APPLICATION") )
    if ( oappl = oprj->SubApplicationByName(def_app) )
      oappl->Open(NULL,tc,YES);
RECOVER
  term = YES;
ENDSEQ
  delete splash;splash = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseDictPH - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDictPH"

void TProjectManager :: ReleaseDictPH ( )
{

  dict_pi_reserved = UNDEF;


}

/******************************************************************************/
/**
\brief  ReserveDictPH - 



\return dict_ph - 

\param  res_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveDictPH"

PropertyHandle *TProjectManager :: ReserveDictPH (int32 res_id )
{
  PropertyHandle          *dict_ph = &dict_pi;
BEGINSEQ
  if ( dict_pi_reserved == res_id )                  LEAVESEQ
  if ( dict_pi_reserved )                            
                                                     OADIERR(99)
  if ( !dict_pi.IsValid() )
    dict_pi.Open(UCB()->sdbures->dbhandle,"VOID",PI_Read);

  if ( !dict_pi.Get(res_id) )                        ERROR
    
  dict_pi_reserved = res_id;
RECOVER
  dict_ph = NULL;
ENDSEQ
  return(dict_ph);
}

/******************************************************************************/
/**
\brief  Run - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Run"

logical TProjectManager :: Run ( )
{
  logical        term = NO;
BEGINSEQ
  if ( OpenProject() )                               ERROR   

  app->exec();

  delete cache;
  cache = NULL;
  delete design_cache;
  design_cache = NULL;
  
//  ucb->sdbudat->Close();
//  ucb->sdbures->Close();
//  ucb->sdbusys->Close();
  ucb->CloseSYS();             // schliesst alle anderen implizit
  ucb->connection.ShutDown();
  delete ucb; 
  ucb = NULL;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetErrHandle - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrHandle"

logical TProjectManager :: SetErrHandle ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || !errhdl )                               ERROR
    
  P_Error().SetHandle(errhdl);
  OADIError().SetHandle(errhdl);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetErrorObject - 




\param  obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrorObject"

void TProjectManager :: SetErrorObject (DBObjectHandle &obhandle )
{

  if ( this ) 
    errhdl->SetErrorObject(obhandle);


}

/******************************************************************************/
/**
\brief  SetMainWindow - 



\return term - 

\param  pOProject - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMainWindow"

logical TProjectManager :: SetMainWindow (OProject *pOProject )
{
  TProject      *tproj;
  logical        term = NO;
BEGINSEQ
  if ( !pOProject )                                  LEAVESEQ

  projects.GoTop();
  while ( tproj = projects.GetNext() )
    if ( tproj->get_project() == pOProject )
    {
      tproj->SetMainWindow();
      LEAVESEQ
    }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupStandardActions - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupStandardActions"

void TProjectManager :: SetupStandardActions ( )
{
  TAction                *taction;
  DAction                *dact;
  OEventActionControl    *oact;
  int32                   indx = 0;  

  while ( taction = std_actions->GetEntry(++indx) )
  {
    if ( oact = Cache()->ReadEventActionControl(taction->get_sys_ident()) )
    {
      dact = new DAction(taction->get_sys_ident());
      dact->Initialize(taction->get_sys_ident(),
                       !oact->get_autoOpen(),
                       oact->get_textDefinitions().get_title(), 
                       oact->get_textDefinitions().get_tooltip(),
                       oact->get_textDefinitions().get_long_text(),
                       oact->get_key_string(),
                       oact->get_bitmap()->GetInactiveBitmap(),
                       oact->get_bitmap()->GetActiveBitmap(),
                       oact->get_bitmap()->GetDisabledBitmap(),
                       oact->get_font());
      if ( !app->AddDefaultAction(dact) )
        delete dact;
    }
  }

}

/******************************************************************************/
/**
\brief  TProjectManager - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TProjectManager"

     TProjectManager :: TProjectManager ( )
                     : //  b(new BProjectManager),
  app(NULL),
  desktop(NULL),
  ucb(NULL),
  errhdl(NULL),
  projects(),
  std_actions(NULL),
  dict_pi(),
  dict_pi_reserved(0),
  cache(NULL),
  design_cache(NULL),
  splash(NULL)
{

  TPM = this;


}

/******************************************************************************/
/**
\brief  UCB - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCB"

UtilityHandle *TProjectManager :: UCB ( )
{

  return ucb;

}

/******************************************************************************/
/**
\brief  ~TProjectManager - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TProjectManager"

     TProjectManager :: ~TProjectManager ( )
{

  dict_pi.Close();
  
  delete std_actions;
  std_actions = NULL;

  delete ucb;
  ucb = NULL;

  delete cache;
  cache = NULL;
  delete design_cache;
  design_cache = NULL;

}


