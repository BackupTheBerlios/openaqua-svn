/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cCreatePH

\brief    


\date     $Date: 2006/04/24 13:33:57,27 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cCreatePH_HPP
#define   cCreatePH_HPP

class     cCreatePH;

#include  <sPropertyHandle.hpp>
class  cCreatePH :public CTX_Control
{
protected  :         PropertyHandle                               datasource;                                                // 

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterOpen ( );
public     :                                                             cCreatePH ( );
public     : virtual                                                     ~cCreatePH ( );
};

#endif
