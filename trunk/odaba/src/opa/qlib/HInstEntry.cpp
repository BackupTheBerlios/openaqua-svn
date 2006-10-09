/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    HInstEntry

\brief    


\date     $Date: 2006/03/12 19:17:35,65 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HInstEntry"

#include  <popa7.h>
#include  <win32f.h>
#include  <ssvel.hpp>
#include  <sHInstEntry.hpp>
#include <iostream>

/******************************************************************************/
/**
\brief  HInstEntry - 



\param  dllname -
\param  check_opt -
*/
/******************************************************************************/

void* LoadLibrary(std::string name){
  void* handle = NULL;
  std::cerr << "load:(" << name << ")" << std::endl;
  handle = dlopen(name.c_str(),RTLD_NOW);
  if(!handle){
    std::cerr << "failure: " << dlerror() << std::endl;
    return NULL;
  }
  dlerror();
  return handle;
    
}
#undef     MOD_ID
#define    MOD_ID  "HInstEntry"

                        HInstEntry :: HInstEntry (char *dllname, logical check_opt )
{
  svel      *svelptr;
  char       dllpath[513];
  char       string[25];
  char      *pos;
  char      *syspath = NULL;

BEGINSEQ
  SDBEV1(dllname,UNDEF)
  gvtxstb(dll_name,dllname,256);
  hinstance = NULL;
  strcpy(dllpath,dllname);

  if ( !(hinstance = LoadLibrary(dllpath)) )       
  {
#ifndef __unix__    
    if ( !check_opt )
      SDBError().TraceMessage("Path: ",dllname,"System error: ",gvtxltoa(GetLastError(),string,10));
#endif
    *dllpath = 0;
    syspath = GetSysVariable("ODABA_PATH");
    if ( syspath && *syspath )
    {
      strcpy(dllpath,syspath);
      ReplaceSysVariable(dllpath,sizeof(dllpath)-1);
      if ( dllpath[strlen(dllpath)-1] != '/' && dllpath[strlen(dllpath)-1] != '\\' )
        strcat(dllpath,"/");
      if ( pos = STRSearchChar(dllname,'/',YES) )
        pos++;
      else
        pos = dllname;
      strcat(dllpath,pos);
      if ( !(hinstance = LoadLibrary(dllpath)) )       
      {
        if ( !check_opt )
        SDBError().TraceMessage("Path: ",dllpath," is invalid");
#ifndef __unix__    
        SDBError().TraceMessage("Path: ",dllpath,"System error: ",gvtxltoa(GetLastError(),string,10));
#endif      
        *dllpath = 0;
      }
    }
    else
    {
      syspath = GetSysVariable("PROJECT_PATH");
      if ( syspath && *syspath )
      {
        strcpy(dllpath,syspath);
        ReplaceSysVariable(dllpath,sizeof(dllpath)-1);
        if ( dllpath[strlen(dllpath)-1] != '/' && dllpath[strlen(dllpath)-1] != '\\' )
          strcat(dllpath,"/");
        if ( pos = STRSearchChar(dllname,'/',YES) )
          pos++;
        else
          pos = dllname;
        strcat(dllpath,pos);
        hinstance = LoadLibrary(dllpath);       
      }
    }
  }
  if ( !hinstance )       
  {
    if ( check_opt )                                           ERROR
#ifndef __unix__    
    SDBError().TraceMessage("Path: ",dllpath,"System error: ",gvtxltoa(GetLastError(),string,10));
#else
    SDBError().TraceMessage("Path: ",dllpath," is invalid");
#endif
    SDBERR(202)
  }
//  else
//    SDBError().TraceMessage(dllpath, " loaded successfully");

RECOVER
  SDBRESET  // bleibt sonst manchmal beim oeffnen einer DB stehen (context-dll)

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~HInstEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~HInstEntry"

                        HInstEntry :: ~HInstEntry ( )
{



}


