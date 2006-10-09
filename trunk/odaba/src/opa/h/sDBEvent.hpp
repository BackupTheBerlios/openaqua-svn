/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    DBEvent

\brief    


\date     $Date: 2006/04/07 13:28:45,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBEvent_HPP
#define   DBEvent_HPP

class     DBEvent;

#include  <sDLL.h>
class     DBReaction;
class     CAU_Event;
class     CAU_simpleAction;
class     CTX_DBBase;
class     UCA_Action;
#include  <cDB_Event.h>
#pragma pack(8)

class  DBEvent
{
protected  :         char                                         name[40];                                                  
protected  :         UCA_Action                                  *pre_condition;                                             
protected  :         logical                                      pre_cond_true;                                             
protected  :         UCA_Action                                  *post_condition;                                            
protected  :         DB_Event                                     int_event;                                                 
protected  :         DLL(DBReaction)                             *reactions;                                                 

public     :
                     char                                        *get_name() { return(name); }
                     UCA_Action                                  *get_pre_condition() { return(pre_condition); }
                     logical                                      get_pre_cond_true() { return(pre_cond_true); }
                     UCA_Action                                  *get_post_condition() { return(post_condition); }
                     DB_Event                                     get_int_event() { return(int_event); }
                     DLL(DBReaction)                             *get_reactions() { return(reactions); }
public     :                                     logical CheckEvent (CTX_DBBase *ctxptr, logical clear_event=NO );
public     :                                     UCA_Action *CreateCondition (CAU_simpleAction *simplact, CTX_DBBase *ctxptr );
public     :                                                             DBEvent (CAU_Event *cauevt_ptr, CTX_DBBase *ctxptr );
public     :                                                             DBEvent (PropertyHandle &ph, CTX_DBBase *ctxptr );
public     :                                                             DBEvent ( );
public     :                                                             ~DBEvent ( );
};

#pragma pack()
#endif
