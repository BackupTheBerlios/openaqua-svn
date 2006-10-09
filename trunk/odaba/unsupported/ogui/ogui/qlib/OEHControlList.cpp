/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHControlList

\brief    Base class for all list data widgets


\date     $Date: 2006/08/04 18:53:36,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHControlList"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODSRegion.hpp>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOEHControlList.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OEHControlList :: Activate ( )
{

  return ( ActivateList(NO) );

}

/******************************************************************************/
/**
\brief  ActivateList - 



\return term - 

\param  ignore_evthandling - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateList"

logical OEHControlList :: ActivateList (logical ignore_evthandling )
{
  logical                 ini  = stscini();
  logical                 term = NO;
  if ( !ini && (event_handling || ignore_evthandling) )
  {
    if ( !ods()->get_path().get_collection() )
      Connect( SIGNAL (OnInstanceSelected()), SLOT (listChange())    );
    else
      Connect( SIGNAL (OnInstanceSelected()), SLOT (valueSelect())   );
    
    Connect( SIGNAL (OnActivated(logical))  , SLOT (handleActivate()));
    Connect( SIGNAL (OnHandleOpened())      , SLOT (handleOpen())    );
    Connect( SIGNAL (OnInstanceReset())     , SLOT (valueReset())    );
    Connect( SIGNAL (OnInstanceUpdated())   , SLOT (valueUpdate())   );
/*  
    if ( ods()->get_path().get_collection() )
      Connect( SIGNAL (OnInstanceSelected()), SLOT (listChange())    );
    else
      Connect( SIGNAL (OnInstanceSelected()), SLOT (valueSelect())   );
*/
  }
  
  OEHControlData::Activate();

  if ( !ini && (event_handling || ignore_evthandling) )
  {
    Connect( SIGNAL (OnCollectionUpdated()) , SLOT (listUpdate())    );
    Connect( SIGNAL (OnCollectionReset())   , SLOT (listReset())     );
    Connect( SIGNAL (OnCollectionChanged()) , SLOT (listChange())    );   
// 17.11.2005 um Inserted/Removed kuemmert sich das Model
//    Connect( SIGNAL (OnInstanceRemoved())   , SLOT (valueRemove())   );   
//    Connect( SIGNAL (OnInstanceInserted())  , SLOT (valueInsert())   );   
  }


  return(term);
}

/******************************************************************************/
/**
\brief  DA_FindEntry - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OEHControlList :: DA_FindEntry ( )
{

  return ( OEHDataWidget::DA_FindEntry() );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  skey - 
\param  cur_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OEHControlList :: DA_FindEntry (char *skey, logical cur_opt )
{

  lastKey    = skey;
  lastInstID = UNDEF;
  
  if ( !cur_opt )
    lastODS = NULL;

  updateSelection();
  return(NO);
}

/******************************************************************************/
/**
\brief  DA_Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Refresh"

logical OEHControlList :: DA_Refresh ( )
{
  logical                 term = NO;
  ods()->ResetState();
  ListChanged(YES); //060411 assoziate checkbox
  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate - 



\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OEHControlList :: Deactivate (logical data_only )
{

  return ( DeactivateList(NO,data_only) );

}

/******************************************************************************/
/**
\brief  DeactivateList - 



\return term - 

\param  ignore_evthandling - 
\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateList"

logical OEHControlList :: DeactivateList (logical ignore_evthandling, logical data_only )
{
  logical                 ini  = stscini();
  logical                 term = NO;
  if ( ini && (event_handling || ignore_evthandling) && !data_only )
  {
    Disconnect( SIGNAL (OnActivated(logical))  , SLOT (handleActivate()));
    Disconnect( SIGNAL (OnHandleOpened())      , SLOT (handleOpen())    );
    Disconnect( SIGNAL (OnInstanceReset())     , SLOT (valueReset())    );
    Disconnect( SIGNAL (OnInstanceUpdated())   , SLOT (valueUpdate())   );
  
    if ( ods()->get_path().get_collection() )
      Disconnect( SIGNAL (OnInstanceSelected()), SLOT (listChange())    );
    else
      Disconnect( SIGNAL (OnInstanceSelected()), SLOT (valueSelect())   );
  }
  
  OEHControlData::Deactivate(data_only);

  if ( ini && (event_handling || ignore_evthandling) && !data_only )
  {
    Disconnect( SIGNAL (OnCollectionUpdated()) , SLOT (listUpdate())    );
    Disconnect( SIGNAL (OnCollectionReset())   , SLOT (listReset())     );
    Disconnect( SIGNAL (OnCollectionChanged()) , SLOT (listChange())    );   
// 17.11.2005 um Inserted/Removed kuemmert sich das Model
//    Disconnect( SIGNAL (OnInstanceRemoved())   , SLOT (valueRemove())   );   
//    Disconnect( SIGNAL (OnInstanceInserted())  , SLOT (valueInsert())   );   
  }


  return(term);
}

/******************************************************************************/
/**
\brief  GetKey - 



\return key_area - Kea area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *OEHControlList :: GetKey ( )
{

  return ( cur_item->GetKey() );



}

/******************************************************************************/
/**
\brief  GetNextListItem - 



\return pItemData - ItemData

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextListItem"

ItemData *OEHControlList :: GetNextListItem (ItemData *pItemData )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  HandleActivated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleActivated"

void OEHControlList :: HandleActivated ( )
{

  if ( !ods()->get_path().get_collection() )
    Reconnect( SIGNAL (OnInstanceSelected()), SLOT (listChange()) , SLOT (valueSelect())  );
  else
    Reconnect( SIGNAL (OnInstanceSelected()), SLOT (valueSelect()), SLOT (listChange())   );

  OEHControlData::HandleActivated();

}

/******************************************************************************/
/**
\brief  IsCurItem - 



\return cond - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  pItemData - ItemData
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCurItem"

logical OEHControlList :: IsCurItem (ItemData *pItemData, logical recursive )
{
  logical       cond = YES;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( cur_item == pItemData )                       LEAVESEQ
  
  if ( !cur_item )                                   ERROR
  if ( !recursive )                                  ERROR
  
  cond = IsCurItem(pItemData,cur_item->Parent());
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pItemData - ItemData
\param  cur_item_parent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCurItem"

logical OEHControlList :: IsCurItem (ItemData *pItemData, ItemData *cur_item_parent )
{
  logical       cond = YES;
BEGINSEQ
  if ( cur_item_parent == pItemData )                LEAVESEQ 
  
  if ( !cur_item_parent )                            ERROR
  
  cond = IsCurItem(pItemData,cur_item_parent->Parent());
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ListChanged - 




\param  chk_visible - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListChanged"

void OEHControlList :: ListChanged (logical chk_visible )
{

  lastInstID = UNDEF;

  OEHControlData::ListChanged(chk_visible);

}

/******************************************************************************/
/**
\brief  OEHControlList - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlList"

     OEHControlList :: OEHControlList (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : OEHControlData (pODataWidget,oODataWidget,create_ods),
  cur_item(NULL),
  lastKey(),
  lastIndex(AUTO),
  lastInstID(0),
  lastODS(NULL)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlList"

     OEHControlList :: OEHControlList (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : OEHControlData (pODataWidget,oODataWidget,pODS),
  cur_item(NULL),
  lastKey(),
  lastIndex(AUTO),
  lastInstID(0),
  lastODS(NULL)

{



}

/******************************************************************************/
/**
\brief  ProvideContextMenu - 



\return term - 

\param  watched - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideContextMenu"

logical OEHControlList :: ProvideContextMenu (QObject *watched )
{
  PropertyHandle         *ph           = GetCurrentPropertyHandle(); // GetPropertyHandle();
  smcb                   *sk           = NULL;
  smcb                   *ik           = NULL;
  long                    count        = 0;
  logical                 exist        = NO;
  logical                 inst_ro      = NO;
  logical                 coll_ro      = NO;
  logical                 own          = NO;
  logical                 filter       = NO;
  logical                 ods_not_list = NO;
  logical                 term         = NO;
BEGINSEQ
  if ( !context_menu )
  {
    if ( !(context_menu = new OPopupMenu(this,this)) )
                                                     OGUIERR(95)
    context_menu->SetupActions(oeh()->FindAction(NULL,"___ContextMenu",NO));
  }
    
  if ( !ph->IsValid() )                              ERROR
    
  if ( !context_menu->stscfil() )
  {  
    own          = ph->GetDescription()->get_owning();
    sk           = ph->GetSortKeySMCB();
    ik           = ph->GetKeySMCB();
    ods_not_list = ods() != List() ? YES : NO;
    
    oeh()->FindAction("AppendEntry",NULL,NO)->SetActive(sk ? NO : YES);
    oeh()->FindAction("MoveUp",NULL,NO)->SetActive(sk && !sk->smcbsts.stscold() ? NO : YES);
    oeh()->FindAction("MoveDown",NULL,NO)->SetActive(sk && !sk->smcbsts.stscold() ? NO : YES);
    oeh()->FindAction("RenameEntry",NULL,NO)->SetActive(!sk && !ik ? NO : YES);
    oeh()->FindAction("FindEntry",NULL,NO)->SetActive(!sk && !ik ? NO : YES);
    oeh()->FindAction("NewFindEntry",NULL,NO)->SetActive(!sk && !ik ? NO : YES);
    oeh()->FindAction("Associate",NULL,NO)->SetActive(ods_not_list && own ? NO : YES);
    oeh()->FindAction("SetSelection",NULL,NO)->SetActive(ods_not_list ? NO : YES);
    oeh()->FindAction("ResetSelection",NULL,NO)->SetActive(ods_not_list ? NO : YES);
    oeh()->FindAction("SetCascadingSelection",NULL,NO)->SetActive(ods_not_list ? NO : YES);
    oeh()->FindAction("ResetCascadingSelection",NULL,NO)->SetActive(ods_not_list ? NO : YES);
    oeh()->FindAction("UpdateEntries",NULL,NO)->SetActive(ods_not_list ? NO : YES);
    oeh()->FindAction("RemoveEntry",NULL,NO)->SetActive(own ? NO : YES);
    oeh()->FindAction("RemoveSet",NULL,NO)->SetActive(own ? NO : YES);
    oeh()->FindAction("DeleteEntry",NULL,NO)->SetActive(!own ? NO : YES);
    oeh()->FindAction("DeleteSet",NULL,NO)->SetActive(!own ? NO : YES);
    
    context_menu->stssfil();
  }
  
  count    = ph->GetCount();
  if ( !ph->IsSelected() && ph->Exist() )
    ph->Get(AUTO);
  exist    = ph->IsPositioned();  // ggf. reicht es, wenn current entry existiert ...
  inst_ro  = !ph->IsWrite() || IsReadOnly();
  coll_ro  = !ph->IsCollectionUpdate() || IsReadOnly();
//  filter = ph->IsExpressionSet();
  
  oeh()->SetActionDisabled("EditEntry"  ,NULL,!exist);                           // instance selected and update
  oeh()->SetActionDisabled("CopyEntry"  ,NULL,!exist || coll_ro);                // collection is update and instance selected
  oeh()->SetActionDisabled("RenameEntry",NULL,inst_ro);                          // instance selected and update
  oeh()->SetActionDisabled("MoveUp"     ,NULL,coll_ro);                          // instance selected and update
  oeh()->SetActionDisabled("MoveDown"   ,NULL,coll_ro);                          // instance selected and update
  
  oeh()->SetActionDisabled("InsertEntry",NULL,coll_ro);                          // collection is update 
  oeh()->SetActionDisabled("AppendEntry",NULL,coll_ro);                          // collection is update 
  oeh()->SetActionDisabled("Associate"  ,NULL,coll_ro);                          // collection is update 
  oeh()->SetActionDisabled("DeleteEntry",NULL,!exist || coll_ro);                // instance selected and update
  oeh()->SetActionDisabled("DeleteSet"  ,NULL,count <= 0 || coll_ro);            // collection is update and more than 1 entry

  oeh()->SetActionDisabled("NewFindEntry"           ,NULL,count <= 0);                        // 
  oeh()->SetActionDisabled("FindEntry"              ,NULL,count <= 0 || find_text.isEmpty()); // no key set
  oeh()->SetActionDisabled("SetSelection"           ,NULL,count <= 0 || filter);              // no selection set
  oeh()->SetActionDisabled("ResetSelection"         ,NULL,!filter);                           // selection set
  oeh()->SetActionDisabled("SetCascadingSelection"  ,NULL,YES);                               // no selection set
  oeh()->SetActionDisabled("ResetCascadingSelection",NULL,YES);                               // selection set



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveItem - 




\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItem"

void OEHControlList :: RemoveItem (ItemData *pItemData )
{



}

/******************************************************************************/
/**
\brief  ResetCurrentItem - 




\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCurrentItem"

void OEHControlList :: ResetCurrentItem (ItemData *pItemData )
{

  if ( !pItemData || cur_item == pItemData )
    cur_item = NULL;

}

/******************************************************************************/
/**
\brief  SetDefaultReactions - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OEHControlList :: SetDefaultReactions ( )
{
  logical                 term = NO;
  OEHDataWidget::SetDefaultReactions();
  
  SetGUIDefReaction(NULL,"___ContextMenu",NULL);
  
  SetGUIDefReaction("EditEntry"              ,OEHShortcut("F4")          ,"___ContextMenu");
  SetGUIDefReaction("InsertEntry"            ,OEHShortcut("CTRL+I")      ,"___ContextMenu");        // "Del"
  SetGUIDefReaction("AppendEntry"            ,OEHShortcut("CTRL+A")      ,"___ContextMenu");
  SetGUIDefReaction("RemoveEntry"            ,OEHShortcut("CTRL+D")      ,"___ContextMenu");
  SetGUIDefReaction("DeleteEntry"            ,OEHShortcut("CTRL+D")      ,"___ContextMenu");
  SetGUIDefReaction("Refresh"                ,OEHShortcut("CTRL+R")      ,"___ContextMenu")->SetSeparated(YES);
  
  SetGUIDefReaction("...more","...more","___ContextMenu");
  
  SetGUIDefReaction("Associate"              ,OEHShortcut("SHIFT+F1")    ,"...more");
  SetGUIDefReaction("CopyEntry"              ,OEHShortcut("F5")          ,"...more");
  SetGUIDefReaction("RenameEntry"            ,OEHShortcut("F6")          ,"...more");
  SetGUIDefReaction("DeleteSet"              ,OEHShortcut("CTRL+SHIFT+D"),"...more");
  SetGUIDefReaction("MoveUp"                 ,OEHShortcut("CTRL+H")      ,"...more")->SetSeparated(YES);
  SetGUIDefReaction("MoveDown"               ,OEHShortcut("CTRL+R")      ,"...more");
  SetGUIDefReaction("FindEntry"              ,OEHShortcut("F3")          ,"...more")->SetSeparated(YES);   
  SetGUIDefReaction("NewFindEntry"           ,OEHShortcut("ALT+F3")      ,"...more");                      // plus "CTRL+F"
  SetGUIDefReaction("SetSelection"           ,OEHShortcut("F9")          ,"...more")->SetSeparated(YES);   // "SPACE"
  SetGUIDefReaction("ResetSelection"         ,OEHShortcut("ALT+F9")      ,"...more");
  SetGUIDefReaction("UpdateEntries"          ,OEHShortcut("CTRL+F9")     ,"...more");
  SetGUIDefReaction("SetCascadingSelection"  ,OEHShortcut("F10")         ,"...more");
  SetGUIDefReaction("ResetCascadingSelection",OEHShortcut("ALT+F10")     ,"...more");

  return(term);
}

/******************************************************************************/
/**
\brief  SetLastID - 




\param  inst_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastID"

void OEHControlList :: SetLastID (int32 inst_id )
{

  if ( this )
    lastInstID = inst_id;

}

/******************************************************************************/
/**
\brief  SetLastKey - 



\return term - 

\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastKey"

logical OEHControlList :: SetLastKey (ODS *pODS )
{
  logical                 term = NO;
  char                   *pchKey;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( !pODS )
  {
    lastODS    = NULL;
    lastKey    = "";  // vielleicht zu viel
    lastInstID = UNDEF;
  }
  else
  {
    lastODS    = pODS;
    
    pchKey = pODS->InstGetKeyString(); // pchKey == Null ->accessviolation on std::string(NULL)
    if ( pchKey && *pchKey )
      lastKey    = std::string(pchKey);
    else
      lastKey    = "";
    lastInstID = pODS->Handle()->GetLOID();
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateControl"

void OEHControlList :: UpdateControl ( )
{

  ListChanged(YES);
  if(ods()->get_path().get_collection())
    ods()->ResetValue();
  ValueSelected();


}

/******************************************************************************/
/**
\brief  doInstanceInserted - Reaction on an add instance to collection




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doInstanceInserted"

void OEHControlList :: doInstanceInserted ( )
{

//  lastIndex = List()->ColGetIndex();
  lastIndex = GetSelectedODS()->ColGetIndex();  
  SetLastKey(GetSelectedODS());


}

/******************************************************************************/
/**
\brief  doInstanceRemoved - Reaction on a remove instance from collection




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doInstanceRemoved"

void OEHControlList :: doInstanceRemoved ( )
{

  lastKey    = "";
  lastInstID = UNDEF;

}

/******************************************************************************/
/**
\brief  doInstanceUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doInstanceUpdated"

void OEHControlList :: doInstanceUpdated ( )
{

//  lastIndex = List()->ColGetIndex();

}

/******************************************************************************/
/**
\brief  set_cur_item - 




\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_cur_item"

void OEHControlList :: set_cur_item (ItemData *pItemData )
{

  if ( this )
    cur_item = pItemData;

}

/******************************************************************************/
/**
\brief  ~OEHControlList - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHControlList"

     OEHControlList :: ~OEHControlList ( )
{



}


