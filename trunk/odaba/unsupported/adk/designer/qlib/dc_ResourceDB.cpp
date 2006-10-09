/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    dc_ResourceDB

\brief    


\date     $Date: 2006/06/17 14:42:10,73 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dc_ResourceDB"

#include  <pdesign.h>
#include  <sDatabaseHandle.hpp>
#include  <spc1_ADK_Resource.hpp>
#include  <spc1_ODC_Project.hpp>
#include  <sdc_ResourceDB.hpp>


/******************************************************************************/
/**
\brief  InitResourceDB - 


\return term - 
-------------------------------------------------------------------------------
\brief  i01 - 


\param  source_dc - 
\param  extnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical dc_ResourceDB :: InitResourceDB (dc_ResourceDB *source_dc, char *extnames )
{
  pc1_ADK_Resource   source(*source_dc,extnames,PI_Read);
  return ( pc1_ADK_Resource(*this,extnames,PI_Update).
             InitResourceDB(source) );


}

/******************************************************************************/
/**
\brief  i02 - 


\param  source_dc - 
\param  extnames - 
\param  inst_key - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical dc_ResourceDB :: InitResourceDB (dc_ResourceDB *source_dc, char *extnames, char *inst_key )
{
  PropertyHandle         key(inst_key);
  PropertyHandle         source(*source_dc,extnames,PI_Read);
  PropertyHandle         target(*this,extnames,PI_Write);
  int32                  indx0 = 0;
  logical                term = NO;
  

BEGINSEQ
  if ( !inst_key || !*inst_key || *inst_key == '*' )
  {
    if ( target.CopySet(source,REPL_none) < 0 )      ERROR
  }
  else
  {
    if ( !source.Get(key) )                          ERROR
    if ( !target.Copy(source,REPL_none) )            ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitResourceDB_DE - 


\return term - 

\param  source_dc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB_DE"

logical dc_ResourceDB :: InitResourceDB_DE (dc_ResourceDB *source_dc )
{
  logical                 term = NO;
  odc_project.InitResourceDB("<CTX_Interface>",&source_dc->get_odc_project());
  
  adk_classes.InitResourceDB("CCHAR",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("CHAR",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("COLLECTION",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("DATE",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("ENUMERATION",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("IMBEDDED",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("INT",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("LOGICAL",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("MEMO",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("REAL",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("STRING",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("TIME",source_dc->get_adk_classes());
  adk_classes.InitResourceDB("UINT",source_dc->get_adk_classes());
  
  InitResourceDB(source_dc,"ADKS_CheckBox");
  InitResourceDB(source_dc,"ADKS_Edit");
  InitResourceDB(source_dc,"ADKS_ListBox");
  InitResourceDB(source_dc,"ADKS_Menu");
  InitResourceDB(source_dc,"ADKS_PushButton");
  InitResourceDB(source_dc,"ADKS_RadioGroup");
  InitResourceDB(source_dc,"ADKS_SrcollBar");
  InitResourceDB(source_dc,"ADKS_StatLine");
  InitResourceDB(source_dc,"ADKS_Symbol");
  InitResourceDB(source_dc,"ADKS_Tab");
  InitResourceDB(source_dc,"ADKS_Splitter");
  InitResourceDB(source_dc,"ADKS_ToolBox");
  InitResourceDB(source_dc,"ADKS_Virtual");
  InitResourceDB(source_dc,"ADKS_Window");

  InitResourceDB(source_dc,"ADK_Highlighter");
  InitResourceDB(source_dc,"ADK_SyntaxClass");
  InitResourceDB(source_dc,"ADK_Project");
  InitResourceDB(source_dc,"ADK_Application");

  InitResourceDB(source_dc,"ADA_WinAction");
  
  InitResourceDB(source_dc,"ADK_ColorGroup");
  InitResourceDB(source_dc,"ADK_Font");
  InitResourceDB(source_dc,"ADK_Layout");
  
  InitResourceDB(source_dc,"ADK_EventActionControl");

  return(term);
}

/******************************************************************************/
/**
\brief  InitResourceDB_KE - 


\return term - 

\param  source_dc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB_KE"

logical dc_ResourceDB :: InitResourceDB_KE (dc_ResourceDB *source_dc )
{
  logical      term = NO;
  odc_project.InitResourceDB("<CTX_Interface>",&source_dc->get_odc_project());
  odc_project.InitResourceDB("#_SOS",&source_dc->get_odc_project());
  odc_project.InitResourceDB("#_OPI",&source_dc->get_odc_project());
  odc_project.InitResourceDB("#_OPA",&source_dc->get_odc_project());
  odc_project.InitResourceDB("#_ODCP",&source_dc->get_odc_project());
  
  InitResourceDB(source_dc,"ODC_PFunction","<Function>");
  InitResourceDB(source_dc,"ODC_PFunction","ExecuteFunction");
  InitResourceDB(source_dc,"SDB_GenType","*");
  return(term);
}

/******************************************************************************/
/**
\brief  dc_ResourceDB - 



\param  db_handle - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dc_ResourceDB"

     dc_ResourceDB :: dc_ResourceDB (DatabaseHandle &db_handle, PIACC accopt )
                     : DatabaseHandle (db_handle),
  adk_classes(db_handle,accopt),
  odc_project(db_handle,accopt)
{



}


