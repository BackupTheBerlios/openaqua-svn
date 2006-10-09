/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_UnfallVSAusgangsdaten

\brief    


\date     $Date: 2006/07/03 11:32:03,35 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_UnfallVSAusgangsdaten_HPP
#define   pc0_UnfallVSAusgangsdaten_HPP

class     pc0_UnfallVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_UnfallVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_UnfallVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
