/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/06/01 17:39:00,35 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHActions_HPP
#define   OEHActions_HPP

class     OEHActions;

class  OEHActions
{

public     :
public     :                                        logical AppendEntry ( );
public     :                                        logical BrowseFiles ( );
public     :                                        logical BrowseWriteFiles ( );
public     :                                        logical Cancel ( );
public     :                                        logical CancelClose ( );
public     :                                        logical CopyEntry ( );
public     :                                        logical DeleteEntry ( );
public     :                                        logical DeleteSet ( );
public     :                                        logical DoAfterChangeSelection ( );
public     :                                        logical DoAfterClearData ( );
public     :                                        logical DoAfterDeleteData ( );
public     :                                        logical DoAfterEnter ( );
public     :                                        logical DoAfterInsertData ( );
public     :                                        logical DoAfterKeyInput ( );
public     :                                        logical DoAfterSelect ( );
public     :                                        logical DoAfterSetData ( );
public     :                                        logical DoAfterStoreData ( );
public     :                                        logical DoAfterUpdateCollection ( );
public     :                                        logical DoAfterUpdateInstance ( );
public     :                                        logical DoBeforeClose ( );
public     :                                        logical DoBeforeDeleteData ( );
public     :                                        logical DoBeforeFillData ( );
public     :                                        logical DoBeforeInsertData ( );
public     :                                        logical DoBeforeLeave ( );
public     :                                        logical DoBeforeOpen ( );
public     :                                        logical DoBeforeSetData ( );
public     :                                        logical DoBeforeStoreData ( );
public     :                                        logical DoValidateData ( );
public     :                                        logical EditEntry ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt );
public     :                                        logical FindEntry ( );
public     :                                        logical InsertEntry ( );
public     :                                        logical MoveDown ( );
public     :                                        logical MoveUp ( );
public     :                                        logical NewFindEntry ( );
public     :                                        logical RenameEntry ( );
public     :                                        logical ResetCascadingSelection ( );
public     :                                        logical ResetSelection ( );
public     :                                        logical Save ( );
public     :                                        logical SaveClose ( );
public     :                                        logical SelectEntry ( );
public     :                                        logical SetCascadingSelection ( );
public     :                                        logical SetSelection ( );
public     :                                        logical ShowSelecion ( );
public     :                                        logical StoreEntry ( );
public     :                                        logical UpdateEntries ( );
};

#endif
