/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_RosshaftpflichtVS

\brief    


\date     $Date: 2006/06/29 21:21:10,75 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_RosshaftpflichtVS_HPP
#define   pc0_RosshaftpflichtVS_HPP

class     pc0_RosshaftpflichtVS;

class     TP_ImportGlobals;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_RosshaftpflichtVS :public pc0Base_VS
{

public     :
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                             pc0_RosshaftpflichtVS (PropertyHandle *prophdl );
public     :                                             pc0_RosshaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
