/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_PrivathaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/06/29 18:12:40,73 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_PrivathaftpflichtVSAusgangsdaten_HPP
#define   pc0_PrivathaftpflichtVSAusgangsdaten_HPP

class     pc0_PrivathaftpflichtVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_PrivathaftpflichtVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_PrivathaftpflichtVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
