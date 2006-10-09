/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_WohngebaeudeVS

\brief    


\date     $Date: 2006/07/20 16:50:08,45 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_WohngebaeudeVS_HPP
#define   pc0_WohngebaeudeVS_HPP

class     pc0_WohngebaeudeVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_WohngebaeudeVS :public pc0Base_VS
{

public     :
public     :                                        logical CalculateVersicherungssumme ( );
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_WohngebaeudeVS (PropertyHandle *prophdl );
public     :                                             pc0_WohngebaeudeVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
