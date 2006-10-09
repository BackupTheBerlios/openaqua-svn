/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TApplication



\date     $Date: 2006/04/28 15:20:35,92 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TApplication"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sCTX_Application.hpp>
#include  <sOApplication.hpp>
#include  <sODApplication.hpp>
#include  <sODataSource.hpp>
#include  <sODataWidget.hpp>
#include  <sOElementStyle.hpp>
#include  <sTControl.hpp>
#include  <sTProject.hpp>
#include  <sTProjectManager.hpp>
#include  <sUCTX_dll.hpp>
#include  <sTApplication.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TApplication :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TApplication") ? this
                                               : TWindow::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateControl

\return rc

\param  tc_ptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateControl"

int32 TApplication :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TApplication();
  return(0);

}

/******************************************************************************/
/**
\brief  DoCreate

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TApplication :: DoCreate ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !application )
    if ( !(application = OI_CAST(OApplication,elementStyle)) )
                                                     OADIERR(99)
  if ( !complexWidget )
    if ( !(complexWidget = new ODApplication(ComplexWidgetParent(),
                                             application->get_sys_ident())) )
                                                     OADIERR(95)
  
  if ( TWindow::DoCreate() )                         ERROR
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoCreated

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreated"

logical TApplication :: DoCreated ( )
{
  logical       is_prj = context ? YES : NO;
  logical       term   = NO;
BEGINSEQ
  if ( !context )
    context = UDLL_Handle()->CreateApplicationCtx(elementStyle->get_res_id());
  
  if ( TWindow::DoCreated() )                        ERROR
  
  if ( application->get_database().GetPath() )
  {
    ((ODApplication *)complexWidget)->SetDataSource(
                (char *)application->get_database().GetPath(),
                application->get_database().GetAccessMode(),
                application->get_database().get_netOpt());
  }
  else
  {
    if ( TProjectManager::TPM->OpenDAT() )           ERROR
    complexWidget->SetDataSource(TProjectManager::TPM->UCB()->sdbudat->object_handle);
  }
 
  complexWidget->SetPath((char *)application->get_dataSource().GetPath(),
                         application->get_dataSource().get_structureName(),
                         application->get_dataSource().get_isCollection(),
                         application->get_dataSource().get_sortOrder(),
                         application->get_dataSource().GetPathType(),
                         application->get_dataSource().get_accmode());
    
  if ( !is_prj )
    complexWidget->Activate();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EventFrame

\return event_frame

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventFrame"

OEH_Frame TApplication :: EventFrame ( )
{

  return(OEH_Application);

}

/******************************************************************************/
/**
\brief  TApplication


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TApplication"

     TApplication :: TApplication ( )
                     : TWindow (),
  application(NULL)

{
}


