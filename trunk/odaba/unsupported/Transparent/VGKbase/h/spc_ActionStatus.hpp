/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_ActionStatus

\brief    


\date     $Date: 2006/07/21 13:08:48,93 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ActionStatus_HPP
#define   pc_ActionStatus_HPP

class     pc_ActionStatus;

#include  <sPropertyHandle.hpp>
class  pc_ActionStatus :public PropertyHandle
{

public     :
public     :                                        int32 CheckStatus (char *state_string );
public     :                                        int32 CheckStatus (int32 id );
public     :                                        int32 SetStatus (char *state_string );
public     :                                        int32 SetStatus (int32 id );
public     :                                             pc_ActionStatus (PropertyHandle *prophdl );
};

#endif
