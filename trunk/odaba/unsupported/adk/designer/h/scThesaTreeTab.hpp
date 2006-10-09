/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cThesaTreeTab

\brief    


\date     $Date: 2006/04/24 13:02:19,09 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cThesaTreeTab_HPP
#define   cThesaTreeTab_HPP

class     cThesaTreeTab;

class  cThesaTreeTab :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     int8 DoAfterSelect ( );
public     :                                                             cThesaTreeTab ( );
public     :                                                             ~cThesaTreeTab ( );
};

#endif
