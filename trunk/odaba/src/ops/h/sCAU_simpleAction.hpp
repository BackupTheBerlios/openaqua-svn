/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_simpleAction

\brief    Simple action
          A  simple action defines an action  outside of any specific context by
          name  and action type. Simple actions must be defined as method in the
          context  where  they  are  defined  (e.g. in the structure or property
          context  when defining a structure or  property action). The method an
          action  is  referring  to,  may  have  different  types  as  function,
          expression etc.

\date     $Date: 2006/03/13 21:30:06,40 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_simpleAction_HPP
#define   CAU_simpleAction_HPP

class     CAU_simpleAction;

#include  <cActionType.h>
#pragma pack(8)

class  CAU_simpleAction
{
protected  :         char                                         sys_ident[40];                                             // Method name
protected  :         ActionType                                   action_type;                                               // Action types

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     ActionType                                   get_action_type() { return(action_type); }
public     :         OPS7ImpExp                                          CAU_simpleAction (char *actnames, ActionType acttyp );
public     :         OPS7ImpExp                                          CAU_simpleAction ( );
public     :         OPS7ImpExp                  void set_action_type (ActionType acttyp ){

  action_type = acttyp;

}

};

#pragma pack()
#endif
