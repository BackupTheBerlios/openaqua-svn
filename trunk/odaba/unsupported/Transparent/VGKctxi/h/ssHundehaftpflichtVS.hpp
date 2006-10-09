/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sHundehaftpflichtVS

\brief    


\date     $Date: 2006/06/27 12:54:18,59 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sHundehaftpflichtVS_HPP
#define   sHundehaftpflichtVS_HPP

class     sHundehaftpflichtVS;

#include  <sCTX_Structure.hpp>
#include  <ssVS_base.hpp>
class  sHundehaftpflichtVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     :                                             sHundehaftpflichtVS ( );
public     : virtual                                     ~sHundehaftpflichtVS ( );
};

#endif
