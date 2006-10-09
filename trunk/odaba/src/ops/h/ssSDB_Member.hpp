/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Member

\brief    


\date     $Date: 2006/03/13 21:30:15,43 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Member_HPP
#define   sSDB_Member_HPP

class     sSDB_Member;

#include  <sCTX_Structure.hpp>
class  sSDB_Member :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     :                                     logical DBRead ( );
public     :                                     logical DBStore ( );
public     :                                     logical DataTypeCString ( );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     logical SetupStructReference (logical auto_correct );
public     :                                                             sSDB_Member ( );
public     :                                                             ~sSDB_Member ( );
};

#endif
