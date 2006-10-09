/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    sosi

\brief    Global interface class


\date     $Date: 2006/08/27 20:29:47,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sosi"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <cwinsock.h>
#include  <deferr.h>
#include  <dstats.h>
#include  <exthrde.h>
#include  <fileacc.h>
#include  <globals.h>
#include  <sBNFData.hpp>
#include  <sBNFDefinition.hpp>
#include  <sBNFParser.hpp>
#include  <sBinArray.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCS_Client.hpp>
#include  <sCS_Server.hpp>
#include  <sCS_ServerClient.hpp>
#include  <sCTX_Base.hpp>
#include  <sError.hpp>
#include  <sHierarchicalIntervall.hpp>
#include  <sHierarchyTable.hpp>
#include  <sNBuffer.hpp>
#include  <sNString.hpp>
#include  <iNetConversion.h>
#include  <sNumFraction.hpp>
#include  <sObjectReferenceHandle.hpp>
#include  <sProcessInfo.hpp>
#include  <sPtrArray.hpp>
#include  <sRTTIClassInfo.hpp>
#include  <sReferenceObject.hpp>
#include  <sSOS_Variables.hpp>
#include  <sSimpleAction.hpp>
#include  <sStatistic.hpp>
#include  <sSystemIO.hpp>
#include  <sThreadEntry.hpp>
#include  <sUCA_CAction.hpp>
#include  <sUCA_CActionList.hpp>
#include  <sacc.hpp>
#include  <scfte.hpp>
#include  <sfld.hpp>
#include  <sflnk.hpp>
#include  <sguid.hpp>
#include  <sisrt.hpp>
#include  <sisrtu.hpp>
#include  <ssmcb.hpp>
#include  <ssvel.hpp>
#include  <stim.hpp>

#include  <isosi.h>

/******************************************************************************/
/**
\brief  ConnectErrorHandle - 



\return term - Success

\param  error_obj - Error object
\param  proc_vt - 
\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectErrorHandle"

logical __cdecl ConnectErrorHandle (Error *error_obj, ProcVariableTypes proc_vt, ProcessVariableNames pv_name )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(proc_vt);
  Error       *error;
  logical                 term = NO;
BEGINSEQ
// geht nicht, da parent_proc manchmal Müll ist. 
/*
  if ( !proc_info->get_parent_info() )               LEAVESEQ

  if ( (error = (Error *)proc_info->get_parent_info()->GetProcessVariable(pv_name)) )
    error_obj->SetHandle(error->get_error_handle());
*/
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConnectSystemVariables - 




\param  svelptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectSystemVariables"

void __cdecl ConnectSystemVariables (svel *svelptr )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  svel      *old_svel;
  logical    del_opt = NO;
BEGINSEQ
  if ( !svelptr )                                    ERROR
    
  if ( old_svel = SystemVariables() )
  {
    svelptr->ConnectTail(old_svel);
    del_opt = proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,NO);
  } 
  
  proc_info->SetProcessVariable(PVN_SOSSysVariables,svelptr);
  proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,del_opt);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CreateParser - Create BNF-parser

        The  function  creates  a  BNF  parser  for  the  BNF passed in the file
        'path'.  The  function  returns  a  pointer  to the parser, which allows
        analysing syntax aexpressions according to the defined BNF. 
        Since  the function is  optimizing the priority  for the parser symbols,
        one  may  list  the  priority  list  for the symbols, beginning with the
        symbol  of  highest  priority.  When  sub-parsers  are  referenced,  the
        symbols  for  sub-parsers  are  listed  as  well.  Symbols  with  higher
        priority  are  analized  before  symbols  of lower priority. This solves
        some  of ambiguity problems,  which result from  the fact, that the same
        symbol can be used as starting symbol in different production rules.
        The  parser  will  analyse  about  50  000 characters of compressed code
        within  one second (measured on  a 2 GHz intel  pentium 4 machine with a
        BNF  based on 75 symbols) within  one second. This example creates about
        60 000 nodes in the syntax tree occupiying 12 MB memory.

\return bparser - 

\param  path - Complete path
\param  list_symbols - List symbols
\param  trace_path - Trace file location
\param  bnf_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateParser"

BNFParser *__cdecl CreateParser (char *path, logical list_symbols, char *trace_path, char *bnf_path )
{
  BNFParser              *bparser = NULL;
  BNFParser              *parser  = NULL;
  BNFData                *bdata = NULL;
BEGINSEQ
  if ( bnf_path && *bnf_path )
  {
    if ( !(parser = CreateParser(bnf_path,NO,trace_path,NULL)) )
                                                     ERROR
  }
  else 
    parser = new BNFDefinition(NULL,trace_path);
    
  if ( !(bdata = parser->AnalyzeFile(path,YES)) )    ERROR

  if ( !(bparser = bdata->CreateParser(NULL,list_symbols,trace_path)) )
                                                     ERROR

RECOVER
  delete bparser;
  bparser = NULL;
ENDSEQ
  delete bdata;
  if ( parser )
    delete parser;
  return(bparser);
}

/******************************************************************************/
/**
\brief  DisconnectSystemVariables - 




\param  svelptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectSystemVariables"

void __cdecl DisconnectSystemVariables (svel *svelptr )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  svel      *cursvel;
  svel      *old_svel;
  logical    del_opt = NO;
  if ( cursvel = SystemVariables() )
  {
    if ( old_svel = cursvel->DisconnectTail(svelptr) )
      del_opt = proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,NO);
  } 
    
  if ( old_svel )
  {
    proc_info->SetProcessVariable(PVN_SOSSysVariables,old_svel); 
    proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,del_opt);
  }

}

/******************************************************************************/
/**
\brief  ExecuteCommand - 



\return retval - 

\param  cmdline - 
\param  nresult - 
\param  err2out - 
\param  erronly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteCommand"

int32 __cdecl ExecuteCommand (char *cmdline, NBuffer &nresult, logical err2out, logical erronly )
{
char                  psBuffer[1024];
FILE                * pPipe = NULL;
int32                 retval = 0;

#if defined(WIN32)
HANDLE                my_pipein[2], my_pipeout[2], my_pipeerr[2];
PROCESS_INFORMATION   piProcInfo;
STARTUPINFO           siStartInfo;
SECURITY_ATTRIBUTES   sa;
#endif /* WIN32*/

BEGINSEQ
#if defined(WIN32)
  my_pipein[0]   = INVALID_HANDLE_VALUE;
  my_pipein[1]   = INVALID_HANDLE_VALUE;
  my_pipeout[0]  = INVALID_HANDLE_VALUE;
  my_pipeout[1]  = INVALID_HANDLE_VALUE;
  my_pipeerr[0]  = INVALID_HANDLE_VALUE;
  my_pipeerr[1]  = INVALID_HANDLE_VALUE;
        
/*
 * Soll der stderr auf stdin umgelenkt werden ? */

/*
 * Erzeuge die Pipes... */
  sa.nLength = sizeof(sa);          /* Laenge in Byte */
  sa.bInheritHandle = 1;            /* Descriptoren sollen vererbbar sein */
  sa.lpSecurityDescriptor = NULL;
        
  if ( !CreatePipe(&my_pipein[0],&my_pipein[1],&sa,1 << 13) )
                ERROR
  if ( !CreatePipe(&my_pipeout[0],&my_pipeout[1],&sa,1 << 13) )
                ERROR   
  if ( !CreatePipe(&my_pipeerr[0],&my_pipeerr[1],&sa,1 << 13) )
                ERROR
        
/*
 * Erzeuge jetzt den Sohnprozess */
  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb           = sizeof(STARTUPINFO);
  siStartInfo.hStdInput    = my_pipein[0];
  if ( !erronly )
    siStartInfo.hStdOutput   = my_pipeout[1];
  else
    siStartInfo.hStdOutput   = my_pipeerr[1];
        
  if ( err2out || erronly )
    siStartInfo.hStdError  = my_pipeout[1];
  else
    siStartInfo.hStdError  = my_pipeerr[1];
        
  siStartInfo.dwFlags    = STARTF_USESTDHANDLES;
        
  if ( !CreateProcess(NULL,
          (LPTSTR)cmdline,    // command line 
          NULL,               // process security attributes 
          NULL,               // primary thread security attributes 
          TRUE,               // handles are inherited 
                  CREATE_NO_WINDOW, // creation flags: Ohne Fenster (?)
                  NULL,               // use parent's environment 
                  NULL,               // use parent's current directory 
                  &siStartInfo,       // STARTUPINFO pointer 
                  &piProcInfo)        // receives PROCESS_INFORMATION 
    )
  {
    nresult = "Invalid command '";
    nresult += cmdline;
    nresult += "'";
    ERROR
  }

/* these handles belong to the child process*/
  CloseHandle(my_pipein[0]);  my_pipein[0]  = INVALID_HANDLE_VALUE;
  CloseHandle(my_pipeout[1]); my_pipeout[1] = INVALID_HANDLE_VALUE;
  CloseHandle(my_pipeerr[1]); my_pipeerr[1] = INVALID_HANDLE_VALUE;


  pPipe = _fdopen(_open_osfhandle((long)my_pipeout[0],_O_BINARY),"r");
#endif /* WIN32*/

  if ( !pPipe )
        ERROR

  while( !feof( pPipe ) )
  {
        if ( fgets( psBuffer, 128, pPipe ) != NULL )
        {
                nresult += psBuffer;
        }
  }

#if defined(WIN32)
  fclose(pPipe);
  my_pipeout[0] = INVALID_HANDLE_VALUE;
#endif /* WIN32 */

RECOVER
retval = ERIC;
ENDSEQ
#if defined(WIN32)
if (my_pipein[0]  != INVALID_HANDLE_VALUE)
        CloseHandle(my_pipein[0]);
if (my_pipein[1]  != INVALID_HANDLE_VALUE)
        CloseHandle(my_pipein[1]);
if (my_pipeout[0] != INVALID_HANDLE_VALUE)
        CloseHandle(my_pipeout[0]);
if (my_pipeout[1] != INVALID_HANDLE_VALUE)
        CloseHandle(my_pipeout[1]);
if (my_pipeerr[0] != INVALID_HANDLE_VALUE)
        CloseHandle(my_pipeerr[0]);
if (my_pipeerr[1] != INVALID_HANDLE_VALUE)
        CloseHandle(my_pipeerr[1]);
#endif /* WIN32 */
 
return retval;

}

/******************************************************************************/
/**
\brief  ExecuteProgram - 



\return term - Success

\param  prgnams - Program path
\param  pgmparm1 - First parameter
\param  pgmparm2 - Third parameter
\param  pgmparm3 - Third parameter
\param  pgmparm4 - Fourth parameter
\param  pgmparm5 - Fifth parameter
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteProgram"

logical __cdecl ExecuteProgram (char *prgnams, char *pgmparm1, char *pgmparm2, char *pgmparm3, char *pgmparm4, char *pgmparm5 )
{
  char      cmdline[512];

  strcpy(cmdline,prgnams);  

  if ( pgmparm1 && strlen(cmdline) + strlen(pgmparm1) +1 < sizeof(cmdline) )
    strcat(strcat(cmdline," "),pgmparm1); 
  if ( pgmparm2 && strlen(cmdline) + strlen(pgmparm2) +1 < sizeof(cmdline) )
    strcat(strcat(cmdline," "),pgmparm2); 
  if ( pgmparm3 && strlen(cmdline) + strlen(pgmparm3) +1 < sizeof(cmdline) )
    strcat(strcat(cmdline," "),pgmparm3); 
  if ( pgmparm4 && strlen(cmdline) + strlen(pgmparm4) +1 < sizeof(cmdline) )
    strcat(strcat(cmdline," "),pgmparm4); 
  if ( pgmparm5 && strlen(cmdline) + strlen(pgmparm5) +1 < sizeof(cmdline) )
    strcat(strcat(cmdline," "),pgmparm5); 

#ifndef  __unix__
  WinExec(cmdline,SW_SHOW);
#endif

  return(NO);

}

/******************************************************************************/
/**
\brief  GenerateParser - 



\return term - Success

\param  path - Complete path
\param  outpath - 
\param  trace_path - Trace file location
\param  bnf_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateParser"

logical __cdecl GenerateParser (char *path, char *outpath, char *trace_path, char *bnf_path )
{
  BNFParser        *parser = NULL;
  BNFData          *bdata = NULL;
  logical           term = NO;
BEGINSEQ
  if ( bnf_path && *bnf_path )
  {
    if ( !(parser = CreateParser(bnf_path,NO,trace_path,NULL)) )
                                                     ERROR
  }
  else 
    parser = new BNFDefinition(NULL,trace_path);
  
  if ( !(bdata = parser->AnalyzeFile(path,YES)) )     ERROR

  bdata->GenerateSource(outpath);
  if ( bdata->GenerateSource(outpath) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  delete bdata;
  if ( parser )
    delete parser;
  return(term);
}

/******************************************************************************/
/**
\brief  GetApplicationContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetApplicationContext"

CTX_Base *__cdecl GetApplicationContext ( )
{
  SystemIO    *sio = (SystemIO *)GetProcessVariable(PVN_SOSSystemIO);
  CTX_Base    *ctxptr = NULL;
BEGINSEQ
  if ( !sio )                                       ERROR
  
  ctxptr = sio->GetContext();
RECOVER
  ctxptr = NULL;
ENDSEQ
  return(ctxptr);
}

/******************************************************************************/
/**
\brief  GetErrorObject - 



\return error_ref - 

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorObject"

Error &__cdecl GetErrorObject (ProcessVariableNames pv_name )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  Error       *error = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = SOSInitProcessInfo()) )          ERROR

  error = (Error *)proc_info->GetProcessVariable(pv_name);

RECOVER

ENDSEQ
  return(*error);
}

/******************************************************************************/
/**
\brief  GetPosSysVariable - 



\return sysvartext - 

\param  indx - 
\param  vnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosSysVariable"

char *__cdecl GetPosSysVariable (int16 indx, char *vnames )
{
  svel     *var_list = SystemVariables();
  char     *vtext    = NULL;
  char      keyarea[ID_SIZE+1];
  if ( var_list )
    vtext = var_list->svelget(indx,vnames);

  return(vtext);
}

/******************************************************************************/
/**
\brief  GetProcessUseCount - 



\return use_count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProcessUseCount"

int32 __cdecl GetProcessUseCount ( )
{

  return ( ThreadEntry::GetProcessUseCount() );

}

/******************************************************************************/
/**
\brief  GetProcessVariable - Provide process variable



\return proc_variable - Process variable

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProcessVariable"

void *__cdecl GetProcessVariable (ProcessVariableNames pv_name )
{
  ProcessInfo            *proc_info = NULL;
  if ( proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS) )
    return(proc_info->GetProcessVariable(pv_name));
  return(NULL);


}

/******************************************************************************/
/**
\brief  GetSectionVariable - 



\return sysvartext - 

\param  vnames - 
\param  sectionname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSectionVariable"

char *__cdecl GetSectionVariable (char *vnames, char *sectionname )
{
  svel     *var_list = SystemVariables();
  char     *vtext;
BEGINSEQ
  if ( !sectionname || !*sectionname )
    vtext = GetSysVariable(vnames);
  else
    if ( var_list )
    {
      if ( !(vtext = var_list->svelread(vnames,sectionname)) ||
           !*vtext                                   )   ERROR
    }

RECOVER
  SOSRESET
  vtext = NULL;
ENDSEQ
  return(vtext);
}

/******************************************************************************/
/**
\brief  GetSysVariable - 



\return sysvartext - 

\param  vnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSysVariable"

char *__cdecl GetSysVariable (char *vnames )
{
  svel     *var_list = SystemVariables();
  char     *vtext;
  char      keyarea[ID_SIZE+1];

BEGINSEQ
  if ( var_list )
  {
    if ( !(vtext = var_list->svelget(vnames)) ||
         !*vtext                                   )     ERROR
  }
  else    
    vtext = getenv(gvtxbts(keyarea,vnames,ID_SIZE));

RECOVER
  vtext = NULL;
ENDSEQ
  return(vtext);

}

/******************************************************************************/
/**
\brief  GetSysVariableINIFile - 



\return sysvartext - 

\param  vnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSysVariableINIFile"

char *__cdecl GetSysVariableINIFile (char *vnames )
{
  svel           *var_list = SystemVariables();
  char           *string = NULL;
  while ( var_list && 
          !(string = var_list->GetINIFile()) && *string )
    var_list = var_list->Parent();

  if (string == 0) string = "";
  return( string );

}

/******************************************************************************/
/**
\brief  GetSysVariablePath - 



\return sysvartext - 

\param  vnames - 
\param  path - Complete path
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSysVariablePath"

char *__cdecl GetSysVariablePath (char *vnames, char *path, int32 maxlen )
{
  char           *string = NULL;
BEGINSEQ
  if ( !(string = GetSysVariable(vnames)) )          ERROR

  if ( !maxlen )
    maxlen = 257;
  strncpy(path,string,maxlen-1);
  path[maxlen-1] = 0;

  STRExchange(path,"\\","/",maxlen);

  string = path;
RECOVER
  string = NULL;
ENDSEQ
  return(string);

}

/******************************************************************************/
/**
\brief  GetThreadID - 



\return tid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThreadID"

int32 __cdecl GetThreadID ( )
{

  return(ThreadEntry::GetThreadID());

}

/******************************************************************************/
/**
\brief  PopSystemVariables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopSystemVariables"

void __cdecl PopSystemVariables ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  svel      *svelptr;
  logical    del_opt;
  if ( svelptr = SystemVariables()->Pop() )
  {  
    del_opt = proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,NO);
    proc_info->SetProcessVariable(PVN_SOSSysVariables,svelptr);
    proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,del_opt);
  }


}

/******************************************************************************/
/**
\brief  PushSystemVariables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushSystemVariables"

void __cdecl PushSystemVariables ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  svel      *svelptr;
  logical    del_opt;
  if ( svelptr = SystemVariables()->Push() )
  {  
    del_opt = proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,NO);
    proc_info->SetProcessVariable(PVN_SOSSysVariables,svelptr);
    proc_info->GetProcessVariables()->SetDeleteOption(PVN_SOSSysVariables,del_opt);
  }

}

/******************************************************************************/
/**
\brief  ReadSysVariable - 



\return sysvartext - 

\param  vnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadSysVariable"

char *__cdecl ReadSysVariable (char *vnames )
{
  svel     *var_list = SystemVariables();
  char     *vtext;
  char      keyarea[ID_SIZE+1];

BEGINSEQ
  if ( var_list )
  {
    if ( !(vtext = var_list->svelread(vnames)) ||
         !*vtext                                   )     ERROR
  }
  else    
    vtext = getenv(gvtxbts(keyarea,vnames,ID_SIZE));

RECOVER
  SOSRESET
  vtext = NULL;
ENDSEQ
  return(vtext);

}

/******************************************************************************/
/**
\brief  RegisterProcess - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterProcess"

void __cdecl RegisterProcess ( )
{

  ThreadEntry::CreateEntry();


}

/******************************************************************************/
/**
\brief  RemoveSysVariable - 




\param  vnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveSysVariable"

void __cdecl RemoveSysVariable (char *vnames )
{
  svel     *var_list = SystemVariables();

  if ( var_list )
    var_list->svelrmv(vnames);

}

/******************************************************************************/
/**
\brief  ReplaceSysVariable - 



\return textstr - 

\param  textstr - 
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSysVariable"

char *__cdecl ReplaceSysVariable (char *textstr, int32 maxlen )
{
  svel     *var_list = SystemVariables();

  return ( var_list ? var_list->svelexc(textstr,maxlen) : NULL);

}

/******************************************************************************/
/**
\brief  SOSError - 



\return error_ref - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SOSError"

Error &__cdecl SOSError ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  Error       *error = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = SOSInitProcessInfo()) )          ERROR

  error = (Error *)proc_info->GetProcessVariable(PVN_SOSError);

RECOVER

ENDSEQ
  return(*error);
}

/******************************************************************************/
/**
\brief  SOSInitProcessInfo - 



\return proc_info - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SOSInitProcessInfo"

ProcessInfo *__cdecl SOSInitProcessInfo ( )
{
  ProcessInfo *proc_info = NULL;

  if ( thread_list )
    if ( !(proc_info = ThreadEntry::GetCurProcInfo()) )
      proc_info = ThreadEntry::CreateCurProcInfo(NULL);
  
  if ( proc_info && !proc_info->GetVariableManager(PVT_SOS) )
    proc_info->SetVariableManager(new SOS_Variables(proc_info->GetProcessVariables()));

   

  return(proc_info);
}

/******************************************************************************/
/**
\brief  SOSResources - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SOSResources"

void __cdecl SOSResources ( )
{
extern       int32   vcls_count;
extern       int32   msm_count;
extern       int32   msm_area;
extern       int32   dll_count;
extern       int32   lo_count;
extern       int32   ctx_count;
  char               string[31];
  SOSError().TraceMessage("vcls count: ",gvtxltoa(vcls_count,string,10));
  vcls_count = 0;
  SOSError().TraceMessage("pecb count: ",gvtxltoa(msm_count,string,10));
  msm_count = 0;
  SOSError().TraceMessage("pecb size : ",gvtxltoa(msm_area,string,10));
  msm_area = 0;
  SOSError().TraceMessage("dll count : ",gvtxltoa(dll_count,string,10));
  dll_count = 0;
  SOSError().TraceMessage("lo count  : ",gvtxltoa(lo_count,string,10));
  lo_count = 0;
  SOSError().TraceMessage("ctx count : ",gvtxltoa(ctx_count,string,10));
  ctx_count = 0;


}

/******************************************************************************/
/**
\brief  SetApplicationContext - 



\return term - Success

\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetApplicationContext"

logical __cdecl SetApplicationContext (CTX_Base *ctxptr )
{
  SystemIO    *sio = (SystemIO *)GetProcessVariable(PVN_SOSSystemIO);
  logical      term = NO;
BEGINSEQ
  if ( !sio )                                       ERROR
  
  sio->SetContext(ctxptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetProcessVariable - 




\param  pv_name - Process variable name
\param  proc_variable - Process variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProcessVariable"

void __cdecl SetProcessVariable (ProcessVariableNames pv_name, void *proc_variable )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = SOSInitProcessInfo()) )          ERROR

  proc_info->SetProcessVariable(pv_name,proc_variable);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetSysVarINIFile - 




\param  inipath - 
\param  sectionname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSysVarINIFile"

void __cdecl SetSysVarINIFile (char *inipath, char *sectionname )
{
  svel     *var_list = SystemVariables();

  if ( var_list )
    var_list->svelfini(inipath,sectionname);

}

/******************************************************************************/
/**
\brief  SetSysVariable - 



\return term - Success

\param  vnames - 
\param  vtext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSysVariable"

logical __cdecl SetSysVariable (char *vnames, char *vtext )
{
  svel     *var_list = SystemVariables();

  return ( var_list ? var_list->svelset(vnames,vtext) : YES );


}

/******************************************************************************/
/**
\brief  SetSystemVariables - 



\return term - Success

\param  svelptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSystemVariables"

logical __cdecl SetSystemVariables (svel *svelptr )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  logical      term = NO;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = SOSInitProcessInfo()) )          ERROR

  proc_info->SetProcessVariable(PVN_SOSSysVariables,svelptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ShutDownProcess - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShutDownProcess"

void __cdecl ShutDownProcess ( )
{

  ThreadEntry::DeleteEntry();


}

/******************************************************************************/
/**
\brief  SystemInput - 



\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemInput"

char *__cdecl SystemInput (char *string )
{
  SystemIO    *sio = (SystemIO *)GetProcessVariable(PVN_SOSSystemIO);

BEGINSEQ
  if ( !sio )                                       ERROR

  string = sio->Read(string);
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  SystemOutput - 



\return term - Success

\param  string - String value
\param  clear_opt - 
\param  flush_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemOutput"

logical __cdecl SystemOutput (char *string, logical clear_opt, logical flush_opt )
{
  SystemIO    *sio = (SystemIO *)GetProcessVariable(PVN_SOSSystemIO);
  logical      term = NO;
BEGINSEQ
  if ( !sio )                                       ERROR

  sio->Write(string,clear_opt,flush_opt);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SystemVariables - 



\return svelptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemVariables"

svel *__cdecl SystemVariables ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_SOS);
  svel        *svelptr = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = SOSInitProcessInfo()) )          ERROR

  svelptr = (svel *)proc_info->GetProcessVariable(PVN_SOSSysVariables);

RECOVER

ENDSEQ
  return(svelptr);
}

/******************************************************************************/
/**
\brief  TestSysVariable - 



\return cond - Return value

\param  vnames - 
\param  vtext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TestSysVariable"

logical __cdecl TestSysVariable (char *vnames, char *vtext )
{
  char      *sysvar_str;
  logical    cond = YES;

BEGINSEQ
  if ( !(sysvar_str = GetSysVariable(vnames)) )      ERROR
  
  if ( strcmp(sysvar_str,vtext) )                    ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  UnregisterProcess - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterProcess"

void __cdecl UnregisterProcess ( )
{

  ThreadEntry::RemoveEntry();


}

/******************************************************************************/
/**
\brief  UpdateSysVariable - 



\return vtext - 

\param  vnames - 
\param  vtext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateSysVariable"

char *__cdecl UpdateSysVariable (char *vnames, char *vtext )
{
  svel     *var_list = SystemVariables();
  return( var_list ? var_list->svelupd(vnames,vtext) : NULL);

}

/******************************************************************************/
/**
\brief  htonb - 



\return big_val - 

\param  big_int - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "htonb"

int64 __cdecl htonb (int64 big_int )
{
  int32           val_lo;
  int32           val_hi;
  int64           big_val;
  val_lo = big_int;
  val_lo = htonl(val_lo);
  val_hi = big_int >> 32;
  val_hi = htonl(val_hi);
  *(int32 *)&big_val = val_lo;
  *(int32 *)(((char *)&big_val)+4) = val_hi;

  return(big_val);
}

/******************************************************************************/
/**
\brief  ntohb - 



\return big_int - 

\param  big_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ntohb"

int64 __cdecl ntohb (int64 big_val )
{
  int32              val_lo;
  int32              val_hi;
  int64              big_int;
  val_lo = *(int32 *)&big_val;
  val_lo = ntohl(big_val);
  val_hi = *(int32 *)(((char *)&big_val)+4);
  val_hi = ntohl(val_hi);
  big_int = val_hi;
  big_int = ( big_int << 32 ) + val_lo;

  return(big_int);
}

