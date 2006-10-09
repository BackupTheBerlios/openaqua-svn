/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODSItem

\brief    
          valueSet  - ist bleibt auch gesetzt, wenn der value-string (durch eine
          Context-Anforderung) bereits in die property übertragen wurde.

\date     $Date: 2006/08/29 20:03:17,30 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItem"

#include  <pogui7.h>
#include  <zodsitem.h>
#include  <mODSItem.h>
#include  <cDataFormSpec.h>
#include  <cItemStates.h>
#include  <sDBObjectHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sEventHandler.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sOEHDBEventHandler.hpp>
#include  <sPropertyHandle.hpp>
#include  <ssmcb.hpp>
#include  <sODSItem.hpp>

ODSItem                * _static = NULL;
int32 odsi_count = 0;
int32 odsi_max = 0;
int32 odsi_total = 0;

/******************************************************************************/
/**
\brief  ActivateDBEvents - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateDBEvents"

void ODSItem :: ActivateDBEvents ( )
{

  if ( this && eventHandler )
    eventHandler->ActivateEvents();


}

/******************************************************************************/
/**
\brief  AddODS - 




\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddODS"

void ODSItem :: AddODS (ODS *pODS )
{

  odslist.AddTail(pODS);



}

/******************************************************************************/
/**
\brief  AutoPosition - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoPosition"

logical ODSItem :: AutoPosition ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( property->IsSelected() )                      LEAVESEQ
  if ( !isTop() )  
    if ( !parent->property->IsSelected() )           ERROR
  
  if ( property->PositionTop() )                     ERROR
    
  if ( !property->Get(FIRST_INSTANCE) )
  {
    if ( is_multiple || path.get_collection() )      ERROR
    if ( !property->GetInitInstance() )              ERROR
  }
  SetItemState(YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BlockEvents - 



\return block_opt - 

\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockEvents"

logical ODSItem :: BlockEvents (logical block_opt )
{
  DBObjectHandle         obhandle;
  logical                done = NO;
  if ( property && 
       (obhandle = property->GetObjectHandle()) &&
       block_opt == obhandle.EventHandling()        ) // ungleicher Zustand
  {
    if ( block_opt )
      obhandle.DisableEventHandling();
    else
      obhandle.EnableEventHandling();
    done          = YES;
  }


  return(done);
}

/******************************************************************************/
/**
\brief  BlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void ODSItem :: BlockSignals (logical block_opt )
{

BEGINSEQ
  if ( signalsBlocked() == (bool)block_opt )         LEAVESEQ
  
  blockSignals(block_opt);
  
  FIRE_ODS_SIGNAL  ( obj->BlockSignals(block_opt) );
  FIRE_CHILD_SIGNAL( obj->BlockSignals(block_opt) ); // koennte auch zuviel sein

ENDSEQ

}

/******************************************************************************/
/**
\brief  CheckCollPosition - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckCollPosition"

logical ODSItem :: CheckCollPosition ( )
{
  PropertyHandle   *ph   = property->GetCollectionProperty();
  logical           term = NO;
BEGINSEQ
  if ( !ph )                                         LEAVESEQ
  if ( ph->IsPositioned() )                          LEAVESEQ

  if ( ph->Exist() )
  {
    if ( !ph->Get(AUTO) )                            ERROR
  }
  else
  {
    if ( !ph->IsAutoSelection() )                    ERROR
    if ( ph->Get(FIRST_INSTANCE) )                   ERROR
  }
  SetItemState(NO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckItem - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckItem"

logical ODSItem :: CheckItem ( )
{
  logical          term      = NO;
BEGINSEQ
  if ( istate >= IST_selected )                      LEAVESEQ
  
  if ( istate < IST_valid )
  {
    if ( parent && !isTop() && !IsUserDefined() )
      if ( parent->CheckItem() )                     ERROR
    SetItemState(YES);
  }
  if ( istate < IST_valid )                          ERROR
  if ( (!isKey() && !IsSingleReference() && istate < IST_located) )
  {
    CheckCollPosition();
    if ( istate < IST_located )                      ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return ( term );
}

/******************************************************************************/
/**
\brief  ColFind - 



\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  rcqsKey - 
\param  fConvert_YES - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColFind"

logical ODSItem :: ColFind (const QString &rcqsKey, logical fConvert_YES )
{

  return( !rcqsKey.isEmpty()
          ? ColFind(QS2SZ(rcqsKey),fConvert_YES)
          : NO                                   );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  cszKey - 
\param  fConvert_YES - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColFind"

logical ODSItem :: ColFind (const char *cszKey, logical fConvert_YES )
{
  smcb      *keysmcb;
  char       key[MAX_KEYLEN];
  logical    found = YES;
BEGINSEQ
  if ( initColAction(YES,YES,NO) )                   ERROR
  
  if ( !cszKey ) 
    cszKey= "";
      
  if ( !(keysmcb = getKeySMCB()) )                   ERROR
  if ( fConvert_YES )
    keysmcb->ConvertToStruct(CC cszKey,key);
  else 
    memcpy(key,cszKey,keysmcb->GetInstLength(NO));
    
  if ( property->LocateKey(::Key(key)) )             ERROR

  SetItemState(NO);

RECOVER
  found = NO;
ENDSEQ
  return(found);
}

/******************************************************************************/
/**
\brief  ColGetCount - 



\return res - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColGetCount"

int ODSItem :: ColGetCount ( )
{
  int32    count = 0;
BEGINSEQ
  if ( initColAction(NO,YES,NO) )                   ERROR

  if ( isKey() ) 
    count = 1;
  else
  {
    CheckCollPosition();
    count = property->GetCount();
  }
RECOVER

ENDSEQ
  return count >= 0 ? count : 0;
}

/******************************************************************************/
/**
\brief  ColGetIndex - 



\return res - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColGetIndex"

int ODSItem :: ColGetIndex ( )
{
  long   indx0 = 0;
BEGINSEQ
  if ( isKey() )                                     LEAVESEQ
  
  if ( istate < IST_located )
  {
    ProvideItem();
    if ( istate < IST_located )                      ERROR
  }
  
  if ( lastIndex == AUTO )
    lastIndex = property->GetCurrentIndex();
  indx0 = lastIndex;
RECOVER
  lastIndex = AUTO;
  indx0 = AUTO;
ENDSEQ
  return(indx0);
}

/******************************************************************************/
/**
\brief  ColInit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColInit"

void ODSItem :: ColInit ( )
{

  if ( this )
  {
    if ( !path.get_collection() )
    {
      ProvideItem();
      value = getKey(YES);
    }
  }


}

/******************************************************************************/
/**
\brief  ColIsModified - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColIsModified"

logical ODSItem :: ColIsModified ( )
{
  int              mc = 0;
  int              id = 0;
  logical          cond = NO;

BEGINSEQ
  if ( !coll_prop.IsValid() )                        ERROR
    
  if ( (id = GetColID()) > 0 )
    mc = coll_prop.GetRefModCount();
    
  if ( mc != refModCount || id != lastRefID || lastRefID <= 0 )
    cond = YES;

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ColIsValid - 



\return cond - 

\param  set_state - 
\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColIsValid"

logical ODSItem :: ColIsValid (logical set_state, logical check_opt )
{
  logical     cond = YES;
BEGINSEQ
  if ( path.IsUndefined() )                          LEAVESEQ
    
  if ( isKey() ) 
  {
    cond = parent->ColIsValid(set_state,check_opt);  LEAVESEQ
  }
  
  if ( IsAttribute() ) 
  {
    if ( istate >= IST_selected )                    LEAVESEQ
    ERROR
  }
  
  if ( istate >= IST_valid )                         LEAVESEQ
  
  if ( !property ) 
    openPH();
  if ( !property )                                   ERROR
  
  if ( path.get_type() == PT_BaseCollection || is_path )
    property->PositionTop();
  
  if ( !set_state )                                  LEAVESEQ
    
  SetItemState(check_opt);
  if ( istate < IST_valid )                          ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ColNext - 



\return cond - 

\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColNext"

logical ODSItem :: ColNext (logical fire_signals )
{

  return( !ColPosition(+1,fire_signals) );

}

/******************************************************************************/
/**
\brief  ColPosition - 



\return term - 

\param  direction - 
\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColPosition"

logical ODSItem :: ColPosition (int8 direction, logical fire_signals )
{
  logical     term = NO;
BEGINSEQ
  if ( direction && istate < IST_located )    // sonst hat ColScroll das schon gemacht
    SetItemState(YES);
  if ( istate < IST_valid )                          ERROR
    
  if ( initColAction(NO,YES,NO) )                    ERROR
  
  if ( !is_multiple ) 
  {
    if ( direction + lastIndex != 0 )                ERROR
    property->Get(FIRST_INSTANCE);
  }
  else if ( signalsBlocked() && direction > 0 && sort_key ) // scrol forward
    property->NextKey();
  else if ( direction )
    property->Position(direction);
  else
  {
    if ( lastIndex == AUTO )
      property->ToTop();
    else    
      property->Get(lastIndex);
  }
  
  SetItemState(NO);
  
  if ( fire_signals )
    FireInstanceSignals();
      
  if ( istate < IST_located )                        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ColPrev - 



\return cond - 

\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColPrev"

logical ODSItem :: ColPrev (logical fire_signals )
{

  return( !ColPosition(-1,fire_signals) );

}

/******************************************************************************/
/**
\brief  ColReset - 




\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColReset"

void ODSItem :: ColReset (logical fire_signals )
{
  logical   blocked = DeactivateDBEvents();

  if ( this )
  {
    ValueReset();
    property->ToTop();
    SetItemState(NO);
  }
  
  if ( blocked ) 
    ActivateDBEvents();


}

/******************************************************************************/
/**
\brief  ColScroll - 



\return term - 

\param  lIndex - 
\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColScroll"

logical ODSItem :: ColScroll (int32 lIndex, logical fire_signals )
{
  logical            term = NO;
BEGINSEQ
  SetItemState(YES);
  
  if ( istate >= IST_positioned && lIndex == lastIndex )
                                                     LEAVESEQ
  lastIndex = lIndex;
  
  if ( ColPosition(0,fire_signals) )                 ERROR
RECOVER
  term = YES;
ENDSEQ
  return( term );
}

/******************************************************************************/
/**
\brief  ColSetOrder - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColSetOrder"

void ODSItem :: ColSetOrder ( )
{

BEGINSEQ
  if ( !property )                                   LEAVESEQ
  if ( isKey() )                                     LEAVESEQ

  property->SetOrder(sort_key);

  SetItemState(NO);
 

ENDSEQ

}

/******************************************************************************/
/**
\brief  ColSync - Synchronize ODS

        The  function  synchronizes  the  selection  in  the  ODSItem  with  the
        selection stored in the control.

\return term - 

\param  lID - 
\param  lIndexHint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColSync"

logical ODSItem :: ColSync (int32 lID, int32 lIndexHint )
{
  logical    term = NO;
BEGINSEQ
  if ( initColAction(YES,YES,NO) )                  ERROR
      
  if ( property->GetCurrentIndex() != lIndexHint )
    property->Get(lIndexHint);
        
  if ( lID != AUTO )
    if ( property->GetID() != lID )
      if ( property->Locate(lID) )        // *fixme* muss noch optimiert werden       
        property->ToTop();
  
  SetItemState(NO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CollectionChanged - 




\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CollectionChanged"

void ODSItem :: CollectionChanged (logical clear_opt )
{
  logical       mod;

BEGINSEQ
  if ( signalsBlocked() )                             LEAVESEQ
  
  if ( !clear_opt && !auto_position )                 LEAVESEQ
    
  if ( lastObjID > 0 )
    FireInstanceSignals();
  
  if ( auto_position )
    ProvideItem();
    
  mod = ColIsModified();
  FireCollectionSignals();
  
  if ( mod )
  {
    clear_opt = coll_prop.GetCount() <= 0;
    FIRE_CHILD_SIGNAL( obj->CollectionChanged(clear_opt) );
  }
  

ENDSEQ

}

/******************************************************************************/
/**
\brief  CollectionReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CollectionReset"

void ODSItem :: CollectionReset ( )
{
 

  FireCollectionSignals();

}

/******************************************************************************/
/**
\brief  CollectionUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CollectionUpdated"

void ODSItem :: CollectionUpdated ( )
{

  FireCollectionSignals();

}

/******************************************************************************/
/**
\brief  DBEventsActive - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBEventsActive"

logical ODSItem :: DBEventsActive ( )
{

  return ( this && eventHandler 
           ? eventHandler->get_is_busy() : NO );

}

/******************************************************************************/
/**
\brief  DeactivateDBEvents - 



\return done - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateDBEvents"

logical ODSItem :: DeactivateDBEvents ( )
{
  logical       done = NO;
  if ( this && eventHandler && !DBEventsActive() )
  {  
    eventHandler->DeactivateEvents();
    done = YES;
  }

  return(done);
}

/******************************************************************************/
/**
\brief  Deref - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deref"

void ODSItem :: Deref ( )
{

  if ( !(--refCount) )
    deactivate();





}

/******************************************************************************/
/**
\brief  EmitRefreshEvents - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EmitRefreshEvents"

logical ODSItem :: EmitRefreshEvents ( )
{
  logical                term = NO;
BEGINSEQ
  if ( !property )                                   LEAVESEQ
    
  FIRE_ODS_SIGNAL ( obj->OnCollectionChanged() );
  
  if ( istate >= IST_positioned )
  {
    FIRE_ODS_SIGNAL ( obj->OnInstanceSelected() );
//  property->Save();
//  property->Reset();
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FireCollectionSignals - 




\param  reset_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FireCollectionSignals"

void ODSItem :: FireCollectionSignals (logical reset_opt_w )
{
  DLL(ODS)             cursor(odslist);
  ODS                 *ods;
  logical              new_coll;
BEGINSEQ
  if ( signalsBlocked() )                            LEAVESEQ
  
  if ( !ColIsModified() )                            LEAVESEQ
  
  SetItemState(NO);
  if ( istate >= IST_valid )
  {
    SetCurrentCol();  
    ColInit();
  }
  else
  {
    ResetCurrentCol();  
    ColReset();
  }
    
  cursor.GoTop();
  while ( ods = cursor.GetNext() )
  {
    new_coll = ods->ChangedCollection(); 
    if ( ods->HasColChanged() )
    {
      if ( ods->ItemState() >= IST_valid )
      {
        if ( new_coll )
          ods->OnCollectionChanged();
        else
          ods->OnCollectionUpdated();
      }
      else
        ods->OnCollectionReset();
    }
//    ods->SyncColState();
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  FireInstanceSignals - 




\param  reset_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FireInstanceSignals"

void ODSItem :: FireInstanceSignals (logical reset_opt_w )
{
  DLL(ODS)             cursor(odslist);
  ODS                 *ods;

BEGINSEQ
  if ( !InstIsModified() )                           LEAVESEQ
  
  if ( !signalsBlocked() )                            
  {  
    if ( !reset_opt_w )
      SetItemState(NO);
    if ( !reset_opt_w && istate >= IST_located )
    {
      SetCurrentInst();  
      ValueInit();
    }
    else
    {
      ResetCurrentInst();  
      ValueReset();
    }
    
    cursor.GoTop();
    while ( ods = cursor.GetNext() )
    {
      if ( ods->HasInstChanged() )
      {
        if ( reset_opt_w || ods->ItemState() < IST_located )
          ods->OnInstanceReset();
        else
          ods->OnInstanceSelected();
      }
//      ods->SyncInstState();
    }
//  das wurde bisher auch für signals blocked gemacht. Dann werden 
//  nachgeordnete Windows für Listen aber ständig gefüllt. 
    if ( !reset_opt_w && istate >= IST_located )
    {
      FIRE_CHILD_SIGNAL( obj->RefreshSubItems(YES) );
    }  
    else
    {
      FIRE_CHILD_SIGNAL( obj->ResetSubItems() );
    }
  }
  

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetColID - 



\return id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetColID"

int32 ODSItem :: GetColID ( )
{
  int              id = 0;

  if ( this && coll_prop.IsValid() )
  {
    if ( path.get_type() == PT_BaseCollection && coll_prop.ValidateNode(NO) )
      coll_prop.PositionTop();
    if ( !(id = coll_prop.GetCollectionID()) )
    {
      PropertyHandle  ph(coll_prop.GetParentProperty());
      if ( ph.IsValid() )
        if ( ph.IsSelected() )
          id = AUTO;
    }
  }    

  return(id);
}

/******************************************************************************/
/**
\brief  GetInstID - 



\return id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstID"

int32 ODSItem :: GetInstID ( )
{
  int              id = 0;

  if ( property )
    if ( !(id = property->GetLOID()) )
      if ( property->IsSelected() )
        id = AUTO;
    

  return(id);
}

/******************************************************************************/
/**
\brief  GetLastIndex - 



\return indx0 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastIndex"

int32 ODSItem :: GetLastIndex ( )
{

  return ( this ? lastIndex : AUTO );

}

/******************************************************************************/
/**
\brief  GetLastObjID - 



\return objid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastObjID"

int32 ODSItem :: GetLastObjID ( )
{

  return ( this ? lastObjID : 0 );

}

/******************************************************************************/
/**
\brief  GetODS - 



\return odsptr - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetODS"

ODS *ODSItem :: GetODS (int32 indx0 )
{

  return(odslist.FindIndex(indx0) ? odslist.GetAt() : NULL);

}

/******************************************************************************/
/**
\brief  GetObjectHandle - 



\return ob_handle - Database object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandle"

DBObjectHandle &ODSItem :: GetObjectHandle ( )
{
  DBObjectHandle ret;
BEGINSEQ
  if (!this || !obhandle.IsValid()){
    ret = obhandle;
    LEAVESEQ
  }
  if (parent)
    ret = parent->GetObjectHandle();  

//j060829: gcc: error: operands to ?: have different types
//  return ( this && obhandle.IsValid() 
//           ? obhandle : parent 
//                        ? parent->GetObjectHandle()
//                        : NULL );
ENDSEQ
return ret;
}

/******************************************************************************/
/**
\brief  GetType - 



\return strnames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetType"

char *ODSItem :: GetType ( )
{

  return(path.get_struct_name());

}

/******************************************************************************/
/**
\brief  HandleClosed - PropertyHandle is closed

        The function is called as reaction on the Database event DBO_Closed.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleClosed"

void ODSItem :: HandleClosed ( )
{
// reaktion auf: PropertyHandle ist geschlossen
  coll_prop.Close();

  UpdateItemState();
  FIRE_ODS_SIGNAL ( obj->OnHandleClosed() );

  


}

/******************************************************************************/
/**
\brief  HandleOpened - PropertyHandle is opened

        The  function is  called as  reaction on  the Database event DBO_Opened.
        Metadata information is available, but not neccessaraly data.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleOpened"

void ODSItem :: HandleOpened ( )
{
  DBFieldDef           *fielddef = property->GetFieldDef();
// reaktion auf: PropertyHandle ist geöffnet
  if ( fielddef )
  {
    is_reference  = fielddef->fmcbrlev == R_REFR || fielddef->fmcbrlev == R_GENERIC;
    is_multiple   = property->GetDimension() != 1 && !property->IsAutoSelection();
    is_bool       = fielddef->fmcbityp == T_LO;
    is_number     = fielddef->IsInteger();
  }
  is_memo     = property->IsMemo();
  is_generic  = property->IsGenericAttribute();
  is_path     = property->IsPathExpression();
  
  coll_prop.Open(   is_reference                  || 
                    is_multiple                   ||   // neu 27.7.04 (imbedded arrays)
                    property->IsShareBaseHandle()
                  ? property 
                  : property->GetCollectionProperty() );

  UpdateItemState();
  
  if ( (!is_reference && is_path) || 
       (!is_multiple && property->IsAutoSelection()) || is_memo )
    auto_position = YES;
  
  FIRE_ODS_SIGNAL ( obj->OnHandleOpened() );
  


}

/******************************************************************************/
/**
\brief  HasBaseCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasBaseCollection"

logical ODSItem :: HasBaseCollection ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( !property )                                   ERROR 

  if ( property->IsEnumeration() )                   LEAVESEQ

  if ( property->GetBaseProperty() )                 LEAVESEQ
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  InitStatic - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitStatic"

logical __cdecl ODSItem :: InitStatic ( )
{
  logical                 term = NO;
  if ( !_static )
    _static = new ODSItem();

  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ODSItem :: Initialize ( )
{

  istate             = IST_undefined;
  auto_position      = NO;
  is_reference       = NO;
  is_memo            = NO;
  is_multiple        = NO;
  is_generic         = NO;
  is_path            = NO;
  is_bool            = NO;
  is_number          = NO;
  sort_key           = NULL;
  property           = NULL;
  refCount           = 0;
  ownsProperty       = NO;
  valueSet           = NO;
  parent             = NULL;
  accessMode         = PI_undefined;
  eventHandler       = NULL;
  block_count        = 0;
  coll_prop.Close();


}

/******************************************************************************/
/**
\brief  InstGetKeyString - 



\return skey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstGetKeyString"

char *ODSItem :: InstGetKeyString ( )
{
  static char           keystr[1025];
  logical               sort_key = NO;
  smcb                 *keydef   = NULL;
  ::Key                 key;

BEGINSEQ
  memset(keystr,0,sizeof(keystr));
  
  if ( !(keydef = getKeySMCB()) )                    ERROR
  
  if ( valueSet )
    memcpy(keystr,QS2SZ(value),value.length());
  else
    if ( key = property->GetKey() )
      property->KeyToString(keystr,key,keydef->smcbname);

RECOVER

ENDSEQ
  return(keystr);
}

/******************************************************************************/
/**
\brief  InstGetObjID - 



\return objid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstGetObjID"

int32 ODSItem :: InstGetObjID ( )
{

BEGINSEQ
  if ( istate < IST_located )
  {
    ProvideItem();
    if ( istate < IST_located )                      ERROR
  }
  
  if ( !lastObjID )
    lastObjID = property->GetLOID();
// bis 8.12.05  lastObjID = (coll_prop.IsValid() ? &coll_prop : property)->GetLOID();
// aber InstIsModified vergleicht mit property->GetLOID() (was genau genug fuer attr. in gen. ref             

RECOVER
  lastObjID = AUTO;
ENDSEQ
  return(lastObjID);
}

/******************************************************************************/
/**
\brief  InstGetString - 



\return res - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstGetString"

QString ODSItem :: InstGetString ( )
{
  QString        result;
BEGINSEQ
  if ( CheckItem() )                                 LEAVESEQ
  
  if ( valueSet && parent && !parent->IsCollection() ) 
    result = value;
  else if ( isKey() )
    result = parent->getKey(YES);
  else
  {
    CheckCollPosition();
    result = SZ2QS(property->GetString());
  }
ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  InstGetType - 



\return sType - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstGetType"

std_string ODSItem :: InstGetType ( )
{

  // war qcstring
  return( CheckItem()
          ? std::string()
          : std::string(property->GetFieldDef()->fmcbtype,ID_SIZE) );



}

/******************************************************************************/
/**
\brief  InstInit - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstInit"

logical ODSItem :: InstInit ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( istate < IST_selected )
  {
    if ( istate < IST_valid )                        ERROR
    if ( AutoPosition() )                            ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InstIsModified - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstIsModified"

logical ODSItem :: InstIsModified ( )
{
  int              mc = 0;
  int              id = 0;
  logical          cond = NO;
BEGINSEQ
  if ( !property )                                   ERROR
  
  if ( id = property->GetLOID() )
    mc = property->GetInstModCount();
  else
    if ( property->IsSelected() )
      id = AUTO;
  
  if ( mc != instModCount || id != lastObjID ||
       ( lastIndex != coll_prop.GetCurrentIndex()) )
    cond = YES;

RECOVER

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  InstIsReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstIsReadOnly"

logical ODSItem :: InstIsReadOnly ( )
{

  return ( !IsWrite() );


}

/******************************************************************************/
/**
\brief  InstSave - 



\return term - 

\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstSave"

logical ODSItem :: InstSave (logical recursive )
{
  logical term = NO;
BEGINSEQ
  if ( recursive )
    FIRE_CHILD_SIGNAL( obj->InstSave(YES) );

  if ( is_reference )
  {
    if ( CheckItem() )                               ERROR

    if ( property->Save() )
    {
      OGUISET(666)
      OGUIRESET
    }
    SetItemState(NO);  // ggf. müssen wir hier auch noch den modcount der instanz setzen
  }



RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  InstStore - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstStore"

void ODSItem :: InstStore ( )
{

  if ( refCount == 1 && property )
    ValueStore();

  InstSave(NO);

  if ( refCount == 1 )
    if ( property && ownsProperty && property->IsOwner() ) 
      property->ToTop();




}

/******************************************************************************/
/**
\brief  InstanceInitialized - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceInitialized"

void ODSItem :: InstanceInitialized ( )
{

  UpdateItemState();
  FireInstanceSignals();

}

/******************************************************************************/
/**
\brief  InstanceInserted - 

        When  an instance has been inserted  from another control or from within
        the  context,  the  control  must  be  re-filled.  Usually, the instance
        previously  selected in the control  should be selected after re-filling
        the control.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceInserted"

void ODSItem :: InstanceInserted ( )
{
// reaktion auf: eigene appl. hat in menge hinzugefügt
BEGINSEQ
  if ( signalsBlocked() )                             LEAVESEQ
  
  UpdateItemState();  
  
  FIRE_ODS_SIGNAL ( obj->OnInstanceInserted() );
  FIRE_CHILD_SIGNAL( obj->RefreshSubItems(YES) );

ENDSEQ

}

/******************************************************************************/
/**
\brief  InstanceRemoved - Instance has been removed

        When  an instance has  been removed from  another control or from within
        the  context,  the  control  must  be  re-filled.  Usually, the instance
        previously  selected in the control  should be selected after re-filling
        the control.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceRemoved"

void ODSItem :: InstanceRemoved ( )
{
// reaktion auf: eigene appl. hat aus menge gelöscht
BEGINSEQ
  if ( signalsBlocked() )                             LEAVESEQ
  
  UpdateItemState();  
  
  FIRE_ODS_SIGNAL ( obj->OnInstanceRemoved() );
  FIRE_CHILD_SIGNAL( obj->ResetSubItems() );

ENDSEQ

}

/******************************************************************************/
/**
\brief  InstanceReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceReset"

void ODSItem :: InstanceReset ( )
{

  FireInstanceSignals(YES);

}

/******************************************************************************/
/**
\brief  InstanceSelected - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceSelected"

void ODSItem :: InstanceSelected ( )
{

  FireInstanceSignals();

}

/******************************************************************************/
/**
\brief  InstanceUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceUpdated"

void ODSItem :: InstanceUpdated ( )
{
// reaktion auf: andere appl. hat instanz geändert oder gelöscht
//             : eigene appl. instanz wurde gespeichert
  long           objid = 0;
BEGINSEQ
  if ( signalsBlocked() )                             LEAVESEQ
  
  UpdateItemState();  
  
  FIRE_ODS_SIGNAL ( obj->OnInstanceUpdated() );

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttribute"

logical ODSItem :: IsAttribute ( )
{

  return ( this ? istate >= IST_opened &&
                  (!is_reference || is_memo || is_generic) : NO);

}

/******************************************************************************/
/**
\brief  IsAutoLocate - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoLocate"

logical ODSItem :: IsAutoLocate ( )
{

  return ( this ? auto_position : NO);

}

/******************************************************************************/
/**
\brief  IsCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollection"

logical ODSItem :: IsCollection ( ) const
{

  return ( is_multiple && !is_generic );


}

/******************************************************************************/
/**
\brief  IsReference - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReference"

logical ODSItem :: IsReference ( )
{

  return ( this ? istate >= IST_opened && !IsAttribute() : NO);

}

/******************************************************************************/
/**
\brief  IsSingleReference - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSingleReference"

logical ODSItem :: IsSingleReference ( ) const
{

  return( is_reference && !is_multiple );


}

/******************************************************************************/
/**
\brief  IsUserDefined - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUserDefined"

logical ODSItem :: IsUserDefined ( )
{

  return ( path.get_type() == PT_none );

}

/******************************************************************************/
/**
\brief  ItemState - 



\return istate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemState"

ItemStates ODSItem :: ItemState ( )
{

  return(this ? istate : IST_undefined);

}

/******************************************************************************/
/**
\brief  ODSItem - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItem"

     ODSItem :: ODSItem ( )
                     : QObject ()
{
// null
  Initialize();
//  InitStatic();
//  registerItem(this);
odsi_total++;
if ( odsi_max < ++odsi_count ) odsi_max = odsi_count;

}

/******************************************************************************/
/**
\brief  i07 - 



\param  pODSItemParent - 
\param  prophdl - 
\param  fOwnsProperty - 
\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItem"

     ODSItem :: ODSItem (ODSItem *pODSItemParent, PropertyHandle *prophdl, logical fOwnsProperty, DBObjectHandle &ob_handle )
                     : QObject ()
{

  Initialize();
  property     = prophdl;
  ownsProperty = fOwnsProperty;
  parent       = pODSItemParent;
  
  if ( ob_handle )
    obhandle = ob_handle;
    
  InitStatic();
  
  if ( prophdl )
    accessMode = prophdl->GetMode();
  
  parent->registerChild(this);
  registerItem(this);
  updateAccessMode(NO);
odsi_total++;
if ( odsi_max < ++odsi_count ) odsi_max = odsi_count;

}

/******************************************************************************/
/**
\brief  i1 - 



\param  pODSItemMaster - 
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItem"

     ODSItem :: ODSItem (ODSItem *pODSItemMaster, PIACC accmode )
                     : QObject ()
{
// twins
  Initialize();
  parent            = pODSItemMaster->parent;
  ownsProperty      = YES;
  accessMode        = accmode;
  
  path.SetPath(pODSItemMaster->path);
  
  if ( pODSItemMaster )
    obhandle = pODSItemMaster->obhandle;
    
  InitStatic();
  
  parent->registerChild(this);
  openPH();
odsi_total++;
if ( odsi_max < ++odsi_count ) odsi_max = odsi_count;

}

/******************************************************************************/
/**
\brief  i2 - 



\param  pODSItemParent - 
\param  rODSPropPath - 
\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItem"

     ODSItem :: ODSItem (ODSItem *pODSItemParent, ODSPropPath &rODSPropPath, DBObjectHandle &ob_handle )
                     : QObject ()
{
// subprops or extents or sys_variables
  Initialize();
  parent     = pODSItemParent;
  obhandle   = ob_handle;
  accessMode = rODSPropPath.get_acc_mode();
  path.SetPath(rODSPropPath);
  
  if ( pODSItemParent && !obhandle.IsOpened() )
    obhandle = pODSItemParent->obhandle;
    
  InitStatic();
  
  if ( parent )
    parent->registerChild(this);
  
  openPH();
odsi_total++;
if ( odsi_max < ++odsi_count ) odsi_max = odsi_count;

}

/******************************************************************************/
/**
\brief  i3 - 



\param  pODSItemParent - 
\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItem"

     ODSItem :: ODSItem (ODSItem *pODSItemParent, DBObjectHandle &ob_handle )
                     : QObject ()
{
// dbobjecthandle
  Initialize();
  parent       = pODSItemParent;
  ownsProperty = YES;

  InitStatic();
  
  if ( ob_handle )
  {
    obhandle   = ob_handle;
    accessMode = ob_handle.GetAccess() > PI_Read ? PI_Update : PI_Read;
  }
  
  parent->registerChild(this);
  registerItem(this);
odsi_total++;
if ( odsi_max < ++odsi_count ) odsi_max = odsi_count;

}

/******************************************************************************/
/**
\brief  i4 - 



\param  pODSItemParent - 
\param  pODSItemTemplate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItem"

     ODSItem :: ODSItem (ODSItem *pODSItemParent, ODSItem *pODSItemTemplate )
                     : QObject ()
{

  Initialize();
  parent       = pODSItemParent;
  ownsProperty = YES;
  
  if ( parent )
    obhandle = parent->obhandle;
  
  InitStatic();
  
  property = new PropertyHandle();
    
  if ( property->CreateTempExtent(*pODSItemTemplate->property) )
  {
    qWarning("Could not create temporary extent based on %s.", pODSItemTemplate->path);
    delete property;
    property= NULL;
    return;
  }
    
  path.SetPath(property->GetExtentName(),PT_Extent);
    
  parent->registerChild(this);
  registerItem(this);
  updateAccessMode(NO);
odsi_total++;
if ( odsi_max < ++odsi_count ) odsi_max = odsi_count;

}

/******************************************************************************/
/**
\brief  OnBlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnBlockSignals"

void ODSItem :: OnBlockSignals (logical block_opt )
{

  FIRE_ODS_SIGNAL  ( obj->OnBlockSignals(block_opt); );
  FIRE_CHILD_SIGNAL( obj->OnBlockSignals(block_opt);  );

}

/******************************************************************************/
/**
\brief  OpenSystemVariable - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenSystemVariable"

logical ODSItem :: OpenSystemVariable ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !path.get_collection() )
  {
    if ( OpenUserField("STRING") )                   ERROR
    *property = GetSysVariable(path.get_path());
   InstanceSelected();
  }
  else
  {
    // srt-node für coll SDB_SystemVariable
    
    
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenUserField - 



\return term - 

\param  strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenUserField"

logical ODSItem :: OpenUserField (char *strnames )
{
  logical                 term = NO;
BEGINSEQ
  property = new PropertyHandle(); 
  
  switch ( fmcb::GetInternalType(strnames) )
  {
    case T_INT     : 
    case T_UINT    : property->Open((int32)0);
                     break;
    case T_GUID    :
    case T_CHAR    :
    case T_CCHAR   :
    case T_STRING  : property->Open((char *)NULL);
                     break;
    case T_LO      : property->Open((logical)0);
                     break;
    case T_REAL    : property->Open(0.0);
                     break;
    case T_DATE    : {
                       dbdt      date;
                       property->Open(date);
                     }
                     break;
    case T_TIME    : {
                       dbtm      time;
                       property->Open(time);
                     }
                     break;
    case T_DATETIME: {
                       dttm      datetime;
                       property->Open(datetime);
                     }
                     break;
    case T_VOID    : break;
    default        : if ( !obhandle.IsOpened() )     ERROR
                     if ( property->Open(obhandle.GetDictionary(),strnames) )
                                                     ERROR
  }
  
  registerItem(this);
  updateAccessMode(NO);
  HandleOpened();

RECOVER
  delete property;
  property = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Provide - 



\return pODSItem - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODSItemParent - 
\param  rODSPropPath - 
\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

ODSItem *__cdecl ODSItem :: Provide (ODSItem *pODSItemParent, ODSPropPath &rODSPropPath, DBObjectHandle &ob_handle )
{
  ODSItem         *odsitem = NULL;
BEGINSEQ
//  if ( pODSItemParent )
//    pODSItemParent->refCount++;;
    
  switch ( rODSPropPath.get_type() )
  {
    case PT_undefined        : odsitem = new ODSItem(pODSItemParent,NULL,NO,pODSItemParent->get_obhandle());
                               break;
    case PT_Self             : odsitem = pODSItemParent;
                               break;
    case PT_NewCursor        : odsitem = new ODSItem(pODSItemParent,rODSPropPath.get_acc_mode());
                               break;
    
                               break;  
    case PT_SystemVariable   :
    case PT_Extent           : pODSItemParent = ProvideDBItem(pODSItemParent->obhandle);
                               break;
    case PT_Enumeration      : 
    case PT_DictionaryExtent : pODSItemParent = ProvideDBItem(pODSItemParent->obhandle.GetDictionary());
                               break;  
    
    case PT_none             :    
    case PT_Intern           :    
    case PT_Property         :
    case PT_CopyProperty     :
    case PT_Key              :
    case PT_BaseCollection   : break;
    
    default                  : OGUIERR(99)
  }

  if ( !odsitem )
    if ( !(odsitem = new ODSItem(pODSItemParent,rODSPropPath,ob_handle)) )
                                                     OGUIERR(95)
  odsitem->Ref();
RECOVER
//  if ( pODSItemParent )
//    pODSItemParent->refCount--;;

ENDSEQ
  return(odsitem);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ob_handle - Database object handle
\param  rODSPropPath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

ODSItem *__cdecl ODSItem :: Provide (DBObjectHandle &ob_handle, ODSPropPath &rODSPropPath )
{
  ODSItem    *pODSItemParent = NULL;
  ODSItem    *odsitem        = NULL;

BEGINSEQ
  if ( !(pODSItemParent = ProvideDBItem(ob_handle)) )
                                                     ERROR
  if ( !(odsitem = Provide(pODSItemParent,rODSPropPath,ob_handle)) )
                                                     ERROR

RECOVER

ENDSEQ
  return(odsitem);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  prophdl - 
\param  fOwnsProperty - 
\param  ob_handle - Database object handle
\param  rODSPropPath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

ODSItem *__cdecl ODSItem :: Provide (PropertyHandle *prophdl, logical fOwnsProperty, DBObjectHandle &ob_handle, ODSPropPath &rODSPropPath )
{

  return Provide(new ODSItem(_static,prophdl,fOwnsProperty,ob_handle),
                 rODSPropPath,ob_handle);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  pODSItemParent - 
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

ODSItem *__cdecl ODSItem :: Provide (ODSItem *pODSItemParent, PropertyHandle *ph )
{
  ODSItem    *odsitem        = NULL;

BEGINSEQ
  if ( !pODSItemParent )
    if ( !(pODSItemParent = ProvideDBItem(ph->GetObjectHandle())) )
                                                     ERROR
  odsitem = new ODSItem(pODSItemParent,NULL,NO,pODSItemParent->get_obhandle());
  
  odsitem->Ref();
  odsitem->SetPropertyHandle(ph);

RECOVER

ENDSEQ
  return(odsitem);
}

/******************************************************************************/
/**
\brief  ProvideDBItem - 



\return pODSItem - 

\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDBItem"

ODSItem *__cdecl ODSItem :: ProvideDBItem (DBObjectHandle &ob_handle )
{
  ODSItem    *pODSItem = NULL;
BEGINSEQ
  OGUIRESET
  InitStatic();
  
  DLL(ODSItem)  it(_static->subs);
  it.GoTop();
  while ( pODSItem = it.GetNext() )
    if ( pODSItem->obhandle == ob_handle && !pODSItem->property ) 
      break;

  if ( !pODSItem )
    if ( !(pODSItem = new ODSItem(_static,ob_handle)) )
    {
      OGUIERR(95)
      OGUISDBCERR
    }

RECOVER
  pODSItem = NULL;
ENDSEQ
  return(pODSItem);
}

/******************************************************************************/
/**
\brief  ProvideItem - 



\return istate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideItem"

ItemStates ODSItem :: ProvideItem ( )
{
  int32           lobid = lastObjID;
  int32           lrfid = lastRefID;
BEGINSEQ
  if ( istate >= IST_selected )                      LEAVESEQ

  if ( !property && !isKey() ) 
  {
    openPH();
    if ( istate < IST_opened )                       ERROR
  }
  
  if ( istate < IST_valid ||
       ( (!is_reference || auto_position) && 
         parent->ItemState() < IST_selected) )
  {
    if ( parent && !isTop() && !IsUserDefined() )
    {
      parent->ProvideItem();
      SetItemState(NO);
    }
    if ( auto_position )
      AutoPosition();
    if ( istate < IST_valid )                        ERROR
  }
  
  if ( lrfid != lastRefID )
    ResetCurrentCol();
  if ( lobid != lastObjID )
    ResetCurrentInst();
  if ( istate >= IST_selected )                      LEAVESEQ

  if ( is_reference && !is_multiple && AutoPosition() )              
                                                     ERROR
  SetItemState(YES);
RECOVER

ENDSEQ
  return (istate);
}

/******************************************************************************/
/**
\brief  Refresh - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

void ODSItem :: Refresh ( )
{

  if ( InstIsModified() )
    InstanceUpdated();
  
  if ( ColIsModified() )
    CollectionUpdated();


}

/******************************************************************************/
/**
\brief  RefreshSubItems - 




\param  own_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshSubItems"

void ODSItem :: RefreshSubItems (logical own_opt )
{
  char      old_node[sizeof(PropertyHandle)];
BEGINSEQ
  if ( !property )                                   LEAVESEQ
  if ( own_opt ) 
    property->ValidateNode(YES);
    
/* das macht PH jetzt    
  if ( own_opt )  // da sollte sich PH drum kümmern, tuts aber noch nicht
  {
    memcpy(old_node,property,sizeof(PropertyHandle));
    property->ValidateNode(YES);
    if ( memcmp(old_node,property,sizeof(PropertyHandle)) )  // optimierung
      eventHandler->ActivateEventHandler();
  }
*/  
  istate = IST_opened;
  ProvideItem();
  FireInstanceSignals();
ENDSEQ

}

/******************************************************************************/
/**
\brief  RemODS - 




\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemODS"

void ODSItem :: RemODS (ODS *pODS )
{

  odslist.Remove(pODS);

}

/******************************************************************************/
/**
\brief  ResetCurrentCol - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCurrentCol"

void ODSItem :: ResetCurrentCol ( )
{

  if ( !IsCollection() && path.get_collection() )   
    ResetCurrentInst();
  
  lastRefID   = 0;
  refModCount = AUTO;


}

/******************************************************************************/
/**
\brief  ResetCurrentInst - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCurrentInst"

void ODSItem :: ResetCurrentInst ( )
{

  lastIndex    = AUTO;
  lastObjID    = 0;
  instModCount = AUTO;

  ValueReset();

}

/******************************************************************************/
/**
\brief  ResetPH - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPH"

void ODSItem :: ResetPH ( )
{

  if ( property ) 
  {
//    unregisterItem(this);
    
    property = NULL;
  }

}

/******************************************************************************/
/**
\brief  ResetPropertyHandle - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyHandle"

logical ODSItem :: ResetPropertyHandle ( )
{
  logical                term = NO;
  closePH();


  return(term);
}

/******************************************************************************/
/**
\brief  ResetSubItems - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSubItems"

logical ODSItem :: ResetSubItems ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !property || istate < IST_valid )             LEAVESEQ
    
  if ( parent->ItemState() <= IST_valid )
    istate = property ? IST_opened : IST_defined;  
  else
    istate = IST_valid;
    
  FireInstanceSignals(YES);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCurrentCol - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentCol"

void ODSItem :: SetCurrentCol ( )
{
//  PropertyHandle   *coll_ph = getCollPH();
BEGINSEQ
  if ( !this )                                       ERROR
  switch ( lastRefID = GetColID() )
  {
    case AUTO : refModCount = 0;
                break;
    case    1 : OGUISET(777)
                OGUIRESET
                break;
    default   : refModCount = AUTO; // In case of AUTO ODS checks mod count of PH
//    case    1 : refModCount  = coll_prop.IsValid() ? coll_prop.GetRefModCount() : 0;
  }

  if ( !IsCollection() && path.get_collection() )   
    SetCurrentInst();
    


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetCurrentInst - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentInst"

void ODSItem :: SetCurrentInst ( )
{
  logical               mod = InstIsModified();
BEGINSEQ
  if ( istate < IST_located )
  {
    ResetCurrentInst();                              LEAVESEQ
  }
  
  if ( auto_position && parent )
    instModCount = parent->instModCount;
  else if ( property )
    instModCount = property->GetInstModCount();

  if ( mod )
    ValueInit();


ENDSEQ

}

/******************************************************************************/
/**
\brief  SetFilter - 



\return term - 

\param  expression - 
\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical ODSItem :: SetFilter (char *expression, logical enable_opt )
{
  logical    term = NO;
  path.SetFilter(expression,enable_opt);

  if ( expression )
  {
    term = Handle()->SetSelection(expression);
    path.SetFilter(NULL,enable_opt);
  }
  else
    term = Handle()->ResetSelection();

  return(term);
}

/******************************************************************************/
/**
\brief  SetItemState - 



-------------------------------------------------------------------------------
\brief  - 



\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetItemState"

void ODSItem :: SetItemState (logical check_opt )
{
  logical   ph_valid = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( !check_opt )
  {
    istate       = IST_defined;
    lastIndex    = AUTO;
    lastObjID    = AUTO;
    inst_write   = NO;
    col_write    = NO;
  }
  if ( istate == IST_positioned )                    LEAVESEQ
    
  if ( property && property->IsValid() )
  {
    if ( coll_prop.IsValid() )
    {
      if ( istate < IST_opened )
        istate = IST_opened;
      if ( istate < IST_located )
        if ( (lastIndex = coll_prop.GetCurrentIndex()) >= 0 )
        {  
          istate = IST_located;
          lastObjID = auto_position && !isTop() ? parent->lastObjID 
                                               : property->GetLOID(); // bis 8.12.05 coll_prop.GetLOID(); aber InstIsModified vergleicht mit property->GetLOID() (was genau genug fuer attr. in gen. ref 
        }
      if ( istate == IST_located && coll_prop.IsPositioned() )
      {
        istate = IST_positioned;
        inst_write = coll_prop.IsWrite();
      }
      else if ( istate < IST_selected && property->IsSelected() )
      {
        istate = IST_selected;
        lastObjID = AUTO;
        inst_write = YES;
      }
    }
    else // dumme Nodes
    {
      istate     = IST_positioned;
      inst_write = YES;
      lastIndex  = 0;
      lastObjID  = 0;
    }

    if ( istate == IST_opened )
    {
      PropertyHandle  ph(coll_prop.IsValid() && !property->Is(coll_prop)
                         ? &coll_prop 
                         : property->GetParentProperty());
      if ( (ph_valid = !ph.IsValid()) || ph.IsSelected() )
      {
        istate = IST_valid;
        lastObjID = 0;
        if ( !is_reference )
          istate = IST_positioned;
        col_write = (!ph_valid || ph.IsWrite()) ? property->IsCollectionUpdate() : NO;
      }
      else if ( ph.Exist() && ph.Get() )
      {
        istate = IST_valid;
        lastObjID = 0;
        col_write = ph.IsWrite() && property->IsCollectionUpdate();
      }
    }
  }
  else if ( isKey() )
  {
    col_write = parent->get_col_write();
    switch ( parent->ItemState() )
    {
      case IST_undefined  :
      case IST_defined    : break;
      case IST_opened     : 
      case IST_valid      : istate = IST_opened;
                            break;
      case IST_located    : istate = IST_valid;
                            lastObjID = 0;
                            break;
      case IST_selected   : 
      case IST_positioned : istate = IST_positioned;
                            lastObjID  = 0;
                            inst_write = col_write;
                            break;
    }
  }
  SetItemState(istate);

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  item_state - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetItemState"

void ODSItem :: SetItemState (ItemStates item_state )
{

  istate = item_state;
  
  if ( istate < IST_positioned )
  {
    if ( istate < IST_located )
    {
      lastIndex = AUTO;
      lastObjID = 0;
    }
  }


}

/******************************************************************************/
/**
\brief  SetPropertyHandle - 



\return term - 

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical ODSItem :: SetPropertyHandle (PropertyHandle *prophdl )
{
  logical             term = NO;

BEGINSEQ
  if ( !prophdl || !prophdl->IsValid() )             LEAVESEQ

  ownsProperty = YES;
  property     = new PropertyHandle(prophdl);          

  registerItem(this);
  updateAccessMode(YES);
  if ( property->IsValid() )
    HandleOpened();
  if ( !property )                                   ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetSortKey - 




\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSortKey"

void ODSItem :: SetSortKey (char *names )
{
  char         string[ID_SIZE+1];
  if ( sort_key )
    free(sort_key);
  sort_key = NULL;
  if ( names )
    sort_key = strdup(gvtxbts(string,names,ID_SIZE));


}

/******************************************************************************/
/**
\brief  Signal - 




\param  fnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Signal"

void ODSItem :: Signal (char *fnames )
{

BEGINSEQ
  if ( !strcmp(fnames,"InstanceSelected") )
    InstanceSelected();
  else                                               OGUIERR(99)
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  UpdateItemState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateItemState"

void ODSItem :: UpdateItemState ( )
{

  SetItemState(NO);
  SetCurrentCol();
  SetCurrentInst();


}

/******************************************************************************/
/**
\brief  Value - 



\return qstring - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Value"

QString ODSItem :: Value ( )
{

  return( this ? value : QString() );

}

/******************************************************************************/
/**
\brief  ValueGetDate - 



\return date - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetDate"

dbdt ODSItem :: ValueGetDate ( )
{
  dbdt           date;
  if ( this ) 
     date.FromString(QS2SZ(value),11,DFS_Default);

  return(date);
}

/******************************************************************************/
/**
\brief  ValueGetInt - 



\return number - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetInt"

int32 ODSItem :: ValueGetInt ( )
{

  return( this ? value.toInt() : 0);

}

/******************************************************************************/
/**
\brief  ValueGetString - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetString"

char *ODSItem :: ValueGetString ( )
{
  static QByteArray  static_qba;
  return( this ? QS2SZ_P(value,static_qba) : "" );


}

/******************************************************************************/
/**
\brief  ValueGetTime - 



\return time - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetTime"

dbtm ODSItem :: ValueGetTime ( )
{
  dbtm                   time;
  if ( this ) 
     time.FromString(QS2SZ(value),10,DFS_Default);

  return(time);
}

/******************************************************************************/
/**
\brief  ValueInit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueInit"

void ODSItem :: ValueInit ( )
{

  if ( this )
  {
    valueSet = NO;
    if ( IsReference() )
    {
      if ( !is_multiple && istate <= IST_located )
      {
        property->Get(FIRST_INSTANCE);
        SetItemState(YES);
      }
      value = getKey(YES);
    }
    else
      value = InstGetString();
  }


}

/******************************************************************************/
/**
\brief  ValueIsTrue - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueIsTrue"

logical ODSItem :: ValueIsTrue ( )
{

  return( this && value == dfs::GetOnValue() ? YES : NO);

}

/******************************************************************************/
/**
\brief  ValueIsUpdated - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueIsUpdated"

logical ODSItem :: ValueIsUpdated ( )
{

  return( this && valueSet );

}

/******************************************************************************/
/**
\brief  ValueIsValid - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueIsValid"

logical ODSItem :: ValueIsValid ( )
{

BEGINSEQ
  return ( this && istate >= IST_located && !value.isNull() );                             ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ValueReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueReset"

void ODSItem :: ValueReset ( )
{

  if ( this && valueSet )
  {
    valueSet = NO;
    value.fromLatin1(NULL);
  }

}

/******************************************************************************/
/**
\brief  ValueSet - 



\return changed - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  rcqsText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODSItem :: ValueSet (const QString &rcqsText )
{
  logical          changed = NO;
  if ( this && value != rcqsText )
  {
    value    = rcqsText;
    valueSet = YES;
    changed  = YES;
//  FIRE_ODS_SIGNAL ( obj->OnInstanceUpdated() );
  }


  return(changed);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODSItem :: ValueSet (char *string )
{

  return( ValueSet(SZ2QS(string)) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODSItem :: ValueSet (int32 number )
{
  QString         qs;
  qs.setNum(number);
  return( ValueSet(qs) );

}

/******************************************************************************/
/**
\brief  i03 - 



\param  cond - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODSItem :: ValueSet (logical cond )
{

  return( ValueSet(cond ? dfs::GetOnValue() : dfs::GetOffValue()) );


}

/******************************************************************************/
/**
\brief  i04 - 



\param  date - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODSItem :: ValueSet (dbdt date )
{
  char         string[11];
  return( ValueSet(SZ2QS(date.ToString(string,sizeof(string)-1,
                   DFS_Default))) );

}

/******************************************************************************/
/**
\brief  i05 - 



\param  time - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODSItem :: ValueSet (dbtm time )
{
  char         string[12];
  return( ValueSet(SZ2QS(time.ToString(string,sizeof(string)-1,
                   DFS_Default))) );


}

/******************************************************************************/
/**
\brief  ValueStore - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueStore"

logical ODSItem :: ValueStore ( )
{
  PropertyHandle  *ph           = NULL;
  int64            loid         = 0;
  ::Key            key;
  QByteArray       qba;
  logical          had_valueSet = valueSet;
  logical          changed      = NO;

BEGINSEQ
  if ( valueSet )
  {
    if ( CheckItem() )                               ERROR
    
    QString  local_value(this->value); // safety
    valueSet = NO;  
    if ( local_value != InstGetString() )
    {
      if ( !is_reference || is_generic || is_memo )
      {
        if ( path.get_type() != PT_Key )
        {
          (*property) = QS2SZ_P(local_value,qba);
          if ( path.get_type() == PT_SystemVariable )
          {
            InstanceUpdated();
            SetSysVariable(path.get_path(),property->GetString());
          }
        }
        else
        {
          ph = parent->Handle();
          key = ph->StringToKey(QS2SZ(local_value));
          if ( ph->GetSortKeyLength() > 0 )
            ph->SetSortKey(key);
          else if ( ph->GetKeyLength() > 0 )
            ph->SetKey(key);
        }
        changed= YES;
        if ( !lastObjID )
          lastObjID = -1;
      }
      else if ( !path.get_collection() )
      {
        loid = property->GetLOID(AUTO);
        if ( local_value.isEmpty() )
          property->Delete();
        else
        {
          PropertyHandle   key(QS2SZ(local_value));
          property->Provide(key);
        }
        if ( loid != property->GetLOID(AUTO) )
          changed= YES;
        SetItemState(NO);
      }
    }
  }
RECOVER

ENDSEQ
  return(changed);
}

/******************************************************************************/
/**
\brief  closePH - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "closePH"

void ODSItem :: closePH ( )
{

  if ( property || path.get_type() == PT_none )
  {
    if ( ownsProperty ) 
      delete property;
    ownsProperty = NO;
    property = NULL;

    HandleClosed();
    
    unregisterItem(this);
  }

}

/******************************************************************************/
/**
\brief  collectAccessMode - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "collectAccessMode"

PIACC ODSItem :: collectAccessMode ( )
{
 

BEGINSEQ
  if ( accessMode == PI_Write )                      LEAVESEQ
    
  FIRE_ODS_SIGNAL( if ( obj->accessMode > accessMode ) 
                     accessMode = obj->accessMode )


ENDSEQ
  return accessMode;
}

/******************************************************************************/
/**
\brief  deactivate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "deactivate"

void ODSItem :: deactivate ( )
{

  closePH();    
  
  if ( parent )
  {
    parent->subs.Remove(this); // this is for safety (if I'm the last)
    parent->Deref();
    parent = NULL;
  }
  
  if ( this == _static ) 
  {
    delete _static;
    _static = NULL;
  }
  else if ( refCount != -1 )  // not called from destructor
  {
    refCount = -1;
    delete this;    
  }

}

/******************************************************************************/
/**
\brief  getKey - 



\return res - 

\param  fConvert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getKey"

QString ODSItem :: getKey (logical fConvert )
{
  smcb     *keydef;
  char      keystr[MAX_KEYLEN];
  char     *key = NULL;


BEGINSEQ
  if ( !property->Exist() )                          ERROR
  
  if ( keydef = getKeySMCB() )
  {
    if ( !(key = property->GetKey()) )               ERROR
    
    if ( fConvert )
      property->KeyToString(keystr,key,NULL);
    
    return SZ2QS(keystr);
  }
  else
  {
    if ( !property->IsPositioned() )                 ERROR
    return SZ2QS(property->GetString());
  }

RECOVER
  return QString();
ENDSEQ

}

/******************************************************************************/
/**
\brief  getKeySMCB - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getKeySMCB"

smcb *ODSItem :: getKeySMCB ( )
{
  smcb        *keydef   = NULL;

BEGINSEQ
  if ( !(keydef = property->GetSortKeySMCB()) )
    if ( !(keydef = property->GetKeySMCB()) )          ERROR

RECOVER

ENDSEQ
  return(keydef);

}

/******************************************************************************/
/**
\brief  initColAction - 



\return term - 

\param  chk_key - Check for is key
\param  chk_col - Check for valid collection
\param  chk_inst - Check for valid instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "initColAction"

logical ODSItem :: initColAction (logical chk_key, logical chk_col, logical chk_inst )
{
  logical                 term = NO;
BEGINSEQ
  if ( chk_key )
    if ( isKey() )                                   ERROR
  
  if ( chk_col )
    if ( !ColIsValid(YES,YES) )                      ERROR
  
  if ( chk_inst )
    if ( CheckItem() )                               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  isDerived - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isDerived"

logical ODSItem :: isDerived ( )
{

  return( parent ? !parent->isTop() || 
                    (parent->property && parent->property->IsValid()) 
                 : NO );

}

/******************************************************************************/
/**
\brief  isKey - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isKey"

logical ODSItem :: isKey ( )
{

  return( path.get_type() == PT_Key );

}

/******************************************************************************/
/**
\brief  isTop - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isTop"

logical ODSItem :: isTop ( )
{

//  return parent == 0 || parent == _static->root;
//nd

  return ( !parent || path.get_type() == PT_Extent ||
           (!property && parent == _static) ? YES : NO );


}

/******************************************************************************/
/**
\brief  openPH - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "openPH"

void ODSItem :: openPH ( )
{
  DBStructDef      *strdef;
  int32             size;
BEGINSEQ
  if ( property )                                    LEAVESEQ
  
  if ( path.get_type() == PT_SystemVariable )
  {
    if ( OpenSystemVariable() )                      ERROR
    LEAVESEQ
  }
  if ( path.get_type() == PT_none )  // user defined transient field
  {
    if ( path.get_collection() || !path.get_struct_name() || !*path.get_struct_name() )
                                                     LEAVESEQ
    if ( OpenUserField(path.get_struct_name()) )     ERROR
    LEAVESEQ
  }
  

  if ( isDerived() && !parent->property ) 
    parent->openPH();

  ownsProperty = NO;

  if ( path.get_type() == PT_Intern )
  {
    ownsProperty = YES;
    size         = parent && parent->Handle()->IsValid() ? parent->Handle()->GetStringLength() : 513;
    property     = new PropertyHandle((char *)NULL);
  }
  else
    if ( isDerived() )
    {
      if ( !parent->property )                         ERROR
      
      if ( path.get_type() != PT_Key )
      {
        if ( path.get_type() == PT_BaseCollection )
        {
          if ( parent->property->IsEnumeration() )
          {
            ownsProperty = YES;
            property = new PropertyHandle(parent->property->GetDictionary(),parent->property->GetType(),PI_Read);
          }
          else          
            property = parent->property->GetBaseProperty();
        }
        else
        {
          property = new PropertyHandle(parent->property,path.get_path()); 
          ownsProperty = YES;
        }
        
        if ( path.get_type() == PT_CopyProperty || 
             ( path.get_type() == PT_BaseCollection && !ownsProperty ) )
        {
          PropertyHandle  ph(*property);
          if ( ownsProperty )
            delete property;
          ownsProperty = YES;
          property     = new PropertyHandle(&ph);          
        }
        else if ( !ownsProperty )
        {
          ownsProperty = YES;
          property     = new PropertyHandle(property);          
        }
        if ( property && property->GetSortKeySMCB() ) 
        {
          SetSortKey(property->GetSortKeySMCB()->smcbname);        
          if ( property->IsWeakTyped() && path.get_struct_name() )
            if ( strdef = property->GetDictionary().GetStructDef(path.get_struct_name()) )
              if ( strdef->IsBasedOn(property->GetType()) )
                property->SetType(path.get_struct_name());
        }
      }
    }
    else
    {
      if ( path.get_type() == PT_Extent || path.get_type() == PT_Enumeration 
                                        || path.get_type() == PT_DictionaryExtent )
      {
        ownsProperty = YES;
        property     = new PropertyHandle(parent->obhandle,path.get_path(),path.get_acc_mode());
//        property     = OpenExtent(parent->obhandle,path.get_path(),YES);
      }
//      else
//        qWarning( "Only PT_Extent allowed on database." );
// ist nicht wahr, geht auch für 
    }

  registerItem(this);
  updateAccessMode(NO);
  if ( property->IsValid() )
    HandleOpened();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  registerChild - 




\param  pODSItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "registerChild"

void ODSItem :: registerChild (ODSItem *pODSItem )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  Ref(); 
  subs.AddTail(pODSItem); 

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  registerItem - 




\param  pODSItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "registerItem"

void __cdecl ODSItem :: registerItem (ODSItem *pODSItem )
{

  unregisterItem(pODSItem);

  if ( pODSItem->property )
  {
    if ( !pODSItem->eventHandler )
      pODSItem->eventHandler = new OEHDBEventHandler(pODSItem); 
  }


}

/******************************************************************************/
/**
\brief  unregisterItem - 




\param  pODSItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "unregisterItem"

void __cdecl ODSItem :: unregisterItem (ODSItem *pODSItem )
{

  if ( pODSItem->eventHandler ) 
  {
    delete pODSItem->eventHandler;
    pODSItem->eventHandler = NULL;
  }

// for safety we don't check if it's a collection etc.
// (maybe the property has been closed)


}

/******************************************************************************/
/**
\brief  updateAccessMode - 



\return changed - 

\param  incr_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateAccessMode"

logical ODSItem :: updateAccessMode (logical incr_opt )
{
  PIACC   acc     = accessMode;
  logical changed = NO;
BEGINSEQ
  if ( path.get_type() == PT_BaseCollection )        
  {
    property->ChangeMode(PI_Read);
    LEAVESEQ
  }
    
  if ( path.get_type() == PT_Enumeration    ||
       path.get_type() == PT_DictionaryExtent   )
    if ( property->GetObjectHandle().GetAccess() <= PI_Read )
      LEAVESEQ
  
  if ( isKey() ) 
  {
    parent->updateAccessMode(incr_opt);
    LEAVESEQ
  }

  collectAccessMode();

  if ( accessMode == PI_undefined && parent )
    accessMode = parent->accessMode;
  
  if ( accessMode == PI_undefined ) 
    accessMode = property ? property->GetMode() : PI_Read;
   
  if ( property && property->GetMode() != accessMode &&
       ( !incr_opt || accessMode > acc )                )
    property->ChangeMode(accessMode);

  if ( accessMode != acc )
    changed = YES;

ENDSEQ
  return changed;
}

/******************************************************************************/
/**
\brief  xxClearExtentCache - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxClearExtentCache"

void __cdecl ODSItem :: xxClearExtentCache ( )
{

//  _static->extentCache.Clear();

}

/******************************************************************************/
/**
\brief  xxOpenExtent - 



\return term - 

\param  vDBObjectHandle - 
\param  rcsName - 
\param  fClone - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxOpenExtent"

PropertyHandle *__cdecl ODSItem :: xxOpenExtent (DBObjectHandle &vDBObjectHandle, const std_string &rcsName, logical fClone )
{
  PropertyHandle  *prop;

/*
  if ( !(prop = (PropertyHandle*)_static->extentCache.Find(&k)) )
  {
    prop = new PropertyHandle(vDBObjectHandle,CC rcsName.c_str(),PI_Read);
    _static->extentCache.Add(&k,prop);
  }
  return fClone ? new PropertyHandle(*prop) : prop;
*/
return NULL;
}

/******************************************************************************/
/**
\brief  xxcheckItems - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxcheckItems"

void __cdecl ODSItem :: xxcheckItems ( )
{
  std::vector<ODSItem*>::iterator   it;
  ODSItem                          *obj = NULL;
/*
  for( it = _static->items.begin();
       it!= _static->items.end(); 
       it++)
  {
      obj = (*it);
//    obj->Refresh();
  }
*/

}

/******************************************************************************/
/**
\brief  ~ODSItem - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSItem"

     ODSItem :: ~ODSItem ( )
{

  if ( refCount != -1 ) 
  {
    refCount = -1;
    deactivate();
  }
  
  SetSortKey(NULL);
odsi_count--;
}


