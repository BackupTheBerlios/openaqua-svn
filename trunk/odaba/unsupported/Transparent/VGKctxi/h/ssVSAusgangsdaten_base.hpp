/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sVSAusgangsdaten_base

\brief    


\date     $Date: 2006/07/05 23:28:59,12 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sVSAusgangsdaten_base_HPP
#define   sVSAusgangsdaten_base_HPP

class     sVSAusgangsdaten_base;

#include  <sCTX_Structure.hpp>
class  sVSAusgangsdaten_base :public CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreated ( );
public     :                                        logical SetupCollectionsByTyp ( );
public     :                                             sVSAusgangsdaten_base ( );
};

#endif
