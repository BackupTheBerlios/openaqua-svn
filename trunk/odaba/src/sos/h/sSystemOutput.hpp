/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    SystemOutput

\brief    


\date     $Date: 2006/08/27 10:41:07,17 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SystemOutput_HPP
#define   SystemOutput_HPP

#include "csosdll.h"
class     SystemOutput;

#include  <sSystemIO.hpp>
class  SystemOutput :public SystemIO
{

public     :
public     :                  SOSImpExp                  SystemOutput ( );
public     :                  SOSImpExp             logical Write (char *string, logical line_end, logical clear_opt, logical flush_opt );
public     : virtual          SOSImpExp                  ~SystemOutput ( );
};

#endif
