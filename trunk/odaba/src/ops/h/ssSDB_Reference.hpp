/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Reference

\brief    


\date     $Date: 2006/03/13 21:30:15,71 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Reference_HPP
#define   sSDB_Reference_HPP

class     sSDB_Reference;

class     CTX_Structure;
#include  <sDatabaseHandle.hpp>
#include  <ssSDB_Member_base.hpp>
class  sSDB_Reference :public sSDB_Member_base
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames );
public     :                                                             sSDB_Reference ( );
public     : virtual                                                     ~sSDB_Reference ( );
};

#endif
