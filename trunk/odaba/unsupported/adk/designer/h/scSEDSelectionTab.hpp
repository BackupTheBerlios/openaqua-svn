/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSEDSelectionTab



\date     $Date: 2006/04/24 13:45:32,73 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSEDSelectionTab_HPP
#define   cSEDSelectionTab_HPP

class     cSEDSelectionTab;

class  cSEDSelectionTab :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSelect ( );
public     :                                                             cSEDSelectionTab ( );
public     : virtual                                                     ~cSEDSelectionTab ( );
};

#endif
