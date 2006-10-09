/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TWindow



\date     $Date: 2006/05/03 23:22:23,98 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TWindow"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODWindow.hpp>
#include  <sOElementStyle.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOSWindow.hpp>
#include  <sOWindow.hpp>
#include  <sTWindow.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TWindow :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TWindow")      ? this
                                               : TField::CastPointer(typenames) );

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

int32 TWindow :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TWindow();
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

logical TWindow :: DoCreate ( )
{
  logical             term = NO;
BEGINSEQ
// 1,65 (44)
  if ( TField::DoCreate() )                          ERROR

statistics5.Start();
  if ( !complexWidget )
    if ( !(complexWidget = ComplexWidgetParent()->CreateSubWindow(elementStyle->get_sys_ident())) )
                                                     OADIERR(95)
  
  if ( complexWidget->CreateClientArea(elementStyle->GetControlName(),
                                       Style()->IsWorkspace(),
                                       elementStyle->get_displayLevel(),
                                       elementStyle->IsField() && frameStyle->IsSimpleWindow(),
                                       WT_Normal,NO,NO) )
                                                     ERROR
  complexWidget->SetExtraData(this);
  
  if ( elementStyle->get_docking_area() )
    complexWidget->CreateDockingArea();
  

RECOVER
  term = YES;
ENDSEQ
statistics5.Stop();
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

logical TWindow :: DoCreated ( )
{
  DAlign      *align;
  logical term = NO;
BEGINSEQ
  SetWindowFlags(YES);
  
  if ( TField::DoCreated() )                         ERROR
  if ( !complexWidget )                              ERROR
  
  complexWidget->UpdateScrollBars(Style()->HasHscrol(),Style()->HasVscrol());

  align = elementStyle->Align();
//  if ( align->get_arrange() == AT_Grid )
//    complexWidget->CreateLayout(DSize(0,0),align->get_margin());

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

OEH_Frame TWindow :: EventFrame ( )
{

  return(OEH_Window);

}

/******************************************************************************/
/**
\brief  Style

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSWindow *TWindow :: Style ( ) const
{

//  return (OSWindow *)style;
  return OI_CAST(OSWindow,style);

}

/******************************************************************************/
/**
\brief  TWindow

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TWindow"

     TWindow :: TWindow ( )
                     : TField ()
{


}


