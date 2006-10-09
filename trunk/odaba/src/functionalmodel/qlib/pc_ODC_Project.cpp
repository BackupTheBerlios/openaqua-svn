/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_Project

\brief    


\date     $Date: 2006/07/12 19:09:33,90 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_Project"

#include  <pfmodel.h>
#include  <cSystemPathes.h>
#include  <spc_ODC_ImpClass.hpp>
#include  <spc_ODC_Main.hpp>
#include  <spc_ODC_Project.hpp>


/******************************************************************************/
/**
\brief  CreateCompAllUnix - 


\return term - 

\param  compreq - 
\param  nocomp_ignore - 
\param  result_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCompAllUnix"

logical pc_ODC_Project :: CreateCompAllUnix (CompileStates compreq, logical nocomp_ignore, NString *result_string )
{
  char        *sourcegen_root = GetSysVariable("SOURCEGEN_ROOT");
  char         area[60000];
  char         sections[4000];
  char         procpath[512];
  char         string[256];
  char         procstr[512];
  int32        indx0         = 0;
  logical      term          = NO;
  *procpath = 0;
  if ( sourcegen_root )
    strcpy(procpath,sourcegen_root);
  strcat(strcat(strcat(procpath,"/"),GetString("sys_ident")),"/bat/");
  
  pc_ODC_ImpClass  classes(GPH("classes"));  // 15.3.06: oder "proj_classes"
  PropertyHandle  *cls_sys_ident   = classes.GPH("sys_ident");
  PropertyHandle  *cls_no_compile  = classes.GPH("no_compile");
  PropertyHandle  *cls_req_compile = classes.GPH("req_compile");
  PropertyHandle  *cls_opt_debug   = classes.GPH("opt_debug");

  *area = 0;
  while ( classes.Get(indx0++) )
    if ( (nocomp_ignore || !cls_no_compile->GetInt())       &&
         (compreq == CPS_undefined || cls_req_compile->GetInt() == compreq) )
    {
      CreateCompLine3(procstr,cls_sys_ident->GetString(),cls_opt_debug->GetInt());
      strcat(area,procstr);
    }

  WriteBatchFile(area,procpath,"classes-prj",result_string);

  PH(this,main_functions)
  PropertyHandle  *fct_sys_ident   = main_functions.GPH("sys_ident");
  PropertyHandle  *fct_no_compile  = main_functions.GPH("no_compile");
  PropertyHandle  *fct_req_compile = main_functions.GPH("req_compile");
  PropertyHandle  *fct_opt_debug   = main_functions.GPH("opt_debug");
  PropertyHandle  *fct_dll_option  = main_functions.GPH("dll_option");
  
  indx0     = 0;
  *area     = 0;
  *sections = 0;
  while ( main_functions(indx0++) )
    if ( (nocomp_ignore || !fct_no_compile->GetInt()) &&
         (compreq == CPS_undefined || fct_req_compile->GetInt() == compreq) )
    {
      if ( !fct_dll_option->GetInt() )
      {
        CreateCompLine3(procstr,fct_sys_ident->GetString(),fct_opt_debug->GetInt());
        strcat(area,procstr);
      }
      CreateSection(procstr,main_functions);
      strcat(sections,procstr);
    }

  indx0 = 0;
  while ( classes.Get(indx0++) )
    if ( (nocomp_ignore || !cls_no_compile->GetInt()) &&
         (compreq == CPS_undefined || cls_req_compile->GetInt() == compreq) && 
         classes.IsIFClass()                                        )
    {
      CreateCompLine3(procstr,strcat(strcpy(string,"_if_"),cls_sys_ident->GetString()),NO);
      strcat(area,procstr);
      CreateSection_if(procstr,string);
      strcat(sections,procstr);
    }

  WriteBatchFile(area,procpath,"classes-exe",result_string);
  WriteBatchFile(sections,procpath,"binaries",result_string);
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCompAllWin - 


\return term - 

\param  compreq - 
\param  nocomp_ignore - 
\param  result_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCompAllWin"

logical pc_ODC_Project :: CreateCompAllWin (CompileStates compreq, logical nocomp_ignore, NString *result_string )
{
  NString         work_string;
  NString         nstring;
  NString         nstring_if;
  char            procstr[512];
  long int        indx0    = 0;
  logical         term     = NO;
  pc_ODC_ImpClass  classes(GPH("classes"));  // 15.3.06: oder "proj_classes"
  PropertyHandle  *cls_sys_ident   = classes.GPH("sys_ident");
  PropertyHandle  *cls_no_compile  = classes.GPH("no_compile");
  PropertyHandle  *cls_req_compile = classes.GPH("req_compile");
  
  while ( classes.Get(indx0++) )
    if ( (nocomp_ignore || !cls_no_compile->GetInt()) &&
         (compreq == CPS_undefined || cls_req_compile->GetInt() == compreq) )
    { 
      work_string = "";
      CreateCompLine2(procstr,classes.GetCompileCommand(work_string),cls_sys_ident->GetString());
      nstring += procstr;
      if ( classes.IsIFClass() )
        nstring_if += procstr;
    }
  
  WriteBatchFile(nstring,NULL,"compall.bat",result_string);
  WriteBatchFile(nstring_if,NULL,"comp_if.bat",result_string);

  pc_ODC_Main      main_functions(GPH("main_functions"));
  PropertyHandle  *fct_sys_ident   = main_functions.GPH("sys_ident");
  PropertyHandle  *fct_no_compile  = main_functions.GPH("no_compile");
  PropertyHandle  *fct_req_compile = main_functions.GPH("req_compile");
  
  nstring = "";
  indx0   = 0;
  while ( main_functions(indx0++) )
    if ( (nocomp_ignore || !fct_no_compile->GetInt()) &&
         (compreq == CPS_undefined || fct_req_compile->GetInt() == compreq) )
    {
      work_string = "";
      CreateCompLine2(procstr,main_functions.GetCompileCommand(work_string),fct_sys_ident->GetString());
      nstring += procstr;
    }
  
  WriteBatchFile(nstring,NULL,"compmains.bat",result_string);

  return(term);
}

/******************************************************************************/
/**
\brief  CreateCompLine - 



\param  procstr - 
\param  project_name - 
\param  storage_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCompLine"

void pc_ODC_Project :: CreateCompLine (char *procstr, char *project_name, char *storage_name )
{
  char       string[ID_SIZE+1];
  strcpy(procstr,"./compclass ");
  strcat(procstr,gvtxbts(string,project_name,ID_SIZE));
  strcat(procstr," ");
  strcat(procstr,gvtxbts(string,storage_name,ID_SIZE));
  strcat(procstr,"\n");


}

/******************************************************************************/
/**
\brief  CreateCompLine2 - 



\param  procstr - 
\param  cmdline - 
\param  obname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCompLine2"

void pc_ODC_Project :: CreateCompLine2 (char *procstr, char *cmdline, char *obname )
{
  char       string[ID_SIZE+1];
  if ( cmdline && *cmdline )
  {  
    strcpy(procstr,"call ");
    strcat(strcat(procstr,cmdline)," ");
    strcat(procstr,"YES");
    strcat(procstr,"\r\n");
  }
  else if ( obname && *obname > ' ' )
  {  
    strcpy(procstr,"rem ");
    strcat(procstr,gvtxbts(string,obname,ID_SIZE));
    strcat(procstr,"\r\n");
  }


}

/******************************************************************************/
/**
\brief  CreateCompLine3 - 



\param  procstr - 
\param  storage_name - 
\param  debug_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCompLine3"

void pc_ODC_Project :: CreateCompLine3 (char *procstr, char *storage_name, logical debug_opt )
{

  *procstr = 0;
  strcat(procstr,storage_name);
  if ( debug_opt )
  strcat(procstr," debug");
  strcat(procstr,"\n");


}

/******************************************************************************/
/**
\brief  CreateSection - 



\param  procstr - 
\param  exe_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSection"

void pc_ODC_Project :: CreateSection (char *procstr, PropertyHandle &exe_ph )
{
  char       bin_name[ID_SIZE+1];
BEGINSEQ
  if ( !exe_ph.Exist() )                             ERROR
    
  *procstr = 0;
  strcpy(bin_name,exe_ph.GetString("id8"));
  strcat(strcat(strcpy(procstr,"["),bin_name),"]\n");;
  
  strcat(procstr,"  type     = ");
  if ( !exe_ph.GetInt("dll_option") )
  {
    if ( exe_ph.GetInt("autolink") )
      strcat(procstr,"dynl\n");
    else
    {
      strcat(procstr,"exe\n");
      strcat(procstr,"  projects = . ");
// ggf sub-projects nachziehen
      strcat(procstr,"\n");
      
      strcat(procstr,"  classes  = ");
      strcat(procstr,bin_name);
      strcat(procstr,"\n");
    }
  }
  else
  {
    strcat(procstr,"lib\n");
    if ( exe_ph.GetInt("autolink") )
      strcat(strcat(strcat(procstr,"  aliases_dynl = "),bin_name),"\n");
// ggf sub-projects nachziehen
  }
      
  strcat(procstr,"\n");

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CreateSection_if - 



\param  procstr - 
\param  class_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSection_if"

void pc_ODC_Project :: CreateSection_if (char *procstr, char *class_names )
{
  char       bin_name[ID_SIZE+1];
  *procstr = 0;
  strcpy(bin_name,class_names);
  strcat(strcat(strcpy(procstr,"["),bin_name),"]\n");;
  
  strcat(procstr,"  type     = dynl\n");
  strcat(procstr,"\n");


}

/******************************************************************************/
/**
\brief  GetCompileCommand - 


\return command - 

\param  nstring - 
\param  praefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

char *pc_ODC_Project :: GetCompileCommand (NString &nstring, char *praefix )
{

  return ( pc_ODC_compile_object_base::GetCompileCommand(nstring,NO,NO,praefix) );

}

/******************************************************************************/
/**
\brief  GetDocFileName - 


\return ppath - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  nstring - 
\param  doc_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *pc_ODC_Project :: GetDocFileName (NString &nstring, char *doc_type )
{
  char        *extension   = ".hpp";
  char        *preafix     = NULL;
  if ( !strcmp(doc_type,"XSD") )
    extension = ".xsd";
  else if ( !strcmp(doc_type,"Expression") )
    extension = ".osi";
  else if ( !strcmp(doc_type,"SQL") )
    extension = ".sql";
  else if ( !strcmp(doc_type,"COM_Include") )
    extension = "COM.h";
  else if ( !strcmp(doc_type,"CS_Defines") )
    preafix = "_cs_def_";
  else if ( !strcmp(doc_type,"SC_Defines") )
    preafix = "_sc_def_";
  else if ( !strcmp(doc_type,"CS_Tables") )
    preafix = "_cs_tbl_";
  else if ( !strcmp(doc_type,"CS_Classes") )
    preafix = "_cs_ctbl_";
  else if ( !strcmp(doc_type,"SC_Tables") )
    preafix = "_sc_tbl_";
  else if ( !strcmp(doc_type,"SC_Classes") )
    preafix = "_sc_ctbl_";
  else if ( !strcmp(doc_type,"CS_Include") )
    preafix = "s_cs_";
  else if ( !strcmp(doc_type,"SC_Include") )
    preafix = "s_sc_";
  else if ( !strcmp(doc_type,"CI_Include") )
  {
    preafix   = "ci_";
    extension = ".h";
  }
  else 
  {
    extension   = ".cpp";
    
    if ( !strcmp(doc_type,"SC_Source") )
      preafix   = "_sc_";
    if ( !strcmp(doc_type,"CS_Source") )
      preafix   = "_cs_";
    else if ( !strcmp(doc_type,"CI_Source") )
      preafix   = "ci_";
    else if ( !strcmp(doc_type,"C_Stub") )
      extension = "_CStub.cpp";
    else if ( !strcmp(doc_type,"PL_Interface") )
      extension = ".package.sql";
  }
  
  if ( preafix )
    nstring += preafix;
  nstring += GPH("sys_ident")->GetString();
  nstring += extension;

  return(nstring);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  ppath - 
\param  folder_type - 
\param  max_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *pc_ODC_Project :: GetDocFileName (char *ppath, char *folder_type, int max_len )
{
  NString      nstring;
BEGINSEQ
  if ( !GetProjectPath(nstring,folder_type) )        ERROR
  
  nstring.Copy(ppath,max_len);

RECOVER
  if ( ppath )
    *ppath = 0;
ENDSEQ
  if (ppath) return ppath;
  else return "";
}

/******************************************************************************/
/**
\brief  GetLinkCommand - 


\return command - 

\param  nstring - 
\param  debug_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLinkCommand"

char *pc_ODC_Project :: GetLinkCommand (NString &nstring, logical debug_opt )
{
  PropertyHandle  *project      = NULL;
  PropertyHandle  *environment  = NULL;
  logical          is_project   = NO;

BEGINSEQ
  nstring = "";
  if ( !IsPositioned() )                             ERROR

  is_project = !strcmp(GetCurrentType(),"ODC_Project") ? YES : NO;
  project    = is_project ? this : GetProject();

  pc_ODC_Project    project_pc(project);
  if ( !project_pc.IsValid() )                       SDBERR(99)

// L:/ops/bat/
  project_pc.GetProjectPath(nstring,"ERC_Batch");
  
  if ( debug_opt )  
    nstring += 'D';
  
// L:/ops/bat/d[s7] 
  environment = project_pc.GPH("environment");
  if ( !environment->Get(FIRST_INSTANCE) )           ERROR
  nstring += environment->GPH("sys_ident")->GetString();
  
  nstring += "link";
  nstring += ".BAT";
RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetProjectPath - 


\return ppath - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  nstring - 
\param  folder_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *pc_ODC_Project :: GetProjectPath (NString &nstring, char *folder_type )
{
  PropertyHandle   *path_names = GPH("path_names");
  char              proj_root[256];
  char              proj_folder[256];
  char             *folder     = NULL;
  int32             indx0      = AUTO;

BEGINSEQ
  nstring  = GPH("proj_path")->GetString();
  nstring += "/";

  if ( (indx0 = GetProjectPathIndex(folder_type)) == ERIC )
                                                    LEAVESEQ
  if ( indx0 == AUTO )
  {
    if ( GetLastFolderInfo(nstring,proj_root,proj_folder,sizeof(proj_root),sizeof(proj_folder)) )
      nstring = proj_root;  
  }
  else if ( (folder = (char *)path_names->Get(indx0).GetData()) && *folder > ' ' )
  {
    nstring += path_names->GetString();
    nstring += "/";
  }

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  ppath - 
\param  folder_type - 
\param  max_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *pc_ODC_Project :: GetProjectPath (char *ppath, char *folder_type, int max_len )
{
  NString      nstring;
BEGINSEQ
  if ( !GetProjectPath(nstring,folder_type) )        ERROR
  
  nstring.Copy(ppath,max_len);

RECOVER
  if ( ppath )
    *ppath = 0;
ENDSEQ
  if (ppath) return ppath; 
  else return "";
}

/******************************************************************************/
/**
\brief  GetProjectPathIndex - 


\return folder_index - 

\param  folder_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPathIndex"

int32 pc_ODC_Project :: GetProjectPathIndex (char *folder_type )
{
  int32   indx0      = ERIC;

  if ( folder_type )
  {
    if ( !strcmp(folder_type,"ERC_Source") )
      indx0 = SP_SOURCE;          
    else if ( !strcmp(folder_type,"ERC_Include") )
      indx0 = SP_INCLUDE;
    else if ( !strcmp(folder_type,"ERC_Library") )
      indx0 = SP_LIB;
    else if ( !strcmp(folder_type,"ERC_Executable") )
      indx0 = SP_EXE;
    else if ( !strcmp(folder_type,"ERC_Document") )
      indx0 = SP_DOC;
    else if ( !strcmp(folder_type,"ERC_Batch") )
      indx0 = SP_BAT;
    else if ( !strcmp(folder_type,"ERC_Temp") )
      indx0 = SP_TEMP;
    else if ( !strcmp(folder_type,"ERC_Test") )
      indx0 = SP_USER1;
    else if ( !strcmp(folder_type,"ERC_Template") )
      indx0 = SP_USER2;
    else if ( !strcmp(folder_type,"ERC_Root") )
      indx0 = AUTO;
  }
  return(indx0);
}

/******************************************************************************/
/**
\brief  InitializeExternalResources - 


\return term - 

\param  error_string - 
\param  folder_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeExternalResources"

logical pc_ODC_Project :: InitializeExternalResources (NString *error_string, logical folder_opt )
{
  PropertyHandle  *sys_ident     = GPH("sys_ident");
  PropertyHandle  *proj_path     = GPH("proj_path");
  PropertyHandle  *resource_base = GPH("resource_base");
  char            *cpath         = NULL;
  char             string[1024];
  char             fname[128];
  char             fext[32];
  logical          term          = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR

  *fname = 0;
  *fext  = 0;

  if ( !(cpath = GetDBHandle().GetPath()) )
    error_string->Append("\nDatabase path could not be evaluated");
  else if ( !GetFileNameInfo(cpath,fname,fext,sizeof(fname),sizeof(fext)) )
    error_string->Append("\nDatabase directory path could not be evaluated");

  if ( resource_base->IsEmpty() && *fname )
    *resource_base = strcat(strcat(strcpy(string,fname),"."),fext);
  
  if ( proj_path->IsEmpty() && cpath )
  {
    if ( !GetDirectoryPathInfo(cpath,string,sizeof(string)) )
      error_string->Append("\nDatabase directory path could not be evaluated");
    else
    {
      if ( *sys_ident != fname )
        strcat(string,sys_ident->GetString());
      *proj_path = string;
    }
  }

  if ( folder_opt )
  {  
    InitializeFolder(error_string,"ERC_Batch"     ,"BAT");          
    InitializeFolder(error_string,"ERC_Source"    ,"QLIB");          
    InitializeFolder(error_string,"ERC_Include"   ,"H");          
    InitializeFolder(error_string,"ERC_Library"   ,"LIB");          
    InitializeFolder(error_string,"ERC_Executable","EXE");          
    InitializeFolder(error_string,"ERC_Document"  ,"DOC");          
    InitializeFolder(error_string,"ERC_Temp"      ,"TEMP");          
    InitializeFolder(error_string,"ERC_Test"      ,"TST");          
    InitializeFolder(error_string,"ERC_Template"  ,"TPL");          
  }
  
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeFolder - 


\return term - 

\param  error_string - 
\param  folder_type - 
\param  init_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeFolder"

logical pc_ODC_Project :: InitializeFolder (NString *error_string, char *folder_type, char *init_string )
{
  PropertyHandle  *path_names = GPH("path_names");
  NString          nstring;
  char            *dpath      = NULL;
  char            *folder     = NULL;
  int32            indx0      = GetProjectPathIndex(folder_type);
  logical          term       = NO;
BEGINSEQ
  if ( indx0 < 0 || !(folder = (char *)path_names->Get(indx0).GetData()) ) 
  {
    error_string->Append("\nPath for folder type '");
    error_string->Append(folder_type);
    error_string->Append("' could not be located in current project");
  }
  else
  {
    if ( *folder <= ' ' )
    {
      if ( !init_string )
      {
       error_string->Append("\nFolder name for type '");
       error_string->Append(folder_type);
       error_string->Append("' is missing");
      }
      else
        *path_names = init_string;
    }
    
    dpath = GetProjectPath(nstring,folder_type);
    if ( IsDirectory(dpath) )                       LEAVESEQ
    
    if ( MakePathDirectories(dpath) )
      error_string->Append("\nError making directories for folder path '");
    else
      error_string->Append("\nCreated directories for folder path '");
    error_string->Append(dpath);
    error_string->Append("'");
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCompile - 



\param  compreq - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompile"

void pc_ODC_Project :: SetCompile (CompileStates compreq )
{
  PropertyHandle   *req_compile = GPH("req_compile");
  if ( !NoWrite() && req_compile->GetInt() != CPS_requested )
  {
    *req_compile = (int32)compreq; 
    Save();
    SDBRESET
  }


}

/******************************************************************************/
/**
\brief  SetGenInc - 



\param  genincl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenInc"

void pc_ODC_Project :: SetGenInc (logical genincl )
{
  PropertyHandle   *req_genincl = GPH("req_genincl");
  if ( !NoWrite() && req_genincl->GetInt() != genincl )
  {
    *GPH("req_genincl") = genincl; 
    Save();
    SDBRESET
  }


}

/******************************************************************************/
/**
\brief  SetupReferences - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReferences"

logical pc_ODC_Project :: SetupReferences ( )
{
  int32             indx0   = 0;
  logical           term    = NO;
BEGINSEQ
  if ( !IsPositioned() )                      ERROR
  
  pc_ODC_ImpClass   classes(GPH("classes")); 
  while ( classes.Get(indx0++) )
    if ( classes.SetupReferences() )
      term = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WriteBatchFile - 


\return term - 

\param  area - 
\param  path - 
\param  filnames - 
\param  result_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteBatchFile"

logical pc_ODC_Project :: WriteBatchFile (char *area, char *path, char *filnames, NString *result_string )
{
  NString         nstring;
  char            procstr[512];
  logical         term    = NO;
  if ( !path )
    path = GetProjectPath(nstring,"ERC_Batch");
    
  strcat(strcpy(procstr,path),filnames);
  
  if ( result_string )
  {
    result_string->Append("  ",UNDEF);
    result_string->Append(procstr,UNDEF);
    result_string->Append("\n",UNDEF);
  }
  
  FileWrite(procstr,area,strlen(area));

  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_Project - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_Project"

     pc_ODC_Project :: pc_ODC_Project (PropertyHandle *prophdl )
                     : pc_ODC_compile_object_base (prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_Project"

     pc_ODC_Project :: pc_ODC_Project (DatabaseHandle &dbhandle )
                     : pc_ODC_compile_object_base (dbhandle,"ODC_Project")
{



}


