/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OWidget

\brief    


\date     $Date: 2006/07/24 20:32:51,20 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWidget_HPP
#define   OWidget_HPP

class     OWidget;

class     ODataWidget;
class     OWidgetDesignMode;
class     OWidgetDesignModeBase;
class     OWidgetDesignModeFactory;
#include  <cADK_SizeType.h>
#include  <sDColor.hpp>
#include  <sDFont.hpp>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
#pragma pack(4)

class  OWidget
{
protected  :         logical                                      enabled;                                                   // 
protected  :         logical                                      readOnly;                                                  // 
protected  :         logical                                      has_edit;                                                  // 
protected  :         int8                                         in_design_mode;                                            // 
public     :         OWidgetDesignModeBase                       *design_mode;                                               // 
protected  :         logical                                      test_record_mode;                                          // 
protected  :         logical                                      visible;                                                   // 
protected  :         logical                                      is_destroying;                                             // 

public     :
                     logical                                      get_enabled() { return(enabled); }
                     logical                                      get_readOnly() { return(readOnly); }
                     logical                                      get_has_edit() { return(has_edit); }
                     int8                                         get_in_design_mode() { return(in_design_mode); }
                     logical                                      get_visible() { return(visible); }
                     logical                                      get_is_destroying() { return(is_destroying); }
public     :                                        void ActivateDesignMode (logical fDmode );
public     : virtual          OGUIImpExp            void DisableDesignMode ( );
public     : virtual          OGUIImpExp            OWidgetDesignModeBase *EnableDesignMode (OWidgetDesignModeFactory *dmode_factory=NULL );
public     :                  OGUIImpExp            logical EnableTestRecordMode ( );
public     : virtual          OGUIImpExp            DColor GetBackgroundColor ( );
public     : virtual                                ODataWidget *GetDataWidget ( );
public     :                  OGUIImpExp            int GetDecision (char *title_text, char *text, int button0, int button1, int button2 );
public     :                  OGUIImpExp            OWidgetDesignModeBase *GetDesignMode ( );
public     : virtual          OGUIImpExp            DFont GetFont ( );
public     : virtual          OGUIImpExp            DColor GetForegroundColor ( );
public     : static                                 QSizePolicy::Policy __cdecl GetMaxQSizeType (QSizePolicy::Policy qSizeType, ADK_SizeType size_policy );
public     :                  OGUIImpExp            char *GetName ( );
public     : virtual          OGUIImpExp            DPoint GetPosition ( );
public     : static                                 QSizePolicy::Policy __cdecl GetQSizeType (ADK_SizeType size_policy );
public     :                                        DSize GetSize ( );
public     :                  OGUIImpExp            logical HasEdit ( );
public     :                  OGUIImpExp            logical HasFocus ( );
public     :                  OGUIImpExp            logical InDesignMode ( );
public     :                  OGUIImpExp            logical IsEnabled ( );
public     : virtual          OGUIImpExp            logical IsInDesignMode ( );
public     :                                        logical IsInTestRecordMode ( );
public     :                  OGUIImpExp            logical IsReadOnly ( );
public     :                                        DPoint Move (const DPoint &rcDPoint );
public     :                                        DPoint Move (int x, int y );
public     :                  OGUIImpExp                 OWidget ( );
public     : virtual                                OWidget *Parent ( );
public     :                                        logical RecordTest (QObject *pQObject, QEvent *pQEvent );
public     :                  OGUIImpExp            void SetBackgroundColor (DColor &rDColor );
public     : virtual          OGUIImpExp            void SetEnabled (logical fEnabled );
public     :                                        logical SetFocus ( );
public     : virtual          OGUIImpExp            void SetFont (DFont &rDFont );
public     : virtual          OGUIImpExp            void SetPosition (const DPoint &rcDPoint );
public     : virtual          OGUIImpExp            void SetPosition (int x, int y );
public     :                  OGUIImpExp            void SetReadOnly (logical fReadOnly );
public     : virtual          OGUIImpExp            void SetSize (const DSize &rcDSize );
public     : virtual          OGUIImpExp            void SetSize (int x, int y );
public     :                  OGUIImpExp            void SetTextColor (DColor &rDColor );
public     : virtual          OGUIImpExp            void SetToggleMode (logical fEnabled );
public     : virtual          OGUIImpExp            void SetVisible (logical fEnabled );
public     :                                        logical SetWidgetBusy (bool toggle=FALSE );
protected  :                  OGUIImpExp            void UpdateEnabled ( );
protected  : virtual          OGUIImpExp            void UpdateReadOnly (logical fReadOnly );
protected  :                  OGUIImpExp            void UpdateState ( );
public     : virtual          OGUIImpExp            QWidget *WidgetQ ( );
protected  : virtual          OGUIImpExp            logical getEnabled ( );
public     : virtual          OGUIImpExp                 ~OWidget ( );
};

#pragma pack()
#endif
