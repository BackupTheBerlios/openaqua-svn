/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_RechtsschutzVS

\brief    


\date     $Date: 2006/07/03 10:51:45,18 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_RechtsschutzVS_HPP
#define   pc0_RechtsschutzVS_HPP

class     pc0_RechtsschutzVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_RechtsschutzVS :public pc0Base_VS
{

public     :
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_RechtsschutzVS (PropertyHandle *prophdl );
public     :                                             pc0_RechtsschutzVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
