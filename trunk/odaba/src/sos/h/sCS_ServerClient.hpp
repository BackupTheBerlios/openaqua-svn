/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_ServerClient

\brief    


\date     $Date: 2006/03/12 19:19:46,75 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_ServerClient_HPP
#define   CS_ServerClient_HPP

class     CS_ServerClient;

class     CS_Message;
class     CS_Server;
#include  <cMachineTypes.h>
#include  <sCS_Connection.hpp>
#pragma pack(8)

class  CS_ServerClient :public CS_Connection
{
protected  :         int16                                        client_ptr_size ATTR_ALIGN(4);                             //
protected  :         MachineTypes                                 client_mtype;                                              //
public     :         CS_Server                                   *server;                                                    

public     :
public     :         SOS7ImpExp                                          CS_ServerClient ( );
public     :                                     logical Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult, logical *pError );
public     :                                     int64 GetClientObject ( );
public     :         SOS7ImpExp                  logical KillClient ( );
public     : virtual SOS7ImpExp                  logical OnExecTerm ( );
public     :         SOS7ImpExp                  void SetCMachineType (MachineTypes mach_type );
public     :         SOS7ImpExp                  void SetCPointerSize (int16 ptr_size );
public     : virtual SOS7ImpExp                                          ~CS_ServerClient ( );
};

#pragma pack()
#endif
