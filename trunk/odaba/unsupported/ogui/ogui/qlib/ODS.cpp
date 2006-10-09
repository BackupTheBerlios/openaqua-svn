/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODS

\brief    


\date     $Date: 2006/08/29 19:51:53,88 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODS"

#include  <pogui7.h>
#include  <mODS.h>
#include  <sDatabaseHandle.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODSList.hpp>
#include  <sODSRegion.hpp>
#include  <sOEH.hpp>
#include  <sPropertyHandle.hpp>
#include  <sODS.hpp>

int32 ods_count = 0;
int32 ods_max = 0;
int32 ods_total = 0;

/******************************************************************************/
/**
\brief  ActivateDesignMode - 




\param  fDmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateDesignMode"

void ODS :: ActivateDesignMode (logical fDmode )
{
  ODS               *c;
  if ( this )
  {
    DLL(ODS)           it(childODS);
  
    emit OnDesignModeActivated(fDmode);
    
    while( c = it.GetNext() )
      c->ActivateDesignMode(fDmode);
  }

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

logical ODS :: BlockEvents (logical block_opt )
{

  return( prop ? prop->BlockEvents(block_opt) : NO);


}

/******************************************************************************/
/**
\brief  BlockItemEvents - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockItemEvents"

void ODS :: BlockItemEvents (logical block_opt )
{

  if ( block_opt==YES )
    prop->DeactivateDBEvents();
  else
    prop->ActivateDBEvents();    



}

/******************************************************************************/
/**
\brief  BlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void ODS :: BlockSignals (logical block_opt )
{

BEGINSEQ
  if ( signalsBlocked() == (bool)block_opt )         LEAVESEQ
  
  blockSignals(block_opt);
  
  if ( prop )
  {
    BlockItemEvents(block_opt);
    prop->BlockSignals(block_opt);
  }
    

ENDSEQ

}

/******************************************************************************/
/**
\brief  ChangedCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangedCollection"

logical ODS :: ChangedCollection ( )
{

  return( prop && lastRefID != prop->get_lastRefID() ? YES : NO);



}

/******************************************************************************/
/**
\brief  CheckItem - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckItem"

logical ODS :: CheckItem ( )
{

  return ( this && prop ? prop->CheckItem() : NO );

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

logical ODS :: ColFind (const QString &rcqsKey, logical fConvert_YES )
{

  return (   this && prop 
           ? prop->ColFind(rcqsKey,fConvert_YES)
           : NO );


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

logical ODS :: ColFind (const char *cszKey, logical fConvert_YES )
{

  return (   this && prop 
           ? prop->ColFind(cszKey,fConvert_YES)
           : NO );


}

/******************************************************************************/
/**
\brief  ColGetCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColGetCount"

int32 ODS :: ColGetCount ( )
{

  return ( (this && prop) ? prop->ColGetCount() : 0) ;


}

/******************************************************************************/
/**
\brief  ColGetIndex - 



\return indx0 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColGetIndex"

int32 ODS :: ColGetIndex ( )
{

  return ( this && prop ? prop->ColGetIndex() : -1 );

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

logical ODS :: ColIsValid (logical set_state, logical check_opt )
{

  return ((this && prop) ? prop->ColIsValid(set_state,check_opt) : NO);

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

logical ODS :: ColNext (logical fire_signals )
{

  return (   !this || !prop         ? NO 
           : !path.get_collection() ? YES  
           :                          prop->ColNext(fire_signals) );

}

/******************************************************************************/
/**
\brief  ColPosition - 



\return term - 

\param  indx0 - 
\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColPosition"

logical ODS :: ColPosition (int32 indx0, logical fire_signals )
{

  return (   !this || !prop         ? YES 
           : !path.get_collection() ? NO  
           :                          prop->ColPosition(indx0,fire_signals) );

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

logical ODS :: ColPrev (logical fire_signals )
{

  return (   !this || !prop         ? NO 
           : !path.get_collection() ? YES  
           :                          prop->ColPrev(fire_signals) );

}

/******************************************************************************/
/**
\brief  ColReset - 




\param  fire_signals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColReset"

void ODS :: ColReset (logical fire_signals )
{

  if ( this && prop )
    prop->ColReset();

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

logical ODS :: ColScroll (int32 lIndex, logical fire_signals )
{

  return (   !this || !prop        ? YES 
           : path.get_collection() ? prop->ColScroll(lIndex,fire_signals)
           :                         prop->ColGetIndex() > AUTO ? NO : YES   );


}

/******************************************************************************/
/**
\brief  ColSync - 



\return modified - 

\param  lID - 
\param  lIndexHint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColSync"

logical ODS :: ColSync (int32 lID, int32 lIndexHint )
{
  logical   modified = NO;
  if ( this && prop ) 
  {
    prop->ColSync(lID,lIndexHint);
    modified = SyncInstState();
  }
  return(modified);
}

/******************************************************************************/
/**
\brief  DefinesCollection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DefinesCollection"

logical ODS :: DefinesCollection ( )
{

  return ( this ? path.get_collection() : NO );

}

/******************************************************************************/
/**
\brief  GenerateEvent - 



\return term - 

\param  ogui_db_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical ODS :: GenerateEvent (ADK_DBEVENT ogui_db_event )
{
  OEH                    *oehptr = NULL;
  ODataWidget            *causer = NULL;
  logical                 term = NO;
// *fixme* woher kommt der oeh
  
//  oehptr->GenerateEvent(ogui_db_event,causer);
  return(term);
}

/******************************************************************************/
/**
\brief  GetStructure - 



\return strnames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructure"

char *ODS :: GetStructure ( )
{

  return( path.get_struct_name() );

}

/******************************************************************************/
/**
\brief  GetType - 



\return strnames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetType"

char *ODS :: GetType ( )
{

  return( prop ? prop->GetType() : NULL );

}

/******************************************************************************/
/**
\brief  Handle - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Handle"

PropertyHandle *ODS :: Handle ( )
{

  return this && prop ? prop->get_property() : NULL;

}

/******************************************************************************/
/**
\brief  HasBaseCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasBaseCollection"

logical ODS :: HasBaseCollection ( )
{

  return ( prop && prop->HasBaseCollection() );

}

/******************************************************************************/
/**
\brief  HasColChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasColChanged"

logical ODS :: HasColChanged ( )
{
  logical       cond = NO;
  if ( !path.get_collection() )   
    cond = HasInstChanged();
  
  if ( !cond )
  {
    ColIsValid(NO,NO);
    cond = HasListChanged(prop,Handle());
  }
  return(cond);
}

/******************************************************************************/
/**
\brief  HasInstChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasInstChanged"

logical ODS :: HasInstChanged ( )
{

  return ( HasValueChanged(prop,Handle()) );


}

/******************************************************************************/
/**
\brief  HasSelection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasSelection"

logical ODS :: HasSelection ( )
{

  return ( this ? path.get_selection() : NO );

}

/******************************************************************************/
/**
\brief  InstGetKeyString - 



\return skey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstGetKeyString"

char *ODS :: InstGetKeyString ( )
{

  return (   this && prop 
           ? prop->InstGetKeyString() 
           : NULL                     );

}

/******************************************************************************/
/**
\brief  InstGetObjID - 



\return objid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstGetObjID"

int32 ODS :: InstGetObjID ( )
{

  return (this && prop) ? prop->InstGetObjID() : NULL;

}

/******************************************************************************/
/**
\brief  InstInit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstInit"

void ODS :: InstInit ( )
{

  if ( this && prop )
    prop->InstInit();

}

/******************************************************************************/
/**
\brief  InstIsModified - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstIsModified"

logical ODS :: InstIsModified ( )
{

  return (this && prop) && prop->InstIsModified();

}

/******************************************************************************/
/**
\brief  InstIsReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstIsReadOnly"

logical ODS :: InstIsReadOnly ( )
{

  return !this                 ||
         accessMode == PI_Read || 
         !prop                 || 
         prop->InstIsReadOnly();

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

logical ODS :: InstSave (logical recursive )
{

  return ( (this && prop) ? prop->InstSave(recursive) : YES );


}

/******************************************************************************/
/**
\brief  IsAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttribute"

logical ODS :: IsAttribute ( )
{

  return (   this && prop 
           ? prop->IsAttribute() 
           : NO);

}

/******************************************************************************/
/**
\brief  IsAutoLocate - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoLocate"

logical ODS :: IsAutoLocate ( )
{

  return (   this && prop 
           ? prop->IsAutoLocate() 
           : NO);

}

/******************************************************************************/
/**
\brief  IsBaseCollection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBaseCollection"

logical ODS :: IsBaseCollection ( )
{

  return (   this && prop  
           ? prop->get_path().get_type() == PT_BaseCollection
           : NO );

}

/******************************************************************************/
/**
\brief  IsBool - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBool"

logical ODS :: IsBool ( )
{

  return (   this && prop 
           ? prop->get_is_bool()
           : NO );

}

/******************************************************************************/
/**
\brief  IsCollection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollection"

logical ODS :: IsCollection ( )
{

  return (   this && prop 
           ? prop->IsCollection()
           : NO );

}

/******************************************************************************/
/**
\brief  IsKey - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsKey"

logical ODS :: IsKey ( )
{

  return (   this && prop 
           ? prop->isKey() 
           : NO);

}

/******************************************************************************/
/**
\brief  IsNumber - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNumber"

logical ODS :: IsNumber ( )
{

  return (   this && prop 
           ? prop->get_is_number()
           : NO );

}

/******************************************************************************/
/**
\brief  IsReference - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReference"

logical ODS :: IsReference ( )
{

  return (   this && prop 
           ? prop->IsReference() 
           : NO);

}

/******************************************************************************/
/**
\brief  IsSingleReference - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSingleReference"

logical ODS :: IsSingleReference ( )
{

  return (   this && prop 
           ? prop->IsSingleReference() 
           : NO);

}

/******************************************************************************/
/**
\brief  ItemState - 



\return istate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemState"

ItemStates ODS :: ItemState ( )
{

  return(this ? prop->ItemState() : IST_undefined);

}

/******************************************************************************/
/**
\brief  ListODS - 



\return pODSList - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListODS"

ODSList *ODS :: ListODS ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  ODS - 



\return term - 
-------------------------------------------------------------------------------
\brief  i - 



\param  vDBObjectHandle - 
\param  rODSPropPath - 
\param  active_f - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODS"

     ODS :: ODS (DBObjectHandle &vDBObjectHandle, ODSPropPath &rODSPropPath, logical active_f )
                     : QObject (),
ODSItemState (),
  path(rODSPropPath),
  prop(NULL),
  parentODS(NULL),
  parentDB(NULL),
  parentODSItem(NULL),
  active(NO),
  accessMode(rODSPropPath.get_acc_mode()),
  childODS()
{

  SetParentDB(vDBObjectHandle);

  if ( active_f ) 
    SetActive(YES);
ods_total++;
if ( ods_max < ++ods_count ) ods_max = ods_count;

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODS"

     ODS :: ODS ( )
                     : QObject (),
ODSItemState (),
  path(),
  prop(NULL),
  parentODS(NULL),
  parentDB(NULL),
  parentODSItem(NULL),
  active(NO),
  accessMode(PI_undefined),
  childODS()
{


ods_total++;
if ( ods_max < ++ods_count ) ods_max = ods_count;

}

/******************************************************************************/
/**
\brief  i2 - 



\param  rcODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODS"

     ODS :: ODS (const ODS &rcODS )
                     : QObject (),
ODSItemState (),
  path(rcODS.Path()),
  prop(NULL),
  parentODS(NULL),
  parentDB(NULL),
  parentODSItem(NULL),
  active(NO),
  accessMode(rcODS.accessMode),
  childODS()
{

  if ( rcODS.parentODS ) 
    SetParentODS(rcODS.parentODS);

  if ( ((DBObjectHandle *)&rcODS.parentDB)->IsValid() ) 
    SetParentDB(*(DBObjectHandle *)&rcODS.parentDB);

 if ( rcODS.parentODSItem ) 
   SetParentODSItem(rcODS.parentODSItem);

  SetActive(rcODS.active);
ods_total++;
if ( ods_max < ++ods_count ) ods_max = ods_count;

}

/******************************************************************************/
/**
\brief  i3 - 



\param  pODS - 
\param  rODSPropPath - 
\param  active_f - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODS"

     ODS :: ODS (ODS *pODS, ODSPropPath &rODSPropPath, logical active_f )
                     : QObject (),
ODSItemState (),
  path(rODSPropPath),
  prop(NULL),
  parentODS(NULL),
  parentDB(NULL),
  parentODSItem(NULL),
  active(NO),
  accessMode(pODS->accessMode),
  childODS()
{

  SetParentODS(pODS);

  if ( active_f ) 
    SetActive(YES);
ods_total++;
if ( ods_max < ++ods_count ) ods_max = ods_count;

}

/******************************************************************************/
/**
\brief  ParentDB - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParentDB"

DBObjectHandle &ODS :: ParentDB ( )
{
  static   DBObjectHandle   empty;
  return( this 
          ? parentDB ? parentDB : ParentODS()->ParentDB() 
          : empty );

}

/******************************************************************************/
/**
\brief  ParentODS - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParentODS"

ODS *ODS :: ParentODS ( )
{

  return( this ? parentODS : NULL);

}

/******************************************************************************/
/**
\brief  ParentODSItem - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParentODSItem"

ODSItem *ODS :: ParentODSItem ( )
{

  return( this ? parentODSItem : NULL);

}

/******************************************************************************/
/**
\brief  ProvideItem - 



\return istate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideItem"

ItemStates ODS :: ProvideItem ( )
{

  return(this && prop ? prop->ProvideItem() : IST_undefined);

}

/******************************************************************************/
/**
\brief  RegionODS - 



\return pODSRegion - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegionODS"

ODSRegion *ODS :: RegionODS ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  ResetPropertyHandle - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyHandle"

logical ODS :: ResetPropertyHandle ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  activate(NO);
  
  if ( prop && prop->ResetPropertyHandle() )         ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetActive - 




\param  fActive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActive"

void ODS :: SetActive (logical fActive )
{

BEGINSEQ
  if ( active == fActive )                           LEAVESEQ

  active = fActive;
  activate(active);
  
  if ( !fActive )
    ResetState();

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

logical ODS :: SetFilter (char *expression, logical enable_opt )
{

  path.SetFilter(expression,enable_opt);
  
  return ( prop ? prop->SetFilter(expression,enable_opt) : YES);


}

/******************************************************************************/
/**
\brief  SetItemState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetItemState"

void ODS :: SetItemState ( )
{

  if ( this && prop )
    prop->SetItemState(NO);

}

/******************************************************************************/
/**
\brief  SetParentDB - 




\param  vDBObjectHandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParentDB"

void ODS :: SetParentDB (DBObjectHandle &vDBObjectHandle )
{

BEGINSEQ
  if ( vDBObjectHandle == parentDB )                 LEAVESEQ

  if ( active ) 
    activate(NO);

  parentDB = DBObjectHandle();
  SetParentODS(NULL);
  SetParentODSItem(NULL);
  parentDB = vDBObjectHandle;
  
//  if ( accessMode == PI_undefined )
//    accessMode = parentDB.GetAccess();

  if ( active ) 
    activate(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetParentODS - 




\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParentODS"

void ODS :: SetParentODS (ODS *pODS )
{

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  if ( pODS == parentODS )                           LEAVESEQ

  if ( active ) 
    activate(NO);

  if ( parentODS )
    parentODS->childODS.Remove(this);
  parentODS = NULL;
  DBObjectHandle dbohandle;
  SetParentDB(dbohandle);
  SetParentODSItem((ODSItem*)NULL);
  
  parentODS = pODS;

  if ( parentODS )
    parentODS->childODS.AddTail(this);

  if ( active ) 
    activate(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetParentODSItem - 




\param  pODSItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParentODSItem"

void ODS :: SetParentODSItem (ODSItem *pODSItem )
{
  ODSItem  *old_parent;
BEGINSEQ
  if ( pODSItem == parentODSItem )                   LEAVESEQ

  if ( active ) 
    activate(NO);

  old_parent    = parentODSItem;
  parentODSItem = NULL;

  SetParentODS((ODS*)NULL);
  DBObjectHandle dbohandle;
  SetParentDB(dbohandle);

  if ( pODSItem ) 
    pODSItem->Ref();
  if ( old_parent ) 
    old_parent->Deref();
  parentODSItem = pODSItem;

  if ( active ) 
    activate(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetPath - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prop_path - Property path
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void ODS :: SetPath (char *prop_path, ODSPropertyType prop_type )
{

  SetPath(prop_path,NULL,NO,NULL,prop_type);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  rODSPropPath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void ODS :: SetPath (ODSPropPath &rODSPropPath )
{
  logical    same_path_type;
  same_path_type = path == rODSPropPath ? YES : NO;
    
  if ( !same_path_type && active ) 
    activate(NO);

  path.SetPath(rODSPropPath);
  
  if ( !same_path_type && active ) 
    activate(YES);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  prop_path - Property path
\param  strname - 
\param  is_collection - Is referenced path pointing to a collection
\param  sort_index_name - 
\param  prop_type - Property path  type
\param  accmode_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void ODS :: SetPath (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type, PIACC accmode_w )
{
  ODSPropPath    new_path;
  new_path.SetPath(prop_path,strname,is_collection,sort_index_name,prop_type,accmode_w);
  accessMode = accmode_w;
  
  SetPath(new_path);


}

/******************************************************************************/
/**
\brief  SetPropHdl - 




\param  pODSItem - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropHdl"

void ODS :: SetPropHdl (ODSItem *pODSItem )
{

  if ( prop = pODSItem )
    active = YES;  
  else
  {
    active = NO;
    ResetState();
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

logical ODS :: SetPropertyHandle (PropertyHandle *prophdl )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !prophdl )                                    ERROR
    
  activate(NO);
  
  if ( path.get_type() != PT_none && path.get_type() != PT_SystemVariable)   // neu 24.11.2004 DRT_UserDefined
    path.SetType(PT_undefined);
  
  if ( !(prop = ODSItem::Provide(parentODS->prop,prophdl)) )
                                                    ERROR
  active = YES;
  prop->AddODS(this);
  activate_intern();


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Signal - 



\return term - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Signal"

logical ODS :: Signal (char *names )
{
  logical                 term = NO;
BEGINSEQ
  if ( !strcmp(names,"OnCollectionChanged") )
    emit OnCollectionChanged();
  else if ( !strcmp(names,"OnCollectionReset") )
    emit OnCollectionReset();
  else if ( !strcmp(names,"OnCollectionUpdated") )
    emit OnCollectionUpdated();
  else if( !strcmp(names,"OnInstanceSelected") )
    emit OnInstanceSelected();
  else if( !strcmp(names,"OnInstanceInserted") )
    emit OnInstanceInserted();
  else if( !strcmp(names,"OnInstanceUpdated") )
    emit OnInstanceUpdated();
  else                                               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SyncColState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncColState"

logical ODS :: SyncColState ( )
{
  logical         modified = HasColChanged();
BEGINSEQ
  if ( !prop )                                       LEAVESEQ
  
  if ( !path.get_collection() )   
    SyncInstState();
    
  SyncList(prop);
  
  if ( refModCount == AUTO ) 
    refModCount = Handle()->GetRefModCount();

ENDSEQ
  return(modified);
}

/******************************************************************************/
/**
\brief  SyncInstState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncInstState"

logical ODS :: SyncInstState ( )
{
  logical         modified = HasInstChanged();
BEGINSEQ
  if ( !prop )                                       LEAVESEQ
    
  SyncValue(prop);

  if ( lastObjID > 0 && instModCount == AUTO ) 
    instModCount = Handle()->GetInstModCount();

ENDSEQ
  return(modified);
}

/******************************************************************************/
/**
\brief  SyncState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncState"

logical ODS :: SyncState ( )
{

  return( SyncInstState() || SyncColState() );

}

/******************************************************************************/
/**
\brief  Value - 



\return value - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Value"

QString ODS :: Value ( )
{

  return( this ? prop->Value() : QString() );

}

/******************************************************************************/
/**
\brief  ValueGetDate - 



\return date - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetDate"

dbdt ODS :: ValueGetDate ( )
{

  return( this ? prop->ValueGetDate() : dbdt() );

}

/******************************************************************************/
/**
\brief  ValueGetInt - 



\return number - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetInt"

int32 ODS :: ValueGetInt ( )
{

  return( this ? prop->ValueGetInt() : 0 );

}

/******************************************************************************/
/**
\brief  ValueGetString - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetString"

char *ODS :: ValueGetString ( )
{

  return( this ? prop->ValueGetString() : "");

}

/******************************************************************************/
/**
\brief  ValueGetTime - 



\return time - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueGetTime"

dbtm ODS :: ValueGetTime ( )
{

  return( this ? prop->ValueGetTime() : dbtm() );

}

/******************************************************************************/
/**
\brief  ValueInit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueInit"

void ODS :: ValueInit ( )
{

  if ( this )
    prop->ValueInit();

}

/******************************************************************************/
/**
\brief  ValueIsTrue - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueIsTrue"

logical ODS :: ValueIsTrue ( )
{

  return( this ? prop->ValueIsTrue() : NO);

}

/******************************************************************************/
/**
\brief  ValueIsUpdated - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueIsUpdated"

logical ODS :: ValueIsUpdated ( )
{

  return (this && prop->ValueIsUpdated());

}

/******************************************************************************/
/**
\brief  ValueIsValid - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueIsValid"

logical ODS :: ValueIsValid ( )
{

  return( this ? prop->ValueIsValid() : NO );

}

/******************************************************************************/
/**
\brief  ValueReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueReset"

void ODS :: ValueReset ( )
{

  if ( this )
    prop->ValueReset();

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

logical ODS :: ValueSet (const QString &rcqsText )
{

  return( this ? prop->ValueSet(rcqsText) : NO );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODS :: ValueSet (char *string )
{

  return( this ? prop->ValueSet(string) : NO );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODS :: ValueSet (int32 number )
{

  return( this ? prop->ValueSet(number) : NO );

}

/******************************************************************************/
/**
\brief  i03 - 



\param  cond - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODS :: ValueSet (logical cond )
{

  return( this ? prop->ValueSet(cond) : NO );

}

/******************************************************************************/
/**
\brief  i04 - 



\param  date - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODS :: ValueSet (dbdt date )
{

  return( this ? prop->ValueSet(date) : NO );

}

/******************************************************************************/
/**
\brief  i05 - 



\param  time - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSet"

logical ODS :: ValueSet (dbtm time )
{

  return( this ? prop->ValueSet(time) : NO );

}

/******************************************************************************/
/**
\brief  ValueStore - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueStore"

void ODS :: ValueStore ( )
{

  if ( this && prop )
    prop->ValueStore();

}

/******************************************************************************/
/**
\brief  activate - 




\param  fActivate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "activate"

void ODS :: activate (logical fActivate )
{
  ODS      *c;
  logical   cs = YES;

BEGINSEQ
  if ( fActivate )
  {
if ( prop )
  cs = YES;
    if ( parentODS )
    {
      if ( parentODS->IsActivated() || path.get_type() == PT_none )  // neu 24.11.2004
        prop = ODSItem::Provide(parentODS->prop,path,ParentDB());
    }
    else if ( parentODSItem )
      prop = ODSItem::Provide(parentODSItem,path,ParentDB());
    else if ( parentDB.IsValid() )
      prop = ODSItem::Provide(parentDB,path);
    else; // !parentODSItem for setPropertyHandle of root element, weak-typed??
//      prop = ODSItem::Provide();
  
    if ( !prop )                                     LEAVESEQ
  
    prop->AddODS(this);
    activate_intern();    
  }
  else
  {
// *fixme* this may to be reviewed (order of events during children activate)
    {
      DLL(ODS)  it(childODS);
      while( c = it.GetNext() )
        if ( c->active && c->prop ) 
          c->activate(NO);
    }
  
    if ( !prop )                                     LEAVESEQ
    prop->RemODS(this);

    prop->InstStore();
    prop->Deref();
    prop = NULL;
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  activate_intern - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "activate_intern"

void ODS :: activate_intern ( )
{
  ODS      *c;
  logical   cs = YES;

BEGINSEQ
  if ( !prop )                                      ERROR
  
  if ( path.GetOrder() ) 
  {
    prop->SetSortKey(path.GetOrder());  // das dürfen nur die Originale. Sonst setzt jeder was anderes
    prop->ColSetOrder();
  }
  
// *fixme* this may to be reviewed (order of events during children activate)

  emit OnActivated(YES);
  
  {
    DLL(ODS)  it(childODS);
    while( c = it.GetNext() )
      if ( c->active && !c->prop ) 
        c->activate(YES);
  }   
  
  if ( Handle()->IsValid() )
    emit OnHandleOpened();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ODS - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODS"

     ODS :: ~ODS ( )
{
  ODS      *child_ods = NULL;
  while ( child_ods = childODS.GetHead() ) 
    child_ods->SetParentODS(NULL);

  SetActive(NO);
  SetParentODSItem(NULL);
  SetParentODS(NULL);
ods_count--;
}


