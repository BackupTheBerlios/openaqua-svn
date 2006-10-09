/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_HundehaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/07/21 16:27:44,48 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_HundehaftpflichtVSAusgangsdaten_HPP
#define   pc_HundehaftpflichtVSAusgangsdaten_HPP

class     pc_HundehaftpflichtVSAusgangsdaten;

#include  <sPropertyHandle.hpp>
class  pc_HundehaftpflichtVSAusgangsdaten :public PropertyHandle
{

public     :
public     :                                        logical CalculateAnzahlHunde ( );
public     :                                             pc_HundehaftpflichtVSAusgangsdaten (PropertyHandle *prophdl );
};

#endif
