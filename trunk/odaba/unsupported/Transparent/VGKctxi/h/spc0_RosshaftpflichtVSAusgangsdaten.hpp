/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_RosshaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/06/29 21:10:23,06 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_RosshaftpflichtVSAusgangsdaten_HPP
#define   pc0_RosshaftpflichtVSAusgangsdaten_HPP

class     pc0_RosshaftpflichtVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_RosshaftpflichtVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_RosshaftpflichtVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
