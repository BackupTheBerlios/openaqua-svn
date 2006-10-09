/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHControlData

\brief    
          can anybody please document? please

\date     $Date: 2006/07/24 21:53:53,15 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHControlData"

#include  <pogui7.h>
#include  <cqt.h>
#ifndef   DLL_CellData_HPP
#define   DLL_CellData_HPP
#include  <sCellData.hpp>
#include  <sDLL.h>
#endif
class     CellData;
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHSlotRouter.hpp>
#include  <sOStringList.hpp>
#include  <sOEHControlData.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OEHControlData :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
BEGINSEQ
  if ( !ini )
    Connect( SIGNAL (OnDesignModeActivated(logical))  , SLOT (activateDesignMode(logical)));

  if ( OEHDataWidget::Activate() )                  ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddCell - 




\param  pCellData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCell"

void OEHControlData :: AddCell (CellData *pCellData )
{

  if ( !cells )
    cells = new DLL(CellData)();

  cells->AddTail(pCellData);

}

/******************************************************************************/
/**
\brief  BeginOnce - 



\return started - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BeginOnce"

logical OEHControlData :: BeginOnce ( )
{
  logical     started = !ignore;
  ignore = YES;
  
  return ( started );

}

/******************************************************************************/
/**
\brief  ClearData - remove data




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OEHControlData :: ClearData ( )
{
  CellData            *cell;
  if ( cells )
  {
    cells->GoTop();
    while ( cell = cells->GetNext() )
      cell->ClearData();
  }


}

/******************************************************************************/
/**
\brief  ClearList - remove all list items




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearList"

void OEHControlData :: ClearList ( )
{



}

/******************************************************************************/
/**
\brief  Connect - 




\param  ods_signal - 
\param  oeh_slot - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

void OEHControlData :: Connect (char *ods_signal, char *oeh_slot )
{

  router->Connect(ods_signal,oeh_slot);

}

/******************************************************************************/
/**
\brief  CreateStringList - 



\return string_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStringList"

OStringList *OEHControlData :: CreateStringList ( )
{
  PropertyHandle       *prophdl;
  BEGIN_ONCE(ignore)
BEGINSEQ
  RemoveStringList();
  
  ProvideBaseODS();
  if ( !(prophdl = List()->Handle()) )               ERROR
  
  string_list = new OStringList();
  if ( string_list->Fill(prophdl) )                  ERROR

RECOVER

ENDSEQ
  END_ONCE
  return(string_list);
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

logical OEHControlData :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( OEHDataWidget::Deactivate(data_only) ) 
    term = YES;

  if ( ini && !data_only )
    Disconnect( SIGNAL (OnDesignModeActivated(logical))  , SLOT (activateDesignMode(logical)));

  return(term);
}

/******************************************************************************/
/**
\brief  Disconnect - 




\param  ods_signal - 
\param  oeh_slot - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void OEHControlData :: Disconnect (char *ods_signal, char *oeh_slot )
{

  router->Disconnect(ods_signal,oeh_slot);

}

/******************************************************************************/
/**
\brief  EndOnce - 




\param  started - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EndOnce"

void OEHControlData :: EndOnce (logical started )
{

  if ( started )
    ignore = NO;

}

/******************************************************************************/
/**
\brief  FillData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OEHControlData :: FillData ( )
{



}

/******************************************************************************/
/**
\brief  FillList - Create (all) ListItems




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillList"

void OEHControlData :: FillList ( )
{



}

/******************************************************************************/
/**
\brief  GetStringList - 



\return string_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringList"

OStringList *OEHControlData :: GetStringList ( )
{


  return(this ? string_list : NULL);
}

/******************************************************************************/
/**
\brief  HandleActivated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleActivated"

void OEHControlData :: HandleActivated ( )
{

  GenerateEvent(DEV_Activated);
//  ValueSelected();

}

/******************************************************************************/
/**
\brief  HandleClosed - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleClosed"

void OEHControlData :: HandleClosed ( )
{

//  GenerateEvent(DEV_Close);  event not yet defined
  ods()->ValueReset();
  UpdateState();
  
  ClearList();
  ClearData();
  

  


}

/******************************************************************************/
/**
\brief  HandleOpened - 




\param  chk_visible - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleOpened"

void OEHControlData :: HandleOpened (logical chk_visible )
{
  BEGIN_ONCE(ignore)
  QWidget            *qw = WidgetQ();

BEGINSEQ
  ods()->ValueInit();
  UpdateState();
  
  GenerateEvent(DEV_Opened);
  
  if ( chk_visible && qw && !qw->isVisible() )       LEAVESEQ
  if ( !SyncColState() )                             ERROR
  
  GenerateEvent(DEV_Fill);
  FillList();
  FillData();
  GenerateEvent(DEV_Filled);

RECOVER

ENDSEQ
  END_ONCE
}

/******************************************************************************/
/**
\brief  ListChanged - 




\param  chk_visible - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListChanged"

void OEHControlData :: ListChanged (logical chk_visible )
{
  BEGIN_ONCE(ignore)
  QWidget            *qw;
  OEH                *pOEH = oeh();
BEGINSEQ
  if ( !pOEH )                                       LEAVESEQ
  qw = pOEH->get_oeh_widget()->WidgetQ();
  
  ods()->ValueInit();
  UpdateState();
  
  if ( chk_visible && qw && !qw->isVisible() )       LEAVESEQ
  if ( !SyncColState() )                             LEAVESEQ
  if ( !ods()->DefinesCollection() &&                          // 14.10.2005, damit die Events nicht fuer einfache attribute erzeugt werden
       !GetListControl() )                           LEAVESEQ  // 15.11.2005, damit tabellen auf eingestellter instanz gefuellt werden 
  
  GenerateEvent(DEV_Fill);
  FillList();
  GenerateEvent(DEV_Filled);

ENDSEQ
  END_ONCE
}

/******************************************************************************/
/**
\brief  ListReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListReset"

void OEHControlData :: ListReset ( )
{
  BEGIN_ONCE(ignore)
  ods()->ResetList();
  
  UpdateState();
  GenerateEvent(DEV_Clear);
  
  ClearList();
  

  END_ONCE
}

/******************************************************************************/
/**
\brief  ListUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListUpdated"

void OEHControlData :: ListUpdated ( )
{
  BEGIN_ONCE(ignore)
  QWidget            *qw = WidgetQ();
BEGINSEQ
  ods()->ValueInit();
  UpdateState();
  
  if ( qw && !qw->isVisible() )                      LEAVESEQ
  if ( !SyncColState() )                      ERROR
  
  GenerateEvent(DEV_Fill); // ist zuviel, wenn UpdateList überladen ist, 
  
  UpdateList();
  
  GenerateEvent(DEV_Filled);

RECOVER

ENDSEQ
  END_ONCE
}

/******************************************************************************/
/**
\brief  OEHControlData - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlData"

     OEHControlData :: OEHControlData (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : OEHDataWidget (pODataWidget,oODataWidget,pODS_w),
  string_list(NULL),
  cells(NULL),
  ignore(NO),
  router(NULL)
{

  router = new OEHSlotRouter(this);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlData"

     OEHControlData :: OEHControlData (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : OEHDataWidget (pODataWidget,oODataWidget,create_ods),
  string_list(NULL),
  cells(NULL),
  ignore(NO),
  router(NULL)

{

  router = new OEHSlotRouter(this);

}

/******************************************************************************/
/**
\brief  Reconnect - 




\param  ods_signal - 
\param  oeh_slot - 
\param  oeh_prev_slot - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reconnect"

void OEHControlData :: Reconnect (char *ods_signal, char *oeh_slot, char *oeh_prev_slot )
{

  router->Reconnect(ods_signal,oeh_slot,oeh_prev_slot);

}

/******************************************************************************/
/**
\brief  RemoveCell - 




\param  pCellData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveCell"

void OEHControlData :: RemoveCell (CellData *pCellData )
{

  if ( cells )
    cells->Remove(pCellData);


}

/******************************************************************************/
/**
\brief  RemoveStringList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveStringList"

void OEHControlData :: RemoveStringList ( )
{

  delete string_list;
  string_list = NULL;

}

/******************************************************************************/
/**
\brief  SetReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OEHControlData :: SetReadOnly (logical fReadOnly )
{
  CellData            *cell;
//*** wozu ??  
/*
  if ( cells )
  {
    cells->GoTop();
    while ( cell = cells->GetNext() )
      cell->SetReadOnly(fReadOnly);
  }
*/

}

/******************************************************************************/
/**
\brief  StoreToValue - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  qsValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreToValue"

void OEHControlData :: StoreToValue (QString qsValue )
{
  BEGIN_ONCE(ignore)
  ods()->ValueSet(qsValue);

  END_ONCE
}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreToValue"

void OEHControlData :: StoreToValue (char *string )
{
  BEGIN_ONCE(ignore)
  ods()->ValueSet(string);
  END_ONCE
}

/******************************************************************************/
/**
\brief  i02 - 



\param  number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreToValue"

void OEHControlData :: StoreToValue (int32 number )
{
  BEGIN_ONCE(ignore)
  ods()->ValueSet(number);
  END_ONCE
}

/******************************************************************************/
/**
\brief  i03 - 



\param  cond - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreToValue"

void OEHControlData :: StoreToValue (logical cond )
{
  BEGIN_ONCE(ignore)
  ods()->ValueSet(cond);
  END_ONCE
}

/******************************************************************************/
/**
\brief  i04 - 



\param  date - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreToValue"

void OEHControlData :: StoreToValue (dbdt date )
{
  BEGIN_ONCE(ignore)
  ods()->ValueSet(date);
  END_ONCE
}

/******************************************************************************/
/**
\brief  i05 - 



\param  time - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreToValue"

void OEHControlData :: StoreToValue (dbtm time )
{
  BEGIN_ONCE(ignore)
  ods()->ValueSet(time);
  END_ONCE
}

/******************************************************************************/
/**
\brief  SyncColState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncColState"

logical OEHControlData :: SyncColState ( )
{

  return(ods()->SyncColState());

}

/******************************************************************************/
/**
\brief  SyncInstState - 



\return modified - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncInstState"

logical OEHControlData :: SyncInstState ( )
{

  return(ods()->SyncInstState());

}

/******************************************************************************/
/**
\brief  UnsyncColState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnsyncColState"

void OEHControlData :: UnsyncColState ( )
{

  return(ods()->ResetState());

}

/******************************************************************************/
/**
\brief  UnsyncState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnsyncState"

void OEHControlData :: UnsyncState ( )
{

  ods()->ResetState();

}

/******************************************************************************/
/**
\brief  UpdateControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateControl"

void OEHControlData :: UpdateControl ( )
{

  if ( !InDesignMode() )
  {
    ListChanged(YES);
    ods()->ResetValue();
    ValueSelected();
  }

}

/******************************************************************************/
/**
\brief  UpdateList - update the list

        most effective is of course a fill list.
        elegant is to detect what happened and then react


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateList"

void OEHControlData :: UpdateList ( )
{

  FillList();

}

/******************************************************************************/
/**
\brief  UpdateReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateReadOnly"

void OEHControlData :: UpdateReadOnly (logical fReadOnly )
{
  logical read_only;
  read_only = fReadOnly;
  
  if ( !in_design_mode )  
    read_only = fReadOnly || 
                (event_handling && ods()->InstIsReadOnly());
  
  SetReadOnly(read_only);  


}

/******************************************************************************/
/**
\brief  UpdateStringList - 



\return string_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateStringList"

OStringList *OEHControlData :: UpdateStringList ( )
{

BEGINSEQ
  if ( string_list && !List()->SyncColState() )      LEAVESEQ
  
  string_list = CreateStringList();

ENDSEQ
  return(string_list);
}

/******************************************************************************/
/**
\brief  ValueInserted - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueInserted"

void OEHControlData :: ValueInserted ( )
{

  ValueSelected();

}

/******************************************************************************/
/**
\brief  ValueRemoved - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueRemoved"

void OEHControlData :: ValueRemoved ( )
{

  ValueReset();

}

/******************************************************************************/
/**
\brief  ValueReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueReset"

void OEHControlData :: ValueReset ( )
{
  BEGIN_ONCE(ignore)
  ods()->ResetValue();
  UpdateState();
  
  GenerateEvent(DEV_Clear);
  
  ClearData();
  

  END_ONCE
}

/******************************************************************************/
/**
\brief  ValueSelected - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSelected"

logical OEHControlData :: ValueSelected ( )
{
  logical             term = NO;
  BEGIN_ONCE(ignore)
  QWidget            *qw = WidgetQ();

BEGINSEQ
//  ods()->ValueInit();
  UpdateState();
  
  if ( qw && !qw->isVisible() )                      LEAVESEQ
  if ( ods()->DefinesCollection() )                  LEAVESEQ
  if ( !SyncInstState() )                            ERROR
  
  if ( GenerateEvent(DEV_Fill) != YES )
  {
    FillData();
    GenerateEvent(DEV_Filled);
  }
  else
    ClearData();
RECOVER
  term = YES;
ENDSEQ
  END_ONCE
  return(term);
}

/******************************************************************************/
/**
\brief  ValueUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueUpdated"

void OEHControlData :: ValueUpdated ( )
{
  BEGIN_ONCE(ignore)
  GenerateEvent(DEV_Fill);
  FillData();
  GenerateEvent(DEV_Filled);

  END_ONCE
}

/******************************************************************************/
/**
\brief  getEnabled - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OEHControlData :: getEnabled ( )
{

  return( ods()->ColIsValid(YES,YES) );

}

/******************************************************************************/
/**
\brief  ~OEHControlData - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHControlData"

     OEHControlData :: ~OEHControlData ( )
{

  is_destroying = YES;
  
  RemoveStringList();
  
  delete router;
  router = NULL;

}


