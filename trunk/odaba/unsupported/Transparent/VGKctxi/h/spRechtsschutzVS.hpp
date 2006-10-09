/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pRechtsschutzVS

\brief    


\date     $Date: 2006/07/06 14:53:36,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pRechtsschutzVS_HPP
#define   pRechtsschutzVS_HPP

class     pRechtsschutzVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pRechtsschutzVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pRechtsschutzVS ( );
public     : virtual                                     ~pRechtsschutzVS ( );
};

#endif
