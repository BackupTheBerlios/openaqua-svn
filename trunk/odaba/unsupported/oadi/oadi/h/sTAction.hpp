/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    TAction

\brief    


\date     $Date: 2006/03/13 21:32:55,89 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TAction_HPP
#define   TAction_HPP

class     TAction;

#define  TACTION_KEYLEN                            40
class     CTX_GUIBase;
#include  <sOCAU_Action.hpp>
class  TAction
{
protected  :         char                                         sys_ident[40];                                             //
protected  :         OCAU_Action                                 *action;                                                    //

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     OCAU_Action                                 *get_action() { return(action); }
public     :                                     char Execute (CTX_GUIBase *ctxptr );
public     :                                     ActionType GetActionType ( );
public     :                                                             TAction (char *act_names, OCAU_Action *pOCAU_Action );
};

#endif
