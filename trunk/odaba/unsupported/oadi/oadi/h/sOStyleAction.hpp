/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OStyleAction



\date     $Date: 2006/04/28 15:39:36,29 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OStyleAction_HPP
#define   OStyleAction_HPP

class     OStyleAction;

#include  <sDLL.h>
class     OButton;
#include  <sDLL.h>
class     OEventAction;
#include  <sDLL.h>
class     OField;
#include  <sDLL.h>
class     OToolBox;
class     OButton;
class     OButtonControl;
class     OContextStyle;
class     OElementStyle;
class     OField;
class     OFieldControl;
class     OFrameStyle;
class     OLabelDefinition;
class     OListLayout;
class     OMenu;
class     OResource;
class     OTreeLayout;
class     OWindow;
class     PropertyHandle;
class     TControl;
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <sDMargin.hpp>
#include  <sDSize.hpp>
#include  <sDString.hpp>
#include  <sOEventActionControl.hpp>
#pragma pack(4)

class  OStyleAction :public OEventActionControl
{
protected  :         logical                                      outer_elements;                                            
protected  :         DLL(OField)                                 *fields;                                                    
protected  :         DLL(OField)                                 *columns;                                                   
protected  :         DLL(OField)                                 *regions;                                                   
protected  :         DLL(OButton)                                *buttons;                                                   
protected  :         OMenu                                       *menu;                                                      
protected  :         OMenu                                       *contextmenu;                                               
protected  :         DLL(OToolBox)                               *tool_bars;                                                 
protected  :         DLL(OEventAction)                           *reactions;                                                 
protected  :         int32                                        left_size;                                                 
protected  :         int32                                        top_size;                                                  
protected  :         int32                                        right_size;                                                
protected  :         int32                                        bottom_size;                                               
protected  :         int32                                        left_height;                                               
protected  :         int32                                        right_height;                                              
protected  :         int32                                        top_width;                                                 
protected  :         int32                                        top_left_width;                                            
protected  :         int32                                        top_right_width;                                           
protected  :         int32                                        bottom_width;                                              
protected  :         int32                                        bottom_left_width;                                         
protected  :         int32                                        bottom_right_width;                                        

public     :
                     logical                                      get_outer_elements() { return(outer_elements); }
                     DLL(OField)                                 *get_fields() { return(fields); }
                     DLL(OField)                                 *get_columns() { return(columns); }
                     DLL(OField)                                 *get_regions() { return(regions); }
                     DLL(OButton)                                *get_buttons() { return(buttons); }
                     OMenu                                       *get_contextmenu() { return(contextmenu); }
                     DLL(OToolBox)                               *get_tool_bars() { return(tool_bars); }
                     int32                                        get_left_size() { return(left_size); }
                     int32                                        get_top_size() { return(top_size); }
                     int32                                        get_right_size() { return(right_size); }
                     int32                                        get_bottom_size() { return(bottom_size); }
                     int32                                        get_left_height() { return(left_height); }
                     int32                                        get_right_height() { return(right_height); }
                     int32                                        get_top_width() { return(top_width); }
                     int32                                        get_top_left_width() { return(top_left_width); }
                     int32                                        get_top_right_width() { return(top_right_width); }
                     int32                                        get_bottom_width() { return(bottom_width); }
                     int32                                        get_bottom_left_width() { return(bottom_left_width); }
                     int32                                        get_bottom_right_width() { return(bottom_right_width); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        OField *Column (int index );
public     :                                        OMenu *ContextMenu ( );
public     :                                        OField *Field (int index );
public     :                                        OField *FieldByName (const DString &rcdsName );
public     :                                        int FieldCount ( );
public     :                                        DSize GetFrameSize (DSize dsize, DMargin &field_margin );
public     :                                        OMenu *Menu ( );
public     :                                             OStyleAction ( );
public     :                                             OStyleAction (OEventActionControl bc, logical outer_elements, DLL(OField) *fields, DLL(OField) *columns, DLL(OField) *regions, DLL(OButton) *buttons, OMenu *menu, OMenu *contextmenu, DLL(OToolBox) *tool_bars, DLL(OEventAction) *reactions, int32 left_size, int32 top_size, int32 right_size, int32 bottom_size, int32 left_height, int32 right_height, int32 top_width, int32 top_left_width, int32 top_right_width, int32 bottom_width, int32 blw, int32 brw );
public     : virtual                                TControl *OpenControl (char *typenames, TControl *tparent, OFrameStyle *pOFrameStyle, OResource *owner );
public     :                                        logical PrepareRead (PropertyHandle *ph );
public     :                                        DLL(OEventAction) *Reactions ( );
public     : virtual                                logical Read (PropertyHandle *ph );
protected  :                                        logical ReadButtons (PropertyHandle *ph );
protected  :                                        logical ReadColumns (PropertyHandle *ph );
protected  :                                        logical ReadContextMenu (PropertyHandle *ph );
protected  :                                        logical ReadFields (PropertyHandle *ph );
protected  :                                        logical ReadMenu (PropertyHandle *ph );
protected  :                                        logical ReadRegions (PropertyHandle *ph );
protected  :                                        logical ReadToolBars (PropertyHandle *ph );
public     :                                        OField *Region (int index );
public     : virtual                                void Reset ( );
public     :                                        logical SetupElementSize (OElementStyle *pOElementStyle );
public     :                                        logical SetupElementSize (OFieldControl *pOFieldControl );
public     :                                        logical SetupElementSize (OContextStyle *pOContextStyle, DSize dsize );
public     :                                        logical SetupLabelSize (OLabelDefinition *pOLabelDefinition );
public     : virtual                                logical SetupListLayout (OListLayout *pOListLayout );
public     :                                        void SetupMargin ( );
public     :                                        logical SetupSize (ADK_VertPos vert_pos, ADK_HoriPos hori_pos, DSize dsize, int32 distance );
public     : virtual                                logical SetupTreeLayout (OTreeLayout *pOTreeLayout, logical recursive );
public     :                                        DLL(OToolBox) *Toolbars ( );
public     : virtual                                     ~OStyleAction ( );
};

#pragma pack()
#endif
