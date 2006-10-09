/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CAU_State

\brief    


\date     $Date: 2006/03/12 19:12:23,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_State_HPP
#define   CAU_State_HPP

class     CAU_State;

#ifndef   P_CAU_Description_HPP
#define   P_CAU_Description_HPP
#include  <sPI.hpp>
class       CAU_Description;
PI_dcl     (CAU_Description)
#endif
#ifndef   P_CAU_StateAction_HPP
#define   P_CAU_StateAction_HPP
#include  <sPI.hpp>
class       CAU_StateAction;
PI_dcl     (CAU_StateAction)
#endif
class     CTX_Base;
class     CTX_DBBase;
class     fnc;
#pragma pack(8)

class  CAU_State
{
protected  :         char                                         sys_ident[40];                                             //
protected  :         fnc                                         *state_context;                                             //
protected  :         logical                                      seriell;                                                   //
protected  :         logical                                      concurrent;                                                //
protected  :         PI(CAU_Description)                          description;                                               //
protected  :         PI(CAU_StateAction)                          actions;                                                   
protected  :         PI(CAU_StateAction)                          pre_actions;                                               

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     fnc                                         *get_state_context() { return(state_context); }
                     logical                                      get_seriell() { return(seriell); }
                     logical                                      get_concurrent() { return(concurrent); }
                     PI(CAU_Description)                         &get_description() { return(description); }
                     PI(CAU_StateAction)                         &get_actions() { return(actions); }
                     PI(CAU_StateAction)                         &get_pre_actions() { return(pre_actions); }
public     :                                     logical ExecuteCAction ( );
public     :                                     logical SetContext (CTX_DBBase *ctxptr );
public     :                                     logical SetContext (fnc *fncptr );
};

#pragma pack()
#endif
