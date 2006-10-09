/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    sODC_Variable



\date     $Date: 2006/05/03 16:36:13,31 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODC_Variable_HPP
#define   sODC_Variable_HPP

class     sODC_Variable;

class     CTX_Structure;
#include  <sDatabaseHandle.hpp>
#include  <ssSDB_Member_base.hpp>
class  sODC_Variable :public sSDB_Member_base
{

public     :
public     :                                        int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     :                                        logical DataTypeCString ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetCastType ( );
public     :                                        logical ParmTypeCString ( );
public     : virtual                                logical SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames );
public     :                                             sODC_Variable ( );
public     : virtual                                     ~sODC_Variable ( );
};

#endif
