/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cProjectInputHelp

\brief    


\date     $Date: 2006/06/21 16:44:15,17 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cProjectInputHelp_HPP
#define   cProjectInputHelp_HPP

class     cProjectInputHelp;

#include  <scInputHelpBase.hpp>
class  cProjectInputHelp :public cInputHelpBase
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterShow ( );
public     :                                             cProjectInputHelp ( );
public     : virtual                                     ~cProjectInputHelp ( );
};

#endif
