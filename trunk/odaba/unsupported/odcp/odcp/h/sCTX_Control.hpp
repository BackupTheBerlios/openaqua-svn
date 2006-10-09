/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/08/26 17:08:26,51 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Control_HPP
#define   CTX_Control_HPP

class     CTX_Control;

class     CTX_Control;
class     TWidgetControl;
#include  <cADK_DataReferenceType.h>
#include  <cCTX_Types.h>
#include  <sCTX_GUIBase.hpp>
#include  <sDColor.hpp>
#include  <sDFont.hpp>
#include  <sDKey.hpp>
#include  <sDPixmap.hpp>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
class  CTX_Control :public CTX_GUIBase
{

public     :
public     :                  ODCPImpExp            void AcceptDrops (logical drop_opt );
public     :                  ODCPImpExp            void ActivateControl ( );
public     :                  ODCPImpExp            char *ActiveAction ( );
public     :                  ODCPImpExp            char *ActiveActionItem ( );
public     :                  ODCPImpExp            int32 AddColumn (int32 parent_id, char *prop_path, logical is_collection, char *text, ADK_DataReferenceType ref_type );
public     :                  ODCPImpExp            int32 AddRegion (int32 parent_id, char *prop_path, logical is_collection, char *text, ADK_DataReferenceType ref_type );
public     :                  ODCPImpExp            logical AssociateData (PropertyHandle *source_ph, char *control_name, char *title );
public     :                                        logical BlockEvents (logical block_opt );
public     :                  ODCPImpExp                 CTX_Control ( );
public     :                  ODCPImpExp            CTX_Control *CreateButton (char *name_s, logical design_mode, DPoint position, int resource_id );
public     :                  ODCPImpExp            logical CreateConstant (char *name_s, logical design_mode );
public     :                  ODCPImpExp            CTX_Control *CreateControl (char *name_s, PropertyHandle *control_ph, DSize size, DPoint position, char *data_source, int16 dsp_level, int resource_id );
public     :                  ODCPImpExp            CTX_Control *CreateField (char *name_s, logical design_mode, DPoint position, int resource_id );
public     :                  ODCPImpExp            void DeactivateControl ( );
public     :                  ODCPImpExp            logical FillControl ( );
public     :                  ODCPImpExp            CTX_Control *GetActiveElementContext ( );
public     :                  ODCPImpExp            PropertyHandle *GetBasePropertyHandle ( );
public     :                  ODCPImpExp            CTX_Control *GetButtonContext (char *button_name );
public     :                  ODCPImpExp            PropertyHandle *GetColumnPropertyHandle (int32 column );
public     :                  ODCPImpExp            CTX_Control *GetConstantContext (char *const_name );
public     : virtual          ODCPImpExp            CTX_Types GetContextType ( );
public     :                  ODCPImpExp            CTX_Control *GetControlContext (char *control_name );
public     :                  ODCPImpExp            PropertyHandle *GetCurrentPropertyHandle ( );
public     :                  ODCPImpExp            int32 GetCurrentRegionID ( );
public     :                  ODCPImpExp            PropertyHandle *GetData ( );
public     :                  ODCPImpExp            int16 GetDisplayLevel ( );
public     :                  ODCPImpExp            int32 GetDropIndex ( );
public     :                  ODCPImpExp            DPoint GetDropPosition ( );
public     :                  ODCPImpExp            PropertyHandle *GetDropPropertyHandle ( );
public     :                  ODCPImpExp            char *GetDropText ( );
public     :                  ODCPImpExp            CTX_Control *GetFieldContext (char *field_name );
public     :                  ODCPImpExp            char *GetFilePath (char *title, char *cpath, char *filter=NULL, logical write_opt=YES );
public     :                  ODCPImpExp            DFont GetFont ( );
public     :                  ODCPImpExp            char *GetKey ( );
public     :                  ODCPImpExp            DFont GetLineFont (int32 column );
public     :                  ODCPImpExp            DPoint GetMousePosition ( );
public     :                  ODCPImpExp            DPoint GetPosition ( );
public     : virtual          ODCPImpExp            PropertyHandle *GetPropertyHandle ( );
public     :                  ODCPImpExp            char *GetResourceName ( );
public     :                  ODCPImpExp            DSize GetSize ( );
public     :                  ODCPImpExp            char *GetString (char *title, char *label, char *textptr );
public     :                  ODCPImpExp            int32 GetSubRegionCount (int32 region_id );
public     :                  ODCPImpExp            logical HasFocus ( );
public     :                  ODCPImpExp            logical IsActionDisabled (char *actnames, char *act_id=NULL );
public     :                  ODCPImpExp            logical IsActionToggled (char *actnames, char *act_id=NULL );
public     :                  ODCPImpExp            logical IsActionVisible (char *actnames, char *act_id=NULL );
public     :                  ODCPImpExp            logical IsLocalDrop ( );
public     : virtual          ODCPImpExp            int32 KeyEvent (DKey dkey );
public     :                  ODCPImpExp            PropertyHandle *ReceiveSelectedItem ( );
public     :                  ODCPImpExp            void RefreshRegion (int32 region_id );
public     :                  ODCPImpExp            logical RemoveButton (char *name_s );
public     :                  ODCPImpExp            logical RemoveColumn (int32 region_id, int32 column_id );
public     :                  ODCPImpExp            logical RemoveConstant (char *name_s );
public     :                  ODCPImpExp            logical RemoveField (char *name_s );
public     :                  ODCPImpExp            int32 ReplaceSubRegions (int32 parent_id, int32 region_id );
public     : virtual          ODCPImpExp            void ResetControl ( );
public     :                  ODCPImpExp            logical ResetRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     :                  ODCPImpExp            logical SearchKey (char *skey=NULL );
public     :                  ODCPImpExp            logical SetActionDisabled (char *actnames, logical disable, char *act_id=NULL );
public     :                  ODCPImpExp            logical SetActionToggled (char *actnames, logical enable, char *act_id=NULL );
public     :                  ODCPImpExp            logical SetActionVisible (char *actnames, logical enable, char *act_id=NULL );
public     :                  ODCPImpExp            logical SetBackgroundColor (DColor &color );
public     :                  ODCPImpExp            logical SetColumnFont (DFont &font, int32 region_id, int32 column_id );
public     :                  ODCPImpExp            logical SetColumnFont (char *font_name, int32 region_id, int32 column_id );
public     :                  ODCPImpExp            logical SetColumnPixmap (DPixmap &pixmap, int32 region_id, int32 column_id );
public     :                  ODCPImpExp            logical SetColumnPixmap (char *pixmap_name, int32 region_id, int32 column_id );
public     :                  ODCPImpExp            logical SetData ( );
public     :                  ODCPImpExp            logical SetData (PropertyHandle *prophdl );
public     :                  ODCPImpExp            logical SetData (char *string );
public     :                  ODCPImpExp            logical SetDatabaseHandle (DatabaseHandle dbhandle );
public     :                  ODCPImpExp            void SetDisabled (logical disabled );
public     :                  ODCPImpExp            logical SetDisplayLevel (int16 dlev, logical fillopt=YES );
public     :                  ODCPImpExp            logical SetDisplayLevel (char *typenames );
public     :                  ODCPImpExp            logical SetDisplayLevel (PropertyHandle *prophdl );
public     :                  ODCPImpExp            logical SetFilter (logical enable );
public     :                  ODCPImpExp            logical SetFilter (char *expression );
public     :                  ODCPImpExp            logical SetFocus ( );
public     :                  ODCPImpExp            logical SetFont (DFont &font );
public     :                  ODCPImpExp            logical SetFont (char *font_name );
public     :                  ODCPImpExp            void SetHidden (logical hidden );
public     :                  ODCPImpExp            logical SetLineFont (DFont &font, int32 column_id );
public     :                  ODCPImpExp            logical SetLineFont (char *font_name, int32 column_id );
public     :                  ODCPImpExp            logical SetLinePixmap (DPixmap &pixmap, int32 column_id );
public     :                  ODCPImpExp            logical SetLinePixmap (char *pixmap_name, int32 column_id );
public     :                  ODCPImpExp            void SetPosition (DPoint position );
public     :                  ODCPImpExp            logical SetPropertyHandle (PropertyHandle *prophdl, logical auto_select=NO );
public     :                  ODCPImpExp            void SetReadOnly (logical read_only );
public     :                  ODCPImpExp            logical SetRegionFont (DFont &font, int32 region_id );
public     :                  ODCPImpExp            logical SetRegionFont (char *font_name, int32 region_id );
public     :                  ODCPImpExp            logical SetRegionPixmap (DPixmap &pixmap, int32 region_id );
public     :                  ODCPImpExp            logical SetRegionPixmap (char *pixmap_name, int32 region_id );
public     :                  ODCPImpExp            void SetSelection (int32 start_pos, int32 length );
public     :                  ODCPImpExp            void SetSelection (DPoint start_point, DPoint end_point );
public     :                  ODCPImpExp            logical SetSize (DSize size, logical hgrow=NO, logical vgrow=NO );
public     :                  ODCPImpExp            logical SetTextColor (DColor &color );
public     :                  ODCPImpExp            logical SetTitle (char *text );
public     :                  ODCPImpExp            logical SetVirtualType (PropertyHandle *prophdl );
public     :                  ODCPImpExp            logical SetVirtualType (char *scoped_name );
public     :                  ODCPImpExp            logical SetZoomOutControl (CTX_GUIBase *ctx_gui, char auto_zoom );
public     :                                        int32 UpdateTreeLayout (int32 region_id );
public     : virtual          ODCPImpExp                 ~CTX_Control ( );
};

#endif
