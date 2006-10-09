/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OEHControlValue

\brief    


\date     $Date: 2006/04/21 17:32:14,60 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHControlValue"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHSlotRouter.hpp>
#include  <sOEHControlValue.hpp>


/******************************************************************************/
/**
\brief  Activate - Activates signals for the value
        coll_opt: connect signals for collections

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OEHControlValue :: Activate ( )
{

  return ( ActivateValue(NO,NO) );

}

/******************************************************************************/
/**
\brief  ActivateValue - 


\return term - 

\param  coll_opt - 
\param  ignore_evthandling - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateValue"

logical OEHControlValue :: ActivateValue (logical coll_opt, logical ignore_evthandling )
{
  logical          ini  = stscini();
  logical                 term = NO;

  if ( !ini && (event_handling || ignore_evthandling) )
  {
    Connect( SIGNAL (OnActivated(logical))  , SLOT (handleActivate()));
    Connect( SIGNAL (OnHandleOpened())      , SLOT (handleOpen())    );
    Connect( SIGNAL (OnInstanceSelected())  , SLOT (valueSelect())   );
    Connect( SIGNAL (OnInstanceReset())     , SLOT (valueReset())    );
    Connect( SIGNAL (OnInstanceUpdated())   , SLOT (valueUpdate())   );
  }
  
  OEHControlData::Activate();

  if ( coll_opt && !ini && (event_handling || ignore_evthandling) )
  {
//    Connect( SIGNAL (OnCollectionUpdated()) , SLOT (valueSelect())   );
//    Connect( SIGNAL (OnCollectionReset())   , SLOT (valueReset())    );
//    Connect( SIGNAL (OnCollectionChanged()) , SLOT (valueSelect())   );   
    Connect( SIGNAL (OnInstanceRemoved())   , SLOT (valueReset())    );   
    Connect( SIGNAL (OnInstanceInserted())  , SLOT (valueSelect())   );   
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

logical OEHControlValue :: Deactivate (logical data_only )
{

  return ( DeactivateValue(NO,NO,data_only) );

}

/******************************************************************************/
/**
\brief  DeactivateValue - 


\return term - 

\param  coll_opt - 
\param  ignore_evthandling - 
\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateValue"

logical OEHControlValue :: DeactivateValue (logical coll_opt, logical ignore_evthandling, logical data_only )
{
  logical                 ini  = stscini();
  logical                 term = NO;
  if ( coll_opt && ini && (event_handling || ignore_evthandling) && !data_only )
  {
    Disconnect( SIGNAL (OnCollectionUpdated()) , SLOT (valueSelect())   );
    Disconnect( SIGNAL (OnCollectionReset())   , SLOT (valueReset())    );
    Disconnect( SIGNAL (OnCollectionChanged()) , SLOT (valueSelect())   );   
    Disconnect( SIGNAL (OnInstanceRemoved())   , SLOT (valueReset())    );   
    Disconnect( SIGNAL (OnInstanceInserted())  , SLOT (valueSelect())   );   
  }
  
  OEHControlData::Deactivate(data_only);

  if ( ini && (event_handling || ignore_evthandling) && !data_only )
  {
    Disconnect( SIGNAL (OnActivated(logical))  , SLOT (handleActivate()));
    Disconnect( SIGNAL (OnHandleOpened())      , SLOT (handleOpen())    );
    Disconnect( SIGNAL (OnInstanceSelected())  , SLOT (valueSelect())   );
    Disconnect( SIGNAL (OnInstanceReset())     , SLOT (valueReset())    );
    Disconnect( SIGNAL (OnInstanceUpdated())   , SLOT (valueUpdate())   );
  }

  return(term);
}

/******************************************************************************/
/**
\brief  OEHControlValue

-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlValue"

                        OEHControlValue :: OEHControlValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : OEHControlData (pODataWidget,oODataWidget,pODS_w)
{



}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHControlValue"

                        OEHControlValue :: OEHControlValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : OEHControlData(pODataWidget,oODataWidget,create_ods)
{



}

/******************************************************************************/
/**
\brief  getEnabled - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OEHControlValue :: getEnabled ( )
{

  return( ods()->ProvideItem() >= IST_selected );

}


