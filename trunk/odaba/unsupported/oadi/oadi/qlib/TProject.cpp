/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TProject

\brief    


\date     $Date: 2006/07/31 11:18:56,03 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TProject"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sCTX_Project.hpp>
#include  <sOApplicationO.hpp>
#include  <sODProject.hpp>
#include  <sODesktop.hpp>
#include  <sODesktopO.hpp>
#include  <sOElementStyle.hpp>
#include  <sOFieldControl.hpp>
#include  <sOProject.hpp>
#include  <sTControl.hpp>
#include  <sTDesktop.hpp>
#include  <sTProjectManager.hpp>
#include  <sTWidgetControl.hpp>
#include  <sUCTX_dll.hpp>
#include  <sTProject.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TProject :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TProject")? this
                                               : TApplication::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateControl - 


\return rc - 

\param  tc_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateControl"

int32 TProject :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TProject();
  return(0);

}

/******************************************************************************/
/**
\brief  DoCreate - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TProject :: DoCreate ( )
{
  TDesktop        *desktop = NULL;
  logical          term    = NO;
BEGINSEQ
  if ( !(desktop = OI_CAST(TDesktop,Owner())) )     OADIERR(99)
    
  if ( !project )
    if ( !(project = OI_CAST(OProject,elementStyle)) )
                                                     OADIERR(99)
  if ( !complexWidget )
    if ( !(complexWidget = new ODProject(desktop->get_complexWidget(),
                                         project->get_sys_ident())) )
                                                     OADIERR(95)
  if ( TApplication::DoCreate() )                    ERROR
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoCreated - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreated"

logical TProject :: DoCreated ( )
{
  logical        term           = NO;
BEGINSEQ
  if ( !context )
    context = UDLL_Handle()->CreateProjectCtx(elementStyle->get_res_id());
  
  if ( TApplication::DoCreated() )                   ERROR
  
  if ( TProjectManager::TPM->OpenDAT() )             ERROR
  
  ((ODProject *)complexWidget)->SetDictionary(
              TProjectManager::TPM->UCB()->sdbudat->dictionary);
  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetMainWindow - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMainWindow"

void TProject :: SetMainWindow ( )
{

BEGINSEQ
  if ( !complexWidget )                                  ERROR
  complexWidget->SetAsMainWindow();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  TProject - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TProject"

     TProject :: TProject ( )
                     : TApplication (),
  project(NULL)
{



}


