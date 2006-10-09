/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pHundehaftpflichtVS

\brief    


\date     $Date: 2006/07/06 14:52:58,12 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pHundehaftpflichtVS_HPP
#define   pHundehaftpflichtVS_HPP

class     pHundehaftpflichtVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pHundehaftpflichtVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pHundehaftpflichtVS ( );
public     : virtual                                     ~pHundehaftpflichtVS ( );
};

#endif
