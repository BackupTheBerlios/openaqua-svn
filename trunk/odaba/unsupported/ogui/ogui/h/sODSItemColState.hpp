/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemColState

\brief    


\date     $Date: 2006/03/13 21:33:57,62 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSItemColState_HPP
#define   ODSItemColState_HPP

class     ODSItemColState;

class  ODSItemColState
{
protected  :         int32                                        lastRefID;                                                 
protected  :         int32                                        refModCount;                                               
protected  :         logical                                      col_write;                                                 

public     :
                     int32                                        get_lastRefID() { return(lastRefID); }
                     int32                                        get_refModCount() { return(refModCount); }
                     logical                                      get_col_write() { return(col_write); }
public     :                                     logical HasChanged (ODSItemColState *col_state, PropertyHandle *ph );
public     :                                                             ODSItemColState ( );
public     :                                     void ResetState ( );
public     :                                     void SetState (PropertyHandle *ph );
public     :                                     void SetupModCount (PropertyHandle *ph );
public     :                                     void SyncState (ODSItemColState *col_state );
};

#endif
