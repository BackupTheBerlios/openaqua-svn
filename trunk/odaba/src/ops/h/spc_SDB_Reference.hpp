/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Reference



\date     $Date: 2006/05/11 15:49:47,84 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Reference_HPP
#define   pc_SDB_Reference_HPP

class     pc_SDB_Reference;

class     ErrorProtocol;
class     PropertyHandle;
#include  <spc_SDB_Property.hpp>
class  pc_SDB_Reference :public pc_SDB_Property
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, logical base_opt=NO );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph );
public     :                                        logical Store (DBFieldDef *dbflddef );
public     :                                        logical StoreAll (DBStructDef *strdefptr );
public     :                  OPSImpExp                  pc_SDB_Reference (PropertyHandle *prophdl );
};

#endif
