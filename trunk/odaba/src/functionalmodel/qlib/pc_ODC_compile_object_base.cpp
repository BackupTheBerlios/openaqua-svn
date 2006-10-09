/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_compile_object_base

\brief    


\date     $Date: 2006/07/17 13:32:06,75 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_compile_object_base"

#include  <pfmodel.h>
#include  <sODC_ImpClass.hpp>
#include  <ifmi.h>
#include  <spc_ODC_Project.hpp>
#include  <spc_SDB_TypeRef_fm.hpp>
#include  <spc_ODC_compile_object_base.hpp>


/******************************************************************************/
/**
\brief  GetCompileCommand - 



\return string - 

\param  nstring - 
\param  main_opt - 
\param  if_opt - 
\param  preafix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

char *pc_ODC_compile_object_base :: GetCompileCommand (NString &nstring, logical main_opt, logical if_opt, char *preafix )
{
  PropertyHandle  *project      = NULL;
  PropertyHandle  *environment  = NULL;
  ProgramLanguage  opt_language = PL_CPP;
  NString          ext;
  logical          is_project   = NO;
  NString          compile_object;

BEGINSEQ
  nstring = "";

  if ( !(project = GetProject()) )                   ERROR

  compile_object  = (char*)(preafix ? preafix : "");
  compile_object += GPH("sys_ident")->GetString();

  pc_ODC_Project    project_pc(project);
  if ( !project_pc.IsValid() )                       SDBERR(99)

// L:/ops/bat/
  project_pc.GetProjectPath(nstring,"ERC_Batch");
  
// L:/ops/bat/[d] 
  if ( !is_project || GPH("opt_debug")->GetInt() )
    nstring += 'D';
  
// L:/ops/bat/d[s7] 
  environment = project_pc.GPH("environment");
  if ( !environment->Get(FIRST_INSTANCE) )           ERROR
  nstring += environment->GPH("sys_ident")->GetString();
  
// L:/ops/bat/ds7[cpp.bat] 
  if ( !is_project )
    opt_language = (ProgramLanguage)GPH("opt_language")->GetInt();
  nstring += ProgramLanguageExtension(ext,GetDBHandle(),opt_language);
  if ( main_opt )
    nstring += "m";
  nstring += ".BAT";
  
// L:/ops/bat/ds7cpp.bat[ ODC_ImpClass] 
  nstring += ' ';
  nstring += compile_object;
  
// L:/ops/bat/ds7cpp.bat ODC_ImpClass[ OPS] 
  nstring += ' ';
  nstring += project_pc.GPH("sys_ident")->GetString();
  
// L:/ops/bat/ds7cpp.bat ODC_ImpClass OPS[ ODC_ImpClass] 
  if ( !is_project )
  {
    nstring += ' ';
    nstring += GPH("sys_ident")->GetString();
  }
    
// L:/ops/bat/ds7cpp.bat ODC_ImpClass OPS ODC_ImpClass[ NO]
  if ( !is_project && !main_opt )
  {
    nstring += ' ';
    nstring += ((char*) (if_opt ? "YES" : "NO"));
  }

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetDocFileName - 



\return filnames - 

\param  nstring - 
\param  doc_type - 
\param  if_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *pc_ODC_compile_object_base :: GetDocFileName (NString &nstring, char *doc_type, logical if_opt )
{
  char            *extension = "";
  ProgramLanguage  plang     = (ProgramLanguage)GPH("opt_language")->GetInt();

BEGINSEQ
  nstring = "";

  if ( !IsPositioned() )                            ERROR
  
  if ( !strcmp(doc_type, "Include") )
  {
                 
    switch(plang) {
       case PL_CPP: extension = ".hpp"; break;
       case PL_C: extension = ".h"; break;
       case PL_COM_IDL: if (if_opt) extension = ".idl" ; else extension = ".hpp"; break;
       default :  extension = ".inl"; break;
    }                  
                  
    switch (plang) {
       case PL_C: nstring.Append("i"); break;
       case PL_COM_IDL:  nstring.Append("com"); break;
       default: nstring.Append("s"); break;
    }                  
  }
  else if ( !strcmp(doc_type,"Source") )
   switch(plang){
      case PL_CPP:
      case PL_C:
      case PL_COM_IDL: extension = ".cpp"; break;
      case PL_ASM: extension = ".asm"; break;
      default:".src";
   }
  
  
  else if ( !strcmp(doc_type,"COM_Include") ) {
    if (plang == PL_COM_IDL) extension = ".h" ; else extension = "";
  }
  else if ( !strcmp(doc_type,"Expression") )
    extension   = ".osi";

  if ( if_opt && plang != PL_COM_IDL )
    nstring.Append("_if_");
  nstring.Append(GPH("sys_ident")->GetString());
  nstring.Append(extension);
 
    


RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetDocFilePath - 



\return filnames - 

\param  nstring - 
\param  doc_type - 
\param  if_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFilePath"

char *pc_ODC_compile_object_base :: GetDocFilePath (NString &nstring, char *doc_type, logical if_opt )
{
  char           *folder_type;
  if (strstr(doc_type,"Include")) folder_type =  "ERC_Include";
  else folder_type = "ERC_Source";
  NString         project_path;
  NString         file_name;

BEGINSEQ
  nstring = "";

  if ( !IsPositioned() )                            ERROR
  
  nstring += GetProjectPath(project_path,folder_type);
  nstring += GetDocFileName(file_name,doc_type,if_opt);

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetProject - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProject"

PropertyHandle *pc_ODC_compile_object_base :: GetProject ( )
{
  PropertyHandle    *prophdl;
  PropertyHandle    *ph;

BEGINSEQ
  if ( !IsPositioned() )                             ERROR
  if ( !(prophdl = GetCollectionProperty()) ) // is a collection ph
    prophdl = this;
    
  if ( !prophdl->Inherits("ODC_Module") )                  
  {
    if ( !(prophdl = prophdl->GPH("module")) )       ERROR
    if ( !prophdl->Get(FIRST_INSTANCE) )             ERROR
  }
  
  while ( !prophdl->IsA("ODC_Project") )                  
  {
    ph = prophdl->GPH("module_ref");
    if ( ph->Get(FIRST_INSTANCE) )
      prophdl = ph;
    else
    {
      prophdl = prophdl->GPH("parent_module");
      if ( !prophdl->Get(FIRST_INSTANCE) )           ERROR
    }
  }
    
  if ( prophdl->IsA("ODC_Project") )                 LEAVESEQ 

  SDBERR(99)

RECOVER
  SDBSET(99)
  SDBRESET
  prophdl = NULL;

ENDSEQ
  return(prophdl);

}

/******************************************************************************/
/**
\brief  GetProjectPath - 



\return command - 

\param  nstring - 
\param  folder_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *pc_ODC_compile_object_base :: GetProjectPath (NString &nstring, char *folder_type )
{
  pc_ODC_Project    project_pc(GetProject());

  nstring = "";

  return( project_pc.GetProjectPath(nstring,folder_type) );


}

/******************************************************************************/
/**
\brief  ResCompileState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResCompileState"

void pc_ODC_compile_object_base :: ResCompileState ( )
{

  *GPH("req_compile") = "CPS_undefined";

}

/******************************************************************************/
/**
\brief  ResModLevel - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResModLevel"

logical pc_ODC_compile_object_base :: ResModLevel ( )
{
  PropertyHandle    *mod_level = GPH("mod_level");
  logical            cond      = NO;
BEGINSEQ
  if ( !IsPositioned() )                             ERROR
  
  if ( mod_level->GetInt() == CML_undefined )        LEAVESEQ

  pc_SDB_TypeRef_fm    typeref_in(GPH("typeref_in"));
  if ( typeref_in.SetCompRequest((ClassModLevel )mod_level->GetInt()) )
                                                     ERROR
  *mod_level = CML_undefined;
  cond = YES;
RECOVER

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ResetProject - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetProject"

void pc_ODC_compile_object_base :: ResetProject (PropertyHandle *prophdl )
{

BEGINSEQ
  if ( !prophdl->IsValid() )                                   LEAVESEQ

/*
  soll genau die Einstellungen zurücknehmen, 
  die GetProject explizit veranlasst hat (damit alles wieder schreibend verfuegbar ist)
*/
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetCompileState - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  compreq - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompileState"

void pc_ODC_compile_object_base :: SetCompileState (CompileStates compreq )
{
  PropertyHandle   *req_compile = GPH("req_compile");
  PropertyHandle   *mod_level   = GPH("mod_level");

  if ( !compreq )
    compreq = CPS_ready;
  *req_compile = (int32)compreq;

  if ( compreq == CPS_requested )
  {
    pc_ODC_Project    project(GetProject());
    project.SetCompile(compreq);
    ResetProject(&project);             
  }
  
  if ( compreq == CPS_ready )
    *mod_level = (int32)CML_undefined;

}

/******************************************************************************/
/**
\brief  i01 - 



\param  compreq_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompileState"

void pc_ODC_compile_object_base :: SetCompileState (char *compreq_string )
{
  PropertyHandle   *req_compile = GPH("req_compile");
  if ( compreq_string )
    *req_compile = compreq_string;
    
  SetCompileState((CompileStates)req_compile->GetInt());

}

/******************************************************************************/
/**
\brief  SetIncludeState - 




\param  genincl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIncludeState"

void pc_ODC_compile_object_base :: SetIncludeState (logical genincl )
{
  PropertyHandle    *req_genincl = GPH("req_genincl");
  *req_genincl = genincl;
  
  if ( genincl )
  {
    pc_ODC_Project    project(GetProject());
    project.SetGenInc(YES);
    ResetProject(&project);             
  }


}

/******************************************************************************/
/**
\brief  SetModified - 



\return cond - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  cmod_level - 
\param  genincl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetModified"

logical pc_ODC_compile_object_base :: SetModified (ClassModLevel cmod_level, logical genincl )
{
  PropertyHandle    *mod_level   = GPH("mod_level");
  PropertyHandle    *req_compile = GPH("req_compile");
  PropertyHandle    *req_genincl = GPH("req_genincl");
  logical            cond        = NO;
  if ( mod_level->GetInt() < cmod_level )
  {
    *mod_level = (int32)cmod_level;
    cond       = YES;
  }
  
  if ( req_compile->GetInt() != CPS_requested )
  {
    SetCompileState(CPS_requested);
    cond       = YES;
  }

  if ( genincl && !req_genincl->GetInt() )
  {
    SetIncludeState(YES);
    cond       = YES;
  }
 return(cond);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  cmod_level_string - 
\param  genincl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetModified"

logical pc_ODC_compile_object_base :: SetModified (char *cmod_level_string, logical genincl )
{
  PropertyHandle  *mod_level     = GPH("mod_level");
  int32            cur_mod_level = mod_level->GetInt();
  if ( cmod_level_string )
    *mod_level = cmod_level_string;

  return ( SetModified((ClassModLevel)MAX(cur_mod_level,mod_level->GetInt()),genincl) );

}

/******************************************************************************/
/**
\brief  pc_ODC_compile_object_base - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_compile_object_base"

     pc_ODC_compile_object_base :: pc_ODC_compile_object_base (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  extnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_compile_object_base"

     pc_ODC_compile_object_base :: pc_ODC_compile_object_base (DatabaseHandle &dbhandle, char *extnames )
                     : PropertyHandle (dbhandle,extnames,PI_Read)
{



}


