/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    odei



\date     $Date: 2006/05/22 11:14:08,10 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "odei"

#include  <pdesign.h>
#include  <spODE.hpp>

#include  <iodei.h>

/******************************************************************************/
/**
\brief  ODEContext

\return pODE

\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODEContext"

pODE *__cdecl ODEContext (CTX_GUIBase *ctxptr )
{
  CTX_Project  *proj_ctx    = ctxptr->GetProjectContext();
  char         *result      = NULL;

BEGINSEQ
  if ( !proj_ctx )                                   ERROR
  if ( proj_ctx->ExecuteFunction("IsODEContext") )   ERROR
    
  if ( !(result = proj_ctx->GetResult()) || 
       *result != 'Y'                       )        ERROR

RECOVER
  proj_ctx = NULL;
ENDSEQ
  return((pODE *)proj_ctx);
}

/******************************************************************************/
/**
\brief  ODEOption

\return option

\param  ctxptr - 
\param  option_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODEOption"

char *__cdecl ODEOption (CTX_GUIBase *ctxptr, char *option_name )
{

  return ( ODEContext(ctxptr)->GetOption(option_name) );

}

/******************************************************************************/
/**
\brief  ODEOptionIsOn

\return cond - 

\param  ctxptr - 
\param  option_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODEOptionIsOn"

logical __cdecl ODEOptionIsOn (CTX_GUIBase *ctxptr, char *option_name )
{
  char     *option = ODEContext(ctxptr)->GetOption(option_name);
  return (   option && *option == 'Y' 
           ? YES
           : NO   );

}

/******************************************************************************/
/**
\brief  ODEOutput

\return term - 

\param  ctxptr - 
\param  string
\param  clear_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODEOutput"

logical __cdecl ODEOutput (CTX_GUIBase *ctxptr, char *string, logical clear_opt )
{

  return ( ODEContext(ctxptr)->SetupOutput(string,clear_opt) );

}

