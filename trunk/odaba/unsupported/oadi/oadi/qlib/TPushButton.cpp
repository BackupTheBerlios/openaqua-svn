/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TPushButton



\date     $Date: 2006/04/30 14:38:47,81 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TPushButton"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sCTX_Control.hpp>
#include  <sOActionControl.hpp>
#include  <sOButton.hpp>
#include  <sOCAU_Action.hpp>
#include  <sODControl.hpp>
#include  <sOElementStyle.hpp>
#include  <sOPushButton.hpp>
#include  <sOSButton.hpp>
#include  <sTField.hpp>
#include  <sUCTX_dll.hpp>
#include  <sTPushButton.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TPushButton :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TPushButton")  ? this
                                               : TWidgetControl::CastPointer(typenames) );

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

int32 TPushButton :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TPushButton();
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

logical TPushButton :: DoCreate ( )
{
  OSButton         *bstyle = Style();
  OButton          *button;
  TField           *tfield;
  OCAU_Action      *action;
  char             *act_namesc;
  char             *text;
  int8              toggle_state = 0;
  logical           def_opt = NO;
  logical           term    = NO;
BEGINSEQ
  if ( TWidgetControl::DoCreate() )                  ERROR

  text         = (char *)elementStyle->get_textDefinitions().GetTitle();
  if ( bstyle )
    toggle_state = bstyle->get_tristate() ? 3 : bstyle->get_toggle() ? 2 : 1;
  
  if ( !ProvideComplexWidget() )                     ERROR
    
  if ( button = OI_CAST(OButton,elementStyle) )
    def_opt = button->get_def_opt();
  if ( complexWidget->CreatePushButton(elementStyle->GetControlName(),text,toggle_state,
                                             def_opt,elementStyle->get_displayLevel()) )
                                                     OADIGUICERR
  complexWidget->SetExtraData(this);
  
  if ( button )
  {
    if ( !(tfield = (TField *)OwnerOfType("TField")) )
                                                     OADIERR(99)
    tfield->SetAction(button,NULL,OEH_undefined);
    complexWidget->ConnectAction(button->ActionID(),button->ActionItemID());
  }
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

logical TPushButton :: DoCreated ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !context )
    context = UDLL_Handle()->CreateControlCtx(elementStyle->get_res_id());
  context->Initialize(owner ? OI_CAST(TWidgetControl,owner)->Context() : NULL);
  context->set_control(this);
//  action_hdl.SetContext(context);
//  complexWidget->SetUserActionHdl(&action_hdl);

  if ( TWidgetControl::DoCreated() )                 ERROR



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Style

\return pOSButton

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSButton *TPushButton :: Style ( ) const
{

  return ( OI_CAST(OSButton,style) );

}

/******************************************************************************/
/**
\brief  TPushButton

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TPushButton"

     TPushButton :: TPushButton ( )
                     : TWidgetControl ()
{


}


