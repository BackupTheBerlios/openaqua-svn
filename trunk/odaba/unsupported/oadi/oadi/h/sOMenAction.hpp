/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OMenAction



\date     $Date: 2006/04/30 16:13:33,75 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OMenAction_HPP
#define   OMenAction_HPP

class     OMenAction;

class     CTX_GUIBase;
class     OEventAction;
class     PropertyHandle;
#include  <sOAction.hpp>
#include  <sOContextStyle.hpp>
class  OMenAction :public OAction,
public OContextStyle
{
protected  :         OEventAction                                *menu;                                                      
protected  :         logical                                      contextMenu;                                               

public     :
                     logical                                      get_contextMenu() { return(contextMenu); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        char Execute (CTX_GUIBase *ctxptr );
public     :                                             OMenAction ( );
public     :                                             OMenAction (OAction bcOAction, OContextStyle bcOContextStyle, OEventAction *pOEventAction, logical is_context_menu );
public     :                                        logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     :                                        void SetContextMenuProperty ( );
public     :                                             ~OMenAction ( );
};

#endif
