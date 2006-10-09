/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODControl

\brief    Complex Control
          The  class  supports  complex  controls. Compex controls do consist of
          different  parts as e.g. lable and  edit area. Complex controls manage
          the  connection  between  label  and data control, are responsible for
          drawing frames and outer widgets for certain controls.
          Complex  controls  are  collecting  the  events  from  all  associated
          controls  and sending  the events  to the parent. Subordinated complex
          controls  as labes do not handle  events explicitly but sending events
          to  the  parent,  the  control  owning the label. You may set an event
          handler  for the control,  which receives all  events collected by the
          control (see OEH).

\date     $Date: 2006/08/29 19:42:07,19 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODControl"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#ifndef   DLL_ODControl_HPP
#define   DLL_ODControl_HPP
#include  <sODControl.hpp>
#include  <sDLL.h>
#endif
#include  <sCellData.hpp>
#include  <sDBorder.hpp>
#include  <sDLayout.hpp>
#include  <sDPixmap.hpp>
#include  <sDRect.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sOCheckBox.hpp>
#include  <sOComboBox.hpp>
#include  <sOComboListBox.hpp>
#include  <sOControlLayout.hpp>
#include  <sODControl.hpp>
#include  <sODControlList.hpp>
#include  <sODLabel.hpp>
#include  <sODSItem.hpp>
#include  <sODTabControl.hpp>
#include  <sODWindow.hpp>
#include  <sODataWidget.hpp>
#include  <sODateEdit.hpp>
#include  <sODialog.hpp>
#include  <sODockArea.hpp>
#include  <sODockWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHActionHandler.hpp>
#include  <sOEHEvent.hpp>
#include  <sOEHReaction.hpp>
#include  <sOIconSet.hpp>
#include  <sOLabel.hpp>
#include  <sOListView.hpp>
#include  <sOMultiLineEdit.hpp>
#include  <sOObject.hpp>
#include  <sOPushButton.hpp>
#include  <sORichTextEdit.hpp>
#include  <sOSimpleWidget.hpp>
#include  <sOSingleLineEdit.hpp>
#include  <sOTab.hpp>
#include  <sOTableView.hpp>
#include  <sOTimeEdit.hpp>
#include  <sOToolBar.hpp>
#include  <sOToolBox.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOTreeView.hpp>
#include  <sOWidgetStack.hpp>
#include  <sODControl.hpp>


/******************************************************************************/
/**
\brief  Activate - Activate data for complex control

        The control widget is activated.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ODControl :: Activate ( )
{
  logical      term = NO;
BEGINSEQ
  if ( !controlWidget )                              ERROR
  
  controlWidget->GenerateEvent(GEV_Open);
  
  if ( controlWidget->Activate() )                   ERROR

  controlWidget->GenerateEvent(GEV_Opened);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ActivateElements - 



\return term - 

\param  act_curent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateElements"

logical ODControl :: ActivateElements (logical act_curent )
{
  ODControl   *control;
  logical      term = NO;
BEGINSEQ
  if ( !controlWidget )                              ERROR
  
  if ( controls )
  {
    controls->GoTop();
    while ( control = controls->GetNext() )
      control->ActivateElements(YES);
  }
  
  if ( act_curent )
    if ( controlWidget->Activate() )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ActivateMouseTracking - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateMouseTracking"

logical ODControl :: ActivateMouseTracking ( )
{
  logical                 term = NO;
  controlWidget->SetMouseTracking();
  return(term);
}

/******************************************************************************/
/**
\brief  AddColumn - 



\return pOListLayout - 
-------------------------------------------------------------------------------
\brief  i01 - 



\param  prop_path - Property path
\param  text - 
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

OListLayout *ODControl :: AddColumn (char *prop_path, char *text, ODSPropertyType prop_type )
{

  return (   controlWidget 
           ? controlWidget->AddColumn(prop_path,text,prop_type)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  i02 - 



\param  region_id - 
\param  prop_path - Property path
\param  text - 
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

OListLayout *ODControl :: AddColumn (int32 region_id, char *prop_path, char *text, ODSPropertyType prop_type )
{

  return (   controlWidget 
           ? controlWidget->AddColumn(region_id,prop_path,text,prop_type)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  AddHighlightClass - 



\return term - 

\param  names - 
\param  dsyntaxclass - 
\param  dfont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHighlightClass"

logical ODControl :: AddHighlightClass (char *names, DSyntaxClass &dsyntaxclass, DFont &dfont )
{
  logical                 term = NO;
BEGINSEQ
  if ( !controlWidget )                              ERROR

  term = controlWidget->AddHighlightClass(names,dsyntaxclass,dfont);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddInputHelp - 



\return term - 

\param  pODControl - 
\param  activate_strings - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInputHelp"

logical ODControl :: AddInputHelp (ODControl *pODControl, VECTOR(std_string) &activate_strings )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || !controlWidget || !pODControl )      ERROR

  pODControl->Show(NO);
    
  controlWidget->AddInputHelp(pODControl->get_controlWidget(),
                              activate_strings);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddRegion - 



\return region_id - 

\param  parent_id - 
\param  prop_path - Property path
\param  is_collection - Is referenced path pointing to a collection
\param  text - 
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

int32 ODControl :: AddRegion (int32 parent_id, char *prop_path, logical is_collection, char *text, ODSPropertyType prop_type )
{

  return (   controlWidget 
           ? controlWidget->AddRegion(parent_id,prop_path,is_collection,text,prop_type)
           : UNDEF                               );


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

logical ODControl :: AssociateData (PropertyHandle *source_ph, char *control_name, char *title )
{
  OEHDataWidget    *oeh_dw;

  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->AssociateData(source_ph,control_name,title)
           : YES                         );


}

/******************************************************************************/
/**
\brief  BindClientWidget - 




\param  pQWidget_Outer - 
\param  pQWidget_Inner - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BindClientWidget"

void ODControl :: BindClientWidget (ODataWidget *pQWidget_Outer, ODataWidget *pQWidget_Inner )
{
  QWidget          *frame;
  QWidget          *parent;
  QGridLayout      *client_layout;
  if ( clientInnerWidget ) 
  {
    client_layout = new QGridLayout(clientInnerWidget->WidgetQ());
    client_layout->addWidget(pQWidget_Outer->WidgetQ(),0,0);
    client_layout->setSpacing(0);    // default für Dialogs is 6 in Qt4
    client_layout->setMargin(0);     // default für Windows is 11 in Qt4
  }
  if ( !clientOuterWidget ) 
    clientOuterWidget = pQWidget_Outer;

  if ( pQWidget_Inner ) 
    clientInnerWidget = pQWidget_Inner;

  // if this is a MDI child we have to use another OuterWidget (experimental?)
  if ( frame = WidgetFrame()->WidgetQ() )
    if ( (parent = frame->parentWidget()) && parent->inherits("QWorkspace") )
  {
    ((QWorkspace *)parent)->addWindow(frame);
    frame->showMaximized();
  }


}

/******************************************************************************/
/**
\brief  ClientWidget - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClientWidget"

ODataWidget *ODControl :: ClientWidget ( ) const
{

  return( !this             ? NULL              :
          clientInnerWidget ? clientInnerWidget :
          clientOuterWidget ? clientOuterWidget :
          controlWidget                        );

}

/******************************************************************************/
/**
\brief  ClientWidgetParent - Get Widget parent for current data widget

        The  function  returns  the  widget,  which  may  act  as parent for the
        current  widget. This  is usually  the parent,  but when the parent is a
        control  (e.g. single line edit) the parent  is the parent from the edit
        control.

\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClientWidgetParent"

ODataWidget *ODControl :: ClientWidgetParent ( )
{
  ODTabControl   *tab_parent = this && parent 
                               ? parent->GetTabControl() : NULL;
  return( !this             ? NULL              :
          clientInnerWidget ? clientInnerWidget :
          frameInnerWidget  ? frameInnerWidget  :
          lmFrame           ? lmFrame           :
          tab_parent        ? display_level     ? tab_parent->PanelWidgetParent()
                                                : tab_parent   
                                                :
          parent    ? parent->ClientWidgetParent()
//        parent    ? parent->ChildPositionLayout( elementStyle->Align()->Hori(HPS_InnerLeft),elementStyle->Align()->Vert(VPS_InnerTop))->mainWidget() 
                           : NULL);

}

/******************************************************************************/
/**
\brief  ConnectAction - 



\return term - 

\param  act_namesc - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectAction"

logical ODControl :: ConnectAction (const char *act_namesc, char *loid )
{

  return( controlWidget 
          ? controlWidget->SetStandardAction(act_namesc,loid)
          : YES);

}

/******************************************************************************/
/**
\brief  ControlWidget - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ControlWidget"

ODataWidget *ODControl :: ControlWidget ( ) const
{

  return controlWidget;

}

/******************************************************************************/
/**
\brief  CreateCheckBox - 



\return term - 

\param  control_name - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCheckBox"

logical ODControl :: CreateCheckBox (char *control_name, int16 dsp_level )
{
  OCheckBox     *check_box = NULL;
  logical        term = NO;
BEGINSEQ
  InitControlWidget();
  
// *fixme* der owner_ods für die eventbehandlung muss nicht der parent OD... sein!  
  
  if ( !(check_box = new OCheckBox(ClientWidgetParent(),
                                   WidgetOwner(),odw_ods)) )    // ?? wenns sowieso dasselbe ist ??
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(check_box,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR

RECOVER
  delete check_box;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateClientArea - 



\return term - 

\param  control_name - 
\param  is_workspace - 
\param  dsp_level - 
\param  is_control - 
\param  win_type - 
\param  vertical - 
\param  exclusive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateClientArea"

logical ODControl :: CreateClientArea (char *control_name, logical is_workspace, int16 dsp_level, logical is_control, OWindowTypes win_type, logical vertical, logical exclusive )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  CreateComboBox - Create a OComboBox control



\return term - 

\param  control_name - 
\param  editable - Is edit possible?
\param  sort_opt - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateComboBox"

logical ODControl :: CreateComboBox (char *control_name, logical editable, logical sort_opt, int16 dsp_level )
{
  OComboBox        *combo_box = NULL;
  logical           term      = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(combo_box = new OComboBox(ClientWidgetParent(),
                                   WidgetOwner(),odw_ods,
                                   editable,sort_opt)) ) 
                                                     OGUIERR(95)
                                                     OGUICERR
  
  if ( SetControlWidget(combo_box,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete combo_box;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateComboListBox - 



\return term - 

\param  control_name - 
\param  chk_items - 
\param  multi_sel - 
\param  sort_opt - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateComboListBox"

logical ODControl :: CreateComboListBox (char *control_name, logical chk_items, logical multi_sel, logical sort_opt, int16 dsp_level )
{
  OComboListBox      *combo_list_box;
  logical             term = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(combo_list_box = new OComboListBox(ClientWidgetParent(),
                                       WidgetOwner(),odw_ods,
                                       multi_sel,sort_opt)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(combo_list_box,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete combo_list_box;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateContextMenu - 



\return term - 

\param  act_namesc - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContextMenu"

logical ODControl :: CreateContextMenu (const char *act_namesc, char *loid )
{

  return (   controlWidget 
           ? controlWidget->CreateContextMenu(act_namesc,loid)
           : NULL );

}

/******************************************************************************/
/**
\brief  CreateDateEdit - 



\return term - 

\param  control_name - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDateEdit"

logical ODControl :: CreateDateEdit (char *control_name, int16 dsp_level )
{
  ODateEdit        *date_edit = NULL;
  logical           term      = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(date_edit = new ODateEdit(ClientWidgetParent(),WidgetOwner(),odw_ods)) ) 
                                                     OGUIERR(95)
                                                     OGUICERR
  
  if ( SetControlWidget(date_edit,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete date_edit;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateDockingArea - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDockingArea"

logical ODControl :: CreateDockingArea ( )
{
  QWidget                *widget = clientInnerWidget->WidgetQ();
  QLayout                *layout = NULL;
  logical                 term = NO;
  if ( layout = clientOuterWidget->WidgetQ()->layout() )
    layout->removeWidget(widget);
  
  widget->setParent(NULL);
  if ( !dock_area )
    dock_area = new ODockArea(clientOuterWidget,WidgetOwner(),ods(),widget);

  if ( layout )
    layout->addWidget(dock_area);

  return(term);
}

/******************************************************************************/
/**
\brief  CreateLabel - 



\return term - 

\param  dsize - 
\param  verti_pos - Vertical position
\param  hori_pos - Horizontal position
\param  label_text - Label text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateLabel"

logical ODControl :: CreateLabel (DSize &dsize, ADK_VertPos verti_pos, ADK_HoriPos hori_pos, char *label_text )
{
  ODTabControl *otc;
  QWidget      *widget = controlWidget ? controlWidget->WidgetQ() : NULL;
  logical       term   = NO;
BEGINSEQ
  if ( otc = (parent ? parent->GetTabControl() : NULL) )
    otc->SetTabText(label_text,display_level);
  else
  {
    if ( !widget || !lmCells )                         ERROR
    
    if ( !label )
      label = new OLabel(LabelParentWidget(),WidgetOwner());
    
    label->UpdateSize(dsize);
    lmCells->PositionElement(label,verti_pos,hori_pos);
  
    label->setBuddy(widget);  
    label->setFocusProxy(widget);  
  
    label->SetDrawFocusRect(NO);
    SetLabelText(label_text);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateLayout - 




\param  grid_size - 
\param  dmargin - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateLayout"

void ODControl :: CreateLayout (DSize &grid_size, DMargin &dmargin )
{
  QWidget     *widget = WidgetQ();
  QLayout     *layout = NULL;
  int          spacing = 0;
BEGINSEQ
  if ( ClientWidget() )
    widget = ClientWidget()->WidgetQ();
  if ( !widget )                                     ERROR
  
  if ( widget->inherits("QWorkspace") )              LEAVESEQ
  if ( widget->inherits("QTab") )                    LEAVESEQ
    
  switch ( grid_control = (grid_size.Width  > 0)*1 + 
                          (grid_size.Height > 0)*2   )
  {
    case 1 : // horizontal layout
             {
               layout = new QHBoxLayout(widget);
               spacing = dmargin.Left;
             }
             break;
    case 2 : // vertical layout
             {
               layout = new QVBoxLayout(widget);
               spacing = dmargin.Top;
             }
             break;
    case 3 : // grid layout
             {
               layout = new QGridLayout(widget);
             }
             break;
    case 0 : // no layout
             break;
  }
  if ( layout )
  {
    if ( spacing )
      ((QBoxLayout *)layout)->addSpacing(spacing);
    else
      layout->setSpacing(0);
    layout->setMargin(0);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CreateListView - 



\return term - 

\param  control_name - 
\param  chk_items - 
\param  multi_sel - 
\param  sort_opt - 
\param  dsp_level - 
\param  fast_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateListView"

logical ODControl :: CreateListView (char *control_name, logical chk_items, logical multi_sel, logical sort_opt, int16 dsp_level, logical fast_list )
{
  ODataWidget   *list_view = NULL;
  int            columns   = 10;
  logical        term      = NO;
BEGINSEQ
  InitControlWidget();

  if ( columns <= 1 )
    list_view = new OListView(ClientWidgetParent(),
                              WidgetOwner(),odw_ods,
                              multi_sel,sort_opt ? 1 : 0,chk_items);
  else
    list_view = new OTreeView(ClientWidgetParent(),
                              WidgetOwner(),odw_ods,
                              multi_sel,sort_opt,NO,chk_items);
  
  if ( !list_view )                                  OGUIERR(95)
                                                     OGUICERR 
  
  if ( SetControlWidget(list_view,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR

RECOVER
  delete list_view;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateMenuBar - 



\return term - 

\param  act_namesc - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMenuBar"

logical ODControl :: CreateMenuBar (const char *act_namesc, char *loid )
{

  return (   controlWidget 
           ? controlWidget->CreateMenuBar(act_namesc,loid)
           : NULL );

}

/******************************************************************************/
/**
\brief  CreateMultiLineEdit - 



\return term - 

\param  control_name - 
\param  dsp_level - 
\param  hl_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMultiLineEdit"

logical ODControl :: CreateMultiLineEdit (char *control_name, int16 dsp_level, HighLighting hl_type )
{
  OMultiLineEdit    *multi_line = NULL;
  logical            term = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(multi_line = new OMultiLineEdit(ClientWidgetParent(),
                                         WidgetOwner(),odw_ods,hl_type)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(multi_line,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete multi_line;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreatePushButton - 



\return term - 

\param  control_name - 
\param  title_text - 
\param  toggle_state - 
\param  default_opt - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePushButton"

logical ODControl :: CreatePushButton (char *control_name, char *title_text, int8 toggle_state, logical default_opt, int16 dsp_level )
{
  OPushButton     *push_button = NULL;
  logical          term        = NO;
BEGINSEQ
  InitControlWidget();
  
// *fixme* der owner_ods für die eventbehandlung muss nicht der parent OD... sein!  
  
  if ( !(push_button = new OPushButton(ClientWidgetParent(),
                                       WidgetOwner(),toggle_state,default_opt)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(push_button,parent->GetButtonList(),control_name,dsp_level) )
                                                     ERROR

  SetText(title_text);
RECOVER
  delete push_button;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRadioButtons - 



\return term - 

\param  control_name - 
\param  label_text - Label text
\param  dsp_level - 
\param  auto_size - Determin size dynamically
\param  no_strips - Number of strips
\param  hori_strip - Horizontal orientation
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRadioButtons"

logical ODControl :: CreateRadioButtons (char *control_name, char *label_text, int16 dsp_level, logical auto_size, int32 no_strips, logical hori_strip )
{
//  ORadioButton      *radio_button = NULL;
  logical            term = NO;
BEGINSEQ
OGUIERR(999)
/* *** keine listen
InitControlWidget();
  
  if ( !(radio_button = new ORadioButton(ClientWidgetParent(),WidgetOwner(),
                                         label_text,auto_size,odw_ods,no_strips,hori_strip)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(radio_button,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
*/
RECOVER
//  delete radio_button;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRichTextEdit - 



\return term - 

\param  control_name - 
\param  dsp_level - 
\param  rtf_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRichTextEdit"

logical ODControl :: CreateRichTextEdit (char *control_name, int16 dsp_level, logical rtf_opt )
{
  ORichTextEdit     *rich_text = NULL;
  logical            term      = NO;
BEGINSEQ
InitControlWidget();
  
  if ( !(rich_text = new ORichTextEdit(ClientWidgetParent(),
                                        WidgetOwner(),odw_ods)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(rich_text,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR

RECOVER
  delete rich_text;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSingleLineEdit - 



\return term - 

\param  control_name - 
\param  dsp_level - 
\param  pwd_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSingleLineEdit"

logical ODControl :: CreateSingleLineEdit (char *control_name, int16 dsp_level, logical pwd_opt )
{
  OSingleLineEdit      *single_line = NULL;
  logical               term        = NO;
BEGINSEQ
InitControlWidget();
  
// *fixme* der owner_ods für die eventbehandlung muss nicht der parent OD... sein!  
  
  if ( !(single_line = new OSingleLineEdit(ClientWidgetParent(),
                                           WidgetOwner(),odw_ods,pwd_opt)) )    // ?? wenns sowieso dasselbe ist ??
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(single_line,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR

RECOVER
  delete single_line;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSubWindow - Create Window

        Windows  are  created  in  different  ways  depending on the parent. For
        Tab-Controls, each windo creates a new tab in the TabControl.

\return pODWindow - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubWindow"

ODWindow *ODControl :: CreateSubWindow (char *names )
{
  ODWindow   *new_win = NULL;
  new_win = new ODWindow(this,names);
  GetControlList()->AddTail(new_win);
  return(new_win);
}

/******************************************************************************/
/**
\brief  CreateTabControl - 



\return term - 

\param  control_name - 
\param  dsp_level - 
\param  tb_upper - Position for displaying the tabs
\param  tb_normal - Size of tabs in the tab-bar
\param  stb_upper - Position of static area for the tab-control
\param  dyn_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTabControl"

logical ODControl :: CreateTabControl (char *control_name, int16 dsp_level, logical tb_upper, logical tb_normal, logical stb_upper, char dyn_opt )
{
  OTab          *tab_control = NULL;
  logical        term = NO;
BEGINSEQ
  dynamic = dyn_opt;
  
InitControlWidget();
  
// *fixme* der owner_ods für die eventbehandlung muss nicht der parent OD... sein!  
  
  if ( !(tab_control = new OTab(ClientWidgetParent(),
                                WidgetOwner(),odw_ods,
                                tb_upper,tb_normal,stb_upper,dyn_opt)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  if ( SetControlWidget(tab_control,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
//  clientInnerWidget = tab_control;

RECOVER
  delete tab_control;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTable - 



\return term - 

\param  control_name - 
\param  multi_sel - 
\param  transposed - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTable"

logical ODControl :: CreateTable (char *control_name, logical multi_sel, logical transposed, int16 dsp_level )
{
  OTableView    *table = NULL;
  logical        term  = NO;
BEGINSEQ
  InitControlWidget();

  if ( !(table = new OTableView(ClientWidgetParent(),
                                WidgetOwner(),odw_ods,
                                multi_sel,transposed)) )    
                                                     OGUIERR(95)
                                                     OGUICERR 
  if ( SetControlWidget(table,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR

RECOVER
  delete table;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTimeEdit - 



\return term - 

\param  control_name - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTimeEdit"

logical ODControl :: CreateTimeEdit (char *control_name, int16 dsp_level )
{
  OTimeEdit        *time_edit = NULL;
  logical           term      = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(time_edit = new OTimeEdit(ClientWidgetParent(),WidgetOwner(),odw_ods)) ) 
                                                     OGUIERR(95)
                                                     OGUICERR
  
  if ( SetControlWidget(time_edit,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete time_edit;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateToolBar - 



\return term - 

\param  act_namesc - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateToolBar"

logical ODControl :: CreateToolBar (const char *act_namesc, char *loid )
{
  OToolBar     *toolbar;
  logical       term = NO;
BEGINSEQ
  if ( !controlWidget )                              ERROR
  
  if ( !(toolbar = controlWidget->CreateToolBar(act_namesc,loid)) )
                                                     ERROR
  if ( dock_area )
    dock_area->addToolBar(toolbar);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateToolBox - 



\return term - 

\param  control_name - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateToolBox"

logical ODControl :: CreateToolBox (char *control_name, int16 dsp_level )
{
  OToolBox         *tool_box = NULL;
  logical           term      = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(tool_box = new OToolBox(ClientWidgetParent(),WidgetOwner(),odw_ods)) ) 
                                                     OGUIERR(95)
                                                     OGUICERR
  
  if ( SetControlWidget(tool_box,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete tool_box;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTreeView - 



\return term - 

\param  control_name - 
\param  chk_items - 
\param  multi_sel - 
\param  sort_opt - 
\param  dsp_level - 
\param  fast_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTreeView"

logical ODControl :: CreateTreeView (char *control_name, logical chk_items, logical multi_sel, logical sort_opt, int16 dsp_level, logical fast_list )
{
  ODataWidget     *tree_view = NULL;
  logical          term      = NO;
BEGINSEQ
  InitControlWidget();
  
  if ( !(tree_view = new OTreeView(ClientWidgetParent(),
                                   WidgetOwner(),odw_ods,
                                   multi_sel,sort_opt,YES,chk_items)) )
                                                     OGUIERR(95)
                                                     OGUICERR 
  if ( SetControlWidget(tree_view,parent->GetControlList(),control_name,dsp_level) )
                                                     ERROR
RECOVER
  delete tree_view;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateWindowArea - 



\return term - 

\param  control_name - 
\param  is_modal - 
\param  win_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateWindowArea"

logical ODControl :: CreateWindowArea (char *control_name, logical is_modal, OWindowTypes win_type )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  DA_FindEntry - 



\return term - 

\param  skey - 
\param  cur_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical ODControl :: DA_FindEntry (char *skey, logical cur_opt )
{
  OEHDataWidget    *oeh_dw;
  logical           term = NO;
BEGINSEQ
  if ( !(oeh_dw = controlOEHWidget()) )              ERROR

  if ( skey )
    term = oeh_dw->DA_FindEntry(skey,cur_opt);
  else
    term = oeh_dw->DA_FindEntry();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Refresh"

logical ODControl :: DA_Refresh ( )
{
  OEHDataWidget    *oeh_dw;
  logical           term = NO;
BEGINSEQ
  if ( !(oeh_dw = controlOEHWidget()) )              ERROR

  term = oeh_dw->DA_Refresh();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_StoreEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_StoreEntry"

logical ODControl :: DA_StoreEntry ( )
{
  OEHDataWidget    *oeh_dw;
  logical           term = NO;
BEGINSEQ
  if ( !(oeh_dw = controlOEHWidget()) )              ERROR

  term = oeh_dw->DA_StoreEntry();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeactivateElements - 



\return term - 

\param  act_curent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateElements"

logical ODControl :: DeactivateElements (logical act_curent )
{
  ODControl   *control;
  logical      term = NO;
BEGINSEQ
  if ( !controlWidget )                              ERROR
  
  if ( act_curent ) 
    controlWidget->Deactivate(YES);
  else
    controlWidget->DeactivateElements();
  
  if ( controls )
  {
    controls->GoTop();
    while ( control = controls->GetNext() )
      control->DeactivateElements(YES);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Destroy - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Destroy"

void ODControl :: Destroy ( )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ

  is_destroying = YES;
  
  delete controls;
  controls = NULL;

  delete buttons;
  buttons = NULL;

  delete constants;
  constants = NULL;
  
  if ( name )
    free(name);
  name = NULL;
  
  delete dock_area;
  dock_area = NULL;
  
  delete dock_widget;
  dock_widget = NULL;
  
  RemoveControlWidget();
ENDSEQ

}

/******************************************************************************/
/**
\brief  DockControl - 



\return term - 

\param  position - 
\param  dalign - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DockControl"

logical ODControl :: DockControl (DPoint &position, DAlign &dalign )
{
  ODockArea              *dock_area;
  logical                 term = NO;
BEGINSEQ
  if ( dock_widget )                                 LEAVESEQ
    
  if ( !(dock_area = parent->GetDockArea()) )        ERROR

  dock_widget = new ODockWidget(parent->ClientWidget(),WidgetOwner(),ods(),
                               WidgetFrame()); 
  dock_widget->set_od_control(this);
  
  dock_area->AddDockWidget(dock_widget,dalign);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Enable - 



\return term - 

\param  fEnable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Enable"

logical ODControl :: Enable (logical fEnable )
{

  if ( controlWidget ) 
    controlWidget->SetEnabled(fEnable);

  if ( label )
    label->SetEnabled(fEnable);
  return(NO);
}

/******************************************************************************/
/**
\brief  EnableInputHelp - 




\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableInputHelp"

void ODControl :: EnableInputHelp (logical enable_opt )
{

  if( this && controlWidget )
    controlWidget->EnableInputHelp(enable_opt);


}

/******************************************************************************/
/**
\brief  Execute - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ODControl :: Execute ( )
{
  QDialog   *qd   = NULL;
  logical    term = YES;
  if ( frameInnerWidget && frameInnerWidget->WidgetQ()->inherits("QDialog") &&
       (qd = ((QDialog*)(ODialog *)frameInnerWidget))->isModal()          )
    term = qd->exec() == QDialog::Accepted ? NO : YES;
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteDefaultAction - 



\return executed - Action executed

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDefaultAction"

int8 ODControl :: ExecuteDefaultAction (char *act_names )
{
  OEH       *oeh    = NULL;
  OEHAction *action = NULL;
  return (   controlWidget &&
             (oeh    = controlWidget->oeh()) && 
             (action = oeh->FindAction(act_names,NULL,NO))
           ? oeh->ExecuteReaction(action,YES)
           : AUTO );

}

/******************************************************************************/
/**
\brief  ExtraData - 



\return extra_data - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtraData"

void *ODControl :: ExtraData ( )
{

  return(extra_data);

}

/******************************************************************************/
/**
\brief  FrameWidget - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameWidget"

ODataWidget *ODControl :: FrameWidget ( )
{

  return( !this             ? NULL              :
          frameOuterWidget  ? frameOuterWidget  :
          frameInnerWidget  ? frameInnerWidget  :
          controlWidget     ? controlWidget     : NULL );


}

/******************************************************************************/
/**
\brief  GetActiveAction - Name of the currently toggled action object

        If  an action  has been  toggled, this  function returns the name of the
        action object previously set for this action when calling SetAction.

\return loid - Identification for an action object

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveAction"

char *ODControl :: GetActiveAction ( )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->GetActiveAction()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetActiveActionItem - 



\return loid - Identification for an action object

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveActionItem"

char *ODControl :: GetActiveActionItem ( )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->GetActiveActionItem()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetActiveControl - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveControl"

ODControl *ODControl :: GetActiveControl ( )
{

  return( GetCurrentControl() );

}

/******************************************************************************/
/**
\brief  GetBasePropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBasePropertyHandle"

PropertyHandle *ODControl :: GetBasePropertyHandle ( )
{

  return (   controlWidget 
           ? ((OEHDataWidget *)controlWidget)->GetBasePropertyHandle()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetButton - 



\return pODControl - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetButton"

ODControl *ODControl :: GetButton (char *control_name )
{

  return (   buttons 
           ? buttons->FindField(control_name)
           : NULL                                );


}

/******************************************************************************/
/**
\brief  GetButtonList - 



\return child_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetButtonList"

DLL(ODControl) *ODControl :: GetButtonList ( )
{

  if ( !buttons )
    buttons = new ODControlList();
  return(buttons);
}

/******************************************************************************/
/**
\brief  GetChildControl - 



\return pODControl - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChildControl"

ODControl *ODControl :: GetChildControl (int32 indx0 )
{
  ODControl                 *pODControl = NULL;
BEGINSEQ
  if ( indx0 < 0 || !controls )                      ERROR
    
  pODControl = controls->GetHead();
  while ( indx0-- )
    if ( !(pODControl = controls->GetNext()) )        
      ERROR
RECOVER
  pODControl = NULL;
ENDSEQ
  return(pODControl);
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

PropertyHandle *ODControl :: GetColumnPropertyHandle (int column )
{
  CellData   *cell = controlWidget ? 
                     controlWidget->Cell(AUTO,column) : NULL;
  return (   cell
           ? cell->GetPropertyHandle() 
           : NULL );


}

/******************************************************************************/
/**
\brief  GetConstant - 



\return pODControl - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConstant"

ODControl *ODControl :: GetConstant (char *control_name )
{

  return (   constants 
           ? constants->FindField(control_name)
           : NULL                                );


}

/******************************************************************************/
/**
\brief  GetConstantList - 



\return child_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConstantList"

DLL(ODControl) *ODControl :: GetConstantList ( )
{

  if ( !constants )
    constants = new ODControlList();
  return(constants);
}

/******************************************************************************/
/**
\brief  GetControl - 



\return pODControl - 

\param  control_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControl"

ODControl *ODControl :: GetControl (char *control_name )
{
  ODControl       *control = NULL;
BEGINSEQ
  if ( controls )
    if ( control = controls->FindControl(control_name) )
                                                     LEAVESEQ
  if ( buttons )
    if ( control = buttons->FindControl(control_name) )
                                                     LEAVESEQ
  if ( constants )
    if ( control = constants->FindControl(control_name) )
                                                     LEAVESEQ

ENDSEQ
  return(control);
}

/******************************************************************************/
/**
\brief  GetControlList - 



\return child_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlList"

DLL(ODControl) *ODControl :: GetControlList ( )
{

  if ( this && !controls )
    controls = new ODControlList();
  return(this ? controls : NULL);
}

/******************************************************************************/
/**
\brief  GetControlName - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlName"

char *ODControl :: GetControlName ( )
{
  char          *string = NULL;
  if ( controlWidget )
    string = controlWidget->GetName();
  else if ( clientOuterWidget )
    string = clientOuterWidget->GetName();
  else if ( clientInnerWidget )
    string = clientInnerWidget->GetName();
  

  return(string);
}

/******************************************************************************/
/**
\brief  GetControlWidget - Get Control Widget

        The  control widget is the data widget,  which is considered as the main
        widget  od  a  complex  control.  Usually  the data widget is the widget
        visible as edit area or list.

\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlWidget"

ODataWidget *ODControl :: GetControlWidget ( )
{

  return ( this ? controlWidget : NULL );

}

/******************************************************************************/
/**
\brief  GetCurrentControl - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentControl"

ODControl *ODControl :: GetCurrentControl ( )
{
  ODControl      *curr_control = NULL;
  ODataWidget    *odw = NULL;
  QObject        *fwidget = qApp->focusWidget();
  while ( fwidget && !(odw = OObject::GetODW(fwidget)) )
    fwidget = fwidget->parent();
 
  while ( odw && !(curr_control = odw->get_od_control()) )
    odw = odw->get_parent_odw();

  return(curr_control);
}

/******************************************************************************/
/**
\brief  GetCurrentPropertyHandle - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentPropertyHandle"

PropertyHandle *ODControl :: GetCurrentPropertyHandle ( )
{

  return (   controlWidget
           ? controlWidget->GetCurrentPropertyHandle() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetCurrentRegionID - 



\return region_id - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentRegionID"

int32 ODControl :: GetCurrentRegionID ( )
{

  return (   controlWidget 
           ? controlWidget->GetCurrentRegionID()
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  parent_id - 
\param  prop_path - Property path
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentRegionID"

int32 ODControl :: GetCurrentRegionID (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type )
{
  int32   region_id;

  return(region_id);
}

/******************************************************************************/
/**
\brief  GetDSPropertyHandle - Get PropertyHandle

        The  function returns the  property handle opend  as data background for
        the control.

\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDSPropertyHandle"

PropertyHandle *ODControl :: GetDSPropertyHandle ( )
{

  return (   controlWidget 
           ? controlWidget->GetPropertyHandle()
           : NULL );

}

/******************************************************************************/
/**
\brief  GetDockArea - 



\return dock_area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDockArea"

ODockArea *ODControl :: GetDockArea ( )
{

  return( !this ? NULL
                : dock_area ? dock_area
                            : parent->GetDockArea() );

}

/******************************************************************************/
/**
\brief  GetDropIndex - 



\return index - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropIndex"

int32 ODControl :: GetDropIndex ( )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->get_drop_index()
           : AUTO                         );

}

/******************************************************************************/
/**
\brief  GetDropPoint - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropPoint"

DPoint ODControl :: GetDropPoint ( )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? DPoint(oeh_dw->get_drop_point().x(),
                    oeh_dw->get_drop_point().y())
           : DPoint()    );


}

/******************************************************************************/
/**
\brief  GetDropPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropPropertyHandle"

PropertyHandle *ODControl :: GetDropPropertyHandle ( )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->get_decoded_propertyhandle()
           : NULL    );

}

/******************************************************************************/
/**
\brief  GetDropText - 



\return label_text - Label text

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropText"

char *ODControl :: GetDropText ( )
{
  OEHDataWidget     *oeh_dw;
  static QByteArray  static_qba;
  return (  (oeh_dw = controlOEHWidget()) 
           ? QS2SZ_P(oeh_dw->get_decoded_text(),static_qba)
           : NULL    );

}

/******************************************************************************/
/**
\brief  GetField - 



\return pODControl - 

\param  field_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetField"

ODControl *ODControl :: GetField (char *field_name )
{

  return (   controls 
           ? controls->FindField(field_name)
           : NULL                                );


}

/******************************************************************************/
/**
\brief  GetFont - 



\return dFont - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

DFont ODControl :: GetFont ( )
{
  DFont                   empty;
  return (   controlWidget 
           ? controlWidget->GetFont()
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

PropertyHandle *ODControl :: GetInitPropertyHandle ( )
{

  return (   controlWidget
           ? controlWidget->GetInitPropertyHandle() 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetLabelText - Get label text

        The function returns the text currently set for the label.

\return label_text - Label text

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLabelText"

char *ODControl :: GetLabelText ( )
{

  return(label->GetText());

}

/******************************************************************************/
/**
\brief  GetLastChildControl - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastChildControl"

ODControl *ODControl :: GetLastChildControl ( )
{
  ODControl                 *pODControl = NULL;
BEGINSEQ
  if ( !controls )                             ERROR
    
  pODControl = controls->GetTail();

RECOVER
  pODControl = NULL;
ENDSEQ
  return(pODControl);
}

/******************************************************************************/
/**
\brief  GetLayout - 



\return pOTreeLayout - Tree layout definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLayout"

OTreeLayout *ODControl :: GetLayout ( )
{
  OTreeLayout      *pOTreeLayout = NULL;
BEGINSEQ
  if ( controlWidget )
  {
    if ( !olayout )
      olayout = controlWidget->GetLayout();
    else  
      if ( olayout != controlWidget->get_olayout() ) OGUIERR(99)
  }
  else
    OEHDataWidget::GetLayout();
    
  pOTreeLayout = olayout;


RECOVER
  pOTreeLayout = NULL;
ENDSEQ
  return(pOTreeLayout);
}

/******************************************************************************/
/**
\brief  GetLineFont - 



\return DFont - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLineFont"

DFont ODControl :: GetLineFont (int column )
{
  DFont                   empty;
  return (   controlWidget 
           ? controlWidget->GetLineFont(column)
           : empty                        );

}

/******************************************************************************/
/**
\brief  GetListLayout - 



\return pOTreeLayout - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListLayout"

OTreeLayout *ODControl :: GetListLayout ( )
{

  return(controlWidget ? controlWidget->GetListLayout() : NULL);

}

/******************************************************************************/
/**
\brief  GetListValue - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListValue"

const char *ODControl :: GetListValue ( )
{
  char    *key;
  return (   controlWidget 
           ? key = controlWidget->List()->InstGetKeyString()
           : NULL );


}

/******************************************************************************/
/**
\brief  GetMousePosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMousePosition"

DPoint ODControl :: GetMousePosition ( )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->get_mouse_pos()
           : DPoint()    );


}

/******************************************************************************/
/**
\brief  GetName - 



\return names - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *ODControl :: GetName ( )
{

  return(name);

}

/******************************************************************************/
/**
\brief  GetParent - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParent"

ODControl *ODControl :: GetParent ( )
{

  return(this ? parent : NULL);

}

/******************************************************************************/
/**
\brief  GetSize - 



\return dsize - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

DSize &ODControl :: GetSize ( )
{
  QSize                   size;
  DSize                   ret;
BEGINSEQ
  if ( !this || !WidgetFrame() )                     ERROR

  size = WidgetFrame()->WidgetQ()->size();
  ret = DSize(size.width(),size.height());
RECOVER

ENDSEQ
  return ret;
}

/******************************************************************************/
/**
\brief  GetSubRegionCount - 



\return count - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int ODControl :: GetSubRegionCount (int32 region_id )
{

  return (   controlWidget 
           ? controlWidget->GetSubRegionCount(region_id)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  parent_id - 
\param  prop_path - Property path
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int ODControl :: GetSubRegionCount (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type )
{
  int   count;

  return(count);
}

/******************************************************************************/
/**
\brief  GetTabControl - 



\return pODTabControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTabControl"

ODTabControl *ODControl :: GetTabControl ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetTextPosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextPosition"

DPoint ODControl :: GetTextPosition ( )
{
  DPoint                 position;
  return ( this && controlWidget 
           ? controlWidget->GetTextPosition()
           : position );

}

/******************************************************************************/
/**
\brief  GetValue - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

PropertyHandle *ODControl :: GetValue ( )
{

  ProvideValue();
  value_handle = controlWidget->Value()->ValueGetString();
  

  return(&value_handle);
}

/******************************************************************************/
/**
\brief  Init - 




\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

void ODControl :: Init (char *names )
{

  if ( names )
    name = strdup(names);

}

/******************************************************************************/
/**
\brief  InitControlWidget - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitControlWidget"

logical ODControl :: InitControlWidget ( )
{
  logical                 term = NO;
  RemoveControlWidget();
  
  lmFrame = new OSimpleWidget(ClientWidgetParent(),
                              WidgetOwner(),odw_ods);
  lmFrame->SetControl(this);
  lmCells = new OControlLayout(lmFrame,0,0);

  if ( lmFrame->parent()->inherits("QSplitter") )
    ((QSplitter *)lmFrame->parentWidget())->addWidget(lmFrame);
  return(term);
}

/******************************************************************************/
/**
\brief  InstallEventFilter - 




\param  pQObject - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstallEventFilter"

void ODControl :: InstallEventFilter (QObject *pQObject )
{
  ODataWidget     *dw;
BEGINSEQ
  if ( !(dw = frameOuterWidget) && 
       !(dw = clientOuterWidget)    )              LEAVESEQ
    
  dw->WidgetQ()->installEventFilter(pQObject);

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsActionDisabled - 



\return cond - 

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionDisabled"

logical ODControl :: IsActionDisabled (char *act_names, char *loid )
{

  return ( this && controlWidget && 
           controlWidget->oeh()->IsActionDisabled(act_names,loid) );

}

/******************************************************************************/
/**
\brief  IsActionGrouped - 



\return cond - 

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionGrouped"

logical ODControl :: IsActionGrouped (char *act_names, char *loid )
{

  return ( this && controlWidget && 
           controlWidget->oeh()->IsActionGrouped(act_names,loid) );

}

/******************************************************************************/
/**
\brief  IsActionSeparated - 



\return cond - 

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionSeparated"

logical ODControl :: IsActionSeparated (char *act_names, char *loid )
{

  return ( this && controlWidget && 
           controlWidget->oeh()->IsActionSeparated(act_names,loid) );

}

/******************************************************************************/
/**
\brief  IsActionToggled - 



\return cond - 

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionToggled"

logical ODControl :: IsActionToggled (char *act_names, char *loid )
{

  return ( this && controlWidget && 
           controlWidget->oeh()->IsActionToggled(act_names,loid) );

}

/******************************************************************************/
/**
\brief  IsActionVisible - 



\return cond - 

\param  act_names - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionVisible"

logical ODControl :: IsActionVisible (char *act_names, char *loid )
{

  return ( this && controlWidget && 
           controlWidget->oeh()->IsActionVisible(act_names,loid) );

}

/******************************************************************************/
/**
\brief  IsButton - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsButton"

logical ODControl :: IsButton ( )
{

  return ( this && controlWidget && 
           controlWidget->WidgetQ()->inherits("QPushButton") );

}

/******************************************************************************/
/**
\brief  IsConstant - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConstant"

logical ODControl :: IsConstant ( )
{

  // gibts noch nicht
  return(NO);

}

/******************************************************************************/
/**
\brief  IsDestroying - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDestroying"

logical ODControl :: IsDestroying ( )
{

  return(is_destroying);

}

/******************************************************************************/
/**
\brief  IsField - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsField"

logical ODControl :: IsField ( )
{

  return ( this && !IsButton() && !IsConstant() );

}

/******************************************************************************/
/**
\brief  IsLocalDrop - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalDrop"

logical ODControl :: IsLocalDrop ( )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->IsLocalDrop(oeh_dw->WidgetQ()) 
           : NO    );


}

/******************************************************************************/
/**
\brief  LabelParentWidget - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LabelParentWidget"

ODataWidget *ODControl :: LabelParentWidget ( )
{

  return( !this            ? NULL              :
          lmFrame          ? lmFrame           :
          parent           ? parent->ClientWidgetParent()
                           : NULL);

}

/******************************************************************************/
/**
\brief  MenuWidgetParent - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MenuWidgetParent"

ODataWidget *ODControl :: MenuWidgetParent ( )
{

  return ( !this         ? NULL :
           controlWidget ? controlWidget :
           parent->MenuWidgetParent()      );


}

/******************************************************************************/
/**
\brief  ODControl - 



-------------------------------------------------------------------------------
\brief  i01 - 



\param  pODControl - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODControl"

     ODControl :: ODControl (ODControl *pODControl, char *names )
                     : OEHDataWidget (NULL,pODControl,YES),
  name(NULL),
  label(NULL),
  frameOuterWidget(NULL),
  frameInnerWidget(NULL),
  controlWidget(NULL),
  clientInnerWidget(NULL),
  clientOuterWidget(NULL),
  lmFrame(NULL),
  defaultHeight(0),
  grid_control(NO),
  lmCells(0),
  parent(pODControl),
  controls(NULL),
  buttons(NULL),
  constants(NULL),
  extra_data(NULL),
  dock_area(NULL),
  dock_widget(NULL),
  is_destroying(NO)
{

  Init(names);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  pODControl - 
\param  oODataWidget - Owning data widget
\param  create_ods - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODControl"

     ODControl :: ODControl (ODControl *pODControl, ODataWidget *oODataWidget, logical create_ods, char *names )
                     : OEHDataWidget (pODControl,oODataWidget,create_ods),
  name(NULL),
  label(NULL),
  frameOuterWidget(NULL),
  frameInnerWidget(NULL),
  controlWidget(NULL),
  clientInnerWidget(NULL),
  clientOuterWidget(NULL),
  lmFrame(NULL),
  defaultHeight(0),
  grid_control(NO),
  lmCells(0),
  parent(pODControl),
  controls(NULL),
  buttons(NULL),
  constants(NULL),
  extra_data(NULL),
  dock_area(NULL),
  dock_widget(NULL),
  is_destroying(NO)
{

  Init(names);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODControl"

     ODControl :: ODControl (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, char *names )
                     : OEHDataWidget (pODataWidget,oODataWidget,create_ods),
  name(NULL),
  label(NULL),
  frameOuterWidget(0),
  frameInnerWidget(0),
  controlWidget(0),
  clientInnerWidget(0),
  clientOuterWidget(0),
  lmFrame(0),
  lmCells(0),
  defaultHeight(0),
  grid_control(NO),
  parent(0),
  controls(NULL),
  buttons(NULL),
  constants(NULL),
  extra_data(NULL),
  dock_area(NULL),
  dock_widget(NULL),
  is_destroying(NO)
{

  Init(names);

}

/******************************************************************************/
/**
\brief  ProvideValue - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideValue"

PropertyHandle *ODControl :: ProvideValue ( )
{

  if ( !value_handle.IsValid() )
    value_handle.Open((char *)NULL);
  

  return(&value_handle);
}

/******************************************************************************/
/**
\brief  ReceiveSelectedItem - 



\return prop_hdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReceiveSelectedItem"

PropertyHandle *ODControl :: ReceiveSelectedItem ( )
{

  return ( this && controlWidget 
           ? controlWidget->ReceiveSelectedItem()
           : NULL );

}

/******************************************************************************/
/**
\brief  RefreshElements - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshElements"

logical ODControl :: RefreshElements ( )
{
  ODControl   *pODControl = NULL;
  logical      term       = NO;
BEGINSEQ
  if ( !controls )                                  LEAVESEQ
    
  controls->GoTop();
  while ( pODControl = controls->GetNext() )
    if ( pODControl->DA_Refresh() )
      term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RefreshRegion - 




\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshRegion"

void ODControl :: RefreshRegion (int32 region_id )
{

  if ( controlWidget )
    controlWidget->RefreshRegion(region_id);


}

/******************************************************************************/
/**
\brief  RegisterControlWidget - 



\return term - 

\param  control_name - 
\param  child_list - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterControlWidget"

logical ODControl :: RegisterControlWidget (char *control_name, DLL(ODControl) *child_list, int16 dsp_level )
{
  ODTabControl   *tab_parent = this && parent 
                               ? parent->GetTabControl() : NULL;
  logical         term = NO;
BEGINSEQ
  ODataWidget::SetDisplayLevel(dsp_level);
  
  if ( !controlWidget )                              OGUIERR(99)
    
  if ( child_list && !child_list->Find(this) )
    child_list->AddTail(this);
  if ( control_name && controlWidget->WidgetQ() )
    controlWidget->WidgetQ()->setObjectName(control_name);
    
  if ( lmCells )
    lmCells->addWidget(controlWidget->WidgetQ(),2,2);

  if ( olayout )
    controlWidget->SetLayout(olayout);
  
  if ( tab_parent )
    tab_parent->CreateTab(this,"text");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveButton - 



\return user_object - 

\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveButton"

void *ODControl :: RemoveButton (char *string )
{
  ODControl              *button;
  void                   *user_object = NULL;
BEGINSEQ
  if ( string && *string )
    button = buttons->FindField(string);
  if ( !button )                                   ERROR
    
  user_object = extra_data;
  buttons->Find(button);
  buttons->RemoveAt();
  delete button;

RECOVER
  user_object = NULL;
ENDSEQ
  return(user_object);
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

logical ODControl :: RemoveColumn (int32 region_id, int32 column_id )
{

  return (   controlWidget 
           ? controlWidget->RemoveColumn(region_id,column_id)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  RemoveConstant - 



\return user_object - 

\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveConstant"

void *ODControl :: RemoveConstant (char *string )
{
  ODControl              *constant;
  void                   *user_object = NULL;
BEGINSEQ
  if ( string && *string )
    constant = constants->FindField(string);
  if ( !constant )                                       ERROR
    
  user_object = extra_data;
  constants->Find(constant);
  constants->RemoveAt();
  delete constant;

RECOVER
  user_object = NULL;
ENDSEQ
  return(user_object);
}

/******************************************************************************/
/**
\brief  RemoveControl - 



\return pODControl - 

\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveControl"

ODControl *ODControl :: RemoveControl (char *string )
{
  ODControl              *control = NULL;
BEGINSEQ
  if ( string && *string )
    control = controls->FindControl(string);
  if ( !control )                                  ERROR
    
  controls->Remove(control);

RECOVER
  control = NULL;
ENDSEQ
  return(control);
}

/******************************************************************************/
/**
\brief  RemoveControlWidget - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveControlWidget"

void ODControl :: RemoveControlWidget ( )
{
  ODataWidget  *cwidget = controlWidget;
BEGINSEQ
  if ( !controlWidget )                              LEAVESEQ

  controlWidget = NULL;
  
  if ( clientInnerWidget == cwidget )
    clientInnerWidget = NULL;
  
  if ( clientOuterWidget == cwidget )
    clientOuterWidget = NULL;
  
  if ( frameOuterWidget == cwidget )
    frameOuterWidget = NULL;
  
  if ( frameInnerWidget == cwidget )
    frameInnerWidget = NULL;
  
  if ( olayout == cwidget->get_olayout() ) 
    olayout = NULL;
    
  if ( lmFrame )
    delete lmFrame;
  else if ( frameOuterWidget )
    delete frameOuterWidget;
  else if ( clientOuterWidget )
    delete clientOuterWidget;
  else
    delete cwidget;
    
  lmFrame = NULL;
  lmCells = NULL;
  frameOuterWidget  = NULL; 
  frameInnerWidget  = NULL; 
  clientOuterWidget = NULL;
  clientInnerWidget = NULL;
ENDSEQ

}

/******************************************************************************/
/**
\brief  RemoveField - 



\return user_object - 

\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveField"

void *ODControl :: RemoveField (char *string )
{
  ODControl              *control = this;
  void                   *user_object = NULL;
BEGINSEQ
  if ( string && *string )
    control = controls->FindField(string);
  if ( !control )                                  ERROR
    
  user_object = extra_data;
  controls->Find(control);
  controls->RemoveAt();
  delete control;

RECOVER
  user_object = NULL;
ENDSEQ
  return(user_object);
}

/******************************************************************************/
/**
\brief  RemoveInputHelp - 



\return term - 

\param  pODControl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveInputHelp"

logical ODControl :: RemoveInputHelp (ODControl *pODControl )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || !controlWidget || !pODControl )      ERROR

  controlWidget->RemoveInputHelp(pODControl->get_controlWidget());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reparent - 




\param  pODControl - 
\param  dsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reparent"

void ODControl :: Reparent (ODControl *pODControl, DSize &dsize )
{
  QWidget         *qwidget = WidgetQ();
BEGINSEQ
  if ( !this || !lmCells || !parent )                OGUIERR(99)
  
  if ( pODControl )
  {
    qwidget->setParent(pODControl->WidgetQ());
    UpdateSize(dsize);
  }
  else
  {
    qwidget->setParent(lmFrame);
    lmCells->addWidget(qwidget,2,2);
  }

RECOVER

ENDSEQ

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

int32 ODControl :: ReplaceSubRegions (int32 parent_id, int32 region_id )
{

  return (   controlWidget 
           ? controlWidget->ReplaceSubRegions(parent_id,region_id)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  ResetControlWidget - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetControlWidget"

void ODControl :: ResetControlWidget ( )
{

  if ( this )
  {
    if ( controlWidget && olayout == controlWidget->get_olayout() ) 
      olayout = NULL;
  
    controlWidget = NULL;
  }

}

/******************************************************************************/
/**
\brief  ResetDockWidget - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetDockWidget"

void ODControl :: ResetDockWidget ( )
{

  dock_widget = NULL;

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

logical ODControl :: ResetRegion (int32 parent_id, int32 region_id, logical reset_columns )
{

  return (   controlWidget 
           ? controlWidget->ResetRegion(parent_id,region_id,reset_columns)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  SetAcceptDrops - 



\return term - 

\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAcceptDrops"

logical ODControl :: SetAcceptDrops (logical enable_opt )
{
  logical                 term = NO;
BEGINSEQ
  if ( clientInnerWidget )
    clientInnerWidget->WidgetQ()->setAcceptDrops(enable_opt);
  else if ( clientOuterWidget )
    clientOuterWidget->WidgetQ()->setAcceptDrops(enable_opt);
  else if ( frameInnerWidget )
    frameInnerWidget->WidgetQ()->setAcceptDrops(enable_opt);
  else if ( frameOuterWidget )
    frameOuterWidget->WidgetQ()->setAcceptDrops(enable_opt);
  else                                               ERROR
    
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetAction - Provide an action for the complex control



\return action - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  parent_loid - 
\param  pOEHEvent - Event pointer
\param  oODataWidget_w - 
\param  pass_opt_w - 
\param  pass_to - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, char *parent_loid, OEHEvent *pOEHEvent, ODataWidget *oODataWidget_w, ActionBubbleType pass_opt_w, char *pass_to )
{

  return( controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,parent_loid,
                                     pOEHEvent,oODataWidget_w,NO,
                                     pass_opt_w,pass_to)
          : NULL);

}

/******************************************************************************/
/**
\brief  i00 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  parent_loid - 
\param  pass_opt_w - 
\param  pass_to - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, char *parent_loid, ActionBubbleType pass_opt_w, char *pass_to )
{

  return( controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,parent_loid,
                                     pass_opt_w,pass_to,NO)
          : NULL);


}

/******************************************************************************/
/**
\brief  i02 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  mouse_event - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, OEHMouseEvent mouse_event, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     mouse_event,oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  mouse_clicks - 
\param  key_alt - 
\param  key_shift - 
\param  key_ctrl - 
\param  mouse_right - 
\param  mouse_mid - 
\param  mouse_left - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, int mouse_clicks, logical key_alt, logical key_shift, logical key_ctrl, logical mouse_right, logical mouse_mid, logical mouse_left )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                OEHMouseEvent(mouse_clicks,key_alt,key_shift,key_ctrl,
                              mouse_right,mouse_mid,mouse_left),
                              NULL,NO)
          : NULL);

}

/******************************************************************************/
/**
\brief  i04 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  string - Character string
\param  oeh_frame - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, char *string, OEH_Frame oeh_frame, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     OEHShortcut(string,oeh_frame),
                                     oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i05 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  short_cut - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, OEHShortcut short_cut, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     short_cut,oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i06 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  int_event - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, int int_event, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     int_event,oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i07 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  data_event - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, DB_Event data_event, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     data_event,oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i08 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  time_event - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, OEHTimeEvent time_event, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     time_event,oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i09 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  start_date - 
\param  start_time - 
\param  dist_date - 
\param  dist_time - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, dbdt start_date, dbtm start_time, int32 dist_date, dbtm dist_time, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     OEHTimeEvent(start_date,start_time,dist_date,dist_time),
                                     oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i10 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  key_event - 
\param  oODataWidget_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, OEHKeyEvent key_event, ODataWidget *oODataWidget_w )
{

  return(   controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     key_event,oODataWidget_w)
          : NULL);

}

/******************************************************************************/
/**
\brief  i11 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  key_code - 
\param  key_alt - 
\param  key_shift - 
\param  key_ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

OEHAction *ODControl :: SetAction (const char *act_namesc, char *loid, int key_code, logical key_alt, logical key_shift, logical key_ctrl )
{

  return( controlWidget 
          ? controlWidget->SetAction(act_namesc,loid,
                                     OEHKeyEvent(key_code,key_alt,key_shift,key_ctrl),
                                     NULL,NO)
          : NULL);

}

/******************************************************************************/
/**
\brief  SetActionControl - Change visibility of action items

        By  default, action items shown for the action are visible. The function
        allows  changing the  visibility for  the action  items according to the
        passsed  option. Disable visibility (hide) all action items (menu items,
        buttons)  become invisible. Enable visibility will show the action items
        again. Invisible actions can still be executed.
        The  function will not change the appearance for the control, unless the
        control  itself is an action item associated with the action, which is a
        very rare case.

\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  pODControl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionControl"

logical ODControl :: SetActionControl (char *act_names, char *loid, ODControl *pODControl )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->SetActionWidget(act_names,loid,
                                                   pODControl ? pODControl->get_controlWidget() 
                                                              : NULL)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionDisabled - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionDisabled"

logical ODControl :: SetActionDisabled (char *act_names, char *loid, logical fEnabled )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->SetActionDisabled(act_names,loid,
                                              fEnabled)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionGrouped - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionGrouped"

logical ODControl :: SetActionGrouped (char *act_names, char *loid, logical fEnabled )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->SetActionGrouped(act_names,loid,
                                                    fEnabled)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionIcon - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  text - 
\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionIcon"

logical ODControl :: SetActionIcon (char *act_names, char *loid, char *text, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled )
{
  OIconSet     icon(pDPixmap_normal,pDPixmap_active,
                    pDPixmap_disabled);
  return (   this && controlWidget 
           ? controlWidget->oeh()->SetActionIcon(act_names,loid,
                                                 text,&icon) 
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionSeparated - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionSeparated"

logical ODControl :: SetActionSeparated (char *act_names, char *loid, logical fEnabled )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->SetActionSeparated(act_names,loid,
                                                      fEnabled)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionText - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  text - 
\param  tip - 
\param  status_tip - 
\param  what - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionText"

logical ODControl :: SetActionText (char *act_names, char *loid, char *text, char *tip, char *status_tip, char *what )
{

  return (   this && controlWidget 
           ? controlWidget->oeh()->SetActionText(act_names,loid,
                                                 text,tip,
                                                 status_tip,what)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionToggled - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionToggled"

logical ODControl :: SetActionToggled (char *act_names, char *loid, logical fEnabled )
{

  return (   this && controlWidget
           ? controlWidget->oeh()->SetActionToggled(act_names,loid,
                                                    fEnabled)
           : YES );

}

/******************************************************************************/
/**
\brief  SetActionVisible - 



\return term - 

\param  act_names - Action name
\param  loid - Identification for an action object
\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionVisible"

logical ODControl :: SetActionVisible (char *act_names, char *loid, logical fEnabled )
{

  return (   this && controlWidget
           ? controlWidget->oeh()->SetActionVisible(act_names,loid,
                                             fEnabled)
           : YES );

}

/******************************************************************************/
/**
\brief  SetAsMainWindow - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAsMainWindow"

void ODControl :: SetAsMainWindow ( )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
/* in QT4 funktionalitaet (so) nicht mehr verfuegbar

  if ( frameOuterWidget )
    qApp->setMainWidget(frameOuterWidget->WidgetQ());
  else if ( controlWidget )
    qApp->setMainWidget(controlWidget->WidgetQ());
*/
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetBasePath - 



\return term - 

\param  base_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBasePath"

logical ODControl :: SetBasePath (char *base_path )
{
  logical                 term = NO;
  return( controlWidget 
          ? controlWidget->SetBasePath(base_path)
          : YES);
  return(term);
}

/******************************************************************************/
/**
\brief  SetColumnFont - 



\return term - 

\param  pDFont - 
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnFont"

logical ODControl :: SetColumnFont (DFont *pDFont, int32 region_id, int32 column_id )
{

  return( controlWidget 
          ? controlWidget->SetColumnFont(pDFont,region_id,column_id)
          : YES);

}

/******************************************************************************/
/**
\brief  SetColumnPixmap - 



\return term - 

\param  pDPixmap - 
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnPixmap"

logical ODControl :: SetColumnPixmap (DPixmap *pDPixmap, int32 region_id, int32 column_id )
{

  return( controlWidget 
          ? controlWidget->SetColumnPixmap(pDPixmap,region_id,column_id)
          : YES);

}

/******************************************************************************/
/**
\brief  SetControlProperties - 




\param  dynamic_opt - 
\param  out_opt - 
\param  chache_opt - 
\param  max_length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControlProperties"

void ODControl :: SetControlProperties (logical dynamic_opt, logical out_opt, logical chache_opt, int32 max_length )
{

  dynamic    = dynamic_opt;
  readOnly   = out_opt;
//??         = max_length (ODataWidget, fehlt noch)
//data_cache = cache_opt  (ODataWidget, fehlt noch)



}

/******************************************************************************/
/**
\brief  SetControlWidget - 



\return term - 

\param  pODataWidget - Parent data widget
\param  child_list - 
\param  control_name - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControlWidget"

logical ODControl :: SetControlWidget (ODataWidget *pODataWidget, DLL(ODControl) *child_list, char *control_name, int16 dsp_level )
{
  logical         term = NO;
BEGINSEQ
  if ( controlWidget )                               OGUIERR(99)
    
  controlWidget = pODataWidget;
  controlWidget->set_od_control(this);
  BindClientWidget(controlWidget,0);
  
  RegisterControlWidget(control_name,child_list,dsp_level);
  
  controlWidget->SetReadOnly(readOnly);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDataSource - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical ODControl :: SetDataSource (DBObjectHandle &ob_handle )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->SetDataSource(ob_handle)
           : YES );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dictionary - 
\param  db_path - 
\param  accmode - 
\param  net_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical ODControl :: SetDataSource (DictionaryHandle *dictionary, char *db_path, PIACC accmode, logical net_opt )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->SetDataSource(dictionary,db_path,accmode,net_opt)
           : YES );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  ds_name - Data source name
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical ODControl :: SetDataSource (char *ds_name, PIACC accmode )
{
  OEHDataWidget    *oeh_dw;
  return (  (oeh_dw = controlOEHWidget()) 
           ? oeh_dw->SetDataSource(ds_name,accmode)
           : YES );

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

logical ODControl :: SetDatabaseHandle (DatabaseHandle &db_handle )
{
  logical   term = NO;
BEGINSEQ
  DeactivateElements(NO);
  
  if ( SetDataSource(db_handle) )                    ERROR

  ActivateElements(YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultReactions - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical ODControl :: SetDefaultReactions ( )
{
  logical                 term = NO;
OGUISET(777)
OGUIRESET
  if ( controlWidget )
    term = controlWidget->SetDefaultReactions();
  return(term);
}

/******************************************************************************/
/**
\brief  SetDisabled - Disable data widget

        The  function  disables  or  enables  the data widget, if possible. When
        being  disabled, the widget does not allow entering data and actions are
        disabled.  Passing  true  (YES)  will  disable the widget. Passing false
        (NO) will enable the widget.


\param  disable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisabled"

void ODControl :: SetDisabled (logical disable_opt )
{

  if ( controlWidget )
    controlWidget->SetDisabled(disable_opt);

}

/******************************************************************************/
/**
\brief  SetDisplayLevel - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical ODControl :: SetDisplayLevel (int16 dsp_level )
{

  return( this && controlWidget 
          ? controlWidget->SetDisplayLevel(dsp_level)
          : YES );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical ODControl :: SetDisplayLevel (char *typenames )
{

  return( this && controlWidget 
          ? controlWidget->SetType(typenames)
          : YES );


}

/******************************************************************************/
/**
\brief  i02 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical ODControl :: SetDisplayLevel (PropertyHandle *prophdl )
{

  return( this && controlWidget 
          ? controlWidget->SetType(prophdl)
          : YES );


}

/******************************************************************************/
/**
\brief  SetExtraData - 




\param  extra_data_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExtraData"

void ODControl :: SetExtraData (void *extra_data_ptr )
{

  extra_data = extra_data_ptr;

}

/******************************************************************************/
/**
\brief  SetFilter - 



\return term - 

\param  expression - 
\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical ODControl :: SetFilter (char *expression, logical enable_opt )
{

  return( this && controlWidget 
          ? controlWidget->SetFilter(expression,enable_opt)
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

logical ODControl :: SetFocus ( )
{
  logical         term = NO;
BEGINSEQ
  if ( this && controlWidget && controlWidget->WidgetQ() )
    controlWidget->WidgetQ()->setFocus();
  else                                               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetFont - 



\return term - 

\param  pDFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

logical ODControl :: SetFont (DFont *pDFont )
{

  return( controlWidget 
          ? controlWidget->SetFont(pDFont)
          : YES);

}

/******************************************************************************/
/**
\brief  SetHandleWidth - 



\return term - 

\param  handle_width - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHandleWidth"

logical ODControl :: SetHandleWidth (int16 handle_width )
{

  return(controlWidget->SetHandleWidth(handle_width));

}

/******************************************************************************/
/**
\brief  SetHelp - 



\return term - 

\param  text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHelp"

logical ODControl :: SetHelp (char *text )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( controlWidget )
    controlWidget->SetHelp(text);
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetHidden - Hide control

        The  functin allows hiding  or displaying a  control. Passing true (YES)
        wil hide the control. Passing false (NO) will show the control.


\param  hidden - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHidden"

void ODControl :: SetHidden (logical hidden )
{

  if ( controlWidget )
    Show(!hidden);
//  controlWidget->SetHidden(hidden);

}

/******************************************************************************/
/**
\brief  SetLabelText - Set label text

        The  function  is  setting  the  label  text  in  the area considered as
        control  lable. For  Windows, this  will be  the windows title line. For
        controls it is usuly the assigned control lable area.


\param  label_text - Label text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLabelText"

void ODControl :: SetLabelText (char *label_text )
{

  if ( label )
    label->setText(SZ2QS(label_text));

}

/******************************************************************************/
/**
\brief  SetLineFont - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  font_names - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical ODControl :: SetLineFont (char *font_names, int column )
{

  return( controlWidget 
          ? controlWidget->SetLineFont(font_names,column)
          : YES);
  return(YES);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pDFont - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical ODControl :: SetLineFont (DFont *pDFont, int column )
{

  return( controlWidget 
          ? controlWidget->SetLineFont(pDFont,column)
          : YES);
  return(YES);
}

/******************************************************************************/
/**
\brief  SetLinePixmap - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  pixmap_names - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLinePixmap"

logical ODControl :: SetLinePixmap (char *pixmap_names, int column )
{

  return( controlWidget 
          ? controlWidget->SetLinePixmap(pixmap_names,column)
          : YES);
  return(YES);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pDPixmap - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLinePixmap"

logical ODControl :: SetLinePixmap (DPixmap *pDPixmap, int column )
{

  return( controlWidget 
          ? controlWidget->SetLinePixmap(pDPixmap,column)
          : YES);
  return(YES);
}

/******************************************************************************/
/**
\brief  SetPalette - 



\return term - 

\param  pDLayout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPalette"

logical ODControl :: SetPalette (DLayout *pDLayout )
{
  QPalette                palette;
  logical                 term = NO;
  if ( controlWidget )
  {
    pDLayout->SetPalette(palette);
    controlWidget->WidgetQ()->setPalette(palette);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetPixmaps - 



\return term - 

\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPixmaps"

logical ODControl :: SetPixmaps (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled )
{
  ODTabControl   *tab_parent = this && parent 
                               ? parent->GetTabControl() : NULL;
  logical         term = NO;
  OIconSet icon_set(pDPixmap_normal,pDPixmap_active,pDPixmap_disabled);

  if ( tab_parent )
    ((OTab *)tab_parent->get_controlWidget())->SetTabIcon(&icon_set,display_level);
  else
    if ( controlWidget )
      controlWidget->SetIconSet(&icon_set);
  return(term);
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

logical ODControl :: SetPropertyHandle (PropertyHandle *prophdl, logical auto_select )
{
  DBObjectHandle      obhandle;
  logical             ta_started = NO;
  logical             blocked = NO;
  logical             term    = NO;
BEGINSEQ
  if ( parent && parent->ods()->get_prop() &&
       parent->ods()->get_prop() == ods()->get_prop() )
    parent->SetPropertyHandle(prophdl,auto_select);
  else
  {
    if ( !ods()->Handle()->Is(*prophdl) )  
    {
      ta_started = prophdl->StartRTA() ? YES : NO;
/*    
      obhandle = ods()->Handle()->GetObjectHandle();
      if ( obhandle.EventHandling() )
      {
        obhandle.DisableEventHandling();
        blocked = YES;
      }
*/        
      DeactivateElements(NO);
  
      if ( !(term = ODataWidget::SetPropertyHandle(prophdl,auto_select)) )
        ActivateElements(YES);
/*
      if ( blocked )
        obhandle.EnableEventHandling();
*/    
      prophdl->StopRTA(ta_started);

      if ( term )                                      ERROR
      ods()->get_prop()->EmitRefreshEvents();
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetReaction - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  act_names - Action name
\param  keycode - 
\param  key_alt - 
\param  key_shift - 
\param  key_ctrl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReaction"

logical ODControl :: SetReaction (char *act_names, int keycode, logical key_alt, logical key_shift, logical key_ctrl )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  act_names - Action name
\param  int_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReaction"

logical ODControl :: SetReaction (char *act_names, int int_event )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  act_names - Action name
\param  clicks - 
\param  key_alt - 
\param  key_shift - 
\param  key_ctrl - 
\param  mouse_right - 
\param  mouse_mid - 
\param  mouse_left - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReaction"

logical ODControl :: SetReaction (char *act_names, char clicks, logical key_alt, logical key_shift, logical key_ctrl, logical mouse_right, logical mouse_mid, logical mouse_left )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetReadOnly - Set Control to read-only state

        The  control is  set into  the read-only  state, which shows the control
        with  a disabled lable  and which does  not allow entering data into the
        control.  Context  menu  and  actions  for the control are still active.
        Passinf  true  (YES)  to  the  function will enable the read-only state,
        passing false (NO) will disable the read-only state.


\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void ODControl :: SetReadOnly (logical fReadOnly )
{

  if ( controlWidget ) 
  {
    OWidget::SetReadOnly(fReadOnly);
    controlWidget->SetReadOnly(fReadOnly);
  }

}

/******************************************************************************/
/**
\brief  SetRegionFont - 



\return term - 

\param  pDFont - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionFont"

logical ODControl :: SetRegionFont (DFont *pDFont, int32 region_id )
{

  return( controlWidget 
          ? controlWidget->SetRegionFont(pDFont,region_id)
          : YES);

}

/******************************************************************************/
/**
\brief  SetRegionPixmap - 



\return term - 

\param  pDPixmap - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionPixmap"

logical ODControl :: SetRegionPixmap (DPixmap *pDPixmap, int32 region_id )
{

  return( controlWidget 
          ? controlWidget->SetRegionPixmap(pDPixmap,region_id)
          : YES);

}

/******************************************************************************/
/**
\brief  SetSize - 




\param  rcDSize - 
\param  hgrow - 
\param  vgrow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void ODControl :: SetSize (const DSize &rcDSize, logical hgrow, logical vgrow )
{
  QWidget    *frame  = WidgetFrame()->WidgetQ();
  QWidget    *parent = frame->parentWidget();
  QSize       size(DSIZE2QSIZE(rcDSize));
BEGINSEQ
  if ( !this || !frame )                           ERROR

  if ( parent && parent->inherits("QDockWidget") )
    ((ODockWidget *)parent)->UpdateSize((DSize &)rcDSize,
                            vgrow ? SIZE_Grow : SIZE_Fixed,
                            hgrow ? SIZE_Grow : SIZE_Fixed,
                            0,0);
                            
  WidgetFrame()->UpdateSize((DSize &)rcDSize,
                            vgrow ? SIZE_Grow : SIZE_Fixed,
                            hgrow ? SIZE_Grow : SIZE_Fixed,
                            0,0);
                            
// so einfach gehts nicht. Hier muss man rechnen
  controlWidget->UpdateSize((DSize &)rcDSize,
                            vgrow ? SIZE_Grow : SIZE_Fixed,
                            hgrow ? SIZE_Grow : SIZE_Fixed,
                            0,0);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetText - 



\return term - 

\param  title_text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

logical ODControl :: SetText (char *title_text )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( controlWidget && title_text )
  {
    if ( controlWidget->WidgetQ()->inherits("QAbstractButton") )
      ((QAbstractButton *)controlWidget->WidgetQ())->setText(SZ2QS(title_text));
    else
      controlWidget->Value()->ValueSet(title_text);
  }
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetTextPosition - 




\param  position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextPosition"

void ODControl :: SetTextPosition (DPoint &position )
{

  if ( controlWidget )
    controlWidget->SetTextPosition(position);

}

/******************************************************************************/
/**
\brief  SetTextSelection - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  start_pos - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void ODControl :: SetTextSelection (int32 start_pos, int32 length )
{

  if ( controlWidget )
    controlWidget->SetTextSelection(start_pos,length);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  start_point - 
\param  end_point - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void ODControl :: SetTextSelection (DPoint start_point, DPoint end_point )
{

  if ( controlWidget )
    controlWidget->SetTextSelection(start_point,end_point);

}

/******************************************************************************/
/**
\brief  SetTitle - 




\param  title_text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTitle"

void ODControl :: SetTitle (char *title_text )
{

BEGINSEQ
  if ( !this || !title_text )                                LEAVESEQ
    
  if ( frameOuterWidget )
    frameOuterWidget->WidgetQ()->setWindowTitle(SZ2QS(title_text));
  else if ( dock_widget )
    dock_widget->setWindowTitle(SZ2QS(title_text));
  else if ( label )
    SetLabelText(title_text);
  else if ( controlWidget && controlWidget->WidgetQ()->inherits("QFrame") )
    controlWidget->WidgetQ()->setWindowTitle(SZ2QS(title_text));

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetTooltip - 



\return term - 

\param  text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTooltip"

logical ODControl :: SetTooltip (char *text )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( controlWidget )
    controlWidget->SetTooltip(text);
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetUserActionHdl - 



\return term - 

\param  pOEHActionHandler - 
\param  gui_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserActionHdl"

logical ODControl :: SetUserActionHdl (OEHActionHandler *pOEHActionHandler, logical gui_opt )
{
  logical      term = NO;
BEGINSEQ
  if ( !controlWidget )                                ERROR

  if ( controlWidget->SetUserActionHdl(pOEHActionHandler,gui_opt) )
                                                       ERROR
  if ( controlWidget->GenerateEvent(GEV_Open) == YES ) ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical ODControl :: SetValue ( )
{
  logical      term = NO;
BEGINSEQ
  if ( SetText(ProvideValue()->GetString()) )        ERROR
  if ( DA_StoreEntry() )                             ERROR
RECOVER
  term = YES;
ENDSEQ
  DA_Refresh();
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical ODControl :: SetValue (PropertyHandle *prophdl )
{
  logical                 term = NO;
  *ProvideValue() = *prophdl;
  
  term = SetValue();
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical ODControl :: SetValue (char *text )
{
  logical                 term = NO;
  *ProvideValue() = text;
  
  term = SetValue();
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

logical ODControl :: SetVirtualType (PropertyHandle *prophdl )
{
  DBObjectHandle      obhandle;
  ODControl          *ctl         = NULL;
  char               *struct_name = NULL;
  char               *strnames    = NULL;
  logical             blocked     = NO;
  logical             term        = NO;
BEGINSEQ
  if ( !prophdl || !prophdl->IsValid() )             OGUIERR(17)
  
  if ( dynamic )
  {
    strnames = prophdl->GetCurrentType();
    if ( !ods()->Handle()->Is(*prophdl) ) /* && type not changed */ 
    {  
      obhandle = ods()->Handle()->GetObjectHandle();
      if ( obhandle.EventHandling() )
      {
        obhandle.DisableEventHandling();
        blocked = YES;
      }
    
      DeactivateElements(NO);
  
      if ( blocked )
        obhandle.EnableEventHandling();
    
      if ( controlWidget->SetType(prophdl) )        ERROR
    }
  }    
  SetPropertyHandle(prophdl,NO);

/*  war erst so gedacht  
  controls->GoTop();
  while ( ctl = controls->GetNext() )
    if ( (struct_name = ctl->ods()->GetStructure()) && !strcmp(strnames,struct_name) )
    {
      ctl->SetPropertyHandle(prophdl,NO);
      controlWidget->SetType(strnames);
    }
*/

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  type - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVirtualType"

logical ODControl :: SetVirtualType (char *scoped_name )
{
  logical            term = NO;
BEGINSEQ
  if ( !scoped_name || !*scoped_name )            OGUIERR(17)
  
  if ( dynamic )
    if ( controlWidget->SetType(scoped_name) )    ERROR


RECOVER
  term = YES;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetWindowFlags - 




\param  reset_flags - 
\param  has_title - 
\param  has_border - 
\param  has_close - 
\param  has_resize - 
\param  has_minmax - 
\param  has_sysmenu - 
\param  is_top_always - 
\param  has_small_title - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWindowFlags"

void ODControl :: SetWindowFlags (logical reset_flags, logical has_title, logical has_border, logical has_close, logical has_resize, logical has_minmax, logical has_sysmenu, logical is_top_always, logical has_small_title )
{

  FrameWidget()->SetWindowFlags(reset_flags,has_title,
                     has_border,has_close,has_resize,has_minmax,
                     has_sysmenu,is_top_always,has_small_title);

}

/******************************************************************************/
/**
\brief  SetZoomOutWindow - 



\return term - 

\param  pODControl - 
\param  auto_zoom - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetZoomOutWindow"

logical ODControl :: SetZoomOutWindow (ODControl *pODControl, char auto_zoom )
{
  ODataWidget    *zoom_out = NULL;
  logical         term     = NO;
BEGINSEQ
  if ( !controlWidget || !pODControl )               ERROR
  
  if ( pODControl->GetTabControl() )
    zoom_out = pODControl->get_lmFrame();
  else
    zoom_out = pODControl->get_controlWidget();
    
  controlWidget->SetZoomOutWidget(zoom_out,auto_zoom);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupFont - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupFont"

logical ODControl :: SetupFont ( )
{

  return( controlWidget 
          ? controlWidget->SetupFont()
          : YES);

}

/******************************************************************************/
/**
\brief  SetupParentDataSource - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupParentDataSource"

void ODControl :: SetupParentDataSource ( )
{
  ODataWidget   *parent_dw;
BEGINSEQ
  if ( !this || !controlWidget ||
       !(parent_dw = controlWidget->get_owning_odw()) )
                                                     LEAVESEQ
    
  controlWidget->ods()->SetParentODS(parent_dw->GetSelectedODS());

ENDSEQ

}

/******************************************************************************/
/**
\brief  Show - 




\param  fShow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

void ODControl :: Show (logical fShow )
{
  QWidget  *w  = NULL;
  ODialog  *wd = NULL;

  if ( frameOuterWidget ) 
  {
    w = frameOuterWidget->WidgetQ();
    if ( w->inherits("QDialog") )
      wd = (ODialog *)frameOuterWidget;
  }
  else if ( clientOuterWidget ) 
    w = clientOuterWidget->WidgetQ();

  // nötig, weil qt sonst abstürtzt, Dockarea (parent) muss Show vor 
  if ( dock_widget )
  {
    if ( fShow )
      dock_widget->show(); 
    else 
      dock_widget->hide();
  }
  
  if ( lmFrame )
  {
    if ( fShow )
      lmFrame->show(); 
    else 
      lmFrame->hide();
  }
  
  if ( w )
  {
    if ( !fShow )
      w->hide();
    else
    {
      if ( !wd || !wd->isModal() )  
        w->show(); 
//      else
//        wd->exec();
    }
  }

  if ( label )
  {
    if ( fShow )
      label->show(); 
    else 
      label->hide();
  }

  controlWidget->ShowToolbars();

}

/******************************************************************************/
/**
\brief  UpdateFrameStyle - Set frame style




\param  pDBorder - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateFrameStyle"

void ODControl :: UpdateFrameStyle (DBorder *pDBorder )
{
  ODTabControl   *tab = NULL;
  ODataWidget    *odw = NULL;

  if ( tab = GetTabControl() )
  {
    if ( odw = tab->PanelWidgetParent() )
      odw->SetFrameStyle(pDBorder);
  }
  else
  {
    if ( frameOuterWidget )
      frameOuterWidget->SetFrameStyle(pDBorder);
    
    if ( controlWidget )
      controlWidget->SetFrameStyle(!frameOuterWidget ? pDBorder : NULL);
    
    if ( clientInnerWidget )
      clientInnerWidget->SetFrameStyle(!frameOuterWidget && !controlWidget ? pDBorder : NULL);
  }

}

/******************************************************************************/
/**
\brief  UpdateLayout - 




\param  position - 
\param  inner_dist - 
\param  outer_dist - 
\param  dsize - 
\param  frame_size - 
\param  dalign - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

void ODControl :: UpdateLayout (DPoint &position, int16 inner_dist, int16 outer_dist, DSize &dsize, DSize &frame_size, DAlign &dalign, int16 dsp_level )
{
  OControlLayout *parent_oc    = parent  ? parent->get_lmCells() : NULL;
BEGINSEQ
statistics5.Start();
  ODataWidget::SetDisplayLevel(dsp_level); // könnte auch OEHDataWidget sein
  if ( !parent || !controlWidget )               LEAVESEQ

  if ( lmCells && !dalign.get_margin().IsEmpty() )
    lmCells->SetInnerMargin(dalign.get_margin());    
  
//  if ( inner_dist && controlWidget->FrameQ() )
//    controlWidget->FrameQ()->setContentsMargins(inner_dist,inner_dist,inner_dist,inner_dist);
                            
  controlWidget->UpdateSize(dsize,dalign.get_vertSizing(),dalign.get_horiSizing(),
                            dalign.get_horiSizingRate(),dalign.get_vertSizingRate());
  
  if ( parent_oc && !dalign.IsInside() )  // parent is simple grid widget (outer element)
  {
    if ( WidgetFrame()->WidgetQ()->parent() != parent->WidgetFrame()->WidgetQ() )
      WidgetFrame()->WidgetQ()->setParent(parent->WidgetFrame()->WidgetQ());

    WidgetFrame()->UpdateSize(frame_size,dalign.get_vertSizing(),dalign.get_horiSizing(),
                              dalign.get_horiSizingRate(),dalign.get_vertSizingRate());
    parent->get_lmFrame()->UpgradeSizePolicy(dalign.get_vertSizing(),dalign.get_horiSizing());
    parent_oc->PositionElement(WidgetFrame(),dalign.get_vert(),dalign.get_hori());
  }
  else if ( !parent || !parent->get_grid_control() || dalign.get_arrange() != AT_Grid )
  {
    WidgetFrame()->SetGeometry(position,frame_size);
  }
  else // position in (Grid) layout
  {
    WidgetFrame()->UpdateSize(parent->ClientWidget()->WidgetQ(),parent->get_grid_control(),frame_size,position,dalign);
  }
  if ( lmCells )
    lmCells->SetMargin(outer_dist);
  if ( lmFrame && lmFrame->parent() && lmFrame->parent()->inherits("QSplitter")){
    lmFrame->UpgradeSizePolicy(dalign.get_vertSizingRate(), dalign.get_horiSizingRate());
  }
  if ( lmFrame && lmFrame->parent() && lmFrame->parent()->inherits("QWidgetStack")){
    lmFrame->UpdateSize(dsize);
  }
  ClientWidget()->SetSpacing(inner_dist);
  if ( dalign.Arrange(AT_Absolut) == AT_Docking )
    DockControl(position,dalign);
ENDSEQ
statistics5.Stop();

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

logical ODControl :: UpdateTreeLayout (int32 region_id )
{

  return (   controlWidget 
           ? controlWidget->UpdateTreeLayout(region_id)
           : UNDEF                               );


}

/******************************************************************************/
/**
\brief  WidgetFrame - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetFrame"

ODataWidget *ODControl :: WidgetFrame ( )
{

  return !this             ? NULL              :
         lmFrame           ? lmFrame           :
         frameOuterWidget  ? frameOuterWidget  :
         frameInnerWidget  ? frameInnerWidget  :
         clientOuterWidget;


}

/******************************************************************************/
/**
\brief  WidgetOwner - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetOwner"

ODataWidget *ODControl :: WidgetOwner ( )
{

  return(parent ? parent->GetControlWidget()  : NULL);

}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODControl :: WidgetQ ( )
{

  return(controlWidget ? controlWidget->WidgetQ() : NULL);

}

/******************************************************************************/
/**
\brief  controlOEHWidget - 



\return pOEHDataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "controlOEHWidget"

OEHDataWidget *ODControl :: controlOEHWidget ( )
{

  return (   this && controlWidget 
           ? controlWidget->DataWidgetOEH()
           : NULL );

}

/******************************************************************************/
/**
\brief  setReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setReadOnly"

void ODControl :: setReadOnly (logical fReadOnly )
{

  if ( label )
    label->setDisabled(fReadOnly);

}

/******************************************************************************/
/**
\brief  ~ODControl - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODControl"

     ODControl :: ~ODControl ( )
{

  Destroy();

}


