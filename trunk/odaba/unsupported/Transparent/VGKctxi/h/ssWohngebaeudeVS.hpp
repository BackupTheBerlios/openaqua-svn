/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sWohngebaeudeVS

\brief    


\date     $Date: 2006/06/15 13:43:19,23 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sWohngebaeudeVS_HPP
#define   sWohngebaeudeVS_HPP

class     sWohngebaeudeVS;

class     CTX_Structure;
#include  <ssVS_base.hpp>
class  sWohngebaeudeVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     :                                             sWohngebaeudeVS ( );
public     : virtual                                     ~sWohngebaeudeVS ( );
};

#endif
