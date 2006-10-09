/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    pc_SDB_ValueList



\date     $Date: 2006/05/22 22:44:05,70 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_ValueList_HPP
#define   pc_SDB_ValueList_HPP

class     pc_SDB_ValueList;

class  pc_SDB_ValueList :public PropertyHandle
{

public     :
public     :                                        char *GetDocFileName (NString &nstring );
public     :                  OPSImpExp             logical Initialize (char *basetype, char *scope );
public     :                  OPSImpExp                  pc_SDB_ValueList (PropertyHandle *prophdl );
};

#endif
