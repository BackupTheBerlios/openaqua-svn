/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ODE_Templates

\brief    


\date     $Date: 2006/08/30 14:44:47,57 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODE_Templates"

#include  <pdesign.h>
#include  <ifil.h>
#include  <spc1_ODC_Project.hpp>
#include  <ssrt.hpp>
#include  <sODE_Templates.hpp>


/******************************************************************************/
/**
\brief  GetTemplatePathSubFolder - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTemplatePathSubFolder"

char *ODE_Templates :: GetTemplatePathSubFolder ( )
{
  char       *sub_folder = "";
BEGINSEQ
  if ( type )
  {
    if ( !strcmp(type,"ERC_Batch") )
      sub_folder = "bat";
    else if ( !strcmp(type,"ERC_Include") )
      sub_folder = "h";
    else if ( !strcmp(type,"ERC_Source") )
      sub_folder = "qlib";
    else if ( !strcmp(type,"ERC_Library") )
      sub_folder = "lib";
    else if ( !strcmp(type,"ERC_Executable") )
      sub_folder = "exe";
    else if ( !strcmp(type,"ERC_Document") )
      sub_folder = "doc";
    else if ( !strcmp(type,"ERC_Temp") )
      sub_folder = "temp";
    else if ( !strcmp(type,"ERC_Test") )
      sub_folder = "test";
    else if ( !strcmp(type,"ERC_Template") )
      sub_folder = "tpl";
    else if ( !strcmp(type,"ERC_Root") )
      sub_folder = "..";
    else
      P_ERR(99);
  }
RECOVER

ENDSEQ
  return(sub_folder);
}

/******************************************************************************/
/**
\brief  GetTemplateVariable - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTemplateVariable"

char *ODE_Templates :: GetTemplateVariable ( )
{
  char       *vname = "";
BEGINSEQ
  if ( type )
  {
    if ( !strcmp(type,"ERC_Batch") )
      vname = "_env_";
    else if ( !strcmp(type,"ERC_Include") )
      vname = "_prj_";
    else 
      P_ERR(99);
  }
RECOVER

ENDSEQ
  return(vname);
}

/******************************************************************************/
/**
\brief  InitFile - 



\return term - 

\param  srce_path - 
\param  fnames - 
\param  var_ident - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFile"

logical ODE_Templates :: InitFile (char *srce_path, char *fnames, char *var_ident, NString &nstring )
{
  NString          target_file(fnames);
  NString          cpath;
  logical          term      = NO;
BEGINSEQ
  cpath  = srce_path;
  cpath += "/";
  cpath += fnames;
  
  NString  area(ReadTextFile(cpath));
  if ( area.IsEmpty() )
  {
    nstring += "...  '";
    nstring += cpath;
    nstring += "' template could not be read";
    ERROR
  }

  area.ReplaceSysVariables(SystemVariables(),UNDEF);
  target_file.ReplaceFirstSymbol(GetTemplateVariable(),var_ident);
  cpath  = target_path;
  cpath += "/";
  cpath += target_file;
    
  if ( WriteFile(cpath,area,nstring) )              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitFiles - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  pimpl_type - 
\param  var_ident - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFiles"

logical ODE_Templates :: InitFiles (ProjectImplementationType pimpl_type, char *var_ident, NString &nstring )
{
  char            *sub1       = NULL;
  char            *sub2       = NULL;
  NString          tplsub_path;
  logical          term       = NO;
  if ( InitFiles(tpl_path,var_ident,nstring) )
    term = YES;

  switch ( pimpl_type )
  {
    case PIT_DBContextInterfaceDLL :
         sub1  = "db/";
         sub2  = "dll/";
         break;
    case PIT_GUIContextInterfaceDLL :
         sub1  = "gui/";
         sub2  = "dll/";
         break;
    case PIT_ConsoleApplications :
         sub1  = "db/";
         sub2  = "no_dll/";
         break;
    case PIT_GUIApplications :
         sub1  = "gui/";
         sub2  = "no_dll/";
         break;
    case PIT_ClassLibrary :
         sub1  = "db/";
         sub2  = "dll/";
         break;
    default : ;
  }

  if ( sub1 )
  {
    tplsub_path = tpl_path;
    tplsub_path += sub1;
    if ( InitFiles(tplsub_path,var_ident,nstring) )
      term = YES;

    if ( sub2 )
    {
      tplsub_path = tpl_path;
      tplsub_path += sub2;
      if ( InitFiles(tplsub_path,var_ident,nstring) )
        term = YES;
      tplsub_path += sub1;
      if ( InitFiles(tplsub_path,var_ident,nstring) )
        term = YES;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  srce_path - 
\param  var_ident - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFiles"

logical ODE_Templates :: InitFiles (char *srce_path, char *var_ident, NString &nstring )
{
  srt             *file_table = NULL;
  char            *fnames     = NULL;
  int32            indx0      = 0;
  logical          term       = NO;
BEGINSEQ
  if ( !IsDirectory(srce_path) || 
       !(file_table = CreateFileTable(srce_path,"*.*")) )
                                                    ERROR
  while ( fnames = (char *)file_table->srtigt(++indx0) )
    if ( InitFile(srce_path,fnames,var_ident,nstring) )
      term = YES;
      
  delete file_table;
  file_table = NULL;
RECOVER
  nstring += "...  '";
  nstring += srce_path;
  nstring += "' - templates not found\n";
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ODE_Templates - 




\param  folder_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODE_Templates"

     ODE_Templates :: ODE_Templates (char *folder_type )
                     :   tpl_path(),
  target_path(),
  type(folder_type)
{



}

/******************************************************************************/
/**
\brief  TargetPath - 



\return string - 

\param  prophdl - Property handle
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TargetPath"

char *ODE_Templates :: TargetPath (PropertyHandle *prophdl, NString &nstring )
{

BEGINSEQ
  target_path = "";
  if ( !pc1_ODC_Project(prophdl).GetProjectPath(target_path,type,NULL) )
                                                    ERROR
RECOVER
  nstring += "...  '";
  nstring += (char*) (type ? type : "UNKNOWN");
  nstring.Append("...  project folder could not be evalueated\n");

ENDSEQ
  return(target_path);
}

/******************************************************************************/
/**
\brief  TemplatePath - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TemplatePath"

char *ODE_Templates :: TemplatePath ( )
{

  tpl_path = GetSysVariable("PROGPATH");
  tpl_path += "/tpl/";
  tpl_path += GetTemplatePathSubFolder();
  tpl_path += "/";
  return(tpl_path);
}

/******************************************************************************/
/**
\brief  WriteFile - 



\return term - 

\param  cpath - 
\param  area - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteFile"

logical ODE_Templates :: WriteFile (char *cpath, char *area, NString &nstring )
{
  logical     term = NO;
BEGINSEQ
  nstring += "...  '";
  nstring += cpath;

  if ( !WriteTextFile(cpath,area) )
    nstring += "' file written";
  else
  {
    nstring += "' file could not be written";
    ERROR
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


