/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHDBEventHandler

\brief    


\date     $Date: 2006/03/13 21:35:47,34 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHDBEventHandler"

#include  <pogui7.h>
#include  <sEventHandler.hpp>
#include  <sODSItem.hpp>
#include  <sOEHDBEventHandler.hpp>


/******************************************************************************/
/**
\brief  ActivateEventHandler - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateEventHandler"

void OEHDBEventHandler :: ActivateEventHandler ( )
{

  ActivateProcessEventHandler();
  ActivateServerEventHandler();

}

/******************************************************************************/
/**
\brief  ActivateEvents


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateEvents"

void OEHDBEventHandler :: ActivateEvents ( )
{

  is_busy = NO;

}

/******************************************************************************/
/**
\brief  DeactivateEventHandler


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateEventHandler"

void OEHDBEventHandler :: DeactivateEventHandler ( )
{

  DeactivateProcessEventHandler();
  DeactivateServerEventHandler();

}

/******************************************************************************/
/**
\brief  DeactivateEvents - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateEvents"

void OEHDBEventHandler :: DeactivateEvents ( )
{

  is_busy = YES;

}

/******************************************************************************/
/**
\brief  InstanceEventHandler - 


\return term -

\param  csa_event -
\param  objid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceEventHandler"

logical OEHDBEventHandler :: InstanceEventHandler (CSA_Events csa_event, int32 objid )
{
  logical                 term = NO;
BEGINSEQ
  if ( is_busy )                                     LEAVESEQ
  is_busy = YES;
      
  switch ( csa_event )
  {
    case SE_Update : ods_item->InstanceUpdated();
                     break;
    case SE_Delete : ods_item->InstanceUpdated();
                     break;
    default        : ;
  }
  
  is_busy = NO;

ENDSEQ
  is_busy = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  OEHDBEventHandler - 



\param  odsitem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHDBEventHandler"

                        OEHDBEventHandler :: OEHDBEventHandler (ODSItem *odsitem )
                     : EventHandler(*odsitem->get_property()),
  ods_item(odsitem),
  is_busy(NO)
{

//  odsitem->Handle()->RegisterHandle();
  
  ActivateEventHandler();


}

/******************************************************************************/
/**
\brief  ProcessInstanceHandler - 


\return term -

\param  db_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessInstanceHandler"

logical OEHDBEventHandler :: ProcessInstanceHandler (DB_Event db_event )
{
  logical                 term = NO;
BEGINSEQ
  if ( is_busy )                                     LEAVESEQ
  is_busy = YES;
      
  switch ( db_event )
  {
    case DBO_Initialize : ods_item->InstanceInitialized();
                          break;
/*  
    case DBO_Read       : ods_item->InstanceSelected();
                          break;
*/
    case DBP_Store      :
    case DBO_Stored     : ods_item->InstanceUpdated();
                          break;
    case DBO_Reset      : ods_item->InstanceReset();
                          break;
    default             : ;
  }
  
  is_busy = NO;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProcessPropertyHandler - 


\return term -

\param  db_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessPropertyHandler"

logical OEHDBEventHandler :: ProcessPropertyHandler (DB_Event db_event )
{
  logical                 term = NO;
BEGINSEQ
  if ( is_busy )                                     LEAVESEQ
  is_busy = YES;
      
  switch ( db_event )
  {
    case DBO_Opened     : ods_item->RefreshSubItems(NO);
                          break;
    case DBO_Initialize : ods_item->InstanceInitialized();
    case DBO_Read       : 
    case DBO_Created    : 
    case DBP_Select     : ods_item->InstanceSelected();
                          break;
 // ggf. müssen die folgenden events ebenso ODSItem-gemäss reagieren,
 // um z.B. arrays auch wie collections zu behandeln
    case DBO_Refresh    : ods_item->CollectionChanged(YES); // ods-item optimiert ueber mod
                          break;
    case DBO_Reset      : ods_item->InstanceReset(); // war collection reset, geaendert, weil ph->findnext irgendwas tat
                          break;
    case DBO_Stored     : ods_item->InstanceUpdated();
                          break;
    case DBO_Removed    : ods_item->InstanceRemoved();
                          break;
    case DBO_Inserted   : ods_item->InstanceInserted();
                          break;
    case DBO_Close      : ods_item->ResetPH();
                          break;
    default             : ;
  }
  
  is_busy = NO;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PropertyEventHandler - 


\return term -

\param  csa_event -
\param  objid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyEventHandler"

logical OEHDBEventHandler :: PropertyEventHandler (CSA_Events csa_event, int32 objid )
{
  logical                 term = NO;
BEGINSEQ
  if ( is_busy )                                     LEAVESEQ
  is_busy = YES;
  
  switch ( csa_event )
  {
    case SE_Update : 
    case SE_Delete : ods_item->CollectionUpdated();
                     break;
    default        : ;
  }

  is_busy = NO;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OEHDBEventHandler - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHDBEventHandler"

                        OEHDBEventHandler :: ~OEHDBEventHandler ( )
{

  DeactivateEventHandler();

}


