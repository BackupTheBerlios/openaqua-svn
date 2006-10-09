/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cPFunctionRetParms



\date     $Date: 2006/04/24 13:42:59,27 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cPFunctionRetParms_HPP
#define   cPFunctionRetParms_HPP

class     cPFunctionRetParms;

#include  <scNotifyHighContext.hpp>
class  cPFunctionRetParms :public cNotifyHighContext
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoBeforeFillData ( );
public     :                                                             cPFunctionRetParms ( );
public     : virtual                                                     ~cPFunctionRetParms ( );
};

#endif
