/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/08/26 17:18:09,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODControl_HPP
#define   ODControl_HPP

class     ODControl;

#include  <sDLL.h>
class     ODControl;
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     DBorder;
class     DLayout;
class     DPixmap;
class     DictionaryHandle;
class     OControlLayout;
class     ODControl;
class     ODControlList;
class     ODLabel;
class     ODTabControl;
class     ODWindow;
class     ODataWidget;
class     ODockArea;
class     ODockWidget;
class     OEHAction;
class     OEHActionHandler;
class     OEHEvent;
class     OEHReaction;
class     OLabel;
class     OSimpleWidget;
class     OTreeLayout;
#include  <cADK_DataReferenceType.h>
#include  <cADK_HoriPos.h>
#include  <cADK_SizeType.h>
#include  <cADK_VertPos.h>
#include  <cActionBubbleType.h>
#include  <cHighLighting.h>
#include  <cOEH_Frame.h>
#include  <cOWindowTypes.h>
#include  <cSplitterTypes.h>
#include  <sDAlign.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDFont.hpp>
#include  <sDMargin.hpp>
#include  <sDPoint.hpp>
#include  <sDRect.hpp>
#include  <sDSize.hpp>
#include  <sDSyntaxClass.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOEHKeyEvent.hpp>
#include  <sOEHMouseEvent.hpp>
#include  <sOEHShortcut.hpp>
#include  <sOEHTimeEvent.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(4)

class  ODControl :public OEHDataWidget
{
protected  :         char                                        *name;                                                      // 
protected  :         OLabel                                      *label;                                                     // 
protected  :         ODataWidget                                 *frameOuterWidget;                                          // 
protected  :         ODataWidget                                 *frameInnerWidget;                                          // 
protected  :         ODataWidget                                 *controlWidget;                                             // 
protected  :         ODataWidget                                 *clientInnerWidget;                                         // 
protected  :         ODataWidget                                 *clientOuterWidget;                                         // 
protected  :         OSimpleWidget                               *lmFrame;                                                   // 
protected  :         logical                                      defaultHeight;                                             // 
protected  :         uint8                                        grid_control;                                              // 
protected  :         OControlLayout                              *lmCells;                                                   // 
protected  :         ODControl                                   *parent;                                                    // 
protected  :         ODControlList                               *controls;                                                  // 
protected  :         ODControlList                               *buttons;                                                   // 
protected  :         ODControlList                               *constants;                                                 // 
protected  :         void                                        *extra_data;                                                // 
protected  :         ODockArea                                   *dock_area;                                                 // 
protected  :         ODockWidget                                 *dock_widget;                                               // 
protected  :         logical                                      is_destroying;                                             // 
protected  :         PropertyHandle                               value_handle;                                              // 

public     :
                     char                                        *get_name() { return(name); }
                     ODataWidget                                 *get_frameOuterWidget() { return(frameOuterWidget); }
                     ODataWidget                                 *get_frameInnerWidget() { return(frameInnerWidget); }
                     ODataWidget                                 *get_controlWidget() { return(controlWidget); }
                     ODataWidget                                 *get_clientInnerWidget() { return(clientInnerWidget); }
                     ODataWidget                                 *get_clientOuterWidget() { return(clientOuterWidget); }
                     OSimpleWidget                               *get_lmFrame() { return(lmFrame); }
                     uint8                                        get_grid_control() { return(grid_control); }
                     OControlLayout                              *get_lmCells() { return(lmCells); }
                     ODControl                                   *get_parent() { return(parent); }
                     ODControlList                               *get_controls() { return(controls); }
                     ODControlList                               *get_buttons() { return(buttons); }
                     ODControlList                               *get_constants() { return(constants); }
                     ODockArea                                   *get_dock_area() { return(dock_area); }
                     ODockWidget                                 *get_dock_widget() { return(dock_widget); }
                     logical                                      get_is_destroying() { return(is_destroying); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     : virtual                                logical ActivateElements (logical act_curent );
public     :                  OGUIImpExp            logical ActivateMouseTracking ( );
public     : virtual          OGUIImpExp            OListLayout *AddColumn (char *prop_path, char *text, ODSPropertyType prop_type=PT_undefined );
public     : virtual          OGUIImpExp            OListLayout *AddColumn (int32 region_id, char *prop_path, char *text, ODSPropertyType prop_type=PT_undefined );
public     : virtual          OGUIImpExp            logical AddHighlightClass (char *names, DSyntaxClass &dsyntaxclass, DFont &dfont );
public     :                  OGUIImpExp            logical AddInputHelp (ODControl *pODControl, VECTOR(std_string) &activate_strings );
public     : virtual          OGUIImpExp            int32 AddRegion (int32 parent_id, char *prop_path, logical is_collection, char *text, ODSPropertyType prop_type=PT_undefined );
public     :                  OGUIImpExp            logical AssociateData (PropertyHandle *source_ph, char *control_name, char *title );
public     :                  OGUIImpExp            void BindClientWidget (ODataWidget *pQWidget_Outer, ODataWidget *pQWidget_Inner );
public     :                  OGUIImpExp            ODataWidget *ClientWidget ( ) const;
public     :                  OGUIImpExp            ODataWidget *ClientWidgetParent ( );
public     :                  OGUIImpExp            logical ConnectAction (const char *act_namesc, char *loid );
public     :                  OGUIImpExp            ODataWidget *ControlWidget ( ) const;
public     :                  OGUIImpExp            logical CreateCheckBox (char *control_name, int16 dsp_level );
public     : virtual          OGUIImpExp            logical CreateClientArea (char *control_name, logical is_workspace, int16 dsp_level, logical is_control, OWindowTypes win_type, logical vertical, logical exclusive );
public     :                  OGUIImpExp            logical CreateComboBox (char *control_name, logical editable, logical sort_opt, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateComboListBox (char *control_name, logical chk_items, logical multi_sel, logical sort_opt, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateContextMenu (const char *act_namesc, char *loid );
public     :                  OGUIImpExp            logical CreateDateEdit (char *control_name, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateDockingArea ( );
public     : virtual          OGUIImpExp            logical CreateLabel (DSize &dsize, ADK_VertPos verti_pos, ADK_HoriPos hori_pos, char *label_text );
public     : virtual          OGUIImpExp            void CreateLayout (DSize &grid_size, DMargin &dmargin );
public     :                  OGUIImpExp            logical CreateListView (char *control_name, logical chk_items, logical multi_sel, logical sort_opt, int16 dsp_level, logical fast_list );
public     :                  OGUIImpExp            logical CreateMenuBar (const char *act_namesc, char *loid );
public     :                  OGUIImpExp            logical CreateMultiLineEdit (char *control_name, int16 dsp_level, HighLighting hl_type=HL_none );
public     :                  OGUIImpExp            logical CreatePushButton (char *control_name, char *title_text, int8 toggle_state, logical default_opt, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateRadioButtons (char *control_name, char *label_text, int16 dsp_level, logical auto_size=NO, int32 no_strips=1, logical hori_strip=NO );
public     :                  OGUIImpExp            logical CreateRichTextEdit (char *control_name, int16 dsp_level, logical rtf_opt=NO );
public     :                  OGUIImpExp            logical CreateSingleLineEdit (char *control_name, int16 dsp_level, logical pwd_opt=NO );
public     : virtual          OGUIImpExp            ODWindow *CreateSubWindow (char *names );
public     :                  OGUIImpExp            logical CreateTabControl (char *control_name, int16 dsp_level, logical tb_upper=YES, logical tb_normal=YES, logical stb_upper=YES, char dyn_opt=NO );
public     :                  OGUIImpExp            logical CreateTable (char *control_name, logical multi_sel, logical transposed, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateTimeEdit (char *control_name, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateToolBar (const char *act_namesc, char *loid );
public     :                  OGUIImpExp            logical CreateToolBox (char *control_name, int16 dsp_level );
public     :                  OGUIImpExp            logical CreateTreeView (char *control_name, logical chk_items, logical multi_sel, logical sort_opt, int16 dsp_level, logical fast_list );
public     : virtual          OGUIImpExp            logical CreateWindowArea (char *control_name, logical is_modal, OWindowTypes win_type );
public     : virtual          OGUIImpExp            logical DA_FindEntry (char *skey, logical cur_opt=YES );
public     : virtual          OGUIImpExp            logical DA_Refresh ( );
public     : virtual          OGUIImpExp            logical DA_StoreEntry ( );
public     :                                        logical DeactivateElements (logical act_curent );
public     :                  OGUIImpExp            void Destroy ( );
public     :                                        logical DockControl (DPoint &position, DAlign &dalign );
public     :                  OGUIImpExp            logical Enable (logical fEnable );
public     :                  OGUIImpExp            void EnableInputHelp (logical enable_opt );
public     :                  OGUIImpExp            logical Execute ( );
public     :                  OGUIImpExp            int8 ExecuteDefaultAction (char *act_names );
public     :                  OGUIImpExp            void *ExtraData ( );
public     :                  OGUIImpExp            ODataWidget *FrameWidget ( );
public     :                  OGUIImpExp            char *GetActiveAction ( );
public     :                  OGUIImpExp            char *GetActiveActionItem ( );
public     : virtual          OGUIImpExp            ODControl *GetActiveControl ( );
public     :                  OGUIImpExp            PropertyHandle *GetBasePropertyHandle ( );
public     :                  OGUIImpExp            ODControl *GetButton (char *control_name );
public     :                  OGUIImpExp            DLL(ODControl) *GetButtonList ( );
public     :                  OGUIImpExp            ODControl *GetChildControl (int32 indx0 );
public     :                  OGUIImpExp            PropertyHandle *GetColumnPropertyHandle (int column );
public     :                  OGUIImpExp            ODControl *GetConstant (char *control_name );
public     :                  OGUIImpExp            DLL(ODControl) *GetConstantList ( );
public     :                  OGUIImpExp            ODControl *GetControl (char *control_name );
public     :                  OGUIImpExp            DLL(ODControl) *GetControlList ( );
public     :                  OGUIImpExp            char *GetControlName ( );
public     :                  OGUIImpExp            ODataWidget *GetControlWidget ( );
public     :                  OGUIImpExp            ODControl *GetCurrentControl ( );
public     :                  OGUIImpExp            PropertyHandle *GetCurrentPropertyHandle ( );
public     : virtual          OGUIImpExp            int32 GetCurrentRegionID ( );
public     : virtual          OGUIImpExp            int32 GetCurrentRegionID (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type );
public     :                  OGUIImpExp            PropertyHandle *GetDSPropertyHandle ( );
public     :                                        ODockArea *GetDockArea ( );
public     :                  OGUIImpExp            int32 GetDropIndex ( );
public     :                  OGUIImpExp            DPoint GetDropPoint ( );
public     :                  OGUIImpExp            PropertyHandle *GetDropPropertyHandle ( );
public     :                  OGUIImpExp            char *GetDropText ( );
public     :                  OGUIImpExp            ODControl *GetField (char *field_name );
public     : virtual          OGUIImpExp            DFont GetFont ( );
public     :                  OGUIImpExp            PropertyHandle *GetInitPropertyHandle ( );
public     :                  OGUIImpExp            char *GetLabelText ( );
public     :                  OGUIImpExp            ODControl *GetLastChildControl ( );
public     : virtual          OGUIImpExp            OTreeLayout *GetLayout ( );
public     :                                        DFont GetLineFont (int column );
public     : virtual          OGUIImpExp            OTreeLayout *GetListLayout ( );
public     :                  OGUIImpExp            const char *GetListValue ( );
public     :                  OGUIImpExp            DPoint GetMousePosition ( );
public     :                  OGUIImpExp            char *GetName ( );
public     :                  OGUIImpExp            ODControl *GetParent ( );
public     :                  OGUIImpExp            DSize &GetSize ( );
public     : virtual          OGUIImpExp            int GetSubRegionCount (int32 region_id );
public     : virtual          OGUIImpExp            int GetSubRegionCount (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type );
public     : virtual          OGUIImpExp            ODTabControl *GetTabControl ( );
public     : virtual          OGUIImpExp            DPoint GetTextPosition ( );
public     :                  OGUIImpExp            PropertyHandle *GetValue ( );
public     :                                        void Init (char *names );
public     :                                        logical InitControlWidget ( );
public     :                  OGUIImpExp            void InstallEventFilter (QObject *pQObject );
public     :                  OGUIImpExp            logical IsActionDisabled (char *act_names, char *loid );
public     :                  OGUIImpExp            logical IsActionGrouped (char *act_names, char *loid );
public     :                  OGUIImpExp            logical IsActionSeparated (char *act_names, char *loid );
public     :                  OGUIImpExp            logical IsActionToggled (char *act_names, char *loid );
public     :                  OGUIImpExp            logical IsActionVisible (char *act_names, char *loid );
public     :                  OGUIImpExp            logical IsButton ( );
public     :                  OGUIImpExp            logical IsConstant ( );
public     :                                        logical IsDestroying ( );
public     :                  OGUIImpExp            logical IsField ( );
public     :                  OGUIImpExp            logical IsLocalDrop ( );
public     :                  OGUIImpExp            ODataWidget *LabelParentWidget ( );
public     :                  OGUIImpExp            ODataWidget *MenuWidgetParent ( );
public     :                  OGUIImpExp                 ODControl (ODControl *pODControl, char *names );
public     :                  OGUIImpExp                 ODControl (ODControl *pODControl, ODataWidget *oODataWidget, logical create_ods, char *names );
public     :                  OGUIImpExp                 ODControl (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, char *names );
public     :                                        PropertyHandle *ProvideValue ( );
public     : virtual          OGUIImpExp            PropertyHandle *ReceiveSelectedItem ( );
public     :                                        logical RefreshElements ( );
public     : virtual          OGUIImpExp            void RefreshRegion (int32 region_id );
public     :                  OGUIImpExp            logical RegisterControlWidget (char *control_name, DLL(ODControl) *child_list, int16 dsp_level );
public     :                  OGUIImpExp            void *RemoveButton (char *string );
public     : virtual          OGUIImpExp            logical RemoveColumn (int32 region_id, int32 column_id );
public     :                  OGUIImpExp            void *RemoveConstant (char *string );
public     :                  OGUIImpExp            ODControl *RemoveControl (char *string );
public     :                                        void RemoveControlWidget ( );
public     :                  OGUIImpExp            void *RemoveField (char *string );
public     :                  OGUIImpExp            logical RemoveInputHelp (ODControl *pODControl );
public     :                  OGUIImpExp            void Reparent (ODControl *pODControl, DSize &dsize );
public     : virtual          OGUIImpExp            int32 ReplaceSubRegions (int32 parent_id, int32 region_id );
public     :                                        void ResetControlWidget ( );
public     :                                        void ResetDockWidget ( );
public     : virtual          OGUIImpExp            logical ResetRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     :                  OGUIImpExp            logical SetAcceptDrops (logical enable_opt );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, char *parent_loid, OEHEvent *pOEHEvent, ODataWidget *oODataWidget_w=NULL, ActionBubbleType pass_opt_w=ABT_never, char *pass_to=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, char *parent_loid, ActionBubbleType pass_opt_w=ABT_never, char *pass_to=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, OEHMouseEvent mouse_event, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, int mouse_clicks, logical key_alt, logical key_shift, logical key_ctrl, logical mouse_right, logical mouse_mid, logical mouse_left );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, char *string, OEH_Frame oeh_frame, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, OEHShortcut short_cut, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, int int_event, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, DB_Event data_event, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, OEHTimeEvent time_event, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, dbdt start_date, dbtm start_time, int32 dist_date, dbtm dist_time, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, OEHKeyEvent key_event, ODataWidget *oODataWidget_w=NULL );
public     :                  OGUIImpExp            OEHAction *SetAction (const char *act_namesc, char *loid, int key_code, logical key_alt, logical key_shift, logical key_ctrl );
public     :                  OGUIImpExp            logical SetActionControl (char *act_names, char *loid, ODControl *pODControl );
public     :                  OGUIImpExp            logical SetActionDisabled (char *act_names, char *loid, logical fEnabled );
public     :                  OGUIImpExp            logical SetActionGrouped (char *act_names, char *loid, logical fEnabled );
public     :                                        logical SetActionIcon (char *act_names, char *loid, char *text, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled );
public     :                  OGUIImpExp            logical SetActionSeparated (char *act_names, char *loid, logical fEnabled );
public     :                                        logical SetActionText (char *act_names, char *loid, char *text, char *tip, char *status_tip, char *what );
public     :                  OGUIImpExp            logical SetActionToggled (char *act_names, char *loid, logical fEnabled );
public     :                  OGUIImpExp            logical SetActionVisible (char *act_names, char *loid, logical fEnabled );
public     :                  OGUIImpExp            void SetAsMainWindow ( );
public     : virtual          OGUIImpExp            logical SetBasePath (char *base_path );
public     :                  OGUIImpExp            logical SetColumnFont (DFont *pDFont, int32 region_id, int32 column_id );
public     :                  OGUIImpExp            logical SetColumnPixmap (DPixmap *pDPixmap, int32 region_id, int32 column_id );
public     :                  OGUIImpExp            void SetControlProperties (logical dynamic_opt, logical out_opt, logical chache_opt, int32 max_length );
public     :                  OGUIImpExp            logical SetControlWidget (ODataWidget *pODataWidget, DLL(ODControl) *child_list, char *control_name, int16 dsp_level );
public     :                  OGUIImpExp            logical SetDataSource (DBObjectHandle &ob_handle );
public     :                  OGUIImpExp            logical SetDataSource (DictionaryHandle *dictionary, char *db_path, PIACC accmode, logical net_opt );
public     :                  OGUIImpExp            logical SetDataSource (char *ds_name, PIACC accmode );
public     : virtual          OGUIImpExp            logical SetDatabaseHandle (DatabaseHandle &db_handle );
public     : virtual                                logical SetDefaultReactions ( );
public     :                  OGUIImpExp            void SetDisabled (logical disable_opt );
public     : virtual          OGUIImpExp            logical SetDisplayLevel (int16 dsp_level );
public     : virtual          OGUIImpExp            logical SetDisplayLevel (char *typenames );
public     : virtual          OGUIImpExp            logical SetDisplayLevel (PropertyHandle *prophdl );
public     :                  OGUIImpExp            void SetExtraData (void *extra_data_ptr );
public     :                  OGUIImpExp            logical SetFilter (char *expression, logical enable_opt );
public     :                  OGUIImpExp            logical SetFocus ( );
public     :                  OGUIImpExp            logical SetFont (DFont *pDFont );
public     : virtual          OGUIImpExp            logical SetHandleWidth (int16 handle_width );
public     :                  OGUIImpExp            logical SetHelp (char *text );
public     :                  OGUIImpExp            void SetHidden (logical hidden );
public     :                  OGUIImpExp            void SetLabelText (char *label_text );
public     :                  OGUIImpExp            logical SetLineFont (char *font_names, int column );
public     :                  OGUIImpExp            logical SetLineFont (DFont *pDFont, int column );
public     :                  OGUIImpExp            logical SetLinePixmap (char *pixmap_names, int column );
public     :                  OGUIImpExp            logical SetLinePixmap (DPixmap *pDPixmap, int column );
public     :                  OGUIImpExp            logical SetPalette (DLayout *pDLayout );
public     :                  OGUIImpExp            logical SetPixmaps (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled );
public     :                  OGUIImpExp            logical SetPropertyHandle (PropertyHandle *prophdl, logical auto_select );
public     :                                        logical SetReaction (char *act_names, int keycode, logical key_alt, logical key_shift, logical key_ctrl );
public     :                                        logical SetReaction (char *act_names, int int_event );
public     :                                        logical SetReaction (char *act_names, char clicks, logical key_alt, logical key_shift, logical key_ctrl, logical mouse_right, logical mouse_mid, logical mouse_left );
public     :                  OGUIImpExp            void SetReadOnly (logical fReadOnly );
public     :                  OGUIImpExp            logical SetRegionFont (DFont *pDFont, int32 region_id );
public     :                  OGUIImpExp            logical SetRegionPixmap (DPixmap *pDPixmap, int32 region_id );
public     :                  OGUIImpExp            void SetSize (const DSize &rcDSize, logical hgrow, logical vgrow );
public     :                  OGUIImpExp            logical SetText (char *title_text );
public     : virtual          OGUIImpExp            void SetTextPosition (DPoint &position );
public     :                  OGUIImpExp            void SetTextSelection (int32 start_pos, int32 length );
public     :                  OGUIImpExp            void SetTextSelection (DPoint start_point, DPoint end_point );
public     :                  OGUIImpExp            void SetTitle (char *title_text );
public     :                  OGUIImpExp            logical SetTooltip (char *text );
public     :                  OGUIImpExp            logical SetUserActionHdl (OEHActionHandler *pOEHActionHandler, logical gui_opt );
public     :                  OGUIImpExp            logical SetValue ( );
public     :                  OGUIImpExp            logical SetValue (PropertyHandle *prophdl );
public     :                  OGUIImpExp            logical SetValue (char *text );
public     :                  OGUIImpExp            logical SetVirtualType (PropertyHandle *prophdl );
public     :                  OGUIImpExp            logical SetVirtualType (char *scoped_name );
public     :                  OGUIImpExp            void SetWindowFlags (logical reset_flags, logical has_title, logical has_border, logical has_close, logical has_resize, logical has_minmax, logical has_sysmenu, logical is_top_always, logical has_small_title );
public     :                  OGUIImpExp            logical SetZoomOutWindow (ODControl *pODControl, char auto_zoom );
public     :                  OGUIImpExp            logical SetupFont ( );
public     :                  OGUIImpExp            void SetupParentDataSource ( );
public     :                  OGUIImpExp            void Show (logical fShow );
public     :                  OGUIImpExp            void UpdateFrameStyle (DBorder *pDBorder );
public     : virtual          OGUIImpExp            void UpdateLayout (DPoint &position, int16 inner_dist, int16 outer_dist, DSize &dsize, DSize &frame_size, DAlign &dalign, int16 dsp_level );
public     : virtual          OGUIImpExp            logical UpdateTreeLayout (int32 region_id );
public     :                  OGUIImpExp            ODataWidget *WidgetFrame ( );
public     :                                        ODataWidget *WidgetOwner ( );
public     :                                        QWidget *WidgetQ ( );
public     :                                        OEHDataWidget *controlOEHWidget ( );
public     : virtual          OGUIImpExp            void setReadOnly (logical fReadOnly );
public     :                                             ~ODControl ( );
};

#pragma pack()
#endif
