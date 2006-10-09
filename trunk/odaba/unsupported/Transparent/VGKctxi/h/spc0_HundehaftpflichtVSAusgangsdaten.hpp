/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_HundehaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/06/29 19:06:17,17 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_HundehaftpflichtVSAusgangsdaten_HPP
#define   pc0_HundehaftpflichtVSAusgangsdaten_HPP

class     pc0_HundehaftpflichtVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_HundehaftpflichtVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_HundehaftpflichtVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
