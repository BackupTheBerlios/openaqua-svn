/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Attribute

\brief    


\date     $Date: 2006/03/13 21:30:15,23 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Attribute_HPP
#define   sSDB_Attribute_HPP

class     sSDB_Attribute;

class     CTX_Structure;
#include  <sDatabaseHandle.hpp>
#include  <ssSDB_Member_base.hpp>
class  sSDB_Attribute :public sSDB_Member_base
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames );
public     :                                                             sSDB_Attribute ( );
public     :                                                             ~sSDB_Attribute ( );
};

#endif
