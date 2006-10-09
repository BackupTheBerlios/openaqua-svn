/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pImportProtokoll

\brief    


\date     $Date: 2006/06/29 15:01:38,53 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pImportProtokoll_HPP
#define   pImportProtokoll_HPP

class     pImportProtokoll;

#include  <sCTX_Property.hpp>
class  pImportProtokoll :protected CTX_Property
{

public     :
public     :                                        int32 Create (CTX_Property **ctx_prop_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical ImportXMLAction ( );
public     :                                        logical ImportXMLOpenActions ( );
public     :                                             pImportProtokoll ( );
public     : virtual                                     ~pImportProtokoll ( );
};

#endif
