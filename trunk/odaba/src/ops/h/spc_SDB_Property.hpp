/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_Property



\date     $Date: 2006/05/11 14:27:06,07 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_Property_HPP
#define   pc_SDB_Property_HPP

class     pc_SDB_Property;

class     ErrorProtocol;
class     PropertyHandle;
#include  <spc_SDB_Member.hpp>
class  pc_SDB_Property :public pc_SDB_Member
{

public     :
public     :                  OPSImpExp             logical CheckKeyField (ErrorProtocol *protocol );
public     :                                        logical Store (DBFieldDef *dbflddef );
public     :                  OPSImpExp                  pc_SDB_Property (PropertyHandle *prophdl );
};

#endif
