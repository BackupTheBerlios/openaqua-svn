/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHSlotRouter

\brief    


\date     $Date: 2006/03/13 21:35:52,04 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHSlotRouter"

#include  <pogui7.h>
#include  <mOEHSlotRouter.h>
#include  <sOEHControlData.hpp>
#include  <sOEHSlotRouter.hpp>


/******************************************************************************/
/**
\brief  ActivateColl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateColl"

void OEHSlotRouter :: ActivateColl ( )
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

void OEHSlotRouter :: Connect (char *ods_signal, char *oeh_slot )
{

  connect(value->ods(), ods_signal,
          this        , oeh_slot  );


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

void OEHSlotRouter :: Disconnect (char *ods_signal, char *oeh_slot )
{

  disconnect(value->ods(), ods_signal,
             this        , oeh_slot  );


}

/******************************************************************************/
/**
\brief  OEHSlotRouter - 



\param  pOEHControlData -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHSlotRouter"

                        OEHSlotRouter :: OEHSlotRouter (OEHControlData *pOEHControlData )
                     : QObject (),
  value(pOEHControlData)
{



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

void OEHSlotRouter :: Reconnect (char *ods_signal, char *oeh_slot, char *oeh_prev_slot )
{

  if ( disconnect(value->ods(),ods_signal,
                  this        ,oeh_prev_slot) )
    connect(value->ods(), ods_signal,
            this        , oeh_slot  );


}

/******************************************************************************/
/**
\brief  activateDesignMode - 



\param  fDmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "activateDesignMode"

void OEHSlotRouter :: activateDesignMode (logical fDmode )
{

  value->ActivateDesignMode(fDmode);

}

/******************************************************************************/
/**
\brief  activateValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "activateValue"

void OEHSlotRouter :: activateValue ( )
{



}

/******************************************************************************/
/**
\brief  clearValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "clearValue"

void OEHSlotRouter :: clearValue ( )
{



}

/******************************************************************************/
/**
\brief  closeValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "closeValue"

void OEHSlotRouter :: closeValue ( )
{



}

/******************************************************************************/
/**
\brief  handleActivate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "handleActivate"

void OEHSlotRouter :: handleActivate ( )
{

  value->HandleActivated();

}

/******************************************************************************/
/**
\brief  handleClose - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "handleClose"

void OEHSlotRouter :: handleClose ( )
{

  value->HandleClosed();

}

/******************************************************************************/
/**
\brief  handleOpen - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "handleOpen"

void OEHSlotRouter :: handleOpen ( )
{

  value->HandleOpened(YES);

}

/******************************************************************************/
/**
\brief  insertedValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "insertedValue"

void OEHSlotRouter :: insertedValue ( )
{



}

/******************************************************************************/
/**
\brief  listChange - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "listChange"

void OEHSlotRouter :: listChange ( )
{

  value->ListChanged(YES);

}

/******************************************************************************/
/**
\brief  listReset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "listReset"

void OEHSlotRouter :: listReset ( )
{

  value->ListReset();

}

/******************************************************************************/
/**
\brief  listUpdate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "listUpdate"

void OEHSlotRouter :: listUpdate ( )
{

  value->ListUpdated();

}

/******************************************************************************/
/**
\brief  loadValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "loadValue"

void OEHSlotRouter :: loadValue ( )
{



}

/******************************************************************************/
/**
\brief  openValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "openValue"

void OEHSlotRouter :: openValue ( )
{



}

/******************************************************************************/
/**
\brief  removedValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "removedValue"

void OEHSlotRouter :: removedValue ( )
{



}

/******************************************************************************/
/**
\brief  set_value - 


\return term -

\param  pOEHControlData -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_value"

logical OEHSlotRouter :: set_value (OEHControlData *pOEHControlData )
{
  logical                 term = NO;
  value = pOEHControlData;
  return(term);
}

/******************************************************************************/
/**
\brief  updateValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateValue"

void OEHSlotRouter :: updateValue ( )
{



}

/******************************************************************************/
/**
\brief  valueInsert - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "valueInsert"

void OEHSlotRouter :: valueInsert ( )
{

  value->ValueInserted();

}

/******************************************************************************/
/**
\brief  valueRemove - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "valueRemove"

void OEHSlotRouter :: valueRemove ( )
{

  value->ValueRemoved();

}

/******************************************************************************/
/**
\brief  valueReset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "valueReset"

void OEHSlotRouter :: valueReset ( )
{

  value->ValueReset();

}

/******************************************************************************/
/**
\brief  valueSelect - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "valueSelect"

void OEHSlotRouter :: valueSelect ( )
{

  value->ValueSelected();

}

/******************************************************************************/
/**
\brief  valueUpdate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "valueUpdate"

void OEHSlotRouter :: valueUpdate ( )
{

  value->ValueUpdated();

}

/******************************************************************************/
/**
\brief  ~OEHSlotRouter - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHSlotRouter"

                        OEHSlotRouter :: ~OEHSlotRouter ( )
{



}


