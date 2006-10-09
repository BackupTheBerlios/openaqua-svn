/********************************* Class Declaration ***************************/
/**
\package  VGKctxi
\class    pleistungen_base



\date     $Date: 2006/05/15 21:12:41,70 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pleistungen_base_HPP
#define   pleistungen_base_HPP

class     pleistungen_base;

#include  <sCTX_Property.hpp>
class  pleistungen_base :public CTX_Property
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetupCollectionByTyp ( );
public     :                                             pleistungen_base ( );
public     : virtual                                     ~pleistungen_base ( );
};

#endif
