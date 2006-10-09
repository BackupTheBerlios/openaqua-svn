/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Relationship



\date     $Date: 2006/05/14 13:14:04,32 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Relationship_HPP
#define   pc_SDB_Relationship_HPP

class     pc_SDB_Relationship;

class     ErrorProtocol;
class     PropertyHandle;
#include  <sTypeKey.hpp>
#include  <spc_SDB_Reference.hpp>
class  pc_SDB_Relationship :public pc_SDB_Reference
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph, logical base_opt=NO );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph );
public     :                  OPSImpExp             logical CheckExtend (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *ext_ph, char *extent_path );
public     :                  OPSImpExp             TypeKey &GetExtentKey (TypeKey &tkey, char *extent_path_w=NULL );
public     :                                        logical Store (DBFieldDef *dbflddef );
public     :                                        logical StoreAll (DBStructDef *strdefptr );
public     :                  OPSImpExp                  pc_SDB_Relationship (PropertyHandle *prophdl );
};

#endif
