/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/21|16:26:03,43}|(REF) - Context that communicates with the output area
\class    cLanguageDependend

\brief    


\date     $Date: 2006/04/24 12:54:28,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cLanguageDependend_HPP
#define   cLanguageDependend_HPP

class     cLanguageDependend;

class  cLanguageDependend :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoBeforeFillData ( );
public     :                                                             cLanguageDependend ( );
public     : virtual                                                     ~cLanguageDependend ( );
};

#endif
