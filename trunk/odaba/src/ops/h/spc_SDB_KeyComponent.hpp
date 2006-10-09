/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_KeyComponent



\date     $Date: 2006/05/11 13:39:40,62 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_KeyComponent_HPP
#define   pc_SDB_KeyComponent_HPP

class     pc_SDB_KeyComponent;

class     ErrorProtocol;
class     fmcb;
class     smcb;
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc_SDB_KeyComponent :public PropertyHandle
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol, char *prop_path );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol );
public     :                                        logical IsKeyComponent (char *fldnames );
public     :                                        char *KeyDataDecl (NString &nstring, PropertyHandle *dbs_ph );
public     :                                        logical Store (fmcb *fmcbptr );
public     :                                        logical StoreAll (smcb *keysmcb );
public     :                  OPSImpExp                  pc_SDB_KeyComponent (PropertyHandle *prophdl );
};

#endif
