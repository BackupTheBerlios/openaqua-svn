/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    sSDB_Member_base



\date     $Date: 2006/05/13 18:03:40,73 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Member_base_HPP
#define   sSDB_Member_base_HPP

class     sSDB_Member_base;

#include  <sCTX_Structure.hpp>
#include  <sDatabaseHandle.hpp>
class  sSDB_Member_base :public CTX_Structure
{

public     :
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetScopedType ( );
public     :                                        logical SetDefaults ( );
public     : virtual                                logical SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames );
public     :                                             sSDB_Member_base ( );
public     :                                             ~sSDB_Member_base ( );
};

#endif
