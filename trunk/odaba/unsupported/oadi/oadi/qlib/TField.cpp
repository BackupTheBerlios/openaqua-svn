/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TField

\brief    


\date     $Date: 2006/07/17 14:11:07,21 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#ifndef   GSRT_TAction_HPP
#define   GSRT_TAction_HPP
#include  <sTAction.hpp>
#include  <sGSRT.h>
#endif
#include  <cMOUSKEY.h>
#include  <sCTX_Control.hpp>
#include  <sOADKFactory.hpp>
#include  <sOAction.hpp>
#include  <sOCAU_Action.hpp>
#include  <sODControl.hpp>
#include  <sODataSource.hpp>
#include  <sODataWidget.hpp>
#include  <sOEventAction.hpp>
#include  <sOField.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOMenu.hpp>
#include  <sOToolBox.hpp>
#include  <sOWinAction.hpp>
#include  <sOWindow.hpp>
#include  <sTControlFactory.hpp>
#include  <sUCTX_dll.hpp>
#include  <sTField.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 



\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TField :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TField")       ? this
                                               : TWidgetControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  Close - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void TField :: Close ( )
{

  action_hdl.SetContext(NULL);
  if ( complexWidget )
    complexWidget->SetUserActionHdl(NULL,UNDEF);

  TWidgetControl::Close();

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

int32 TField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TField();
  return(0);

}

/******************************************************************************/
/**
\brief  CreateOutsideLabel - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOutsideLabel"

void TField :: CreateOutsideLabel ( )
{
  DPoint             p;
BEGINSEQ
  if ( !elementStyle->LabelPosition()->HasShowLabel() )
                                                     LEAVESEQ
  
  complexWidget->CreateLabel((DSize &)elementStyle->LabelPosition()->Size(),
                             elementStyle->LabelPosition()->VertPos(VPS_undefined),
                             elementStyle->LabelPosition()->HoriPos(HPS_undefined),
                             (char *)elementStyle->get_textDefinitions().GetTitle());

/*                                                     
  es = new OElementStyle; 
  es->Create(this,YES);
  st = new OStyle;
  st->Create(this,YES);
  fs = new OFrameStyle; 
  fs->Create(this,YES);
  es->SetStyle(st);

  a = es->Align();
  a->SetHori(elementStyle->LabelPosition()->HoriPos(HPS_undefined));
  a->SetVert(elementStyle->LabelPosition()->VertPos(VPS_undefined));
  es->SetSize(elementStyle->LabelPosition()->Size());
  
  complexWidget->CreateLabel(es->Align()->GetOrientation(),
                             es->Align()->GetEdge(),
                             (DSize &)es->Size(),
                             (char *)elementStyle->get_textDefinitions().GetTitle());
*/
ENDSEQ

}

/******************************************************************************/
/**
\brief  DoCreate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TField :: DoCreate ( )
{
  logical              term = NO;
BEGINSEQ
  if ( TWidgetControl::DoCreate() )                     ERROR

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

logical TField :: DoCreated ( )
{
  OField          *ofield      = OI_CAST(OField,elementStyle);
  char            *struct_name = NULL;
  char             sname[ID_SIZE+1];
  ODataSource     *odsource    = NULL;
  logical          term        = NO;
BEGINSEQ
  if ( !complexWidget )                              LEAVESEQ
    
  if ( !context )
    context = UDLL_Handle()->CreateControlCtx(elementStyle->get_res_id());
  context->Initialize(owner ? OI_CAST(TWidgetControl,owner)->Context() : NULL);
  context->set_control(this);
  action_hdl.SetContext(context);

// the subsequent line requires 97% of time for the whole function !!!!
  complexWidget->SetUserActionHdl(&action_hdl,context->IsUserContext());

  if ( TWidgetControl::DoCreated() )                 ERROR

  CreateOutsideLabel();

  if ( odsource = elementStyle->GetDataSource() )
    struct_name = odsource->get_structureName();

  if ( ofield )
  {
    complexWidget->SetControlProperties(ofield->get_dynamic(),ofield->get_output(),
                                        ofield->get_cache(),ofield->get_length());
    if ( !struct_name )
      struct_name = gvtxbts(sname,ofield->GetAccessClassName(),ID_SIZE);
  }

  complexWidget->SetPath(odsource ? (char *)odsource->GetPath()   : NULL,
                         struct_name,
                         odsource ? odsource->get_isCollection()  : NO,
                         odsource ? odsource->get_sortOrder()     : NULL,
                         odsource ? odsource->GetPathType ()      : PT_undefined,
                         odsource ? odsource->get_accmode()       : PI_Read);
  if ( odsource && odsource->get_baseCollection() )
    complexWidget->SetBasePath(odsource->get_baseCollection());

  if ( odsource && odsource->get_dataPH().IsValid() )
    complexWidget->SetDataSource(odsource->get_dataPH().GetObjectHandle());
  
  SetupReactions();
  SetupToolbars();
  SetupContextMenu();
  SetupMenu();
  
  if ( elementStyle->IsDisabled() )
    complexWidget->SetDisabled(YES);
  if ( elementStyle->IsHidden() )
    complexWidget->SetHidden(YES);
  complexWidget->SetReadOnly(complexWidget->IsReadOnly());
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EventFrame - 



\return event_frame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventFrame"

OEH_Frame TField :: EventFrame ( )
{

  return(OEH_Widget);

}

/******************************************************************************/
/**
\brief  SetAction - 



\return term - 

\param  pOEventAction - 
\param  parent_action - 
\param  event_frame - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

logical TField :: SetAction (OEventAction *pOEventAction, OEventAction *parent_action, OEH_Frame event_frame )
{

  action_hdl.SetAction(pOEventAction->ActionID(),
                       &pOEventAction->get_default_action());
  TWidgetControl::SetAction(pOEventAction,parent_action,EventFrame());
  return(NO);
}

/******************************************************************************/
/**
\brief  SetupContextMenu - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupContextMenu"

logical TField :: SetupContextMenu ( )
{
  OMenu        *context_menu;
  logical       term  = NO;
  if ( context_menu = OI_CAST(OStyleAction,elementStyle)->ContextMenu() )
  {
    SetAction(context_menu,NULL,EventFrame());
    complexWidget->CreateContextMenu(context_menu->ActionID(),
                                     context_menu->ActionItemID());
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetupMenu - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupMenu"

logical TField :: SetupMenu ( )
{
  OMenu        *menu;
  logical       term  = NO;
  if ( menu = OI_CAST(OStyleAction,elementStyle)->Menu() )
  {
    SetAction(menu,NULL,EventFrame());
    complexWidget->CreateMenuBar(menu->ActionID(),
                                 menu->ActionItemID());
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetupReactions - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReactions"

logical TField :: SetupReactions ( )
{
  DLL(OEventAction)     *reactions = NULL;
  OEventAction          *action    = NULL;
  logical                term      = NO;
  if ( reactions = OI_CAST(OStyleAction,elementStyle)->Reactions() )
  {
    reactions->GoTop();
    while ( action = reactions->GetNext() )
      SetAction(action,NULL,EventFrame());
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetupToolbars - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupToolbars"

logical TField :: SetupToolbars ( )
{
  DLL(OToolBox)       *toolbars;
  OEventAction        *action;
  OCAU_Action         *oact;
  OMenu               *context_menu;
  char                *act_names;
  logical              term     = NO;
  if ( toolbars = OI_CAST(OStyleAction,elementStyle)->Toolbars() )
  {
    toolbars->GoTop();
    while ( action = toolbars->GetNext() )
    {
      SetAction(action,NULL,EventFrame());
      complexWidget->CreateToolBar(action->ActionID(),
                                   action->ActionItemID());
      
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Show - 




\param  fShow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

void TField :: Show (logical fShow )
{

  TWidgetControl::Show(fShow);


}

/******************************************************************************/
/**
\brief  TField - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TField"

     TField :: TField ( )
                     : TWidgetControl (),
  action_hdl()
{



}

/******************************************************************************/
/**
\brief  ~TField - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TField"

     TField :: ~TField ( )
{

  Deleting();
  Close();

}


