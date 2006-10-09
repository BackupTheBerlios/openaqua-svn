/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TField

\brief    


\date     $Date: 2006/07/17 14:09:03,51 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TField_HPP
#define   TField_HPP

class     TField;

#include  <sGSRT.h>
class     TAction;
class     OCAU_Action;
class     ODataSource;
class     OEventAction;
class     OFieldControl;
class     OFrameStyle;
#include  <cOEH_Frame.h>
#include  <sTActionHandler.hpp>
#include  <sTControl.hpp>
#include  <sTWidgetControl.hpp>
#pragma pack(4)

class  TField :public TWidgetControl
{
protected  :         TActionHandler                               action_hdl;                                                // 

public     :
                     TActionHandler                              &get_action_hdl() { return(action_hdl); }
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                void Close ( );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     :                                        void CreateOutsideLabel ( );
public     :                                        logical DoCreate ( );
public     :                                        logical DoCreated ( );
public     : virtual                                OEH_Frame EventFrame ( );
public     : virtual                                logical SetAction (OEventAction *pOEventAction, OEventAction *parent_action, OEH_Frame event_frame );
public     :                                        logical SetupContextMenu ( );
public     :                                        logical SetupMenu ( );
public     :                                        logical SetupReactions ( );
public     :                                        logical SetupToolbars ( );
public     :                                        void Show (logical fShow );
public     :                                             TField ( );
public     : virtual                                     ~TField ( );
};

#pragma pack()
#endif
