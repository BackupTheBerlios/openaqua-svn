/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ProcessEventHandler

\brief    


\date     $Date: 2006/07/18 11:44:05,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ProcessEventHandler_HPP
#define   ProcessEventHandler_HPP

class     ProcessEventHandler;

#define  MAX_EVENTS                                8
class     ACObject;
class     bnode;
#include  <cDB_Event.h>
#include  <sDBEvent.hpp>
#include  <sEventLinkList.hpp>
class  ProcessEventHandler :public EventLinkList
{
protected  :         ACObject                                    *ob_handle;                                                 // 
protected  :         bnode                                       *causer;                                                    // 
protected  :         DB_Event                                     event_cash[8];                                             // 
protected  :         logical                                      registered;                                                // 

public     :
                     ACObject                                    *get_ob_handle() { return(ob_handle); }
                     bnode                                       *get_causer() { return(causer); }
public     :                                        logical EmitEvents (logical emit_opt );
public     :                                        logical GenerateEvent (DB_Event intevent );
public     :                                        void InitCash ( );
public     :                                             ProcessEventHandler (bnode *bnodeptr );
public     :                                        int8 SequenceOption (DB_Event intevent );
public     :                                        void set_causer (bnode *bnodeptr );
public     :                                             ~ProcessEventHandler ( );
};

#endif
