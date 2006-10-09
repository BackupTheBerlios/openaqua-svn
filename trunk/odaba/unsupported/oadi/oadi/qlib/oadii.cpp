/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    oadii

\brief    


\date     $Date: 2006/07/29 13:43:50,92 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "oadii"

#include  <poadi.h>
#include  <cmacros.h>
#include  <iigui.h>
#include  <sCTX_Control.hpp>
#include  <sCTX_GUIBase.hpp>
#include  <sOADKFactory.hpp>
#include  <sOButton.hpp>
#include  <sOButtonControl.hpp>
#include  <sODataSource.hpp>
#include  <sOElementStyle.hpp>
#include  <sOField.hpp>
#include  <sOFieldControl.hpp>
#include  <sOWinAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTField.hpp>
#include  <sTProjectManager.hpp>
#include  <sTPushButton.hpp>
#include  <sTWidgetControl.hpp>

#include  <ioadii.h>

/******************************************************************************/
/**
\brief  CreateButton - 



\return button - 

\param  button_ph - 
\param  parent_field - 
\param  position - 
\param  resource_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateButton"

TWidgetControl *__cdecl CreateButton (PropertyHandle *button_ph, TWidgetControl *parent_field, DPoint position, int resource_id )
{
  TWidgetControl           *button = NULL;
  TControl                 *tc;
  OButton                  *bu;
BEGINSEQ
  if ( !(bu = CACHE_READ(button_ph,NULL,OButton)) )   ERROR
  if ( position != DPoint(0,0) )
    bu->set_position(position);
  
// Open Control
  tc = bu->Open(parent_field,YES);

  button = OI_CAST(TWidgetControl,tc);
RECOVER
  button = NULL;
ENDSEQ
  return(button);
}

/******************************************************************************/
/**
\brief  CreateConstant - 



\return button - 

\param  constant_ph - 
\param  parent_field - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateConstant"

TWidgetControl *__cdecl CreateConstant (PropertyHandle *constant_ph, TWidgetControl *parent_field )
{
  TWidgetControl     *constant = NULL;
// kommt später
  return(constant);
}

/******************************************************************************/
/**
\brief  CreateField - 



\return control - 

\param  field_ph - 
\param  parent_field - 
\param  position - 
\param  design_mode - 
\param  resource_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField"

TWidgetControl *__cdecl CreateField (PropertyHandle *field_ph, TWidgetControl *parent_field, DPoint position, logical design_mode, int resource_id )
{
  TWidgetControl           *control = NULL;
  TControl                 *tc;
  OField                   *fi;
BEGINSEQ
  if ( !(fi = CACHE_READ(field_ph,NULL,OField)) )    ERROR
  if ( position != DPoint(0,0) )
    fi->set_position(position);
  
  if ( resource_id != AUTO )
    fi->set_res_id(resource_id);

  if ( design_mode )
    fi->ResetDataSource();
  tc = fi->Open(parent_field,YES);
  control = OI_CAST(TWidgetControl,tc);
RECOVER
  control = NULL;
ENDSEQ
  return(control);
}

/******************************************************************************/
/**
\brief  CreateField_intern - 



\return control - 

\param  name - 
\param  control_ph - 
\param  parent_field - 
\param  dsize - 
\param  position - 
\param  dsp_level - 
\param  as_collection - 
\param  resource_id - 
\param  pODataSource - 
\param  active_f - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField_intern"

TWidgetControl *__cdecl CreateField_intern (char *name, PropertyHandle *control_ph, TWidgetControl *parent_field, DSize dsize, DPoint position, int16 dsp_level, logical as_collection, int resource_id, ODataSource *pODataSource, logical active_f )
{
  TControl                 *tc;
  TWidgetControl           *control = NULL;
  OField                   *fi;
BEGINSEQ
// Read Control-Info 
  fi = ADKFACTORY(NULL,OField);
  if ( fi->Read_intern(control_ph) )               ERROR
  
  if ( dsize != DSize(0,0) )
    fi->set_size(dsize);
  if ( position != DPoint(0,0) )
    fi->set_position(position);
  fi->get_align().SetGrow();
  fi->set_accept_drop(YES);
  
  fi->set_name(name);
  fi->get_dataSource().set_referenceType(DRT_UserDefined);
  fi->get_dataSource().set_isCollection(as_collection);
  fi->SetDisplayLevel(dsp_level);
  
  if ( resource_id != AUTO )
    fi->set_res_id(resource_id);
    
  if ( pODataSource )
    fi->get_dataSource() = *pODataSource;
    
  tc = fi->Open(parent_field,active_f);
  control = OI_CAST(TWidgetControl,tc);
RECOVER
  control = NULL;
ENDSEQ
  return(control);
}

/******************************************************************************/
/**
\brief  CreateInputHelp - 



\return control - 

\param  class_names - 
\param  ctl_names - 
\param  parent_field - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInputHelp"

TWidgetControl *__cdecl CreateInputHelp (char *class_names, char *ctl_names, TWidgetControl *parent_field )
{
  PropertyHandle   class_names_ph(class_names);
  PropertyHandle   ctl_names_ph(ctl_names);
  PropertyHandle  *control_ph = NULL;
  TWidgetControl  *control    = NULL;
BEGINSEQ
  PropertyHandle class_ph(TProjectManager::TPM->UCB()->sdbures->dbhandle,"ADK_Class",PI_Read);

  control_ph   = class_ph.GPH("controls");

  if ( !class_ph.Get(class_names_ph) )               OADIERR(100)
  if ( !control_ph->Get(ctl_names_ph) )              OADIERR(101)
  
  if ( !(control = CreateField_intern("InputHelp",control_ph,parent_field,
                                      DSize(),DPoint(),0,YES,AUTO,NULL,YES)) )
                                                     ERROR

RECOVER
  control = NULL;
ENDSEQ
  return(control);
}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return executed - How was function exetuted

\param  act_names - 
\param  vActionType - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

char __cdecl ExecuteAction (char *act_names, ActionType vActionType, CTX_GUIBase *ctxptr )
{
  OCAU_SimpleAction   *oact     = NULL;
  CTX_Control         *control_ctx = ctxptr->GetControlContext();
  logical              executed = AUTO;
BEGINSEQ
  if ( !(oact = ADKFACTORY(NULL,OCAU_SimpleAction)) )
                                                     ERROR
  oact->SetAction(act_names,vActionType);
  oact->SetCurrentComponent(control_ctx ? control_ctx->get_control() : NULL);
  
  executed = oact->Execute(ctxptr);

RECOVER
  executed = YES;
ENDSEQ
  delete oact;
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteWindow - 



\return executed - How was function exetuted

\param  class_names - 
\param  win_names - 
\param  as_collection - 
\param  prophdl - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteWindow"

char __cdecl ExecuteWindow (char *class_names, char *win_names, logical as_collection, PropertyHandle *prophdl, CTX_GUIBase *ctxptr )
{
  OWinAction      *owact     = NULL;
  CTX_Control     *control_ctx = ctxptr->GetControlContext();
  char             executed  = AUTO;
BEGINSEQ
  if ( !(owact = ADKFACTORY(NULL,OWinAction)) )
                                                    ERROR
  
  owact->SetProperties(class_names,win_names,as_collection,prophdl,ctxptr);

  executed = owact->Execute(control_ctx);

RECOVER
  executed = AUTO;
ENDSEQ
  delete owact;
  return(executed);
}

/******************************************************************************/
/**
\brief  FlushGUIEvents - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushGUIEvents"

void __cdecl FlushGUIEvents ( )
{

  FlushEvents();

}

/******************************************************************************/
/**
\brief  GetPropPathType - 



\return prop_type - 

\param  prop_path - 
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropPathType"

ODSPropertyType __cdecl GetPropPathType (char *prop_path, ADK_DataReferenceType ref_type )
{
  ODSPropertyType     prop_type = PT_Self;
BEGINSEQ
  if ( (!prop_path || prop_path[0] == '*') &&
       ref_type != DRT_UserDefined )              LEAVESEQ

  switch ( ref_type )
  {
    case DRT_Extent         : prop_type = PT_Extent;
                              break;
    case DRT_ResExtent      : prop_type = PT_DictionaryExtent;
                              break;
    case DRT_Enumeration    : prop_type = PT_Enumeration;
                              break;
    case DRT_SystemVariable : prop_type = PT_SystemVariable;
                              break;
    case DRT_UserDefined    : prop_type = PT_none;     // 22.7.04 PT_NewCursor;
                              break;
    case DRT_PropertyPath   : if ( !strcmp(prop_path,"__SORTKEY") )
                              {
                                prop_type = PT_Key;
                                break;
                              }
    case DRT_undefined      : prop_type = PT_Property;
                              break;
    case DRT_View           :
    default                 : OADIERR(105);
  }

RECOVER

ENDSEQ
  return(prop_type);
}

/******************************************************************************/
/**
\brief  OADIGlobals - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OADIGlobals"

logical __cdecl OADIGlobals ( )
{
  logical     term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  OADIResources - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OADIResources"

void __cdecl OADIResources ( )
{
  extern        int32 ores_count;
  extern        int32 ores_total;
  extern        int32 bc_count;
  extern        int32 bc_total;
  char          string[31];
  SDBError().TraceMessage("ores count: ",gvtxltoa(ores_count,string,10));
  ores_count = 0;
  SDBError().TraceMessage("ores total: ",gvtxltoa(ores_total,string,10));
  ores_total = 0;
  SDBError().TraceMessage("bc count: ",gvtxltoa(bc_count,string,10));
  bc_count = 0;
  SDBError().TraceMessage("bc total: ",gvtxltoa(bc_total,string,10));
  bc_total = 0;


}

/******************************************************************************/
/**
\brief  SetPointer - 




\param  wait_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPointer"

void __cdecl SetPointer (logical wait_opt )
{

  SetBusy(wait_opt);

}

