/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    UCTX_dll

\brief    


\date     $Date: 2006/08/22 12:08:23,84 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCTX_dll"

#include  <podcp8.h>
#include  <fctypes.h>
#include  <ifil.h>
#include  <win32f.h>
#include  <sCTX_Administration.hpp>
#include  <sCTX_Application.hpp>
#include  <sCTX_Control.hpp>
#include  <sCTX_Document.hpp>
#include  <sCTX_Project.hpp>
#include  <sUCTX_dll.hpp>


/******************************************************************************/
/**
\brief  CreateAdminCtx - 



\return ctx_adm - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAdminCtx"

CTX_Administration *UCTX_dll :: CreateAdminCtx (int32 resid )
{
  CTX_Base               *ctx_base = NULL;
  CTX_Administration     *ctx_adm  = NULL;
BEGINSEQ
  if ( crt_ctx )
    if ( ctx_base = crt_ctx(resid) )
      if ( ctx_base->GetContextType() == CTXT_Administration )
        ctx_adm = (CTX_Administration *)ctx_base;
      else
      {
        delete ctx_base;
        ctx_base = NULL;
        OADISET(99)
      }
      
  if ( !ctx_adm )
  { 
    ctx_adm = new CTX_Administration();
    ctx_adm->set_user_context(NO);
  }

  if ( !ctx_adm )                                    OADIERR(95)
RECOVER
  ctx_adm = NULL;
ENDSEQ
  return(ctx_adm);
}

/******************************************************************************/
/**
\brief  CreateApplicationCtx - 



\return ctx_appl - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateApplicationCtx"

CTX_Application *UCTX_dll :: CreateApplicationCtx (int32 resid )
{
  CTX_Base               *ctx_base = NULL;
  CTX_Application        *ctx_appl = NULL;
BEGINSEQ
  if ( crt_ctx )
    if ( ctx_base = crt_ctx(resid) )
      if ( ctx_base->GetContextType() == CTXT_Application )
        ctx_appl = (CTX_Application *)ctx_base;
      else
      {
        delete ctx_base;
        ctx_base = NULL;
        OADISET(99)
      }
      
  if ( !ctx_appl )
  { 
    ctx_appl = new CTX_Application();
    ctx_appl->set_user_context(NO);
  }

  if ( !ctx_appl )                                    OADIERR(95)
RECOVER
  ctx_appl = NULL;
ENDSEQ
  return(ctx_appl);
}

/******************************************************************************/
/**
\brief  CreateControlCtx - 



\return ctx_ctl - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateControlCtx"

CTX_Control *UCTX_dll :: CreateControlCtx (int32 resid )
{
  CTX_Base               *ctx_base = NULL;
  CTX_Control            *ctx_ctl  = NULL;
BEGINSEQ
  if ( crt_ctx )
    if ( ctx_base = crt_ctx(resid) )
      if ( ctx_base->GetContextType() == CTXT_Control )
        ctx_ctl = (CTX_Control *)ctx_base;
      else
      {
        delete ctx_base;
        ctx_base = NULL;
        OADISET(99)
      }
      
  if ( !ctx_ctl )
  { 
    ctx_ctl = new CTX_Control();
    ctx_ctl->set_user_context(NO);
  }

  if ( !ctx_ctl )                                    OADIERR(95)
RECOVER
  ctx_ctl = NULL;
ENDSEQ
  return(ctx_ctl);
}

/******************************************************************************/
/**
\brief  CreateDocumentCtx - 



\return ctx_doc - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDocumentCtx"

CTX_Document *UCTX_dll :: CreateDocumentCtx (int32 resid )
{
  CTX_Base               *ctx_base = NULL;
  CTX_Document           *ctx_doc  = NULL;
BEGINSEQ
  if ( crt_ctx )
    if ( ctx_base = crt_ctx(resid) )
      if ( ctx_base->GetContextType() == CTXT_Document )
        ctx_doc = (CTX_Document *)ctx_base;
      else
      {
        delete ctx_base;
        ctx_base = NULL;
        OADISET(99)
      }
      
  if ( !ctx_doc )
  { 
    ctx_doc = new CTX_Document();
    ctx_doc->set_user_context(NO);
  }

  if ( !ctx_doc )                                    OADIERR(95)
RECOVER
  ctx_doc = NULL;
ENDSEQ
  return(ctx_doc);
}

/******************************************************************************/
/**
\brief  CreateProjectCtx - 



\return ctx_prj - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProjectCtx"

CTX_Project *UCTX_dll :: CreateProjectCtx (int32 resid )
{
  CTX_Base               *ctx_base = NULL;
  CTX_Project            *ctx_prj  = NULL;
BEGINSEQ
  if ( crt_ctx )
    if ( ctx_base = crt_ctx(resid) )
      if ( ctx_base->GetContextType() == CTXT_Project )
        ctx_prj = (CTX_Project *)ctx_base;
      else
      {
        delete ctx_base;
        ctx_base = NULL;
        OADISET(99)
      }
      
  if ( !ctx_prj )
  { 
    ctx_prj = new CTX_Project();
    ctx_prj->set_user_context(NO);
  }

  if ( !ctx_prj )                                    OADIERR(95)
RECOVER
  ctx_prj = NULL;
ENDSEQ
  return(ctx_prj);
}

/******************************************************************************/
/**
\brief  GetDLLPath - 



\return dllpath - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDLLPath"

char *UCTX_dll :: GetDLLPath ( )
{
  static  char       dll_path[1000];
  char               dll_name[40];
  char              *opath    = NULL;
  char              *db_path  = NULL;
  char               drives[5];
  char               dirs[512];
BEGINSEQ
  strcpy(dll_name,"uctx");
  if ( GetSysVariable("PROJECT_PATH") )
  {
    if ( GetSysVariable("PROJECT_DLL") )
      strcpy(dll_name,GetSysVariable("PROJECT_DLL"));
    else if ( GetSysVariable("PROJECT") )
      strcpy(dll_name,GetSysVariable("PROJECT"));
    strcpy(dll_path,GetSysVariable("PROJECT_PATH"));
    if ( dll_path[strlen(dll_path)-1] != '\\' && 
         dll_path[strlen(dll_path)-1] != '/'     )
      strcat(dll_path,"/");
    strcat(strcat(dll_path,dll_name),".dll");
    if ( IsFile(dll_path) )                          LEAVESEQ
    *dll_path = 0;
    opath   = GetSysVariable("ODABA_PATH");
    db_path = GetSysVariable("RESDB");
  }
  else if ( GetSysVariable("PROGPATH") )
  {
    if ( GetSysVariable("PROJECT_DLL") )
      strcpy(dll_name,GetSysVariable("PROJECT_DLL"));
    else if ( GetSysVariable("PROJECT") )
      strcpy(dll_name,GetSysVariable("PROJECT"));
    strcpy(dll_path,GetSysVariable("PROGPATH"));
    if ( dll_path[strlen(dll_path)-1] != '\\' && 
         dll_path[strlen(dll_path)-1] != '/'     )
      strcat(dll_path,"/");
    strcat(strcat(dll_path,dll_name),".dll");
    if ( IsFile(dll_path) )                          LEAVESEQ
    *dll_path = 0;
    opath   = GetSysVariable("ODABA_PATH");
    db_path = GetSysVariable("RESDB");
  }
  
  if ( db_path )
  {
    fildirg (db_path,drives,dirs);
  
    strcat(strcat(strcpy(dll_path,drives),dirs),"exe/");
    strcat(strcat(dll_path,dll_name),".dll");
    if ( IsFile(dll_path) )                         LEAVESEQ
    *dll_path = 0;
  
    strcat(strcpy(dll_path,drives),dirs);
    strcat(strcat(dll_path,dll_name),".dll");
    if ( IsFile(dll_path) )                         LEAVESEQ
  }
  
  if ( opath )
  {
    strcpy(dll_path,opath);
    strcat(strcat(dll_path,dll_name),".dll");
    if ( IsFile(dll_path) )                         LEAVESEQ
  }
  strcat(strcpy(dll_path,dll_name),".dll");

ENDSEQ
  return(dll_path);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical UCTX_dll :: Initialize ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( loaded && dll_instance == NULL )              ERROR
  
#ifdef __unix__    
  dll_instance = dlopen(GetDLLPath(),RTLD_LAZY);
#else
  dll_instance = LoadLibrary(GetDLLPath());
#endif
  if ( !dll_instance )                               OADIERR(202)
    
  crt_ctx  = (CreateCtxPtr)  GetProcAddress(dll_instance,"CreateContext");

/*    
  crt_adm_ctx  = (CreateAdminCtxPtr)GetProcAddress(dll_instance,"CreateAdminContext");
  crt_appl_ctx = (CreateApplCtxPtr) GetProcAddress(dll_instance,"CreateApplicationContext");
  crt_ctl_ctx  = (CreateCtlCtxPtr)  GetProcAddress(dll_instance,"CreateControlContext");
  crt_doc_ctx  = (CreateDocCtxPtr)  GetProcAddress(dll_instance,"CreateDocumentContext");
  crt_prj_ctx  = (CreatePrjCtxPtr)  GetProcAddress(dll_instance,"CreateProjectContext");
*/
RECOVER
  term = YES;
ENDSEQ
  loaded = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  UCTX_dll - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCTX_dll"

     UCTX_dll :: UCTX_dll ( )
                     :   dll_instance(NULL),
  crt_ctx(NULL),
  loaded(NO)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  ~UCTX_dll - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~UCTX_dll"

     UCTX_dll :: ~UCTX_dll ( )
{

  if ( dll_instance )
#ifdef __unix__    
    dlclose(dll_instance);
#else
    FreeLibrary(dll_instance);
#endif

}


