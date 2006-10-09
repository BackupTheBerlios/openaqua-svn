/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cFunctionInputHelp

\brief    


\date     $Date: 2006/06/21 16:43:23,52 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cFunctionInputHelp_HPP
#define   cFunctionInputHelp_HPP

class     cFunctionInputHelp;

#include  <scInputHelpBase.hpp>
class  cFunctionInputHelp :public cInputHelpBase
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterShow ( );
public     :                                             cFunctionInputHelp ( );
public     : virtual                                     ~cFunctionInputHelp ( );
};

#endif
