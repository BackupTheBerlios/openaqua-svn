/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    ODSItemState



\date     $Date: 2006/05/01 16:52:26,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItemState"

#include  <pogui7.h>
#include  <sODSItemState.hpp>

int32 is_count = 0;
int32 is_max = 0;
int32 is_total = 0;

/******************************************************************************/
/**
\brief  HasListChanged

\return cond

\param  col_state
\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasListChanged"

logical ODSItemState :: HasListChanged (ODSItemColState *col_state, PropertyHandle *ph )
{

  return ( ODSItemColState::HasChanged(col_state,ph) );

}

/******************************************************************************/
/**
\brief  HasValueChanged

\return cond

\param  inst_state
\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasValueChanged"

logical ODSItemState :: HasValueChanged (ODSItemInstState *inst_state, PropertyHandle *ph )
{

  return ( ODSItemInstState::HasChanged(inst_state,ph) );

}

/******************************************************************************/
/**
\brief  IsWrite

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical ODSItemState :: IsWrite ( )
{

  return( inst_write || col_write );

}

/******************************************************************************/
/**
\brief  ODSItemState


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemState"

     ODSItemState :: ODSItemState ( )
{
  ResetState();
is_total++;
if ( is_max < ++is_count ) is_max = is_count;

}

/******************************************************************************/
/**
\brief  ResetList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetList"

void ODSItemState :: ResetList ( )
{

  ODSItemColState::ResetState();

}

/******************************************************************************/
/**
\brief  ResetState


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetState"

void ODSItemState :: ResetState ( )
{

  ResetValue();
  ResetList();

}

/******************************************************************************/
/**
\brief  ResetValue


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetValue"

void ODSItemState :: ResetValue ( )
{

  ODSItemInstState::ResetState();

}

/******************************************************************************/
/**
\brief  SetList


\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetList"

void ODSItemState :: SetList (PropertyHandle *ph )
{

  ODSItemColState::SetState(ph);

}

/******************************************************************************/
/**
\brief  SetState


\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetState"

void ODSItemState :: SetState (PropertyHandle *ph )
{

  SetValue(ph);
  SetList(ph);

}

/******************************************************************************/
/**
\brief  SetValue


\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

void ODSItemState :: SetValue (PropertyHandle *ph )
{

  ODSItemInstState::SetState(ph);

}

/******************************************************************************/
/**
\brief  SyncList


\param  col_state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncList"

void ODSItemState :: SyncList (ODSItemColState *col_state )
{

  ODSItemColState::SyncState(col_state);

}

/******************************************************************************/
/**
\brief  SyncValue


\param  inst_state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncValue"

void ODSItemState :: SyncValue (ODSItemInstState *inst_state )
{

  ODSItemInstState::SyncState(inst_state);

}

/******************************************************************************/
/**
\brief  ~ODSItemState


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSItemState"

     ODSItemState :: ~ODSItemState ( )
{
is_count--;
}


