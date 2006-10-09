/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OWidgetStack

\brief    


\date     $Date: 2006/07/13 10:51:03,71 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWidgetStack_HPP
#define   OWidgetStack_HPP

class     OWidgetStack;

#ifndef   DLL_ODataWidget_HPP
#define   DLL_ODataWidget_HPP
#include  <sODataWidget.hpp>
#include  <sDLL.h>
#endif
class     DBStructDef;
class     ODS;
class     ODTabControl;
class     PropertyHandle;
#include  <sODataWidget.hpp>
class  OWidgetStack :public QStackedWidget,
public ODataWidget
{
protected  :         DLL(ODataWidget)                             children;                                                  // 

public     :
                     DLL(ODataWidget)                            &get_children() { return(children); }
public     :                                        logical ActivateODChildren (ODataWidget *child, PropertyHandle *prophdl );
public     :                                        logical ActivateODChildren (char *typenames );
public     :                                        logical ActivateODChildren (DBStructDef *struct_def );
public     :                                        logical AddChild (ODataWidget *child, int32 tab_index );
public     : virtual                                QFrame *FrameQ ( );
public     :                                        ODataWidget *GetChild (char *typenames );
public     :                                        ODataWidget *GetChild (int16 dsp_level );
public     :                                        ODTabControl *GetODTabControl ( );
public     :                                             OWidgetStack (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                             OWidgetStack (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                        logical SetDisplayLevel (int32 tab_index );
public     :                                        int16 SetTypeLevel (PropertyHandle *prophdl );
public     :                                        int16 SetTypeLevel (char *typenames );
public     :                                        int16 SetTypeLevel (DBStructDef *struct_def );
public     : virtual                                QWidget *WidgetQ ( );
public     : virtual                                     ~OWidgetStack ( );
};

#endif
