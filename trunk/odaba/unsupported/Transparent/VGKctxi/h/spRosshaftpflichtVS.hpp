/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pRosshaftpflichtVS

\brief    


\date     $Date: 2006/07/06 14:53:45,75 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pRosshaftpflichtVS_HPP
#define   pRosshaftpflichtVS_HPP

class     pRosshaftpflichtVS;

#include  <sCTX_Property.hpp>
#include  <spVS_base.hpp>
class  pRosshaftpflichtVS :public pVS_base
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetSparte ( );
public     :                                             pRosshaftpflichtVS ( );
public     : virtual                                     ~pRosshaftpflichtVS ( );
};

#endif
