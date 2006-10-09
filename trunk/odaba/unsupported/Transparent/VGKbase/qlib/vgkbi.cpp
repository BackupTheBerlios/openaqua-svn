/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    vgkbi

\brief    


\date     $Date: 2006/07/21 12:13:16,95 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "vgkbi"

#include  <pVGKbase.h>
#include  <spc__Project.hpp>

#include  <ivgkbi.h>

/******************************************************************************/
/**
\brief  BauPreisIndex - 



\return value - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BauPreisIndex"

double __cdecl BauPreisIndex ( )
{

  return ( 10.5 );

}

/******************************************************************************/
/**
\brief  GetEigentuemerKennung - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEigentuemerKennung"

char *__cdecl GetEigentuemerKennung ( )
{
  char     *kenner = GetSysVariable("EIGENTUEMER_KENNUNG");
  return ( kenner && *kenner ? kenner : "T" );

}

/******************************************************************************/
/**
\brief  GetImportFolder - 



\return string - 

\param  nstring - 
\param  dbhandle - 
\param  sub_folder - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImportFolder"

char *__cdecl GetImportFolder (NString &nstring, DatabaseHandle &dbhandle, char *sub_folder )
{

  return ( pc__Project(dbhandle,PI_Read).GetImportFolder(nstring,sub_folder) );

}

/******************************************************************************/
/**
\brief  GetSparteFromType - 



\return string - 

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSparteFromType"

char *__cdecl GetSparteFromType (PropertyHandle *prophdl )
{
  char   *sparte = "";

  return(sparte);
}

