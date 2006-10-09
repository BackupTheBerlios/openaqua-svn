/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_NameSpace



\date     $Date: 2006/05/14 11:29:04,10 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_NameSpace_HPP
#define   pc_SDB_NameSpace_HPP

class     pc_SDB_NameSpace;

class     PropertyHandle;
#include  <spc_SDB_Type.hpp>
class  pc_SDB_NameSpace :public pc_SDB_Type
{

public     :
public     :                                        char *Scope (char *string, int32 &len_ref );
public     :                                             pc_SDB_NameSpace (PropertyHandle *prophdl );
public     :                                             pc_SDB_NameSpace (DatabaseHandle &dbhandle, PIACC accopt_w=PI_Read );
public     :                                             pc_SDB_NameSpace (DatabaseHandle &dbhandle, char *strnames, PIACC accopt_w=PI_Read );
};

#endif
