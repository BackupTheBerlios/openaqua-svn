/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODSItemInstState

\brief    


\date     $Date: 2006/06/13 22:52:19,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItemInstState"

#include  <pogui7.h>
#include  <sODSItemInstState.hpp>


/******************************************************************************/
/**
\brief  HasChanged - 


\return cond - 

\param  inst_state - 
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasChanged"

logical ODSItemInstState :: HasChanged (ODSItemInstState *inst_state, PropertyHandle *ph )
{
  int32   mc   = inst_state ? inst_state->get_instModCount() : UNDEF;
  logical cond = NO;
  cond = inst_state && ( lastObjID    != inst_state->get_lastObjID() ||
                         (mc != AUTO && instModCount != mc)          ||
                         lastObjID <= 0                                );

  if ( !cond && mc == AUTO )
    if ( instModCount != ph->GetInstModCount() )
      cond = YES;

  return(cond);
}

/******************************************************************************/
/**
\brief  ODSItemInstState - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemInstState"

     ODSItemInstState :: ODSItemInstState ( )
                     :   lastIndex(AUTO),
  lastObjID(0),
  instModCount(0),
  inst_write(NO)
{



}

/******************************************************************************/
/**
\brief  ResetState - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetState"

void ODSItemInstState :: ResetState ( )
{

  lastIndex    = AUTO;
  lastObjID    = 0;
  instModCount = 0;

  inst_write   = NO;


}

/******************************************************************************/
/**
\brief  SetState - 



\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetState"

void ODSItemInstState :: SetState (PropertyHandle *ph )
{

  lastIndex    = ph->GetCurrentIndex();
  lastObjID    = ph->GetLOID();
  instModCount = ph->GetInstModCount();

  inst_write   = ph->IsWrite();


}

/******************************************************************************/
/**
\brief  SetupModCount - 



\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupModCount"

void ODSItemInstState :: SetupModCount (PropertyHandle *ph )
{

  if ( lastObjID > 0 && instModCount == AUTO ) 
    instModCount = ph->GetInstModCount();


}

/******************************************************************************/
/**
\brief  SyncState - 



\param  inst_state - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncState"

void ODSItemInstState :: SyncState (ODSItemInstState *inst_state )
{

  if ( inst_state )
  {
    lastIndex    = inst_state->get_lastIndex();
    lastObjID    = inst_state->get_lastObjID();
    instModCount = inst_state->get_instModCount();
  }


}


