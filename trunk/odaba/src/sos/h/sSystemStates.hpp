/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    SystemStates



\date     $Date: 2006/05/03 13:06:21,50 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SystemStates_HPP
#define   SystemStates_HPP
#include "csosdll.h"

class     SystemStates;

#include  <cCTX_DataStates.h>
#include  <cCTX_DisplayState.h>
#include  <cCTX_ProcessState.h>
#include  <cCTX_RequestTypes.h>
#include  <ssts.hpp>
#pragma pack(8)

class  SystemStates
{
public     :         CTX_DisplayState                             display_state;                                             
public     :         CTX_DataStates                               data_state;                                                
public     :         CTX_ProcessState                             process_state;                                             
public     :         sts                                          sys_sts;                                                   
public     :         char                                         element_stati[14];                                         

public     :
public     :                  SOSImpExp             logical CheckRequest (CTX_RequestTypes reqtype );
public     :                                        void DisableContext ( );
public     :                                        void EnableContext ( );
public     :                  SOSImpExp             void ResetRequest (CTX_RequestTypes reqtype );
public     :                  SOSImpExp             void SetRequest (CTX_RequestTypes reqtype );
public     :                  SOSImpExp                  SystemStates ( )                     :   display_state(DSP_undefined),
  data_state(DAT_undefined),
  process_state(PRC_undefined),
  sys_sts()
{
  memset(element_stati,0,sizeof(element_stati));
}

};

#pragma pack()
#endif
