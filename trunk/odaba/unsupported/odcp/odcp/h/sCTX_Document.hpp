/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    CTX_Document

\brief    


\date     $Date: 2006/03/12 19:39:57,98 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Document_HPP
#define   CTX_Document_HPP

class     CTX_Document;

#include  <cCTX_Types.h>
#include  <sCTX_GUIBase.hpp>
class  CTX_Document :public CTX_GUIBase
{

public     :
public     :         ODCP8ImpExp                                         CTX_Document ( );
public     : virtual ODCP8ImpExp                 CTX_Types GetContextType ( );
public     : virtual ODCP8ImpExp                                         ~CTX_Document ( );
};

#endif
