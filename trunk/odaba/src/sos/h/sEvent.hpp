/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    Event

\brief    


\date     $Date: 2006/03/12 19:19:59,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Event_HPP
#define   Event_HPP

class     Event;

#pragma pack(8)

class  Event
{
protected  :         HANDLE                                       event_object;                                              

public     :
public     :         SOS7ImpExp                                          Event ( );
public     :         SOS7ImpExp                  logical Reset ( );
public     :         SOS7ImpExp                  logical Set ( );
public     :         SOS7ImpExp                  logical WaitForSet (int32 timeout );
public     :         SOS7ImpExp                                          ~Event ( );
};

#pragma pack()
#endif
