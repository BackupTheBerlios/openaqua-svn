/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSelectionTree



\date     $Date: 2006/04/24 13:45:49,49 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSelectionTree_HPP
#define   cSelectionTree_HPP

class     cSelectionTree;

class  cSelectionTree :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterHandleActivated ( );
public     : virtual                             int8 DoAfterSelect ( );
public     :                                                             cSelectionTree ( );
public     : virtual                                                     ~cSelectionTree ( );
};

#endif
