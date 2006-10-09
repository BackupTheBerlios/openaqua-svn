/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sNotiz

\brief    


\date     $Date: 2006/07/08 12:13:05,31 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sNotiz_HPP
#define   sNotiz_HPP

class     sNotiz;

#include  <sCTX_Structure.hpp>
class  sNotiz :public CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **ctx_str_ptrp );
public     : virtual                                logical DBInitialize ( );
public     : virtual                                logical DBModify ( );
public     : virtual                                logical DBStored ( );
public     :                                        logical InitWV ( );
public     :                                             sNotiz ( );
};

#endif
