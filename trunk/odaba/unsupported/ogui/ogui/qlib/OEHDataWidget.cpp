/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHDataWidget

\brief    Event handling data widget
          Event  handling data widgets  are data widgets,  which will handle all
          events  from the  current widget  and widgets, which are sub-ordinated
          and  not marked as event handling data widgets. This is mainly used to
          pass  events  created  in  context  menus or associated buttons to the
          owning  data  widget.  The  owning  data widget can be the control, an
          upper control in the hierarchy or an OD-Control. 
          Events  are collected in subordinated controls  and passed to the next
          higher  level. Depending on the interface (O or OD) the object causing
          the event is passed as an O or OD-object. 
          Eventhandling  is  enabled  by  default  for  all controls (O and OD),
          which do have a parent. This is usually the case for all O-Controls.
          OEHDataWidget is using the following status indicator (sts):
          stsdel:   widget is closing, eventhandling is deactivated
          stsini:    eventhandling is activated, slots ate connected to signals
          stsfil:     widget is filled (after ods has been activated)
          stsmod: data is modified
          stslck:    zeitweise keine Verarbeitung von spontanen GUI-Events (z.B.
          SetFocus)

\date     $Date: 2006/08/29 20:17:15,21 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHDataWidget"

#include  <pogui7.h>
#include  <cactp.h>
#include  <cqt.h>
class     CellData;
class     ItemData;
#include  <sDAction.hpp>
#include  <sDFont.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sFAssociate.hpp>
#include  <sFFileDialog.hpp>
#include  <sFInsert.hpp>
#include  <sOApplicationO.hpp>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODataWidget.hpp>
#include  <sODockWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOEHEvent.hpp>
#include  <sOFont.hpp>
#include  <sOObject.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOStringList.hpp>
#include  <sOTreeLayout.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbsts.hpp>
#include  <scfte.hpp>
#include  <iigui.h>
#include  <sOEHDataWidget.hpp>


/******************************************************************************/
/**
\brief  Activate - Activate data for event handling data widget

        The  data source definition set in the  layout is activated into the ODS
        owned by the data widget. The ODS is set activ.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OEHDataWidget :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
BEGINSEQ
  if ( ODataWidget::Activate() )                     ERROR
    
  if ( !ini )
  { 
    oeh_widget = this;
    if ( event_handling && !event_filter )
      event_filter = new OEHDataWidgetEventFilter(this);
    OObject::RegisterODW(this);
  }
    
  stssini();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddFont - 



\return pOFont - 

\param  pDFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddFont"

OFont *OEHDataWidget :: AddFont (DFont *pDFont )
{
  OFont       *font;
BEGINSEQ
  if ( !pDFont )                                     ERROR
  fonts.AddTail(font = new OFont(*pDFont));
RECOVER
  font = NULL;
ENDSEQ
  return(font);
}

/******************************************************************************/
/**
\brief  AssociateData - 



\return term - 

\param  source_ph - 
\param  control_name - 
\param  title - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AssociateData"

logical OEHDataWidget :: AssociateData (PropertyHandle *source_ph, char *control_name, char *title )
{
  logical                 term = NO;
BEGINSEQ
  FAssociate     fa(this,this,(ODS *)NULL);

//  SetPath(NULL,NULL,YES,NULL,PT_none);
//  fa.ods()->SetParentODS(List());
  fa.Initialize(source_ph,control_name,title);
  fa.ods()->SetParentODS(ods());
  if ( fa.exec() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void OEHDataWidget :: BlockSignals (logical block_opt )
{

BEGINSEQ
  if ( WidgetQ()->signalsBlocked() == (bool)block_opt )
                                                     LEAVESEQ
  WidgetQ()->blockSignals(block_opt);
  
  if ( odw_ods )
    odw_ods->BlockSignals(block_opt);
ENDSEQ

}

/******************************************************************************/
/**
\brief  CheckKey - 



\return term - 

\param  prophdl_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckKey"

logical OEHDataWidget :: CheckKey (PropertyHandle **prophdl_ptr )
{
  PropertyHandle         *prophdl = *prophdl_ptr;
  char                   *str_key = NULL;
  smcb                   *smcbptr = NULL;
  logical                 empty   = NO;
  logical                 term    = NO;
BEGINSEQ
  if ( smcbptr = prophdl->GetSortKeySMCB()  ) 
  {
    if ( !smcbptr->smcbsts.stscold() )  // not __AUTOIDENT
      empty = smcbptr->IsEmpty(prophdl->ExtractSortKey(Key(),new_instance.GetInstance()));
  }
  else if ( smcbptr = prophdl->GetKeySMCB()  ) 
  {
    if ( !smcbptr->smcbsts.stscold() )  // not __AUTOIDENT
      empty = smcbptr->IsEmpty(prophdl->ExtractKey(Key(),new_instance.GetInstance()));
  }

  if ( empty )
  {
    FInsert      fi(this,this,NULL);
    QByteArray   qba;
      
    fi.SetPath(NULL,NULL,YES,NULL,PT_none);
    fi.ods()->SetParentODS(List());
    fi.Activate();
    if ( !fi.exec() )                                ERROR
    if ( !(str_key = QS2SZ_P(fi.ResultString(),qba)) )
                                                     ERROR
    if ( prophdl = fi.ResultPH() )
      *prophdl_ptr = prophdl;
    ProvideNewInstance(*prophdl_ptr,str_key);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ContextMenuEvent - 



\return term - 

\param  watched - 
\param  x - 
\param  y - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ContextMenuEvent"

logical OEHDataWidget :: ContextMenuEvent (QObject *watched, int x, int y )
{
  logical          term    = NO;
BEGINSEQ
  GenerateEvent(GEV_ContextMenu);
  if ( ProvideContextMenu(watched) )                 ERROR

  context_menu->exec(QCursor::pos());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Add - 



\return term - 

\param  fAppend - 
\param  str_key - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Add"

logical OEHDataWidget :: DA_Add (logical fAppend, char *str_key )
{
  PropertyHandle  *coll_ph = GetSelectedPropertyHandle();
  QByteArray       qba;
  logical          started = NO;
  logical          term    = NO;
BEGINSEQ
  if ( !coll_ph )                                    LEAVESEQ
  if ( !coll_ph->IsCollectionUpdate() )              ERROR
                
  if ( !str_key && HasEdit() )
    str_key = QS2SZ_P(Value()->Value(),qba);
    
  ProvideNewInstance(coll_ph,str_key);
  if ( !new_instance.Exist() )                       OGUISDBCSERR(12)
  
  if ( GenerateEvent(DEV_Initialize) == YES )        ERROR
  if ( CheckKey(&coll_ph) )                          ERROR
  GenerateEvent(DEV_Initialized);
    
  if ( GenerateEvent(DEV_Insert) == YES )            ERROR
  
  started = coll_ph->StartRTA() ? YES : NO;
  coll_ph->Add(new_instance.Get(),fAppend ? LAST_INSTANCE : coll_ph->GetCurrentIndex());
  if ( !SDBERROR )
    CacheEvent(DEV_Inserted);
  coll_ph->StopRTA(started);
  FlushEventCache();
  coll_ph->Save();
RECOVER
  term = YES;
ENDSEQ
  new_instance.Close();
  return(term);
}

/******************************************************************************/
/**
\brief  DA_AppendEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_AppendEntry"

logical OEHDataWidget :: DA_AppendEntry ( )
{

  return(DA_Add(YES,NULL));

}

/******************************************************************************/
/**
\brief  DA_Associate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Associate"

logical OEHDataWidget :: DA_Associate ( )
{
  logical                 term = NO;
  return(AssociateData(NULL,NULL,"Associate Instance(s)"));

  return(term);
}

/******************************************************************************/
/**
\brief  DA_BrowseDirectories - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BrowseDirectories"

logical OEHDataWidget :: DA_BrowseDirectories ( )
{
  logical                 term = NO;
  QString                 qsfn;
BEGINSEQ
  FFileDialog f(this,this,ods(),ods()->ValueGetString(),"");

  if ( f.OpenDirectory() )                                   ERROR
  qsfn = f.GetFilename(YES);

  ods()->ValueSet(qsfn);
  DA_Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_BrowseFiles - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BrowseFiles"

logical OEHDataWidget :: DA_BrowseFiles ( )
{
  logical                 term = NO;
  QString                 qsfn;
BEGINSEQ
  FFileDialog f(this,this,ods(),"","");

  if ( f.Open() )                                   ERROR
  qsfn = f.GetFilename(YES);

  ods()->ValueSet(qsfn);
  DA_Save();
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_BrowseWriteFiles - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_BrowseWriteFiles"

logical OEHDataWidget :: DA_BrowseWriteFiles ( )
{
  logical                 term = NO;
BEGINSEQ
  FFileDialog f(this,this,ods(),"","");
  if ( f.Save() )                                   ERROR
  SetText(QS2SZ(f.GetFilename(YES)));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Cancel - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Cancel"

logical OEHDataWidget :: DA_Cancel ( )
{
  PropertyHandle         *coll_ph;
  logical                 term = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( coll_ph->Reset() )                            ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_CancelClose - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_CancelClose"

logical OEHDataWidget :: DA_CancelClose ( )
{
  logical                 term = NO;
  term = DA_Cancel();

  return(term);
}

/******************************************************************************/
/**
\brief  DA_Copy - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Copy"

logical OEHDataWidget :: DA_Copy ( )
{
  logical                 term = NO;
BEGINSEQ
  /* multilineedit::copy */
  OGUIERR(98);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_CopyEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_CopyEntry"

logical OEHDataWidget :: DA_CopyEntry ( )
{
  PropertyHandle  *coll_ph  = GetPropertyHandle();
  char             key[512];
  char             skey[513];
  logical          sort_key = YES;
  char            *newkey   = NULL;
  logical          term     = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( !coll_ph->IsCollectionUpdate() )              ERROR
  
// *fixme* soll auch fuer unsortierte owning-mengen laufen  
  
  if ( !coll_ph->IsPositioned() )
    coll_ph->Get(Key(GetKey()));
  if ( !coll_ph->IsPositioned() )                    ERROR
  
  if ( !coll_ph->ExtractSortKey(key) )
    if ( !coll_ph->ExtractKey(key) )                 ERROR
  
  coll_ph->KeyToString(skey,key);
  
  if ( !(newkey = GetString("Copy Instance","Enter new key value",skey,this)) )
                                                     ERROR
  newkey = coll_ph->StringToKey(newkey);
/*
  if ( coll_ph->ExtractSortKey(newkey) || coll_ph->ExtractKey(newkey) )
    if( QMessageBox::question(
        NULL,
        "Copy Entry",
        "The provided Key already exists. Overwriting can cause trouble.\n"
        "Are you sure?",
        "&Yes", "&No",
        QString(), 0, 1)
      )                                               ERROR
*/
  coll_ph->Duplicate(Key(newkey),REPL_local);        OGUISDBCERR
                   // nd 3.8.04  REPL_all fuehrt zu leeren von shared basisinstanzen

  coll_ph->Reset();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Cut - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Cut"

logical OEHDataWidget :: DA_Cut ( )
{
  logical                 term = NO;
BEGINSEQ
  /* multilineedit::cut */
  OGUIERR(98);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_DeleteEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_DeleteEntry"

logical OEHDataWidget :: DA_DeleteEntry ( )
{
  PropertyHandle  *coll_ph = NULL;
  logical          started = NO;
  logical          term    = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( !coll_ph->IsCollectionUpdate() )              ERROR
  
  if ( GenerateEvent(DEV_Delete) == YES )            ERROR

  if ( GetApplication()->CheckQueryOption("QL_Delete") )
    if ( GetDecision("Löschen Eintrag","Wollen Sie den ausgewählten Eintrag wirklich entfernen?",
                     QMessageBox::Yes,QMessageBox::No,UNDEF) == QMessageBox::No )
                                                     ERROR
  started = coll_ph->StartRTA() ? YES : NO;
  coll_ph->Delete();
  if ( !SDBERROR )
    CacheEvent(DEV_Deleted);
  coll_ph->StopRTA(started);
  FlushEventCache();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_DeleteSet - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_DeleteSet"

logical OEHDataWidget :: DA_DeleteSet ( )
{
  PropertyHandle  *coll_ph;
  logical          term      = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( !coll_ph->IsCollectionUpdate() )              ERROR

// *fixme* event(s) sind nicht geeignet fuer ganze Menge  
  if ( GenerateEvent(DEV_Delete) == YES )            ERROR


  coll_ph->DeleteSet();                              OGUISDBCERR
  GenerateEvent(DEV_Deleted);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_EditEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_EditEntry"

logical OEHDataWidget :: DA_EditEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  // die idee ist, hier ein dynamisches-Window zum Anzeigen aller 
  // Felder aufzubauen
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
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

logical OEHDataWidget :: DA_FindEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
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

logical OEHDataWidget :: DA_FindEntry (char *skey, logical cur_opt )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_ImportFile - Import Data from external file into data source

        Diese   Standardimplementierung   importiert   den   Inhalte   eines  
        auszuwählenden  Files in den Datenhintergrund (am sinnvollsten ein MEMO)
        des   Controls.   Der   ursprüngliche   Inhalt   wird  dabei vollständig
        überschrieben.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ImportFile"

logical OEHDataWidget :: DA_ImportFile ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_InsertEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_InsertEntry"

logical OEHDataWidget :: DA_InsertEntry ( )
{

  return(DA_Add(NO,NULL));

}

/******************************************************************************/
/**
\brief  DA_Move - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Move"

logical OEHDataWidget :: DA_Move ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_MoveDown - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_MoveDown"

logical OEHDataWidget :: DA_MoveDown ( )
{
  PropertyHandle  *coll_ph;
  logical          term = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( coll_ph->NoWrite() )                          ERROR

  coll_ph->MoveDown();                               OGUISDBCERR
  DA_Refresh();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_MoveUp - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_MoveUp"

logical OEHDataWidget :: DA_MoveUp ( )
{
  PropertyHandle  *coll_ph;
  logical          term = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( coll_ph->NoWrite() )                          ERROR

  coll_ph->MoveUp();                                 OGUISDBCERR
  DA_Refresh();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_NewFindEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_NewFindEntry"

logical OEHDataWidget :: DA_NewFindEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Paste - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Paste"

logical OEHDataWidget :: DA_Paste ( )
{
  logical                 term = NO;
BEGINSEQ
  /* multilineedit::paste */
  OGUIERR(98);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Redo - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Redo"

logical OEHDataWidget :: DA_Redo ( )
{
  logical                 term = NO;
BEGINSEQ
  /* multilineedit::redo */
  OGUIERR(98);
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

logical OEHDataWidget :: DA_Refresh ( )
{

  if ( List() )
  {
    List()->ResetState();
    List()->Signal("OnCollectionChanged");
  }
  
  if ( ods() && ods() != List() )
  {
    ods()->ResetState();
    ods()->ValueInit();
    ods()->Signal("OnCollectionChanged");
    ods()->Signal("OnInstanceSelected");
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  DA_RenameEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_RenameEntry"

logical OEHDataWidget :: DA_RenameEntry ( )
{
  PropertyHandle         *coll_ph;
  char                   *new_name;
  logical                 term = NO;
BEGINSEQ
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( !coll_ph->IsCollectionUpdate() )              ERROR
  
  new_name = GetNewKey(coll_ph,"Rename Instance","Enter new key value");
  if ( !new_name || !*new_name )                     ERROR
    
  new_name = coll_ph->StringToKey(new_name);
  
  if ( coll_ph->GetSortKeyLength() > 0 )
    coll_ph->SetSortKey(new_name);
  else  
    coll_ph->SetKey(new_name);
  coll_ph->Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Reset - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Reset"

logical OEHDataWidget :: DA_Reset ( )
{
  logical                 term = NO;
  ods()->ResetState();
  ods()->ProvideItem();
  return(term);
}

/******************************************************************************/
/**
\brief  DA_ResetCascadingSelection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ResetCascadingSelection"

logical OEHDataWidget :: DA_ResetCascadingSelection ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_ResetSelection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ResetSelection"

logical OEHDataWidget :: DA_ResetSelection ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Save - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Save"

logical OEHDataWidget :: DA_Save ( )
{
  PropertyHandle         *coll_ph = NULL;
  logical                 save    = NO;
  logical                 term    = NO;
BEGINSEQ
  DA_StoreEntry();
  
  if ( !(coll_ph = GetSelectedPropertyHandle() ) )   LEAVESEQ
  if ( coll_ph->NoWrite() )                          LEAVESEQ
    
// wenn ph-function zuverlaessig laeuft, kann die Abfrage zum wegsprung fuehren    
  
  if ( save = coll_ph->IsModified() ) 
    if ( GenerateEvent(DEV_Save) == YES )            ERROR
  
  coll_ph->Save();                                   OGUISDBCERR
  
  if ( save )
    GenerateEvent(DEV_Saved);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_SaveClose - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SaveClose"

logical OEHDataWidget :: DA_SaveClose ( )
{
  logical                 term = NO;
  
  term = DA_Save();
  return(term);
}

/******************************************************************************/
/**
\brief  DA_SelectEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SelectEntry"

logical OEHDataWidget :: DA_SelectEntry ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  DA_SetCascadingSelection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetCascadingSelection"

logical OEHDataWidget :: DA_SetCascadingSelection ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel0 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel0"

logical OEHDataWidget :: DA_SetDisplayLevel0 ( )
{

  return(SetDisplayLevel((int16)0));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel1 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel1"

logical OEHDataWidget :: DA_SetDisplayLevel1 ( )
{

  return(SetDisplayLevel(1));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel2 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel2"

logical OEHDataWidget :: DA_SetDisplayLevel2 ( )
{

  return(SetDisplayLevel(2));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel3 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel3"

logical OEHDataWidget :: DA_SetDisplayLevel3 ( )
{

  return(SetDisplayLevel(3));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel4 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel4"

logical OEHDataWidget :: DA_SetDisplayLevel4 ( )
{

  return(SetDisplayLevel(4));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel5 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel5"

logical OEHDataWidget :: DA_SetDisplayLevel5 ( )
{

  return(SetDisplayLevel(5));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel6 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel6"

logical OEHDataWidget :: DA_SetDisplayLevel6 ( )
{

  return(SetDisplayLevel(6));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel7 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel7"

logical OEHDataWidget :: DA_SetDisplayLevel7 ( )
{

  return(SetDisplayLevel(7));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel8 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel8"

logical OEHDataWidget :: DA_SetDisplayLevel8 ( )
{

  return(SetDisplayLevel(8));

}

/******************************************************************************/
/**
\brief  DA_SetDisplayLevel9 - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetDisplayLevel9"

logical OEHDataWidget :: DA_SetDisplayLevel9 ( )
{

  return(SetDisplayLevel(9));

}

/******************************************************************************/
/**
\brief  DA_SetSelection - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_SetSelection"

logical OEHDataWidget :: DA_SetSelection ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_StoreEntry - Store data from control into data source

        Im  Allg. wird  für die  Aktion DA_StoreEntry der aktuelle Controlinhalt
        in  das  interne  value  property  übertragen. Anschließend wird für das
        Control  ein  GUI  event  DEV_Store  erzeugt,  in  dessen  Reaktion  das
        Übertragen  der  Daten  in  den Datenhintergrund verhindert werden kann.
        Nach  dem  Übertragen  wird  für  das  Control  ein GUI event DEV_Stored
        erzeugt. 
        Beachte: Listen-Controls verarbeiten die Aktion DA_StoreEntry anders.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_StoreEntry"

logical OEHDataWidget :: DA_StoreEntry ( )
{
  ODSItem          *vi   = ValueItem();
  logical           term = NO;
BEGINSEQ
  if ( !vi || !vi->ValueIsUpdated() )                 LEAVESEQ
  
  if ( GenerateEvent(DEV_Store) == YES )              ERROR
  if ( vi->ValueStore() ) 
    GenerateEvent(DEV_Stored);



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_Undo - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Undo"

logical OEHDataWidget :: DA_Undo ( )
{
  logical                 term = NO;
BEGINSEQ
  /* multilineedit::undo */
  OGUIERR(98);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_UpdateEntries - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_UpdateEntries"

logical OEHDataWidget :: DA_UpdateEntries ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_ValidateData - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ValidateData"

logical OEHDataWidget :: DA_ValidateData ( )
{
  logical                 term = NO;
BEGINSEQ
  OGUIERR(98)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_ZoomIn - The Control is zoomed in

        Die  Standardimplementierung der  Aktion verkleinert  ein Multiline Edit
        Control auf seine Originalgröße.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ZoomIn"

logical OEHDataWidget :: DA_ZoomIn ( )
{

// only implemented for MultiLineEdit  
  
  return(NO);

}

/******************************************************************************/
/**
\brief  DA_ZoomOut - Tthe Control is zoomed out

        Die  Standardimplementierung  der  Aktion  vergrößert ein Multiline Edit
        Control auf die Größe seines parents.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ZoomOut"

logical OEHDataWidget :: DA_ZoomOut ( )
{

// only implemented for MultiLineEdit  
  
  return(NO);

}

/******************************************************************************/
/**
\brief  DataWidgetOEH - 



\return pOEHDataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataWidgetOEH"

OEHDataWidget *OEHDataWidget :: DataWidgetOEH ( )
{

  return(this);

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

logical OEHDataWidget :: Deactivate (logical data_only )
{
  logical                 term = NO;
  if ( base_ods )
    base_ods->SetActive(NO);
  
  if ( ods() )
    ods()->SetActive(NO);
    
  if ( !data_only )
  {
    delete event_filter;
    event_filter = NULL;
  
    if ( event_handler )
      event_handler->Close();
      
    stsrini();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return executed - Action executed

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 OEHDataWidget :: ExecuteAction (char *act_names )
{
  char      actname[ID_SIZE];
  cfte     *cfteptr;
  int8      executed = AUTO;  // action not found
BEGINSEQ
/*    
    "NextEntry       ", // 17
    "PreviousEntry   ", // 18
    "SaveEntry       ", // 19
    "ValidateControl ", // 20
    "HelpControl     ", // 21
*/    
  static cfte acttbl[] = { 
         
         cfte("InsertEntry",      ALINK(this,OEHDataWidget,DA_InsertEntry)),
         cfte("AppendEntry",      ALINK(this,OEHDataWidget,DA_AppendEntry)),
         cfte("MoveUp",           ALINK(this,OEHDataWidget,DA_MoveUp)),
         cfte("MoveDown",         ALINK(this,OEHDataWidget,DA_MoveDown)),
         cfte("DeleteEntry",      ALINK(this,OEHDataWidget,DA_DeleteEntry)),
         cfte("RemoveEntry",      ALINK(this,OEHDataWidget,DA_DeleteEntry)),
         cfte("DeleteSet",        ALINK(this,OEHDataWidget,DA_DeleteSet)),
         cfte("CopyEntry",        ALINK(this,OEHDataWidget,DA_CopyEntry)),
         cfte("Associate",        ALINK(this,OEHDataWidget,DA_Associate)),
         cfte("NewFindEntry",     ALINK(this,OEHDataWidget,DA_NewFindEntry)),
         cfte("FindEntry",        ALINK(this,OEHDataWidget,DA_FindEntry)),
         cfte("RenameEntry",      ALINK(this,OEHDataWidget,DA_RenameEntry)),
         cfte("EditEntry",        ALINK(this,OEHDataWidget,DA_EditEntry)),
         cfte("StoreEntry",       ALINK(this,OEHDataWidget,DA_StoreEntry)),
         cfte("UpdateEntries",    ALINK(this,OEHDataWidget,DA_UpdateEntries)),
         cfte("ValidateData",     ALINK(this,OEHDataWidget,DA_ValidateData)),
         cfte("ZoomOut",          ALINK(this,OEHDataWidget,DA_ZoomOut)),
         cfte("ZoomIn",           ALINK(this,OEHDataWidget,DA_ZoomIn)),
         cfte("Refresh",          ALINK(this,OEHDataWidget,DA_Refresh)),
         cfte("Reset",            ALINK(this,OEHDataWidget,DA_Reset)),
                           
         cfte("ImportFile",       ALINK(this,OEHDataWidget,DA_ImportFile)),
         cfte("BrowseWriteFiles", ALINK(this,OEHDataWidget,DA_BrowseWriteFiles)),
         cfte("BrowseFiles",      ALINK(this,OEHDataWidget,DA_BrowseFiles)),
         cfte("BrowseDirectories",ALINK(this,OEHDataWidget,DA_BrowseDirectories)),
                           
         cfte("SetSelection",           ALINK(this,OEHDataWidget,DA_SetSelection)),
         cfte("ResetSelection",         ALINK(this,OEHDataWidget,DA_ResetSelection)),
         cfte("SetCascadingSelection",  ALINK(this,OEHDataWidget,DA_SetCascadingSelection)),
         cfte("ResetCascadingSelection",ALINK(this,OEHDataWidget,DA_ResetCascadingSelection)),

         cfte("SetDisplayLevel1", ALINK(this,OEHDataWidget,DA_SetDisplayLevel1)),
         cfte("SetDisplayLevel2", ALINK(this,OEHDataWidget,DA_SetDisplayLevel2)),
         cfte("SetDisplayLevel3", ALINK(this,OEHDataWidget,DA_SetDisplayLevel3)),
         cfte("SetDisplayLevel4", ALINK(this,OEHDataWidget,DA_SetDisplayLevel4)),
         cfte("SetDisplayLevel5", ALINK(this,OEHDataWidget,DA_SetDisplayLevel5)),
         cfte("SetDisplayLevel6", ALINK(this,OEHDataWidget,DA_SetDisplayLevel6)),
         cfte("SetDisplayLevel7", ALINK(this,OEHDataWidget,DA_SetDisplayLevel7)),
         cfte("SetDisplayLevel8", ALINK(this,OEHDataWidget,DA_SetDisplayLevel8)),
         cfte("SetDisplayLevel9", ALINK(this,OEHDataWidget,DA_SetDisplayLevel9)),
         cfte("SetDisplayLevel0", ALINK(this,OEHDataWidget,DA_SetDisplayLevel0)),

         cfte("SaveClose",        ALINK(this,OEHDataWidget,DA_SaveClose)),
         cfte("CancelClose",      ALINK(this,OEHDataWidget,DA_CancelClose)),
         cfte("Save",             ALINK(this,OEHDataWidget,DA_Save)),
         cfte("Cancel",           ALINK(this,OEHDataWidget,DA_Cancel)),

         /* multilineedit */
         cfte("Cut",              ALINK(this,OEHDataWidget,DA_Cut)),
         cfte("Copy",             ALINK(this,OEHDataWidget,DA_Copy)),
         cfte("Paste",            ALINK(this,OEHDataWidget,DA_Paste)),
         cfte("Undo",             ALINK(this,OEHDataWidget,DA_Undo)),
         cfte("Redo",             ALINK(this,OEHDataWidget,DA_Redo)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,act_names,ID_SIZE))) )
  {
    if ( cfteptr->ActionCall(this) )
      ; // *fixme* nachrichtenausgabe   OGUIDISPLAY_ERROR
      
    executed = YES;
  }
RECOVER

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  FocusInEvent - 



\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusInEvent"

int8 OEHDataWidget :: FocusInEvent ( )
{
  ODataWidget     *odw = GetApplication()->GetLastFocusWidget();

  if ( odw )
  {
    odw->FocusDeactivate();
    GetApplication()->SetLastFocusWidget(NULL);
  }

  FocusSet();
  return ( FocusActivate() );

}

/******************************************************************************/
/**
\brief  FocusOutEvent - The O-Control lost the focus



\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusOutEvent"

int8 OEHDataWidget :: FocusOutEvent ( )
{
  int8                executed = NO;
BEGINSEQ
  GetApplication()->SetLastFocusWidget(this);
  FocusReset();
    
  if ( DA_StoreEntry() )                            ERROR
 


RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  Font - Bereitstellen eines definierten Fonts

        Ist  ein  Name  angegeben,  wird  der  Font in der Liste der definierten
        fonts  gesucht.  Andernfalls  liefert  die Funktion den Standardfont für
        das data widget.

\return pOFont - 

\param  font_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Font"

OFont *OEHDataWidget :: Font (char *font_names )
{
  char       name[ID_SIZE];
  OFont     *pOFont = NULL;
BEGINSEQ
  OGUIERR(999)
/*
  if ( !font_names )
    pOFont = ODataWidget::Font();
  else
  {
    gvtxstb(name,font_names,sizeof(name));
    fonts.GoTop();
    while ( pOFont = fonts.GetNext() )
      if ( !memcmp(pOFont->get_name(),name,sizeof(name)) )
                                                     LEAVESEQ
  }
*/
RECOVER

ENDSEQ
  return(pOFont);
}

/******************************************************************************/
/**
\brief  GetBasePropertyHandle - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBasePropertyHandle"

PropertyHandle *OEHDataWidget :: GetBasePropertyHandle ( )
{
  PropertyHandle     *ph = NULL;
  PropertyHandle     *cph = NULL;
  char               *key;
BEGINSEQ
  cph = GetCurrentPropertyHandle();
  
  if ( base_ods && cph == ods()->Handle() )
  {
    if ( !base_ods->Item() )
      base_ods->SetActive(YES);
    ph = base_ods->Handle();
  }

  if ( !ph )
  {
    if ( !cph )                                      ERROR
    ph = cph->GetBaseProperty();
  }

  if ( cph && (key = cph->GetSortKey()) )
    ph->SetOrder(key);
RECOVER
  ph = NULL;
ENDSEQ
  return(ph);
}

/******************************************************************************/
/**
\brief  GetInitPropertyHandle - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitPropertyHandle"

PropertyHandle *OEHDataWidget :: GetInitPropertyHandle ( )
{

  return( this ? &new_instance : NULL );

}

/******************************************************************************/
/**
\brief  GetNewInstanceHandle - 



\return prop_handle - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewInstanceHandle"

PropertyHandle *OEHDataWidget :: GetNewInstanceHandle ( )
{

  return ( new_instance.IsValid() ? &new_instance : NULL );

}

/******************************************************************************/
/**
\brief  GetNewKey - 



\return string - Character string

\param  ph - 
\param  text1 - 
\param  text2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewKey"

char *OEHDataWidget :: GetNewKey (PropertyHandle *ph, char *text1, char *text2 )
{
  char                    key[512];
  char                    skey[513];
  char                   *new_name;
  logical                 sort_key = YES;
BEGINSEQ
  skey[0] = 0;
  
  if ( !ph->IsPositioned() )
    ph->Get(Key(GetKey()));
  if ( !ph->IsPositioned() )                    ERROR
  
  if ( !ph->ExtractSortKey(key) )
  { 
    sort_key = NO;
    if ( !ph->ExtractKey(key) )                 ERROR
  }
  ph->KeyToString(skey,key);
  
  if ( !(new_name = GetString(text1,text2,skey,this)) )
                                                     LEAVESEQ

RECOVER
  new_name = skey;
ENDSEQ
  return(new_name);
}

/******************************************************************************/
/**
\brief  HideEvent - 



\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HideEvent"

int8 OEHDataWidget :: HideEvent ( )
{


  return( GenerateEvent(GEV_Hide) );
  


}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OEHDataWidget :: Initialize ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( parent_odw )
    enableEventHandling(NO); 
    
//  if ( !(olayout = new OTreeLayout()) )              OGUIERR(95)
// nd: das kann problematisch werden, da zu zeitig darauf zugegriffen wird
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  KeyEvent - Key event occured

        Key  events are calling associated actions. When the action is executed,
        the  key event is considered as  handled. This is independent wether the
        action  was executed successfully or not.  When no action was found, the
        key event is passed to the next higher context.

\return term - 

\param  keycode - 
\param  keystate - 
\param  keyreleased - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyEvent"

logical OEHDataWidget :: KeyEvent (int keycode, int keystate, logical keyreleased )
{
  OEHEvent                evt(OEHKeyEvent(keycode,keystate));
  logical                 term = NO;
BEGINSEQ
  if ( keyreleased )
  {  
    if ( oeh()->ExecuteReaction(&evt,this) != AUTO ) LEAVESEQ
  }
  else
  {  
    if ( oeh()->FindReaction(&evt,this) )            LEAVESEQ
  }
    
    
  if ( !event_handler->get_user_hdl() )              ERROR
  DKey dkey(keycode,keystate,keyreleased);
  if ( event_handler->get_user_hdl()->ProcessKeyEvent(dkey) == AUTO )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MouseClickEvent - 



\return executed - Action executed

\param  x - 
\param  y - 
\param  click_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseClickEvent"

char OEHDataWidget :: MouseClickEvent (int x, int y, int32 click_count )
{
  char             executed    = AUTO;
  mouse_pos = DPoint(x,y);
  switch ( click_count )
  {
    case  1 : executed = GenerateEvent(GEV_MouseClick);
              break;
    case  2 : executed = GenerateEvent(GEV_MouseDoubleClick);
              break;
  }

  

  return(executed);
}

/******************************************************************************/
/**
\brief  MouseMoveEvent - 



\return executed - Action executed

\param  x - 
\param  y - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MouseMoveEvent"

char OEHDataWidget :: MouseMoveEvent (int x, int y )
{
  char     executed    = AUTO;
  mouse_pos = DPoint(x,y);
  executed = GenerateEvent(GEV_MouseMove);

  return(executed);
}

/******************************************************************************/
/**
\brief  OEHDataWidget - Constructor



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHDataWidget"

     OEHDataWidget :: OEHDataWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : bsts (),
ODataWidget (pODataWidget,oODataWidget,create_ods),
ODragAndDrop (),
  base_ods(NULL),
  fonts(),
  event_filter(NULL),
  new_instance(),
  find_text(),
  mouse_pos()
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
#define    MOD_ID  "OEHDataWidget"

     OEHDataWidget :: OEHDataWidget (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : bsts (),
ODataWidget (pODataWidget,oODataWidget,pODS),
ODragAndDrop (),
  base_ods(NULL),
  fonts(),
  event_filter(NULL),
  new_instance(),
  find_text(),
  mouse_pos()
{

BEGINSEQ
  OGUICERR
  
  if ( !pODS )
    CreateODS();    
    
  Initialize();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ProvideBaseODS - 



\return pODS - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideBaseODS"

ODS *OEHDataWidget :: ProvideBaseODS ( )
{

  if ( !base_ods )
  {
    base_ods = new ODS();
    base_ods->SetPath(NULL,NULL,YES,NULL,PT_BaseCollection);
  }
  base_ods->SetParentODS(ods());
  base_ods->SetActive(YES);

  return(base_ods);
}

/******************************************************************************/
/**
\brief  ProvideNewInstance - 



\return instance - 

\param  prophdl - 
\param  str_key - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideNewInstance"

Instance OEHDataWidget :: ProvideNewInstance (PropertyHandle *prophdl, char *str_key )
{
  Instance           instance;
BEGINSEQ
  new_instance.Open(prophdl->GetCurrentTypeDef(),Instance());
  new_instance.AllocateArea();
  PropertyHandle   cpy(*prophdl);
  if ( !(instance = cpy.GetInitInstance()) )         ERROR
  new_instance.FillData(instance);
  
  SetNewInstKey(prophdl,str_key);
RECOVER

ENDSEQ
 return(new_instance.GetInstance());
}

/******************************************************************************/
/**
\brief  SetBasePath - 



\return term - 

\param  base_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBasePath"

logical OEHDataWidget :: SetBasePath (char *base_path )
{
  ODSPropertyType         prop_type = PT_BaseCollection;
  logical                 term = NO;
  if ( !base_ods )
  {
    base_ods = new ODS();
    base_ods->SetParentODS(ods());
  }
  
  if ( base_path && *base_path )
  {
    prop_type = PT_Property;
    if ( *base_path == '.' )
      base_path++;
    else
      prop_type = PT_Extent;
  }
  
  base_ods->SetPath(base_path,NULL,YES,NULL,prop_type);

  return(term);
}

/******************************************************************************/
/**
\brief  SetDataSource - Set data source

        The  function allows setting the data widget data source. This is either
        an opened database object handle or a data source name.

\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical OEHDataWidget :: SetDataSource (DBObjectHandle &ob_handle )
{
  logical                 term = NO;
  ods()->SetParentDB(ob_handle);

  GenerateEvent(DEV_Activated);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  dictionary - 
\param  db_path - 
\param  accmode - 
\param  net_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical OEHDataWidget :: SetDataSource (DictionaryHandle *dictionary, char *db_path, PIACC accmode, logical net_opt )
{
  logical                 term = NO;
BEGINSEQ
  DatabaseHandle dbh(*dictionary,db_path,accmode,net_opt);
                                                        SDBCERR
  SetDataSource(dbh);

// *fixme* wo bleibt das db-handle ?
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  ds_name - Data source name
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataSource"

logical OEHDataWidget :: SetDataSource (char *ds_name, PIACC accmode )
{
  logical                 term = NO;
  ODABAClient             oclient;
BEGINSEQ
 // wo kommt der client her??

  DBObjectHandle dbo(oclient,ds_name,accmode);        SDBCERR
  SetDataSource(dbo);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultReactions - Set default actions for control

        The  function implements  the default  actions for the control. Usually,
        this  function is overloaded  in the specific  control classes. The base
        calss implements the following default actions:
        F1 - Help

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OEHDataWidget :: SetDefaultReactions ( )
{
  logical                 term = NO;
  SetGUIDefReaction("Exit",             OEHShortcut("CTRL+ALT+F4"));
  SetGUIDefReaction("Help",             OEHShortcut("F1"));
  SetGUIDefReaction("BrowseDirectories",OEHShortcut("CTRL+ALT+D"));
  SetGUIDefReaction("BrowseFiles",      OEHShortcut("CTRL+ALT+F"));
  SetGUIDefReaction("BrowseWriteFiles", OEHShortcut("CTRL+SHIFT+F"));
  
  SetGUIDefReaction("Associate",      OEHShortcut("SHIFT+F1"));
  SetGUIDefReaction("EditEntry",      OEHShortcut("F4")); 
  SetGUIDefReaction("StoreEntry",     OEHShortcut("F2")); 
  SetGUIDefReaction("Save",           OEHShortcut("CTRL+SHIFT+B"));
  SetGUIDefReaction("Refresh",        OEHShortcut("CTRL+R")); 
  if(event_handling > 1){
	  SetGUIDefReaction("DoBeforeOpen",   OEHInternalEvent(GEV_Open));
	  SetGUIDefReaction("DoAfterOpen",    OEHInternalEvent(GEV_Opened));
	  SetGUIDefReaction("DoBeforeClose",  OEHInternalEvent(GEV_Close));
	  SetGUIDefReaction("DoAfterShow",   OEHInternalEvent(GEV_Show));
	  SetGUIDefReaction("DoAfterHide",    OEHInternalEvent(GEV_Hide));
	  SetGUIDefReaction("DoAfterEnter",   OEHInternalEvent(GEV_Enter));
	  SetGUIDefReaction("DoBeforeLeave",  OEHInternalEvent(GEV_Leave));
	  SetGUIDefReaction("DoBeforeSelect", OEHInternalEvent(GEV_Select));
	  SetGUIDefReaction("DoAfterSelect",  OEHInternalEvent(GEV_Selected));
	  SetGUIDefReaction("DoAfterKeyInput",OEHInternalEvent(GEV_KeyInput));
	  SetGUIDefReaction("DoBeforeContextMenu",OEHInternalEvent(GEV_ContextMenu));
	  SetGUIDefReaction("DoBeforeDrag",   OEHInternalEvent(GEV_BeginDrag));
	  SetGUIDefReaction("DoAfterDrag",    OEHInternalEvent(GEV_EndDrag));
	  SetGUIDefReaction("DoBeforeDrop",   OEHInternalEvent(GEV_BeginDrop));
	  SetGUIDefReaction("DoAfterDrop",    OEHInternalEvent(GEV_EndDrop));
	  SetGUIDefReaction("DoAfterUndock",  OEHInternalEvent(GEV_Undock));
	  SetGUIDefReaction("DoAfterDock",    OEHInternalEvent(GEV_Dock));
	  SetGUIDefReaction("DoAfterMouseMove",OEHInternalEvent(GEV_MouseMove));
	  SetGUIDefReaction("DoAfterMouseClick",OEHInternalEvent(GEV_MouseClick));
	  SetGUIDefReaction("DoAfterMouseDoubleClick",OEHInternalEvent(GEV_MouseDoubleClick));
	  
	  SetGUIDefReaction("DoAfterHandleActivated",OEHInternalEvent(DEV_Activated));
	  SetGUIDefReaction("DoAfterHandleOpen",OEHInternalEvent(DEV_Opened));
	  SetGUIDefReaction("DoAfterClearData",OEHInternalEvent(DEV_Clear));
	  SetGUIDefReaction("DoBeforeDeleteData",OEHInternalEvent(DEV_Delete));
	  SetGUIDefReaction("DoAfterDeleteData",OEHInternalEvent(DEV_Deleted));
	  SetGUIDefReaction("DoBeforeInitializeData",OEHInternalEvent(DEV_Initialize));
	  SetGUIDefReaction("DoAfterInitializeData",OEHInternalEvent(DEV_Initialized));
	  SetGUIDefReaction("DoBeforeFillData",OEHInternalEvent(DEV_Fill));
	  SetGUIDefReaction("DoAfterFillData",OEHInternalEvent(DEV_Filled));
	  SetGUIDefReaction("DoBeforeDataSet",OEHInternalEvent(DEV_BeforeDataSet));
	  SetGUIDefReaction("DoAfterDataSet",OEHInternalEvent(DEV_AfterDataSet));
	  SetGUIDefReaction("DoBeforeInsertData",OEHInternalEvent(DEV_Insert));
	  SetGUIDefReaction("DoAfterInsertData",OEHInternalEvent(DEV_Inserted));
	  SetGUIDefReaction("DoBeforeStoreData",OEHInternalEvent(DEV_Store));
	  SetGUIDefReaction("DoAfterStoreData",OEHInternalEvent(DEV_Stored));
	  SetGUIDefReaction("DoBeforeSaveData",OEHInternalEvent(DEV_Save));
	  SetGUIDefReaction("DoAfterSaveData",OEHInternalEvent(DEV_Saved));
	  SetGUIDefReaction("DoValidateData",OEHInternalEvent(DEV_Validate));
	
	  SetGUIDefReaction("DoAfterUpdateCollection",OEHInternalEvent(DBEV_CollectionUpdated));
	//  SetGUIDefReaction("DoAfterChangeSelection",OEHInternalEvent(DBEV_InstanceUnselected));
	//  SetGUIDefReaction("DoAfterChangeSelection",OEHInternalEvent(DBEV_InstanceSelected));
	  SetGUIDefReaction("DoAfterUpdateInstance",OEHInternalEvent(DBEV_InstanceUpdated));
	//  SetGUIDefReaction("DoAfterInsertInstance",OEHInternalEvent(DBEV_InstanceInserted));
	//  SetGUIDefReaction("DoAfterRemoveInstance",OEHInternalEvent(DBEV_DBEV_InstanceRemoved));
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetGUIDefReaction - 



\return action - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  act_namesc - Action name
\param  loid - Identification for an action object
\param  parent_loid_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, char *loid, char *parent_loid_w )
{

  return ( SetAction(act_namesc,loid,parent_loid_w,
                     ABT_never,NULL,YES) );

}

/******************************************************************************/
/**
\brief  i00 - 



\param  act_namesc - Action name
\param  short_cut - 
\param  parent_loid_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, OEHShortcut short_cut, char *parent_loid_w )
{
  DAction           *actdef = NULL;
  OEHAction         *action = NULL;
BEGINSEQ
  if ( actdef = GetApplication()->GetDefaultAction(act_namesc) )
    if ( actdef->IsDisabled() )                     ERROR
    
  if ( action = SetAction(act_namesc,NULL,short_cut,this,YES,parent_loid_w) )
    if ( actdef )
      action->Setup(actdef);
RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  act_namesc - Action name
\param  key_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, OEHKeyEvent key_event )
{

  return ( SetAction(act_namesc,NULL,
                     key_event,this,YES) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  act_namesc - Action name
\param  system_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, OEHInternalEvent system_event )
{

  return ( SetAction(act_namesc,NULL,
                     system_event,this,YES) );

}

/******************************************************************************/
/**
\brief  i03 - 



\param  act_namesc - Action name
\param  mouse_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, OEHMouseEvent mouse_event )
{

  return ( SetAction(act_namesc,NULL,
                     mouse_event,this,YES) );

}

/******************************************************************************/
/**
\brief  i04 - 



\param  act_namesc - Action name
\param  data_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, DB_Event data_event )
{

  return ( SetAction(act_namesc,NULL,
                     data_event,this,YES) );

}

/******************************************************************************/
/**
\brief  i05 - 



\param  act_namesc - Action name
\param  time_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, OEHTimeEvent time_event )
{

  return ( SetAction(act_namesc,NULL,
                     time_event,this,YES) );


}

/******************************************************************************/
/**
\brief  i06 - 



\param  act_namesc - Action name
\param  int_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUIDefReaction"

OEHAction *OEHDataWidget :: SetGUIDefReaction (const char *act_namesc, int int_event )
{

  return ( SetAction(act_namesc,NULL,
                     int_event,this,YES) );

}

/******************************************************************************/
/**
\brief  SetNewInstKey - 



\return term - 

\param  prophdl - 
\param  str_key - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNewInstKey"

logical OEHDataWidget :: SetNewInstKey (PropertyHandle *prophdl, char *str_key )
{

  if ( str_key )
  {  
    if ( prophdl->GetSortKeySMCB() )
      prophdl->SetSortKey(prophdl->StringToKey(str_key),new_instance.Get());
    else if ( prophdl->GetKeySMCB() )
      prophdl->SetKey(prophdl->StringToKey(str_key),new_instance.Get());
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  SetPath - 



\return pOTreeLayout - Tree layout definition
-------------------------------------------------------------------------------
\brief  i00 - 



\param  prop_path - Property path
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

OTreeLayout *OEHDataWidget :: SetPath (char *prop_path, ODSPropertyType prop_type )
{

BEGINSEQ
  if ( !GetLayout() )                                ERROR
  olayout->SetPath(prop_path,prop_type);

RECOVER

ENDSEQ
  return(olayout);
}

/******************************************************************************/
/**
\brief  i01 - 



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

OTreeLayout *OEHDataWidget :: SetPath (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type, PIACC accmode_w )
{

BEGINSEQ
  if ( !GetLayout() )                                ERROR 
  olayout->SetPath(prop_path,strname,is_collection,sort_index_name,prop_type,accmode_w);
  if ( accmode_w == PI_Read )
    readOnly = YES;
RECOVER

ENDSEQ
  return(olayout);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  rODSPropPath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

OTreeLayout *OEHDataWidget :: SetPath (ODSPropPath &rODSPropPath )
{

BEGINSEQ
  if ( !GetLayout() )                                ERROR 
  olayout->SetPath(rODSPropPath);
  if ( rODSPropPath.get_acc_mode() == PI_Read )
    readOnly = YES;
RECOVER

ENDSEQ
  return(olayout);
}

/******************************************************************************/
/**
\brief  SetPropertyHandle - 



\return term - 

\param  prophdl - 
\param  auto_select - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyHandle"

logical OEHDataWidget :: SetPropertyHandle (PropertyHandle *prophdl, logical auto_select )
{
  logical                 term = NO;
BEGINSEQ
  if ( ! prophdl )                                   ERROR
  Activate();
  
  if ( ODataWidget::SetPropertyHandle(prophdl,auto_select) )
                                                     ERROR
  DA_Refresh();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ShowEvent - 



\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowEvent"

int8 OEHDataWidget :: ShowEvent ( )
{
  QWidget     *widget;
  QWidget     *parent;
  int8         executed = AUTO;

BEGINSEQ
  if ( GenerateEvent(GEV_Show) == YES )              ERROR
  
  UpdateControl();
  
/* das alles dient der Grössenkorretur bei Splitter und Docking. Geht aber nicht
  if ( (widget = WidgetQ()) && parent_odw && 
       parent_odw->WidgetQ()              &&                       
       (parent = parent_odw->WidgetQ()->parentWidget()) ) // parent=OSimpleWidget
  {
    if ( parent->inherits("QDockWidget") && od_control )
      od_control->get_dock_widget()->ResetSize(this);
    if ( parent->inherits("QSplitter") )
      ResetSize(this);
  }
*/
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  UpdateControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateControl"

void OEHDataWidget :: UpdateControl ( )
{



}

/******************************************************************************/
/**
\brief  ValueItem - 



\return pODSItem - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueItem"

ODSItem *OEHDataWidget :: ValueItem ( )
{
  ODS         *ods = GetSelectedODS();
  return ( ods ? ods->get_prop() : NULL);

}

/******************************************************************************/
/**
\brief  updateSelection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateSelection"

void OEHDataWidget :: updateSelection ( )
{



}

/******************************************************************************/
/**
\brief  ~OEHDataWidget - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHDataWidget"

     OEHDataWidget :: ~OEHDataWidget ( )
{
  OFont    *of;
  stssdel();             // closing widget                 

  Deactivate(NO);
    
  delete base_ods;
  base_ods = NULL;

  while ( of = fonts.RemoveTail() )
    delete of;


}


