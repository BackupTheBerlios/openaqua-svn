/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cLanguage

\brief    


\date     $Date: 2006/04/24 12:53:43,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cLanguage_HPP
#define   cLanguage_HPP

class     cLanguage;

class  cLanguage :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoAfterSelect ( );
public     :                                                             cLanguage ( );
public     : virtual                                                     ~cLanguage ( );
};

#endif
