/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODABA2_extern

\brief    


\date     $Date: 2006/03/13 21:30:38,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODABA2_extern"

#include  <pfmodel.h>
#include  <cSystemPathes.h>
#include  <sODABA2_extern.hpp>


/******************************************************************************/
/**
\brief  GetProjectPath - 


\return ppath -
/******************************************************************************/
/**
\brief  i00


\param  folder_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *ODABA2_extern :: GetProjectPath (char *folder_type )
{
  static   char   ppath[DEF_BUFLEN+1];
  return ( GetProjectPath(ppath,folder_type) );

}

/******************************************************************************/
/**
\brief  i01


\param  ppath -
\param  folder_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *ODABA2_extern :: GetProjectPath (char *ppath, char *folder_type )
{
  char    *folder = NULL;
  strcat(strcpy(ppath,proj_path),"\\");

  if ( folder_type )
  {
    if ( !strcmp(folder_type,"ERC_Source") )
      folder = path_names[SP_SOURCE];          
    else if ( !strcmp(folder_type,"ERC_Include") )
      folder = path_names[SP_INCLUDE];
    else if ( !strcmp(folder_type,"ERC_Executable") )
      folder = path_names[SP_EXE];
    else if ( !strcmp(folder_type,"ERC_Document") )
      folder = path_names[SP_DOC];
    else if ( !strcmp(folder_type,"ERC_Batch") )
      folder = path_names[SP_BAT];
    else if ( !strcmp(folder_type,"ERC_Temp") )
      folder = path_names[SP_TEMP];
    else if ( !strcmp(folder_type,"ERC_Test") )
      folder = path_names[SP_USER1];
    else if ( !strcmp(folder_type,"ERC_Template") )
      folder = path_names[SP_USER2];
  }

  if ( folder && *folder )
    strcat(gvtxbts(ppath+strlen(ppath),folder,sizeof(path_names[0])),"\\");

  return(ppath);
}


