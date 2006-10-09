/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cThesaTree

\brief    


\date     $Date: 2006/04/24 13:02:08,10 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cThesaTree_HPP
#define   cThesaTree_HPP

class     cThesaTree;

class  cThesaTree :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSelect ( );
public     :                                                             cThesaTree ( );
public     : virtual                                                     ~cThesaTree ( );
};

#endif
