/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OEHDataWidget

\brief    Event handling data widget
          Event  handling data widgets  are data widgets,  which will handle all
          events  from the  current widget  and widgets, which are sub-ordinated
          and  not marked as event handling data widgets. This is mainly used to
          pass  events  created  in  context  menus or associated buttons to the
          owning  data  widget.  The  owning  data widget can be the control, an
          upper control in the hierarchy or an OD-Control. 
          Events  are collected in subordinated controls  and passed to the next
          higher  level. Depending on the interface (O or OD) the object causing
          the event is passed as an O or OD-object. 
          Eventhandling  is  enabled  by  default  for  all controls (O and OD),
          which do have a parent. This is usually the case for all O-Controls.
          OEHDataWidget is using the following status indicator (sts):
          stsdel:   widget is closing, eventhandling is deactivated
          stsini:    eventhandling is activated, slots ate connected to signals
          stsfil:     widget is filled (after ods has been activated)
          stsmod: data is modified
          stslck:    zeitweise keine Verarbeitung von spontanen GUI-Events (z.B.
          SetFocus)

\date     $Date: 2006/07/26 16:55:35,00 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHDataWidget_HPP
#define   OEHDataWidget_HPP

class     OEHDataWidget;

#ifndef   DLL_OFont_HPP
#define   DLL_OFont_HPP
#include  <sOFont.hpp>
#include  <sDLL.h>
#endif
class     CellData;
class     DFont;
class     DictionaryHandle;
class     ItemData;
class     ODS;
class     ODSItem;
class     OEHAction;
class     OEHDataWidget;
class     OEHDataWidgetEventFilter;
class     OEHEvent;
class     OFont;
class     OPopupMenu;
class     OStringList;
class     OTreeLayout;
#include  <cADK_DATAEVENT.h>
#include  <cADK_DBEVENT.h>
#include  <cADK_GUIEVENT.h>
#include  <cODSPropertyType.h>
#include  <sDBObjectHandle.hpp>
#include  <sDPoint.hpp>
#include  <sInstance.hpp>
#include  <sODSPropPath.hpp>
#include  <sODataWidget.hpp>
#include  <sODragAndDrop.hpp>
#include  <sOEHInternalEvent.hpp>
#include  <sOEHKeyEvent.hpp>
#include  <sOEHMouseEvent.hpp>
#include  <sOEHShortcut.hpp>
#include  <sOEHTimeEvent.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbsts.hpp>
class  OEHDataWidget :public bsts,
public ODataWidget,
public ODragAndDrop
{
protected  :         ODS                                         *base_ods;                                                  // Base collection
protected  :         DLL(OFont)                                   fonts;                                                     // Value ODS
protected  :         OEHDataWidgetEventFilter                    *event_filter;                                              // 
protected  :         PropertyHandle                               new_instance;                                              // Value ODS
protected  :         QString                                      find_text;                                                 // 
protected  :         DPoint                                       mouse_pos;                                                 // 

public     :
                     ODS                                         *get_base_ods() { return(base_ods); }
                     DLL(OFont)                                  &get_fonts() { return(fonts); }
                     OEHDataWidgetEventFilter                    *get_event_filter() { return(event_filter); }
                     PropertyHandle                              &get_new_instance() { return(new_instance); }
                     QString                                     &get_find_text() { return(find_text); }
                     DPoint                                      &get_mouse_pos() { return(mouse_pos); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     :                                        OFont *AddFont (DFont *pDFont );
public     :                  OGUIImpExp            logical AssociateData (PropertyHandle *source_ph, char *control_name, char *title );
public     :                                        void BlockSignals (logical block_opt );
public     :                                        logical CheckKey (PropertyHandle **prophdl_ptr );
public     :                                        logical ContextMenuEvent (QObject *watched, int x, int y );
public     : virtual                                logical DA_Add (logical fAppend, char *str_key );
public     : virtual                                logical DA_AppendEntry ( );
public     : virtual                                logical DA_Associate ( );
public     :                                        logical DA_BrowseDirectories ( );
public     : virtual                                logical DA_BrowseFiles ( );
public     : virtual                                logical DA_BrowseWriteFiles ( );
public     : virtual                                logical DA_Cancel ( );
public     : virtual                                logical DA_CancelClose ( );
public     : virtual                                logical DA_Copy ( );
public     : virtual                                logical DA_CopyEntry ( );
public     : virtual                                logical DA_Cut ( );
public     : virtual                                logical DA_DeleteEntry ( );
public     : virtual                                logical DA_DeleteSet ( );
public     : virtual                                logical DA_EditEntry ( );
public     : virtual                                logical DA_FindEntry ( );
public     : virtual                                logical DA_FindEntry (char *skey, logical cur_opt=YES );
public     : virtual                                logical DA_ImportFile ( );
public     : virtual                                logical DA_InsertEntry ( );
public     : virtual                                logical DA_Move ( );
public     : virtual                                logical DA_MoveDown ( );
public     : virtual                                logical DA_MoveUp ( );
public     : virtual                                logical DA_NewFindEntry ( );
public     : virtual                                logical DA_Paste ( );
public     : virtual                                logical DA_Redo ( );
public     : virtual          OGUIImpExp            logical DA_Refresh ( );
public     : virtual                                logical DA_RenameEntry ( );
public     : virtual                                logical DA_Reset ( );
public     : virtual                                logical DA_ResetCascadingSelection ( );
public     : virtual                                logical DA_ResetSelection ( );
public     : virtual                                logical DA_Save ( );
public     : virtual                                logical DA_SaveClose ( );
public     :                                        logical DA_SelectEntry ( );
public     : virtual                                logical DA_SetCascadingSelection ( );
public     :                                        logical DA_SetDisplayLevel0 ( );
public     :                                        logical DA_SetDisplayLevel1 ( );
public     :                                        logical DA_SetDisplayLevel2 ( );
public     :                                        logical DA_SetDisplayLevel3 ( );
public     :                                        logical DA_SetDisplayLevel4 ( );
public     :                                        logical DA_SetDisplayLevel5 ( );
public     :                                        logical DA_SetDisplayLevel6 ( );
public     :                                        logical DA_SetDisplayLevel7 ( );
public     :                                        logical DA_SetDisplayLevel8 ( );
public     :                                        logical DA_SetDisplayLevel9 ( );
public     : virtual                                logical DA_SetSelection ( );
public     : virtual                                logical DA_StoreEntry ( );
public     : virtual                                logical DA_Undo ( );
public     : virtual                                logical DA_UpdateEntries ( );
public     : virtual                                logical DA_ValidateData ( );
public     : virtual                                logical DA_ZoomIn ( );
public     : virtual                                logical DA_ZoomOut ( );
public     : virtual          OGUIImpExp            OEHDataWidget *DataWidgetOEH ( );
public     : virtual                                logical Deactivate (logical data_only=NO );
public     : virtual                                int8 ExecuteAction (char *act_names );
public     : virtual                                int8 FocusInEvent ( );
public     : virtual                                int8 FocusOutEvent ( );
public     :                                        OFont *Font (char *font_names );
public     :                                        PropertyHandle *GetBasePropertyHandle ( );
public     : virtual                                PropertyHandle *GetInitPropertyHandle ( );
public     : virtual          OGUIImpExp            PropertyHandle *GetNewInstanceHandle ( );
public     :                                        char *GetNewKey (PropertyHandle *ph, char *text1, char *text2 );
public     : virtual                                int8 HideEvent ( );
public     :                                        logical Initialize ( );
public     :                                        logical KeyEvent (int keycode, int keystate, logical keyreleased );
public     :                                        char MouseClickEvent (int x, int y, int32 click_count );
public     :                                        char MouseMoveEvent (int x, int y );
public     :                  OGUIImpExp                 OEHDataWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                  OGUIImpExp                 OEHDataWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                        ODS *ProvideBaseODS ( );
public     :                                        Instance ProvideNewInstance (PropertyHandle *prophdl, char *str_key );
public     : virtual          OGUIImpExp            logical SetBasePath (char *base_path );
public     :                  OGUIImpExp            logical SetDataSource (DBObjectHandle &ob_handle );
public     :                  OGUIImpExp            logical SetDataSource (DictionaryHandle *dictionary, char *db_path, PIACC accmode, logical net_opt );
public     :                  OGUIImpExp            logical SetDataSource (char *ds_name, PIACC accmode );
public     : virtual                                logical SetDefaultReactions ( );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, char *loid, char *parent_loid_w=NULL );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, OEHShortcut short_cut, char *parent_loid_w=NULL );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, OEHKeyEvent key_event );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, OEHInternalEvent system_event );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, OEHMouseEvent mouse_event );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, DB_Event data_event );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, OEHTimeEvent time_event );
public     :                                        OEHAction *SetGUIDefReaction (const char *act_namesc, int int_event );
public     :                                        logical SetNewInstKey (PropertyHandle *prophdl, char *str_key );
public     : virtual          OGUIImpExp            OTreeLayout *SetPath (char *prop_path, ODSPropertyType prop_type=PT_undefined );
public     : virtual          OGUIImpExp            OTreeLayout *SetPath (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type=PT_undefined, PIACC accmode_w=PI_Update );
public     : virtual          OGUIImpExp            OTreeLayout *SetPath (ODSPropPath &rODSPropPath );
public     :                  OGUIImpExp            logical SetPropertyHandle (PropertyHandle *prophdl, logical auto_select );
public     : virtual                                int8 ShowEvent ( );
public     : virtual                                void UpdateControl ( );
public     : virtual          OGUIImpExp            ODSItem *ValueItem ( );
public     : virtual          OGUIImpExp            void updateSelection ( );
public     :                                             ~OEHDataWidget ( );
};

#endif
