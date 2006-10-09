/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TWidgetControl

\brief    


\date     $Date: 2006/08/26 17:29:46,25 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TWidgetControl"

#include  <poadi.h>
#include  <cmacros.h>
#ifndef   DLL_TWidgetControl_HPP
#define   DLL_TWidgetControl_HPP
#include  <sTWidgetControl.hpp>
#include  <sDLL.h>
#endif
#include  <sCTX_Control.hpp>
#include  <sDPixmap.hpp>
#include  <sOButton.hpp>
#include  <sOButtonControl.hpp>
#include  <sOCBitmap.hpp>
#include  <sODControl.hpp>
#include  <sODSItem.hpp>
#include  <sODWindow.hpp>
#include  <sODataWidget.hpp>
#include  <sODialog.hpp>
#include  <sOElementStyle.hpp>
#include  <sOEventAction.hpp>
#include  <sOField.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFont_.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOStyle.hpp>
#include  <sOWidget.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sOWidgetDesignModeFactory.hpp>
#include  <sOWindow.hpp>
#include  <sTField.hpp>
#include  <sTProjectManager.hpp>
#include  <sTWidgetControl.hpp>
#include  <ioadii.h>
#include  <sTWidgetControl.hpp>


/******************************************************************************/
/**
\brief  AcceptDrops - 




\param  drop_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AcceptDrops"

void TWidgetControl :: AcceptDrops (logical drop_opt )
{

  if ( this && complexWidget )
    complexWidget->SetAcceptDrops(drop_opt);


}

/******************************************************************************/
/**
\brief  Activate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

void TWidgetControl :: Activate ( )
{

//  UpdateLayout();

  if ( complexWidget )
  {
    complexWidget->Activate();
  
    Show(!elementStyle->IsHidden());
  }

}

/******************************************************************************/
/**
\brief  ActiveAction - 



\return minames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActiveAction"

char *TWidgetControl :: ActiveAction ( )
{

  return (   this && complexWidget 
           ? complexWidget->GetActiveAction()
           : NULL   );

}

/******************************************************************************/
/**
\brief  ActiveActionItem - 



\return minames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActiveActionItem"

char *TWidgetControl :: ActiveActionItem ( )
{

  return (   this && complexWidget 
           ? complexWidget->GetActiveActionItem()
           : NULL   );

}

/******************************************************************************/
/**
\brief  AddColumn - 



\return column_id - 

\param  region_id - 
\param  prop_path - 
\param  text - 
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

int32 TWidgetControl :: AddColumn (int32 region_id, char *prop_path, char *text, ADK_DataReferenceType ref_type )
{
  OListLayout            *column;
  int32                   column_id = 0;
  if ( complexWidget )
    if ( column = complexWidget->AddColumn(region_id,prop_path,text,
                                           GetPropPathType(prop_path,ref_type)) )
      column_id = column->get_intern_id();

  return(column_id);
}

/******************************************************************************/
/**
\brief  AddInputHelp - 



\return ctl_context - 

\param  class_name - 
\param  ctl_names - 
\param  activate_strings - 
\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInputHelp"

CTX_Control *TWidgetControl :: AddInputHelp (char *class_name, char *ctl_names, VECTOR(std_string) &activate_strings, PropertyHandle *prophdl )
{
  TWidgetControl     *control = NULL;
BEGINSEQ
  if ( !this || !complexWidget )                     ERROR
  
  if ( !input_help )
    input_help = new DLL(TWidgetControl);

  if ( !(control = ::CreateInputHelp(class_name,ctl_names,this)) )
                                                     ERROR
  input_help->AddTail(control);
  
  if ( prophdl )
    control->SetPropertyHandle(prophdl,NO);
    
  if ( complexWidget->AddInputHelp(control->get_complexWidget(),
                                   activate_strings) )    
                                                     ERROR
RECOVER

ENDSEQ
  return(control ? control->get_context() : NULL);
}

/******************************************************************************/
/**
\brief  AddRegion - 



\return region_id - 

\param  parent_id - 
\param  prop_path - 
\param  text - 
\param  is_collection - 
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

int32 TWidgetControl :: AddRegion (int32 parent_id, char *prop_path, char *text, logical is_collection, ADK_DataReferenceType ref_type )
{

  return ( complexWidget 
           ? complexWidget->AddRegion(parent_id,prop_path,is_collection,text,
                                      GetPropPathType(prop_path,ref_type))
           : UNDEF );


}

/******************************************************************************/
/**
\brief  AssociateData - 



\return term - 

\param  source_ph - 
\param  control_name - 
\param  title - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AssociateData"

logical TWidgetControl :: AssociateData (PropertyHandle *source_ph, char *control_name, char *title )
{

  return (   this && complexWidget 
           ? complexWidget->AssociateData(source_ph,control_name,title)
           : NULL   );

}

/******************************************************************************/
/**
\brief  CastPointer - 



\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TWidgetControl :: CastPointer (char *typenames )
{

  return (   !typenames                           ? NULL
           : !strcmp(typenames,"TWidgetControl")  ? this
                                                  : TControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  Close - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void TWidgetControl :: Close ( )
{
  TWidgetControl     *control = NULL;
  if ( context )
  {
    context->ResetControl();
    delete context;
    context = NULL;
  }
  
  if ( complexWidget && input_help )
  {
    if ( input_help )
    {
      while ( control = input_help->RemoveTail() )
      {
        complexWidget->RemoveInputHelp(control->get_complexWidget());
        delete control;
      }
      delete input_help;
      input_help = NULL;
    }
    complexWidget->Destroy();
    complexWidget = NULL;
  }

  TControl::Close();


}

/******************************************************************************/
/**
\brief  ComplexWidgetOwner - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ComplexWidgetOwner"

ODControl *TWidgetControl :: ComplexWidgetOwner ( )
{
  TWidgetControl    *otwc = (TWidgetControl *)OwnerOfType("TWidgetControl");
  return ( otwc ? otwc->get_complexWidget() : NULL );

}

/******************************************************************************/
/**
\brief  ComplexWidgetParent - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ComplexWidgetParent"

ODControl *TWidgetControl :: ComplexWidgetParent ( )
{
  TWidgetControl    *otwc ;
  ODControl         *pODControl = NULL;

  if ( otwc = OI_CAST(TWidgetControl,Owner()) )
    pODControl = otwc->get_complexWidget();

  return(pODControl);
}

/******************************************************************************/
/**
\brief  Context - 



\return context - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Context"

CTX_Control *TWidgetControl :: Context ( )
{

  return(this ? context : NULL);

}

/******************************************************************************/
/**
\brief  ControlWidgetParent - 



\return pODataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ControlWidgetParent"

ODataWidget *TWidgetControl :: ControlWidgetParent ( )
{

  return ( ComplexWidgetParent()->ClientWidgetParent() );

}

/******************************************************************************/
/**
\brief  CreateButton - 



\return ctl_context - 

\param  class_ph - 
\param  name - 
\param  position - 
\param  resource_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateButton"

CTX_Control *TWidgetControl :: CreateButton (PropertyHandle &class_ph, char *name, DPoint position, int resource_id )
{
  PropertyHandle          ctl_ph(class_ph.GPH("controls"));
  PropertyHandle          button_ph(ctl_ph.GPH("buttons"));
  char                    buffer[ID_SIZE];
  TWidgetControl         *control;
  CTX_Control            *ctl_context = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !class_ph(((OFieldControl *)elementStyle)->get_class_name())     ||
       !ctl_ph(gvtxstb(buffer,complexWidget->GetControlName(),sizeof(buffer))) ||
       !button_ph(gvtxstb(buffer,name,sizeof(buffer))) )
                                                     ERROR
  if ( !(control = ::CreateButton(&button_ph,this,position,resource_id)) )
                                                     ERROR
  ctl_context = control->get_context();
RECOVER
  ctl_context = NULL;
ENDSEQ
  return(ctl_context);
}

/******************************************************************************/
/**
\brief  CreateConstant - 



\return term - 

\param  class_ph - 
\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateConstant"

logical TWidgetControl :: CreateConstant (PropertyHandle &class_ph, char *name )
{
  PropertyHandle          ctl_ph(class_ph.GPH("controls"));
  PropertyHandle          const_ph(ctl_ph.GPH("constants"));
  char                    buffer[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !class_ph(((OFieldControl *)elementStyle)->get_class_name()) ||
       !ctl_ph(gvtxstb(buffer,complexWidget->GetControlName(),sizeof(buffer))) ||
       !const_ph(gvtxstb(buffer,name,sizeof(buffer))) )
                                                     ERROR
  if ( !::CreateConstant(&const_ph,this) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateField - 



\return ctl_context - 

\param  class_ph - 
\param  name - 
\param  position - 
\param  design_mode - 
\param  resource_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField"

CTX_Control *TWidgetControl :: CreateField (PropertyHandle &class_ph, char *name, DPoint position, logical design_mode, int resource_id )
{
  PropertyHandle          ctl_ph(class_ph.GPH("controls"));
  PropertyHandle          field_ph(ctl_ph.GPH("fields"));
  char                    buffer[ID_SIZE];
  TWidgetControl         *control;
  CTX_Control            *ctl_context = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !class_ph(((OFieldControl *)elementStyle)->get_class_name())     ||
       !ctl_ph(gvtxstb(buffer,complexWidget->GetControlName(),sizeof(buffer))) ||
       !field_ph(gvtxstb(buffer,name,sizeof(buffer))) )
                                                     ERROR
  if ( !(control = ::CreateField(&field_ph,this,position,design_mode,resource_id)) )
                                                     ERROR
  ctl_context = control->get_context();
RECOVER
  ctl_context = NULL;
ENDSEQ
  return(ctl_context);
}

/******************************************************************************/
/**
\brief  Deactivate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

void TWidgetControl :: Deactivate ( )
{

//  UpdateLayout();

  if ( complexWidget )
    complexWidget->Deactivate();
  


}

/******************************************************************************/
/**
\brief  DoCreate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TWidgetControl :: DoCreate ( )
{
  ADK_WinType    wstyle;
  logical        term = NO;
BEGINSEQ
  if ( TControl::DoCreate() )                        ERROR

  switch( wstyle = frameStyle->WinType(WT_Simple) )
  {
    case WT_Dialog    :
    case WT_Hierarchy :
    case WT_Popup     :
    case WT_Tool      :
        
        if ( !complexWidget )
          complexWidget = new ODWindow(ComplexWidgetParent(),elementStyle->get_sys_ident());
        
        complexWidget->CreateWindowArea(                  // frameInnerWidget und frameOuterWidget !!
             elementStyle->GetControlName(),
             frameStyle->IsSystemModal(),(OWindowTypes)wstyle);
        break;
       
    case WT_Simple   :
    default          : ;
  }

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

logical TWidgetControl :: DoCreated ( )
{
  OFieldControl          *fctl;
  DSize                   grid_size;
  DMargin                 dm;
  logical                 term = NO;

BEGINSEQ
  if ( complexWidget ) 
  {
    elementStyle->OElementStyle::SetupListLayout(complexWidget->GetLayout());
    elementStyle->SetupTreeLayout(complexWidget->GetListLayout(),YES);
    
    complexWidget->SetAcceptDrops(elementStyle->get_accept_drop());
    if ( fctl = OI_CAST(OFieldControl,elementStyle) )
      grid_size = fctl->get_grid_size();
    complexWidget->CreateLayout(grid_size,fctl ? fctl->Align()->get_margin() : dm);
  }
//  UpdateLayout();

  if ( TControl::DoCreated() )                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EnableDesignMode - 



\return designer_mode - 

\param  dmode_factory - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableDesignMode"

OWidgetDesignModeBase *TWidgetControl :: EnableDesignMode (OWidgetDesignModeFactory *dmode_factory )
{

  return (   complexWidget
           ? complexWidget->WidgetFrame()->EnableDesignMode(dmode_factory) 
           : NULL );

}

/******************************************************************************/
/**
\brief  EnableInputHelp - 



\return term - 

\param  enable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableInputHelp"

logical TWidgetControl :: EnableInputHelp (logical enable_opt )
{
  logical      term = NO;
BEGINSEQ
  if ( !this || !complexWidget )                     ERROR
  if ( !input_help )                                 LEAVESEQ
    
  complexWidget->EnableInputHelp(enable_opt);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteDefaultAction - 



\return executed - How was function exetuted

\param  act_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDefaultAction"

char TWidgetControl :: ExecuteDefaultAction (char *act_names )
{

  return ( complexWidget->ExecuteDefaultAction(act_names) );

}

/******************************************************************************/
/**
\brief  FillControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillControl"

logical TWidgetControl :: FillControl ( )
{
  logical                 term = NO;
  complexWidget->DA_Refresh();
  return(term);
}

/******************************************************************************/
/**
\brief  GetActiveControl - 



\return pTWidgetControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveControl"

TWidgetControl *TWidgetControl :: GetActiveControl ( )
{
  ODControl    *pODControl;
  return (   complexWidget && 
             (pODControl = complexWidget->GetActiveControl())
           ? (TWidgetControl *)pODControl->ExtraData()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetBasePropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBasePropertyHandle"

PropertyHandle *TWidgetControl :: GetBasePropertyHandle ( )
{

  return ( complexWidget->GetBasePropertyHandle() );

}

/******************************************************************************/
/**
\brief  GetButton - 



\return pTWidgetControl - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetButton"

TWidgetControl *TWidgetControl :: GetButton (char *control_name )
{
  ODControl    *pODControl;
  return (   complexWidget && 
             (pODControl = complexWidget->GetButton(control_name))
           ? (TWidgetControl *)pODControl->ExtraData()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetColumnPropertyHandle - 



\return ph - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetColumnPropertyHandle"

PropertyHandle *TWidgetControl :: GetColumnPropertyHandle (int column )
{

  return (   this && complexWidget
           ? complexWidget->GetColumnPropertyHandle(column) 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetConstant - 



\return pTWidgetControl - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConstant"

TWidgetControl *TWidgetControl :: GetConstant (char *control_name )
{
  ODControl    *pODControl;
  return (   complexWidget && 
             (pODControl = complexWidget->GetConstant(control_name))
           ? (TWidgetControl *)pODControl->ExtraData()
           : NULL );


}

/******************************************************************************/
/**
\brief  GetContext - 



\return ctx_ctl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Control *TWidgetControl :: GetContext ( )
{

  return ( context );

}

/******************************************************************************/
/**
\brief  GetControl - 



\return pTWidgetControl - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControl"

TWidgetControl *TWidgetControl :: GetControl (char *control_name )
{
  ODControl    *pODControl;
  return (   complexWidget && 
             (pODControl = complexWidget->GetControl(control_name))
           ? (TWidgetControl *)pODControl->ExtraData()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetControlName - 



\return control_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlName"

char *TWidgetControl :: GetControlName ( )
{
  OField       *ofield;
  char         *names = NULL;
BEGINSEQ
  if ( !elementStyle )                               ERROR
  if ( !(ofield = OI_CAST(OField,elementStyle)) )   ERROR
  if ( !ofield->get_fieldControl() )                 ERROR
  
  names = ofield->get_fieldControl()->get_sys_ident();

RECOVER
  names = NULL;
ENDSEQ
  return(names);
}

/******************************************************************************/
/**
\brief  GetCurrentControl - 



\return pTWidgetControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentControl"

TWidgetControl *TWidgetControl :: GetCurrentControl ( )
{
  ODControl    *pODControl;
  return (   complexWidget && 
             (pODControl = complexWidget->GetCurrentControl())
           ? (TWidgetControl *)pODControl->ExtraData()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetCurrentPropertyHandle - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentPropertyHandle"

PropertyHandle *TWidgetControl :: GetCurrentPropertyHandle ( )
{

  return (   this && complexWidget
           ? complexWidget->GetCurrentPropertyHandle() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetCurrentRegionID - 



\return region_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentRegionID"

int32 TWidgetControl :: GetCurrentRegionID ( )
{

  return ( complexWidget 
           ? complexWidget->GetCurrentRegionID()
           : UNDEF );

}

/******************************************************************************/
/**
\brief  GetDSPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDSPropertyHandle"

PropertyHandle *TWidgetControl :: GetDSPropertyHandle ( )
{

  return ( complexWidget->GetDSPropertyHandle() );

}

/******************************************************************************/
/**
\brief  GetData - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

PropertyHandle *TWidgetControl :: GetData ( )
{

  return (   this && complexWidget
           ? complexWidget->GetValue() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetDecision - 



\return button0 - 

\param  szTitle - 
\param  szText - 
\param  button0 - 
\param  button1 - 
\param  button2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

int TWidgetControl :: GetDecision (char *szTitle, char *szText, int button0, int button1, int button2 )
{

  return ( complexWidget->GetDecision(szTitle,szText,
                                      button0,button1,button2) );

}

/******************************************************************************/
/**
\brief  GetDesignMode - 



\return designer_mode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDesignMode"

OWidgetDesignModeBase *TWidgetControl :: GetDesignMode ( )
{

  return (   complexWidget
           ? complexWidget->WidgetFrame()->GetDesignMode() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetDisplayLevel - 



\return dsp_level - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDisplayLevel"

int16 TWidgetControl :: GetDisplayLevel ( )
{

  return (   complexWidget 
           ? complexWidget->GetDisplayLevel()
           : UNDEF                           );

}

/******************************************************************************/
/**
\brief  GetDropIndex - 



\return index - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropIndex"

int32 TWidgetControl :: GetDropIndex ( )
{

  return ( complexWidget->GetDropIndex() );

}

/******************************************************************************/
/**
\brief  GetDropPoint - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropPoint"

DPoint TWidgetControl :: GetDropPoint ( )
{

  return ( complexWidget->GetDropPoint() );

}

/******************************************************************************/
/**
\brief  GetDropPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropPropertyHandle"

PropertyHandle *TWidgetControl :: GetDropPropertyHandle ( )
{

  return ( complexWidget->GetDropPropertyHandle() );

}

/******************************************************************************/
/**
\brief  GetDropText - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropText"

char *TWidgetControl :: GetDropText ( )
{

  return ( complexWidget->GetDropText() );

}

/******************************************************************************/
/**
\brief  GetField - 



\return pTWidgetControl - 

\param  field_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetField"

TWidgetControl *TWidgetControl :: GetField (char *field_name )
{
  ODControl    *pODControl;
  return (   complexWidget && 
             (pODControl = complexWidget->GetField(field_name))
           ? (TWidgetControl *)pODControl->ExtraData()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetFont - 



\return font - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

DFont TWidgetControl :: GetFont ( )
{
  DFont          empty;
  return (   complexWidget 
           ? complexWidget->GetFont()
           : empty                        );

}

/******************************************************************************/
/**
\brief  GetInitPropertyHandle - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitPropertyHandle"

PropertyHandle *TWidgetControl :: GetInitPropertyHandle ( )
{

  return (   this && complexWidget
           ? complexWidget->GetInitPropertyHandle() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetKey - 



\return skey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

const char *TWidgetControl :: GetKey ( )
{

  return ( complexWidget->GetListValue() );

}

/******************************************************************************/
/**
\brief  GetLineFont - 



\return font - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLineFont"

DFont TWidgetControl :: GetLineFont (int column )
{
  DFont                  empty;
  return (   complexWidget 
           ? complexWidget->GetLineFont(column)
           : empty                        );

}

/******************************************************************************/
/**
\brief  GetMousePosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMousePosition"

DPoint TWidgetControl :: GetMousePosition ( )
{

  return ( complexWidget->GetMousePosition() );

}

/******************************************************************************/
/**
\brief  GetPosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

DPoint TWidgetControl :: GetPosition ( )
{
  DPoint                  position;
  return ( complexWidget 
           ? complexWidget->GetTextPosition()
           : position );

}

/******************************************************************************/
/**
\brief  GetSize - 



\return dsize - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

DSize TWidgetControl :: GetSize ( )
{

  return ( this && complexWidget ? complexWidget->GetSize() : DSize() );


}

/******************************************************************************/
/**
\brief  GetSubRegionCount - 



\return count - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int32 TWidgetControl :: GetSubRegionCount (int32 region_id )
{

  return ( complexWidget 
           ? complexWidget->GetSubRegionCount(region_id)
           : UNDEF );

}

/******************************************************************************/
/**
\brief  HasFocus - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFocus"

logical TWidgetControl :: HasFocus ( )
{

  return (   complexWidget 
           ? complexWidget->HasFocus()
           : YES                       );

}

/******************************************************************************/
/**
\brief  IsActionDisabled - 



\return cond - 

\param  act_names - 
\param  loid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionDisabled"

logical TWidgetControl :: IsActionDisabled (char *act_names, char *loid )
{

  return (   complexWidget
           ? complexWidget->IsActionDisabled(act_names,loid) 
           : NO );

}

/******************************************************************************/
/**
\brief  IsActionToggled - 



\return cond - 

\param  act_names - 
\param  loid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionToggled"

logical TWidgetControl :: IsActionToggled (char *act_names, char *loid )
{

  return (   complexWidget
           ? complexWidget->IsActionToggled(act_names,loid) 
           : NO );

}

/******************************************************************************/
/**
\brief  IsActionVisible - 



\return cond - 

\param  act_names - 
\param  loid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionVisible"

logical TWidgetControl :: IsActionVisible (char *act_names, char *loid )
{

  return (   complexWidget
           ? complexWidget->IsActionVisible(act_names,loid) 
           : NO );

}

/******************************************************************************/
/**
\brief  IsLocalDrop - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalDrop"

logical TWidgetControl :: IsLocalDrop ( )
{

  return ( complexWidget->IsLocalDrop() );

}

/******************************************************************************/
/**
\brief  LoadDynamicControl - 



\return term - 

\param  class_name - 
\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadDynamicControl"

logical TWidgetControl :: LoadDynamicControl (char *class_name, char *control_name )
{
  TWidgetControl         *tc = NULL;
  DatabaseHandle         &resdb = TProjectManager::TPM->UCB()->sdbures->dbhandle;
  PropertyHandle          classes(resdb,"ADK_Class",PI_Read);
  PropertyHandle          controls(&classes,"controls");
  ODataSource             data_source;
  ODControl              *odc;
  logical                 term = NO;
BEGINSEQ
  data_source.set_referenceType(DRT_UserDefined);
  data_source.set_isCollection(NO);
  data_source.set_structureName(class_name);
  data_source.set_dataReference("");
  
  PropertyHandle  cln(class_name);
  if ( !classes(cln) )                               ERROR
  
  if ( !control_name )
    if ( odc = complexWidget->GetChildControl(0) )
      control_name = odc->GetControlName();
  if ( !control_name )
    control_name = "dyn_edit";
  PropertyHandle  con(control_name);
  if ( !controls(con) )                              ERROR

  tc = CreateField_intern(control_name,&controls,this,GetSize(),
                          DPoint(0,0),AUTO,NO,AUTO,&data_source,NO);
  if ( !tc )                                         ERROR    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideComplexWidget - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideComplexWidget"

ODControl *TWidgetControl :: ProvideComplexWidget ( )
{
  char        *names = "";
BEGINSEQ
  if ( complexWidget )                               LEAVESEQ
      
  if ( !(complexWidget = new ODControl(ComplexWidgetParent(),elementStyle->get_sys_ident())) )
  {
    OADIERR(95)
    OADIGUICERR
  }
RECOVER
  delete complexWidget;
  complexWidget = NULL;
ENDSEQ
  return(complexWidget);
}

/******************************************************************************/
/**
\brief  ReceiveSelectedItem - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReceiveSelectedItem"

PropertyHandle *TWidgetControl :: ReceiveSelectedItem ( )
{

  return (   this && complexWidget
           ? complexWidget->ReceiveSelectedItem() 
           : NULL );

}

/******************************************************************************/
/**
\brief  RefreshRegion - 




\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshRegion"

void TWidgetControl :: RefreshRegion (int32 region_id )
{

  if ( complexWidget )
    complexWidget->RefreshRegion(region_id);


}

/******************************************************************************/
/**
\brief  RemoveButton - 



\return term - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveButton"

logical TWidgetControl :: RemoveButton (char *name )
{

  return( complexWidget->RemoveButton(name) ? NO : YES );

}

/******************************************************************************/
/**
\brief  RemoveColumn - 



\return term - 

\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveColumn"

logical TWidgetControl :: RemoveColumn (int32 region_id, int32 column_id )
{

  return ( complexWidget 
           ? complexWidget->RemoveColumn(region_id,column_id)
           : UNDEF );

}

/******************************************************************************/
/**
\brief  RemoveComplexWidget - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveComplexWidget"

void TWidgetControl :: RemoveComplexWidget ( )
{

  delete complexWidget;
  complexWidget = NULL;

}

/******************************************************************************/
/**
\brief  RemoveConstant - 



\return term - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveConstant"

logical TWidgetControl :: RemoveConstant (char *name )
{

  return( complexWidget->RemoveConstant(name) ? NO : YES );

}

/******************************************************************************/
/**
\brief  RemoveField - 



\return term - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveField"

logical TWidgetControl :: RemoveField (char *name )
{

  return( complexWidget->RemoveField(name) ? NO : YES );

}

/******************************************************************************/
/**
\brief  ReplaceSubRegions - 



\return region_id - 

\param  parent_id - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSubRegions"

int32 TWidgetControl :: ReplaceSubRegions (int32 parent_id, int32 region_id )
{

  return ( complexWidget 
           ? complexWidget->ReplaceSubRegions(parent_id,region_id)
           : UNDEF );


}

/******************************************************************************/
/**
\brief  ResetRegion - 



\return term - 

\param  parent_id - 
\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRegion"

logical TWidgetControl :: ResetRegion (int32 parent_id, int32 region_id, logical reset_columns )
{

  return ( complexWidget 
           ? complexWidget->ResetRegion(parent_id,region_id,reset_columns)
           : UNDEF );

}

/******************************************************************************/
/**
\brief  SearchKey - 



\return term - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchKey"

logical TWidgetControl :: SearchKey (char *skey )
{

  return (   complexWidget 
           ? complexWidget->DA_FindEntry(skey)
           : YES                               );

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

logical TWidgetControl :: SetAction (OEventAction *pOEventAction, OEventAction *parent_action, OEH_Frame event_frame )
{
  logical                 term = NO;
BEGINSEQ
  if ( pOEventAction->SetAction(this,parent_action,event_frame) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionDisabled - 



\return cond - 

\param  act_names - 
\param  loid - 
\param  fDisable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionDisabled"

logical TWidgetControl :: SetActionDisabled (char *act_names, char *loid, logical fDisable )
{
  logical          term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
           
  complexWidget->SetActionDisabled(act_names,loid,fDisable);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionToggled - 



\return cond - 

\param  act_names - 
\param  loid - 
\param  fEnable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionToggled"

logical TWidgetControl :: SetActionToggled (char *act_names, char *loid, logical fEnable )
{
  logical          term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
           
  complexWidget->SetActionToggled(act_names,loid,fEnable);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActionVisible - 



\return cond - 

\param  act_names - 
\param  loid - 
\param  fEnable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionVisible"

logical TWidgetControl :: SetActionVisible (char *act_names, char *loid, logical fEnable )
{
  logical          term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
           
  complexWidget->SetActionVisible(act_names,loid,fEnable);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetBackgroundColor - 



\return term - 

\param  rDColor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBackgroundColor"

logical TWidgetControl :: SetBackgroundColor (DColor &rDColor )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetBackgroundColor(rDColor);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetColumnFont - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font - 
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnFont"

logical TWidgetControl :: SetColumnFont (DFont *font, int32 region_id, int32 column_id )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetColumnFont(font,region_id,column_id);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - 
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnFont"

logical TWidgetControl :: SetColumnFont (char *font_name, int32 region_id, int32 column_id )
{
  OFont_                 *font;
  logical                 term = NO;
BEGINSEQ
  if ( !(font = OFont_::ReadFromResource(font_name)) )
                                                     ERROR
  term = SetColumnFont(font,region_id,column_id);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetColumnPixmap - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pixmap - 
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnPixmap"

logical TWidgetControl :: SetColumnPixmap (DPixmap *pixmap, int32 region_id, int32 column_id )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetColumnPixmap(pixmap,region_id,column_id);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pixmap_name - 
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnPixmap"

logical TWidgetControl :: SetColumnPixmap (char *pixmap_name, int32 region_id, int32 column_id )
{
  OCBitmap               *bitmap = NULL;
  logical                 term   = NO;
BEGINSEQ
  if ( !(bitmap = OCBitmap::ReadFromResource(pixmap_name)) )
                                                     ERROR
  term = SetColumnPixmap(bitmap->GetActiveBitmap(),region_id,column_id);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetData - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical TWidgetControl :: SetData ( )
{

  return (   this && complexWidget
           ? complexWidget->SetValue() 
           : NULL );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical TWidgetControl :: SetData (PropertyHandle *prophdl )
{

  return (   this && complexWidget
           ? complexWidget->SetValue(prophdl) 
           : NULL );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical TWidgetControl :: SetData (char *string )
{

  return (   this && complexWidget
           ? complexWidget->SetValue(string) 
           : NULL );

}

/******************************************************************************/
/**
\brief  SetDatabaseHandle - 



\return term - 

\param  db_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDatabaseHandle"

logical TWidgetControl :: SetDatabaseHandle (DatabaseHandle &db_handle )
{

  return ( complexWidget 
           ? complexWidget->SetDatabaseHandle(db_handle)
           : YES );

}

/******************************************************************************/
/**
\brief  SetDisabled - 




\param  disable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisabled"

void TWidgetControl :: SetDisabled (logical disable )
{

  if ( complexWidget )
    complexWidget->SetDisabled(disable);

}

/******************************************************************************/
/**
\brief  SetDisplayLevel - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical TWidgetControl :: SetDisplayLevel (int16 dsp_level )
{

  return (   complexWidget 
           ? complexWidget->SetDisplayLevel(dsp_level)
           : YES                               );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical TWidgetControl :: SetDisplayLevel (char *typenames )
{

  return (   complexWidget 
           ? complexWidget->SetDisplayLevel(typenames)
           : YES                               );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical TWidgetControl :: SetDisplayLevel (PropertyHandle *prophdl )
{

  return (   complexWidget 
           ? complexWidget->SetDisplayLevel(prophdl)
           : YES                               );

}

/******************************************************************************/
/**
\brief  SetFilter - 



\return term - 

\param  expression - 
\param  enable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical TWidgetControl :: SetFilter (char *expression, logical enable_opt )
{

  return (   complexWidget 
           ? complexWidget->SetFilter(expression,enable_opt)
           : YES );


}

/******************************************************************************/
/**
\brief  SetFocus - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFocus"

logical TWidgetControl :: SetFocus ( )
{

  return (   complexWidget 
           ? complexWidget->SetFocus()
           : YES                       );

}

/******************************************************************************/
/**
\brief  SetFont - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

logical TWidgetControl :: SetFont (DFont *font )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetFont(font);
  complexWidget->SetupFont();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

logical TWidgetControl :: SetFont (char *font_name )
{
  OFont_                 *font;
  logical                 term = NO;
BEGINSEQ
  if ( !(font = OFont_::ReadFromResource(font_name)) )
                                                     ERROR
  term = SetFont(font);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetHidden - 




\param  hidden - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHidden"

void TWidgetControl :: SetHidden (logical hidden )
{

  if ( complexWidget )
    complexWidget->SetHidden(hidden);

}

/******************************************************************************/
/**
\brief  SetLineFont - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical TWidgetControl :: SetLineFont (DFont *font, int32 column_id )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetLineFont(font,column_id);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical TWidgetControl :: SetLineFont (char *font_name, int32 column_id )
{
  OFont_                 *font;
  logical                 term = NO;
BEGINSEQ
  if ( !(font = OFont_::ReadFromResource(font_name)) )
                                                     ERROR
  term = SetLineFont(font,column_id);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetLinePixmap - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pixmap - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLinePixmap"

logical TWidgetControl :: SetLinePixmap (DPixmap *pixmap, int32 column_id )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetLinePixmap(pixmap,column_id);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pixmap_name - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLinePixmap"

logical TWidgetControl :: SetLinePixmap (char *pixmap_name, int32 column_id )
{
  OCBitmap               *bitmap = NULL;
  logical                 term   = NO;
BEGINSEQ
  if ( !(bitmap = OCBitmap::ReadFromResource(pixmap_name)) )
                                                     ERROR
  term = SetLinePixmap(bitmap->GetActiveBitmap(),column_id);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPosition - 




\param  position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void TWidgetControl :: SetPosition (DPoint position )
{

  if ( complexWidget )
    complexWidget->SetTextPosition(position);

}

/******************************************************************************/
/**
\brief  SetPropertyHandle - 



\return term - 

\param  prophdl - 
\param  auto_select - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical TWidgetControl :: SetPropertyHandle (PropertyHandle *prophdl, logical auto_select )
{

  return(complexWidget->SetPropertyHandle(prophdl,auto_select));

}

/******************************************************************************/
/**
\brief  SetReadOnly - 




\param  read_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void TWidgetControl :: SetReadOnly (logical read_only )
{

  if ( complexWidget )
    complexWidget->SetReadOnly(read_only);

}

/******************************************************************************/
/**
\brief  SetRegionFont - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionFont"

logical TWidgetControl :: SetRegionFont (DFont *font, int32 region_id )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetRegionFont(font,region_id);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionFont"

logical TWidgetControl :: SetRegionFont (char *font_name, int32 region_id )
{
  OFont_                 *font;
  logical                 term = NO;
BEGINSEQ
  if ( !(font = OFont_::ReadFromResource(font_name)) )
                                                     ERROR
  term = SetRegionFont(font,region_id);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetRegionPixmap - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pixmap - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionPixmap"

logical TWidgetControl :: SetRegionPixmap (DPixmap *pixmap, int32 region_id )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetRegionPixmap(pixmap,region_id);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pixmap_name - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionPixmap"

logical TWidgetControl :: SetRegionPixmap (char *pixmap_name, int32 region_id )
{
  OCBitmap               *bitmap = NULL;
  logical                 term   = NO;
BEGINSEQ
  if ( !(bitmap = OCBitmap::ReadFromResource(pixmap_name)) )
                                                     ERROR
  term = SetRegionPixmap(bitmap->GetActiveBitmap(),region_id);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetSelection - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  start_pos - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

void TWidgetControl :: SetSelection (int32 start_pos, int32 length )
{

  if ( complexWidget )
    complexWidget->SetTextSelection(start_pos,length);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  start_point - 
\param  end_point - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

void TWidgetControl :: SetSelection (DPoint start_point, DPoint end_point )
{

  if ( complexWidget )
    complexWidget->SetTextSelection(start_point,end_point);

}

/******************************************************************************/
/**
\brief  SetSize - 



\return term - 

\param  dsize - 
\param  hgrow - 
\param  vgrow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

logical TWidgetControl :: SetSize (DSize dsize, logical hgrow, logical vgrow )
{
  logical            term = NO;
BEGINSEQ
  if ( !this || !complexWidget )                     ERROR
    
  complexWidget->SetSize(dsize,hgrow,vgrow);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTextColor - 



\return term - 

\param  rDColor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

logical TWidgetControl :: SetTextColor (DColor &rDColor )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetTextColor(rDColor);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTitle - 



\return term - 

\param  text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTitle"

logical TWidgetControl :: SetTitle (char *text )
{
  logical         term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
  
  complexWidget->SetTitle(text);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetVirtualType - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVirtualType"

logical TWidgetControl :: SetVirtualType (PropertyHandle *prophdl )
{

  return(complexWidget->SetVirtualType(prophdl));

}

/******************************************************************************/
/**
\brief  type - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVirtualType"

logical TWidgetControl :: SetVirtualType (char *scoped_name )
{

  return(complexWidget->SetVirtualType(scoped_name));

}

/******************************************************************************/
/**
\brief  SetWindowFlags - 



\return term - 

\param  reset_flags - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWindowFlags"

logical TWidgetControl :: SetWindowFlags (logical reset_flags )
{
  logical        term = NO;
BEGINSEQ
  if ( !complexWidget )                              ERROR
    
  complexWidget->SetWindowFlags(
             reset_flags,
             frameStyle->HasTitle(),
             style->HasBorder(),
             frameStyle->HasClose(),
             frameStyle->HasResize(),
             frameStyle->HasMinmax(),
             frameStyle->HasTitle(),      // has System Menu
             frameStyle->IsTopAlways(),
             frameStyle->HasSmallTitle()    );

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetZoomOutWidget - 



\return term - 

\param  pTWidgetControl - 
\param  auto_zoom - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetZoomOutWidget"

logical TWidgetControl :: SetZoomOutWidget (TWidgetControl *pTWidgetControl, char auto_zoom )
{

  return (   this && complexWidget && pTWidgetControl
           ? complexWidget->SetZoomOutWindow(pTWidgetControl->get_complexWidget(),auto_zoom)
           : YES );


}

/******************************************************************************/
/**
\brief  SetupParentDataSource - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupParentDataSource"

void TWidgetControl :: SetupParentDataSource ( )
{

  if ( complexWidget )
    complexWidget->SetupParentDataSource();


}

/******************************************************************************/
/**
\brief  Show - 




\param  fShow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

void TWidgetControl :: Show (logical fShow )
{
 

  if ( complexWidget )
    complexWidget->Show(fShow);
  UpdateLayout();


}

/******************************************************************************/
/**
\brief  TWidgetControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TWidgetControl"

     TWidgetControl :: TWidgetControl ( )
                     : TControl (),
  context(NULL),
  complexWidget(NULL),
  input_help(NULL)
{



}

/******************************************************************************/
/**
\brief  UpdateLayout - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

void TWidgetControl :: UpdateLayout ( )
{
  DPoint                       e;
  DPoint                       o;
  OFieldControl               *of;
  char                        *title;
  int16                        inner_dist = 0;
  if ( of = OI_CAST(OFieldControl,elementStyle) )
    inner_dist = of->get_inner_distance();
  
  if ( complexWidget )
  {
    DPoint dpES(elementStyle->Position());
    DSize  dsES(elementStyle->Size());
    DAlign daES = *elementStyle->Align();
    DSize  fsES(elementStyle->GetFrameSize(elementStyle->Size(),elementStyle->Align()->get_margin()));
    complexWidget->UpdateLayout(dpES,
                                inner_dist,
                                elementStyle->get_distance(),
                                dsES,
                                fsES,
                                daES,
                                elementStyle->get_displayLevel());
    
    complexWidget->UpdateFrameStyle(style && style->get_border()
                                    ? &style->get_border_style() : NULL);
    
    if ( (title = (char *)elementStyle->get_textDefinitions().GetTitle()) && *title )
      complexWidget->SetTitle(title);
    complexWidget->SetTooltip((char *)elementStyle->get_textDefinitions().GetTooltip());
    complexWidget->SetHelp((char *)elementStyle->get_textDefinitions().GetHelp());

    if ( elementStyle->get_layout() )
      complexWidget->SetPalette(elementStyle->get_layout());
  
    if ( elementStyle->get_bitmap() )
      complexWidget->SetPixmaps(elementStyle->get_bitmap()->GetInactiveBitmap(),
                                elementStyle->get_bitmap()->GetActiveBitmap(),
                                elementStyle->get_bitmap()->GetDisabledBitmap());
    
    if ( elementStyle->get_mouse_tracking() )
      complexWidget->ActivateMouseTracking();
    
  }

}

/******************************************************************************/
/**
\brief  UpdateTreeLayout - 



\return term - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTreeLayout"

logical TWidgetControl :: UpdateTreeLayout (int32 region_id )
{

  return (   this && complexWidget 
           ? complexWidget->UpdateTreeLayout(region_id)
           : NULL   );

}

/******************************************************************************/
/**
\brief  WidgetOwner - 



\return pODataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetOwner"

ODataWidget *TWidgetControl :: WidgetOwner ( )
{
  TWidgetControl    *otwc = (TWidgetControl *)OwnerOfType("TWidgetControl");
  return ( otwc ? otwc->get_complexWidget()->ControlWidget() : NULL );
  return(NULL);

}

/******************************************************************************/
/**
\brief  closeRequest - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "closeRequest"

void TWidgetControl :: closeRequest ( )
{



}

/******************************************************************************/
/**
\brief  enable - 



\return term - 

\param  fEnable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "enable"

logical TWidgetControl :: enable (logical fEnable )
{

  if ( complexWidget ) 
    complexWidget->Enable(fEnable);
  return(NO);
}

/******************************************************************************/
/**
\brief  loadBounds - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "loadBounds"

void TWidgetControl :: loadBounds ( )
{

  UpdateLayout();

}

/******************************************************************************/
/**
\brief  storeBounds - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeBounds"

void TWidgetControl :: storeBounds ( )
{
  DRect     bounds;
BEGINSEQ
  OADIERR(999)
/*  
  if ( !complexWidget )                              LEAVESEQ
  if ( elementStyle->Align()->Arrange(AT_Absolut) == AT_Grid )
                                                     LEAVESEQ
                                                     
  if ( !complexWidget->GetBounds(bounds,elementStyle->Align()->GetEdge(),
                                 elementStyle->Size().Height) )
                                                     LEAVESEQ
  if ( elementStyle->Bounds() != bounds )
   elementStyle->SetBounds(bounds);
*/
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~TWidgetControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TWidgetControl"

     TWidgetControl :: ~TWidgetControl ( )
{

  Deleting();
  Close();  
  


}


