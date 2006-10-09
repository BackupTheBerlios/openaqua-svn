/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_Include

\brief    


\date     $Date: 2006/06/13 23:02:52,60 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ODC_Include"

#include  <pdesign.h>
#include  <sODE_Templates.hpp>
#include  <ifil.h>
#include  <spc1_ODC_Include.hpp>


/******************************************************************************/
/**
\brief  InitExternalResource - 


\return term - 

\param  pimpl_type - 
\param  ini_opt - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExternalResource"

logical pc1_ODC_Include :: InitExternalResource (ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring )
{
  ODE_Templates    ode_tpl("ERC_Include");
  PropertyHandle  *parent    = GetParentProperty();
  char            *prj_ident = parent->GPH("sys_ident")->GetString();
  char            *incl_path = NULL;
  Key              idkey;
  NString          ident_string;
  NString          prj_file;
  NString          area;
  logical          term      = NO;
BEGINSEQ
  if ( !ini_opt )                                   LEAVESEQ
  
  if ( !ode_tpl.TemplatePath() || !(incl_path = ode_tpl.TargetPath(parent,nstring)) )  
                                                    ERROR
  SetSysVariable("PROJECT_NAME",prj_ident);
  term = ode_tpl.InitFiles(pimpl_type,prj_ident,nstring);
  
  prj_file  = incl_path;
  prj_file += "/";
  prj_file += KeyToString(idkey,ExtractKey());
  prj_file += ".h";
  if ( !IsFile(prj_file) )
  {
    area  = "#include <";
    area += ProjectIncludeName(ident_string);
    area += ".h>";
    term = ode_tpl.WriteFile(prj_file,area,nstring);
  }

    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProjectIncludeName - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProjectIncludeName"

char *pc1_ODC_Include :: ProjectIncludeName (NString &nstring )
{

  nstring  = "p";
  nstring += GetParentProperty()->GPH("sys_ident")->GetString();

  return(nstring);
}

/******************************************************************************/
/**
\brief  ProvideProjectInclude - 


\return term - 

\param  ctxptr - 
\param  pimpl_type - 
\param  ini_opt - 
\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProjectInclude"

logical pc1_ODC_Include :: ProvideProjectInclude (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring )
{
  NString          ident_string;
  logical          term = NO;
BEGINSEQ
  PropertyHandle   incl_ident(ProjectIncludeName(ident_string));
  Provide(incl_ident);                               P_SDBCERR

  InitExternalResource(pimpl_type,ini_opt,nstring);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc1_ODC_Include - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ODC_Include"

     pc1_ODC_Include :: pc1_ODC_Include (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


