/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemInstState

\brief    


\date     $Date: 2006/03/13 21:33:57,76 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSItemInstState_HPP
#define   ODSItemInstState_HPP

class     ODSItemInstState;

class  ODSItemInstState
{
protected  :         int32                                        lastIndex;                                                 
protected  :         int32                                        lastObjID;                                                 
protected  :         int32                                        instModCount;                                              
protected  :         logical                                      inst_write;                                                

public     :
                     int32                                        get_lastIndex() { return(lastIndex); }
                     int32                                        get_lastObjID() { return(lastObjID); }
                     int32                                        get_instModCount() { return(instModCount); }
                     logical                                      get_inst_write() { return(inst_write); }
public     :                                     logical HasChanged (ODSItemInstState *inst_state, PropertyHandle *ph );
public     :                                                             ODSItemInstState ( );
public     :                                     void ResetState ( );
public     :                                     void SetState (PropertyHandle *ph );
public     :                                     void SetupModCount (PropertyHandle *ph );
public     :                                     void SyncState (ODSItemInstState *inst_state );
};

#endif
