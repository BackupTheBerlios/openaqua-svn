/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_KFZVSAusgangsdaten

\brief    


\date     $Date: 2006/07/03 16:56:17,39 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_KFZVSAusgangsdaten_HPP
#define   pc0_KFZVSAusgangsdaten_HPP

class     pc0_KFZVSAusgangsdaten;

class     PropertyHandle;
class     TP_ImportGlobals;
#include  <spc0_Ausgangsdaten.hpp>
class  pc0_KFZVSAusgangsdaten :public pc0_Ausgangsdaten
{

public     :
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_KFZVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
