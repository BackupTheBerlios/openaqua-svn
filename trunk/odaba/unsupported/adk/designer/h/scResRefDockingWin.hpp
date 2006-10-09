/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cResRefDockingWin



\date     $Date: 2006/03/12 19:36:32,17 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cResRefDockingWin_HPP
#define   cResRefDockingWin_HPP

class     cResRefDockingWin;

class  cResRefDockingWin :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterDock ( );
public     : virtual                             int8 DoAfterOpen ( );
public     : virtual                             int8 DoAfterUndock ( );
public     :                                                             cResRefDockingWin ( );
public     : virtual                                                     ~cResRefDockingWin ( );
};

#endif
