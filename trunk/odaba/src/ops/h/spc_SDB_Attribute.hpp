/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Attribute



\date     $Date: 2006/05/11 14:43:22,92 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Attribute_HPP
#define   pc_SDB_Attribute_HPP

class     pc_SDB_Attribute;

class     ErrorProtocol;
class     PropertyHandle;
#include  <spc_SDB_Property.hpp>
class  pc_SDB_Attribute :public pc_SDB_Property
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph );
public     :                                        logical Store (DBFieldDef *dbflddef );
public     :                                        logical StoreAll (DBStructDef *strdefptr );
public     :                  OPSImpExp                  pc_SDB_Attribute (PropertyHandle *prophdl );
};

#endif
