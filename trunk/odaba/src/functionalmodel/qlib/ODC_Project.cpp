/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_Project



\date     $Date: 2006/05/20 19:08:33,06 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_Project"

#include  <pfmodel.h>
#include  <spc_ODC_Project.hpp>
#include  <sODC_Project.hpp>


/******************************************************************************/
/**
\brief  GetDocFileName

\return filnames
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
\param  doc_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *ODC_Project :: GetDocFileName (PropertyHandle *prophdl, NString &nstring, char *doc_type )
{

  return ( pc_ODC_Project(prophdl).GetDocFileName(nstring,doc_type) );

}

/******************************************************************************/
/**
\brief  GetProjectPath

\return ppath
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
\param  folder_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *ODC_Project :: GetProjectPath (PropertyHandle *prophdl, NString &nstring, char *folder_type )
{


  return ( pc_ODC_Project(prophdl).GetProjectPath(nstring,folder_type) );

}


