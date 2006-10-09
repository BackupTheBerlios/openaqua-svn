/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_BaseStruct



\date     $Date: 2006/05/13 17:32:39,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_BaseStruct_HPP
#define   pc_SDB_BaseStruct_HPP

class     pc_SDB_BaseStruct;

class     ErrorProtocol;
class     PropertyHandle;
#include  <spc_SDB_Relationship.hpp>
class  pc_SDB_BaseStruct :public pc_SDB_Relationship
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph );
public     :                                        logical Store (DBFieldDef *dbflddef );
public     :                                        logical StoreAll (DBStructDef *strdefptr );
public     :                  OPSImpExp                  pc_SDB_BaseStruct (PropertyHandle *prophdl );
};

#endif
