/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OListCtl

\brief    


\date     $Date: 2006/08/26 17:49:59,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OListCtl"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sCellData.hpp>
#include  <sDPixmap.hpp>
#include  <sFFileDialog.hpp>
#include  <sItemData.hpp>
#include  <sODSPropPath.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHEvent.hpp>
#include  <sOHeaderView.hpp>
#include  <sOItemDelegate.hpp>
#include  <sOListCtl.hpp>
#include  <sOListLayout.hpp>
#include  <sOPixmap.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOTreeLayout.hpp>
#include  <sPropertyHandle.hpp>
#include  <sQAbstractItemView.hpp>
#include  <scfte.hpp>
#include  <standard.hpp>
#include  <sOListCtl.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OListCtl :: Activate ( )
{
  logical                 term = NO;
BEGINSEQ
/*
  if ( stscini() )                                   
  {
    listCache.Activate();
    LEAVESEQ
  }
*/  
  if ( !olayout )                                    OGUIERR(99)
  if ( !olayout->get_columns() )
    olayout->AddColumn(NULL,NULL,NO,NULL,PT_Key);
  
  ODSPropPath  save_path(*olayout);
  olayout->SetPath(NULL,NULL,save_path.get_collection(),NULL,PT_Self);
  if ( listCache.SetLayout(olayout) )
    term = YES;
  olayout->SetPath(save_path);
    
  listCache.Activate();

  if ( OEHControlList::ActivateList(YES) )
    term = YES;
 
  if ( !olayout->DisplayHeader() && Header() )
    Header()->hide();
  else
    UpdateLayout();
  

RECOVER
  term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddRegion - 



\return region_id - 

\param  parent_id - 
\param  prop_path - Property path
\param  is_collection - Is referenced path pointing to a collection
\param  text - 
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

int32 OListCtl :: AddRegion (int32 parent_id, char *prop_path, logical is_collection, char *text, ODSPropertyType prop_type )
{
  OTreeLayout   *region = GetLayout()->AddRegion(parent_id,prop_path,is_collection,prop_type);
  if ( text && region )
    region->SetStaticText(text);

  return( region ? region->get_intern_id() : UNDEF );

}

/******************************************************************************/
/**
\brief  BookmarkRestore - 



\return cond - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BookmarkRestore"

logical OListCtl :: BookmarkRestore (int32 indx0 )
{
logical                              cond      = YES;
std::vector<StringVector>::iterator  bi;
ItemData                            *canitem   = NULL;

BEGINSEQ
if( bookmarks.size() < indx0 && indx0>0)            ERROR

canitem = PersistentItemRestore(bookmarks[indx0]);

if(canitem){
  SetCurrentItem(canitem);
}else{
  // remove item from bookmarks
  for(bi = bookmarks.begin();bi!=bookmarks.end();bi++)
    if(*bi == bookmarks[indx0])
      bookmarks.erase(bi);  
}
RECOVER
cond = NO;
ENDSEQ
return cond;
}

/******************************************************************************/
/**
\brief  DA_BookmarkNext - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BookmarkNext"

void OListCtl :: DA_BookmarkNext ( )
{
logical cond = YES;
StringVector begin;
BEGINSEQ
if( bookmarks.size() == 0 )                         ERROR
begin = StringVector(bookmarks[0]);
bookmarks.push_back(begin);
bookmarks.erase(bookmarks.begin());

BookmarkRestore(0);

RECOVER
cond = NO;
ENDSEQ
//return cond;
}

/******************************************************************************/
/**
\brief  DA_BookmarkPrevious - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BookmarkPrevious"

logical OListCtl :: DA_BookmarkPrevious ( )
{
logical cond = YES;
StringVector last;
BEGINSEQ
if(bookmarks.size()==0)                             ERROR
last = StringVector(bookmarks.back());
bookmarks.insert(bookmarks.begin(),last);
bookmarks.pop_back();

BookmarkRestore(0);
RECOVER
cond = NO;
ENDSEQ
return cond;
}

/******************************************************************************/
/**
\brief  DA_BookmarkRemove - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BookmarkRemove"

logical OListCtl :: DA_BookmarkRemove ( )
{
logical cond = YES;
StringVector bookmark;
std::vector<StringVector>::iterator bi;
ItemData *curitem = NULL;
logical removed = NO;
BEGINSEQ
if(bookmarks.size()==0)                              ERROR
curitem = GetCurrentItem();
if(curitem)
  curitem->GetHierarchyPath(bookmark);

for(bi = bookmarks.begin();bi!=bookmarks.end()&&!removed;bi++)
  if((*bi) == bookmark){
    bookmarks.erase(bi);
    removed=YES;    
  }

settings.Store(SZ2QS("bookmarks"),bookmarks);
settings.Store();


if(!removed){ // the current element is not selected or damaged
  removed = YES;
}
  

RECOVER
cond = NO;
ENDSEQ
return cond;
}

/******************************************************************************/
/**
\brief  DA_BookmarkStore - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BookmarkStore"

logical OListCtl :: DA_BookmarkStore ( )
{
logical cond = YES;
StringVector bookmark;
std::vector<StringVector>::iterator bi;
logical available = NO;

PersistentItem(GetCurrentItem(),bookmark);

for(bi = bookmarks.begin();bi!=bookmarks.end()&&!available;bi++)
  if((*bi) == bookmark)
      available=YES;    

if(!available)
  bookmarks.push_back(StringVector(bookmark));

// store to registry
settings.Store(SZ2QS("bookmarks"),bookmarks);
settings.SetTimeout(SZ2QS("bookmarks"),"application");
return cond;
}

/******************************************************************************/
/**
\brief  DA_CSVExport - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_CSVExport"

logical OListCtl :: DA_CSVExport ( )
{
 logical term = NO;
 std_string str_file, sdata;
 int ccount,rcount,r,c;
 QAbstractItemModel *m;
 QModelIndex         mi;
 QString             qsdata;
 QVariant            qvdata;
BEGINSEQ
  SetBusy(YES);
  m = &listCache;
  if(!m)                                            ERROR
  if ( str_file=="" ){  // change from context
    FFileDialog fd(this,this,(ODS*)NULL,"e:\\","*.csv");
    if(fd.Save())                                   ERROR
    str_file=fd.GetFilename(true).toStdString();
  }
  std::ofstream csvf(str_file.c_str(),std::ios::out);  
  if(csvf.bad())                                    ERROR
  
  rcount = m->rowCount();
  ccount = m->columnCount();
  // header
  for(c = 0; c < ccount; c++){
    if(c!=0) csvf << ";"; // separator
    csvf << "\"" ;        // text 
     // escape 
    qvdata = m->headerData(c,Qt::Horizontal);
    qsdata = qvdata.toString();
    sdata  = qsdata.toStdString();   
    csvf << sdata;        
    csvf << "\"";         // text
  }
  csvf << std::endl;
  // data
  for(r = 0; r < rcount; r++){
    for(c = 0; c < ccount; c++){
      if(c!=0) csvf << ";"; // separator
      csvf << "\"" ;        // text 
      mi = m->index(r,c);
      // escape || convert to std
      qvdata = m->data(mi);
      if(qvdata==QVariant()){
        qvdata = m->data(mi,Qt::CheckStateRole);
        sdata = qvdata.toBool()?"1":"0";
      }else{
        sdata = std_string(qvdata.toString().toAscii().constData());
      }
      csvf << sdata;        
      csvf << "\"";         // text
    }
    csvf << std::endl;
  }
  csvf.close();

RECOVER
  term = YES;
ENDSEQ
  SetBusy(NO);
  return term;
}

/******************************************************************************/
/**
\brief  DA_FindEntry - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OListCtl :: DA_FindEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetSearchString(this,NULL,NULL) )            ERROR
  
  term = DA_NewFindEntry();

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical OListCtl :: DA_FindEntry (char *skey, logical cur_opt )
{

  return ( OEHControlList::DA_FindEntry(skey,cur_opt) );

}

/******************************************************************************/
/**
\brief  DA_HistoryNext - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_HistoryNext"

void OListCtl :: DA_HistoryNext ( )
{

HistoryRestore(history_index+1);

}

/******************************************************************************/
/**
\brief  DA_HistoryPrevious - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_HistoryPrevious"

void OListCtl :: DA_HistoryPrevious ( )
{

if(history_index == history.size()-1)
  HistoryStore();
HistoryRestore(history_index-1);

}

/******************************************************************************/
/**
\brief  DA_NewFindEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_NewFindEntry"

logical OListCtl :: DA_NewFindEntry ( )
{
  ItemData      *item_data = NULL;
  logical        term      = NO;
BEGINSEQ
  if ( find_text.isEmpty() ) 
    term = DA_FindEntry();
  else
  {  
//  j recursive lohnt ganz selten
//    if ( !(item_data = LocateItem(find_text,YES)) )  ERROR
    if ( !(item_data = LocateItem(find_text,NO)) )  ERROR
    SetCurrentItem(item_data);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Refresh - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Refresh"

logical OListCtl :: DA_Refresh ( )
{

  listCache.ResetState();
  listCache.ClearData(NO);
  
// kann sein, dass wir das SelectionModel beim Refresh Clearen müssen. Dann kann das aus DA_Reset raus
//  if ( item_view )
//    item_view->selectionModel()->clear();

  OEHControlList::DA_Refresh();
  if ( ItemViewQ() )
    SetCurrentItem(ItemViewQ()->currentIndex());
  return(NO);
}

/******************************************************************************/
/**
\brief  DA_Reset - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Reset"

logical OListCtl :: DA_Reset ( )
{
  QAbstractItemView  *item_view = ItemViewQ();
// wer ruft denn dieses Teil auf???
  bookmarks.clear();
    
  if ( item_view )
    item_view->selectionModel()->clear();
  
  DA_Refresh();
  return(NO);
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

logical OListCtl :: Deactivate (logical data_only )
{

  listCache.Deactivate();
  
  OEHControlList::DeactivateList(YES,data_only);

  listCache.ClearData(NO);

  return(NO);
}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return executed - 

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 OListCtl :: ExecuteAction (char *act_names )
{
  char      actname[ID_SIZE];
  cfte     *cfteptr;
  int8      executed = AUTO;  // action not found
BEGINSEQ
  static cfte acttbl[] = 
  { 
    cfte( "BookmarkStore",           ALINK( this, OListCtl, DA_BookmarkStore ) ), 
    cfte( "BookmarkRemove",          ALINK( this, OListCtl, DA_BookmarkRemove ) ), 
    cfte( "BookmarkNext",            ALINK( this, OListCtl, DA_BookmarkNext ) ), 
    cfte( "BookmarkPrevious",        ALINK( this, OListCtl, DA_BookmarkPrevious ) ), 
    cfte( "HistoryNext",             ALINK( this, OListCtl, DA_HistoryNext ) ), 
    cfte( "HistoryPrevious",         ALINK( this, OListCtl, DA_HistoryPrevious ) ), 
    cfte( "CSVExport",               ALINK( this, OListCtl, DA_CSVExport ) ), 
  };
  static srt  cftesrt( sizeof( acttbl )/CFTE, CFTE, UNDEF, UNDEF, UNDEF, (char * )acttbl, NO );

  if ( !cftesrt.srtkln( ) )
    cftesrt.srtsor( CFTE_KPS, CFTE_KLN, CFTE_KTP );

  if ( cfteptr = (cfte * )cftesrt.srtigt( cftesrt.srtssr( gvtxstb( actname, act_names, ID_SIZE ) ) ) )
  {
    cfteptr->LINKINST( this );
    if ( cfteptr->ActionCall( ) )
      ; // *fixme* nachrichtenausgabe   OGUIDISPLAY_ERROR
      
    executed = YES;
  }
  else
    executed = OEHDataWidget::ExecuteAction(act_names);
  

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  ExpandIndex - 



\return term - 

\param  model_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpandIndex"

logical OListCtl :: ExpandIndex (const QModelIndex &model_index )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  FillData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OListCtl :: FillData ( )
{


BEGINSEQ
  if ( !listCache.get_path().get_collection() )      LEAVESEQ
  SetCurrentItem(listCache.ItemByDBIndex(ods()->get_lastIndex(),YES));
ENDSEQ

}

/******************************************************************************/
/**
\brief  FillList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillList"

void OListCtl :: FillList ( )
{
  PropertyHandle *ph = NULL;
BEGINSEQ
  UpdateState(); 
  
  if ( !listCache.get_prop() )                       ERROR
  
  if ( ph = listCache.Handle() )
    ph->StartRTA();
  updateListData(); 
  if ( ph )
    ph->StopRTA(YES);
RECOVER
  List()->ResetState();
ENDSEQ

}

/******************************************************************************/
/**
\brief  FocusInEvent - 



\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusInEvent"

int8 OListCtl :: FocusInEvent ( )
{
  logical  save_result = NO;
  int8     executed    = NO;
  save_result = DA_Save();
    
  executed = OEHDataWidget::FocusInEvent();

  stssmod();
  return(!executed ? save_result : executed);
}

/******************************************************************************/
/**
\brief  GetCurrentItem - 



\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentItem"

ItemData *OListCtl :: GetCurrentItem ( )
{
  QAbstractItemView  *item_view = ItemViewQ();
  return (   item_view 
           ? listCache.Item(item_view->currentIndex())
           : cur_item );

}

/******************************************************************************/
/**
\brief  GetCurrentPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentPropertyHandle"

PropertyHandle *OListCtl :: GetCurrentPropertyHandle ( )
{

  return ( cur_item 
           ? cur_item->Handle() 
           : listCache.get_path().get_collection() 
             ? listCache.Handle()
             : listCache.Region(0)->Handle() );


}

/******************************************************************************/
/**
\brief  GetCurrentRegionID - 



\return region_id - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentRegionID"

int32 OListCtl :: GetCurrentRegionID ( )
{
  ItemData             *item_data = cur_item ? cur_item : GetCurrentItem();
  return( item_data 
          ? item_data->get_region()->get_region()->GetLayout()->get_intern_id()
          : UNDEF );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  parent_id - 
\param  prop_path - Property path
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentRegionID"

int32 OListCtl :: GetCurrentRegionID (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type )
{
  int32   region_id;

  return(region_id);
}

/******************************************************************************/
/**
\brief  GetLineFont - 



\return DFont - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLineFont"

DFont OListCtl :: GetLineFont (int column )
{

  return (   cur_item->HasLayout(column)
           ? cur_item->GetLayout(column)
           : OWidget::GetFont()         ); 


}

/******************************************************************************/
/**
\brief  GetListControl - 



\return pOListCtl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListControl"

OListCtl *OListCtl :: GetListControl ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetListLayout - 



\return pOTreeLayout - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListLayout"

OTreeLayout *OListCtl :: GetListLayout ( )
{

  return(GetLayout());

}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return prop_hdl - 

\param  pODSPropPath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *OListCtl :: GetPropertyHandle (ODSPropPath *pODSPropPath )
{


  return(listCache.GetPropertyHandle(pODSPropPath));


}

/******************************************************************************/
/**
\brief  GetSelectedODS - 



\return pODS - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedODS"

ODS *OListCtl :: GetSelectedODS ( )
{

  return ( cur_item 
           ? cur_item->Region()
           : listCache.get_path().get_collection() 
             ? &listCache
             : listCache.Region(0) );


}

/******************************************************************************/
/**
\brief  GetSelectedPropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedPropertyHandle"

PropertyHandle *OListCtl :: GetSelectedPropertyHandle ( )
{

  return ( GetCurrentPropertyHandle() );

// Fuer Multiselection in ueber mehrere Regions koennte es abweichen, 
// falls nicht vor jeder Anforderung (bei multi ist die Frage welcher!!)
// cur_item gesetzt wird

// *** kann ggf. raus. wenn multiselektion geklaert ist

}

/******************************************************************************/
/**
\brief  GetSubRegionCount - 



\return count - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int OListCtl :: GetSubRegionCount (int32 region_id )
{

  return( GetLayout()->GetSubRegionCount(region_id) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  parent_id - 
\param  prop_path - Property path
\param  ref_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubRegionCount"

int OListCtl :: GetSubRegionCount (int32 parent_id, char *prop_path, ADK_DataReferenceType ref_type )
{
  int   count;

  return(count);
}

/******************************************************************************/
/**
\brief  Header - 



\return pOHeaderView - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Header"

OHeaderView *OListCtl :: Header ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  HistoryRestore - 




\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HistoryRestore"

void OListCtl :: HistoryRestore (int32 indx0 )
{
  ItemData *canitem = NULL;
BEGINSEQ
if( indx0>=history.size() || indx0<0 )               ERROR
canitem = PersistentItemRestore(history[indx0]);
if(!canitem)                                         ERROR
SetCurrentItem(canitem);
history_index = indx0;
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  HistoryStore - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HistoryStore"

void OListCtl :: HistoryStore ( )
{
StringVector hentry;
BEGINSEQ
// delete everything after the current hindex
if(history_index != history.size()-1)
 while(history.size() && history.size()-1>history_index )
  history.pop_back();
// delete the oldest
while(history.size()>20)
  history.erase(history.begin());
// create a persistent restorable item
PersistentItem(GetCurrentItem(),hentry);
// dont store it if its the last
if(history.size() && history.back() == hentry)      LEAVESEQ
// store to history
history.push_back(StringVector(hentry));
history_index = history.size()-1;
settings.Store(SZ2QS("history"),history);
settings.SetTimeout(SZ2QS("history"),"runtime");
ENDSEQ

}

/******************************************************************************/
/**
\brief  Initialize - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OListCtl :: Initialize ( )
{

  listCache.SetHandler(this);
  listCache.SetParentODS(ods()); 
   
  settings.Restore(SZ2QS("bookmarks"),bookmarks); // bookmarks
  settings.Restore(SZ2QS("history"),history);     // history restore
  if(history.size())
    history_index = history.size()-1;
  else 
    history_index = 0;

}

/******************************************************************************/
/**
\brief  i01 - 



\param  multi_sel - 
\param  sort_order - 
\param  check_items - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OListCtl :: Initialize (logical multi_sel, int8 sort_order, logical check_items )
{
  QAbstractItemView  *item_view = ItemViewQ();
  listCache.set_check_box(check_items);
  
  if ( item_view )
  {
    item_view->setAcceptDrops(true);
    item_view->setModel(&listCache);
    item_view->setSelectionMode(   multi_sel 
                      ? QAbstractItemView::ExtendedSelection 
                      : QAbstractItemView::SingleSelection);
    SetSorting(sort_order);
    
    item_view->setItemDelegate(new OItemDelegate(this));
  }

}

/******************************************************************************/
/**
\brief  IsItemExpanded - 



\return cond - 

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemExpanded"

logical OListCtl :: IsItemExpanded (ItemData *pItemData )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsTransposed - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTransposed"

logical OListCtl :: IsTransposed ( )
{

  return ( listCache.get_transposed() );

}

/******************************************************************************/
/**
\brief  ItemViewQ - 



\return pQAbstractItemView - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemViewQ"

QAbstractItemView *OListCtl :: ItemViewQ ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  LocateItem - 



\return pItemData - ItemData
-------------------------------------------------------------------------------
\brief  i0 - 



\param  model_index - 
\param  rcqsText - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateItem"

ItemData *OListCtl :: LocateItem (const QModelIndex &model_index, const QString &rcqsText, logical recursive )
{
  QModelIndexList   indexes;
  Qt::MatchFlags    search_flags(Qt::MatchStartsWith);
  ItemData         *pItemData = cur_item;
  char             *skey      = NULL;
BEGINSEQ
  if ( skey = pItemData->GetKey() )
    if ( !rcqsText.compare(skey) )                   LEAVESEQ
    
  if ( recursive )
    search_flags = search_flags | Qt::MatchRecursive;  // | Qt::MatchCaseSensitive;

/* this code will crash qt at some list destructor * /
  indexes = listCache.match(model_index,
                            Qt::DisplayRole,rcqsText,1,search_flags);

  if ( indexes.isEmpty() )                           ERROR
  pItemData = ((CellData *)indexes.at(0).internalPointer())->Item(); 
  //indexes.removeAt(0);
  indexes.clear();
/ * */

  // this is slower but hopefuly more reliable
  // but for its simplicity not recursive
  QModelIndex indx,p;
  if(!model_index.isValid())
    indx = listCache.index(0,0);
  else
    indx = model_index;
  logical     matched  = false,looped = false;
  QVariant    data;
  QString     sdata;
  QString     qsPattern(rcqsText);
  qsPattern+=".*";
  QRegExp     rx(qsPattern,Qt::CaseInsensitive);
  int         r = indx.row(),c = indx.column();
  p = indx.parent();
  while(!matched && indx.isValid()){
    data = listCache.data(indx,Qt::DisplayRole);
    sdata = data.toString();
    if(rx.indexIn(sdata)==0) //matched at first character
      matched = true;
    else{
      r++;
      indx = listCache.index( r, c, p);
      if(!indx.isValid()&&!looped){
        indx = listCache.index( 0, c, p);
        looped = true;
        r = 0;
      }
    }                            
  }
  if(matched){
    pItemData = ((CellData *)indx.internalPointer())->Item(); 
  }

RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  rcqsText - 
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateItem"

ItemData *OListCtl :: LocateItem (const QString &rcqsText, logical recursive )
{

  return LocateItem(listCache.index(0,0)
                   ,rcqsText
                   ,recursive);


}

/******************************************************************************/
/**
\brief  LocateKey - 



\return pItemData - ItemData

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

ItemData *OListCtl :: LocateKey (char *skey )
{
  ItemData         *pItemData = NULL;
  pItemData = listCache.ItemByKey(NULL,skey,NO);
  SetCurrentItem(pItemData);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  LocateRow - 



\return pItemData - ItemData

\param  row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateRow"

ItemData *OListCtl :: LocateRow (int row )
{
  ItemData         *pItemData = NULL;
  pItemData = listCache.ItemByRow(row);
  SetCurrentItem(pItemData);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  LocateValue - 



\return pItemData - ItemData

\param  pQString - 
\param  col - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateValue"

ItemData *OListCtl :: LocateValue (QString &pQString, int col )
{
  ItemData         *pItemData = NULL;
  pItemData = listCache.ItemByValue(NULL,pQString,col);
  SetCurrentItem(pItemData);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  NextItem - 



\return pItemData - ItemData

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextItem"

ItemData *OListCtl :: NextItem (ItemData *pItemData )
{
  int          row = 0;
  QModelIndex  index;  
  QModelIndex  parent;
BEGINSEQ
  if ( pItemData )
  {
    index  = pItemData->GetModelIndex();
    row    = index.row()+1;
    parent = index.parent();
  }

  index = listCache.index(row,0,parent);
  
  if ( !index.isValid() )                            ERROR
  
  pItemData = listCache.Item(index);
RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  OListCtl - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListCtl"

     OListCtl :: OListCtl (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : ODSTreeHandler (),
OEHControlList (pODataWidget,oODataWidget,create_ods),
  listCache(this),
  bookmarks(),
  history(),
  history_index(0),
  settings(SZ2QS("OListCtl"),this),
  itemViewOptions()
{

BEGINSEQ
  OGUICERR
  Initialize();
RECOVER

ENDSEQ

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
#define    MOD_ID  "OListCtl"

     OListCtl :: OListCtl (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : ODSTreeHandler (),
OEHControlList (pODataWidget,oODataWidget,pODS),
  listCache(this),
  bookmarks(),
  history(),
  history_index(0),
  settings(SZ2QS("OListCtl"),this),
  itemViewOptions()
{

BEGINSEQ
  OGUICERR
  Initialize();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  PersistentItem - 




\param  pItemData - ItemData
\param  rStringVector - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PersistentItem"

void OListCtl :: PersistentItem (ItemData *pItemData, StringVector &rStringVector )
{

BEGINSEQ
if(!pItemData)                                      ERROR

pItemData->GetHierarchyPath(rStringVector);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  PersistentItemRestore - 



\return pItemData - 

\param  crStringVector - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PersistentItemRestore"

ItemData *OListCtl :: PersistentItemRestore (const StringVector &crStringVector )
{
StringVector::const_reverse_iterator it;
std::vector<StringVector>::iterator  bi;
ItemData                            *curitem   = NULL;
ItemData                            *canitem   = NULL;
QModelIndex                          indx      = QModelIndex();

indx = listCache.index(0,0);

for(it = crStringVector.rbegin();crStringVector.rend()!=it && indx.isValid();it++){
  // find the item with the keyval 
  curitem = LocateItem(indx,QString((*it).c_str()),false);
  if(curitem){
    canitem = curitem;
    indx = listCache.index(0,0,canitem->GetModelIndex());
  }else{
    canitem = NULL;
    break;
  }
}

  return canitem;
}

/******************************************************************************/
/**
\brief  PreviousItem - 



\return pItemData - ItemData

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PreviousItem"

ItemData *OListCtl :: PreviousItem (ItemData *pItemData )
{
  int          row = 0;
  QModelIndex  index;  
  QModelIndex  parent;
BEGINSEQ
  if ( pItemData )
  {
    index  = pItemData->GetModelIndex();
    row    = index.row()-1;
    parent = index.parent();
  }
  else
    row = listCache.rowCount()-1;

  index = listCache.index(row,0,parent);
  
  if ( !index.isValid() )                            ERROR
  
  pItemData = listCache.Item(index);
RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
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

logical OListCtl :: ProvideContextMenu (QObject *watched )
{
  logical   term = NO;
  StringVector::iterator bit;
  std::vector<StringVector>::iterator blit;
  OPopupMenu *bookmark_context_menu = NULL;
  OPopupMenu *history_context_menu = NULL;
  QString      qsText;

BEGINSEQ
  term = OEHControlList::ProvideContextMenu(watched);
  if(term)                                          ERROR
  LEAVESEQ
  // update the contextmenu for bookmarks and history
  if(bookmark_context_menu) 
    delete bookmark_context_menu;
  bookmark_context_menu = new OPopupMenu(this,this);
  bookmark_context_menu->setTitle("Bookmarks");
  for(blit=bookmarks.begin();blit!=bookmarks.end();blit++){
	  qsText = "";
	  for(bit=(*blit).begin();bit!=(*blit).end();bit++){
	    qsText+=SZ2QS((*bit).c_str());
	  }
	  bookmark_context_menu->addAction(qsText);
  }
  if(context_menu)
    context_menu->insertMenu(context_menu->menuAction(),bookmark_context_menu);  
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReceiveSelectedItem - 



\return prop_hdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReceiveSelectedItem"

PropertyHandle *OListCtl :: ReceiveSelectedItem ( )
{
  PropertyHandle *   prop_hdl = NULL;
  ItemData       *   item     = NULL;
BEGINSEQ
// geht z.Z. nur für CheckLists, nicht für multi-selection!!

  while ( item = NextItem(item) ) 
    if ( item->IsChecked() )
    {
      item->HierSync(YES);
      listCache.SetCurItem(item);
      prop_hdl = GetCurrentPropertyHandle();
      item->ToggleChecked();                      
      LEAVESEQ
    }

ENDSEQ
  return(prop_hdl);
}

/******************************************************************************/
/**
\brief  RefreshCurrentRegion - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshCurrentRegion"

void OListCtl :: RefreshCurrentRegion ( )
{
  ItemData             *item_data = cur_item ? cur_item : GetCurrentItem();
  if ( item_data ) 
    item_data->get_region()->get_region()->RefreshRegion(UNDEF);


}

/******************************************************************************/
/**
\brief  RefreshRegion - 




\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshRegion"

void OListCtl :: RefreshRegion (int32 region_id )
{

  if ( region_id == AUTO )
    RefreshCurrentRegion();
  else if ( region_id )
    listCache.RefreshRegion(region_id);
  else
  {
    listCache.SetLayout(GetLayout());
//    UpdateLayout(); // header actualisieren
  }

}

/******************************************************************************/
/**
\brief  ReplaceSubRegions - 



\return region_id - 

\param  parent_id - 
\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSubRegions"

int32 OListCtl :: ReplaceSubRegions (int32 parent_id, int32 region_id )
{
  OTreeLayout   *region = GetLayout()->ReplaceSubRegions(parent_id,region_id);
  return( region ? region->get_intern_id() : UNDEF );

}

/******************************************************************************/
/**
\brief  ResetRegion - 



\return term - 

\param  parent_id - 
\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRegion"

logical OListCtl :: ResetRegion (int32 parent_id, int32 region_id, logical reset_columns )
{

  listCache.RemoveRegion(parent_id,region_id,reset_columns);
  GetLayout()->ResetRegion(parent_id,region_id,reset_columns);
  
  lastODS    = NULL;
  cur_item   = NULL;
  lastInstID = UNDEF;

  return(NO);
}

/******************************************************************************/
/**
\brief  SetCurrentItem - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentItem"

void OListCtl :: SetCurrentItem (ItemData *pItemData )
{
  BEGIN_ONCE(ignore)
  QAbstractItemView  *item_view = ItemViewQ();
BEGINSEQ
  if ( !pItemData )                                  LEAVESEQ
  
  cur_item = pItemData;
  
  if ( item_view )
  {
    QModelIndex  mindex = pItemData->GetModelIndex();
    
    item_view->setCurrentIndex(mindex);
    doCurrentChanged(pItemData);  
    
//    item_view->selectionModel()->select(mindex,QItemSelectionModel::Select);
    item_view->selectionModel()->select(mindex,QItemSelectionModel::Rows);
    item_view->scrollTo(mindex,QAbstractItemView::EnsureVisible);
  }

ENDSEQ
  END_ONCE

}

/******************************************************************************/
/**
\brief  i01 - 



\param  qt_current - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentItem"

void OListCtl :: SetCurrentItem (const QModelIndex &qt_current )
{
  ItemData         *item = ((CellData *)qt_current.internalPointer())->Item();
  if ( item )
  {
    SetCurrentItem(item);
    item->HierSync(YES);  // stellt item ein, aber das kann zuviel sein
  }


}

/******************************************************************************/
/**
\brief  SetDefaultReactions - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OListCtl :: SetDefaultReactions ( )
{
  logical   term = NO;
  OEHControlList::SetDefaultReactions();
  

  SetGUIDefReaction("...nav","...nav","___ContextMenu");
  SetGUIDefReaction("BookmarkStore"                 ,OEHShortcut("CTRL+Down")      ,"...nav");
  SetGUIDefReaction("BookmarkRemove"                ,OEHShortcut("CTRL+Up")        ,"...nav");
  SetGUIDefReaction("BookmarkNext"                  ,OEHShortcut("CTRL+Right")     ,"...nav");
  SetGUIDefReaction("BookmarkPrevious"              ,OEHShortcut("CTRL+Left")      ,"...nav");

  SetGUIDefReaction("HistoryNext"                   ,OEHShortcut("ALT+Right")      ,"...nav")->SetSeparated(YES);;
  SetGUIDefReaction("HistoryPrevious"               ,OEHShortcut("ALT+Left")       ,"...nav");

  SetGUIDefReaction("CSVExport"                     ,OEHShortcut("CTRL+X")       ,"...more");      

  return(term);
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

logical OListCtl :: SetFilter (char *expression, logical enable_opt )
{

  listCache.SetFilter(expression,enable_opt);
  return(NO);
}

/******************************************************************************/
/**
\brief  SetLineFont - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  font_names - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical OListCtl :: SetLineFont (char *font_names, int column )
{
  int          count = UNDEF;
  logical      term  = NO;
BEGINSEQ
OGUIERR(999)
/* *** not used -> rk 10.10.2005
/*
  if ( !cur_item )                                   OGUIERR(99)
  
  if ( column >= 0 )
    cur_item->fonts.SetAtGrow(column,font_names ? Font(font_names) : NULL );
  else
    if ( count = GetColumns()->GetCount() )
      while ( count-- )
        cur_item->fonts.SetAtGrow(count,font_names ?  Font(font_names) : NULL );
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pDFont - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineFont"

logical OListCtl :: SetLineFont (DFont *pDFont, int column )
{

  return ( cur_item->SetLayout(pDFont,column) );

}

/******************************************************************************/
/**
\brief  SetLinePixmap - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pixmap_names - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLinePixmap"

logical OListCtl :: SetLinePixmap (char *pixmap_names, int column )
{
  DPixmap     *pDPixmap = NULL;
  logical      term     = NO;
//  wofür benutzt ?  
//  pDPixmap = 
  
  term = SetLinePixmap(pDPixmap,column);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pDPixmap - 
\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLinePixmap"

logical OListCtl :: SetLinePixmap (DPixmap *pDPixmap, int column )
{


  return ( cur_item->SetIcon(pDPixmap,NULL,NULL,column) );


}

/******************************************************************************/
/**
\brief  SetSorting - Set default sort oder for the list control

        The  default  sorting  is  set  for  the  first column. If sort_order is
        graeter  zero  an  ascending  sort  sort  order  is set; if sort oder is
        negative an descending sort order is set.
        For sort_order zero no sorting by the model is requested.


\param  sort_order - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSorting"

void OListCtl :: SetSorting (int8 sort_order )
{

  if ( sort_order ) 
    listCache.sort(0,sort_order > 0 ? Qt::AscendingOrder 
                                    : Qt::DescendingOrder); 


}

/******************************************************************************/
/**
\brief  SyncColState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncColState"

logical OListCtl :: SyncColState ( )
{
  logical    term = NO;
  if ( term = OEHControlList::SyncColState() )
    listCache.ResetState();
    
//  return ( listCache.SyncColState() );
  return(term);
}

/******************************************************************************/
/**
\brief  SyncInstState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncInstState"

logical OListCtl :: SyncInstState ( )
{

  return(listCache.SyncInstState());

}

/******************************************************************************/
/**
\brief  UnsyncState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnsyncState"

void OListCtl :: UnsyncState ( )
{

  listCache.ResetState();

}

/******************************************************************************/
/**
\brief  UpdateColumnProperties - 



\return hsize - 

\param  pOListLayout - 
\param  col - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateColumnProperties"

int OListCtl :: UpdateColumnProperties (OListLayout *pOListLayout, int col )
{
  QHeaderView    *header       = Header();
  int             section_size = AUTO;
  int             hsize        = AUTO;
  header = Header();
  
  if ( !IsTransposed() )
  {
    if ( !(section_size = pOListLayout->get_width()) )
      section_size = 100;
    hsize = pOListLayout->get_header_height();
  }
  else
  {
    if ( !(section_size = pOListLayout->get_height()) )
      section_size = 22;
    hsize = pOListLayout->get_header_width();
  }

  if ( section_size == AUTO )
    header->setResizeMode(col,QHeaderView::Stretch);
  else
    header->resizeSection(col,section_size);

  return(hsize);
}

/******************************************************************************/
/**
\brief  UpdateLayout - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

void OListCtl :: UpdateLayout ( )
{

BEGINSEQ
  if ( !GetLayout() )                                OGUIERR(99)

  UpdateLayout(olayout);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  list_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

void OListCtl :: UpdateLayout (OListLayout *list_layout )
{
  OHeaderView   *header    = NULL;
  OListLayout   *column    = NULL;
  int32          col       = 0;
  int            hsize     = AUTO;
  int            hsize_max = AUTO;

BEGINSEQ
  if ( !(header = Header()) )                        LEAVESEQ
  header->setModel(&listCache);

  while ( column = list_layout->Column(col) )
    if ( (hsize = UpdateColumnProperties(column,col++)) > hsize_max )
      hsize_max = hsize;

  header->SetSize(hsize_max);
ENDSEQ

}

/******************************************************************************/
/**
\brief  UpdateTreeLayout - 



\return term - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTreeLayout"

logical OListCtl :: UpdateTreeLayout (int32 region_id )
{
  OTreeLayout            *region = GetLayout()->FindRegion(region_id);
  logical                 term = NO;
BEGINSEQ
  if ( !region )                                     ERROR

  UpdateLayout(region);
  
  listCache.UpdateTreeLayout(region);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ValueUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueUpdated"

void OListCtl :: ValueUpdated ( )
{
  BEGIN_ONCE(ignore)
  ItemData                *pItemData = NULL;
  int                      col = 0;
  int32                    id;
BEGINSEQ
OGUIERR(999)
/* *** keine listen        
  if ( (id = ods()->Item()->GetLastObjID()) > 0 ) 
    if ( pItemData = GetItemByID(id) )
      if ( pItemData->Region() )
        pItemData->Region()->SetItemData(pItemData,NULL,col);
*/


RECOVER

ENDSEQ
  END_ONCE
}

/******************************************************************************/
/**
\brief  doCurrentChanged - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doCurrentChanged"

logical OListCtl :: doCurrentChanged (ItemData *pItemData )
{
//  PropertyHandle  *ph = GetPropertyHandle();
  logical          started = NO;
  logical          term = NO;

  cur_item = pItemData;
    
// dann wird nicht immer alles gefüllt!!
//  started = pItemData->Handle()->StartRTA() ? YES : NO;
  if ( !pItemData || pItemData->get_lastIndex() < 0 ) 
  {
    lastIndex = AUTO;
    ods()->ColScroll(-1);
  }
  else
  { 
    lastIndex = pItemData->get_lastIndex();   // fragwuerdig fuer sub-regions
    pItemData->HierSync(NO);
    
    GenerateEvent(GEV_Selected);
  }
  
  SetLastKey(GetSelectedODS());
//  pItemData->Handle()->StopRTA(started);
  stsrmod();
  return term;
}

/******************************************************************************/
/**
\brief  i01 - 



\param  qt_current - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doCurrentChanged"

logical OListCtl :: doCurrentChanged (const QModelIndex &qt_current )
{
//  BEGIN_ONCE(ignore)
  ItemData           *new_cur_item = NULL;
  QAbstractItemView  *item_view    = ItemViewQ();

BEGINSEQ
  if ( stscusr1() )                                 LEAVESEQ
  stssusr1();

  QPersistentModelIndex mi_current_persistent = qt_current;

  if ( qt_current.isValid() )
    new_cur_item = ((CellData *)qt_current.internalPointer())->Item();
  
//  if ( cur_item == new_cur_item )                    LEAVESEQ
  cur_item = new_cur_item;
  //possibly changes the contents of qt_current
  doCurrentChanged(cur_item);
  
  item_view->scrollTo(mi_current_persistent,QAbstractItemView::EnsureVisible); // PositionAtTop
ENDSEQ
  stsrusr1();
//  END_ONCE
  return(NO);
}

/******************************************************************************/
/**
\brief  getEnabled - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OListCtl :: getEnabled ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  selectionRestore - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "selectionRestore"

logical OListCtl :: selectionRestore ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  selectionStore - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "selectionStore"

logical OListCtl :: selectionStore ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  updateListData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateListData"

void OListCtl :: updateListData ( )
{

  if ( !InDesignMode() )
  {
    SetBusy(YES);
    selectionStore();
  
    listCache.UpdateData();
 
    selectionRestore();
    updateSelection();
    SetBusy(NO);
  }

}

/******************************************************************************/
/**
\brief  updateSelection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateSelection"

void OListCtl :: updateSelection ( )
{
  QAbstractItemView  *item_view  = ItemViewQ();
  ItemData           *item_data  = NULL;
  int                 item_count = 0;
  logical             started    = NO;
  logical             hier_sync  = YES;
BEGINSEQ
//  started = BeginOnce();
//  if ( item_view )
//    item_view->clearSelection(); 
//  EndOnce(started);
  
  cur_item = NULL;
  
  if ( !lastODS )
    lastODS = GetSelectedODS();   // wegen cur_item = NULL immer top-region-ODS
  
  if ( lastInstID > 0 )
    item_data = listCache.ItemByLOID((ItemData *)NULL,lastInstID,NO);  // war bis 11.5.06 YES, aber das macht probleme für Instance-Regions (is_collection = NO)
    
  if ( !item_data && !lastKey.empty() && lastODS && lastODS->DefinesCollection() )
    if ( lastODS->ColFind(lastKey.data(),YES) )
    {
      item_data = listCache.ItemByKey(NULL,(char *)lastKey.data(),NO); // war bis 11.5.06 YES, aber das macht probleme für Instance-Regions (is_collection = NO)
      if ( ! item_data )                             ERROR
      hier_sync = NO;  
    }
      
  if ( !item_data )
  { 
    item_count = listCache.ItemCount();   
    if ( lastIndex >= item_count )
      lastIndex = item_count-1;
    if ( lastIndex < 0 )
      lastIndex = 0;
    item_data = listCache.ItemByDBIndex((ODSRegion *)lastODS,lastIndex);
  }
  
  if ( item_data )
  {
    SetCurrentItem(item_data);            // 7.5.2006, sonst wird für DA_FindEntry selektierter Item nicht sichtbar
    if ( hier_sync )
    {  
      bool bBlock = item_view ? item_view->signalsBlocked() : false;
       BlockSignals(YES);
      item_data->HierSync(YES);
      BlockSignals(bBlock);
    }
  }
 
  if ( item_view )
  {
    if ( item_data )
      item_view->setCurrentIndex(item_data->GetModelIndex());
    else
      item_view->clearSelection(); 
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OListCtl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OListCtl"

     OListCtl :: ~OListCtl ( )
{



}


