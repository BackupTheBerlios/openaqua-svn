/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEventHandler

\brief    


\date     $Date: 2006/03/13 21:35:52,78 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEventHandler"

#include  <pogui7.h>
#include  <sODSItem.hpp>
#include  <sODeferrer.hpp>
#include  <sOEventHandler.hpp>


/******************************************************************************/
/**
\brief  InstanceEventHandler - 


\return cond -

\param  csa_event_id -
\param  objid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceEventHandler"

logical OEventHandler :: InstanceEventHandler (CSA_Events csa_event_id, int32 objid )
{

BEGINSEQ
  if ( objid == o->InstGetObjID() )
    USE_DEFERRER1(o,param1->modUpdate(YES,YES,NO); 
                    param1->OnInstChanged(),        
                  ODSItem*,o);      
  
  USE_DEFERRER2(o,param1->modUpdate(YES,YES,NO); 
                  param1->OnBlockInstChanged(param2),
                ODSItem*,o,long,objid);              


RECOVER

ENDSEQ
  return YES;
}

/******************************************************************************/
/**
\brief  OEventHandler - 



\param  pODSItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEventHandler"

                        OEventHandler :: OEventHandler (ODSItem *pODSItem )
                     : EventHandler (pODSItem ? *pODSItem->Handle() : PropertyHandle()),
  o(pODSItem)
{



}

/******************************************************************************/
/**
\brief  PropertyEventHandler - 


\return cond -

\param  csa_event_id -
\param  objid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyEventHandler"

logical OEventHandler :: PropertyEventHandler (CSA_Events csa_event_id, int32 objid )
{

BEGINSEQ
  USE_DEFERRER1(o,param1->modUpdate(YES,YES,NO); 
                  param1->OnColChanged(),
                ODSItem*,o);


RECOVER

ENDSEQ
  return YES;
}


