/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sSDB_Structure



\date     $Date: 2006/04/19 22:46:52,06 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Structure_HPP
#define   sSDB_Structure_HPP

class     sSDB_Structure;

#include  <sCTX_Structure.hpp>
class  sSDB_Structure :public CTX_Structure
{

public     :
public     :                                     logical CheckExtentPath ( );
public     :                                     logical CheckPropertyPath ( );
public     :                                     logical CheckStructure ( );
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                                             sSDB_Structure ( );
public     : virtual                                                     ~sSDB_Structure ( );
};

#endif
