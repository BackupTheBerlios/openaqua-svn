/********************************* Class Declaration ***************************/
/**
\package  ODCP - 
\class    CTX_GUIBase

\brief    GUI base context class
          This  class is the base class for GUI context functions. It contains a
          number  of pre- and  post-action handlers, which  can be overloaded by
          appropriate  context functions.  Pre event  handlers are called at the
          beginning  of an event  reaction. Post handlers  are called at the end
          ov  an  reaction.  Context  actions  are  the  consequence from events
          raised in the application or can be executed directly.

\date     $Date: 2006/06/21 15:37:06,78 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_GUIBase_HPP
#define   CTX_GUIBase_HPP

class     CTX_GUIBase;

#define  POINTER_Arrow                             0
#define  POINTER_Wait                              1
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     CTX_Control;
class     CTX_GUIBase;
class     CTX_Project;
class     TWidgetControl;
#include  <cCTX_Types.h>
#include  <sCTX_Base.hpp>
#include  <sNString.hpp>
class  CTX_GUIBase :public CTX_Base
{
protected  :         TWidgetControl                              *control;                                                   // 
protected  :         NString                                      nstring;                                                   // 

public     :
                     TWidgetControl                              *get_control() { return(control); }
                     NString                                     &get_nstring() { return(nstring); }
public     :                  ODCPImpExp            CTX_Control *AddInputHelp (PropertyHandle *prophdl, char *class_name, char *ctnames, VECTOR(std_string) &activate_strings );
public     :                                        void Beep ( );
public     :                                             CTX_GUIBase ( );
public     :                  ODCPImpExp            logical CheckResult (char *string );
public     :                  ODCPImpExp            void DisplayMessage (int msgnum_w=UNDEF, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     : virtual          ODCPImpExp            int8 DoAfterChangeSelection ( );
public     : virtual          ODCPImpExp            int8 DoAfterClearData ( );
public     : virtual          ODCPImpExp            int8 DoAfterDataSet ( );
public     : virtual          ODCPImpExp            int8 DoAfterDeleteData ( );
public     : virtual          ODCPImpExp            int8 DoAfterDock ( );
public     : virtual          ODCPImpExp            int8 DoAfterDrag ( );
public     : virtual          ODCPImpExp            int8 DoAfterDrop ( );
public     : virtual          ODCPImpExp            int8 DoAfterEnter ( );
public     : virtual          ODCPImpExp            int8 DoAfterFillData ( );
public     : virtual          ODCPImpExp            int8 DoAfterHandleActivated ( );
public     : virtual          ODCPImpExp            int8 DoAfterHandleOpen ( );
public     : virtual          ODCPImpExp            int8 DoAfterHide ( );
public     : virtual          ODCPImpExp            int8 DoAfterInitializeData ( );
public     : virtual          ODCPImpExp            int8 DoAfterInsertData ( );
public     : virtual          ODCPImpExp            int8 DoAfterKeyInput ( );
public     : virtual          ODCPImpExp            int8 DoAfterMouseMove ( );
public     : virtual          ODCPImpExp            int8 DoAfterOpen ( );
public     : virtual          ODCPImpExp            int8 DoAfterSaveData ( );
public     : virtual          ODCPImpExp            int8 DoAfterSelect ( );
public     : virtual          ODCPImpExp            int8 DoAfterShow ( );
public     : virtual          ODCPImpExp            int8 DoAfterStoreData ( );
public     : virtual          ODCPImpExp            int8 DoAfterUndock ( );
public     : virtual          ODCPImpExp            int8 DoAfterUpdateCollection ( );
public     : virtual          ODCPImpExp            int8 DoAfterUpdateInstance ( );
public     : virtual          ODCPImpExp            int8 DoBeforeClose ( );
public     : virtual          ODCPImpExp            int8 DoBeforeDataSet ( );
public     : virtual          ODCPImpExp            int8 DoBeforeDeleteData ( );
public     : virtual          ODCPImpExp            int8 DoBeforeDrag ( );
public     : virtual          ODCPImpExp            int8 DoBeforeDrop ( );
public     : virtual          ODCPImpExp            int8 DoBeforeFillData ( );
public     : virtual          ODCPImpExp            int8 DoBeforeInitializeData ( );
public     : virtual          ODCPImpExp            int8 DoBeforeInsertData ( );
public     : virtual          ODCPImpExp            int8 DoBeforeLeave ( );
public     : virtual          ODCPImpExp            int8 DoBeforeOpen ( );
public     : virtual          ODCPImpExp            int8 DoBeforeSaveData ( );
public     : virtual          ODCPImpExp            int8 DoBeforeSelect ( );
public     : virtual          ODCPImpExp            int8 DoBeforeStoreData ( );
public     : virtual          ODCPImpExp            int8 DoValidateData ( );
public     :                  ODCPImpExp            logical EnableInputHelp (logical enable_opt );
public     :                  ODCPImpExp            logical ExecuteAction (char *actnames, int16 actype );
public     : virtual          ODCPImpExp            logical ExecuteFunction (char *fnames, logical chk_opt=NO );
public     :                  ODCPImpExp            logical ExecuteWindow (PropertyHandle *prophdl, char *class_name, char *wnames, logical as_collection_w=NO );
public     :                  ODCPImpExp            logical Exit ( );
public     :                  ODCPImpExp            void FlushGUI ( );
public     :                  ODCPImpExp            CTX_Control *GetControlContext ( );
public     :                  ODCPImpExp            DatabaseHandle &GetDATDB ( );
public     : virtual          ODCPImpExp            PropertyHandle GetDBField (char *prop_names );
public     :                  ODCPImpExp            DatabaseHandle &GetDBHandle ( );
public     :                                        logical GetDecision (int msgnum, int button0, int button1, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                  ODCPImpExp            logical GetDecisionOk (int msgnum, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                  ODCPImpExp            logical GetDecisionYes (int msgnum, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                  ODCPImpExp            DictionaryHandle &GetDictionary ( );
public     :                  ODCPImpExp            CTX_GUIBase *GetHighContext (CTX_Types ctxtype=CTXT_undefined );
public     :                  ODCPImpExp            CTX_GUIBase *GetHighContext (char *res_names );
public     :                  ODCPImpExp            PropertyHandle *GetInitPropertyHandle ( );
public     :                  ODCPImpExp            CTX_Project *GetProjectContext (CTX_Types ctxtype=CTXT_undefined );
public     : virtual          ODCPImpExp            PropertyHandle *GetPropertyHandle ( );
public     : virtual          ODCPImpExp            PropertyHandle *GetPropertyHandle (char *prop_names );
public     :                  ODCPImpExp            DatabaseHandle &GetRESDB ( );
public     :                  ODCPImpExp            DictionaryHandle &GetRESDictionary ( );
public     :                  ODCPImpExp            DBObjectHandle &GetRESObject ( );
public     :                  ODCPImpExp            DatabaseHandle &GetResourceDB ( );
public     :                  ODCPImpExp            char *GetResult ( );
public     :                  ODCPImpExp            DictionaryHandle &GetWorkDictionary ( );
public     :                  ODCPImpExp            logical InvalidateDesignerCache ( );
public     :                  ODCPImpExp            logical InvalidateResourceCache ( );
public     : virtual          ODCPImpExp            logical IsActionDisabled (char *actnames, char *act_id=NULL );
public     :                  ODCPImpExp            logical IsUserContext ( );
public     :                  ODCPImpExp            void Pointer (logical wait_opt );
public     :                  ODCPImpExp            logical ReleaseResourceDictionary ( );
public     :                  ODCPImpExp            DictionaryHandle &ReserveResourceDictionary ( );
public     :                  ODCPImpExp            void ResetWorkDictionary ( );
public     :                  ODCPImpExp            void SetResult (char *result_string );
public     :                  ODCPImpExp            logical WaitForExecute (char *wait_file, int msgnum, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL );
public     :                                        void set_control (TWidgetControl *ctlptr );
public     :                                        void set_user_context (logical user_opt );
public     : virtual          ODCPImpExp                 ~CTX_GUIBase ( );
};

#endif
