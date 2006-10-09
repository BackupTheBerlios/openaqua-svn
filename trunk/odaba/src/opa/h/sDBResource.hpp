/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    DBResource



\date     $Date: 2006/05/01 16:28:01,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBResource_HPP
#define   DBResource_HPP

class     DBResource;

#include  <sDPA.h>
class     DBEvent;
#include  <sDPA.h>
class     UCA_CAction;
class     CAU_Causality;
class     CTX_DBBase;
class     DBEvent;
class     DBEventList;
class     Dictionary;
class     UCA_CActionList;
#include  <cDB_Event.h>
#pragma pack(8)

class  DBResource
{
protected  :         int32                                        res_id;                                                    
protected  :         DBEventList                                 *events;                                                    
protected  :         UCA_CActionList                             *action_list;                                               
protected  :         DPA(DBEvent)                                *int_reactions;                                             
protected  :         Dictionary                                  *dictionary;                                                

public     :
                     int32                                        get_res_id() { return(res_id); }
                     DBEventList                                 *get_events() { return(events); }
                     UCA_CActionList                             *get_action_list() { return(action_list); }
                     DPA(DBEvent)                                *get_int_reactions() { return(int_reactions); }
                     Dictionary                                  *get_dictionary() { return(dictionary); }
public     :                                        logical CheckEvent (CTX_DBBase *ctxptr, logical clear_event=NO );
public     :                                        logical ContextRequired ( );
public     :                                             DBResource (Dictionary *dictptr );
public     :                                        logical GenerateEvent (DB_Event intevent, CTX_DBBase *ctxptr );
public     :                                        logical GenerateEvent (char *evtnames, CTX_DBBase *ctxptr );
public     :                                        logical GenerateEvent (DBEvent *dbevent, CTX_DBBase *ctxptr );
public     :                                        logical Initialize (CAU_Causality *causality, int32 resid );
public     :                                        logical Initialize (PropertyHandle &ph );
public     :                                             ~DBResource ( );
};

#pragma pack()
#endif
