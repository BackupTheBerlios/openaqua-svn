/********************************* Class Declaration ***************************/
/**
\package  VGKctxi
\class    sUnfallVS



\date     $Date: 2006/05/17 13:09:14,23 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sUnfallVS_HPP
#define   sUnfallVS_HPP

class     sUnfallVS;

class     CTX_Structure;
#include  <ssVS_base.hpp>
class  sUnfallVS :public sVS_base
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBCreate ( );
public     : virtual                                logical DBCreated ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical Export ( );
public     :                                        logical SetupCollectionsByTyp ( );
public     :                                             sUnfallVS ( );
public     : virtual                                     ~sUnfallVS ( );
};

#endif
