/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_HausratVSAusgangsdaten

\brief    


\date     $Date: 2006/06/29 11:32:57,64 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_HausratVSAusgangsdaten_HPP
#define   pc0_HausratVSAusgangsdaten_HPP

class     pc0_HausratVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_HausratVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_HausratVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
