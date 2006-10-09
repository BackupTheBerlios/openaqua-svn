/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    ODSItemColState



\date     $Date: 2006/04/25 13:00:58,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItemColState"

#include  <pogui7.h>
#include  <sODSItemColState.hpp>


/******************************************************************************/
/**
\brief  HasChanged

\return cond

\param  col_state
\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasChanged"

logical ODSItemColState :: HasChanged (ODSItemColState *col_state, PropertyHandle *ph )
{
  int32   mc   = col_state ? col_state->get_refModCount() : UNDEF;
  logical cond = NO;
  cond = col_state && ( lastRefID   != col_state->get_lastRefID() ||
                        (mc != AUTO && refModCount != mc)         ||
                        !lastRefID                                  );

  if ( !cond && mc == AUTO )
    if ( refModCount != ph->GetRefModCount() )
      cond = YES;

  return(cond);
}

/******************************************************************************/
/**
\brief  ODSItemColState


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemColState"

                        ODSItemColState :: ODSItemColState ( )
                     :   lastRefID(0),
  refModCount(0),
  col_write(NO)
{
}

/******************************************************************************/
/**
\brief  ResetState


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetState"

void ODSItemColState :: ResetState ( )
{
  lastRefID    = 0;
  refModCount  = 0;

  col_write    = NO;
}

/******************************************************************************/
/**
\brief  SetState


\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetState"

void ODSItemColState :: SetState (PropertyHandle *ph )
{

  lastRefID    = ph->GetCollectionID();
  refModCount  = ph->GetRefModCount();

  col_write    = ph->IsCollectionUpdate();

}

/******************************************************************************/
/**
\brief  SetupModCount


\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupModCount"

void ODSItemColState :: SetupModCount (PropertyHandle *ph )
{

  if ( refModCount == AUTO ) 
    refModCount = ph->GetRefModCount();


}

/******************************************************************************/
/**
\brief  SyncState


\param  col_state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyncState"

void ODSItemColState :: SyncState (ODSItemColState *col_state )
{

  if ( col_state )
  {
    lastRefID   = col_state->get_lastRefID();
    refModCount = col_state->get_refModCount();
  }

}


