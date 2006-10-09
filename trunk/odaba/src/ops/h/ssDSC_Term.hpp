/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sDSC_Term

\brief    


\date     $Date: 2006/03/13 21:30:14,89 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sDSC_Term_HPP
#define   sDSC_Term_HPP

class     sDSC_Term;

class     CTX_Structure;
#include  <ssLanguageDependend.hpp>
#pragma pack(8)

class  sDSC_Term :public sLanguageDependend
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     :                                                             sDSC_Term ( );
public     : virtual                                                     ~sDSC_Term ( );
};

#pragma pack()
#endif
