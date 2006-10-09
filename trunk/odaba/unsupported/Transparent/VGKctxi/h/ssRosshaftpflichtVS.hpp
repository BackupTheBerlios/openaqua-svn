/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sRosshaftpflichtVS

\brief    


\date     $Date: 2006/06/27 12:56:05,06 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sRosshaftpflichtVS_HPP
#define   sRosshaftpflichtVS_HPP

class     sRosshaftpflichtVS;

#include  <sCTX_Structure.hpp>
#include  <ssVS_base.hpp>
class  sRosshaftpflichtVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     :                                             sRosshaftpflichtVS ( );
public     : virtual                                     ~sRosshaftpflichtVS ( );
};

#endif
