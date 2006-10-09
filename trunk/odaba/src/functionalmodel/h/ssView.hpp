/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    sView

\brief    


\date     $Date: 2006/03/13 21:30:36,85 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sView_HPP
#define   sView_HPP

class     sView;

#include  <sCTX_Structure.hpp>
#pragma pack(8)

class  sView :public CTX_Structure
{

public     :
public     :                                     logical Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical DBCreate ( );
public     :                                                             sView ( );
public     : virtual                                                     ~sView ( );
};

#pragma pack()
#endif
