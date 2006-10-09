/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    sSDB_CodeSet



\date     $Date: 2006/04/24 17:05:54,23 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_CodeSet_HPP
#define   sSDB_CodeSet_HPP

class     sSDB_CodeSet;

#include  <sCTX_Structure.hpp>
class  sSDB_CodeSet :protected CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     logical ProvideSDB_ValueList ( );
public     :                                                             sSDB_CodeSet ( );
public     : virtual                                                     ~sSDB_CodeSet ( );
};

#endif
