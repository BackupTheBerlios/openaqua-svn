/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Index



\date     $Date: 2006/05/14 13:14:14,28 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Index_HPP
#define   pc_SDB_Index_HPP

class     pc_SDB_Index;

class     DBIndex;
class     DBIndexList;
class     ErrorProtocol;
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
class  pc_SDB_Index :public PropertyHandle
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, PropertyHandle *str_ph, TypeKey &tkey );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, TypeKey &tkey );
public     :                                        logical Store (DBIndex *dbidxdef );
public     :                                        logical StoreAll (DBIndexList *indexlist );
public     :                  OPSImpExp                  pc_SDB_Index (PropertyHandle *prophdl );
};

#endif
