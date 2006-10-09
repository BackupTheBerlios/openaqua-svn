/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pWohngebaeudeVS

\brief    


\date     $Date: 2006/07/06 14:54:06,46 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pWohngebaeudeVS_HPP
#define   pWohngebaeudeVS_HPP

class     pWohngebaeudeVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pWohngebaeudeVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pWohngebaeudeVS ( );
public     : virtual                                     ~pWohngebaeudeVS ( );
};

#endif
