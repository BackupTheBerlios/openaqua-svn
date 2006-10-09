/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDoubleTabSlave

\brief    


\date     $Date: 2006/04/24 13:35:26,04 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cDoubleTabSlave_HPP
#define   cDoubleTabSlave_HPP

class     cDoubleTabSlave;

class  cDoubleTabSlave :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSelect ( );
};

#endif
