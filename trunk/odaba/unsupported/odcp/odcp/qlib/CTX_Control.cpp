/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    CTX_Control

\brief    GUI control context
          GUI  control  context  class  provides  basic  functionality  for  GUI
          controls.  Each GUI control in an ODABA application is associated with
          a  GUI  control  context  class,  which  can  be  implemented  by  the
          application.  The context  class for  a GUI  control is defined in the
          field  control definition (general context)  or in the field defintion
          (specific  context).  A  context  class  in  the  field defintion will
          replace the context class definition in the control. 
          All  application context classed must be  derived from the GUI control
          context class.

\date     $Date: 2006/08/26 17:11:57,93 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Control"

#include  <podcp8.h>
#include  <cqt.h>
#include  <sCTX_Control.hpp>
#include  <sTWidgetControl.hpp>
#include  <iigui.h>
#include  <ioadii.h>
#include  <sCTX_Control.hpp>


/******************************************************************************/
/**
\brief  AcceptDrops - Accept drop events

        The  function enables or disables the control for accepting drop events.
        Usually,  drop  events  are  handled  by  the  control  according to the
        control  type. You may, however, handle different phases of the event by
        specific context actions as "DoBeforeDrop" or "DoAfterDrop".


\param  drop_opt - Drop option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AcceptDrops"

void CTX_Control :: AcceptDrops (logical drop_opt )
{

  if ( this && control )
    control->AcceptDrops(drop_opt);

}

/******************************************************************************/
/**
\brief  ActivateControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateControl"

void CTX_Control :: ActivateControl ( )
{

  if ( this && control )
    control->Activate();

}

/******************************************************************************/
/**
\brief  ActiveAction - 



\return minames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActiveAction"

char *CTX_Control :: ActiveAction ( )
{

  return ( control->ActiveAction() );


}

/******************************************************************************/
/**
\brief  ActiveActionItem - 



\return minames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActiveActionItem"

char *CTX_Control :: ActiveActionItem ( )
{

  return ( control->ActiveActionItem() );

}

/******************************************************************************/
/**
\brief  AddColumn - 



\return column_id - 

\param  parent_id - 
\param  prop_path - 
\param  is_collection - 
\param  text - 
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

int32 CTX_Control :: AddColumn (int32 parent_id, char *prop_path, logical is_collection, char *text, ADK_DataReferenceType ref_type )
{

  return ( this && control ? control->AddColumn(parent_id,prop_path,text,ref_type) : UNDEF );

}

/******************************************************************************/
/**
\brief  AddRegion - Create Region

        For  a  list  view  or  tree you may dynamically create new regions. New
        regions  are appended  at the  end ot  the sub-region list of the parent
        region.  When  no  parent  region  id  (0) is passed, the region will be
        added at the end of the list.
        The parent region id can be obtained by calling GetCurrentRegionID().
        The  function returns  the identifier  (ID) for  the region created. The
        region can be removed by calling RemoveRegion().
        Subregions   can   be   added   to   a   region   also   by   calling  
        ReplaceSubRegions().

\return region_id - 

\param  parent_id - 
\param  prop_path - 
\param  is_collection - 
\param  text - 
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

int32 CTX_Control :: AddRegion (int32 parent_id, char *prop_path, logical is_collection, char *text, ADK_DataReferenceType ref_type )
{

  return ( this && control ? control->AddRegion(parent_id,prop_path,text,
                                                is_collection,ref_type) : UNDEF );

}

/******************************************************************************/
/**
\brief  AssociateData - Associate data/instance from base collection

        The  function associates one or more  instances from the base collection
        of  the current control  to the collection  the current control is based
        on.  In order  to select  instances from  the default base collection as
        being  defined in the data source for  the control, you may pass NULL as
        source_ph.  You may, however,  define or locate  your own collextion and
        passing it to the function via source_ph.
        The  function opens  a standard  dialogue, which  lists the instances of
        the  base  collection  and  e  check  box  for selecting instances to be
        linked.  You may  define your  own selection  list layout by defining an
        appropriate  control  in  the  class  the base collection refers to. The
        default  control name  is "associate",  which can  be overwritten by the
        control_name option.

\return term - 

\param  source_ph - 
\param  control_name - Control name
\param  title - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AssociateData"

logical CTX_Control :: AssociateData (PropertyHandle *source_ph, char *control_name, char *title )
{

  return(control->AssociateData(source_ph,control_name,title));

}

/******************************************************************************/
/**
\brief  BlockEvents - Block database events

        The  function can be called to block  database events from being sent to
        the  GUI. The  function returns  the blocking  state before blocking the
        events.

\return term - 

\param  block_opt - Event blocking option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockEvents"

logical CTX_Control :: BlockEvents (logical block_opt )
{

//  return ( control->BlockEvents(block_opt) );
  return(NO);

}

/******************************************************************************/
/**
\brief  CTX_Control - Constructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Control"

     CTX_Control :: CTX_Control ( )
                     : CTX_GUIBase ()
{



}

/******************************************************************************/
/**
\brief  CreateButton - Create Button

        The  function creates a button for a field control. The button name must
        refer to a button defined for the control resource. 
        The  function  can  be  used  to  activate  buttons, which have not been
        activated when opening the control (auto_open = NO).
        When  the button is requested in design mode, it will be loaded from the
        data-data  base instead of the resource database. This feature is mainly
        used  in  design  mode,  but  can  also  be  used  for  overloading  or 
        customizing applications.

\return ctl_context - 

\param  name_s - Name of resoure
\param  design_mode - Indicates design mode
\param  position - 
\param  resource_id - Resource ID
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateButton"

CTX_Control *CTX_Control :: CreateButton (char *name_s, logical design_mode, DPoint position, int resource_id )
{

  PropertyHandle  class_ph(design_mode ? GetDATDB()
                                       : GetRESDB(),"ADK_Class",PI_Read);
  return(control->CreateButton(class_ph,name_s,position,resource_id));

}

/******************************************************************************/
/**
\brief  CreateConstant - Create constant

        The  function  creates  a  constant  element  for  a  field control. The
        constant  name  must  refer  to  a  constant  defined  for  the  control
        resource.  The function  can be  used to  activate constants, which have
        not been activated when opening the control (auto_open = NO).
        When  the constant is  requested in design  mode, it will be loaded from
        the  data-data base  instead of  the resource  database. This feature is
        mainly  used  in  design  mode,  but can also be used for overloading or
        customizing applications.

\return term - 

\param  name_s - Name of resoure
\param  design_mode - Indicates design mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateConstant"

logical CTX_Control :: CreateConstant (char *name_s, logical design_mode )
{

  PropertyHandle  class_ph(design_mode ? GetDATDB()
                                       : GetRESDB(),"ADK_Class",PI_Read);
  return(control->CreateConstant(class_ph,name_s));

}

/******************************************************************************/
/**
\brief  CreateControl - Create dynamical Control

        The  function creates a control for the field control passed and returns
        the control context.

\return ctl_context - 

\param  name_s - Name of resoure
\param  control_ph - 
\param  size - 
\param  position - 
\param  data_source - 
\param  dsp_level - 
\param  resource_id - Resource ID
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateControl"

CTX_Control *CTX_Control :: CreateControl (char *name_s, PropertyHandle *control_ph, DSize size, DPoint position, char *data_source, int16 dsp_level, int resource_id )
{
  TWidgetControl     *ctrl;
  CTX_Control        *context = NULL;
BEGINSEQ
  if ( !(ctrl = CreateField_intern(name_s,control_ph,control,size,position,dsp_level,NO,resource_id,NULL,YES)) )
                                                     ERROR
  context = ctrl->get_context();
RECOVER
  context = NULL;
ENDSEQ
  return(context);
}

/******************************************************************************/
/**
\brief  CreateField - Create field

        The  function creates a  field for a  field control. The field name must
        refer to a field defined for the control. 
        The  function  can  be  used  to  activate  fields,  which have not been
        activated when opening the control (auto_open = NO).
        When  the field is requested in design  mode, it will be loaded from the
        data-data  base instead of the resource database. This feature is mainly
        used  in  design  mode,  but  can  also  be  used  for  overloading  or 
        customizing applications.

\return ctl_context - 

\param  name_s - Name of resoure
\param  design_mode - Indicates design mode
\param  position - 
\param  resource_id - Resource ID
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField"

CTX_Control *CTX_Control :: CreateField (char *name_s, logical design_mode, DPoint position, int resource_id )
{

  PropertyHandle  class_ph(design_mode ? GetDATDB()
                                       : GetRESDB(),"ADK_Class",PI_Read);
  return( control->CreateField(class_ph,name_s,position,design_mode,resource_id) );

}

/******************************************************************************/
/**
\brief  DeactivateControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateControl"

void CTX_Control :: DeactivateControl ( )
{

  if ( this && control )
    control->Deactivate();

}

/******************************************************************************/
/**
\brief  FillControl - Fill control

        The  function can be used for  explicitly filling the control after data
        has  changed  in  the  instance  displayed  in the control. Usually, all
        changes  in  data  is  registered  and reflected in the control. In some
        cases  (e.g.  when  bloccking  events  with  BlockEvents())  it  might, 
        however,  better to  refill the  control explicitly  after data has been
        changed by the context.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillControl"

logical CTX_Control :: FillControl ( )
{

  return ( this ? control->FillControl() : YES );

}

/******************************************************************************/
/**
\brief  GetActiveElementContext - Get context for active control

        The  active control  is the  control, which  is currently selected or on
        top.  Tor idget  stacks or  tab-controls, this  the the control recently
        activated.  For  ordenary  window  controls  it  is  the  control  which
        currently  has  the  focus.  For  a  workspace  the function returns the
        context of the active MDI window.

\return ctx_ctl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveElementContext"

CTX_Control *CTX_Control :: GetActiveElementContext ( )
{
  TWidgetControl     *sub_control;
  CTX_Control        *ctx_ctl = NULL;
BEGINSEQ
  if ( !(sub_control = control->GetActiveControl()) )    ERROR
  ctx_ctl = sub_control->GetContext();

RECOVER
  ctx_ctl = NULL;
ENDSEQ
  return(ctx_ctl);
}

/******************************************************************************/
/**
\brief  GetBasePropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBasePropertyHandle"

PropertyHandle *CTX_Control :: GetBasePropertyHandle ( )
{
  PropertyHandle     *ph;
  ph = control->GetBasePropertyHandle();
  return ( ph && ph->IsValid() ? ph : NULL );

}

/******************************************************************************/
/**
\brief  GetButtonContext - Get button context by button name

        The  function searches for  a subordinated button  with the passed name.
        When  a  name  has  been  used  several  times, the function returns the
        context for the first button with the given name.

\return ctx_ctl - 

\param  button_name - Button name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetButtonContext"

CTX_Control *CTX_Control :: GetButtonContext (char *button_name )
{
  char               *wstring = NULL;
  char               *point   = NULL;
  TWidgetControl     *sub_control;
  CTX_Control        *ctx_ctl = NULL;
BEGINSEQ
  if ( button_name && *button_name == '.' )
  {
    if ( GetHighContext(CTXT_Control) )
      ctx_ctl = ((CTX_Control *)GetHighContext())->GetButtonContext(button_name+1);
    LEAVESEQ
  }
  
  if ( !button_name )                                ERROR
    
  wstring = strdup(button_name);
  if ( point = strchr(wstring,'.') )
    *point = 0;
          
  if ( sub_control = control->GetButton(wstring) )
    ctx_ctl = sub_control->GetContext();
  
  if ( !ctx_ctl )                                   OADIERR(7)

  if ( point )
    ctx_ctl = ctx_ctl->GetButtonContext(point+1);

RECOVER
  ctx_ctl = NULL;
ENDSEQ
  return(ctx_ctl);
}

/******************************************************************************/
/**
\brief  GetColumnPropertyHandle - 



\return prophdl - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetColumnPropertyHandle"

PropertyHandle *CTX_Control :: GetColumnPropertyHandle (int32 column )
{

  return ( this ? control->GetColumnPropertyHandle(column) : NULL );


}

/******************************************************************************/
/**
\brief  GetConstantContext - Get button context by constant name

        The  function searches for a subordinated constant with the passed name.
        When  a  name  has  been  used  several  times, the function returns the
        context for the first constant with the given name.
        The  name  may  contain  a  path  to  the  control,  also  with starting
        points(s) for higher context levels(s).

\return ctx_ctl - 

\param  const_name - Constant name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConstantContext"

CTX_Control *CTX_Control :: GetConstantContext (char *const_name )
{
  char               *wstring = NULL;
  char               *point   = NULL;
  TWidgetControl     *sub_control;
  CTX_Control        *ctx_ctl = NULL;
BEGINSEQ
  if ( const_name && *const_name == '.' )
  {
    if ( GetHighContext(CTXT_Control) )
      ctx_ctl = ((CTX_Control *)GetHighContext())->GetConstantContext(const_name+1);
    LEAVESEQ
  }
  
  if ( !const_name )                                   ERROR
    
  wstring = strdup(const_name);
  if ( point = strchr(wstring,'.') )
    *point = 0;
          
  if ( sub_control = control->GetConstant(wstring) )
    ctx_ctl = sub_control->GetContext();
  
  if ( !ctx_ctl )                                   OADIERR(7)

  if ( point )
    ctx_ctl = ctx_ctl->GetConstantContext(point+1);

RECOVER
  ctx_ctl = NULL;
ENDSEQ
  return(ctx_ctl);
}

/******************************************************************************/
/**
\brief  GetContextType - Returns CTXT_Control



\return ctxtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Control :: GetContextType ( )
{

  return ( CTXT_Control );

}

/******************************************************************************/
/**
\brief  GetControlContext - Get context for a control by Name

        The  function searches  for a  control (button,  field or constant) with
        the  given  name  (control_name).  When not found, the function searches
        for  the element using the control name.  If a Null pointer is passed as
        control name, the function returns the context of the current control. 
        The  control name may contain a  path to the control, including starting
        points(s) for higher context levels(s). 
        The  context  of  the  current  control  is  returned, when passing NULL
        instead  of control name.  Do not pass  an empty string (""), since this
        interpreted as valid control name.

\return ctx_ctl - 

\param  control_name - Control name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlContext"

CTX_Control *CTX_Control :: GetControlContext (char *control_name )
{
  char               *wstring = NULL;
  char               *point   = NULL;
  TWidgetControl     *sub_control;
  CTX_Control        *ctx_ctl = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( control_name && *control_name == '.' )
  {
    if ( GetHighContext(CTXT_Control) )
      ctx_ctl = ((CTX_Control *)GetHighContext())->GetControlContext(control_name+1);
    LEAVESEQ
  }
  
  if ( !control_name )
  {
    if ( !(sub_control = control->GetCurrentControl()) )
                                                     ERROR
    ctx_ctl = sub_control->GetContext();
  }
  else
  {
    wstring = strdup(control_name);
    if ( point = strchr(wstring,'.') )
      *point = 0;
          
    if ( sub_control = control->GetControl(wstring) )
      ctx_ctl = sub_control->GetContext();
  }
  if ( !ctx_ctl )                                   OADIERR(7)

  if ( point )
  {
    *point = '.';
    ctx_ctl = ctx_ctl->GetControlContext(point+1);
  }

RECOVER
  ctx_ctl = NULL;
ENDSEQ
  if ( wstring )
    free(wstring);
  return(ctx_ctl);
}

/******************************************************************************/
/**
\brief  GetCurrentPropertyHandle - Get current property handle

        The  function  usually  returns  the same value as the GetPropertyHandle
        function.  When  applying  the  function  on a tree view, it returns the
        property  handle for the currently selected  region or for the region to
        be  filled. In  case of  a list  box the function returns the handle for
        the  region to be filled  or for the selected  region, when the list has
        regions,  otherwise the  property handle  for the  list control (same as
        GetPropertyHandle()).

\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentPropertyHandle"

PropertyHandle *CTX_Control :: GetCurrentPropertyHandle ( )
{

  return ( this ? control->GetCurrentPropertyHandle() : NULL );


}

/******************************************************************************/
/**
\brief  GetCurrentRegionID - Get current region identifier

        Within  a list  view or  tree, each  region has a unique identifier. The
        function  returns  the  identifier  for  the  region, whcih contains the
        currently selected item of the list.

\return region_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentRegionID"

int32 CTX_Control :: GetCurrentRegionID ( )
{

  return ( this && control ? control->GetCurrentRegionID() : NULL );

}

/******************************************************************************/
/**
\brief  GetData - Provide control value



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

PropertyHandle *CTX_Control :: GetData ( )
{

  return ( control->GetData() );

}

/******************************************************************************/
/**
\brief  GetDisplayLevel - 



\return dlev - Display level

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDisplayLevel"

int16 CTX_Control :: GetDisplayLevel ( )
{

  return( this ? control->GetDisplayLevel() : UNDEF);

}

/******************************************************************************/
/**
\brief  GetDropIndex - Get drop index in list

        For  list controls the function returns  the index position for the last
        drop  event.  The  index  points  to  the  line position, where the drag
        buffer  will  be  inserted.  When  index  is  larger  than the number of
        entries in the list, the drag content is appended to the list.

\return index - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropIndex"

int32 CTX_Control :: GetDropIndex ( )
{

  return ( control->GetDropIndex() );

}

/******************************************************************************/
/**
\brief  GetDropPosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropPosition"

DPoint CTX_Control :: GetDropPosition ( )
{

  return ( control->GetDropPoint() );

}

/******************************************************************************/
/**
\brief  GetDropPropertyHandle - Get property handle from drag and drop object

        The  function  can  be  called  in  the  DoBeforeDrop handler to get the
        property handle, which helds the instance for the drag action.

\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropPropertyHandle"

PropertyHandle *CTX_Control :: GetDropPropertyHandle ( )
{

  return ( control->GetDropPropertyHandle() );

}

/******************************************************************************/
/**
\brief  GetDropText - Get text from drag and drop object

        The  function can be  called in the  DoBeforeDrop and in the DoAfterDrag
        handler  to  get  the  text  that  is  going  to be dropped. The text is
        returned as 0-terminated string.

\return string - 0-terminated string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDropText"

char *CTX_Control :: GetDropText ( )
{

  return ( control->GetDropText() );

}

/******************************************************************************/
/**
\brief  GetFieldContext - Get context by field or button name

        The  function searches  for a  subordinated field  with the passed name.
        When  a  name  has  been  used  several  times, the function returns the
        context for the first field with the given name.
        The  name  may  contain  a  path  to  the  control,  also  with starting
        points(s) for higher context levels(s).

\return ctx_ctl - 

\param  field_name - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldContext"

CTX_Control *CTX_Control :: GetFieldContext (char *field_name )
{
  char               *wstring = NULL;
  char               *point   = NULL;
  TWidgetControl     *sub_control;
  CTX_Control        *ctx_ctl = NULL;
BEGINSEQ
  if ( field_name && *field_name == '.' )
  {
    if ( GetHighContext(CTXT_Control) )
      ctx_ctl = ((CTX_Control *)GetHighContext())->GetFieldContext(field_name+1);
    LEAVESEQ
  }
  
  if ( !field_name )
  {
    if ( sub_control = control->GetCurrentControl() )
      ctx_ctl = sub_control->GetContext();
  }
  else
  {
    wstring = strdup(field_name);
    if ( point = strchr(wstring,'.') )
      *point = 0;
          
    if ( sub_control = control->GetField(wstring) )
      ctx_ctl = sub_control->GetContext();
  }
  if ( !ctx_ctl )                                   OADIERR(7)

  if ( point )
    ctx_ctl = ctx_ctl->GetFieldContext(point+1);

RECOVER
  ctx_ctl = NULL;
ENDSEQ
  if ( wstring )
    free(wstring);
  return(ctx_ctl);
}

/******************************************************************************/
/**
\brief  GetFilePath - 



\return string - 0-terminated string

\param  title - 
\param  cpath - 
\param  filter - 
\param  write_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFilePath"

char *CTX_Control :: GetFilePath (char *title, char *cpath, char *filter, logical write_opt )
{

  return ( ::GetFilePath(title,cpath,filter,write_opt,control->ControlWidgetParent()) );

}

/******************************************************************************/
/**
\brief  GetFont - Get Control Font

        The  function returns the font currently activated for the control. This
        function  should be called before changing the font in order to keep the
        current setings (e.g. the font type when changing the font color).

\return dDFont - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

DFont CTX_Control :: GetFont ( )
{
  DFont          empty;
  return(control ? control->GetFont() : empty );

}

/******************************************************************************/
/**
\brief  GetKey - Get selected value from collection control



\return skey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *CTX_Control :: GetKey ( )
{

  return ( (char *)control->GetKey() );

}

/******************************************************************************/
/**
\brief  GetLineFont - Get List Item Font

        The  function returns the font currently  activated for the current list
        line  or  list  cell.  When  the  list  supports multi column lines, the
        coulumn  numer must be  passed. When passing  AUTO, the function returns
        the  font for the first  column that is associated  with a font. When no
        font is set, the function returns an empty font. 
        This  function  should  be  called  before updating the font in order to
        keep  the  current  setings  (e.g.  the font type when changing the font
        color).

\return dDFont - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLineFont"

DFont CTX_Control :: GetLineFont (int32 column )
{
  DFont          empty;
  return(control ? control->GetLineFont(column) : empty );

}

/******************************************************************************/
/**
\brief  GetMousePosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMousePosition"

DPoint CTX_Control :: GetMousePosition ( )
{

  return ( control->GetMousePosition() );

}

/******************************************************************************/
/**
\brief  GetPosition - 



\return position - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

DPoint CTX_Control :: GetPosition ( )
{
  DPoint                  position;
  return ( this && control 
           ? control->GetPosition()
           : position );

}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CTX_Control :: GetPropertyHandle ( )
{
  PropertyHandle     *ph;
  ph = control->GetDSPropertyHandle();
  return ( ph && ph->IsValid() ? ph : NULL );

}

/******************************************************************************/
/**
\brief  GetResourceName - Get the name of the control resource

        The  function returns the name, the control has been created with. If no
        name is set for the control, the function returns an empty string.

\return resname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceName"

char *CTX_Control :: GetResourceName ( )
{

  return ( control->GetControlName() );

}

/******************************************************************************/
/**
\brief  GetSize - Get control size

        The function returns the size of the outer control area.

\return size - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

DSize CTX_Control :: GetSize ( )
{

  return ( this ? control->GetSize() : DSize() );

}

/******************************************************************************/
/**
\brief  GetString - 



\return string - 0-terminated string

\param  title - 
\param  label - 
\param  textptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *CTX_Control :: GetString (char *title, char *label, char *textptr )
{

  return ( ::GetString(title,label,textptr,control->ControlWidgetParent()) );

}

/******************************************************************************/
/**
\brief  GetSubRegionCount - Get sub-region count

        The  function returns  the number  of subregions  defined for the region
        with  the  passed  region-id.  In  order  to  retreive  the  number  of 
        sub-regions for the current region you may pass AUTO as region-id.
        The number of top regions is returned when passing 0 as region-id.

\return count - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int32 CTX_Control :: GetSubRegionCount (int32 region_id )
{

  return ( this && control ? control->GetSubRegionCount(region_id) : YES );

}

/******************************************************************************/
/**
\brief  HasFocus - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFocus"

logical CTX_Control :: HasFocus ( )
{

  return ( this ? control->HasFocus() : NO );

}

/******************************************************************************/
/**
\brief  IsActionDisabled - Is action item disabled

        The  function returns, whether  action items (as  buttons or menu items)
        for  an  action  are  disabled  or  not.  Disabled actions are displayed
        differently and cannot be executed.

\return cond - 

\param  actnames - Action name
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionDisabled"

logical CTX_Control :: IsActionDisabled (char *actnames, char *act_id )
{

  return ( this ? control->IsActionDisabled(actnames,act_id) : NO );

}

/******************************************************************************/
/**
\brief  IsActionToggled - Is action toggled

        The  function returns, wether  the action is  toggled or not. The toggle
        mode  has  no  influence  on  the  execution of the action, but when the
        action  is associated with visible action  items, those are displayed as
        toggled (menu items as checked and buttons as pressed).

\return cond - 

\param  actnames - Action name
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionToggled"

logical CTX_Control :: IsActionToggled (char *actnames, char *act_id )
{

  return ( this ? control->IsActionToggled(actnames,act_id) : NO );

}

/******************************************************************************/
/**
\brief  IsActionVisible - Is action item visible

        The  function returns,  wether action  items (as  buttons or menu items)
        for  an action are visible or not.  Visibility does not influence on the
        execution of the action.

\return cond - 

\param  actnames - Action name
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionVisible"

logical CTX_Control :: IsActionVisible (char *actnames, char *act_id )
{

  return ( this ? control->IsActionVisible(actnames,act_id) : NO );

}

/******************************************************************************/
/**
\brief  IsLocalDrop - Is drop event local

        A  drop  event  is  considered  as  local, when the drop source and drop
        target  are identical, i.e. the drag  and drop action takes place within
        the control.

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalDrop"

logical CTX_Control :: IsLocalDrop ( )
{

  return ( control->IsLocalDrop() );

}

/******************************************************************************/
/**
\brief  KeyEvent - Key event handler

        The  key event  handler is  called for  any key pressed for the control.
        The  key event handler returns the result  of key handling, when the key
        was  handles. When the  key was not  handled, the function should return
        an  error (YES) or AUTO to indicate,  that no action has been performed.
        Following successor actins are performed for different return codes:
        AUTO  (no action): The system tries to locate other actions for the same
        control associated with the event.
        YES (error): The system passes the event to the parent control.
        NO (ok): The key event is not handled further on. 
        When  the key  pressed should  appear in  the control area, the function
        must  not return NO. When returning NO,  any further action with the key
        pressed is suppressed.

\return rc - 

\param  dkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyEvent"

int32 CTX_Control :: KeyEvent (DKey dkey )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  ReceiveSelectedItem - Get next selected item and reset

        The  function provides  the next  selected item  in a multi-selection or
        check  list/tree in the  current property handle.  The selection for the
        item  is  reset.  For  accessing  the  instance  the  represented by the
        selected   item   you   may   use   GetCurrentPropertyHandle(), which is
        positioned  to  the  selected  list  entry. In multiple region lists the
        property   handle   may   change   for   each   selected   item.   Thus,
        GetCurrentPropertyHandle() should be called after each function call.
        The  function returns true, when an error  has been detected or when the
        end  of the list has been reached. Otherwise, the function returns falss
        (NO).
        When  applying the  function on  simple fields,  the function returns an
        error  (true). When applying the function on a single-selection list, it
        returns one item, if there is an item selected in the list.

\return prop_hdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReceiveSelectedItem"

PropertyHandle *CTX_Control :: ReceiveSelectedItem ( )
{

  return ( this && control ? control->ReceiveSelectedItem() : NULL );

}

/******************************************************************************/
/**
\brief  RefreshRegion - 




\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshRegion"

void CTX_Control :: RefreshRegion (int32 region_id )
{

  if ( this && control )
    control->RefreshRegion(region_id);

}

/******************************************************************************/
/**
\brief  RemoveButton - Remove button

        The  function removes a  button from the  visible control. The button is
        not removed from the resource.

\return term - 

\param  name_s - Name of resoure
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveButton"

logical CTX_Control :: RemoveButton (char *name_s )
{

  return( control->RemoveButton(name_s) );

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

logical CTX_Control :: RemoveColumn (int32 region_id, int32 column_id )
{

  return ( this && control ? control->RemoveColumn(region_id,column_id) : YES );

}

/******************************************************************************/
/**
\brief  RemoveConstant - Remove constant

        The  function removes a constant from  the visible control. The constant
        is not removed from the resource.

\return term - 

\param  name_s - Name of resoure
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveConstant"

logical CTX_Control :: RemoveConstant (char *name_s )
{

  return( control->RemoveConstant(name_s) );

}

/******************************************************************************/
/**
\brief  RemoveField - Remove Field

        The  function removes a field from the visible control. The field is not
        removed from the resource.

\return term - 

\param  name_s - Name of resoure
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveField"

logical CTX_Control :: RemoveField (char *name_s )
{

  return( control->RemoveField(name_s) );

}

/******************************************************************************/
/**
\brief  ReplaceSubRegions - Replace sub-regions

        For  a  region  in  a  list  view or tree you may dynamically create new
        sub-regions.  Subrergions can  be inherited  from the region referred to
        by  region_id.  This  allows  re-using  region  definitions  as  well as
        defining recursive tree layouts.
        When  the  current  region  referred  to  by parent_id does already have
        sub-regions,  those will be  removed as well  as columns defined for the
        current region.
        Note,  that  the  region  list  is inherited from the referenced region.
        Adding  new sub-regions wii affect both, the current region but also the
        original  region.  Column  lists  are  inherited  as  well. Thus, adding
        columns  will  affect  also  the  original  region  and  all  inheriting
        regions.

\return region_id - 

\param  parent_id - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSubRegions"

int32 CTX_Control :: ReplaceSubRegions (int32 parent_id, int32 region_id )
{

BEGINSEQ
  if ( !this || !control )                           ERROR
  if ( parent_id == region_id )                      LEAVESEQ
  
  region_id = control->ReplaceSubRegions(parent_id,region_id);

RECOVER
  region_id = UNDEF;
ENDSEQ
  return(region_id);
}

/******************************************************************************/
/**
\brief  ResetControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetControl"

void CTX_Control :: ResetControl ( )
{

  control = NULL;

}

/******************************************************************************/
/**
\brief  ResetRegion - Remove region

        The  function  allows  removing  a  region from a tree or list view. The
        region  to  be  removed  must  be  identified  by its parend and its own
        identifier.  In order to remove a top  region, 0 is passed as parent id.
        Removing  all sub regions for a region  can be achieved by passing 0 for
        the region_id (region to be removed).

\return term - 

\param  parent_id - 
\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRegion"

logical CTX_Control :: ResetRegion (int32 parent_id, int32 region_id, logical reset_columns )
{

  return ( this && control ? control->ResetRegion(parent_id,region_id,reset_columns) : YES );

}

/******************************************************************************/
/**
\brief  SearchKey - Select key value in collection control



\return term - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchKey"

logical CTX_Control :: SearchKey (char *skey )
{

  return ( control->SearchKey(skey) );

}

/******************************************************************************/
/**
\brief  SetActionDisabled - Set action disable state

        By  default, control  actions are  enabled. The function allows changing
        the  disabled  state  for  the  action  items  according  to the passsed
        option.  Disabling the action for the control will change the appearence
        for  all  associated  action  items  (menu  items, buttons) to disabled.
        Enabling changes the associated action items to enabled.
        Disabled  actions cannot be executed in the context of the control, i.e.
        even  an explicite ExecuteAction() call will be refused, when the action
        is disabled. 
        The  function will not change the appearance for the control, unless the
        control  itself is an action item associated with the action, which is a
        very rare case.

\return cond - 

\param  actnames - Action name
\param  disable - 
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionDisabled"

logical CTX_Control :: SetActionDisabled (char *actnames, logical disable, char *act_id )
{

  return ( this ? control->SetActionDisabled(actnames,act_id,disable) : NO );

}

/******************************************************************************/
/**
\brief  SetActionToggled - Set action toggle state

        By  default,  actions  are  marked  as  not toggled. The function allows
        changing  the toggle state for the related action items according to the
        passsed  option. Toggeling the action will change the appearence for all
        associated  action  items  (menu  items  will  be  checked, buttons will
        appear  as pressed) to toggled. Untoggling changes the associated action
        items to "not checked" or "not pressed".
        Regardless on the toggle mode, actions can be executed. 
        The  function will not change the appearance for the control, unless the
        control  itself is an action item associated with the action, which is a
        very rare case.

\return cond - 

\param  actnames - Action name
\param  enable - 
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionToggled"

logical CTX_Control :: SetActionToggled (char *actnames, logical enable, char *act_id )
{

  return ( this ? control->SetActionToggled(actnames,act_id,enable) : NO );

}

/******************************************************************************/
/**
\brief  SetActionVisible - Change visibility of action items

        By  default, action items shown for the action are visible. The function
        allows  changing the  visibility for  the action  items according to the
        passsed  option. Disable visibility (hide) all action items (menu items,
        buttons)  become invisible. Enable visibility will show the action items
        again. Invisible actions can still be executed.
        The  function will not change the appearance for the control, unless the
        control  itself is an action item associated with the action, which is a
        very rare case.

\return cond - 

\param  actnames - Action name
\param  enable - 
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionVisible"

logical CTX_Control :: SetActionVisible (char *actnames, logical enable, char *act_id )
{

  return ( this ? control->SetActionVisible(actnames,act_id,enable) : NO );

}

/******************************************************************************/
/**
\brief  SetBackgroundColor - Set background color

        The  function will change  the background color  for the current control
        or  window. The function cannot be used for changing the line layout for
        a certain line in a list.

\return term - 

\param  color - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBackgroundColor"

logical CTX_Control :: SetBackgroundColor (DColor &color )
{

  return(control ? control->SetBackgroundColor(color) : YES);

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

logical CTX_Control :: SetColumnFont (DFont &font, int32 region_id, int32 column_id )
{

  return(control ? control->SetColumnFont(&font,region_id,column_id) : YES);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - Font name
\param  region_id - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetColumnFont"

logical CTX_Control :: SetColumnFont (char *font_name, int32 region_id, int32 column_id )
{

  return(control ? control->SetColumnFont(font_name,region_id,column_id) : YES);

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

logical CTX_Control :: SetColumnPixmap (DPixmap &pixmap, int32 region_id, int32 column_id )
{

  return(control ? control->SetColumnPixmap(&pixmap,region_id,column_id) : YES);

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

logical CTX_Control :: SetColumnPixmap (char *pixmap_name, int32 region_id, int32 column_id )
{

  return(control ? control->SetColumnPixmap(pixmap_name,region_id,column_id) : YES);

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

logical CTX_Control :: SetData ( )
{

  return ( control->SetData() );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical CTX_Control :: SetData (PropertyHandle *prophdl )
{

  return ( control->SetData(prophdl) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  string - 0-terminated string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical CTX_Control :: SetData (char *string )
{

  return ( control->SetData(string) );

}

/******************************************************************************/
/**
\brief  SetDatabaseHandle - Set database handle for data source

        Usually,  datasources refer  to the  database, which  is defined for the
        application.  You  may,  however,  refer  to alternative databases in an
        application  by setting  the data  source explicitly to another database
        handle.  Then, all subsequent data sources  refer to the Databse defined
        in this parent data source.

\return term - 

\param  dbhandle - Database Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDatabaseHandle"

logical CTX_Control :: SetDatabaseHandle (DatabaseHandle dbhandle )
{

  return(this ? control->SetDatabaseHandle(dbhandle) : YES);

}

/******************************************************************************/
/**
\brief  SetDisabled - Disable or enable control

        The  function  disables  or  enables  the data widget, if possible. When
        being  disabled, the widget does not allow entering data and actions are
        disabled.  Passing  true  (YES)  will  disable the widget. Passing false
        (NO) will enable the widget.


\param  disabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisabled"

void CTX_Control :: SetDisabled (logical disabled )
{

  if ( this && control )
    control->SetDisabled(disabled);

}

/******************************************************************************/
/**
\brief  SetDisplayLevel - Change the display level

        For  tab controls or windows with  level controls (fields with a display
        level)  only  fields  for  the  selected  display  level are schown. The
        function allows changing the display level.

\return term - 
-------------------------------------------------------------------------------
\brief  i00 - Change display level by number

        Changing  the display  level by  the number  passed to the function will
        switch  the display  level (or  tab) to  the pased number. Passing 0 wil
        result  in displaying standard field, only  (fields with display level 0
        are always visible).

\param  dlev - Display level
\param  fillopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical CTX_Control :: SetDisplayLevel (int16 dlev, logical fillopt )
{

  return( this ? control->SetDisplayLevel(dlev) : YES);

}

/******************************************************************************/
/**
\brief  i01 - Changing display level by type

        Changing  display level by  name allows switching  to a level associated
        with  the type name passed to the  function. This feature is mainly used
        with  dynamic  control  stacks.  The  type name passed is interpreted as
        class  name for the GUI class, from wich the tab-control for the dynamic
        control stack is do be loaded.

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical CTX_Control :: SetDisplayLevel (char *typenames )
{

  return( this ? control->SetDisplayLevel(typenames) : YES);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical CTX_Control :: SetDisplayLevel (PropertyHandle *prophdl )
{

  return( this ? control->SetDisplayLevel(prophdl) : YES);

}

/******************************************************************************/
/**
\brief  SetFilter - Activate instance filter

        Instance  filters  can  be  activated  by  setting a filter condition or
        activating  filtering  explicitly.  When  filters are activated, filling
        controls with data runs slowlier than without activated filters.

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - Using context filter

        Context  filter  are  implemented  by  overloading  the  DoBeforeDataSet
        handler  or implementing  an appropriate  action. for activating context
        filter, SetFilter(YES) should be called in the DoAfterOpen() handler.

\param  enable - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical CTX_Control :: SetFilter (logical enable )
{

  return(control ? control->SetFilter(NULL,enable) : YES);

}

/******************************************************************************/
/**
\brief  i01 - Filter by expression

        An  expression can be set for selecting instances from a collection in a
        property  handle.  The  function  can  also  be used for deactivating an
        expression  previously set for  the filter by  passing a NULL pointer as
        expression.  When  deactivating  an  expression,  the  filter feature is
        disabled. To re-activate context filter, you must call SetFilter(YES).

\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical CTX_Control :: SetFilter (char *expression )
{
  logical        enable = expression ? YES : NO;
  return(control ? control->SetFilter(expression,enable) : YES);

}

/******************************************************************************/
/**
\brief  SetFocus - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFocus"

logical CTX_Control :: SetFocus ( )
{

  return(control ? control->SetFocus() : YES);

}

/******************************************************************************/
/**
\brief  SetFont - Set font

        The  function will  change the  font for  the current control or window.
        Changing  the font includes  changing the text  and background color and
        the  character  layout.  The  font  definition  must  be passed as DFont
        object, which is owned by the application. 
        You  cannot  use  the  function  for changing the current line font. Use
        ChangeLineFont()  instead. When  passing a  font name  instead of a font
        definition,  the font name must refer to  a defined font in the resource
        database.

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

logical CTX_Control :: SetFont (DFont &font )
{

  return(control ? control->SetFont(&font) : YES);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - Font name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

logical CTX_Control :: SetFont (char *font_name )
{

  return(control ? control->SetFont(font_name) : YES);

}

/******************************************************************************/
/**
\brief  SetHidden - Hide or show control

        The  functin allows hiding or showing  a control. Passing true (YES) wil
        hide the control. Passing false (NO) will show the control again.


\param  hidden - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHidden"

void CTX_Control :: SetHidden (logical hidden )
{

  if ( this && control )
    control->SetHidden(hidden);

}

/******************************************************************************/
/**
\brief  SetLineFont - Set font for current line

        The  function  is  setting  the  font  (character  style, text color and
        background  color)  for  the  currently selected line. The function will
        set  the font for the column in the line referred to as 'column_id'. The
        first  column has the number 0. When  passing -1 (AUTO), the passed font
        applies to all available columns.
        When  passing a  font name  instead of  a font definition, the font name
        must refer to a defined font in the resource database.
        To  display  the  line  properly,  the  function should be called in the
        DEV_BeforeDataSet event.

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font - 
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical CTX_Control :: SetLineFont (DFont &font, int32 column_id )
{

  return(control ? control->SetLineFont(&font,column_id) : YES);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - Font name
\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical CTX_Control :: SetLineFont (char *font_name, int32 column_id )
{

  return(control ? control->SetLineFont(font_name,column_id) : YES);

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

logical CTX_Control :: SetLinePixmap (DPixmap &pixmap, int32 column_id )
{

  return(control ? control->SetLinePixmap(&pixmap,column_id) : YES);

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

logical CTX_Control :: SetLinePixmap (char *pixmap_name, int32 column_id )
{

  return(control ? control->SetLinePixmap(pixmap_name,column_id) : YES);

}

/******************************************************************************/
/**
\brief  SetPosition - Set line position in control

        The  function positions the selected line or entry of the control to the
        position  passed  as  parameter.  The  function  is  used  to  position 
        (hilighting) the line in a multi-line edit or list.


\param  position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void CTX_Control :: SetPosition (DPoint position )
{

  if ( this && control )
    control->SetPosition(position);

}

/******************************************************************************/
/**
\brief  SetPropertyHandle - 



\return term - 

\param  prophdl - 
\param  auto_select - Automatic selection of valid object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical CTX_Control :: SetPropertyHandle (PropertyHandle *prophdl, logical auto_select )
{

  return(this ? control->SetPropertyHandle(prophdl,auto_select) : YES);

}

/******************************************************************************/
/**
\brief  SetReadOnly - Set Control to read-only state

        The  control is  set into  the read-only  state, which shows the control
        with  a disabled lable  and which does  not allow entering data into the
        control.  Context  menu  and  actions  for the control are still active.
        Passinf  true  (YES)  to  the  function will enable the read-only state,
        passing false (NO) will disable the read-only state.


\param  read_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void CTX_Control :: SetReadOnly (logical read_only )
{

  if ( this && control )
    control->SetReadOnly(read_only);

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

logical CTX_Control :: SetRegionFont (DFont &font, int32 region_id )
{

  return(control ? control->SetRegionFont(&font,region_id) : YES);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  font_name - Font name
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRegionFont"

logical CTX_Control :: SetRegionFont (char *font_name, int32 region_id )
{

  return(control ? control->SetRegionFont(font_name,region_id) : YES);

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

logical CTX_Control :: SetRegionPixmap (DPixmap &pixmap, int32 region_id )
{

  return(control ? control->SetRegionPixmap(&pixmap,region_id) : YES);

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

logical CTX_Control :: SetRegionPixmap (char *pixmap_name, int32 region_id )
{

  return(control ? control->SetRegionPixmap(pixmap_name,region_id) : YES);

}

/******************************************************************************/
/**
\brief  SetSelection - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  start_pos - 
\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

void CTX_Control :: SetSelection (int32 start_pos, int32 length )
{

  if ( this && control )
    control->SetSelection(start_pos,length);

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

void CTX_Control :: SetSelection (DPoint start_point, DPoint end_point )
{

  if ( this && control )
    control->SetSelection(start_point,end_point);

}

/******************************************************************************/
/**
\brief  SetSize - Set control size

        The  function  changes  the  size  of  the  control to the passed value.
        Controls  size  can  be  adapted  automatically  when changing the upper
        window/control  size by passing vertical  and/or horizontal grow (vgroe,
        hgrow).

\return term - 

\param  size - 
\param  hgrow - Horizontal resize mode
\param  vgrow - Vertical resize mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

logical CTX_Control :: SetSize (DSize size, logical hgrow, logical vgrow )
{

  return ( this ? control->SetSize(size,hgrow,vgrow) : YES );

}

/******************************************************************************/
/**
\brief  SetTextColor - Set text color

        The  function  will  change  the  text  color for the current control or
        window.  The function cannot be used for  changing the line layout for a
        certain line in a list.

\return term - 

\param  color - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

logical CTX_Control :: SetTextColor (DColor &color )
{

  return(control ? control->SetTextColor(color) : YES);

}

/******************************************************************************/
/**
\brief  SetTitle - Set title or lable

        The  function sets the title or label  for a window o0r control. When no
        title or label is defined the function has no effect.

\return term - 

\param  text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTitle"

logical CTX_Control :: SetTitle (char *text )
{

  return(control ? control->SetTitle(text) : YES);

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

logical CTX_Control :: SetVirtualType (PropertyHandle *prophdl )
{

  return(this ? control->SetVirtualType(prophdl) : YES);

}

/******************************************************************************/
/**
\brief  type - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVirtualType"

logical CTX_Control :: SetVirtualType (char *scoped_name )
{

  return(this ? control->SetVirtualType(scoped_name) : YES);

}

/******************************************************************************/
/**
\brief  SetZoomOutControl - Re-define Zoom-out control

        When  calling the zoom-out  action for multi-line  text edit fields, the
        next  higher  window  context  is  used  as  zoom-out frame. This is not
        sufficient in many cases and can be reset by this function.
        The  context passed refers to the context, which will act as parent (and
        frame) for the zoom-out window.

\return term - 

\param  ctx_gui - Pointer to GUI resource context class instance
\param  auto_zoom - Automatically zoom-in control
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetZoomOutControl"

logical CTX_Control :: SetZoomOutControl (CTX_GUIBase *ctx_gui, char auto_zoom )
{

  return(   control && ctx_gui 
          ? control->SetZoomOutWidget(ctx_gui->get_control(),auto_zoom) 
          : YES);

}

/******************************************************************************/
/**
\brief  UpdateTreeLayout - 



\return region_id - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTreeLayout"

int32 CTX_Control :: UpdateTreeLayout (int32 region_id )
{

  return ( this && control ? control->UpdateTreeLayout(region_id) : YES );

}

/******************************************************************************/
/**
\brief  ~CTX_Control - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Control"

     CTX_Control :: ~CTX_Control ( )
{



}


