/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UserStates

\brief    


\date     $Date: 2006/03/12 19:20:21,78 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UserStates_HPP
#define   UserStates_HPP

class     UserStates;

#pragma pack(8)

class  UserStates
{
public     :         int16                                        state1;                                                    
public     :         int16                                        state2;                                                    
public     :         int16                                        state3;                                                    
public     :         char                                         object_states[16];                                         

public     :
public     :                                                             UserStates ( );
};

#pragma pack()
#endif
