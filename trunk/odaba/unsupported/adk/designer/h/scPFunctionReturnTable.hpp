/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cPFunctionReturnTable

\brief    


\date     $Date: 2006/04/24 13:43:25,65 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cPFunctionReturnTable_HPP
#define   cPFunctionReturnTable_HPP

class     cPFunctionReturnTable;

#include  <scSDBResourceNotifyHigh.hpp>
#include  <scSDBResource_Base.hpp>
class  cPFunctionReturnTable :public cSDBResourceNotifyHigh
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSaveData ( );
public     : virtual                             int8 DoAfterStoreData ( );
public     :                                                             cPFunctionReturnTable ( );
public     : virtual                                                     ~cPFunctionReturnTable ( );
};

#endif
