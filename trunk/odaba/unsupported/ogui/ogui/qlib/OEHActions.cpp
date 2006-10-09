/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHActions

\brief    Standard actions
          This  is a summary  of standard action  and standard action names. All
          actions  can be provided  within the application.  Some of the actions
          have  standard implementation, which are described for the appropriate
          actions.  Some of the standard actions should not be overloaded in the
          application  or  at  least  not  without  calling  the standard action
          within the overloaded action.

\date     $Date: 2006/06/21 18:44:02,74 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHActions"

#include  <pogui7.h>
#include  <sOEHActions.hpp>


/******************************************************************************/
/**
\brief  AppendEntry - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AppendEntry"

logical OEHActions :: AppendEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  BrowseFiles - Select file name
        The  action should returns a file name  by a file dialogue and stores it
        in the edit control. The action works for edit controls, only. 
        <u>Standard Action</u>
        The  action  is  calling  the  standard  file  dialogue from QT. You may
        select an existing file name, only. 
        <i>Assigned key</i>: Ctrl--Alt-F

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BrowseFiles"

logical OEHActions :: BrowseFiles ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  BrowseWriteFiles - Get new file path
        The  action should returns a file name  by a file dialogue and stores it
        in the edit control. The action works for edit controls, only. 
        <u>Standard Action</u>
        The  action  is  calling  the  standard  file  dialogue from QT. You may
        select an existing file or a new file name.
        <i>Assigned key</i>: Ctrl--Shift-F

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BrowseWriteFiles"

logical OEHActions :: BrowseWriteFiles ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  Cancel - Cancel modification or action
        The  action  will  cancel  the  actions  done  in  the control so far as
        possible and re-read the data for the control.
        <u>Standard Action</u>
        This  action is implemented for any type  of control. It will cancel the
        selected  instance in the property handle  and re-read the data from the
        original instance.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical OEHActions :: Cancel ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  CancelClose - Cancel modification or action and close control
        The  action  will  cancel  the  actions  done  in  the control so far as
        possible and close the control.
        <u>Standard Action</u>
        This  action is implemented for any type  of control. It will cancel the
        selected instance in the property handle and close the control.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelClose"

logical OEHActions :: CancelClose ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  CopyEntry - Copy instance
        The  action allows copying  an instance within  a collection. The action
        works  for  list  controls,  only,  and  can  be  overwritten  by  the 
        application.  
        <u>Standard Action</u>
        The  action is opening a GetString dialogue for entering the new key for
        the  target  instance.  When  the  dialogue  is  opened,  the old key is
        displayed  according to  the settings  in the  list. When confirming the
        entered key with OK the instance is copied. 
        <i>Assigned key</i>: F5

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyEntry"

logical OEHActions :: CopyEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  DeleteEntry - Delete selected entry
        The  action deletes the instance selected in the active control from the
        collection  associated  with  the  control.  The action is supported for
        list controls, only. 
        <u>Standard Action</u>
        The  action  deletes  the  selected  instance  from  collection  of  the
        control. 
        <i>Assigned key</i>: Ctrl-D

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEntry"

logical OEHActions :: DeleteEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  DeleteSet - Delete collection
        The  action  deletes  all  instance  in  the control from the collection
        associated  with the control. The action is supported for list controls,
        only. 
        <u>Standard Action</u>
        The  action  deletes  the  selected  instance  from  collection  of  the
        control. 
        <i>Assigned key</i>: Ctrl-Shift-D

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSet"

logical OEHActions :: DeleteSet ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  DoAfterChangeSelection - After change selection action
        The  action  is  called  when  another  instance  has been selected in a
        collection (PropertyHandle).
        <u>Standard Action</u>
        The  standard action will refill subordinated controlls and windows. The
        standard  action is  called in  any case,  independent on implementing a
        user action or not.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterChangeSelection"

logical OEHActions :: DoAfterChangeSelection ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterClearData - After clear data action
        The  action is called after the control  or window has been cleared (all
        data removed from element). 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterClearData"

logical OEHActions :: DoAfterClearData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterDeleteData - Ater delete data action
        The  action  is  called  after  deleting  data  in  a control. It is not
        called,  when deleting  text in  an edit  control, but for actions only,
        that  delete an instance in the  database. Usually, the action is called
        in the DeleteEntry standard action after deleting an instance.  
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDeleteData"

logical OEHActions :: DoAfterDeleteData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterEnter - After enter action
        The  action is called after the control or window has got the focus. The
        action  can  be  used  for  initialising  or refreshing the control when
        being entered.
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterEnter"

logical OEHActions :: DoAfterEnter ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterInsertData - After insert data action
        The  action  is  called  after  an  instance  has  been  inserted  in  a
        collection. 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInsertData"

logical OEHActions :: DoAfterInsertData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterKeyInput - After key input action
        The action is called after a key input has been made for the control.  
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterKeyInput"

logical OEHActions :: DoAfterKeyInput ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterSelect - After instance selection action
        The  action  is  called  after  an  entry  (usually  in a list) has been
        selected. 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

logical OEHActions :: DoAfterSelect ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterSetData - After set data action
        The  action  is  called  after  data  has  set for a control. For simple
        controls  this is  identical with  the DoAfterFillData action. For lists
        this  action is called for each list  entry. The function can be used to
        change  the font and color  for the list items  (columns) or to insert a
        pix-map dynamically.   
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSetData"

logical OEHActions :: DoAfterSetData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterStoreData - After store data Action
        The  action  is  called  after  data has been stored (StoreEntry) to the
        instance or database.  
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterStoreData"

logical OEHActions :: DoAfterStoreData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterUpdateCollection - After update collection action
        The  action is  called when  a collection  the control is based on (list
        controls, only) has been changed.  
        <u>Standard Action</u>
        Refill  the visible part  of the list  or the complete list depending on
        the  type of  list control.  The standard  action is called in any case,
        independent on implementing a user action or not.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterUpdateCollection"

logical OEHActions :: DoAfterUpdateCollection ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterUpdateInstance - After update instance action
        The  action is called  when an instance  the control is based on (window
        controls) has been changed.   
        <u>Standard Action</u>
        Refill  the visible part  of the control.  The standard action is called
        in any case, independent on implementing a user action or not.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterUpdateInstance"

logical OEHActions :: DoAfterUpdateInstance ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeClose - Before close action
        The  action is called  before closing a  GUI element (control or window,
        allpication,  project).  Terminating  the  action  with error (YES), the
        element  will not be closed. This has no effect for controls, which will
        be closed anyhow. 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

logical OEHActions :: DoBeforeClose ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeDeleteData - Before delete data action
        The  action  is  called  before  deleting  data  in a control. It is not
        called,  when deleting  text in  an edit  control, but for actions only,
        that  delete an instance in the  database. Usually, the action is called
        by the DeleteEntry standard action before deleting an instance. 
        Terminating  the  action  with  error  (YES)  will  deny  deleting  the 
        instance.  
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDeleteData"

logical OEHActions :: DoBeforeDeleteData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeFillData - Before fill data action
        The action is called before a controll is filled with data. 
        Terminating the action with error (YES) will deny filling the control.  
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

logical OEHActions :: DoBeforeFillData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeInsertData - Before insert data action
        The  action  is  called  before  inserting or appending an instance to a
        collection  or single reference. Terminating the action with error (YES)
        will deny inserting the entry. 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeInsertData"

logical OEHActions :: DoBeforeInsertData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeLeave - Before leave action
        The  action is  called before  leaving the  control, i.e. when the a GUI
        element  (control  or  window)  looses the focus. Terminating the action
        with  error  (YES)  will  cause  the element to remain avztive (keep the
        focus). 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeLeave"

logical OEHActions :: DoBeforeLeave ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeOpen - Before open action
        The  action is called  before opening a  GUI element (control or window,
        allpication,  project).  Terminating  the  action  with error (YES), the
        element will not be opened. 
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeOpen"

logical OEHActions :: DoBeforeOpen ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeSetData - Before set data action
        The  action  is  called  after  data  has  set for a control. For simple
        controls  this is  identical with  the DoAfterFillData action. For lists
        this  action  is  called  for  each list entry. Returning an error (YES)
        will suppress the instance from being displayed in the list.  
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeSetData"

logical OEHActions :: DoBeforeSetData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoBeforeStoreData - Before Store Data action
        The  action is called  before storing (saving)  an instance or attribute
        (StoreEntry  action). Terminating the action  with error (YES) will deny
        storing the data.
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeStoreData"

logical OEHActions :: DoBeforeStoreData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DoValidateData - Validate data action
        The  action is  called when  the content  of an GUI element has changed,
        when  it has been filled, when data in  a control has been changed or in
        other  cases when it  needs to be  refreshed. The action is called, when
        data  has been  fiiled into  the control  and can  be used to change the
        current  setting  for  the  GUI  element  (hiding controls, changing the
        display level or tab, etc.)
        <u>Standard Action</u>
        There is no standard action provided.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoValidateData"

logical OEHActions :: DoValidateData ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  EditEntry - Edit selected instance
        The  action edits the data for an  instance selected in a control. It is
        supported  for list and edit controls. The  window is opened as modal or
        modales  dialogue depending  on the  window's definition. When opening a
        modales  dialogue,  the  window  stays  open and scrolls with the parent
        control. 
        <i>Assigned key</i>: F4
        The action can be overloaded by the application. 
        <u>Standard Action (OADI)</u>
        The  action tries  to open  a subsequent  window for the window class of
        the  associated instance using the window action definition "EditEntry".
        If  this  window  action  is  not  explicitly  defined,  it  is  defined
        internally  with the window  name "Edit". Defining  the window action in
        your  application, you  can overwrite  the standard  window name in your
        application.  You should leave the class name empty to enable the window
        action  looking  for  the  window  name  in  the  class according to the
        proberty  handle  (data  source)  for  the  control,  which  invokes the
        action.
        <u>Standard Action (OGUI)</u>
        The  action opens an  internally defined standard  window for the window
        class  of the associated instance. The window contains standard controls
        for all properties from the class of the associated instance.  
        t

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditEntry"

logical OEHActions :: EditEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return term - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical OEHActions :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("UpdateEntries",ALINK(this,OEHActions,UpdateEntries)),
                           cfte("StoreEntry",ALINK(this,OEHActions,StoreEntry)),
                           cfte("SetSelection",ALINK(this,OEHActions,SetSelection)),
                           cfte("SetCascadingSelection",ALINK(this,OEHActions,SetCascadingSelection)),
                           cfte("SelectEntry",ALINK(this,OEHActions,SelectEntry)),
                           cfte("ResetSelection",ALINK(this,OEHActions,ResetSelection)),
                           cfte("ResetCascadingSelection",ALINK(this,OEHActions,ResetCascadingSelection)),
                           cfte("RenameEntry",ALINK(this,OEHActions,RenameEntry)),
                           cfte("NewFindEntry",ALINK(this,OEHActions,NewFindEntry)),
                           cfte("MoveUp",ALINK(this,OEHActions,MoveUp)),
                           cfte("MoveDown",ALINK(this,OEHActions,MoveDown)),
                           cfte("InsertEntry",ALINK(this,OEHActions,InsertEntry)),
                           cfte("FindEntry",ALINK(this,OEHActions,FindEntry)),
                           cfte("EditEntry",ALINK(this,OEHActions,EditEntry)),
                           cfte("DoValidateData",ALINK(this,OEHActions,DoValidateData)),
                           cfte("DoBeforeStoreData",ALINK(this,OEHActions,DoBeforeStoreData)),
                           cfte("DoBeforeSetData",ALINK(this,OEHActions,DoBeforeSetData)),
                           cfte("DoBeforeOpen",ALINK(this,OEHActions,DoBeforeOpen)),
                           cfte("DoBeforeLeave",ALINK(this,OEHActions,DoBeforeLeave)),
                           cfte("DoBeforeInsertData",ALINK(this,OEHActions,DoBeforeInsertData)),
                           cfte("DoBeforeFillData",ALINK(this,OEHActions,DoBeforeFillData)),
                           cfte("DoBeforeDeleteData",ALINK(this,OEHActions,DoBeforeDeleteData)),
                           cfte("DoBeforeClose",ALINK(this,OEHActions,DoBeforeClose)),
                           cfte("DoAfterUpdateInstance",ALINK(this,OEHActions,DoAfterUpdateInstance)),
                           cfte("DoAfterUpdateCollection",ALINK(this,OEHActions,DoAfterUpdateCollection)),
                           cfte("DoAfterStoreData",ALINK(this,OEHActions,DoAfterStoreData)),
                           cfte("DoAfterSetData",ALINK(this,OEHActions,DoAfterSetData)),
                           cfte("DoAfterSelect",ALINK(this,OEHActions,DoAfterSelect)),
                           cfte("DoAfterKeyInput",ALINK(this,OEHActions,DoAfterKeyInput)),
                           cfte("DoAfterInsertData",ALINK(this,OEHActions,DoAfterInsertData)),
                           cfte("DoAfterEnter",ALINK(this,OEHActions,DoAfterEnter)),
                           cfte("DoAfterDeleteData",ALINK(this,OEHActions,DoAfterDeleteData)),
                           cfte("DoAfterClearData",ALINK(this,OEHActions,DoAfterClearData)),
                           cfte("DoAfterChangeSelection",ALINK(this,OEHActions,DoAfterChangeSelection)),
                           cfte("DeleteSet",ALINK(this,OEHActions,DeleteSet)),
                           cfte("DeleteEntry",ALINK(this,OEHActions,DeleteEntry)),
                           cfte("CopyEntry",ALINK(this,OEHActions,CopyEntry)),
                           cfte("BrowseWriteFiles",ALINK(this,OEHActions,BrowseWriteFiles)),
                           cfte("BrowseFiles",ALINK(this,OEHActions,BrowseFiles)),
                           cfte("AppendEntry",ALINK(this,OEHActions,AppendEntry)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FindEntry - Find entry in list
        The  action allows locating  an instance in  a collection according to a
        given  selection criteria, usually a key value, which has been set using
        the  NewFindEntry action. The action works  for list controls, only, and
        can be overwritten by the application.  
        <u>Standard Action</u>
        The  control tries to  locate the key  according to the last settings in
        the  list control (NewFindEntry).  When being located  the list entry is
        high-lighted. . 
        <i>Assigned key</i>: F3

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindEntry"

logical OEHActions :: FindEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  InsertEntry - Insert entry in collection
        The  action inserts an instance to  a collection ibfront of the selected
        instance.  The action should  not be overloaded  by the application. The
        action is supported for list controls, only.
        <u>Standard Action</u>
        This  action is implemented for any type of lists. It allows inserting a
        new  entry for visible lists but also  for drop lists. The action always
        works  on the list part of the control, which might be actually the base
        collection. 
        The  key  for  creating  the  new  entry  is  taken  from the edit, when
        avaialable.  When  the  list  does  not  provide  an edit field, but the
        collection  requires  a  key,  the  function pops up with a dialogue for
        entering a key.
        <i>Assigned key</i>: Ctrl-I

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertEntry"

logical OEHActions :: InsertEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  MoveDown - Move Down
        The  action  moves  an  entry  in  a  list one position down. The action
        should  not be  overloaded by  the application.  The action is supported
        for list controls, only.
        <u>Standard Action</u>
        This  action is implemented for any type of lists. It allows moving down
        a  list  entry  for  unordered  lists  and  lists  using  autonumbering 
        (__AUTOIDENT): 
        <i>Assigned key</i>: Ctrl-Down

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical OEHActions :: MoveDown ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  MoveUp - Move up
        The  action  moves  an  instance  in  a list one position up. The action
        should  not be  overloaded by  the application.  The action is supported
        for list controls, only.
        <u>Standard Action</u>
        This  action is implemented for any type of lists. It allows moving up a
        list   entry   for   unordered   lists   and  lists using auto-numbering
        (__AUTOIDENT): 
        <i>Assigned key</i>: Ctrl-Up

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical OEHActions :: MoveUp ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  NewFindEntry - Find new entry
        The  action allows locating  an instance in  a collection according to a
        given  selection criteria, which is requested  from the user. The action
        works  for  list  controls,  only,  and  can  be  overwritten  by  the 
        application.  
        <u>Standard Action</u>
        The  action is opening a GetString dialogue for entering the search key.
        The  control tries to  locate the key  according to the list settings in
        the list. When being located the list entry is high-lighted. . 
        <i>Assigned key</i>: Alt-F3

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewFindEntry"

logical OEHActions :: NewFindEntry ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  RenameEntry - Rename instance
        The  action allows renaming an instance in  a list. The action works for
        list controls, only, and can be overwritten by the application.  
        <u>Standard Action</u>
        The  action  is  opening  a  GetString dialogue for entering the new key
        search  key.  When  the  dialogue  is  opened,  the old key is displayed
        according  to the settings in the  list. When confirming the entered key
        with OK the instance is renamed. 
        <i>Assigned key</i>: F6

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RenameEntry"

logical OEHActions :: RenameEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  ResetCascadingSelection - Reset cascading selection
        The  action  allows  resetting  a  condition for a collection, which has
        been  set  with  the  SetCascadingSelection  action  or the SetSelection
        function  for the property  handle. The action  works for list controls,
        only. 
        <u>Standard Action</u>
        The action resets the filter currently set in the property handle.   
        <i>Assigned key</i>: Alt-F10

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCascadingSelection"

logical OEHActions :: ResetCascadingSelection ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ResetSelection - Reset selection condition
        The  action  allows  resetting  a  condition for a collection, which has
        been  set with the SetSelection action  or the SetSelection function for
        the property handle. The action works for list controls, only. 
        <u>Standard Action</u>
        The action resets the filter currently set in the property handle.   
        <i>Assigned key</i>: Alt-F9

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSelection"

logical OEHActions :: ResetSelection ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  Save - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical OEHActions :: Save ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  SaveClose - Save modification or execute action and close control
        The  action  will  save  updates  made in the control and/or execute the
        required  action after closing the  control. This behaviour is typically
        for dialogue boxes..
        <u>Standard Action</u>
        This  action  is  implemented  for  any  type  of  control. It will save
        modifications made, close the control and execute the required action.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveClose"

logical OEHActions :: SaveClose ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  SelectEntry - Select entry
        The  action  allows  selecting  an  instance in a related collection for
        being  associated  with  the  current  edit  or list control. The action
        works  for list  controls and  edit controls,  and can be overwritten by
        the application.  
        <u>Standard Action</u>
        The  action  pos  up  with  a  selection  list,  which usually shows the
        instances  for  the  base  collection  defined in the database or in the
        application  (SetBasePath). When selecting an  entry and klicking on the
        OK  button, the  selected entry  will be  associated with (added to) the
        current list. 
        <i>Assigned key</i>: Shift-F1

        The  action should provide selection list  for associating an entry with
        the property handle selected for the control. 
        <u>Standard Action</u>
        Currently  the  function  pops  up  with  a  dialogue. It works only for
        controls, which have an assigned base collection (GUI or database).
        <i>Assigned key</i>: Ctrl-F1
        roberty handle (data source) for the control, which invokes the action.
        <u>Standard Action (OGUI)</u>
        The  action opens an  internally defined standard  window for the window
        class  of the associated instance. The window contains standard controls
        for all properties from the class of the associated instance.  
        —

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectEntry"

logical OEHActions :: SelectEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  SetCascadingSelection - Set cascading selection
        The  action allows setting a condition for the current collection, which
        filters  the entries in  the collection. When  a cascading selection has
        already  been set, the new selection  filters instances from the current
        collection, only. The action works for list controls, only. 
        <u>Standard Action</u>
        The  action  is  opening  a  GetString  dialogue for entering the filter
        condition  for the collection. The filter  condition must be provided as
        valid  ODABA  OQL  expression.  The  filter  can  be  reset  using  the 
        ResetCascadingSelection action.  
        <i>Assigned key</i>: F10

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCascadingSelection"

logical OEHActions :: SetCascadingSelection ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetSelection - Set selection for collection
        The  action allows setting  a condition for  a collection, which filters
        the  entries  in  the  collection.  The  action works for list controls,
        only. 
        <u>Standard Action</u>
        The  action  is  opening  a  GetString  dialogue for entering the filter
        condition  for the collection. The filter  condition must be provided as
        valid  ODABA  OQL  expression.  The  filter  can  be  reset  using  the 
        ResetSelection  action. Setting a new  selection will reset the previous
        selection. 
        <i>Assigned key</i>: F9

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSelection"

logical OEHActions :: SetSelection ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  ShowSelecion - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowSelecion"

logical OEHActions :: ShowSelecion ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  StoreEntry - Store data action
        The  action saves the  data for the  selected control. The action can be
        called  for  any  control.  The  action  should not be overloaded in the
        application. 
        <u>Standard Action</u>
        When  the control is a list control,  the data for the selected instance
        is  saved to the  database (or transaction).  When the control refers to
        an  attribute the attribute data is stored to the database instance, but
        not to the database.
        <i>Assigned key</i>: F2

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreEntry"

logical OEHActions :: StoreEntry ( )
{

return NO;

}

/******************************************************************************/
/**
\brief  UpdateEntries - 
        The  action updates all  entries in the  collection according to a given
        expression. The action works for list controls, only. 
        <u>Standard Action</u>
        The  action is opening a GetString  dialogue for entering the expression
        defining  the update  rules. The  update expression  must be provided as
        valid  ODABA  OQL  expression.  When  confirming  the  dialogue  with OK
        instances  in the collection  are updated. When  a filter is defined for
        the  collection, only instances displayed are updated. The function does
        nor work on collections with cascading selections. 
        <i>Assigned key</i>: Ctrl-F9

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateEntries"

logical OEHActions :: UpdateEntries ( )
{

return NO;

}


