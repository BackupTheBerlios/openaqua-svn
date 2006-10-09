/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pUnfallVS

\brief    


\date     $Date: 2006/07/06 14:53:54,98 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pUnfallVS_HPP
#define   pUnfallVS_HPP

class     pUnfallVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pUnfallVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pUnfallVS ( );
public     : virtual                                     ~pUnfallVS ( );
};

#endif
