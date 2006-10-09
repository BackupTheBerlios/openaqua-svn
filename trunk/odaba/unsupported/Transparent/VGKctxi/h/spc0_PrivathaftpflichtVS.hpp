/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_PrivathaftpflichtVS

\brief    


\date     $Date: 2006/06/29 18:30:03,56 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_PrivathaftpflichtVS_HPP
#define   pc0_PrivathaftpflichtVS_HPP

class     pc0_PrivathaftpflichtVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_PrivathaftpflichtVS :public pc0Base_VS
{

public     :
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_PrivathaftpflichtVS (PropertyHandle *prophdl );
public     :                                             pc0_PrivathaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
