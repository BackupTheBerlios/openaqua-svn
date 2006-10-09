/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemState

\brief    


\date     $Date: 2006/03/13 21:33:57,89 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSItemState_HPP
#define   ODSItemState_HPP

class     ODSItemState;

#include  <cItemStates.h>
#include  <sODSItemColState.hpp>
#include  <sODSItemInstState.hpp>
class  ODSItemState :public ODSItemColState,
public ODSItemInstState
{

public     :
public     :                                     logical HasListChanged (ODSItemColState *col_state, PropertyHandle *ph );
public     :                                     logical HasValueChanged (ODSItemInstState *inst_state, PropertyHandle *ph );
public     :                                     logical IsWrite ( );
public     :                                                             ODSItemState ( );
public     :                                     void ResetList ( );
public     :                                     void ResetState ( );
public     :                                     void ResetValue ( );
public     :                                     void SetList (PropertyHandle *ph );
public     :                                     void SetState (PropertyHandle *ph );
public     :                                     void SetValue (PropertyHandle *ph );
public     :                                     void SyncList (ODSItemColState *col_state );
public     :                                     void SyncValue (ODSItemInstState *inst_state );
public     :                                                             ~ODSItemState ( );
};

#endif
