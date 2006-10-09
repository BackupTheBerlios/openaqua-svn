/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pODE

\brief    


\date     $Date: 2006/08/28 07:56:31,54 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pODE"

#include  <pdesign.h>
#include  <cProjectImplementationType.h>
#include  <sErrorMessage.hpp>
#include  <sPropertyHandle.hpp>
#include  <sdc_ResourceDB.hpp>
#include  <ifil.h>
#include  <igvts.h>
#include  <spc1_ODC_PFunction.hpp>
#include  <spODE.hpp>


/******************************************************************************/
/**
\brief  ChangeLanguage - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeLanguage"

int8 pODE :: ChangeLanguage ( )
{
  char      *mninames = ActiveActionItem();
BEGINSEQ
  if ( !mninames )                                   LEAVESEQ
     
  SetSysVariable("DSC_Language",mninames);

  if ( *language )
    SetActionToggled("ChangeLanguage",YES,language);
  SetActionToggled("ChangeLanguage",YES,mninames);
  strcpy(language,mninames);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DeselectProject - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeselectProject"

void pODE :: DeselectProject ( )
{

  implemented = NO;

  DeinitRefProjects();
  project.ToTop();

  SetSysVariable("DEF_PATH",""); 
  SetSysVariable("DEF_STRUCT",""); 
  SetSysVariable("DEF_CODESET",""); 

  memset(project_name,0,sizeof(project_name));
  
  
  


}

/******************************************************************************/
/**
\brief  DistributeSearchReplace - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DistributeSearchReplace"

logical pODE :: DistributeSearchReplace ( )
{

  return ( DistributeSearchReplace(GetCurSearchReplace()) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  ode_search_replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DistributeSearchReplace"

logical pODE :: DistributeSearchReplace (ODE_SearchReplace *ode_search_replace )
{
  CTX_Control     *context = NULL;
  logical          term    = NO;
BEGINSEQ
  if ( !ode_search_replace )                         P_ERR(99)
    
  switch ( ode_search_replace->GetLocation() )
  {
    case 1  : // FSR_Implementation
    case 2  : // FSR_Function
    case 3  : // FSR_Class
      
      if ( !(context = GetImpClassContext()) )       P_ERR(99)
      context->ExecuteFunction("DistributeSearchReplace");
      break;
    
    case 4  :  // FSR_Project
    
      ExecuteFunction("ExecSearchReplace");
      break;
    
    default : ;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterHandleActivated - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleActivated"

int8 pODE :: DoAfterHandleActivated ( )
{
  DatabaseHandle    dbhandle = GetDBHandle();
  NString           nstring;
  char             *prj_name = project_name;
  char              fname[ID_SIZE+1];
  char              fext[ID_SIZE+1];
  logical           auto_ini = UNDEF;
  if ( db_handle != dbhandle )
  {
    db_handle = dbhandle;
    
    OpenPHs(project_name,PI_Update);
    if ( !project.GetCount() )
    {
      if ( auto_ini = ODEOptionIsOn(this,"AutoInitialize") )
        ExecuteFunction("InitResourceDB");

      if ( *prj_name <= ' ' )
        prj_name = GetOption("CurrentProject");
      if ( !prj_name || *prj_name <= ' ' )
        prj_name = GetFileNameInfo(db_handle.GetPath(),fname,fext,sizeof(fname),sizeof(fext));
      project.NewProject(this,prj_name,auto_ini,nstring);
    }
    
    ODE_Helper::Initialize(this);
    
    InitOptions(); 
  }

  search_replace.Init(GetRESDictionary());
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 pODE :: DoAfterOpen ( )
{
  char         *option;
  if ( !*(option = GetOption("DocumentationLanguage")) )
    option = GetSysVariable("DSC_Language");
  if ( !option || !*option )
    option = "English";
  SetSysVariable("DSC_Language",strcpy(language,option));
  SetActionToggled("ChangeLanguage",YES,language);

  option = GetOption("OnlineDocumentation");
  docu_enabled = *option == 'Y' || *option == 'y' ? YES : NO;
  SetActionToggled("Documentation",docu_enabled);

  if ( option = GetOption("CurrentProject") )
    strncpy(project_name,option,ID_SIZE);

  SetSysVariable("ClassDevelopment","YES"); // for creating head lines

  strcpy(application_name,"ODE");

  return(NO);
}

/******************************************************************************/
/**
\brief  DoBeforeClose - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

int8 pODE :: DoBeforeClose ( )
{

  SelectProject(NULL);
  
  ClosePHs();
  db_handle = DatabaseHandle();

  search_replace.Deinit();
  return(NO);
}

/******************************************************************************/
/**
\brief  Documentation - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Documentation"

logical pODE :: Documentation ( )
{


  EnableDocumentation(!docu_enabled);

  return(NO);
}

/******************************************************************************/
/**
\brief  EnableDocumentation - 



\return enable_opt - 

\param  enable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableDocumentation"

logical pODE :: EnableDocumentation (logical enable_opt )
{
  logical  enabled = docu_enabled;
BEGINSEQ
  if ( docu_enabled == enable_opt )                             LEAVESEQ

  if ( docu_enabled && docu_ctx )
    docu_ctx->SetPropertyHandle(NULL);

  docu_enabled = enable_opt;
  SetActionToggled(ActiveAction(),docu_enabled);
ENDSEQ
  return(enabled);
}

/******************************************************************************/
/**
\brief  EnableInputHelp - 



\return term - 

\param  enable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableInputHelp"

logical pODE :: EnableInputHelp (logical enable_opt )
{
  CTX_Control  *context  = GetImpClassContext();
  char         *mninames = ActiveAction();
  logical       enable = enable_opt;
  logical       term = NO;
  if ( enable != YES && enable != NO )
    enable = IsActionToggled(mninames);
   
  SetActionToggled(mninames,enable);

  if ( context )
  {
    context->SetParm(enable ? "YES" : "NO");
    context->ExecuteFunction("InputHelp");
  }
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

logical pODE :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("ChangeLanguage",ALINK(this,pODE,ChangeLanguage)),
                           cfte("DistributeSearchReplace",ALINK(this,pODE,DistributeSearchReplace)),
                           cfte("Documentation",ALINK(this,pODE,Documentation)),
                           cfte("Find",ALINK(this,pODE,Find)),
                           cfte("GenerateSystemInclude",ALINK(this,pODE,GenerateSystemInclude)),
                           cfte("GetProjectName",ALINK(this,pODE,GetProjectName)),
                           cfte("GetProjectPath",ALINK(this,pODE,GetProjectPath)),
                           cfte("InputHelp",ALINK(this,pODE,InputHelp)),
                           cfte("IsODEContext",ALINK(this,pODE,IsODEContext)),
                           cfte("NewProject",ALINK(this,pODE,NewProject)),
                           cfte("ProvideNewError",ALINK(this,pODE,ProvideNewError)),
                           cfte("ProvideReferencedType",ALINK(this,pODE,ProvideReferencedType)),
                           cfte("ProvideType",ALINK(this,pODE,ProvideType)),
                           cfte("ReleaseProject",ALINK(this,pODE,ReleaseProject)),
                           cfte("Replace",ALINK(this,pODE,Replace)),
                           cfte("ReserveProject",ALINK(this,pODE,ReserveProject)),
                           cfte("ResetCache",ALINK(this,pODE,ResetCache)),
                           cfte("SetupOutput",ALINK(this,pODE,SetupOutput)),
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
    term = CTX_Project::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Find - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

logical pODE :: Find ( )
{

  return ( SearchReplace(NO) );

}

/******************************************************************************/
/**
\brief  GenerateSystemInclude - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSystemInclude"

logical pODE :: GenerateSystemInclude ( )
{
  NString   path    = GetOption("DEF_PATH");
  NString   str_def = GetOption("DEF_STRUCT");
  NString   cs_def  = GetOption("DEF_CODESET");
  logical   term    = NO;
BEGINSEQ
  if ( !project.IsPositioned() )                     ERROR
  
  if ( path.IsEmpty() ) 
  {
    path  = ProjectPath("ERC_Include");
    path += "/csysstr.h";
  }
  if ( str_def.IsEmpty() )
  {
    str_def  = ProjectName();
    str_def += "-SysStruct";
  }
  if ( cs_def.IsEmpty() )
  {
    cs_def  = ProjectName();
    cs_def += "-SysCS";
  }

  SetSysVariable("DEF_PATH",path); 
  SetSysVariable("DEF_STRUCT",str_def); 
  SetSysVariable("DEF_CODESET",cs_def); 
  
  if ( ExecuteWindow(NULL,"VOID","PARMS_SysTypes_Include",NO) )
                                                     ERROR
  Pointer(POINTER_Wait);
  
  output = "...generating system type include ";
  output += GetSysVariable("DEF_PATH");
  output += " \n";
  DisplayOutput();
  
  if ( !project.ExecuteExpression(GetRESDB(),"SysTypes_Include()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  else
    SetupOutput("...  terminated successfully\n",NO);

  Pointer(POINTER_Arrow);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCurSearchReplace - 



\return ode_search_replace - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurSearchReplace"

ODE_SearchReplace *pODE :: GetCurSearchReplace ( )
{

  return ( this ? cur_search_replace : NULL );

}

/******************************************************************************/
/**
\brief  GetImpClassContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImpClassContext"

CTX_Control *pODE :: GetImpClassContext ( )
{

  return(imp_class_ctx);


}

/******************************************************************************/
/**
\brief  GetOption - 



\return option - 

\param  option_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOption"

char *pODE :: GetOption (char *option_name )
{
  char            *option = "";
BEGINSEQ
  if ( !this )                                      ERROR

  if ( !(option = GetSectionVariable(option_name,"Options")) )
    if ( !(option = GetSysVariable(option_name)) )
      option = "";
RECOVER

ENDSEQ
  return(option);
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

char *pODE :: GetOptionState (char *option_name )
{
  char            *option = NULL;
  if ( !strcmp(option_name,"DocumentationLanguage") )
    option = GetSysVariable("DSC_Language");
  else if ( !strcmp(option_name,"OnlineDocumentation") )
    option = IsActionToggled("Documentation") ? "YES" : "NO";
  else if ( !strcmp(option_name,"CurrentProject") )
    option = project_name;
  else
    option = GetOption(option_name);
  return(option);
}

/******************************************************************************/
/**
\brief  GetProjectName - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectName"

logical pODE :: GetProjectName ( )
{

  SetResult(project_name);

  return(*project_name ? NO : YES);
}

/******************************************************************************/
/**
\brief  GetProjectPath - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

logical pODE :: GetProjectPath ( )
{
  char     *proj_path = ProjectPath(Parm(1));
  logical   term      = NO;
BEGINSEQ
  if ( !proj_path || !*proj_path )                   ERROR
  
  SetResult(proj_path);

RECOVER
  SetResult("");
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitOptions - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitOptions"

void pODE :: InitOptions ( )
{
  char       *option = NULL;

  if ( !(option = GetOption("DefaultMethodType")) )
    option = "MT_CPPFunction";
  SetSysVariable("DefaultMethodType",option);


}

/******************************************************************************/
/**
\brief  InitializePFunction - 



\return cond - 

\param  pfunct_pc - 
\param  type_key - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializePFunction"

logical pODE :: InitializePFunction (pc1_ODC_PFunction *pfunct_pc, TypeKey &type_key, logical recursive )
{
  ODE_Project     *odeprj = NULL;
  int32            indx0  = 0;
  logical          cond   = YES;
BEGINSEQ
  if ( ODE_Project::InitializePFunction(pfunct_pc,type_key,recursive ? this : NULL) )
                                                     LEAVESEQ
  InitRefProjects();
  while ( odeprj = ref_projects->GetEntry(++indx0) )
    if ( odeprj->InitializePFunction(pfunct_pc,type_key,recursive ? this : NULL) )
                                                     LEAVESEQ
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  InputHelp - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputHelp"

logical pODE :: InputHelp ( )
{

  return( EnableInputHelp(AUTO) );
   


}

/******************************************************************************/
/**
\brief  IsODEContext - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsODEContext"

logical pODE :: IsODEContext ( )
{

  SetResult("YES");

  return(NO);
}

/******************************************************************************/
/**
\brief  NewProject - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewProject"

logical pODE :: NewProject ( )
{
  char                      *parm        = Parm(1);
  char                      *new_project = NULL;
  NString                    nstring;
  logical                    term        = NO;
BEGINSEQ
  if ( !(new_project = GetString("New Project","Project name",parm)) )
                                                    LEAVESEQ
  DeselectProject();

  nstring.Append(' ',2);
  nstring += new_project;
  nstring += "...Provide new project and initializing external resources - folder and procedures\n";
  ODEOutput(this,nstring,YES);
  nstring = "";

  project.NewProject(this,new_project,ODEOptionIsOn(this,"AutoInitialize"),nstring);
  ODEOutput(this,nstring,NO);
  
  SelectProject(new_project);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProjectContextClass - 



\return proj_ctx - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProjectContextClass"

char *pODE :: ProjectContextClass ( )
{
  PropertyHandle   *imp_classes = project.GPH("classes");
  static   char     proj_ctx[ID_SIZE+1];
  logical           term = NO;
BEGINSEQ
  memset(proj_ctx,0,sizeof(proj_ctx));
  
  if ( !project.IsPositioned() )                     ERROR
  
  strcpy(proj_ctx,"Context");
  PropertyHandle phproj_ctx_Context(proj_ctx);
  if ( imp_classes->Get(phproj_ctx_Context) )               LEAVESEQ
    
  strcpy(proj_ctx,"UCTXDesignerInterface");
  PropertyHandle phproj_ctx_UCTXDesignerInterface(proj_ctx);
  if ( imp_classes->Get(phproj_ctx_UCTXDesignerInterface) )
                                                    LEAVESEQ
         
  strcat(strcpy(proj_ctx,"CTX"),ProjectName());
  PropertyHandle phproj_ctx_CTXProject(proj_ctx);
  if ( imp_classes->Get(phproj_ctx_CTXProject) )    LEAVESEQ
         
  memset(proj_ctx,0,sizeof(proj_ctx));

RECOVER

ENDSEQ
  return(proj_ctx);
}

/******************************************************************************/
/**
\brief  ProjectName - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProjectName"

char *pODE :: ProjectName ( )
{

  return ( this && *project_name ? project_name : NULL );

}

/******************************************************************************/
/**
\brief  ProjectPath - 



\return string - 

\param  folder_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProjectPath"

char *pODE :: ProjectPath (char *folder_type )
{
  static   char  proj_path[1025];
  logical        term = NO;
BEGINSEQ
  memset(proj_path,0,sizeof(proj_path));
  
  if ( !project.IsPositioned() )                     ERROR
  
  if ( project.ExecuteInstanceAction("GetProjectPath",folder_type) )
                                                     ERROR
  strncpy(proj_path,project.GetActionResult(),sizeof(proj_path)-1);
RECOVER

ENDSEQ
  return(proj_path);
}

/******************************************************************************/
/**
\brief  ProvideNewError - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideNewError"

logical pODE :: ProvideNewError ( )
{
  PropertyHandle    *error_class  = NULL;
  PropertyHandle    *class_errors = NULL;
  PropertyHandle    *errors       = NULL;
  int32              newkey       = 1;
  char               string[13];
  logical            term         = NO;
BEGINSEQ
  if ( !project.IsPositioned() )                     ERROR
  error_class  = project.GPH("error_class");
  errors       = project.GPH("errors");
  class_errors = error_class->GPH("errors");

  if ( !error_class->Get(FIRST_INSTANCE) )           P_ERR(99)

  if ( class_errors->Get(LAST_INSTANCE) )
    newkey = class_errors->GPH("_errnum")->GetInt()+1;
  //itoa(newkey,string,10);
  sprintf (string, "%d", newkey) ;
  PropertyHandle phstring(string);
  errors->Add(phstring);               P_SDBCERR
  SetResult(string);
RECOVER
  SetResult("*ERROR*");
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideReferencedType - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideReferencedType"

logical pODE :: ProvideReferencedType ( )
{
  TypeKey      type_key(dictionary,Parm(1));
  return ( ProvideType(type_key,YES) );

}

/******************************************************************************/
/**
\brief  ProvideType - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideType"

logical pODE :: ProvideType ( )
{
  TypeKey      type_key(dictionary,Parm(1));
  return ( ProvideType(type_key,NO) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  type_key - 
\param  no_struct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideType"

logical pODE :: ProvideType (TypeKey &type_key, logical no_struct )
{
  ODE_Project     *odeprj = NULL;
  int32            indx0  = 0;
  logical          term   = NO;
BEGINSEQ
  if ( GetRESDictionary().BaseType(type_key.Name())) LEAVESEQ
  
  if ( !ODE_Project::ProvideType(type_key,NULL,NULL,no_struct,this) )
                                                     LEAVESEQ
  InitRefProjects();
  if ( !impclasses.CheckReferencedClass(type_key,ref_projects,this) )
                                                     LEAVESEQ
  while ( odeprj = ref_projects->GetEntry(++indx0) )
    if ( !odeprj->ProvideType(type_key,&impclasses,&enums,no_struct,this) )  
                                                     LEAVESEQ
  
  PropertyHandle  newtype(GetRESDictionary(),"FORM_new_ODE_TypeRef");
                                                     P_SDBCERR
  *newtype.GPH("type_name") = type_key.Name();
  *newtype.GPH("project")   = project_name;
  *newtype.GPH("impltype")  = "IT_Class";
  *newtype.GPH("prg_lang")  = "PL_CPP";
  
  while ( !ExecuteWindow(&newtype,"FORM_new_ODE_TypeRef","Edit",NO) )
  {
    switch ( newtype.GPH("impltype")->GetInt() )
    {
      case 1   : // IT_Structure 
                 if ( no_struct )                    ERROR
                 structures.Add(type_key);           P_SDBCERR
                 LEAVESEQ
      
      case 2   : // IT_Class
                 if ( impclasses.CreateReferencedClass(&newtype) )
                                                     ERROR
                 LEAVESEQ
      
      case 3   : // IT_Enumeration 
                 enums.Add(type_key);                P_SDBCERR
                 LEAVESEQ
      
      default  : ERROR
    }
  }

  ERROR

RECOVER
  term = YES;
ENDSEQ
  impclasses.ToTop();
  structures.ToTop();
  enums.ToTop();
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseProject - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProject"

logical pODE :: ReleaseProject ( )
{

BEGINSEQ
  if ( !this )                                       ERROR
  project.Unlock();
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  Replace - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

logical pODE :: Replace ( )
{

  return ( SearchReplace(NO) );

}

/******************************************************************************/
/**
\brief  ReserveProject - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveProject"

logical pODE :: ReserveProject ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( project.Lock() )                              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetCache - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCache"

logical pODE :: ResetCache ( )
{

  return( InvalidateResourceCache() );

}

/******************************************************************************/
/**
\brief  SearchReplace - 



\return term - 

\param  do_replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchReplace"

logical pODE :: SearchReplace (logical do_replace )
{
  logical          term    = NO;
BEGINSEQ
  SetupOutput(do_replace ? "Find" : "Replace",YES);
  
  if ( search_replace.GetData("FSR_Project",do_replace,this) )
                                                     ERROR  
  SetCurSearchReplace(&search_replace);
  term = DistributeSearchReplace(&search_replace);
  SetCurSearchReplace(NULL);

  SetupOutput(" reached starting point of the search\n",NO);

RECOVER
  SetupOutput(" terminated with error\n",NO);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SelectProject - 



\return term - 

\param  prj_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectProject"

logical pODE :: SelectProject (char *prj_name )
{
  PropertyHandle  name_ph("");
  logical         term = NO;
BEGINSEQ
  if ( prj_name )
  {
    if ( !strcmp(project_name,prj_name) )           LEAVESEQ 
    name_ph = *prj_name ? prj_name : project_name;
  }

  DeselectProject();
  if ( !prj_name )                                  LEAVESEQ
  
  strncpy(project_name,name_ph.GetString(),ID_SIZE);

  if ( !project.Get(name_ph) )
    term = YES;
  else
  {
    implemented = project.IsImplemented(NO);
    SetupProjectSelection(YES);                // ev. ist YES zuviel
  }

  SetApplicationTitle(NULL,NULL,NULL);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetApplicationTitle - 




\param  appl_name - 
\param  prj_name - 
\param  selected_object - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetApplicationTitle"

void pODE :: SetApplicationTitle (char *appl_name, char *prj_name, char *selected_object )
{
  NString            title;
  if ( !appl_name || !*appl_name )
    appl_name = application_name;
  title.Append(appl_name,ID_SIZE);
  
  if ( !prj_name || !*prj_name ) 
    prj_name = project_name;
  if ( prj_name && *prj_name ) 
  {
    title += " -";
    title += ' ';
    title.Append(prj_name,ID_SIZE); 
  }
   
  if ( selected_object && *selected_object )  
  {
    title += " [";
    title += selected_object;
    title += ']';
  }
  
  SetTitle(title);

}

/******************************************************************************/
/**
\brief  SetCurSearchReplace - 



\return term - 

\param  ode_search_replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurSearchReplace"

logical pODE :: SetCurSearchReplace (ODE_SearchReplace *ode_search_replace )
{
  logical   term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  cur_search_replace = ode_search_replace;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDocumentContext - 



\return term - 

\param  ctx_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDocumentContext"

logical pODE :: SetDocumentContext (CTX_Control *ctx_ptr )
{
  logical           term = NO;
  docu_ctx = ctx_ptr;
  return(term);
}

/******************************************************************************/
/**
\brief  SetDocumentPH - 




\param  doc_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDocumentPH"

void pODE :: SetDocumentPH (PropertyHandle *doc_ph )
{
  PropertyHandle         *topic;
  NString                 title;
  if ( docu_ctx && docu_enabled )
  {
    title = doc_ph->GetCurrentType();
    title += " - Documentation";
    docu_ctx->SetTitle(title);
    if ( doc_ph = doc_ph->GPH("resource_ref") )
    {
      if ( !doc_ph->Get(FIRST_INSTANCE) )
        doc_ph->GetInitInstance();
      topic = doc_ph->GPH("description");
      if ( !topic->Get(FIRST_INSTANCE) )
        topic->GetInitInstance();
      docu_ctx->SetPropertyHandle(doc_ph);
    }
  }

}

/******************************************************************************/
/**
\brief  SetImpClassContext - 




\param  control_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetImpClassContext"

void pODE :: SetImpClassContext (CTX_Control *control_ctx )
{

  imp_class_ctx = control_ctx;

}

/******************************************************************************/
/**
\brief  SetupOutput - 



\return term - 

\param  string - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupOutput"

logical pODE :: SetupOutput (char *string, logical clear_opt )
{

  return ( OutputArea::SetupOutput(string,clear_opt) );

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

logical pODE :: SetupProjectSelection (logical reset_opt )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ShowMessage - 



\return term - 

\param  pError - 
\param  err_message - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical pODE :: ShowMessage (Error *pError, ErrorMessage *err_message )
{
  NString         string;
  if ( !err_message )
    string = "Error";
  else
  {
    string.Append(err_message->component,sizeof(err_message->component));
    string += ' ';
    string.Append(err_message->error_type,sizeof(err_message->error_type));
    string += ' ';
    string.Append(err_message->error_code,sizeof(err_message->error_code));
    string += ':';
    string += ' ';
    if ( !pError )
      string.Append(err_message->text,sizeof(err_message->text));
  }
  MessageOutput(string,pError);
  return(NO);
}

/******************************************************************************/
/**
\brief  ShowProtocol - 



\return term - 

\param  pError - 
\param  err_message - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowProtocol"

logical pODE :: ShowProtocol (Error *pError, ErrorMessage *err_message )
{

  MessageOutput("Message: ",pError);

  return( NO );
}

/******************************************************************************/
/**
\brief  pODE - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pODE"

     pODE :: pODE ( )
                     : CTX_Project (),
ODE_Project (),
  docu_enabled(YES),
  docu_ctx(NULL),
  search_replace(),
  cur_search_replace(NULL),
  imp_class_ctx(NULL)

{

  memset(language,0,sizeof(language));

}

/******************************************************************************/
/**
\brief  ~pODE - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pODE"

     pODE :: ~pODE ( )
{



}


