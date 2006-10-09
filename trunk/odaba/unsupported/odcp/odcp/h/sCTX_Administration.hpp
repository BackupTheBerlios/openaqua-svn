/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    CTX_Administration

\brief    


\date     $Date: 2006/03/12 19:39:52,59 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Administration_HPP
#define   CTX_Administration_HPP

class     CTX_Administration;

#include  <cCTX_Types.h>
#include  <sCTX_Application.hpp>
class  CTX_Administration :public CTX_Application
{

public     :
public     :         ODCP8ImpExp                                         CTX_Administration ( );
public     : virtual ODCP8ImpExp                 CTX_Types GetContextType ( );
public     : virtual ODCP8ImpExp                                         ~CTX_Administration ( );
};

#endif
