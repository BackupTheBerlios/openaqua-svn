/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OContextStyle

\brief    


\date     $Date: 2006/07/09 12:19:42,68 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OContextStyle_HPP
#define   OContextStyle_HPP

class     OContextStyle;

class     OContextStyle;
class     PropertyHandle;
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <sDPoint.hpp>
#include  <sDRect.hpp>
#include  <sDSize.hpp>
#include  <sOAlign.hpp>
#include  <sOLabelDefinition.hpp>
#include  <sOPersistent.hpp>
#include  <sOText.hpp>
#pragma pack(4)

class  OContextStyle :public OPersistent
{
protected  :         logical                                      autoOpen;                                                  // 
protected  :         logical                                      separate;                                                  // 
protected  :         logical                                      mouse_tracking;                                            // 
protected  :         logical                                      hidden;                                                    // 
protected  :         logical                                      disabled;                                                  // 
protected  :         logical                                      checked;                                                   // 
protected  :         logical                                      docking_area;                                              // 
protected  :         logical                                      accept_drop;                                               // 
protected  :         int16                                        displayLevel;                                              // 
protected  :         int16                                        distance;                                                  // 
protected  :         DRect                                        bounds;                                                    // 
protected  :         OAlign                                       align;                                                     // 
protected  :         OLabelDefinition                             labelPosition;                                             // 
protected  :         OText                                        textDefinitions;                                           // 
protected  :         int                                          childDisplayLevel;                                         // 

public     :
                     logical                                      get_autoOpen() { return(autoOpen); }
                     logical                                      get_separate() { return(separate); }
                     logical                                      get_mouse_tracking() { return(mouse_tracking); }
                     logical                                      get_hidden() { return(hidden); }
                     logical                                      get_disabled() { return(disabled); }
                     logical                                      get_checked() { return(checked); }
                     logical                                      get_docking_area() { return(docking_area); }
                     logical                                      get_accept_drop() { return(accept_drop); }
                     int16                                        get_displayLevel() { return(displayLevel); }
                     int16                                        get_distance() { return(distance); }
                     DRect                                       &get_bounds() { return(bounds); }
                     OAlign                                      &get_align() { return(align); }
                     OLabelDefinition                            &get_labelPosition() { return(labelPosition); }
                     OText                                       &get_textDefinitions() { return(textDefinitions); }
                     int                                         &get_childDisplayLevel() { return(childDisplayLevel); }
public     :                                        OAlign *Align ( ) const;
public     : virtual                                const DRect &Bounds ( ) const;
public     :                                        logical CellAt (const DPoint &rcDPoint, ADK_HoriPos rADK_HoriPos, ADK_VertPos rADK_VertPos ) const;
public     :                                        int ChildDisplayLevel ( ) const;
public     :                                        int DisplayLevel ( );
public     :                                        logical IsAutoOpen ( );
public     :                                        logical IsChecked ( );
public     :                                        logical IsDisabled ( );
public     :                                        logical IsHidden ( );
public     :                                        logical IsOuterElement ( );
public     :                                        logical IsSeparate ( );
public     :                                        OLabelDefinition *LabelPosition ( ) const;
public     :                                        DPoint MapFromCell (const DPoint &rcDPoint, ADK_HoriPos vADK_HoriPos, ADK_VertPos vADK_VertPos );
public     :                                        DPoint MapToCell (const DPoint &rcDPoint, ADK_HoriPos vADK_HoriPos, ADK_VertPos vADK_VertPos );
public     :                                             OContextStyle ( );
public     :                                             OContextStyle (OPersistent bcOPersistent, logical autoOpen, logical separate, logical mouse_tracking, logical hidden, logical disabled, logical checked, logical docking_area, logical accept_drop, int16 displayLevel, int32 distance, DRect bounds, OAlign &align, OLabelDefinition labelPosition, OText textDefinitions, int childDisplayLevel );
public     :                                        const DPoint &Position ( ) const;
protected  : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     :                                        void SetDisplayLevel (int16 dsp_level );
public     :                                        logical SetPosition (const DPoint &rcDPoint );
public     :                                        logical SetSize (const DSize &rcDSize );
public     :                                        const DSize &Size ( ) const;
public     :                                        OText *TextDefinitions ( ) const;
public     :                                        void set_accept_drop (logical drop_opt );
public     : virtual                                     ~OContextStyle ( );
};

#pragma pack()
#endif
