/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Structure



\date     $Date: 2006/05/13 14:33:35,75 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Structure_HPP
#define   pc_SDB_Structure_HPP

class     pc_SDB_Structure;

class     ErrorProtocol;
class     PropertyHandle;
#include  <sNString.hpp>
#include  <sTypeKey.hpp>
#include  <spc_SDB_NameSpace.hpp>
class  pc_SDB_Structure :public pc_SDB_NameSpace
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol );
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, PropertyHandle *str_ph, PropertyHandle *cs_ph, PropertyHandle *ext_ph );
public     :                  OPSImpExp             logical CheckBasePath (ErrorProtocol *protocol, char *prop_path, TypeKey &tkey );
public     :                  OPSImpExp             logical CheckKeyField (ErrorProtocol *protocol, char *prop_path, logical refr_accept, logical mult_accept, logical base_accept, logical err_opt );
public     :                  OPSImpExp             PropertyHandle *GetMember (ErrorProtocol *protocol, char *propnames, logical recursiv, logical err_opt );
public     :                  OPSImpExp             PropertyHandle *GetMember (char *propnames, logical recursiv, logical err_opt );
public     :                                        logical IsBasedOn (TypeKey mkey, TypeKey &tkey );
public     :                  OPSImpExp             logical IsChecked ( );
public     :                  OPSImpExp             logical IsKeyComponent (char *fldnames );
public     :                                        logical SetChecked (logical option );
public     :                                        logical Store (DBStructDef *strdefptr );
public     :                  OPSImpExp                  pc_SDB_Structure (PropertyHandle *prophdl );
public     :                  OPSImpExp                  pc_SDB_Structure (DatabaseHandle &dbhandle, PIACC accopt_w=PI_Read );
public     :                  OPSImpExp                  pc_SDB_Structure (DatabaseHandle &dbhandle, char *strnames, PIACC accopt_w=PI_Read );
};

#endif
