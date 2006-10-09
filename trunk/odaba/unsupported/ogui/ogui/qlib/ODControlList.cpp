/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODControlList

\brief    


\date     $Date: 2006/03/13 21:35:20,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODControlList"

#include  <pogui7.h>
#include  <sODControl.hpp>
#include  <sODControlList.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ODControlList :: Activate ( )
{
  ODControl         *pODControl;
  ODataWidget       *control_widget;
  logical            term       = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ

  DLL(ODControl)     cursor(*this);
  
  cursor.GoTop();
  while ( pODControl = cursor.GetNext() )
    if ( control_widget = pODControl->get_controlWidget() )
      if ( control_widget->Activate() )
        term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate - 


\return term -

\param  data_only -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical ODControlList :: Deactivate (logical data_only )
{
  ODControl         *pODControl;
  ODataWidget       *control_widget;
  logical            term       = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ

  DLL(ODControl)     cursor(*this);
  
  cursor.GoTop();
  while ( pODControl = cursor.GetNext() )
    if ( control_widget = pODControl->get_controlWidget() )
      if ( control_widget->Deactivate(data_only) )
        term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FindControl - 


\return pODControl -

\param  control_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindControl"

ODControl *ODControlList :: FindControl (char *control_name )
{
  ODataWidget       *control_widget = NULL;
  QWidget           *qwidget        = NULL;
  QString            ctrl_name(control_name);
  ODControl         *pODControl     = NULL;
BEGINSEQ
  if ( !this )                                       ERROR

  DLL(ODControl)     cursor(*this);
  
  cursor.GoTop();
  while ( pODControl = cursor.GetNext() )
    if ( (control_widget = pODControl->get_controlWidget()) &&
         (qwidget        = control_widget->WidgetQ())       &&
         qwidget->objectName() == ctrl_name   )      LEAVESEQ

  ERROR
RECOVER
  pODControl = NULL;
ENDSEQ
  return(pODControl);
}

/******************************************************************************/
/**
\brief  FindField - 


\return pODControl -

\param  control_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindField"

ODControl *ODControlList :: FindField (char *control_name )
{
  ODControl         *pODControl = NULL;
BEGINSEQ
  if ( !this )                                       ERROR

  DLL(ODControl)     cursor(*this);
  
  cursor.GoTop();
  while ( pODControl = cursor.GetNext() )
    if ( pODControl->get_name() && !strcmp(pODControl->get_name(),control_name) )
                                                     LEAVESEQ

RECOVER
  pODControl = NULL;
ENDSEQ
  return(pODControl);
}

/******************************************************************************/
/**
\brief  ODControlList - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODControlList"

                        ODControlList :: ODControlList ( )
                     : DLL(ODControl) ()
{



}

/******************************************************************************/
/**
\brief  ~ODControlList - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODControlList"

                        ODControlList :: ~ODControlList ( )
{



}


