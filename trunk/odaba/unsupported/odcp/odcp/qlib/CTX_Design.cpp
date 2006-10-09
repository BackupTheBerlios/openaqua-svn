/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    CTX_Design

\brief    


\date     $Date: 2006/07/05 14:04:29,93 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Design"

#include  <podcp8.h>
#include  <cqt.h>
#include  <sCTX_Control.hpp>
#include  <sDesignerMode.hpp>
#include  <sDesignerModeControl.hpp>
#include  <sDesignerModeControlFactory.hpp>
#include  <sDesignerModeFactory.hpp>
#include  <sNString.hpp>
#include  <sODControl.hpp>
#include  <sTWidgetControl.hpp>
#include  <sCTX_Design.hpp>


/******************************************************************************/
/**
\brief  CTX_Design - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Design"

     CTX_Design :: CTX_Design ( )
                     : CTX_Control (),
  control_ph(NULL),
  designer(NULL)
{



}

/******************************************************************************/
/**
\brief  DeleteField - 



\return term - 

\param  ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteField"

logical CTX_Design :: DeleteField (ODControl *ctrl )
{
  logical                  term         = NO;
  PropertyHandle         * field_ph     = NULL;
BEGINSEQ
  if ( field_ph = GetFieldPH(ctrl) )
  {
    if ( ctrl->IsField() )
    {
      if ( RemoveField(ctrl->GetName()) )                OADIERR(99)
    } else
    if ( ctrl->IsButton() )
    {
      if ( RemoveButton(ctrl->GetName()) )               OADIERR(99)
    } else
    if ( ctrl->IsConstant() )
      if ( RemoveConstant(ctrl->GetName()) )             OADIERR(99)
    
    field_ph->Delete();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 CTX_Design :: DoAfterOpen ( )
{
  DesignerModeFactory     factory;  
  DesignerMode          * dmode    = NULL;
  ODControl             * widget   = NULL;
  DLL(ODControl)          children;
  ODControl             * child    = NULL;
  int8                    executed = NO;
  DSize                   size;
BEGINSEQ
  if ( !(widget = control->get_complexWidget()) )          OADIERR(99)
  
  widget->EnableDesignMode(&DesignerModeControlFactory());
  designer = (DesignerModeControl *)widget->GetDesignMode();
   
  if ( widget->GetControlList() )
    children.Copy(*widget->GetControlList());
  if ( widget->GetButtonList() )
    children.Copy(*widget->GetButtonList());
  if ( widget->GetConstantList() )
    children.Copy(*widget->GetConstantList());
  children.GoTop();
  for ( child = children.GetHead(); child; child = children.GetNext() )
  {
    child->WidgetFrame()->EnableDesignMode(&factory);
    
    dmode = (DesignerMode *) child->WidgetFrame()->GetDesignMode();
    dmode->SetODControl(child);
    dmode->SetContext(this);
  }
RECOVER

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  EditField - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditField"

logical CTX_Design :: EditField (ODControl *ctrl )
{
  PropertyHandle        * field_ph = NULL;
  logical                 term     = NO;
  if ( field_ph = GetFieldPH(ctrl) )
    EditField(field_ph);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  field_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditField"

logical CTX_Design :: EditField (PropertyHandle *field_ph )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  EditFieldControl - 



\return term - 

\param  ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditFieldControl"

logical CTX_Design :: EditFieldControl (ODControl *ctrl )
{
  logical                  term             = NO;
  PropertyHandle         * field_ph         = NULL;
  PropertyHandle         * field_control_ph = NULL;

BEGINSEQ
  if ( field_ph = GetFieldPH(ctrl) )
  { 
    if ( ! ctrl->IsField() )                         LEAVESEQ
    
    if ( !(field_control_ph = field_ph->GetPropertyHandle("field_control")) )
                                                     OADIERR(99)
    if ( !field_control_ph->Get(FIRST_INSTANCE) )    OADIERR(99)
  
    OpenFieldControl(field_ph, field_control_ph);
  }
  else                                               OADIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EditFieldLabel - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditFieldLabel"

logical CTX_Design :: EditFieldLabel (ODControl *ctrl )
{
  PropertyHandle        * field_ph = NULL;
  logical                 term     = NO;
  if ( field_ph = GetFieldPH(ctrl) )
    EditFieldLabel(field_ph);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  field_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditFieldLabel"

logical CTX_Design :: EditFieldLabel (PropertyHandle *field_ph )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  EnableFieldDesignMode - 



\return term - 

\param  field_context - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableFieldDesignMode"

logical CTX_Design :: EnableFieldDesignMode (CTX_Control *field_context )
{
  logical                 term         = NO;
  ODControl             * field_widget = NULL;
  DesignerModeFactory     factory;  
  DesignerMode          * dmode        = NULL;
BEGINSEQ
  if ( !(field_widget = field_context->get_control()->get_complexWidget()) )
                                                     OADIERR(99)

  field_widget->WidgetFrame()->EnableDesignMode(&factory);  

  dmode = (DesignerMode *) field_widget->WidgetFrame()->GetDesignMode();
  dmode->SetODControl(field_widget);
  dmode->SetContext(this);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetControlPH - 



\return field_ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlPH"

PropertyHandle *CTX_Design :: GetControlPH ( )
{


  return(control_ph);
}

/******************************************************************************/
/**
\brief  GetFieldPH - 



\return field_ph - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldPH"

PropertyHandle *CTX_Design :: GetFieldPH (ODControl *ctrl )
{
char                   * ref_name = NULL;
if ( ctrl->IsField() )
  ref_name = "fields";
if ( ctrl->IsButton() )
  ref_name = "buttons";
if ( ctrl->IsConstant() )
  ref_name = "constants";
return GetFieldPH(ref_name, ctrl->GetName());
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ref_name - 
\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldPH"

PropertyHandle *CTX_Design :: GetFieldPH (char *ref_name, char *name )
{
  char                    buffer[ID_SIZE];
  PropertyHandle        * field_ph = NULL;
BEGINSEQ
  gvtxstb(buffer, name, ID_SIZE);
  field_ph = control_ph->GetPropertyHandle(ref_name);
  if ( ! field_ph )                                   OADIERR(99)
  if ( ! field_ph->Get(buffer) )                      OADIERR(99)

RECOVER
  field_ph = NULL;
ENDSEQ
  return(field_ph);
}

/******************************************************************************/
/**
\brief  HasPreview - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasPreview"

logical CTX_Design :: HasPreview ( )
{


return designer->HasPreview();
}

/******************************************************************************/
/**
\brief  InitDesigner - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDesigner"

void CTX_Design :: InitDesigner ( )
{
  ODControl             * widget   = NULL;
  DSize                   size;
BEGINSEQ
  if ( !designer )                                   ERROR
  
  widget = control->get_complexWidget();
  designer->SetContext(this);
  designer->SetClientWidget(widget->ClientWidget());
  designer->SetControlWidget(widget->ControlWidget());
  size = designer->InitGrid();
  SetSize(size + GetSize());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  LoadControlAttribute - 



\return value - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadControlAttribute"

PropertyHandle CTX_Design :: LoadControlAttribute (char *name )
{
  PropertyHandle          value;
  PropertyHandle        * ctrl_ph   = NULL;
  PropertyHandle        * attr_ph   = NULL;
BEGINSEQ
  if ( ctrl_ph = GetControlPH() )
  {
    attr_ph = ctrl_ph->GetPropertyHandle(name);
    if ( ! attr_ph )                                   OADIERR(99)
      value = *attr_ph;
  }

RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  LoadFieldAttribute - 



\return value - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctrl - 
\param  attr_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadFieldAttribute"

PropertyHandle CTX_Design :: LoadFieldAttribute (ODControl *ctrl, char *attr_name )
{
  PropertyHandle          value;
  PropertyHandle        * field_ph  = NULL;
  if ( field_ph = GetFieldPH(ctrl) )
    value = LoadFieldAttribute(field_ph, attr_name);
  return(value);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ref_name - 
\param  fld_name - 
\param  attr_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadFieldAttribute"

PropertyHandle CTX_Design :: LoadFieldAttribute (char *ref_name, char *fld_name, char *attr_name )
{
  PropertyHandle          value;
  PropertyHandle        * field_ph  = NULL;
  if ( field_ph = GetFieldPH(ref_name, fld_name) )
    value = LoadFieldAttribute(field_ph, attr_name);

  return(value);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  field_ph - 
\param  attr_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadFieldAttribute"

PropertyHandle CTX_Design :: LoadFieldAttribute (PropertyHandle *field_ph, char *attr_name )
{
  PropertyHandle          value;
  PropertyHandle        * attr_ph = NULL;
BEGINSEQ
  attr_ph = field_ph->GetPropertyHandle(attr_name);
  if ( ! attr_ph )                                   OADIERR(99)
    value = *attr_ph;

RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  OpenFieldControl - 



\return term - 

\param  field_ph - 
\param  field_control_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenFieldControl"

logical CTX_Design :: OpenFieldControl (PropertyHandle *field_ph, PropertyHandle *field_control_ph )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Preview - 



\return term - 

\param  pv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Preview"

logical CTX_Design :: Preview (logical pv )
{
  logical                 term = NO;
  DSize                   size;
  size = designer->Preview(pv);
  SetSize(size + GetSize());
  ExecuteFunction("SizeChanged");
  return(term);
}

/******************************************************************************/
/**
\brief  RefreshControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshControl"

logical CTX_Design :: RefreshControl ( )
{

  return ExecuteFunction("Refresh");

}

/******************************************************************************/
/**
\brief  RefreshField - 



\return term - 

\param  ctrl - 
\param  focused - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshField"

logical CTX_Design :: RefreshField (ODControl *ctrl, logical focused )
{
  logical                 term          = NO;
  PropertyHandle        * field_ph      = NULL;
  NString                 field_name    = ctrl->GetName();
  CTX_Control           * field_context = NULL;
BEGINSEQ
  InvalidateDesignerCache();
  
  if ( !(field_ph = GetFieldPH(ctrl)) )              OADIERR(99)
  field_ph->Save();

  if ( ctrl->IsField() )
  {
    RemoveField((char*)field_name);
    field_context = CreateField((char*)field_name, YES, DPoint(), UNDEF);
  } else
  if ( ctrl->IsButton() )
  {
    RemoveButton((char*)field_name);
    field_context = CreateButton((char*)field_name, YES, DPoint(), UNDEF);
  } else
  if ( ctrl->IsConstant() )
  {
//    RemoveConstant((char*)field_name);
//    field_context = CreateConstant((char*)field_name, YES, DPoint(), UNDEF);
  }

  if ( !field_context )                              OADIERR(99)
  EnableFieldDesignMode(field_context);
  
  ((DesignerModeControl *)control->get_complexWidget()->GetDesignMode())->Refresh();

  if ( focused )
    field_context->get_control()->get_complexWidget()->WidgetFrame()->WidgetQ()->setFocus();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetControl"

void CTX_Design :: ResetControl ( )
{
  DesignerMode          * dmode    = NULL;
  ODControl             * widget   = NULL;
  ODControl             * child    = NULL;
  DLL(ODControl)          children;

  if ( widget = control->get_complexWidget() )
  {
    children.Copy(*widget->GetControlList()); 
    children.Copy(*widget->GetButtonList());
    children.Copy(*widget->GetConstantList());
    children.GoTop();

    for ( child = children.GetHead(); child; child = children.GetNext() )
      if ( dmode = (DesignerMode *) child->WidgetFrame()->GetDesignMode() )
        dmode->SetContext(NULL);
  }
  CTX_Control::ResetControl();

}

/******************************************************************************/
/**
\brief  SelectField - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectField"

logical CTX_Design :: SelectField (ODControl *ctrl )
{
  PropertyHandle        * field_ph = NULL;
  logical                 term     = NO;
  if ( field_ph = GetFieldPH(ctrl) )
    SelectField(field_ph);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  field_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectField"

logical CTX_Design :: SelectField (PropertyHandle *field_ph )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetControlPH - 




\param  ph_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControlPH"

void CTX_Design :: SetControlPH (PropertyHandle *ph_ptr )
{

  control_ph=ph_ptr;


}

/******************************************************************************/
/**
\brief  StoreControlAttribute - 



\return term - 

\param  name - 
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreControlAttribute"

logical CTX_Design :: StoreControlAttribute (char *name, PropertyHandle value )
{
  logical                 term     = NO;
  PropertyHandle        * ctrl_ph  = NULL;
  PropertyHandle        * attr_ph  = NULL;

BEGINSEQ
  if ( ctrl_ph = GetControlPH() )
  {
    attr_ph = ctrl_ph->GetPropertyHandle(name);
    if ( ! attr_ph )                                 OADIERR(99)
    
    *attr_ph = value;
    ctrl_ph->Save();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StoreFieldAttribute - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctrl - 
\param  attr_name - 
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreFieldAttribute"

logical CTX_Design :: StoreFieldAttribute (ODControl *ctrl, char *attr_name, PropertyHandle value )
{
  logical                 term     = NO;
  PropertyHandle        * field_ph = NULL;
  if ( field_ph = GetFieldPH(ctrl) )
    StoreFieldAttribute(field_ph, attr_name, value);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ref_name - 
\param  fld_name - 
\param  attr_name - 
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreFieldAttribute"

logical CTX_Design :: StoreFieldAttribute (char *ref_name, char *fld_name, char *attr_name, PropertyHandle value )
{
  logical                 term = NO;
  PropertyHandle        * field_ph = NULL;
  if ( field_ph = GetFieldPH(ref_name, fld_name) )
    StoreFieldAttribute(field_ph, attr_name, value);

  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  field_ph - 
\param  attr_name - 
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreFieldAttribute"

logical CTX_Design :: StoreFieldAttribute (PropertyHandle *field_ph, char *attr_name, PropertyHandle value )
{
  logical                 term = NO;
  PropertyHandle        * attr_ph  = NULL;
BEGINSEQ
  attr_ph = field_ph->GetPropertyHandle(attr_name);
  if ( ! attr_ph )                                 OADIERR(99)

  *attr_ph = value;
  field_ph->Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~CTX_Design - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Design"

     CTX_Design :: ~CTX_Design ( )
{



}


