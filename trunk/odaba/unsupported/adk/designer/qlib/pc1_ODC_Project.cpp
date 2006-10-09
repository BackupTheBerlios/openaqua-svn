/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_Project



\date     $Date: 2006/05/30 14:16:07,28 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ODC_Project"

#include  <pdesign.h>
#ifndef   GSRT_ODE_Project_HPP
#define   GSRT_ODE_Project_HPP
#include  <sODE_Project.hpp>
#include  <sGSRT.h>
#endif
#include  <iodei.h>
#include  <spc1_ODC_Environment.hpp>
#include  <spc1_ODC_Include.hpp>
#include  <spc_ClassInputHelp.hpp>
#include  <spc1_ODC_Project.hpp>


/******************************************************************************/
/**
\brief  GetInterfaceClassName

\return string

\param  init_string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInterfaceClassName"

char *pc1_ODC_Project :: GetInterfaceClassName (char *init_string )
{
  pc1_ODC_ImpClass  classes(GPH("classes"));
  return (   classes.GetContextInterface() 
           ? classes.GPH("sys_ident")->GetString()
           : init_string   );


}

/******************************************************************************/
/**
\brief  GetProjectPath

\return string

\param  nstring
\param  folder_type
\param  init_string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

char *pc1_ODC_Project :: GetProjectPath (NString &nstring, char *folder_type, char *init_string )
{

  nstring = "";
  
  if ( !ExecuteInstanceAction("GetProjectPath",folder_type) )
    nstring = GetActionResult();
    
  if ( nstring.IsEmpty() && init_string )
    nstring = init_string;

  return(nstring);
}

/******************************************************************************/
/**
\brief  InitExternalResources

\return term - 

\param  ctxptr - 
\param  pimpl_type
\param  ini_opt
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExternalResources"

logical pc1_ODC_Project :: InitExternalResources (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring )
{
  logical          auto_ini = ODEOptionIsOn(ctxptr,"AutoInitialize");
  logical          term     = NO;
  ExecuteInstanceAction("InitializeExternalResources",ini_opt ? "YES" : "NO");
  nstring = GetActionResult();
  
  pc1_ODC_Environment(GPH("environment")).ProvideEnvironment(ctxptr,pimpl_type,auto_ini,nstring);
  pc1_ODC_Include(GPH("proj_include")).ProvideProjectInclude(ctxptr,pimpl_type,auto_ini,nstring);
  return(term);
}

/******************************************************************************/
/**
\brief  InitResourceDB

\return term - 

\param  prjnames
\param  source_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pc1_ODC_Project :: InitResourceDB (char *prjnames, PropertyHandle *source_ph )
{
  PropertyHandle    prj_ident(prjnames);
  logical           term = NO;

BEGINSEQ
  if ( !source_ph->Get(prj_ident) )                ERROR

  if ( !Copy(*source_ph,REPL_local) )
  {
    SDBCERR
    ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsImplemented

\return cond - 

\param  read_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsImplemented"

logical pc1_ODC_Project :: IsImplemented (logical read_opt )
{
  logical    cond = YES;
BEGINSEQ
  if ( !IsPositioned() )
  {
    if ( !read_opt )                                 ERROR
    if ( !Get(FIRST_INSTANCE) )                      ERROR
  }
  
  if ( *GPH("sys_ident")->GetString() == '#' )       ERROR


RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  NewProject

\return term - 

\param  ctxptr - 
\param  prj_names
\param  ini_opt
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewProject"

logical pc1_ODC_Project :: NewProject (CTX_GUIBase *ctxptr, char *prj_names, logical ini_opt, NString &nstring )
{
  ProjectImplementationType  pimpl_type = PIT_ClassLibrary;
  PropertyHandle             idkey(prj_names);
  logical                    started  = NO;
  logical                    term     = NO;
BEGINSEQ
  if ( idkey.IsEmpty() )                            ERROR
  
  started = StartRTA() ? YES : NO;

  Add(idkey);                                       P_SDBCERR
  
  if ( ini_opt )
  {
    if ( ctxptr->GetDecisionYes(19,"GUIContextInterfaceDLL") )
    {
      pimpl_type = PIT_GUIContextInterfaceDLL;
      pc1_ODC_ImpClass(GPH("classes")).ProvideContextInterface(YES,nstring);
    }
    else if ( ctxptr->GetDecisionYes(19,"DBContextInterfaceDLL") )
    {
      pimpl_type = PIT_DBContextInterfaceDLL;
      pc1_ODC_ImpClass(GPH("classes")).ProvideContextInterface(NO,nstring);
    }
    else if ( ctxptr->GetDecisionYes(19,"ConsoleApplications") )
      pimpl_type = PIT_ConsoleApplications;
    else if ( ctxptr->GetDecisionYes(19,"GUIApplications") )
      pimpl_type = PIT_GUIApplications;
  }  
  
  if ( InitExternalResources(ctxptr,pimpl_type,ini_opt,nstring) )
                                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  StopRTA(started);
  return(term);
}

/******************************************************************************/
/**
\brief  pc1_ODC_Project

-------------------------------------------------------------------------------
\brief  i0


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ODC_Project"

     pc1_ODC_Project :: pc1_ODC_Project (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{
}

/******************************************************************************/
/**
\brief  i01


\param  db_handle
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ODC_Project"

     pc1_ODC_Project :: pc1_ODC_Project (DatabaseHandle &db_handle, PIACC accopt )
                     : PropertyHandle (db_handle,"ODC_Project",accopt)
{
}


