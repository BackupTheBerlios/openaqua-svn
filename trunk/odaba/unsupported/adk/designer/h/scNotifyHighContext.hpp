/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cNotifyHighContext

\brief    


\date     $Date: 2006/06/03 15:05:23,25 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cNotifyHighContext_HPP
#define   cNotifyHighContext_HPP

class     cNotifyHighContext;

class  cNotifyHighContext :public CTX_Control
{

public     :
public     : virtual                                logical Changed ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        int8 DoAfterSelect ( );
public     :                                        int8 DoAfterStoreData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
};

#endif
