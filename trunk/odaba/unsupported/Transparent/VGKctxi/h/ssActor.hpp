/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sActor

\brief    


\date     $Date: 2006/06/20 11:03:26,68 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sActor_HPP
#define   sActor_HPP

class     sActor;

#include  <sCTX_Structure.hpp>
#include  <ssBase_SharedData.hpp>
class  sActor :public sBase_SharedData
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBInitialize ( );
public     :                                             sActor ( );
public     : virtual                                     ~sActor ( );
};

#endif
