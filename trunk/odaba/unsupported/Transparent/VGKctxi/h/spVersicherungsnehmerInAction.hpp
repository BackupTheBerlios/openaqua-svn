/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pVersicherungsnehmerInAction

\brief    


\date     $Date: 2006/07/07 12:32:49,68 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pVersicherungsnehmerInAction_HPP
#define   pVersicherungsnehmerInAction_HPP

class     pVersicherungsnehmerInAction;

#include  <sCTX_Property.hpp>
class  pVersicherungsnehmerInAction :protected CTX_Property
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical DBInserted ( );
public     :                                             pVersicherungsnehmerInAction ( );
public     : virtual                                     ~pVersicherungsnehmerInAction ( );
};

#endif
