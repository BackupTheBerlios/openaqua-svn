/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    SimpleAction

\brief    Simple action definition
          A  simple  action  defines  an  action  of  a  given  type. Actions of
          differeent  types  can  be  called  via  context  functions. An action
          provides  an interface to the supported action types. According to the
          action  type the detailled  specification of the  action is defined in
          the ressource database.

\date     $Date: 2006/03/12 19:20:17,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SimpleAction_HPP
#define   SimpleAction_HPP

class     SimpleAction;

#include  <cActionType.h>
#pragma pack(4)

class  SimpleAction
{
protected  :         char                                         action_name[40];                                           //
protected  :         ActionType                                   action_type;                                               //

public     :
                     char                                        *get_action_name() { return(action_name); }
                     ActionType                                   get_action_type() { return(action_type); }
public     :         SOS7ImpExp                  void SetActionName (char *acnames );
public     :         SOS7ImpExp                  void SetActionType (ActionType act_type );
public     :         SOS7ImpExp                                          SimpleAction (char *acnames, ActionType actype );
public     :         SOS7ImpExp                                          SimpleAction ( );
public     :                                     void set_action_type (ActionType act_type ){

  action_type = act_type;

}

};

#pragma pack()
#endif
