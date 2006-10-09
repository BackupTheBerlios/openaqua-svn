/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    CTX_Base

\brief    General Context Class
          The  general  context  class  is  a base class for all database or GUI
          context  classes. A context  usually defines a  data element or a data
          collection  in its specific context, e.g. children in the context of a
          person  or in a list in a  GUI application. In a context the behaviour
          of  object becomes more specific, which  can be expressed in a context
          class.  Context  classes  have  to  be  defined  in  a  specified form
          according to the type of context to be implemented. 
          Contexts  in an application form a hierarchy, i.e. each context object
          has  either  a  parent  (upper)  context  or  is  a  top context (e.g.
          database or project context). 
          Each  context  has  two  status  properties  which reflect the current
          state  of the context. Since context  classes area created and deleted
          by  the  system  the  current  state  of a context class (as opened or
          closed)  is  not  always  clear  for  the  application programmer. The
          process  state (->  CTX_ProcessState) describes  the the current state
          in  the processing. The display  state (-> CTX_DisplayState) describes
          the  visibility of  the context.  For GUI  context classes this is the
          way  the associated GUI element is presented at the moment on the user
          interface.  State properties are  maintained by the  system but can be
          retrieved by the application. 
          Moreover,  the context  class provides  three user  states that can be
          updated and retrieved by the application. 
          Context  classes  signal  several  events  that  are  relevent for the
          specific  context.  Thus,  context  classes  are  typically  used  for
          handling  system events  as delete  or inserted for database instances
          or  lose/get  focus  for  GUI  contexts.  The  enumeration  of  events
          supported  by a context class is defined in the cpecific context class
          implementation. 
          The  context  class  supports  the  action  interface,  which  enables
          functions  in context  classes calling  actions defined in a reasource
          database or created internally. 
          E

\date     $Date: 2006/08/28 11:57:50,62 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Base_HPP
#define   CTX_Base_HPP
#include "csosdll.h"

class     CTX_Base;

class     CTX_Base;
class     CTX_UCBase;
class     Error;
class     ErrorMessage;
class     NParm;
class     SimpleAction;
class     UCA_Action;
class     UCA_CAction;
class     svel;
#include  <cActionType.h>
#include  <cCTX_DataStates.h>
#include  <cCTX_DisplayState.h>
#include  <cCTX_ProcessState.h>
#include  <cCTX_RequestTypes.h>
#include  <cCTX_Types.h>
#include  <cInternalEvent.h>
#include  <cReplyCombi.h>
#include  <cReplyTypes.h>
#include  <sSystemStates.hpp>
#include  <sUserStates.hpp>
#include  <ssts.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  CTX_Base :public vcls
{
protected  :         CTX_Base                                    *high_ctx;                                                  // Parent context
protected  :         UserStates                                   user_states;                                               // User States
protected  :         SystemStates                                 intern_states;                                             // System states
protected  :         int32                                        action_rc;                                                 // Last action return code
protected  :         NParm                                       *action_parms;                                              // Parameter passed to the action

public     :
                     CTX_Base                                    *get_high_ctx() { return(high_ctx); }
                     UserStates                                  &get_user_states() { return(user_states); }
                     SystemStates                                &get_intern_states() { return(intern_states); }
                     int32                                        get_action_rc() { return(action_rc); }
public     :                  SOSImpExp                  CTX_Base ( );
public     : virtual          SOSImpExp             logical CheckPermission (UCA_Action *actptr );
public     : virtual          SOSImpExp             logical Close ( );
public     : virtual          SOSImpExp             UCA_Action *CreateAction (SimpleAction *action );
public     :                  SOSImpExp             UCA_CAction *CreateCAction (SimpleAction *prehandler, SimpleAction *action, SimpleAction *postandler );
public     :                  SOSImpExp             CTX_DataStates DataState ( );
public     : virtual          SOSImpExp             logical DeleteData ( );
public     :                  SOSImpExp             void Disable ( );
public     : virtual          SOSImpExp             ReplyTypes DisplayDecision (int16 msgnum, ReplyCombi buttons, ReplyTypes def_dec, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL );
public     : virtual          SOSImpExp             void DisplayMessage (int16 w_msgnum=0, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL );
public     :                  SOSImpExp             CTX_DisplayState DisplayState ( );
public     :                  SOSImpExp             void Enable ( );
public     : virtual          SOSImpExp             logical ExecLogin (PropertyHandle *prophdl );
public     : virtual          SOSImpExp             logical ExecuteAction (char *acnames, ActionType actype );
public     : virtual          SOSImpExp             logical ExecuteAction (InternalEvent eventid );
public     : virtual          SOSImpExp             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     : virtual          SOSImpExp             logical ExecuteFunction (char *fname, int16 parmcnt, PropertyHandle **parmlist, PropertyHandle &retfld );
public     :                  SOSImpExp             logical ExecuteProgram (char *prgnams, char *pgmparm1=NULL, char *pgmparm2=NULL, char *pgmparm3=NULL, char *pgmparm4=NULL, char *pgmparm5=NULL );
public     : virtual          SOSImpExp             logical FillData ( );
public     :                  SOSImpExp             logical FindContext (CTX_Base *highctx );
public     : virtual          SOSImpExp             CTX_UCBase *GUIContext ( );
public     : virtual          SOSImpExp             logical GenerateEvent (InternalEvent eventid );
public     :                  SOSImpExp             int32 GetActionResult ( );
public     : virtual          SOSImpExp             CTX_Types GetContextType ( );
public     : virtual          SOSImpExp             logical GetDecision (int16 msgnum, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL );
public     : virtual          SOSImpExp             char *GetMessageString (int16 msgnum, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL );
public     :                  SOSImpExp             logical GetParameters (char **pparm1, char **pparm2=NULL, char **pparm3=NULL, char **pparm4=NULL, char **pparm5=NULL );
public     : virtual          SOSImpExp             char *GetResourceName ( );
public     :                  SOSImpExp             sts &GetSystemStates ( );
public     :                  SOSImpExp             CTX_Base *HighContext (CTX_Types ctxtype=CTXT_undefined );
public     :                  SOSImpExp             CTX_Base *HighContext (char *resname, CTX_Types ctxtype=CTXT_undefined );
public     : virtual          SOSImpExp             logical InitData ( );
public     :                  SOSImpExp             void Initialize (CTX_Base *highctx );
public     : virtual          SOSImpExp             char *Input (char *string );
public     : virtual          SOSImpExp             logical InsertData ( );
public     : virtual          SOSImpExp             logical IsEdit ( );
public     :                  SOSImpExp             logical IsEnabled ( );
public     : virtual          SOSImpExp             logical NextData ( );
public     : virtual          SOSImpExp             logical Open ( );
public     : virtual          SOSImpExp             logical Output (char *string, logical clear_opt=NO, logical flush_opt=YES );
public     :                  SOSImpExp             char *Parm (int32 parm_no );
public     :                  SOSImpExp             char *Parm (char *parm_key );
public     :                  SOSImpExp             char *Parm ( );
public     : virtual          SOSImpExp             logical PreviousData ( );
public     :                  SOSImpExp             CTX_ProcessState ProcessState ( );
public     : virtual          SOSImpExp             logical ResetData ( );
public     : virtual          SOSImpExp             logical SaveData ( );
public     : virtual          SOSImpExp             logical SelectData ( );
public     :                  SOSImpExp             void SetActionResult (int32 rc );
public     :                  SOSImpExp             CTX_DataStates SetDataState (CTX_DataStates datstate );
public     :                  SOSImpExp             CTX_DisplayState SetDisplayState (CTX_DisplayState dspstate );
public     :                  SOSImpExp             logical SetParm (char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                  SOSImpExp             CTX_ProcessState SetProcessState (CTX_ProcessState prcstate );
public     :                  SOSImpExp             void SetRequest (CTX_RequestTypes reqtype );
public     :                  SOSImpExp             int16 SetUserState1 (int16 userstat );
public     :                  SOSImpExp             int16 SetUserState2 (int16 userstat );
public     :                  SOSImpExp             int16 SetUserState3 (int16 userstat );
public     :                  SOSImpExp             logical SetupParm (char separator=',', logical key_parms=NO );
public     : virtual          SOSImpExp             logical StoreData ( );
public     :                  SOSImpExp             int16 UserState1 ( );
public     :                  SOSImpExp             int16 UserState2 ( );
public     :                  SOSImpExp             int16 UserState3 ( );
public     : virtual          SOSImpExp                  ~CTX_Base ( );
public     : virtual          SOSImpExp             PropertyHandle GetDBField (char *fldname_w=NULL ) = 0;
};

#pragma pack()
#endif
