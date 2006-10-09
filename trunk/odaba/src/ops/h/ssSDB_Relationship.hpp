/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Relationship

\brief    


\date     $Date: 2006/03/13 21:30:15,81 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Relationship_HPP
#define   sSDB_Relationship_HPP

class     sSDB_Relationship;

class     CTX_Structure;
#include  <sDatabaseHandle.hpp>
#include  <ssSDB_Member_base.hpp>
class  sSDB_Relationship :public sSDB_Member_base
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames );
public     :                                                             sSDB_Relationship ( );
public     : virtual                                                     ~sSDB_Relationship ( );
};

#endif
