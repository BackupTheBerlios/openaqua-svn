/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    sSDB_BaseStruct



\date     $Date: 2006/05/13 18:04:37,98 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_BaseStruct_HPP
#define   sSDB_BaseStruct_HPP

class     sSDB_BaseStruct;

class     CTX_Structure;
#include  <sDatabaseHandle.hpp>
#include  <ssSDB_Member_base.hpp>
class  sSDB_BaseStruct :public sSDB_Member_base
{

public     :
public     :                                        int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                                logical DBCreate ( );
public     : virtual                                logical SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames );
public     :                                             sSDB_BaseStruct ( );
public     :                                             ~sSDB_BaseStruct ( );
};

#endif
