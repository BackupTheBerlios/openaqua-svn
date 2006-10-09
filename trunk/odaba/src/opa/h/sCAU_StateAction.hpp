/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CAU_StateAction

\brief    


\date     $Date: 2006/03/12 19:12:23,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_StateAction_HPP
#define   CAU_StateAction_HPP

class     CAU_StateAction;

#ifndef   P_CAU_Description_HPP
#define   P_CAU_Description_HPP
#include  <sPI.hpp>
class       CAU_Description;
PI_dcl     (CAU_Description)
#endif
#ifndef   P_CAU_State_HPP
#define   P_CAU_State_HPP
#include  <sPI.hpp>
class       CAU_State;
PI_dcl     (CAU_State)
#endif
#include  <sCAU_simpleAction.hpp>
#pragma pack(8)

class  CAU_StateAction :public CAU_simpleAction
{
protected  :         PI(CAU_State)                                next_state;                                                //
protected  :         PI(CAU_State)                                pre_state;                                                 //
protected  :         PI(CAU_Description)                          description;                                               //

public     :
                     PI(CAU_State)                               &get_next_state() { return(next_state); }
                     PI(CAU_State)                               &get_pre_state() { return(pre_state); }
                     PI(CAU_Description)                         &get_description() { return(description); }
};

#pragma pack()
#endif
