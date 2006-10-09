/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UserStates

\brief    


\date     $Date: 2006/03/12 19:22:03,12 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UserStates"

#include  <pdefault.h>
#include  <sUserStates.hpp>


/******************************************************************************/
/**
\brief  UserStates


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UserStates"

                        UserStates :: UserStates ( )
                     :   state1(UNDEF),
  state2(UNDEF),
  state3(UNDEF)
{

  memset(object_states,0,sizeof(object_states));

}


