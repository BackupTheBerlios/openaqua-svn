/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OWinAction



\date     $Date: 2006/04/30 16:21:54,89 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OWinAction_HPP
#define   OWinAction_HPP

class     OWinAction;

class     CTX_GUIBase;
class     OStyleAction;
class     OWindow;
class     PropertyHandle;
class     TWidgetControl;
#include  <sDString.hpp>
#include  <sOAction.hpp>
#pragma pack(4)

class  OWinAction :public OAction
{
protected  :         char                                         window[41];                                                
protected  :         OWindow                                     *win;                                                       

public     :
                     char                                        *get_window() { return(window); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char Execute (CTX_GUIBase *ctxptr );
public     :                                             OWinAction ( );
public     :                                             OWinAction (OAction bcOAction, char *swindow, OWindow *pOWindow );
public     :                                        TWidgetControl *OpenWindow (CTX_GUIBase *ctxptr );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void SetContext (CTX_GUIBase *ctxptr );
public     :                                        void SetEditProperty (char *class_names, char *win_names );
public     :                                        logical SetProperties (char *class_names, char *win_names, logical as_collection, PropertyHandle *prophdl, CTX_GUIBase *ctxptr );
public     : virtual                                     ~OWinAction ( );
};

#pragma pack()
#endif
