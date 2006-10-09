/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHControlListValue

\brief    


\date     $Date: 2006/07/05 16:37:44,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHControlListValue"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODSPropPath.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlList.hpp>
#include  <sOListCtl.hpp>
#include  <sOStringList.hpp>
#include  <sOEHControlListValue.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OEHControlListValue :: Activate ( )
{

  return ( ActivateListValue(NO) );

}

/******************************************************************************/
/**
\brief  ActivateListValue - 



\return term - 

\param  ignore_evthandling - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateListValue"

logical OEHControlListValue :: ActivateListValue (logical ignore_evthandling )
{
  logical                 ini  = stscini();
  logical                 term = NO;
  OEHControlList::ActivateList(ignore_evthandling);

  if ( odw_ods->get_path().get_collection() && !base_ods )
  {
    list_as_ods = YES;
  }
  else
  {
    ProvideBaseODS();
    list_as_ods = NO;
  }

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

logical OEHControlListValue :: Deactivate (logical data_only )
{

  return ( DeactivateListValue(NO,data_only) );

}

/******************************************************************************/
/**
\brief  DeactivateListValue - 



\return term - 

\param  ignore_evthandling - 
\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateListValue"

logical OEHControlListValue :: DeactivateListValue (logical ignore_evthandling, logical data_only )
{
  logical                 ini  = stscini();
  logical                 term = NO;
  OEHControlList::DeactivateList(ignore_evthandling,data_only);


  return(term);
}

/******************************************************************************/
/**
\brief  HandleActivated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleActivated"

void OEHControlListValue :: HandleActivated ( )
{

  Reconnect( SIGNAL (OnInstanceSelected()), SLOT (valueSelect()), SLOT (listChange())   );

  OEHControlData::HandleActivated();

}

/******************************************************************************/
/**
\brief  HandleOpened - 




\param  chk_visible - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleOpened"

void OEHControlListValue :: HandleOpened (logical chk_visible )
{
  ODS               *vods = ods();
BEGINSEQ
  ods_attribute  = UNDEF; 
  ods_multi_ref  = UNDEF;
    
  if ( vods->ItemState() < IST_opened )                ERROR
    
  ods_multi_ref = NO;
  if ( vods->IsAttribute() )
    ods_attribute = YES;
  else if ( vods->IsCollection() )
    ods_multi_ref = YES;

  OEHControlList::HandleOpened(chk_visible);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  List - 



\return pODS - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "List"

ODS *OEHControlListValue :: List ( )
{


  return ( list_as_ods ? ods() : base_ods );
}

/******************************************************************************/
/**
\brief  ListControl - 



\return pOListCtl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListControl"

OListCtl *OEHControlListValue :: ListControl ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  OEHControlListValue - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlListValue"

     OEHControlListValue :: OEHControlListValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : OEHControlList (pODataWidget,oODataWidget,create_ods),
  list_as_ods(NO),
  ods_attribute(UNDEF),
  ods_multi_ref(UNDEF)
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
#define    MOD_ID  "OEHControlListValue"

     OEHControlListValue :: OEHControlListValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : OEHControlList (pODataWidget,oODataWidget,pODS),
  list_as_ods(NO),
  ods_attribute(UNDEF),
  ods_multi_ref(UNDEF)
{



}

/******************************************************************************/
/**
\brief  UpdateControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateControl"

void OEHControlListValue :: UpdateControl ( )
{

  OEHControlData::UpdateControl();


}

/******************************************************************************/
/**
\brief  ValueInserted - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueInserted"

void OEHControlListValue :: ValueInserted ( )
{

  OEHControlList::ValueInserted();
//  ValueUpdated();

}

/******************************************************************************/
/**
\brief  ValueLocate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueLocate"

logical OEHControlListValue :: ValueLocate ( )
{

  if ( !ods_attribute && !ods_multi_ref )   // for singl. reference
    ods()->Item()->ColScroll(0);            // position first instance
  
  return ( !List()->ColFind(ods()->Value(),YES) );

}

/******************************************************************************/
/**
\brief  ValueSelected - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValueSelected"

logical OEHControlListValue :: ValueSelected ( )
{
  logical             term = NO;
  BEGIN_ONCE(ignore)
  QWidget            *qw = WidgetQ();
BEGINSEQ
  UpdateState();
  
  if ( qw && !qw->isVisible() )                      LEAVESEQ
  if ( !SyncInstState() )                            ERROR
  
  GenerateEvent(DEV_Fill);
  FillData();
  GenerateEvent(DEV_Filled);

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

void OEHControlListValue :: ValueUpdated ( )
{

  if ( !ValueLocate() && ListControl() )
    ListControl()->ValueUpdated();
  
  ods()->ResetState();
  ValueSelected();

}

/******************************************************************************/
/**
\brief  ~OEHControlListValue - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHControlListValue"

     OEHControlListValue :: ~OEHControlListValue ( )
{

  RemoveStringList();
  Deactivate(NO);


}


