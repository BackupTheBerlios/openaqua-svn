/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc0_SDB_ValueList



\date     $Date: 2006/05/23 13:04:54,93 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_SDB_ValueList_HPP
#define   pc0_SDB_ValueList_HPP

class     pc0_SDB_ValueList;

#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc0_SDB_ValueList :public PropertyHandle
{

public     :
public     :                                        logical IsEnumeration (PropertyHandle *prophdl );
public     :                                             pc0_SDB_ValueList (DBObjectHandle &obhandle );
};

#endif
