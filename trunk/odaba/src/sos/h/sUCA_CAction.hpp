/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_CAction

\brief    


\date     $Date: 2006/03/12 19:20:21,18 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UCA_CAction_HPP
#define   UCA_CAction_HPP

class     UCA_CAction;

class     CTX_Base;
class     UCA_Action;
#pragma pack(8)

class  UCA_CAction
{
protected  :         UCA_Action                                  *pre_handler;                                               //
protected  :         UCA_Action                                  *action;                                                    //
protected  :         UCA_Action                                  *post_handler;                                              //

public     :
                     UCA_Action                                  *get_pre_handler() { return(pre_handler); }
                     UCA_Action                                  *get_action() { return(action); }
                     UCA_Action                                  *get_post_handler() { return(post_handler); }
public     :         SOS7ImpExp                  logical Execute ( );
public     :         SOS7ImpExp                  logical Execute (CTX_Base *ctxptr );
public     :         SOS7ImpExp                                          UCA_CAction (UCA_Action *pre_action, UCA_Action *cur_action, UCA_Action *post_action );
public     :         SOS7ImpExp                                          UCA_CAction ( );
public     :         SOS7ImpExp                                          ~UCA_CAction ( );
};

#pragma pack()
#endif
