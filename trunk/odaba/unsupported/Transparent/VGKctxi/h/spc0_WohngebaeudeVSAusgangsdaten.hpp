/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_WohngebaeudeVSAusgangsdaten

\brief    


\date     $Date: 2006/07/01 23:51:20,31 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_WohngebaeudeVSAusgangsdaten_HPP
#define   pc0_WohngebaeudeVSAusgangsdaten_HPP

class     pc0_WohngebaeudeVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_WohngebaeudeVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_WohngebaeudeVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
