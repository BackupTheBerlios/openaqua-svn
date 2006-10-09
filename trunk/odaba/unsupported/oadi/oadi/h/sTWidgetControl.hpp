/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TWidgetControl

\brief    


\date     $Date: 2006/08/26 17:11:41,06 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TWidgetControl_HPP
#define   TWidgetControl_HPP

class     TWidgetControl;

#include  <sDLL.h>
class     TWidgetControl;
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     CTX_Control;
class     DPixmap;
class     ODControl;
class     ODataWidget;
class     OElementStyle;
class     OEventAction;
class     OWidget;
class     OWidgetDesignModeBase;
class     OWidgetDesignModeFactory;
class     TWidgetControl;
#include  <cADK_DataReferenceType.h>
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <cOEH_Frame.h>
#include  <sDColor.hpp>
#include  <sDFont.hpp>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
#include  <sODataSource.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#pragma pack(4)

class  TWidgetControl :public TControl
{
protected  :         DLL(TWidgetControl)                         *input_help;                                                // 
protected  :         CTX_Control                                 *context;                                                   // 
protected  :         ODControl                                   *complexWidget;                                             // 

public     :
                     CTX_Control                                 *get_context() { return(context); }
                     ODControl                                   *get_complexWidget() { return(complexWidget); }
public     :                                        void AcceptDrops (logical drop_opt );
public     : virtual                                void Activate ( );
public     :                  OADIImpExp            char *ActiveAction ( );
public     :                  OADIImpExp            char *ActiveActionItem ( );
public     :                                        int32 AddColumn (int32 region_id, char *prop_path, char *text, ADK_DataReferenceType ref_type );
public     :                  OADIImpExp            CTX_Control *AddInputHelp (char *class_name, char *ctl_names, VECTOR(std_string) &activate_strings, PropertyHandle *prophdl );
public     :                                        int32 AddRegion (int32 parent_id, char *prop_path, char *text, logical is_collection, ADK_DataReferenceType ref_type );
public     :                  OADIImpExp            logical AssociateData (PropertyHandle *source_ph, char *control_name, char *title );
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                void Close ( );
public     :                                        ODControl *ComplexWidgetOwner ( );
public     :                                        ODControl *ComplexWidgetParent ( );
public     :                                        CTX_Control *Context ( );
public     :                  OADIImpExp            ODataWidget *ControlWidgetParent ( );
public     :                  OADIImpExp            CTX_Control *CreateButton (PropertyHandle &class_ph, char *name, DPoint position, int resource_id=AUTO );
public     :                  OADIImpExp            logical CreateConstant (PropertyHandle &class_ph, char *name );
public     :                  OADIImpExp            CTX_Control *CreateField (PropertyHandle &class_ph, char *name, DPoint position, logical design_mode, int resource_id=AUTO );
public     : virtual                                void Deactivate ( );
protected  : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
public     :                                        OWidgetDesignModeBase *EnableDesignMode (OWidgetDesignModeFactory *dmode_factory );
public     :                  OADIImpExp            logical EnableInputHelp (logical enable_opt );
public     :                                        char ExecuteDefaultAction (char *act_names );
public     :                  OADIImpExp            logical FillControl ( );
public     :                                        TWidgetControl *GetActiveControl ( );
public     :                                        PropertyHandle *GetBasePropertyHandle ( );
public     :                                        TWidgetControl *GetButton (char *control_name );
public     :                  OADIImpExp            PropertyHandle *GetColumnPropertyHandle (int column );
public     :                                        TWidgetControl *GetConstant (char *control_name );
public     :                  OADIImpExp            CTX_Control *GetContext ( );
public     :                                        TWidgetControl *GetControl (char *control_name );
public     :                                        char *GetControlName ( );
public     :                  OADIImpExp            TWidgetControl *GetCurrentControl ( );
public     :                  OADIImpExp            PropertyHandle *GetCurrentPropertyHandle ( );
public     :                                        int32 GetCurrentRegionID ( );
public     :                                        PropertyHandle *GetDSPropertyHandle ( );
public     :                                        PropertyHandle *GetData ( );
public     :                  OADIImpExp            int GetDecision (char *szTitle, char *szText, int button0, int button1, int button2 );
public     :                                        OWidgetDesignModeBase *GetDesignMode ( );
public     :                  OADIImpExp            int16 GetDisplayLevel ( );
public     :                                        int32 GetDropIndex ( );
public     :                                        DPoint GetDropPoint ( );
public     :                                        PropertyHandle *GetDropPropertyHandle ( );
public     :                                        char *GetDropText ( );
public     :                                        TWidgetControl *GetField (char *field_name );
public     :                                        DFont GetFont ( );
public     :                  OADIImpExp            PropertyHandle *GetInitPropertyHandle ( );
public     :                  OADIImpExp            const char *GetKey ( );
public     :                                        DFont GetLineFont (int column );
public     :                                        DPoint GetMousePosition ( );
public     :                                        DPoint GetPosition ( );
public     :                  OADIImpExp            DSize GetSize ( );
public     :                                        int32 GetSubRegionCount (int32 region_id );
public     :                  OADIImpExp            logical HasFocus ( );
public     :                                        logical IsActionDisabled (char *act_names, char *loid );
public     :                                        logical IsActionToggled (char *act_names, char *loid );
public     :                                        logical IsActionVisible (char *act_names, char *loid );
public     :                  OADIImpExp            logical IsLocalDrop ( );
public     :                                        logical LoadDynamicControl (char *class_name, char *control_name );
public     :                                        ODControl *ProvideComplexWidget ( );
public     :                  OADIImpExp            PropertyHandle *ReceiveSelectedItem ( );
public     :                                        void RefreshRegion (int32 region_id );
public     :                  OADIImpExp            logical RemoveButton (char *name );
public     :                                        logical RemoveColumn (int32 region_id, int32 column_id );
public     :                                        void RemoveComplexWidget ( );
public     :                  OADIImpExp            logical RemoveConstant (char *name );
public     :                  OADIImpExp            logical RemoveField (char *name );
public     :                                        int32 ReplaceSubRegions (int32 parent_id, int32 region_id );
public     :                                        logical ResetRegion (int32 parent_id, int32 region_id, logical reset_columns );
public     :                  OADIImpExp            logical SearchKey (char *skey );
public     : virtual                                logical SetAction (OEventAction *pOEventAction, OEventAction *parent_action, OEH_Frame event_frame );
public     :                                        logical SetActionDisabled (char *act_names, char *loid, logical fDisable );
public     :                                        logical SetActionToggled (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetActionVisible (char *act_names, char *loid, logical fEnable );
public     :                                        logical SetBackgroundColor (DColor &rDColor );
public     :                                        logical SetColumnFont (DFont *font, int32 region_id, int32 column_id );
public     :                                        logical SetColumnFont (char *font_name, int32 region_id, int32 column_id );
public     :                                        logical SetColumnPixmap (DPixmap *pixmap, int32 region_id, int32 column_id );
public     :                                        logical SetColumnPixmap (char *pixmap_name, int32 region_id, int32 column_id );
public     :                  OADIImpExp            logical SetData ( );
public     :                  OADIImpExp            logical SetData (PropertyHandle *prophdl );
public     :                  OADIImpExp            logical SetData (char *string );
public     :                                        logical SetDatabaseHandle (DatabaseHandle &db_handle );
public     :                  OADIImpExp            void SetDisabled (logical disable );
public     :                  OADIImpExp            logical SetDisplayLevel (int16 dsp_level );
public     :                  OADIImpExp            logical SetDisplayLevel (char *typenames );
public     :                  OADIImpExp            logical SetDisplayLevel (PropertyHandle *prophdl );
public     :                  OADIImpExp            logical SetFilter (char *expression, logical enable_opt );
public     :                  OADIImpExp            logical SetFocus ( );
public     :                                        logical SetFont (DFont *font );
public     :                                        logical SetFont (char *font_name );
public     :                  OADIImpExp            void SetHidden (logical hidden );
public     :                                        logical SetLineFont (DFont *font, int32 column_id );
public     :                                        logical SetLineFont (char *font_name, int32 column_id );
public     :                                        logical SetLinePixmap (DPixmap *pixmap, int32 column_id );
public     :                                        logical SetLinePixmap (char *pixmap_name, int32 column_id );
public     :                  OADIImpExp            void SetPosition (DPoint position );
public     :                                        logical SetPropertyHandle (PropertyHandle *prophdl, logical auto_select );
public     :                  OADIImpExp            void SetReadOnly (logical read_only );
public     :                                        logical SetRegionFont (DFont *font, int32 region_id );
public     :                                        logical SetRegionFont (char *font_name, int32 region_id );
public     :                                        logical SetRegionPixmap (DPixmap *pixmap, int32 region_id );
public     :                                        logical SetRegionPixmap (char *pixmap_name, int32 region_id );
public     :                  OADIImpExp            void SetSelection (int32 start_pos, int32 length );
public     :                  OADIImpExp            void SetSelection (DPoint start_point, DPoint end_point );
public     :                                        logical SetSize (DSize dsize, logical hgrow, logical vgrow );
public     :                                        logical SetTextColor (DColor &rDColor );
public     :                                        logical SetTitle (char *text );
public     :                                        logical SetVirtualType (PropertyHandle *prophdl );
public     :                                        logical SetVirtualType (char *scoped_name );
protected  : virtual                                logical SetWindowFlags (logical reset_flags );
public     :                  OADIImpExp            logical SetZoomOutWidget (TWidgetControl *pTWidgetControl, char auto_zoom );
public     :                                        void SetupParentDataSource ( );
public     : virtual                                void Show (logical fShow );
public     :                                             TWidgetControl ( );
public     : virtual                                void UpdateLayout ( );
public     :                  OADIImpExp            logical UpdateTreeLayout (int32 region_id );
public     :                                        ODataWidget *WidgetOwner ( );
public     : virtual                                void closeRequest ( );
public     :                                        logical enable (logical fEnable );
protected  :                                        void loadBounds ( );
public     :                                        void storeBounds ( );
public     : virtual                                     ~TWidgetControl ( );
};

#pragma pack()
#endif
