/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_Environment



\date     $Date: 2006/05/31 12:29:58,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ODC_Environment"

#include  <pdesign.h>
#include  <sODE_Templates.hpp>
#include  <ifil.h>
#include  <iodei.h>
#include  <spc1_ODC_Project.hpp>
#include  <spc1_ODC_Environment.hpp>


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

logical pc1_ODC_Environment :: InitExternalResources (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring )
{
  ODE_Templates    ode_tpl("ERC_Batch");
  pc1_ODC_Project  parent(GetParentProperty());
  char            *prj_ident  = parent.GPH("sys_ident")->GetString();
  char            *env_ident  = GPH("sys_ident")->GetString();
  char            *bat_path   = NULL;
  NString          lstring;
  logical          gui        = NO;
  logical          term       = NO;
BEGINSEQ
  if ( !ini_opt )                                   LEAVESEQ
  
  if ( !ode_tpl.TemplatePath() || !(bat_path = ode_tpl.TargetPath(&parent,nstring)) )  
                                                    ERROR
  SetSysVariable("DevelopmentEnvironment",env_ident);
  SetSysVariable("PROJECT_NAME",prj_ident);

  SetSysVariable("PROJECT_BATCH",bat_path);
  SetSysVariable("PROJECT_LIB",parent.GetProjectPath(lstring,"ERC_Library","PROJECT_LIB_UNKNOWN"));
  SetSysVariable("PROJECT_INCLUDE",parent.GetProjectPath(lstring,"ERC_Include","PROJECT_INCLUDE_UNKNOWN"));

  parent.GetProjectPath(lstring,"ERC_Root","PROJECT_ROOT_UNKNOWN");
  if ( !ODEOptionIsOn(ctxptr,"UNIX") )
    lstring.ReplaceFirstSymbol("/","\\");
  SetSysVariable("PROJECT_ROOT",lstring);

  if ( (gui = (pimpl_type == PIT_GUIContextInterfaceDLL)) ||
       pimpl_type == PIT_DBContextInterfaceDLL              )
  {
    SetSysVariable("DLL_NAME",prj_ident);
    SetSysVariable("OBJECT_FILE_NAME",
         parent.GetInterfaceClassName(gui ? "UCTXInterface" : "CTXInterface"));
  }

  term = ode_tpl.InitFiles(pimpl_type,env_ident,nstring);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideEnvironment

\return term - 

\param  ctxptr - 
\param  pimpl_type
\param  ini_opt
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEnvironment"

logical pc1_ODC_Environment :: ProvideEnvironment (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring )
{
  PropertyHandle   env_ident(ODEOption(ctxptr,"DevelopmentEnvironment"));
  logical          term = NO;
BEGINSEQ
  if ( env_ident.IsEmpty() )                        LEAVESEQ
  
  Provide(env_ident);                               P_SDBCERR
  InitExternalResources(ctxptr,pimpl_type,ini_opt,nstring);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc1_ODC_Environment


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ODC_Environment"

     pc1_ODC_Environment :: pc1_ODC_Environment (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{
}


