/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OEventAction



\date     $Date: 2006/04/28 16:30:20,15 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEventAction_HPP
#define   OEventAction_HPP

class     OEventAction;

#include  <sDLL.h>
class     OEventAction;
class     OEventAction;
class     PropertyHandle;
class     TWidgetControl;
#include  <cOEH_Frame.h>
#include  <sOEventActionControl.hpp>
class  OEventAction :public OEventActionControl
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OEventAction ( );
public     :                                             OEventAction (OEventActionControl bcOEventActionControl );
public     :                                        logical Read (PropertyHandle *ph );
public     :                                        OEventActionControl *ReadAction (PropertyHandle *ph, char *action_prop );
public     :                                        void Reset ( );
public     :                                        logical SetAction (TWidgetControl *parent_field, OEventAction *parent_action, OEH_Frame event_frame );
public     :                                        logical SetActions (TWidgetControl *parent_field, DLL(OEventAction) *action_list, OEH_Frame event_frame );
public     :                                        void SetupAction ( );
public     :                                             ~OEventAction ( );
};

#endif
