/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/03/13 21:30:17,87 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_RCT_Path"

#include  <pops7.h>
#include  <sCAU_RCT_Path.hpp>



