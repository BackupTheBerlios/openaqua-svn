/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    oadii

\brief    


\date     $Date: 2006/07/29 13:43:49,18 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   oadii_H
#define   oadii_H

class     CTX_GUIBase;
class     ODataSource;
class     PropertyHandle;
class     TField;
class     TPushButton;
class     TWidgetControl;
#include  <cADK_DataReferenceType.h>
#include  <cActionType.h>
#include  <cODSPropertyType.h>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

OADIImpExp         TWidgetControl *__cdecl CreateButton (PropertyHandle *button_ph, TWidgetControl *parent_field, DPoint position, int resource_id );
OADIImpExp         TWidgetControl *__cdecl CreateConstant (PropertyHandle *constant_ph, TWidgetControl *parent_field );
OADIImpExp         TWidgetControl *__cdecl CreateField (PropertyHandle *field_ph, TWidgetControl *parent_field, DPoint position, logical design_mode, int resource_id );
OADIImpExp         TWidgetControl *__cdecl CreateField_intern (char *name, PropertyHandle *control_ph, TWidgetControl *parent_field, DSize dsize, DPoint position, int16 dsp_level, logical as_collection, int resource_id, ODataSource *pODataSource, logical active_f );
OADIImpExp         TWidgetControl *__cdecl CreateInputHelp (char *class_names, char *ctl_names, TWidgetControl *parent_field );
OADIImpExp         char __cdecl ExecuteAction (char *act_names, ActionType vActionType, CTX_GUIBase *ctxptr );
OADIImpExp         char __cdecl ExecuteWindow (char *class_names, char *win_names, logical as_collection, PropertyHandle *prophdl, CTX_GUIBase *ctxptr );
OADIImpExp         void __cdecl FlushGUIEvents ( );
                   ODSPropertyType __cdecl GetPropPathType (char *prop_path, ADK_DataReferenceType ref_type );
                   logical __cdecl OADIGlobals ( );
OADIImpExp         void __cdecl OADIResources ( );
OADIImpExp         void __cdecl SetPointer (logical wait_opt );

#if defined (__cplusplus)
             }
#endif
#endif
