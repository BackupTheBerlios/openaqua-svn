/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassCode



\date     $Date: 2006/06/01 16:20:12,85 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassCode_HPP
#define   cClassCode_HPP

class     cClassCode;

#define  ERR_MACRO_POS                             52
#include  <scClassCodeBase.hpp>
class  cClassCode :public cClassCodeBase
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterStoreData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical InsertCheckError ( );
public     :                                        logical InsertErrString (char *text );
public     :                                        logical InsertError ( );
public     :                                        logical InsertErrorNum ( );
public     :                                        logical InsertLeaveseq ( );
public     :                                        logical InsertProjError ( );
public     :                                             cClassCode ( );
public     : virtual                                     ~cClassCode ( );
};

#endif
