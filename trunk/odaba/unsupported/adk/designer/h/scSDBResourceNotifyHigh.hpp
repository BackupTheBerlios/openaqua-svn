/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDBResourceNotifyHigh

\brief    


\date     $Date: 2006/06/03 15:05:24,37 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSDBResourceNotifyHigh_HPP
#define   cSDBResourceNotifyHigh_HPP

class     cSDBResourceNotifyHigh;

#include  <scSDBResource_Base.hpp>
class  cSDBResourceNotifyHigh :public cSDBResource_Base
{

public     :
public     :                                        logical Changed ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterSelect ( );
public     : virtual                                int8 DoAfterStoreData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             cSDBResourceNotifyHigh ( );
public     : virtual                                     ~cSDBResourceNotifyHigh ( );
};

#endif
