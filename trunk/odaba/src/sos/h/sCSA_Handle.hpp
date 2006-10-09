/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CSA_Handle

\brief    


\date     $Date: 2006/03/12 19:19:40,06 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSA_Handle_HPP
#define   CSA_Handle_HPP

class     CSA_Handle;

#define  CSA_EVENT                                 -1
#define  CSA_MESSAGE                               -2
class     CS_Connection;
class     CS_Message;
#include  <cCSA_Events.h>
#include  <sCS_Handle.hpp>
#pragma pack(8)

class  CSA_Handle :public CS_Handle
{
protected  :         CS_Connection                               *csconnection ATTR_ALIGN(4);                                

public     :
                     CS_Connection                               *get_csconnection() { return(csconnection); }
public     : virtual SOS7ImpExp                  void CSAClose (char *parmstring );
public     : virtual SOS7ImpExp                  void CSAClosed (char *parmstring );
public     : virtual SOS7ImpExp                  void CSACommand (char *parmstring );
public     : virtual SOS7ImpExp                  void CSACreate (char *parmstring );
public     : virtual SOS7ImpExp                  void CSADelete (char *parmstring );
public     : virtual SOS7ImpExp                  void CSADirty (char *parmstring );
public     : virtual SOS7ImpExp                  void CSAInsert (char *parmstring );
public     : virtual SOS7ImpExp                  void CSAOpen (char *parmstring );
public     : virtual SOS7ImpExp                  void CSAOpened (char *parmstring );
public     : virtual SOS7ImpExp                  void CSARemove (char *parmstring );
public     : virtual SOS7ImpExp                  void CSAUpdate (char *parmstring );
public     :         SOS7ImpExp                                          CSA_Handle (CS_Connection *cs_connection );
public     :         SOS7ImpExp                                          CSA_Handle ( );
public     : virtual SOS7ImpExp                  logical ExecuteEvent (uint32 dwServiceFunc, char *parmstring );
public     : virtual SOS7ImpExp                  logical FireEvent (CSA_Events event_id, char *parmstring );
public     :         SOS7ImpExp                  logical GenerateCSEvent (CSA_Events event_id, CS_Message *pParams );
public     :                                     void RunCommand (char *command, char *parmstring );
public     : virtual SOS7ImpExp                                          ~CSA_Handle ( );
};

#pragma pack()
#endif
