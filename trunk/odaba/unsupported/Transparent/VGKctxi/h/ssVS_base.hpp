/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sVS_base

\brief    


\date     $Date: 2006/07/11 19:11:01,96 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sVS_base_HPP
#define   sVS_base_HPP

class     sVS_base;

#include  <sCTX_Structure.hpp>
class  sVS_base :public CTX_Structure
{

public     :
public     :                                        logical DBCreate_intern (char *sparte_str );
public     : virtual                                logical DBCreated ( );
public     : virtual                                logical DBOpened ( );
public     :                                        logical DBRead ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical FillIdentifier ( );
public     :                                        logical SetupCollectionsByTyp ( );
public     :                                             sVS_base ( );
public     : virtual                                     ~sVS_base ( );
};

#endif
