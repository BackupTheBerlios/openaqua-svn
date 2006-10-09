/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBEventList

\brief    


\date     $Date: 2006/03/12 19:12:47,70 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBEventList_HPP
#define   DBEventList_HPP

class     DBEventList;

#ifndef   DLL_DBEvent_HPP
#define   DLL_DBEvent_HPP
#include  <sDBEvent.hpp>
#include  <sDLL.h>
#endif
class     CTX_DBBase;
class     DBEvent;
#pragma pack(8)

class  DBEventList :public DLL(DBEvent)
{
protected  :         logical                                      user_events ATTR_ALIGN(4);                                 

public     :
                     logical                                      get_user_events() { return(user_events); }
public     :                                     logical Append (DBEvent *evtptr );
public     :                                     logical Check (CTX_DBBase *ctxptr, logical clear_event=NO );
public     :                                                             DBEventList ( );
public     :                                     DBEvent *Search (char *evtnames );
public     :                                                             ~DBEventList ( );
};

#pragma pack()
#endif
