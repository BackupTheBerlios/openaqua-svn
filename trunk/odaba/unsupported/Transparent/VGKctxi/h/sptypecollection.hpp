/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    ptypecollection

\brief    


\date     $Date: 2006/06/20 15:09:51,71 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ptypecollection_HPP
#define   ptypecollection_HPP

class     ptypecollection;

#include  <sCTX_Property.hpp>
class  ptypecollection :protected CTX_Property
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetupCollectionByTyp ( );
public     :                                             ptypecollection ( );
public     : virtual                                     ~ptypecollection ( );
};

#endif
