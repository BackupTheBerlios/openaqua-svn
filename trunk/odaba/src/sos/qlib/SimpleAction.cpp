/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    SimpleAction

\brief    Simple action definition
          A  simple  action  defines  an  action  of  a  given  type. Actions of
          differeent  types  can  be  called  via  context  functions. An action
          provides  an interface to the supported action types. According to the
          action  type the detailled  specification of the  action is defined in
          the ressource database.

\date     $Date: 2006/03/12 19:21:58,68 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SimpleAction"

#include  <pdefault.h>
#include  <sSimpleAction.hpp>


/******************************************************************************/
/**
\brief  SetActionName


\param  acnames - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionName"

void SimpleAction :: SetActionName (char *acnames )
{

  gvtxstb(action_name,acnames,ID_SIZE);

}

/******************************************************************************/
/**
\brief  SetActionType


\param  act_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionType"

void SimpleAction :: SetActionType (ActionType act_type )
{

  action_type = act_type;

}

/******************************************************************************/
/**
\brief  SimpleAction

-------------------------------------------------------------------------------
\brief i0


\param  acnames - Action name
\param  actype - Action type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SimpleAction"

                        SimpleAction :: SimpleAction (char *acnames, ActionType actype )
                     : action_type(actype)
{

  gvtxstb(action_name,acnames,ID_SIZE);

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SimpleAction"

                        SimpleAction :: SimpleAction ( )
                     :  action_type(ACT_undefined)
{

  memset(action_name,' ',ID_SIZE);

}


