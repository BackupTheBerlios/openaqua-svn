/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Key



\date     $Date: 2006/05/11 13:39:08,70 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Key_HPP
#define   pc_SDB_Key_HPP

class     pc_SDB_Key;

#include  <sDLL.h>
class     kcb;
class     ErrorProtocol;
class     kcb;
#include  <sPropertyHandle.hpp>
class  pc_SDB_Key :public PropertyHandle
{

public     :
public     :                  OPSImpExp             logical Check (ErrorProtocol *protocol );
public     :                  OPSImpExp             logical CheckAll (ErrorProtocol *protocol );
public     :                                        logical IsKeyComponent (char *fldnames );
public     :                                        logical Store (kcb *kcbptr );
public     :                                        logical StoreAll (DLL(kcb) *keylist );
public     :                  OPSImpExp                  pc_SDB_Key (PropertyHandle *prophdl );
};

#endif
