/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OCAU_SimpleAction



\date     $Date: 2006/04/28 16:58:21,96 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OCAU_SimpleAction_HPP
#define   OCAU_SimpleAction_HPP

class     OCAU_SimpleAction;

class     CTX_GUIBase;
class     OAction;
class     PropertyHandle;
class     TComponent;
#include  <cActionType.h>
#include  <sOResource.hpp>
#pragma pack(4)

class  OCAU_SimpleAction :public OResource
{
protected  :         ActionType                                   actionType;                                                
protected  :         OAction                                     *action;                                                    
protected  :         TComponent                                  *current_component;                                         

public     :
                     ActionType                                   get_actionType() { return(actionType); }
                     OAction                                     *get_action() { return(action); }
                     TComponent                                  *get_current_component() { return(current_component); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        char Execute (CTX_GUIBase *ctxptr );
public     :                                        logical IsEmpty ( ) const;
public     :                                             OCAU_SimpleAction ( );
public     :                                             OCAU_SimpleAction (OResource bcOResource, int32 actionType, OAction *pOAction );
public     :                                        logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        logical SetAction (char *act_names, ActionType vActionType );
public     :                                        void SetCurrentComponent (TComponent *pTComponent );
public     :                                        void set_actionType (ActionType act_type );
public     : virtual                                     ~OCAU_SimpleAction ( );
};

#pragma pack()
#endif
