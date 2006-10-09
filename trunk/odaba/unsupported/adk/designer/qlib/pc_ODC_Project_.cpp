/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ODC_Project_



\date     $Date: 2006/05/19 19:07:00,51 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_Project_"

#include  <pdesign.h>
#ifndef   GSRT_ODE_Project_HPP
#define   GSRT_ODE_Project_HPP
#include  <sODE_Project.hpp>
#include  <sGSRT.h>
#endif
#include  <spc_ClassInputHelp.hpp>
#include  <spc_ODC_Project_.hpp>


/******************************************************************************/
/**
\brief  InitExternalResources

\return term - 

\param  nstring
\param  impl_env
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExternalResources"

logical pc_ODC_Project_ :: InitExternalResources (NString &nstring, char *impl_env )
{
  PropertyHandle  *environment = GPH("environment");
  logical          term        = NO;
BEGINSEQ
  ExecuteInstanceAction("InitializeExternalResources","YES");
  nstring = GetActionResult();
  
  if ( impl_env )
  {
    PropertyHandle   env_ident(impl_env);
    environment->Provide(env_ident);                P_SDBCERR
// ... init der batch-prozeduren    
  }

RECOVER
  term = YES;
ENDSEQ
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

logical pc_ODC_Project_ :: InitResourceDB (char *prjnames, PropertyHandle *source_ph )
{
  logical                 term = NO;

BEGINSEQ
  if(!prjnames)                                     ERROR
  PropertyHandle  phprjnames(prjnames);
  if ( !source_ph->Get(phprjnames) )                ERROR

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

logical pc_ODC_Project_ :: IsImplemented (logical read_opt )
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

\param  prj_names
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewProject"

logical pc_ODC_Project_ :: NewProject (char *prj_names )
{
  PropertyHandle   idkey(prj_names);
  logical          started = NO;
  logical          term    = NO;
BEGINSEQ
  if ( idkey.IsEmpty() )                            ERROR
  
  started = StartRTA() ? YES : NO;
  Add(idkey);                                       P_SDBCERR

  ExecuteInstanceAction("InitializeExternalResources","NO");
  StopRTA(started);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_Project_

-------------------------------------------------------------------------------
\brief  i0


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_Project_"

     pc_ODC_Project_ :: pc_ODC_Project_ (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc_ODC_Project_"

     pc_ODC_Project_ :: pc_ODC_Project_ (DatabaseHandle &db_handle, PIACC accopt )
                     : PropertyHandle (db_handle,"ODC_Project",accopt)
{
}


