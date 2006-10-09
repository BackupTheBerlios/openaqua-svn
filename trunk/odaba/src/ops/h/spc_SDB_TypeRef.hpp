/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/27|20:15:43,93}|(REF)
\class    pc_SDB_TypeRef



\date     $Date: 2006/04/05 23:01:26,71 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_TypeRef_HPP
#define   pc_SDB_TypeRef_HPP

class     pc_SDB_TypeRef;

class  pc_SDB_TypeRef :public PropertyHandle
{

public     :
public     :         OPSImpExp                   void SetCodeLevel (int16 codelev, logical exact );
public     :         OPSImpExp                   void SetIncLevel (int16 inclev, logical exact );
public     :         OPSImpExp                   logical SetupReference (int16 inclev, int16 codelev, logical gen_opt );
public     :         OPSImpExp                                           pc_SDB_TypeRef (PropertyHandle *prophdl );
};

#endif
