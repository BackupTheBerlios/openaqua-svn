/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    pRetvalInODC_Function



\date     $Date: 2006/04/21 14:08:34,23 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pRetvalInODC_Function_HPP
#define   pRetvalInODC_Function_HPP

class     pRetvalInODC_Function;

class  pRetvalInODC_Function :public CTX_Property
{

public     :
public     :                                     int32 Create (CTX_Property **CTX_Property_ptrp );
public     : virtual                             logical DBInserted ( );
public     :                                                             pRetvalInODC_Function ( );
public     : virtual                                                     ~pRetvalInODC_Function ( );
};

#endif
