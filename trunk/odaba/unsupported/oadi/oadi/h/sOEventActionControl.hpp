/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OEventActionControl



\date     $Date: 2006/04/28 16:37:30,14 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEventActionControl_HPP
#define   OEventActionControl_HPP

class     OEventActionControl;

#include  <sDLL.h>
class     OEventAction;
class     OCBitmap;
class     OEventActionControl;
class     OField;
class     PropertyHandle;
#include  <cEventActionType.h>
#include  <sOEventAction_intern.hpp>
#pragma pack(4)

class  OEventActionControl :public OEventAction_intern
{
protected  :         EventActionType                              type;                                                      
protected  :         OField                                      *action_field;                                              
protected  :         DLL(OEventAction)                           *group_actions;                                             
protected  :         DLL(OEventAction)                           *sub_actions;                                               

public     :
                     EventActionType                              get_type() { return(type); }
                     OField                                      *get_action_field() { return(action_field); }
                     DLL(OEventAction)                           *get_group_actions() { return(group_actions); }
                     DLL(OEventAction)                           *get_sub_actions() { return(sub_actions); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        OEventActionControl *GroupItem (int index );
public     :                                        OEventActionControl *ListItem (int index );
public     :                                             OEventActionControl ( );
public     :                                             OEventActionControl (OEventAction_intern bcOEventAction_intern, int16 iEAType, OField *pOField, DLL(OEventAction) *pOEventActions, DLL(OEventAction) *pOSubEventActions );
public     :                                        logical Read (PropertyHandle *ph );
public     :                                        logical ReadAction (PropertyHandle *ph, char *action_prop );
public     :                                        logical ReadActions (PropertyHandle *ph, DLL(OEventAction) **p_action_list );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OEventActionControl ( );
};

#pragma pack()
#endif
