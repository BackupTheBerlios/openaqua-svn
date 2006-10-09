/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pKlasseditor

\brief    


\date     $Date: 2006/08/28 07:57:04,26 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pKlasseditor"

#include  <pdesign.h>
#include  <cProjectImplementationType.h>
#include  <sdc_ResourceDB.hpp>
#include  <spKlasseditor.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - 

\param  ctx_prj_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pKlasseditor :: Create (CTX_Project **ctx_prj_ptrp )
{

  *ctx_prj_ptrp = new pKlasseditor();
  return(NO);

}

/******************************************************************************/
/**
\brief  CreateCInterface - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCInterface"

logical pKlasseditor :: CreateCInterface ( )
{
  int32            rc          = ERIC;
  logical          crt_stub    = NO;
  logical          term        = NO;
BEGINSEQ
  if ( ReserveProject() )                            ERROR
  SetActionDisabled(NULL,YES,"CreateCInterface");
  Pointer(POINTER_Wait);
  
  SetSysVariable("C_INTERFACE","Y");
  SetSysVariable("INCCLASS","");
  
  SetupOutput("...Creating C-Interface Header File\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"C_InterfaceHeader()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  
  SetupOutput("...Creating C-Interface Source File\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"C_InterfaceSource()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  
  if ( crt_stub = TestSysVariable("CREATE_STUBLIB","YES") )
  {
    SetSysVariable("PROJECT_NAME",ProjectName());
  
    SetupOutput("...Creating C_Stub ComeIn\n",YES);
    if ( !project.ExecuteExpression(GetRESDB(),"C_StubSource()").IsValid() )
      SetupOutput("...  terminated with errors\n",NO);
  
    SetupOutput("...Creating PL_Interface Source File\n",YES);
    if ( !project.ExecuteExpression(GetRESDB(),"PL_InterfaceSource()").IsValid() )
      SetupOutput("...  terminated with errors\n",NO);
  }
  
  if ( project.ExecuteInstanceAction("GetCompileCommand","ci_") )
    SetupOutput("Error: providing compile\n",NO);
  else
  {
    rc = ExecuteCommand(project.GetActionResult(),output,YES,NO);
    SetupOutput(NULL,NO);
  }                   
  
  if ( crt_stub )
  {
//    strcat(ppd22ptr->GetProjectPath(comppath,ERC_Batch),"CreateStublib.bat");
//    ExecuteProgram(comppath,ppd22ptr->GetProjectName());  
  }
  
  SetSysVariable("C_INTERFACE","");
  
  Pointer(POINTER_Arrow);
  SetActionDisabled(NULL,NO,"CreateCInterface");
  ReleaseProject();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateClientServerInterface - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateClientServerInterface"

logical pKlasseditor :: CreateClientServerInterface ( )
{
  int32            rc          = ERIC;
  logical          term        = NO;
BEGINSEQ
  if ( ReserveProject() )                            ERROR
  SetActionDisabled(NULL,YES,"CreateClientServerInterface");
  Pointer(POINTER_Wait);

  SetSysVariable("IF_IMP_NAME",GetOptionState("CSIPrefix"));  

  SetupOutput("...Creating Class and Function Definitions for Client Server Interface\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"CS_Generate()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  
  if ( project.ExecuteInstanceAction("GetCompileCommand","_cs_") )
    SetupOutput("Error: providing compile\n",NO);
  else
  {
    rc = ExecuteCommand(project.GetActionResult(),output,YES,NO);
    SetupOutput(NULL,NO);
  }                   
  
  Pointer(POINTER_Arrow);
  SetActionDisabled(NULL,NO,"CreateClientServerInterface");
  ReleaseProject();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateICEInterface - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateICEInterface"

logical pKlasseditor :: CreateICEInterface ( )
{
  logical          term        = NO;
BEGINSEQ
  if ( ReserveProject() )                            ERROR
  SetActionDisabled(NULL,YES,"CreateICEInterface");
  Pointer(POINTER_Wait);
  
  SetupOutput("...Creating ICE-Interface SLICE File\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"ICE_InterfaceSlice()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  
  SetupOutput("...Creating ICE-Interface Header File\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"ICE_InterfaceHeader()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);

  SetupOutput("...Creating ICE-Interface Source File\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"ICE_InterfaceSource()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);

  SetupOutput("...Creating ICE-Interface Helper Files\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"ICE_InterfaceHelper()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
      

  Pointer(POINTER_Arrow);
  SetActionDisabled(NULL,NO,"CreateICEInterface");
  ReleaseProject();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateServerClientInterface - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateServerClientInterface"

logical pKlasseditor :: CreateServerClientInterface ( )
{
  int32            rc          = ERIC;
  logical          term        = NO;
BEGINSEQ
  if ( ReserveProject() )                            ERROR
  SetActionDisabled(NULL,YES,"CreateServerClientInterface");
  Pointer(POINTER_Wait);
  
  SetSysVariable("IF_IMP_NAME",GetOptionState("SCIPrefix"));  

  SetupOutput("...Creating Class and Function definitions for Server Client Interface\n",YES);
  if ( !project.ExecuteExpression(GetRESDB(),"SC_Generate()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  
  if ( project.ExecuteInstanceAction("GetCompileCommand","_sc_") )
    SetupOutput("Error: providing compile\n",NO);
  else
  {
    rc = ExecuteCommand(project.GetActionResult(),output,YES,NO);
    SetupOutput(NULL,NO);
  }                   
  
  Pointer(POINTER_Arrow);
  SetActionDisabled(NULL,NO,"CreateServerClientInterface");
  ReleaseProject();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateUSERContext - Create context includes from SDB_ResourceRefs

        The   action   writes   the   two   include   files  'iCtxClasses.h' and
        'iCtxIncl.h' to the include folder of the currently selected project.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateUSERContext"

logical pKlasseditor :: CreateUSERContext ( )
{
  PropertyHandle  *imp_classes = NULL;
  char            *proj_name   = NULL;
  char            *proj_path   = NULL;
  char            *proj_ctx    = NULL;
  char             parmstr[ID_SIZE*2+3];
  int32            rc          = ERIC;
  logical          term        = NO;
BEGINSEQ
  if ( ReserveProject() )                            ERROR
  SetActionDisabled(NULL,YES,"CreateUSERContext");
  Pointer(POINTER_Wait);
  
  SetupOutput("...Creating context include files\n",YES);
  
  proj_name = ProjectName();
  proj_path = ProjectPath("ERC_Include");
  proj_ctx  = ProjectContextClass();
  
  PropertyHandle    resrefs(GetDATDB(),"SDB_ResourceRef",PI_Read);
  term = resrefs.ExecutePropertyAction("WriteContextFiles",
                                        strcat(strcat(strcpy(parmstr,proj_name),","),
                                                                     proj_path));
  if ( term )
    SetupOutput("...  terminated with errors\n",NO);
  else
  {    
    if ( !proj_ctx || !*proj_ctx )  
      SetupOutput("Warning: context class could not be located for compiling\n",NO);
    else
    {  
      imp_classes = project.GPH("classes");
      if ( imp_classes->ExecuteInstanceAction("GetCompileCommand",NULL) )
        SetupOutput("Error: providing compile\n",NO);
      else
      {
        rc = ExecuteCommand(imp_classes->GetActionResult(),output,YES,NO);
        SetupOutput(NULL,NO);
  
        if ( !imp_classes->NoWrite() )
          *imp_classes->GPH("req_compile") = (char*)( rc ? "CPS_failed" : "CPS_ready" );
      }                   
    }                   
  }                   
  
  Pointer(POINTER_Arrow);
  SetActionDisabled(NULL,NO,"CreateUSERContext");
  ReleaseProject();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 pKlasseditor :: DoAfterOpen ( )
{
  char        *option       = NULL;
  logical      term         = NO;
  term = pODE::DoAfterOpen();

  strcpy(application_name,"Developer");
  
  if ( !*GetOption("CSIPrefix") )
    SetSysVariable("CSIPrefix","ci");
  if ( !*GetOption("SCIPrefix") )
    SetSysVariable("SCIPrefix","si");
    
  option = GetOption("InputHelp");
  EnableInputHelp(*option == 'Y' || *option == 'y');  

  option = GetOption("ProjectSelection");
  SetActionToggled("ProjectSelection",*option == 'Y' || *option == 'y' ? YES : NO);

  SelectProject(""); // has been set in pODE::DoAfterOpen  
  

  return(term);
}

/******************************************************************************/
/**
\brief  DoForProject - 



\return term - 

\param  expression - 
\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoForProject"

logical pKlasseditor :: DoForProject (char *expression, char *string )
{
  logical                 term = NO;
BEGINSEQ
  if ( ReserveProject() )                            ERROR
  Pointer(POINTER_Wait);
  
  SetupOutput(string,YES);
  if ( !project.ExecuteExpression(GetRESDB(),expression).IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  else
    SetupOutput("...  terminated successfully\n",NO);

  Pointer(POINTER_Arrow);
  ReleaseProject();


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 



\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical pKlasseditor :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("CreateClientServerInterface",ALINK(this,pKlasseditor,CreateClientServerInterface)),
                           cfte("CreateICEInterface",ALINK(this,pKlasseditor,CreateICEInterface)),
                           cfte("CreateServerClientInterface",ALINK(this,pKlasseditor,CreateServerClientInterface)),
                           cfte("CreateUSERContext",ALINK(this,pKlasseditor,CreateUSERContext)),
                           cfte("GenerateAllIncludes",ALINK(this,pKlasseditor,GenerateAllIncludes)),
                           cfte("GenerateAllSources",ALINK(this,pKlasseditor,GenerateAllSources)),
                           cfte("GenerateCompileBatchForUNIX",ALINK(this,pKlasseditor,GenerateCompileBatchForUNIX)),
                           cfte("GenerateCompileBatchForWIN",ALINK(this,pKlasseditor,GenerateCompileBatchForWIN)),
                           cfte("GenerateIncludes",ALINK(this,pKlasseditor,GenerateIncludes)),
                           cfte("GenerateSources",ALINK(this,pKlasseditor,GenerateSources)),
                           cfte("InitProjectResources",ALINK(this,pKlasseditor,InitProjectResources)),
                           cfte("InitResourceDB",ALINK(this,pKlasseditor,InitResourceDB)),
                           cfte("Link",ALINK(this,pKlasseditor,Link)),
                           cfte("ProjectSelection",ALINK(this,pKlasseditor,ProjectSelection)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = pODE::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateAllIncludes - Generate header files  for all implementation classes

        For  all implementation classes of current project the header files will
        be generated.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateAllIncludes"

logical pKlasseditor :: GenerateAllIncludes ( )
{

  return ( DoForProject("All_Includes()",
                        "...generating header files for all implementation classes of current project\n") );

}

/******************************************************************************/
/**
\brief  GenerateAllSources - Generate source files  for all implementation classes

        For  all implementation classes of current project the source files will
        be generated.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateAllSources"

logical pKlasseditor :: GenerateAllSources ( )
{

  return ( DoForProject("All_Sources()",
                        "...generating source files for all implementation classes of current project\n") );


}

/******************************************************************************/
/**
\brief  GenerateCompileBatch - 



\return term - 

\param  parm1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCompileBatch"

logical pKlasseditor :: GenerateCompileBatch (char *parm1 )
{
  char           parm_string[512];
  logical        term = NO;
BEGINSEQ
  if ( !project.IsPositioned() )                     ERROR
  
  PropertyHandle  select(GetRESDictionary(),"FORM_select_ODC_ImpClasses");
                                                     P_SDBCERR
  if ( ExecuteWindow(&select,"FORM_select_ODC_ImpClasses","Edit",NO) )
                                                     LEAVESEQ
  Pointer(POINTER_Wait);
  
  output = "...Generating compile batch for ";
  output += parm1;
  output += " \n";
  DisplayOutput();

  strcpy(parm_string,parm1);
  strcat(strcat(parm_string,","),select.GPH("comp_state")->GetString());
  strcat(strcat(parm_string,","),select.GPH("comp_no")->GetString());
  strcat(strcat(parm_string,","),select.GPH("collect_name")->GetString());
  project.ExecuteInstanceAction("GenerateCompile",parm_string);

  SetupOutput(project.GetActionResult(),NO);

  Pointer(POINTER_Arrow);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateCompileBatchForUNIX - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCompileBatchForUNIX"

logical pKlasseditor :: GenerateCompileBatchForUNIX ( )
{

  return ( GenerateCompileBatch("UNIX") );

}

/******************************************************************************/
/**
\brief  GenerateCompileBatchForWIN - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCompileBatchForWIN"

logical pKlasseditor :: GenerateCompileBatchForWIN ( )
{

  return ( GenerateCompileBatch("WIN") );

}

/******************************************************************************/
/**
\brief  GenerateIncludes - Generate header files  for modified implementation classes

        For  all modified  implementation classes  of current project the header
        files will be generated.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateIncludes"

logical pKlasseditor :: GenerateIncludes ( )
{

  return ( DoForProject("RQ_Includes()",
                        "...generating header files for modified implementation classes of current project\n") );


}

/******************************************************************************/
/**
\brief  GenerateSources - Generate source files  for modified implementation classes

        For  all modified  implementation classes  of current project the source
        files will be generated.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSources"

logical pKlasseditor :: GenerateSources ( )
{

  return ( DoForProject("RQ_Sources()",
                        "...generating source files for modified implementation classes of current project\n") );


}

/******************************************************************************/
/**
\brief  GetImpClassContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImpClassContext"

CTX_Control *pKlasseditor :: GetImpClassContext ( )
{

//*** re-implement *** s.a. pODE
//  return ( GetControlContext("klasseditor.class_ws.class_stack.edit_class_function") );
  return( pODE::GetImpClassContext() );

}

/******************************************************************************/
/**
\brief  GetOptionState - 



\return option - 

\param  option_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOptionState"

char *pKlasseditor :: GetOptionState (char *option_name )
{
  char *   option = NULL;
  if ( !strcmp(option_name,"InputHelp") )
    option = IsActionToggled("InputHelp") ? "YES" : "NO";
  else if ( !strcmp(option_name,"ProjectSelection") )
    option = IsActionToggled("ProjectSelection") ? "YES" : "NO";
  else
    option = pODE::GetOptionState(option_name);
    
  

  return(option);
}

/******************************************************************************/
/**
\brief  InitProjectResources - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitProjectResources"

logical pKlasseditor :: InitProjectResources ( )
{
  CTX_Control    *context = GetControlContext("klasseditor.class_ws.class_stack");
  PropertyHandle *ph      = NULL;
  NString         nstring;
  logical         term    = NO;
  nstring.Append(' ',2);
  nstring += project_name;
  nstring += "...Initializing external resources - folder and procedures\n";
  ODEOutput(this,nstring,YES);
  nstring = "";

  if ( context )
    context->ExecuteAction("Save",ACT_Function);

  if ( project.Reset() )
    SelectProject("");

  term = project.InitExternalResources(this,PIT_undefined,YES,nstring);
  ODEOutput(this,nstring,NO);
  
  if ( context && (ph = context->GetCurrentPropertyHandle()) )
  {
    ph->Reset();
    context->FillControl();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  InitResourceDB - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pKlasseditor :: InitResourceDB ( )
{
  dc_ResourceDB    resdb(GetResourceDB(),PI_Read);
  dc_ResourceDB    datdb(GetDBHandle(),PI_Write);
  logical          term  = NO;
  datdb.InitResourceDB_KE(&resdb);
  return(term);
}

/******************************************************************************/
/**
\brief  Link - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Link"

logical pKlasseditor :: Link ( )
{
  logical  term = NO;
BEGINSEQ
  if ( !project.IsPositioned() )                     ERROR

  SetupOutput("... start project link\n",YES);
  
  Pointer(POINTER_Wait);

  if ( project.ExecuteInstanceAction("GetLinkCommand",NULL) )
    SetupOutput("Error: providing link command\n",NO);
  else
  {
    ExecuteCommand(project.GetActionResult(),output,YES,NO);
    SetupOutput(NULL,NO);
  }                   

  Pointer(POINTER_Arrow);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProjectSelection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProjectSelection"

logical pKlasseditor :: ProjectSelection ( )
{
  CTX_Control  *context  = GetFieldContext("klasseditor.project_selection/class_tree.dropdown");
  char         *mninames = ActiveAction();
  logical       enable   = UNDEF;
  logical       term     = NO;
  enable = IsActionToggled(mninames);
  
  SetActionToggled(mninames,enable);
  SetSysVariable("PROJECT_SELECTION",enable ? "YES" : "NO");

  if ( context )
    context->FillControl();
  return(term);
}

/******************************************************************************/
/**
\brief  SetupProjectSelection - 



\return term - 

\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupProjectSelection"

logical pKlasseditor :: SetupProjectSelection (logical reset_opt )
{
  CTX_Control    *context = GetFieldContext("klasseditor.project_selection/class_tree.dropdown");
  PropertyHandle *ph      = context ? context->GetPropertyHandle() : NULL;
  logical         term    = NO;
  if ( ph )
  {
    if ( reset_opt )
    {
      ph->ToTop();
      context->FillControl();
    }
        
    PropertyHandle    key(project_name);
    ph->Get(key);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  pKlasseditor - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pKlasseditor"

     pKlasseditor :: pKlasseditor ( )
                     : pODE ()
{



}

/******************************************************************************/
/**
\brief  ~pKlasseditor - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pKlasseditor"

     pKlasseditor :: ~pKlasseditor ( )
{



}


