/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    SystemInput

\brief    


\date     $Date: 2006/08/26 20:42:37,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SystemInput_HPP
#define   SystemInput_HPP

#include "csosdll.h"
class     SystemInput;

#include  <sSystemIO.hpp>
class  SystemInput :public SystemIO
{

public     :
public     : virtual          SOSImpExp             char *Read ( );
public     :                  SOSImpExp                  SystemInput ( );
public     :                                             ~SystemInput ( );
};

#endif
