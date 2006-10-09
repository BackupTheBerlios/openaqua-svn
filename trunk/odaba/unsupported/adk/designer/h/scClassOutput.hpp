/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassOutput

\brief    


\date     $Date: 2006/04/24 13:32:46,34 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassOutput_HPP
#define   cClassOutput_HPP

class     cClassOutput;

class  cClassOutput :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterOpen ( );
public     : virtual                             int8 DoAfterSelect ( );
public     : virtual                             int8 DoBeforeClose ( );
public     :                                                             cClassOutput ( );
public     : virtual                                                     ~cClassOutput ( );
};

#endif
