/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Type

\brief    


\date     $Date: 2006/03/13 21:30:16,03 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sSDB_Type_HPP
#define   sSDB_Type_HPP

class     sSDB_Type;

#include  <sCTX_Structure.hpp>
class  sSDB_Type :public CTX_Structure
{

public     :
public     :                                     int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                             logical DBOpened ( );
public     :                                                             sSDB_Type ( );
public     : virtual                                                     ~sSDB_Type ( );
};

#endif
