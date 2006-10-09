/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/07/05 14:04:31,74 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_GUIBase"

#include  <podcp8.h>
#include  <cqt.h>
#include  <ifil.h>
#include  <ioadii.h>
#include  <stdinc.h>
#include  <sCTX_Control.hpp>
#include  <sCTX_GUIBase.hpp>
#include  <sCTX_Project.hpp>
#include  <sTProjectManager.hpp>
#include  <sTWidgetControl.hpp>
#include  <iigui.h>
#include  <sCTX_GUIBase.hpp>


/******************************************************************************/
/**
\brief  AddInputHelp - 



\return ctxptr - 

\param  prophdl - 
\param  class_name - 
\param  ctnames - 
\param  activate_strings - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInputHelp"

CTX_Control *CTX_GUIBase :: AddInputHelp (PropertyHandle *prophdl, char *class_name, char *ctnames, VECTOR(std_string) &activate_strings )
{

  return (   this 
           ? control->AddInputHelp(class_name,ctnames,activate_strings,prophdl) 
           : NULL);

}

/******************************************************************************/
/**
\brief  Beep - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Beep"

void CTX_GUIBase :: Beep ( )
{

  TProjectManager::TPM->Beep();


}

/******************************************************************************/
/**
\brief  CTX_GUIBase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_GUIBase"

     CTX_GUIBase :: CTX_GUIBase ( )
                     : CTX_Base (),
  control(NULL),
  nstring()
{

  set_user_context(YES);

}

/******************************************************************************/
/**
\brief  CheckResult - 



\return cond - 

\param  string - 0-terminated string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckResult"

logical CTX_GUIBase :: CheckResult (char *string )
{

  return ( nstring == string ? YES : NO );

}

/******************************************************************************/
/**
\brief  DisplayMessage - 




\param  msgnum_w - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

void CTX_GUIBase :: DisplayMessage (int msgnum_w, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{

  if ( msgnum_w )
    P_ISET(msgnum_w);

  if ( parm1 )
    P_SETEV1(parm1,UNDEF);
  if ( parm2 )
    P_SETEV2(parm2,UNDEF);
  if ( parm3 )
    P_SETEV3(parm3,UNDEF);
  if ( parm4 )
    P_SETEV4(parm4,UNDEF);
  if ( parm5 )
    P_SETEV5(parm5,UNDEF);

//  adcappl->adcaepws(GetWindow());
  P_Error().DisplayMessage();


}

/******************************************************************************/
/**
\brief  DoAfterChangeSelection - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterChangeSelection"

int8 CTX_GUIBase :: DoAfterChangeSelection ( )
{

  return(AUTO);

// *fixme* wird nicht mehr erzeugt
//         stattdessen waere moeglich: DoBeforeInstanceUnselect ?
//                                     DoAfterInstanceSelected  ?

}

/******************************************************************************/
/**
\brief  DoAfterClearData - Pre-event handler for initialize data events

        The  pre-event handler for an initialize  data event allows providing or
        modifying  the key or data  for the new instance  to be created. The new
        instance can be provided by calling GetInitPropertyHandle().
        The  pre-event  handler  is  called  before the key dialogue pops up. By
        setting  or  removing  the  key  value  for the instance the handler may
        control, whether the dialogue is supressed or displayed. 
        The insert/create action can be cancelled by returning an error (YES).

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterClearData"

int8 CTX_GUIBase :: DoAfterClearData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterDataSet - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDataSet"

int8 CTX_GUIBase :: DoAfterDataSet ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterDeleteData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDeleteData"

int8 CTX_GUIBase :: DoAfterDeleteData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterDock - Post-event handler for Docking events

        The  event is signaled,  when a doccing  window is docked ti its docking
        area.

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDock"

int8 CTX_GUIBase :: DoAfterDock ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterDrag - Post-event handler for Drag events

        The  post-event handler  for drag  events allows manipulating the object
        stored  in the  drag buffer.  The handler  may access information in the
        drop     object     using     functions     as     GetDropText()     or 
        GetDropPropertyHandle().
        The  handler is called,  only, when the  darg event has been accepted by
        the pre-event.

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDrag"

int8 CTX_GUIBase :: DoAfterDrag ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterDrop - Post-event handler for Drop events

        The  post-event  handler  for  drop  events  allows handling the updated
        instance  for a drop  event. The handler  is called, only, when the drop
        event  has been  accepted by  the pre-event.  Information about the drag
        object are not available anymore.

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDrop"

int8 CTX_GUIBase :: DoAfterDrop ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterEnter - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterEnter"

int8 CTX_GUIBase :: DoAfterEnter ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterFillData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterFillData"

int8 CTX_GUIBase :: DoAfterFillData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterHandleActivated - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleActivated"

int8 CTX_GUIBase :: DoAfterHandleActivated ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterHandleOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleOpen"

int8 CTX_GUIBase :: DoAfterHandleOpen ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterHide - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHide"

int8 CTX_GUIBase :: DoAfterHide ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterInitializeData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInitializeData"

int8 CTX_GUIBase :: DoAfterInitializeData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterInsertData - Post-event handler for insert data events

        The  post-event handler for initialize  events allows modifying the data
        for  the instance created. The instance can be made available by calling
        GetCurrentPropertyHandle().   When   modifying   instance   data   it is
        suggested  to save the  instance (PropertyHandle::Save()) before leaving
        the handler.

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInsertData"

int8 CTX_GUIBase :: DoAfterInsertData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterKeyInput - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterKeyInput"

int8 CTX_GUIBase :: DoAfterKeyInput ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterMouseMove - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterMouseMove"

int8 CTX_GUIBase :: DoAfterMouseMove ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 CTX_GUIBase :: DoAfterOpen ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterSaveData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSaveData"

int8 CTX_GUIBase :: DoAfterSaveData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterSelect - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 CTX_GUIBase :: DoAfterSelect ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterShow - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterShow"

int8 CTX_GUIBase :: DoAfterShow ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterStoreData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterStoreData"

int8 CTX_GUIBase :: DoAfterStoreData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterUndock - Post-event handler for Undocking events

        The  event  is  signaled,  when  a  doccing  window is undocked from its
        docking area.

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterUndock"

int8 CTX_GUIBase :: DoAfterUndock ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterUpdateCollection - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterUpdateCollection"

int8 CTX_GUIBase :: DoAfterUpdateCollection ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoAfterUpdateInstance - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterUpdateInstance"

int8 CTX_GUIBase :: DoAfterUpdateInstance ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeClose - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

int8 CTX_GUIBase :: DoBeforeClose ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeDataSet - Data select handler

        The  handler allows filtering items in a list. The handler is called for
        each  item in  the list.  The selected  item is available in the current
        property  handle  (GetCurrentPropertyHandle()).  For  accepting an item,
        the Function should return NO. Items not accespted return YES (error). 
        For  activating  the  handler,  selection  must  be  set  for  the  list
        (SetSelection()) when the control has been opened (DoAfterOpen()).

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDataSet"

int8 CTX_GUIBase :: DoBeforeDataSet ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeDeleteData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDeleteData"

int8 CTX_GUIBase :: DoBeforeDeleteData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeDrag - Pre-event handler for Drag events

        The  handler function is called before the drag action will be executed.
        The drag action can be cancelled by returning an error (YES).

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDrag"

int8 CTX_GUIBase :: DoBeforeDrag ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeDrop - Pre-event handler for Drop events

        The  handler function is called befor  the drop action will be executed.
        The  handler may access  information in the  drop object using functions
        as  GetDropText() or  GetDropPropertyHandle(). GetVerticalDropPosition()
        and  GetHorizontalDropPosition()  will  return  the  position  where the
        object is going to be dropped.
        The drop action can be refused by returning an error (YES).

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDrop"

int8 CTX_GUIBase :: DoBeforeDrop ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeFillData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 CTX_GUIBase :: DoBeforeFillData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeInitializeData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeInitializeData"

int8 CTX_GUIBase :: DoBeforeInitializeData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeInsertData - Pre-event handler for insert data events

        The  pre-event handler for an initialize data event allows modifying the
        key  or data for the new instance to be created. Standard initialization
        provides  the key value for the instance to be created. The new instance
        can  be provided by calling  GetInitPropertyHandle(). You may initialize
        other instance fields before the instance is added to a collection.
        The insert/create action can be cancelled by returning an error (YES).

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeInsertData"

int8 CTX_GUIBase :: DoBeforeInsertData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeLeave - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeLeave"

int8 CTX_GUIBase :: DoBeforeLeave ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeOpen"

int8 CTX_GUIBase :: DoBeforeOpen ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeSaveData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeSaveData"

int8 CTX_GUIBase :: DoBeforeSaveData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeSelect - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeSelect"

int8 CTX_GUIBase :: DoBeforeSelect ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoBeforeStoreData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeStoreData"

int8 CTX_GUIBase :: DoBeforeStoreData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  DoValidateData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoValidateData"

int8 CTX_GUIBase :: DoValidateData ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  EnableInputHelp - 



\return term - 

\param  enable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableInputHelp"

logical CTX_GUIBase :: EnableInputHelp (logical enable_opt )
{

  return (   this 
           ? control->EnableInputHelp(enable_opt) 
           : UNDEF);

}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return term - 

\param  actnames - Action name
\param  actype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

logical CTX_GUIBase :: ExecuteAction (char *actnames, int16 actype )
{

  return (   !IsActionDisabled(actnames)
           ? ::ExecuteAction(actnames,(ActionType)actype,this) 
           : YES  );

}

/******************************************************************************/
/**
\brief  ExecuteFunction - 



\return term - 

\param  fnames - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical CTX_GUIBase :: ExecuteFunction (char *fnames, logical chk_opt )
{
  short int    funccnt;
  short int    lindx0     = 0;                         
  char         buffer[ID_SIZE];
  char         executed  = AUTO;
  logical      term      = AUTO;

BEGINSEQ
  static char *functbl[] = 
  { 
      "fc_dummy                ",  //  1
      "DoBeforeOpen            ",  //  2
      "DoAfterOpen             ",  //  3
      "DoBeforeClose           ",  //  4
      "DoAfterEnter            ",  //  5
      "DoBeforeLeave           ",  //  6
      "DoAfterSelect           ",  //  7
      "DoAfterKeyInput         ",  //  8
      "DoAfterClearData        ",  //  9
      "DoBeforeDeleteData      ",  // 10
      "DoAfterDeleteData       ",  // 11
      "DoBeforeFillData        ",  // 12
      "DoAfterFillData         ",  // 13
      "DoBeforeDataSet         ",  // 14
      "DoAfterDataSet          ",  // 15
      "DoBeforeInsertData      ",  // 16
      "DoAfterInsertData       ",  // 17
      "DoBeforeStoreData       ",  // 18
      "DoAfterStoreData        ",  // 19
      "DoBeforeSaveData        ",  // 20
      "DoAfterSaveData         ",  // 21
      "DoValidateData          ",  // 22
      "DoAfterUpdateCollection ",  // 23
      "DoAfterUpdateInstance   ",  // 24
      "DoAfterChangeSelection  ",  // 25  *fixme* wird nicht mehr erzeugt
                                   //     stattdessen waere moeglich: DoBeforeInstanceUnselect ?
                                   //                                 DoAfterInstanceSelected  ?
                                   //     zusaetzlich waere moeglich: DoAfterInsertInstance
                                   //                                 DoAfterDeleteInstance
      "DoBeforeDrag            ",  // 26
      "DoAfterDrag             ",  // 27
      "DoBeforeDrop            ",  // 28
      "DoAfterDrop             ",  // 29
      "DoAfterMouseMove        ",  // 30
      "DoAfterHandleOpen       ",  // 31
      "DoBeforeSelect          ",  // 32
      "DoAfterHandleActivated  ",  // 33
      "DoAfterShow             ",  // 34
      "DoAfterHide             ",  // 35
      "DoAfterDock             ",  // 36
      "DoAfterUndock           ",  // 37
  };
  
  gvtxstb(buffer,fnames,ID_SIZE);
  
  funccnt = sizeof(functbl)/sizeof(functbl[0]);                           
  while ( lindx0++ < funccnt )
    if ( !memcmp(buffer,functbl[lindx0-1],24) )
      break;

  switch ( lindx0 )
  {
    case  1 :                                        break;
    case  2 : executed = DoBeforeOpen();             break;
    case  3 : executed = DoAfterOpen();              break;
    case  4 : executed = DoBeforeClose();            break;
    case  5 : executed = DoAfterEnter();             break;
    case  6 : executed = DoBeforeLeave();            break;
    case  7 : executed = DoAfterSelect();            break;
    case  8 : executed = DoAfterKeyInput();          break;
    case  9 : executed = DoAfterClearData();         break;
    case 10 : executed = DoBeforeDeleteData();       break;
    case 11 : executed = DoAfterDeleteData();        break;
    case 12 : executed = DoBeforeFillData();         break;
    case 13 : executed = DoAfterFillData();          break;
    case 14 : executed = DoBeforeDataSet();          break;
    case 15 : executed = DoAfterDataSet();           break;
    case 16 : executed = DoBeforeInsertData();       break;
    case 17 : executed = DoAfterInsertData();        break;
    case 18 : executed = DoBeforeStoreData();        break;
    case 19 : executed = DoAfterStoreData();         break;
    case 20 : executed = DoBeforeSaveData();         break;
    case 21 : executed = DoAfterSaveData();          break;
    case 22 : executed = DoValidateData();           break;
    case 23 : executed = DoAfterUpdateCollection();  break;
    case 24 : executed = DoAfterUpdateInstance();    break;
    case 25 : executed = DoAfterChangeSelection();   break;
    case 26 : executed = DoBeforeDrag();             break;
    case 27 : executed = DoAfterDrag();              break;
    case 28 : executed = DoBeforeDrop();             break;
    case 29 : executed = DoAfterDrop();              break;
    case 30 : executed = DoAfterMouseMove();         break;
    case 31 : executed = DoAfterHandleOpen();        break;
    case 32 : executed = DoBeforeSelect();           break;
    case 33 : executed = DoAfterHandleActivated();   break;
    case 34 : executed = DoAfterShow();             break;
    case 35 : executed = DoAfterHide();              break;
    case 36 : executed = DoAfterDock();              break;
    case 37 : executed = DoAfterUndock();            break;
    
    default : ;
//              OADIERV1(buffer,ID_SIZE);                 
//              OADIERR(101)
  } 

  term = executed;
RECOVER
  nstring = NULL;
  term    = AUTO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteWindow - 



\return term - 

\param  prophdl - 
\param  class_name - 
\param  wnames - 
\param  as_collection_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteWindow"

logical CTX_GUIBase :: ExecuteWindow (PropertyHandle *prophdl, char *class_name, char *wnames, logical as_collection_w )
{

  return ( ::ExecuteWindow(class_name,wnames,as_collection_w,
                           prophdl,this) );

}

/******************************************************************************/
/**
\brief  Exit - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exit"

logical CTX_GUIBase :: Exit ( )
{

  return ( Quit() );

}

/******************************************************************************/
/**
\brief  FlushGUI - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushGUI"

void CTX_GUIBase :: FlushGUI ( )
{

  FlushGUIEvents();

}

/******************************************************************************/
/**
\brief  GetControlContext - 



\return ctx_ctl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlContext"

CTX_Control *CTX_GUIBase :: GetControlContext ( )
{

  return (   this && GetContextType() != CTXT_Document
           ? (CTX_Control *)this
           : NULL  );

}

/******************************************************************************/
/**
\brief  GetDATDB - Get Database Handle

        The function is used for compatibility reasons. See GetDBHandle().

\return rDBHandle - Reference to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDATDB"

DatabaseHandle &CTX_GUIBase :: GetDATDB ( )
{

  return(GetDBHandle());

}

/******************************************************************************/
/**
\brief  GetDBField - 



\return prophdl - 

\param  prop_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBField"

PropertyHandle CTX_GUIBase :: GetDBField (char *prop_names )
{

  return PropertyHandle() ;

}

/******************************************************************************/
/**
\brief  GetDBHandle - Get Database Handle

        The  function  returns  the  databse,  which  is  associated  with  the 
        application  or  the  project.  The  function  searches  in  the context
        hierarchy until a data source for a database handle has been found.

\return rDBHandle - Reference to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBHandle"

DatabaseHandle &CTX_GUIBase :: GetDBHandle ( )
{

  return(TProjectManager::TPM->UCB()->sdbudat->dbhandle);

}

/******************************************************************************/
/**
\brief  GetDecision - 



\return cond - 

\param  msgnum - 
\param  button0 - 
\param  button1 - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical CTX_GUIBase :: GetDecision (int msgnum, int button0, int button1, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{
  char             *msgtext;
  DBObjectHandle    obhandle(GetRESObject());
  logical           cond = YES;
BEGINSEQ
  msgtext = P_Error().GetErrorText(&obhandle,msgnum,parm1,parm2,parm3,parm4,parm5);
  
  if ( control->GetDecision(NULL,msgtext,
                            button0,button1,0) == button1 )
                                                    ERROR
  


RECOVER
  cond = NO;
ENDSEQ
  P_RESET
  return(cond);
}

/******************************************************************************/
/**
\brief  GetDecisionOk - 



\return cond - 

\param  msgnum - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecisionOk"

logical CTX_GUIBase :: GetDecisionOk (int msgnum, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{

  return ( GetDecision(msgnum,QMessageBox::Ok,QMessageBox::Cancel,
                       parm1,parm2,parm3,parm4,parm5)              );
  



}

/******************************************************************************/
/**
\brief  GetDecisionYes - 



\return cond - 

\param  msgnum - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecisionYes"

logical CTX_GUIBase :: GetDecisionYes (int msgnum, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{

  return ( GetDecision(msgnum,QMessageBox::Yes,QMessageBox::No,
                       parm1,parm2,parm3,parm4,parm5)              );
  



}

/******************************************************************************/
/**
\brief  GetDictionary - 



\return rDictionary - Reference to Dictionary Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

DictionaryHandle &CTX_GUIBase :: GetDictionary ( )
{

  return(GetDBHandle().GetDictionary());

}

/******************************************************************************/
/**
\brief  GetHighContext - 



\return ctx_gui - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ctxtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighContext"

CTX_GUIBase *CTX_GUIBase :: GetHighContext (CTX_Types ctxtype )
{
  CTX_GUIBase  *high_context = NULL;
  CTX_Types     curtype      = CTXT_undefined;
BEGINSEQ
  if ( !this || !high_ctx )                          ERROR
    
  curtype      = high_ctx->GetContextType();
  high_context = (CTX_GUIBase *)high_ctx;
      
  switch ( ctxtype ) 
  {
    case CTXT_undefined   : LEAVESEQ
    case CTXT_Document    : if ( curtype == CTXT_Document )
                                                     LEAVESEQ
                            ERROR
    case CTXT_Project     : if ( curtype == CTXT_Project )
                                                     LEAVESEQ
                            ERROR
    case CTXT_Application : if ( curtype == CTXT_Application || curtype == CTXT_Project )
                                                     LEAVESEQ
                            ERROR
    case CTXT_Control     : if ( curtype == CTXT_Control || curtype == CTXT_Application || curtype == CTXT_Project )
                                                     LEAVESEQ
                            ERROR
    default               : ERROR
  }
RECOVER
  high_context = NULL;
ENDSEQ
  return(high_context);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  res_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighContext"

CTX_GUIBase *CTX_GUIBase :: GetHighContext (char *res_names )
{
  CTX_GUIBase  *high_context = GetHighContext(CTXT_undefined);
  char         *string;

BEGINSEQ
  if ( !res_names || !high_context )                 ERROR
           
  if ( !(string = high_context->GetResourceName()) ) ERROR
  if ( !strcmp(string,res_names) )                   LEAVESEQ
  
  high_context = high_context->GetHighContext(res_names);
RECOVER
  high_context = NULL;
ENDSEQ
  return(high_context);
}

/******************************************************************************/
/**
\brief  GetInitPropertyHandle - Get property handle for initialized instance

        Some  actions (as insert  or append) create  an internal instance, which
        can  be filled before it will be  added to the collection. This instance
        is  provided in a separate property  handle. The instance can be updated
        by the application. 
        GetInitPropertyHandle()  returns a  valid result  only when being called
        while  creating  a  new  instance.  The  event  handlers, which may call
        GetInitPropertyHandle()  do describe this  explicitly. When being called
        in another context the function returns NULL.

\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitPropertyHandle"

PropertyHandle *CTX_GUIBase :: GetInitPropertyHandle ( )
{
  PropertyHandle         *prophdl;
  prophdl = control->GetInitPropertyHandle();
  
  return ( prophdl && prophdl->IsValid() ? prophdl : NULL );

}

/******************************************************************************/
/**
\brief  GetProjectContext - 



\return prjctx - 

\param  ctxtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectContext"

CTX_Project *CTX_GUIBase :: GetProjectContext (CTX_Types ctxtype )
{
  CTX_GUIBase  *context = this;

  while ( context && context->GetContextType() != CTXT_Project )
    context = context->GetHighContext();

  return((CTX_Project *)context);
}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return prophdl - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CTX_GUIBase :: GetPropertyHandle ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CTX_GUIBase :: GetPropertyHandle (char *prop_names )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetRESDB - Get Database Handle for Resource Database

        This   function   is   supported   for   compatibility   reasons.   See 
        GetReourceDB().

\return rDBHandle - Reference to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRESDB"

DatabaseHandle &CTX_GUIBase :: GetRESDB ( )
{

  return(GetResourceDB());

}

/******************************************************************************/
/**
\brief  GetRESDictionary - 



\return rDictionary - Reference to Dictionary Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRESDictionary"

DictionaryHandle &CTX_GUIBase :: GetRESDictionary ( )
{

  return(TProjectManager::TPM->UCB()->res_dict);

}

/******************************************************************************/
/**
\brief  GetRESObject - 



\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRESObject"

DBObjectHandle &CTX_GUIBase :: GetRESObject ( )
{

  return(TProjectManager::TPM->UCB()->sdbures->object_handle);

}

/******************************************************************************/
/**
\brief  GetResourceDB - 



\return rDBHandle - Reference to database handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceDB"

DatabaseHandle &CTX_GUIBase :: GetResourceDB ( )
{

  return(TProjectManager::TPM->UCB()->sdbures->dbhandle);

}

/******************************************************************************/
/**
\brief  GetResult - 



\return result_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResult"

char *CTX_GUIBase :: GetResult ( )
{

  return(nstring);

}

/******************************************************************************/
/**
\brief  GetWorkDictionary - 



\return rDictionary - Reference to Dictionary Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkDictionary"

DictionaryHandle &CTX_GUIBase :: GetWorkDictionary ( )
{
  UtilityHandle    *uti_hdl = TProjectManager::TPM->UCB();
  if ( !uti_hdl->work_dict )
    uti_hdl->OpenWorkDict(uti_hdl->sdbudat->dbhandle);
  return(TProjectManager::TPM->UCB()->work_dict);

}

/******************************************************************************/
/**
\brief  InvalidateDesignerCache - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InvalidateDesignerCache"

logical CTX_GUIBase :: InvalidateDesignerCache ( )
{

  return ( TProjectManager::TPM->InvalidateCache(2) );

}

/******************************************************************************/
/**
\brief  InvalidateResourceCache - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InvalidateResourceCache"

logical CTX_GUIBase :: InvalidateResourceCache ( )
{

  return ( TProjectManager::TPM->InvalidateCache(1) );

}

/******************************************************************************/
/**
\brief  IsActionDisabled - Is action disabled



\return cond - 

\param  actnames - Action name
\param  act_id - Unique action identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActionDisabled"

logical CTX_GUIBase :: IsActionDisabled (char *actnames, char *act_id )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  IsUserContext - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUserContext"

logical CTX_GUIBase :: IsUserContext ( )
{

  return ( GetSystemStates().stscfil() );

}

/******************************************************************************/
/**
\brief  Pointer - 




\param  wait_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pointer"

void CTX_GUIBase :: Pointer (logical wait_opt )
{

  SetPointer(wait_opt);

}

/******************************************************************************/
/**
\brief  ReleaseResourceDictionary - 



\return closed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseResourceDictionary"

logical CTX_GUIBase :: ReleaseResourceDictionary ( )
{

  TProjectManager::TPM->UCB()->CloseWorkDict();

  return ( !TProjectManager::TPM->UCB()->work_dict ? YES : NO );

}

/******************************************************************************/
/**
\brief  ReserveResourceDictionary - 



\return rDictionary - Reference to Dictionary Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveResourceDictionary"

DictionaryHandle &CTX_GUIBase :: ReserveResourceDictionary ( )
{

  TProjectManager::TPM->UCB()->OpenWorkDict(GetResourceDB());

  return(TProjectManager::TPM->UCB()->work_dict);

}

/******************************************************************************/
/**
\brief  ResetWorkDictionary - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWorkDictionary"

void CTX_GUIBase :: ResetWorkDictionary ( )
{
  UtilityHandle    *uti_hdl = TProjectManager::TPM->UCB();
  if ( !uti_hdl->work_dict )
    uti_hdl->CloseWorkDict();


}

/******************************************************************************/
/**
\brief  SetResult - 




\param  result_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetResult"

void CTX_GUIBase :: SetResult (char *result_string )
{

  nstring.SetString(result_string,UNDEF);

}

/******************************************************************************/
/**
\brief  WaitForExecute - 



\return cond - 

\param  wait_file - 
\param  msgnum - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WaitForExecute"

logical CTX_GUIBase :: WaitForExecute (char *wait_file, int msgnum, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{
  char             *msgtext;
  DBObjectHandle    obhandle(GetRESObject());
  logical           cond = YES;
BEGINSEQ
  msgtext = P_Error().GetErrorText(&obhandle,msgnum,parm1,parm2,parm3,parm4,parm5);
  
  while ( cond )
  {
    if ( control->GetDecision("Waiting for...",msgtext,QMessageBox::Ok,QMessageBox::Cancel,0)
                           == QMessageBox::Cancel )  ERROR
    if ( !IsFile(wait_file) )                        LEAVESEQ
  }
  


RECOVER
  cond = NO;
ENDSEQ
  P_RESET
  return(cond);
}

/******************************************************************************/
/**
\brief  set_control - 




\param  ctlptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_control"

void CTX_GUIBase :: set_control (TWidgetControl *ctlptr )
{

  if ( this )
    control = ctlptr;

}

/******************************************************************************/
/**
\brief  set_user_context - 




\param  user_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_user_context"

void CTX_GUIBase :: set_user_context (logical user_opt )
{

  if ( user_opt )
    GetSystemStates().stssfil();
  else
    GetSystemStates().stsrfil();


}

/******************************************************************************/
/**
\brief  ~CTX_GUIBase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_GUIBase"

     CTX_GUIBase :: ~CTX_GUIBase ( )
{

  delete control;
  control = NULL;

}


