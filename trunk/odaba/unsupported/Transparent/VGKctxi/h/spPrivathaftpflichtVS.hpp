/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pPrivathaftpflichtVS

\brief    


\date     $Date: 2006/07/06 14:53:23,73 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pPrivathaftpflichtVS_HPP
#define   pPrivathaftpflichtVS_HPP

class     pPrivathaftpflichtVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pPrivathaftpflichtVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pPrivathaftpflichtVS ( );
public     : virtual                                     ~pPrivathaftpflichtVS ( );
};

#endif
