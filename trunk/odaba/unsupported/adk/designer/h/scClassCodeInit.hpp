/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassCodeInit

\brief    Context for init code in CPP functions and OSI expressions2


\date     $Date: 2006/06/01 16:43:00,42 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassCodeInit_HPP
#define   cClassCodeInit_HPP

class     cClassCodeInit;

#include  <scClassCodeBase.hpp>
class  cClassCodeInit :public cClassCodeBase
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetupInitCode ( );
public     :                                             cClassCodeInit ( );
public     : virtual                                     ~cClassCodeInit ( );
};

#endif
