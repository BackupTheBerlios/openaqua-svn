/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSEDSelection

\brief    


\date     $Date: 2006/04/24 13:45:18,30 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSEDSelection_HPP
#define   cSEDSelection_HPP

class     cSEDSelection;

#include  <scSDBResource_Base.hpp>
class  cSEDSelection :public cSDBResource_Base
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     int8 DoAfterSelect ( );
public     :                                                             cSEDSelection ( );
public     : virtual                                                     ~cSEDSelection ( );
};

#endif
