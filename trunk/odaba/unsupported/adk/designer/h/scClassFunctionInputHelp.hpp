/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassFunctionInputHelp

\brief    


\date     $Date: 2006/06/21 16:46:52,62 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassFunctionInputHelp_HPP
#define   cClassFunctionInputHelp_HPP

class     cClassFunctionInputHelp;

#include  <scClassInputHelp.hpp>
class  cClassFunctionInputHelp :public cClassInputHelp
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterHandleOpen ( );
public     : virtual                                int8 DoAfterShow ( );
public     : virtual                                int8 DoBeforeDataSet ( );
public     :                                             cClassFunctionInputHelp ( );
public     : virtual                                     ~cClassFunctionInputHelp ( );
};

#endif
