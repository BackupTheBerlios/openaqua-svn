/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pHausratVS

\brief    


\date     $Date: 2006/07/06 14:39:54,23 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pHausratVS_HPP
#define   pHausratVS_HPP

class     pHausratVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pHausratVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pHausratVS ( );
public     : virtual                                     ~pHausratVS ( );
};

#endif
