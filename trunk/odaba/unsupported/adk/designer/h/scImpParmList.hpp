/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cImpParmList

\brief    


\date     $Date: 2006/04/24 13:37:55,87 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cImpParmList_HPP
#define   cImpParmList_HPP

class     cImpParmList;

#include  <scSDBResourceNotifyHigh.hpp>
class  cImpParmList :public cSDBResourceNotifyHigh
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterDeleteData ( );
public     : virtual                             int8 DoAfterInsertData ( );
public     : virtual                             int8 DoAfterSaveData ( );
public     : virtual                             int8 DoAfterSelect ( );
public     :                                     logical SetupHeadline ( );
public     :                                                             cImpParmList ( );
public     : virtual                                                     ~cImpParmList ( );
};

#endif
