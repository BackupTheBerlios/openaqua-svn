/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_RCT_Path

\brief    Actor path
          The  actor path points to an object or collection of objects, which is
          reacting  on the event. The reaction path  is a sort of bridge between
          the  sender of  the event  and the  receiver. All receivers will react
          with  an  action  with  the  same  name,  but  the  action  might  be 
          implemented differently for different receivers.
          Usually,  the defined  action is  expected in  the property context of
          the  receiver. One may, however, explicitly define, that the action is
          defined  in the structure  context of the  instances referenced by the
          receiver, when the receiver is a reference or relationship.

\date     $Date: 2006/03/13 21:30:06,20 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_RCT_Path_HPP
#define   CAU_RCT_Path_HPP

class     CAU_RCT_Path;

#ifndef   P_CAU_RCT_PathComp_HPP
#define   P_CAU_RCT_PathComp_HPP
#include  <sPI.hpp>
class       CAU_RCT_PathComp;
PI_dcl     (CAU_RCT_PathComp)
#endif
#pragma pack(8)

class  CAU_RCT_Path
{
protected  :         logical                                      struct_event;                                              // Structure context action
protected  :         logical                                      active;                                                    
protected  :         PI(CAU_RCT_PathComp)                         property_path;                                             // Path components to the receiver

public     :
                     logical                                      get_struct_event() { return(struct_event); }
                     logical                                      get_active() { return(active); }
                     PI(CAU_RCT_PathComp)                        &get_property_path() { return(property_path); }
};

#pragma pack()
#endif
