/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBReaction

\brief    


\date     $Date: 2006/03/12 19:13:00,53 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBReaction_HPP
#define   DBReaction_HPP

class     DBReaction;

#ifndef   DPA_DBFieldDef_HPP
#define   DPA_DBFieldDef_HPP
#include  <sDBFieldDef.hpp>
#include  <sDPA.h>
#endif
class     CTX_DBBase;
class     DBStructDef;
class     Dictionary;
class     UCA_CAction;
class     srt;
#include  <cCAU_Delay_Types.h>
#include  <cCAU_RCT_Types.h>
#pragma pack(8)

class  DBReaction
{
protected  :         int32                                        react_id;                                                  
protected  :         CAU_RCT_Types                                type;                                                      
protected  :         DPA(DBFieldDef)                              prop_path;                                                 
protected  :         CAU_Delay_Types                              delay;                                                     
protected  :         UCA_CAction                                 *action;                                                    
protected  :         int16                                        active;                                                    
protected  :         logical                                      struct_event;                                              
protected  :         logical                                      prop_action;                                               

public     :
                     int32                                        get_react_id() { return(react_id); }
                     CAU_RCT_Types                                get_type() { return(type); }
                     DPA(DBFieldDef)                             &get_prop_path() { return(prop_path); }
                     CAU_Delay_Types                              get_delay() { return(delay); }
                     UCA_CAction                                 *get_action() { return(action); }
                     int16                                        get_active() { return(active); }
                     logical                                      get_struct_event() { return(struct_event); }
                     logical                                      get_prop_action() { return(prop_action); }
public     :                                     logical Connect (Dictionary *dictptr );
public     :                                                             DBReaction (int32 rident );
public     :                                     logical Execute (CTX_DBBase *ctxptr );
public     :                                     logical ExecuteInstAct (PropertyHandle *inst_pi, int16 level );
public     :                                     CTX_DBBase *GetActionContext (CTX_DBBase *ctxptr );
public     :                                     CTX_DBBase *GetActiveContext ( );
public     :                                                             ~DBReaction ( );
};

#pragma pack()
#endif
