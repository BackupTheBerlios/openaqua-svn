/********************************* Class Declaration ***************************/
/**
\package  VGKctxi
\class    sRechtsschutzVS



\date     $Date: 2006/05/17 13:08:25,53 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sRechtsschutzVS_HPP
#define   sRechtsschutzVS_HPP

class     sRechtsschutzVS;

class     CTX_Structure;
#include  <ssVS_base.hpp>
class  sRechtsschutzVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     :                                             sRechtsschutzVS ( );
public     : virtual                                     ~sRechtsschutzVS ( );
};

#endif
