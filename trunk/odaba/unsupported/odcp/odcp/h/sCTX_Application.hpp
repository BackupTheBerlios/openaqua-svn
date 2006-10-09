/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    CTX_Application

\brief    


\date     $Date: 2006/03/12 19:39:53,70 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Application_HPP
#define   CTX_Application_HPP

class     CTX_Application;

#include  <cCTX_Types.h>
#include  <sCTX_Control.hpp>
class  CTX_Application :public CTX_Control
{

public     :
public     :         ODCP8ImpExp                                         CTX_Application ( );
public     : virtual ODCP8ImpExp                 CTX_Types GetContextType ( );
public     : virtual ODCP8ImpExp                                         ~CTX_Application ( );
};

#endif
