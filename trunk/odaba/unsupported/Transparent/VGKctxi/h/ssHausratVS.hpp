/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sHausratVS

\brief    


\date     $Date: 2006/06/26 15:55:48,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sHausratVS_HPP
#define   sHausratVS_HPP

class     sHausratVS;

class     CTX_Structure;
#include  <ssVS_base.hpp>
class  sHausratVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     :                                             sHausratVS ( );
public     : virtual                                     ~sHausratVS ( );
};

#endif
