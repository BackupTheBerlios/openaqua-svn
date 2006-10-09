/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pVS_base

\brief    


\date     $Date: 2006/07/06 14:31:48,87 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pVS_base_HPP
#define   pVS_base_HPP

class     pVS_base;

#include  <sCTX_Property.hpp>
class  pVS_base :protected CTX_Property
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     :                                             pVS_base ( );
public     : virtual                                     ~pVS_base ( );
};

#endif
