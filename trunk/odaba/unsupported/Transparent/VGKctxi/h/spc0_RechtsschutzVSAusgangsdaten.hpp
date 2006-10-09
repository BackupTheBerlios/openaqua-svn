/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_RechtsschutzVSAusgangsdaten

\brief    


\date     $Date: 2006/07/06 11:48:01,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_RechtsschutzVSAusgangsdaten_HPP
#define   pc0_RechtsschutzVSAusgangsdaten_HPP

class     pc0_RechtsschutzVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_RechtsschutzVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_RechtsschutzVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
