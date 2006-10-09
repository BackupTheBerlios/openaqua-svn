/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_HundehaftpflichtVS

\brief    


\date     $Date: 2006/06/29 20:48:16,29 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_HundehaftpflichtVS_HPP
#define   pc0_HundehaftpflichtVS_HPP

class     pc0_HundehaftpflichtVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_HundehaftpflichtVS :public pc0Base_VS
{

public     :
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_HundehaftpflichtVS (PropertyHandle *prophdl );
public     :                                             pc0_HundehaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
