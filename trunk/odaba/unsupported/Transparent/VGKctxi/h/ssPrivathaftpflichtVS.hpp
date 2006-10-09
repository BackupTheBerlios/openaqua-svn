/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sPrivathaftpflichtVS

\brief    


\date     $Date: 2006/06/15 13:39:52,42 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sPrivathaftpflichtVS_HPP
#define   sPrivathaftpflichtVS_HPP

class     sPrivathaftpflichtVS;

#include  <sCTX_Structure.hpp>
#include  <ssVS_base.hpp>
class  sPrivathaftpflichtVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     :                                             sPrivathaftpflichtVS ( );
public     : virtual                                     ~sPrivathaftpflichtVS ( );
};

#endif
