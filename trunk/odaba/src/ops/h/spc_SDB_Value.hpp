/********************************* Class Declaration ***************************/
/**
\package  OPS - 
\class    pc_SDB_Value

\brief    


\date     $Date: 2006/08/28 19:53:07,54 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Value_HPP
#define   pc_SDB_Value_HPP

class     pc_SDB_Value;

#include  <sPropertyHandle.hpp>
class  pc_SDB_Value :public PropertyHandle
{

public     :
public     :                                        logical ContainsZeroValue ( );
public     :                                        logical SetupCopySet (PropertyHandle *srce_ph );
public     :                                             pc_SDB_Value (PropertyHandle *prophdl );
};

#endif
