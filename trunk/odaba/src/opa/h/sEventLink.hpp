/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EventLink

\brief    Event Link
          This  is a function link object for handling events. The function link
          stores  a pointer to the handler class instance and the function to be
          called.
          The following status indicators are used:
          stsini - handler is active and will be executed

\date     $Date: 2006/03/12 19:13:21,46 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EventLink_HPP
#define   EventLink_HPP

class     EventLink;

class     vcls;
#include  <cDB_Event.h>
#include  <sPropertyHandle.hpp>
#include  <sflnk.hpp>
#pragma pack(8)

class  EventLink :public bsts,
public flnk
{

public     :
public     :                                     void Activate ( );
public     :         opa7ImpExp                  logical Call (CSA_Events event_id, int64 identity, PropertyHandle &prophdl_ref );
public     :         opa7ImpExp                  logical Call (DB_Event intevent );
public     :                                     void Deactivate ( );
public     :         opa7ImpExp                                          EventLink (vcls *vclsptr, EVTP evtptri );
public     :         opa7ImpExp                                          EventLink ( );
public     :         opa7ImpExp                                          EventLink (vcls *vclsptr, EVTPL evtptril );
public     :                                     logical IsActive ( );
public     :         opa7ImpExp                                          ~EventLink ( );
};

#pragma pack()
#endif
