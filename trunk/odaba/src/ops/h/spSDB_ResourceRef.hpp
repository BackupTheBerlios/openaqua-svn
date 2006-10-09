/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    pSDB_ResourceRef



\date     $Date: 2006/03/13 21:30:14,59 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pSDB_ResourceRef_HPP
#define   pSDB_ResourceRef_HPP

class     pSDB_ResourceRef;

#include  <sCTX_Property.hpp>
class  pSDB_ResourceRef :public CTX_Property
{

public     :
public     :                                     int32 Create (CTX_Property **propctx_ptrp );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     logical WriteContextFiles ( );
public     :                                     logical WriteContextFiles (char *project, char *path );
public     :                                                             pSDB_ResourceRef ( );
public     : virtual                                                     ~pSDB_ResourceRef ( );
};

#endif
