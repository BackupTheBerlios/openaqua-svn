/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    TActionHandler

\brief    


\date     $Date: 2006/03/13 21:32:56,03 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TActionHandler_HPP
#define   TActionHandler_HPP

class     TActionHandler;

#include  <sGSRT.h>
class     TAction;
class     CTX_Control;
class     OCAU_Action;
class     ODataWidget;
#include  <cADK_GUIEVENT.h>
#include  <sDKey.hpp>
#include  <sOEHActionHandler.hpp>
class  TActionHandler :public OEHActionHandler
{
protected  :         GSRT(TAction)                               *actions;                                                   //
protected  :         CTX_Control                                 *context;                                                   //

public     :
                     GSRT(TAction)                               *get_actions() { return(actions); }
                     CTX_Control                                 *get_context() { return(context); }
public     :                                     logical CloseControl ( );
public     : virtual                             int8 ExecuteAction (char *act_names );
public     : virtual                             int32 ExecuteDBEventAction (ADK_DBEVENT ogui_db_event );
public     : virtual                             int32 ExecuteDataEventAction (ADK_DATAEVENT ogui_data_event );
public     :                                     char ExecuteDefaultAction (char *act_names );
public     : virtual                             int32 ExecuteGUIEventAction (ADK_GUIEVENT ogui_event );
public     :                                     logical LoadDynamicControl ( );
public     :                                     int32 ProcessKeyEvent (DKey dkey );
public     :                                     logical SetAction (char *act_names, OCAU_Action *pOCAU_Action );
public     :                                     void SetContext (CTX_Control *ctx_ctl );
public     :                                                             TActionHandler ( );
public     :                                                             ~TActionHandler ( );
};

#endif
